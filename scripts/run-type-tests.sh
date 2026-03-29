#!/usr/bin/env bash

set -u   # undefined variables are errors

TEST_DIR="tst/declarations"
TESTS=("$TEST_DIR"/tst*.ada)

COMPILER="./bin/ada-cc"

##
## -- If a test name is provided and exists, use only that test.
##    Otherwise fall back to all tests.
##    ----------------------------------------------------------
if [[ $# -ge 1 ]]; then
    if [[ -f "$TEST_DIR/$1" ]]; then
        TESTS=("$TEST_DIR/$1")
    else
        echo "Warning: test '$1' not found in $TEST_DIR — running full suite."
        TESTS=("$TEST_DIR"/tst*.ada)
    fi
else
    TESTS=("$TEST_DIR"/tst*.ada)
fi

failures=0
total=0

echo "Running ${#TESTS[@]} tests"
echo

for test in "${TESTS[@]}"; do
    name=$(basename "$test")
    printf "[ RUN      ] %s\r" "$name"

    if "$COMPILER" types "$test" > /dev/null 2>&1 ; then
        printf "[       OK ] %s\n" "$name"
    else
        printf "[  FAILED  ] %s\n" "$name"
        failures=$((failures + 1))
    fi

    total=$((total + 1))
done

echo
echo "================================"
echo "Tests run : $total"
echo "Failures  : $failures"
echo "================================"

if [ "$failures" -ne 0 ]; then
    exit 1
fi
