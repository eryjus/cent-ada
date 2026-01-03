//=================================================================================================================
//  parser/ch3/type-definition.cc -- All the permutations to define a type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  type_definition ::= enumeration_type_definition
//                    | integer_type_definition
//                    | real_type_definition
//                    | array_type_definition
//                    | record_type_definition
//                    | access_type_definition
//                    | derived_type_definition
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
// -- Parse a Type Definition
//    ------------------------
bool Parser::ParseTypeDefinition(Id &id)
{
    Production p(*this, "type_definition");

    if (ParseEnumerationTypeDefinition(id)) return true;
    if (ParseIntegerTypeDefinition(id))     return true;
    if (ParseRealTypeDefinition(id))        return true;
    if (ParseArrayTypeDefinition(id))       return true;
    if (ParseRecordTypeDefinition(id))      return true;
    if (ParseAccessTypeDefinition(id))      return true;
    if (ParseDerivedTypeDefinition(id))     return true;
    return false;
}



