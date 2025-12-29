//=================================================================================================================
//  main.cc -- This is the main entry point for the Century Ada Compiler
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-04  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- This enum will be used to control the parse type
//    ------------------------------------------------
typedef enum {
    COMPILE_FULL,
    COMPILE_TYPES,
    COMPILE_EXPRS,
} ParseType_t;



//
// -- The global token stream used for scanning
//    -----------------------------------------
TokenStream *tokens = nullptr;



//
// -- Scan the input for testing purposes
//    -----------------------------------
static int Scan(std::string filename)
{
    extern char *yytext;
    extern TokenType_t yylex(void);
    extern FILE *yyin;

    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        std::cerr << "Unable to open file " << filename << '\n';
        return EXIT_FAILURE;
    }

    TokenType_t tok = yylex();

    while (tok) {
        switch (tok) {
        case TOK_QUOTATION:             std::cout << "\"\n";        break;
        case TOK_SHARP:                 std::cout << "#\n";         break;
        case TOK_AMPERSAND:             std::cout << "&\n";         break;
        case TOK_APOSTROPHE:            std::cout << "'\n";         break;
        case TOK_LEFT_PARENTHESIS:      std::cout << "(\n";         break;
        case TOK_RIGHT_PARENTHESIS:     std::cout << ")\n";         break;
        case TOK_STAR:                  std::cout << "*\n";         break;
        case TOK_PLUS:                  std::cout << "+\n";         break;
        case TOK_COMMA:                 std::cout << ",\n";         break;
        case TOK_HYPHEN:                std::cout << "-\n";         break;
        case TOK_DOT:                   std::cout << ".\n";         break;
        case TOK_SLASH:                 std::cout << "/\n";         break;
        case TOK_COLON:                 std::cout << ":\n";         break;
        case TOK_SEMICOLON:             std::cout << ";\n";         break;
        case TOK_LESS_THAN:             std::cout << "<\n";         break;
        case TOK_EQUAL:                 std::cout << "=\n";         break;
        case TOK_GREATER_THAN:          std::cout << ">\n";         break;
        case TOK_UNDERLINE:             std::cout << "_\n";         break;
        case TOK_VERTICAL_BAR:          std::cout << "|\n";         break;
        case TOK_EXCLAMATION_MARK:      std::cout << "!\n";         break;
        case TOK_DOLLAR:                std::cout << "$\n";         break;
        case TOK_PERCENT:               std::cout << "%\n";         break;
        case TOK_QUESTION_MARK:         std::cout << "?\n";         break;
        case TOK_COMMERCIAL_AT:         std::cout << "@\n";         break;
        case TOK_LEFT_SQUARE_BRACKET:   std::cout << "[\n";         break;
        case TOK_BACK_SLASH:            std::cout << "\\\n";        break;
        case TOK_RIGHT_SQUARE_BRACKET:  std::cout << "]\n";         break;
        case TOK_CIRCUMFLEX:            std::cout << "^\n";         break;
        case TOK_GRAVE_ACCENT:          std::cout << "`\n";         break;
        case TOK_LEFT_BRACE:            std::cout << "{\n";         break;
        case TOK_RIGHT_BRACE:           std::cout << "}\n";         break;
        case TOK_TILDE:                 std::cout << "~\n";         break;

        case TOK_ARROW:                 std::cout << "=>\n";        break;
        case TOK_DOUBLE_DOT:            std::cout << "..\n";        break;
        case TOK_DOUBLE_STAR:           std::cout << "**\n";        break;
        case TOK_ASSIGNMENT:            std::cout << ":=\n";        break;
        case TOK_INEQUALITY:            std::cout << "/=\n";        break;
        case TOK_GREATER_THAN_OR_EQUAL: std::cout << ">=\n";        break;
        case TOK_LESS_THAN_OR_EQUAL:    std::cout << "<=\n";        break;
        case TOK_LEFT_LABEL_BRACKET:    std::cout << "<<\n";        break;
        case TOK_RIGHT_LABEL_BRACKET:   std::cout << ">>\n";        break;
        case TOK_BOX:                   std::cout << "<>\n";        break;

        case TOK_ABORT:                 std::cout << "ABORT\n";     break;
        case TOK_ABS:                   std::cout << "ABS\n";       break;
        case TOK_ACCEPT:                std::cout << "ACCEPT\n";    break;
        case TOK_ACCESS:                std::cout << "ACCESS\n";    break;
        case TOK_ALL:                   std::cout << "ALL\n";       break;
        case TOK_AND:                   std::cout << "AND\n";       break;
        case TOK_ARRAY:                 std::cout << "ARRAY\n";     break;
        case TOK_AT:                    std::cout << "AT\n";        break;
        case TOK_BEGIN:                 std::cout << "BEGIN\n";     break;
        case TOK_BODY:                  std::cout << "BODY\n";      break;
        case TOK_CASE:                  std::cout << "CASE\n";      break;
        case TOK_CONSTANT:              std::cout << "CONSTANT\n";  break;
        case TOK_DECLARE:               std::cout << "DECLARE\n";   break;
        case TOK_DELAY:                 std::cout << "DELAY\n";     break;
        case TOK_DELTA:                 std::cout << "DELTA\n";     break;
        case TOK_DIGITS:                std::cout << "DIGITS\n";    break;
        case TOK_DO:                    std::cout << "DO\n";        break;
        case TOK_ELSE:                  std::cout << "ELSE\n";      break;
        case TOK_ELSIF:                 std::cout << "ELSIF\n";     break;
        case TOK_END:                   std::cout << "END\n";       break;
        case TOK_ENTRY:                 std::cout << "ENTRY\n";     break;
        case TOK_EXCEPTION:             std::cout << "EXCEPTION\n"; break;
        case TOK_EXIT:                  std::cout << "EXIT\n";      break;
        case TOK_FOR:                   std::cout << "FOR\n";       break;
        case TOK_FUNCTION:              std::cout << "FUNCTION\n";  break;
        case TOK_GENERIC:               std::cout << "GENERIC\n";   break;
        case TOK_GOTO:                  std::cout << "GOTO\n";      break;
        case TOK_IF:                    std::cout << "IF\n";        break;
        case TOK_IN:                    std::cout << "IN\n";        break;
        case TOK_IS:                    std::cout << "IS\n";        break;
        case TOK_LIMITED:               std::cout << "LIMITED\n";   break;
        case TOK_LOOP:                  std::cout << "LOOP\n";      break;
        case TOK_MOD:                   std::cout << "MOD\n";       break;
        case TOK_NEW:                   std::cout << "NEW\n";       break;
        case TOK_NOT:                   std::cout << "NOT\n";       break;
        case TOK_NULL:                  std::cout << "NULL\n";      break;
        case TOK_OF:                    std::cout << "OF\n";        break;
        case TOK_OR:                    std::cout << "OR\n";        break;
        case TOK_OTHERS:                std::cout << "OTHERS\n";    break;
        case TOK_OUT:                   std::cout << "OUT\n";       break;
        case TOK_PACKAGE:               std::cout << "PACKAGE\n";   break;
        case TOK_PRAGMA:                std::cout << "PRAGMA\n";    break;
        case TOK_PRIVATE:               std::cout << "PRIVATE\n";   break;
        case TOK_PROCEDURE:             std::cout << "PROCEDURE\n"; break;
        case TOK_RAISE:                 std::cout << "RAISE\n";     break;
        case TOK_RANGE:                 std::cout << "RANGE\n";     break;
        case TOK_RECORD:                std::cout << "RECORD\n";    break;
        case TOK_REM:                   std::cout << "REM\n";       break;
        case TOK_RENAMES:               std::cout << "RENAMES\n";   break;
        case TOK_RETURN:                std::cout << "RETURN\n";    break;
        case TOK_REVERSE:               std::cout << "REVERSE\n";   break;
        case TOK_SELECT:                std::cout << "SELECT\n";    break;
        case TOK_SEPARATE:              std::cout << "SEPARATE\n";  break;
        case TOK_SUBTYPE:               std::cout << "SUBTYPE\n";   break;
        case TOK_TASK:                  std::cout << "TASK\n";      break;
        case TOK_TERMINATE:             std::cout << "TERMINATE\n"; break;
        case TOK_THEN:                  std::cout << "THEN\n";      break;
        case TOK_TYPE:                  std::cout << "TYPE\n";      break;
        case TOK_USE:                   std::cout << "USE\n";       break;
        case TOK_WHEN:                  std::cout << "WHEN\n";      break;
        case TOK_WHILE:                 std::cout << "WHILE\n";     break;
        case TOK_WITH:                  std::cout << "WITH\n";      break;
        case TOK_XOR:                   std::cout << "XOR\n";       break;
        case TOK_AND_THEN:              std::cout << "AND THEN\n";  break;
        case TOK_OR_ELSE:               std::cout << "OR ELSE\n";   break;

        case TOK_IDENTIFIER:
            std::cout << "IDENTIFIER: (" << yytext << ")\n";
            break;

        case TOK_UNIVERSAL_INT_LITERAL:
            std::cout << "INTEGER LITERAL: (" << yytext << ")\n";
            break;

        case TOK_UNIVERSAL_REAL_LITERAL:
            std::cout << "REAL LITERAL: (" << yytext << ")\n";
            break;

        case TOK_CHARACTER_LITERAL:
            std::cout << "CHARACTER LITERAL: (" << yytext[1] << ")\n";
            break;

        case TOK_STRING_LITERAL:
            std::cout << "STRING LITERAL: (" << strVal << ")\n";
            break;

        case TOK_PRAGMA_NAME:
            std::cout << "PRAGMA DIRECTIVE: " << yytext << '\n';
            break;

        case TOK_ERROR:
            std::cout << "ERROR\n";
            break;

        default:
            std::cerr << "Unknown Token Type: " << tok << '\n'; break;
        }

        tok = yylex();
    }


    return EXIT_SUCCESS;
}



