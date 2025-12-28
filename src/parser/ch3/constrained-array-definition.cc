//=================================================================================================================
//  parser/ch3/constrained-array-definition.cc -- Define a constrained array
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  constrained_array_definition ::= array index_constraint of discrete_subtype_indication
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
// -- Parse a Constrained Array Definition
//    ------------------------------------
bool Parser::ParseConstrainedArrayDefinition(void)
{
    Production p(*this, "constrained_array_definition");
    MarkStream m(tokens, diags);


    //
    // -- Start with the TOK_ARRAY and carry right on through
    //    ---------------------------------------------------
    if (!Require(TOK_ARRAY)) return false;
    if (!ParseIndexConstraint()) return false;
    if (!Require(TOK_OF)) return false;
    if (!ParseDiscreteSubtypeIndication()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}




