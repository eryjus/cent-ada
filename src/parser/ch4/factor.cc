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
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;

    if (Require(TokenType::TOK_ABS)) {
        loc = tokens.SourceLocation();

        lhs = ParsePrimary();
        if (!lhs) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "ABS" } );
        }

        p.At("ABS");
        m.Commit();

        return std::make_unique<UnaryExpr>(astLoc, UnaryOper::Abs, std::move(lhs));
    } else if (Require(TokenType::TOK_NOT)) {
        loc = tokens.SourceLocation();

        lhs = ParsePrimary();
        if (!lhs) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "NOT" } );
        }

        p.At("NOT");
        m.Commit();

        return std::make_unique<UnaryExpr>(astLoc, UnaryOper::Not, std::move(lhs));
    } else {
        lhs = ParsePrimary();
        if (!lhs) {
            p.At("No Primary");
            return nullptr;
        }

        if (Optional(TokenType::TOK_DOUBLE_STAR)) {
            rhs = ParsePrimary();
            if (!rhs) return nullptr;
            p.At("STAR_STAR");
            m.Commit();
            return std::make_unique<BinaryExpr>(astLoc, BinaryOper::Power, std::move(lhs), std::move(rhs));
        }

        p.At("Single");
        m.Commit();

        return lhs;
    }


    p.At("Failed");
    return nullptr;
}



