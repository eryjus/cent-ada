//=================================================================================================================
//  parser/ch4/multiplying-operator.cc -- A multiplication operator
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseMultiplyingOperator(void)
{
    Production p(*this, "multiplying_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TokenType::TOK_STAR:
    case TokenType::TOK_SLASH:
    case TokenType::TOK_MOD:
    case TokenType::TOK_REM:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



