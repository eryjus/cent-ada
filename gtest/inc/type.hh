//===================================================================================================================
// decl-tests.cc -- This file enumerates the raw tests for declarations (used in several places)
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
// -- Test case for testing declarations
//    ----------------------------------
class DeclTest : public testing::TestWithParam<int> {
protected:
    DeclTest(void) : symTab(SymbolTable::Get()) {}


protected:
    SymbolTable &symTab;


    void SetUp() override {
        // Code here runs before EACH test
        symTab.Reset();
    }

    void TearDown() override {
        // Code to run after each test (e.g., resource release)
    }
};


