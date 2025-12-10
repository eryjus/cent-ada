//=================================================================================================================
//  tstream.cc -- Implementation of the token stream
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-05  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- This is used by the scanner to save additional info for a token
//    ---------------------------------------------------------------
int column = 1;



//
// -- Construct the token stream.  This is done by scanning the entire file and
//    turning each token into an element in the vector table.
//    -------------------------------------------------------------------------
TokenStream::TokenStream(const char *fn) : filename(fn?fn:"stdin"), loc(0)
{
    extern int yylex(void);
    extern FILE *yyin;
    extern YYSTYPE yylval;
    extern int yylineno;

    yyin = nullptr;
    yylineno = 0;           // set to 0 to make everything happy!
    column = 1;

    if (fn) yyin = fopen(fn, "r");

    if (!yyin) {
        std::cerr << "Unable to open file; using stdin.\n";
        std::cerr << "   Ctrl-c to stop; Ctrl-d for EOF\n";
        yyin = stdin;
        sourceValid = false;
    } else {
        static char buf[2048];
        while (fgets(buf, 2048, yyin)) {
            source.push_back(std::string(buf));
        }

        fseek(yyin, 0, SEEK_SET);
        sourceValid = true;
    }

    int tok = yylex();
    while (tok) {
        Token *t = new Token(filename, yylineno, column, (TokenType_t)tok);
        tokStream.push_back(t);

        tok = yylex();
    }


    //
    // -- add an EOF marker so that we can query it
    //    -----------------------------------------
    tokStream.push_back(new Token(filename, source.size(), 0, (TokenType_t)EOF));

    fclose(yyin);
}



