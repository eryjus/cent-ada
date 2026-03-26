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

        // -- when
        SymbolTable::Scope *sc = table.Push(n);

        // -- then
        EXPECT_TRUE(sc);
        EXPECT_FALSE(LocalTest(table, "integer"));
        ASSERT_TRUE(GlobalTest(table, "integer"));
        EXPECT_EQ(table.current->name, n);
        ASSERT_TRUE(table.current->parent);
        EXPECT_EQ(table.current->parent->name, "global");
        ASSERT_TRUE(table.current->parent->parent);
        EXPECT_EQ(table.current->parent->parent->name, "standard");
        ASSERT_FALSE(table.current->parent->parent->parent);

        // -- also when
        table.Pop();

        // -- then
        EXPECT_FALSE(LocalTest(table, "integer"));
        ASSERT_TRUE(GlobalTest(table, "integer"));
        EXPECT_EQ(table.current->name, "global");
        ASSERT_TRUE(table.current->parent);
        EXPECT_EQ(table.current->parent->name, "standard");
        ASSERT_FALSE(table.current->parent->parent);
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

