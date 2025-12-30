//=================================================================================================================
//  visitors.hh -- Define the classes which will visit nodes
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



//
// -- This class will be able to visit each symbol structure
//    ------------------------------------------------------
class SymbolVisitor {
public:
    virtual void Visit(const Symbol &) = 0;
    virtual void Visit(const EnumTypeSymbol &) = 0;
    virtual void Visit(const EnumLiteralSymbol &) = 0;
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
    virtual void Visit(const EnumTypeSymbol &s) override;
    virtual void Visit(const EnumLiteralSymbol &s) override;
};



