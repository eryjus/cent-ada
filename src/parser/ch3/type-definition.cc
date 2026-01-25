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
TypeSpecPtr Parser::ParseTypeDefinition(Id &id)
{
    Production p(*this, "type_definition");
    TypeSpecPtr rv = nullptr;

    if ((rv = std::move(ParseEnumerationTypeDefinition(id))) != nullptr) return std::move(rv);
    if ((rv = std::move(ParseIntegerTypeDefinition(id))) != nullptr)     return std::move(rv);
    if ((rv = std::move(ParseRealTypeDefinition(id))) != nullptr)        return std::move(rv);
    if ((rv = std::move(ParseArrayTypeDefinition(id))) != nullptr)       return std::move(rv);
    if ((rv = std::move(ParseRecordTypeDefinition(id))) != nullptr)      return std::move(rv);
    if ((rv = std::move(ParseAccessTypeDefinition(id))) != nullptr)      return std::move(rv);
    if ((rv = std::move(ParseDerivedTypeDefinition(id))) != nullptr)     return std::move(rv);
    return nullptr;
}



