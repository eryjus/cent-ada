//=================================================================================================================
//  parser/ch4/component-association.cc -- An associate a component with a value (positional or by name)
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  component_association ::= [ choice {| choice} =>] expression
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
bool Parser::ParseComponentAssociation(void)
{
    Production p(*this, "component_association");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (ParseChoice()) {
        while (Optional(TokenType::TOK_VERTICAL_BAR)) {
            loc = tokens.SourceLocation();
            if (!ParseChoice()) {
                diags.Error(loc, DiagID::ExtraVertialBar, { "component association" } );
            }
        }
    }

    if (!Require(TokenType::TOK_ARROW)) return false;
    if (!ParseExpression()) return false;

    m.Commit();
    return true;
}



