//=================================================================================================================
//  parser/ch3/type-declaration.cc -- All the permutations needed to parse a type declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  type_declaration ::= full_type_declaration
//                     | incomplete_type_declaration
//                     | private_type_declaration
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Type Declaration
//    ------------------------
TypeDeclPtr Parser::ParseTypeDeclaration(void)
{
    Production p(*this, "type_declaration");
    TypeDeclPtr rv = nullptr;


    rv = ParseFullTypeDeclaration();
    if (rv) return rv;

    rv = ParseIncompleteTypeDeclaration();
    if (rv) return rv;

    rv = ParsePrivateTypeDeclaration();
    if (rv) return rv;


    return nullptr;
}






