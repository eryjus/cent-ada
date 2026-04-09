
.SILENT:

.phony: all
all:
	tup



.PHONY: test-invar
test-invar: all
	echo "== Running AST Invariant tests =="
	./scripts/run-invar-tests.sh

.PHONY: test-ast
test-ast: all
	echo "== Running AST tests =="
	./scripts/run-ast-tests.sh


.PHONY: test-stmts
test-stmts: all
	echo "== Running Statement tests =="
	./scripts/run-stmt-tests.sh


## The following is built to always pass each test group!
## DO NOT USE IN CI as undesirable results will occur
.PHONY: test
test: all
	gtest/bin/test || true
	echo "== Running ALL tests =="
	echo "Invar:"
	./scripts/run-invar-tests.sh | grep FAILED --color=always || true
	echo "AST:"
	./scripts/run-ast-tests.sh | grep -E 'FAILED|MISSING' --color=always || true
	echo "Stmts:"
	./scripts/run-stmt-tests.sh | grep -E 'FAILED|MISSING' --color=always || true


