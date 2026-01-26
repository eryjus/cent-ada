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
    SourceLoc_t astLoc;

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        CharacterLiteralNamePtr rv = std::move(std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload())));
        m.Commit();
        return std::move(rv);
    }

    NamePtr rv = nullptr;

    if ((rv = std::move(ParseSimpleName())) != nullptr)             { m.Commit(); return rv; }
    if ((rv = std::move(ParseOperatorSymbol())) != nullptr)         { m.Commit(); return rv; }
    if ((rv = std::move(ParseIndexedComponent())) != nullptr)       { m.Commit(); return rv; }
    if ((rv = std::move(ParseSlice())) != nullptr)                  { m.Commit(); return rv; }
    if ((rv = std::move(ParseSelectedComponent())) != nullptr)      { m.Commit(); return rv; }
    if ((rv = std::move(ParseAttribute())) != nullptr)              { m.Commit(); return rv; }

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
    NamePtr rv = nullptr;

    if ((rv = ParseName_Base()) == nullptr)        return nullptr;

    while (ParseName_Postfix(rv)) {
        // -- Do something important here
    }

    m.Commit();
    return std::move(rv);
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
    NamePtr rv = nullptr;
    SourceLoc_t astLoc = tokens.SourceLocation();

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        rv = std::move(std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload())));
        m.Commit();
        return std::move(rv);
    }

    if ((rv = std::move(ParseSimpleName())) != nullptr)                return rv;
    if ((rv = std::move(ParseOperatorSymbol())) != nullptr)            return rv;

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

    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        if ((rv = std::move(ParseName_IndexOrSliceSuffix(prefix))) != nullptr) {
            SourceLoc_t loc = tokens.SourceLocation();
            if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
                diags.Error(loc, DiagID::MissingRightParen, { "index or selected component" } );
            }

            m.Commit();
            return std::move(rv);
        }
    }

    if (ParseName_SelectedComponentSuffix(prefix) != nullptr) {
        m.Commit();
        return rv;
    }

    if ((rv = ParseName_AttributeSuffix(prefix)) != nullptr) {
        m.Commit();
        return rv;
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
    if (ParseName_SliceSuffix(prefix)) {
        // -- do something important here
        m.Commit();
        return rv;
    }


    m.Reset();
    if ((rv = std::move(ParseName_IndexComponentSuffix(prefix))) != nullptr) {
        m.Commit();
        return rv;
    }


    m.Reset();
    if (ParseName_SelectedComponentSuffix(prefix) != nullptr) {
        // -- do something important here
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

    if ((name = std::move(ParseNameNonExpr())) == nullptr) return nullptr;
    const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

    if (vec) {
        for (int i = 0; i < vec->size(); i ++) {
            if (vec->at(i)->kind == Symbol::SymbolKind::Type) return std::move(name);
            if (vec->at(i)->kind == Symbol::SymbolKind::IncompleteType) return std::move(name);
        }
    }

    p.At("failed");
    return nullptr;
}




//
// -- Parse a name which will be a subtype name
//    -----------------------------------------
NamePtr Parser::ParseSubtypeName(void) {
    NamePtr name = nullptr;

    if ((name = std::move(ParseNameNonExpr())) == nullptr) return nullptr;
    const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

    if (!vec || vec->empty()) return nullptr;

    for (int i = 0; i < vec->size(); i ++) {
        if (vec->at(i)->kind == Symbol::SymbolKind::Type) {
            TypeSymbol *tp = static_cast<TypeSymbol *>(vec->at(i));
            if (tp->category == TypeSymbol::TypeCategory::Subtype) return std::move(name);
        }
    }

    return nullptr;
}

