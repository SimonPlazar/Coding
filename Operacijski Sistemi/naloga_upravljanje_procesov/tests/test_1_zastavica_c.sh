#!/usr/bin/env bash

source test_common.sh
source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

init_common

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - working of the flag -c"; echo

################################################################################
# Subtests
################################################################################

# 1. -c [A1, A2, B1, B2]
print_subtest_title "-c \"${PROG_AB_NAME}\""
expected_output=$(get_expected_output "$PID_A1,$PID_A2,$PID_B1,$PID_B2")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 2. -c [C1, C2]
print_subtest_title "-c \"${PROG_C_NAME}\""
expected_output=$(get_expected_output "$PID_C1,$PID_C2")
actual_output=$("${EXEC}" -c "${PROG_C_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 3. -c []
print_subtest_title "-c \"prog_null\""
expected_output=""
actual_output=$("${EXEC}" -c "prog_null")
check "$?" 0 "$actual_output" "$expected_output"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

deinit_common

exit "$TEST_RESULT"
