//===================================================================================================================
// lexer.hh -- This google test executes tests against the lexer
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-04  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "ada.hh"
#include <gtest/gtest.h>



extern TokenType yylex(void);
extern FILE *yyin;
extern YYSTYPE yylval;
extern int yylineno;
extern void ScanString(const std::string &s);


//
// -- Test case for testing all the proper tokens
//    -------------------------------------------
class LexTest : public testing::Test {
protected:
    //
    // -- Construct the testing environment
    //    ---------------------------------
    LexTest(void) {
        yyin = stdin;
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
};



