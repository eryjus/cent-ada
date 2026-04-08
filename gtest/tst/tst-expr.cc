//===================================================================================================================
// tst-exor.cc -- This google test executes tests against basic declarations/expressions
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================


#include "expr-tests.hh"
#include "expr.hh"


//
// -- Test the parsing of the exprs
//    -----------------------------
TEST_P(ExprTest, TestExpressions)
{
    extern void ScanString(const std::string &s);

    // -- given
    int iter = GetParam();
    TokenStream &tokens = TokenStream::TestFactory(ExprTestCode::code[iter]);
    ScanString(ExprTestCode::code[iter]);
    tokens.Reset(0);
    Parser parser(tokens);

    // -- when
    int pos = tokens.Location();
    while (tokens.Current() != TokenType::YYEOF) {
        // -- then
        if (!parser.ParseBasicDeclaration()) break;
        ASSERT_NE(pos, tokens.Location());
        pos = tokens.Location();
    }

    pos = tokens.Location();
    while (tokens.Current() != TokenType::YYEOF) {
        // -- then
        ASSERT_TRUE(parser.ParseExpression());
        ASSERT_NE(pos, tokens.Location());
        pos = tokens.Location();
    }

    EXPECT_EQ(diags.Errors(), 0);
    EXPECT_TRUE(tokens.Current() == TokenType::YYEOF);
}



INSTANTIATE_TEST_SUITE_P(Expr, ExprTest, testing::Range(ExprTestCode::ExprTest001, ExprTestCode::Last)); //Last

