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
    //
    // -- Some friends for testing
    //    ------------------------
    friend class TestOutput;
    friend class TestSyms;
    friend class TestSequence;
    friend class DeclTest;
    friend class ExprTest;


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

        std::string to_string(void) const;
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
    // -- This is a structure for checkpointing, commit, and rollback
    //    -----------------------------------------------------------
    class Checkpoint {
    private:
        Scope *curScope;
        unsigned long scopecount;
        unsigned long currentcount;
        bool committed;

    public:
        Checkpoint(void) :
                curScope(current),
                scopecount(table.size()),
                currentcount(current->stack.size()),
                committed(false) {}

        ~Checkpoint() { Rollback(); }

    public:
        void Commit(void) { committed = true; }
        void Rollback(void);
    };



    //
    // -- This is the current scope
    //    -------------------------
public:
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
    static void Print(std::ostream &os = std::cout, bool printHeader = true);


protected:
    // -- for testing
    static std::string CurrentScope(void) { return current->name; }
    static void Reset(void) { table.resize(1); current = table[0].get(); Push("GLOBAL"); }
    static std::vector<std::tuple<std::string, std::string, SymbolTable::SymbolKind, std::string>>GetAllSymbols(void);


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



//                       scope        symbol       kind                     type
using Tuple = std::tuple<std::string, std::string, SymbolTable::SymbolKind, std::string>;
using SymSeq = std::vector<Tuple>;




using Symbol = SymbolTable::Symbol;
extern SymbolTable &symTab;




