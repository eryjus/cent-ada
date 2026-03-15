//=================================================================================================================
//  parser/ch5/null-statement.cc -- Parse a null statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  null_statement ;;= null ;
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
// -- Parse a null statement
//    ----------------------
NullStmtPtr Parser::ParseNullStatement(NameListPtr &labels)
{
    Production p(*this, "null_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;

    p.At("NULL token");
    if (!Require(TokenType::TOK_NULL)) return nullptr;

    loc = TokenStream::Get().SourceLocation();
    if (!Optional(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "NULL statement" } );
    }

    p.At("complete NULL statement");
    m.Commit();
    return std::make_unique<NullStmt>(astLoc, std::move(labels));
}
