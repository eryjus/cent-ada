//=================================================================================================================
//  parser/ch5/case-statement-alternative.cc -- Parse a case statement alternative
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
CaseStmtAltPtr Parser::ParseCaseStatementAlternative(void)
{
    Production p(*this, "assignment_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ChoiceListPtr choices = std::make_unique<ChoiceList>();
    ChoicePtr choice = nullptr;
    StmtListPtr stmts = nullptr;



    if (!Require(TokenType::TOK_WHEN)) return nullptr;

    loc = TokenStream::Get().SourceLocation();
    choice = ParseChoice();
    if (!choice) {
        diags.Error(loc, DiagID::InvalidChoiceInVariant, { } );
        goto statements;
    } else {
        choices->push_back(std::move(choice));
    }


    while (TokenStream::Get().Current() == TokenType::TOK_VERTICAL_BAR) {
        TokenStream::Get().Advance();
        choice = ParseChoice();
    }

statements:
    stmts = ParseSequenceOfStatements();


    return std::make_unique<CaseStmtAlt>(astLoc, std::move(choices), std::move(stmts));
}