//=================================================================================================================
//  parser/ch3/type-mark.cc -- a type mark is 2 special cases for name
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  type_mark ::= type_name | subtype_name
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"


//
// -- Parse a Type Mark
//    -----------------
bool Parser::ParseTypeMark(void)
{
    Production p(*this, "type_mark");

    if (ParseTypeName())        return true;
    if (ParseSubtypeName())     return true;

    return false;
}



//
// -- TODO: This needs to be removed once confirmed the logic was properly implemented
//    --------------------------------------------------------------------------------
#if 0
//
// -- Parse a Type Mark
//    -----------------
bool Parser::ParseTypeMark(void)
{
    Production p(*this, "type_mark");
    MarkStream m(tokens, diags);
    std::string id;

    if (!ParseNameNonExpr(id)) return false;

    //
    // -- At this point, the name is required to be either a `type_` name or a
    //    `subtype_` name.  Therefore, some additional processing is required here
    //    to ensure the name matches the requirements.  Even though the syntax
    //    might technically work by matching a `name` alone, some context is also
    //    needed to sure a proper parse.  The parse may still fail.
    //
    //    TODO: Check for a type or subtype name
    //    --------------------------------------------------------------------------

    Symbol *sym = scopes.Lookup(id);
    if (!sym) {
        // --TODO: Issue an error here for unknown type/subtype
        return false;
    }

    if (sym->kind != Symbol::SymbolKind::Type && sym->kind != Symbol::SymbolKind::Subtype && sym->kind != Symbol::SymbolKind::IncompleteType) {
        // -- TODO: Issue an error here?
        return false;
    }


    m.Commit();
    return true;
}
#endif
