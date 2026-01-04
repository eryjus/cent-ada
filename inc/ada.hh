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



//
// -- Here are quite a few forward declarations
//    -----------------------------------------
class AccessTypeSymbol;
class ArrayTypeSymbol;
class ASTNode;
class AttributeSymbol;
class ComponentSymbol;
class Decl;
class DerivedTypeSymbol;
class DiscriminantSymbol;
class EnumerationTypeSpec;
class EnumLiteralSymbol;
class EnumTypeSymbol;
class Expr;
class IncompleteTypeSymbol;
class IntegerTypeSymbol;
class Name;
class NumberDeclaration;
class ObjectDeclaration;
class ObjectSymbol;
class RealTypeSymbol;
class RecordTypeSymbol;
class Stmt;
class SubtypeIndication;
class SubtypeSymbol;
class Symbol;
class SymbolVisitor;
class TypeDecl;
class TypeSpec;
class TypeSymbol;
class RangeConstraint;
class DiscreteRange;
class IntegerTypeSpec;
class Range;
class SubtypeRange;


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

using IdList = std::vector<struct Id>;
using IdListPtr = std::unique_ptr<IdList>;




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


