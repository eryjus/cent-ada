//=================================================================================================================
//  parser/ch4/primary.cc -- A primary expression
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
//  primary ::= numeric_literal
//            | null
//            | aggregate
//            | string_literal
//            | name
//            | allocator
//            | function_call
//            | type_conversion
//            | qualified_expression
//            | ( expression )
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
// -- Parse a Primary
//    ---------------
bool Parser::ParsePrimary(void)
{
    Production p(*this, "primary");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t loc;

    //
    // -- The spec calls for a `numeric_literal` here.  I am going to split them out
    //    here rather than in the lexer.
    //    --------------------------------------------------------------------------
    if (Optional(TokenType::TOK_UNIVERSAL_INT_LITERAL)) {
        m.Commit();
        return true;
    }

    if (Optional(TokenType::TOK_UNIVERSAL_REAL_LITERAL)) {
        m.Commit();
        return true;
    }

    if (Optional(TokenType::TOK_NULL)) {
        m.Commit();
        return true;
    }


    if (ParseAggregate()) {
        m.Commit();
        return true;
    }

    if (Optional(TokenType::TOK_LEFT_PARENTHESIS)) {
        if (!ParseExpression()) return false;

        if (Optional(TokenType::TOK_RIGHT_PARENTHESIS)) {
            m.Commit();
            return true;
        }

        switch (tokens.Current()) {
        case TokenType::TOK_COMMA:
        case TokenType::TOK_WHEN:
        case TokenType::TOK_OTHERS:
        case TokenType::TOK_DOUBLE_DOT:
        case TokenType::TOK_VERTICAL_BAR:
        case TokenType::TOK_ARROW:
            loc = tokens.SourceLocation();
            if (ParseAggregateMore()) {
                SourceLoc_t loc = tokens.SourceLocation();

                if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
                    diags.Error(loc, DiagID::MissingRightParen, { "aggregate" } );
                    // -- keep going
                }

                m.Commit();
                return true;
            }

            diags.Error(loc, DiagID::UnknownError, { __FILE__, __PRETTY_FUNCTION__, std::to_string(__LINE__) } );
            //    fall through
        default:
            m.Reset();
        }
    }


    if (Optional(TokenType::TOK_STRING_LITERAL)) {
        m.Commit();
        return true;
    }

    if (ParseNameExpr(id)) {
        m.Commit();
        return true;
    }

    if (ParseAllocator()) {
        m.Commit();
        return true;
    }

    if (ParseFunctionCall()) {
        m.Commit();
        return true;
    }

    if (ParseTypeConversion()) {
        m.Commit();
        return true;
    }

    if (ParseQualifiedExpression()) {
        m.Commit();
        return true;
    }


    return false;
}



