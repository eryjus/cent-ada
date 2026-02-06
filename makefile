
.SILENT:

.phony: all
all:
	tup



.phony: test-scanner
test-scanner: all
	for file in tst/scanner/*.ada; do \
		bin/ada-cc scan $$file ;\
	done


.PHONY: test-types
test-types: all
	echo "== Running Declaration tests =="
	./scripts/run-type-tests.sh


.PHONY: test-exprs
test-exprs: all
	echo "== Running Expression tests =="
	./scripts/run-expr-tests.sh


.PHONY: test-invar
test-invar: all
	echo "== Running AST Invariant tests =="
	./scripts/run-invar-tests.sh


## The following is built to always pass each test group!
## DO NOT USE IN CI as undesirable results will occur
.PHONY: test
test: all
	echo "== Running ALL tests =="
	echo "Types:"
	./scripts/run-type-tests.sh | grep FAILED --color=always || true
	echo "Exprs:"
	./scripts/run-expr-tests.sh | grep FAILED --color=always || true
	echo "Invar:"
	./scripts/run-invar-tests.sh | grep FAILED --color=always || true
	echo "AST:"
	./scripts/run-ast-tests.sh | grep -E 'FAILED|MISSING' --color=always || true


