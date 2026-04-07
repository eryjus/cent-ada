//=================================================================================================================
//  ada.hh -- This is the global header file for the entire compiler
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once



//
// -- Include standard libraries
//    --------------------------
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <variant>
#include <algorithm>
#include <sstream>



//
// -- Get the enumeration definitions before anything else
//    ----------------------------------------------------
#include "enum.hh"



//
// -- Inlcude the tokens and then clean up some types
//    -----------------------------------------------
#include "tokens.hh"
extern YYSTYPE yylval;



//
// -- Here are quite a few forward declarations
//    -----------------------------------------
class AccessTypeSpec;
class AggregateExpr;
class AllocatorExpr;
class ArrayTypeSpec;
class ASTNode;
class AttributeName;
class AttributeRange;
class BinaryExpr;
class CharacterLiteralName;
class Choice;
class ComponentAssociation;
class ComponentDeclaration;
class ComponentList;
class Constraint;
class Decl;
class DerivedTypeSpec;
class DiscreteRange;
class DiscriminantAssociation;
class DiscriminantConstraint;
class DiscriminantSpecification;
class EnumerationTypeSpec;
class Expr;
class ExprChoice;
class IdentifierList;
class IndexConstraint;
class IndexedName;
class IntLiteralExpr;
class Name;
class NameChoice;
class NameExpr;
class NullLiteralExpr;
class NumericTypeSpec;
class ObjectDeclaration;
class OthersChoice;
class QualExprAllocatorExpr;
class QualifiedExpr;
class Range;
class RangeChoice;
class RangeConstraint;
class RangeExpr;
class RealConstraint;
class RealLiteralExpr;
class RecordSpecification;
class SelectedName;
class SimpleName;
class SliceName;
class Stmt;
class StringLiteralExpr;
class SubtypeIndication;
class SubtypeIndicationAllocatorExpr;
class SubtypeRange;
class SymbolVisitor;
class TypeConversionExpr;
class TypeDecl;
class TypeSpec;
class UnaryExpr;
class UnboundedRange;
class Variant;
class VariantPart;
class AttributeConstraint;
class NullStmt;
class AssignStmt;
class IfStmt;
class CaseStmtAlt;
class CaseStmt;
class LoopStmt;
class BlockStmt;
class ExitStmt;
class ReturnStmt;
class GotoStmt;



