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
NamePtr Parser::ParseSimpleName(void)
{
    Production p(*this, "simple_name");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();
    SourceLoc_t astLoc = loc;
    Id id;

    if (!RequireIdent(id)) {
        p.At("No ID");
        return nullptr;
    }

    if (scopes.Lookup(id.name) == nullptr) {
        diags.Error(loc, DiagID::UnknownName, { id.name } );
        // -- continue anyway
    }


    m.Commit();
    p.At("Success");

    return std::make_unique<SimpleName>(astLoc, id);
}
