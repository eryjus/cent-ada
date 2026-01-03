//=================================================================================================================
//  ast.hh -- This is the declarations for the Abstract Syntax Tree (AST)
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
// -- This is the root node against which all other node types are derived
//    --------------------------------------------------------------------
class ASTNode {
    ASTNode(void) = delete;
    ASTNode(const ASTNode &) = delete;
    ASTNode &operator=(const ASTNode &) = delete;

public:
    SourceLoc_t loc;
    virtual ~ASTNode() = default;
    virtual void Accept(ASTVisitor &) = 0;


public:
    ASTNode(SourceLoc_t l) : loc(l) {}
};

// -- Alias the pointer to this class
using NodePtr = std::unique_ptr<ASTNode>;



//
// -- Here are some structural node types which need to be defined, starting with a Declaration
//    -----------------------------------------------------------------------------------------
class Decl : public ASTNode {
    Decl(void) = delete;
    Decl(const Decl &) = delete;
    Decl &operator=(const Decl &) = delete;

public:
    Decl(SourceLoc_t l) : ASTNode(l) {}
};



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
// -- The common Statement node
//    -------------------------
class Stmt : public ASTNode {
    Stmt(void) = delete;
    Stmt(const Stmt &) = delete;
    Stmt &operator=(const Stmt &) = delete;

public:
    Stmt(SourceLoc_t l) : ASTNode(l) {}
};



//
// -- The common Name node
//    --------------------
class Name : public ASTNode {
    Name(void) = delete;
    Name(const Name &) = delete;
    Name &operator=(const Name &) = delete;

public:
    Name(SourceLoc_t l) : ASTNode(l) {}


public:
    virtual void Accept(ASTVisitor &) override {}
};



//
// -- The common Type Expressions node (describing a type)
//    ----------------------------------------------------
class TypeExpr : public ASTNode {
    TypeExpr(void) = delete;
    TypeExpr(const TypeExpr &) = delete;
    TypeExpr &operator=(const TypeExpr &) = delete;

public:
    TypeExpr(SourceLoc_t l) : ASTNode(l) {}
};



//
// -- Finally, some aliasing for readability
//    --------------------------------------
using DeclPtr = std::unique_ptr<Decl>;
using ExprPtr = std::unique_ptr<Expr>;
using StmtPtr = std::unique_ptr<Stmt>;
using NamePtr = std::unique_ptr<Name>;
using TypeExprPtr = std::unique_ptr<TypeExpr>;



//
// -- Some additional aliasing
//    ------------------------
using IdList = std::vector<Parser::Id>;


#include "ast/decl.hh"
#include "ast/expr.hh"
#include "ast/stmt.hh"
#include "ast/name.hh"
#include "ast/node.hh"
#include "ast/typeexpr.hh"
