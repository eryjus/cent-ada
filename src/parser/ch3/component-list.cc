//=================================================================================================================
//  parser/ch3/component-list.cc -- Any components in the record type definition
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  component_list ::= null ;
//                   | component_declaration {component_declaration}
//                   | {component_declaration} variant_part
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
// -- Parse a Component List
//    ----------------------
bool Parser::ParseComponentList(RecordTypeSymbol *rec)
{
    Production p(*this, "component_list");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;



    //
    // -- Handle the trivial case first: TOK_NULL;
    //    ----------------------------------------
    if (Require(TOK_NULL)) {
        loc = tokens.SourceLocation();
        if (!Require(TOK_SEMICOLON)) {
            diags.Error(loc, DiagID::MissingSemicolon, { "TOK_NULL" } );
            // -- continue on in hopes that this does not create a cascade of errors
        }


        //
        // -- Consider this parse to be good
        //    ------------------------------
        m.Commit();
        return true;
    }


    //
    // -- from here we need to make sure that if we do not have a `variant_part`,
    //    there is at least 1 `component_declaration`.  Set up the check later.
    //    -----------------------------------------------------------------------
    int declCnt = 0;
    bool hasVariant = false;


    //
    // -- Parse all component declarations
    //    --------------------------------
    loc = tokens.SourceLocation();
    while (ParseComponentDeclaration(rec)) {
        declCnt ++;
    }


    //
    // -- Check for the optional variant part
    //    -----------------------------------
    if (ParseVariantPart(rec)) {
        hasVariant = true;
    }



    //
    // -- Finally, make sure we have at least one or the other
    //    ----------------------------------------------------
    if (declCnt == 0 && hasVariant == false) {
        diags.Error(loc, DiagID::MissingRecordComponentDefinitions);
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



