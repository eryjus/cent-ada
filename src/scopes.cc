//=================================================================================================================
//  scopes.cc -- This file is the implementation of the scope stack
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-15  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Construct a scope
//    -----------------
Scope::Scope(Scope *parent, Kind kind) : parent(parent),kind(kind)
{
    ordered.clear();
    index.clear();
}



//
// -- perform a lookup of the symnbol name in this scope
//    --------------------------------------------------
Symbol *Scope::LocalLookup(std::string_view name) const
{
    auto it = index.find(std::string(name));
    if (it != index.end()) {
        return it->second;
    }

    return nullptr;
}



//
// -- insert a new symbol into the table
//    ----------------------------------
Symbol *Scope::Declare(std::unique_ptr<Symbol> sym)
{
    if (LocalLookup(sym->name) == nullptr) {
        Symbol *raw = sym.get();
        index[raw->name] = raw;
        ordered.push_back(std::move(sym));
        return sym.get();
    }

    return nullptr;
}



//
// -- Construct the Scope Manager
//    ---------------------------
ScopeManager::ScopeManager(void)
{
    stack.push_back(std::make_unique<Scope>(nullptr, Scope::Kind::Global));

    Declare(std::make_unique<Symbol>("integer", SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("boolean", SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("array", SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("real", SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("character", SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("string", SymbolKind::Type, tokens->EmptyLocation()));


    Declare(std::make_unique<Symbol>("false",SymbolKind::Object, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("true",SymbolKind::Object, tokens->EmptyLocation()));
}



//
// -- Create a new scope and push it onto the stack
//    ---------------------------------------------
void ScopeManager::PushScope(Scope::Kind kind)
{
    stack.push_back(std::make_unique<Scope>(CurrentScope()->Parent(), kind));
}



//
// -- Pop a scope from the stack, with a check that the global scope always remains
//    -----------------------------------------------------------------------------
void ScopeManager::PopScope(void)
{
    if (CurrentScope()->GetKind() == Scope::Kind::Global) {
        exit(EXIT_FAILURE);
    }

    stack.pop_back();
}



//
// -- Look for a symbol in all the scopes
//    -----------------------------------
Symbol *ScopeManager::Lookup(std::string_view name) const
{
    for (auto it = stack.rbegin(); it != stack.rend(); it ++) {
        Symbol *sym = it->get()->LocalLookup(name);
        if (sym) return sym;
    }

    return nullptr;
}
