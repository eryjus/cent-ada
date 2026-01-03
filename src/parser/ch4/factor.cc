//=================================================================================================================
//  parser/ch4/factor.cc -- A factor
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  factor ::= primary [** primary]
//           | abs primary
//           | not primary
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-31  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse a Factor
//    --------------
bool Parser::ParseFactor(void)
{
    Production p(*this, "factor");
    MarkStream m(tokens, diags);
    SourceLoc_t loc;

    if (Require(TokenType::TOK_ABS)) {
        loc = tokens.SourceLocation();
        if (!ParsePrimary()) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "ABS" } );
        }

        m.Commit();
        return true;
    } else if (Require(TokenType::TOK_NOT)) {
        loc = tokens.SourceLocation();
        if (!ParsePrimary()) {
            diags.Error(loc, DiagID::InvalidPrimaryExpr, { "NOT" } );
        }

        m.Commit();
        return true;
    } else {
        if (!ParsePrimary())    return false;

        if (Optional(TokenType::TOK_DOUBLE_STAR)) {
            if (!ParsePrimary())    return false;
        }

        m.Commit();
        return true;
    }

    return false;
}



