//=================================================================================================================
//  parser/ch3/choice.cc -- Parse a choice
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  choice ::= simple_expression
//           | discrete_range
//           | others
//           | component_simple_name
//
//  This one is going to be a mess since `simple_name` can be part of a `simple_expression` or even a
//  `discrete_range`.  This will have to be refactored.
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
// -- Parse a Choice
//    --------------
bool Parser::ParseChoice(void)
{
    Production p(*this, "choice");
    MarkStream m(tokens, diags);
    Id id;


    //
    // -- The orders of these have been changed to allow more complicated alternatives
    //    happen before the simpler ones which may consume fewer tokens -- other than
    //    the trivial deterministic options, where were placed first.
    //    ----------------------------------------------------------------------------
    if (Optional(TokenType::TOK_OTHERS)) {
        diags.Debug("Choice: OTHERS");
        m.Commit();
        return true;
    }

    if (ParseDiscreteRange()) {
        diags.Debug("Choice: discrete_range");
        m.Commit();
        return true;
    }

    if (ParseSimpleName(id)) {
        //
        // -- This is required to be a component simple name
        //
        //    TODO: Check the type of the simple name
        //    ----------------------------------------------
        const std::vector<Symbol *> *vec = scopes.Lookup(id.name);
        if (vec != nullptr) {
            for (auto &sym : *vec) {
                if (sym->kind == Symbol::SymbolKind::Component) {
                    diags.Debug("Choice: component_simple_name");
                    m.Commit();
                    return true;
                }
            }
        }

        m.Reset();
    }

    if (ParseSimpleExpression()) {
        diags.Debug("Choice: simple_expression");
        m.Commit();
        return true;
    }

    diags.Error(tokens.SourceLocation(), DiagID::InvalidChoiceInVariant);

    return false;
}



