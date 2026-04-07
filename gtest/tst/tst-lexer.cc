//===================================================================================================================
// tst-lexer.cc -- This google test executes tests against the lexer
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
// -- Single Character Symbols
//    ------------------------
TEST_F(LexTest, ampersand_sp) { TestSymbol(" & ", TokenType::TOK_AMPERSAND); }
TEST_F(LexTest, leftparen_sp) { TestSymbol(" ( ", TokenType::TOK_LEFT_PARENTHESIS); }
TEST_F(LexTest, rightparen_sp) { TestSymbol(" ) ", TokenType::TOK_RIGHT_PARENTHESIS); }
TEST_F(LexTest, star_sp) { TestSymbol(" * ", TokenType::TOK_STAR); }
TEST_F(LexTest, plus_sp) { TestSymbol(" + ", TokenType::TOK_PLUS); }
TEST_F(LexTest, comma_sp) { TestSymbol(" , ", TokenType::TOK_COMMA); }
TEST_F(LexTest, hyphen_sp) { TestSymbol(" - ", TokenType::TOK_HYPHEN); }
TEST_F(LexTest, dot_sp) { TestSymbol(" . ", TokenType::TOK_DOT); }
TEST_F(LexTest, slash_sp) { TestSymbol(" / ", TokenType::TOK_SLASH); }
TEST_F(LexTest, colon_sp) { TestSymbol(" : ", TokenType::TOK_COLON); }
TEST_F(LexTest, semicolon_sp) { TestSymbol(" ; ", TokenType::TOK_SEMICOLON); }
TEST_F(LexTest, less_than_sp) { TestSymbol(" < ", TokenType::TOK_LESS_THAN); }
TEST_F(LexTest, equal_sp) { TestSymbol(" = ", TokenType::TOK_EQUAL); }
TEST_F(LexTest, greater_than_sp) { TestSymbol(" > ", TokenType::TOK_GREATER_THAN); }
TEST_F(LexTest, vertical_bar_sp) { TestSymbol(" | ", TokenType::TOK_VERTICAL_BAR); }
TEST_F(LexTest, exclamation_mark_sp) { TestSymbol(" ! ", TokenType::TOK_EXCLAMATION_MARK); }
TEST_F(LexTest, dollar_sp) { TestSymbol(" $ ", TokenType::TOK_DOLLAR); }
TEST_F(LexTest, percent_sp) { TestSymbol(" % ", TokenType::TOK_PERCENT); }
TEST_F(LexTest, question_mark_sp) { TestSymbol(" ? ", TokenType::TOK_QUESTION_MARK); }
TEST_F(LexTest, commercial_at_sp) { TestSymbol(" @ ", TokenType::TOK_COMMERCIAL_AT); }
TEST_F(LexTest, left_square_bracket_sp) { TestSymbol(" [ ", TokenType::TOK_LEFT_SQUARE_BRACKET); }
TEST_F(LexTest, back_slash_sp) { TestSymbol(" \\ ", TokenType::TOK_BACK_SLASH); }
TEST_F(LexTest, right_square_bracket_sp) { TestSymbol(" ] ", TokenType::TOK_RIGHT_SQUARE_BRACKET); }
TEST_F(LexTest, circumflex_sp) { TestSymbol(" ^ ", TokenType::TOK_CIRCUMFLEX); }
TEST_F(LexTest, grave_accent_sp) { TestSymbol(" ` ", TokenType::TOK_GRAVE_ACCENT); }
TEST_F(LexTest, left_brace_sp) { TestSymbol(" { ", TokenType::TOK_LEFT_BRACE); }
TEST_F(LexTest, right_brace_sp) { TestSymbol(" } ", TokenType::TOK_RIGHT_BRACE); }
TEST_F(LexTest, tilde_sp) { TestSymbol(" ~ ", TokenType::TOK_TILDE); }

