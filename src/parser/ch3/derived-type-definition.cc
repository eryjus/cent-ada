//=================================================================================================================
//  parser/ch3/derived-type-definition.cc -- A derived type from another type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  derived_type_definition ::= new subtype_indication
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
// -- Parse a Derived Type Definition
//    -------------------------------
bool Parser::ParseDerivedTypeDefinition(void)
{
    Production p(*this, "derived_type_definition");
    MarkStream m(tokens, diags);


    //
    // -- This is just a TOK_NEW with a Subtype Indication
    //    ------------------------------------------------
    if (!Require(TOK_NEW)) return false;
    if (!ParseSubtypeIndication()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}







