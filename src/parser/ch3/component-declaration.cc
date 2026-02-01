//=================================================================================================================
//  parser/ch3/component-declaration.cc -- Parse a component declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  component_declaration ::= identifier_list : component_subtype_definition [:+ expression] ;
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
// -- Parse a Component Declaration
//    -----------------------------
ComponentDeclarationPtr Parser::ParseComponentDeclaration(RecordTypeSymbol *rec)
{
    Production p(*this, "component_declaration");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    SubtypeIndicationPtr type = nullptr;
    ExprPtr expr = nullptr;


    //
    // -- Start by getting the list of identifiers
    //    ----------------------------------------
    idList = ParseIdentifierList();
    if (!idList) {
        p.At("no IdList");
        return nullptr;
    }

    for (int i = 0; i < idList->size(); i ++) {
        ComponentSymbolPtr sym = std::make_unique<ComponentSymbol>(idList->at(i).name, idList->at(i).loc, scopes.CurrentScope());
        rec->components.push_back(sym.get());
        scopes.Declare(std::move(sym));
    }

    if (!Require(TokenType::TOK_COLON)) {
        p.At("no TOK_COLON");
        return nullptr;
    }


    type = ParseComponentSubtypeDefinition();
    if (!type) {
        p.At("No Component Subtype Definition");
        return nullptr;
    }


    //
    // -- find the optional default initialization value
    //    ----------------------------------------------
    if (Optional(TokenType::TOK_ASSIGNMENT)) {
        loc = tokens.SourceLocation();

        expr = ParseExpression();
        if (!expr) {
            diags.Error(loc, DiagID::MissingExpression, { "component declaration assignment" } );
        }

        // -- continue on as if nothing happened
    }

    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(tokens.SourceLocation(), DiagID::MissingSemicolon, { "component declaration" } );
        // -- continue on in hopes that this does not create a cascade of errors

    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();

    return std::make_unique<ComponentDeclaration>(astLoc, std::move(idList), std::move(type), std::move(expr));
}



