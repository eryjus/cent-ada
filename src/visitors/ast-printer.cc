//=================================================================================================================
//  ast-printer.cc -- Implement the classes which will print the different AST structures
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
// -- Print a required child helper function
//    --------------------------------------
void ASTPrinter::PrintRequiredChild(std::string label, ASTNode *child) {
    // -- TODO: Remove the following if-statement and block after the entire AST has been properly built
    if (!child) {
        PrintDepth();
        std::cout << label << '\n';
        depth ++;
        PrintDepth();
        std::cout << "(null)\n";
        depth --;
        return;
    };

    assert(child);
    PrintDepth();
    std::cout << label << '\n';
    depth ++;
    child->Accept(*this);
    depth --;
}



//
// -- Print an optional AST Child helper function
//    -------------------------------------------
void ASTPrinter::PrintOptionalChild(std::string label, ASTNode *child) {
    PrintDepth();
    std::cout << label << '\n';
    if (child) {
        depth ++;
        child->Accept(*this);
        depth --;
    } else {
        depth ++;
        PrintDepth();
        std::cout << "(null)\n";
        depth --;
    }
}



//
// -- Print a field
//    -------------
void ASTPrinter::PrintField(std::string label, std::string value) {
    PrintDepth();
    std::cout << label << '\n';
    depth ++;
    PrintDepth();
    std::cout << "- " << value << '\n';
    depth --;
}



//
// -- Print an Identifier List
//    ------------------------
void ASTPrinter::PrintIdList(std::string label, IdList *child) {
    assert(child);

    PrintDepth();
    std::cout << label << '\n';

    depth ++;
    for (auto &id : *child) {
        PrintDepth();
        std::cout << "- " << id.name << '\n';
    }
    depth --;
}



//
// -- Print a SubtypeInciation AST node
//    ---------------------------------
void ASTPrinter::Visit(const SubtypeIndication &n)
{
    PrintDepth();
    std::cout << "SubtypeIndication\n";
    depth ++;

    PrintRequiredChild("type mark", n.name.get());
    PrintOptionalChild("constraint", n.constraint.get());

    depth --;
}



//
// -- Print a Number Declaration AST node
//    -----------------------------------
void ASTPrinter::Visit(const NumberDeclaration &n)
{
    PrintDepth();
    std::cout << "NumberDeclaration\n";
    depth ++;

    PrintIdList("names", n.names.get());
    PrintRequiredChild("initializer", n.initializer.get());

    depth --;
}



//
// -- Print an Object Declaration AST node
//    ------------------------------------
void ASTPrinter::Visit(const ObjectDeclaration &n)
{
    PrintDepth();
    std::cout << "ObjectDeclaration\n";
    depth ++;

    PrintIdList("names", n.names.get());
    PrintField("constant", (n.isConstant?"true":"false"));
    PrintRequiredChild("typeSpec", n.typeSpec.get());
    PrintRequiredChild("initializer", n.initializer.get());

    depth --;
}



//
// -- Print an Full Type Declaration AST node
//    ---------------------------------------
void ASTPrinter::Visit(const TypeDecl &n)
{
    PrintDepth();
    std::cout << "TypeDecl\n";
    depth ++;

    PrintField("name", n.name.name);
    PrintOptionalChild("discriminantPart", n.discriminantPart.get());
    PrintRequiredChild("definition", n.definition.get());

    depth --;
}



//
// -- Print an Enumeration Type Specification
//    ---------------------------------------
void ASTPrinter::Visit(const EnumerationTypeSpec &n)
{
    PrintDepth();
    std::cout << "EnumerationTypeSpec\n";
    depth ++;

    PrintIdList("literals", n.literals.get());

    depth --;
}



//
// -- Print a Range Constraint
//    ------------------------
void ASTPrinter::Visit(const RangeConstraint &n)
{
    PrintDepth();
    std::cout << "RangeConstraint\n";
    depth ++;

    PrintRequiredChild("range", n.range.get());

    depth --;
}



//
// -- Print a Range
//    -------------
void ASTPrinter::Visit(const Range &n)
{
    PrintDepth();
    std::cout << "Range\n";
    depth ++;

    PrintRequiredChild("lower", n.lowerBound.get());
    PrintRequiredChild("upper", n.upperBound.get());

    depth --;
}


//
// -- Print a Subtype Range
//    ---------------------
void ASTPrinter::Visit(const SubtypeRange &n)
{
    PrintDepth();
    std::cout << "SubtypeRange\n";
    depth ++;

    PrintRequiredChild("attribute", n.rangeAttribute.get());

    depth --;
}




//
// -- Print an Integer Type
//    ------------------------
void ASTPrinter::Visit(const NumericTypeSpec &n)
{
    PrintDepth();
    std::cout << "NumericTypeSpec\n";
    depth ++;

    PrintRequiredChild("range", n.range.get());

    depth --;
}




