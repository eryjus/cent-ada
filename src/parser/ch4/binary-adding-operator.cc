//=================================================================================================================
//  parser/ch4/binary-adding-operator.cc -- A addition operator
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseBinaryAddingOperator(void)
{
    Production p(*this, "binary_adding_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TokenType::TOK_PLUS:
    case TokenType::TOK_MINUS:
    case TokenType::TOK_AMPERSAND:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



