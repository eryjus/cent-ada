//===================================================================================================================
// tokens.cc -- This source implements the token tests
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial
//===================================================================================================================



#include "tokens.hh"



//
// -- Test a basic symbol match
//    -------------------------
void TokTest::TestSymbol(std::string code, TokenType exp)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);

    // -- when
    TokenType tok = tokens.Current();
    tokens.Advance();

    // -- then
    EXPECT_EQ(tok, exp);
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}


//
// -- Test an identifier match (with lexeme matching)
//    -----------------------------------------------
void TokTest::TestIdent(std::string code)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<IdentifierLexeme>(tokens.Payload()));
    ASSERT_NO_THROW(lexeme = std::get<IdentifierLexeme>(tokens.Payload()).name);
    EXPECT_EQ(tok, TokenType::TOK_IDENTIFIER);
    EXPECT_EQ(lexeme, exp);

    tokens.Advance();
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}



//
// -- Test an universal integer (with lexeme matching)
//    ------------------------------------------------
void TokTest::TestUInt(std::string code)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<IntLiteral>(tokens.Payload()));
    ASSERT_NO_THROW(lexeme = std::get<IntLiteral>(tokens.Payload()).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_UNIVERSAL_INT_LITERAL);
    EXPECT_EQ(lexeme, exp);

    tokens.Advance();
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}



//
// -- Test an universal real (with lexeme matching)
//    ---------------------------------------------
void TokTest::TestUReal(std::string code)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);
    std::string exp = code;
    std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
    exp = exp.substr(exp.find_first_not_of(" "));
    exp = exp.substr(0, exp.find_last_not_of(" ") + 1);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<RealLiteral>(tokens.Payload()));
    ASSERT_NO_THROW(lexeme = std::get<RealLiteral>(tokens.Payload()).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_UNIVERSAL_REAL_LITERAL);
    EXPECT_EQ(lexeme, exp);

    tokens.Advance();
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}



//
// -- Test astring (with lexeme matching)
//    -----------------------------------
void TokTest::TestString(std::string code, std::string exp)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    std::string lexeme;

    ASSERT_TRUE(std::holds_alternative<StringLiteral>(tokens.Payload()));
    ASSERT_NO_THROW(lexeme = std::get<StringLiteral>(tokens.Payload()).lexeme);
    EXPECT_EQ(tok, TokenType::TOK_STRING_LITERAL);
    EXPECT_EQ(lexeme, exp);

    tokens.Advance();
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}



//
// -- Test a character (with lexeme matching)
//    ---------------------------------------
void TokTest::TestChar(std::string code, char exp)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    int value;

    ASSERT_TRUE(std::holds_alternative<CharLiteral>(tokens.Payload()));
    ASSERT_NO_THROW(value = std::get<CharLiteral>(tokens.Payload()).value);
    EXPECT_EQ(tok, TokenType::TOK_CHARACTER_LITERAL);
    EXPECT_EQ(value, exp);

    tokens.Advance();
    EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
}



//
// -- Test an error condition with the proper message
//    -----------------------------------------------
void TokTest::TestError(std::string code, DiagID did, ArgList expErr, bool chkEOF)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);

    // -- when
    TokenType tok = tokens.Current();

    // -- then
    ScannerError err;

    ASSERT_TRUE(std::holds_alternative<ScannerError>(tokens.Payload()));
    ASSERT_NO_THROW(err = std::get<ScannerError>(tokens.Payload()));
    EXPECT_EQ(tok, TokenType::TOK_ERROR);
    EXPECT_EQ(err.msg, did);
    EXPECT_EQ(err.args.size(), expErr.size());
    EXPECT_EQ(err.args, expErr);
    if (chkEOF) {
        tokens.Advance();
        EXPECT_EQ(tokens.Current(), TokenType::YYEOF);
    }
}



//
// -- Test a list of tokens
//    ---------------------
void TokTest::TestTokenStream(std::string code, std::vector<TokenType> expected)
{
    // -- given
    TokenStream &tokens = TokenStream::TestFactory(code);
    int idx = 0;

    // -- Test the stream
    while (tokens.Current() != TokenType::YYEOF) {
        ASSERT_LT(idx, expected.size());
        EXPECT_EQ(tokens.Current(), expected[idx]);
        tokens.Advance();
        idx ++;
    }

    // -- check that we got all the tokens expected
    EXPECT_EQ(idx, expected.size());
    tokens.Reset(0);
    idx = 0;


    // -- Test the stream again!
    while (tokens.Current() != TokenType::YYEOF) {
        ASSERT_LT(idx, expected.size());
        EXPECT_EQ(tokens.Current(), expected[idx]);
        tokens.Advance();
        idx ++;
    }
}



