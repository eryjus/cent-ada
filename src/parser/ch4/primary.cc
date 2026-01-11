//=================================================================================================================
//  parser/ch4/primary.cc -- A primary expression
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
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
//  So, this is a mess (like 'name').  several of these productions can start with similar symbols and end
//  up in different places -- meaning you likely cannot determine what is the correct production until you
//  get to the end.  The above alternatives are reorganized based on concrete and indeterminate alternatives
//  based on the starting tokens and problematic alteratives.
//
//  * null                      TOK_NULL
//  * numeric_literal           TOK_NUMERIC_LITERAL
//  * string_literal            TOK_STRING_LITERAL
//  * allocator                 TOK_NEW
//
//  * function_call             TOK_IDENTIFIER:subprogram
//  * name                      TOK_IDENTIFIER:other-non-type || TOK_CHARACTER_LITERAL || TOK_STRING_LITERAL
//  * type_conversion           TOK_IDENTIFIER:type_mark TOK_LEFT_PARENTHESIS
//  * qualified_expression      TOK_IDENTIFIER:type_mark TOK_APOSTROPHE
//
//  * aggregate                 TOK_LEFT_PARENTHESIS expression ...
//  * ( expression )            TOK_LEFT_PARENTHESIS expression
//
//  Therefore, this production will make extensive use of the `Optional` and `Peek` functions to make some
//  critical decisions while parsing.
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
ExprPtr Parser::ParsePrimary(void)
{
    Production p(*this, "primary");
    MarkStream m(tokens, diags);
    SourceLoc_t loc = tokens.SourceLocation();
    SourceLoc_t astLoc = tokens.SourceLocation();

    if (Optional(TokenType::TOK_NULL)) {
        NullLiteralExprPtr rv = std::make_unique<NullLiteralExpr>(astLoc);
        m.Commit();
        return std::move(rv);
    }


    //
    // -- The spec calls for a `numeric_literal` here.  I am going to split them out
    //    here rather than in the lexer.
    //    --------------------------------------------------------------------------
    if (tokens.Current() == TokenType::TOK_UNIVERSAL_INT_LITERAL) {
        IntLiteralExprPtr rv = std::make_unique<IntLiteralExpr>(astLoc, std::get<IntLiteral>(tokens.Payload()));
        tokens.Advance();
        m.Commit();
        return std::move(rv);
    }


    if (tokens.Current() == TokenType::TOK_UNIVERSAL_REAL_LITERAL) {
        RealLiteralExprPtr rv = std::make_unique<RealLiteralExpr>(astLoc, std::get<RealLiteral>(tokens.Payload()));
        tokens.Advance();
        m.Commit();
        return std::move(rv);
    }


    if (tokens.Current() == TokenType::TOK_STRING_LITERAL) {
        StringLiteralExprPtr rv = std::make_unique<StringLiteralExpr>(astLoc, std::get<StringLiteral>(tokens.Payload()));
        tokens.Advance();
        m.Commit();
        return std::move(rv);
    }


    if (tokens.Current() == TokenType::TOK_NEW) {
        if (ParseAllocator()) {
            m.Commit();
            return true;
        }

        m.Reset();
    }


    if (tokens.Current() == TokenType::TOK_CHARACTER_LITERAL) {
        if (ParseNameExpr()) {
            m.Commit();
            return true;
        }

        m.Reset();
    }


    if (ParseOperatorSymbol()) {
        m.Commit();
        return true;
    }


    //
    // -- Now, an Identifier can start several different alternatives.  Check here for each.
    //    ----------------------------------------------------------------------------------
    if (tokens.Current() == TokenType::TOK_IDENTIFIER) {
        IdentifierLexeme idLex = std::get<IdentifierLexeme>(tokens.Payload());
        const std::vector<Symbol *> *vec = scopes.Lookup(idLex.name);

        if (vec != nullptr) {
            TypeSymbol *type = nullptr;

            for (auto &sym : *vec) {
                if (sym->kind == Symbol::SymbolKind::Deleted) continue;
                if (sym->kind == Symbol::SymbolKind::Type || sym->kind == Symbol::SymbolKind::IncompleteType) {
                    if (tokens.Peek() == TokenType::TOK_APOSTROPHE) {
                        if (tokens.Peek(2) == TokenType::TOK_DIGITS || tokens.Peek(2) == TokenType::TOK_DELTA) {
                            if (ParseNameExpr()) {
                                m.Commit();
                                return true;
                            }
                        }
                        if (ParseQualifiedExpression()) {
                            m.Commit();
                            return true;
                        } else if (ParseNameExpr()) {
                            m.Commit();
                            return true;
                        }
                    }
                    if (tokens.Peek() == TokenType::TOK_LEFT_PARENTHESIS) {
                        if (ParseTypeConversion()) {
                            m.Commit();
                            return true;
                        }
                    }
                }
                if (sym->kind == Symbol::SymbolKind::Subprogram) {
                    if (ParseFunctionCall()) {
                        m.Commit();
                        return true;
                    }
                }
                if (ParseNameExpr()) {
                    m.Commit();
                    return true;
                }

                diags.Error(loc, DiagID::UnknownError, { __FILE__, __PRETTY_FUNCTION__, std::to_string(__LINE__) } );
            }
        }
    }


    //
    // -- Now, everything else will start with a TOK_LEFT_PAREN
    //    -----------------------------------------------------
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;


    //
    // -- If we have an expression followed by a TOK_RIGHT_PARENTHESIS, then we have a parenthetical expression
    //    -----------------------------------------------------------------------------------------------------
    if (ParseExpression()) {
        if (Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            m.Commit();
            return true;
        }
    }

    // -- we want to reset here and try again with an aggregate -- the only thing left
    m.Reset();

    if (ParseAggregate()) {
        m.Commit();
        return true;
    }

    return nullptr;
}


