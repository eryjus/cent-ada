//===================================================================================================================
// lexer.cc -- This google test executes tests against the lexer
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Mar-20  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "ada.hh"
#include <gtest/gtest.h>



extern TokenType yylex(void);
extern FILE *yyin;
extern YYSTYPE yylval;
extern int yylineno;
extern "C" void *yy_scan_string(const char *);
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
    void TestSymbol(std::string code, TokenType exp) {
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
    void TestIdent(std::string code) {
        // -- given
        ScanString(code);
        std::string exp = code;
        std::transform(exp.begin(), exp.end(), exp.begin(), [](unsigned char c){ return std::tolower(c); });
        while (exp.size() && exp[0] == ' ') exp = exp.substr(1);
        while (exp.size() && exp[exp.size() - 1] == ' ') exp= exp.substr(0, exp.size() - 1);

        // -- when
        TokenType tok = yylex();
        std::string lexeme = std::get<IdentifierLexeme>(yylval).name;

        // -- then
        EXPECT_EQ(tok, TokenType::TOK_IDENTIFIER);
        EXPECT_EQ(lexeme, exp);
        EXPECT_EQ(yylex(), TokenType::YYEOF);
    }
};



//
// == The individual tests
//    ====================
TEST_F(LexTest, ampersand) { TestSymbol(" & ", TokenType::TOK_AMPERSAND); }
TEST_F(LexTest, leftparen) { TestSymbol(" ( ", TokenType::TOK_LEFT_PARENTHESIS); }
TEST_F(LexTest, rightparen) { TestSymbol(" ) ", TokenType::TOK_RIGHT_PARENTHESIS); }
TEST_F(LexTest, star) { TestSymbol(" * ", TokenType::TOK_STAR); }
TEST_F(LexTest, plus) { TestSymbol(" + ", TokenType::TOK_PLUS); }
TEST_F(LexTest, comma) { TestSymbol(" , ", TokenType::TOK_COMMA); }
TEST_F(LexTest, hyphen) { TestSymbol(" - ", TokenType::TOK_HYPHEN); }
TEST_F(LexTest, dot) { TestSymbol(" . ", TokenType::TOK_DOT); }
TEST_F(LexTest, slash) { TestSymbol(" / ", TokenType::TOK_SLASH); }
TEST_F(LexTest, colon) { TestSymbol(" : ", TokenType::TOK_COLON); }
TEST_F(LexTest, semicolon) { TestSymbol(" ; ", TokenType::TOK_SEMICOLON); }
TEST_F(LexTest, less_than) { TestSymbol(" < ", TokenType::TOK_LESS_THAN); }
TEST_F(LexTest, equal) { TestSymbol(" = ", TokenType::TOK_EQUAL); }
TEST_F(LexTest, greater_than) { TestSymbol(" > ", TokenType::TOK_GREATER_THAN); }
TEST_F(LexTest, underline) { TestSymbol(" _ ", TokenType::TOK_UNDERLINE); }
TEST_F(LexTest, vertical_bar) { TestSymbol(" | ", TokenType::TOK_VERTICAL_BAR); }
TEST_F(LexTest, exclamation_mark) { TestSymbol(" ! ", TokenType::TOK_EXCLAMATION_MARK); }
TEST_F(LexTest, dollar) { TestSymbol(" $ ", TokenType::TOK_DOLLAR); }
TEST_F(LexTest, percent) { TestSymbol(" % ", TokenType::TOK_PERCENT); }
TEST_F(LexTest, question_mark) { TestSymbol(" ? ", TokenType::TOK_QUESTION_MARK); }
TEST_F(LexTest, commercial_at) { TestSymbol(" @ ", TokenType::TOK_COMMERCIAL_AT); }
TEST_F(LexTest, left_square_bracket) { TestSymbol(" [ ", TokenType::TOK_LEFT_SQUARE_BRACKET); }
TEST_F(LexTest, back_slash) { TestSymbol(" \\ ", TokenType::TOK_BACK_SLASH); }
TEST_F(LexTest, right_square_bracket) { TestSymbol(" ] ", TokenType::TOK_RIGHT_SQUARE_BRACKET); }
TEST_F(LexTest, circumflex) { TestSymbol(" ^ ", TokenType::TOK_CIRCUMFLEX); }
TEST_F(LexTest, grave_accent) { TestSymbol(" ` ", TokenType::TOK_GRAVE_ACCENT); }
TEST_F(LexTest, left_brace) { TestSymbol(" { ", TokenType::TOK_LEFT_BRACE); }
TEST_F(LexTest, right_brace) { TestSymbol(" } ", TokenType::TOK_RIGHT_BRACE); }
TEST_F(LexTest, tilde) { TestSymbol(" ~ ", TokenType::TOK_TILDE); }

