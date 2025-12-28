//=================================================================================================================
//  parser.cc -- Miscellaneous functions and variables for the parser
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
// -- This statically declaraed member in the Mark class needs a physical memory location
//    -----------------------------------------------------------------------------------
int Parser::MarkStream::depth = 0;
bool Parser::Production::trace = false;



//
// -- Check the local symbol table for this ID and if it does not exist, add it
//    -------------------------------------------------------------------------
void Parser::CheckLocalId(std::string &id, SourceLoc_t loc, Symbol::SymbolKind kind)
{
    if (scopes.IsLocalDefined(id)) {
        const std::vector<Symbol *> *vec = scopes.CurrentScope()->LocalLookup(id);

#if 0
        if (kind == Symbol::SymbolKind::Type && sym->kind == Symbol::SymbolKind::IncompleteType) {
            sym->kind = kind;
            return;
        }
        diags.Error(loc, DiagID::DuplicateName, { id } );
        diags.Note(scopes.CurrentScope()->LocalLookup(id)->loc, DiagID::DuplicateName2);
#endif
    } else {
        std::unique_ptr<Symbol> sym = std::make_unique<Symbol>(id, kind, loc);
        scopes.Declare(std::move(sym));
    }
}
