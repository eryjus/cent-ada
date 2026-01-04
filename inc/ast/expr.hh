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



