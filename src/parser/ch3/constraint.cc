//=================================================================================================================
//  parser/ch3/constraint.cc -- All the permutations needed to parse a constraint
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  constraint ::= range_constraint
//               | floating_point_constraint
//               | fixed_point_constraint
//               | index_constraint
//               | discriminant_constraint
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
// -- Parse a Constraint
//    ------------------
bool Parser::ParseConstraint(void)
{
    Production p(*this, "constraint");
    std::string id;

    if (ParseRangeConstraint())             return true;
    if (ParseFloatingPointConstraint(id))   return true;
    if (ParseFixedPointConstraint(id))      return true;
    if (ParseIndexConstraint())             return true;
    if (ParseDiscriminantConstraint())      return true;

    return false;
}




