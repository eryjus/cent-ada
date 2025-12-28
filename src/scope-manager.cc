//=================================================================================================================
//  scope-manager.cc -- This file is the implementation of the scope interface
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-15  Initial   0.0.0   ADCL  Initial version
//  2025-Dec-28  Initial   0.0.0   ADCL  Renamed scopes.cc to scope-manager.cc
//
//=================================================================================================================



#include "ada.hh"



//
// -- Construct the Scope Manager
//    ---------------------------
ScopeManager::ScopeManager(void)
{
    stack.push_back(std::make_unique<Scope>(nullptr, Scope::ScopeKind::Global));

    Declare(std::make_unique<Symbol>("integer", Symbol::SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("boolean", Symbol::SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("array", Symbol::SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("real", Symbol::SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("character", Symbol::SymbolKind::Type, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("string", Symbol::SymbolKind::Type, tokens->EmptyLocation()));


    Declare(std::make_unique<Symbol>("false", Symbol::SymbolKind::Object, tokens->EmptyLocation()));
    Declare(std::make_unique<Symbol>("true", Symbol::SymbolKind::Object, tokens->EmptyLocation()));
}



//
// -- Create a new scope and push it onto the stack
//    ---------------------------------------------
void ScopeManager::PushScope(Scope::ScopeKind kind)
{
    stack.push_back(std::make_unique<Scope>(CurrentScope()->Parent(), kind));
}



//
// -- Pop a scope from the stack, with a check that the global scope always remains
//    -----------------------------------------------------------------------------
void ScopeManager::PopScope(void)
{
    if (CurrentScope()->GetKind() == Scope::ScopeKind::Global) {
        exit(EXIT_FAILURE);
    }

    stack.pop_back();
}



//
// -- Look for a symbol in all the scopes
//    -----------------------------------
const std::vector<Symbol *> *ScopeManager::Lookup(std::string_view name) const
{
    for (auto it = stack.rbegin(); it != stack.rend(); it ++) {
        const std::vector<Symbol *> *vec = it->get()->LocalLookup(name);
        if (vec) return vec;
    }

    return nullptr;
}



//
// -- Print the complete symbol table
//    -------------------------------
void ScopeManager::Print(void) const
{
    for (auto it = stack.rbegin(); it != stack.rend(); it ++) {
        it->get()->Print();
    }
}



