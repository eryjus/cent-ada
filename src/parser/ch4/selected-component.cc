//=================================================================================================================
//  parser/ch4/selected-component.cc -- A selected component
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
// -- Parse a Selected Component
//    --------------------------
SelectedNamePtr Parser::ParseSelectedComponent(void)
{
    Production p(*this, "selected_component");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc =TokenStream::Get().SourceLocation();
    NamePtr prefix = nullptr;
    SelectedNamePtr selector = nullptr;
    std::string discard;


    prefix = ParsePrefix();
    if (!prefix)                                                    return nullptr;
    if (!Require(TokenType::TOK_DOT))                               return nullptr;

    selector = ParseSelector(prefix);
    if (!selector) return nullptr;


    m.Commit();
    return selector;
}



//
// -- Parse an Selected Component for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
SelectedNamePtr Parser::ParseName_SelectedComponentSuffix(NamePtr &prefix)
{
    Production p(*this, "selected_component(suffix)");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SelectedNamePtr selector = nullptr;

    if (!Require(TokenType::TOK_DOT)) return nullptr;

    selector = ParseSelector(prefix);
    if (!selector) return nullptr;

    m.Commit();

    return selector;
}



