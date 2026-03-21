//=================================================================================================================
//  parser/ch5/label.cc -- Parse a labels
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  label ;;= << label_simple_name >>
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Feb-21  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a list of labels
//    ----------------------
NamePtr Parser::ParseLabel(void)
{
    Production p(*this, "label");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    std::vector<Symbol *> *vec = nullptr;
    NamePtr label;


    if (!Require(TokenType::TOK_LEFT_LABEL_BRACKET)) return nullptr;

// TODO: Return to this production    label = ParseSimpleName();
// Also TODO:         if (!label) return nullptr;

    Id id;
    loc = tokens.SourceLocation();
    if (RequireIdent(id)) {
        label = std::make_unique<SimpleName>(astLoc, id);
    }


    if (!label) return nullptr;

    if (scopes.IsLocalDefined(label->GetName())) {
        vec = scopes.CurrentScope()->LocalLookup(label->GetName());

        if (vec->at(0)->kind != Symbol::SymbolKind::UndefinedLabel && vec->at(0)->kind != Symbol::SymbolKind::Deleted) {
            diags.Error(loc, DiagID::DuplicateName, { "Statement Label" } );
            diags.Note(loc, DiagID::DuplicateName2, { TokenStream::Get().SourceLine() } );
        } else if (vec->at(0)->kind == Symbol::SymbolKind::UndefinedLabel) {
            vec->at(0)->kind = Symbol::SymbolKind::Deleted;
        }
    }

    scopes.Declare(std::make_unique<LabelSymbol>(std::string(label->GetName()), astLoc, scopes.CurrentScope()));


    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_LABEL_BRACKET)) {
        diags.Error(loc, DiagID::MissingRightLabelBracket, { label ? label->GetName() : "" } );
    }


    p.At("completed label");
    TOKEN;
    m.Commit();
    s.Commit();

    return label;
}
