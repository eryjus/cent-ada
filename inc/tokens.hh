//=================================================================================================================
//  TokenStream::Get().hh -- This header defines the tokens used by the compiler
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



#include <vector>



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
// -- Define an error message from the scanner to the parser
//    ------------------------------------------------------
enum class DiagID;
using ArgList = std::vector<std::string>;

struct ScannerError {
    DiagID msg;
    ArgList args = {};
};



//
// -- This is the payload for the lexer to communicate extra information to the parser
//    --------------------------------------------------------------------------------
using YYSTYPE = std::variant<
    std::monostate,             // empty token payload      0
    struct CharLiteral,         // a character literal      1
    struct IntLiteral,          // an integer literal       2
    struct RealLiteral,         // a real literal           3
    struct StringLiteral,       // a string literal         4
    struct IdentifierLexeme,    // identifier               5
    struct ScannerError         // scanner error            6
>;


extern YYSTYPE yylval;



