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
// -- Component declaration
//    ---------------------
class ComponentDeclaration : public Decl {
    ComponentDeclaration(void) = delete;
    ComponentDeclaration(const ComponentDeclaration &) = delete;
    ComponentDeclaration &operator=(const ComponentDeclaration &) = delete;


public:
    IdListPtr names;
    TypeSpecPtr typeSpec;
    ExprPtr initializer;                // may be nullptr


public:
    ComponentDeclaration(SourceLoc_t l, IdListPtr ids, TypeSpecPtr s, ExprPtr i) :
            Decl(l), names(std::move(ids)), typeSpec(std::move(s)), initializer(std::move(i)) {}

};




//
// -- Variants
//    --------
class Variant : public Decl {
    Variant(void) = delete;
    Variant(const Variant &) = delete;
    Variant &operator=(const Variant &) = delete;


public:
    ChoiceListPtr choices;              // -- may be nullptr
    ComponentListPtr components;


public:
    Variant(SourceLoc_t l, ChoiceListPtr choices, ComponentListPtr components)
            : Decl(l), choices(std::move(choices)), components(std::move(components)) {}

};





//
// -- Variant Part
//    ------------
class VariantPart : public Decl {
    VariantPart(void) = delete;
    VariantPart(const VariantPart &) = delete;
    VariantPart &operator=(const VariantPart &) = delete;


public:
    NamePtr name;
    VariantListPtr variants;


public:
    VariantPart(SourceLoc_t l, NamePtr n, VariantListPtr v) : Decl(l), name(std::move(n)), variants(std::move(v)) {}

};




//
// -- Component list
//    --------------
class ComponentList : public Decl {
    ComponentList(void) = delete;
    ComponentList(const ComponentList &) = delete;
    ComponentList &operator=(const ComponentList &) = delete;


public:
    ComponentDeclarationListPtr components;         // -- may be an empty list
    VariantPartPtr variantPart;                     // -- may be nullptr


public:
    ComponentList(SourceLoc_t l, ComponentDeclarationListPtr c, VariantPartPtr v) :
            Decl(l), components(std::move(c)), variantPart(std::move(v)) {}

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





