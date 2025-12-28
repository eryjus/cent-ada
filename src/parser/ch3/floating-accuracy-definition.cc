//=================================================================================================================
//  parser/ch3/floating-accuracy-definition.cc -- Parse a floating point accuracy definition
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseFloatingAccuracyDefinition(void)
{
    Production p(*this, "floating_accuracy_definition");
    MarkStream m(tokens, diags);


    //
    // -- this production starts with a DIGITS token
    //    ------------------------------------------
    if (!Require(TOK_DIGITS)) return false;


    //
    // -- and constains a static simple expression
    //    ----------------------------------------
    if (!ParseStaticSimpleExpression()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



