//=================================================================================================================
//  parser/ch3/floating-point-constraint.cc -- Parse a floating point constraint
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  floating_point_constraint ::= floating_accuracy_definition [range_constraint]
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
// -- Parse a Floating Point Constraint
//    ---------------------------------
NumericTypeSpecPtr Parser::ParseFloatingPointConstraint(Id &id)
{
    Production p(*this, "floating_point_constraint");
    SymbolTable::Checkpoint cp;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    ExprPtr size = nullptr;
    Symbol *sym = nullptr;


    //
    // -- Check on the Floating Point Accuracy Definition
    //    -----------------------------------------------
    size = ParseFloatingAccuracyDefinition();
    if (!size) return nullptr;


    //
    // -- and then check on the optional Range Constraint
    //    -----------------------------------------------
    RangeConstraintPtr range = ParseRangeConstraint();



    //
    // -- Manage the symbol table
    //    -----------------------
    if (!id.name.empty()) {
        sym = symTab.LocalLookup(id.name);
        if (sym) {
            if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
                updateIncomplete = true;
            } else {
                diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
                diags.Note(sym->loc, DiagID::DuplicateName2, { } );
            }
        } else {
            sym = symTab.Declare(astLoc, id.name, SymbolTable::SymbolKind::Type);
        }
    }



    //
    // -- The parse is good here
    //    ----------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;
    cp.Commit();

    return std::make_unique<NumericTypeSpec>(astLoc, NumericTypeSpec::Kind::FloatingPoint, std::move(size), std::move(range));
}