//
// -- Tokenize the source into a token stream
//    ---------------------------------------
static int Tokenize(std::string filename)
{
    tokens = new TokenStream(filename.c_str());
    tokens->Listing();
    tokens->List();

    return EXIT_SUCCESS;
}



//
// -- Properly Compile the source
//    ---------------------------
static int Compile(std::string filename, ParseType_t type)
{
    tokens = new TokenStream(filename.c_str());
    Parser *parser = new Parser(*tokens);
    diags.SetParser(parser);
//    parser->SetTrace(true);
    int cnt = 0;
    int rv = EXIT_SUCCESS;

    switch (type) {
    case COMPILE_TYPES:
        while (tokens->Current() != YYEOF) {
            if(!parser->ParseBasicDeclaration()) {
                std::cerr << "ERROR: Unable to properly parse Basic Declaration\n";
                rv = EXIT_FAILURE;
                goto exit;
            }
        }

        break;


    case COMPILE_EXPRS:
        while (parser->ParseBasicDeclaration()) {}
        std::cerr << "\n";
        std::cerr << "********************************\n";
        std::cerr << "** Starting Expressions Parse **\n";
        std::cerr << "********************************\n\n";
        if(!parser->ParseExpression()) {
            std::cerr << "\nERROR: Unable to properly parse Expression\n";
            rv = EXIT_FAILURE;
            goto exit;
        }

        std::cerr << "next token " << tokens->tokenStr(tokens->Current()) << '\n';
        if (tokens->Current() != YYEOF) {
            std::cerr << "\nERROR: Extra input in Expression parse\n";
            rv = EXIT_FAILURE;
            goto exit;
        }

        break;


    default:
        break;
    }

    std::cerr << "Parse Complete.\n";

exit:
    tokens->Listing();
    parser->Scopes()->Print();

    std::cerr << "   Errors  : " << diags.Errors() << '\n';
    std::cerr << "   Warnings: " << diags.Warnings() << '\n';
    return rv;
}



