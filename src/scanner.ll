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
    #include "ada.hh"
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
{WS}        {}
{LF}        {}
--.*        {}



        /*
         * -- handle the single character symbols
         *    -----------------------------------
         */
\"          { BEGIN(str); strVal = ""; }
&           { return TOK_AMPERSAND; }
\(          { return TOK_LEFT_PARENTHESIS; }
\)          { return TOK_RIGHT_PARENTHESIS; }
\*          { return TOK_STAR; }
\+          { return TOK_PLUS; }
,           { return TOK_COMMA; }
-           { return TOK_HYPHEN; }
\.          { return TOK_DOT; }
\/          { return TOK_SLASH; }
\:          { return TOK_COLON; }
;           { return TOK_SEMICOLON; }
\<          { return TOK_LESS_THAN; }
=           { return TOK_EQUAL; }
\>          { return TOK_GREATER_THAN; }
_           { return TOK_UNDERLINE; }
\|          { return TOK_VERTICAL_BAR; }
!           { return TOK_EXCLAMATION_MARK; }
\$          { return TOK_DOLLAR; }
\%          { return TOK_PERCENT; }
\?          { return TOK_QUESTION_MARK; }
\@          { return TOK_COMMERCIAL_AT; }
\[          { return TOK_LEFT_SQUARE_BRACKET; }
\\          { return TOK_BACK_SLASH; }
\]          { return TOK_RIGHT_SQUARE_BRACKET; }
\^          { return TOK_CIRCUMFLEX; }
`           { return TOK_GRAVE_ACCENT; }
\{          { return TOK_LEFT_BRACE; }
\}          { return TOK_RIGHT_BRACE; }
~           { return TOK_TILDE; }


        /*
         * -- handle the compound symbols
         *    ---------------------------
         */
\=\>        { return TOK_ARROW; }
\.\.        { return TOK_DOUBLE_DOT; }
\*\*        { return TOK_DOUBLE_STAR; }
\:\=        { return TOK_ASSIGNMENT; }
\/\=        { return TOK_INEQUALITY; }
\>\=        { return TOK_GREATER_THAN_OR_EQUAL; }
\<\=        { return TOK_LESS_THAN_OR_EQUAL; }
\<\<        { return TOK_LEFT_LABEL_BRACKET; }
\>\>        { return TOK_RIGHT_LABEL_BRACKET; }
\<\>        { return TOK_BOX; }


        /*
        * -- handle keywords
        *    ---------------
        */
abort       { return TOK_ABORT; }
abs         { return TOK_ABS; }
accept      { return TOK_ACCEPT; }
access      { return TOK_ACCESS; }
all         { return TOK_ALL; }
and         { return TOK_AND; }
array       { return TOK_ARRAY; }
at          { return TOK_AT; }
begin       { return TOK_BEGIN; }
body        { return TOK_BODY; }
case        { return TOK_CASE; }
constant    { return TOK_CONSTANT; }
declare     { return TOK_DECLARE; }
delay       { return TOK_DELAY; }
delta       { return TOK_DELTA; }
digits      { return TOK_DIGITS; }
do          { return TOK_DO; }
else        { return TOK_ELSE; }
elsif       { return TOK_ELSIF; }
end         { return TOK_END; }
entry       { return TOK_ENTRY; }
exception   { return TOK_EXCEPTION; }
exit        { return TOK_EXIT; }
for         { return TOK_FOR; }
function    { return TOK_FUNCTION; }
generic     { return TOK_GENERIC; }
goto        { return TOK_GOTO; }
if          { return TOK_IF; }
in          { return TOK_IN; }
is          { return TOK_IS; }
limited     { return TOK_LIMITED; }
loop        { return TOK_LOOP; }
mod         { return TOK_MOD; }
new         { return TOK_NEW; }
not         { return TOK_NOT; }
null        { return TOK_NULL; }
of          { return TOK_OF; }
or          { return TOK_OR; }
others      { return TOK_OTHERS; }
out         { return TOK_OUT; }
package     { return TOK_PACKAGE; }
pragma      { BEGIN(prg); return TOK_PRAGMA; }
private     { return TOK_PRIVATE; }
procedure   { return TOK_PROCEDURE; }
raise       { return TOK_RAISE; }
range       { return TOK_RANGE; }
record      { return TOK_RECORD; }
rem         { return TOK_REM; }
renames     { return TOK_RENAMES; }
return      { return TOK_RETURN; }
reverse     { return TOK_REVERSE; }
select      { return TOK_SELECT; }
separate    { return TOK_SEPARATE; }
subtype     { return TOK_SUBTYPE; }
task        { return TOK_TASK; }
terminate   { return TOK_TERMINATE; }
then        { return TOK_THEN; }
type        { return TOK_TYPE; }
use         { return TOK_USE; }
when        { return TOK_WHEN; }
while       { return TOK_WHILE; }
with        { return TOK_WITH; }
xor         { return TOK_XOR; }



        /*
         * -- handle other identifiers which are not keywords
         *    -----------------------------------------------
         */
{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                return TOK_IDENTIFIER;
            }



        /*
         * -- These rules will handle all universal integer literals
         *    ------------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_INT_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_INT_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_INT_LITERAL;
            }



        /*
         * -- These rules will handle all universal real literals
         *    ---------------------------------------------------
         */
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }

{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*# {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e\+?{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#e-{DIGIT}({UNDERLINE}|{DIGIT})* {
                return TOK_UNIVERSAL_REAL_LITERAL;
            }



        /*
         * -- Handle a character literal
         *    --------------------------
         */
\'.\'       {
                return TOK_CHARACTER_LITERAL;
            }



        /*
         * -- Handle a string literal
         *    -----------------------
         */
<str>\"     { BEGIN(INITIAL); return TOK_STRING_LITERAL; }
<str>{LF}   { BEGIN(INITIAL); return TOK_ERROR; }
<str>\"\"   { strVal += '"'; }
<str>.      { strVal += yytext[0]; }



        /*
         * -- determine which pragma name we are parsing and its args
         *    -------------------------------------------------------
         */
<prg>{LF}   { BEGIN(INITIAL); return TOK_ERROR; }
<prg>[^(;]* { BEGIN(arg); return TOK_PRAGMA_NAME; }

<arg>;      { BEGIN(INITIAL); return TOK_SEMICOLON; }
<arg>\(     { return TOK_LEFT_PARENTHESIS; }
<arg>\)     { BEGIN(INITIAL); return TOK_RIGHT_PARENTHESIS; }
<arg>,      { return TOK_COMMA; }
<arg>\=\>   { return TOK_ARROW; }
<arg>{LETTER}({UNDERLINE}|{LETTER}|{DIGIT})* {
                return TOK_IDENTIFIER;
            }



        /*
         * -- Handle EOF
         *    ----------
         */
<*><<EOF>>  { return 0; }
.           { return TOK_ERROR; }


%%

std::string strVal;

