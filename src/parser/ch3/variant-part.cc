//=================================================================================================================
//  parser/ch3/variant-part.cc -- Parse a record variant part
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
VariantPartPtr Parser::ParseVariantPart(RecordTypeSymbol *rec)
{
    Production p(*this, "variant_part");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    VariantListPtr variants = std::make_unique<VariantList>();
    NamePtr name = nullptr;
    VariantPtr variant = nullptr;


    //
    // -- Start this off with a TOK_CASE token
    //    ------------------------------------
    if (!Require(TokenType::TOK_CASE)) return nullptr;


    //
    // -- Check for a simple name
    //    -----------------------
    loc = tokens.SourceLocation();
    if ((name = std::move(ParseDiscriminantSimpleName())) == nullptr) return nullptr;


    //
    // -- parse the variants
    //    ------------------
    if (!Require(TokenType::TOK_IS)) return nullptr;
    if ((variant = std::move(ParseVariant(rec))) ==nullptr) return nullptr;
    variants->push_back(std::move(variant));

    while ((variant = std::move(ParseVariant(rec))) != nullptr) {
        variants->push_back(std::move(variant));
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
    VariantPartPtr rv = std::make_unique<VariantPart>(astLoc, std::move(name), std::move(variants));

    m.Commit();
    return rv;
}



