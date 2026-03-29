//=================================================================================================================
//  parser/ch3/record-type-definition.cc -- All the possible definitions for a record type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
RecordSpecificationPtr Parser::ParseRecordTypeDefinition(Id &id)
{
    Production p(*this, "record_type_definition");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    bool updateIncomplete = false;
    ComponentListPtr list = nullptr;



    //
    // -- this production starts with a TOK_RECORD
    //    ----------------------------------------
    if (!Require(TokenType::TOK_RECORD)) return nullptr;



    //
    // -- Symbol table management
    //    -----------------------
    Symbol *sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        sym = symTab.Declare(loc, id.name, SymbolTable::SymbolKind::Type);
    }



    //
    // -- then is followed by a list of components
    //    ----------------------------------------
    list = ParseComponentList(sym);
    if (!list) {
        return nullptr;
    }




    //
    // -- and then by TOK_END and TOK_RECORD again
    //    ----------------------------------------
    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_END)) {
        diags.Error(loc, DiagID::MissingEnd, { "record component list" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }

    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_RECORD)) {
        diags.Error(loc, DiagID::MissingEndingTag, { "record" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;

    cp.Commit();
    m.Commit();

    return std::make_unique<RecordSpecification>(astLoc, std::move(list));
}




