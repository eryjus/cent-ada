//===================================================================================================================
// symbols2.hh -- This defined the tests against the symbol pretty output
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
// == Test the output of printing the symbol table
//    ============================================



//
// -- This class will test the formatted output for each kind of symbol
//    -----------------------------------------------------------------
class TestOutput : public testing::Test {
protected:
    TestOutput(void) {}


    void TestSymbol(std::string expected, SourceLoc_t l, std::string n, SymbolTable::SymbolKind k, std::string t = "", int lvl = 0);
};

