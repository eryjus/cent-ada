//=================================================================================================================
//  parser/ch5/loop-parameter-specification.cc -- Parse the specification of a for loop
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  loop_parameter_specification ::= identifier in [reverse] discrete_range
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Feb-23  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse an iteration scheme
//    -------------------------
ExprPtr Parser::ParseLoopParameterSpecification(LoopType &kind)
{
    Production p(*this, "iteration_scheme");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr rv = nullptr;
    ExprPtr lhs = nullptr;
    ExprPtr rhs = nullptr;
    DiscreteRangePtr dr = nullptr;
    NamePtr name = nullptr;
    Id id;
    bool rev = false;


    if (!RequireIdent(id)) return nullptr;
    if (!Require(TokenType::TOK_IN)) return nullptr;
    rev = Require(TokenType::TOK_REVERSE);

    dr = ParseDiscreteRange();
    if (!dr) return nullptr;


    //
    // -- build the lhs
    //    -------------
    name = std::make_unique<SimpleName>(astLoc, id);
    lhs = std::make_unique<NameExpr>(astLoc, std::move(name));


    //
    // -- build the rhs
    //    -------------
    rhs = std::make_unique<RangeExpr>(astLoc, std::move(dr));


    kind = (rev ? LoopType::LoopReverseFor : LoopType::LoopFor);



    return std::make_unique<BinaryExpr>(astLoc, BinaryOper::In, std::move(lhs), std::move(rhs));
}


