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


    //
    // -- Manage the symbol table
    //    -----------------------
    if (!id.name.empty()) {
        if (scopes.IsLocalDefined(std::string_view(id.name))) {
            // -- name is used in this scope is it a singleton and incomplete class?
            vec = scopes.CurrentScope()->LocalLookup(std::string_view(id.name));

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
    if (!ParseFloatingAccuracyDefinition()) return nullptr;


    //
    // -- and then check on the optional Range Constraint
    //    -----------------------------------------------
    RangeConstraintPtr range = std::move(ParseRangeConstraint());



    //
    // -- The parse is good here
    //    ----------------------
    NumericTypeSpecPtr rv = std::make_unique<NumericTypeSpec>(astLoc, NumericTypeSpec::Kind::FloatingPoint, nullptr, std::move(range));

    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    return std::move(rv);
}



