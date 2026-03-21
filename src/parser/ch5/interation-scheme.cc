//=================================================================================================================
//  parser/ch5/iteration-cheme.cc -- Parse an optional interation scheme for a loop statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  iteration_scheme ::= while condition
//                     | for loop_paramter_specification
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
ExprPtr Parser::ParseIterationScheme(LoopType &kind)
{
    Production p(*this, "iteration_scheme");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr rv = nullptr;

    if (Require(TokenType::TOK_WHILE)) {
        rv = ParseCondition();
        kind = LoopType::LoopWhile;

        p.At("While condition");
        m.Commit();

        return rv;
    }

    if (Require(TokenType::TOK_FOR)) {
        rv = ParseLoopParameterSpecification(kind);

        p.At("For Loop Spec");
        m.Commit();
        return rv;
    }


    kind = LoopType::LoopNone;
    return nullptr;
}


