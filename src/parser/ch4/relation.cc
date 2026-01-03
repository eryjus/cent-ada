//=================================================================================================================
//  parser/ch4/relation.cc -- An expressions relations to each side
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  relation ::= simple_expression [relational_operator simple_expression]
//             | simple_expression [not] in range
//             | simple_expression [not] in type_mark
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
// -- Parse a Relation
//    ----------------
bool Parser::ParseRelation(void)
{
    Production p(*this, "relation");
    MarkStream m(tokens, diags);
    bool hasNot = false;

    if (!ParseSimpleExpression())  return false;

    if ((tokens.Current() == TokenType::TOK_NOT && tokens.Peek() == TokenType::TOK_IN)
            || tokens.Current() == TokenType::TOK_IN) {
        if (Optional(TokenType::TOK_NOT)) hasNot = true;
        if (!Require(TokenType::TOK_IN))  return false;

        if (ParseRange()) {
            m.Commit();
            return true;
        }

        if (ParseTypeMark()) {
            m.Commit();
            return true;
        }

        return false;
    }


    if (ParseRelationalOperator()) {
        if (!ParseSimpleExpression()) return false;
    }


    m.Commit();
    return true;
}



