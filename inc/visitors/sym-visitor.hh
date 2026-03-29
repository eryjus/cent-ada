//=================================================================================================================
//  sym-visitor.hh -- Handle visiting all the symbols
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



#pragma once


//
// -- This class will be able to visit each symbol structure
//    ------------------------------------------------------
class SymbolVisitor {
public:
    virtual void Visit(const Symbol &) = 0;
};



//
// -- This class will be used to print the symbol table
//    -------------------------------------------------
class SymbolPrinter : public SymbolVisitor {
private:
   std::ostream &out;


public:
    explicit SymbolPrinter(std::ostream &o) : out(o) {}


public:
    virtual void Visit(const Symbol &s) override;
};







