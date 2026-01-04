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
    MarkSymbols s(scopes);
    std::unique_ptr<IdList> idList;
    bool isConstant = false;
    std::string where;
    SourceLoc_t astLoc = tokens.SourceLocation();
    SourceLoc_t loc;
    TypeSpecPtr typeSpec;

    //
    // -- Parse the common prefix
    //    -----------------------
    idList = ParseIdentifierList();
    if (!idList) return nullptr;
    if (!Require(TokenType::TOK_COLON)) return nullptr;
    isConstant = Optional(TokenType::TOK_CONSTANT);


    //
    // -- Now, check for any duplicates and add the name if there are none
    //    ----------------------------------------------------------------
    for (int i = 0; i < idList->size(); i ++) {
        if (scopes.IsLocalDefined(idList->at(i).name)) {
            diags.Error(idList->at(i).loc, DiagID::DuplicateName, { idList->at(i).name } );

            const std::vector<Symbol *> *vec = scopes.Lookup(std::string_view(idList->at(i).name));
            SourceLoc_t loc2 = vec->at(0)->loc;
            diags.Error(loc, DiagID::DuplicateName2, { } );
        } else {
            scopes.Declare(std::make_unique<ObjectSymbol>(idList->at(i).name, idList->at(i).loc, scopes.CurrentScope()));
        }
    }


    //
    // -- Here is where the rules differ
    //    ------------------------------
    ;
    if ((typeSpec = ParseSubtypeIndication()) != nullptr) {
        where = "subtype_indication";
    } else if (ParseConstrainedArrayDefinition(idList.get())) {
        where = "constrained_array_definition";
    } else {
        // -- These are not the tokens we are looking for
        return nullptr;
    }



    //
    // -- Now, check for an optional assignment to an expression
    //    ------------------------------------------------------
    loc = tokens.SourceLocation();
    if (Optional(TokenType::TOK_ASSIGNMENT)) {
        if (!ParseExpression()) {
            diags.Error(loc, DiagID::MissingExpression, { "assignment" } );
        }

        where = "assignment and expression";
    }


    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { where } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------

    ObjectDeclarationPtr rv = std::make_unique<ObjectDeclaration>(loc, std::move(idList), isConstant, nullptr, nullptr);


    s.Commit();
    m.Commit();
    return rv;
}




