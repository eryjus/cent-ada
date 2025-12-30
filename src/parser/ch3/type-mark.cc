//=================================================================================================================
//  parser/ch3/type-mark.cc -- a type mark is 2 special cases for name
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  type_mark ::= type_name | subtype_name
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
// -- Parse a Type Mark
//    -----------------
bool Parser::ParseTypeMark(void)
{
    Production p(*this, "type_mark");

    if (ParseTypeName())        return true;
    if (ParseSubtypeName())     return true;

    return false;
}




