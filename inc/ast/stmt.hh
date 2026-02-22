//=================================================================================================================
//  ast/stmt.hh -- This header is used for defining the classes which are derived from Stmt
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
// -- The common Statement node
//    -------------------------
class Stmt : public ASTNode {
    Stmt(void) = delete;
    Stmt(const Stmt &) = delete;
    Stmt &operator=(const Stmt &) = delete;


public:
    NameListPtr labels;


public:
    Stmt(SourceLoc_t l, NameListPtr lbls) : ASTNode(l), labels(std::move(lbls)) {}
};



//
// -- The Null Statement node
//    -----------------------
class NullStmt : public Stmt {
    NullStmt(void) = delete;
    NullStmt(const Stmt &) = delete;
    NullStmt &operator=(const Stmt &) = delete;


public:
    NameListPtr labels;


public:
    NullStmt(SourceLoc_t l, NameListPtr lbls) : Stmt(l, std::move(lbls)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



