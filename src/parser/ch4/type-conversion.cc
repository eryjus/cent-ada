//=================================================================================================================
//  parser/ch4/type-conversion.cc -- A type conversino
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  type_conversion ::= type_mark ( expression )
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
// -- Parse a Type Conversion
//    -----------------------
bool Parser::ParseTypeConversion(void)
{
    Production p(*this, "type_conversion");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!ParseTypeMark())       return false;
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))     return false;
    loc = tokens.SourceLocation();
    if (!ParseExpression()) {
        diags.Error(loc, DiagID::InvalidExpression, { "type conversion" } );
    }
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }

    m.Commit();
    return true;
}



