//=================================================================================================================
//  parser/ch3/derived-type-definition.cc -- A derived type from another type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  derived_type_definition ::= new subtype_indication
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
// -- Parse a Derived Type Definition
//    -------------------------------
bool Parser::ParseDerivedTypeDefinition(Id &id)
{
    Production p(*this, "derived_type_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;


    //
    // -- This is just a TOK_NEW with a Subtype Indication
    //    ------------------------------------------------
    if (!Require(TOK_NEW)) return false;


    //
    // -- Manage the symbol table
    //    -----------------------
    if (scopes.IsLocalDefined(std::string_view(id.name))) {
        // -- name is used in this scope is it a singleton and incomplete class?
        vec = scopes.CurrentScope()->LocalLookup(std::string_view(id.name));

        if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
        }
    }

    scopes.Declare(std::make_unique<DerivedTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    if (!ParseSubtypeIndication()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    m.Commit();
    return true;
}







