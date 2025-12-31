//=================================================================================================================
//  parser/ch3/record-type-definition.cc -- All the possible definitions for a record type
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  record_type_definition ::= record component_list end record
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-27  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Record Type Definition
//    ------------------------------
bool Parser::ParseRecordTypeDefinition(Id &id)
{
    Production p(*this, "record_type_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    SourceLoc_t loc;
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;



    //
    // -- this production starts with a TOK_RECORD
    //    ----------------------------------------
    if (!Require(TOK_RECORD)) return false;



    //
    // -- Symbol table management
    //    -----------------------
    std::unique_ptr<RecordTypeSymbol> recSym = std::make_unique<RecordTypeSymbol>(id.name, id.loc, scopes.CurrentScope());
    RecordTypeSymbol *rec = recSym.get();

    if (scopes.IsLocalDefined(std::string_view(id.name))) {
        // -- name is used in this scope is it a singleton and incomplete class?
        vec = scopes.CurrentScope()->LocalLookup(std::string_view(id.name));

        if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
        }
    }

    scopes.Declare(std::move(recSym));
    scopes.PushScope(Scope::ScopeKind::Record, id.name);


    //
    // -- then is followed by a list of components
    //    ----------------------------------------
    if (!ParseComponentList(rec)) return false;



    //
    // -- and then by TOK_END and TOK_RECORD again
    //    ----------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "record component list" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }

    loc = tokens.SourceLocation();
    if (!Require(TOK_RECORD)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "record" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    m.Commit();
    scopes.PopScope();
    return true;
}




