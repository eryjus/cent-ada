//=================================================================================================================
//  ast/discrete-range.hh -- This header is used for defining the classes which are discrete ranges
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
// -- This is the base class for all ranges
//    -------------------------------------
class DiscreteRange : public ASTNode {
    DiscreteRange(void) = delete;
    DiscreteRange(const DiscreteRange &) = delete;
    DiscreteRange &operator=(const DiscreteRange &) = delete;

public:
    DiscreteRange(SourceLoc_t loc) : ASTNode(loc) {}
};



//
// -- This is a range
//    ---------------
class Range : public DiscreteRange {
    Range(void) = delete;
    Range(const Range &) = delete;
    Range &operator=(const Range &) = delete;

public:
    ExprPtr lowerBound;
    ExprPtr upperBound;

public:
    Range(SourceLoc_t loc, ExprPtr l, ExprPtr r)
            : DiscreteRange(loc), lowerBound(std::move(l)), upperBound(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};



//
// -- This is a subtype range
//    -----------------------
class SubtypeRange : public DiscreteRange {
    SubtypeRange(void) = delete;
    SubtypeRange(const SubtypeRange &) = delete;
    SubtypeRange &operator=(const SubtypeRange &) = delete;

public:
    SubtypeIndicationPtr subtype;

public:
    SubtypeRange(SourceLoc_t loc, SubtypeIndicationPtr r)
            : DiscreteRange(loc), subtype(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};



//
// -- This is an attribute range
//    --------------------------
class AttributeRange : public DiscreteRange {
    AttributeRange(void) = delete;
    AttributeRange(const AttributeRange &) = delete;
    AttributeRange &operator=(const AttributeRange &) = delete;

public:
    NamePtr rangeAttribute;

public:
    AttributeRange(SourceLoc_t loc, NamePtr r)
            : DiscreteRange(loc), rangeAttribute(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};


//
// -- This is an unbounded index range
//    --------------------------------
class UnboundedRange : public DiscreteRange {
    UnboundedRange(void) = delete;
    UnboundedRange(const UnboundedRange &) = delete;
    UnboundedRange &operator=(const UnboundedRange &) = delete;

public:
    Id type;

public:
    UnboundedRange(SourceLoc_t loc, Id id)
            : DiscreteRange(loc), type(id) {}

};


