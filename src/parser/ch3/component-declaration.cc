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
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    SubtypeIndicationPtr type = nullptr;
    ExprPtr expr = nullptr;


    //
    // -- Start by getting the list of identifiers
    //    ----------------------------------------
    idList = ParseIdentifierList();
    if (!idList) return nullptr;

    for (int i = 0; i < idList->size(); i ++) {
        std::unique_ptr<ComponentSymbol> sym = std::make_unique<ComponentSymbol>(idList->at(i).name, idList->at(i).loc, scopes.CurrentScope());
        rec->components.push_back(sym.get());
        scopes.Declare(std::move(sym));
    }

    if (!Require(TokenType::TOK_COLON)) return nullptr;
    if ((type = std::move(ParseComponentSubtypeDefinition())) == nullptr) return nullptr;


    //
    // -- find the optional default initialization value
    //    ----------------------------------------------
    if (Optional(TokenType::TOK_ASSIGNMENT)) {
        loc = tokens.SourceLocation();
        if ((expr = std::move(ParseExpression())) == nullptr) {
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
    ComponentDeclarationPtr rv = std::make_unique<ComponentDeclaration>(astLoc, std::move(idList), std::move(type), std::move(expr));

    s.Commit();
    m.Commit();
    return std::move(rv);
}



