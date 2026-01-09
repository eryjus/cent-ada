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
    std::string discard;
    SourceLoc_t astLoc;

    if (!ParsePrefix())                     return nullptr;
    if (!Require(TokenType::TOK_DOT))                  return nullptr;
    if (!ParseSelector())                   return nullptr;


    SelectedNamePtr rv = std::make_unique<SelectedName>(astLoc, nullptr, nullptr);

    m.Commit();
    return std::move(rv);
}



//
// -- Parse an Selected Component for Name
//
//    For this function, name has already been accounted for
//    ------------------------------------------------------
bool Parser::ParseName_SelectedComponentSuffix(void)
{
    Production p(*this, "selected_component(suffix)");
    MarkStream m(tokens, diags);

    if (!Require(TokenType::TOK_DOT))           return false;
    if (!ParseSelector())                       return false;

    m.Commit();
    return true;
}



