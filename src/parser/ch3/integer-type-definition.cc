//=================================================================================================================
//  parser/ch3/integer-type-definition.cc -- Parse an integer type definition
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  integer_type_definition ::= range_constraint
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
// -- Parse an Integer Type Definition
//    --------------------------------
bool Parser::ParseIntegerTypeDefinition(void)
{
    Production p(*this, "integer_type_definition");

    if (ParseRangeConstraint()) return true;

    return false;
}



