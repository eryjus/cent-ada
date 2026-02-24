//=================================================================================================================
//  parser/ch5/loop-statement.cc -- Parse a loop statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  loop_statement ::= [ loop_simple_name : ]
//                        [ iteration_scheme ] loop
//                        sequence_of_statements
//                        end loop [ loop_simple_name ] ;
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
    Scope *scope = nullptr;



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


    //
    // -- For this block of statements, we need a pseudo scope
    //    ----------------------------------------------------
    if (loopName) {
        scope = scopes.PushScope(Scope::ScopeKind::Loop, std::string(loopName->GetName()));
        scopes.Declare(std::make_unique<LoopSymbol>(std::string(loopName->GetName()), astLoc, scope));
    }

    stmts = ParseSequenceOfStatements();

    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "loop statement" } );
    }

    if (!Require(TokenType::TOK_LOOP)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "loop" } );
    }

    endName = ParseSimpleName();

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "loop statement" } );
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


    //
    // -- if we created a scope, pop it here
    //    ----------------------------------
    if (loopName) {
        scopes.PopScope(scope);
    }



    m.Commit();
    return std::make_unique<LoopStmt>(astLoc, std::move(labels), std::move(loopName), kind, std::move(spec), std::move(stmts));
}


