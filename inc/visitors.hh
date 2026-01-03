//=================================================================================================================
//  visitors.hh -- Define the classes which will visit nodes
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
    virtual void Visit(const TypeSymbol &) = 0;
    virtual void Visit(const EnumTypeSymbol &) = 0;
    virtual void Visit(const RecordTypeSymbol &) = 0;
    virtual void Visit(const DerivedTypeSymbol &) = 0;
    virtual void Visit(const AccessTypeSymbol &) = 0;
    virtual void Visit(const IntegerTypeSymbol &) = 0;
    virtual void Visit(const RealTypeSymbol &) = 0;
    virtual void Visit(const ArrayTypeSymbol &) = 0;
    virtual void Visit(const SubtypeSymbol&) = 0;
    virtual void Visit(const EnumLiteralSymbol &) = 0;
    virtual void Visit(const DiscriminantSymbol&) = 0;
    virtual void Visit(const AttributeSymbol&) = 0;
    virtual void Visit(const ObjectSymbol&) = 0;
    virtual void Visit(const ComponentSymbol&) = 0;
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
    virtual void Visit(const TypeSymbol &s) override;
    virtual void Visit(const EnumTypeSymbol &s) override;
    virtual void Visit(const RecordTypeSymbol &s) override;
    virtual void Visit(const DerivedTypeSymbol &s) override;
    virtual void Visit(const AccessTypeSymbol &s) override;
    virtual void Visit(const IntegerTypeSymbol &s) override;
    virtual void Visit(const RealTypeSymbol &s) override;
    virtual void Visit(const ArrayTypeSymbol &s) override;
    virtual void Visit(const SubtypeSymbol &s) override;
    virtual void Visit(const EnumLiteralSymbol &s) override;
    virtual void Visit(const DiscriminantSymbol &s) override;
    virtual void Visit(const AttributeSymbol &s) override;
    virtual void Visit(const ObjectSymbol &s) override;
    virtual void Visit(const ComponentSymbol &s) override;
};



