#!/usr/bin/env bash

set -euo pipefail

TEST_DIR="tst/declarations"
EXP_DIR="tst/ast-checks"
COMPILER="./bin/ada-cc"

# If a test name is provided and exists, use only that test.
# Otherwise fall back to all tests.
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
    total=$((total + 1))

    name=$(basename "$test")
    expected="$EXP_DIR/${name%.ada}.exp"
    actual=$(mktemp)
    target=$(mktemp)
    printf "[ RUN      ] %s\r" "$name"

    if [[ ! -f "$expected" ]] ; then
        echo "[  MISSING ] $name (no expected file)"
        failures=$((failures + 1))
        continue
    fi

    if ! "$COMPILER" ast "$test" 2> /dev/null > "$actual" ; then
        printf "[  FAILED  ] %s\n" "$name"
        failures=$((failures + 1))
        rm -f "$actual"
        continue
    fi

    sed -i 's/[[:space:]]*$//' "$actual"
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$actual"

    sed -i 's/[[:space:]]*$//' "$expected"
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$expected"


    echo "PRINTING THE AST STRUCTURE" > "$target"
    echo "==========================" >> "$target"
    cat "$expected" >> "$target"
    echo >> "$target"
    echo >> "$target"

    sed -i 's/[[:space:]]*$//' "$target"
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$target"


    if diff -u "$target" "$actual" > /dev/null ; then
        printf "[      OK  ] %s\n" "$name"
    else
        printf "[  FAILED  ] %s (AST mismatch)\n" "$name"
        echo "---- diff ----"
        diff -u "$target" "$actual" --color=always || true
        echo "--------------"
        failures=$((failures + 1))
    fi

    rm -f "$actual"
done

echo
echo "================================"
echo "Tests run : $total"
echo "Failures  : $failures"
echo "================================"

if [ "$failures" -ne 0 ]; then
    exit 1
fi
