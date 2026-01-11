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



//
// -- A literal expression node
//    -------------------------
class LiteralExpr : public Expr {
    LiteralExpr(void) = delete;
    LiteralExpr(const LiteralExpr &) = delete;
    LiteralExpr &operator=(const LiteralExpr &) = delete;


public:
    LiteralExpr(SourceLoc_t loc) : Expr(loc) {}
};



//
// -- This is a NULL literal
//    ----------------------
class NullLiteralExpr : public LiteralExpr {
    NullLiteralExpr(void) = delete;
    NullLiteralExpr(const NullLiteralExpr &) = delete;
    NullLiteralExpr &operator=(const NullLiteralExpr &) = delete;


public:
    NullLiteralExpr(SourceLoc_t loc) : LiteralExpr(loc) {}
};



//
// -- This is an int literal
//    ----------------------
class IntLiteralExpr : public LiteralExpr {
    IntLiteralExpr(void) = delete;
    IntLiteralExpr(const IntLiteralExpr &) = delete;
    IntLiteralExpr &operator=(const IntLiteralExpr &) = delete;


public:
    IntLiteral lit;


public:
    IntLiteralExpr(SourceLoc_t loc, IntLiteral l) : LiteralExpr(loc), lit(l) {}
};



//
// -- This is a real literal
//    ----------------------
class RealLiteralExpr : public LiteralExpr {
    RealLiteralExpr(void) = delete;
    RealLiteralExpr(const RealLiteralExpr &) = delete;
    RealLiteralExpr &operator=(const RealLiteralExpr &) = delete;


public:
    RealLiteral lit;


public:
    RealLiteralExpr(SourceLoc_t loc, RealLiteral l) : LiteralExpr(loc), lit(l) {}
};



//
// -- This is a string literal
//    ------------------------
class StringLiteralExpr : public LiteralExpr {
    StringLiteralExpr(void) = delete;
    StringLiteralExpr(const StringLiteralExpr &) = delete;
    StringLiteralExpr &operator=(const StringLiteralExpr &) = delete;


public:
    StringLiteral lit;


public:
    StringLiteralExpr(SourceLoc_t loc, StringLiteral l) : LiteralExpr(loc), lit(l) {}
};



//
// -- This is a name expression
//    -------------------------
class NameExpr : public Expr {
    NameExpr(void) = delete;
    NameExpr(const NameExpr &) = delete;
    NameExpr &operator=(const NameExpr &) = delete;


public:
    NamePtr name;


public:
    NameExpr(SourceLoc_t loc, NamePtr n) : Expr(loc), name(std::move(n)) {}
};









