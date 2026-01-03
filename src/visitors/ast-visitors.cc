//=================================================================================================================
//  ast-visitors.cc -- Implement the classes which will visit the different AST structures
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


