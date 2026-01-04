//=================================================================================================================
//  ast/typedecl.hh -- This header is used for defining the classes which type declarations (creating new ones)
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



class FullTypeDeclaration : public TypeDecl {
    FullTypeDeclaration(void) = delete;
    FullTypeDeclaration(const FullTypeDeclaration &) = delete;
    FullTypeDeclaration &operator=(const FullTypeDeclaration &) = delete;


public:
    Id name;
    ExprPtr discriminantPart;           // -- may be null
    TypeSpecPtr definition;


public:
    FullTypeDeclaration(SourceLoc_t loc, Id n, ExprPtr dis, TypeSpecPtr defn)
            : TypeDecl(loc), name(n), discriminantPart(std::move(dis)), definition(std::move(defn)) {}

public:
    virtual void Accept(ASTVisitor &v) override { v.Visit(*this); }
};





