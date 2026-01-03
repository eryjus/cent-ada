//=================================================================================================================
//  parser/ch3/enumeration-literal-specification.cc -- Specify an enumeration literal
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  enumeration_literal_specification ::= enumeration_literal
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
// -- Parse an Enumeration Literal Specification
//    ------------------------------------------
bool Parser::ParseEnumerationLiteralSpecification(EnumTypeSymbol *type)
{
    Production p(*this, "enumeration_literal_specification");

    if (ParseEnumerationLiteral(type)) return true;

    return false;
}




