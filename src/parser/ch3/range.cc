//=================================================================================================================
//  parser/ch3/range.cc -- Parse a range
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
RangeConstraintPtr Parser::ParseRange(void)
{
    Production p(*this, "range");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();


    //
    // -- If we find a range attribute we're done
    //    ---------------------------------------
    if (ParseRangeAttribute()) {
        RangeConstraintPtr rv = std::make_unique<AttributeRangeConstraint>(astLoc, nullptr);

        m.Commit();
        return std::move(rv);
    }


    //
    // -- otherwise, we have a range expression
    //    -------------------------------------
    if (!ParseSimpleExpression()) return nullptr;
    if (!Require(TokenType::TOK_DOUBLE_DOT)) return nullptr;
    if (!ParseSimpleExpression()) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    RangeConstraintPtr rv = std::make_unique<DiscreteRangeConstraint>(astLoc, nullptr, nullptr);

    m.Commit();
    return std::move(rv);
}



