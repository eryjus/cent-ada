//=================================================================================================================
//  parser/ch4/expression.cc -- An expression defined the computation of a value
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  expression ::= relation [and relation]
//               | relation [and then relation]
//               | relation [or relation]
//               | relation [or else relation]
//               | relation [xor relation]
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
// -- Parse an Expression
//    -------------------
ExprPtr Parser::ParseExpression(void)
{
    Production p(*this, "expression");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    BinaryOper bop = BinaryOper::Unspecified;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;
    TokenType tok;


    lhs = ParseRelation();
    if (!lhs) {
        p.At("empty lhs");
        return nullptr;
    }

    switch (tokens.Current()) {
    case TokenType::TOK_AND:        bop = BinaryOper::And;      tok = tokens.Current();  break;
    case TokenType::TOK_AND_THEN:   bop = BinaryOper::AndThen;  tok = tokens.Current();  break;
    case TokenType::TOK_OR:         bop = BinaryOper::Or;       tok = tokens.Current();  break;
    case TokenType::TOK_OR_ELSE:    bop = BinaryOper::OrElse;   tok = tokens.Current();  break;
    case TokenType::TOK_XOR:        bop = BinaryOper::Xor;      tok = tokens.Current();  break;
    default:
        p.At("lhs only");
        m.Commit();
        return lhs;
    }


    while (Optional(tok)) {
        rhs = ParseRelation();
        if (!rhs) {
            // -- TODO: maybe issue an error about missing a relation and return true instead???
            p.At("no rhs");
            return nullptr;
        }


        lhs = std::make_unique<BinaryExpr>(astLoc, bop, std::move(lhs), std::move(rhs));
    }


    p.At("only lhs");
    m.Commit();

    return lhs;
}



