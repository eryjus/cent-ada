//=================================================================================================================
//  parser/ch3/choice.cc -- Parse a choice
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
ChoicePtr Parser::ParseChoice(void)
{
    Production p(*this, "choice");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t astLoc = tokens.SourceLocation();
    DiscreteRangePtr range = nullptr;
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;


    //
    // -- The orders of these have been changed to allow more complicated alternatives
    //    happen before the simpler ones which may consume fewer tokens -- other than
    //    the trivial deterministic options, where were placed first.
    //    ----------------------------------------------------------------------------
    if (Optional(TokenType::TOK_OTHERS)) {
        p.At("TOK_OTHERS");
        m.Commit();
        return std::make_unique<OthersChoice>(astLoc);
    }


    range = ParseDiscreteRange();
    if (range) {
        p.At("Range");
        m.Commit();
        return std::make_unique<RangeChoice>(astLoc, std::move(range));
    }


    name = ParseSimpleName();
    if (name) {
        //
        // -- This is required to be a component simple name
        //    ----------------------------------------------
        const std::vector<Symbol *> *vec = scopes.Lookup(id.name);
        if (vec != nullptr) {
            for (auto &sym : *vec) {
                if (sym->kind == Symbol::SymbolKind::Component) {
                    p.At("Component Simple Name");
                    m.Commit();
                    return std::make_unique<NameChoice>(astLoc, std::move(name));
                }
            }
        }

        m.Reset();
    }

    expr = ParseSimpleExpression();
    if (expr) {
        p.At("Expression");
        m.Commit();
        return std::make_unique<ExprChoice>(astLoc, std::move(expr));
    }


    diags.Error(tokens.SourceLocation(), DiagID::InvalidChoiceInVariant);

    return nullptr;
}



