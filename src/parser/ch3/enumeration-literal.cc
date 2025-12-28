//=================================================================================================================
//  parser/ch3/enumeration-literal.cc -- Parse an enumeration literal
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  enumeration_literal ::= identifier | character_literal
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
// -- Parse an Enumeration Literal
//    ----------------------------
bool Parser::ParseEnumerationLiteral(void)
{
    Production p(*this, "enumeration_literal");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;
    std::string id;


    //
    // -- Trivially check if it's a character literal
    //    -------------------------------------------
    if (Optional(TOK_CHARACTER_LITERAL)) {
        m.Commit();
        return true;
    }


    //
    // -- Now check for an id and if we have one check for duplicates
    //    -----------------------------------------------------------
    if (RequireIdent(id)) {

        //
        // -- Check for a duplicate and insert new or report an error
        //    -------------------------------------------------------
#if 0
        const std::vector<Symbol *> *vec = scopes.Lookup(id);
        if (vec || vec->empty()) {
            diags.Error(loc, DiagID::DuplicateName, { id } );
            diags.Note(sym->loc, DiagID::DuplicateName2);
        } else {
            scopes.Declare(std::make_unique<Symbol>(id, Symbol::SymbolKind::EnumerationLiteral, loc));
        }
#endif


        //
        // -- Consider this parse to be good
        //    ------------------------------
        m.Commit();
        return true;
    }

    return false;
}



