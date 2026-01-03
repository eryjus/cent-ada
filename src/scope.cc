//=================================================================================================================
//  scope.cc -- This scope stack implementation
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  This file starts from breaking apart `scopes.cc` into separate concerns.
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-28  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Construct a scope
//    -----------------
Scope::Scope(Scope *parent, ScopeKind kind, int level, std::string name)
        : parent(parent),kind(kind), level(level), name(name)
{
    ordered.clear();
    index.clear();
}



//
// -- Perform a rollback if we are not keeping the changes
//    ----------------------------------------------------
void Scope::Rollback(size_t cp)
{
    while (ordered.size() > cp) {
        Symbol *sym = ordered.back().get();
        auto it = index.find(sym->name);
        if (it != index.end()) {
            auto &vec = it->second;
            vec.pop_back();
            if (vec.empty()) {
                index.erase(it);
            }
        }

        ordered.pop_back();
    }
}



//
// -- perform a lookup of the symnbol name in this scope
//    --------------------------------------------------
std::vector<Symbol *> *Scope::LocalLookup(std::string_view name)
{
    auto it = index.find(std::string(name));
    if (it == index.end()) {
        return nullptr;
    }

    return &it->second;
}



//
// -- print the local scope
//    ---------------------
void Scope::Print(void) const
{
    SymbolPrinter printer(std::cerr);

    for (auto &sym : ordered) {
        sym.get()->Accept(printer);
    }
}



