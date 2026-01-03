//=================================================================================================================
//  parser/ch4/term.cc -- A term
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  term ::= factor {multiplying_operator factor}
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Term
//    ------------
bool Parser::ParseTerm(void)
{
    Production p(*this, "term");
    MarkStream m(tokens, diags);

    if (!ParseFactor()) return false;

    while (ParseMultiplyingOperator()) {
        if (!ParseFactor()) return false;
    }

    m.Commit();
    return true;
}



