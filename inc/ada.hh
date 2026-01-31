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




//
// -- Inlcude the tokens and then clean up some types
//    -----------------------------------------------
#include "tokens.hh"
extern YYSTYPE yylval;



enum class UnaryOper {
    Unspecified,
    Plus,
    Minus,
    Abs,
    Not,
};


enum class BinaryOper {
    Unspecified,
    And,
    AndThen,
    Or,
    OrElse,
    Xor,
    Equal,
    NotEqual,
    LessThan,
    LessEqual,
    GreaterThan,
    GreaterEqual,
    Plus,
    Minus,
    Concatenate,
    Times,
    Divide,
    Mod,
    Rem,
    Power,
    In,
};



//
// -- Here are quite a few forward declarations
//    -----------------------------------------
class AccessTypeSpec;
class AccessTypeSymbol;
class AggregateExpr;
class AllocatorExpr;
class ArrayTypeSpec;
class ArrayTypeSymbol;
class ASTNode;
class AttributeName;
class AttributeRange;
class AttributeSymbol;
class BinaryExpr;
class CharacterLiteralName;
class Choice;
class ComponentAssociation;
class ComponentDeclaration;
class ComponentList;
class ComponentSymbol;
class Constraint;
class Decl;
class DerivedTypeSpec;
class DerivedTypeSymbol;
class DiscreteRange;
class DiscriminantAssociation;
class DiscriminantConstraint;
class DiscriminantSpecification;
class DiscriminantSymbol;
class EnumerationTypeSpec;
class EnumLiteralSymbol;
class EnumTypeSymbol;
class Expr;
class ExprChoice;
class IncompleteTypeSymbol;
class IndexConstraint;
class IndexedName;
class IntegerTypeSymbol;
class IntLiteralExpr;
class Name;
class NameChoice;
class NameExpr;
class NullLiteralExpr;
class NumberDeclaration;
class NumericTypeSpec;
class ObjectDeclaration;
class ObjectSymbol;
class OthersChoice;
class QualExprAllocatorExpr;
class QualifiedExpr;
class Range;
class RangeChoice;
class RangeConstraint;
class RangeExpr;
class RealConstraint;
class RealLiteralExpr;
class RealTypeSymbol;
class RecordSpecification;
class RecordTypeSymbol;
class SelectedName;
class SimpleName;
class SliceName;
class Stmt;
class StringLiteralExpr;
class SubtypeIndication;
class SubtypeIndicationAllocatorExpr;
class SubtypeRange;
class SubtypeSymbol;
class Symbol;
class SymbolVisitor;
class TypeConversionExpr;
class TypeDecl;
class TypeSpec;
class TypeSymbol;
class UnaryExpr;
class UnboundedRange;
class Variant;
class VariantPart;
class AttributeConstraint;



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
using NumberDeclarationPtr = std::unique_ptr<NumberDeclaration>;
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
using ComponentSymbolPtr = std::unique_ptr<ComponentSymbol>;
using AttributeConstraintPtr = std::unique_ptr<AttributeConstraint>;
using RecordTypeSymbolPtr = std::unique_ptr<RecordTypeSymbol>;



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



//
// -- Include the other headers
//    -------------------------
#include "options.hh"
#include "tstream.hh"
#include "diag.hh"
#include "visitors.hh"
#include "symbol.hh"
#include "scope.hh"
#include "scope-manager.hh"
#include "parser.hh"
#include "ast.hh"




//
// -- some global variables
//    ---------------------
extern std::string strVal;
extern int column;
extern TokenStream *tokens;


