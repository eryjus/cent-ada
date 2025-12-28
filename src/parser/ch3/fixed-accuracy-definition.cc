//=================================================================================================================
//  parser/ch3/fixed-accuracy-definition.cc -- Parse a fixed point accuracy definition
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  fixed_accuracy_definition ::= delta static_simple_expression
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
// -- Parse a Fixed Accuracy Deinition
//    --------------------------------
bool Parser::ParseFixedAccuracyDefinition(void)
{
    Production(*this, "fixed_accuracy_definition");
    MarkStream m(tokens, diags);

    //
    // -- this production starts with a DELTA token
    //    -----------------------------------------
    if (!Require(TOK_DELTA)) return false;


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

