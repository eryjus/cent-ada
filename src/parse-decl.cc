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
// -- This statically declaraed member in the Mark class needs a physical memory location
//    -----------------------------------------------------------------------------------
int Parser::MarkStream::depth = 0;
bool Parser::Production::trace = false;



//
// -- For Chapter 3, a `basic_declaration` is the top-level production
//    ----------------------------------------------------------------
bool Parser::ParseBasicDeclaration(void)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "basic_declaration");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseObjectDeclaration()))            return true;
    if (m.CommitIf(ParseNumberDeclaration()))            return true;
    if (m.CommitIf(ParseTypeDeclaration()))              return true;
    if (m.CommitIf(ParseSubtypeDeclaration()))           return true;
    if (m.CommitIf(ParseSubprogramDeclaration()))        return true;
    if (m.CommitIf(ParsePackageDeclaration()))           return true;
    if (m.CommitIf(ParseTaskDeclaration()))              return true;
    if (m.CommitIf(ParseGenericDeclaration()))           return true;
    if (m.CommitIf(ParseExceptionDeclaration()))         return true;
    if (m.CommitIf(ParseGenericInstantiation()))         return true;
    if (m.CommitIf(ParseRenamingDeclaration()))          return true;
    if (m.CommitIf(ParseDeferredConstantDeclaration()))  return true;

    return false;
}



//
// -- Parse an Object Declaration
//    ---------------------------
bool Parser::ParseObjectDeclaration(void)
{
    Production p(*this, "object_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();

    bool isConstant = false;
    if (!ParseIdentifierList(idList.get())) return false;
    if (!Require(TOK_COLON)) return false;
    isConstant = Optional(TOK_CONSTANT);


    for (int i = 0; i < idList->size(); i ++) {
        CheckLocalId(idList->at(i).name, idList->at(i).loc, isConstant ? SymbolKind::Constant : SymbolKind::Object);
    }


    if (ParseSubtypeIndication()) {
        // -- do something important here
    } else if (ParseConstrainedArrayDefinition()) {
        // -- do something important here
    } else return false;

    if (Optional(TOK_ASSIGNMENT)) {
        ParseExpression();
    }

    if (!Require(TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"expression"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    s.Commit();
    m.Commit();
    return true;
}



//
// -- Parse a Number Declaration
//    --------------------------
bool Parser::ParseNumberDeclaration(void)
{
    Production p(*this, "number_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();

    if (!ParseIdentifierList(idList.get())) return false;

    for (int i = 0; i < idList->size(); i ++) {
        CheckLocalId(idList->at(i).name, idList->at(i).loc, SymbolKind::Constant);
    }

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
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"expression"});
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Here, the identifier can be added to the scope's names table as a constant.
    //    ---------------------------------------------------------------------------

    s.Commit();
    m.Commit();
    return true;
}



//
// -- Parse an Identifier List
//    ------------------------
bool Parser::ParseIdentifierList(IdList *ids)
{
    Production p(*this, "identifier_list");
    MarkStream m(tokens, diags);
    std::string id;

    ids->clear();

    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;
    ids->push_back( { id, loc } );

    while (Optional(TOK_COMMA)) {
        if (!RequireIdent(id)) return false;
        ids->push_back( { id, loc } );
    }

    m.Commit();
    return true;
}



//
// -- Parse a Type Declaration
//    ------------------------
bool Parser::ParseTypeDeclaration(void)
{
    Production p(*this, "type_declaration");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseFullTypeDeclaration()))         return true;
    if (m.CommitIf(ParseIncompleteTypeDeclaration()))   return true;
    if (m.CommitIf(ParsePrivateTypeDeclaration()))      return true;
    return false;
}



//
// -- Parse a Full Type Declaration
//    -----------------------------
bool Parser::ParseFullTypeDeclaration(void)
{
    Production p(*this, "full_type_definition");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::string id;

    if (!Require(TOK_TYPE)) return false;
    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;
    CheckLocalId(id, loc, SymbolKind::Type);
    ParseDiscriminantPart();
    if (!Require(TOK_IS)) return false;
    ParseTypeDefinition();
    if (!Require(TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"type definition"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    s.Commit();
    m.Commit();
    return true;
}



//
// -- Parse a Type Definition
//    ------------------------
bool Parser::ParseTypeDefinition(void)
{
    Production p(*this, "type_definition");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseEnumerationTypeDefinition()))      return true;
    if (m.CommitIf(ParseIntegerTypeDefinition()))          return true;
    if (m.CommitIf(ParseRealTypeDefinition()))             return true;
    if (m.CommitIf(ParseArrayTypeDefinition()))            return true;
    if (m.CommitIf(ParseRecordTypeDefinition()))           return true;
    if (m.CommitIf(ParseAccessTypeDefinition()))           return true;
    if (m.CommitIf(ParseDerivedTypeDefinition()))          return true;
    return false;
}




