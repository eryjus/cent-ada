//=================================================================================================================
//  parser/ch5/block-statement.cc -- Parse a block statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  case_statement ::= case expression is
//                     case_statement_alternative
//                     { case_statement_alternative }
//                     end case ;
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
// -- Parse a case statement
//    ----------------------
BlockStmtPtr Parser::ParseBlockStatement(NameListPtr &labels)
{
    Production p(*this, "assignment_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    SimpleNamePtr blockName = nullptr;
    SimpleNamePtr endName = nullptr;
    DeclListPtr decls = nullptr;
    StmtListPtr stmts = nullptr;

    Scope *scope = nullptr;



    blockName = ParseSimpleName();
    if (blockName) {
        loc = TokenStream::Get().SourceLocation();

        if (!Require(TokenType::TOK_COLON)) {
            diags.Error(loc, DiagID::MissingColon, { "block name" } );
        }
    }


    if (Require(TokenType::TOK_DECLARE)) {
        decls = ParseDeclarativePart();
    }


    if (!Require(TokenType::TOK_BEGIN)) return nullptr;



    //
    // -- For this block of statements, we need a pseudo scope
    //    ----------------------------------------------------
    if (blockName) {
        scope = scopes.PushScope(Scope::ScopeKind::Loop, std::string(blockName->GetName()));
    }

    stmts = ParseSequenceOfStatements();



    //
    // -- Exceptions are not defined yet, this is just a placeholder.
    //    -----------------------------------------------------------
    if (Optional(TokenType::TOK_EXCEPTION)) {
        // -- TODO: need to fix the AST for exceptions
        while (ParseExceptionHandler()) {}
    }




    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "block statement" } );
    }

    endName = ParseSimpleName();

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "block statement" } );
    }

    if (blockName || endName) {
        if (blockName && !endName) {
            diags.Error(loc, DiagID::MissingEndingName, { "block", blockName->GetName() } );
        }

        if (!blockName && endName) {
            diags.Error(loc, DiagID::MissingName, { "block", endName->GetName() } );
        }

        if (blockName && endName && blockName->GetName() != endName->GetName()) {
            diags.Error(loc, DiagID::NameMismatch, { "block", blockName->GetName(), endName->GetName() } );
        }
    }


    //
    // -- if we created a scope, pop it here
    //    ----------------------------------
    if (blockName) {
        scopes.PopScope(scope);
    }



    m.Commit();
    return std::make_unique<BlockStmt>(astLoc, std::move(labels), std::move(blockName), std::move(decls), std::move(stmts), nullptr);
}


