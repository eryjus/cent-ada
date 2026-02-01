//=================================================================================================================
//  ast/component-association.hh -- This header is used for defining the component association class
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
// -- This is the component association class
//    ---------------------------------------
class ComponentAssociation : public ASTNode {
    ComponentAssociation(void) = delete;
    ComponentAssociation(const ComponentAssociation &) = delete;
    ComponentAssociation &operator=(const ComponentAssociation &) = delete;

public:
    ChoiceListPtr choices;
    ExprPtr expr;


public:
    ComponentAssociation(SourceLoc_t loc, ChoiceListPtr l, ExprPtr e)
            : ASTNode(loc), choices(std::move(l)), expr(std::move(expr)) {}


public:
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



