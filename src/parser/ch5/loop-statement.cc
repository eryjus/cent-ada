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
    SymbolTable::Checkpoint cp;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    SimpleNamePtr loopName = nullptr;
    SimpleNamePtr endName = nullptr;
    ExprPtr spec = nullptr;
    StmtListPtr stmts = nullptr;
    LoopType kind = LoopType::LoopNone;



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
        Symbol *sym = symTab.LocalLookup(id.name);
        if (sym) {
            if (sym->kind != SymbolTable::SymbolKind::UndefinedLabel && sym->kind != SymbolTable::SymbolKind::Deleted) {
                diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
                diags.Note(sym->loc, DiagID::DuplicateName2, { } );
            } else {
                sym->kind = SymbolTable::SymbolKind::LoopName;
            }
        } else {
            symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::LoopName);
        }
    }


    spec = ParseIterationScheme(kind);

    if (!Require(TokenType::TOK_LOOP)) {
        p.At("Missing Loop");
        return nullptr;
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



    p.At("Complete loop");
    cp.Commit();
    m.Commit();
    return std::make_unique<LoopStmt>(astLoc, std::move(labels), std::move(loopName), kind, std::move(spec), std::move(stmts));
}


