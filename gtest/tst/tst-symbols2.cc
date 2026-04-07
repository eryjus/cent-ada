//===================================================================================================================
// tst-symbols2.cc -- This google test executes tests against the symbol table pretty output
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "symbols2.hh"




//
// -- Test the output of printing the symbol table
//    --------------------------------------------

TEST_F(TestOutput, TestObject) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "Object Symbol: pi\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "pi", SymbolTable::SymbolKind::Object);
}


TEST_F(TestOutput, TestObject1) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "-------------------\n\n";
    expected << "Scope Name: test\n";
    expected << "Scope ID  : 2\n";
    expected << "-------------------\n";
    expected << "Object Symbol: pi\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "pi", SymbolTable::SymbolKind::Object, "", 1);
}


TEST_F(TestOutput, TestType) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "Type Symbol: color\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "color", SymbolTable::SymbolKind::Type);
}


TEST_F(TestOutput, TestIncompleteType) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "IncompleteType Symbol: person\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "person", SymbolTable::SymbolKind::IncompleteType);
}



TEST_F(TestOutput, TestLabel) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "Label Symbol: here\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "here", SymbolTable::SymbolKind::Label);
}



TEST_F(TestOutput, TestUndefinedLabel) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "UndefinedLabel Symbol: here\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "here", SymbolTable::SymbolKind::UndefinedLabel);
}



TEST_F(TestOutput, TestLoopName) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "LoopName Symbol: here\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "here", SymbolTable::SymbolKind::LoopName);
}



TEST_F(TestOutput, TestBlockName) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "BlockName Symbol: here\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "here", SymbolTable::SymbolKind::BlockName);
}


TEST_F(TestOutput, TestEnumLiteral) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "EnumLiteral Symbol: red\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "red", SymbolTable::SymbolKind::EnumLiteral);
}



TEST_F(TestOutput, TestComponent) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "Component Symbol: wife\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "wife", SymbolTable::SymbolKind::Component);
}



TEST_F(TestOutput, TestDiscriminant) {
    std::ostringstream expected;
    expected << "Scope Name: GLOBAL\n";
    expected << "Scope ID  : 1\n";
    expected << "-------------------\n";
    expected << "Discriminant Symbol: device\n";
    expected << "-------------------\n\n";

    TestSymbol(expected.str(), { }, "device", SymbolTable::SymbolKind::Discriminant);
}


