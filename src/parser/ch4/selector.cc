//=================================================================================================================
//  parser/ch4/selector.cc -- A selector for a selected component
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  selected_component ::= prefix . selector
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Selector
//    ----------------
bool Parser::ParseSelector(void)
{
    Production p(*this, "selector");
    MarkStream m(tokens, diags);
    Id id;

    if (Optional(TokenType::TOK_ALL)) {
        m.Commit();
        return true;
    }

    if (Optional(TokenType::TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if (m.CommitIf(ParseSimpleName() != nullptr)) {
        if (!scopes.Lookup(id.name)) {
            diags.Error(loc, DiagID::UnknownName, { "selector"} );
            // -- allow the parse to continue
        }

        m.Commit();
        return true;
    }

    if (ParseOperatorSymbol()) {
        m.Commit();
        return true;
    }

    return false;
}


