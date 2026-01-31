//=================================================================================================================
//  parser/ch3/index-constraint.cc -- Define an index constraint
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  index_constraint ::= ( discrete_range {, discrete_range} )
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
// -- Parse an Index Constraint
//    -------------------------
IndexConstraintPtr Parser::ParseIndexConstraint(void)
{
    Production p(*this, "index_constraint");
    MarkStream m(tokens, diags);
    SourceLoc_t loc, astLoc = tokens.SourceLocation();      // -- only init astLoc
    DiscreteRangePtr range = nullptr;
    DiscreteRangeListPtr vec = std::make_unique<std::vector<DiscreteRangePtr>>();


    //
    // -- This production start with a paren
    //    ----------------------------------
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;


    //
    // -- and then a range for the index
    //    ------------------------------
    range = ParseDiscreteRange();
    if (!range) return nullptr;
    vec->push_back(std::move(range));



    //
    // -- followed by any number of additional indices
    //    --------------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        range = ParseDiscreteRange();
        if (!range) {
            diags.Error(loc, DiagID::ExtraComma, { "discrete_range" } );

            // -- continue on
            break;
        }

        vec->push_back(std::move(range));
        loc = tokens.SourceLocation();
    }


    //
    // -- The closing paren is required
    //    -----------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, {"discrete range"});
        // -- continue on in hopes that this does not create a cascade of errors
    }



    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();

    return std::make_unique<IndexConstraint>(astLoc, false, std::move(vec));
}