TEST_F(LexTest, ampersand) {TestSymbol("&", TokenType::TOK_AMPERSAND); }
TEST_F(LexTest, leftparen) { TestSymbol("(", TokenType::TOK_LEFT_PARENTHESIS); }
TEST_F(LexTest, rightparen) { TestSymbol(")", TokenType::TOK_RIGHT_PARENTHESIS); }
TEST_F(LexTest, star) { TestSymbol("*", TokenType::TOK_STAR); }
TEST_F(LexTest, plus) { TestSymbol("+", TokenType::TOK_PLUS); }
TEST_F(LexTest, comma) { TestSymbol(",", TokenType::TOK_COMMA); }
TEST_F(LexTest, hyphen) { TestSymbol("-", TokenType::TOK_HYPHEN); }
TEST_F(LexTest, dot) { TestSymbol(".", TokenType::TOK_DOT); }
TEST_F(LexTest, slash) { TestSymbol("/", TokenType::TOK_SLASH); }
TEST_F(LexTest, colon) { TestSymbol(":", TokenType::TOK_COLON); }
TEST_F(LexTest, semicolon) { TestSymbol(";", TokenType::TOK_SEMICOLON); }
TEST_F(LexTest, less_than) { TestSymbol("<", TokenType::TOK_LESS_THAN); }
TEST_F(LexTest, equal) { TestSymbol("=", TokenType::TOK_EQUAL); }
TEST_F(LexTest, greater_than) { TestSymbol(">", TokenType::TOK_GREATER_THAN); }
TEST_F(LexTest, vertical_bar) { TestSymbol("|", TokenType::TOK_VERTICAL_BAR); }
TEST_F(LexTest, exclamation_mark) { TestSymbol("!", TokenType::TOK_EXCLAMATION_MARK); }
TEST_F(LexTest, dollar) { TestSymbol("$", TokenType::TOK_DOLLAR); }
TEST_F(LexTest, percent) { TestSymbol("%", TokenType::TOK_PERCENT); }
TEST_F(LexTest, question_mark) { TestSymbol("?", TokenType::TOK_QUESTION_MARK); }
TEST_F(LexTest, commercial_at) { TestSymbol("@", TokenType::TOK_COMMERCIAL_AT); }
TEST_F(LexTest, left_square_bracket) { TestSymbol("[", TokenType::TOK_LEFT_SQUARE_BRACKET); }
TEST_F(LexTest, back_slash) { TestSymbol("\\", TokenType::TOK_BACK_SLASH); }
TEST_F(LexTest, right_square_bracket) { TestSymbol("]", TokenType::TOK_RIGHT_SQUARE_BRACKET); }
TEST_F(LexTest, circumflex) { TestSymbol("^", TokenType::TOK_CIRCUMFLEX); }
TEST_F(LexTest, grave_accent) { TestSymbol("`", TokenType::TOK_GRAVE_ACCENT); }
TEST_F(LexTest, left_brace) { TestSymbol("{", TokenType::TOK_LEFT_BRACE); }
TEST_F(LexTest, right_brace) { TestSymbol("}", TokenType::TOK_RIGHT_BRACE); }
TEST_F(LexTest, tilde) { TestSymbol("~", TokenType::TOK_TILDE); }


//
// -- Multi-Character Symbols
//    -----------------------
TEST_F(LexTest, arrow_sp) { TestSymbol(" => ", TokenType::TOK_ARROW); }
TEST_F(LexTest, double_dot_sp) { TestSymbol(" .. ", TokenType::TOK_DOUBLE_DOT); }
TEST_F(LexTest, double_star_sp) { TestSymbol(" ** ", TokenType::TOK_DOUBLE_STAR); }
TEST_F(LexTest, assignment_sp) { TestSymbol(" := ", TokenType::TOK_ASSIGNMENT); }
TEST_F(LexTest, inequality_sp) { TestSymbol(" /= ", TokenType::TOK_INEQUALITY); }
TEST_F(LexTest, greater_than_or_equal_sp) { TestSymbol(" >= ", TokenType::TOK_GREATER_THAN_OR_EQUAL); }
TEST_F(LexTest, less_than_or_equal_sp) { TestSymbol(" <= ", TokenType::TOK_LESS_THAN_OR_EQUAL); }
TEST_F(LexTest, left_label_bracket_sp) { TestSymbol(" << ", TokenType::TOK_LEFT_LABEL_BRACKET); }
TEST_F(LexTest, right_label_bracket_sp) { TestSymbol(" >> ", TokenType::TOK_RIGHT_LABEL_BRACKET); }
TEST_F(LexTest, box_sp) { TestSymbol(" <> ", TokenType::TOK_BOX); }

TEST_F(LexTest, arrow) { TestSymbol("=>", TokenType::TOK_ARROW); }
TEST_F(LexTest, double_dot) { TestSymbol("..", TokenType::TOK_DOUBLE_DOT); }
TEST_F(LexTest, double_star) { TestSymbol("**", TokenType::TOK_DOUBLE_STAR); }
TEST_F(LexTest, assignment) { TestSymbol(":=", TokenType::TOK_ASSIGNMENT); }
TEST_F(LexTest, inequality) { TestSymbol("/=", TokenType::TOK_INEQUALITY); }
TEST_F(LexTest, greater_than_or_equal) { TestSymbol(">=", TokenType::TOK_GREATER_THAN_OR_EQUAL); }
TEST_F(LexTest, less_than_or_equal) { TestSymbol("<=", TokenType::TOK_LESS_THAN_OR_EQUAL); }
TEST_F(LexTest, left_label_bracket) { TestSymbol("<<", TokenType::TOK_LEFT_LABEL_BRACKET); }
TEST_F(LexTest, right_label_bracket) { TestSymbol(">>", TokenType::TOK_RIGHT_LABEL_BRACKET); }
TEST_F(LexTest, box) { TestSymbol("<>", TokenType::TOK_BOX); }



