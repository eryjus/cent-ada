//=================================================================================================================
//  parser/ch3/floating-accuracy-definition.cc -- Parse a floating point accuracy definition
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  floating_accuracy_definition ::= digits static_simple_expression
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-27  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Floating Accuracy Deinition
//    -----------------------------------
ExprPtr Parser::ParseFloatingAccuracyDefinition(void)
{
    Production p(*this, "floating_accuracy_definition");
    MarkStream m(tokens, diags);
    ExprPtr rv = nullptr;


    //
    // -- this production starts with a DIGITS token
    //    ------------------------------------------
    if (!Require(TokenType::TOK_DIGITS)) return nullptr;


    //
    // -- and constains a static simple expression
    //    ----------------------------------------
    rv = ParseStaticSimpleExpression();
    if (!rv) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return rv;
}



