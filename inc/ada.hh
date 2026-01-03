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


class ASTNode;
class SymbolVisitor;
class Symbol;
class TypeSymbol;
class EnumTypeSymbol;
class RecordTypeSymbol;
class DerivedTypeSymbol;
class AccessTypeSymbol;
class IntegerTypeSymbol;
class RealTypeSymbol;
class ArrayTypeSymbol;
class SubtypeSymbol;
class EnumLiteralSymbol;
class DiscriminantSymbol;
class AttributeSymbol;
class ObjectSymbol;
class ComponentSymbol;


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



//
// -- some global variables
//    ---------------------
extern std::string strVal;
extern int column;
extern TokenStream *tokens;


