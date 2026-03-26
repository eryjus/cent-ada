//=================================================================================================================
//  sym-tab.hh -- This header defines the interfaces for the symbol table and its scope manager
//
//        Copyright (c)  2026-2026 -- Adam Clark; See LICENSE.md
//
//  This header defines a symbol, which will be a data payload (struct), a stack of symbols as a scope, and
//  a stack of scopes as the entire symbol table.
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Mar-25  Initial   0.0.0   ADCL  Initial version, replacing scope-manager.hh, scope.hh, and symbol.hh
//
//=================================================================================================================


#pragma once

#include <string>
#include <vector>
#include <memory>


class SymbolTable {
public:
    //
    // -- The list of types of symbols we need to track
    //    ---------------------------------------------
    enum class SymbolKind {
        Any,
        Object,
        Type,
        Subprogram,
        EnumLiteral,
        Component,
        Package,
        Label,
        Discriminant,
        Attribute,
        Pragma,
        IncompleteType,
        Deleted,
        UndefinedLabel,
        LoopName,
        BlockName,
    };



    //
    // -- An actual Symbol in the symbol table
    //    ------------------------------------
    struct Symbol {
        std::string symName;
        SymbolKind kind;
        SourceLoc_t loc;
        std::string typeName;
    };



    //
    // -- A scope of defined symbols
    //    --------------------------
    struct Scope {
        Scope *parent;
        std::string name;
        std::vector<std::unique_ptr<Symbol>> stack;
    };



    //
    // -- The current scope
    //    -----------------
    static Scope *current;



    //
    // -- Define the APIs for the symbol table
    //    ------------------------------------
public:
    static SymbolTable &Get(void);
    static Scope *Push(std::string name);
    static void Pop(void);
    static bool IsOverloaded(std::string n);
    static Symbol *Declare(SourceLoc_t l, std::string n, SymbolKind k, std::string t = "");
    static Symbol *LocalLookup(std::string n, SymbolKind k = SymbolKind::Any, std::string t = "");
    static Symbol *GlobalLookup(std::string n, SymbolKind k = SymbolKind::Any, std::string t = "");


private:
    //
    // -- members
    //    -------
    static SymbolTable *symTab;
    static std::vector<std::unique_ptr<Scope>> table;



    //
    // -- Constructor
    //    -----------
    SymbolTable(void);
};


