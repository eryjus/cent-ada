//===================================================================================================================
// symbols3.hh -- This defined the tests against the symbol sequencing
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
// -- This class will test the sequence of the symbol in the symbol table
//    -------------------------------------------------------------------
class TestSequence : public testing::Test {
protected:
    TestSequence(void) {}

    void TearDown() override {
        // Code to run after each test (e.g., resource release)
        delete TokenStream::singleton;
        TokenStream::singleton = nullptr;
    }
};





