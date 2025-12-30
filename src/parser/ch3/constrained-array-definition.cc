//=================================================================================================================
//  parser/ch3/constrained-array-definition.cc -- Define a constrained array
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
    if (!Require(TOK_ARRAY)) return false;
    if (!ParseIndexConstraint()) return false;
    if (!Require(TOK_OF)) return false;
    if (!ParseDiscreteSubtypeIndication()) return false;

    return true;
}



//
// -- Parse a Constrained Array Definition
//    ------------------------------------
bool Parser::ParseConstrainedArrayDefinition(const std::string &id)
{
    Production p(*this, "constrained_array_definition (id)");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);



    //
    // -- Start by adding a new Array Type with the name
    //    ----------------------------------------------
    ArrayTypeSymbol *type = scopes.Declare(std::make_unique<ArrayTypeSymbol>(id, tokens.SourceLocation(), scopes.CurrentScope()));


    if (!_HelpParseConstrainedArrayDefinition()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
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
    // -- Start by adding a new Array Type with the name
    //    ----------------------------------------------
    for (auto &id : *list) {
        ArrayTypeSymbol *type = scopes.Declare(std::make_unique<ArrayTypeSymbol>(id.name, tokens.SourceLocation(), scopes.CurrentScope()));
    }



    if (!_HelpParseConstrainedArrayDefinition()) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}





