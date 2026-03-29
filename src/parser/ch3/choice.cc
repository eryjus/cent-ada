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
    Id id;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    DiscreteRangePtr range = nullptr;
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;



    //
    // -- Try the trivial OTHERS token first
    //    ----------------------------------
    {
        MarkStream m(tokens, diags);

        if (Optional(TokenType::TOK_OTHERS)) {
            p.At("TOK_OTHERS");
            m.Commit();
            return std::make_unique<OthersChoice>(astLoc);
        }
    }



    //
    // -- Try a discrete range
    //    --------------------
    {
        MarkStream m(tokens, diags);

        range = ParseDiscreteRange();
        if (range) {
            p.At("Range");
            m.Commit();
            return std::make_unique<RangeChoice>(astLoc, std::move(range));
        }
    }



    //
    // -- Try a component simple name
    //    ---------------------------
    {
        MarkStream m(tokens, diags);

        name = ParseSimpleName();
        if (name) {
            //
            // -- This is required to be a component simple name
            //    ----------------------------------------------
            Symbol *sym = symTab.LocalLookup(id.name);
            if (sym) {
                if (sym->kind == SymbolTable::SymbolKind::Component) {
                    p.At("Component Simple Name");
                    m.Commit();
                    return std::make_unique<NameChoice>(astLoc, std::move(name));
                }
            }

            m.Reset();
        }
    }



    //
    // -- Try a simple expression
    //    -----------------------
    {
        MarkStream m(tokens, diags);

        expr = ParseSimpleExpression();
        if (expr) {
            p.At("Expression");
            m.Commit();
            return std::make_unique<ExprChoice>(astLoc, std::move(expr));
        }
    }



    //
    // -- prodection failes, so issue a failure
    //    -------------------------------------
    {
        MarkStream m(tokens, diags);

        diags.Error(TokenStream::Get().SourceLocation(), DiagID::InvalidChoiceInVariant);
        m.Commit();

        return nullptr;
    }
}



