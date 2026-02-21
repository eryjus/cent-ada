/*=================================================================================================================*/
/*  scanner.ll -- The flex implementation of a tokenizer for the Ada compiler                                      */
/*                                                                                                                 */
/*        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md                                                   */
/*                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                 */
/*     Date      Tracker  Version  Pgmr  Description                                                               */
/*  -----------  -------  -------  ----  ------------------------------------------------------------------------- */
/*  2025-Dec-03  Initial   0.0.0   ADCL  Initial version                                                           */
/*                                                                                                                 */
/*=================================================================================================================*/


%option yylineno
%option noyywrap
%option caseless


/*
 * -- These lines are added into the top of the resulting C source file
 *    -----------------------------------------------------------------
 */
%{
    #include <string>
    #include <iostream>
    #include <variant>

    #define YY_DECL TokenType yylex(void)

    extern int column;
    extern std::string strVal;
    std::string ToLower(const char *s);

    #include "tokens.hh"
%}


LETTER      [a-z]
DIGIT       [0-9]
HEXDIGIT    [0-9a-f]
UNDERLINE   _
LF          (\n|\r|\n\r|\r\n|\v)
WS          [ \t]


%x          prg arg
%x          str


/*
 * -- This marks the end of the first definition specification
 *    --------------------------------------------------------
 */
%%

        /*
         * -- handle some separator characters
         *    --------------------------------
         */
{WS}        { column ++; }
{LF}        { column = 1; }
--.*        { column += strlen(yytext); }



        /*
         * -- handle the single character symbols
         *    -----------------------------------
         */
