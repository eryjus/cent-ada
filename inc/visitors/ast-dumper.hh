//=================================================================================================================
//  ast-dumper.hh -- Dump the contents of the AST in an S-Expr format
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Apr-04  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once




//
// -- This class will be able to dump the contents of each AST Node
//    -------------------------------------------------------------
class ASTDumper : public ASTVisitor {
    ASTDumper(const ASTDumper &) = delete;
    ASTDumper &operator=(const ASTDumper &) = delete;


protected:
    int depth;
    std::ostringstream os;


public:
    explicit ASTDumper(void) { depth = 0; }
    ~ASTDumper() = default;


public:
    std::string Get(void) { return os.str(); }



public:
    virtual void Visit(const AccessTypeSpec &) override {}
    virtual void Visit(const AggregateExpr &) override {}
    virtual void Visit(const ArrayTypeSpec &) override {}
    virtual void Visit(const AttributeName &) override {}
    virtual void Visit(const AttributeRange &) override {}
    virtual void Visit(const BinaryExpr &) override {}
    virtual void Visit(const CharacterLiteralName &) override {}
    virtual void Visit(const ComponentAssociation &) override {}
    virtual void Visit(const ComponentDeclaration &) override {}
    virtual void Visit(const ComponentList &) override {}
    virtual void Visit(const DerivedTypeSpec &) override {}
    virtual void Visit(const DiscriminantAssociation &) override {}
    virtual void Visit(const DiscriminantConstraint &) override {}
    virtual void Visit(const DiscriminantSpecification &) override {}
    virtual void Visit(const EnumerationTypeSpec &) override {}
    virtual void Visit(const ExprChoice &) override {}
    virtual void Visit(const IdentifierList &) override {}
    virtual void Visit(const IndexConstraint &) override {}
    virtual void Visit(const IndexedName &) override {}
    virtual void Visit(const IntLiteralExpr &) override {}
    virtual void Visit(const NameChoice &) override {}
    virtual void Visit(const NameExpr &) override {}
    virtual void Visit(const NullLiteralExpr &) override {}
    virtual void Visit(const NumericTypeSpec &) override {}
    virtual void Visit(const ObjectDeclaration &) override {}
    virtual void Visit(const OthersChoice &) override {}
    virtual void Visit(const QualExprAllocatorExpr &) override {}
    virtual void Visit(const QualifiedExpr &) override {}
    virtual void Visit(const Range &) override {}
    virtual void Visit(const RangeChoice &) override {}
    virtual void Visit(const RangeConstraint &) override {}
    virtual void Visit(const RangeExpr &) override {}
    virtual void Visit(const RealConstraint &) override {}
    virtual void Visit(const RealLiteralExpr &) override {}
    virtual void Visit(const RecordSpecification &) override {}
    virtual void Visit(const SelectedName &) override {}
    virtual void Visit(const SimpleName &) override {}
    virtual void Visit(const SliceName &) override {}
    virtual void Visit(const StringLiteralExpr &) override {}
    virtual void Visit(const SubtypeIndication &) override {}
    virtual void Visit(const SubtypeIndicationAllocatorExpr &) override {}
    virtual void Visit(const SubtypeRange &) override {}
    virtual void Visit(const TypeConversionExpr &) override {}
    virtual void Visit(const TypeDecl &) override {}
    virtual void Visit(const UnaryExpr &) override {}
    virtual void Visit(const UnboundedRange &) override {}
    virtual void Visit(const Variant &) override {}
    virtual void Visit(const VariantPart &) override {}
    virtual void Visit(const NullStmt &) override {}
    virtual void Visit(const AssignStmt &) override {}
    virtual void Visit(const IfStmt &) override {}
    virtual void Visit(const CaseStmtAlt &) override {}
    virtual void Visit(const CaseStmt &) override {}
    virtual void Visit(const LoopStmt &) override {}
    virtual void Visit(const BlockStmt &) override {}
    virtual void Visit(const ExitStmt &) override {}
    virtual void Visit(const ReturnStmt &) override {}
    virtual void Visit(const GotoStmt &) override {}
};

