//=================================================================================================================
//  parser/ch5/return-statement.cc -- Parse a return statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  return_statement ::= return [ expression ] ;
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Feb-22  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a return statement
//    ------------------------
ReturnStmtPtr Parser::ParseReturnStatement(NameListPtr &labels)
{
    Production p(*this, "return_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr expr = nullptr;

    if (!Require(TokenType::TOK_RETURN)) return nullptr;

    expr = ParseExpression();

    m.Commit();

    return std::make_unique<ReturnStmt>(astLoc, std::move(labels), std::move(expr));
}


