//=================================================================================================================
//  ast-printer.cc -- Implement the classes which will print the different AST structures
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
// -- Print a required child helper function
//    --------------------------------------
void ASTPrinter::PrintRequiredChild(std::string label, ASTNode *child) {
    // -- TODO: Remove the following if-statement and block after the entire AST has been properly built
    if (!child) {
        PrintDepth();
        std::cout << label << '\n';
        depth ++;
        PrintDepth();
        std::cout << "(null)\n";
        depth --;
        return;
    };

    assert(child);
    PrintDepth();
    std::cout << label << '\n';
    depth ++;
    child->Accept(*this);
    depth --;
}



//
// -- Print an optional AST Child helper function
//    -------------------------------------------
void ASTPrinter::PrintOptionalChild(std::string label, ASTNode *child) {
    PrintDepth();
    std::cout << label << '\n';
    if (child) {
        depth ++;
        child->Accept(*this);
        depth --;
    } else {
        depth ++;
        PrintDepth();
        std::cout << "(null)\n";
        depth --;
    }
}



//
// -- Print a field
//    -------------
void ASTPrinter::PrintField(std::string label, std::string value) {
    PrintDepth();
    std::cout << label << " --> " << value << '\n';
}



//
// -- Print an Identifier List
//    ------------------------
void ASTPrinter::PrintIdList(std::string label, IdList *child) {
    assert(child);

    PrintDepth();
    std::cout << label << '\n';

    depth ++;
    for (auto &id : *child) {
        PrintDepth();
        std::cout << "--> " << id.name << '\n';
    }
    depth --;
}



//
// -- Output the AST Node Preamble
//    ----------------------------
void ASTPrinter::Entry(std::string label)
{
    PrintDepth();
    std::cout << label << '\n';
    depth ++;
}



//
// == Individual class Printer methods
//    ================================



//
// -- AccessTypeSpec
//    --------------
void ASTPrinter::Visit(const AccessTypeSpec &n)
{
    Entry("AccessTypeSpec");
    PrintRequiredChild("name", n.name.get());
    PrintRequiredChild("type", n.type.get());
    Exit();
}



//
// -- AggregateExpr
//    -------------
void ASTPrinter::Visit(const AggregateExpr &n)
{
    Entry("AggregateExpr");
    if (n.list) PrintList("list", *n.list.get()); else PrintField("list", "(null)");
    Exit();
}



//
// -- ArrayTypeSpec
//    -------------
void ASTPrinter::Visit(const ArrayTypeSpec &n)
{
    Entry("ArrayTypeSpec");
    if (n.list) PrintList("list", *n.list.get()); else PrintField("list", "(null)");
    PrintField("unconstrained", (n.unconstrained?"true":"false"));
    PrintRequiredChild("indices", n.indices.get());
    PrintRequiredChild("subtype", n.component.get());
    Exit();
}



//
// -- AttributeName
//    -------------
void ASTPrinter::Visit(const AttributeName &n)
{
    Entry("AttributeName");
    PrintRequiredChild("prefix", n.prefix.get());
    PrintRequiredChild("attribute", n.attr.get());
    PrintOptionalChild("expr", n.expr.get());
    Exit();
}



//
// -- AttributeRange
//    --------------
void ASTPrinter::Visit(const AttributeRange &n)
{
    Entry("AttributeRange");
    PrintRequiredChild("attribute", n.rangeAttribute.get());
    Exit();
}



