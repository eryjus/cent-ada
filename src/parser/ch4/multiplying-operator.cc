//=================================================================================================================
//  parser/ch4/multiplying-operator.cc -- A multiplication operator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  binary_adding_operator ::= * | / | mod | rem
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
// -- Parse a Multiplying Operator
//    ----------------------------
BinaryOper Parser::ParseMultiplyingOperator(void)
{
    Production p(*this, "multiplying_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TokenType::TOK_STAR:       tokens.Advance();  m.Commit();  return BinaryOper::Times;
    case TokenType::TOK_SLASH:      tokens.Advance();  m.Commit();  return BinaryOper::Divide;
    case TokenType::TOK_MOD:        tokens.Advance();  m.Commit();  return BinaryOper::Mod;
    case TokenType::TOK_REM:        tokens.Advance();  m.Commit();  return BinaryOper::Rem;
    default:                                                        return BinaryOper::Unspecified;
    }
}



