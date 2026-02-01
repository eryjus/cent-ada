//=================================================================================================================
//  parser/ch4/name.cc -- All the different methods for handling a name production
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  Sample of the complexity here, which will drive some serious left-factoring.
//
//  name ::= simple_name                // TOK_IDENTIFIER
//         | character_literal          // TOK_CHARACTER_LITERAL
//         | operator_symbol            // "<", "<=", etc.
//         | indexed_component          // prefix TOK_LPAREN expression {,expression} TOK_RPAREN
//         | slice                      // prefix TOK_LPAREN expression TOK_DOUBLE_FOT expression TOK_RPAREN
//         | selected_component         // prefix TOK_DOT selector
//         | attribute                  // prefix TOK_APOSTROPHE attribute_designator
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- For Chapter 4, a `name` is the top-level production
//
//    This production is used for all things 'name' outside of an expression
//    ----------------------------------------------------------------------
NamePtr Parser::ParseNameNonExpr(void)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "name(non-expr)");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr rv = nullptr;

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        m.Commit();

        return std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload()));
    }


    rv = ParseSimpleName();
    if (rv) { m.Commit(); return rv; }

    rv = ParseOperatorSymbol();
    if (rv) { m.Commit(); return rv; }

    rv = ParseIndexedComponent();
    if (rv) { m.Commit(); return rv; }

    rv = ParseSlice();
    if (rv) { m.Commit(); return rv; }

    rv = ParseSelectedComponent();
    if (rv) { m.Commit(); return rv; }

    rv = ParseAttribute();
    if (rv) { m.Commit(); return rv; }


    return nullptr;
}



//
// -- For Chapter 4, a `name` is the top-level production
//
//    This production is used for all things 'name' for an expression production
//
//    The production for `name` needs to be refactored to eliminate indirect
//    left recursion into a `base + suffix` form.  Therefore, 2 new functions
//    are added here for `ParseName_Base` and `ParseName_Suffix` to handle
//    all things which are `name` cleanly without left recursion.
//    ------------------------------------------------------------------------
NamePtr Parser::ParseNameExpr(void)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "name(expr)");
    MarkStream m(tokens, diags);
    NamePtr pre = nullptr;
    NamePtr wrk = nullptr;


    TOKEN;


    pre = ParseName_Base();
    if (!pre) return nullptr;

    TOKEN;

    wrk = ParseName_Postfix(pre);
    while (wrk) {
        pre = std::move(wrk);
        TOKEN;
        wrk = ParseName_Postfix(pre);
    }

    m.Commit();

    return pre;
}



//
// -- Parse a Name (Base)
//
//    These alternatives are not dependent on `name` and therefore MUST
//    consume a token from the stream.
//    -----------------------------------------------------------------
NamePtr Parser::ParseName_Base(void)
{
    Production p(*this, "name(base)");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr rv = nullptr;

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        m.Commit();

        return std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload()));
    }


    rv = ParseSimpleName();
    if (rv) {
        m.Commit();
        return rv;
    }

    rv = ParseOperatorSymbol();
    if (rv) {
        m.Commit();
        return rv;
    }


    return nullptr;
}



//
// -- Parse a Name (Postfix)
//
//    These alternatives depend on name, so the concrete tokens have
//    aready been factored out.  These alternatives are anything which
//    can legally follow a base.
//    ----------------------------------------------------------------
NamePtr Parser::ParseName_Postfix(NamePtr &prefix)
{
    Production p(*this, "name(postfix)");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr rv = nullptr;
    SelectedNamePtr selected = nullptr;
    AttributeNamePtr attr = nullptr;

    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        rv = ParseName_IndexOrSliceSuffix(prefix);
        if (rv) {
            SourceLoc_t loc = tokens.SourceLocation();
            if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
                diags.Error(loc, DiagID::MissingRightParen, { "index or selected component" } );
            }

            m.Commit();

            return rv;
        }
    }


    selected = ParseName_SelectedComponentSuffix(prefix);
    if (selected) {
        m.Commit();

        return selected;
    }


    attr = ParseName_AttributeSuffix(prefix);
    if (attr) {
        m.Commit();

        return attr;
    }


    return nullptr;
}



//
// -- Parse either a Indexed or Selected component
//    --------------------------------------------
NamePtr Parser::ParseName_IndexOrSliceSuffix(NamePtr &prefix)
{
    Production p(*this, "name(index_or_selected_component)");
    MarkStream m(tokens, diags);
    NamePtr rv = nullptr;

    m.Reset();
    rv = ParseName_SliceSuffix(prefix);
    if (rv) {
        m.Commit();
        return rv;
    }


    m.Reset();
    rv = ParseName_IndexComponentSuffix(prefix);
    if (rv) {
        m.Commit();
        return rv;
    }


    m.Reset();
    rv = ParseName_SelectedComponentSuffix(prefix);
    if (rv) {
        m.Commit();
        return rv;
    }


    return nullptr;
}



//
// -- Parse a name which will be a Type name (maybe incomplete)
//    ---------------------------------------------------------
NamePtr Parser::ParseTypeName(void) {
    Production p(*this, "Name(type)");
    NamePtr name = nullptr;

    name = ParseNameNonExpr();
    if (!name) return nullptr;
    const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

    if (vec) {
        for (int i = 0; i < vec->size(); i ++) {
            if (vec->at(i)->kind == Symbol::SymbolKind::Type) return name;
            if (vec->at(i)->kind == Symbol::SymbolKind::IncompleteType) return name;
        }
    }

    p.At("failed");
    return nullptr;
}




//
// -- Parse a name which will be a subtype name
//    -----------------------------------------
NamePtr Parser::ParseSubtypeName(void) {
    Production p(*this, "Name(Subtype)");
    NamePtr name = nullptr;

    name = ParseNameNonExpr();
    if (!name) return nullptr;

    const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

    if (!vec || vec->empty()) return nullptr;

    for (int i = 0; i < vec->size(); i ++) {
        if (vec->at(i)->kind == Symbol::SymbolKind::Type) {
            TypeSymbol *tp = static_cast<TypeSymbol *>(vec->at(i));
            if (tp->category == TypeSymbol::TypeCategory::Subtype) return name;
        }
    }

    return nullptr;
}

