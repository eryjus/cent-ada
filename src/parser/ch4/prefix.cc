//=================================================================================================================
//  parser/ch4/prefix.cc -- A prefix to a more complicated name expression
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  prefix ::= name
//           | function_call
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Prefix
//    --------------
NamePtr Parser::ParsePrefix(void)
{
    Production p(*this, "prefix");
    NamePtr rv = nullptr;

    if ((rv = std::move(ParseNameExpr())) != nullptr)       return rv;
    if ((rv = std::move(ParseFunctionCall())) != nullptr)   return rv;

    return nullptr;
}



