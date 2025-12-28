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
    std::unique_ptr<IdList> idList = std::make_unique<IdList>();
    SourceLoc_t loc;


    //
    // -- Get a list of identifiers
    //    -------------------------
    if (!ParseIdentifierList(idList.get())) return false;


    //
    // -- Get the TOK_COLON
    //    -----------------
    if (!Require(TOK_COLON)) return false;


    //
    // -- Now get the type
    //    ----------------
    if (!ParseTypeMark()) return false;


    //
    // -- Finally an optional assignment
    //    ------------------------------
    if (Optional(TOK_ASSIGNMENT)) {
        loc = tokens.SourceLocation();
        if (!ParseExpression()) {
            diags.Error(loc, DiagID::MissingExpression, { "assignment" } );
        }
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return true;
}



