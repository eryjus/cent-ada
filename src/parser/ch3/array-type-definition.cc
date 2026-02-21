//=================================================================================================================
//  parser/ch3/array-type-definition.cc -- All the possible definitions for an array type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  array_type_definition ::= unconstrained_array_definition | constrained_array_definitino
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
// -- Parse an Array Type Definition
//    ------------------------------
ArrayTypeSpecPtr Parser::ParseArrayTypeDefinition(Id &id)
{
    Production p(*this, "array_type_definition");
    ArrayTypeSpecPtr rv = nullptr;

    rv = ParseUnconstrainedArrayDefinition(id);
    if (rv) {
        p.At("Unconstrained Array");
        return rv;
    }

    rv = ParseConstrainedArrayDefinition(id);
    if (rv) {
        p.At("Constrained Array");
        return rv;
    }

    p.At("no match");
    return nullptr;
}



