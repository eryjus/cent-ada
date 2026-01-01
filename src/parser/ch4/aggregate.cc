//=================================================================================================================
//  parser/ch4/aggregate.cc -- An aggregate combines component values into a composite record or array
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  aggregate ::= ( component_association {, component_association} )
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse an Aggregate
//    ------------------
bool Parser::ParseAggregate(void)
{
    Production p(*this, "aggregate");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))         return false;
    if (!ParseComponentAssociation())           return false;

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        if (!ParseComponentAssociation()) {
            diags.Error(loc, DiagID::ExtraComma, { "component association" } );
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
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
    while (Optional(TokenType::TOK_COMMA)) {
        if (!ParseComponentAssociation()) {
            diags.Error(loc, DiagID::ExtraComma, { "aggregate" } );
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "component_association" } );
    }

    m.Commit();
    return true;
}




