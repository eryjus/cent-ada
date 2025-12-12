/*=================================================================================================================*/
/*  parser.yy -- The bison implementation of the Century Ada Compiler                                              */
/*                                                                                                                 */
/*        Copyright (c)  2025      -- Adam Clark; See LICENSE.md                                                   */
/*                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                 */
/*     Date      Tracker  Version  Pgmr  Description                                                               */
/*  -----------  -------  -------  ----  ------------------------------------------------------------------------- */
/*  2025-Dec-05  Initial   0.0.0   ADCL  Initial version                                                           */
/*                                                                                                                 */
/*=================================================================================================================*/


%output "parser.cc"
%defines "tokens.hh"
%glr-parser

%{
    #include "ada.hh"

    //
    // -- Some code to determine what fraction of the parser is in play
    //    -------------------------------------------------------------
    extern ParserMode_t parserMode;


    extern int yylex(void);
    extern void yyerror(const char* s);
%}


%code requires {
    typedef enum {
        MODE_FULL_PROGRAM,
        MODE_BASIC_DECLARATION,
    } ParserMode_t;
}


%code requires {
    int Lex(void);   /* forward declaration for the parser */
}


%code {
    #define YYLEX Lex
}


%start start


/*
 * -- These are the tokens for the scanner to find
 *    --------------------------------------------
 */

%token YYEOF
%token TOK_QUOTATION
%token TOK_SHARP
%token TOK_AMPERSAND
%token TOK_APOSTROPHE
%token TOK_LEFT_PARENTHESIS
%token TOK_RIGHT_PARENTHESIS
%token TOK_STAR
%token TOK_MULTIPLY
%token TOK_PLUS
%token TOK_COMMA
%token TOK_HYPHEN
%token TOK_MINUS
%token TOK_DOT
%token TOK_POINT
%token TOK_PERIOD
%token TOK_SLASH
%token TOK_DIVIDE
%token TOK_COLON
%token TOK_SEMICOLON
%token TOK_LESS_THAN
%token TOK_EQUAL
%token TOK_GREATER_THAN
%token TOK_UNDERLINE
%token TOK_VERTICAL_BAR
%token TOK_EXCLAMATION_MARK
%token TOK_DOLLAR
%token TOK_PERCENT
%token TOK_QUESTION_MARK
%token TOK_COMMERCIAL_AT
%token TOK_LEFT_SQUARE_BRACKET
%token TOK_BACK_SLASH
%token TOK_RIGHT_SQUARE_BRACKET
%token TOK_CIRCUMFLEX
%token TOK_GRAVE_ACCENT
%token TOK_LEFT_BRACE
%token TOK_RIGHT_BRACE
%token TOK_TILDE
%token TOK_ARROW
%token TOK_DOUBLE_DOT
%token TOK_DOUBLE_STAR
%token TOK_EXPONENTIATE
%token TOK_ASSIGNMENT
%token TOK_INEQUALITY
%token TOK_GREATER_THAN_OR_EQUAL
%token TOK_LESS_THAN_OR_EQUAL
%token TOK_LEFT_LABEL_BRACKET
%token TOK_RIGHT_LABEL_BRACKET
%token TOK_BOX
%token TOK_ABORT
%token TOK_ABS
%token TOK_ACCEPT
%token TOK_ACCESS
%token TOK_ALL
%token TOK_AND
%token TOK_ARRAY
%token TOK_AT
%token TOK_BEGIN
%token TOK_BODY
%token TOK_CASE
%token TOK_CONSTANT
%token TOK_DECLARE
%token TOK_DELAY
%token TOK_DELTA
%token TOK_DIGITS
%token TOK_DO
%token TOK_ELSE
%token TOK_ELSIF
%token TOK_END
%token TOK_ENTRY
%token TOK_EXCEPTION
%token TOK_EXIT
%token TOK_FOR
%token TOK_FUNCTION
%token TOK_GENERIC
%token TOK_GOTO
%token TOK_IF
%token TOK_IN
%token TOK_IS
%token TOK_LIMITED
%token TOK_LOOP
%token TOK_MOD
%token TOK_NEW
%token TOK_NOT
%token TOK_NULL
%token TOK_OF
%token TOK_OR
%token TOK_OTHERS
%token TOK_OUT
%token TOK_PACKAGE
%token TOK_PRAGMA
%token TOK_PRIVATE
%token TOK_PROCEDURE
%token TOK_RAISE
%token TOK_RANGE
%token TOK_RECORD
%token TOK_REM
%token TOK_RENAMES
%token TOK_RETURN
%token TOK_REVERSE
%token TOK_SELECT
%token TOK_SEPARATE
%token TOK_SUBTYPE
%token TOK_TASK
%token TOK_TERMINATE
%token TOK_THEN
%token TOK_TYPE
%token TOK_USE
%token TOK_WHEN
%token TOK_WHILE
%token TOK_WITH
%token TOK_XOR
%token TOK_IDENTIFIER
%token TOK_UNIVERSAL_INT_LITERAL
%token TOK_UNIVERSAL_REAL_LITERAL
%token TOK_CHARACTER_LITERAL
%token TOK_STRING_LITERAL
%token TOK_PRAGMA_NAME
%token TOK_ERROR



