//=================================================================================================================
//  ast/decl.hh -- This header is used for defining the classes which are derived from Decl
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
// -- Number declaration
//    ------------------
class NumberDeclaration : public Decl {
    NumberDeclaration(void) = delete;
    NumberDeclaration(const NumberDeclaration &) = delete;
    NumberDeclaration &operator=(const NumberDeclaration &) = delete;


public:
    IdListPtr names;
    ExprPtr initializer;


public:
    NumberDeclaration(SourceLoc_t l, IdListPtr ids, ExprPtr i) :
            Decl(l), names(std::move(ids)), initializer(std::move(i)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};



//
// -- Object declaration
//    ------------------
class ObjectDeclaration : public Decl {
    ObjectDeclaration(void) = delete;
    ObjectDeclaration(const ObjectDeclaration &) = delete;
    ObjectDeclaration &operator=(const ObjectDeclaration &) = delete;


public:
    IdListPtr names;
    bool isConstant;
    TypeSpecPtr typeSpec;
    ExprPtr initializer;                // may be nullptr


public:
    ObjectDeclaration(SourceLoc_t l, IdListPtr ids, bool c, TypeSpecPtr s, ExprPtr i) :
            Decl(l), names(std::move(ids)), isConstant(c), typeSpec(std::move(s)), initializer(std::move(i)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};



//
// -- The common Type Declaration node (Creating a type)
//    --------------------------------------------------
class TypeDecl : public Decl{
    TypeDecl(void) = delete;
    TypeDecl(const TypeDecl &) = delete;
    TypeDecl &operator=(const TypeDecl &) = delete;

public:
    Id name;
    ExprPtr discriminantPart;           // -- may be null
    TypeSpecPtr definition;             // -- may be null if incomplete


public:
    TypeDecl(SourceLoc_t loc, Id n, ExprPtr dis, TypeSpecPtr defn)
            : Decl(loc), name(n), discriminantPart(std::move(dis)), definition(std::move(defn)) {}

public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};