//
// -- Keywords
//    --------
TEST_F(LexTest, k_abort_sp) { TestSymbol(" abort ", TokenType::TOK_ABORT); }
TEST_F(LexTest, k_abs_sp) { TestSymbol(" abs ", TokenType::TOK_ABS); }
TEST_F(LexTest, k_accept_sp) { TestSymbol(" accept ", TokenType::TOK_ACCEPT); }
TEST_F(LexTest, k_access_sp) { TestSymbol(" access ", TokenType::TOK_ACCESS); }
TEST_F(LexTest, k_all_sp) { TestSymbol(" all ", TokenType::TOK_ALL); }
TEST_F(LexTest, k_and_sp) { TestSymbol(" and ", TokenType::TOK_AND); }
TEST_F(LexTest, k_array_sp) { TestSymbol(" array ", TokenType::TOK_ARRAY); }
TEST_F(LexTest, k_at_sp) { TestSymbol(" at ", TokenType::TOK_AT); }
TEST_F(LexTest, k_begin_sp) { TestSymbol(" begin ", TokenType::TOK_BEGIN); }
TEST_F(LexTest, k_body_sp) { TestSymbol(" body ", TokenType::TOK_BODY); }
TEST_F(LexTest, k_case_sp) { TestSymbol(" case ", TokenType::TOK_CASE); }
TEST_F(LexTest, k_constant_sp) { TestSymbol(" constant ", TokenType::TOK_CONSTANT); }
TEST_F(LexTest, k_declare_sp) { TestSymbol(" declare ", TokenType::TOK_DECLARE); }
TEST_F(LexTest, k_delay_sp) { TestSymbol(" delay ", TokenType::TOK_DELAY); }
TEST_F(LexTest, k_delta_sp) { TestSymbol(" delta ", TokenType::TOK_DELTA); }
TEST_F(LexTest, k_digits_sp) { TestSymbol(" digits ", TokenType::TOK_DIGITS); }
TEST_F(LexTest, k_do_sp) { TestSymbol(" do ", TokenType::TOK_DO); }
TEST_F(LexTest, k_else_sp) { TestSymbol(" else ", TokenType::TOK_ELSE); }
TEST_F(LexTest, k_elsif_sp) { TestSymbol(" elsif ", TokenType::TOK_ELSIF); }
TEST_F(LexTest, k_end_sp) { TestSymbol(" end ", TokenType::TOK_END); }
TEST_F(LexTest, k_entry_sp) { TestSymbol(" entry ", TokenType::TOK_ENTRY); }
TEST_F(LexTest, k_exception_sp) { TestSymbol(" exception ", TokenType::TOK_EXCEPTION); }
TEST_F(LexTest, k_exit_sp) { TestSymbol(" exit ", TokenType::TOK_EXIT); }
TEST_F(LexTest, k_for_sp) { TestSymbol(" for ", TokenType::TOK_FOR); }
TEST_F(LexTest, k_function_sp) { TestSymbol(" function ", TokenType::TOK_FUNCTION); }
TEST_F(LexTest, k_generic_sp) { TestSymbol(" generic ", TokenType::TOK_GENERIC); }
TEST_F(LexTest, k_goto_sp) { TestSymbol(" goto ", TokenType::TOK_GOTO); }
TEST_F(LexTest, k_if_sp) { TestSymbol(" if ", TokenType::TOK_IF); }
TEST_F(LexTest, k_in_sp) { TestSymbol(" in ", TokenType::TOK_IN); }
TEST_F(LexTest, k_is_sp) { TestSymbol(" is ", TokenType::TOK_IS); }
TEST_F(LexTest, k_limited_sp) { TestSymbol(" limited ", TokenType::TOK_LIMITED); }
TEST_F(LexTest, k_loop_sp) { TestSymbol(" loop ", TokenType::TOK_LOOP); }
TEST_F(LexTest, k_mod_sp) { TestSymbol(" mod ", TokenType::TOK_MOD); }
TEST_F(LexTest, k_new_sp) { TestSymbol(" new ", TokenType::TOK_NEW); }
TEST_F(LexTest, k_not_sp) { TestSymbol(" not ", TokenType::TOK_NOT); }
TEST_F(LexTest, k_null_sp) { TestSymbol(" null ", TokenType::TOK_NULL); }
TEST_F(LexTest, k_of_sp) { TestSymbol(" of ", TokenType::TOK_OF); }
TEST_F(LexTest, k_or_sp) { TestSymbol(" or ", TokenType::TOK_OR); }
TEST_F(LexTest, k_others_sp) { TestSymbol(" others ", TokenType::TOK_OTHERS); }
TEST_F(LexTest, k_out_sp) { TestSymbol(" out ", TokenType::TOK_OUT); }
TEST_F(LexTest, k_package_sp) { TestSymbol(" package ", TokenType::TOK_PACKAGE); }
TEST_F(LexTest, k_pragma_sp) { TestSymbol(" pragma ", TokenType::TOK_PRAGMA); }
TEST_F(LexTest, k_private_sp) { TestSymbol(" private ", TokenType::TOK_PRIVATE); }
TEST_F(LexTest, k_procedure_sp) { TestSymbol(" procedure ", TokenType::TOK_PROCEDURE); }
TEST_F(LexTest, k_raise_sp) { TestSymbol(" raise ", TokenType::TOK_RAISE); }
TEST_F(LexTest, k_range_sp) { TestSymbol(" range ", TokenType::TOK_RANGE); }
TEST_F(LexTest, k_record_sp) { TestSymbol(" record ", TokenType::TOK_RECORD); }
TEST_F(LexTest, k_rem_sp) { TestSymbol(" rem ", TokenType::TOK_REM); }
TEST_F(LexTest, k_renames_sp) { TestSymbol(" renames ", TokenType::TOK_RENAMES); }
TEST_F(LexTest, k_return_sp) { TestSymbol(" return ", TokenType::TOK_RETURN); }
TEST_F(LexTest, k_reverse_sp) { TestSymbol(" reverse ", TokenType::TOK_REVERSE); }
TEST_F(LexTest, k_select_sp) { TestSymbol(" select ", TokenType::TOK_SELECT); }
TEST_F(LexTest, k_separate_sp) { TestSymbol(" separate ", TokenType::TOK_SEPARATE); }
TEST_F(LexTest, k_subtype_sp) { TestSymbol(" subtype ", TokenType::TOK_SUBTYPE); }
TEST_F(LexTest, k_task_sp) { TestSymbol(" task ", TokenType::TOK_TASK); }
TEST_F(LexTest, k_terminate_sp) { TestSymbol(" terminate ", TokenType::TOK_TERMINATE); }
TEST_F(LexTest, k_then_sp) { TestSymbol(" then ", TokenType::TOK_THEN); }
TEST_F(LexTest, k_type_sp) { TestSymbol(" type ", TokenType::TOK_TYPE); }
TEST_F(LexTest, k_use_sp) { TestSymbol(" use ", TokenType::TOK_USE); }
TEST_F(LexTest, k_when_sp) { TestSymbol(" when ", TokenType::TOK_WHEN); }
TEST_F(LexTest, k_while_sp) { TestSymbol(" while ", TokenType::TOK_WHILE); }
TEST_F(LexTest, k_with_sp) { TestSymbol(" with ", TokenType::TOK_WITH); }
TEST_F(LexTest, k_xor_sp) { TestSymbol(" xor ", TokenType::TOK_XOR); }