//
// -- Print the help message and exit
//    -------------------------------
static void Usage(std::string pgm)
{
    std::cout << "Usage:\n";

    exit(EXIT_SUCCESS);
}


#include <unistd.h>
//
// -- The main entry point
//    --------------------
int main(int argc, char *argv[])
{
    enum {
        ACT_COMPILE,
        ACT_SCAN,
        ACT_TOKENIZE,
    } action = ACT_COMPILE;
    std::string filename = "";
    ParseType_t type = COMPILE_FULL;

    for (int i = 1; i < argc; i ++) {
        std::string arg(argv[i]);

        if (arg == "-h" || arg == "--help") {
            Usage(argv[0]);
        }

        if (arg == "scan") {
            action = ACT_SCAN;
            continue;
        }

        if (arg == "tokenize") {
            action = ACT_TOKENIZE;
            continue;
        }

        if (arg == "declarations" || arg == "types") {
            action = ACT_COMPILE;
            type = COMPILE_TYPES;
            continue;
        }

        if (arg == "expressions" || arg == "expr") {
            action = ACT_COMPILE;
            type = COMPILE_EXPRS;
            continue;
        }

        filename = arg;
    }

    // -- now, execute the requested main program step

    switch (action) {
    case ACT_SCAN:
        return Scan(filename);

    case ACT_TOKENIZE:
        return Tokenize(filename);

    default:
        return Compile(filename, type);
    }
}


