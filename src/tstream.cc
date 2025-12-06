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
yystype_t yylval;
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
        Token *t = new Token(filename, yylineno, column, (TokenType_t)tok, yylval);
        tokStream.push_back(t);

        tok = yylex();
    }


    //
    // -- add an EOF marker so that we can query it
    //    -----------------------------------------
    tokStream.push_back(new Token(filename, source.size(), 0, (TokenType_t)YYEOF, yylval));

    fclose(yyin);
}



//
// -- Perform a token lookup for the description
//    ------------------------------------------
const char *TokenStream::tokenStr(int tok) const
{
    const char *str[] = {
        "",                                 // 256
        "TOK_QUOTATION",                    // 257
        "TOK_SHARP",                        // 258
        "TOK_AMPERSAND",                    // 259
        "TOK_APOSTROPHE",                   // 260
        "TOK_LEFT_PARENTHESIS",             // 261
        "TOK_RIGHT_PARENTHESIS",            // 262
        "TOK_STAR",                         // 263
        "TOK_PLUS",                         // 264
        "TOK_COMMA",                        // 265
        "TOK_HYPHEN",                       // 266
        "TOK_DOT",                          // 267
        "TOK_SLASH",                        // 268
        "TOK_COLON",                        // 269
        "TOK_SEMICOLON",                    // 270
        "TOK_LESS_THAN",                    // 271
        "TOK_EQUAL",                        // 272
        "TOK_GREATER_THAN",                 // 273
        "TOK_UNDERLINE",                    // 274
        "TOK_VERTICAL_BAR",                 // 275
        "TOK_EXCLAMATION_MARK",             // 276
        "TOK_DOLLAR",                       // 277
        "TOK_PERCENT",                      // 278
        "TOK_QUESTION_MARK",                // 279
        "TOK_COMMERCIAL_AT",                // 280
        "TOK_LEFT_SQUARE_BRACKET",          // 281
        "TOK_BACK_SLASH",                   // 282
        "TOK_RIGHT_SQUARE_BRACKET",         // 283
        "TOK_CIRCUMFLEX",                   // 284
        "TOK_GRAVE_ACCENT",                 // 285
        "TOK_LEFT_BRACE",                   // 286
        "TOK_RIGHT_BRACE",                  // 287
        "TOK_TILDE",                        // 288
        "",                                 // 289
        "TOK_ARROW",                        // 290
        "TOK_DOUBLE_DOT",                   // 291
        "TOK_DOUBLE_STAR",                  // 292
        "TOK_ASSIGNMENT",                   // 293
        "TOK_INEQUALITY",                   // 294
        "TOK_GREATER_THAN_OR_EQUAL",        // 295
        "TOK_LESS_THAN_OR_EQUAL",           // 296
        "TOK_LEFT_LABEL_BRACKET",           // 297
        "TOK_RIGHT_LABEL_BRACKET",          // 298
        "TOK_BOX",                          // 299
        "",                                 // 300
        "",                                 // 301
        "",                                 // 302
        "",                                 // 303
        "",                                 // 304
        "",                                 // 305
        "",                                 // 306
        "",                                 // 307
        "",                                 // 308
        "",                                 // 309
        "",                                 // 310
        "",                                 // 311
        "",                                 // 312
        "",                                 // 313
        "",                                 // 314
        "",                                 // 315
        "",                                 // 316
        "",                                 // 317
        "",                                 // 318
        "",                                 // 319
        "TOK_ABORT",                        // 320
        "TOK_ABS",                          // 321
        "TOK_ACCEPT",                       // 322
        "TOK_ACCESS",                       // 323
        "TOK_ALL",                          // 324
        "TOK_AND",                          // 325
        "TOK_ARRAY",                        // 326
        "TOK_AT",                           // 327
        "TOK_BEGIN",                        // 328
        "TOK_BODY",                         // 329
        "TOK_CASE",                         // 330
        "TOK_CONSTANT",                     // 331
        "TOK_DECLARE",                      // 332
        "TOK_DELAY",                        // 333
        "TOK_DELTA",                        // 334
        "TOK_DIGITS",                       // 335
        "TOK_DO",                           // 336
        "TOK_ELSE",                         // 337
        "TOK_ELSIF",                        // 338
        "TOK_END",                          // 339
        "TOK_ENTRY",                        // 340
        "TOK_EXCEPTION",                    // 341
        "TOK_EXIT",                         // 342
        "TOK_FOR",                          // 343
        "TOK_FUNCTION",                     // 344
        "TOK_GENERIC",                      // 345
        "TOK_GOTO",                         // 346
        "TOK_IF",                           // 347
        "TOK_IN",                           // 348
        "TOK_IS",                           // 349
        "TOK_LIMITED",                      // 350
        "TOK_LOOP",                         // 351
        "TOK_MOD",                          // 352
        "TOK_NEW",                          // 353
        "TOK_NOT",                          // 354
        "TOK_NULL",                         // 355
        "TOK_OF",                           // 356
        "TOK_OR",                           // 357
        "TOK_OTHERS",                       // 358
        "TOK_OUT",                          // 359
        "TOK_PACKAGE",                      // 360
        "TOK_PRAGMA",                       // 361
        "TOK_PRIVATE",                      // 362
        "TOK_PROCEDURE",                    // 363
        "TOK_RAISE",                        // 364
        "TOK_RANGE",                        // 365
        "TOK_RECORD",                       // 366
        "TOK_REM",                          // 367
        "TOK_RENAMES",                      // 368
        "TOK_RETURN",                       // 369
        "TOK_REVERSE",                      // 370
        "TOK_SELECT",                       // 371
        "TOK_SEPARATE",                     // 372
        "TOK_SUBTYPE",                      // 373
        "TOK_TASK",                         // 374
        "TOK_TERMINATE",                    // 375
        "TOK_THEN",                         // 376
        "TOK_TYPE",                         // 377
        "TOK_USE",                          // 378
        "TOK_WHEN",                         // 379
        "TOK_WHILE",                        // 380
        "TOK_WITH",                         // 381
        "TOK_XOR",                          // 382
        "",                                 // 383
        "",                                 // 384
        "",                                 // 385
        "",                                 // 386
        "",                                 // 387
        "",                                 // 388
        "",                                 // 389
        "TOK_IDENTIFIER",                   // 390
        "TOK_UNIVERSAL_INT_LITERAL",        // 391
        "TOK_UNIVERSAL_REAL_LITERAL",       // 392
        "TOK_CHARACTER_LITERAL",            // 393
        "TOK_STRING_LITERAL",               // 394
        "",                                 // 395
        "",                                 // 396
        "",                                 // 397
        "",                                 // 398
        "",                                 // 399
    };

    if (tok == YYEOF) return "YYEOF";
    if (tok == TOK_ERROR) return "TOK_ERROR";
    if (tok == TOK_PRAGMA_NAME) return "TOK_PRAGMA_NAME";
    if ((int)tok >= 400) return "UNKNOWN";

    return str[tok - DUMMY_FIRST_TOKEN];
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


