//=================================================================================================================
//  parser/ch5/if-statement.cc -- Parse an if statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  if_statement ::= if condition then
//                       sequence_of_statements
//                   { elif condition then
//                       sequence_of_statements }
//                   [ else
//                       sequence_of_statements }
//                    end if ;
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
// -- Parse an if statement
//    ---------------------
IfStmtPtr Parser::ParseIfStatement(NameListPtr &labels)
{
    Production p(*this, "assignment_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    std::vector<Symbol *> *vec = nullptr;
    StmtListPtr stmts = nullptr;
    ExprPtr cond = nullptr;
    IfStmtPtr rv = nullptr;


    if (!Require(TokenType::TOK_IF)) return nullptr;

    loc = TokenStream::Get().SourceLocation();
    cond = ParseCondition();
    if (!cond) {
        diags.Error(loc, DiagID::MissingExpression, { "'if' keyword" } );
        // -- continue to try to parse the if statemnet
        TokenStream::Get().Recovery(TokenType::TOK_THEN);
    }

    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_THEN)) {
        diags.Error(loc, DiagID::MissingThen, { } );
    }


    stmts = ParseSequenceOfStatements();
    if (!stmts) {
        diags.Error(loc, DiagID::ExpectedStatement, { } );
    }


    rv = std::make_unique<IfStmt>(astLoc, std::move(labels), std::move(cond), std::move(stmts));


    while (Require(TokenType::TOK_ELSIF)) {
        loc = TokenStream::Get().SourceLocation();
        cond = ParseCondition();
        if (!cond) {
            diags.Error(loc, DiagID::MissingExpression, { "'if' keyword" } );
            // -- continue to try to parse the if statemnet
            TokenStream::Get().Recovery(TokenType::TOK_THEN);
        }

        loc = TokenStream::Get().SourceLocation();
        if (!Require(TokenType::TOK_THEN)) {
            diags.Error(loc, DiagID::MissingThen, { } );
        }


        stmts = ParseSequenceOfStatements();
        if (!stmts) {
            diags.Error(loc, DiagID::ExpectedStatement, { } );
        }

        rv->AddElsif(std::move(cond), std::move(stmts));
    }



    if (Require(TokenType::TOK_ELSE)) {
        loc = TokenStream::Get().SourceLocation();

        stmts = ParseSequenceOfStatements();
        if (!stmts) {
            diags.Error(loc, DiagID::ExpectedStatement, { } );
        }

        rv->AddElse(std::move(stmts));
    }



    return rv;
}