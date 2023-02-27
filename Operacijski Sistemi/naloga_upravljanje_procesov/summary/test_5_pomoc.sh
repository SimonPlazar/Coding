#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################


################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - program help"; echo
printf_local "  - program start without flags"; echo

################################################################################
# Subtests
################################################################################

print_subtest_title "pomoč programa"
expected_output="Izpis pomoči z vsemi zastavicami in njihovimi opisi."
actual_output=$("${EXEC}" -h)
check_status "$?" 0 "$actual_output" "$expected_output"

print_subtest_title "zagon programa brez zastavic"
expected_output="Izpis pomoči z vsemi zastavicami in njihovimi opisi."
actual_output=$("${EXEC}")
check_status "$?" 0 "$actual_output" "$expected_output"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "$TEST_RESULT"
