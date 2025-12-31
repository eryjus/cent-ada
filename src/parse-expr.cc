//=================================================================================================================
//  parse-expr.cc -- Parse Chapter 4 Names and Expressions
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  The following productions from the spec are not used and therefore are not included here:
//  * logical_operator
//  * highest_precedence_operator
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-21  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"





//
// -- For Chapter 4, a `name` is the top-level production
//
//    This production is used for all things 'name' outside of an expression
//    ----------------------------------------------------------------------
bool Parser::ParseNameNonExpr(Id &id)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "name");
    MarkStream m(tokens, diags);

    if (Optional(TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }

    if (m.CommitIf(ParseSimpleName(id)))                return true;
    if (m.CommitIf(ParseOperatorSymbol()))              return true;
    if (m.CommitIf(ParseIndexedComponent()))            return true;
    if (m.CommitIf(ParseSlice()))                       return true;
    if (m.CommitIf(ParseSelectedComponent()))           return true;
    if (m.CommitIf(ParseAttribute()))                   return true;

    return false;
}



//
// -- For Chapter 4, a `name` is the top-level production
//
//    This production is used for all things 'name' for an expression production
//
//    The production for `name` needs to be refactored to eliminate indirect
//    left recursion into a `base + suffix` form.  Therefore, 2 new functions
//    are added here for `ParseName_Base` and `ParseName_Suffix` to handle
//    all things which are `name` cleanly without left recursion.
//    ------------------------------------------------------------------------
bool Parser::ParseNameExpr(Id &id)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "name");
    MarkStream m(tokens, diags);

    if (!ParseName_Base(id))        return false;

    while (ParseName_Postfix()) {
        // -- Do something important here
    }

    m.Commit();
    return true;
}



//
// -- Parse a Name (Base)
//
//    These alternatives are not dependent on `name` and therefore MUST
//    consume a token from the stream.
//    -----------------------------------------------------------------
bool Parser::ParseName_Base(Id &id)
{
    Production p(*this, "name(base)");
    MarkStream m(tokens, diags);

    if (Optional(TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }

    if (m.CommitIf(ParseSimpleName(id)))                return true;
    if (m.CommitIf(ParseOperatorSymbol()))              return true;

    return false;
}



//
// -- Parse a Name (Postfix)
//
//    These alternatives depend on name, so the concrete tokens have
//    aready been factored out.  These alternatives are anything which
//    can legally follow a base.
//    ----------------------------------------------------------------
bool Parser::ParseName_Postfix(void)
{
    Production p(*this, "name(postfix)");
    MarkStream m(tokens, diags);

    if (Optional(TOK_LEFT_PARENTHESIS)) {
        if (ParseName_IndexOrSliceSuffix()) {
            SourceLoc_t loc = tokens.SourceLocation();
            if (!Require(TOK_RIGHT_PARENTHESIS)) {
                diags.Error(loc, DiagID::MissingRightParen, { "index or selected component" } );
            }

            m.Commit();
            return true;
        }
    }

    if (m.CommitIf(ParseName_SelectedComponentSuffix()))    return true;
    if (m.CommitIf(ParseName_AttributeSuffix()))            return true;

    return false;



#if 0
    if (m.CommitIf(ParseName_IndexComponentSuffix()))       return true;
    m.Reset();
    if (m.CommitIf(ParseName_SelectedComponentSuffix()))    return true;
    m.Reset();
#endif


}



//
// -- Parse either a Indexed or Selected component
//    --------------------------------------------
bool Parser::ParseName_IndexOrSliceSuffix(void)
{
    Production p(*this, "name(index_or_selected_component)");
    MarkStream m(tokens, diags);

    if (ParseName_IndexComponentSuffix()) {
        // -- do something important here
        m.Commit();
        return true;
    }

    m.Reset();
    if (ParseName_SelectedComponentSuffix()) {
        // -- do something important here
        m.Commit();
        return true;
    }

    return false;
}



//
// -- Parse an Attribute Suffix for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_AttributeSuffix(void)
{
    Production p(*this, "name(attribute)");
    MarkStream m(tokens, diags);

    if (!Require(TOK_APOSTROPHE))       return false;
    if (!ParseAttributeDesignator())    return false;

    m.Commit();
    return true;
}



//
// -- Parse an Indexed Component for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_IndexComponentSuffix(void)
{
    Production p(*this, "name(indexed_component)");
    MarkStream m(tokens, diags);

    if (!ParseExpression())                     return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseExpression())                 return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Slice for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_SliceSuffix(void)
{
    Production p(*this, "name(slice)");
    MarkStream m(tokens, diags);

    if (!ParseDiscreteRange())                  return false;

    m.Commit();
    return true;
}



//
// -- Parse an Selected Component for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_SelectedComponentSuffix(void)
{
    Production p(*this, "name(selected_component)");
    MarkStream m(tokens, diags);

    if (!Require(TOK_DOT))                      return false;
    if (!ParseSelector())                       return false;

    m.Commit();
    return true;
}



//
// -- Parse a Simple Name, an identifier with not additional decorations
//    ------------------------------------------------------------------
bool Parser::ParseSimpleName(Id &id)
{
    Production p(*this, "simple_name");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();

    if (!RequireIdent(id))  return false;

    if (scopes.Lookup(id.name) == nullptr) {
        diags.Error(loc, DiagID::UnknownName, { id.name } );
        // -- continue anyway
    }

    m.Commit();
    return true;
}



//
// -- Parse a Prefix
//    --------------
bool Parser::ParsePrefix(void)
{
    Production p(*this, "prefix");
    MarkStream m(tokens, diags);
    Id discard;

    if (m.CommitIf(ParseNameExpr(discard)))         return true;
    if (m.CommitIf(ParseFunctionCall()))            return true;
    return false;
}



//
// -- Parse an Indexed Copmonent
//    --------------------------
bool Parser::ParseIndexedComponent(void)
{
    Production p(*this, "indexed_component");
    MarkStream m(tokens, diags);

    if (!ParsePrefix())                     return false;
    if (!Require(TOK_LEFT_PARENTHESIS))     return false;
    if (!ParseExpression())                 return false;

    while (Optional(TOK_COMMA)) {
        if (!ParseExpression())             return false;
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }

    m.Commit();
    return true;
}



//
// -- Parse an Slice
//    --------------
bool Parser::ParseSlice(void)
{
    Production p(*this, "slice");
    MarkStream m(tokens, diags);

    if (!ParsePrefix())                     return false;
    if (!Require(TOK_LEFT_PARENTHESIS))     return false;
    if (!ParseDiscreteRange())              return false;

    SourceLoc_t loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "discrete_range" } );
    }

    m.Commit();
    return true;
}



