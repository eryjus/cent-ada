//=================================================================================================================
//  parser/ch4/relational-operator.cc -- A relational operator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  relational_operator ::= = | /= | < | <= | > | >=
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
// -- Parse a Relational Operator
//    ---------------------------
BinaryOper Parser::ParseRelationalOperator(void)
{
    Production p(*this, "relational_operator");
    MarkStream m(tokens, diags);


    switch (TokenStream::Get().Current()) {
    case TokenType::TOK_EQUAL:                  TokenStream::Get().Advance();  m.Commit();  return BinaryOper::Equal;
    case TokenType::TOK_INEQUALITY:             TokenStream::Get().Advance();  m.Commit();  return BinaryOper::NotEqual;
    case TokenType::TOK_LESS_THAN:              TokenStream::Get().Advance();  m.Commit();  return BinaryOper::LessThan;
    case TokenType::TOK_LESS_THAN_OR_EQUAL:     TokenStream::Get().Advance();  m.Commit();  return BinaryOper::LessEqual;
    case TokenType::TOK_GREATER_THAN:           TokenStream::Get().Advance();  m.Commit();  return BinaryOper::GreaterThan;
    case TokenType::TOK_GREATER_THAN_OR_EQUAL:  TokenStream::Get().Advance();  m.Commit();  return BinaryOper::GreaterEqual;
    default:                                                                    return BinaryOper::Unspecified;
    }
}



