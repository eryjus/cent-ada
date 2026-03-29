//=================================================================================================================
//  parser/ch3/number-declaration.cc -- All the permutations needed to parse a number declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  number_declaration ::= identifier_list : constant := universal_static_expression;
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Number Declaration
//    --------------------------
ObjectDeclarationPtr Parser::ParseNumberDeclaration(void)
{
    Production p(*this, "number_declaration");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    std::unique_ptr<IdList> idList;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    ExprPtr expr = nullptr;


    //
    // -- Get the list of identifiers
    //    ---------------------------
    idList = ParseIdentifierList();
    if (!idList) return nullptr;


    //
    // -- Now, check for any duplicates and add the name if there are none
    //    ----------------------------------------------------------------
    for (int i = 0; i < idList->size(); i ++) {
        Symbol *sym = symTab.LocalLookup(idList->at(i).name);
        if (sym) {
            diags.Error(idList->at(i).loc, DiagID::DuplicateName, { idList->at(i).name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        } else {
            symTab.Declare(astLoc, idList->at(i).name, SymbolTable::SymbolKind::Object);
        }
    }


    //
    // -- there are 3 consecutive tokens required
    //    ---------------------------------------
    if (!Require(TokenType::TOK_COLON)) return nullptr;
    if (!Require(TokenType::TOK_CONSTANT)) return nullptr;
    if (!Require(TokenType::TOK_ASSIGNMENT)) return nullptr;


    //
    // -- This expression needs to be a `universal_static_expression`.  Therefore,
    //    the value must be static and must also evalueate to either a `universal_real`
    //    or a `universal_integer` type.
    //    -----------------------------------------------------------------------------
    expr = ParseUniversalStaticExpression();



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "expression" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    cp.Commit();
    m.Commit();

    return std::make_unique<ObjectDeclaration>(astLoc, std::move(idList), true, nullptr, std::move(expr));
}