//
// -- Parse a Subtype Declaration
//    ---------------------------
bool Parser::ParseSubtypeDeclaration(void)
{
    Production p(*this, "subtype_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::string id;

    if (!Require(TOK_SUBTYPE)) return false;
    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;
    CheckLocalId(id, loc, SymbolKind::Subtype);
    if (!Require(TOK_IS)) return false;
    if (!ParseSubtypeIndication()) return false;
    if (!Require(TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"subtype"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    s.Commit();
    m.Commit();
    return true;
}



//
// -- Parse a Subtype Indication
//    --------------------------
bool Parser::ParseSubtypeIndication(void)
{
    Production p(*this, "subtype_indication");
    MarkStream m(tokens, diags);

    std::cerr << "Subtype Indication, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (!ParseTypeMark()) return false;
    std::cerr << "Checking optional Constraint in `subtype_indication`\n";
    ParseConstraint();
    std::cerr << "Subtype Indication, ending token: " << tokens.tokenStr(tokens.Current()) << '\n';

    m.Commit();
    return true;
}



//
// -- Parse a Type Mark
//    -----------------
bool Parser::ParseTypeMark(void)
{
    Production p(*this, "type_mark");
    MarkStream m(tokens, diags);
    std::string id;

    std::cerr << "Type Mark; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (!ParseName(id)) return false;

    //
    // -- At this point, the name is required to be either a `type_` name or a
    //    `subtype_` name.  Therefore, some additional processing is required here
    //    to ensure the name matches the requirements.  Even though the syntax
    //    might technically work by matching a `name` alone, some context is also
    //    needed to sure a proper parse.  The parse may still fail.
    //
    //    TODO: Check for a type or subtype name
    //    --------------------------------------------------------------------------

    Symbol *sym = scopes.Lookup(id);
    if (!sym) {
        std::cerr << "Failed to find type " << id << '\n';
        // --TODO: Issue an error here for unknown type/subtype
        return false;
    }

    if (sym->kind != SymbolKind::Type && sym->kind != SymbolKind::Subtype && sym->kind != SymbolKind::IncompleteType) {
        std::cerr << id << "is the wrong type \n";
        // -- TODO: Issue an error here?
        return false;
    }


    m.Commit();
    return true;
}



//
// -- Parse a Constraint
//    ------------------
bool Parser::ParseConstraint(void)
{
    Production p(*this, "constraint");
    MarkStream m(tokens, diags);

    std::cerr << "Checking Range Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseRangeConstraint()))                return true;
    std::cerr << "Checking Floating Point Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseFloatingPointConstraint()))        return true;
    std::cerr << "Checking Fixed Point Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseFixedPointConstraint()))           return true;
    std::cerr << "Checking Index Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseIndexConstraint()))                return true;
    std::cerr << "Checking Discriminant Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseDiscriminantConstraint()))         return true;
    std::cerr << "NO Constraint; leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    return false;
}



//
// -- Parse a Derived Type Definition
//    -------------------------------
bool Parser::ParseDerivedTypeDefinition(void)
{
    Production p(*this, "derived_type_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "range_constraint");
    MarkStream m(tokens, diags);

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
    Production p(*this, "range");
    MarkStream m(tokens, diags);

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
    Production p(*this, "enumeration_type_definition");
    MarkStream m(tokens, diags);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseEnumerationLiteralSpecification()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseEnumerationLiteralSpecification()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"enumeration literal"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    m.Commit();
    return true;
}



//
// -- Parse an Enumeration Literal Specification
//    ------------------------------------------
bool Parser::ParseEnumerationLiteralSpecification(void)
{
    Production p(*this, "enumeration_literal_specification");
    MarkStream m(tokens, diags);

    if (!ParseEnumerationLiteral()) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Enumeration Literal
//    ----------------------------
bool Parser::ParseEnumerationLiteral(void)
{
    Production p(*this, "enumeration_literal");
    MarkStream m(tokens, diags);

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
    Production p(*this, "integer_type_definition");
    MarkStream m(tokens, diags);

    if (!ParseRangeConstraint()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Real Type Definition
//    ----------------------------
bool Parser::ParseRealTypeDefinition(void)
{
    Production p(*this, "real_type_definition");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseFloatingPointConstraint()))    return true;
    if (m.CommitIf(ParseFixedPointConstraint()))       return true;
    return false;
}



//
// -- Parse a Floating Point Constraint
//    ---------------------------------
bool Parser::ParseFloatingPointConstraint(void)
{
    Production p(*this, "floating_point_constraint");
    MarkStream m(tokens, diags);

    if (!ParseFloatingAccuracyDefinition()) return false;
    ParseRangeConstraint();

    m.Commit();
    return true;
}



//
// -- Parse a Floating Accuracy Deinition
//    -----------------------------------
bool Parser::ParseFloatingAccuracyDefinition(void)
{
    Production p(*this, "floating_accuracy_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "fixed_point_constraint");
    MarkStream m(tokens, diags);

    if (!ParseFixedAccuracyDefinition()) return false;
    ParseRangeConstraint();

    m.Commit();
    return true;
}



//
// -- Parse a Fixed Accuracy Deinition
//    --------------------------------
bool Parser::ParseFixedAccuracyDefinition(void)
{
    Production(*this, "fixed_accuracy_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "array_type_definition");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseUnconstrainedArrayDefinition()))   return true;
    if (m.CommitIf(ParseConstrainedArrayDefinition()))     return true;
    return false;
}



//
// -- Parse an Unconstrained Array Definition
//    ---------------------------------------
bool Parser::ParseUnconstrainedArrayDefinition(void)
{
    Production p(*this, "unconstrained_array_definition");
    MarkStream m(tokens, diags);

    if (!Require(TOK_ARRAY)) return false;
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseIndexSubtypeDefinition()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseIndexSubtypeDefinition()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"array index subtype definition"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

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
    Production p(*this, "constrained_array_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "index_subtype_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "index_constraint");
    MarkStream m(tokens, diags);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscreteRange()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseDiscreteRange()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"discrete range"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    m.Commit();
    return true;
}



//
// -- Parse Discrete Range
//    --------------------
bool Parser::ParseDiscreteRange(void)
{
    Production p(*this, "discrete_range");
    MarkStream m(tokens, diags);

    //
    // -- In the following check, it must be a `discrete_` subtype indication.  Just
    //    having a successful parse is not correct.
    //
    //    TODO: Check for Discrete type
    //    ---------------------------------------------------------------------------
    if (m.CommitIf(ParseSubtypeIndication()))      return true;
    if (m.CommitIf(ParseRange()))                  return true;

    return false;
}



//
// -- Parse a Record Type Definition
//    ------------------------------
bool Parser::ParseRecordTypeDefinition(void)
{
    Production p(*this, "record_type_definition");
    MarkStream m(tokens, diags);

    if (!Require(TOK_RECORD)) return false;


    if (!ParseComponentList()) return false;
    std::cerr << "Back from Component List\n";
    if (!Require(TOK_END)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingEnd, {"record component list"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    if (!Require(TOK_RECORD)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingEndingTag, {"record"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    m.Commit();
    return true;
}




//
// -- Parse a Component List
//    ----------------------
bool Parser::ParseComponentList(void)
{
    Production p(*this, "component_list");
    MarkStream m(tokens, diags);

    if (Require(TOK_NULL)) {
        if (!Require(TOK_SEMICOLON)) {
            diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"null"});
            // -- continue on in hopes that this does not create a cascade of errors
        }

        m.Commit();
        return true;
    }


    int declCnt = 0;
    bool hasVariant = false;

    std::cerr << "Starting checks for Component Declarations, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';

    while (ParseComponentDeclaration()) {
        declCnt ++;
    }

    std::cerr << "Starting checks for Variant Part\n";

    if (ParseVariantPart()) {
        hasVariant = true;
    }

    if (declCnt == 0 && hasVariant == false) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRecordComponentDefinitions);
        // -- continue on in hopes that this does not create a cascade of errors
    }

    std::cerr << "Returning at this point: declCnt = " << declCnt << "; hasVariant = " << hasVariant << '\n';

    m.Commit();
    return true;
}



//
// -- Parse a Component Declaration
//    -----------------------------
bool Parser::ParseComponentDeclaration(void)
{
    Production p(*this, "component_declaration");
    MarkStream m(tokens, diags);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();

    std::cerr << "Component Declaration, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (!ParseIdentifierList(idList.get())) return false;
    if (!Require(TOK_COLON)) return false;
    if (!ParseComponentSubtypeDefinition()) return false;

    if (Optional(TOK_ASSIGNMENT)) {
        if (!ParseExpression()) return false;
    }

    if (!Require(TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"expression"});
        // -- continue on in hopes that this does not create a cascade of errors

    }

    m.Commit();
    return true;
}



//
// -- Parse a Component Subtype Definition
//    ------------------------------------
bool Parser::ParseComponentSubtypeDefinition(void)
{
    Production p(*this, "component_subtype_definition");
    MarkStream m(tokens, diags);

    std::cerr << "Component Subtype Definition, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (m.CommitIf(ParseSubtypeIndication()))      return true;
    return false;
}



//
// -- Parse a Discriminant Part
//    -------------------------
bool Parser::ParseDiscriminantPart(void)
{
    Production p(*this, "disctiminant_part");
    MarkStream m(tokens, diags);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantSpecification()) return false;

    while (Optional(TOK_SEMICOLON)) {
        if (!ParseDiscriminantSpecification()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"discriminant specification"});
        // -- continue on in hopes that this does not create a cascade of errors
    }


    m.Commit();
    return true;
}



//
// -- Parse a Discriminant Specification
//    ----------------------------------
bool Parser::ParseDiscriminantSpecification(void)
{
    Production p(*this, "discriminant_specification");
    MarkStream m(tokens, diags);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();

    if (!ParseIdentifierList(idList.get())) return false;
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
    Production p(*this, "discriminant_constraint");
    MarkStream m(tokens, diags);

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantAssociation()) return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseDiscriminantAssociation()) return false;
    }

    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"discriminant association"});
        // -- continue on in hopes that this does not create a cascade of errors
    }


    m.Commit();
    return true;
}



