//=================================================================================================================
//  symbol.hh -- This header defines the symbol table
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
// -- This is the basic symbol structure -- will be expanded later
//    ------------------------------------------------------------
class Symbol {
public:
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
        Component,
        Subprogram,
        Package,
    };


private:
    std::string name;
    SymbolKind kind;
    SourceLoc_t loc;
    bool hidden = false;

public:
    Symbol(std::string n, SymbolKind k, SourceLoc_t l) : name(n), kind(k), loc(l) {}
    const std::string &to_string(void);

public:
    void Hide(bool h = true) { hidden = h; }
    bool Hidden(void) const { return hidden; }
    const std::string &Name(void) const { return name; }
    SymbolKind Kind(void) const { return kind; }
    const SourceLoc_t &Loc(void) const { return loc; }
};


