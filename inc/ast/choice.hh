//=================================================================================================================
//  ast/choice.hh -- This header is used for defining the classes which are choices
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Jan-14  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once



//
// -- This is the base class for all choices
//    --------------------------------------
class Choice : public ASTNode {
    Choice(void) = delete;
    Choice(const Choice &) = delete;
    Choice &operator=(const Choice &) = delete;

public:
    Choice(SourceLoc_t loc) : ASTNode(loc) {}
};



//
// -- This is an 'others' choice
//    --------------------------
class OthersChoice : public Choice {
    OthersChoice(void) = delete;
    OthersChoice(const OthersChoice &) = delete;
    OthersChoice &operator=(const OthersChoice &) = delete;

public:
    OthersChoice(SourceLoc_t loc) : Choice(loc) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a range choice
//    ----------------------
class RangeChoice : public Choice {
    RangeChoice(void) = delete;
    RangeChoice(const RangeChoice &) = delete;
    RangeChoice &operator=(const RangeChoice &) = delete;


public:
    DiscreteRangePtr range;


public:
    RangeChoice(SourceLoc_t loc, DiscreteRangePtr r) : Choice(loc), range(std::move(r)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a name choice
//    ---------------------
class NameChoice : public Choice {
    NameChoice(void) = delete;
    NameChoice(const NameChoice &) = delete;
    NameChoice &operator=(const NameChoice &) = delete;


public:
    NamePtr name;


public:
    NameChoice(SourceLoc_t loc, NamePtr n) : Choice(loc), name(std::move(n)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is an expr choice
//    ---------------------
class ExprChoice : public Choice {
    ExprChoice(void) = delete;
    ExprChoice(const ExprChoice &) = delete;
    ExprChoice &operator=(const ExprChoice &) = delete;


public:
    ExprPtr expr;


public:
    ExprChoice(SourceLoc_t loc, ExprPtr e) : Choice(loc), expr(std::move(e)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



