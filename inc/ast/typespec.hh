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
// -- An Enumeration Type Spec
//    ------------------------
class EnumerationTypeSpec : public TypeSpec {
    EnumerationTypeSpec(void) = delete;
    EnumerationTypeSpec(const EnumerationTypeSpec &) = delete;
    EnumerationTypeSpec &operator=(const EnumerationTypeSpec &) = delete;

public:
    IdListPtr literals;


public:
    EnumerationTypeSpec(SourceLoc_t l, IdListPtr lits)
            : TypeSpec(l), literals(std::move(lits)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- A numeric Type Specification
//    ----------------------------
class NumericTypeSpec : public TypeSpec {
    NumericTypeSpec(void) = delete;
    NumericTypeSpec(const NumericTypeSpec &) = delete;
    NumericTypeSpec &operator=(const NumericTypeSpec &) = delete;


public:
    enum class Kind {
        Integer,
        FixedPoint,
        FloatingPoint,
    };


public:
    Kind kind;
    ExprPtr size;                   // nullptr for Kind::Integer; ::FixedPoint = Delta; ::FloatingPoint = Digits
    RangeConstraintPtr range;


public:
    NumericTypeSpec(SourceLoc_t l, Kind k, ExprPtr s, RangeConstraintPtr c)
            : TypeSpec(l), kind(k), size(std::move(s)), range(std::move(c)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
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



//
// -- An array type specification
//    ---------------------------
class ArrayTypeSpec : public TypeSpec {
    ArrayTypeSpec(void) = delete;
    ArrayTypeSpec(const ArrayTypeSpec &) = delete;
    ArrayTypeSpec &operator=(const ArrayTypeSpec &) = delete;

public:
    NamePtr name;
    bool unconstrained;
    DiscreteRangeListPtr indices;
    SubtypeIndicationPtr component;


public:
    ArrayTypeSpec(SourceLoc_t l, NamePtr n, bool u, DiscreteRangeListPtr i, SubtypeIndicationPtr c)
            : TypeSpec(l), name(std::move(n)), unconstrained(u), indices(std::move(i)), component(std::move(c)) {}

};



