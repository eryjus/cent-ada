//=================================================================================================================
//  parser/ch4/simple-name.cc -- A simple name
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  simple_name ::= identifier
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
// -- Parse a Simple Name, an identifier with not additional decorations
//    ------------------------------------------------------------------
bool Parser::ParseSimpleName(Id &id)
{
    Production p(*this, "simple_name");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();

    if (!RequireIdent(id))  return false;

    if (scopes.Lookup(id.name) == nullptr) {
        diags.Error(loc, DiagID::UnknownName, { id.name } );
        // -- continue anyway
    }

    m.Commit();
    return true;
}
