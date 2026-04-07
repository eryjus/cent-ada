//===================================================================================================================
// tst-type.cc -- This google test executes tests against basic type declarations
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================


#include "decl-tests.hh"
#include "type.hh"


//
// -- Test the parsing of the types
//    -----------------------------
TEST_P(DeclTest, TestDeclarations)
{
    extern void ScanString(const std::string &s);

    // -- given
    int iter = GetParam();
    TokenStream &tokens = TokenStream::TestFactory(DeclTestCode::code[iter]);
    ScanString(DeclTestCode::code[iter]);
    tokens.Reset(0);
    Parser parser(tokens);

    // -- when
    int pos = tokens.Location();
    while (tokens.Current() != TokenType::YYEOF) {
        // -- then
        EXPECT_TRUE(parser.ParseBasicDeclaration());
        ASSERT_NE(pos, tokens.Location());
        pos = tokens.Location();
    }

    EXPECT_EQ(diags.Errors(), 0);
    EXPECT_TRUE(tokens.Location());
}



INSTANTIATE_TEST_SUITE_P(Decl, DeclTest, testing::Range(DeclTestCode::DeclTest001, DeclTestCode::Last)); //Last

