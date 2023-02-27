#!/usr/bin/env bash

TEST_LOCALIZATIONS_FILE="$(realpath ./tests/test_localizations_slo.sh)"
EXEC_SERVER="${EXEC_SERVER:-$(realpath ./exec/var_server)}"
EXEC_CLIENT="${EXEC_CLIENT:-$(realpath ./exec/var_client)}"

export TEST_LOCALIZATIONS_FILE
export EXEC_SERVER
export EXEC_CLIENT

if which valgrind &>/dev/null
then
    VALGRIND="valgrind --quiet --leak-check=full --errors-for-leak-kinds=all \
        --show-leak-kinds=all --error-exitcode=1"
else
    VALGRIND=""
fi
export VALGRIND
export TEST_VERSION='v1.10'
