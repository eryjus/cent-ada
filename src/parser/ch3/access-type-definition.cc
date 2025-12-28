//=================================================================================================================
//  parser/ch3/access-type-definition.cc -- Define an access type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  access_type_definition ::= access subtype_indication
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
// -- Parse an Access Type Definition
//    -------------------------------
bool Parser::ParseAccessTypeDefinition(void)
{
    Production p(*this, "access_type_definition");
    MarkStream m(tokens, diags);


    //
    // -- Parse the sequence
    //    ------------------
    if (!Require(TOK_ACCESS)) return false;
    if (!ParseSubtypeIndication()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



