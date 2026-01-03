//=================================================================================================================
//  parser/ch3/range-constraint.cc -- Parse a range constraint
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  range_constraint ::= range range
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
// -- Parse a Range Constraint
//    ------------------------
bool Parser::ParseRangeConstraint(void)
{
    Production p(*this, "range_constraint");
    MarkStream m(tokens, diags);


    //
    // -- the range starts with the TOK_RANGE token
    //    -----------------------------------------
    if (!Require(TokenType::TOK_RANGE)) return false;
    SourceLoc_t loc = tokens.SourceLocation();
    if (!ParseRange()) {
        diags.Error(loc, DiagID::InvalidRangeConstraint);
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



