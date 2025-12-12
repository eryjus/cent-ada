//=================================================================================================================
//  parse-decl.cc -- Parse Chapter 3 Declarations and Types
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-10  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- For Chapter 3, a `basic_declaration` is the top-level production
//    ----------------------------------------------------------------
bool Parser::ParseBasicDeclaration(void)
{
    diags.Note(tokens.SourceLocation(), DiagID::TestDiagnistic, {"it's working!"});

    if (ParseObjectDeclaration())           return true;
    if (ParseNumberDeclaration())           return true;
    if (ParseTypeDeclaration())             return true;
    if (ParseSubtypeDeclaration())          return true;
    if (ParseSubprogramDeclaration())       return true;
    if (ParsePackageDeclaration())          return true;
    if (ParseTaskDeclaration())             return true;
    if (ParseGenericDeclaration())          return true;
    if (ParseExpeptionDeclaration())        return true;
    if (ParseGenericInstantiation())        return true;
    if (ParseRenamingDeclaration())         return true;
    if (ParseDeferredConstantDeclaration()) return true;
    return false;
}



//
// -- Parse an Object Declaration
//    ---------------------------
bool Parser::ParseObjectDeclaration(void)
{
    Mark m(tokens);

    bool isConstant = false;
    if (!ParseIdentifierList()) return false;
    if (!Require(TOK_COLON)) return false;
    isConstant = Optional(TOK_CONSTANT);
    if (!(ParseSubtypeIndication() || ParseConstrainedArrayDefinition())) return false;
    if (Optional(TOK_ASSIGNMENT)) ParseExpression();
    if (!Require(TOK_SEMICOLON)) {
        // -- TODO: simply missing a semicolon; issue an error and continue
    }

    m.Commit();
    return true;
}



//
// -- Parse a Number Declaration
//    --------------------------
bool Parser::ParseNumberDeclaration(void)
{
    Mark m(tokens);

    if (!ParseIdentifierList()) return false;
    if (!Require(TOK_COLON)) return false;
    if (!Require(TOK_CONSTANT)) return false;
    if (!Require(TOK_ASSIGNMENT)) return false;

    //
    // -- This expression needs to be a `universal_static_expression`.  Therefore,
    //    the value must be static and must also evalueate to either a `universal_real`
    //    or a `universal_integer` type.
    //    -----------------------------------------------------------------------------
    ParseExpression();

    if (!Require(TOK_SEMICOLON)) {
        // -- TODO: maybe only missing a semicolon; issue an error and continue on
    }


    //
    // -- Here, the identifier can be added to the scope's names table as a constant.
    //    ---------------------------------------------------------------------------


    m.Commit();
    return true;
}



