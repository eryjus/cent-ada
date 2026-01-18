//=================================================================================================================
//  parser/ch3/real-type-definition.cc -- Parse a real type definition
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
NumericTypeSpecPtr Parser::ParseRealTypeDefinition(Id &id)
{
    Production p(*this, "real_type_definition");
    NumericTypeSpecPtr rv = nullptr;

    if ((rv = std::move(ParseFloatingPointConstraint(id))) != nullptr)   return std::move(rv);
    if ((rv = std::move(ParseFixedPointConstraint(id))) != nullptr)      return std::move(rv);

    return nullptr;
}



