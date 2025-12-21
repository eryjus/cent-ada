/*=================================================================================================================*/
/*  scanner.ll -- The flex implementation of a tokenizer for the Ada compiler                                      */
/*                                                                                                                 */
/*        Copyright (c)  2025      -- Adam Clark; See LICENSE.md                                                   */
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

    extern int column;
    extern std::string strVal;
    extern union YYSTYPE yylval;

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
&           { column ++; return TOK_AMPERSAND; }
\(          { column ++; return TOK_LEFT_PARENTHESIS; }
\)          { column ++; return TOK_RIGHT_PARENTHESIS; }
\*          { column ++; return TOK_STAR; }
\+          { column ++; return TOK_PLUS; }
,           { column ++; return TOK_COMMA; }
-           { column ++; return TOK_HYPHEN; }
\.          { column ++; return TOK_DOT; }
\/          { column ++; return TOK_SLASH; }
\:          { column ++; return TOK_COLON; }
;           { column ++; return TOK_SEMICOLON; }
\<          { column ++; return TOK_LESS_THAN; }
=           { column ++; return TOK_EQUAL; }
\>          { column ++; return TOK_GREATER_THAN; }
_           { column ++; return TOK_UNDERLINE; }
\|          { column ++; return TOK_VERTICAL_BAR; }
!           { column ++; return TOK_EXCLAMATION_MARK; }
\$          { column ++; return TOK_DOLLAR; }
\%          { column ++; return TOK_PERCENT; }
\?          { column ++; return TOK_QUESTION_MARK; }
\@          { column ++; return TOK_COMMERCIAL_AT; }
\[          { column ++; return TOK_LEFT_SQUARE_BRACKET; }
\\          { column ++; return TOK_BACK_SLASH; }
\]          { column ++; return TOK_RIGHT_SQUARE_BRACKET; }
\^          { column ++; return TOK_CIRCUMFLEX; }
`           { column ++; return TOK_GRAVE_ACCENT; }
\{          { column ++; return TOK_LEFT_BRACE; }
\}          { column ++; return TOK_RIGHT_BRACE; }
~           { column ++; return TOK_TILDE; }


        /*
         * -- handle the compound symbols
         *    ---------------------------
         */
\=\>        { column += 2; return TOK_ARROW; }
\.\.        { column += 2; return TOK_DOUBLE_DOT; }
\*\*        { column += 2; return TOK_DOUBLE_STAR; }
\:\=        { column += 2; return TOK_ASSIGNMENT; }
\/\=        { column += 2; return TOK_INEQUALITY; }
\>\=        { column += 2; return TOK_GREATER_THAN_OR_EQUAL; }
\<\=        { column += 2; return TOK_LESS_THAN_OR_EQUAL; }
\<\<        { column += 2; return TOK_LEFT_LABEL_BRACKET; }
\>\>        { column += 2; return TOK_RIGHT_LABEL_BRACKET; }
\<\>        { column += 2; return TOK_BOX; }


        /*
        * -- handle keywords
        *    ---------------
        */
abort       { column += strlen(yytext); return TOK_ABORT; }
abs         { column += strlen(yytext); return TOK_ABS; }
accept      { column += strlen(yytext); return TOK_ACCEPT; }
access      { column += strlen(yytext); return TOK_ACCESS; }
all         { column += strlen(yytext); return TOK_ALL; }
and         { column += strlen(yytext); return TOK_AND; }
array       { column += strlen(yytext); return TOK_ARRAY; }
at          { column += strlen(yytext); return TOK_AT; }
begin       { column += strlen(yytext); return TOK_BEGIN; }
body        { column += strlen(yytext); return TOK_BODY; }
case        { column += strlen(yytext); return TOK_CASE; }
constant    { column += strlen(yytext); return TOK_CONSTANT; }
declare     { column += strlen(yytext); return TOK_DECLARE; }
delay       { column += strlen(yytext); return TOK_DELAY; }
delta       { column += strlen(yytext); return TOK_DELTA; }
digits      { column += strlen(yytext); return TOK_DIGITS; }
do          { column += strlen(yytext); return TOK_DO; }
else        { column += strlen(yytext); return TOK_ELSE; }
elsif       { column += strlen(yytext); return TOK_ELSIF; }
end         { column += strlen(yytext); return TOK_END; }
entry       { column += strlen(yytext); return TOK_ENTRY; }
exception   { column += strlen(yytext); return TOK_EXCEPTION; }
exit        { column += strlen(yytext); return TOK_EXIT; }
for         { column += strlen(yytext); return TOK_FOR; }
function    { column += strlen(yytext); return TOK_FUNCTION; }
generic     { column += strlen(yytext); return TOK_GENERIC; }
goto        { column += strlen(yytext); return TOK_GOTO; }
if          { column += strlen(yytext); return TOK_IF; }
in          { column += strlen(yytext); return TOK_IN; }
is          { column += strlen(yytext); return TOK_IS; }
limited     { column += strlen(yytext); return TOK_LIMITED; }
loop        { column += strlen(yytext); return TOK_LOOP; }
mod         { column += strlen(yytext); return TOK_MOD; }
new         { column += strlen(yytext); return TOK_NEW; }
not         { column += strlen(yytext); return TOK_NOT; }
null        { column += strlen(yytext); return TOK_NULL; }
of          { column += strlen(yytext); return TOK_OF; }
or          { column += strlen(yytext); return TOK_OR; }
others      { column += strlen(yytext); return TOK_OTHERS; }
out         { column += strlen(yytext); return TOK_OUT; }
package     { column += strlen(yytext); return TOK_PACKAGE; }
pragma      { column += strlen(yytext); BEGIN(prg); return TOK_PRAGMA; }
private     { column += strlen(yytext); return TOK_PRIVATE; }
procedure   { column += strlen(yytext); return TOK_PROCEDURE; }
raise       { column += strlen(yytext); return TOK_RAISE; }
range       { column += strlen(yytext); return TOK_RANGE; }
record      { column += strlen(yytext); return TOK_RECORD; }
rem         { column += strlen(yytext); return TOK_REM; }
renames     { column += strlen(yytext); return TOK_RENAMES; }
return      { column += strlen(yytext); return TOK_RETURN; }
reverse     { column += strlen(yytext); return TOK_REVERSE; }
select      { column += strlen(yytext); return TOK_SELECT; }
separate    { column += strlen(yytext); return TOK_SEPARATE; }
subtype     { column += strlen(yytext); return TOK_SUBTYPE; }
task        { column += strlen(yytext); return TOK_TASK; }
terminate   { column += strlen(yytext); return TOK_TERMINATE; }
then        { column += strlen(yytext); return TOK_THEN; }
type        { column += strlen(yytext); return TOK_TYPE; }
use         { column += strlen(yytext); return TOK_USE; }
when        { column += strlen(yytext); return TOK_WHEN; }
while       { column += strlen(yytext); return TOK_WHILE; }
with        { column += strlen(yytext); return TOK_WITH; }
xor         { column += strlen(yytext); return TOK_XOR; }



        /*
         * -- handle other identifiers which are not keywords
         *    -----------------------------------------------
         */
{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                yylval.ident = new std::string(yytext);
                return TOK_IDENTIFIER;
            }



        /*
         * -- These rules will handle all universal integer literals
         *    ------------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_INT_LITERAL;
            }



        /*
         * -- These rules will handle all universal real literals
         *    ---------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                 column += strlen(yytext);
                return TOK_UNIVERSAL_REAL_LITERAL;
            }



        /*
         * -- Handle a character literal
         *    --------------------------
         */
\'.\'       {
                 column += strlen(yytext);
                return TOK_CHARACTER_LITERAL;
            }



        /*
         * -- Handle a string literal
         *    -----------------------
         */
<str>\"     { column ++; BEGIN(INITIAL); return TOK_STRING_LITERAL; }
<str>{LF}   { column = 0; BEGIN(INITIAL); return TOK_ERROR; }
<str>\"\"   { column += 2; strVal += '"'; }
<str>.      { column ++; strVal += yytext[0]; }



        /*
         * -- determine which pragma name we are parsing and its args
         *    -------------------------------------------------------
         */
<prg>{WS}   { column ++; }
<prg>{LF}   { column = 0; BEGIN(INITIAL); return TOK_ERROR; }
<prg>{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                BEGIN(arg);
                return TOK_PRAGMA_NAME;
            }
<prg>.      { column ++; BEGIN(INITIAL); return TOK_ERROR; }

<arg>{WS}   { column ++; }
<arg>;      { column ++; BEGIN(INITIAL); return TOK_SEMICOLON; }
<arg>\(     { column ++; return TOK_LEFT_PARENTHESIS; }
<arg>\)     { column ++; BEGIN(INITIAL); return TOK_RIGHT_PARENTHESIS; }
<arg>,      { column ++; return TOK_COMMA; }
<arg>\=\>   { column += 2; return TOK_ARROW; }
<arg>{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                column += strlen(yytext);
                yylval.ident = new std::string(yytext);
                return TOK_IDENTIFIER;
            }
<arg>.      { column ++; BEGIN(INITIAL); return TOK_ERROR; }



        /*
         * -- Handle EOF
         *    ----------
         */
<*><<EOF>>  { return 0; }
'           { column ++; return TOK_APOSTROPHE; }
#           { column ++; return TOK_SHARP; }
.           { column ++; return TOK_ERROR; }


%%

std::string strVal;
union YYSTYPE yylval;

