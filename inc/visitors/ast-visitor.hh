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
    virtual void Visit(const Name &) { std::cout << "Unimplemented\n"; }

    virtual void Visit(const SubtypeIndication &) = 0;
    virtual void Visit(const NumberDeclaration &) = 0;
    virtual void Visit(const ObjectDeclaration &) = 0;
    virtual void Visit(const TypeDecl &) = 0;
    virtual void Visit(const EnumerationTypeSpec &) = 0;
    virtual void Visit(const RangeConstraint &) = 0;
    virtual void Visit(const NumericTypeSpec &) = 0;
    virtual void Visit(const Range &) = 0;
    virtual void Visit(const SubtypeRange &) = 0;
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
    void PrintField(std::string label, std::string value);
    void PrintIdList(std::string label, IdList *child);


    virtual void Visit(const SubtypeIndication &) override;
    virtual void Visit(const NumberDeclaration &) override;
    virtual void Visit(const ObjectDeclaration &) override;
    virtual void Visit(const TypeDecl &) override;
    virtual void Visit(const EnumerationTypeSpec &) override;
    virtual void Visit(const RangeConstraint &) override;
    virtual void Visit(const NumericTypeSpec &) override;
    virtual void Visit(const Range &) override;
    virtual void Visit(const SubtypeRange &) override;
};



//
// -- AST Invariant checker
//    ---------------------
class ASTInvariant : public ASTVisitor {
protected:
    int depth = 0;


public:
    ASTInvariant(void) {}


protected:
    virtual void Visit(const SubtypeIndication &n) override;
    virtual void Visit(const NumberDeclaration &n) override;
    virtual void Visit(const ObjectDeclaration &n) override;
    virtual void Visit(const TypeDecl &n) override;
    virtual void Visit(const EnumerationTypeSpec &n) override;
    virtual void Visit(const RangeConstraint &n) override;
    virtual void Visit(const NumericTypeSpec &n) override;
    virtual void Visit(const Range &n) override;
    virtual void Visit(const SubtypeRange &n) override;
};


