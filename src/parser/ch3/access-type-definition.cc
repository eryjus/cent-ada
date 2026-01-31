//=================================================================================================================
//  parser/ch3/access-type-definition.cc -- Define an access type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  access_type_definition ::= access subtype_indication
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
// -- Parse an Access Type Definition
//    -------------------------------
AccessTypeSpecPtr Parser::ParseAccessTypeDefinition(Id &id)
{
    Production p(*this, "access_type_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = tokens.SourceLocation();
    SubtypeIndicationPtr type = nullptr;



    //
    // -- Parse the sequence
    //    ------------------
    if (!Require(TokenType::TOK_ACCESS)) {
        p.At("TOK_ACCESS");
        return nullptr;
    }



    //
    // -- Manage the symbol table
    //    -----------------------
    if (scopes.IsLocalDefined(id.name)) {
        // -- name is used in this scope is it a singleton and incomplete class?
        vec = scopes.CurrentScope()->LocalLookup(id.name);

        if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
        }
    }

    scopes.Declare(std::make_unique<AccessTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    //
    // -- Check for the optional Subtype Indication
    //    -----------------------------------------
    type = ParseSubtypeIndication();
    if (!type) {
        p.At("Subtype Indication");
        return nullptr;
    }



    //
    // -- Consider this parse to be good; build the AST nodes
    //    ---------------------------------------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;



    //
    // -- Commit and Exit
    //    ---------------
    s.Commit();
    m.Commit();

    SimpleNamePtr name = std::make_unique<SimpleName>(astLoc, id);
    return std::make_unique<AccessTypeSpec>(astLoc, std::move(name), std::move(type));
}



