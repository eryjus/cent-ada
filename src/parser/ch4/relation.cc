//=================================================================================================================
//  parser/ch4/relation.cc -- An expressions relations to each side
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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

    //
    // -- check for some illegal variations which should fail the parse early
    //    -------------------------------------------------------------------
    if (Illegal(TokenType::TOK_COMMA)) {
        m.Commit();
        return true;
    }
    if (Illegal(TokenType::TOK_ARROW)) {
        m.Commit();
        return true;
    }
    if (Illegal(TokenType::TOK_VERTICAL_BAR)) {
        m.Commit();
        return true;
    }
    if (Illegal(TokenType::TOK_DOUBLE_DOT)) {
        m.Commit();
        return true;
    }


    if (ParseRelationalOperator()) {
        if (!ParseSimpleExpression()) return false;

        m.Commit();
        return true;
    }


    if (Optional(TokenType::TOK_NOT)) hasNot = true;
    if (!Optional(TokenType::TOK_IN)) {
        m.Commit();
        return true;
    }

    if (ParseRange()) {
        m.Commit();
        return true;
    }

    if (ParseTypeMark()) {
        m.Commit();
        return true;
    }

    // -- TODO: Is there some form of recovery needed here?

    m.Commit();
    return true;
}



