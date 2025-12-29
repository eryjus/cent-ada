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
    Scope *declScope;

    stack.push_back(std::make_unique<Scope>(nullptr, Scope::ScopeKind::Global, 0, "standard"));
    declScope = stack.back().get();

    Declare(std::make_unique<Symbol>("integer", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("boolean", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("array", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("real", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("character", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("string", Symbol::SymbolKind::Type, tokens->EmptyLocation(), declScope));


    Declare(std::make_unique<Symbol>("false", Symbol::SymbolKind::Object, tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<Symbol>("true", Symbol::SymbolKind::Object, tokens->EmptyLocation(), declScope));

    stack.push_back(std::make_unique<Scope>(CurrentScope(), Scope::ScopeKind::Global, CurrentScope()->Level() + 1, "GLOBAL"));
}



//
// -- Create a new scope and push it onto the stack
//    ---------------------------------------------
void ScopeManager::PushScope(Scope::ScopeKind kind, std::string name)
{
    stack.push_back(std::make_unique<Scope>(CurrentScope()->Parent(), kind, CurrentScope()->Level() + 1, name));
    current = stack.back().get();
}



//
// -- Pop a scope from the stack, with a check that the global scope always remains
//    -----------------------------------------------------------------------------
void ScopeManager::PopScope(void)
{
    if (CurrentScope()->GetKind() == Scope::ScopeKind::Global) {
        exit(EXIT_FAILURE);
    }

    current = current->Parent();
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
    std::cerr << "=========================================\n";
    std::cerr << "=========================================\n";
    std::cerr << "====   Printing Symbol Scope Stack   ====\n";
    std::cerr << "=========================================\n";
    std::cerr << "=========================================\n";
    std::cerr << '\n';

    // -- Skip the 'standard' scope, which is always the first one
    for (auto it = stack.begin() + 1; it != stack.end(); it ++) {
        std::cerr << "Scope Name : " << it->get()->Name() << '\n';
        std::cerr << "Scope Depth: " << it->get()->Level() << '\n';
        std::cerr << "-------------------\n";

        it->get()->Print();

        std::cerr << "-------------------\n\n";
    }
}



