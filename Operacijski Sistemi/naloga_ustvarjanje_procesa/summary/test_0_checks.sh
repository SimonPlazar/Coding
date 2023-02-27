#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local '  - an implementation is available and can be tested'; echo

print_subtest_title "$(printf_local 'looking for executable')"

if ! [ -v EXEC ]
then
    echo_fail "$(printf_local 'Executable not set.')"
    exit 1
fi

if ! [ -a "${EXEC}" ]
then
    echo_fail "$(printf_local 'Executable not found:')"
    echo_fail "${EXEC}"
    exit 1
fi

echo_ok "$(printf_local 'Executable found:')"
echo_ok "${EXEC}"

exit 0
