
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
	echo "== Running declaration tests =="
	./scripts/run-type-tests.sh


.PHONY: test-exprs
test-exprs: all
	echo "== Running expression tests =="
	./scripts/run-expr-tests.sh


## The following is built to always pass each test group!
## DO NOT USE IN CI as undesirable results will occur
.PHONY: test
test: all
	echo "== Running ALL tests =="
	echo "types:"
	./scripts/run-type-tests.sh | grep FAILED || true
	echo "exprs:"
	./scripts/run-expr-tests.sh | grep FAILED || true


