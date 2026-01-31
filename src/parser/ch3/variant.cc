//=================================================================================================================
//  parser/ch3/variant.cc -- Parse a variant
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  variant ::= when choice {| choice} => component_list
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
// -- Parse a Variant
//    ---------------
VariantPtr Parser::ParseVariant(RecordTypeSymbol *rec)
{
    Production p(*this, "variant");
    MarkStream m(tokens, diags);
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    ChoicePtr choice = nullptr;
    ChoiceListPtr choices = std::make_unique<ChoiceList>();
    ComponentListPtr comps = nullptr;


    //
    // -- start this parse with the required token
    //    ----------------------------------------
    if (!Require(TokenType::TOK_WHEN)) return nullptr;

    choice = ParseChoice();
    if (!choice) return nullptr;
    choices->push_back(std::move(choice));

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_VERTICAL_BAR)) {
        choice = ParseChoice();
        if (choice) {
            choices->push_back(std::move(choice));
        } else {
            diags.Error(loc, DiagID::ExtraVertialBar, { "choice" } );
            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- Complete the parse
    //    ------------------
    if (!Require(TokenType::TOK_ARROW)) return nullptr;

    comps = ParseComponentList(rec);
    if (!comps) return nullptr;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();

    return std::make_unique<Variant>(astLoc, std::move(choices), std::move(comps));
}



