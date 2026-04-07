//===================================================================================================================
// tst-symbols1.cc -- This google test executes tests against the symbols
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
// -- Test the foundation of the Symbol Table functionality
//    -----------------------------------------------------



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



