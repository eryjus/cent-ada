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
// -- This is a range constraint, which can come is 2 flavors
//    -------------------------------------------------------
class RangeConstraint : public Constraint {
    RangeConstraint(void) = delete;
    RangeConstraint(const RangeConstraint &) = delete;
    RangeConstraint &operator=(const RangeConstraint &) = delete;

public:
    RangeConstraint(SourceLoc_t loc) : Constraint(loc) {}
};



//
// -- This is a discrete range constriant
//    -----------------------------------
class DiscreteRangeConstraint : public RangeConstraint {
    DiscreteRangeConstraint(void) = delete;
    DiscreteRangeConstraint(const DiscreteRangeConstraint &) = delete;
    DiscreteRangeConstraint &operator=(const DiscreteRangeConstraint &) = delete;

public:
    ExprPtr lowerBound;
    ExprPtr upperBound;

public:
    DiscreteRangeConstraint(SourceLoc_t loc, ExprPtr l, ExprPtr r)
            : RangeConstraint(loc), lowerBound(std::move(l)), upperBound(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};



//
// -- This is a attribute range constriant
//    ------------------------------------
class AttributeRangeConstraint : public RangeConstraint {
    AttributeRangeConstraint(void) = delete;
    AttributeRangeConstraint(const AttributeRangeConstraint &) = delete;
    AttributeRangeConstraint &operator=(const AttributeRangeConstraint &) = delete;

public:
    NamePtr rangeAttribute;

public:
    AttributeRangeConstraint(SourceLoc_t loc, NamePtr r)
            : RangeConstraint(loc), rangeAttribute(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};
