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
IndexedNamePtr Parser::ParseIndexedComponent(void)
{
    Production p(*this, "indexed_component");
    MarkStream m(tokens, diags);
    NamePtr pre = nullptr;
    ExprListPtr idx = std::make_unique<ExprList>();
    SourceLoc_t astLoc = tokens.SourceLocation();

    if (!ParsePrefix())                                 return nullptr;
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))      return nullptr;
    if (!ParseExpression())                             return nullptr;

    while (Optional(TokenType::TOK_COMMA)) {
        if (!ParseExpression())                         return nullptr;
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }


    IndexedNamePtr rv = std::make_unique<IndexedName>(astLoc, std::move(pre), std::move(idx));

    m.Commit();
    return std::move(rv);
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