//
// -- Perform a token lookup for the description
//    ------------------------------------------
const char *TokenStream::tokenStr(int tok) const
{
    const char *str[] = {
        "YYerror",                         // 256
        "YYUNDEF",                         // 257
        "TOK_QUOTATION",                   // 258
        "TOK_SHARP",                       // 259
        "TOK_AMPERSAND",                   // 260
        "TOK_APOSTROPHE",                  // 261
        "TOK_LEFT_PARENTHESIS",            // 262
        "TOK_RIGHT_PARENTHESIS",           // 263
        "TOK_STAR",                        // 264
        "TOK_MULTIPLY",                    // 265
        "TOK_PLUS",                        // 266
        "TOK_COMMA",                       // 267
        "TOK_HYPHEN",                      // 268
        "TOK_MINUS",                       // 269
        "TOK_DOT",                         // 270
        "TOK_POINT",                       // 271
        "TOK_PERIOD",                      // 272
        "TOK_SLASH",                       // 273
        "TOK_DIVIDE",                      // 274
        "TOK_COLON",                       // 275
        "TOK_SEMICOLON",                   // 276
        "TOK_LESS_THAN",                   // 277
        "TOK_EQUAL",                       // 278
        "TOK_GREATER_THAN",                // 279
        "TOK_UNDERLINE",                   // 280
        "TOK_VERTICAL_BAR",                // 281
        "TOK_EXCLAMATION_MARK",            // 282
        "TOK_DOLLAR",                      // 283
        "TOK_PERCENT",                     // 284
        "TOK_QUESTION_MARK",               // 285
        "TOK_COMMERCIAL_AT",               // 286
        "TOK_LEFT_SQUARE_BRACKET",         // 287
        "TOK_BACK_SLASH",                  // 288
        "TOK_RIGHT_SQUARE_BRACKET",        // 289
        "TOK_CIRCUMFLEX",                  // 290
        "TOK_GRAVE_ACCENT",                // 291
        "TOK_LEFT_BRACE",                  // 292
        "TOK_RIGHT_BRACE",                 // 293
        "TOK_TILDE",                       // 294
        "TOK_ARROW",                       // 295
        "TOK_DOUBLE_DOT",                  // 296
        "TOK_DOUBLE_STAR",                 // 297
        "TOK_EXPONENTIATE",                // 298
        "TOK_ASSIGNMENT",                  // 299
        "TOK_INEQUALITY",                  // 300
        "TOK_GREATER_THAN_OR_EQUAL",       // 301
        "TOK_LESS_THAN_OR_EQUAL",          // 302
        "TOK_LEFT_LABEL_BRACKET",          // 303
        "TOK_RIGHT_LABEL_BRACKET",         // 304
        "TOK_BOX",                         // 305
        "TOK_ABORT",                       // 306
        "TOK_ABS",                         // 307
        "TOK_ACCEPT",                      // 308
        "TOK_ACCESS",                      // 309
        "TOK_ALL",                         // 310
        "TOK_AND",                         // 311
        "TOK_ARRAY",                       // 312
        "TOK_AT",                          // 313
        "TOK_BEGIN",                       // 314
        "TOK_BODY",                        // 315
        "TOK_CASE",                        // 316
        "TOK_CONSTANT",                    // 317
        "TOK_DECLARE",                     // 318
        "TOK_DELAY",                       // 319
        "TOK_DELTA",                       // 320
        "TOK_DIGITS",                      // 321
        "TOK_DO",                          // 322
        "TOK_ELSE",                        // 323
        "TOK_ELSIF",                       // 324
        "TOK_END",                         // 325
        "TOK_ENTRY",                       // 326
        "TOK_EXCEPTION",                   // 327
        "TOK_EXIT",                        // 328
        "TOK_FOR",                         // 329
        "TOK_FUNCTION",                    // 330
        "TOK_GENERIC",                     // 331
        "TOK_GOTO",                        // 332
        "TOK_IF",                          // 333
        "TOK_IN",                          // 334
        "TOK_IS",                          // 335
        "TOK_LIMITED",                     // 336
        "TOK_LOOP",                        // 337
        "TOK_MOD",                         // 338
        "TOK_NEW",                         // 339
        "TOK_NOT",                         // 340
        "TOK_NULL",                        // 341
        "TOK_OF",                          // 342
        "TOK_OR",                          // 343
        "TOK_OTHERS",                      // 344
        "TOK_OUT",                         // 345
        "TOK_PACKAGE",                     // 346
        "TOK_PRAGMA",                      // 347
        "TOK_PRIVATE",                     // 348
        "TOK_PROCEDURE",                   // 349
        "TOK_RAISE",                       // 350
        "TOK_RANGE",                       // 351
        "TOK_RECORD",                      // 352
        "TOK_REM",                         // 353
        "TOK_RENAMES",                     // 354
        "TOK_RETURN",                      // 355
        "TOK_REVERSE",                     // 356
        "TOK_SELECT",                      // 357
        "TOK_SEPARATE",                    // 358
        "TOK_SUBTYPE",                     // 359
        "TOK_TASK",                        // 360
        "TOK_TERMINATE",                   // 361
        "TOK_THEN",                        // 362
        "TOK_TYPE",                        // 363
        "TOK_USE",                         // 364
        "TOK_WHEN",                        // 365
        "TOK_WHILE",                       // 366
        "TOK_WITH",                        // 367
        "TOK_XOR",                         // 368
        "TOK_IDENTIFIER",                  // 369
        "TOK_UNIVERSAL_INT_LITERAL",       // 370
        "TOK_UNIVERSAL_REAL_LITERAL",      // 371
        "TOK_CHARACTER_LITERAL",           // 372
        "TOK_STRING_LITERAL",              // 373
        "TOK_PRAGMA_NAME",                 // 374
        "TOK_ERROR",                       // 375
    };

    if ((int)tok >= TOK_ERROR) return "UNKNOWN";

    return str[tok - 256];
}



//
// -- Create a listing
//    ----------------
void TokenStream::Listing(void)
{
    const char *line = "============================================================================================";

    std::cout << "Listing for " << filename << ":\n";
    std::cout << std::string(line).substr(0, filename.length() + 13) << '\n';

    for (int i = 0; i < source.size(); i ++) {
        std::cout << std::setw(6) << i + 1 << "   " << source[i];
    }

    std::cout << "\n\n";
}



//
// -- List the tokens in the stream
//    -----------------------------
void TokenStream::List(void)
{
    const char *line = "============================================================================================";

    std::cout << "Token Stream for " << filename << ":\n";
    std::cout << std::string(line).substr(0, filename.length() + 18) << '\n';
    Reset();

    while (Current() != YYEOF) {
        std::cout << std::setw(8) << loc + 1;
        std::cout << "  (" << std::setw(6) << LineNo() << ',' << std::setw(3) << Column() << ")  ";
        std::cout << Current() << " : " << tokenStr(Current()) << '\n';
        Advance();
    }

    std::cout << "\n\n";
}


