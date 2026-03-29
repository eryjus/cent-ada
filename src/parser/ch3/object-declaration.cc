//=================================================================================================================
//  parser/ch3/object-declaration.cc -- All the permutations needed to parse an object declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  object_declaration ::= identifier_list : [constant] subtype_indication [:= expression] ;
//                       | identifier_list : [constant] constrained_array_definition [:= expression] ;
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
// -- Parse an Object Declaration
//    ---------------------------
ObjectDeclarationPtr Parser::ParseObjectDeclaration(void)
{
    Production p(*this, "object_declaration");
    MarkStream m(tokens, diags);
    SymbolTable::Checkpoint cp;
    std::unique_ptr<IdList> idList;
    bool isConstant = false;
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc = astLoc;
    SourceLoc_t whereLoc = TokenStream::EmptyLocation();
    TypeSpecPtr typeSpec = nullptr;
    ExprPtr expr = nullptr;
    std::string where;



    //
    // -- Parse the common prefix
    //    -----------------------
    idList = ParseIdentifierList();

    if (!idList) {
        p.At("no IdList");
        return nullptr;
    }


    if (!Require(TokenType::TOK_COLON)) {
        p.At("no TOK_COLON");
        return nullptr;
    }


    isConstant = Optional(TokenType::TOK_CONSTANT);



    //
    // -- Now, check for any duplicates and add the name if there are none
    //    ----------------------------------------------------------------
    for (int i = 0; i < idList->size(); i ++) {
        Symbol *sym = symTab.LocalLookup(idList->at(i).name);
        if (sym) {
            diags.Error(idList->at(i).loc, DiagID::DuplicateName, { idList->at(i).name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        } else {
            sym = symTab.Declare(loc, idList->at(i).name, SymbolTable::SymbolKind::Object);
        }
    }



    //
    // -- Here is where the rules differ
    //    ------------------------------
    loc = tokens.SourceLocation();
    typeSpec = ParseSubtypeIndication();
    if (typeSpec) {
        where = "subtype_indication";
        whereLoc = loc;
    } else {
        typeSpec = ParseConstrainedArrayDefinition(idList);
        if (typeSpec) {
            where = "constrained_array_definition";
            whereLoc = loc;
        } else {
            // -- These are not the tokens we are looking for
            p.At("Type indication fail");
            return nullptr;
        }
    }



    //
    // -- Now, check for an optional assignment to an expression
    //    ------------------------------------------------------
    loc = tokens.SourceLocation();
    TOKEN;
    if (Optional(TokenType::TOK_ASSIGNMENT)) {
        TOKEN;
        loc = tokens.SourceLocation();
        expr = ParseExpression();
        TOKEN;
        if (!expr) {
            diags.Error(loc, DiagID::MissingExpression, { "assignment" } );
        }

        where = "assignment and expression";
        whereLoc = loc;
    }



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(whereLoc, DiagID::MissingSemicolon, { where } );
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    TOKEN;
    p.At("proper obj decl");
    TOKEN;

    cp.Commit();
    m.Commit();

    return std::make_unique<ObjectDeclaration>(loc, std::move(idList), isConstant, std::move(typeSpec), std::move(expr));
}




