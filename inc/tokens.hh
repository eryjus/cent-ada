//=================================================================================================================
//  tokens.hh -- This header defines the tokens used by the compiler
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-05  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- These are the tokens which will be used in scanning and parsing
//    ---------------------------------------------------------------
enum class TokenType {
    YYEOF = 0,                              /* "end of file"  */
    YYUNDEF = 257,                          /* "invalid token"  */
    TOK_QUOTATION = 258,                    /* TOK_QUOTATION  */
    TOK_SHARP = 259,                        /* TOK_SHARP  */
    TOK_AMPERSAND = 260,                    /* TOK_AMPERSAND  */
    TOK_APOSTROPHE = 261,                   /* TOK_APOSTROPHE  */
    TOK_LEFT_PARENTHESIS = 262,             /* TOK_LEFT_PARENTHESIS  */
    TOK_RIGHT_PARENTHESIS = 263,            /* TOK_RIGHT_PARENTHESIS  */
    TOK_STAR = 264,                         /* TOK_STAR  */
    TOK_MULTIPLY = 265,                     /* TOK_MULTIPLY  */
    TOK_PLUS = 266,                         /* TOK_PLUS  */
    TOK_COMMA = 267,                        /* TOK_COMMA  */
    TOK_HYPHEN = 269,                       /* TOK_HYPHEN  */
    TOK_MINUS = 269,                        /* TOK_MINUS  */
    TOK_DOT = 270,                          /* TOK_DOT  */
    TOK_POINT = 271,                        /* TOK_POINT  */
    TOK_PERIOD = 272,                       /* TOK_PERIOD  */
    TOK_SLASH = 273,                        /* TOK_SLASH  */
    TOK_DIVIDE = 274,                       /* TOK_DIVIDE  */
    TOK_COLON = 275,                        /* TOK_COLON  */
    TOK_SEMICOLON = 276,                    /* TOK_SEMICOLON  */
    TOK_LESS_THAN = 277,                    /* TOK_LESS_THAN  */
    TOK_EQUAL = 278,                        /* TOK_EQUAL  */
    TOK_GREATER_THAN = 279,                 /* TOK_GREATER_THAN  */
    TOK_UNDERLINE = 280,                    /* TOK_UNDERLINE  */
    TOK_VERTICAL_BAR = 281,                 /* TOK_VERTICAL_BAR  */
    TOK_EXCLAMATION_MARK = 282,             /* TOK_EXCLAMATION_MARK  */
    TOK_DOLLAR = 283,                       /* TOK_DOLLAR  */
    TOK_PERCENT = 284,                      /* TOK_PERCENT  */
    TOK_QUESTION_MARK = 285,                /* TOK_QUESTION_MARK  */
    TOK_COMMERCIAL_AT = 286,                /* TOK_COMMERCIAL_AT  */
    TOK_LEFT_SQUARE_BRACKET = 287,          /* TOK_LEFT_SQUARE_BRACKET  */
    TOK_BACK_SLASH = 288,                   /* TOK_BACK_SLASH  */
    TOK_RIGHT_SQUARE_BRACKET = 289,         /* TOK_RIGHT_SQUARE_BRACKET  */
    TOK_CIRCUMFLEX = 290,                   /* TOK_CIRCUMFLEX  */
    TOK_GRAVE_ACCENT = 291,                 /* TOK_GRAVE_ACCENT  */
    TOK_LEFT_BRACE = 292,                   /* TOK_LEFT_BRACE  */
    TOK_RIGHT_BRACE = 293,                  /* TOK_RIGHT_BRACE  */
    TOK_TILDE = 294,                        /* TOK_TILDE  */
    TOK_ARROW = 295,                        /* TOK_ARROW  */
    TOK_DOUBLE_DOT = 296,                   /* TOK_DOUBLE_DOT  */
    TOK_DOUBLE_STAR = 297,                  /* TOK_DOUBLE_STAR  */
    TOK_EXPONENTIATE = 297,                 /* TOK_EXPONENTIATE  */
    TOK_ASSIGNMENT = 299,                   /* TOK_ASSIGNMENT  */
    TOK_INEQUALITY = 300,                   /* TOK_INEQUALITY  */
    TOK_GREATER_THAN_OR_EQUAL = 301,        /* TOK_GREATER_THAN_OR_EQUAL  */
    TOK_LESS_THAN_OR_EQUAL = 302,           /* TOK_LESS_THAN_OR_EQUAL  */
    TOK_LEFT_LABEL_BRACKET = 303,           /* TOK_LEFT_LABEL_BRACKET  */
    TOK_RIGHT_LABEL_BRACKET = 304,          /* TOK_RIGHT_LABEL_BRACKET  */
    TOK_BOX = 305,                          /* TOK_BOX  */
    TOK_ABORT = 306,                        /* TOK_ABORT  */
    TOK_ABS = 307,                          /* TOK_ABS  */
    TOK_ACCEPT = 308,                       /* TOK_ACCEPT  */
    TOK_ACCESS = 309,                       /* TOK_ACCESS  */
    TOK_ALL = 310,                          /* TOK_ALL  */
    TOK_AND = 311,                          /* TOK_AND  */
    TOK_ARRAY = 312,                        /* TOK_ARRAY  */
    TOK_AT = 313,                           /* TOK_AT  */
    TOK_BEGIN = 314,                        /* TOK_BEGIN  */
    TOK_BODY = 315,                         /* TOK_BODY  */
    TOK_CASE = 316,                         /* TOK_CASE  */
    TOK_CONSTANT = 317,                     /* TOK_CONSTANT  */
    TOK_DECLARE = 318,                      /* TOK_DECLARE  */
    TOK_DELAY = 319,                        /* TOK_DELAY  */
    TOK_DELTA = 320,                        /* TOK_DELTA  */
    TOK_DIGITS = 321,                       /* TOK_DIGITS  */
    TOK_DO = 322,                           /* TOK_DO  */
    TOK_ELSE = 323,                         /* TOK_ELSE  */
    TOK_ELSIF = 324,                        /* TOK_ELSIF  */
    TOK_END = 325,                          /* TOK_END  */
    TOK_ENTRY = 326,                        /* TOK_ENTRY  */
    TOK_EXCEPTION = 327,                    /* TOK_EXCEPTION  */
    TOK_EXIT = 328,                         /* TOK_EXIT  */
    TOK_FOR = 329,                          /* TOK_FOR  */
    TOK_FUNCTION = 330,                     /* TOK_FUNCTION  */
    TOK_GENERIC = 331,                      /* TOK_GENERIC  */
    TOK_GOTO = 332,                         /* TOK_GOTO  */
    TOK_IF = 333,                           /* TOK_IF  */
    TOK_IN = 334,                           /* TOK_IN  */
    TOK_IS = 335,                           /* TOK_IS  */
    TOK_LIMITED = 336,                      /* TOK_LIMITED  */
    TOK_LOOP = 337,                         /* TOK_LOOP  */
    TOK_MOD = 338,                          /* TOK_MOD  */
    TOK_NEW = 339,                          /* TOK_NEW  */
    TOK_NOT = 340,                          /* TOK_NOT  */
    TOK_NULL = 341,                         /* TOK_NULL  */
    TOK_OF = 342,                           /* TOK_OF  */
    TOK_OR = 343,                           /* TOK_OR  */
    TOK_OTHERS = 344,                       /* TOK_OTHERS  */
    TOK_OUT = 345,                          /* TOK_OUT  */
    TOK_PACKAGE = 346,                      /* TOK_PACKAGE  */
    TOK_PRAGMA = 347,                       /* TOK_PRAGMA  */
    TOK_PRIVATE = 348,                      /* TOK_PRIVATE  */
    TOK_PROCEDURE = 349,                    /* TOK_PROCEDURE  */
    TOK_RAISE = 350,                        /* TOK_RAISE  */
    TOK_RANGE = 351,                        /* TOK_RANGE  */
    TOK_RECORD = 352,                       /* TOK_RECORD  */
    TOK_REM = 353,                          /* TOK_REM  */
    TOK_RENAMES = 354,                      /* TOK_RENAMES  */
    TOK_RETURN = 355,                       /* TOK_RETURN  */
    TOK_REVERSE = 356,                      /* TOK_REVERSE  */
    TOK_SELECT = 357,                       /* TOK_SELECT  */
    TOK_SEPARATE = 358,                     /* TOK_SEPARATE  */
    TOK_SUBTYPE = 359,                      /* TOK_SUBTYPE  */
    TOK_TASK = 360,                         /* TOK_TASK  */
    TOK_TERMINATE = 361,                    /* TOK_TERMINATE  */
    TOK_THEN = 362,                         /* TOK_THEN  */
    TOK_TYPE = 363,                         /* TOK_TYPE  */
    TOK_USE = 364,                          /* TOK_USE  */
    TOK_WHEN = 365,                         /* TOK_WHEN  */
    TOK_WHILE = 366,                        /* TOK_WHILE  */
    TOK_WITH = 367,                         /* TOK_WITH  */
    TOK_XOR = 368,                          /* TOK_XOR  */
    TOK_IDENTIFIER = 369,                   /* TOK_IDENTIFIER  */
    TOK_UNIVERSAL_INT_LITERAL = 370,        /* TOK_UNIVERSAL_INT_LITERAL  */
    TOK_UNIVERSAL_REAL_LITERAL = 371,       /* TOK_UNIVERSAL_REAL_LITERAL  */
    TOK_CHARACTER_LITERAL = 372,            /* TOK_CHARACTER_LITERAL  */
    TOK_STRING_LITERAL = 373,               /* TOK_STRING_LITERAL  */
    TOK_PRAGMA_NAME = 374,                  /* TOK_PRAGMA_NAME  */
    TOK_AND_THEN = 375,                     /* TOK_AND_THEN  */
    TOK_OR_ELSE = 376,                      /* TOK_OR_ELSE  */
    TOK_ERROR = 377,                        /* TOK_ERROR  */
};



//
// -- Define what a character literal will look like passed from the lexer to the parser
//    ----------------------------------------------------------------------------------
struct CharLiteral {
    std::string lexeme;
    int value;
};



//
// -- Define what an integer literal will look like when when passed from lexer to parser
//    -----------------------------------------------------------------------------------
struct IntLiteral {
    std::string lexeme;
};



//
// -- Define what a real literal will look like when when passed from lexer to parser
//    -------------------------------------------------------------------------------
struct RealLiteral {
    std::string lexeme;
};



//
// -- Define what a string literal will look like when when passed from lexer to parser
//    ---------------------------------------------------------------------------------
struct StringLiteral {
    std::string lexeme;
};



//
// -- Define what an identifier will look like passed from the lexer to the parser
//    ----------------------------------------------------------------------------
struct IdentifierLexeme {
    std::string name;
};



//
// -- This is the payload for the lexer to communicate extra information to the parser
//    --------------------------------------------------------------------------------
using YYSTYPE = std::variant<
    std::monostate,             // empty token payload
    struct CharLiteral,         // a character literal
    struct IntLiteral,          // an integer literal
    struct RealLiteral,         // a real literal
    struct IdentifierLexeme     // identifier
>;


extern YYSTYPE yylval;



