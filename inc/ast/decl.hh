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
// -- Object declaration
//    ------------------
class ObjectDeclaration : public Decl {
    ObjectDeclaration(void) = delete;
    ObjectDeclaration(const ObjectDeclaration &) = delete;
    ObjectDeclaration &operator=(const ObjectDeclaration &) = delete;


public:
    IdList names;
    bool isConstant;
    SubtypeIndicationPtr subtype;
    ExprPtr initializer;                // may be nullptr


public:
    ObjectDeclaration(SourceLoc_t l, IdList ids, bool c, SubtypeIndicationPtr s, ExprPtr i) :
            Decl(l), names(ids), isConstant(c), subtype(std::move(s)), initializer(std::move(i)) {}
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
    bool isConstant;
    ExprPtr initializer;


public:
    NumberDeclaration(SourceLoc_t l, IdListPtr ids, bool c, ExprPtr i) :
            Decl(l), names(std::move(ids)), isConstant(c), initializer(std::move(i)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
};



