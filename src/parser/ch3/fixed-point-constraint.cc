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
bool Parser::ParseFixedPointConstraint(Id &id)
{
    Production p(*this, "fixed_point_constraint");
    MarkScope s(scopes);


    if (!id.name.empty()) {
        scopes.Declare(std::make_unique<RealTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));
    }


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
    s.Commit();
    return true;
}


