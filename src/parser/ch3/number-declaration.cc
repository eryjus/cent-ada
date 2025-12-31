//=================================================================================================================
//  parser/ch3/number-declaration.cc -- All the permutations needed to parse a number declaration
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
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
bool Parser::ParseNumberDeclaration(void)
{
    Production p(*this, "number_declaration");
    MarkStream m(tokens, diags);
    MarkSymbols s(scopes);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();
    SourceLoc_t loc;


    //
    // -- Get the list of identifiers
    //    ---------------------------
    if (!ParseIdentifierList(idList.get())) return false;


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
    // -- there are 3 consecutive tokens required
    //    ---------------------------------------
    if (!Require(TokenType::TOK_COLON)) return false;
    if (!Require(TokenType::TOK_CONSTANT)) return false;
    if (!Require(TokenType::TOK_ASSIGNMENT)) return false;


    //
    // -- This expression needs to be a `universal_static_expression`.  Therefore,
    //    the value must be static and must also evalueate to either a `universal_real`
    //    or a `universal_integer` type.
    //    -----------------------------------------------------------------------------
    ParseUniversalStaticExpression();



    //
    // -- Finally, the production must end with a TOK_SEMICOLON
    //    -----------------------------------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_SEMICOLON)) {
        diags.Error(loc, DiagID::MissingSemicolon, { "expression" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}