TEST_F(LexTest, k_abort) { TestSymbol("abort", TokenType::TOK_ABORT); }
TEST_F(LexTest, k_abs) { TestSymbol("abs", TokenType::TOK_ABS); }
TEST_F(LexTest, k_accept) { TestSymbol("accept", TokenType::TOK_ACCEPT); }
TEST_F(LexTest, k_access) { TestSymbol("access", TokenType::TOK_ACCESS); }
TEST_F(LexTest, k_all) { TestSymbol("all", TokenType::TOK_ALL); }
TEST_F(LexTest, k_and) { TestSymbol("and", TokenType::TOK_AND); }
TEST_F(LexTest, k_array) { TestSymbol("array", TokenType::TOK_ARRAY); }
TEST_F(LexTest, k_at) { TestSymbol("at", TokenType::TOK_AT); }
TEST_F(LexTest, k_begin) { TestSymbol("begin", TokenType::TOK_BEGIN); }
TEST_F(LexTest, k_body) { TestSymbol("body", TokenType::TOK_BODY); }
TEST_F(LexTest, k_case) { TestSymbol("case", TokenType::TOK_CASE); }
TEST_F(LexTest, k_constant) { TestSymbol("constant", TokenType::TOK_CONSTANT); }
TEST_F(LexTest, k_declare) { TestSymbol("declare", TokenType::TOK_DECLARE); }
TEST_F(LexTest, k_delay) { TestSymbol("delay", TokenType::TOK_DELAY); }
TEST_F(LexTest, k_delta) { TestSymbol("delta", TokenType::TOK_DELTA); }
TEST_F(LexTest, k_digits) { TestSymbol("digits", TokenType::TOK_DIGITS); }
TEST_F(LexTest, k_do) { TestSymbol("do", TokenType::TOK_DO); }
TEST_F(LexTest, k_else) { TestSymbol("else", TokenType::TOK_ELSE); }
TEST_F(LexTest, k_elsif) { TestSymbol("elsif", TokenType::TOK_ELSIF); }
TEST_F(LexTest, k_end) { TestSymbol("end", TokenType::TOK_END); }
TEST_F(LexTest, k_entry) { TestSymbol("entry", TokenType::TOK_ENTRY); }
TEST_F(LexTest, k_exception) { TestSymbol("exception", TokenType::TOK_EXCEPTION); }
TEST_F(LexTest, k_exit) { TestSymbol("exit", TokenType::TOK_EXIT); }
TEST_F(LexTest, k_for) { TestSymbol("for", TokenType::TOK_FOR); }
TEST_F(LexTest, k_function) { TestSymbol("function", TokenType::TOK_FUNCTION); }
TEST_F(LexTest, k_generic) { TestSymbol("generic", TokenType::TOK_GENERIC); }
TEST_F(LexTest, k_goto) { TestSymbol("goto", TokenType::TOK_GOTO); }
TEST_F(LexTest, k_if) { TestSymbol("if", TokenType::TOK_IF); }
TEST_F(LexTest, k_in) { TestSymbol("in", TokenType::TOK_IN); }
TEST_F(LexTest, k_is) { TestSymbol("is", TokenType::TOK_IS); }
TEST_F(LexTest, k_limited) { TestSymbol("limited", TokenType::TOK_LIMITED); }
TEST_F(LexTest, k_loop) { TestSymbol("loop", TokenType::TOK_LOOP); }
TEST_F(LexTest, k_mod) { TestSymbol("mod", TokenType::TOK_MOD); }
TEST_F(LexTest, k_new) { TestSymbol("new", TokenType::TOK_NEW); }
TEST_F(LexTest, k_not) { TestSymbol("not", TokenType::TOK_NOT); }
TEST_F(LexTest, k_null) { TestSymbol("null", TokenType::TOK_NULL); }
TEST_F(LexTest, k_of) { TestSymbol("of", TokenType::TOK_OF); }
TEST_F(LexTest, k_or) { TestSymbol("or", TokenType::TOK_OR); }
TEST_F(LexTest, k_others) { TestSymbol("others", TokenType::TOK_OTHERS); }
TEST_F(LexTest, k_out) { TestSymbol("out", TokenType::TOK_OUT); }
TEST_F(LexTest, k_package) { TestSymbol("package", TokenType::TOK_PACKAGE); }
TEST_F(LexTest, k_pragma) { TestSymbol("pragma", TokenType::TOK_PRAGMA); }
TEST_F(LexTest, k_private) { TestSymbol("private", TokenType::TOK_PRIVATE); }
TEST_F(LexTest, k_procedure) { TestSymbol("procedure", TokenType::TOK_PROCEDURE); }
TEST_F(LexTest, k_raise) { TestSymbol("raise", TokenType::TOK_RAISE); }
TEST_F(LexTest, k_range) { TestSymbol("range", TokenType::TOK_RANGE); }
TEST_F(LexTest, k_record) { TestSymbol("record", TokenType::TOK_RECORD); }
TEST_F(LexTest, k_rem) { TestSymbol("rem", TokenType::TOK_REM); }
TEST_F(LexTest, k_renames) { TestSymbol("renames", TokenType::TOK_RENAMES); }
TEST_F(LexTest, k_return) { TestSymbol("return", TokenType::TOK_RETURN); }
TEST_F(LexTest, k_reverse) { TestSymbol("reverse", TokenType::TOK_REVERSE); }
TEST_F(LexTest, k_select) { TestSymbol("select", TokenType::TOK_SELECT); }
TEST_F(LexTest, k_separate) { TestSymbol("separate", TokenType::TOK_SEPARATE); }
TEST_F(LexTest, k_subtype) { TestSymbol("subtype", TokenType::TOK_SUBTYPE); }
TEST_F(LexTest, k_task) { TestSymbol("task", TokenType::TOK_TASK); }
TEST_F(LexTest, k_terminate) { TestSymbol("terminate", TokenType::TOK_TERMINATE); }
TEST_F(LexTest, k_then) { TestSymbol("then", TokenType::TOK_THEN); }
TEST_F(LexTest, k_type) { TestSymbol("type", TokenType::TOK_TYPE); }
TEST_F(LexTest, k_use) { TestSymbol("use", TokenType::TOK_USE); }
TEST_F(LexTest, k_when) { TestSymbol("when", TokenType::TOK_WHEN); }
TEST_F(LexTest, k_while) { TestSymbol("while", TokenType::TOK_WHILE); }
TEST_F(LexTest, k_with) { TestSymbol("with", TokenType::TOK_WITH); }
TEST_F(LexTest, k_xor) { TestSymbol("xor", TokenType::TOK_XOR); }



