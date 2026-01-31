//=================================================================================================================
//  parser/ch4/binary-adding-operator.cc -- A addition operator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  binary_adding_operator ::= + | - | &
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
// -- Parse a Binary Adding Operator
//    ------------------------------
BinaryOper Parser::ParseBinaryAddingOperator(void)
{
    Production p(*this, "binary_adding_operator");
    MarkStream m(tokens, diags);


    switch (tokens.Current()) {
    case TokenType::TOK_PLUS:       tokens.Advance();  m.Commit();  return BinaryOper::Plus;
    case TokenType::TOK_MINUS:      tokens.Advance();  m.Commit();  return BinaryOper::Minus;
    case TokenType::TOK_AMPERSAND:  tokens.Advance();  m.Commit();  return BinaryOper::Concatenate;
    default:                                                        return BinaryOper::Unspecified;
    }
}



