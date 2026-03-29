//=================================================================================================================
//  parser/ch3/derived-type-definition.cc -- A derived type from another type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  derived_type_definition ::= new subtype_indication
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
// -- Parse a Derived Type Definition
//    -------------------------------
DerivedTypeSpecPtr Parser::ParseDerivedTypeDefinition(Id &id)
{
    Production p(*this, "derived_type_definition");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SimpleNamePtr name = nullptr;
    SubtypeIndicationPtr type = nullptr;


    //
    // -- This is just a TOK_NEW with a Subtype Indication
    //    ------------------------------------------------
    if (!Require(TokenType::TOK_NEW)) return nullptr;


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

    name = std::make_unique<SimpleName>(astLoc, id);


    //
    // -- Get the subtype
    //    ---------------
    type = ParseSubtypeIndication();
    if (!type) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;

    cp.Commit();
    m.Commit();

    return std::make_unique<DerivedTypeSpec>(astLoc, /*std::move(name),*/ std::move(type));
}







