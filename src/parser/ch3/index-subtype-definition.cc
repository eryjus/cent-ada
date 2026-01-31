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
UnboundedRangePtr Parser::ParseIndexSubtypeDefinition(void)
{
    Production p(*this, "index_subtype_definition");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr id =nullptr;


    //
    // -- Get a type mark, and then the 2 required tokens to provide context
    //    ------------------------------------------------------------------
    id = ParseTypeMark();
    if (!id) return nullptr;

    if (!Require(TokenType::TOK_RANGE)) return nullptr;
    if (!Require(TokenType::TOK_BOX)) return nullptr;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();

    return std::make_unique<UnboundedRange>(astLoc, std::move(id));
}



