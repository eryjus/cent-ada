
.SILENT:

.phony: all
all:
	tup



.phony: test
test: all
	for file in tst/scanner/*.ada; do \
		bin/ada-cc scan $$file ;\
	done



.PHONY: test-types
test-types:
	echo "== Running declaration tests =="
	tup
	./scripts/run-type-tests.sh
