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
NodePtr Parser::ParseDeclarativePart(void)
{
    Production p(*this, "declarative_part");
    MarkStream m(tokens, diags);



    //
    // -- handle the basic declarative items
    //    ----------------------------------
    while (ParseBasicDeclarativeItem()) {
        // -- for now, nothing to be done here
    }


    //
    // -- handle the later declarative items
    //    ----------------------------------
    while (ParseLaterDeclarativeItem()) {
        // -- for now, nothing to be done here
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return std::move(std::make_unique<ASTNode>(tokens.EmptyLocation()));
}



