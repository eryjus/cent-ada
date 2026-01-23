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
class AccessTypeSymbol;
class AggregateExpr;
class AllocatorExpr;
class ArrayTypeSymbol;
class ASTNode;
class AttributeName;
class AttributeRange;
class AttributeSymbol;
class BinaryExpr;
class CharacterLiteralName;
class Choice;
class ComponentAssociation;
class ComponentSymbol;
class Decl;
class DerivedTypeSymbol;
class DiscreteRange;
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
class RealLiteralExpr;
class RealTypeSymbol;
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
class ArrayTypeSpec;
class AccessTypeSpec;
class DerivedTypeSpec;
class RealConstraint;
class Constraint;


using NodePtr = std::unique_ptr<ASTNode>;
using DeclPtr = std::unique_ptr<Decl>;
using ExprPtr = std::unique_ptr<Expr>;
using NamePtr = std::unique_ptr<Name>;
using NumberDeclarationPtr = std::unique_ptr<NumberDeclaration>;
using ObjectDeclarationPtr = std::unique_ptr<ObjectDeclaration>;
using StmtPtr = std::unique_ptr<Stmt>;
using SubtypeIndicationPtr = std::unique_ptr<SubtypeIndication>;
using TypeDeclPtr = std::unique_ptr<TypeDecl>;
using TypeSpecPtr = std::unique_ptr<TypeSpec>;
using EnumerationTypeSpecPtr = std::unique_ptr<EnumerationTypeSpec>;
using RangeConstraintPtr = std::unique_ptr<RangeConstraint>;
using DiscreteRangePtr = std::unique_ptr<DiscreteRange>;
using RangePtr = std::unique_ptr<Range>;
using NumericTypeSpecPtr = std::unique_ptr<NumericTypeSpec>;
using IndexConstraintPtr = std::unique_ptr<IndexConstraint>;
using SubtypeRangePtr = std::unique_ptr<SubtypeRange>;
using CharacterLiteralNamePtr = std::unique_ptr<CharacterLiteralName>;
using SimpleNamePtr = std::unique_ptr<SimpleName>;
using IndexedNamePtr = std::unique_ptr<IndexedName>;
using SliceNamePtr = std::unique_ptr<SliceName>;
using SelectedNamePtr = std::unique_ptr<SelectedName>;
using AttributeNamePtr = std::unique_ptr<AttributeName>;
using NullLiteralExprPtr = std::unique_ptr<NullLiteralExpr>;
using IntLiteralExprPtr = std::unique_ptr<IntLiteralExpr>;
using RealLiteralExprPtr = std::unique_ptr<RealLiteralExpr>;
using StringLiteralExprPtr = std::unique_ptr<StringLiteralExpr>;
using NameExprPtr = std::unique_ptr<NameExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;
using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using RangeExprPtr = std::unique_ptr<RangeExpr>;
using ChoicePtr = std::unique_ptr<Choice>;
using OthersChoicePtr = std::unique_ptr<OthersChoice>;
using RangeChoicePtr = std::unique_ptr<RangeChoice>;
using NameChoicePtr = std::unique_ptr<NameChoice>;
using ExprChoicePtr = std::unique_ptr<ExprChoice>;
using ComponentAssociationPtr = std::unique_ptr<ComponentAssociation>;
using AggregateExprPtr = std::unique_ptr<AggregateExpr>;
using QualifiedExprPtr = std::unique_ptr<QualifiedExpr>;
using TypeConversionExprPtr = std::unique_ptr<TypeConversionExpr>;
using QualExprAllocatorExprPtr = std::unique_ptr<QualExprAllocatorExpr>;
using SubtypeIndicationAllocatorExprPtr = std::unique_ptr<SubtypeIndicationAllocatorExpr>;
using AllocatorExprPtr = std::unique_ptr<AllocatorExpr>;
using UnboundedRangePtr = std::unique_ptr<UnboundedRange>;
using ArrayTypeSpecPtr = std::unique_ptr<ArrayTypeSpec>;
using AccessTypeSpecPtr = std::unique_ptr<AccessTypeSpec>;
using DerivedTypeSpecPtr = std::unique_ptr<DerivedTypeSpec>;
using RealConstraintPtr = std::unique_ptr<RealConstraint>;
using ConstraintPtr = std::unique_ptr<Constraint>;



using IdList = std::vector<struct Id>;
using IdListPtr = std::unique_ptr<IdList>;
using ExprList = std::vector<ExprPtr>;
using ExprListPtr = std::unique_ptr<ExprList>;
using NameList = std::vector<NamePtr>;
using NameListPtr = std::unique_ptr<NameList>;
using ChoiceList = std::vector<ChoicePtr>;
using ChoiceListPtr = std::unique_ptr<ChoiceList>;
using ComponentAssociationList = std::vector<ComponentAssociationPtr>;
using ComponentAssociationListPtr = std::unique_ptr<ComponentAssociationList>;
using DiscreteRangeList = std::vector<DiscreteRangePtr>;
using DiscreteRangeListPtr = std::unique_ptr<DiscreteRangeList>;




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


