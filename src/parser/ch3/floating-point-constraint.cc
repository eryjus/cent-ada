//=================================================================================================================
//  parser/ch3/floating-point-constraint.cc -- Parse a floating point constraint
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  floating_point_constraint ::= floating_accuracy_definition [range_constraint]
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
// -- Parse a Floating Point Constraint
//    ---------------------------------
bool Parser::ParseFloatingPointConstraint(Id &id)
{
    Production p(*this, "floating_point_constraint");
    MarkScope s(scopes);


    if (!id.name.empty()) {
        scopes.Declare(std::make_unique<RealTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));
    }


    //
    // -- Check on the Floating Point Accuracy Definition
    //    -----------------------------------------------
    if (!ParseFloatingAccuracyDefinition()) return false;


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



