//=================================================================================================================
//  scope.hh -- This header defines the scope stack
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  This file starts from breaking apart `scopes.hh` into separate concerns.
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-28  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- This is a scope of symbols
//    --------------------------
class Scope {
    Scope(void) = delete;
    Scope(const Scope &) = delete;
    Scope &operator=(const Scope &)  = delete;

public:
    enum class ScopeKind {
        Global,
        Package,
        Subprogram,
        Block,
        Enumeration,
        Record,
    };


private:
    std::string name;
    int level;
    Scope *parent;      // -- the next broader scope, not the owner
    ScopeKind kind;

    // -- declaration order -- needed for rollback
    std::vector<std::unique_ptr<Symbol>> ordered;

    //
    // -- This is critical understanding:
    //
    //    Each identifier name needs to be able to be pointed to one of several symbol objects,
    //    Each symbol object identifies its own type.  I believe at this point only enums cab be
    //    overloaded.  However, this means that each name will need to be able to be resolved
    //    to each possible symbol in the scope.  `std::vector<Symbol *>` is a vector of symbols,
    //    not types.
    //    ---------------------------------------------------------------------------------------
    std::unordered_map<std::string, std::vector<Symbol *>> index;


public:
    explicit Scope(Scope *parent, ScopeKind kind, int level, std::string name = "");

public:
    Scope *Parent(void) const { return parent; }
    ScopeKind GetKind(void) const { return kind; }

    size_t Checkpoint(void) { return ordered.size(); }

    void Rollback(size_t cp);
    const std::vector<Symbol *> *LocalLookup(std::string_view name) const;
    void AddType(const std::string name, TypeSymbol *type) { index.find(name)->second.push_back(type); };
    void Print(void) const;


public:
    template <typename T>
    T *Declare(std::unique_ptr<T> sym) {
        static_assert(std::is_base_of_v<Symbol, T>, "Declare<T>: T must derive from Symbol");
        T *raw = sym.get();
        ordered.push_back(std::move(sym));
        index[raw->name].push_back(raw);
        return raw;
    }


public:
    int Level(void) const { return level; }
    void Level(int l) { level = l; }
    const std::string &Name(void) const { return name; }
};




