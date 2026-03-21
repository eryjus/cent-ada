//=================================================================================================================
//  parser/ch3/declarative-part.cc -- Parse iterations of a declarative part
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  declarative_part ::= {basic_declarative_item} {later_declarative_item}
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-27  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Declarative Part
//    ------------------------
DeclListPtr Parser::ParseDeclarativePart(void)
{
    Production p(*this, "declarative_part");
    MarkStream m(tokens, diags);
    DeclPtr decl = nullptr;
    DeclListPtr rv = std::make_unique<DeclList>();



    //
    // -- handle the basic declarative items
    //    ----------------------------------
    decl = ParseBasicDeclarativeItem();
    while (decl) {
        rv->push_back(std::move(decl));
        decl = ParseBasicDeclarativeItem();
    }


    //
    // -- handle the later declarative items
    //    ----------------------------------
    decl = ParseLaterDeclarativeItem();
    while (ParseLaterDeclarativeItem()) {
        rv->push_back(std::move(decl));
        decl = ParseLaterDeclarativeItem();
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();


    return rv;
}



