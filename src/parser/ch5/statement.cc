//=================================================================================================================
//  parser/ch5/statement.cc -- Parse a single statement
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  statement ::= simple_statement
//              | compound_statement
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
// -- Parse a Single Statement
//    ------------------------
StmtPtr Parser::ParseStatement(void)
{
    Production p(*this, "statement");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    NameListPtr labels = std::make_unique<NameList>();
    StmtPtr stmt = nullptr;
    std::vector<Symbol *> *vec = nullptr;
    NamePtr label;



    //
    // -- Get any optional labels
    //    -----------------------
    label = ParseLabel();
    while (label) {
        labels->push_back(std::move(label));
        label = ParseLabel();
    }


    //
    // -- Parse a statement
    //    -----------------
    stmt = ParseSimpleStatement(labels);
    if (!stmt) stmt = ParseCompoundStatement(labels);
    if (!stmt) return nullptr;



    p.At("Complete Statement");
    m.Commit();
    s.Commit();

    return stmt;
}
