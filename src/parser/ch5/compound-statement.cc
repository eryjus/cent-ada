//=================================================================================================================
//  parser/ch5/compound-statement.cc -- Parse a simple statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  compound_statement ::= if_statement
//                       | case_statement
//                       | loop_statement
//                       | block_statement
//                       | accept_statement
//                       | select_statement
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
// -- Parse a Compound Statement
//    --------------------------
StmtPtr Parser::ParseCompoundStatement(NameListPtr &labels)
{
    Production p(*this, "compound_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    StmtPtr rv = nullptr;


    rv = ParseIfStatement(labels);
    if (rv) {
        p.At("If Statement");
        m.Commit();
        return rv;
    }


    rv = ParseCaseStatement(labels);
    if (rv) {
        p.At("Case Statement");
        m.Commit();
        return rv;
    }


    rv = ParseLoopStatement(labels);
    if (rv) {
        p.At("Loop Statement");
        m.Commit();
        return rv;
    }


    rv = ParseBlockStatement(labels);
    if (rv) {
        p.At("Block Statement");
        m.Commit();
        return rv;
    }


    rv = ParseAcceptStatement(labels);
    if (rv) {
        p.At("Accept Statement");
        m.Commit();
        return rv;
    }


    rv = ParseSelectStatement(labels);
    if (rv) {
        p.At("Select Statement");
        m.Commit();
        return rv;
    }


    p.At("No Statement");
    return nullptr;
}
