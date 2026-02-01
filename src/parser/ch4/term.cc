//=================================================================================================================
//  parser/ch4/term.cc -- A term
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  term ::= factor {multiplying_operator factor}
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
// -- Parse a Term
//    ------------
ExprPtr Parser::ParseTerm(void)
{
    Production p(*this, "term");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    BinaryOper bop = BinaryOper::Unspecified;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;


    lhs = ParseFactor();
    if (!lhs) {
        p.At("Failed");
        return nullptr;
    }

    bop = ParseMultiplyingOperator();
    while (bop != BinaryOper::Unspecified) {
        rhs = ParseFactor();
        if (!rhs) return nullptr;

        lhs = std::make_unique<BinaryExpr>(astLoc, bop, std::move(lhs), std::move(rhs));

        bop = ParseMultiplyingOperator();
    }


    p.At("proper term");
    m.Commit();

    return lhs;
}



