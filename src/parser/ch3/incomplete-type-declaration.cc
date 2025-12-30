//=================================================================================================================
//  parser/ch3/incomplete-type-declaration.cc -- Declare an incomplete type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  incomplete_type_declaration ::= type identifier [discriminant_part] ;
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
// -- Parse an Incomplete Type Declaration
//    ------------------------------------
bool Parser::ParseIncompleteTypeDeclaration(void)
{
    Production p(*this, "incomplete_type_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::string id;
    SourceLoc_t loc;
    std::string where = "incomplete type identifier";


    //
    // -- Start with the definitive tokens
    //    --------------------------------
    if (!Require(TOK_TYPE)) return false;
    loc = tokens.SourceLocation();


    //
    // -- Get the name of the incomplete type declaration
    //    -----------------------------------------------
    if (!RequireIdent(id)) return false;

    if (scopes.IsLocalDefined(id)) {
        diags.Error(loc, DiagID::DuplicateName, { id } );
        // -- TODO: issue the second part of this error
    } else {
        scopes.Declare(std::make_unique<Symbol>(id, Symbol::SymbolKind::Type, loc, scopes.CurrentScope()));
    }


    //
    // -- this is optional
    //    ----------------
    if (ParseDiscriminantPart()) where = "discriminant part";


    //
    // -- End with a semicolon
    //    --------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { where } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}



