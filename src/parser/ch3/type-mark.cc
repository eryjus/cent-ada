//=================================================================================================================
//  parser/ch3/type-mark.cc -- a type mark is 2 special cases for name
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
NamePtr Parser::ParseTypeMark(void)
{
    Production p(*this, "type_mark");
    NamePtr rv;

    if ((rv = std::move(ParseTypeName())) != nullptr)        { diags.Debug(rv->GetName()); return rv; }
    if ((rv = std::move(ParseSubtypeName())) != nullptr)     { diags.Debug(rv->GetName()); return rv; }

    return nullptr;
}




