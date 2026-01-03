//=================================================================================================================
//  ast-visitor.hh -- Handle visiting all the AST nodes
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
// -- This class will be able to visit each AST Node
//    ----------------------------------------------
class ASTVisitor {
public:
    virtual void Visit(const SubtypeIndication &) = 0;
    virtual void Visit(const Name &) { std::cout << "Unimplemented\n"; }
};




//
// -- Print each AST node
//    -------------------
class ASTPrinter : public ASTVisitor {
protected:
    int depth = 0;


public:
    ASTPrinter(void) { std::cout << "PRINTING THE AST STRUCTURE\n==========================\n"; }

protected:

    void PrintDepth(void) {
        for (int i = 0; i < depth; i ++) std::cout << "  ";
    }


protected:
    void PrintRequiredChild(std::string label, ASTNode *child);
    void PrintOptionalChild(std::string label, ASTNode *child);
    void Visit(const SubtypeIndication &);
};