/*
 * -- union of the token payload
 *    --------------------------
 */
%union {
    std::string *errMsg;
}



%%



//
// -- The Parser Entry Point
//    ----------------------
start : basic_declaration { if (parserMode != MODE_BASIC_DECLARATION) YYERROR; }



//
// == Rules from Chapter 3 on Declarations and Types
//    ==============================================



//===================================================================================================================



//
// -- Basic Declarations
//    ------------------
basic_declaration : object_declaration
basic_declaration : number_declaration
basic_declaration : type_declaration
basic_declaration : subtype_declaration
basic_declaration : subprogram_declaration
basic_declaration : package_declaration
basic_declaration : task_declaraction
basic_declaration : generic_declaration
basic_declaration : exception_declaration
basic_declaration : generic_instantiation
basic_declaration : renaming_declaration
basic_declaration : deferred_constant_declaration



//
// -- Object Declarations
//    -------------------
object_declaration : identifier_list TOK_COLON TOK_CONSTANT subtype_indication TOK_ASSIGNMENT expression TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON subtype_indication TOK_ASSIGNMENT expression TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON TOK_CONSTANT subtype_indication TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON subtype_indication TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON TOK_CONSTANT constrained_array_definition TOK_ASSIGNMENT expression TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON constrained_array_definition TOK_ASSIGNMENT expression TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON TOK_CONSTANT constrained_array_definition TOK_SEMICOLON
object_declaration : identifier_list TOK_COLON constrained_array_definition TOK_SEMICOLON



//
// -- Number Declarations
//    -------------------
number_declaration : identifier_list TOK_COLON TOK_CONSTANT TOK_ASSIGNMENT expression TOK_SEMICOLON



//
// -- Identifier List
//    ---------------
identifier_list : TOK_IDENTIFIER
identifier_list : identifier_list TOK_COMMA TOK_IDENTIFIER



//
// -- Type Declarations
//    -----------------
type_declaration : full_type_declaration
type_declaration : incomplete_type_declaration
type_declaration : private_type_declaration



//
// -- Full Type Declarations
//    ----------------------
full_type_declaration : TOK_TYPE TOK_IDENTIFIER discriminant_part TOK_IS type_definition TOK_SEMICOLON
full_type_declaration : TOK_TYPE TOK_IDENTIFIER TOK_IS type_definition TOK_SEMICOLON



//
// -- Type Definitions
//    ----------------
type_definition : enumeration_type_definition
type_definition : integer_type_definition
type_definition : real_type_definition
type_definition : array_type_definition
type_definition : record_type_definition
type_definition : access_type_definition
type_definition : derived_type_definition



//
// -- Subtype Declarations
//    --------------------
subtype_declaration : TOK_SUBTYPE TOK_IDENTIFIER TOK_IS subtype_indication TOK_SEMICOLON



//
// -- Subtype Indications
//    -------------------
subtype_indication : type_mark constraint
subtype_indication : type_mark