TEST_F(LexTest, arrow) { TestSymbol(" => ", TokenType::TOK_ARROW); }
TEST_F(LexTest, double_dot) { TestSymbol(" .. ", TokenType::TOK_DOUBLE_DOT); }
TEST_F(LexTest, double_star) { TestSymbol(" ** ", TokenType::TOK_DOUBLE_STAR); }
TEST_F(LexTest, assignment) { TestSymbol(" := ", TokenType::TOK_ASSIGNMENT); }
TEST_F(LexTest, inequality) { TestSymbol(" /= ", TokenType::TOK_INEQUALITY); }
TEST_F(LexTest, greater_than_or_equal) { TestSymbol(" >= ", TokenType::TOK_GREATER_THAN_OR_EQUAL); }
TEST_F(LexTest, less_than_or_equal) { TestSymbol(" <= ", TokenType::TOK_LESS_THAN_OR_EQUAL); }
TEST_F(LexTest, left_label_bracket) { TestSymbol(" << ", TokenType::TOK_LEFT_LABEL_BRACKET); }
TEST_F(LexTest, right_label_bracket) { TestSymbol(" >> ", TokenType::TOK_RIGHT_LABEL_BRACKET); }
TEST_F(LexTest, box) { TestSymbol(" <> ", TokenType::TOK_BOX); }

