//=================================================================================================================
//  parser/ch4/aggregate.cc -- An aggregate combines component values into a composite record or array
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
ExprPtr Parser::ParseAggregate(void)
{
    Production p(*this, "aggregate");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    ComponentAssociationListPtr list = std::make_unique<ComponentAssociationList>();
    ComponentAssociationPtr assoc = nullptr;

    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))          return nullptr;
    if ((assoc = std::move(ParseComponentAssociation())) == nullptr)   return nullptr;

    list->push_back(std::move(assoc));

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        if ((assoc = std::move(ParseComponentAssociation())) != nullptr) {
            list->push_back(std::move(assoc));
        } else {
            diags.Error(loc, DiagID::ExtraComma, { "component association" } );
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "component_association" } );
    }


    AggregateExprPtr rv = std::make_unique<AggregateExpr>(astLoc, std::move(list));

    m.Commit();
    return std::move(rv);
}



#if 0
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
#endif



