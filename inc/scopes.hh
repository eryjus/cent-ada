//=================================================================================================================
//  scopes.hh -- This header defines scopes for layers of symbol tables
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-14  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- Need a forward declaration here
//    -------------------------------
class Parser;



//
// -- These are the kinds of symbols which will need to be discerned
//    --------------------------------------------------------------
enum class SymbolKind {
    IncompleteType,
    Type,
    Subtype,
    Object,
    Constant,
    EnumerationLiteral,
    Discriminant,
    Subprogram,
    Package,
};



//
// -- This is the basic symbol structure -- will be expanded later
//    ------------------------------------------------------------
typedef struct Symbol {
    std::string name;
    SymbolKind kind;
    SourceLoc_t loc;

    Symbol(std::string n, SymbolKind k, SourceLoc_t l) : name(n), kind(k), loc(l) {}
} Symbol;



//
// -- This is a scope of symbols
//    --------------------------
class Scope {
    Scope(void) = delete;
    Scope(const Scope &) = delete;
    Scope &operator=(const Scope &)  = delete;

public:
    enum class Kind {
        Global,
        Package,
        Subprogram,
        Block,
    };


private:
    Scope *parent;
    Kind kind;
    std::vector<std::unique_ptr<Symbol>> ordered;
    std::unordered_map<std::string, Symbol *> index;


public:
    explicit Scope(Scope *parent, Kind kind);


public:
    Scope *Parent(void) const { return parent; }
    Kind GetKind(void) const { return kind; }

    size_t Checkpoint(void) { return ordered.size(); }
    void Rollback(size_t cp) {
        while (ordered.size() > cp) {
            auto &sym = ordered.back();
            index.erase(sym->name);
            ordered.pop_back();
        }
    }

    Symbol *LocalLookup(std::string_view name) const;
    Symbol *Declare(std::unique_ptr<Symbol> sym);
};



//
// -- Finally, the scope manager
//    --------------------------
class ScopeManager {
    ScopeManager(const ScopeManager &) = delete;
    ScopeManager &operator=(const ScopeManager &) = delete;
    friend class Parser;


private:
    std::vector<std::unique_ptr<Scope>> stack;


private:
    // -- these are only accessible from Parser
    void PushScope(Scope::Kind kind);
    void PopScope(void);
    //
    // -- This function must be called no more than once for any given scope
    //    ------------------------------------------------------------------
    std::unique_ptr<Scope> ClaimCurrentScope(void) {
        if (CurrentScope() == nullptr) {
            std::cerr << "Internal error: Scope claimed multiple times\n";
            exit(EXIT_FAILURE);
        }
        if (CurrentScope()->GetKind() != Scope::Kind::Global) {
            return std::move(stack[stack.size() - 1]);
        } else {
            std::cerr << "Internal error: tried to claim the global scope; not allowed\n";
            exit(EXIT_FAILURE);
        }
    }
    Symbol *Declare(std::unique_ptr<Symbol> sym) { return CurrentScope()->Declare(std::move(sym)); }


public:
    explicit ScopeManager(void);


public:
    Symbol *Lookup(std::string_view name) const;
    Scope *CurrentScope(void) const { return stack[stack.size() - 1].get(); }
    bool IsLocalDefined(std::string_view name) const { return CurrentScope()->LocalLookup(name) != nullptr; }
};



