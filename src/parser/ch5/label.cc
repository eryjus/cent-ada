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
    SymbolTable::Checkpoint cp;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    std::vector<Symbol *> *vec = nullptr;
    NamePtr label = nullptr;


    if (!Require(TokenType::TOK_LEFT_LABEL_BRACKET)) return nullptr;

    Id id;
    loc = tokens.SourceLocation();
    if (RequireIdent(id)) {
        label = std::make_unique<SimpleName>(astLoc, id);
    }


    if (!label) return nullptr;


    Symbol *sym = symTab.LocalLookup(id.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::UndefinedLabel) {
            sym->kind = SymbolTable::SymbolKind::Label;
        } else {
            diags.Error(id.loc, DiagID::DuplicateName, { id.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        symTab.Declare(id.loc, id.name, SymbolTable::SymbolKind::Label);
    }


    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_LABEL_BRACKET)) {
        diags.Error(loc, DiagID::MissingRightLabelBracket, { label ? label->GetName() : "" } );
    }


    p.At("completed label");
    TOKEN;
    cp.Commit();
    m.Commit();

    return label;
}
