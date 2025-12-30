//=================================================================================================================
//  parser/ch3/discriminant-association.cc -- Parse a discriminant association
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  discriminant_association ::= [discriminant_simple_name {| discriminant_simple_name} => ] expression
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
// -- Parse a Discriminant Association
//    --------------------------------
bool Parser::ParseDiscriminantAssociation(void)
{
    Production p(*this, "disriminant_association");
    MarkStream m(tokens, diags);
    std::vector<Symbol *> *vec = nullptr;
    std::string id;
    SourceLoc_t loc;


    //
    // -- Start by checking if there is a discriminant simple name
    //    --------------------------------------------------------
    loc = tokens.SourceLocation();
    if (ParseDiscriminantSimpleName(id)) {
        //
        // -- This will only work if the next token is a TOK_VERTICAL_BAR or TOK_ARROW
        //    Otherwise it will be an expression as a simple name
        //    ------------------------------------------------------------------------
        if (tokens.Current() != TOK_VERTICAL_BAR && tokens.Current() != TOK_ARROW) {
            // -- not the correct condition, backtrack and parse an expression
            m.Reset();
            goto expr;
        }


        //
        // -- The name should be known -- so check
        //    ------------------------------------
#if 0
        vec = scopes.Lookup(id);
        if (!vec || vec->empty()) {
            diags.Error(loc, DiagID::UnknownName, { "discriminant simple name" } );
        }

        if (sym && sym->kind != Symbol::SymbolKind::Object) {
            diags.Error(loc, DiagID::InvalidName, { id, "discriminant simple name" } );
        }
#endif


        //
        // -- Check for optional more
        //    -----------------------
        loc = tokens.SourceLocation();
        while (Optional(TOK_VERTICAL_BAR)) {
            if (!ParseDiscriminantSimpleName(id)) {
                diags.Error(loc, DiagID::ExtraVertialBar, { "discriminant simple name" } );
                break;
            }

#if 0
            sym = scopes.Lookup(id);
            if (sym == nullptr) {
                diags.Error(loc, DiagID::UnknownName, { "discriminant simple name" } );
            }

            if (sym && sym->kind != Symbol::SymbolKind::Object) {
                diags.Error(loc, DiagID::InvalidName, { id, "discriminant simple name" } );
            }
#endif
            loc = tokens.SourceLocation();
        }


        if (!Require(TOK_ARROW)) return false;
    }

expr:
    loc = tokens.SourceLocation();
    if (!ParseExpression()) {
        diags.Error(loc, DiagID::MissingExpression, { "discriminant association" } );
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



