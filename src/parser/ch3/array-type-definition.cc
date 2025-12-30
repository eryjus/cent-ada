//=================================================================================================================
//  parser/ch3/array-type-definition.cc -- All the possible definitions for an array type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  array_type_definition ::= unconstrained_array_definition | constrained_array_definitino
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
// -- Parse an Array Type Definition
//    ------------------------------
bool Parser::ParseArrayTypeDefinition(const std::string &id)
{
    Production p(*this, "array_type_definition");

    if (ParseUnconstrainedArrayDefinition(id))    return true;
    if (ParseConstrainedArrayDefinition(id))      return true;

    return false;
}



