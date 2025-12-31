//=================================================================================================================
//  visitors.cc -- Implement the classes which will visit the different symbol structures
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-28  Initial   0.0.0   ADCL  Initial version
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
void SymbolPrinter::Visit(const TypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Type: " << s.name << " : " << s.CategoryString() << " (May need a new Visitor)\n";
}
void SymbolPrinter::Visit(const EnumTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Enumeration Type: " << s.name << " : " << s.CategoryString() << '\n';
    out << "   containing literals (";
    for (auto &sym : s.literals) out << sym->name << ' ';
    out << "\b)\n";
}
void SymbolPrinter::Visit(const RecordTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Record Type: " << s.name << " : " << s.CategoryString() << '\n';
    out << "   containing components (";
    for (auto &sym : s.components) out << sym->name << ' ';
    out << "\b)\n";
}
void SymbolPrinter::Visit(const DerivedTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Derived Type: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const AccessTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Access Type: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const IntegerTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Integer Type: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const RealTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Real Type: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const ArrayTypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Array Type: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const SubtypeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Subtype: " << s.name << " : " << s.CategoryString() << '\n';
}
void SymbolPrinter::Visit(const EnumLiteralSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Enumeration Literal: " << s.name << " : " << s.KindString() << " of type " << s.type->name << "; value (" << s.ordinal << ")\n";
}
void SymbolPrinter::Visit(const DiscriminantSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Discriminant Symbol: " << s.name << " : " << s.KindString() << '\n';
}
void SymbolPrinter::Visit(const AttributeSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Attribute Symbol: " << s.name << " : " << s.KindString() << '\n';
}
void SymbolPrinter::Visit(const ObjectSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Object Symbol: " << s.name << " : " << s.KindString() << '\n';
}
void SymbolPrinter::Visit(const ComponentSymbol &s) {
    if (s.kind == Symbol::SymbolKind::Deleted) return;
    out << "Component Symbol: " << s.name << " : " << s.KindString() << '\n';
}




