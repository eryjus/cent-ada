//=================================================================================================================
//  tstream.hh -- This header defines the stream of tokens, and operations which can happen on it.
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



//
// -- This include clears up the syntax highlighter issues
//    ----------------------------------------------------
#include "ada.hh"



//
// -- This structure is the location of the token in the source file
//    --------------------------------------------------------------
using SourceLoc_t = struct SourceLoc_t {
    std::string filename;
    long line;
    int col;
    std::string sourceLine;
    bool valid;
};



//
// -- This is the stream of tokens organized as a vector table so the parser can look ahead
//    -------------------------------------------------------------------------------------
class TokenStream {
private:
    using Token = struct Token {
    public:
        std::string &filename;
        int yylineno;
        int column;
        TokenType_t tok;
        YYSTYPE payload;

    public:
        Token(std::string &f, int l, int c, TokenType_t t, YYSTYPE &p)
                : filename(f), yylineno(l), column(c), tok(t), payload(p) {}
    };


private:
    std::vector<Token *> tokStream;
    int loc;
    std::string filename;
    std::vector<std::string> source;
    bool sourceValid;


public:
    const char *tokenStr(int tok) const;

public:
    TokenStream(const char *fn);

public:
    void Advance(int n = 1) { loc += n; }
    TokenType_t Current(void) const { return tokStream[loc]->tok; }
    YYSTYPE &Payload(void) const { return tokStream[loc]->payload; }
    TokenType_t Peek(int n = 1) { return tokStream[loc + n]->tok; }
    std::string FileName(void) const { return filename; }
    long LineNo(void) const { return tokStream[loc]->yylineno; }
    int Column(void) const { return tokStream[loc]->column; }
    void Recovery(TokenType_t t = TOK_SEMICOLON) { while (Current() != t) { Advance(); } Advance(); }
    void Reset(int nLoc) { loc = nLoc; }
    int Location(void) const { return loc; }
    void Listing(void);
    void List(void);
    SourceLoc_t SourceLocation(void);
    static SourceLoc_t EmptyLocation(void);


public:
//    std::string &GetErrMsg(void) const { return *(tokStream[loc]->payload.errMsg); }
};