//
// -- BinaryExpr
//    ----------
void ASTPrinter::Visit(const BinaryExpr &n)
{
    Entry("BinaryExpr");

    switch (n.op) {
    case BinaryOper::And:           PrintField("op", "AND");                        break;
    case BinaryOper::AndThen:       PrintField("op", "AND_THEN");                   break;
    case BinaryOper::Concatenate:   PrintField("op", "& (concat)");                 break;
    case BinaryOper::Divide:        PrintField("op", "/ (divide)");                 break;
    case BinaryOper::Equal:         PrintField("op", "= (equal)");                  break;
    case BinaryOper::GreaterEqual:  PrintField("op", ">= (greater or equal)");      break;
    case BinaryOper::GreaterThan:   PrintField("op", "> (greater)");                break;
    case BinaryOper::In:            PrintField("op", "IN");                         break;
    case BinaryOper::LessEqual:     PrintField("op", "<= (less equal)");            break;
    case BinaryOper::LessThan:      PrintField("op", "< (less)");                   break;
    case BinaryOper::Minus:         PrintField("op", "- (minus)");                  break;
    case BinaryOper::Mod:           PrintField("op", "MOD");                        break;
    case BinaryOper::NotEqual:      PrintField("op", "/= (not equal)");             break;
    case BinaryOper::Or:            PrintField("op", "OR");                         break;
    case BinaryOper::OrElse:        PrintField("op", "OR_ELSE");                    break;
    case BinaryOper::Plus:          PrintField("op", "+ (plus)");                   break;
    case BinaryOper::Power:         PrintField("op", "** (power)");                 break;
    case BinaryOper::Rem:           PrintField("op", "REM");                        break;
    case BinaryOper::Times:         PrintField("op", "* (times)");                  break;
    case BinaryOper::Xor:           PrintField("op", "XOR");                        break;
    default:                        assert(false);
    }

    PrintRequiredChild("lhs", n.lhs.get());
    PrintRequiredChild("rhs", n.rhs.get());
    Exit();
}



//
// -- CharacterLiteralName
//    --------------------
void ASTPrinter::Visit(const CharacterLiteralName &n)
{
    Entry("CharacterLiteralName");
    PrintField("literal", n.lit.lexeme);
    Exit();
}



