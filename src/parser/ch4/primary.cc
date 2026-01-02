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
bool Parser::ParsePrimary(void)
{
    Production p(*this, "primary");
    MarkStream m(tokens, diags);
    Id id;
    SourceLoc_t loc = tokens.SourceLocation();

    diags.Debug("*** Starting to parse a 'Primary' " + std::string(tokens.tokenStr(tokens.Current())));

    if (Optional(TokenType::TOK_NULL)) {
        diags.Debug("*** .. trivial NULL");
        m.Commit();
        return true;
    }


    //
    // -- The spec calls for a `numeric_literal` here.  I am going to split them out
    //    here rather than in the lexer.
    //    --------------------------------------------------------------------------
    if (Optional(TokenType::TOK_UNIVERSAL_INT_LITERAL)) {
        diags.Debug("*** .. trivial INTEGER");
        m.Commit();
        return true;
    }

    if (Optional(TokenType::TOK_UNIVERSAL_REAL_LITERAL)) {
        diags.Debug("*** .. trivial REAL");
        m.Commit();
        return true;
    }


    if (Optional(TokenType::TOK_STRING_LITERAL)) {
        diags.Debug("*** .. trivial name (string lit)");
        m.Commit();
        return true;
    }


    if (tokens.Current() == TokenType::TOK_NEW) {
        diags.Debug("*** .. trivial NEW");
        if (ParseAllocator()) {
            m.Commit();
            return true;
        }

        m.Reset();
    }


    if (tokens.Current() == TokenType::TOK_CHARACTER_LITERAL) {
        diags.Debug("*** .. trivial name (char lit)");
        if (ParseNameExpr(id)) {
            m.Commit();
            return true;
        }

        m.Reset();
    }


    if (ParseOperatorSymbol()) {
        diags.Debug("*** .. near trivial operator symbol");
        m.Commit();
        return true;
    }


    //
    // -- Now, an Identifier can start several different alternatives.  Check here for each.
    //    ----------------------------------------------------------------------------------
    if (tokens.Current() == TokenType::TOK_IDENTIFIER) {
        diags.Debug("*** .. IDENTIFIER");
        IdentifierLexeme idLex = std::get<IdentifierLexeme>(tokens.Payload());
        const std::vector<Symbol *> *vec = scopes.Lookup(idLex.name);

        if (vec != nullptr) {
            TypeSymbol *type = nullptr;

            for (auto &sym : *vec) {
                if (sym->kind == Symbol::SymbolKind::Deleted) continue;
                if (sym->kind == Symbol::SymbolKind::Type || sym->kind == Symbol::SymbolKind::IncompleteType) {
                    if (tokens.Peek() == TokenType::TOK_APOSTROPHE) {
                        if (ParseQualifiedExpression()) {
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
                if (ParseNameExpr(id)) {
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
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return false;
    diags.Debug("*** .. Consumed: LEFT PAREN");


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

    diags.Debug("*** .. Falling back on an aggregate... " + std::string(tokens.tokenStr(tokens.Current())));
    if (ParseAggregate()) {
        m.Commit();
        return true;
    }


    diags.Debug("*** NOTHING MATCHED!!!");

    return false;
}


#if 0
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


#endif