//
// -- Parse a Selected Component
//    --------------------------
bool Parser::ParseSelectedComponent(void)
{
    Production p(*this, "selected_component");
    MarkStream m(tokens, diags);
    std::string discard;

    if (!ParsePrefix())                     return false;
    if (!Require(TOK_DOT))                  return false;
    if (!ParseSelector())                   return false;

    m.Commit();
    return true;
}



//
// -- Parse a Selector
//    ----------------
bool Parser::ParseSelector(void)
{
    Production p(*this, "selector");
    MarkStream m(tokens, diags);
    Id id;

    if (Optional(TOK_ALL)) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if (m.CommitIf(ParseSimpleName(id))) {
        if (!scopes.Lookup(id.name)) {
            diags.Error(loc, DiagID::UnknownName, { "selector"} );
            // -- allow the parse to continue
        }

        m.Commit();
        return true;
    }

    if (ParseOperatorSymbol()) {
        m.Commit();
        return true;
    }

    return false;
}


//
// -- Parse an Attribute
//    ------------------
bool Parser::ParseAttribute(void)
{
    Production p(*this, "attribute");
    MarkStream m(tokens, diags);

    if (!ParsePrefix())                 return false;
    if (!Require(TOK_APOSTROPHE))       return false;
    if (!ParseAttributeDesignator())    return false;

    m.Commit();
    return true;
}



//
// -- Parse an Attribute Designator
//    -----------------------------
bool Parser::ParseAttributeDesignator(void)
{
    Production p(*this, "attribute_designator");
    MarkStream m(tokens, diags);
    Id id;

    if (!ParseSimpleName(id))           return false;
    if (Optional(TOK_LEFT_PARENTHESIS)) {
        if (!ParseExpression()) return false;

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression"} );
            // -- allow to continue
        }
    }

    m.Commit();
    return true;
}



//
// -- Parse an Aggregate
//    ------------------
bool Parser::ParseAggregate(void)
{
    Production p(*this, "aggregate");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!Require(TOK_LEFT_PARENTHESIS))         return false;
    if (!ParseComponentAssociation())           return false;

    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseComponentAssociation()) {
            diags.Error(loc, DiagID::ExtraComma, { "component association" } );
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "component_association" } );
    }

    m.Commit();
    return true;
}




//
// -- Parse an Aggregate Suffix
//    -------------------------
bool Parser::ParseAggregateMore(void)
{
    Production p(*this, "aggregate(more)");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseComponentAssociation()) {
            diags.Error(loc, DiagID::ExtraComma, { "aggregate" } );
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "component_association" } );
    }

    m.Commit();
    return true;
}




