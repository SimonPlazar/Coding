#!/usr/bin/env bash

TEST_LOCALIZATIONS_FILE="$(realpath ./tests/test_localizations_slo.sh)"
EXEC="${EXEC:-$(realpath ./exec/hexprint)}"

export TEST_LOCALIZATIONS_FILE
export EXEC

if which valgrind &>/dev/null
then
    VALGRIND='valgrind -q --leak-check=full --error-exitcode=1'
    export VALGRIND
fi
