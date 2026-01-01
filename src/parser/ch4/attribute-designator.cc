//=================================================================================================================
//  parser/ch4/attribute-designator.cc -- An attribute designator
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseAttributeDesignator(void)
{
    Production p(*this, "attribute_designator");
    MarkStream m(tokens, diags);
    Id id;

    if (!ParseSimpleName(id))           return false;
    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        if (!ParseExpression()) return false;

        SourceLoc_t loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            diags.Error(loc, DiagID::MissingRightParen, { "expression"} );
            // -- allow to continue
        }
    }

    m.Commit();
    return true;
}



