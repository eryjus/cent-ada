//=================================================================================================================
//  parser/ch3/subtype-declaration.cc -- All the permutations needed to parse a subtype declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
TypeDeclPtr Parser::ParseSubtypeDeclaration(void)
{
    Production p(*this, "subtype_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    Id id;
    SourceLoc_t loc;
    SourceLoc_t astLoc;
    SubtypeIndicationPtr type = nullptr;


    //
    // -- start with a TOK_SUBTYPE token
    //    ------------------------------
    if (!Require(TokenType::TOK_SUBTYPE)) return nullptr;


    //
    // -- Get the type name and check if its used
    //    ---------------------------------------
    loc = tokens.SourceLocation();
    if (!RequireIdent(id)) return nullptr;

    if (scopes.IsLocalDefined(id.name)) {
        diags.Error(loc, DiagID::DuplicateName, { id.name } );

        const std::vector<Symbol *> *vec = scopes.Lookup(std::string_view(id.name));
        SourceLoc_t loc2 = vec->at(0)->loc;
        diags.Error(loc, DiagID::DuplicateName2, { } );
    } else {
        scopes.Declare(std::make_unique<SubtypeSymbol>(id.name, id.loc, scopes.CurrentScope()));
    }


    //
    // -- The definition of the subtype; TOK_IS and the subtype_indication
    //    must be present for this production to be valid.
    //    ----------------------------------------------------------------
    if (!Require(TokenType::TOK_IS)) return nullptr;
    if ((type = std::move(ParseSubtypeIndication())) == nullptr) return nullptr;



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "subtype declaration" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    TypeDeclPtr rv = std::make_unique<TypeDecl>(astLoc, id, nullptr, std::move(type));

    s.Commit();
    m.Commit();
    return std::move(rv);
}




