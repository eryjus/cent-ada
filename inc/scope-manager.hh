//=================================================================================================================
//  scope-manager.hh -- This header defines the interface point for the scope-manager
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-14  Initial   0.0.0   ADCL  Initial version
//  2025-Dec-28  Initial   0.0.0   ADCL  Renamed scopes.hh to scope-manager.hh
//
//=================================================================================================================



//
// -- Finally, the scope manager
//    --------------------------
class ScopeManager {
    ScopeManager(const ScopeManager &) = delete;
    ScopeManager &operator=(const ScopeManager &) = delete;
    friend class Parser;


private:
    std::vector<std::unique_ptr<Scope>> stack;
    Scope *current = nullptr;


private:
    // -- these are only accessible from Parser
    void PushScope(Scope::ScopeKind kind, std::string name);
    void PopScope(void);


public:
    template <typename T>
    T *Declare(std::unique_ptr<T> sym) { return CurrentScope()->Declare(std::move(sym)); }


public:
    explicit ScopeManager(void);


public:
    const std::vector<Symbol *> *Lookup(std::string_view name) const;
    Scope *CurrentScope(void) const { return stack[stack.size() - 1].get(); }
    bool IsLocalDefined(std::string_view name) const { return CurrentScope()->LocalLookup(name) != nullptr; }
    void Print(void) const;
    std::unique_ptr<Scope> Claim(void) {
        std::unique_ptr<Scope> rv = std::move(stack.back());
        stack.pop_back();
        current = rv->Parent();
        return std::move(rv);
    }
};



