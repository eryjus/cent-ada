//===================================================================================================================
// tokens.cc -- This google test executes tests against the token stream
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Mar-31  Initial  v0.0.0   Initial Google Tests
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
    void TestSymbol(std::string code, TokenType exp) {
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
    void TestIdent(std::string code) {
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
    void TestUInt(std::string code) {
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
    void TestUReal(std::string code) {
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
    void TestString(std::string code, std::string exp) {
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
    void TestChar(std::string code, char exp) {
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
    void TestError(std::string code, DiagID did, ArgList expErr, bool chkEOF = true) {
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
    void TestTokenStream(std::string code, std::vector<TokenType> expected)
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
};



//
// -- Test an empty stream of tokens
//    ------------------------------
TEST_F(TokTest, TestEmpty) {
    // -- given
    TokenStream &tokens = TokenStream::TestFactory("");

    // -- when

    // -- then
    ASSERT_TRUE(tokens.Current() == TokenType::YYEOF);
}



//
// -- Test reading past the end of the stream
//    ---------------------------------------
TEST_F(TokTest, TestEmpty2) {
    // -- given
    TokenStream &tokens = TokenStream::TestFactory("");
    std::cout << "Constructed\n";

    // -- when
    tokens.Advance();
    std::cout << "Advanced\n";
    tokens.Current();
    std::cout << "Current\n";

    // -- then
    ASSERT_EQ(tokens.Current(), TokenType::YYEOF);
    std::cout << "Asserted\n";
}



//
// -- Test peeking past the end of the stream
//    ---------------------------------------
TEST_F(TokTest, TestPeek) {
    // -- given
    TokenStream &tokens = TokenStream::TestFactory("");

    // -- when
    TokenType tok = tokens.Peek();

    // -- then
    ASSERT_TRUE(tok == TokenType::YYEOF);
}



//
// -- Test peeking way past the end of the stream
//    -------------------------------------------
TEST_F(TokTest, TestPeek2) {
    // -- given
    TokenStream &tokens = TokenStream::TestFactory("");

    // -- when
    TokenType tok = tokens.Peek(1000);

    // -- then
    ASSERT_TRUE(tok == TokenType::YYEOF);
}



//
// == The individual tests
//    ====================


//
// -- Single Character Symbols
//    ------------------------
TEST_F(TokTest, ampersand_sp) { TestSymbol(" & ", TokenType::TOK_AMPERSAND); }
TEST_F(TokTest, leftparen_sp) { TestSymbol(" ( ", TokenType::TOK_LEFT_PARENTHESIS); }
TEST_F(TokTest, rightparen_sp) { TestSymbol(" ) ", TokenType::TOK_RIGHT_PARENTHESIS); }
TEST_F(TokTest, star_sp) { TestSymbol(" * ", TokenType::TOK_STAR); }
TEST_F(TokTest, plus_sp) { TestSymbol(" + ", TokenType::TOK_PLUS); }
TEST_F(TokTest, comma_sp) { TestSymbol(" , ", TokenType::TOK_COMMA); }
TEST_F(TokTest, hyphen_sp) { TestSymbol(" - ", TokenType::TOK_HYPHEN); }
TEST_F(TokTest, dot_sp) { TestSymbol(" . ", TokenType::TOK_DOT); }
TEST_F(TokTest, slash_sp) { TestSymbol(" / ", TokenType::TOK_SLASH); }
TEST_F(TokTest, colon_sp) { TestSymbol(" : ", TokenType::TOK_COLON); }
TEST_F(TokTest, semicolon_sp) { TestSymbol(" ; ", TokenType::TOK_SEMICOLON); }
TEST_F(TokTest, less_than_sp) { TestSymbol(" < ", TokenType::TOK_LESS_THAN); }
TEST_F(TokTest, equal_sp) { TestSymbol(" = ", TokenType::TOK_EQUAL); }
TEST_F(TokTest, greater_than_sp) { TestSymbol(" > ", TokenType::TOK_GREATER_THAN); }
TEST_F(TokTest, vertical_bar_sp) { TestSymbol(" | ", TokenType::TOK_VERTICAL_BAR); }
TEST_F(TokTest, exclamation_mark_sp) { TestSymbol(" ! ", TokenType::TOK_EXCLAMATION_MARK); }
TEST_F(TokTest, dollar_sp) { TestSymbol(" $ ", TokenType::TOK_DOLLAR); }
TEST_F(TokTest, percent_sp) { TestSymbol(" % ", TokenType::TOK_PERCENT); }
TEST_F(TokTest, question_mark_sp) { TestSymbol(" ? ", TokenType::TOK_QUESTION_MARK); }
TEST_F(TokTest, commercial_at_sp) { TestSymbol(" @ ", TokenType::TOK_COMMERCIAL_AT); }
TEST_F(TokTest, left_square_bracket_sp) { TestSymbol(" [ ", TokenType::TOK_LEFT_SQUARE_BRACKET); }
TEST_F(TokTest, back_slash_sp) { TestSymbol(" \\ ", TokenType::TOK_BACK_SLASH); }
TEST_F(TokTest, right_square_bracket_sp) { TestSymbol(" ] ", TokenType::TOK_RIGHT_SQUARE_BRACKET); }
TEST_F(TokTest, circumflex_sp) { TestSymbol(" ^ ", TokenType::TOK_CIRCUMFLEX); }
TEST_F(TokTest, grave_accent_sp) { TestSymbol(" ` ", TokenType::TOK_GRAVE_ACCENT); }
TEST_F(TokTest, left_brace_sp) { TestSymbol(" { ", TokenType::TOK_LEFT_BRACE); }
TEST_F(TokTest, right_brace_sp) { TestSymbol(" } ", TokenType::TOK_RIGHT_BRACE); }
TEST_F(TokTest, tilde_sp) { TestSymbol(" ~ ", TokenType::TOK_TILDE); }

TEST_F(TokTest, ampersand) {TestSymbol("&", TokenType::TOK_AMPERSAND); }
TEST_F(TokTest, leftparen) { TestSymbol("(", TokenType::TOK_LEFT_PARENTHESIS); }
TEST_F(TokTest, rightparen) { TestSymbol(")", TokenType::TOK_RIGHT_PARENTHESIS); }
TEST_F(TokTest, star) { TestSymbol("*", TokenType::TOK_STAR); }
TEST_F(TokTest, plus) { TestSymbol("+", TokenType::TOK_PLUS); }
TEST_F(TokTest, comma) { TestSymbol(",", TokenType::TOK_COMMA); }
TEST_F(TokTest, hyphen) { TestSymbol("-", TokenType::TOK_HYPHEN); }
TEST_F(TokTest, dot) { TestSymbol(".", TokenType::TOK_DOT); }
TEST_F(TokTest, slash) { TestSymbol("/", TokenType::TOK_SLASH); }
TEST_F(TokTest, colon) { TestSymbol(":", TokenType::TOK_COLON); }
TEST_F(TokTest, semicolon) { TestSymbol(";", TokenType::TOK_SEMICOLON); }
TEST_F(TokTest, less_than) { TestSymbol("<", TokenType::TOK_LESS_THAN); }
TEST_F(TokTest, equal) { TestSymbol("=", TokenType::TOK_EQUAL); }
TEST_F(TokTest, greater_than) { TestSymbol(">", TokenType::TOK_GREATER_THAN); }
TEST_F(TokTest, vertical_bar) { TestSymbol("|", TokenType::TOK_VERTICAL_BAR); }
TEST_F(TokTest, exclamation_mark) { TestSymbol("!", TokenType::TOK_EXCLAMATION_MARK); }
TEST_F(TokTest, dollar) { TestSymbol("$", TokenType::TOK_DOLLAR); }
TEST_F(TokTest, percent) { TestSymbol("%", TokenType::TOK_PERCENT); }
TEST_F(TokTest, question_mark) { TestSymbol("?", TokenType::TOK_QUESTION_MARK); }
TEST_F(TokTest, commercial_at) { TestSymbol("@", TokenType::TOK_COMMERCIAL_AT); }
TEST_F(TokTest, left_square_bracket) { TestSymbol("[", TokenType::TOK_LEFT_SQUARE_BRACKET); }
TEST_F(TokTest, back_slash) { TestSymbol("\\", TokenType::TOK_BACK_SLASH); }
TEST_F(TokTest, right_square_bracket) { TestSymbol("]", TokenType::TOK_RIGHT_SQUARE_BRACKET); }
TEST_F(TokTest, circumflex) { TestSymbol("^", TokenType::TOK_CIRCUMFLEX); }
TEST_F(TokTest, grave_accent) { TestSymbol("`", TokenType::TOK_GRAVE_ACCENT); }
TEST_F(TokTest, left_brace) { TestSymbol("{", TokenType::TOK_LEFT_BRACE); }
TEST_F(TokTest, right_brace) { TestSymbol("}", TokenType::TOK_RIGHT_BRACE); }
TEST_F(TokTest, tilde) { TestSymbol("~", TokenType::TOK_TILDE); }


//
// -- Multi-Character Symbols
//    -----------------------
TEST_F(TokTest, arrow_sp) { TestSymbol(" => ", TokenType::TOK_ARROW); }
TEST_F(TokTest, double_dot_sp) { TestSymbol(" .. ", TokenType::TOK_DOUBLE_DOT); }
TEST_F(TokTest, double_star_sp) { TestSymbol(" ** ", TokenType::TOK_DOUBLE_STAR); }
TEST_F(TokTest, assignment_sp) { TestSymbol(" := ", TokenType::TOK_ASSIGNMENT); }
TEST_F(TokTest, inequality_sp) { TestSymbol(" /= ", TokenType::TOK_INEQUALITY); }
TEST_F(TokTest, greater_than_or_equal_sp) { TestSymbol(" >= ", TokenType::TOK_GREATER_THAN_OR_EQUAL); }
TEST_F(TokTest, less_than_or_equal_sp) { TestSymbol(" <= ", TokenType::TOK_LESS_THAN_OR_EQUAL); }
TEST_F(TokTest, left_label_bracket_sp) { TestSymbol(" << ", TokenType::TOK_LEFT_LABEL_BRACKET); }
TEST_F(TokTest, right_label_bracket_sp) { TestSymbol(" >> ", TokenType::TOK_RIGHT_LABEL_BRACKET); }
TEST_F(TokTest, box_sp) { TestSymbol(" <> ", TokenType::TOK_BOX); }

TEST_F(TokTest, arrow) { TestSymbol("=>", TokenType::TOK_ARROW); }
TEST_F(TokTest, double_dot) { TestSymbol("..", TokenType::TOK_DOUBLE_DOT); }
TEST_F(TokTest, double_star) { TestSymbol("**", TokenType::TOK_DOUBLE_STAR); }
TEST_F(TokTest, assignment) { TestSymbol(":=", TokenType::TOK_ASSIGNMENT); }
TEST_F(TokTest, inequality) { TestSymbol("/=", TokenType::TOK_INEQUALITY); }
TEST_F(TokTest, greater_than_or_equal) { TestSymbol(">=", TokenType::TOK_GREATER_THAN_OR_EQUAL); }
TEST_F(TokTest, less_than_or_equal) { TestSymbol("<=", TokenType::TOK_LESS_THAN_OR_EQUAL); }
TEST_F(TokTest, left_label_bracket) { TestSymbol("<<", TokenType::TOK_LEFT_LABEL_BRACKET); }
TEST_F(TokTest, right_label_bracket) { TestSymbol(">>", TokenType::TOK_RIGHT_LABEL_BRACKET); }
TEST_F(TokTest, box) { TestSymbol("<>", TokenType::TOK_BOX); }



//
// -- Keywords
//    --------
TEST_F(TokTest, k_abort_sp) { TestSymbol(" abort ", TokenType::TOK_ABORT); }
TEST_F(TokTest, k_abs_sp) { TestSymbol(" abs ", TokenType::TOK_ABS); }
TEST_F(TokTest, k_accept_sp) { TestSymbol(" accept ", TokenType::TOK_ACCEPT); }
TEST_F(TokTest, k_access_sp) { TestSymbol(" access ", TokenType::TOK_ACCESS); }
TEST_F(TokTest, k_all_sp) { TestSymbol(" all ", TokenType::TOK_ALL); }
TEST_F(TokTest, k_and_sp) { TestSymbol(" and ", TokenType::TOK_AND); }
TEST_F(TokTest, k_array_sp) { TestSymbol(" array ", TokenType::TOK_ARRAY); }
TEST_F(TokTest, k_at_sp) { TestSymbol(" at ", TokenType::TOK_AT); }
TEST_F(TokTest, k_begin_sp) { TestSymbol(" begin ", TokenType::TOK_BEGIN); }
TEST_F(TokTest, k_body_sp) { TestSymbol(" body ", TokenType::TOK_BODY); }
TEST_F(TokTest, k_case_sp) { TestSymbol(" case ", TokenType::TOK_CASE); }
TEST_F(TokTest, k_constant_sp) { TestSymbol(" constant ", TokenType::TOK_CONSTANT); }
TEST_F(TokTest, k_declare_sp) { TestSymbol(" declare ", TokenType::TOK_DECLARE); }
TEST_F(TokTest, k_delay_sp) { TestSymbol(" delay ", TokenType::TOK_DELAY); }
TEST_F(TokTest, k_delta_sp) { TestSymbol(" delta ", TokenType::TOK_DELTA); }
TEST_F(TokTest, k_digits_sp) { TestSymbol(" digits ", TokenType::TOK_DIGITS); }
TEST_F(TokTest, k_do_sp) { TestSymbol(" do ", TokenType::TOK_DO); }
TEST_F(TokTest, k_else_sp) { TestSymbol(" else ", TokenType::TOK_ELSE); }
TEST_F(TokTest, k_elsif_sp) { TestSymbol(" elsif ", TokenType::TOK_ELSIF); }
TEST_F(TokTest, k_end_sp) { TestSymbol(" end ", TokenType::TOK_END); }
TEST_F(TokTest, k_entry_sp) { TestSymbol(" entry ", TokenType::TOK_ENTRY); }
TEST_F(TokTest, k_exception_sp) { TestSymbol(" exception ", TokenType::TOK_EXCEPTION); }
TEST_F(TokTest, k_exit_sp) { TestSymbol(" exit ", TokenType::TOK_EXIT); }
TEST_F(TokTest, k_for_sp) { TestSymbol(" for ", TokenType::TOK_FOR); }
TEST_F(TokTest, k_function_sp) { TestSymbol(" function ", TokenType::TOK_FUNCTION); }
TEST_F(TokTest, k_generic_sp) { TestSymbol(" generic ", TokenType::TOK_GENERIC); }
TEST_F(TokTest, k_goto_sp) { TestSymbol(" goto ", TokenType::TOK_GOTO); }
TEST_F(TokTest, k_if_sp) { TestSymbol(" if ", TokenType::TOK_IF); }
TEST_F(TokTest, k_in_sp) { TestSymbol(" in ", TokenType::TOK_IN); }
TEST_F(TokTest, k_is_sp) { TestSymbol(" is ", TokenType::TOK_IS); }
TEST_F(TokTest, k_limited_sp) { TestSymbol(" limited ", TokenType::TOK_LIMITED); }
TEST_F(TokTest, k_loop_sp) { TestSymbol(" loop ", TokenType::TOK_LOOP); }
TEST_F(TokTest, k_mod_sp) { TestSymbol(" mod ", TokenType::TOK_MOD); }
TEST_F(TokTest, k_new_sp) { TestSymbol(" new ", TokenType::TOK_NEW); }
TEST_F(TokTest, k_not_sp) { TestSymbol(" not ", TokenType::TOK_NOT); }
TEST_F(TokTest, k_null_sp) { TestSymbol(" null ", TokenType::TOK_NULL); }
TEST_F(TokTest, k_of_sp) { TestSymbol(" of ", TokenType::TOK_OF); }
TEST_F(TokTest, k_or_sp) { TestSymbol(" or ", TokenType::TOK_OR); }
TEST_F(TokTest, k_others_sp) { TestSymbol(" others ", TokenType::TOK_OTHERS); }
TEST_F(TokTest, k_out_sp) { TestSymbol(" out ", TokenType::TOK_OUT); }
TEST_F(TokTest, k_package_sp) { TestSymbol(" package ", TokenType::TOK_PACKAGE); }
TEST_F(TokTest, k_pragma_sp) { TestSymbol(" pragma ", TokenType::TOK_PRAGMA); }
TEST_F(TokTest, k_private_sp) { TestSymbol(" private ", TokenType::TOK_PRIVATE); }
TEST_F(TokTest, k_procedure_sp) { TestSymbol(" procedure ", TokenType::TOK_PROCEDURE); }
TEST_F(TokTest, k_raise_sp) { TestSymbol(" raise ", TokenType::TOK_RAISE); }
TEST_F(TokTest, k_range_sp) { TestSymbol(" range ", TokenType::TOK_RANGE); }
TEST_F(TokTest, k_record_sp) { TestSymbol(" record ", TokenType::TOK_RECORD); }
TEST_F(TokTest, k_rem_sp) { TestSymbol(" rem ", TokenType::TOK_REM); }
TEST_F(TokTest, k_renames_sp) { TestSymbol(" renames ", TokenType::TOK_RENAMES); }
TEST_F(TokTest, k_return_sp) { TestSymbol(" return ", TokenType::TOK_RETURN); }
TEST_F(TokTest, k_reverse_sp) { TestSymbol(" reverse ", TokenType::TOK_REVERSE); }
TEST_F(TokTest, k_select_sp) { TestSymbol(" select ", TokenType::TOK_SELECT); }
TEST_F(TokTest, k_separate_sp) { TestSymbol(" separate ", TokenType::TOK_SEPARATE); }
TEST_F(TokTest, k_subtype_sp) { TestSymbol(" subtype ", TokenType::TOK_SUBTYPE); }
TEST_F(TokTest, k_task_sp) { TestSymbol(" task ", TokenType::TOK_TASK); }
TEST_F(TokTest, k_terminate_sp) { TestSymbol(" terminate ", TokenType::TOK_TERMINATE); }
TEST_F(TokTest, k_then_sp) { TestSymbol(" then ", TokenType::TOK_THEN); }
TEST_F(TokTest, k_type_sp) { TestSymbol(" type ", TokenType::TOK_TYPE); }
TEST_F(TokTest, k_use_sp) { TestSymbol(" use ", TokenType::TOK_USE); }
TEST_F(TokTest, k_when_sp) { TestSymbol(" when ", TokenType::TOK_WHEN); }
TEST_F(TokTest, k_while_sp) { TestSymbol(" while ", TokenType::TOK_WHILE); }
TEST_F(TokTest, k_with_sp) { TestSymbol(" with ", TokenType::TOK_WITH); }
TEST_F(TokTest, k_xor_sp) { TestSymbol(" xor ", TokenType::TOK_XOR); }

TEST_F(TokTest, k_abort) { TestSymbol("abort", TokenType::TOK_ABORT); }
TEST_F(TokTest, k_abs) { TestSymbol("abs", TokenType::TOK_ABS); }
TEST_F(TokTest, k_accept) { TestSymbol("accept", TokenType::TOK_ACCEPT); }
TEST_F(TokTest, k_access) { TestSymbol("access", TokenType::TOK_ACCESS); }
TEST_F(TokTest, k_all) { TestSymbol("all", TokenType::TOK_ALL); }
TEST_F(TokTest, k_and) { TestSymbol("and", TokenType::TOK_AND); }
TEST_F(TokTest, k_array) { TestSymbol("array", TokenType::TOK_ARRAY); }
TEST_F(TokTest, k_at) { TestSymbol("at", TokenType::TOK_AT); }
TEST_F(TokTest, k_begin) { TestSymbol("begin", TokenType::TOK_BEGIN); }
TEST_F(TokTest, k_body) { TestSymbol("body", TokenType::TOK_BODY); }
TEST_F(TokTest, k_case) { TestSymbol("case", TokenType::TOK_CASE); }
TEST_F(TokTest, k_constant) { TestSymbol("constant", TokenType::TOK_CONSTANT); }
TEST_F(TokTest, k_declare) { TestSymbol("declare", TokenType::TOK_DECLARE); }
TEST_F(TokTest, k_delay) { TestSymbol("delay", TokenType::TOK_DELAY); }
TEST_F(TokTest, k_delta) { TestSymbol("delta", TokenType::TOK_DELTA); }
TEST_F(TokTest, k_digits) { TestSymbol("digits", TokenType::TOK_DIGITS); }
TEST_F(TokTest, k_do) { TestSymbol("do", TokenType::TOK_DO); }
TEST_F(TokTest, k_else) { TestSymbol("else", TokenType::TOK_ELSE); }
TEST_F(TokTest, k_elsif) { TestSymbol("elsif", TokenType::TOK_ELSIF); }
TEST_F(TokTest, k_end) { TestSymbol("end", TokenType::TOK_END); }
TEST_F(TokTest, k_entry) { TestSymbol("entry", TokenType::TOK_ENTRY); }
TEST_F(TokTest, k_exception) { TestSymbol("exception", TokenType::TOK_EXCEPTION); }
TEST_F(TokTest, k_exit) { TestSymbol("exit", TokenType::TOK_EXIT); }
TEST_F(TokTest, k_for) { TestSymbol("for", TokenType::TOK_FOR); }
TEST_F(TokTest, k_function) { TestSymbol("function", TokenType::TOK_FUNCTION); }
TEST_F(TokTest, k_generic) { TestSymbol("generic", TokenType::TOK_GENERIC); }
TEST_F(TokTest, k_goto) { TestSymbol("goto", TokenType::TOK_GOTO); }
TEST_F(TokTest, k_if) { TestSymbol("if", TokenType::TOK_IF); }
TEST_F(TokTest, k_in) { TestSymbol("in", TokenType::TOK_IN); }
TEST_F(TokTest, k_is) { TestSymbol("is", TokenType::TOK_IS); }
TEST_F(TokTest, k_limited) { TestSymbol("limited", TokenType::TOK_LIMITED); }
TEST_F(TokTest, k_loop) { TestSymbol("loop", TokenType::TOK_LOOP); }
TEST_F(TokTest, k_mod) { TestSymbol("mod", TokenType::TOK_MOD); }
TEST_F(TokTest, k_new) { TestSymbol("new", TokenType::TOK_NEW); }
TEST_F(TokTest, k_not) { TestSymbol("not", TokenType::TOK_NOT); }
TEST_F(TokTest, k_null) { TestSymbol("null", TokenType::TOK_NULL); }
TEST_F(TokTest, k_of) { TestSymbol("of", TokenType::TOK_OF); }
TEST_F(TokTest, k_or) { TestSymbol("or", TokenType::TOK_OR); }
TEST_F(TokTest, k_others) { TestSymbol("others", TokenType::TOK_OTHERS); }
TEST_F(TokTest, k_out) { TestSymbol("out", TokenType::TOK_OUT); }
TEST_F(TokTest, k_package) { TestSymbol("package", TokenType::TOK_PACKAGE); }
TEST_F(TokTest, k_pragma) { TestSymbol("pragma", TokenType::TOK_PRAGMA); }
TEST_F(TokTest, k_private) { TestSymbol("private", TokenType::TOK_PRIVATE); }
TEST_F(TokTest, k_procedure) { TestSymbol("procedure", TokenType::TOK_PROCEDURE); }
TEST_F(TokTest, k_raise) { TestSymbol("raise", TokenType::TOK_RAISE); }
TEST_F(TokTest, k_range) { TestSymbol("range", TokenType::TOK_RANGE); }
TEST_F(TokTest, k_record) { TestSymbol("record", TokenType::TOK_RECORD); }
TEST_F(TokTest, k_rem) { TestSymbol("rem", TokenType::TOK_REM); }
TEST_F(TokTest, k_renames) { TestSymbol("renames", TokenType::TOK_RENAMES); }
TEST_F(TokTest, k_return) { TestSymbol("return", TokenType::TOK_RETURN); }
TEST_F(TokTest, k_reverse) { TestSymbol("reverse", TokenType::TOK_REVERSE); }
TEST_F(TokTest, k_select) { TestSymbol("select", TokenType::TOK_SELECT); }
TEST_F(TokTest, k_separate) { TestSymbol("separate", TokenType::TOK_SEPARATE); }
TEST_F(TokTest, k_subtype) { TestSymbol("subtype", TokenType::TOK_SUBTYPE); }
TEST_F(TokTest, k_task) { TestSymbol("task", TokenType::TOK_TASK); }
TEST_F(TokTest, k_terminate) { TestSymbol("terminate", TokenType::TOK_TERMINATE); }
TEST_F(TokTest, k_then) { TestSymbol("then", TokenType::TOK_THEN); }
TEST_F(TokTest, k_type) { TestSymbol("type", TokenType::TOK_TYPE); }
TEST_F(TokTest, k_use) { TestSymbol("use", TokenType::TOK_USE); }
TEST_F(TokTest, k_when) { TestSymbol("when", TokenType::TOK_WHEN); }
TEST_F(TokTest, k_while) { TestSymbol("while", TokenType::TOK_WHILE); }
TEST_F(TokTest, k_with) { TestSymbol("with", TokenType::TOK_WITH); }
TEST_F(TokTest, k_xor) { TestSymbol("xor", TokenType::TOK_XOR); }


//
// -- Identifiers
//    -----------
TEST_F(TokTest, Ident_one_sp) { TestIdent(" ONE "); }
TEST_F(TokTest, Ident_uno_sp) { TestIdent("   uno   "); }
TEST_F(TokTest, Ident_underscore_sp) { TestIdent(" a_b_C"); }
TEST_F(TokTest, Ident_digits_sp) { TestIdent(" a_b_C_1_2_3 "); }
TEST_F(TokTest, Ident_true_sp) { TestIdent(" true"); }
TEST_F(TokTest, Ident_false_sp) { TestIdent(" false"); }
TEST_F(TokTest, Ident_integer_sp) { TestIdent(" integer"); }
TEST_F(TokTest, Ident_real_sp) { TestIdent(" real"); }

TEST_F(TokTest, Ident_one) { TestIdent("ONE"); }
TEST_F(TokTest, Ident_uno) { TestIdent("uno"); }
TEST_F(TokTest, Ident_underscore) { TestIdent("a_b_C"); }
TEST_F(TokTest, Ident_digits) { TestIdent("a_b_C_1_2_3"); }
TEST_F(TokTest, Ident_true) { TestIdent("true"); }
TEST_F(TokTest, Ident_false) { TestIdent("false"); }
TEST_F(TokTest, Ident_integer) { TestIdent("integer"); }
TEST_F(TokTest, Ident_real) { TestIdent("real"); }



//
// -- Integers
//    --------
TEST_F(TokTest, Int_0x0) { TestUInt("16#0#"); }
TEST_F(TokTest, Int_hex) { TestUInt("16#0123456789abcdef#"); }
TEST_F(TokTest, Int_exp1) { TestUInt("16#0#e12345"); }
TEST_F(TokTest, Int_exp2) { TestUInt("16#0#e-12345"); }
TEST_F(TokTest, Int_hex2) { TestUInt("16#012_34_5_6_789a_bc_def#"); }
TEST_F(TokTest, Int_exp3) { TestUInt("16#0#e+00012345"); }


TEST_F(TokTest, Int_0) { TestUInt("0"); }
TEST_F(TokTest, Int_1) { TestUInt("0e12345"); }
TEST_F(TokTest, Int_2) { TestUInt("0e+12345"); }
TEST_F(TokTest, Int_3) { TestUInt("0e-12345"); }
TEST_F(TokTest, Int_4) { TestUInt("0e-12_345"); }
TEST_F(TokTest, Int_5) { TestUInt("1_000e0"); }



//
// -- Reals
//    -----
TEST_F(TokTest, Real_0x0) { TestUReal("16#0.0#"); }
TEST_F(TokTest, Real_hex) { TestUReal("16#0123456789abcdef.0#"); }
TEST_F(TokTest, Real_exp1) { TestUReal("16#0.0#e12345"); }
TEST_F(TokTest, Real_exp2) { TestUReal("16#0.0#e-12345"); }
TEST_F(TokTest, Real_hex2) { TestUReal("16#012_34_5_6_789a_bc_def.0#"); }


TEST_F(TokTest, Real_0) { TestUReal("0.0"); }
TEST_F(TokTest, Real_1) { TestUReal("0.0e12345"); }
TEST_F(TokTest, Real_2) { TestUReal("0.0e+12345"); }
TEST_F(TokTest, Real_3) { TestUReal("0.0e-12345"); }
TEST_F(TokTest, Real_4) { TestUReal("0.0e-12_345"); }
TEST_F(TokTest, Real_5) { TestUReal("1_000.0e0"); }


//
// -- Strings
//    -------
TEST_F(TokTest, String_0) { TestString("\"string\"", "string"); }
TEST_F(TokTest, String_1) { TestString("\"\"", ""); }
TEST_F(TokTest, String_2) { TestString("\"\"\"\"", "\""); }
TEST_F(TokTest, String_3) { TestString("\"He said \"\"hello\"\" to me\"", "He said \"hello\" to me"); }



//
// -- Character Literals
//    ------------------
TEST_F(TokTest, Char_0) { TestChar("'A'", 'A'); }
TEST_F(TokTest, Char_1) { TestChar("'''", '\''); }
TEST_F(TokTest, Char_2) { TestChar("'\"'", '"'); }


//
// -- Errors
//    ------
TEST_F(TokTest, ErrorIdent1) { TestError( "_a_b_C_1_2_3_", DiagID::IllegalIdentifier, { "_a_b_c_1_2_3_", "Identifier cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIdent2) { TestError( "_", DiagID::IllegalIdentifier, { "_", "Identifier cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorIntBase_0x0) { TestError("_16#0#", DiagID::IllegalInteger, { "_16#0#", "Integer base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIntBase_hex) { TestError("_16#0123456789abcdef#", DiagID::IllegalInteger, { "_16#0123456789abcdef#", "Integer base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIntBase_exp1) { TestError("_16#0#e12345", DiagID::IllegalInteger, { "_16#0#e12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIntBase_exp2) { TestError("_16#0#e-12345", DiagID::IllegalInteger, { "_16#0#e-12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIntBase_exp3) { TestError("_16#0#e-_12345", DiagID::IllegalInteger, { "_16#0#e-_12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorIntBase_hex2) { TestError("_16#012_34_5_6___789a__bc_def#", DiagID::IllegalInteger, { "_16#012_34_5_6___789a__bc_def#", "Integer base cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorInt_0x0) { TestError("16#_0#", DiagID::IllegalInteger, { "16#_0#", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_hex) { TestError("16#_0123456789abcdef#", DiagID::IllegalInteger, { "16#_0123456789abcdef#", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_exp1) { TestError("16#_0#e12345", DiagID::IllegalInteger, { "16#_0#e12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_exp2) { TestError("16#_0#e-12345", DiagID::IllegalInteger, { "16#_0#e-12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_exp3) { TestError("16#_0#e-_12345", DiagID::IllegalInteger, { "16#_0#e-_12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_hex2) { TestError("16#_012_34_5_6___789a__bc_def#", DiagID::IllegalInteger, { "16#_012_34_5_6___789a__bc_def#", "Integer cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorInt_0) { TestError("_0", DiagID::IllegalInteger, { "_0", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_1) { TestError("_0e12345", DiagID::IllegalInteger, { "_0e12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_2) { TestError("_0e+12345", DiagID::IllegalInteger, { "_0e+12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_4) { TestError("_0e-12345", DiagID::IllegalInteger, { "_0e-12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_5) { TestError("_0e-_12345", DiagID::IllegalInteger, { "_0e-_12345", "Integer cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_6) { TestError("_1_000e0", DiagID::IllegalInteger, { "_1_000e0", "Integer cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorIntBased_1) { TestError("000002#20#", DiagID::IllegalDigit, { "000002#20#" } ); }
TEST_F(TokTest, ErrorIntBased_2) { TestError("000003#30#", DiagID::IllegalDigit, { "000003#30#" } ); }
TEST_F(TokTest, ErrorIntBased_3) { TestError("000004#40#", DiagID::IllegalDigit, { "000004#40#" } ); }
TEST_F(TokTest, ErrorIntBased_4) { TestError("000005#50#", DiagID::IllegalDigit, { "000005#50#" } ); }
TEST_F(TokTest, ErrorIntBased_5) { TestError("000006#60#", DiagID::IllegalDigit, { "000006#60#" } ); }
TEST_F(TokTest, ErrorIntBased_6) { TestError("000007#70#", DiagID::IllegalDigit, { "000007#70#" } ); }
TEST_F(TokTest, ErrorIntBased_7) { TestError("000008#80#", DiagID::IllegalDigit, { "000008#80#" } ); }
TEST_F(TokTest, ErrorIntBased_8) { TestError("000009#90#", DiagID::IllegalDigit, { "000009#90#" } ); }
TEST_F(TokTest, ErrorIntBased_9) { TestError("000010#c0#", DiagID::IllegalDigit, { "000010#c0#" } ); }
TEST_F(TokTest, ErrorIntBased_10) { TestError("000016#G0#", DiagID::IllegalDigit, { "000016#G0#" } ); }

TEST_F(TokTest, ErrorIntMissingExp_1) { TestError("1e", DiagID::IllegalInteger, { "1e", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorIntMissingExp_2) { TestError("1e-", DiagID::IllegalInteger, { "1e-", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorIntMissingExp_3) { TestError("1e+", DiagID::IllegalInteger, { "1e+", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorIntMissingExp_4) { TestError("16#1#e", DiagID::IllegalInteger, { "16#1#e", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorIntMissingExp_5) { TestError("16#1#e-", DiagID::IllegalInteger, { "16#1#e-", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorIntMissingExp_6) { TestError("16#1#e+", DiagID::IllegalInteger, { "16#1#e+", "Integer exponent part missing" } ); }

TEST_F(TokTest, ErrorInt_expPart1) { TestError("16#0#e_12345", DiagID::IllegalInteger, { "16#0#e_12345", "Integer exponent part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_expPart2) { TestError("1e-_123_45", DiagID::IllegalInteger, { "1e-_123_45", "Integer exponent part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorInt_expPart3) { TestError("1e", DiagID::IllegalInteger, { "1e", "Integer exponent part missing" } ); }
TEST_F(TokTest, ErrorInt_expPart4) { TestError("1e1e1", DiagID::IllegalInteger, { "1e1e1", "Integer exponent part repeated" } ); }

TEST_F(TokTest, ErrorRealBase_0x0) { TestError("_16#0.0#", DiagID::IllegalReal, { "_16#0.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_hex) { TestError("_16#0123456789abcdef.0#", DiagID::IllegalReal, { "_16#0123456789abcdef.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_hex2) { TestError("_16#012_34_5_6___789a__bc_def.0#", DiagID::IllegalReal, { "_16#012_34_5_6___789a__bc_def.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_exp1) { TestError("_16#0.0#e12345", DiagID::IllegalReal, { "_16#0.0#e12345", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_exp2) { TestError("_16#0.0#e-12345", DiagID::IllegalReal, { "_16#0.0#e-12345", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_exp3) { TestError("_16#0.0#e-_12345", DiagID::IllegalReal, { "_16#0.0#e-_12345", "Real base cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealBase_exp4) { TestError("_16#0.0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "_16#0.0_0_0_0___0_0_0#e12345", "Real base cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorReal_0x0) { TestError("16#_0.0#", DiagID::IllegalReal, { "16#_0.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_hex) { TestError("16#_0123456789abcdef.0#", DiagID::IllegalReal, { "16#_0123456789abcdef.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_hex2) { TestError("16#_012_34_5_6___789a__bc_def.0#", DiagID::IllegalReal, { "16#_012_34_5_6___789a__bc_def.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_exp1) { TestError("16#_0.0#e12345", DiagID::IllegalReal, { "16#_0.0#e12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_exp2) { TestError("16#_0.0#e-12345", DiagID::IllegalReal, { "16#_0.0#e-12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_exp3) { TestError("16#_0.0#e-_12345", DiagID::IllegalReal, { "16#_0.0#e-_12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_exp4) { TestError("16#_0.0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "16#_0.0_0_0_0___0_0_0#e12345", "Real whole part cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorRealDecimal_0x0) { TestError("16#0._0#", DiagID::IllegalReal, { "16#0._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_hex) { TestError("16#0123456789abcdef._0#", DiagID::IllegalReal, { "16#0123456789abcdef._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_0x0_e) { TestError("16#0.0_#", DiagID::IllegalReal, { "16#0.0_#", "Real decimal part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_hex_e) { TestError("16#0123456789abcdef.0_#", DiagID::IllegalReal, { "16#0123456789abcdef.0_#", "Real decimal part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_hex2) { TestError("16#012_34_5_6___789a__bc_def._0#", DiagID::IllegalReal, { "16#012_34_5_6___789a__bc_def._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_exp1) { TestError("16#0._0#e12345", DiagID::IllegalReal, { "16#0._0#e12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_exp2) { TestError("16#0._0#e-12345", DiagID::IllegalReal, { "16#0._0#e-12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_exp3) { TestError("16#0._0#e-_12345", DiagID::IllegalReal, { "16#0._0#e-_12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorRealDecimal_exp4) { TestError("16#0._0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "16#0._0_0_0_0___0_0_0#e12345", "Real decimal part cannot begin with an '_'" } ); }

TEST_F(TokTest, ErrorReal_0) { TestError("_0.0", DiagID::IllegalReal, { "_0.0", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_1) { TestError("_0.0e12345", DiagID::IllegalReal, { "_0.0e12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_2) { TestError("_0.0e+12345", DiagID::IllegalReal, { "_0.0e+12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_4) { TestError("_0.0e-12345", DiagID::IllegalReal, { "_0.0e-12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_5) { TestError("_0.0e-_12345", DiagID::IllegalReal, { "_0.0e-_12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_6) { TestError("_1_000.0e0", DiagID::IllegalReal, { "_1_000.0e0", "Real whole part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_7) { TestError("0_.0", DiagID::IllegalReal, { "0_.0", "Real whole part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorReal_8) { TestError("0_.0e12345", DiagID::IllegalReal, { "0_.0e12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorReal_9) { TestError("0_.0e+12345", DiagID::IllegalReal, { "0_.0e+12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorReal_10) { TestError("0_.0e-12345", DiagID::IllegalReal, { "0_.0e-12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorReal_11) { TestError("0_.0e-_12345", DiagID::IllegalReal, { "0_.0e-_12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(TokTest, ErrorReal_12) { TestError("1_000_.0e0", DiagID::IllegalReal, { "1_000_.0e0", "Real whole part cannot end with an '_'" } ); }

TEST_F(TokTest, ErrorReal_expPart1) { TestError("16#0.0#e_12345", DiagID::IllegalReal, { "16#0.0#e_12345", "Real exponent part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_expPart2) { TestError("1.0e-_123_45", DiagID::IllegalReal, { "1.0e-_123_45", "Real exponent part cannot begin with an '_'" } ); }
TEST_F(TokTest, ErrorReal_expPart3) { TestError("1.0e", DiagID::IllegalReal, { "1.0e", "Real exponent part missing" } ); }
TEST_F(TokTest, ErrorReal_expPart4) { TestError("1.0e1e1", DiagID::IllegalReal, { "1.0e1e1", "Real exponent part repeated" } ); }

TEST_F(TokTest, ErrorString_0) { TestError("\"str\ning\"", DiagID::IllegalString, { "str", "End-of-line found in string" }, false ); }
TEST_F(TokTest, ErrorString_1) { TestError("\"string", DiagID::IllegalString, { "string", "End-of-file found in string" }, false ); }


//
// -- Some streams of tokens
//    ----------------------
TEST_F(TokTest, StreamTest001) { TestTokenStream("package test is", { TokenType::TOK_PACKAGE, TokenType::TOK_IDENTIFIER, TokenType::TOK_IS} ); }
TEST_F(TokTest, StreamTest002) {
    TestTokenStream("COUNT, SUM  : INTEGER;", { TokenType::TOK_IDENTIFIER,
        TokenType::TOK_COMMA,
        TokenType::TOK_IDENTIFIER,
        TokenType::TOK_COLON,
        TokenType::TOK_IDENTIFIER,
        TokenType::TOK_SEMICOLON} );
}