//
// -- Parse a Component Association
//    -----------------------------
bool Parser::ParseComponentAssociation(void)
{
    Production p(*this, "component_association");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (ParseChoice()) {
        while (Optional(TOK_VERTICAL_BAR)) {
            loc = tokens.SourceLocation();
            if (!ParseChoice()) {
                diags.Error(loc, DiagID::ExtraVertialBar, { "component association" } );
            }
        }
    }

    if (!Require(TOK_ARROW)) return false;
    if (!ParseExpression()) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Expression
//    -------------------
bool Parser::ParseExpression(void)
{
    Production p(*this, "expression");
    MarkStream m(tokens, diags);
    TokenType_t tok;


    if (!ParseRelation()) return false;

    switch (tokens.Current()) {
    case TOK_AND:
    case TOK_AND_THEN:
    case TOK_OR:
    case TOK_OR_ELSE:
    case TOK_XOR:
        tok = tokens.Current();
        break;

    default:
        m.Commit();
        return true;
    }

    while (Optional(tok)) {
        if (!ParseRelation()) {
            // -- TODO: maybe issue an error about missing a relation and return true instead???
            return false;
        }
    }

    m.Commit();
    return true;
}



//
// -- Parse a Relation
//    ----------------
bool Parser::ParseRelation(void)
{
    Production p(*this, "relation");
    MarkStream m(tokens, diags);
    bool hasNot = false;

    if (!ParseSimpleExpression())  return false;

    //
    // -- check for some illegal variations which should fail the parse early
    //    -------------------------------------------------------------------
    if (Illegal(TOK_COMMA)) {
        m.Commit();
        return true;
    }
    if (Illegal(TOK_ARROW)) {
        m.Commit();
        return true;
    }
    if (Illegal(TOK_VERTICAL_BAR)) {
        m.Commit();
        return true;
    }
    if (Illegal(TOK_DOUBLE_DOT)) {
        m.Commit();
        return true;
    }


    if (ParseRelationalOperator()) {
        if (!ParseSimpleExpression()) return false;

        m.Commit();
        return true;
    }


    if (Optional(TOK_NOT)) hasNot = true;
    if (!Optional(TOK_IN)) {
        m.Commit();
        return true;
    }

    if (ParseRange()) {
        m.Commit();
        return true;
    }

    if (ParseTypeMark()) {
        m.Commit();
        return true;
    }

    // -- TODO: Is there some form of recovery needed here?

    m.Commit();
    return true;
}



//
// -- Parse a Simple Expression
//    -------------------------
bool Parser::ParseSimpleExpression(void)
{
    Production p(*this, "simple_expression");
    MarkStream m(tokens, diags);

    ParseUnaryAddingOperator();
    if (!ParseTerm()) return false;
    if (tokens.Current() == TOK_COMMA || tokens.Current() == TOK_ARROW)  {
        // -- at this point we already have a good Term
        m.Commit();
        return true;
    }


    while (ParseBinaryAddingOperator()) {
        if (!ParseTerm()) return false;
        if (tokens.Current() == TOK_COMMA || tokens.Current() == TOK_ARROW) {
            // -- at this point we already have a good Term
            m.Commit();
            return true;
        }
    }

    m.Commit();
    return true;
}



//
// -- Parse a Term
//    ------------
bool Parser::ParseTerm(void)
{
    Production p(*this, "term");
    MarkStream m(tokens, diags);

    if (!ParseFactor()) return false;

    while (ParseMultiplyingOperator()) {
        if (!ParseFactor()) return false;
    }

    m.Commit();
    return true;
}



//
// -- Parse a Factor
//    --------------
bool Parser::ParseFactor(void)
{
    Production p(*this, "factor");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (Require(TOK_ABS)) {
        loc = tokens.SourceLocation();
        if (!ParsePrimary()) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "ABS" } );
        }

        m.Commit();
        return true;
    } else if (Require(TOK_NOT)) {
        loc = tokens.SourceLocation();
        if (!ParsePrimary()) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "NOT" } );
        }

        m.Commit();
        return true;
    } else {
        if (!ParsePrimary())    return false;

        if (Optional(TOK_DOUBLE_STAR)) {
            if (!ParsePrimary())    return false;
        }

        m.Commit();
        return true;
    }

    return false;
}



