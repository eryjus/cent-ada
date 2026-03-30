//=================================================================================================================
//  parser/ch3/access-type-definition.cc -- Define an access type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  access_type_definition ::= access subtype_indication
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
// -- Parse an Access Type Definition
//    -------------------------------
AccessTypeSpecPtr Parser::ParseAccessTypeDefinition(Id &id)
{
    Production p(*this, "access_type_definition");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SubtypeIndicationPtr type = nullptr;



    //
    // -- Parse the sequence
    //    ------------------
    if (!Require(TokenType::TOK_ACCESS)) {
        p.At("TOK_ACCESS");
        return nullptr;
    }



    //
    // -- Check for the optional Subtype Indication
    //    -----------------------------------------
    type = ParseSubtypeIndication();
    if (!type) {
        p.At("Subtype Indication");
        return nullptr;
    }



    //
    // -- Manage the symbol table
    //    -----------------------
    Symbol *sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::Type);
    }



    //
    // -- Commit and Exit
    //    ---------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;

    cp.Commit();
    m.Commit();

    SimpleNamePtr name = std::make_unique<SimpleName>(astLoc, id);
    return std::make_unique<AccessTypeSpec>(astLoc, std::move(type));
}



