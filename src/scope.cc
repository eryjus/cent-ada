//=================================================================================================================
//  scope.cc -- This scope stack implementation
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
        auto it = index.find(sym->Name());
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
const std::vector<Symbol *> *Scope::LocalLookup(std::string_view name) const
{
    auto it = index.find(std::string(name));
    if (it == index.end()) {
        return nullptr;
    }

    return &it->second;
}



//
// -- insert a new symbol into the table
//    ----------------------------------
Symbol *Scope::Declare(std::unique_ptr<Symbol> sym)
{
    Symbol *raw = sym.get();
    ordered.push_back(std::move(sym));
    index[raw->Name()].push_back(raw);
    return raw;
}



//
// -- print the local scope
//    ---------------------
void Scope::Print(void) const
{
    for (auto it = ordered.begin(); it != ordered.end(); it ++) {
        Symbol *sym = it->get();

        if (sym->Hidden()) continue;

        std::cerr << "Symbol: " << sym->Name() << " : " << sym->to_string() << '\n';
        std::vector<Symbol *> vec = index.find(sym->Name())->second;

        if (sym->Kind() == Symbol::SymbolKind::EnumerationLiteral) {
            for (int i = 0; i < vec.size(); i ++) {
                std::cerr << "   of type " << vec[i]->Name() << '\n';
            }
        }
    }
}



