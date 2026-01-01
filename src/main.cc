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
using ParseType_t = enum {
    COMPILE_FULL,
    COMPILE_TYPES,
    COMPILE_EXPRS,
};



//
// -- The global token stream used for scanning
//    -----------------------------------------
TokenStream *tokens = nullptr;



//
// -- Global options
//    --------------
Options opts;



//
// -- Scan the input for testing purposes
//    -----------------------------------
static int Scan(std::string filename)
{
    extern char *yytext;
    extern TokenType yylex(void);
    extern FILE *yyin;

    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        std::cerr << "Unable to open file " << filename << '\n';
        return EXIT_FAILURE;
    }

    TokenType tok = yylex();

    while ((int)tok) {
        switch (tok) {
        case TokenType::TOK_QUOTATION:             std::cout << "\"\n";        break;
        case TokenType::TOK_SHARP:                 std::cout << "#\n";         break;
        case TokenType::TOK_AMPERSAND:             std::cout << "&\n";         break;
        case TokenType::TOK_APOSTROPHE:            std::cout << "'\n";         break;
        case TokenType::TOK_LEFT_PARENTHESIS:      std::cout << "(\n";         break;
        case TokenType::TOK_RIGHT_PARENTHESIS:     std::cout << ")\n";         break;
        case TokenType::TOK_STAR:                  std::cout << "*\n";         break;
        case TokenType::TOK_PLUS:                  std::cout << "+\n";         break;
        case TokenType::TOK_COMMA:                 std::cout << ",\n";         break;
        case TokenType::TOK_HYPHEN:                std::cout << "-\n";         break;
        case TokenType::TOK_DOT:                   std::cout << ".\n";         break;
        case TokenType::TOK_SLASH:                 std::cout << "/\n";         break;
        case TokenType::TOK_COLON:                 std::cout << ":\n";         break;
        case TokenType::TOK_SEMICOLON:             std::cout << ";\n";         break;
        case TokenType::TOK_LESS_THAN:             std::cout << "<\n";         break;
        case TokenType::TOK_EQUAL:                 std::cout << "=\n";         break;
        case TokenType::TOK_GREATER_THAN:          std::cout << ">\n";         break;
        case TokenType::TOK_UNDERLINE:             std::cout << "_\n";         break;
        case TokenType::TOK_VERTICAL_BAR:          std::cout << "|\n";         break;
        case TokenType::TOK_EXCLAMATION_MARK:      std::cout << "!\n";         break;
        case TokenType::TOK_DOLLAR:                std::cout << "$\n";         break;
        case TokenType::TOK_PERCENT:               std::cout << "%\n";         break;
        case TokenType::TOK_QUESTION_MARK:         std::cout << "?\n";         break;
        case TokenType::TOK_COMMERCIAL_AT:         std::cout << "@\n";         break;
        case TokenType::TOK_LEFT_SQUARE_BRACKET:   std::cout << "[\n";         break;
        case TokenType::TOK_BACK_SLASH:            std::cout << "\\\n";        break;
        case TokenType::TOK_RIGHT_SQUARE_BRACKET:  std::cout << "]\n";         break;
        case TokenType::TOK_CIRCUMFLEX:            std::cout << "^\n";         break;
        case TokenType::TOK_GRAVE_ACCENT:          std::cout << "`\n";         break;
        case TokenType::TOK_LEFT_BRACE:            std::cout << "{\n";         break;
        case TokenType::TOK_RIGHT_BRACE:           std::cout << "}\n";         break;
        case TokenType::TOK_TILDE:                 std::cout << "~\n";         break;

        case TokenType::TOK_ARROW:                 std::cout << "=>\n";        break;
        case TokenType::TOK_DOUBLE_DOT:            std::cout << "..\n";        break;
        case TokenType::TOK_DOUBLE_STAR:           std::cout << "**\n";        break;
        case TokenType::TOK_ASSIGNMENT:            std::cout << ":=\n";        break;
        case TokenType::TOK_INEQUALITY:            std::cout << "/=\n";        break;
        case TokenType::TOK_GREATER_THAN_OR_EQUAL: std::cout << ">=\n";        break;
        case TokenType::TOK_LESS_THAN_OR_EQUAL:    std::cout << "<=\n";        break;
        case TokenType::TOK_LEFT_LABEL_BRACKET:    std::cout << "<<\n";        break;
        case TokenType::TOK_RIGHT_LABEL_BRACKET:   std::cout << ">>\n";        break;
        case TokenType::TOK_BOX:                   std::cout << "<>\n";        break;

        case TokenType::TOK_ABORT:                 std::cout << "ABORT\n";     break;
        case TokenType::TOK_ABS:                   std::cout << "ABS\n";       break;
        case TokenType::TOK_ACCEPT:                std::cout << "ACCEPT\n";    break;
        case TokenType::TOK_ACCESS:                std::cout << "ACCESS\n";    break;
        case TokenType::TOK_ALL:                   std::cout << "ALL\n";       break;
        case TokenType::TOK_AND:                   std::cout << "AND\n";       break;
        case TokenType::TOK_ARRAY:                 std::cout << "ARRAY\n";     break;
        case TokenType::TOK_AT:                    std::cout << "AT\n";        break;
        case TokenType::TOK_BEGIN:                 std::cout << "BEGIN\n";     break;
        case TokenType::TOK_BODY:                  std::cout << "BODY\n";      break;
        case TokenType::TOK_CASE:                  std::cout << "CASE\n";      break;
        case TokenType::TOK_CONSTANT:              std::cout << "CONSTANT\n";  break;
        case TokenType::TOK_DECLARE:               std::cout << "DECLARE\n";   break;
        case TokenType::TOK_DELAY:                 std::cout << "DELAY\n";     break;
        case TokenType::TOK_DELTA:                 std::cout << "DELTA\n";     break;
        case TokenType::TOK_DIGITS:                std::cout << "DIGITS\n";    break;
        case TokenType::TOK_DO:                    std::cout << "DO\n";        break;
        case TokenType::TOK_ELSE:                  std::cout << "ELSE\n";      break;
        case TokenType::TOK_ELSIF:                 std::cout << "ELSIF\n";     break;
        case TokenType::TOK_END:                   std::cout << "END\n";       break;
        case TokenType::TOK_ENTRY:                 std::cout << "ENTRY\n";     break;
        case TokenType::TOK_EXCEPTION:             std::cout << "EXCEPTION\n"; break;
        case TokenType::TOK_EXIT:                  std::cout << "EXIT\n";      break;
        case TokenType::TOK_FOR:                   std::cout << "FOR\n";       break;
        case TokenType::TOK_FUNCTION:              std::cout << "FUNCTION\n";  break;
        case TokenType::TOK_GENERIC:               std::cout << "GENERIC\n";   break;
        case TokenType::TOK_GOTO:                  std::cout << "GOTO\n";      break;
        case TokenType::TOK_IF:                    std::cout << "IF\n";        break;
        case TokenType::TOK_IN:                    std::cout << "IN\n";        break;
        case TokenType::TOK_IS:                    std::cout << "IS\n";        break;
        case TokenType::TOK_LIMITED:               std::cout << "LIMITED\n";   break;
        case TokenType::TOK_LOOP:                  std::cout << "LOOP\n";      break;
        case TokenType::TOK_MOD:                   std::cout << "MOD\n";       break;
        case TokenType::TOK_NEW:                   std::cout << "NEW\n";       break;
        case TokenType::TOK_NOT:                   std::cout << "NOT\n";       break;
        case TokenType::TOK_NULL:                  std::cout << "NULL\n";      break;
        case TokenType::TOK_OF:                    std::cout << "OF\n";        break;
        case TokenType::TOK_OR:                    std::cout << "OR\n";        break;
        case TokenType::TOK_OTHERS:                std::cout << "OTHERS\n";    break;
        case TokenType::TOK_OUT:                   std::cout << "OUT\n";       break;
        case TokenType::TOK_PACKAGE:               std::cout << "PACKAGE\n";   break;
        case TokenType::TOK_PRAGMA:                std::cout << "PRAGMA\n";    break;
        case TokenType::TOK_PRIVATE:               std::cout << "PRIVATE\n";   break;
        case TokenType::TOK_PROCEDURE:             std::cout << "PROCEDURE\n"; break;
        case TokenType::TOK_RAISE:                 std::cout << "RAISE\n";     break;
        case TokenType::TOK_RANGE:                 std::cout << "RANGE\n";     break;
        case TokenType::TOK_RECORD:                std::cout << "RECORD\n";    break;
        case TokenType::TOK_REM:                   std::cout << "REM\n";       break;
        case TokenType::TOK_RENAMES:               std::cout << "RENAMES\n";   break;
        case TokenType::TOK_RETURN:                std::cout << "RETURN\n";    break;
        case TokenType::TOK_REVERSE:               std::cout << "REVERSE\n";   break;
        case TokenType::TOK_SELECT:                std::cout << "SELECT\n";    break;
        case TokenType::TOK_SEPARATE:              std::cout << "SEPARATE\n";  break;
        case TokenType::TOK_SUBTYPE:               std::cout << "SUBTYPE\n";   break;
        case TokenType::TOK_TASK:                  std::cout << "TASK\n";      break;
        case TokenType::TOK_TERMINATE:             std::cout << "TERMINATE\n"; break;
        case TokenType::TOK_THEN:                  std::cout << "THEN\n";      break;
        case TokenType::TOK_TYPE:                  std::cout << "TYPE\n";      break;
        case TokenType::TOK_USE:                   std::cout << "USE\n";       break;
        case TokenType::TOK_WHEN:                  std::cout << "WHEN\n";      break;
        case TokenType::TOK_WHILE:                 std::cout << "WHILE\n";     break;
        case TokenType::TOK_WITH:                  std::cout << "WITH\n";      break;
        case TokenType::TOK_XOR:                   std::cout << "XOR\n";       break;
        case TokenType::TOK_AND_THEN:              std::cout << "AND THEN\n";  break;
        case TokenType::TOK_OR_ELSE:               std::cout << "OR ELSE\n";   break;

        case TokenType::TOK_IDENTIFIER:
            std::cout << "IDENTIFIER: (" << yytext << ")\n";
            break;

        case TokenType::TOK_UNIVERSAL_INT_LITERAL:
            std::cout << "INTEGER LITERAL: (" << yytext << ")\n";
            break;

        case TokenType::TOK_UNIVERSAL_REAL_LITERAL:
            std::cout << "REAL LITERAL: (" << yytext << ")\n";
            break;

        case TokenType::TOK_CHARACTER_LITERAL:
            std::cout << "CHARACTER LITERAL: (" << yytext[1] << ")\n";
            break;

        case TokenType::TOK_STRING_LITERAL:
            std::cout << "STRING LITERAL: (" << strVal << ")\n";
            break;

        case TokenType::TOK_PRAGMA_NAME:
            std::cout << "PRAGMA DIRECTIVE: " << yytext << '\n';
            break;

        case TokenType::TOK_ERROR:
            std::cout << "ERROR\n";
            break;

        default:
            std::cerr << "Unknown Token Type: " << (int)tok << '\n'; break;
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
    int cnt = 0;
    int rv = EXIT_SUCCESS;

    switch (type) {
    case COMPILE_TYPES:
        while (tokens->Current() != TokenType::YYEOF) {
            if(!parser->ParseBasicDeclaration()) {
                std::cerr << "\e[31;1mERROR: Unable to properly parse Basic Declaration\e[0m\n";
                rv = EXIT_FAILURE;
                goto exit;
            } else {
//                std::cerr << "Completed a Declaration\n";
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
            std::cerr << "\n\e[31;1mERROR: Unable to properly parse Expression\e[0m\n";
            rv = EXIT_FAILURE;
            goto exit;
        }

        std::cerr << "next token " << tokens->tokenStr(tokens->Current()) << '\n';
        if (tokens->Current() != TokenType::YYEOF) {
            std::cerr << "\n\e[31;1mERROR: Extra input in Expression parse\e[0m\n";
            rv = EXIT_FAILURE;
            goto exit;
        }

        break;


    default:
        break;
    }

    std::cerr << "Parse Complete.\n";

exit:
    if (opts.listing) tokens->Listing();
    if (opts.dumpSymtab) parser->Scopes()->Print();

    std::cerr << "   Errors  : " << diags.Errors() << '\n';
    std::cerr << "   Warnings: " << diags.Warnings() << '\n';

    if (diags.Errors() > 0) rv = EXIT_FAILURE;

    return rv;
}



//
// -- Print the help message and exit
//    -------------------------------
static void Usage(std::string pgm)
{
    std::cout << "Usage: " << pgm << "  command [options] [file]\n";

    std::cout << "  where 'command' is one of:\n";
    std::cout << "      scan            scan the file and normalize what is read\n";
    std::cout << "      tokenize        read the file into a token stream and output\n";
    std::cout << "                      the token stream and the source listing\n";
    std::cout << "      declarations, types\n";
    std::cout << "                      process only declarations parts of the parser\n";
    std::cout << "      expressions, expr\n";
    std::cout << "                      process only expressions/declarations parts of the parser\n";
    std::cout << "\n";
    std::cout << "  options:\n";
    std::cout << "  -h, --help          print this screen and exit\n";
    std::cout << "  -t, --trace         output production tracing\n";
    std::cout << "      --dump-symtab   dump the symbol table contents before exiting\n";
    std::cout << "      --listing       produce a listing before exiting\n";
    std::cout << "\n";

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

        if (arg == "--trace" || arg == "-t") {
            opts.trace = true;
            continue;
        }

        if (arg == "--dump-symtab") {
            opts.dumpSymtab = true;
            continue;
        }

        if (arg == "--listing") {
            opts.listing = true;
            continue;
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
            opts.requireBasicDeclaration = true;
            continue;
        }

        if (arg == "expressions" || arg == "expr") {
            action = ACT_COMPILE;
            type = COMPILE_EXPRS;
            opts.requireBasicDeclaration = true;
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


