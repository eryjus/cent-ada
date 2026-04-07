//===================================================================================================================
// lexer.cc -- This google test executes tests against the lexer
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-04  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "lexer.hh"



//
// -- Test a basic symbol match
//    -------------------------
void LexTest::TestSymbol(std::string code, TokenType exp)
{
    // -- given
    ScanString(code);

    // -- when
    TokenType tok = yylex();

    // -- then
    EXPECT_EQ(tok, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}


//
// -- Test an identifier match (with lexeme matching)
//    -----------------------------------------------
void LexTest::TestIdent(std::string code)
{
    // -- given
    ScanString(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = yylex();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<IdentifierLexeme>(yylval));
    ASSERT_NO_THROW(lexeme = std::get<IdentifierLexeme>(yylval).name);
    EXPECT_EQ(tok, TokenType::TOK_IDENTIFIER);
    EXPECT_EQ(lexeme, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}



//
// -- Test an universal integer (with lexeme matching)
//    ------------------------------------------------
void LexTest::TestUInt(std::string code)
{
    // -- given
    ScanString(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = yylex();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<IntLiteral>(yylval));
    ASSERT_NO_THROW(lexeme = std::get<IntLiteral>(yylval).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_UNIVERSAL_INT_LITERAL);
    EXPECT_EQ(lexeme, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}



//
// -- Test an universal real (with lexeme matching)
//    ---------------------------------------------
void LexTest::TestUReal(std::string code)
{
    // -- given
    ScanString(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = yylex();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<RealLiteral>(yylval));
    ASSERT_NO_THROW(lexeme = std::get<RealLiteral>(yylval).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_UNIVERSAL_REAL_LITERAL);
    EXPECT_EQ(lexeme, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}



//
// -- Test astring (with lexeme matching)
//    -----------------------------------
void LexTest::TestString(std::string code, std::string exp)
{
    // -- given
    ScanString(code);

    // -- when
    TokenType tok = yylex();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<StringLiteral>(yylval));
    ASSERT_NO_THROW(lexeme = std::get<StringLiteral>(yylval).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_STRING_LITERAL);
    EXPECT_EQ(lexeme, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}



//
// -- Test a character (with lexeme matching)
//    ---------------------------------------
void LexTest::TestChar(std::string code, char exp)
{
    // -- given
    ScanString(code);

    // -- when
    TokenType tok = yylex();

    // -- then
    int value;

    ASSERT_TRUE(std::holds_alternative<CharLiteral>(yylval));
    ASSERT_NO_THROW(value = std::get<CharLiteral>(yylval).value);
    EXPECT_EQ(tok, TokenType::TOK_CHARACTER_LITERAL);
    EXPECT_EQ(value, exp);
    EXPECT_EQ(yylex(), TokenType::YYEOF);
}



//
// -- Test an error condition with the proper message
//    -----------------------------------------------
void LexTest::TestError(std::string code, DiagID did, ArgList expErr, bool chkEOF)
{
    // -- given
    ScanString(code);

    // -- when
    TokenType tok = yylex();

    // -- then
    ScannerError err;

    ASSERT_TRUE(std::holds_alternative<ScannerError>(yylval));
    ASSERT_NO_THROW(err = std::get<ScannerError>(yylval));
    EXPECT_EQ(tok, TokenType::TOK_ERROR);
    EXPECT_EQ(err.msg, did);
    EXPECT_EQ(err.args.size(), expErr.size());
    EXPECT_EQ(err.args, expErr);
    if (chkEOF) EXPECT_EQ(yylex(), TokenType::YYEOF);
}



