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
    #include <memory>

    #define YY_DECL TokenType yylex(void)

    #include "enum.hh"
    #include "tokens.hh"


    extern int column;
    extern std::string strVal;
    std::string ToLower(const char *s);
    void ScanString(const std::string &s);
    bool ValidateBasedNumber(DiagID &diag);
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
        * -- This is a special case of a single '_' char, which is illegal
        *    -------------------------------------------------------------
        */
{UNDERLINE} {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = ScannerError { DiagID::IllegalIdentifier, { lower, "Identifier cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }



       /*
        * -- These rules will handle all universal integer literals
        *    ------------------------------------------------------
        */
{DIGIT}({UNDERLINE}?{DIGIT})*#[0-9A-Z]({UNDERLINE}?[0-9A-Z])*#(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)? {
                column += strlen(yytext);
                DiagID diag;

                if (ValidateBasedNumber(diag)) {
                    yylval = IntLiteral { std::string(yytext) };
                    return TokenType::TOK_UNIVERSAL_INT_LITERAL;
                } else {
                    yylval = ScannerError { diag, { std::string(yytext) } };
                    return TokenType::TOK_ERROR;
                }
            }
{DIGIT}({UNDERLINE}?{DIGIT})*(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)? {
                column += strlen(yytext);
                yylval = IntLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_INT_LITERAL;
            }



       /*
        * -- These are the possible error constructs around integers
        *    -------------------------------------------------------
        */

       /* -- Underline to start the base */
{UNDERLINE}+{DIGIT}({UNDERLINE}|{DIGIT})*#({UNDERLINE}|{HEXDIGIT})*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer base cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the integer part */
{DIGIT}({UNDERLINE}|{DIGIT})*#{UNDERLINE}+{DIGIT}({UNDERLINE}|{HEXDIGIT})*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the integer part */
{UNDERLINE}+{DIGIT}({UNDERLINE}|{DIGIT})*(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the exponent part */
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#(e[+-]?{UNDERLINE}+{DIGIT}({UNDERLINE}|{DIGIT})*)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the exponent part */
{DIGIT}({UNDERLINE}|{DIGIT})*e[+-]?{UNDERLINE}+{DIGIT}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Missing the exponent part */
{DIGIT}({UNDERLINE}|{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*#(e[+-]?) {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part missing" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Missing the exponent part */
{DIGIT}({UNDERLINE}|{DIGIT})*(e[+-]?) {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part missing" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Multiple the exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*#(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)+ {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part repeated" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Multiple the exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*(e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*)(e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*)+ {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalInteger, { std::string(yytext), "Integer exponent part repeated" } };
                return TokenType::TOK_ERROR;
            }




       /*
        * -- These rules will handle all universal real literals
        *    ---------------------------------------------------
        */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)? {
                column += strlen(yytext);
                yylval = RealLiteral { std::string(yytext) };
                return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
            }
{DIGIT}({UNDERLINE}?{DIGIT})*#[0-9A-Z]({UNDERLINE}?[0-9A-Z])*\.[0-9A-Z]({UNDERLINE}?[0-9A-Z])*#(e[+-]?{DIGIT}({UNDERLINE}?{DIGIT})*)? {
                column += strlen(yytext);
                DiagID diag;

                if (ValidateBasedNumber(diag)) {
                    yylval = RealLiteral { std::string(yytext) };
                    return TokenType::TOK_UNIVERSAL_REAL_LITERAL;
                } else {
                    yylval = ScannerError { diag, { std::string(yytext) } };
                    return TokenType::TOK_ERROR;
                }
            }




       /*
        * -- These are the possible error constructs around reals
        *    ----------------------------------------------------
        */

       /* -- Underline to start the base */
{UNDERLINE}+{DIGIT}({UNDERLINE}?{DIGIT})*#({UNDERLINE}|{HEXDIGIT})*\.({UNDERLINE}|{HEXDIGIT})*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real base cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real whole part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{UNDERLINE}+({UNDERLINE}|{HEXDIGIT})*\.({UNDERLINE}|{HEXDIGIT})*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real whole part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real whole part */
{UNDERLINE}+({UNDERLINE}|{DIGIT})*\.({UNDERLINE}|{DIGIT})*(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real whole part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real whole part */
{DIGIT}({UNDERLINE}?{DIGIT})*#[0-9A-Z]({UNDERLINE}|[0-9A-Z])*{UNDERLINE}+\.({UNDERLINE}|[0-9A-Z])*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real whole part cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real whole part */
{DIGIT}({UNDERLINE}|{DIGIT})*{UNDERLINE}+\.({UNDERLINE}|{DIGIT})*(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real whole part cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real decimal part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*\.{UNDERLINE}({UNDERLINE}|{HEXDIGIT})*#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real decimal part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real decimal part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{UNDERLINE}({UNDERLINE}|{DIGIT})*(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real decimal part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real decimal part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}|{HEXDIGIT})*{UNDERLINE}#(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real decimal part cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real decimal part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}|{DIGIT})*{UNDERLINE}(e[+-]?({UNDERLINE}|{DIGIT})+)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real decimal part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*#e[+-]?{UNDERLINE}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to start the real exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*e[+-]?{UNDERLINE}({UNDERLINE}|{DIGIT})* {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*#{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*\.{HEXDIGIT}({UNDERLINE}?{HEXDIGIT})*#e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*{UNDERLINE} {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*{UNDERLINE} {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- Underline to end the real exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*(e[+-]?{UNDERLINE}({UNDERLINE}|{DIGIT})*)? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }

       /* -- missing exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*e[+-]? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part missing" } };
                return TokenType::TOK_ERROR;
            }

       /* -- missing exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*e[+-]? {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part missing" } };
                return TokenType::TOK_ERROR;
            }

       /* -- repeated exponent part */
{DIGIT}({UNDERLINE}?{DIGIT})*\.{DIGIT}({UNDERLINE}?{DIGIT})*(e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*)(e[+-]?{DIGIT}({UNDERLINE}|{DIGIT})*)+ {
                column += strlen(yytext);
                yylval = ScannerError { DiagID::IllegalReal, { std::string(yytext), "Real exponent part repeated" } };
                return TokenType::TOK_ERROR;
            }





       /*
        * -- handle other identifiers which are not keywords
        *    -----------------------------------------------
        */
{LETTER}({UNDERLINE}?({LETTER}|{DIGIT}))* {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = IdentifierLexeme { lower };
                return TokenType::TOK_IDENTIFIER;
            }




       /*
        * -- These are the possible error constructs around identifiers
        *    ----------------------------------------------------------
        */
{UNDERLINE}({UNDERLINE}?({LETTER}|{DIGIT}))*{UNDERLINE}? {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = ScannerError { DiagID::IllegalIdentifier, { lower, "Identifier cannot begin with an '_'" } };
                return TokenType::TOK_ERROR;
            }
{LETTER}({UNDERLINE}?({LETTER}|{DIGIT}))*{UNDERLINE} {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = ScannerError { DiagID::IllegalIdentifier, { lower, "Identifier cannot end with an '_'" } };
                return TokenType::TOK_ERROR;
            }
{LETTER}({UNDERLINE}{UNDERLINE}+({LETTER}|{DIGIT}))* {
                column += strlen(yytext);
                std::string lower = ToLower(yytext);
                yylval = ScannerError { DiagID::IllegalIdentifier, { lower, "Identifier cannot contain multiple consecutive '_' characters" } };
                return TokenType::TOK_ERROR;
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
<str>\"\"   { column += 2; strVal += '"'; }
<str>.      { column ++; strVal += yytext[0]; }
<str>{LF}   {
                column = 0;
                BEGIN(INITIAL);
                yylval = ScannerError { DiagID::IllegalString, { std::string(strVal), "End-of-line found in string" } };
                return TokenType::TOK_ERROR;
            }
<str><<EOF>> {
                BEGIN(INITIAL);
                yylval = ScannerError { DiagID::IllegalString, { std::string(strVal), "End-of-file found in string" } };
                return TokenType::TOK_ERROR;
            }



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
<prg><<EOF>>  { return TokenType::YYEOF; }

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
<arg><<EOF>>  { return TokenType::YYEOF; }



       /*
        * -- Handle EOF
        *    ----------
        */
'           { column ++; return TokenType::TOK_APOSTROPHE; }
.           { column ++; return TokenType::TOK_ERROR; }
<<EOF>>     { return TokenType::YYEOF; }


%%

std::string strVal;
YYSTYPE yylval;




std::string ToLower(const char *s)
{
    std::string rv = "";

    for (int i = 0; i < strlen(s); i ++) {
        rv.push_back(s[i] >= 'A' && s[i] <= 'Z' ? s[i] - 'A' + 'a' : s[i]);
    }

    return rv;
}



//
// -- Helper function to scan from a string rather than stdin
//    -------------------------------------------------------
void ScanString(const std::string &s)
{
    yy_scan_string(s.c_str());
    BEGIN(INITIAL);
}



//
// -- Check a based number and determine if the digits are valid
//    (Assumes a structurally correct based number)
//    ----------------------------------------------------------
bool ValidateBasedNumber(DiagID &diag)
{
    int i;
    int base = 0;

    // -- collect the base first
    for (i = 0; i < strlen(yytext); i ++) {
        if (yytext[i] == '_') continue;
        if (yytext[i] == '#') break;
        if (yytext[i] < '0' || yytext[i] > '9') {
            diag = DiagID::IllegalBase;
            return false;
        }

        base = base * 10 + (yytext[i] - '0');
    }

    if (base < 2 || base > 16) {
        diag = DiagID::IllegalBase;
        return false;
    }

    // -- now, check the digits against the base
    for (i ++; i < strlen(yytext); i ++) {
        if (yytext[i] == '_') continue;
        if (yytext[i] == '.') continue;
        if (yytext[i] == '#') return true;
        if (yytext[i] >= '0' && yytext[i] <= '9') {
            if (yytext[i] - '0' >= base) {
                diag = DiagID::IllegalDigit;
                return false;
            }

            continue;
        }

        if (yytext[i] >= 'a' && yytext[i] <= 'f') {
            if (yytext[i] - 'a' + 10 >= base) {
                diag = DiagID::IllegalDigit;
                return false;
            }

            continue;
        }

        if (yytext[i] >= 'A' && yytext[i] <= 'F') {
            if (yytext[i] - 'A' + 10 >= base) {
                diag = DiagID::IllegalDigit;
                return false;
            }

            continue;
        }

        diag = DiagID::IllegalDigit;
        return false;
    }

    return true;
}

