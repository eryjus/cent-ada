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

    virtual void Visit(const AccessTypeSpec &) = 0;
    virtual void Visit(const AggregateExpr &) = 0;
    virtual void Visit(const AllocatorExpr &) = 0;
    virtual void Visit(const ArrayTypeSpec &) = 0;
    virtual void Visit(const ASTNode &) = 0;
    virtual void Visit(const AttributeRange &) = 0;
    virtual void Visit(const BinaryExpr &) = 0;
    virtual void Visit(const ComponentAssociation &) = 0;
    virtual void Visit(const ComponentDeclaration &) = 0;
    virtual void Visit(const ComponentList &) = 0;
    virtual void Visit(const DerivedTypeSpec &) = 0;
    virtual void Visit(const DiscriminantAssociation &) = 0;
    virtual void Visit(const DiscriminantConstraint &) = 0;
    virtual void Visit(const DiscriminantSpecification &) = 0;
    virtual void Visit(const EnumerationTypeSpec &) = 0;
    virtual void Visit(const ExprChoice &) = 0;
    virtual void Visit(const IndexConstraint &) = 0;
    virtual void Visit(const IntLiteralExpr &) = 0;
    virtual void Visit(const NameChoice &) = 0;
    virtual void Visit(const NameExpr &) = 0;
    virtual void Visit(const NullLiteralExpr &) = 0;
    virtual void Visit(const NumberDeclaration &) = 0;
    virtual void Visit(const NumericTypeSpec &) = 0;
    virtual void Visit(const ObjectDeclaration &) = 0;
    virtual void Visit(const OthersChoice &) = 0;
    virtual void Visit(const QualExprAllocatorExpr &) = 0;
    virtual void Visit(const QualifiedExpr &) = 0;
    virtual void Visit(const Range &) = 0;
    virtual void Visit(const RangeChoice &) = 0;
    virtual void Visit(const RangeConstraint &) = 0;
    virtual void Visit(const RangeExpr &) = 0;
    virtual void Visit(const RealLiteralExpr &) = 0;
    virtual void Visit(const RecordSpecification &) = 0;
    virtual void Visit(const StringLiteralExpr &) = 0;
    virtual void Visit(const SubtypeIndication &) = 0;
    virtual void Visit(const SubtypeIndicationAllocatorExpr &) = 0;
    virtual void Visit(const SubtypeRange &) = 0;
    virtual void Visit(const TypeConversionExpr &) = 0;
    virtual void Visit(const TypeDecl &) = 0;
    virtual void Visit(const UnaryExpr &) = 0;
    virtual void Visit(const UnboundedRange &) = 0;
    virtual void Visit(const Variant &) = 0;
    virtual void Visit(const VariantPart &) = 0;
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
    virtual void Visit(const IndexConstraint &) override;
    virtual void Visit(const AttributeRange &) override;
    virtual void Visit(const ComponentAssociation &) override {}
    virtual void Visit(const ExprChoice &) override {}
    virtual void Visit(const NameChoice &) override {}
    virtual void Visit(const RangeChoice &) override {}
    virtual void Visit(const OthersChoice &) override {}
    virtual void Visit(const UnboundedRange &) override {}
    virtual void Visit(const DiscriminantConstraint &) override {}
    virtual void Visit(const RecordSpecification &) override {}
    virtual void Visit(const DiscriminantSpecification &) override {}
    virtual void Visit(const DiscriminantAssociation &) override {}
    virtual void Visit(const DerivedTypeSpec &) override {}
    virtual void Visit(const AccessTypeSpec &) override {}
    virtual void Visit(const ArrayTypeSpec &) override {}
    virtual void Visit(const SubtypeIndicationAllocatorExpr &) override {}
    virtual void Visit(const QualExprAllocatorExpr &) override {}
    virtual void Visit(const AllocatorExpr &) override {}
    virtual void Visit(const TypeConversionExpr &) override {}
    virtual void Visit(const QualifiedExpr &) override {}
    virtual void Visit(const AggregateExpr &) override {}
    virtual void Visit(const RangeExpr &) override {}
    virtual void Visit(const NameExpr &) override {}
    virtual void Visit(const StringLiteralExpr &) override {}
    virtual void Visit(const RealLiteralExpr &) override {}
    virtual void Visit(const IntLiteralExpr &) override {}
    virtual void Visit(const NullLiteralExpr &) override {}
    virtual void Visit(const BinaryExpr &) override {}
    virtual void Visit(const UnaryExpr &) override {}
    virtual void Visit(const ComponentList &) override {}
    virtual void Visit(const VariantPart &) override {}
    virtual void Visit(const Variant &) override {}
    virtual void Visit(const ComponentDeclaration &) override {}
    virtual void Visit(const ASTNode &) override {}
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
    virtual void Visit(const AccessTypeSpec &) override;
    virtual void Visit(const AggregateExpr &) override;
    virtual void Visit(const AllocatorExpr &) override;
    virtual void Visit(const ArrayTypeSpec &) override;
    virtual void Visit(const ASTNode &) override;
    virtual void Visit(const AttributeRange &) override;
    virtual void Visit(const BinaryExpr &) override;
    virtual void Visit(const ComponentAssociation &) override;
    virtual void Visit(const ComponentDeclaration &) override;
    virtual void Visit(const ComponentList &) override;
    virtual void Visit(const DerivedTypeSpec &) override;
    virtual void Visit(const DiscriminantAssociation &) override;
    virtual void Visit(const DiscriminantConstraint &) override;
    virtual void Visit(const DiscriminantSpecification &) override;
    virtual void Visit(const EnumerationTypeSpec &n) override;
    virtual void Visit(const ExprChoice &) override;
    virtual void Visit(const IndexConstraint &n) override;
    virtual void Visit(const IntLiteralExpr &) override;
    virtual void Visit(const NameChoice &) override;
    virtual void Visit(const NameExpr &) override;
    virtual void Visit(const NullLiteralExpr &) override;
    virtual void Visit(const NumberDeclaration &n) override;
    virtual void Visit(const NumericTypeSpec &n) override;
    virtual void Visit(const ObjectDeclaration &n) override;
    virtual void Visit(const OthersChoice &) override;
    virtual void Visit(const QualExprAllocatorExpr &) override;
    virtual void Visit(const QualifiedExpr &) override;
    virtual void Visit(const Range &n) override;
    virtual void Visit(const RangeChoice &) override;
    virtual void Visit(const RangeConstraint &n) override;
    virtual void Visit(const RangeExpr &) override;
    virtual void Visit(const RealLiteralExpr &) override;
    virtual void Visit(const RecordSpecification &) override;
    virtual void Visit(const StringLiteralExpr &) override;
    virtual void Visit(const SubtypeIndication &n) override;
    virtual void Visit(const SubtypeIndicationAllocatorExpr &) override;
    virtual void Visit(const SubtypeRange &n) override;
    virtual void Visit(const TypeConversionExpr &) override;
    virtual void Visit(const TypeDecl &n) override;
    virtual void Visit(const UnaryExpr &) override;
    virtual void Visit(const UnboundedRange &) override;
    virtual void Visit(const Variant &) override;
    virtual void Visit(const VariantPart &) override;
};


