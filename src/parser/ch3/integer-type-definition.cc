//=================================================================================================================
//  parser/ch3/integer-type-definition.cc -- Parse an integer type definition
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  integer_type_definition ::= range_constraint
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
// -- Parse an Integer Type Definition
//    --------------------------------
TypeSpecPtr Parser::ParseIntegerTypeDefinition(Id &id)
{
    Production p(*this, "integer_type_definition");
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    RangeConstraintPtr con;
    SourceLoc_t astLoc;


    //
    // -- Manage the symbol table
    //    -----------------------
    if ((con = ParseRangeConstraint()) == nullptr) return nullptr;


    if (scopes.IsLocalDefined(std::string_view(id.name))) {
        // -- name is used in this scope is it a singleton and incomplete class?
        vec = scopes.CurrentScope()->LocalLookup(std::string_view(id.name));

        if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
        }
    }

    scopes.Declare(std::make_unique<IntegerTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));


    //
    // -- Consider this parse complete
    //    ----------------------------
    TypeSpecPtr rv = std::make_unique<IntegerTypeSpec>(astLoc, std::move(con));

    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    return std::move(rv);
}