//
// -- Parse a Primary
//    ---------------
bool Parser::ParsePrimary(void)
{
    Production p(*this, "primary");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t loc;

    //
    // -- The spec calls for a `numeric_literal` here.  I am going to split them out
    //    here rather than in the lexer.
    //    --------------------------------------------------------------------------
    if (Optional(TOK_UNIVERSAL_INT_LITERAL)) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_UNIVERSAL_REAL_LITERAL)) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_NULL)) {
        m.Commit();
        return true;
    }


    if (ParseAggregate()) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_LEFT_PARENTHESIS)) {
        if (!ParseExpression()) return false;

        if (Optional(TOK_RIGHT_PARENTHESIS)) {
            m.Commit();
            return true;
        }

        switch (tokens.Current()) {
        case TOK_COMMA:
        case TOK_WHEN:
        case TOK_OTHERS:
        case TOK_DOUBLE_DOT:
        case TOK_VERTICAL_BAR:
        case TOK_ARROW:
            loc = tokens.SourceLocation();
            if (ParseAggregateMore()) {
                SourceLoc_t loc = tokens.SourceLocation();

                if (!Require(TOK_RIGHT_PARENTHESIS)) {
                    diags.Error(loc, DiagID::MissingRightParen, { "aggregate" } );
                    // -- keep going
                }

                m.Commit();
                return true;
            }

            diags.Error(loc, DiagID::UnknownError, { __FILE__, __PRETTY_FUNCTION__, std::to_string(__LINE__) } );
            //    fall through
        default:
            m.Reset();
        }
    }


    if (Optional(TOK_STRING_LITERAL)) {
        m.Commit();
        return true;
    }

    if (ParseNameExpr(id)) {
        m.Commit();
        return true;
    }

    if (ParseAllocator()) {
        m.Commit();
        return true;
    }

    if (ParseFunctionCall()) {
        m.Commit();
        return true;
    }

    if (ParseTypeConversion()) {
        m.Commit();
        return true;
    }

    if (ParseQualifiedExpression()) {
        m.Commit();
        return true;
    }

#if 0
    if (Require(TOK_LEFT_PARENTHESIS)) {
        if (!ParseExpression()) return true;
        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
            // -- continue anyway
        }

        m.Commit();
        return true;
    }
#endif

    return false;
}



//
// -- Parse a Relational Operator
//    ---------------------------
bool Parser::ParseRelationalOperator(void)
{
    Production p(*this, "relational_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TOK_AND:
    case TOK_OR:
    case TOK_XOR:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



//
// -- Parse a Binary Adding Operator
//    ------------------------------
bool Parser::ParseBinaryAddingOperator(void)
{
    Production p(*this, "binary_adding_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TOK_PLUS:
    case TOK_MINUS:
    case TOK_AMPERSAND:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



//
// -- Parse a Unary Adding Operator
//    -----------------------------
bool Parser::ParseUnaryAddingOperator(void)
{
    Production p(*this, "unary_adding_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TOK_PLUS:
    case TOK_MINUS:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



//
// -- Parse a Multiplying Operator
//    ----------------------------
bool Parser::ParseMultiplyingOperator(void)
{
    Production p(*this, "multiplying_operator");
    MarkStream m(tokens, diags);

    switch (tokens.Current()) {
    case TOK_STAR:
    case TOK_SLASH:
    case TOK_MOD:
    case TOK_REM:
        tokens.Advance();
        m.Commit();
        return true;

    default:
        return false;
    }
}



//
// -- Parse a Type Conversion
//    -----------------------
bool Parser::ParseTypeConversion(void)
{
    Production p(*this, "type_conversion");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!ParseTypeMark())       return false;
    if (!Require(TOK_LEFT_PARENTHESIS))     return false;
    loc = tokens.SourceLocation();
    if (!ParseExpression()) {
        diags.Error(loc, DiagID::InvalidExpression, { "type conversion" } );
    }
    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
    }

    m.Commit();
    return true;
}



//
// -- Parse a Qualified Expression
//    ----------------------------
bool Parser::ParseQualifiedExpression(void)
{
    Production p(*this, "qualified_expression");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!ParseTypeMark())       return false;
    if (!Require(TOK_APOSTROPHE))   return false;

    if (Require(TOK_LEFT_PARENTHESIS)) {
        loc = tokens.SourceLocation();
        if (!ParseExpression()) {
            diags.Error(loc, DiagID::InvalidExpression, { "qualified expression" } );
        }

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression" } );
            // -- continue anyway
        }

        m.Commit();
        return true;
    }

    if (!ParseAggregate()) return false;

    m.Commit();
    return true;
}



//
// -- Parse an Allocator
//    ------------------
bool Parser::ParseAllocator(void)
{
    Production p(*this, "allocator");
    MarkStream m(tokens, diags);

    if (!Require(TOK_NEW)) return false;

    if (ParseSubtypeIndication()) {
        m.Commit();
        return true;
    } else if (ParseQualifiedExpression()) {
        m.Commit();
        return true;
    }

    return false;
}






