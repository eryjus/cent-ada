//=================================================================================================================
//  symbol.hh -- This header defines the symbol entries, including the subclasses
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  This file starts from breaking apart `scopes.hh` into separate concerns.
//
//  `Symbol` (and in fact its subclasses) are data classes (think of them as `struct`s).  As such,
//  nothing is hidden and everything can be accessed publicy.  `Symbol` is there as a common ancestor.
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
    Symbol(void) = delete;
    Symbol(const Symbol &) = delete;
    Symbol &operator=(const Symbol &) = delete;


public:
    //
    // -- These are the kinds of symbols which will need to be discerned
    //    --------------------------------------------------------------
    enum class SymbolKind {
        Object,
        Type,
        Subprogram,
        EnumLiteral,
        Package,
        Label,
        Discriminant,
    };


public:
    // -- common apptributes for all symbols
    std::string name;
    SymbolKind kind;
    SourceLoc_t loc;


    // -- Reference to the scope in which the symbol is declared
    class Scope *declScope = nullptr;


    // -- for use with later phases of the compiler
    class TypeSymbol *type;


public:
    Symbol(std::string n, SymbolKind k, SourceLoc_t l, Scope *d) : name(n), kind(k), loc(l), declScope(d) {}
    virtual ~Symbol() = default;


public:
    virtual void Accept(SymbolVisitor &v) {
        v.Visit(*this);
    };


public:
    const std::string &KindString(void) const {
        static std::string s[] = {
            "Object",
            "Type",
            "Subprogram",
            "EnumLiteral",
            "Package",
            "Label",
            "Discriminant",
        };

        return s[(int)kind];
    }
};



//
// -- This is the root type symbol, extending a basic symbol
//    ------------------------------------------------------
class TypeSymbol : public Symbol {
    TypeSymbol(void) = delete;
    TypeSymbol(const TypeSymbol &) = delete;
    TypeSymbol &operator=(const TypeSymbol &) = delete;


public:
    enum class TypeCategory {
        Enumeration,
        Integer,
        Floating,
        Fixed,
        Array,
        Record,
        Access,
        Subtype,
        Incomplete,
        Derived,
    };


public:
    TypeCategory category;

    const std::string &CategoryString(void) const {
        static std::string s[] = {
            "Enumeration",
            "Integer",
            "Floating",
            "Fixed",
            "Array",
            "Record",
            "Access",
            "Subtype",
            "Incomplete",
            "Derived",
        };

        return s[(int)category];
    }


protected:
    // -- cannot create a new type directly -- must be a subclass
    TypeSymbol(std::string n, TypeCategory c, SourceLoc_t l, Scope *d)
            : Symbol(n, SymbolKind::Type, l, d), category(c) {}
};



//
// -- For Enumeration Types
//    ---------------------
class EnumTypeSymbol : public TypeSymbol {
    EnumTypeSymbol(void) = delete;
    EnumTypeSymbol(const EnumTypeSymbol &) = delete;
    EnumTypeSymbol &operator=(const EnumTypeSymbol &) = delete;


public:
    // -- references to other symbols
    std::vector<class EnumLiteralSymbol *> literals;


public:
    EnumTypeSymbol(std::string n, SourceLoc_t l, Scope *d) : TypeSymbol(n, TypeCategory::Enumeration, l, d) {}


public:
    virtual void Accept(SymbolVisitor &v) override {
        v.Visit(*this);
    }
};



//
// -- For Derived Types
//    -----------------
class DerivedTypeSymbol : public TypeSymbol {
    DerivedTypeSymbol(void) = delete;
    DerivedTypeSymbol(const DerivedTypeSymbol &) = delete;
    DerivedTypeSymbol &operator=(const DerivedTypeSymbol &) = delete;


public:
    DerivedTypeSymbol(std::string n, SourceLoc_t l, Scope *d) : TypeSymbol(n, TypeCategory::Derived, l, d) {}


public:
    virtual void Accept(SymbolVisitor &v) override {
        v.Visit(*this);
    }
};



//
// -- For Array Types
//    ---------------
class ArrayTypeSymbol : public TypeSymbol {
    ArrayTypeSymbol(void) = delete;
    ArrayTypeSymbol(const ArrayTypeSymbol &) = delete;
    ArrayTypeSymbol &operator=(const ArrayTypeSymbol &) = delete;


public:
    ArrayTypeSymbol(std::string n, SourceLoc_t l, Scope *d) : TypeSymbol(n, TypeCategory::Enumeration, l, d) {}


public:
    virtual void Accept(SymbolVisitor &v) override {
        v.Visit(*this);
    }
};



//
// -- An Enumeration Literal
//    ----------------------
class EnumLiteralSymbol : public Symbol {
    EnumLiteralSymbol(void) = delete;
    EnumLiteralSymbol(const EnumLiteralSymbol &) = delete;
    EnumLiteralSymbol &operator=(const EnumLiteralSymbol &) = delete;


public:
    class EnumTypeSymbol *parentType;
    size_t ordinal;


public:
    EnumLiteralSymbol(std::string n, EnumTypeSymbol *p, size_t o, SourceLoc_t l, Scope *d)
            : Symbol(n, SymbolKind::EnumLiteral, l, d), parentType(p), ordinal(o)
    {
        type = parentType;
    }


public:
    virtual void Accept(SymbolVisitor &v) override {
        v.Visit(*this);
    }
};



//
// -- A Discriminant Symbol
//    ---------------------
class DiscriminantSymbol : public Symbol {
    DiscriminantSymbol(void) = delete;
    DiscriminantSymbol(const DiscriminantSymbol &) = delete;
    DiscriminantSymbol &operator=(const DiscriminantSymbol &) = delete;


public:
    DiscriminantSymbol(std::string n, SourceLoc_t l, Scope *d) : Symbol(n, SymbolKind::Discriminant, l, d) {}


public:
    virtual void Accept(SymbolVisitor &v) override {
        v.Visit(*this);
    }
};