//
// -- Parse an Identifier List
//    ------------------------
bool Parser::ParseIdentifierList(void)
{
    Mark m(tokens);

    if (!Require(TOK_IDENTIFIER)) return false;

    while (Optional(TOK_COMMA)) {
        if (!Require(TOK_IDENTIFIER)) return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Type Declaration
//    ------------------------
bool Parser::ParseTypeDeclaration(void)
{
    if (ParseFullTypeDeclaration())         return true;
    if (ParseIncompleteTypeDeclaration())   return true;
    if (ParsePrivateTypeDeclaration())      return true;
    return false;
}



//
// -- Parse a Full Type Declaration
//    -----------------------------
bool Parser::ParseFullTypeDeclaration(void)
{
    Mark m(tokens);

    if (!Require(TOK_TYPE)) return false;
    if (!Require(TOK_IDENTIFIER)) return false;
    ParseDiscriminantPart();
    if (!Require(TOK_IS)) return false;
    ParseTypeDefinition();
    if (!Require(TOK_SEMICOLON)) {
        // TODO: issue an error and assume a semicolon is missing
    }

    m.Commit();
    return true;
}



//
// -- Parse a Type Definition
//    ------------------------
bool Parser::ParseTypeDefinition(void)
{
    if (ParseEnumerationTypeDefinition())   return true;
    if (ParseIntegerTypeDefinition())       return true;
    if (ParseRealTypeDefinition())          return true;
    if (ParseArrayTypeDefinition())         return true;
    if (ParseRecordTypeDefinition())        return true;
    if (ParseAccessTypeDefinition())        return true;
    if (ParseDerivedTypeDefinition())       return true;
    return false;
}




//
// -- Parse a Subtype Declaration
//    ---------------------------
bool Parser::ParseSubtypeDeclaration(void)
{
    Mark m(tokens);

    if (!Require(TOK_SUBTYPE)) return false;
    if (!Require(TOK_IDENTIFIER)) return false;
    if (!Require(TOK_IS)) return false;
    if (!ParseSubtypeIndication()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Subtype Indication
//    --------------------------
bool Parser::ParseSubtypeIndication(void)
{
    Mark m(tokens);

    if (!ParseTypeMark()) return false;
    ParseConstrant();

    m.Commit();
    return true;
}



//
// -- Parse a Type Mark
//    -----------------
bool Parser::ParseTypeMark(void)
{
    Mark m(tokens);

    if (!ParseName()) return false;

    //
    // -- At this point, the name is required to be either a `type_` name or a
    //    `subtype_` name.  Therefore, some additional processing is required here
    //    to ensure the name matches the requirements.  Even though the syntax
    //    might technically work by matching a `name` alone, some context is also
    //    needed to sure a proper parse.  The parse may still fail.
    //
    //    TODO: Check for a type or subtype name
    //    --------------------------------------------------------------------------



    m.Commit();
    return true;
}



//
// -- Parse a Constraint
//    ------------------
bool Parser::ParseConstrant(void)
{
    if (ParseRangeConstraint())                 return true;
    if (ParseFloatingPointConstraint())         return true;
    if (ParseFixedPointConstraint())            return true;
    if (ParseIndexConstraint())                 return true;
    if (ParseDiscriminantConstraint())          return true;
    return false;
}



//
// -- Parse a Derived Type Definition
//    -------------------------------
bool Parser::ParseDerivedTypeDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_NEW)) return false;
    if (!ParseSubtypeIndication()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Range Constraint
//    ------------------------
bool Parser::ParseRangeConstraint(void)
{
    Mark m(tokens);

    if (!Require(TOK_RANGE)) return false;
    if (!ParseRange()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Range
//    -------------
bool Parser::ParseRange(void)
{
    Mark m(tokens);

    if (ParseAttribute()) {
        m.Commit();
        return true;
    }

    // -- different rule
    if (!ParseSimpleExpression()) return false;
    if (!Require(TOK_DOUBLE_DOT)) return false;
    if (!ParseSimpleExpression()) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Enumeration Type Definition
//    ------------------------------------
bool Parser::ParseEnumerationTypeDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseEnumerationLiteralSpecification()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseEnumerationLiteralSpecification()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        // TODO: issue an error about a closing paren and continue
    }

    m.Commit();
    return true;
}



//
// -- Parse an Enumeration Literal Specification
//    ------------------------------------------
bool Parser::ParseEnumerationLiteralSpecification(void)
{
    if (!ParseEnumerationLiteral()) return false;
    return true;
}



//
// -- Parse an Enumeration Literal
//    ----------------------------
bool Parser::ParseEnumerationLiteral(void)
{
    Mark m(tokens);

    if (Optional(TOK_IDENTIFIER)) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }


    //
    // -- This is where bison has problems.  This may or may not be an error.
    //    There may be a problem if the other productions have also failed.
    //    BUT it may not be a problem if other productions have not yet been
    //    attempted.  So, there needs to be some logic here for discernment
    //    somehow before an error is issues.
    //
    //    TODO: maybe issue an error before returning false?
    //    -------------------------------------------------------------------


    return false;
}



//
// -- Parse an Integer Type Definition
//    --------------------------------
bool Parser::ParseIntegerTypeDefinition(void)
{
    if (!ParseRangeConstraint()) return false;
    return true;
}



//
// -- Parse a Real Type Definition
//    ----------------------------
bool Parser::ParseRealTypeDefinition(void)
{
    if (ParseFloatingPointConstraint()) return true;
    if (ParseFixedPointConstraint()) return true;
    return false;
}



//
// -- Parse a Floating Point Constraint
//    ---------------------------------
bool Parser::ParseFloatingPointConstraint(void)
{
    if (!ParseFloatingAccuracyDefinition()) return false;
    ParseRangeConstraint();

    return true;
}



//
// -- Parse a Floating Accuracy Deinition
//    -----------------------------------
bool Parser::ParseFloatingAccuracyDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_DIGITS)) return false;
    if (!ParseSimpleExpression()) return false;

    //
    // -- The Simple Expression must be a `static_` simple expression.
    //    Additional checking may be needed here to ensure that the
    //    parse is correct.
    //
    //    TODO: ensure a static simple expression
    //    ---------------------------------------

    m.Commit();
    return true;
}



//
// -- Parse a Fixed Point Constraint
//    ------------------------------
bool Parser::ParseFixedPointConstraint(void)
{
    if (!ParseFixedAccuracyDefinition()) return false;
    ParseRangeConstraint();

    return true;
}



