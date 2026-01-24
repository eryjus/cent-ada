//=================================================================================================================
//  ast.hh -- This is the declarations for the Abstract Syntax Tree (AST)
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  ChatGPT recommends the following structure:
//
//  ```
//    ASTNode : (root)
//
//      Decl : ASTNode
//        ExceptionDecl : Decl
//        NumberDecl : Decl
//        ObjectDecl : Decl
//        PackageDecl : Decl
//        RenamingDecl : Decl
//        SubprogramDecl : Decl
//        SubtypeDecl : Decl
//        TypeDecl : Decl
//
//      TypeSpec : ASTNode
//        AccessTypeSpec : TypeSpec
//        ConstrainedArrayType : TypeSpec
//        EnumerationTypeSpec : TypeSpec
//        NumericTypeSpec : TypeSpec                        -- added by me
//        RecordTypeSpec : TypeSpec
//        SubtypeIndication : TypeSpec
//
//      Stmt : ASTNode
//        AssignmentStmt : Stmt
//        BlockStmt : Stmt
//        CaseStmt : Stmt
//        ExitStmt : Stmt
//        IfStmt : Stmt
//        LoopStmt : Stmt
//        NullStmt : Stmt
//        ProcedureCallStmt : Stmt
//        ReturnStmt : Stmt
//
//      Expr : ASTNode
//        AggregateExpr : Expr
//        BinaryExpr : Expr
//        LiteralExpr : Expr
//          CharLiteralExpr : LiteralExpr
//          IntegerLiteralExpr : LiteralExpr
//          RealLiteralExpr : LiteralExpr
//          StringLiteralExpr : LiteralExpr
//        NameExpr : Expr
//          FunctionCall : NameExpr                         -- added by me
//        QualifiedExpr : Expr
//        ShortCircuitExpr : Expr
//        UnaryExpr : Expr
//
//      Name : ASTNode
//        AttributeName : Name
//        IndexedName : Name
//        SelectedName : Name
//        SimpleName : Name
//        SliceName : Name
//
//      Constraint : ASTNode
//        IndexConstraint : Constraint
//        RangeConstraint : Constraint
//
//      DiscreteRange : ASTNode
//        Range : DiscreteRange
//        SubtypeRange : DiscreteRange
//
//      Choice : ASTNode
//        ChoiceExpr : Choice
//        ChoiceOthers : Choice
//        ChoiceRange : Choice
//  ```
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
    virtual void Accept(ASTVisitor &) {};


public:
    ASTNode(SourceLoc_t l) : loc(l) {}
};

// -- Alias the pointer to this class
using NodePtr = std::unique_ptr<ASTNode>;



//
// -- Some additional aliasing
//    ------------------------
using IdList = std::vector<Id>;


#include "ast/decl.hh"
#include "ast/expr.hh"
#include "ast/stmt.hh"
#include "ast/name.hh"
#include "ast/node.hh"
#include "ast/typespec.hh"
#include "ast/constraint.hh"
#include "ast/discrete-range.hh"
#include "ast/choice.hh"
#include "ast/component-association.hh"

