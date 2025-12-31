//=================================================================================================================
//  parser/ch3/unconstrained-array-definition.cc -- Define an unconstrained array
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  unconstrained_array_definition ::= array ( index_subtype_definition {, index_subtype_definition} )
//                                         of component_subtype_indication
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
// -- Parse an Unconstrained Array Definition
//    ---------------------------------------
bool Parser::ParseUnconstrainedArrayDefinition(Id &id)
{
    Production p(*this, "unconstrained_array_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    SourceLoc_t loc;


    //
    //
    // -- Start by adding a new Array Type with the name
    //    ----------------------------------------------
    ArrayTypeSymbol *type = scopes.Declare(std::make_unique<ArrayTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    // -- Start parse with the first 2 required tokens
    //    --------------------------------------------
    if (!Require(TOK_ARRAY)) return false;
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;


    //
    // -- now, there should be an index definition
    //    ----------------------------------------
    if (!ParseIndexSubtypeDefinition()) return false;



    //
    // -- now, some optional additional indices
    //    -------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseIndexSubtypeDefinition()) {
            diags.Error(loc, DiagID::ExtraComma, { "index_subtype_definition" } );
            // -- continue on in hopes of finding more errors

            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- The closing paren is required
    //    -----------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, {"array index subtype definition"});
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Wrap up the rest of the production
    //    ----------------------------------
    if (!Require(TOK_OF)) return false;
    if (!ParseComponentSubtypeIndication()) return false;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}



