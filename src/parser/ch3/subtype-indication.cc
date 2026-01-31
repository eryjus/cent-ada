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
    NamePtr id = nullptr;
    ConstraintPtr constraint = nullptr;


    //
    // -- Find a type mark and then optionally a constraint
    //    -------------------------------------------------
    id = ParseTypeMark();
    if (!id) {
        p.At("TypeMark");
        return nullptr;
    }
    constraint = ParseConstraint();



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();

    return std::make_unique<SubtypeIndication>(loc, std::move(id), std::move(constraint));
}



//
// -- Parse a Discrete Subtype Indication
//    -----------------------------------
SubtypeIndicationPtr Parser::ParseDiscreteSubtypeIndication(void)
{
    Production p(*this, "subtype_indication(discrete)");
    SourceLoc_t astLoc = tokens.SourceLocation();
    SubtypeIndicationPtr node = nullptr;

    node = ParseSubtypeIndication();
    if (!node) return nullptr;

    return node;
}




