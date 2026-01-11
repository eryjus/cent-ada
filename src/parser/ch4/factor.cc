//=================================================================================================================
//  parser/ch4/factor.cc -- A factor
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  factor ::= primary [** primary]
//           | abs primary
//           | not primary
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
// -- Parse a Factor
//    --------------
ExprPtr Parser::ParseFactor(void)
{
    Production p(*this, "factor");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;

    if (Require(TokenType::TOK_ABS)) {
        loc = tokens.SourceLocation();
        if ((lhs = std::move(ParsePrimary())) == nullptr) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "ABS" } );
        }

        UnaryExprPtr rv = std::make_unique<UnaryExpr>(astLoc, UnaryOper::Abs, std::move(lhs));
        m.Commit();
        return rv;
    } else if (Require(TokenType::TOK_NOT)) {
        loc = tokens.SourceLocation();
        if ((lhs = std::move(ParsePrimary())) == nullptr) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "NOT" } );
        }

        UnaryExprPtr rv = std::make_unique<UnaryExpr>(astLoc, UnaryOper::Not, std::move(lhs));
        m.Commit();
        return rv;
    } else {
        if ((lhs = std::move(ParsePrimary())) == nullptr)           return nullptr;

        if (Optional(TokenType::TOK_DOUBLE_STAR)) {
            if ((rhs = std::move(ParsePrimary())) == nullptr)       return nullptr;
        }

        BinaryExprPtr rv = std::make_unique<BinaryExpr>(astLoc, BinaryOper::Power, std::move(lhs), std::move(rhs));

        m.Commit();
        return rv;
    }

    return nullptr;
}