//
// -- Identifiers
//    -----------
TEST_F(LexTest, Ident_one_sp) { TestIdent(" ONE "); }
TEST_F(LexTest, Ident_uno_sp) { TestIdent("   uno   "); }
TEST_F(LexTest, Ident_underscore_sp) { TestIdent(" a_b_C"); }
TEST_F(LexTest, Ident_digits_sp) { TestIdent(" a_b_C_1_2_3 "); }
TEST_F(LexTest, Ident_true_sp) { TestIdent(" true"); }
TEST_F(LexTest, Ident_false_sp) { TestIdent(" false"); }
TEST_F(LexTest, Ident_integer_sp) { TestIdent(" integer"); }
TEST_F(LexTest, Ident_real_sp) { TestIdent(" real"); }

TEST_F(LexTest, Ident_one) { TestIdent("ONE"); }
TEST_F(LexTest, Ident_uno) { TestIdent("uno"); }
TEST_F(LexTest, Ident_underscore) { TestIdent("a_b_C"); }
TEST_F(LexTest, Ident_digits) { TestIdent("a_b_C_1_2_3"); }
TEST_F(LexTest, Ident_true) { TestIdent("true"); }
TEST_F(LexTest, Ident_false) { TestIdent("false"); }
TEST_F(LexTest, Ident_integer) { TestIdent("integer"); }
TEST_F(LexTest, Ident_real) { TestIdent("real"); }



