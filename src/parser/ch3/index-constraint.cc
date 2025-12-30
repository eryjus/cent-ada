//=================================================================================================================
//  parser/ch3/index-constraint.cc -- Define an index constraint
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  index_constraint ::= ( discrete_range {, discrete_range} )
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
// -- Parse an Index Constraint
//    -------------------------
bool Parser::ParseIndexConstraint(void)
{
    Production p(*this, "index_constraint");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;


    //
    // -- This production start with a paren
    //    ----------------------------------
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;


    //
    // -- and then a range for the index
    //    ------------------------------
    if (!ParseDiscreteRange()) return false;


    //
    // -- followed by any number of additional indices
    //    --------------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseDiscreteRange()) {
            diags.Error(loc, DiagID::ExtraComma, { "discrete_range" } );

            // -- continue on
            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- The closing paren is required
    //    -----------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, {"discrete range"});
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



