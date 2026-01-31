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
DiscreteRangePtr Parser::ParseRange(void)
{
    Production p(*this, "range");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    AttributeNamePtr attr = nullptr;
    ExprPtr from = nullptr;
    ExprPtr to = nullptr;


    //
    // -- If we find a range attribute we're done
    //    ---------------------------------------
    attr = ParseRangeAttribute();
    if (attr) {
        m.Commit();

        return std::make_unique<AttributeRange>(astLoc, std::move(attr));
    }


    //
    // -- otherwise, we have a range expression
    //    -------------------------------------
    from = ParseSimpleExpression();
    if (!from) return nullptr;

    if (!Require(TokenType::TOK_DOUBLE_DOT)) return nullptr;

    to = ParseSimpleExpression();
    if (!to) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();

    return std::make_unique<Range>(astLoc, std::move(from), std::move(to));
}



