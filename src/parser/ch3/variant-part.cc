//=================================================================================================================
//  parser/ch3/variant-part.cc -- Parse a record variant part
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  variant_part ::= case discriminant_simple_name is variant {| variant} end case ;
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
// -- Parse a Variant Part
//    --------------------
bool Parser::ParseVariantPart(RecordTypeSymbol *rec)
{
    Production p(*this, "variant_part");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t loc;


    //
    // -- Start this off with a TOK_CASE token
    //    ------------------------------------
    if (!Require(TokenType::TOK_CASE)) return false;


    //
    // -- Check for a simple name
    //    -----------------------
    loc = tokens.SourceLocation();
    if (!ParseDiscriminantSimpleName(id)) return false;


    //
    // -- parse the variants
    //    ------------------
    if (!Require(TokenType::TOK_IS)) return false;
    if (!ParseVariant(rec)) return false;

    while (ParseVariant(rec)) {
        // -- for the moment, nothing is needed here
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "variant part" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_CASE)) {
        diags.Error(loc, DiagID::MissingRightParen, { "variant part" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "variant part" } );
        // -- continue on in hopes that this does not create a cascade of errors

    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



