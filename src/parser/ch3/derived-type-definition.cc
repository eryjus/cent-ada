//=================================================================================================================
//  parser/ch3/derived-type-definition.cc -- A derived type from another type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
DerivedTypeSpecPtr Parser::ParseDerivedTypeDefinition(Id &id)
{
    Production p(*this, "derived_type_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = tokens.SourceLocation();
    SimpleNamePtr name = nullptr;
    SubtypeIndicationPtr type = nullptr;


    //
    // -- This is just a TOK_NEW with a Subtype Indication
    //    ------------------------------------------------
    if (!Require(TokenType::TOK_NEW)) return nullptr;


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

    name = std::make_unique<SimpleName>(astLoc, id);

    if ((type = std::move(ParseSubtypeIndication())) == nullptr) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    DerivedTypeSpecPtr rv = std::make_unique<DerivedTypeSpec>(astLoc, std::move(name), std::move(type));
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    m.Commit();
    return std::move(rv);
}







