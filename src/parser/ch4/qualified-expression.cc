//=================================================================================================================
//  parser/ch4/qualified-expression.cc -- A qualified expression
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
QualifiedExprPtr Parser::ParseQualifiedExpression(void)
{
    Production p(*this, "qualified_expression");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    NamePtr id = nullptr;
    ExprPtr expr = nullptr;

    id = ParseTypeMark();
    if (!id) return nullptr;
    if (!Require(TokenType::TOK_APOSTROPHE))   return nullptr;

    expr = ParseAggregate();
    if (expr) {
        m.Commit();
        return std::make_unique<QualifiedExpr>(astLoc, std::move(id), std::move(expr));
    }

    if (Require(TokenType::TOK_LEFT_PARENTHESIS)) {
        loc = tokens.SourceLocation();
        expr = ParseExpression();
        if (!expr) {
            diags.Error(loc, DiagID::InvalidExpression, { "qualified expression" } );
        }

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
            // -- continue anyway
        }

        m.Commit();

        return std::make_unique<QualifiedExpr>(astLoc, std::move(id), std::move(expr));
    }


    return nullptr;
}



