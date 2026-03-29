//=================================================================================================================
//  parser/ch5/assignment-statement.cc -- Parse an assignment statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  assignment_statement ::= variable_name := expression ;
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
// -- Parse an assignment statement
//    -----------------------------
AssignStmtPtr Parser::ParseAssignmentStatement(NameListPtr &labels)
{
    Production p(*this, "assignment_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    std::vector<Symbol *> *vec = nullptr;
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;


    name = ParseNameNonExpr();
    if (!name) {
        p.At("Assignment Target name");
        return nullptr;
    }


    if (!Require(TokenType::TOK_ASSIGNMENT)) {
        p.At(":= symbol");
        return nullptr;
    }

    loc = TokenStream::Get().SourceLocation();
    expr = ParseExpression();
    if (!expr) {
        diags.Error(loc, DiagID::MissingExpression, { "assignment (:=)" } );
    }

    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "assignment expression" } );
    }


    //
    // -- We will accept the production and check for a valid name
    //    --------------------------------------------------------
    if (!symTab.GlobalLookup(name->GetName())) {
        diags.Error(astLoc, DiagID::UnknownName, { name->GetName() } );
    }

    p.At("Complete assignment");
    m.Commit();

    return std::make_unique<AssignStmt>(astLoc, std::move(labels), std::move(name), std::move(expr));
}
