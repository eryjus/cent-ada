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
//    Id id;
    NamePtr id;
    SourceLoc_t astLoc = tokens.SourceLocation();


    //
    // -- Get a type mark, and then the 2 required tokens to provide context
    //    ------------------------------------------------------------------
    if ((id = std::move(ParseTypeMark())) == nullptr) return nullptr;
    if (!Require(TokenType::TOK_RANGE)) return nullptr;
    if (!Require(TokenType::TOK_BOX)) return nullptr;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    UnboundedRangePtr rv = std::make_unique<UnboundedRange>(astLoc, std::move(id));
    m.Commit();
    return std::move(rv);
}



