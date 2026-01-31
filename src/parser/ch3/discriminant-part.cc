//=================================================================================================================
//  parser/ch3/discriminant-part.cc -- Parse a discriminant part
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
DiscriminantSpecificationListPtr Parser::ParseDiscriminantPart(void)
{
    Production p(*this, "discriminant_part");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();
    DiscriminantSpecificationListPtr rv = std::make_unique<DiscriminantSpecificationList>();
    DiscriminantSpecificationPtr spec = nullptr;

    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;

    spec = ParseDiscriminantSpecification();

    if (!spec) return nullptr;

    rv->push_back(std::move(spec));

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_SEMICOLON)) {
        spec = ParseDiscriminantSpecification();
        if (spec) {
            rv->push_back(std::move(spec));
        } else {
        diags.Error(loc, DiagID::ExtraSemicolon, { "discriminant specification" } );
        // -- continue on in hopes that this does not create a cascade of errors
        }
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "discriminant specification" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return rv;
}



