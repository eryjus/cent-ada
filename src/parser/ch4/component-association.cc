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

    diags.Debug("Preparing to parse a Component Association: " + std::string(tokens.tokenStr(tokens.Current())));

    if (ParseChoice()) {
        diags.Debug(".. 1 choice found; parsing more...? " + std::string(tokens.tokenStr(tokens.Current())));
        while (Optional(TokenType::TOK_VERTICAL_BAR)) {
            loc = tokens.SourceLocation();
            if (!ParseChoice()) {
                diags.Error(loc, DiagID::ExtraVertialBar, { "component association" } );
            }
        }

        if (!Require(TokenType::TOK_ARROW)) return false;
    }
    diags.Debug(".. past any possible choices: " + std::string(tokens.tokenStr(tokens.Current())));

    if (!ParseExpression()) return false;

    diags.Debug("Done parsing Component Association: " + std::string(tokens.tokenStr(tokens.Current())));

    m.Commit();
    return true;
}



