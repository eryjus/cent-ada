//=================================================================================================================
//  parser/ch3/enumeration-type-definition.cc -- Parse an enumeration type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  enumeration_type_definition ::= ( enumeration_literal_specification { , enumeration_literal_specification } )
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
// -- Parse an Enumeration Type Definition
//    ------------------------------------
bool Parser::ParseEnumerationTypeDefinition(Id &id)
{
    Production p(*this, "enumeration_type_definition");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;
    MarkScope s(scopes);


    //
    // -- Start by adding a new Enum Type with the name
    //    ---------------------------------------------
    EnumTypeSymbol *type = scopes.Declare(std::make_unique<EnumTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    //
    // -- The enumeration is enclosed in parens
    //    -------------------------------------
    if (!Require(TOK_LEFT_PARENTHESIS)) return false;
    if (!ParseEnumerationLiteralSpecification(type)) return false;



    //
    // -- there may be any number of enumerations
    //    ---------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TOK_COMMA)) {
        if (!ParseEnumerationLiteralSpecification(type)) {
            diags.Error(loc, DiagID::ExtraComma, { "enumeration type definition" } );
            // -- continue on in hopes that this does not create a cascade of errors

            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- end with a closing paren
    //    ------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "enumeration literal" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}




