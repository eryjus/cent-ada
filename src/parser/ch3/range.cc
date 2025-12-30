//=================================================================================================================
//  parser/ch3/range.cc -- Parse a range
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  range ::= range_attribute
//          | simple_expression .. simple_expression
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
// -- Parse a Range
//    -------------
bool Parser::ParseRange(void)
{
    Production p(*this, "range");
    MarkStream m(tokens, diags);


    //
    // -- If we find a range attribute we're done
    //    ---------------------------------------
    if (ParseRangeAttribute()) {
        m.Commit();
        return true;
    }


    //
    // -- otherwise, we have a range expression
    //    -------------------------------------
    if (!ParseSimpleExpression()) return false;
    if (!Require(TOK_DOUBLE_DOT)) return false;
    if (!ParseSimpleExpression()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



