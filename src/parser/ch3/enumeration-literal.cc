//=================================================================================================================
//  parser/ch3/enumeration-literal.cc -- Parse an enumeration literal
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
Id Parser::ParseEnumerationLiteral(Symbol *type)
{
    Production p(*this, "enumeration_literal");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    SourceLoc_t loc = TokenStream::Get().SourceLocation();
    Symbol *sym= nullptr;
    YYSTYPE yy = yylval;      // in case we have a character liteal
    Id id;


    //
    // -- Trivially check if it's a character literal
    //    -------------------------------------------
    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        id.name = std::get<CharLiteral>(TokenStream::Get().Payload()).lexeme;

        sym = symTab.Declare(id.loc, id.name, SymbolTable::SymbolKind::EnumLiteral, type->symName);


        //
        // -- Consider this parse to be good
        //    ------------------------------
        cp.Commit();
        m.Commit();
        return id;
    }


    //
    // -- Now check for an id and if we have one check for duplicates
    //    -----------------------------------------------------------
    if (RequireIdent(id)) {
        sym = symTab.Declare(id.loc, id.name, SymbolTable::SymbolKind::EnumLiteral, type->symName);


        //
        // -- Consider this parse to be good
        //    ------------------------------
        cp.Commit();
        m.Commit();
        return id;
    }


    return { "", TokenStream::Get().EmptyLocation() };
}



