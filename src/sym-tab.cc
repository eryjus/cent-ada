//=================================================================================================================
//  sym-tab.cc -- Implements the functions of the symbol table
//
//        Copyright (c)  2026-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Mar-25  Initial   0.0.0   ADCL  Initial version, replacing scope-manager.hh, scope.hh, and symbol.hh
//
//=================================================================================================================



#include "ada.hh"



//
// -- the singleton
//    -------------
SymbolTable *SymbolTable::symTab = nullptr;
std::vector<std::unique_ptr<SymbolTable::Scope>> SymbolTable::table;
SymbolTable::Scope *SymbolTable::current = nullptr;
SymbolTable &symTab = SymbolTable::Get();



//
// -- Construct and/or get the Symbol Table
//    -------------------------------------
SymbolTable &SymbolTable::Get(void)
{
    if (!symTab) {
        symTab = new SymbolTable();
    }

    return *symTab;
}



//
// -- Push a new scope onto the stack
//    -------------------------------
SymbolTable::Scope *SymbolTable::Push(std::string name)
{
    std::unique_ptr<Scope> wrk = std::make_unique<Scope>();
    Scope *rv = wrk.get();
    wrk->name = name;
    wrk->parent = current;
    wrk->stack.clear();

    table.push_back(std::move(wrk));
    current = rv;

    return rv;
}



//
// -- Pop a scope off the stack, but not really
//    -----------------------------------------
void SymbolTable::Pop(void)
{
    assert(current);
    current = current->parent;
}



//
// -- Check if a symbol name is overloaded
//    ------------------------------------
bool SymbolTable::IsOverloaded(std::string name)
{
    int cnt = 0;

    for (auto &i : current->stack) {
        if (i->symName == name) ++cnt;
    }

    return cnt > 1;
}



//
// -- Declare a symbol (able to duplicate)
//    ------------------------------------
SymbolTable::Symbol *SymbolTable::Declare(SourceLoc_t l, std::string n, SymbolKind k, std::string t)
{
    std::unique_ptr<Symbol> sym = std::make_unique<Symbol>();
    Symbol *rv = sym.get();

    sym->loc = l;
    sym->symName = n;
    sym->kind = k;
    sym->typeName = t;

    current->stack.push_back(std::move(sym));
    return rv;
}



//
// -- Look for a symbol in the current scope
//    --------------------------------------
SymbolTable::Symbol *SymbolTable::LocalLookup(std::string n, SymbolKind k, std::string t)
{
    for (auto &i : current->stack) {
        if (i->symName == n) {
            if (k == SymbolKind::Any) return i.get();
            if (i->kind == k) {
                if (t == "") return i.get();
                if (i->typeName == t) return i.get();
            }
        }
    }

    return nullptr;
}



//
// -- Look for a symbol globally
//    --------------------------
SymbolTable::Symbol *SymbolTable::GlobalLookup(std::string n, SymbolKind k, std::string t)
{
    Scope *wrk = current;

    while (wrk) {
        for (auto &i : wrk->stack) {
            if (i->symName == n) {
                if (k == SymbolKind::Any) return i.get();
                if (i->kind == k) {
                    if (t == "") return i.get();
                    if (i->typeName == t) return i.get();
                }
            }
        }

        wrk = wrk->parent;
    }

    return nullptr;
}



//
// -- Mark the symbol table's current position
//    ----------------------------------------
void SymbolTable::Checkpoint::Rollback(void)
{
    if (committed) return;

    current = curScope;
    current->stack.resize(currentcount);
    table.resize(scopecount);
}



//
// -- return the string representation of the symbol kind
//    ---------------------------------------------------
std::string SymbolTable::Symbol::to_string(void) const
{
    switch(kind) {
    default:                            return "Unknown";
    case SymbolKind::Object:            return "Object";
    case SymbolKind::Type:              return "Type";
    case SymbolKind::Subprogram:        return "Subprogram";
    case SymbolKind::EnumLiteral:       return "EnumLiteral";
    case SymbolKind::Component:         return "Component";
    case SymbolKind::Package:           return "Package";
    case SymbolKind::Label:             return "Label";
    case SymbolKind::Discriminant:      return "Discriminant";
    case SymbolKind::Attribute:         return "Attribute";
    case SymbolKind::Pragma:            return "Pragma";
    case SymbolKind::IncompleteType:    return "IncompleteType";
    case SymbolKind::Deleted:           return "Deleted";
    case SymbolKind::UndefinedLabel:    return "UndefinedLabel";
    case SymbolKind::LoopName:          return "LoopName";
    case SymbolKind::BlockName:         return "BlockName";
    }
}



