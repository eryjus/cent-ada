//=================================================================================================================
//  symbol.cc -- Implement the symbol table
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  This file starts from breaking apart `scopes.cc` into separate concerns.
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-28  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- convert a SymbolKind to a string
//    --------------------------------
const std::string &Symbol::to_string(void)
{
    static std::vector<std::string> str = {
        "IncompleteType",
        "Type",
        "Subtype",
        "Object",
        "Constant",
        "EnumerationLiteral",
        "Discriminant",
        "Component",
        "Subprogram",
        "Package",
    };

    return str[(int)kind];
}




