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
    SymbolTable::Checkpoint cp;
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    RangeConstraintPtr con = nullptr;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    Symbol *sym = nullptr;


    //
    // -- Manage the symbol table
    //    -----------------------
    con = ParseRangeConstraint();
    if (!con) return nullptr;


    sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            sym->kind = SymbolTable::SymbolKind::Type;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::Type);
    }


    //
    // -- Consider this parse complete
    //    ----------------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;

    cp.Commit();

    return std::make_unique<NumericTypeSpec>(astLoc, NumericTypeSpec::Kind::Integer, nullptr, std::move(con));
}



