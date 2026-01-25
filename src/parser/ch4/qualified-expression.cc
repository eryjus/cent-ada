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
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
//    Id id;
    NamePtr id = nullptr;
    ExprPtr expr = nullptr;

    if ((id = std::move(ParseTypeMark())) == nullptr)       return nullptr;
    if (!Require(TokenType::TOK_APOSTROPHE))   return nullptr;

    if ((expr = std::move(ParseAggregate())) != nullptr) {
        QualifiedExprPtr rv = std::make_unique<QualifiedExpr>(astLoc, std::move(id), std::move(expr));
        m.Commit();
        return std::move(rv);
    }

    if (Require(TokenType::TOK_LEFT_PARENTHESIS)) {
        loc = tokens.SourceLocation();
        if ((expr = std::move(ParseExpression())) == nullptr) {
            diags.Error(loc, DiagID::InvalidExpression, { "qualified expression" } );
        }

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
            // -- continue anyway
        }

        QualifiedExprPtr rv = std::make_unique<QualifiedExpr>(astLoc, std::move(id), std::move(expr));

        m.Commit();
        return std::move(rv);
    }

    // -- TODO: Why is this commit here?
    //m.Commit();
    return nullptr;
}



