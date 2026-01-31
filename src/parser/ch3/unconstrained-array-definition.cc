//=================================================================================================================
//  parser/ch3/unconstrained-array-definition.cc -- Define an unconstrained array
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  unconstrained_array_definition ::= array ( index_subtype_definition {, index_subtype_definition} )
//                                         of component_subtype_indication
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
// -- Parse an Unconstrained Array Definition
//    ---------------------------------------
ArrayTypeSpecPtr Parser::ParseUnconstrainedArrayDefinition(Id &id)
{
    Production p(*this, "unconstrained_array_definition");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc=astLoc;
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    DiscreteRangeListPtr idxList = std::make_unique<DiscreteRangeList>();
    IndexConstraintPtr indices = nullptr;
    UnboundedRangePtr idx = nullptr;
    SubtypeIndicationPtr compType = nullptr;



    //
    // -- Start parse with the first 2 required tokens
    //    --------------------------------------------
    if (!Require(TokenType::TOK_ARRAY)) return nullptr;
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;


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

    ArrayTypeSymbol *type = scopes.Declare(std::make_unique<ArrayTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));



    //
    // -- now, there should be an index definition
    //    ----------------------------------------
    idx = ParseIndexSubtypeDefinition();
    if (!idx) return nullptr;
    idxList->push_back(std::move(idx));


    //
    // -- now, some optional additional indices
    //    -------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        idx = ParseIndexSubtypeDefinition();
        if (idx) {
            idxList->push_back(std::move(idx));
        } else {
            diags.Error(loc, DiagID::ExtraComma, { "index_subtype_definition" } );
            // -- continue on in hopes of finding more errors

            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- The closing paren is required
    //    -----------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, {"array index subtype definition"});
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Wrap up the rest of the production
    //    ----------------------------------
    if (!Require(TokenType::TOK_OF)) return nullptr;

    compType = ParseComponentSubtypeIndication();
    if (!compType) return nullptr;



    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;

    NameListPtr list = std::make_unique<NameList>();
    NamePtr name = std::make_unique<SimpleName>(astLoc, id);
    list->push_back(std::move(name));
    indices = std::make_unique<IndexConstraint>(astLoc, true, std::move(idxList));

    s.Commit();
    m.Commit();

    return std::make_unique<ArrayTypeSpec>(astLoc, std::move(list), true, std::move(indices), std::move(compType));
}



