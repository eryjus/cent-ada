#!/usr/bin/env bash

set -euo pipefail

TEST_DIR="tst/ast-checks"
TESTS=("$TEST_DIR"/tst*.ada)

COMPILER="./bin/ada-cc"

failures=0
total=0

echo "Running ${#TESTS[@]} tests"
echo

for test in "${TESTS[@]}"; do
    total=$((total + 1))

    name=$(basename "$test")
    expected="$TEST_DIR/expected/${name%.ada}.expected"
    actual=$(mktemp
    )
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
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$expected"

    if diff -u "$expected" "$actual" > /dev/null ; then
        printf "[      OK  ] %s\n" "$name"
    else
        printf "[  FAILED  ] %s (AST mismatch)\n" "$name"
        echo "---- diff ----"
        diff -u "$expected" "$actual" || true
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
