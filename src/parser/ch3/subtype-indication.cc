//=================================================================================================================
//  parser/ch3/subtype-indication.cc -- an indication of a defined type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  subtype_indication ::= type_mark [constraint]
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Subtype Indication
//    --------------------------
SubtypeIndicationPtr Parser::ParseSubtypeIndication(void)
{
    Production p(*this, "subtype_indication");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();


    //
    // -- Find a type mark and then optionally a constraint
    //    -------------------------------------------------
    if (!ParseTypeMark()) return nullptr;
    ParseConstraint();



    //
    // -- Sine this will pass at this point, build the AST here
    //    -----------------------------------------------------
    SubtypeIndicationPtr rv = std::make_unique<SubtypeIndication>(loc, nullptr, nullptr);
    ASTPrinter prt;
    rv->Accept(prt);



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return std::move(rv);
}





