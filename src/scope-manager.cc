//=================================================================================================================
//  scope-manager.cc -- This file is the implementation of the scope interface
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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


    //
    // -- Take care of the internal fundamental types
    //    -------------------------------------------
    Declare(std::make_unique<IntegerTypeSymbol>("integer", tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<ArrayTypeSymbol>("array", tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<RealTypeSymbol>("real", tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<EnumTypeSymbol>("character", tokens->EmptyLocation(), declScope));
    Declare(std::make_unique<ArrayTypeSymbol>("string", tokens->EmptyLocation(), declScope));


    //
    // -- Create the boolean enumeration
    //    ------------------------------
    std::unique_ptr<EnumTypeSymbol> b = std::make_unique<EnumTypeSymbol>("boolean", tokens->EmptyLocation(), declScope);
    EnumTypeSymbol *bTyp = b.get();
    Declare(std::move(b));

    std::unique_ptr<EnumLiteralSymbol> f;
    f = std::make_unique<EnumLiteralSymbol>("false", bTyp, 0, TokenStream::EmptyLocation(), declScope);
    bTyp->literals.push_back(f.get());
    Declare(std::move(f));

    std::unique_ptr<EnumLiteralSymbol> t;
    t = std::make_unique<EnumLiteralSymbol>("true", bTyp, 1, tokens->EmptyLocation(), declScope);
    bTyp->literals.push_back(t.get());
    Declare(std::move(t));



    //
    // -- create all the possible attribute names
    //    ---------------------------------------
    Declare(std::make_unique<AttributeSymbol>("address", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("aft", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("base", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("callable", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("constrained", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("count", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("delta", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("digits", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("emax", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("epsilon", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("first", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("first_bit", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("fore", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("image", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("large", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("last", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("last_bit", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("length", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_emax", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_emin", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_mastissa", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_overflows", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_radix", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("machine_rounds", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("mantissa", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("pos", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("position", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("pred", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("range", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("safe_emax", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("safe_large", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("safe_small", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("size", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("small", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("storage_size", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("succ", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("terminated", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("val", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("value", TokenStream::EmptyLocation(), declScope));
    Declare(std::make_unique<AttributeSymbol>("width", TokenStream::EmptyLocation(), declScope));



    //
    // -- Finally, create the scope for the global definitions
    //    ----------------------------------------------------
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
        std::cerr << "Scope Name: " << it->get()->Name() << '\n';
        std::cerr << "Scope ID  : " << it->get()->Level() << '\n';
        std::cerr << "-------------------\n";

        it->get()->Print();

        std::cerr << "-------------------\n\n";
    }
}



