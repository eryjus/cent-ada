//===================================================================================================================
// symbols.cc -- This google test executes tests against the symbol table, scope, and manager
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Mar-24  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "ada.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>



//
// == Test the foundation of the Symbol Table functionality
//    =====================================================


//
// -- Test Suite for testing the symbol tables
//    ----------------------------------------
class TestSyms : public testing::Test {
protected:
    TestSyms(void) {}


    SymbolTable::Symbol *GlobalTest(SymbolTable &table, std::string n) {
        return table.GlobalLookup(n);
    }

    SymbolTable::Symbol *LocalTest(SymbolTable &table, std::string n) {
        return table.LocalLookup(n);
    }


    //
    // -- Test a standard symbol in the symbol table
    //    ------------------------------------------
    void TestStandardSymbol(std::string n, SymbolTable::SymbolKind k) {
        // -- given
        SymbolTable &table = SymbolTable::Get();

        // -- when
        SymbolTable::Symbol *sym = GlobalTest(table, n);

        // -- then
        EXPECT_FALSE(LocalTest(table, n));
        ASSERT_TRUE(sym);
        EXPECT_EQ(sym->kind, k);
    }



    //
    // -- Test PUSH/POP of scopes
    //    -----------------------
    void TestPushPop(std::string n) {
        // -- given
        SymbolTable &table = SymbolTable::Get();
        std::string scope = table.CurrentScope();

        // -- when
        SymbolTable::Scope *sc = table.Push(n);

        // -- then
        EXPECT_TRUE(sc);
        EXPECT_FALSE(LocalTest(table, "integer"));
        ASSERT_TRUE(GlobalTest(table, "integer"));
        EXPECT_EQ(table.current->name, n);
        ASSERT_TRUE(table.current->parent);
        EXPECT_EQ(table.current->parent->name, "GLOBAL");
        ASSERT_TRUE(table.current->parent->parent);
        EXPECT_EQ(table.current->parent->parent->name, "STANDARD");
        ASSERT_FALSE(table.current->parent->parent->parent);
        EXPECT_EQ(n, table.CurrentScope());

        // -- also when
        table.Pop();

        // -- then
        EXPECT_FALSE(LocalTest(table, "integer"));
        ASSERT_TRUE(GlobalTest(table, "integer"));
        EXPECT_EQ(table.current->name, "GLOBAL");
        ASSERT_TRUE(table.current->parent);
        EXPECT_EQ(table.current->parent->name, "STANDARD");
        ASSERT_FALSE(table.current->parent->parent);
        EXPECT_EQ(scope, table.CurrentScope());
    }


    //
    // -- Test Rollback of symbols
    //    ------------------------
    void TestRollbackSyms(std::string n) {
        // -- given
        SymbolTable &table = SymbolTable::Get();
        std::string scope = table.CurrentScope();

        {
            // -- when
            SymbolTable::Checkpoint cp;
            SymbolTable::Declare( { }, n, SymbolTable::SymbolKind::Object);

            // -- then
            ASSERT_TRUE(LocalTest(table, n));

            // -- and when not a committed symbol
        }

        // -- then
        EXPECT_EQ(scope, table.CurrentScope());
        EXPECT_FALSE(LocalTest(table, n));
    }



    //
    // -- Test Rollback of scopes
    //    -----------------------
    void TestRollbackScope(std::string n) {
        // -- given
        SymbolTable &table = SymbolTable::Get();
        std::string scope = table.CurrentScope();

        {
            // -- when
            SymbolTable::Checkpoint cp;
            SymbolTable::Push("new_scope");
            SymbolTable::Declare( { }, n, SymbolTable::SymbolKind::Object);

            // -- then
            ASSERT_TRUE(LocalTest(table, n));
            EXPECT_EQ("new_scope", table.CurrentScope());

            // -- and when not a committed symbol
        }

        // -- then
        EXPECT_FALSE(LocalTest(table, n));
        EXPECT_EQ(scope, table.CurrentScope());
    }


    //
    // -- Test Commit of symbols
    //    ----------------------
    void TestCommitSyms(std::string n) {
        // -- given
        SymbolTable &table = SymbolTable::Get();
        std::string scope = table.CurrentScope();

        {
            // -- when
            SymbolTable::Checkpoint cp;
            SymbolTable::Declare( { }, n, SymbolTable::SymbolKind::Object);

            // -- then
            ASSERT_TRUE(LocalTest(table, n));

            // -- and when
            cp.Commit();
        }

        // -- then
        EXPECT_EQ(scope, table.CurrentScope());
        EXPECT_TRUE(LocalTest(table, n));
    }



    //
    // -- Test Commit of scopes
    //    ---------------------
    void TestCommitScope(std::string n) {
        // -- given
        SymbolTable &table = SymbolTable::Get();
        std::string scope = table.CurrentScope();

        {
            // -- when
            SymbolTable::Checkpoint cp;
            SymbolTable::Push("new_scope");
            SymbolTable::Declare( { }, n, SymbolTable::SymbolKind::Object);

            // -- then
            ASSERT_TRUE(LocalTest(table, n));
            EXPECT_EQ("new_scope", table.CurrentScope());

            // -- and when
            cp.Commit();
        }

        // -- then
        EXPECT_TRUE(LocalTest(table, n));
        EXPECT_EQ(scope, table.CurrentScope());
    }
};



