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
    NullStmt(SourceLoc_t l, NameListPtr lbls) : Stmt(l, std::move(lbls)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Assignment Statement node
//    -----------------------------
class AssignStmt : public Stmt {
    AssignStmt(void) = delete;
    AssignStmt(const Stmt &) = delete;
    AssignStmt &operator=(const Stmt &) = delete;


public:
    NamePtr name;
    ExprPtr expr;


public:
    AssignStmt(SourceLoc_t l, NameListPtr lbls, NamePtr n, ExprPtr e) : Stmt(l, std::move(lbls)), name(std::move(n)), expr(std::move(e)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The If Statement node
//    ---------------------
class IfStmt : public Stmt {
    IfStmt(void) = delete;
    IfStmt(const Stmt &) = delete;
    IfStmt &operator=(const Stmt &) = delete;


public:
    ExprPtr cond;           // -- may be null if an `else` part
    StmtListPtr stmts;
    IfStmtPtr elsePart;     // -- only populated if the if statement has an elsif or else part


public:
    IfStmt(SourceLoc_t l, NameListPtr lbls, ExprPtr c, StmtListPtr s) : Stmt(l, std::move(lbls)), cond(std::move(c)), stmts(std::move(s)) {}
    void AddElsif(ExprPtr c, StmtListPtr s) {
        if (!elsePart) {
            elsePart = std::make_unique<IfStmt>(loc, nullptr, std::move(c), std::move(s));
            return;
        }

        IfStmt *wrk = elsePart.get();
        while (wrk->elsePart) wrk = wrk->elsePart.get();
        wrk->elsePart = std::make_unique<IfStmt>(loc, nullptr, std::move(c), std::move(s));
    }
    void AddElse(StmtListPtr s) { AddElsif(nullptr, std::move(s)); }


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