//
// -- Type Mark
//
//    This is important:
//    The specification officially defines `type_mark : *type_*name | *subtype_*name`.  Here
//    we will only map to a `name` and reduce the rule to 1 entry.  The discernment will happen
//    in the semantic phase.
//    -----------------------------------------------------------------------------------------
type_mark : name



//
// -- Constraints
//    -----------
constraint : range_constraint
constraint : floating_point_constraint
constraint : fixed_point_constraint
constraint : index_constraint
constraint : discriminant_constraint



//
// -- Derived Type Definitions
//    ------------------------
derived_type_definition : TOK_NEW subtype_indication



//
// -- Range Constraints
//    -----------------
range_constraint : TOK_RANGE range



//
// -- Ranges
//
//    This is important:
//    The specification officially defines `range : *range_*attribute`.  Here we will only map
//    to an `attribute`.  The additional discernment will happen in the semantic phase.
//    ----------------------------------------------------------------------------------------
range : attribute
range : simple_expression TOK_DOUBLE_DOT simple_expression



//
// -- Enumeration Type Definitions
//    ----------------------------
enumeration_type_definition : TOK_LEFT_PARENTHESIS enumeration_literal_specification_list TOK_RIGHT_PARENTHESIS



//
// -- Enumeration Literal Specification Lists
//    ---------------------------------------
enumeration_literal_specification_list : enumeration_literal_specification
enumeration_literal_specification_list : enumeration_literal_specification_list TOK_COMMA enumeration_literal_specification




//
// -- Enumeration Literal Specifications
//    ----------------------------------
enumeration_literal_specification : enumeration_literal



//
// -- Enumeration Literal
//    -------------------
enumeration_literal : TOK_IDENTIFIER
enumeration_literal : TOK_CHARACTER_LITERAL



//
// -- Integer Type Definitions
//    ------------------------
integer_type_definition : range_constraint



//
// -- Real Type Definitions
//    ---------------------
real_type_definition : floating_point_constraint
real_type_definition : fixed_point_constraint



//
// -- Floating Point Constraints
//    --------------------------
floating_point_constraint : floating_accuracy_definition range_constraint
floating_point_constraint : floating_accuracy_definition



//
// -- Floating Accuracy Definitions
//
//    This is important:
//    The specification officially defines `floating_accuracy_definition : TOK_DIGITS *static_*simple_expression`.
//    Here we will only map to a `simple_expression`.  The additional discernment will happen in the semantic phase.
//    --------------------------------------------------------------------------------------------------------------
floating_accuracy_definition : TOK_DIGITS simple_expression



//
// -- Fixed Point Constraints
//    -----------------------
fixed_point_constraint : fixed_accuracy_definition range_constraint
fixed_point_constraint : fixed_accuracy_definition



//
// -- Fixed Accuracy Definitions
//
//    This is important:
//    The specification officially defines `fixed_accuracy_definition : TOK_DELTA *static_*simple_expression`.
//    Here we will only map to a `simple_expression`.  The additional discernment will happen in the semantic phase.
//    --------------------------------------------------------------------------------------------------------------
fixed_accuracy_definition : TOK_DELTA simple_expression



//
// -- Array Type Definitions
//    ----------------------
array_type_definition : unconstrained_array_definition
array_type_definition : constrained_array_definition



//
// -- Unconstrained Array Definitions
//
//    This is important:
//    The specification officially defines
//    `unconstrained_array_definition : ... TOK_OF *component_*subtype_indication`.  Here we will only map to
//    a `subtype_indication`.  The additional discernment will happen in the semantic phase.
//    -------------------------------------------------------------------------------------------------------
unconstrained_array_definition : TOK_ARRAY TOK_LEFT_PARENTHESIS index_subtype_definition_list
                                    TOK_RIGHT_PARENTHESIS TOK_OF subtype_indication




//
// -- Index Subtype Definition Lists
//    ------------------------------
index_subtype_definition_list : index_subtype_definition
index_subtype_definition_list : index_subtype_definition_list TOK_COMMA index_subtype_definition



