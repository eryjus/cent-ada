//=================================================================================================================
//  parser/ch3/later-declarative-part.cc -- Parse a later declarative item
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  later_declarative_item ::= body
//                           | subprogram_declaration
//                           | package_declaration
//                           | task_declaration
//                           | generic_declaration
//                           | use_clause
//                           | generic_instantiation
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
// -- Parse a Later Declarative Item
//    ------------------------------
NodePtr Parser::ParseLaterDeclarativeItem(void)
{
    Production p(*this, "later_declarative_item");

    if (ParseBody())                        { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseSubprogramDeclaration())       { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParsePackageDeclaration())          { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseTaskDeclaration())             { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseGenericDeclaration())          { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseUseClause())                   { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }
    if (ParseGenericInstantiation())        { return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation())); }

    return nullptr;
}



