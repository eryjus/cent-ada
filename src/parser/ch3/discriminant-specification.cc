//=================================================================================================================
//  parser/ch3/discriminant-specification.cc -- Parse a discriminant specification
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  discriminant_specification ::= identifier_list : type _mark [:= expression]
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
// -- Parse a Discriminant Specification
//    ----------------------------------
bool Parser::ParseDiscriminantSpecification(void)
{
    Production p(*this, "discriminant_specification");
    MarkStream m(tokens, diags);
    MarkScope s(scopes);
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();
    SourceLoc_t loc;


    //
    // -- Get a list of identifiers
    //    -------------------------
    if (!ParseIdentifierList(idList.get())) return false;


    for (int i = 0; i < idList->size(); i ++) {
        scopes.Declare(std::make_unique<DiscriminantSymbol>(idList->at(i).name, idList->at(i).loc, scopes.CurrentScope()));
    }


    //
    // -- Get the TOK_COLON
    //    -----------------
    if (!Require(TokenType::TOK_COLON)) return false;


    //
    // -- Now get the type
    //    ----------------
    if (!ParseTypeMark()) return false;


    //
    // -- Finally an optional assignment
    //    ------------------------------
    if (Optional(TokenType::TOK_ASSIGNMENT)) {
        loc = tokens.SourceLocation();
        if (!ParseExpression()) {
            diags.Error(loc, DiagID::MissingExpression, { "assignment" } );
        }
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    s.Commit();
    m.Commit();
    return true;
}



