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
    SymbolTable::Checkpoint cp;
    Id id;
    SourceLoc_t loc = tokens.SourceLocation();
    SourceLoc_t astLoc = loc;
    SubtypeIndicationPtr type = nullptr;


    //
    // -- start with a TOK_SUBTYPE token
    //    ------------------------------
    if (!Require(TokenType::TOK_SUBTYPE)) {
        p.At("no TOK_SUBTYPE");
        return nullptr;
    }


    //
    // -- Get the type name and check if its used
    //    ---------------------------------------
    loc = TokenStream::Get().SourceLocation();
    if (!RequireIdent(id)) {
        p.At("no TOK_IDENT");
        return nullptr;
    }

    Symbol *sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            sym->kind = SymbolTable::SymbolKind::Type;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::Type);
    }


    //
    // -- The definition of the subtype; TOK_IS and the subtype_indication
    //    must be present for this production to be valid.
    //    ----------------------------------------------------------------
    if (!Require(TokenType::TOK_IS)) {
        p.At("no TOK_IS");
        return nullptr;
    }

    type = ParseSubtypeIndication();
    if (!type) {
        p.At("no Subtype Indication");
        return nullptr;
    }



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "subtype declaration" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    TypeDeclPtr rv = std::make_unique<TypeDecl>(astLoc, id, nullptr, std::move(type));

    p.At("Success");
    cp.Commit();
    m.Commit();
    return std::move(rv);
}




