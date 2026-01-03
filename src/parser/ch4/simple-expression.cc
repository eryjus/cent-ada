//=================================================================================================================
//  parser/ch4/simple-expression.cc -- A simple expression
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  simple_expression ::= [unary_adding_operator] term {binary_adding_operator term}
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
// -- Parse a Simple Expression
//    -------------------------
bool Parser::ParseSimpleExpression(void)
{
    Production p(*this, "simple_expression");
    MarkStream m(tokens, diags);

    ParseUnaryAddingOperator();
    if (!ParseTerm()) return false;
    if (tokens.Current() == TokenType::TOK_COMMA || tokens.Current() == TokenType::TOK_ARROW)  {
        // -- at this point we already have a good Term
        m.Commit();
        return true;
    }


    while (ParseBinaryAddingOperator()) {
        if (!ParseTerm()) return false;
        if (tokens.Current() == TokenType::TOK_COMMA || tokens.Current() == TokenType::TOK_ARROW) {
            // -- at this point we already have a good Term
            m.Commit();
            return true;
        }
    }

    m.Commit();
    return true;
}



