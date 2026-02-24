//=================================================================================================================
//  parser/ch5/goto-statement.cc -- Parse a goto statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  goto_statement ::= goto label_name ;
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Feb-23  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a goto statement
//    ----------------------
GotoStmtPtr Parser::ParseGotoStatement(NameListPtr &labels)
{
    Production p(*this, "goto_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    NamePtr name = nullptr;
    ExprPtr cond = nullptr;

    if (!Require(TokenType::TOK_GOTO)) return nullptr;

    name = ParseNameNonExpr();

    if (name) {
        const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

        if (!(vec->at(0) && vec->at(0)->kind == Symbol::SymbolKind::LoopName)) {
            diags.Error(loc, DiagID::InvalidName, { "goto statement" } );
        }
    } else {
        diags.Error(loc, DiagID::MissingName, { "goto statement" } );
    }

    m.Commit();

    return std::make_unique<GotoStmt>(astLoc, std::move(labels), std::move(name));
}
