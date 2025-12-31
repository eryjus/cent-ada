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
bool Parser::ParseAccessTypeDefinition(Id &id)
{
    Production p(*this, "access_type_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);


    scopes.Declare(std::make_unique<AccessTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));

    //
    // -- Parse the sequence
    //    ------------------
    if (!Require(TOK_ACCESS)) return false;
    if (!ParseSubtypeIndication()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}



