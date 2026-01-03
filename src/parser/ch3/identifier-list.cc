//=================================================================================================================
//  parser/ch3/identifier-list.cc -- A basic identifier list consisting of 1 or more identifiers
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  identifier_list ::= identifier { , identifier }
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
// -- Parse an Identifier List
//    ------------------------
bool Parser::ParseIdentifierList(IdList *ids)
{
    Production p(*this, "identifier_list");
    MarkStream m(tokens, diags);
    Id id;


    //
    // -- start by clearing the list -- it should be empty but just in case
    //    -----------------------------------------------------------------
    ids->clear();


    //
    // -- Read the first identifier in the list
    //    -------------------------------------
    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;
    ids->push_back(id);


    //
    // -- Now, as long as we have a TOK_COMMA, expect another identifer
    //    -------------------------------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        if (!RequireIdent(id)) {
            diags.Error(loc, DiagID::ExtraComma, { "identifier_list" } );

            // -- continue on as if there was no extra comma
            goto exit;
        }

        ids->push_back(id);
        loc = tokens.SourceLocation();
    }


    //
    // -- At this point, we are going to create the AST node
    //    --------------------------------------------------
exit:

    m.Commit();
    return true;
}




