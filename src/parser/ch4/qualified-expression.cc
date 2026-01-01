//=================================================================================================================
//  parser/ch4/qualified-expression.cc -- A qualified expression
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  qualidied_expression ::= type_mark ` ( expression )
//                         | type_mark ` aggregate
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
// -- Parse a Qualified Expression
//    ----------------------------
bool Parser::ParseQualifiedExpression(void)
{
    Production p(*this, "qualified_expression");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!ParseTypeMark())       return false;
    if (!Require(TokenType::TOK_GRAVE_ACCENT))   return false;

    if (Require(TokenType::TOK_LEFT_PARENTHESIS)) {
        loc = tokens.SourceLocation();
        if (!ParseExpression()) {
            diags.Error(loc, DiagID::InvalidExpression, { "qualified expression" } );
        }

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
            // -- continue anyway
        }

        m.Commit();
        return true;
    }

    if (!ParseAggregate()) return false;

    m.Commit();
    return true;
}



