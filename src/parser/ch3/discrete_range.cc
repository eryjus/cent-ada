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
DiscreteRangePtr Parser::ParseDiscreteRange(void)
{
    Production p(*this, "discrete_range");
    DiscreteRangePtr rv;

    if ((rv = std::move(ParseDiscreteSubtypeIndication())) != nullptr)   return rv;
    if ((rv = std::move(ParseRange())) != nullptr)                       return rv;

    return nullptr;
}



