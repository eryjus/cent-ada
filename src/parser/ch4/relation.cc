//=================================================================================================================
//  parser/ch4/relation.cc -- An expressions relations to each side
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  relation ::= simple_expression [relational_operator simple_expression]
//             | simple_expression [not] in range
//             | simple_expression [not] in type_mark
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
// -- Parse a Relation
//    ----------------
ExprPtr Parser::ParseRelation(void)
{
    Production p(*this, "relation");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    bool hasNot = false;
    BinaryOper bop = BinaryOper::Unspecified;
    NamePtr id = nullptr;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;
    DiscreteRangePtr range = nullptr;

    lhs = ParseSimpleExpression();
    if (!lhs) return nullptr;

    if ((tokens.Current() == TokenType::TOK_NOT && tokens.Peek() == TokenType::TOK_IN)
            || tokens.Current() == TokenType::TOK_IN) {
        if (Optional(TokenType::TOK_NOT)) hasNot = true;
        if (!Require(TokenType::TOK_IN))  return nullptr;

        range = ParseRange();
        if (range) {
            rhs = std::make_unique<RangeExpr>(astLoc, std::move(range));
            ExprPtr rv = std::make_unique<BinaryExpr>(astLoc, BinaryOper::In, std::move(lhs), std::move(rhs));
            if (hasNot) rv = std::make_unique<UnaryExpr>(astLoc, UnaryOper::Not, std::move(rv));

            m.Commit();
            return rv;
        }

        id = ParseTypeMark();
        if (id) {
            rhs = std::make_unique<NameExpr>(astLoc, std::move(id));
            ExprPtr rv = std::make_unique<BinaryExpr>(astLoc, BinaryOper::In, std::move(lhs), std::move(rhs));
            if (hasNot) rv = std::make_unique<UnaryExpr>(astLoc, UnaryOper::Not, std::move(rv));

            m.Commit();
            return rv;
        }


        return nullptr;
    }


    bop = ParseRelationalOperator();
    if (bop == BinaryOper::Unspecified) {
        rhs = ParseSimpleExpression();
        if (!rhs) return nullptr;
    }


    m.Commit();

    return std::make_unique<BinaryExpr>(astLoc, bop, std::move(lhs), std::move(rhs));;
}



