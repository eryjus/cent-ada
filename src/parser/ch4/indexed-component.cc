//=================================================================================================================
//  parser/ch4/indexed-component.cc -- An indexed component
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  indexed_component ::= prefix ( expression {, expression} )
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
// -- Parse an Indexed Copmonent
//    --------------------------
bool Parser::ParseIndexedComponent(void)
{
    Production p(*this, "indexed_component");
    MarkStream m(tokens, diags);

    if (!ParsePrefix())                                 return false;
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))      return false;
    if (!ParseExpression())                             return false;

    while (Optional(TokenType::TOK_COMMA)) {
        if (!ParseExpression())                         return false;
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }

    m.Commit();
    return true;
}



//
// -- Parse an Indexed Component for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_IndexComponentSuffix(void)
{
    Production p(*this, "indexed_component(suffix)");
    MarkStream m(tokens, diags);

    if (!ParseExpression())                     return false;

    while (Optional(TokenType::TOK_COMMA)) {
        if (!ParseExpression())                 return false;
    }

    m.Commit();
    return true;
}



