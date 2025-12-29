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

    // -- overloaded identifiers, pointing back to the type symbol name
    std::unordered_map<std::string, std::vector<Symbol *>> index;


public:
    explicit Scope(Scope *parent, ScopeKind kind, int level, std::string name = "");

public:
    Scope *Parent(void) const { return parent; }
    ScopeKind GetKind(void) const { return kind; }

    size_t Checkpoint(void) { return ordered.size(); }

    void Rollback(size_t cp);
    const std::vector<Symbol *> *LocalLookup(std::string_view name) const;
    Symbol *DeclareSym(std::unique_ptr<Symbol> sym);
    TypeSymbol *DeclareType(std::unique_ptr<TypeSymbol> sym);
    EnumTypeSymbol *DeclareEnumType(std::unique_ptr<EnumTypeSymbol> sym);
    void AddType(const std::string name, TypeSymbol *type) { index.find(name)->second.push_back(type); };
    void Print(void) const;

public:
    int Level(void) const { return level; }
    void Level(int l) { level = l; }
    const std::string &Name(void) const { return name; }
};




