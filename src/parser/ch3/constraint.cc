//=================================================================================================================
//  parser/ch3/constraint.cc -- All the permutations needed to parse a constraint
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
ConstraintPtr Parser::ParseConstraint(void)
{
    Production p(*this, "constraint");
    NumericTypeSpecPtr real = nullptr;
    ConstraintPtr rv = nullptr;
    SourceLoc_t astLoc = tokens.SourceLocation();
    Id id;


    //
    // -- Range Constraint
    //    ----------------
    rv = ParseRangeConstraint();
    if (rv) {
        p.At("Range");
        return rv;
    }


    //
    // -- Floating Point Constraint
    //    -------------------------
    real = ParseFloatingPointConstraint(id);
    if (real) {
        p.At("Float");
        return std::make_unique<RealConstraint>(astLoc, std::move(real));
    }


    //
    // -- Fixed Point Constraint
    //    ----------------------
    real = ParseFixedPointConstraint(id);
    if (real) {
        p.At("Fixed");
        return std::make_unique<RealConstraint>(astLoc, std::move(real));
    }


    //
    // -- Index Constraint
    //    ----------------
    rv = ParseIndexConstraint();
    if (rv) {
        p.At("Index");
        return rv;
    }


    //
    // -- Discriminant Constraint
    //    -----------------------
    rv = ParseDiscriminantConstraint();
    if (rv) {
        p.At("Discriminant");
        return rv;
    }


    //
    // -- None of the above
    //    -----------------
    p.At("failed");

    return nullptr;
}