//
// -- Parse a Discriminant Association
//    --------------------------------
bool Parser::ParseDiscriminantAssociation(void)
{
    Production p(*this, "disriminant_association");
    MarkStream m(tokens, diags);
    Symbol *sym = nullptr;
    std::string id;

    std::cerr << "Discriminant Association, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    //
    // -- This is critical here: just because we have a simple name does not mean we have a
    //    discriminant simple name.  We may in fact have an expression.  In order to discren
    //    the difference, we will use the current token check and if the next token is a
    //    TOK_VERTICAL_BAR or TOK_ARROW, then we can be assured we have a "discriminant_simple_name".
    //    Otherwise we will just skip ahead to the expression.
    //    --------------------------------------------------------------------------------------------
    if (ParseSimpleName(id)) {
        std::cerr << "Checking next token: " << tokens.tokenStr(tokens.Current()) << '\n';
        if (tokens.Current() != TOK_VERTICAL_BAR && tokens.Current() != TOK_ARROW) {
            std::cerr << "Resetting for `expression`\n";
            m.Reset();
            goto expr;
        }

        sym = scopes.Lookup(id);
        if (sym == nullptr) {
            // -- TODO: Add an error message here about a non-discriminant name
        }

        if (sym->kind != SymbolKind::Object) {
            // -- TODO: Add an error message here about an invalid name
        }

        while (Optional(TOK_VERTICAL_BAR)) {
            if (!ParseSimpleName(id)) return false;

        sym = scopes.Lookup(id);
        if (sym == nullptr) {
                // -- TODO: Add an error message here about a non-discriminant name
            }

            if (sym->kind != SymbolKind::Object) {
                // -- TODO: Add an error message here about an invalid name
            }
        }


        if (!Require(TOK_ARROW)) return false;
    }

expr:
    if (!ParseExpression()) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Variant Part
//    --------------------
bool Parser::ParseVariantPart(void)
{
    Production p(*this, "variant_part");
    MarkStream m(tokens, diags);
    std::string id;

    std::cerr << "Checking CASE, leading token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (!Require(TOK_CASE)) return false;
    std::cerr << "Checking ident\n";
    SourceLoc_t loc = tokens.SourceLocation();
    if (!ParseSimpleName(id)) return false;
    CheckLocalId(id, loc, SymbolKind::Discriminant);
    std::cerr << "Checking IS\n";
    if (!Require(TOK_IS)) return false;
    std::cerr << "Checking variant\n";
    if (!ParseVariant()) return false;
    std::cerr << "Found variant\n";

    while (ParseVariant()) {
        // -- for the moment, nothing is needed here
    }

    if (!Require(TOK_END)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingEnd, {"variant part"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    if (!Require(TOK_CASE)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingRightParen, {"discriminant specification"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    if (!Require(TOK_SEMICOLON)) return false;

    m.Commit();
    return true;
}



//
// -- Parse a Variant
//    ---------------
bool Parser::ParseVariant(void)
{
    Production p(*this, "variant");
    MarkStream m(tokens, diags);

    std::cerr << "Checking WHEN; token: " << tokens.tokenStr(tokens.Current()) << '\n';
    if (!Require(TOK_WHEN)) return false;
    std::cerr << "Checking choice\n";
    if (!ParseChoice()) return false;
    std::cerr << "Found choice\n";

    while (Optional(TOK_VERTICAL_BAR)) {
        if (!ParseChoice()) return false;
    }

    std::cerr << "Checking ARROW\n";
    if (!Require(TOK_ARROW)) return false;
    std::cerr << "Found ARROW\n";
    if (!ParseComponentList()) return false;
    std::cerr << "Found Component List\n";


    m.Commit();
    return true;
}



//
// -- Parse a Choice
//    --------------
bool Parser::ParseChoice(void)
{
    Production p(*this, "choice");
    MarkStream m(tokens, diags);
    std::string id;

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

    if (ParseSimpleName(id)) {
        //
        // -- This is required to be a component simple name
        //
        //    TODO: Check the type of the simple name
        //    ----------------------------------------------
        m.Commit();
        return true;
    }

    diags.Error(tokens.SourceLocation(), DiagID::InvalidChoiceInVariant);

    return false;
}



//
// -- Parse an Access Type Definition
//    -------------------------------
bool Parser::ParseAccessTypeDefinition(void)
{
    Production p(*this, "access_type_definition");
    MarkStream m(tokens, diags);

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
    Production p(*this, "incomplete_type_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::string id;

    if (!Require(TOK_TYPE)) return false;
    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;
    CheckLocalId(id, loc, SymbolKind::IncompleteType);

    // -- this is optional
    ParseDiscriminantPart();

    if (!Require(TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, {"disctiminant part"});
        // -- continue on in hopes that this does not create a cascade of errors
    }

    s.Commit();
    m.Commit();
    return true;
}



//
// -- Parse a Declarative Part
//    ------------------------
bool Parser::ParseDeclarativePart(void)
{
    Production p(*this, "declarative_part");
    MarkStream m(tokens, diags);

    while (ParseBasicDeclarativeItem()) {
        // -- for now, nothing to be done here
    }

    while (ParseLaterDeclarativeItem()) {
        // -- for now, nothing to be done here
    }

    m.Commit();
    return true;
}



//
// -- Parse a Basic Declarative Item
//    ------------------------------
bool Parser::ParseBasicDeclarativeItem(void)
{
    Production p(*this, "basic_declarative_item");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseBasicDeclaration()))               return true;
    if (m.CommitIf(ParseRepresentationClause()))           return true;
    if (m.CommitIf(ParseUseClause()))                      return true;

    return false;
}



//
// -- Parse a Later Declarative Item
//    ------------------------------
bool Parser::ParseLaterDeclarativeItem(void)
{
    Production p(*this, "later_declarative_item");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseBody()))                           return true;
    if (m.CommitIf(ParseSubprogramDeclaration()))          return true;
    if (m.CommitIf(ParsePackageDeclaration()))             return true;
    if (m.CommitIf(ParseTaskDeclaration()))                return true;
    if (m.CommitIf(ParseGenericDeclaration()))             return true;
    if (m.CommitIf(ParseUseClause()))                      return true;
    if (m.CommitIf(ParseGenericInstantiation()))           return true;

    return false;
}



//
// -- Parse a Body
//    ------------
bool Parser::ParseBody(void)
{
    Production p(*this, "body");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseProperBody()))                     return true;
    if (m.CommitIf(ParseBodyStub()))                       return true;

    return false;
}



//
// -- Parse a Proper Body
//    -------------------
bool Parser::ParseProperBody(void)
{
    Production p(*this, "proper_body");
    MarkStream m(tokens, diags);

    if (m.CommitIf(ParseSubprogramBody()))                 return true;
    if (m.CommitIf(ParsePackageBody()))                    return true;
    if (m.CommitIf(ParseTaskBody()))                       return true;

    return false;
}



