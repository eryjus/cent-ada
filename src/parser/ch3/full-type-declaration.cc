//=================================================================================================================
//  parser/ch3/full-type-declaration.cc -- All the permutations needed to parse a full type declaration
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  full_type_declaration ::= type identifier [discriminant_part] is type_definition ;
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
// -- Parse a Full Type Declaration
//    -----------------------------
bool Parser::ParseFullTypeDeclaration(void)
{
    Production p(*this, "full_type_definition");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    Id id;


    //
    // -- the first consumable is a TOK_TYPE token
    //    ----------------------------------------
    if (!Require(TokenType::TOK_TYPE)) return false;


    //
    // -- Now we get the type name and check it for duplicates
    //    ----------------------------------------------------
    SourceLoc_t loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;



    //
    // -- Here is an optional discriminant part
    //    -------------------------------------
    ParseDiscriminantPart();



    //
    // -- The definition of the type; TOK_IS must be present for this
    //    production to be valid.  See incomplete_type_declaration.
    //    -----------------------------------------------------------
    if (!Require(TokenType::TOK_IS)) return false;
    ParseTypeDefinition(id);


    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "type definition" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}





