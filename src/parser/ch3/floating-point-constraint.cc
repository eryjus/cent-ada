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
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    SourceLoc_t astLoc = tokens.SourceLocation();
    ExprPtr size = nullptr;


    //
    // -- Manage the symbol table
    //    -----------------------
    if (!id.name.empty()) {
        if (scopes.IsLocalDefined(id.name)) {
            // -- name is used in this scope is it a singleton and incomplete class?
            vec = scopes.CurrentScope()->LocalLookup(id.name);

            if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
                updateIncomplete = true;
            } else {
                diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            }
        }

        scopes.Declare(std::make_unique<RealTypeSymbol>(id.name, id.loc, scopes.CurrentScope()));
    }



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
    // -- The parse is good here
    //    ----------------------
    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;

    s.Commit();

    return std::make_unique<NumericTypeSpec>(astLoc, NumericTypeSpec::Kind::FloatingPoint, std::move(size), std::move(range));
}



