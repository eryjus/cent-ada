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
bool Parser::ParseVariant(RecordTypeSymbol *rec)
{
    Production p(*this, "variant");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;


    //
    // -- start this parse with the required token
    //    ----------------------------------------
    if (!Require(TokenType::TOK_WHEN)) return false;
    if (!ParseChoice()) return false;

    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_VERTICAL_BAR)) {
        if (!ParseChoice()) {
            diags.Error(loc, DiagID::ExtraVertialBar, { "choice" } );
            break;
        }

        loc = tokens.SourceLocation();
    }


    //
    // -- Complete the parse
    //    ------------------
    if (!Require(TokenType::TOK_ARROW)) return false;
    if (!ParseComponentList(rec)) return false;


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



