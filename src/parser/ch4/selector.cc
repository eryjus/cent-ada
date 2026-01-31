//=================================================================================================================
//  parser/ch4/selector.cc -- A selector for a selected component
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  selected_component ::= prefix . selector
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
// -- Parse a Selector
//    ----------------
SelectedNamePtr Parser::ParseSelector(NamePtr &prefix)
{
    Production p(*this, "selector");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    NamePtr selector = nullptr;
    SelectedNamePtr rv = nullptr;
    Id id;


    if (Optional(TokenType::TOK_ALL)) {
        m.Commit();

        return std::make_unique<SelectedName>(astLoc, std::move(prefix), nullptr);
    }


    if (tokens.Current() == TokenType::TOK_CHARACTER_LITERAL) {
        CharacterLiteralNamePtr charSelector = std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload()));
        tokens.Advance();
        m.Commit();

        return std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(charSelector));
    }


    SourceLoc_t loc = tokens.SourceLocation();
    selector = ParseSimpleName();
    if (selector) {
        if (!scopes.Lookup(id.name)) {
            diags.Error(loc, DiagID::UnknownName, { "selector"} );
            // -- allow the parse to continue
        }

        m.Commit();
        return std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(selector));
    }


    selector = ParseOperatorSymbol();
    if (selector) {
        m.Commit();

        return std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(selector));;
    }



    return nullptr;
}


