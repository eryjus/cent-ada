//=================================================================================================================
//  parser/ch3/component-subtype-definition.cc -- Parse a component subtype definition
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  component_subtype_definition ::= subtype_indication
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
// -- Parse a Component Subtype Definition
//    ------------------------------------
bool Parser::ParseComponentSubtypeDefinition(void)
{
    Production p(*this, "component_subtype_definition");

    if (ParseSubtypeIndication())   return true;

    return false;
}



