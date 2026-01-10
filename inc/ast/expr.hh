//=================================================================================================================
//  ast/expr.hh -- This header is used for defining the classes which are derived from Expr
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Jan-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once



//
// -- The common Expression node
//    --------------------------
class Expr : public ASTNode {
    Expr(void) = delete;
    Expr(const Expr &) = delete;
    Expr &operator=(const Expr &) = delete;

public:
    Expr(SourceLoc_t l) : ASTNode(l) {}
};



//
// -- A unary expression node
//    -----------------------
class UnaryExpr : public Expr {
    UnaryExpr(void) = delete;
    UnaryExpr(const UnaryExpr &) = delete;
    UnaryExpr &operator=(const UnaryExpr &) = delete;


public:
    UnaryOper op;
    ExprPtr expr;


public:
    UnaryExpr(SourceLoc_t loc, UnaryOper op, ExprPtr e) : Expr(loc), op(op), expr(std::move(e)) {}
};



//
// -- A binary expression node
//    ------------------------
class BinaryExpr : public Expr {
    BinaryExpr(void) = delete;
    BinaryExpr(const BinaryExpr &) = delete;
    BinaryExpr &operator=(const BinaryExpr &) = delete;


public:
    BinaryOper op;
    ExprPtr lhs;
    ExprPtr rhs;


public:
    BinaryExpr(SourceLoc_t loc, BinaryOper op, ExprPtr l, ExprPtr r)
            : Expr(loc), op(op), lhs(std::move(l)), rhs(std::move(r)) {}
};



