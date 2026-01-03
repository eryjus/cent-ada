//=================================================================================================================
//  parser/ch4/expression.cc -- An expression defined the computation of a value
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  expression ::= relation [and relation]
//               | relation [and then relation]
//               | relation [or relation]
//               | relation [or else relation]
//               | relation [xor relation]
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
// -- Parse an Expression
//    -------------------
bool Parser::ParseExpression(void)
{
    Production p(*this, "expression");
    MarkStream m(tokens, diags);
    TokenType tok;


    if (!ParseRelation()) return false;

    switch (tokens.Current()) {
    case TokenType::TOK_AND:
    case TokenType::TOK_AND_THEN:
    case TokenType::TOK_OR:
    case TokenType::TOK_OR_ELSE:
    case TokenType::TOK_XOR:
        tok = tokens.Current();
        break;

    default:
        m.Commit();
        return true;
    }

    while (Optional(tok)) {
        if (!ParseRelation()) {
            // -- TODO: maybe issue an error about missing a relation and return true instead???
            return false;
        }
    }

    m.Commit();
    return true;
}