//
// -- Print the symbol Table
//    ----------------------
void SymbolTable::Print(std::ostream &os, bool printHeader)
{
    if (printHeader) {
        os << "=========================================\n";
        os << "=========================================\n";
        os << "====   Printing Symbol Scope Stack   ====\n";
        os << "=========================================\n";
        os << "=========================================\n";
        os << '\n';
    }

    for (int i = 1; i < table.size(); i ++) {
        os << "Scope Name: " << table[i]->name << "\n";
        os << "Scope ID  : " << i << '\n';
        os << "-------------------\n";

        for (auto &sym : table[i]->stack) {
            os << sym->to_string() << " Symbol: " << sym->symName;
            if (sym->typeName != "") os << " of type " << sym->typeName;
            os << '\n';
        }

        os << "-------------------\n";
        os << '\n';
    }

}



//
// -- Construct the initial symbol table
//    ----------------------------------
SymbolTable::SymbolTable(void)
{
    Push("STANDARD");


    //
    // -- standard types
    //    --------------
    Declare({}, "integer", SymbolKind::Type);
    Declare({}, "array", SymbolKind::Type);
    Declare({}, "real", SymbolKind::Type);
    Declare({}, "character", SymbolKind::Type);
    Declare({}, "string", SymbolKind::Type);


    //
    // -- Create the Boolean Type
    //    ------------------------------
    Declare({}, "boolean", SymbolKind::Type);
    Declare({}, "false", SymbolKind::EnumLiteral, "boolean");
    Declare({}, "true", SymbolKind::EnumLiteral, "boolean");


    //
    // -- Create the possible attribute names
    //    -----------------------------------
    Declare({}, "address", SymbolKind::Attribute);
    Declare({}, "aft", SymbolKind::Attribute);
    Declare({}, "base", SymbolKind::Attribute);
    Declare({}, "callable", SymbolKind::Attribute);
    Declare({}, "constrained", SymbolKind::Attribute);
    Declare({}, "count", SymbolKind::Attribute);
    Declare({}, "delta", SymbolKind::Attribute);
    Declare({}, "digits", SymbolKind::Attribute);
    Declare({}, "emax", SymbolKind::Attribute);
    Declare({}, "epsilon", SymbolKind::Attribute);
    Declare({}, "first", SymbolKind::Attribute);
    Declare({}, "first_bit", SymbolKind::Attribute);
    Declare({}, "fore", SymbolKind::Attribute);
    Declare({}, "image", SymbolKind::Attribute);
    Declare({}, "large", SymbolKind::Attribute);
    Declare({}, "last", SymbolKind::Attribute);
    Declare({}, "last_bit", SymbolKind::Attribute);
    Declare({}, "length", SymbolKind::Attribute);
    Declare({}, "machine_emax", SymbolKind::Attribute);
    Declare({}, "machine_emin", SymbolKind::Attribute);
    Declare({}, "machine_mastissa", SymbolKind::Attribute);
    Declare({}, "machine_overflows", SymbolKind::Attribute);
    Declare({}, "machine_radix", SymbolKind::Attribute);
    Declare({}, "machine_rounds", SymbolKind::Attribute);
    Declare({}, "mantissa", SymbolKind::Attribute);
    Declare({}, "pos", SymbolKind::Attribute);
    Declare({}, "position", SymbolKind::Attribute);
    Declare({}, "pred", SymbolKind::Attribute);
    Declare({}, "range", SymbolKind::Attribute);
    Declare({}, "safe_emax", SymbolKind::Attribute);
    Declare({}, "safe_large", SymbolKind::Attribute);
    Declare({}, "safe_small", SymbolKind::Attribute);
    Declare({}, "size", SymbolKind::Attribute);
    Declare({}, "small", SymbolKind::Attribute);
    Declare({}, "storage_size", SymbolKind::Attribute);
    Declare({}, "succ", SymbolKind::Attribute);
    Declare({}, "terminated", SymbolKind::Attribute);
    Declare({}, "val", SymbolKind::Attribute);
    Declare({}, "value", SymbolKind::Attribute);
    Declare({}, "width", SymbolKind::Attribute);


    //
    // -- Finally, push the global scope
    //    ------------------------------
    Push("GLOBAL");
}

