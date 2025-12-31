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

    if (ParseSimpleExpression()) {
        m.Commit();
        return true;
    }

    if (ParseDiscreteRange()) {
        m.Commit();
        return true;
    }

    if (Optional(TOK_OTHERS)) {
        m.Commit();
        return true;
    }

    if (ParseSimpleName(id)) {
        //
        // -- This is required to be a component simple name
        //
        //    TODO: Check the type of the simple name
        //    ----------------------------------------------
        m.Commit();
        return true;
    }

    diags.Error(tokens.SourceLocation(), DiagID::InvalidChoiceInVariant);

    return false;
}



