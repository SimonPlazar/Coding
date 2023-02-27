#!/usr/bin/env bash

TEST_LOCALIZATIONS_FILE="$(realpath ./tests/test_localizations_slo.sh)"
EXEC="${EXEC:-$(realpath ./exec/mymalloc)}"

export TEST_LOCALIZATIONS_FILE
export EXEC

if which valgrind &>/dev/null
then
    VALGRIND="valgrind --quiet --leak-check=full --errors-for-leak-kinds=all \
              --show-leak-kinds=all --error-exitcode=1"
else
    VALGRIND=""
fi
export VALGRIND
export TEST_VERSION='v1.6'
