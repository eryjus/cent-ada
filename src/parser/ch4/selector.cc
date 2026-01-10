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
    Id id;
    NamePtr selector = nullptr;
    SelectedNamePtr rv = nullptr;

    if (Optional(TokenType::TOK_ALL)) {
        rv = std::make_unique<SelectedName>(astLoc, std::move(prefix), nullptr);
        m.Commit();
        return std::move(rv);
    }

    if (tokens.Current() == TokenType::TOK_CHARACTER_LITERAL) {
        CharacterLiteralNamePtr charSelector = std::make_unique<CharacterLiteralName>(astLoc, std::get<CharLiteral>(tokens.Payload()));
        tokens.Advance();
        rv = std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(charSelector));

        m.Commit();
        return std::move(rv);
    }

    SourceLoc_t loc = tokens.SourceLocation();
    if ((selector = std::move(ParseSimpleName())) != nullptr) {
        if (!scopes.Lookup(id.name)) {
            diags.Error(loc, DiagID::UnknownName, { "selector"} );
            // -- allow the parse to continue
        }

        rv = std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(selector));

        m.Commit();
        return std::move(rv);
    }

    if ((selector = std::move(ParseOperatorSymbol())) != nullptr) {
        rv = std::make_unique<SelectedName>(astLoc, std::move(prefix), std::move(selector));

        m.Commit();
        return rv;
    }

    return nullptr;
}


