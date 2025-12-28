//=================================================================================================================
//  parser/ch3/fixed-point-constraint.cc -- Parse a fixed point constraint
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  fixed_point_constraint ::= fixed_accuracy_definition [range_constraint]
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
// -- Parse a Fixed Point Constraint
//    ------------------------------
bool Parser::ParseFixedPointConstraint(void)
{
    Production p(*this, "fixed_point_constraint");


    //
    // -- Check on the Floating Point Accuracy Definition
    //    -----------------------------------------------
    if (!ParseFixedAccuracyDefinition()) return false;


    //
    // -- and then check on the optional Range Constraint
    //    -----------------------------------------------
    ParseRangeConstraint();


    //
    // -- The parse is good here
    //    ----------------------
    return true;
}


