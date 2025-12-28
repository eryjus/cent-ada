//=================================================================================================================
//  parser/ch3/later-declarative-part.cc -- Parse a later declarative item
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseLaterDeclarativeItem(void)
{
    Production p(*this, "later_declarative_item");

    if (ParseBody())                        return true;
    if (ParseSubprogramDeclaration())       return true;
    if (ParsePackageDeclaration())          return true;
    if (ParseTaskDeclaration())             return true;
    if (ParseGenericDeclaration())          return true;
    if (ParseUseClause())                   return true;
    if (ParseGenericInstantiation())        return true;

    return false;
}



