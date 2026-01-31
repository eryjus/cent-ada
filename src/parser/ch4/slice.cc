//=================================================================================================================
//  parser/ch4/slice.cc -- A single dimensional array slice
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  slice ::= prefix ( discrete_range )
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
// -- Parse an Slice
//    --------------
SliceNamePtr Parser::ParseSlice(void)
{
    Production p(*this, "slice");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr pre = nullptr;
    DiscreteRangePtr range = nullptr;


    pre = ParsePrefix();
    if (!pre) return nullptr;


    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;

    range = ParseDiscreteRange();
    if (!range) return nullptr;

    SourceLoc_t loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "discrete_range" } );
    }


    m.Commit();

    return std::make_unique<SliceName>(astLoc, std::move(pre), std::move(range));
}



//
// -- Parse a Slice for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
SliceNamePtr Parser::ParseName_SliceSuffix(NamePtr &prefix)
{
    Production p(*this, "slice(suffix)");
    MarkStream m(tokens, diags);
    DiscreteRangePtr range = nullptr;
    SourceLoc_t astLoc = tokens.SourceLocation();


    range = ParseDiscreteRange();
    if (!range) return nullptr;


    m.Commit();

    return std::make_unique<SliceName>(astLoc, std::move(prefix), std::move(range));
}



