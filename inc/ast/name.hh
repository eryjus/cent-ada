//=================================================================================================================
//  ast/name.hh -- This header is used for defining the classes which are derived from Name
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



#pragma once



//
// -- The common Name node
//    --------------------
class Name : public ASTNode {
    Name(void) = delete;
    Name(const Name &) = delete;
    Name &operator=(const Name &) = delete;

public:
    Name(SourceLoc_t l) : ASTNode(l) {}


public:
    virtual std::string_view GetName(void) = 0;
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is the AST node for a list of identifiers
//    ----------------------------------------------
class IdentifierList : public Name {
    IdentifierList(void) = delete;
    IdentifierList(const IdentifierList &) = delete;
    IdentifierList &operator=(const IdentifierList &) = delete;

public:
    IdListPtr ids;

public:
    IdentifierList(SourceLoc_t l, IdListPtr list) : Name(loc), ids(std::move(list)) {}


public:
    virtual std::string_view GetName(void) override { return ""; }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a Simple name
//    ---------------------
class SimpleName : public Name {
    SimpleName(void) = delete;
    SimpleName(const SimpleName &) = delete;
    SimpleName &operator=(const SimpleName &) = delete;


public:
    Id id;


public:
    SimpleName(SourceLoc_t loc, Id id) : Name(loc), id(id) {}


public:
    virtual std::string_view GetName(void) override { return id.name; }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a Character Literal name
//    --------------------------------
class CharacterLiteralName : public Name {
    CharacterLiteralName(void) = delete;
    CharacterLiteralName(const CharacterLiteralName &) = delete;
    CharacterLiteralName &operator=(const CharacterLiteralName &) = delete;


public:
    CharLiteral lit;


public:
    CharacterLiteralName(SourceLoc_t loc, CharLiteral lit) : Name(loc), lit(lit) {}


public:
    virtual std::string_view GetName(void) override { return lit.lexeme; }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is an Indexed Name
//    -----------------------
class IndexedName : public Name {
    IndexedName(void) = delete;
    IndexedName(const IndexedName &) = delete;
    IndexedName &operator=(const IndexedName &) = delete;


public:
    NamePtr prefix;
    ExprListPtr indices;


public:
    IndexedName(SourceLoc_t loc, NamePtr prefix, ExprListPtr indices)
            : Name(loc), prefix(std::move(prefix)), indices(std::move(indices)) {}


public:
    virtual std::string_view GetName(void) override { return prefix->GetName(); }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is an Slice Name
//    ---------------------
class SliceName : public Name {
    SliceName(void) = delete;
    SliceName(const SliceName &) = delete;
    SliceName &operator=(const SliceName &) = delete;


public:
    NamePtr prefix;
    DiscreteRangePtr range;


public:
    SliceName(SourceLoc_t loc, NamePtr prefix, DiscreteRangePtr range)
            : Name(loc), prefix(std::move(prefix)), range(std::move(range)) {}


public:
    virtual std::string_view GetName(void) override { return prefix->GetName(); }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is a Selected Name
//    -----------------------
class SelectedName : public Name {
    SelectedName(void) = delete;
    SelectedName(const SelectedName &) = delete;
    SelectedName &operator=(const SelectedName &) = delete;


public:
    NamePtr prefix;
    NamePtr selector;                   // -- may be nullptr
    bool all;                           // -- true when selector is nullptr


public:
    SelectedName(SourceLoc_t loc, NamePtr prefix, NamePtr sel)
            : Name(loc), prefix(std::move(prefix)), selector(std::move(sel)), all(selector == nullptr) {}


public:
    virtual std::string_view GetName(void) override { return prefix->GetName(); }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};



//
// -- This is an Attibute Name
//    ------------------------
class AttributeName : public Name {
    AttributeName(void) = delete;
    AttributeName(const AttributeName &) = delete;
    AttributeName &operator=(const AttributeName &) = delete;


public:
    NamePtr prefix;
    NamePtr attr;
    ExprPtr expr;                   // -- may be nullptr


public:
    AttributeName(SourceLoc_t loc, NamePtr p, NamePtr a, ExprPtr e)
            : Name(loc), prefix(std::move(prefix)), attr(std::move(a)), expr(std::move(e)) {}


public:
    virtual std::string_view GetName(void) override { return prefix->GetName(); }
    virtual void Accept(ASTVisitor &v) { v.Visit(*this); }
};