//
// -- ComponentAssociation
//    --------------------
void ASTPrinter::Visit(const ComponentAssociation &n)
{
    Entry("ComponentAssociation");
    if (n.choices) PrintList("choices", *n.choices.get()); else PrintField("choices", "(null)");
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- ComponentDeclaration
//    --------------------
void ASTPrinter::Visit(const ComponentDeclaration &n)
{
    Entry("ComponentDeclaration");
    PrintIdList(std::string("names"), n.names.get());
    PrintRequiredChild("type", n.typeSpec.get());
    PrintOptionalChild("initializer", n.initializer.get());
    Exit();
}



//
// -- ComponentList
//    -------------
void ASTPrinter::Visit(const ComponentList &n)
{
    Entry("ComponentList");
    if (n.components) PrintList("components", *n.components.get()); else PrintField("components", "(null)");
    PrintRequiredChild("variant part", n.variantPart.get());
    Exit();
}



//
// -- DerivedTypeSpec
//    ---------------
void ASTPrinter::Visit(const DerivedTypeSpec &n)
{
    Entry("DerivedTypeSpec");
    PrintRequiredChild("name", n.name.get());
    PrintRequiredChild("type", n.type.get());
    Exit();
}



//
// -- DiscriminantAssociation
//    -----------------------
void ASTPrinter::Visit(const DiscriminantAssociation &n)
{
    Entry("DiscriminantAssociation");
    if (n.names) PrintList("name", *n.names.get()); else PrintField("names", "(null)");
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- DiscriminantConstraint
//    -----------------------
void ASTPrinter::Visit(const DiscriminantConstraint &n)
{
    Entry("DiscriminantConstraint");
    if (n.list) PrintList("lsit", *n.list.get()); else PrintField("list", "(null)");
    Exit();
}



//
// -- DiscriminantSpecification
//    -------------------------
void ASTPrinter::Visit(const DiscriminantSpecification &n)
{
    Entry("DiscriminantSpecification");
    PrintIdList("ids", n.ids.get());
    PrintRequiredChild("type", n.type.get());
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- EnumerationTypeSpec
//    -------------------
void ASTPrinter::Visit(const EnumerationTypeSpec &n)
{
    Entry("EnumerationTypeSpec");
    PrintIdList("literals", n.literals.get());
    Exit();
}



//
// -- ExprChoice
//    ----------
void ASTPrinter::Visit(const ExprChoice &n)
{
    Entry("ExprChoice");
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- IdentifierList
//    --------------
void ASTPrinter::Visit(const IdentifierList &n)
{
    Entry("IdentifierList");
    PrintIdList("ids", n.ids.get());
    Exit();
}



//
// -- IndexConstraint
//    ---------------
void ASTPrinter::Visit(const IndexConstraint &n)
{
    Entry("IndexConstraint");
    PrintField("unconstrained", n.unconstrained?"true":"false");
    if (n.indices) PrintList("indices", *n.indices.get()); else PrintField("indices", "(null)");
    Exit();
}



//
// -- IndexedName
//    -----------
void ASTPrinter::Visit(const IndexedName &n)
{
    Entry("IndexedName");
    PrintRequiredChild("prefix", n.prefix.get());
    if (n.indices) PrintList("indices", *n.indices.get()); else PrintField("indices", "(null)");
    Exit();
}



//
// -- IntLiteralExpr
//    --------------
void ASTPrinter::Visit(const IntLiteralExpr &n)
{
    Entry("IntLiteralExpr");
    PrintField("value", n.lexeme);
    Exit();
}



//
// -- NameChoice
//    ----------
void ASTPrinter::Visit(const NameChoice &n)
{
    Entry("NameChoice");
    PrintRequiredChild("name", n.name.get());
    Exit();
}



//
// -- NameExpr
//    --------
void ASTPrinter::Visit(const NameExpr &n)
{
    Entry("NameExpr");
    PrintRequiredChild("name", n.name.get());
    Exit();
}



//
// -- NullLiteralExpr
//    ---------------
void ASTPrinter::Visit(const NullLiteralExpr &n)
{
    Entry("NullLiteralExpr");
    PrintField("NullLiteralExpr", "null");
    Exit();
}



//
// -- NumericTypeSpec
//    ---------------
void ASTPrinter::Visit(const NumericTypeSpec &n)
{
    Entry("NumericTypeSpec");

    switch (n.kind) {
    case NumericTypeSpec::Kind::Integer:
        PrintField("kind", "Integer");
        break;

    case NumericTypeSpec::Kind::FixedPoint:
        PrintField("kind", "Fixed Point");
        PrintRequiredChild("delta", n.size.get());
        break;

    case NumericTypeSpec::Kind::FloatingPoint:
        PrintField("kind", "Floating Point");
        PrintRequiredChild("digits", n.size.get());
        break;
    }

    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- ObjectDeclaration
//    -----------------
void ASTPrinter::Visit(const ObjectDeclaration &n)
{
    Entry("ObjectDeclaration");
    PrintIdList("names", n.names.get());
    PrintField("constant", (n.isConstant?"true":"false"));
    PrintRequiredChild("typeSpec", n.typeSpec.get());
    PrintRequiredChild("initializer", n.initializer.get());
    Exit();
}



//
// -- OthersChoice
//    ------------
void ASTPrinter::Visit(const OthersChoice &n)
{
    Entry("OthersChoice");
    PrintField("others", "others");
    Exit();
}



//
// -- QualExprAllocatorExpr
//    ---------------------
void ASTPrinter::Visit(const QualExprAllocatorExpr &n)
{
    Entry("QualExprAllocatorExpr");
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- QualifiedExpr
//    -------------
void ASTPrinter::Visit(const QualifiedExpr &n)
{
    Entry("QualifiedExpr");
    PrintRequiredChild("id", n.id.get());
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- Range
//    -----
void ASTPrinter::Visit(const Range &n)
{
    Entry("Range");
    PrintRequiredChild("lower", n.lowerBound.get());
    PrintRequiredChild("upper", n.upperBound.get());
    Exit();
}



//
// -- RangeChoice
//    -----------
void ASTPrinter::Visit(const RangeChoice &n)
{
    Entry("RangeChoice");
    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- RealConstraint
//    --------------
void ASTPrinter::Visit(const RealConstraint &n)
{
    Entry("RealConstraint");
    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- RangeExpr
//    ---------
void ASTPrinter::Visit(const RangeExpr &n)
{
    Entry("RangeExpr");
    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- RealLiteralExpr
//    ---------------
void ASTPrinter::Visit(const RealLiteralExpr &n)
{
    Entry("RealLiteralExpr");
    PrintField("value", n.lexeme);
    Exit();
}



//
// -- RecordSpecification
//    -------------------
void ASTPrinter::Visit(const RecordSpecification &n)
{
    Entry("RecordSpecification");
    PrintField("ID", n.id.name);
    PrintRequiredChild("components", n.components.get());
    Exit();
}



//
// -- SelectedName
//    ------------
void ASTPrinter::Visit(const SelectedName &n)
{
    Entry("SelectedName");
    PrintRequiredChild("prefix", n.prefix.get());
    PrintOptionalChild("selector", n.selector.get());
    PrintField("all", (n.all?"true":"false"));
    Exit();
}



//
// -- SimpleName
//    ----------
void ASTPrinter::Visit(const SimpleName &n)
{
    Entry("SimpleName");
    PrintField("id", n.id.name);
    Exit();
}



//
// -- SliceName
//    ---------
void ASTPrinter::Visit(const SliceName &n)
{
    Entry("SliceName");
    PrintRequiredChild("prefix", n.prefix.get());
    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- StringLiteralExpr
//    -----------------
void ASTPrinter::Visit(const StringLiteralExpr &n)
{
    Entry("StringLiteralExpr");
    PrintField("value", n.lexeme);
    Exit();
}



//
// -- SubtypeIndication
//    -----------------
void ASTPrinter::Visit(const SubtypeIndication &n)
{
    Entry("SubtypeIndication");
    PrintRequiredChild("type_mark", n.name.get());
    PrintOptionalChild("constraint", n.constraint.get());
    Exit();
}



//
// -- SubtypeIndicationAllocatorExpr
//    ------------------------------
void ASTPrinter::Visit(const SubtypeIndicationAllocatorExpr &n)
{
    Entry("SubtypeIndicationAllocatorExpr");
    PrintRequiredChild("subtype", n.sub.get());
    Exit();
}



//
// -- RangeConstraint
//    ---------------
void ASTPrinter::Visit(const RangeConstraint &n)
{
    Entry("RangeConstraint");
    PrintRequiredChild("range", n.range.get());
    Exit();
}



//
// -- SubtypeRange
//    ------------
void ASTPrinter::Visit(const SubtypeRange &n)
{
    Entry("SubtypeRange");
    PrintRequiredChild("attribute", n.subtype.get());
    Exit();
}



//
// -- TypeConversionExpr
//    ------------------
void ASTPrinter::Visit(const TypeConversionExpr &n)
{
    Entry("TypeConversionExpr");
    PrintRequiredChild("id", n.id.get());
    PrintRequiredChild("expr", n.expr.get());
    Exit();
}



//
// -- TypeDecl
//    --------
void ASTPrinter::Visit(const TypeDecl &n)
{
    Entry("TypeDecl");
    PrintField("name", n.name.name);
    if (n.discriminantPart) PrintList("discriminantPart", *n.discriminantPart.get()); else PrintField("discriminantPart", "(null)");
    PrintOptionalChild("definition", n.definition.get());
    Exit();
}



//
// -- UnaryExpr
//    ---------
void ASTPrinter::Visit(const UnaryExpr &n)
{
    Entry("UnaryExpr");

    switch (n.op) {
    case UnaryOper::Plus:           PrintField("op", "+ (plus)");                   break;
    case UnaryOper::Minus:          PrintField("op", "- (minus)");                  break;
    case UnaryOper::Abs:            PrintField("op", "ABS");                        break;
    case UnaryOper::Not:            PrintField("op", "NOT");                        break;
    default:                        assert(false);
    }

    PrintRequiredChild("operand", n.expr.get());
    Exit();
}



//
// -- UnboundedRange
//    --------------
void ASTPrinter::Visit(const UnboundedRange &n)
{
    Entry("UnboundedRange");
    PrintRequiredChild("type", n.type.get());
    Exit();
}



//
// -- Variant
//    -------
void ASTPrinter::Visit(const Variant &n)
{
    Entry("Variant");
    if (n.choices) PrintList("choices", *n.choices.get()); else PrintField("choices", "(null)");
    PrintRequiredChild("components", n.components.get());
    Exit();
}




//
// -- VariantPart
//    -----------
void ASTPrinter::Visit(const VariantPart &n)
{
    Entry("VariantPart");
    PrintRequiredChild("name", n.name.get());
    if (n.variants) PrintList("variants", *n.variants.get()); else PrintField("variants", "(null)");
    Exit();
}



