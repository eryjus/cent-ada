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
bool Parser::ParseRelationalOperator(void)
{
    Production p(*this, "relational_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TokenType::TOK_EQUAL:
    case TokenType::TOK_INEQUALITY:
    case TokenType::TOK_LESS_THAN:
    case TokenType::TOK_LESS_THAN_OR_EQUAL:
    case TokenType::TOK_GREATER_THAN:
    case TokenType::TOK_GREATER_THAN_OR_EQUAL:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