//
// -- Parse a Fixed Accuracy Deinition
//    --------------------------------
bool Parser::ParseFixedAccuracyDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_DELTA)) return false;
    if (!ParseSimpleExpression()) return false;

    //
    // -- The Simple Expression must be a `static_` simple expression.
    //    Additional checking may be needed here to ensure that the
    //    parse is correct.
    //
    //    TODO: ensure a static simple expression
    //    ---------------------------------------

    m.Commit();
    return true;
}



//
// -- Parse an Array Type Definition
//    ------------------------------
bool Parser::ParseArrayTypeDefinition(void)
{
    if (ParseUnconstrainedArrayDefinition()) return true;
    if (ParseConstrinedArrayDefinition()) return true;
    return false;
}



//
// -- Parse an Unconstrained Array Definition
//    ---------------------------------------
bool Parser::ParseUnconstrainedArrayDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_ARRAY)) return false;
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseIndexSubtypeDefinition()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseIndexSubtypeDefinition()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) return false;
    if (!Require(TOK_OF)) return false;
    if (!ParseSubtypeIndication()) return false;


    //
    // -- The above is a `component_` subtype definition.  So, some additional
    //    checking is required here, and the parse may still fail.
    //
    //    TODO: Check for Componen Subtype Definition
    //    --------------------------------------------------------------------


    m.Commit();
    return true;
}



//
// -- Parse a Constrained Array Definition
//    ------------------------------------
bool Parser::ParseConstrainedArrayDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_ARRAY)) return false;
    if (!ParseIndexConstraint()) return false;
    if (!Require(TOK_OF)) return false;
    if (!ParseSubtypeIndication()) return false;


    //
    // -- The above is a `component_` subtype definition.  So, some additional
    //    checking is required here, and the parse may still fail.
    //
    //    TODO: Check for Componen Subtype Definition
    //    --------------------------------------------------------------------


    m.Commit();
    return true;
}




//
// -- Parse an Index Subtype Definition
//    ---------------------------------
bool Parser::ParseIndexSubtypeDefinition(void)
{
    Mark m(tokens);

    if (!ParseTypeMark()) return false;
    if (!Require(TOK_RANGE)) return false;
    if (!Require(TOK_BOX)) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Index Constraint
//    -------------------------
bool Parser::ParseIndexConstraint(void)
{
    Mark m(tokens);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscreteRange()) return false;

    while (!Optional(TOK_COMMA)) {
        if (!ParseDiscreteRange()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) return false;

    m.Commit();
    return true;
}



//
// -- Parse Discrete Range
//    --------------------
bool Parser::ParseDiscreteRange(void)
{
    //
    // -- In the following check, it must be a `discrete_` subtype indication.  Just
    //    having a successful parse is not correct.
    //
    //    TODO: Check for Discrete type
    //    ---------------------------------------------------------------------------
    if (ParseSubtypeIndication()) return true;

    if (ParseRange()) return true;

    return false;
}



//
// -- Parse a Record Type Definition
//    ------------------------------
bool Parser::ParseRecordTypeDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_RECORD)) return false;
    if (!ParseComponentList()) return false;
    if (!Require(TOK_END)) return false;
    if (!Require(TOK_RECORD)) return false;

    m.Commit();
    return true;
}




