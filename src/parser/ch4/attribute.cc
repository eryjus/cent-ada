//=================================================================================================================
//  parser/ch4/attribute.cc -- An attribute denotes a basic operation of an entity given by a prefix.
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  attribute ::= prefix ' attribute_designator
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
// -- Parse an Attribute
//    ------------------
AttributeNamePtr Parser::ParseAttribute(void)
{
    Production p(*this, "attribute");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();

    if (!ParsePrefix())                             return nullptr;
    if (!Require(TokenType::TOK_APOSTROPHE))        return nullptr;
    if (!ParseAttributeDesignator())                return nullptr;


    AttributeNamePtr rv = std::make_unique<AttributeName>(astLoc, nullptr, nullptr, nullptr);


    m.Commit();
    return std::move(rv);
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

    if (!Require(TokenType::TOK_APOSTROPHE))        return false;
    if (!ParseAttributeDesignator())                return false;

    m.Commit();
    return true;
}



