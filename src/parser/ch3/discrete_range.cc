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
    SubtypeIndicationPtr sType = nullptr;
    SourceLoc_t astLoc = tokens.SourceLocation();


    //
    // -- Try a subtype indication
    //    ------------------------
    sType = ParseDiscreteSubtypeIndication();
    if (sType) return std::make_unique<SubtypeRange>(astLoc, std::move(sType));


    //
    // -- Try a range
    //    -----------
    rv = ParseRange();
    if (rv) return rv;


    //
    // -- nothing found
    //    -------------
    return nullptr;
}



