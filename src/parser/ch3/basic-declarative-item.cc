//=================================================================================================================
//  parser/ch3/basic-declarative-part.cc -- Parse a basic declarative item
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  basic_declarative_item ::= basic_declaration
//                           | representation_clause
//                           | use_clause
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-27  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Basic Declarative Item
//    ------------------------------
NodePtr Parser::ParseBasicDeclarativeItem(void)
{
    Production p(*this, "basic_declarative_item");

    if (ParseBasicDeclaration())        { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseRepresentationClause())    { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseUseClause())               { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }

    return nullptr;
}



