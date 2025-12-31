//=================================================================================================================
//  parser/ch3/enumeration-literal.cc -- Parse an enumeration literal
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  enumeration_literal ::= identifier | character_literal
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse an Enumeration Literal
//    ----------------------------
bool Parser::ParseEnumerationLiteral(EnumTypeSymbol *type)
{
    Production p(*this, "enumeration_literal");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();
    Id id;
    EnumLiteralSymbol *sym;
    YYSTYPE yy = yylval;      // in case we have a character liteal


    //
    // -- Trivially check if it's a character literal
    //    -------------------------------------------
    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        std::unique_ptr<EnumLiteralSymbol> sym;
        id.name = std::get<CharLiteral>(tokens.Payload()).lexeme;
        sym = std::make_unique<EnumLiteralSymbol>(id.name, type, type->literals.size(), loc, scopes.CurrentScope());
        type->literals.push_back(sym.get());
        scopes.Declare(std::move(sym));


        //
        // -- Consider this parse to be good
        //    ------------------------------
        m.Commit();
        return true;
    }


    //
    // -- Now check for an id and if we have one check for duplicates
    //    -----------------------------------------------------------
    if (RequireIdent(id)) {
        std::unique_ptr<EnumLiteralSymbol> sym;
        sym = std::make_unique<EnumLiteralSymbol>(id.name, type, type->literals.size(), id.loc, scopes.CurrentScope());
        type->literals.push_back(sym.get());
        scopes.Declare(std::move(sym));


        //
        // -- Consider this parse to be good
        //    ------------------------------
        m.Commit();
        return true;
    }

    return false;
}



