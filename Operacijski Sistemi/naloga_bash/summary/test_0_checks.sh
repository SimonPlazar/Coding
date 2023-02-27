#!/usr/bin/bash
source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test does basic checks:'; echo
printf_local 'an implementation is available and can be tested'; echo

if ! [ -v EXEC ]
then
    echo_fail "$(printf_local 'Executable not set!')"
    exit 1
fi

if ! [ -a "${EXEC}" ]
then
    echo_fail "$(printf_local 'Executable %s does not exists.' "${EXEC}")"
    exit 1
fi

echo_ok "$(printf_local 'Executable: %s' "${EXEC}".)"

exit 0
