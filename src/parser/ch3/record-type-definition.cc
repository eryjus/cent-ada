//=================================================================================================================
//  parser/ch3/record-type-definition.cc -- All the possible definitions for a record type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  record_type_definition ::= record component_list end record
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
// -- Parse a Record Type Definition
//    ------------------------------
bool Parser::ParseRecordTypeDefinition(void)
{
    Production p(*this, "record_type_definition");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;



    //
    // -- this production starts with a TOK_RECORD
    //    ----------------------------------------
    if (!Require(TOK_RECORD)) return false;


    //
    // -- then is followed by a list of components
    //    ----------------------------------------
    if (!ParseComponentList()) return false;



    //
    // -- and then by TOK_END and TOK_RECORD again
    //    ----------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "record component list" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RECORD)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "record" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}




