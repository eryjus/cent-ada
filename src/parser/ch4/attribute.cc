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
    NamePtr prefix = nullptr;

    if (!ParsePrefix())                             return nullptr;
    if (!Require(TokenType::TOK_APOSTROPHE))        return nullptr;
    if (!ParseAttributeDesignator(prefix))                return nullptr;


    AttributeNamePtr rv = std::make_unique<AttributeName>(astLoc, nullptr, nullptr, nullptr);


    m.Commit();
    return std::move(rv);
}



//
// -- Parse an Attribute Suffix for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
NamePtr Parser::ParseName_AttributeSuffix(NamePtr &prefix)
{
    Production p(*this, "name(attribute)");
    MarkStream m(tokens, diags);
    NamePtr rv = nullptr;

    if (!Require(TokenType::TOK_APOSTROPHE))        return nullptr;
    if ((rv = ParseAttributeDesignator(prefix)) != nullptr)                return nullptr;

    m.Commit();
    return rv;
}



