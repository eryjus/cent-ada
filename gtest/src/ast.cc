//===================================================================================================================
// ast.cc -- This google test executes tests against the AST contents
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
#include <gmock/gmock.h>



//
// -- This is the String Library for the declarations test strings
//    ------------------------------------------------------------
class DeclStringLib {
private:
//    static const std::string declTests[];

public:
//    static const std::string &operator[](DeclarationTests d) { return declTests[(int)d]; }
};
DeclStringLib strings;



//
// -- Test Suite for testing the ast
//    ------------------------------
class TestAst : public testing::Test {
protected:
    TestAst(void) {}



    void TearDown() override {
        // Code to run after each test (e.g., resource release)
        delete TokenStream::singleton;
        TokenStream::singleton = nullptr;
    }



    //
    // -- Test the AST resulting from a list of declarations
    //    --------------------------------------------------
    void TestDecl(std::string code, std::string expected) {
        DeclListPtr list = std::make_unique<DeclList>();
        DeclPtr decl = nullptr;
        std::string actual;
        TokenStream tokens = TokenStream::TestFactory(code);
        Parser parser(tokens);
        std::ostringstream os;

        while ((decl = parser.ParseBasicDeclaration()) != nullptr) {
            list->push_back(std::move(decl));
        }

        ASTDumper dumper;
        for (auto &item : *list) {
            item->Accept(dumper);
        }

        actual = dumper.Get();

        EXPECT_EQ(actual, expected);
    }
};




TEST_F(TestAst, DeclTest001) {
//    std::string code = strings[DeclarationTests::DeclTest001];
    std::string expected = R"(
        (ObjectDeclaration
            (names: "count" "sum")
            (isConstant: false)
            (typeSpec

            )
            (initializer nullptr)
        )
    )";

//    TestDecl(code, expected);
}

