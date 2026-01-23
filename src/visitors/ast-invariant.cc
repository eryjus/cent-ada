//=================================================================================================================
//  ast-invariant.cc -- Implement the classes which will check the different AST structures
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2026-Jan-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"


//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const SubtypeIndication &n)
{
    assert(n.name.get() != nullptr);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const NumberDeclaration &n)
{
    assert(n.names); assert(n.initializer);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const ObjectDeclaration &n)
{
    assert(n.names); assert(n.typeSpec);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const TypeDecl &n)
{
    assert(n.definition);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const EnumerationTypeSpec &n)
{
    assert(n.literals);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const RangeConstraint &n)
{
    assert(n.range);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const NumericTypeSpec &n)
{
    assert(n.range);
    if (n.kind != NumericTypeSpec::Kind::Integer) {
        assert(n.size);
    }
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const Range &n)
{
    assert(n.lowerBound); assert(n.upperBound);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const SubtypeRange &n)
{
    assert(n.subtype);
}



//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const IndexConstraint &n)
{
    assert(n.indices);
}




//
// -- Check invariants for the AST class type
//    ---------------------------------------
void ASTInvariant::Visit(const AttributeRange &n)
{
    assert(n.rangeAttribute);
}






