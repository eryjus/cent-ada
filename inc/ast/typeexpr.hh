//=================================================================================================================
//  ast/typeexpr.hh -- This header is used for defining the classes which type expressions (not type declarations)
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
// -- A Subtype Indication
//    --------------------
class SubtypeIndication : public TypeExpr {
    SubtypeIndication(void) = delete;
    SubtypeIndication(const SubtypeIndication &) = delete;
    SubtypeIndication &operator=(const SubtypeIndication &) = delete;

public:
    NamePtr name;
    ExprPtr constraint;         // may be nullptr


public:
    SubtypeIndication(SourceLoc_t l, NamePtr n, ExprPtr c)
            : TypeExpr(l), name(std::move(n)), constraint(std::move(c)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
};


