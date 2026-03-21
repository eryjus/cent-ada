//=================================================================================================================
//  parser/ch5/sequence-of-statements.cc -- Parse a sequence of 1 or more statements
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  sequence_of_statements ::= statement { statement }
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Feb-21  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Sequence of Statements
//    ------------------------------
StmtListPtr Parser::ParseSequenceOfStatements(void)
{
    Production p(*this, "sequence-of-statements");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc= astLoc;
    StmtPtr stmt = nullptr;
    StmtListPtr rv = std::make_unique<StmtList>();


    // -- must have at least 1 statement
    stmt = ParseStatement();

    if (!stmt) {
        diags.Error(loc, DiagID::ExpectedStatement, { } );
        p.At("No Statement");
        return nullptr;
    }

    while (stmt) {
        rv->push_back(std::move(stmt));
        if (tokens.Current() == TokenType::YYEOF) break;
        stmt = ParseStatement();
    }

    p.At("statement list");
    m.Commit();

    return rv;
}


