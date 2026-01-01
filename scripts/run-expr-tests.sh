#!/usr/bin/env bash

set -u   # undefined variables are errors

TEST_DIR="tst/expressions"
TESTS=("$TEST_DIR"/tst*.ada)

COMPILER="./bin/ada-cc"

failures=0
total=0

echo "Running ${#TESTS[@]} tests"
echo

for test in "${TESTS[@]}"; do
    name=$(basename "$test")
    printf "[ RUN      ] %s\r" "$name"

    if "$COMPILER" expr "$test" > /dev/null 2>&1 ; then
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
