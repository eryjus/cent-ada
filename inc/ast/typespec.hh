//=================================================================================================================
//  ast/typespec.hh -- This header is used for defining the classes which type specifications (using existing)
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
// -- The common Type Specifications node (describing a type)
//    -------------------------------------------------------
class TypeSpec : public ASTNode {
    TypeSpec(void) = delete;
    TypeSpec(const TypeSpec &) = delete;
    TypeSpec &operator=(const TypeSpec &) = delete;

public:
    TypeSpec(SourceLoc_t l) : ASTNode(l) {}
};



//
// -- A Subtype Indication
//    --------------------
class SubtypeIndication : public TypeSpec {
    SubtypeIndication(void) = delete;
    SubtypeIndication(const SubtypeIndication &) = delete;
    SubtypeIndication &operator=(const SubtypeIndication &) = delete;

public:
    NamePtr name;
    ExprPtr constraint;         // may be nullptr


public:
    SubtypeIndication(SourceLoc_t l, NamePtr n, ExprPtr c)
            : TypeSpec(l), name(std::move(n)), constraint(std::move(c)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
};


