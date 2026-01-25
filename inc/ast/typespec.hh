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
    NameListPtr list;
    bool unconstrained;
    IndexConstraintPtr indices;
    SubtypeIndicationPtr component;


public:
    ArrayTypeSpec(SourceLoc_t l, NameListPtr n, bool u, IndexConstraintPtr i, SubtypeIndicationPtr c)
            : TypeSpec(l), list(std::move(n)), unconstrained(u), indices(std::move(i)), component(std::move(c)) {}

};



//
// -- An access type specification
//    ----------------------------
class AccessTypeSpec : public TypeSpec {
    AccessTypeSpec(void) = delete;
    AccessTypeSpec(const AccessTypeSpec &) = delete;
    AccessTypeSpec &operator=(const AccessTypeSpec &) = delete;

public:
    NamePtr name;
    SubtypeIndicationPtr type;


public:
    AccessTypeSpec(SourceLoc_t l, NamePtr n, SubtypeIndicationPtr t)
            : TypeSpec(l), name(std::move(n)), type(std::move(t)) {}

};



//
// -- An derived type specification
//    -----------------------------
class DerivedTypeSpec : public TypeSpec {
    DerivedTypeSpec(void) = delete;
    DerivedTypeSpec(const DerivedTypeSpec &) = delete;
    DerivedTypeSpec &operator=(const DerivedTypeSpec &) = delete;

public:
    NamePtr name;
    SubtypeIndicationPtr type;


public:
    DerivedTypeSpec(SourceLoc_t l, NamePtr n, SubtypeIndicationPtr t)
            : TypeSpec(l), name(std::move(n)), type(std::move(t)) {}

};



//
// -- This is a discriminant association, which stands largely on its own
//    -------------------------------------------------------------------
class DiscriminantAssociation : public ASTNode {
    DiscriminantAssociation(void) = delete;
    DiscriminantAssociation(const DiscriminantAssociation &) = delete;
    DiscriminantAssociation &operator=(const DiscriminantAssociation &) = delete;

public:
    NameListPtr names;              // always initialized; may be an empty list
    ExprPtr expr;

public:
    DiscriminantAssociation(SourceLoc_t l, NameListPtr n, ExprPtr e) : ASTNode(l), names(std::move(n)), expr(std::move(e)) {}
};



//
// -- This is a discriminant specification
//    ------------------------------------
class DiscriminantSpecification : public TypeSpec {
    DiscriminantSpecification(void) = delete;
    DiscriminantSpecification(const DiscriminantSpecification &) = delete;
    DiscriminantSpecification &operator=(const DiscriminantSpecification &) = delete;

public:
    IdListPtr ids;
    NamePtr type;
    ExprPtr expr;

public:
    DiscriminantSpecification(SourceLoc_t l, IdListPtr i, NamePtr t, ExprPtr e)
            : TypeSpec(l), ids(std::move(i)), type(std::move(t)), expr(std::move(e)) {}
};



//
// -- This is a record specification
//    ------------------------------
class RecordSpecification : public TypeSpec {
    RecordSpecification(void) = delete;
    RecordSpecification(const RecordSpecification &) = delete;
    RecordSpecification &operator=(const RecordSpecification &) = delete;

public:
    Id id;
    ComponentListPtr components;

public:
    RecordSpecification(SourceLoc_t l, Id id, ComponentListPtr comps) : TypeSpec(l), id(id), components(std::move(comps)) {}
};



