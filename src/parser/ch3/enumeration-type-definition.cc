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
    SymbolTable::Checkpoint cp;
    SourceLoc_t astLoc = TokenStream::Get().SourceLocation();
    SourceLoc_t loc = astLoc;
    bool updateIncomplete = false;
    IdListPtr ids = std::make_unique<IdList>();
    Symbol *sym = nullptr;
    Id id;



    //
    // -- Start by adding a new Enum Type with the name
    //    ---------------------------------------------
    sym = symTab.LocalLookup(name.name);
    if (sym) {
        if (sym->kind == SymbolTable::SymbolKind::IncompleteType) {
            updateIncomplete = true;
        } else {
            diags.Error(name.loc, DiagID::DuplicateName, { name.name } );
            diags.Note(sym->loc, DiagID::DuplicateName2, { } );
        }
    } else {
        sym = symTab.Declare(name.loc, name.name, SymbolTable::SymbolKind::Type);
    }


    //
    // -- The enumeration is enclosed in parens
    //    -------------------------------------
    if (!Require(TokenType::TOK_LEFT_PARENTHESIS)) return nullptr;
    if ((id = ParseEnumerationLiteralSpecification(sym)).name == "") return nullptr;
    ids->push_back(id);


    //
    // -- there may be any number of enumerations
    //    ---------------------------------------
    loc = TokenStream::Get().SourceLocation();
    while (Optional(TokenType::TOK_COMMA)) {
        if ((id = ParseEnumerationLiteralSpecification(sym)).name == "") {
            diags.Error(loc, DiagID::ExtraComma, { "enumeration type definition" } );
            // -- continue on in hopes that this does not create a cascade of errors

            break;
        }

        ids->push_back(id);
        loc = TokenStream::Get().SourceLocation();
    }


    //
    // -- end with a closing paren
    //    ------------------------
    loc = TokenStream::Get().SourceLocation();
    if (!Require(TokenType::TOK_RIGHT_PARENTHESIS)) {
        diags.Error(loc, DiagID::MissingRightParen, { "enumeration literal" } );
        // -- continue on in hopes that this does not create a cascade of errors
    }


    //
    // -- Consider this parse to be good
    //    ------------------------------
    if (updateIncomplete) sym->kind = SymbolTable::SymbolKind::Type;

    cp.Commit();
    m.Commit();

    return std::make_unique<EnumerationTypeSpec>(astLoc, std::move(ids));
}