using NodePtr = std::unique_ptr<ASTNode>;
using AccessTypeSpecPtr = std::unique_ptr<AccessTypeSpec>;
using AggregateExprPtr = std::unique_ptr<AggregateExpr>;
using AllocatorExprPtr = std::unique_ptr<AllocatorExpr>;
using ArrayTypeSpecPtr = std::unique_ptr<ArrayTypeSpec>;
using AttributeNamePtr = std::unique_ptr<AttributeName>;
using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using CharacterLiteralNamePtr = std::unique_ptr<CharacterLiteralName>;
using ChoicePtr = std::unique_ptr<Choice>;
using ComponentAssociationPtr = std::unique_ptr<ComponentAssociation>;
using ComponentDeclarationPtr = std::unique_ptr<ComponentDeclaration>;
using ComponentListPtr = std::unique_ptr<ComponentList>;
using ConstraintPtr = std::unique_ptr<Constraint>;
using DeclPtr = std::unique_ptr<Decl>;
using DerivedTypeSpecPtr = std::unique_ptr<DerivedTypeSpec>;
using DiscreteRangePtr = std::unique_ptr<DiscreteRange>;
using DiscriminantAssociationPtr = std::unique_ptr<DiscriminantAssociation>;
using DiscriminantConstraintPtr = std::unique_ptr<DiscriminantConstraint>;
using DiscriminantSpecificationPtr = std::unique_ptr<DiscriminantSpecification>;
using EnumerationTypeSpecPtr = std::unique_ptr<EnumerationTypeSpec>;
using ExprChoicePtr = std::unique_ptr<ExprChoice>;
using ExprPtr = std::unique_ptr<Expr>;
using IndexConstraintPtr = std::unique_ptr<IndexConstraint>;
using IndexedNamePtr = std::unique_ptr<IndexedName>;
using IntLiteralExprPtr = std::unique_ptr<IntLiteralExpr>;
using NameChoicePtr = std::unique_ptr<NameChoice>;
using NameExprPtr = std::unique_ptr<NameExpr>;
using NamePtr = std::unique_ptr<Name>;
using NodePtr = std::unique_ptr<ASTNode>;
using NullLiteralExprPtr = std::unique_ptr<NullLiteralExpr>;
using NumericTypeSpecPtr = std::unique_ptr<NumericTypeSpec>;
using ObjectDeclarationPtr = std::unique_ptr<ObjectDeclaration>;
using OthersChoicePtr = std::unique_ptr<OthersChoice>;
using QualExprAllocatorExprPtr = std::unique_ptr<QualExprAllocatorExpr>;
using QualifiedExprPtr = std::unique_ptr<QualifiedExpr>;
using RangeChoicePtr = std::unique_ptr<RangeChoice>;
using RangeConstraintPtr = std::unique_ptr<RangeConstraint>;
using RangeExprPtr = std::unique_ptr<RangeExpr>;
using RangePtr = std::unique_ptr<Range>;
using RealConstraintPtr = std::unique_ptr<RealConstraint>;
using RealLiteralExprPtr = std::unique_ptr<RealLiteralExpr>;
using RecordSpecificationPtr = std::unique_ptr<RecordSpecification>;
using SelectedNamePtr = std::unique_ptr<SelectedName>;
using SimpleNamePtr = std::unique_ptr<SimpleName>;
using SliceNamePtr = std::unique_ptr<SliceName>;
using StmtPtr = std::unique_ptr<Stmt>;
using StringLiteralExprPtr = std::unique_ptr<StringLiteralExpr>;
using SubtypeIndicationAllocatorExprPtr = std::unique_ptr<SubtypeIndicationAllocatorExpr>;
using SubtypeIndicationPtr = std::unique_ptr<SubtypeIndication>;
using SubtypeRangePtr = std::unique_ptr<SubtypeRange>;
using TypeConversionExprPtr = std::unique_ptr<TypeConversionExpr>;
using TypeDeclPtr = std::unique_ptr<TypeDecl>;
using TypeSpecPtr = std::unique_ptr<TypeSpec>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;
using UnboundedRangePtr = std::unique_ptr<UnboundedRange>;
using VariantPartPtr = std::unique_ptr<VariantPart>;
using VariantPtr = std::unique_ptr<Variant>;
using AttributeConstraintPtr = std::unique_ptr<AttributeConstraint>;
using NullStmtPtr = std::unique_ptr<NullStmt>;
using AssignStmtPtr = std::unique_ptr<AssignStmt>;
using IfStmtPtr = std::unique_ptr<IfStmt>;
using CaseStmtAltPtr = std::unique_ptr<CaseStmtAlt>;
using CaseStmtPtr = std::unique_ptr<CaseStmt>;
using LoopStmtPtr = std::unique_ptr<LoopStmt>;
using BlockStmtPtr = std::unique_ptr<BlockStmt>;
using ExitStmtPtr = std::unique_ptr<ExitStmt>;
using ReturnStmtPtr = std::unique_ptr<ReturnStmt>;
using GotoStmtPtr = std::unique_ptr<GotoStmt>;



using NodeList = std::vector<NodePtr>;
using NodeListPtr = std::unique_ptr<NodeList>;
using ChoiceList = std::vector<ChoicePtr>;
using ChoiceListPtr = std::unique_ptr<ChoiceList>;
using ComponentAssociationList = std::vector<ComponentAssociationPtr>;
using ComponentAssociationListPtr = std::unique_ptr<ComponentAssociationList>;
using ComponentDeclarationList = std::vector<ComponentDeclarationPtr>;
using ComponentDeclarationListPtr = std::unique_ptr<ComponentDeclarationList>;
using DiscreteRangeList = std::vector<DiscreteRangePtr>;
using DiscreteRangeListPtr = std::unique_ptr<DiscreteRangeList>;
using DiscriminantAssociationList = std::vector<DiscriminantAssociationPtr>;
using DiscriminantAssociationListPtr = std::unique_ptr<DiscriminantAssociationList>;
using DiscriminantSpecificationList = std::vector<DiscriminantSpecificationPtr>;
using DiscriminantSpecificationListPtr = std::unique_ptr<DiscriminantSpecificationList>;
using ExprList = std::vector<ExprPtr>;
using ExprListPtr = std::unique_ptr<ExprList>;
using IdList = std::vector<struct Id>;
using IdListPtr = std::unique_ptr<IdList>;
using NameList = std::vector<NamePtr>;
using NameListPtr = std::unique_ptr<NameList>;
using VariantList = std::vector<VariantPtr>;
using VariantListPtr = std::unique_ptr<VariantList>;
using StmtList = std::vector<StmtPtr>;
using StmtListPtr = std::unique_ptr<StmtList>;
using CaseStmtAltList = std::vector<CaseStmtAltPtr>;
using CaseStmtAltListPtr = std::unique_ptr<CaseStmtAltList>;
using DeclList = std::vector<DeclPtr>;
using DeclListPtr = std::unique_ptr<DeclList>;




//
// -- Include the other headers
//    -------------------------
#include "options.hh"
#include "tstream.hh"
#include "diag.hh"
#include "sym-tab.hh"
#include "visitors.hh"
#include "parser.hh"
#include "ast.hh"




//
// -- some global variables
//    ---------------------
extern std::string strVal;
extern int column;