TEST_F(TestSyms, integer) { TestStandardSymbol("integer", SymbolTable::SymbolKind::Type); }
TEST_F(TestSyms, array) { TestStandardSymbol("array", SymbolTable::SymbolKind::Type); }
TEST_F(TestSyms, real) { TestStandardSymbol("real", SymbolTable::SymbolKind::Type); }
TEST_F(TestSyms, character) { TestStandardSymbol("character", SymbolTable::SymbolKind::Type); }
TEST_F(TestSyms, string) { TestStandardSymbol("string", SymbolTable::SymbolKind::Type); }
TEST_F(TestSyms, boolean) { TestStandardSymbol("boolean", SymbolTable::SymbolKind::Type); }

TEST_F(TestSyms, t_false) { TestStandardSymbol("false", SymbolTable::SymbolKind::EnumLiteral); }
TEST_F(TestSyms, t_true) { TestStandardSymbol("true", SymbolTable::SymbolKind::EnumLiteral); }


TEST_F(TestSyms, address) { TestStandardSymbol("address", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, aft) { TestStandardSymbol("aft", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, base) { TestStandardSymbol("base", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, callable) { TestStandardSymbol("callable", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, constrained) { TestStandardSymbol("constrained", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, count) { TestStandardSymbol("count", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, delta) { TestStandardSymbol("delta", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, digits) { TestStandardSymbol("digits", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, emax) { TestStandardSymbol("emax", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, epsilon) { TestStandardSymbol("epsilon", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, first) { TestStandardSymbol("first", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, first_bit) { TestStandardSymbol("first_bit", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, fore) { TestStandardSymbol("fore", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, image) { TestStandardSymbol("image", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, large) { TestStandardSymbol("large", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, last) { TestStandardSymbol("last", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, last_bit) { TestStandardSymbol("last_bit", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, length) { TestStandardSymbol("length", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_emax) { TestStandardSymbol("machine_emax", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_emin) { TestStandardSymbol("machine_emin", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_mastissa) { TestStandardSymbol("machine_mastissa", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_overflows) { TestStandardSymbol("machine_overflows", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_radix) { TestStandardSymbol("machine_radix", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, machine_rounds) { TestStandardSymbol("machine_rounds", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, mantissa) { TestStandardSymbol("mantissa", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, pos) { TestStandardSymbol("pos", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, position) { TestStandardSymbol("position", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, pred) { TestStandardSymbol("pred", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, range) { TestStandardSymbol("range", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, safe_emax) { TestStandardSymbol("safe_emax", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, safe_large) { TestStandardSymbol("safe_large", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, safe_small) { TestStandardSymbol("safe_small", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, size) { TestStandardSymbol("size", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, small) { TestStandardSymbol("small", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, storage_size) { TestStandardSymbol("storage_size", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, succ) { TestStandardSymbol("succ", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, terminated) { TestStandardSymbol("terminated", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, val) { TestStandardSymbol("val", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, value) { TestStandardSymbol("value", SymbolTable::SymbolKind::Attribute); }
TEST_F(TestSyms, width) { TestStandardSymbol("width", SymbolTable::SymbolKind::Attribute); }

TEST_F(TestSyms, pushpop) { TestPushPop("test"); }

TEST_F(TestSyms, rollback_symbol1) { TestRollbackSyms("test"); }
TEST_F(TestSyms, rollback_symbol2) { TestRollbackSyms("integer"); }
TEST_F(TestSyms, rollback_scope1) { TestRollbackScope("test"); }
TEST_F(TestSyms, rollback_scope2) { TestRollbackScope("integer"); }


//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================



//
// == Test the output of printing the symbol table
//    ============================================



//
// -- This class will test the formatted output for each kind of symbol
//    -----------------------------------------------------------------
class TestOutput : public testing::Test {
protected:
    TestOutput(void) {}


    void TestSymbol(std::string expected, SourceLoc_t l, std::string n, SymbolTable::SymbolKind k, std::string t = "", int lvl = 0) {
        // -- given
        SymbolTable::Reset();
        std::ostringstream actual;

        // -- when
        while (lvl) { SymbolTable::Push("test"); --lvl; }
        Symbol *sym = SymbolTable::Declare(l, n, k, t);
        SymbolTable::Print(actual, false);

        // -- then
        EXPECT_EQ(expected, actual.str());
    }
};



//
// -- Execute the actual tests
//    ------------------------
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





//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================
//===================================================================================================================



//
// == Test the sequence the symbol table
//    ==================================



//
// -- This class will test the sequence of the symbol in the symbol table
//    -------------------------------------------------------------------
class TestSequence : public testing::Test {
protected:
    TestSequence(void) {}


    void TestSeq(const std::string code, const SymSeq &expected) {
        SymSeq actual = SymbolTable::GetAllSymbols();
        ASSERT_EQ(expected, actual);
    }
};



//
// -- This starts the actual tests
//    ----------------------------






