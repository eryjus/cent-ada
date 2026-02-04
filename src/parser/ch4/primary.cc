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

    TOKEN;

    if (Optional(TokenType::TOK_NULL)) {
        m.Commit();

        return std::make_unique<NullLiteralExpr>(astLoc);
    }


    //
    // -- The spec calls for a `numeric_literal` here.  I am going to split them out
    //    here rather than in the lexer.
    //    --------------------------------------------------------------------------
    if (tokens.Current() == TokenType::TOK_UNIVERSAL_INT_LITERAL) {
        std::string lit = std::get<IntLiteral>(tokens.Payload()).lexeme;
        tokens.Advance();
        p.At("UNIVERSAL_INT_LITERAL");
        m.Commit();

        return std::make_unique<IntLiteralExpr>(astLoc, lit);
    }


    if (tokens.Current() == TokenType::TOK_UNIVERSAL_REAL_LITERAL) {
        std::string lit = std::get<RealLiteral>(tokens.Payload()).lexeme;
        tokens.Advance();
        p.At("UNIVERSAL_REAL_LITERAL");
        m.Commit();

        return std::make_unique<RealLiteralExpr>(astLoc, lit);
    }


    if (tokens.Current() == TokenType::TOK_STRING_LITERAL) {
        std::string lit = std::get<StringLiteral>(tokens.Payload()).lexeme;
        tokens.Advance();
        p.At("UNIVERSAL_STRING_LITERAL");
        m.Commit();

        return std::make_unique<StringLiteralExpr>(astLoc, lit);
    }


    if (tokens.Current() == TokenType::TOK_NEW) {
        AllocatorExprPtr rv = ParseAllocator();
        if (rv) {
            p.At("NEW");
            m.Commit();

            return rv;
        }

        m.Reset();
    }


    if (tokens.Current() == TokenType::TOK_CHARACTER_LITERAL) {
        NamePtr name = ParseNameExpr();
        if (name) {
            p.At("Character Literal");
            m.Commit();

            return std::make_unique<NameExpr>(astLoc, std::move(name));
        }

        m.Reset();
    }


    {   // -- we want a scope here for overall readability
        NamePtr name = ParseOperatorSymbol();
        if (name) {
            p.At("Operator Symbol");
            m.Commit();

            return std::make_unique<NameExpr>(astLoc, std::move(name));;
        }
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
                NamePtr name = nullptr;
                if (sym->kind == Symbol::SymbolKind::Deleted) continue;
                if (sym->kind == Symbol::SymbolKind::Type || sym->kind == Symbol::SymbolKind::IncompleteType) {
                    if (tokens.Peek() == TokenType::TOK_APOSTROPHE) {
                        if (tokens.Peek(2) == TokenType::TOK_DIGITS || tokens.Peek(2) == TokenType::TOK_DELTA) {
                            name = ParseNameExpr();
                            if (name) {
                                p.At("digits/delta next");
                                m.Commit();

                                return std::make_unique<NameExpr>(astLoc, std::move(name));;
                            }
                        }
                        ExprPtr rv = ParseQualifiedExpression();
                        if (rv) {
                            p.At("Qualified Expression");
                            m.Commit();

                            return rv;
                        } else {
                            name = ParseNameExpr();
                            if (name) {
                                p.At("Name Expression");
                                m.Commit();

                                return std::make_unique<NameExpr>(astLoc, std::move(name));;
                            }
                        }
                    }
                    if (tokens.Peek() == TokenType::TOK_LEFT_PARENTHESIS) {
                        ExprPtr rv = ParseTypeConversion();
                        if (rv) {
                            p.At("Type Conversion");
                            m.Commit();

                            return rv;
                        }
                    }
                }


                if (sym->kind == Symbol::SymbolKind::Subprogram) {
                    name = ParseFunctionCall();
                    if (name) {
                        p.At("Function Call");
                        m.Commit();

                        return std::make_unique<NameExpr>(astLoc, std::move(name));;
                    }
                }


                name = ParseNameExpr();
                if (name) {
                    p.At("Name Expression 2");
                    m.Commit();

                    return std::make_unique<NameExpr>(astLoc, std::move(name));;
                }

                diags.Error(loc, DiagID::UnknownError, { __FILE__, __PRETTY_FUNCTION__, std::to_string(__LINE__) } );
            }
        }
    }


    //
    // -- Now, everything else will start with a TOK_LEFT_PAREN
    //    -----------------------------------------------------
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) {
        p.At("No Paren");
        return nullptr;
    }


    //
    // -- If we have an expression followed by a TOK_RIGHT_PARENTHESIS, then we have a parenthetical expression
    //    -----------------------------------------------------------------------------------------------------
    ExprPtr expr = ParseExpression();
    if (expr) {
        if (Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
            p.At("Parenthetical Expression");
            m.Commit();

            return expr;
        }
    }


    //
    // -- we want to reset here and try again with an aggregate -- the only thing left
    //    ----------------------------------------------------------------------------
    m.Reset();

    expr = ParseAggregate();
    if (expr) {
        p.At("Aggregate");
        m.Commit();

        return expr;
    }


    p.At("Failed");
    return nullptr;
}


