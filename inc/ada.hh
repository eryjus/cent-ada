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



#pragma once



//
// -- These are the complete list of token types
//    ------------------------------------------
typedef enum {
    YYEOF                       = 0,

    DUMMY_FIRST_TOKEN           = 256,

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

    TOK_ABORT                   = 320,
    TOK_ABS                     = 321,
    TOK_ACCEPT                  = 322,
    TOK_ACCESS                  = 323,
    TOK_ALL                     = 324,
    TOK_AND                     = 325,
    TOK_ARRAY                   = 326,
    TOK_AT                      = 327,
    TOK_BEGIN                   = 328,
    TOK_BODY                    = 329,
    TOK_CASE                    = 330,
    TOK_CONSTANT                = 331,
    TOK_DECLARE                 = 332,
    TOK_DELAY                   = 333,
    TOK_DELTA                   = 334,
    TOK_DIGITS                  = 335,
    TOK_DO                      = 336,
    TOK_ELSE                    = 337,
    TOK_ELSIF                   = 338,
    TOK_END                     = 339,
    TOK_ENTRY                   = 340,
    TOK_EXCEPTION               = 341,
    TOK_EXIT                    = 342,
    TOK_FOR                     = 343,
    TOK_FUNCTION                = 344,
    TOK_GENERIC                 = 345,
    TOK_GOTO                    = 346,
    TOK_IF                      = 347,
    TOK_IN                      = 348,
    TOK_IS                      = 349,
    TOK_LIMITED                 = 350,
    TOK_LOOP                    = 351,
    TOK_MOD                     = 352,
    TOK_NEW                     = 353,
    TOK_NOT                     = 354,
    TOK_NULL                    = 355,
    TOK_OF                      = 356,
    TOK_OR                      = 357,
    TOK_OTHERS                  = 358,
    TOK_OUT                     = 359,
    TOK_PACKAGE                 = 360,
    TOK_PRAGMA                  = 361,
    TOK_PRIVATE                 = 362,
    TOK_PROCEDURE               = 363,
    TOK_RAISE                   = 364,
    TOK_RANGE                   = 365,
    TOK_RECORD                  = 366,
    TOK_REM                     = 367,
    TOK_RENAMES                 = 368,
    TOK_RETURN                  = 369,
    TOK_REVERSE                 = 370,
    TOK_SELECT                  = 371,
    TOK_SEPARATE                = 372,
    TOK_SUBTYPE                 = 373,
    TOK_TASK                    = 374,
    TOK_TERMINATE               = 375,
    TOK_THEN                    = 376,
    TOK_TYPE                    = 377,
    TOK_USE                     = 378,
    TOK_WHEN                    = 379,
    TOK_WHILE                   = 380,
    TOK_WITH                    = 381,
    TOK_XOR                     = 382,

    TOK_IDENTIFIER              = 390,
    TOK_UNIVERSAL_INT_LITERAL   = 391,
    TOK_UNIVERSAL_REAL_LITERAL  = 392,
    TOK_CHARACTER_LITERAL       = 393,
    TOK_STRING_LITERAL          = 394,

    TOK_PRAGMA_NAME             = 450,

    TOK_ERROR                   = 500,
} TokenType_t;



//
// -- Include standard libraries
//    --------------------------
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>


#include "tstream.hh"



//
// -- some global variables
//    ---------------------
extern std::string strVal;
extern int column;


