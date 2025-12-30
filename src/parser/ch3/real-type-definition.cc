//=================================================================================================================
//  parser/ch3/real-type-definition.cc -- Parse a real type definition
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  real_type_definition ::= floating_point_constraint | fixed_point_constraint
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
// -- Parse a Real Type Definition
//    ----------------------------
bool Parser::ParseRealTypeDefinition(const std::string &id)
{
    Production p(*this, "real_type_definition");

    if (ParseFloatingPointConstraint(id))   return true;
    if (ParseFixedPointConstraint(id))      return true;

    return false;
}



