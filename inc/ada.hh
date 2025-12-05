//=================================================================================================================
//  ada.hh -- This is the global header file for the entire compiler
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- These are the complete list of token types
//    ------------------------------------------
typedef enum {
    TOK_QUOTATION               = 257,
    TOK_SHARP                   = 258,
    TOK_AMPERSAND               = 259,
    TOK_APOSTROPHE              = 260,
    TOK_LEFT_PARENTHESIS        = 261,
    TOK_RIGHT_PARENTHESIS       = 262,
    TOK_STAR                    = 263,
    TOK_MULTIPLY                = 263,
    TOK_PLUS                    = 264,
    TOK_COMMA                   = 265,
    TOK_HYPHEN                  = 266,
    TOK_MINUS                   = 266,
    TOK_DOT                     = 267,
    TOK_POINT                   = 267,
    TOK_PERIOD                  = 267,
    TOK_SLASH                   = 268,
    TOK_DIVIDE                  = 268,
    TOK_COLON                   = 269,
    TOK_SEMICOLON               = 270,
    TOK_LESS_THAN               = 271,
    TOK_EQUAL                   = 272,
    TOK_GREATER_THAN            = 273,
    TOK_UNDERLINE               = 274,
    TOK_VERTICAL_BAR            = 275,
    TOK_EXCLAMATION_MARK        = 276,
    TOK_DOLLAR                  = 277,
    TOK_PERCENT                 = 278,
    TOK_QUESTION_MARK           = 279,
    TOK_COMMERCIAL_AT           = 280,
    TOK_LEFT_SQUARE_BRACKET     = 281,
    TOK_BACK_SLASH              = 282,
    TOK_RIGHT_SQUARE_BRACKET    = 283,
    TOK_CIRCUMFLEX              = 284,
    TOK_GRAVE_ACCENT            = 285,
    TOK_LEFT_BRACE              = 286,
    TOK_RIGHT_BRACE             = 287,
    TOK_TILDE                   = 288,

    TOK_ARROW                   = 290,
    TOK_DOUBLE_DOT              = 291,
    TOK_DOUBLE_STAR             = 292,
    TOK_EXPONENTIATE            = 292,
    TOK_ASSIGNMENT              = 293,
    TOK_INEQUALITY              = 294,
    TOK_GREATER_THAN_OR_EQUAL   = 295,
    TOK_LESS_THAN_OR_EQUAL      = 296,
    TOK_LEFT_LABEL_BRACKET      = 297,
    TOK_RIGHT_LABEL_BRACKET     = 298,
    TOK_BOX                     = 299,

    TOK_ABORT                   = 350,
    TOK_ABS                     = 351,
    TOK_ACCEPT                  = 352,
    TOK_ACCESS                  = 353,
    TOK_ALL                     = 354,
    TOK_AND                     = 355,
    TOK_ARRAY                   = 356,
    TOK_AT                      = 357,
    TOK_BEGIN                   = 358,
    TOK_BODY                    = 359,
    TOK_CASE                    = 360,
    TOK_CONSTANT                = 361,
    TOK_DECLARE                 = 362,
    TOK_DELAY                   = 363,
    TOK_DELTA                   = 364,
    TOK_DIGITS                  = 365,
    TOK_DO                      = 366,
    TOK_ELSE                    = 367,
    TOK_ELSIF                   = 368,
    TOK_END                     = 369,
    TOK_ENTRY                   = 370,
    TOK_EXCEPTION               = 371,
    TOK_EXIT                    = 372,
    TOK_FOR                     = 373,
    TOK_FUNCTION                = 374,
    TOK_GENERIC                 = 375,
    TOK_GOTO                    = 376,
    TOK_IF                      = 377,
    TOK_IN                      = 378,
    TOK_IS                      = 379,
    TOK_LIMITED                 = 380,
    TOK_LOOP                    = 381,
    TOK_MOD                     = 382,
    TOK_NEW                     = 383,
    TOK_NOT                     = 384,
    TOK_NULL                    = 385,
    TOK_OF                      = 386,
    TOK_OR                      = 387,
    TOK_OTHERS                  = 388,
    TOK_OUT                     = 389,
    TOK_PACKAGE                 = 390,
    TOK_PRAGMA                  = 391,
    TOK_PRIVATE                 = 392,
    TOK_PROCEDURE               = 393,
    TOK_RAISE                   = 394,
    TOK_RANGE                   = 395,
    TOK_RECORD                  = 396,
    TOK_REM                     = 397,
    TOK_RENAMES                 = 398,
    TOK_RETURN                  = 399,
    TOK_REVERSE                 = 400,
    TOK_SELECT                  = 401,
    TOK_SEPARATE                = 402,
    TOK_SUBTYPE                 = 403,
    TOK_TASK                    = 404,
    TOK_TERMINATE               = 405,
    TOK_THEN                    = 406,
    TOK_TYPE                    = 407,
    TOK_USE                     = 408,
    TOK_WHEN                    = 409,
    TOK_WHILE                   = 410,
    TOK_WITH                    = 411,
    TOK_XOR                     = 412,

    TOK_IDENTIFIER              = 430,
    TOK_UNIVERSAL_INT_LITERAL   = 431,
    TOK_UNIVERSAL_REAL_LITERAL  = 432,
    TOK_CHARACTER_LITERAL       = 433,
    TOK_STRING_LITERAL          = 434,

    TOK_PRAGMA_NAME             = 450,

    TOK_ERROR                   = 500,
} TokenType;



//
// -- Include standard libraries
//    --------------------------
#include <string>
#include <iostream>
#include <cstdio>



//
// -- some global variables
//    ---------------------
extern std::string strVal;


