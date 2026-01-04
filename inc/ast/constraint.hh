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



