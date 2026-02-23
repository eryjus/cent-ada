//=================================================================================================================
//  parser/ch5/loop-statement.cc -- Parse a loop statement
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
LoopStmtPtr Parser::ParseLoopStatement(NameListPtr &labels)
{
    Production p(*this, "assignment_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    SimpleNamePtr loopName = nullptr;
    SimpleNamePtr endName = nullptr;
    ExprPtr spec = nullptr;
    StmtListPtr stmts = nullptr;
    LoopType kind = LoopType::LoopNone;

    loopName = ParseSimpleName();
    if (loopName) {
        loc = TokenStream::Get().SourceLocation();

        if (!Require(TokenType::TOK_COLON)) {
            diags.Error(loc, DiagID::MissingColon, { "loop name" } );
        }
    }


    spec = ParseIterationScheme(kind);

    if (!Require(TokenType::TOK_LOOP)) {
        if (kind == LoopType::LoopNone) return nullptr;

        diags.Error(loc, DiagID::MissingColon, { kind == LoopType::LoopFor ? "for" : "while" } );
    }

    stmts = ParseSequenceOfStatements();

    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "if statement" } );
    }

    if (!Require(TokenType::TOK_IF)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "if" } );
    }

    endName = ParseSimpleName();

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "if statement" } );
    }

    if (loopName || endName) {
        if (loopName && !endName) {
            diags.Error(loc, DiagID::MissingEndingName, { "loop", loopName->GetName() } );
        }

        if (!loopName && endName) {
            diags.Error(loc, DiagID::MissingName, { "loop", endName->GetName() } );
        }

        if (loopName && endName && loopName->GetName() != endName->GetName()) {
            diags.Error(loc, DiagID::NameMismatch, { "loop", loopName->GetName(), endName->GetName() } );
        }
    }


    m.Commit();
    return std::make_unique<LoopStmt>(astLoc, std::move(labels), std::move(loopName), kind, std::move(spec), std::move(stmts));
}


