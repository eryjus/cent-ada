//=================================================================================================================
//  parser/ch3/constrained-array-definition.cc -- Define a constrained array
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  constrained_array_definition ::= array index_constraint of discrete_subtype_indication
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
// -- This is a helper function in Parser to assist in parsing 2 different classes of
//    Constrained Array Definitions -- one with a single identifier and one with a
//    list of identifiers.
//    -------------------------------------------------------------------------------
bool Parser::_HelpParseConstrainedArrayDefinition(void)
{
    //
    // -- Start parse with the TOK_ARRAY and carry right on through
    //    ---------------------------------------------------------
    if (!Require(TokenType::TOK_ARRAY)) return false;
    if (!ParseIndexConstraint()) return false;
    if (!Require(TokenType::TOK_OF)) return false;
    if (!ParseDiscreteSubtypeIndication()) return false;

    return true;
}



//
// -- Parse a Constrained Array Definition
//    ------------------------------------
bool Parser::ParseConstrainedArrayDefinition(Id &id)
{
    Production p(*this, "constrained_array_definition (id)");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;



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

    ArrayTypeSymbol *type = scopes.Declare(std::make_unique<ArrayTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    if (!_HelpParseConstrainedArrayDefinition()) return false;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    m.Commit();
    return true;
}




//
// -- Parse a Constrained Array Definition
//    ------------------------------------
bool Parser::ParseConstrainedArrayDefinition(IdList *list)
{
    Production p(*this, "constrained_array_definition (list)");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);



    //
    // -- Manage the symbol table
    //    -----------------------
    for (auto &id : *list) {
        ObjectSymbol *type = scopes.Declare(std::make_unique<ObjectSymbol>(id.name, id.loc, scopes.CurrentScope()));
    }



    if (!_HelpParseConstrainedArrayDefinition()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}





