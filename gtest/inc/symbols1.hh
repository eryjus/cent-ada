//===================================================================================================================
// symbols1.hh -- This defined the tests against the symbols
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "ada.hh"
#include <gtest/gtest.h>



//
// == Test the foundation of the Symbol Table functionality
//    =====================================================


//
// -- Test Suite for testing the symbol tables
//    ----------------------------------------
class TestSyms : public testing::Test {
protected:
    TestSyms(void) {}


    SymbolTable::Symbol *GlobalTest(SymbolTable &table, std::string n) {
        return table.GlobalLookup(n);
    }

    SymbolTable::Symbol *LocalTest(SymbolTable &table, std::string n) {
        return table.LocalLookup(n);
    }


    //
    // -- Test a standard symbol in the symbol table
    //    ------------------------------------------
    void TestStandardSymbol(std::string n, SymbolTable::SymbolKind k);


    //
    // -- Test PUSH/POP of scopes
    //    -----------------------
    void TestPushPop(std::string n);

    //
    // -- Test Rollback of symbols
    //    ------------------------
    void TestRollbackSyms(std::string n);


    //
    // -- Test Rollback of scopes
    //    -----------------------
    void TestRollbackScope(std::string n);


    //
    // -- Test Commit of symbols
    //    ----------------------
    void TestCommitSyms(std::string n);


    //
    // -- Test Commit of scopes
    //    ---------------------
    void TestCommitScope(std::string n);
};

