//=================================================================================================================
//  parser/ch3/proper-body.cc -- Parse iterations of a proper-body
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  proper_body ::= subprogram_body | package_body | task_body
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
// -- Parse a Proper Body
//    -------------------
bool Parser::ParseProperBody(void)
{
    Production p(*this, "proper_body");

    if (ParseSubprogramBody())      return true;
    if (ParsePackageBody())         return true;
    if (ParseTaskBody())            return true;

    return false;
}



