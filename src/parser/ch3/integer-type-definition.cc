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
bool Parser::ParseIntegerTypeDefinition(Id &id)
{
    Production p(*this, "integer_type_definition");
    MarkScope s(scopes);


    scopes.Declare(std::make_unique<IntegerTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));

    if (ParseRangeConstraint()) {
        s.Commit();
        return true;
    }

    return false;
}



