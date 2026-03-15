//=================================================================================================================
//  parser/ch5/case-statement.cc -- Parse a case statement
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
CaseStmtPtr Parser::ParseCaseStatement(NameListPtr &labels)
{
    Production p(*this, "case_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr expr = nullptr;
    CaseStmtAltPtr alt = nullptr;
    CaseStmtAltListPtr alts = std::make_unique<CaseStmtAltList>();
    StmtListPtr stmts = nullptr;


    if (!Require(TokenType::TOK_CASE)) return nullptr;

    loc = TokenStream::Get().SourceLocation();
    expr = ParseExpression();
    if (!expr) {
        diags.Error(loc, DiagID::MissingExpression, { "'case' keyword" } );
        // -- continue to try to parse the case statemnet
        TokenStream::Get().Recovery(TokenType::TOK_IS);
    }

    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_IS)) {
        diags.Error(loc, DiagID::MissingIs, { "case" } );
    }


    alt = ParseCaseStatementAlternative();
    if (!alt) {
        diags.Error(loc, DiagID::MissingCaseAlternative, { } );
    } else {
        alts->push_back(std::move(alt));

        alt = ParseCaseStatementAlternative();
        while (alt) {
            alts->push_back(std::move(alt));
            alt = ParseCaseStatementAlternative();
        }
    }


    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "if statement" } );
    }

    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_CASE)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "if" } );
    }

    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "if statement" } );
    }


    m.Commit();
    return std::make_unique<CaseStmt>(astLoc, std::move(labels), std::move(expr), std::move(alts));
}