//
// -- Parse a Component List
//    ----------------------
bool Parser::ParseComponentList(void)
{
    Mark m(tokens);

    if (Require(TOK_NULL)) {
        if (!Require(TOK_SEMICOLON)) {
            // -- TODO: issue a missing semicolon error message
        }

        m.Commit();
        return true;
    }


    int declCnt = 0;
    bool hasVariant = false;


    while (ParseComponentDeclaration()) {
        declCnt ++;
    }

    if (ParseVariantPart()) {
        hasVariant = true;
    }

    if (declCnt == 0 && hasVariant == false) {
        // -- TODO: issue an error about missing record component definitions
        return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Component Declaration
//    -----------------------------
bool Parser::ParseComponentDeclaration(void)
{
    Mark m(tokens);

    if (!ParseIdentifierList()) return false;
    if (!Require(TOK_COLON)) return false;
    if (!ParseComponentSubtypeDefinition()) return false;

    if (Optional(TOK_ASSIGNMENT)) {
        if (!ParseExpression()) return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Component Subtype Definition
//    ------------------------------------
bool Parser::ParseComponentSubtypeDefinition(void)
{
    if (ParseSubtypeIndication()) return true;
    return false;
}



//
// -- Parse a Discriminant Part
//    -------------------------
bool Parser::ParseDiscriminantPart(void)
{
    Mark m(tokens);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantSpecification()) return false;

    while (Optional(TOK_SEMICOLON)) {
        if (!ParseDiscriminantSpecification()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Discriminant Specification
//    ----------------------------------
bool Parser::ParseDiscriminantSpecification(void)
{
    Mark m(tokens);

    if (!ParseIdentifierList()) return false;
    if (!Require(TOK_COLON)) return false;
    if (!ParseTypeMark()) return false;

    if (Optional(TOK_ASSIGNMENT)) {
        if (!ParseExpression()) return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Discriminant Constraint
//    -------------------------------
bool Parser::ParseDiscriminantConstraint(void)
{
    Mark m(tokens);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantAssociation()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseDiscriminantAssociation()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Discriminant Association
//    --------------------------------
bool Parser::ParseDiscriminantAssociation(void)
{
    Mark m(tokens);

    if (ParseSimpleName()) {
        //
        // -- These are discriminant simple names, so some additional analysis
        //    is required here to ensure a proper match.
        //
        //    TODO: make sure the simple name is a discriminant simple name
        //    -----------------------------------------------------------------

        while (Optional(TOK_VERTICAL_BAR)) {
            if (!ParseSimpleName()) return false;
        }


        if (!Require(TOK_ARROW)) return false;
    }

    if (!ParseExpression()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Variant Part
//    --------------------
bool Parser::ParseVariantPart(void)
{
    Mark m(tokens);

    if (!Require(TOK_CASE)) return false;
    if (!ParseSimpleName()) return false;
    if (!Require(TOK_IS)) return false;
    if (!ParseVariant()) return false;

    while (ParseVariant()) {
        // -- for the moment, nothing is needed here
    }

    if (!Require(TOK_END)) return false;
    if (!Require(TOK_CASE)) return false;
    if (!Require(TOK_SEMICOLON)) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Variant
//    ---------------
bool Parser::ParseVariant(void)
{
    Mark m(tokens);

    if (!Require(TOK_WHEN)) return false;
    if (!ParseChoice()) return false;

    while (Optional(TOK_VERTICAL_BAR)) {
        if (!ParseChoice()) return false;
    }

    if (!Require(TOK_ARROW)) return false;
    if (!ParseComponentList()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Choice
//    --------------
bool Parser::ParseChoice(void)
{
    Mark m(tokens);

    if (ParseSimpleExpression()) {
        m.Commit();
        return true;
    }

    if (ParseDiscreteRange()) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_OTHERS)) {
        m.Commit();
        return true;
    }

    if (ParseSimpleName()) {
        //
        // -- This is required to be a component simple name
        //
        //    TODO: Check the type of the simple name
        //    ----------------------------------------------
        m.Commit();
        return true;
    }

    return false;
}



//
// -- Parse an Access Type Definition
//    -------------------------------
bool Parser::ParseAccessTypeDefinition(void)
{
    Mark m(tokens);

    if (!Require(TOK_ACCESS)) return false;
    if (!ParseSubtypeIndication()) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Incomplete Type Declaration
//    ------------------------------------
bool Parser::ParseIncompleteTypeDeclaration(void)
{
    Mark m(tokens);

    if (!Require(TOK_TYPE)) return false;
    if (!Require(TOK_IDENTIFIER)) return false;

    // -- this is optional
    ParseDiscriminantPart();

    if (!Require(TOK_SEMICOLON)) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Declarative Part
//    ------------------------
bool Parser::ParseDeclarativePart(void)
{
    while (ParseBasicDeclarativeItem()) {
        // -- for now, nothing to be done here
    }

    while (ParseLaterDeclarativeItem()) {
        // -- for now, nothing to be done here
    }

    return true;
}



//
// -- Parse a Basic Declarative Item
//    ------------------------------
bool Parser::ParseBasicDeclarativeItem(void)
{
    if (ParseBasicDeclaration()) return true;
    if (ParseRepresentationClause()) return true;
    if (ParseUseClause()) return true;

    return false;
}



//
// -- Parse a Later Declarative Item
//    ------------------------------
bool Parser::ParseLaterDeclarativeItem(void)
{
    if (ParseBody()) return true;
    if (ParseSubprogramDeclaration()) return true;
    if (ParsePackageDeclaration()) return true;
    if (ParseTaskDeclaration()) return true;
    if (ParseGenericDeclaration()) return true;
    if (ParseUseClause()) return true;
    if (ParseGenericInstantiation()) return true;

    return false;
}



//
// -- Parse a Body
//    ------------
bool Parser::ParseBody(void)
{
    if (ParseProperBody()) return true;
    if (ParseBodyStub()) return true;

    return false;
}



//
// -- Parse a Proper Body
//    -------------------
bool Parser::ParseProperBody(void)
{
    if (ParseSubprogramBody()) return true;
    if (ParsePackageBody()) return true;
    if (ParseTaskBody()) return true;

    return false;
}



