#!/usr/bin/env bash


function check_results() {
    cleaned=$(mktemp)
    cat "$actual" | ansifilter > "$cleaned"

    sed -i 's/[[:space:]]*$//' "$cleaned"
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$cleaned"

    if diff -u "$expected" "$cleaned" > /dev/null ; then
        printf "[      OK  ] %s\n" "$name"
    else
        printf "[  FAILED  ] %s (AST mismatch)\n" "$name"
        failures=$((failures + 1))

        echo "---- diff ----"
        diff -u "$expected" "$cleaned" --color=always || true
        echo "--------------"
        echo
    fi

    rm "$cleaned"
}


function try_success() {
    ##
    ## -- Perform the compile, capturing the $actual output
    ##    -------------------------------------------------
    if ! "$COMPILER" stmts "$test" &> "$actual" ; then
        printf "[  FAILED  ] %s (compile failed)\n" "$name"
        failures=$((failures + 1))
    else
        check_results
    fi
}


function try_failure() {
    ##
    ## -- Perform the compile, capturing the $actual output
    ##    -------------------------------------------------
    if "$COMPILER" stmts "$test" &> "$actual" ; then
        printf "[  FAILED  ] %s (compile succeeded when it should not have)\n" "$name"
        failures=$((failures + 1))
    else
        check_results
    fi
}



##
## -- Set up the test environment
##    ---------------------------
TEST_DIR="tst/statements"
EXP_DIR="tst/stmt-checks"
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
        TESTS=("$TEST_DIR"/*.ada)
    fi
else
    TESTS=("$TEST_DIR"/*.ada)
fi



##
## -- Set up some global variables
##    ----------------------------
failures=0
total=0



##
## -- Start running the test
##    ----------------------
echo "Running ${#TESTS[@]} tests"
echo



##
## -- The main test loop
##    ------------------
for test in "${TESTS[@]}"; do
    total=$((total + 1))

    name=$(basename "$test")
    expected="$EXP_DIR/${name%.ada}.exp"

    actual=$(mktemp)


    printf "[ RUN      ] %s\r" "$name"



    ##
    ## -- Check if the expected result exists; if not, we cannot continue
    ##    ---------------------------------------------------------------
    if [[ ! -f "$expected" ]] ; then
        echo "[  MISSING ] $name (don't know what to expect)"
        failures=$((failures + 1))
        continue
    fi

    sed -i 's/[[:space:]]*$//' "$expected"
    sed -i ':a;/^[ \n]*$/{$d;N;ba}' "$expected"


    if [[ ${name:0:3} = "bad" ]]; then
        try_failure
    else
        try_success
    fi

    rm -f "$actual"
done




##
## -- Report the results and exit
##    ---------------------------
echo
echo "================================"
echo "Tests run : $total"
echo "Failures  : $failures"
echo "================================"

if [ "$failures" -ne 0 ]; then
    exit 1
fi

