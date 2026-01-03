//=================================================================================================================
//  parser/ch3/body.cc -- Parse iterations of a body
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  body ::= proper_body | body_stub
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
// -- Parse a Body
//    ------------
bool Parser::ParseBody(void)
{
    Production p(*this, "body");

    if (ParseProperBody())  return true;
    if (ParseBodyStub())    return true;

    return false;
}



