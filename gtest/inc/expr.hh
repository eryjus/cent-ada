//===================================================================================================================
// expr.hh -- This file is used to perform the basic declaration/expressions
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-06  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================


#include "ada.hh"
#include <gtest/gtest.h>


//
// -- Test case for testing expressions
//    ----------------------------------
class ExprTest : public testing::TestWithParam<int> {
protected:
    ExprTest(void) : symTab(SymbolTable::Get()) {}
    ~ExprTest() { delete TokenStream::singleton; TokenStream::singleton = nullptr; }


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


