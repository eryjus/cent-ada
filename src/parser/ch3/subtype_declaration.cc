//=================================================================================================================
//  parser/ch3/subtype-declaration.cc -- All the permutations needed to parse a subtype declaration
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  subtype_declaration ::= subtype identifier is subtype_indication ;
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
// -- Parse a Subtype Declaration
//    ---------------------------
bool Parser::ParseSubtypeDeclaration(void)
{
    Production p(*this, "subtype_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::string id;
    SourceLoc_t loc;


    //
    // -- start with a TOK_SUBTYPE token
    //    ------------------------------
    if (!Require(TOK_SUBTYPE)) return false;


    //
    // -- Get the type name and check if its used
    //    ---------------------------------------
    loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return false;

    if (scopes.IsLocalDefined(id)) {
        diags.Error(loc, DiagID::DuplicateName, { id } );

        const std::vector<Symbol *> *vec = scopes.Lookup(std::string_view(id));
        SourceLoc_t loc2 = vec->at(0)->loc;
        diags.Error(loc, DiagID::DuplicateName2, { } );
    } else {
        scopes.Declare(std::make_unique<Symbol>(id, Symbol::SymbolKind::Type, loc, scopes.CurrentScope()));
    }


    //
    // -- The definition of the subtype; TOK_IS and the subtype_indication
    //    must be present for this production to be valid.
    //    ----------------------------------------------------------------
    if (!Require(TOK_IS)) return false;
    if (!ParseSubtypeIndication()) return false;



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "subtype declaration" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}




