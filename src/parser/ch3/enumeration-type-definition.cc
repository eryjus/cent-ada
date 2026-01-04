//=================================================================================================================
//  parser/ch3/enumeration-type-definition.cc -- Parse an enumeration type
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  enumeration_type_definition ::= ( enumeration_literal_specification { , enumeration_literal_specification } )
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-26  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- Parse an Enumeration Type Definition
//    ------------------------------------
TypeSpecPtr Parser::ParseEnumerationTypeDefinition(Id &name)
{
    Production p(*this, "enumeration_type_definition");
    MarkStream m(tokens, diags);
    SourceLoc_t loc, astLoc;
    MarkScope s(scopes);
    std::vector<Symbol *> *vec;
    bool updateIncomplete = false;
    Id id;
    IdListPtr ids = std::make_unique<IdList>();



    //
    // -- Start by adding a new Enum Type with the name
    //    ---------------------------------------------
    if (scopes.IsLocalDefined(std::string_view(name.name))) {
        // -- name is used in this scope is it a singleton and incomplete class?
        vec = scopes.CurrentScope()->LocalLookup(std::string_view(name.name));

        if (vec->size() == 1 && vec->at(0)->kind == Symbol::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(name.loc, DiagID::DuplicateName, { name.name } );
        }
    }


    EnumTypeSymbol *type = scopes.Declare(std::make_unique<EnumTypeSymbol>(name.name, name.loc, scopes.CurrentScope()));


    //
    // -- The enumeration is enclosed in parens
    //    -------------------------------------
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;
    if ((id = ParseEnumerationLiteralSpecification(type)).name == "") return nullptr;
    ids->push_back(id);


    //
    // -- there may be any number of enumerations
    //    ---------------------------------------
    loc = tokens.SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        if ((id = ParseEnumerationLiteralSpecification(type)).name == "") {
            diags.Error(loc, DiagID::ExtraComma, { "enumeration type definition" } );
            // -- continue on in hopes that this does not create a cascade of errors

            break;
        }

        ids->push_back(id);
        loc = tokens.SourceLocation();
    }


    //
    // -- end with a closing paren
    //    ------------------------
    loc = tokens.SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "enumeration literal" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    EnumerationTypeSpecPtr rv = std::make_unique<EnumerationTypeSpec>(astLoc, std::move(ids));
    ASTPrinter prt;
    rv->Accept(prt);

    if (updateIncomplete) vec->at(0)->kind = Symbol::SymbolKind::Deleted;
    s.Commit();
    m.Commit();
    return std::move(rv);
}




