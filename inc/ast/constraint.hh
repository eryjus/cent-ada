//=================================================================================================================
//  ast/constraint.hh -- This header is used for defining the classes which are constraints
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Jan-04  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once



//
// -- This is the base class for all constraints
//    ------------------------------------------
class Constraint : public ASTNode {
    Constraint(void) = delete;
    Constraint(const Constraint &) = delete;
    Constraint &operator=(const Constraint &) = delete;

public:
    Constraint(SourceLoc_t loc) : ASTNode(loc) {}
};



//
// -- This is a range constraint
//    --------------------------
class RangeConstraint : public Constraint {
    RangeConstraint(void) = delete;
    RangeConstraint(const RangeConstraint &) = delete;
    RangeConstraint &operator=(const RangeConstraint &) = delete;

public:
    DiscreteRangePtr range;

public:
    RangeConstraint(SourceLoc_t loc, DiscreteRangePtr r) : Constraint(loc), range(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This class identifies an index constraint on an array
//    -----------------------------------------------------
class IndexConstraint : public Constraint {
    IndexConstraint(void) = delete;
    IndexConstraint(const IndexConstraint &) = delete;
    IndexConstraint &operator=(const IndexConstraint &) = delete;


public:
    bool unconstrained;
    DiscreteRangeListPtr indices;


public:
    IndexConstraint(SourceLoc_t loc, bool u, DiscreteRangeListPtr r) : Constraint(loc), unconstrained(u), indices(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a real constraint
//    -------------------------
class RealConstraint : public Constraint {
    RealConstraint(void) = delete;
    RealConstraint(const RealConstraint &) = delete;
    RealConstraint &operator=(const RealConstraint &) = delete;

public:
    NumericTypeSpecPtr range;

public:
    RealConstraint(SourceLoc_t loc, NumericTypeSpecPtr r) : Constraint(loc), range(std::move(r)) {}
};



//
// -- This is a discriminant constraint
//    ---------------------------------
class DiscriminantConstraint : public Constraint {
    DiscriminantConstraint(void) = delete;
    DiscriminantConstraint(const DiscriminantConstraint &) = delete;
    DiscriminantConstraint &operator=(const DiscriminantConstraint &) = delete;

public:
    DiscriminantAssociationListPtr list;

public:
    DiscriminantConstraint(SourceLoc_t loc, DiscriminantAssociationListPtr l) : Constraint(loc), list(std::move(l)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



