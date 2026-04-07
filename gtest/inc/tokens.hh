//===================================================================================================================
// tokens.hh -- This defines tests against the token stream
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial
//===================================================================================================================



#include "ada.hh"
#include <gtest/gtest.h>



//
// -- Test case for testing all the stream
//    ------------------------------------
class TokTest : public testing::Test {
protected:
    TokTest(void) {}

    void TearDown() override {
        // Code to run after each test (e.g., resource release)
        delete TokenStream::singleton;
        TokenStream::singleton = nullptr;
    }


    //
    // -- Test a basic symbol match
    //    -------------------------
    void TestSymbol(std::string code, TokenType exp);


    //
    // -- Test an identifier match (with lexeme matching)
    //    -----------------------------------------------
    void TestIdent(std::string code);


    //
    // -- Test an universal integer (with lexeme matching)
    //    ------------------------------------------------
    void TestUInt(std::string code);


    //
    // -- Test an universal real (with lexeme matching)
    //    ---------------------------------------------
    void TestUReal(std::string code);


    //
    // -- Test astring (with lexeme matching)
    //    -----------------------------------
    void TestString(std::string code, std::string exp);


    //
    // -- Test a character (with lexeme matching)
    //    ---------------------------------------
    void TestChar(std::string code, char exp);


    //
    // -- Test an error condition with the proper message
    //    -----------------------------------------------
    void TestError(std::string code, DiagID did, ArgList expErr, bool chkEOF = true);


    //
    // -- Test a list of tokens
    //    ---------------------
    void TestTokenStream(std::string code, std::vector<TokenType> expected);
};


