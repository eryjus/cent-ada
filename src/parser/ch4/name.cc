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
NamePtr Parser::ParseNameNonExpr(Id &id)
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

    if ((rv = std::move(ParseSimpleName())) != nullptr)             return rv;
    if ((rv = std::move(ParseOperatorSymbol())) != nullptr)         return rv;
    if ((rv = std::move(ParseIndexedComponent())) != nullptr)       return rv;
    if ((rv = std::move(ParseSlice())) != nullptr)                  return rv;
    if ((rv = std::move(ParseSelectedComponent())) != nullptr)      return rv;
    if ((rv = std::move(ParseAttribute())) != nullptr)              return rv;

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
bool Parser::ParseNameExpr(Id &id)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "name(expr)");
    MarkStream m(tokens, diags);

    if (!ParseName_Base(id))        return false;

    while (ParseName_Postfix()) {
        // -- Do something important here
    }

    m.Commit();
    return true;
}



//
// -- Parse a Name (Base)
//
//    These alternatives are not dependent on `name` and therefore MUST
//    consume a token from the stream.
//    -----------------------------------------------------------------
bool Parser::ParseName_Base(Id &id)
{
    Production p(*this, "name(base)");
    MarkStream m(tokens, diags);

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }

    if (m.CommitIf(ParseSimpleName() != nullptr))                return true;
    if (ParseOperatorSymbol() != nullptr)              return true;

    return false;
}



//
// -- Parse a Name (Postfix)
//
//    These alternatives depend on name, so the concrete tokens have
//    aready been factored out.  These alternatives are anything which
//    can legally follow a base.
//    ----------------------------------------------------------------
bool Parser::ParseName_Postfix(void)
{
    Production p(*this, "name(postfix)");
    MarkStream m(tokens, diags);

    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        if (ParseName_IndexOrSliceSuffix()) {
            SourceLoc_t loc = tokens.SourceLocation();
            if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
                diags.Error(loc, DiagID::MissingRightParen, { "index or selected component" } );
            }

            m.Commit();
            return true;
        }
    }

    if (m.CommitIf(ParseName_SelectedComponentSuffix()))    return true;
    if (m.CommitIf(ParseName_AttributeSuffix()))            return true;

    return false;
}



//
// -- Parse either a Indexed or Selected component
//    --------------------------------------------
bool Parser::ParseName_IndexOrSliceSuffix(void)
{
    Production p(*this, "name(index_or_selected_component)");
    MarkStream m(tokens, diags);

    m.Reset();
    if (ParseName_SliceSuffix()) {
        // -- do something important here
        m.Commit();
        return true;
    }


    if (ParseName_IndexComponentSuffix()) {
        // -- do something important here
        m.Commit();
        return true;
    }


    m.Reset();
    if (ParseName_SelectedComponentSuffix()) {
        // -- do something important here
        m.Commit();
        return true;
    }

    return false;
}



//
// -- Parse a name which will be a Type name (maybe incomplete)
//    ---------------------------------------------------------
Id Parser::ParseTypeName(void) {
    Id id;
    if (!ParseNameNonExpr(id)) return { "", tokens.EmptyLocation() };
    const std::vector<Symbol *> *vec = scopes.Lookup(id.name);
    if (vec) {
        for (int i = 0; i < vec->size(); i ++) {
            if (vec->at(i)->kind == Symbol::SymbolKind::Type) return id;
            if (vec->at(i)->kind == Symbol::SymbolKind::IncompleteType) return id;
        }
    }


    return { "", tokens.EmptyLocation() };
}




//
// -- Parse a name which will be a subtype name
//    -----------------------------------------
Id Parser::ParseSubtypeName(void) {
    Id id;
    if (!ParseNameNonExpr(id)) return { "", tokens.EmptyLocation() };
    const std::vector<Symbol *> *vec = scopes.Lookup(id.name);
    if (!vec || vec->empty()) return { "", tokens.EmptyLocation() };
    for (int i = 0; i < vec->size(); i ++) {
        if (vec->at(i)->kind == Symbol::SymbolKind::Type) {
            TypeSymbol *tp = static_cast<TypeSymbol *>(vec->at(i));
            if (tp->category == TypeSymbol::TypeCategory::Subtype) return id;
        }
    }

    return { "", tokens.EmptyLocation() };
}

