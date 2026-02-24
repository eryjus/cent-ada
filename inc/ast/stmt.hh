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



//
// -- Case Statement Alternative
//    --------------------------
class CaseStmtAlt : public ASTNode {
    CaseStmtAlt(void) = delete;
    CaseStmtAlt(const Stmt &) = delete;
    CaseStmtAlt &operator=(const Stmt &) = delete;


public:
    ChoiceListPtr choices;
    StmtListPtr stmts;


public:
    CaseStmtAlt(SourceLoc_t l, ChoiceListPtr c, StmtListPtr s) : ASTNode(l), choices(std::move(c)), stmts(std::move(s)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Case Statement node
//    -----------------------
class CaseStmt : public Stmt {
    CaseStmt(void) = delete;
    CaseStmt(const Stmt &) = delete;
    CaseStmt &operator=(const Stmt &) = delete;


public:
    ExprPtr expr;
    CaseStmtAltListPtr alts;


public:
    CaseStmt(SourceLoc_t l, NameListPtr lbls, ExprPtr e, CaseStmtAltListPtr a) : Stmt(l, std::move(lbls)), expr(std::move(e)), alts(std::move(a)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Loop Statement node
//    -----------------------
class LoopStmt : public Stmt {
    LoopStmt(void) = delete;
    LoopStmt(const Stmt &) = delete;
    LoopStmt &operator=(const Stmt &) = delete;



public:
    SimpleNamePtr name;         // -- may be nullptr
    LoopType kind;
    ExprPtr expr;               // -- nullptr when kind == LoopNone
    StmtListPtr stmts;


public:
    LoopStmt(SourceLoc_t l, NameListPtr lbls, SimpleNamePtr n, LoopType k, ExprPtr e, StmtListPtr s)
            : Stmt(l, std::move(lbls)), name(std::move(n)), kind(k), expr(std::move(e)), stmts(std::move(s)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Block Statement node
//    ------------------------
class BlockStmt : public Stmt {
    BlockStmt(void) = delete;
    BlockStmt(const Stmt &) = delete;
    BlockStmt &operator=(const Stmt &) = delete;



public:
    SimpleNamePtr name;         // -- may be nullptr
    DeclListPtr decls;          // -- may be nullptr
    StmtListPtr stmts;
    NodeListPtr excepts;        // -- TODO!!!  may be nullptr


public:
    BlockStmt(SourceLoc_t l, NameListPtr lbls, SimpleNamePtr n, DeclListPtr d, StmtListPtr s, NodeListPtr x)
            : Stmt(l, std::move(lbls)), name(std::move(n)), decls(std::move(d)), stmts(std::move(s)), excepts(std::move(x)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Exit Statement node
//    -----------------------
class ExitStmt : public Stmt {
    ExitStmt(void) = delete;
    ExitStmt(const Stmt &) = delete;
    ExitStmt &operator=(const Stmt &) = delete;



public:
    NamePtr name;               // -- may be nullptr
    ExprPtr when;               // -- may be nullptr


public:
    ExitStmt(SourceLoc_t l, NameListPtr lbls, NamePtr n, ExprPtr w)
            : Stmt(l, std::move(lbls)), name(std::move(n)), when(std::move(w)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Return Statement node
//    -------------------------
class ReturnStmt : public Stmt {
    ReturnStmt(void) = delete;
    ReturnStmt(const Stmt &) = delete;
    ReturnStmt &operator=(const ReturnStmt &) = delete;



public:
    ExprPtr expr;               // -- may be nullptr


public:
    ReturnStmt(SourceLoc_t l, NameListPtr lbls, ExprPtr e) : Stmt(l, std::move(lbls)), expr(std::move(e)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- The Goto Statement node
//    -----------------------
class GotoStmt : public Stmt {
    GotoStmt(void) = delete;
    GotoStmt(const Stmt &) = delete;
    GotoStmt &operator=(const GotoStmt &) = delete;



public:
    NamePtr name;


public:
    GotoStmt(SourceLoc_t l, NameListPtr lbls, NamePtr n) : Stmt(l, std::move(lbls)), name(std::move(n)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};


