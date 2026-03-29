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
ArrayTypeSpecPtr Parser::_HelpParseConstrainedArrayDefinition(IdListPtr &list)
{
    // -- MarkStream is not needed here since this is a helper function.
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    NameListPtr names = std::make_unique<NameList>();
    IndexConstraintPtr range = nullptr;
    SubtypeIndicationPtr type = nullptr;

    for (auto &id : *list) {
        SimpleNamePtr name = std::make_unique<SimpleName>(astLoc, id);
        names->push_back(std::move(name));
    }


    //
    // -- Start parse with the TOK_ARRAY and carry right on through
    //    ---------------------------------------------------------
    if (!Require(TokenType::TOK_ARRAY)) return nullptr;

    range = ParseIndexConstraint();

    if (!range) return nullptr;

    if (!Require(TokenType::TOK_OF)) return nullptr;

    type = ParseDiscreteSubtypeIndication();
    if (!type) return nullptr;

    return std::make_unique<ArrayTypeSpec>(astLoc, false, std::move(range), std::move(type));
}



//
// -- Parse a Constrained Array Definition
//    ------------------------------------
ArrayTypeSpecPtr Parser::ParseConstrainedArrayDefinition(Id &id)
{
    Production p(*this, "constrained_array_definition (id)");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    SourceLoc_t loc = tokens.SourceLocation();
    bool updateIncomplete = false;
    Symbol *sym = nullptr;



    //
    // -- Manage the symbol table
    //    -----------------------
    sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        symTab.Declare(loc, id.name, SymbolTable::SymbolKind::Type);
    }


    IdListPtr list = std::make_unique<IdList>();
    list->push_back(id);

    ArrayTypeSpecPtr rv = _HelpParseConstrainedArrayDefinition(list);
    if (!rv) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;
    cp.Commit();
    m.Commit();

    return rv;
}




//
// -- Parse a Constrained Array Definition
//    ------------------------------------
ArrayTypeSpecPtr Parser::ParseConstrainedArrayDefinition(IdListPtr &list)
{
    Production p(*this, "constrained_array_definition (list)");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;


    ArrayTypeSpecPtr rv = _HelpParseConstrainedArrayDefinition(list);
    p.At("Missing array spec");
    if (!rv) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    cp.Commit();
    m.Commit();
    p.At("Complete array spec");

    return rv;
}