//
// -- Constrained Array Definitions
//
//    This is important:
//    The specification officially defines
//    `constrained_array_definition : ... TOK_OF *component_*subtype_indication`.  Here we will only map to
//    a `subtype_indication`.  The additional discernment will happen in the semantic phase.
//    -------------------------------------------------------------------------------------------------------
constrained_array_definition : TOK_ARRAY index_constraint TOK_OF subtype_indication



//
// -- Index Subtype Definitions
//    -------------------------
index_subtype_definition : type_mark TOK_RANGE TOK_BOX



//
// -- Index Constraints
//    -----------------
index_constraint : TOK_LEFT_PARENTHESIS discrete_range_list TOK_RIGHT_PARENTHESIS



//
// -- Discrete Range Lists
//    --------------------
discrete_range_list : discrete_range
discrete_range_list : discrete_range_list TOK_COMMA discrete_range



//
// -- Discrete Ranges
//
//    This is important:
//    The specification officially defines
//    `discrete_range : *discrete_*subtype_indication`.  Here we will only map to
//    a `subtype_indication`.  The additional discernment will happen in the semantic phase.
//    --------------------------------------------------------------------------------------
discrete_range : subtype_indication
discrete_range : range



//
// -- Record Type Definitions
//    -----------------------
record_type_definition : TOK_RECORD component_list TOK_END TOK_RECORD



//
// -- Component Lists
//    ---------------
component_list : component_declaration_list
component_list : component_declaration_list_opt variant_part
component_list : TOK_NULL TOK_SEMICOLON



//
// -- Optional Component Declarations Lists
//    -------------------------------------
component_declaration_list_opt : /* empty */
component_declaration_list_opt : component_declaration_list



//
// -- Component Declaration Lists
//    ---------------------------
component_declaration_list : component_declaration
component_declaration_list : component_declaration_list component_declaration



//
// -- Component Declarations
//    ----------------------
component_declaration : identifier_list TOK_COLON component_subtype_definition TOK_ASSIGNMENT expression TOK_SEMICOLON
component_declaration : identifier_list TOK_COLON component_subtype_definition TOK_SEMICOLON



//
// -- Component Subtype Definitions
//    -----------------------------
component_subtype_definition : subtype_indication



//
// -- Discriminant Parts
//    ------------------
discriminant_part : TOK_LEFT_PARENTHESIS discriminant_specification_list TOK_RIGHT_PARENTHESIS



//
// -- Discriminant Specification Lists
//    --------------------------------
discriminant_specification_list : discriminant_specification
discriminant_specification_list : discriminant_specification_list TOK_SEMICOLON discriminant_specification



//
// -- Discriminant Specifications
//    ---------------------------
discriminant_specification : identifier_list TOK_COLON type_mark TOK_ASSIGNMENT expression
discriminant_specification : identifier_list TOK_COLON type_mark



//
// -- Discriminant Constraints
//    ------------------------
discriminant_constraint : TOK_LEFT_PARENTHESIS discriminant_association_list TOK_RIGHT_PARENTHESIS



//
// -- Discriminant Association Lists
//    ------------------------------
discriminant_association_list : discriminant_association
discriminant_association_list : discriminant_association_list TOK_COMMA discriminant_association



//
// -- Discriminant Associations
//    -------------------------
discriminant_association : discriminant_simple_name_list TOK_ARROW expression
discriminant_association : expression



//
// -- Discriminant Simple Name Lists
//
//    This is important:
//    The specification officially defines `*discriminant_*simple_name`.  Here we will
//    only map to a `simple_name`.  The additional discernment will happen in
//    the semantic phase.
//    --------------------------------------------------------------------------------
discriminant_simple_name_list : TOK_IDENTIFIER
discriminant_simple_name_list : discriminant_simple_name_list TOK_VERTICAL_BAR TOK_IDENTIFIER



