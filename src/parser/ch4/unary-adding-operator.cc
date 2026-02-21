//=================================================================================================================
//  parser/ch4/unary-adding-operator.cc -- A unary operator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  unary_adding_operator ::= + | -
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
// -- Parse a Unary Adding Operator
//    -----------------------------
UnaryOper Parser::ParseUnaryAddingOperator(void)
{
    Production p(*this, "unary_adding_operator");
    MarkStream m(tokens, diags);


    switch (TokenStream::Get().Current()) {
    case TokenType::TOK_PLUS:   TokenStream::Get().Advance();  m.Commit();  return UnaryOper::Plus;
    case TokenType::TOK_MINUS:  TokenStream::Get().Advance();  m.Commit();  return UnaryOper::Minus;
    default:                                                    return UnaryOper::Unspecified;
    }
}



