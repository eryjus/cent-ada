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
    Production p(*this, "loop_statement");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    SimpleNamePtr loopName = nullptr;
    SimpleNamePtr endName = nullptr;
    ExprPtr spec = nullptr;
    StmtListPtr stmts = nullptr;
    LoopType kind = LoopType::LoopNone;
    Scope *scope = nullptr;
    std::vector<Symbol *> *vec = nullptr;



    Id id;
    loc = tokens.SourceLocation();
    if (RequireIdent(id)) {
        loopName = std::make_unique<SimpleName>(astLoc, id);

        loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_COLON)) {
            diags.Error(loc, DiagID::MissingColon, { "loop name" } );
        }
    }


    if (loopName) {
        if (scopes.IsLocalDefined(loopName->GetName())) {
            vec = scopes.CurrentScope()->LocalLookup(loopName->GetName());

            if (vec->at(0)->kind != Symbol::SymbolKind::UndefinedLabel && vec->at(0)->kind != Symbol::SymbolKind::Deleted) {
                diags.Error(loc, DiagID::DuplicateName, { "Statement Label" } );
                diags.Note(loc, DiagID::DuplicateName2, { TokenStream::Get().SourceLine() } );
            } else if (vec->at(0)->kind == Symbol::SymbolKind::UndefinedLabel) {
                vec->at(0)->kind = Symbol::SymbolKind::Deleted;
            }
        }

        scopes.Declare(std::make_unique<LabelSymbol>(std::string(loopName->GetName()), astLoc, scopes.CurrentScope()));
    }


    spec = ParseIterationScheme(kind);

    if (!Require(TokenType::TOK_LOOP)) {
        p.At("Missing Loop");
        return nullptr;
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
        diags.Error(loc, DiagID::MissingEnd, { "loop body" } );
    }

    if (!Require(TokenType::TOK_LOOP)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "loop" } );
    }

    endName = ParseSimpleName();

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "loop prologue" } );
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


    p.At("Complete loop");
    m.Commit();
    s.Commit();
    return std::make_unique<LoopStmt>(astLoc, std::move(labels), std::move(loopName), kind, std::move(spec), std::move(stmts));
}


