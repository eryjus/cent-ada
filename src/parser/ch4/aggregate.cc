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
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc= astLoc;
    ComponentAssociationListPtr list = std::make_unique<ComponentAssociationList>();
    ComponentAssociationPtr assoc = nullptr;

    if (!Require(TokenType::TOK_LEFT_PARENTHESIS))          return nullptr;

    assoc = ParseComponentAssociation();
    if (!assoc)   return nullptr;

    list->push_back(std::move(assoc));

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        assoc = ParseComponentAssociation();
        if (assoc) {
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



    m.Commit();

    return std::make_unique<AggregateExpr>(astLoc, std::move(list));
}




