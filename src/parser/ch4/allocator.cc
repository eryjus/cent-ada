//=================================================================================================================
//  parser/ch4/allocator.cc -- An allocator
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
AllocatorExprPtr Parser::ParseAllocator(void)
{
    Production p(*this, "allocator");
    MarkStream m(tokens, diags);
    QualifiedExprPtr q = nullptr;
    SubtypeIndicationPtr s = nullptr;
    SourceLoc_t astLoc = tokens.SourceLocation();

    if (!Require(TokenType::TOK_NEW)) return nullptr;

    q = ParseQualifiedExpression();
    if (q) {
        m.Commit();

        return std::make_unique<QualExprAllocatorExpr>(astLoc, std::move(q));
    }

    s = ParseSubtypeIndication();
    if (s) {
        m.Commit();

        return std::make_unique<SubtypeIndicationAllocatorExpr>(astLoc, std::move(s));
    }



    return nullptr;
}



