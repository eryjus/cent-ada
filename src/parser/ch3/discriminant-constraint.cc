//=================================================================================================================
//  parser/ch3/discriminant-constraint.cc -- Parse a discriminant constraint
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  discriminant_constraint ::= ( discriminant_association {, discriminant_association} )
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
// -- Parse a Discriminant Constraint
//    -------------------------------
bool Parser::ParseDiscriminantConstraint(void)
{
    Production p(*this, "discriminant_constraint");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;


    //
    // -- Start with the required left paren token and the first association
    //    ------------------------------------------------------------------
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantAssociation()) return false;


    //
    // -- now get the optionsl additional associations
    //    --------------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseDiscriminantAssociation()) {
            diags.Error(loc, DiagID::ExtraComma, { "discriminant association" } );
            // -- continue on in hopes of competing the parse
            break;
        }

        loc = tokens.SourceLocation();
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "discriminant association" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



