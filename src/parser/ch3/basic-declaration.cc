//=================================================================================================================
//  parser/ch3/basic-declaration.cc -- All the permutations needed to parse a basic declaration
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
//  Right from the start, this production causes issues.  The productions:
//
//      basic_declaration ::= object_declaration
//      basic_declaration ::= number_declaration
//      basic_declaration ::= exception_declaration
//      basic_declaration ::= deferred_constant_declaration
//
//  ... both start with the same list of tokens;
//
//      identifier_list :
//
//  ... and `object_`, `number_` and `deferred_constant_declaration`s have at least
//  and optional `TOK_CONSTANT` token after this.
//
//  To further complicate matters, `renaming_declaration` also begin with:
//
//      * identifier :
//      * TOK_PACKAGE identifier
//      * subprogram_specification
//
//  ... all of which will generate conflicts.
//
//  Finally, a `generic_instantiation` can begin with:
//      * TOK_PACKAGE (like `package_declaration`)
//      * TOK_FUNCTION (like `subprogram_declaration`)
//      * TOK_PROCEDURE (also like `subprogram_declaration`)
//
//  However, with all this said, we will not be left-factoring this production.
//
//  Since this production does not directly consume tokens, there is not need for `MarkStream`.
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
// -- For Chapter 3, a `basic_declaration` is the top-level production
//    ----------------------------------------------------------------
DeclPtr Parser::ParseBasicDeclaration(void)
{
    // -- This top-level production must Mark its location so it can output diags
    Production p(*this, "basic_declaration");
    SourceLoc_t loc = tokens.SourceLocation();
    DeclPtr rv = nullptr;

    if ((rv = std::move(ParseObjectDeclaration())) != nullptr)            { p.At("Object"); return std::move(rv); }
    if ((rv = std::move(ParseNumberDeclaration())) != nullptr)            { return std::move(rv); }
    if ((rv = std::move(ParseTypeDeclaration())) != nullptr)              { return std::move(rv); }
    if ((rv = std::move(ParseSubtypeDeclaration())) != nullptr)           { return std::move(rv); }
    if (!ParseSubprogramDeclaration())        { return nullptr; }
    if (!ParsePackageDeclaration())           { return nullptr; }
    if (!ParseTaskDeclaration())              { return nullptr; }
    if (!ParseGenericDeclaration())           { return nullptr; }
    if (!ParseExceptionDeclaration())         { return nullptr; }
    if (!ParseGenericInstantiation())         { return nullptr; }
    if (!ParseRenamingDeclaration())          { return nullptr; }
    if (!ParseDeferredConstantDeclaration())  { return nullptr; }

    if (opts.requireBasicDeclaration) {
        diags.Error(loc, DiagID::MissingBasicDeclaration);
        tokens.Recovery();
    }

    return nullptr;
}