//
// -- Integers
//    --------
TEST_F(LexTest, Int_0x0) { TestUInt("16#0#"); }
TEST_F(LexTest, Int_hex) { TestUInt("16#0123456789abcdef#"); }
TEST_F(LexTest, Int_exp1) { TestUInt("16#0#e12345"); }
TEST_F(LexTest, Int_exp2) { TestUInt("16#0#e-12345"); }
TEST_F(LexTest, Int_hex2) { TestUInt("16#012_34_5_6_789a_bc_def#"); }
TEST_F(LexTest, Int_exp3) { TestUInt("16#0#e+00012345"); }


TEST_F(LexTest, Int_0) { TestUInt("0"); }
TEST_F(LexTest, Int_1) { TestUInt("0e12345"); }
TEST_F(LexTest, Int_2) { TestUInt("0e+12345"); }
TEST_F(LexTest, Int_3) { TestUInt("0e-12345"); }
TEST_F(LexTest, Int_4) { TestUInt("0e-12_345"); }
TEST_F(LexTest, Int_5) { TestUInt("1_000e0"); }



//
// -- Reals
//    -----
TEST_F(LexTest, Real_0x0) { TestUReal("16#0.0#"); }
TEST_F(LexTest, Real_hex) { TestUReal("16#0123456789abcdef.0#"); }
TEST_F(LexTest, Real_exp1) { TestUReal("16#0.0#e12345"); }
TEST_F(LexTest, Real_exp2) { TestUReal("16#0.0#e-12345"); }
TEST_F(LexTest, Real_hex2) { TestUReal("16#012_34_5_6_789a_bc_def.0#"); }


TEST_F(LexTest, Real_0) { TestUReal("0.0"); }
TEST_F(LexTest, Real_1) { TestUReal("0.0e12345"); }
TEST_F(LexTest, Real_2) { TestUReal("0.0e+12345"); }
TEST_F(LexTest, Real_3) { TestUReal("0.0e-12345"); }
TEST_F(LexTest, Real_4) { TestUReal("0.0e-12_345"); }
TEST_F(LexTest, Real_5) { TestUReal("1_000.0e0"); }


//
// -- Strings
//    -------
TEST_F(LexTest, String_0) { TestString("\"string\"", "string"); }
TEST_F(LexTest, String_1) { TestString("\"\"", ""); }
TEST_F(LexTest, String_2) { TestString("\"\"\"\"", "\""); }
TEST_F(LexTest, String_3) { TestString("\"He said \"\"hello\"\" to me\"", "He said \"hello\" to me"); }



//
// -- Character Literals
//    ------------------
TEST_F(LexTest, Char_0) { TestChar("'A'", 'A'); }
TEST_F(LexTest, Char_1) { TestChar("'''", '\''); }
TEST_F(LexTest, Char_2) { TestChar("'\"'", '"'); }


