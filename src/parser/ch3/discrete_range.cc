//=================================================================================================================
//  parser/ch3/discrete-range.cc -- Define a discrete range
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  discrete_range ::= discrete_subtype_indication | range
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
// -- Parse Discrete Range
//    --------------------
bool Parser::ParseDiscreteRange(void)
{
    Production p(*this, "discrete_range");

    if (ParseDiscreteSubtypeIndication())   return true;
    if (ParseRange())                       return true;

    return false;
}



