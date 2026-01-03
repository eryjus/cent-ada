//=================================================================================================================
//  parser/ch3/subtype-indication.cc -- an indication of a defined type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  subtype_indication ::= type_mark [constraint]
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
// -- Parse a Subtype Indication
//    --------------------------
bool Parser::ParseSubtypeIndication(void)
{
    Production p(*this, "subtype_indication");
    MarkStream m(tokens, diags);


    //
    // -- Find a type mark and then optionally a constraint
    //    -------------------------------------------------
    if (!ParseTypeMark()) return false;
    ParseConstraint();



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}





