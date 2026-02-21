//=================================================================================================================
//  ast/stmt.hh -- This header is used for defining the classes which are derived from Stmt
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
// -- The common Statement node
//    -------------------------
class Stmt : public ASTNode {
    Stmt(void) = delete;
    Stmt(const Stmt &) = delete;
    Stmt &operator=(const Stmt &) = delete;

public:
    Stmt(SourceLoc_t l) : ASTNode(l) {}
};