\"          { column ++; BEGIN(str); strVal = ""; }
&           { column ++; return TokenType::TOK_AMPERSAND; }
\(          { column ++; return TokenType::TOK_LEFT_PARENTHESIS; }
\)          { column ++; return TokenType::TOK_RIGHT_PARENTHESIS; }
\*          { column ++; return TokenType::TOK_STAR; }
\+          { column ++; return TokenType::TOK_PLUS; }
,           { column ++; return TokenType::TOK_COMMA; }
-           { column ++; return TokenType::TOK_HYPHEN; }
\.          { column ++; return TokenType::TOK_DOT; }
\/          { column ++; return TokenType::TOK_SLASH; }
\:          { column ++; return TokenType::TOK_COLON; }
;           { column ++; return TokenType::TOK_SEMICOLON; }
\<          { column ++; return TokenType::TOK_LESS_THAN; }
=           { column ++; return TokenType::TOK_EQUAL; }
\>          { column ++; return TokenType::TOK_GREATER_THAN; }
_           { column ++; return TokenType::TOK_UNDERLINE; }
\|          { column ++; return TokenType::TOK_VERTICAL_BAR; }
!           { column ++; return TokenType::TOK_EXCLAMATION_MARK; }
\$          { column ++; return TokenType::TOK_DOLLAR; }
\%          { column ++; return TokenType::TOK_PERCENT; }
\?          { column ++; return TokenType::TOK_QUESTION_MARK; }
\@          { column ++; return TokenType::TOK_COMMERCIAL_AT; }
\[          { column ++; return TokenType::TOK_LEFT_SQUARE_BRACKET; }
\\          { column ++; return TokenType::TOK_BACK_SLASH; }
\]          { column ++; return TokenType::TOK_RIGHT_SQUARE_BRACKET; }
\^          { column ++; return TokenType::TOK_CIRCUMFLEX; }
`           { column ++; return TokenType::TOK_GRAVE_ACCENT; }
\{          { column ++; return TokenType::TOK_LEFT_BRACE; }
\}          { column ++; return TokenType::TOK_RIGHT_BRACE; }
~           { column ++; return TokenType::TOK_TILDE; }


        /*
         * -- handle the compound symbols
         *    ---------------------------
         */
\=\>        { column += 2; return TokenType::TOK_ARROW; }
\.\.        { column += 2; return TokenType::TOK_DOUBLE_DOT; }
\*\*        { column += 2; return TokenType::TOK_DOUBLE_STAR; }
\:\=        { column += 2; return TokenType::TOK_ASSIGNMENT; }
\/\=        { column += 2; return TokenType::TOK_INEQUALITY; }
\>\=        { column += 2; return TokenType::TOK_GREATER_THAN_OR_EQUAL; }
\<\=        { column += 2; return TokenType::TOK_LESS_THAN_OR_EQUAL; }
\<\<        { column += 2; return TokenType::TOK_LEFT_LABEL_BRACKET; }
\>\>        { column += 2; return TokenType::TOK_RIGHT_LABEL_BRACKET; }
\<\>        { column += 2; return TokenType::TOK_BOX; }


        /*
        * -- handle keywords
        *    ---------------
        */
abort       { column += strlen(yytext); return TokenType::TOK_ABORT; }
abs         { column += strlen(yytext); return TokenType::TOK_ABS; }
accept      { column += strlen(yytext); return TokenType::TOK_ACCEPT; }
access      { column += strlen(yytext); return TokenType::TOK_ACCESS; }
all         { column += strlen(yytext); return TokenType::TOK_ALL; }
and         { column += strlen(yytext); return TokenType::TOK_AND; }
array       { column += strlen(yytext); return TokenType::TOK_ARRAY; }
at          { column += strlen(yytext); return TokenType::TOK_AT; }
begin       { column += strlen(yytext); return TokenType::TOK_BEGIN; }
body        { column += strlen(yytext); return TokenType::TOK_BODY; }
case        { column += strlen(yytext); return TokenType::TOK_CASE; }
constant    { column += strlen(yytext); return TokenType::TOK_CONSTANT; }
declare     { column += strlen(yytext); return TokenType::TOK_DECLARE; }
delay       { column += strlen(yytext); return TokenType::TOK_DELAY; }
delta       { column += strlen(yytext); return TokenType::TOK_DELTA; }
digits      { column += strlen(yytext); return TokenType::TOK_DIGITS; }
do          { column += strlen(yytext); return TokenType::TOK_DO; }
else        { column += strlen(yytext); return TokenType::TOK_ELSE; }
elsif       { column += strlen(yytext); return TokenType::TOK_ELSIF; }
end         { column += strlen(yytext); return TokenType::TOK_END; }
entry       { column += strlen(yytext); return TokenType::TOK_ENTRY; }
exception   { column += strlen(yytext); return TokenType::TOK_EXCEPTION; }
exit        { column += strlen(yytext); return TokenType::TOK_EXIT; }
for         { column += strlen(yytext); return TokenType::TOK_FOR; }
function    { column += strlen(yytext); return TokenType::TOK_FUNCTION; }
generic     { column += strlen(yytext); return TokenType::TOK_GENERIC; }
goto        { column += strlen(yytext); return TokenType::TOK_GOTO; }
if          { column += strlen(yytext); return TokenType::TOK_IF; }
in          { column += strlen(yytext); return TokenType::TOK_IN; }
is          { column += strlen(yytext); return TokenType::TOK_IS; }
limited     { column += strlen(yytext); return TokenType::TOK_LIMITED; }
loop        { column += strlen(yytext); return TokenType::TOK_LOOP; }
mod         { column += strlen(yytext); return TokenType::TOK_MOD; }
new         { column += strlen(yytext); return TokenType::TOK_NEW; }
not         { column += strlen(yytext); return TokenType::TOK_NOT; }
null        { column += strlen(yytext); return TokenType::TOK_NULL; }
of          { column += strlen(yytext); return TokenType::TOK_OF; }
or          { column += strlen(yytext); return TokenType::TOK_OR; }
others      { column += strlen(yytext); return TokenType::TOK_OTHERS; }
out         { column += strlen(yytext); return TokenType::TOK_OUT; }
package     { column += strlen(yytext); return TokenType::TOK_PACKAGE; }
pragma      { column += strlen(yytext); BEGIN(prg); return TokenType::TOK_PRAGMA; }
private     { column += strlen(yytext); return TokenType::TOK_PRIVATE; }
procedure   { column += strlen(yytext); return TokenType::TOK_PROCEDURE; }
raise       { column += strlen(yytext); return TokenType::TOK_RAISE; }
range       { column += strlen(yytext); return TokenType::TOK_RANGE; }
record      { column += strlen(yytext); return TokenType::TOK_RECORD; }
rem         { column += strlen(yytext); return TokenType::TOK_REM; }
renames     { column += strlen(yytext); return TokenType::TOK_RENAMES; }
return      { column += strlen(yytext); return TokenType::TOK_RETURN; }
reverse     { column += strlen(yytext); return TokenType::TOK_REVERSE; }
select      { column += strlen(yytext); return TokenType::TOK_SELECT; }
separate    { column += strlen(yytext); return TokenType::TOK_SEPARATE; }
subtype     { column += strlen(yytext); return TokenType::TOK_SUBTYPE; }
task        { column += strlen(yytext); return TokenType::TOK_TASK; }
terminate   { column += strlen(yytext); return TokenType::TOK_TERMINATE; }
then        { column += strlen(yytext); return TokenType::TOK_THEN; }
type        { column += strlen(yytext); return TokenType::TOK_TYPE; }
use         { column += strlen(yytext); return TokenType::TOK_USE; }
when        { column += strlen(yytext); return TokenType::TOK_WHEN; }
while       { column += strlen(yytext); return TokenType::TOK_WHILE; }
with        { column += strlen(yytext); return TokenType::TOK_WITH; }
xor         { column += strlen(yytext); return TokenType::TOK_XOR; }



        /*
         * -- handle other identifiers which are not keywords
         *    -----------------------------------------------
         */
{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = IdentifierLexeme { lower };
                return TokenType::TOK_IDENTIFIER;
            }



        /*
         * -- These rules will handle all universal integer literals
         *    ------------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }



        /*
         * -- These rules will handle all universal real literals
         *    ---------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }



        /*
         * -- Handle a character literal
         *    --------------------------
         */
\'.\'       {
                column += strlen(yytext);
                yylval = CharLiteral { std::string(yytext), yytext[1] };
                return TokenType::TOK_CHARACTER_LITERAL;
            }



        /*
         * -- Handle a string literal
         *    -----------------------
         */
<str>\"     { column ++; BEGIN(INITIAL); yylval = StringLiteral { strVal }; return TokenType::TOK_STRING_LITERAL; }
<str>{LF}   { column = 0; BEGIN(INITIAL); yylval = StringLiteral { strVal }; return TokenType::TOK_ERROR; }
<str>\"\"   { column += 2; strVal += '"'; }
<str>.      { column ++; strVal += yytext[0]; }



        /*
         * -- determine which pragma name we are parsing and its args
         *    -------------------------------------------------------
         */
<prg>{WS}   { column ++; }
<prg>{LF}   { column = 0; BEGIN(INITIAL); return TokenType::TOK_ERROR; }
<prg>{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                BEGIN(arg);
                return TokenType::TOK_PRAGMA_NAME;
            }
<prg>.      { column ++; BEGIN(INITIAL); return TokenType::TOK_ERROR; }

<arg>{WS}   { column ++; }
<arg>;      { column ++; BEGIN(INITIAL); return TokenType::TOK_SEMICOLON; }
<arg>\(     { column ++; return TokenType::TOK_LEFT_PARENTHESIS; }
<arg>\)     { column ++; BEGIN(INITIAL); return TokenType::TOK_RIGHT_PARENTHESIS; }
<arg>,      { column ++; return TokenType::TOK_COMMA; }
<arg>\=\>   { column += 2; return TokenType::TOK_ARROW; }
<arg>{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = IdentifierLexeme { lower };
                return TokenType::TOK_IDENTIFIER;
            }
<arg>.      { column ++; BEGIN(INITIAL); return TokenType::TOK_ERROR; }



        /*
         * -- Handle EOF
         *    ----------
         */
<*><<EOF>>  { return TokenType::YYEOF; }
'           { column ++; return TokenType::TOK_APOSTROPHE; }
#           { column ++; return TokenType::TOK_SHARP; }
.           { column ++; return TokenType::TOK_ERROR; }


%%

std::string strVal;
YYSTYPE yylval;




std::string ToLower(const char *s)
{
    std::string rv;

    for (int i = 0; i < strlen(s); i ++) {
        rv.push_back(s[i] >= 'A' && s[i] <= 'Z' ? s[i] - 'A' + 'a' : s[i]);
    }

    return rv;
}
