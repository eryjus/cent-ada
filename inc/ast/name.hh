//=================================================================================================================
//  ast/name.hh -- This header is used for defining the classes which are derived from Name
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
// -- The common Name node
//    --------------------
class Name : public ASTNode {
    Name(void) = delete;
    Name(const Name &) = delete;
    Name &operator=(const Name &) = delete;

public:
    Name(SourceLoc_t l) : ASTNode(l) {}


public:
    virtual void Accept(ASTVisitor &) override {}
};



//
// -- This is the AST node for a list of identifiers
//    ----------------------------------------------
class IdentifierList : public Name {
    IdentifierList(void) = delete;
    IdentifierList(const IdentifierList &) = delete;
    IdentifierList &operator=(const IdentifierList &) = delete;

public:
    IdListPtr ids;

public:
    IdentifierList(SourceLoc_t l, IdListPtr list) : Name(loc), ids(std::move(list)) {}


public:
    void Accept(ASTVisitor &v) { v.Visit(*this); }
};
