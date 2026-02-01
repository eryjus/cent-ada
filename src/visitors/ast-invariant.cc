//=================================================================================================================
//  ast-invariant.cc -- Implement the classes which will check the different AST structures
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



#include "ada.hh"



void ASTInvariant::Visit(const AccessTypeSpec &n) { assert(n.name); assert(n.type); }
void ASTInvariant::Visit(const AggregateExpr &n) { assert(n.list); assert(n.list->size()); }
void ASTInvariant::Visit(const AllocatorExpr &) { }
void ASTInvariant::Visit(const ArrayTypeSpec &n) { assert(n.list); assert(n.indices); assert(n.component); assert(n.list->size()); }
void ASTInvariant::Visit(const ASTNode &) { }
void ASTInvariant::Visit(const AttributeRange &n) { assert(n.rangeAttribute); }
void ASTInvariant::Visit(const BinaryExpr &n) { assert(n.lhs); assert(n.rhs); }
void ASTInvariant::Visit(const ComponentAssociation &n) { assert(n.choices); assert(n.expr); assert(n.choices->size()); }
void ASTInvariant::Visit(const ComponentDeclaration &n) { assert(n.names); assert(n.typeSpec); assert(n.names->size()); }
void ASTInvariant::Visit(const ComponentList &n) { assert(n.components); }
void ASTInvariant::Visit(const DerivedTypeSpec &n) { assert(n.name); assert(n.type); }
void ASTInvariant::Visit(const DiscriminantAssociation &n) { assert(n.names); assert(n.expr); }
void ASTInvariant::Visit(const DiscriminantConstraint &n) { assert(n.list); assert(n.list->size()); }
void ASTInvariant::Visit(const DiscriminantSpecification &n) { assert(n.ids); assert(n.type); assert(n.expr); assert(n.ids->size()); }
void ASTInvariant::Visit(const EnumerationTypeSpec &n) { assert(n.literals); assert(n.literals->size()); }
void ASTInvariant::Visit(const ExprChoice &n) { assert(n.expr); }
void ASTInvariant::Visit(const IndexConstraint &n) { assert(n.indices); assert(n.indices->size()); }
void ASTInvariant::Visit(const IntLiteralExpr &) { }
void ASTInvariant::Visit(const NameChoice &n) { assert(n.name); }
void ASTInvariant::Visit(const NameExpr &n) { assert(n.name); }
void ASTInvariant::Visit(const NullLiteralExpr &) { }
void ASTInvariant::Visit(const NumberDeclaration &n) { assert(n.names); assert(n.initializer); assert(n.names->size()); }
void ASTInvariant::Visit(const NumericTypeSpec &n) { assert(n.size); assert(n.range); }
void ASTInvariant::Visit(const ObjectDeclaration &n) { assert(n.names); assert(n.typeSpec); assert(n.names->size()); }
void ASTInvariant::Visit(const OthersChoice &) { }
void ASTInvariant::Visit(const QualExprAllocatorExpr &n) { assert(n.expr); }
void ASTInvariant::Visit(const QualifiedExpr &n) { assert(n.id); assert(n.expr); }
void ASTInvariant::Visit(const Range &n) { assert(n.lowerBound); assert(n.upperBound); }
void ASTInvariant::Visit(const RangeChoice &n) { assert(n.range); }
void ASTInvariant::Visit(const RangeConstraint &n) { assert(n.range); }
void ASTInvariant::Visit(const RangeExpr &n) { assert(n.range); }
void ASTInvariant::Visit(const RealLiteralExpr &) { }
void ASTInvariant::Visit(const RecordSpecification &n) { assert(n.components); }
void ASTInvariant::Visit(const StringLiteralExpr &) { }
void ASTInvariant::Visit(const SubtypeIndication &n) { assert(n.name); assert(n.constraint); }
void ASTInvariant::Visit(const SubtypeIndicationAllocatorExpr &n) { assert(n.sub); }
void ASTInvariant::Visit(const SubtypeRange &n) { assert(n.subtype); }
void ASTInvariant::Visit(const TypeConversionExpr &n) { assert(n.id); assert(n.expr); }
void ASTInvariant::Visit(const TypeDecl &) { }
void ASTInvariant::Visit(const UnaryExpr &n) { assert(n.expr); }
void ASTInvariant::Visit(const UnboundedRange &n) { assert(n.type); }
void ASTInvariant::Visit(const Variant &n) { assert(n.components); }
void ASTInvariant::Visit(const VariantPart &n) { assert(n.name); assert(n.variants); assert(n.variants->size()); }




