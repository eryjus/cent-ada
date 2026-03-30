//=================================================================================================================
//  parser/ch5/block-statement.cc -- Parse a block statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  block_statement ::= [ block_simple_name : ]
//                        [ delare declarative_part ]
//                        begin
//                          sequence_of_statements
//                        end [ block_simple_name ] ;
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
    Production p(*this, "block_statement");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    SimpleNamePtr blockName = nullptr;
    SimpleNamePtr endName = nullptr;
    DeclListPtr decls = nullptr;
    StmtListPtr stmts = nullptr;



    Id id;
    loc = tokens.SourceLocation();
    if (RequireIdent(id)) {
        blockName = std::make_unique<SimpleName>(astLoc, id);

        loc = tokens.SourceLocation();
        if (!Require(TokenType::TOK_COLON)) {
            diags.Error(loc, DiagID::MissingColon, { "block name" } );
        }
    }


    if (blockName) {
        Symbol *sym = symTab.LocalLookup(id.name);
        if (sym) {
            if (sym->kind != SymbolTable::SymbolKind::UndefinedLabel && sym->kind != SymbolTable::SymbolKind::Deleted) {
                diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
                diags.Note(sym->loc, DiagID::DuplicateName2, { } );
            } else {
                sym->kind = SymbolTable::SymbolKind::BlockName;
            }
        } else {
            symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::BlockName);
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
        symTab.Push(blockName->GetName());
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
        symTab.Pop();
    }


    cp.Commit();
    m.Commit();
    return std::make_unique<BlockStmt>(astLoc, std::move(labels), std::move(blockName), std::move(decls), std::move(stmts), nullptr);
}


