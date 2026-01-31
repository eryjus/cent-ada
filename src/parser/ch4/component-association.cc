//=================================================================================================================
//  parser/ch4/component-association.cc -- An associate a component with a value (positional or by name)
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  component_association ::= [ choice {| choice} =>] expression
//
//  However, this structure is rough as well, especially when `choice` is taken into account:
//
//  choice ::= simple_expression        expression
//           | discrete_range           expression
//           | others                   trivial
//           | component_simple_name    expression
//
//  For this production (component_association) to work, the production choice will need to be folded into this
//  function.  This will allow the correct amount of lookahead to cleanly parse this production.  The good news
//  here is that component_association is only referenced from aggregate and as such the only 2 delimiting
//  tokens for a component_association are TOK_COMMA and TOK_RIGHT_PARENTHESIS.
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Component Association
//    -----------------------------
ComponentAssociationPtr Parser::ParseComponentAssociation(void)
{
    Production p(*this, "component_association");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    ChoiceListPtr list = std::make_unique<ChoiceList>();
    ChoicePtr choice = nullptr;
    ExprPtr expr = nullptr;


    choice = ParseChoice();
    if (choice) {
        list->push_back(std::move(choice));
        while (Optional(TokenType::TOK_VERTICAL_BAR)) {
            loc = tokens.SourceLocation();
            choice = ParseChoice();
            if (choice) {
                list->push_back(std::move(choice));
            } else {
                diags.Error(loc, DiagID::ExtraVertialBar, { "component association" } );
            }
        }

        if (!Require(TokenType::TOK_ARROW)) {
            m.Reset();      // -- may only be a simple expression, which cannot be a choice here
        }
    }


    expr = ParseExpression();
    if (!expr) return nullptr;


    m.Commit();

    return std::make_unique<ComponentAssociation>(astLoc, std::move(list), std::move(expr));
}



