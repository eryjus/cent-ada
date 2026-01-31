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
DeclPtr Parser::ParseBasicDeclarativeItem(void)
{
    Production p(*this, "basic_declarative_item");
    DeclPtr rv = nullptr;

    rv = ParseBasicDeclaration();
    if (rv) {
        p.At("BasicDeclaration");
        return rv;
    }


    if (ParseRepresentationClause())    { return nullptr; }
    if (ParseUseClause())               { return nullptr; }


    return nullptr;
}



