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
// -- This is the stream of tokens organized as a vector table so the parser can look ahead
//    -------------------------------------------------------------------------------------
class TokenStream {
private:
    typedef struct Token {
    public:
        std::string &filename;
        int yylineno;
        int column;
        TokenType_t tok;

    public:
        Token(std::string &f, int l, int c, TokenType_t t)
                : filename(f), yylineno(l), column(c), tok(t) {}
    } Token_t;


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
    TokenType_t Peek(int n = 1) { return tokStream[loc + n]->tok; }
    std::string FileName(void) const { return filename; }
    long LineNo(void) const { return tokStream[loc]->yylineno; }
    int Column(void) const { return tokStream[loc]->column; }
    void Recovery(TokenType_t t = TOK_SEMICOLON) { while (Current() != t) { Advance(); } Advance(); }
    void Reset(void) { loc = 0; }
    void Listing(void);
    void List(void);


public:
//    std::string &GetErrMsg(void) const { return *(tokStream[loc]->payload.errMsg); }
};




