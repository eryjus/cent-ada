//=================================================================================================================
//  sym-printer.cc -- Implement the classes which will print the different symbol structures
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
    if (s.kind == SymbolTable::SymbolKind::Deleted) return;
    out << "Symbol: " << s.symName << " : " << s.to_string();
    if (s.typeName != "") out << "of type " << s.typeName;
    out << '\n';
}



