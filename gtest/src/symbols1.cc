//===================================================================================================================
// symbols1.cc -- This defines the tests against the symbols
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "symbols1.hh"



//
// == Test the foundation of the Symbol Table functionality
//    =====================================================



//
// -- Test a standard symbol in the symbol table
//    ------------------------------------------
void TestSyms::TestStandardSymbol(std::string n, SymbolTable::SymbolKind k)
{
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
void TestSyms::TestPushPop(std::string n)
{
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
void TestSyms::TestRollbackSyms(std::string n)
{
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
void TestSyms::TestRollbackScope(std::string n)
{
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
void TestSyms::TestCommitSyms(std::string n)
{
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
void TestSyms::TestCommitScope(std::string n)
{
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

