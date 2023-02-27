#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local '  - an implementation is available and can be tested (server)'; echo
printf_local '  - an implementation is available and can be tested (client)'; echo

################################################################################
# Server
################################################################################

print_subtest_title "$(printf_local 'looking for executable (server)')"

if ! [ -v EXEC_SERVER ]
then
    echo_fail "$(printf_local 'Executable not set (server).')"
    exit 1
fi

if ! [ -a "${EXEC_SERVER}" ]
then
    echo_fail "$(printf_local 'Executable not found (server):')"
    echo_fail "${EXEC_SERVER}"
    exit 1
fi

echo_ok "$(printf_local 'Executable found (server):')"
echo_ok "${EXEC_SERVER}"

################################################################################
# Client
################################################################################

print_subtest_title "$(printf_local 'looking for executable (client)')"

if ! [ -v EXEC_CLIENT ]
then
    echo_fail "$(printf_local 'Executable not set (client).')"
    exit 1
fi

if ! [ -a "${EXEC_CLIENT}" ]
then
    echo_fail "$(printf_local 'Executable not found (client):')"
    echo_fail "${EXEC_CLIENT}"
    exit 1
fi

echo_ok "$(printf_local 'Executable found (client):')"
echo_ok "${EXEC_CLIENT}"

################################################################################
# Valgrind
################################################################################

if [[ -z "${VALGRIND}" ]]
then
    echo
    echo_warn "$(printf_local "Could not find valgrind, tests will be incomplete.")"
fi

exit 0
