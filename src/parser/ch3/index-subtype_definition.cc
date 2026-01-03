//=================================================================================================================
//  parser/ch3/index-subtype-definition.cc -- Define an index subtype
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  index_subtype_definition ::= type_mark range <>
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
// -- Parse an Index Subtype Definition
//    ---------------------------------
bool Parser::ParseIndexSubtypeDefinition(void)
{
    Production p(*this, "index_subtype_definition");
    MarkStream m(tokens, diags);


    //
    // -- Get a type mark, and then the 2 required tokens to provide context
    //    ------------------------------------------------------------------
    if (!ParseTypeMark()) return false;
    if (!Require(TokenType::TOK_RANGE)) return false;
    if (!Require(TokenType::TOK_BOX)) return false;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



