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
    out << "Symbol: " << s.name << " : " << s.KindString() << '\n';
}
void SymbolPrinter::Visit(const EnumTypeSymbol &s) {
    out << "EnumerationType: " << s.name << " : " << s.CategoryString() << '\n';
    out << "   containing literals (";
    for (auto &sym : s.literals) out << sym->name << ' ';
    out << "\b)\n";
}
void SymbolPrinter::Visit(const EnumLiteralSymbol &s) {
    out << "EnumerationLiteral: " << s.name << " : " << s.KindString() << " of type " << s.type->name <<  "; value (" << s.ordinal << ")\n";
}




