//=================================================================================================================
//  parser/ch4/attribute-designator.cc -- An attribute designator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  attribute_designator ::= simple_name {( universal_static_expression )}
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
// -- Parse an Attribute Designator
//    -----------------------------
AttributeNamePtr Parser::ParseAttributeDesignator(NamePtr &prefix)
{
    Production p(*this, "attribute_designator");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;
    Id id;


    //
    // -- handle 3 special cases where the attribute name is not just an ID, but also a token
    //    -----------------------------------------------------------------------------------
    if (Optional(TokenType::TOK_DIGITS)) {
        id = { "digits", loc };
        name = std::make_unique<SimpleName>(loc, id);
    } else if (Optional(TokenType::TOK_DELTA)) {
        id = { "delta", loc };
        name = std::make_unique<SimpleName>(loc, id);
    } else if (Optional(TokenType::TOK_RANGE)) {
        id = { "range", loc };
        name = std::make_unique<SimpleName>(loc, id);
    } else {
        name = ParseSimpleName();
        if (!name) return nullptr;
    }

    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        expr = ParseExpression();
        if (!expr) return nullptr;

        loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression"} );
            // -- allow to continue
        }
    }



    m.Commit();
    return std::make_unique<AttributeName>(loc, std::move(prefix), std::move(name), nullptr);
}



