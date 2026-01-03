//=================================================================================================================
//  parser/ch4/allocator.cc -- An allocator
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  allocator ::= new subtype_indication
//              | new qualified_expression
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
// -- Parse an Allocator
//    ------------------
bool Parser::ParseAllocator(void)
{
    Production p(*this, "allocator");
    MarkStream m(tokens, diags);

    if (!Require(TokenType::TOK_NEW)) return false;

    if (ParseQualifiedExpression()) {
        m.Commit();
        return true;
    }

    if (ParseSubtypeIndication()) {
        m.Commit();
        return true;
    }

    return false;
}



