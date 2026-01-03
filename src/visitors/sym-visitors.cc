//=================================================================================================================
//  sym-visitors.cc -- Implement the classes which will visit the different symbol structures
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Jan-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Make a visitor to print a Symbol
//    --------------------------------
void SymbolPrinter::Visit(const Symbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Symbol: " << s.name << " : " << s.KindString() << " (May need a new Visitor)\n";
}



//
// -- Make a visitor to print a TypeSymbol
//    ------------------------------------
void SymbolPrinter::Visit(const TypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Type: " << s.name << " : " << s.CategoryString() << " (May need a new Visitor)\n";
}



//
// -- Make a visitor to print an EnumTypeSymbol
//    -----------------------------------------
void SymbolPrinter::Visit(const EnumTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Enumeration Type: " << s.name << " : " << s.CategoryString() << '\n';
    out << "   containing literals (";
    for (auto &sym : s.literals) out << sym->name << ' ';
    out << "\b)\n";
}



//
// -- Make a visitor to print a RecordTypeSymbol
//    ------------------------------------------
void SymbolPrinter::Visit(const RecordTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Record Type: " << s.name << " : " << s.CategoryString() << '\n';
    out << "   containing components (";
    for (auto &sym : s.components) out << sym->name << ' ';
    out << "\b)\n";
}



//
// -- Make a visitor to print a DerivedTypeSymbol
//    -------------------------------------------
void SymbolPrinter::Visit(const DerivedTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Derived Type: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print an AccessTypeSymbol
//    -------------------------------------------
void SymbolPrinter::Visit(const AccessTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Access Type: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print an IntegerTypeSymbol
//    --------------------------------------------
void SymbolPrinter::Visit(const IntegerTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Integer Type: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print a RealTypeSymbol
//    ----------------------------------------
void SymbolPrinter::Visit(const RealTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Real Type: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print an ArrayTypeSymbol
//    ------------------------------------------
void SymbolPrinter::Visit(const ArrayTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Array Type: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print a SubtypeSymbol
//    ---------------------------------------
void SymbolPrinter::Visit(const SubtypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Subtype: " << s.name << " : " << s.CategoryString() << '\n';
}



//
// -- Make a visitor to print an EnumLiteralSymbol
//    --------------------------------------------
void SymbolPrinter::Visit(const EnumLiteralSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Enumeration Literal: " << s.name << " : " << s.KindString() << " of type " << s.type->name << "; value (" << s.ordinal << ")\n";
}



//
// -- Make a visitor to print a DiscriminantSymbol
//    --------------------------------------------
void SymbolPrinter::Visit(const DiscriminantSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Discriminant Symbol: " << s.name << " : " << s.KindString() << '\n';
}



//
// -- Make a visitor to print an AttributeSymbol
//    ------------------------------------------
void SymbolPrinter::Visit(const AttributeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Attribute Symbol: " << s.name << " : " << s.KindString() << '\n';
}



//
// -- Make a visitor to print an ObjectSymbol
//    ---------------------------------------
void SymbolPrinter::Visit(const ObjectSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Object Symbol: " << s.name << " : " << s.KindString() << '\n';
}



//
// -- Make a visitor to print a ComponentSymbol
//    -----------------------------------------
void SymbolPrinter::Visit(const ComponentSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Component Symbol: " << s.name << " : " << s.KindString() << '\n';
}



//
// -- Make a visitor to print an IncompleteTypeSymbol
//    -----------------------------------------------
void SymbolPrinter::Visit(const IncompleteTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Incomplete Type: " << s.name << " : " << s.CategoryString() << '\n';
}


