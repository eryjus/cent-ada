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
ExprPtr Parser::ParseSimpleExpression(void)
{
    Production p(*this, "simple_expression");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    UnaryOper uop = UnaryOper::Unspecified;
    BinaryOper bop = BinaryOper::Unspecified;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;

    uop = ParseUnaryAddingOperator();           // -- not required

    lhs = ParseTerm();
    if (!lhs) {
        p.At("No lhs");
        return nullptr;
    }

    if (uop == UnaryOper::Unspecified) {
        lhs = std::make_unique<UnaryExpr>(astLoc, uop, std::move(lhs));
    }

    if (tokens.Current() == TokenType::TOK_COMMA || tokens.Current() == TokenType::TOK_ARROW)  {
        // -- at this point we already have a good Term
        p.At("Comma/Arrow next");
        m.Commit();
        return lhs;
    }


    bop = ParseBinaryAddingOperator();
    while (bop != BinaryOper::Unspecified) {
        rhs = ParseTerm();
        if (!rhs) {
            p.At("lhs only");
            return nullptr;
        }

        if (tokens.Current() == TokenType::TOK_COMMA || tokens.Current() == TokenType::TOK_ARROW) {
            // -- at this point we already have a good Term
            m.Commit();

            return std::make_unique<BinaryExpr>(astLoc, bop, std::move(lhs), std::move(rhs));
        }

        lhs = std::make_unique<BinaryExpr>(astLoc, bop, std::move(lhs), std::move(rhs));
        bop = ParseBinaryAddingOperator();
    }


    p.At("Simple Expression chain");
    m.Commit();

    return lhs;
}