TEST_F(LexTest, k_abort) { TestSymbol(" abort ", TokenType::TOK_ABORT); }
TEST_F(LexTest, k_abs) { TestSymbol(" abs ", TokenType::TOK_ABS); }
TEST_F(LexTest, k_accept) { TestSymbol(" accept ", TokenType::TOK_ACCEPT); }
TEST_F(LexTest, k_access) { TestSymbol(" access ", TokenType::TOK_ACCESS); }
TEST_F(LexTest, k_all) { TestSymbol(" all ", TokenType::TOK_ALL); }
TEST_F(LexTest, k_and) { TestSymbol(" and ", TokenType::TOK_AND); }
TEST_F(LexTest, k_array) { TestSymbol(" array ", TokenType::TOK_ARRAY); }
TEST_F(LexTest, k_at) { TestSymbol(" at ", TokenType::TOK_AT); }
TEST_F(LexTest, k_begin) { TestSymbol(" begin ", TokenType::TOK_BEGIN); }
TEST_F(LexTest, k_body) { TestSymbol(" body ", TokenType::TOK_BODY); }
TEST_F(LexTest, k_case) { TestSymbol(" case ", TokenType::TOK_CASE); }
TEST_F(LexTest, k_constant) { TestSymbol(" constant ", TokenType::TOK_CONSTANT); }
TEST_F(LexTest, k_declare) { TestSymbol(" declare ", TokenType::TOK_DECLARE); }
TEST_F(LexTest, k_delay) { TestSymbol(" delay ", TokenType::TOK_DELAY); }
TEST_F(LexTest, k_delta) { TestSymbol(" delta ", TokenType::TOK_DELTA); }
TEST_F(LexTest, k_digits) { TestSymbol(" digits ", TokenType::TOK_DIGITS); }
TEST_F(LexTest, k_do) { TestSymbol(" do ", TokenType::TOK_DO); }
TEST_F(LexTest, k_else) { TestSymbol(" else ", TokenType::TOK_ELSE); }
TEST_F(LexTest, k_elsif) { TestSymbol(" elsif ", TokenType::TOK_ELSIF); }
TEST_F(LexTest, k_end) { TestSymbol(" end ", TokenType::TOK_END); }
TEST_F(LexTest, k_entry) { TestSymbol(" entry ", TokenType::TOK_ENTRY); }
TEST_F(LexTest, k_exception) { TestSymbol(" exception ", TokenType::TOK_EXCEPTION); }
TEST_F(LexTest, k_exit) { TestSymbol(" exit ", TokenType::TOK_EXIT); }
TEST_F(LexTest, k_for) { TestSymbol(" for ", TokenType::TOK_FOR); }
TEST_F(LexTest, k_function) { TestSymbol(" function ", TokenType::TOK_FUNCTION); }
TEST_F(LexTest, k_generic) { TestSymbol(" generic ", TokenType::TOK_GENERIC); }
TEST_F(LexTest, k_goto) { TestSymbol(" goto ", TokenType::TOK_GOTO); }
TEST_F(LexTest, k_if) { TestSymbol(" if ", TokenType::TOK_IF); }
TEST_F(LexTest, k_in) { TestSymbol(" in ", TokenType::TOK_IN); }
TEST_F(LexTest, k_is) { TestSymbol(" is ", TokenType::TOK_IS); }
TEST_F(LexTest, k_limited) { TestSymbol(" limited ", TokenType::TOK_LIMITED); }
TEST_F(LexTest, k_loop) { TestSymbol(" loop ", TokenType::TOK_LOOP); }
TEST_F(LexTest, k_mod) { TestSymbol(" mod ", TokenType::TOK_MOD); }
TEST_F(LexTest, k_new) { TestSymbol(" new ", TokenType::TOK_NEW); }
TEST_F(LexTest, k_not) { TestSymbol(" not ", TokenType::TOK_NOT); }
TEST_F(LexTest, k_null) { TestSymbol(" null ", TokenType::TOK_NULL); }
TEST_F(LexTest, k_of) { TestSymbol(" of ", TokenType::TOK_OF); }
TEST_F(LexTest, k_or) { TestSymbol(" or ", TokenType::TOK_OR); }
TEST_F(LexTest, k_others) { TestSymbol(" others ", TokenType::TOK_OTHERS); }
TEST_F(LexTest, k_out) { TestSymbol(" out ", TokenType::TOK_OUT); }
TEST_F(LexTest, k_package) { TestSymbol(" package ", TokenType::TOK_PACKAGE); }
TEST_F(LexTest, k_pragma) { TestSymbol(" pragma ", TokenType::TOK_PRAGMA); }
TEST_F(LexTest, k_private) { TestSymbol(" private ", TokenType::TOK_PRIVATE); }
TEST_F(LexTest, k_procedure) { TestSymbol(" procedure ", TokenType::TOK_PROCEDURE); }
TEST_F(LexTest, k_raise) { TestSymbol(" raise ", TokenType::TOK_RAISE); }
TEST_F(LexTest, k_range) { TestSymbol(" range ", TokenType::TOK_RANGE); }
TEST_F(LexTest, k_record) { TestSymbol(" record ", TokenType::TOK_RECORD); }
TEST_F(LexTest, k_rem) { TestSymbol(" rem ", TokenType::TOK_REM); }
TEST_F(LexTest, k_renames) { TestSymbol(" renames ", TokenType::TOK_RENAMES); }
TEST_F(LexTest, k_return) { TestSymbol(" return ", TokenType::TOK_RETURN); }
TEST_F(LexTest, k_reverse) { TestSymbol(" reverse ", TokenType::TOK_REVERSE); }
TEST_F(LexTest, k_select) { TestSymbol(" select ", TokenType::TOK_SELECT); }
TEST_F(LexTest, k_separate) { TestSymbol(" separate ", TokenType::TOK_SEPARATE); }
TEST_F(LexTest, k_subtype) { TestSymbol(" subtype ", TokenType::TOK_SUBTYPE); }
TEST_F(LexTest, k_task) { TestSymbol(" task ", TokenType::TOK_TASK); }
TEST_F(LexTest, k_terminate) { TestSymbol(" terminate ", TokenType::TOK_TERMINATE); }
TEST_F(LexTest, k_then) { TestSymbol(" then ", TokenType::TOK_THEN); }
TEST_F(LexTest, k_type) { TestSymbol(" type ", TokenType::TOK_TYPE); }
TEST_F(LexTest, k_use) { TestSymbol(" use ", TokenType::TOK_USE); }
TEST_F(LexTest, k_when) { TestSymbol(" when ", TokenType::TOK_WHEN); }
TEST_F(LexTest, k_while) { TestSymbol(" while ", TokenType::TOK_WHILE); }
TEST_F(LexTest, k_with) { TestSymbol(" with ", TokenType::TOK_WITH); }
TEST_F(LexTest, k_xor) { TestSymbol(" xor ", TokenType::TOK_XOR); }

TEST_F(LexTest, Ident_one) { TestIdent(" ONE "); }
TEST_F(LexTest, Ident_uno) { TestIdent("  uno  "); }
TEST_F(LexTest, Ident_underscore) { TestIdent(" a_b_C"); }
TEST_F(LexTest, Ident_digits) { TestIdent(" a_b_C_1_2_3_"); }