//
// -- Errors
//    ------
TEST_F(LexTest, ErrorIdent1) { TestError( "_a_b_C_1_2_3_", DiagID::IllegalIdentifier, { "_a_b_c_1_2_3_", "Identifier cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIdent2) { TestError( "_", DiagID::IllegalIdentifier, { "_", "Identifier cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorIntBase_0x0) { TestError("_16#0#", DiagID::IllegalInteger, { "_16#0#", "Integer base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIntBase_hex) { TestError("_16#0123456789abcdef#", DiagID::IllegalInteger, { "_16#0123456789abcdef#", "Integer base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIntBase_exp1) { TestError("_16#0#e12345", DiagID::IllegalInteger, { "_16#0#e12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIntBase_exp2) { TestError("_16#0#e-12345", DiagID::IllegalInteger, { "_16#0#e-12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIntBase_exp3) { TestError("_16#0#e-_12345", DiagID::IllegalInteger, { "_16#0#e-_12345", "Integer base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorIntBase_hex2) { TestError("_16#012_34_5_6___789a__bc_def#", DiagID::IllegalInteger, { "_16#012_34_5_6___789a__bc_def#", "Integer base cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorInt_0x0) { TestError("16#_0#", DiagID::IllegalInteger, { "16#_0#", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_hex) { TestError("16#_0123456789abcdef#", DiagID::IllegalInteger, { "16#_0123456789abcdef#", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_exp1) { TestError("16#_0#e12345", DiagID::IllegalInteger, { "16#_0#e12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_exp2) { TestError("16#_0#e-12345", DiagID::IllegalInteger, { "16#_0#e-12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_exp3) { TestError("16#_0#e-_12345", DiagID::IllegalInteger, { "16#_0#e-_12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_hex2) { TestError("16#_012_34_5_6___789a__bc_def#", DiagID::IllegalInteger, { "16#_012_34_5_6___789a__bc_def#", "Integer cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorInt_0) { TestError("_0", DiagID::IllegalInteger, { "_0", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_1) { TestError("_0e12345", DiagID::IllegalInteger, { "_0e12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_2) { TestError("_0e+12345", DiagID::IllegalInteger, { "_0e+12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_4) { TestError("_0e-12345", DiagID::IllegalInteger, { "_0e-12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_5) { TestError("_0e-_12345", DiagID::IllegalInteger, { "_0e-_12345", "Integer cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_6) { TestError("_1_000e0", DiagID::IllegalInteger, { "_1_000e0", "Integer cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorIntBased_1) { TestError("000002#20#", DiagID::IllegalDigit, { "000002#20#" } ); }
TEST_F(LexTest, ErrorIntBased_2) { TestError("000003#30#", DiagID::IllegalDigit, { "000003#30#" } ); }
TEST_F(LexTest, ErrorIntBased_3) { TestError("000004#40#", DiagID::IllegalDigit, { "000004#40#" } ); }
TEST_F(LexTest, ErrorIntBased_4) { TestError("000005#50#", DiagID::IllegalDigit, { "000005#50#" } ); }
TEST_F(LexTest, ErrorIntBased_5) { TestError("000006#60#", DiagID::IllegalDigit, { "000006#60#" } ); }
TEST_F(LexTest, ErrorIntBased_6) { TestError("000007#70#", DiagID::IllegalDigit, { "000007#70#" } ); }
TEST_F(LexTest, ErrorIntBased_7) { TestError("000008#80#", DiagID::IllegalDigit, { "000008#80#" } ); }
TEST_F(LexTest, ErrorIntBased_8) { TestError("000009#90#", DiagID::IllegalDigit, { "000009#90#" } ); }
TEST_F(LexTest, ErrorIntBased_9) { TestError("000010#c0#", DiagID::IllegalDigit, { "000010#c0#" } ); }
TEST_F(LexTest, ErrorIntBased_10) { TestError("000016#G0#", DiagID::IllegalDigit, { "000016#G0#" } ); }

TEST_F(LexTest, ErrorIntMissingExp_1) { TestError("1e", DiagID::IllegalInteger, { "1e", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorIntMissingExp_2) { TestError("1e-", DiagID::IllegalInteger, { "1e-", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorIntMissingExp_3) { TestError("1e+", DiagID::IllegalInteger, { "1e+", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorIntMissingExp_4) { TestError("16#1#e", DiagID::IllegalInteger, { "16#1#e", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorIntMissingExp_5) { TestError("16#1#e-", DiagID::IllegalInteger, { "16#1#e-", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorIntMissingExp_6) { TestError("16#1#e+", DiagID::IllegalInteger, { "16#1#e+", "Integer exponent part missing" } ); }

TEST_F(LexTest, ErrorInt_expPart1) { TestError("16#0#e_12345", DiagID::IllegalInteger, { "16#0#e_12345", "Integer exponent part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_expPart2) { TestError("1e-_123_45", DiagID::IllegalInteger, { "1e-_123_45", "Integer exponent part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorInt_expPart3) { TestError("1e", DiagID::IllegalInteger, { "1e", "Integer exponent part missing" } ); }
TEST_F(LexTest, ErrorInt_expPart4) { TestError("1e1e1", DiagID::IllegalInteger, { "1e1e1", "Integer exponent part repeated" } ); }

TEST_F(LexTest, ErrorRealBase_0x0) { TestError("_16#0.0#", DiagID::IllegalReal, { "_16#0.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_hex) { TestError("_16#0123456789abcdef.0#", DiagID::IllegalReal, { "_16#0123456789abcdef.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_hex2) { TestError("_16#012_34_5_6___789a__bc_def.0#", DiagID::IllegalReal, { "_16#012_34_5_6___789a__bc_def.0#", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_exp1) { TestError("_16#0.0#e12345", DiagID::IllegalReal, { "_16#0.0#e12345", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_exp2) { TestError("_16#0.0#e-12345", DiagID::IllegalReal, { "_16#0.0#e-12345", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_exp3) { TestError("_16#0.0#e-_12345", DiagID::IllegalReal, { "_16#0.0#e-_12345", "Real base cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealBase_exp4) { TestError("_16#0.0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "_16#0.0_0_0_0___0_0_0#e12345", "Real base cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorReal_0x0) { TestError("16#_0.0#", DiagID::IllegalReal, { "16#_0.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_hex) { TestError("16#_0123456789abcdef.0#", DiagID::IllegalReal, { "16#_0123456789abcdef.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_hex2) { TestError("16#_012_34_5_6___789a__bc_def.0#", DiagID::IllegalReal, { "16#_012_34_5_6___789a__bc_def.0#", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_exp1) { TestError("16#_0.0#e12345", DiagID::IllegalReal, { "16#_0.0#e12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_exp2) { TestError("16#_0.0#e-12345", DiagID::IllegalReal, { "16#_0.0#e-12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_exp3) { TestError("16#_0.0#e-_12345", DiagID::IllegalReal, { "16#_0.0#e-_12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_exp4) { TestError("16#_0.0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "16#_0.0_0_0_0___0_0_0#e12345", "Real whole part cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorRealDecimal_0x0) { TestError("16#0._0#", DiagID::IllegalReal, { "16#0._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_hex) { TestError("16#0123456789abcdef._0#", DiagID::IllegalReal, { "16#0123456789abcdef._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_0x0_e) { TestError("16#0.0_#", DiagID::IllegalReal, { "16#0.0_#", "Real decimal part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_hex_e) { TestError("16#0123456789abcdef.0_#", DiagID::IllegalReal, { "16#0123456789abcdef.0_#", "Real decimal part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_hex2) { TestError("16#012_34_5_6___789a__bc_def._0#", DiagID::IllegalReal, { "16#012_34_5_6___789a__bc_def._0#", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_exp1) { TestError("16#0._0#e12345", DiagID::IllegalReal, { "16#0._0#e12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_exp2) { TestError("16#0._0#e-12345", DiagID::IllegalReal, { "16#0._0#e-12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_exp3) { TestError("16#0._0#e-_12345", DiagID::IllegalReal, { "16#0._0#e-_12345", "Real decimal part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorRealDecimal_exp4) { TestError("16#0._0_0_0_0___0_0_0#e12345", DiagID::IllegalReal, { "16#0._0_0_0_0___0_0_0#e12345", "Real decimal part cannot begin with an '_'" } ); }

TEST_F(LexTest, ErrorReal_0) { TestError("_0.0", DiagID::IllegalReal, { "_0.0", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_1) { TestError("_0.0e12345", DiagID::IllegalReal, { "_0.0e12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_2) { TestError("_0.0e+12345", DiagID::IllegalReal, { "_0.0e+12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_4) { TestError("_0.0e-12345", DiagID::IllegalReal, { "_0.0e-12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_5) { TestError("_0.0e-_12345", DiagID::IllegalReal, { "_0.0e-_12345", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_6) { TestError("_1_000.0e0", DiagID::IllegalReal, { "_1_000.0e0", "Real whole part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_7) { TestError("0_.0", DiagID::IllegalReal, { "0_.0", "Real whole part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorReal_8) { TestError("0_.0e12345", DiagID::IllegalReal, { "0_.0e12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorReal_9) { TestError("0_.0e+12345", DiagID::IllegalReal, { "0_.0e+12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorReal_10) { TestError("0_.0e-12345", DiagID::IllegalReal, { "0_.0e-12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorReal_11) { TestError("0_.0e-_12345", DiagID::IllegalReal, { "0_.0e-_12345", "Real whole part cannot end with an '_'" } ); }
TEST_F(LexTest, ErrorReal_12) { TestError("1_000_.0e0", DiagID::IllegalReal, { "1_000_.0e0", "Real whole part cannot end with an '_'" } ); }

TEST_F(LexTest, ErrorReal_expPart1) { TestError("16#0.0#e_12345", DiagID::IllegalReal, { "16#0.0#e_12345", "Real exponent part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_expPart2) { TestError("1.0e-_123_45", DiagID::IllegalReal, { "1.0e-_123_45", "Real exponent part cannot begin with an '_'" } ); }
TEST_F(LexTest, ErrorReal_expPart3) { TestError("1.0e", DiagID::IllegalReal, { "1.0e", "Real exponent part missing" } ); }
TEST_F(LexTest, ErrorReal_expPart4) { TestError("1.0e1e1", DiagID::IllegalReal, { "1.0e1e1", "Real exponent part repeated" } ); }

TEST_F(LexTest, ErrorString_0) { TestError("\"str\ning\"", DiagID::IllegalString, { "str", "End-of-line found in string" }, false ); }
TEST_F(LexTest, ErrorString_1) { TestError("\"string", DiagID::IllegalString, { "string", "End-of-file found in string" }, false ); }