//
// -- Variant Parts
//
//    This is important:
//    The specification officially defines `*discriminant_*simple_name`.  Here we will
//    only map to a `simple_name`.  The additional discernment will happen in
//    the semantic phase.
//    --------------------------------------------------------------------------------
variant_part : TOK_CASE TOK_IDENTIFIER TOK_IS variant_list TOK_END TOK_CASE TOK_SEMICOLON



//
// -- Variant Lists
//    -------------
variant_list : variant
variant_list : variant_list variant



//
// -- Variants
//    --------
variant : TOK_WHEN choice_list TOK_ARROW component_list



//
// -- Choice Lists
//    ------------
choice_list : choice
choice_list : choice_list TOK_VERTICAL_BAR choice



//
// -- Choices
//
//    This is important:
//    The specification officially defines `*component_*simple_name`.  Here we will
//    only map to a `simple_name`.  The additional discernment will happen in
//    the semantic phase.
//    -----------------------------------------------------------------------------
choice : simple_expression
choice : discrete_range
choice : TOK_OTHERS
choice : TOK_IDENTIFIER



//
// -- Access Type Definitions
//    -----------------------
access_type_definition : TOK_ACCESS subtype_indication



//
// -- Incomplete Type Declarations
//    ----------------------------
incomplete_type_declaration : TOK_TYPE TOK_IDENTIFIER discriminant_part TOK_SEMICOLON
incomplete_type_declaration : TOK_TYPE TOK_IDENTIFIER TOK_SEMICOLON



//
// -- Declarative Parts
//    -----------------
declarative_part : basic_declarative_item_list later_declarative_item_list



//
// -- Basic Declarative Item Lists
//    ----------------------------
basic_declarative_item_list : basic_declarative_item
basic_declarative_item_list : basic_declarative_item_list basic_declarative_item



//
// -- Later Declarative Item Lists
//    ----------------------------
later_declarative_item_list : later_declarative_item
later_declarative_item_list : later_declarative_item_list later_declarative_item



//
// -- Basic Declarative Items
//    -----------------------
basic_declarative_item : basic_declaration
basic_declarative_item : representation_clause
basic_declarative_item : use_clause



//
// -- Later Declarative Items
//    -----------------------
later_declarative_item : body
later_declarative_item : subprogram_declaration
later_declarative_item : package_declaration
later_declarative_item : task_declaraction
later_declarative_item : generic_declaration
later_declarative_item : use_clause
later_declarative_item : generic_instantiation



//
// -- Bodies
//    ------
body : proper_body
body : body_stub



//
// -- Proper Bodies
//    -------------
proper_body : subprogram_body
proper_body : package_body
proper_body : task_body



//===================================================================================================================





//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//==========                                                                                               ==========
//==========                                                                                               ==========
//==========                      Anything below this section is incomplete                                ==========
//==========                                                                                               ==========
//==========                                                                                               ==========
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================



task_body : TOK_TASK TOK_BODY
package_body : TOK_PACKAGE TOK_BODY
subprogram_body : TOK_PROCEDURE | TOK_FUNCTION
body_stub : TOK_BEGIN TOK_END
use_clause : TOK_USE
representation_clause : TOK_WITH
private_type_declaration : TOK_PRIVATE
deferred_constant_declaration : TOK_CONSTANT TOK_SEMICOLON
renaming_declaration : TOK_RENAMES
generic_declaration : TOK_GENERIC
generic_instantiation : TOK_IS TOK_GENERIC
exception_declaration : TOK_EXCEPTION
subprogram_declaration : TOK_PROCEDURE TOK_SEMICOLON
package_declaration : TOK_PACKAGE TOK_SEMICOLON
task_declaraction : TOK_TASK TOK_SEMICOLON


name : TOK_IDENTIFIER
/* simple_name : TOK_IDENTIFIER */
simple_expression : expression
expression : TOK_UNIVERSAL_INT_LITERAL
attribute : TOK_GRAVE_ACCENT TOK_IDENTIFIER


%%

TokenStream *tokens = nullptr;

int Lex(void)
{
    tokens->Advance();
    return tokens->Current();
}


ParserMode_t parserMode = MODE_FULL_PROGRAM;

void yyerror(const char* s)
{
    fputs(s, stderr);
}