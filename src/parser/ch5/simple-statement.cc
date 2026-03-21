//=================================================================================================================
//  parser/ch5/simple-statement.cc -- Parse a simple statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  simple_statement ::= null_statement
//                     | assignment_statement
//                     | procedure_call_statement
//                     | exit_statement
//                     | return_statement
//                     | goto_statement
//                     | entry_call_statement
//                     | delay_statement
//                     | abort_statement
//                     | raise_statement
//                     | code_statement
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
// -- Parse a Single Statement
//    ------------------------
StmtPtr Parser::ParseSimpleStatement(NameListPtr &labels)
{
    Production p(*this, "simple_statement");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    StmtPtr rv = nullptr;


    rv = ParseNullStatement(labels);
    if (rv) {
        p.At("Null Statement");
        m.Commit();
        return rv;
    }


    rv = ParseAssignmentStatement(labels);
    if (rv) {
        p.At("Assign Statement");
        m.Commit();
        return rv;
    }


    rv = ParseProcedureCallStatement(labels);
    if (rv) {
        p.At("Procedure Call Statement");
        m.Commit();
        return rv;
    }


    rv = ParseExitStatement(labels);
    if (rv) {
        p.At("Exit Statement");
        m.Commit();
        return rv;
    }


    rv = ParseReturnStatement(labels);
    if (rv) {
        p.At("Return Statement");
        m.Commit();
        return rv;
    }


    rv = ParseGotoStatement(labels);
    if (rv) {
        p.At("Goto Statement");
        m.Commit();
        return rv;
    }


    rv = ParseEntryCallStatement(labels);
    if (rv) {
        p.At("Entry Call Statement");
        m.Commit();
        return rv;
    }


    rv = ParseDelayStatement(labels);
    if (rv) {
        p.At("Delay Statement");
        m.Commit();
        return rv;
    }


    rv = ParseAbortStatement(labels);
    if (rv) {
        p.At("Abort Statement");
        m.Commit();
        return rv;
    }


    rv = ParseRaiseStatement(labels);
    if (rv) {
        p.At("Raise Statement");
        m.Commit();
        return rv;
    }


    rv = ParseCodeStatement(labels);
    if (rv) {
        p.At("Code Statement");
        m.Commit();
        return rv;
    }


    p.At("No Statement");
    return nullptr;
}
