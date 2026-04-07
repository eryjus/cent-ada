//===================================================================================================================
// symbols2.cc -- This defines the tests against the symbol pretty output
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "symbols2.hh"



//
// == Test the output of printing the symbol table
//    ============================================




void TestOutput::TestSymbol(std::string expected, SourceLoc_t l, std::string n, SymbolTable::SymbolKind k, std::string t, int lvl)
{
    // -- given
    SymbolTable::Reset();
    std::ostringstream actual;

    // -- when
    while (lvl) { SymbolTable::Push("test"); --lvl; }
    Symbol *sym = SymbolTable::Declare(l, n, k, t);
    SymbolTable::Print(actual, false);

    // -- then
    EXPECT_EQ(expected, actual.str());
}

