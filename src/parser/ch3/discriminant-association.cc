//=================================================================================================================
//  parser/ch3/discriminant-association.cc -- Parse a discriminant association
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  discriminant_association ::= [discriminant_simple_name {| discriminant_simple_name} => ] expression
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
// -- Parse a Discriminant Association
//    --------------------------------
DiscriminantAssociationPtr Parser::ParseDiscriminantAssociation(void)
{
    Production p(*this, "disriminant_association");
    MarkStream m(tokens, diags);
    std::vector<Symbol *> *vec = nullptr;
    Id id;
    SourceLoc_t loc;
    SourceLoc_t astLoc = tokens.SourceLocation();
    NameListPtr names = std::make_unique<NameList>();
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;


    //
    // -- Start by checking if there is a discriminant simple name
    //    --------------------------------------------------------
    loc = tokens.SourceLocation();
    if ((name = std::move(ParseDiscriminantSimpleName())) != nullptr) {
        names->push_back(std::move(name));
        //
        // -- This will only work if the next token is a TOK_VERTICAL_BAR or TOK_ARROW
        //    Otherwise it will be an expression as a simple name
        //    ------------------------------------------------------------------------
        if (tokens.Current() != TokenType::TOK_VERTICAL_BAR && tokens.Current() != TokenType::TOK_ARROW) {
            // -- not the correct condition, backtrack and parse an expression
            m.Reset();
            goto expr;
        }


        //
        // -- Check for optional more
        //    -----------------------
        loc = tokens.SourceLocation();
        while (Optional(TokenType::TOK_VERTICAL_BAR)) {
            if ((name = std::move(ParseDiscriminantSimpleName())) != nullptr) {
                names->push_back(std::move(name));
            } else {
                diags.Error(loc, DiagID::ExtraVertialBar, { "discriminant simple name" } );
                break;
            }

            loc = tokens.SourceLocation();
        }


        if (!Require(TokenType::TOK_ARROW)) return nullptr;
    }

expr:
    loc = tokens.SourceLocation();
    if ((expr = std::move(ParseExpression())) == nullptr) {
        diags.Error(loc, DiagID::MissingExpression, { "discriminant association" } );
    }


    DiscriminantAssociationPtr rv = std::make_unique<DiscriminantAssociation>(astLoc, std::move(names), std::move(expr));

    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return std::move(rv);
}



