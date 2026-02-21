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
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    NameListPtr names = std::make_unique<NameList>();
    NamePtr name = nullptr;
    ExprPtr expr = nullptr;
    Id id;


    //
    // -- Start by checking if there is a discriminant simple name
    //    --------------------------------------------------------
    loc = TokenStream::Get().SourceLocation();
    name = ParseDiscriminantSimpleName();
    if (name) {
        //
        // -- This will only work if the next token is a TOK_VERTICAL_BAR or TOK_ARROW
        //    Otherwise it will be an expression as a simple name
        //    ------------------------------------------------------------------------
        if (TokenStream::Get().Current() != TokenType::TOK_VERTICAL_BAR && TokenStream::Get().Current() != TokenType::TOK_ARROW) {
            // -- not the correct condition, backtrack and parse an expression
            m.Reset();
            goto expr;
        } else {
            names->push_back(std::move(name));
        }


        //
        // -- Check for optional more
        //    -----------------------
        loc = TokenStream::Get().SourceLocation();
        while (Optional(TokenType::TOK_VERTICAL_BAR)) {
            name = ParseDiscriminantSimpleName();
            if (name) {
                names->push_back(std::move(name));
            } else {
                diags.Error(loc, DiagID::ExtraVertialBar, { "discriminant simple name" } );
                break;
            }

            loc = TokenStream::Get().SourceLocation();
        }


        if (!Require(TokenType::TOK_ARROW)) {
            p.At("Rejected");
            return nullptr;
        }
    }

expr:
    loc = TokenStream::Get().SourceLocation();
    expr = ParseExpression();
    if (!expr) {
        diags.Error(loc, DiagID::MissingExpression, { "discriminant association" } );
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    m.Commit();
    return std::make_unique<DiscriminantAssociation>(astLoc, std::move(names), std::move(expr));
}



