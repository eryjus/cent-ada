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
ExprPtr Parser::ParseTypeConversion(void)
{
    Production p(*this, "type_conversion");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    Id id;
    ExprPtr expr = nullptr;

    if ((id = ParseTypeMark()).name == "")       return nullptr;
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))     return nullptr;
    loc = tokens.SourceLocation();
    if ((expr = std::move(ParseExpression())) == nullptr) {
        diags.Error(loc, DiagID::InvalidExpression, { "type conversion" } );
    }
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }

    TypeConversionExprPtr rv = std::make_unique<TypeConversionExpr>(astLoc, id, std::move(expr));

    m.Commit();
    return std::move(rv);
}



