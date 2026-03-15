//=================================================================================================================
//  parser/ch5/exit-statement.cc -- Parse a exit statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  exit_statement ;;= exit [ loop_name ] [ when condition ] ;
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
// -- Parse a exit statement
//    ----------------------
ExitStmtPtr Parser::ParseExitStatement(NameListPtr &labels)
{
    Production p(*this, "exit_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    NamePtr name = nullptr;
    ExprPtr cond = nullptr;

    if (!Require(TokenType::TOK_EXIT)) return nullptr;

    name = ParseNameNonExpr();

    if (Optional(TokenType::TOK_WHEN)) {
        loc = TokenStream::Get().SourceLocation();
        cond = ParseCondition();

        if (!cond) {
            diags.Error(loc, DiagID::MissingExpression, { "exit when condition" } );
        }
    }

    if (name) {
        const std::vector<Symbol *> *vec = scopes.Lookup(name->GetName());

        if (!(vec->at(0) && vec->at(0)->kind == Symbol::SymbolKind::LoopName)) {
            diags.Error(loc, DiagID::InvalidName, { "exit statement" } );
        }
    }


    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "exit statement" } );
    }


    m.Commit();

    return std::make_unique<ExitStmt>(astLoc, std::move(labels), std::move(name), std::move(cond));
}
