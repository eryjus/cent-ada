//=================================================================================================================
//  parser/ch3/discriminant-part.cc -- Parse a discriminant part
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  discriminant_part ::= ( discriminant_specification {,discriminant_specification} )
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
// -- Parse a Discriminant Part
//    -------------------------
bool Parser::ParseDiscriminantPart(void)
{
    Production p(*this, "disctiminant_part");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseDiscriminantSpecification()) return false;


    loc = tokens.SourceLocation();
    while (Optional(TOK_SEMICOLON)) {
        if (!ParseDiscriminantSpecification()) {
        diags.Error(loc, DiagID::ExtraSemicolon, { "discriminant specification" } );
        // -- continue on in hopes that this does not create a cascade of errors
        }
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "discriminant specification" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



