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
printf_local "  - working of the flag -e"; echo

################################################################################
# Subtests
################################################################################

# 1. -e abs_path [A1, A2]
print_subtest_title "-e abs_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1,$PID_A2")
actual_output=$("${EXEC}" -e "$(realpath "${PROG_A_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 2. -e abs_path [B1, B2]
print_subtest_title "-e abs_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_B1,$PID_B2")
actual_output=$("${EXEC}" -e "$(realpath "${PROG_B_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 3. -e abs_path [C1, C2]
print_subtest_title "-e abs_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=$(get_expected_output "$PID_C1,$PID_C2")
actual_output=$("${EXEC}" -e "$(realpath "${PROG_C_DIR}${PROG_C_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 4. -e abs_path []
print_subtest_title "-e abs_pot(path_null)"
expected_output=""
actual_output=$("${EXEC}" -e "$(realpath path_null)")
check "$?" 0 "$actual_output" "$expected_output"

# 5. -e rel_path [A1, A2]
print_subtest_title "-e rel_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1,$PID_A2")
actual_output=$("${EXEC}" -e "${PROG_A_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 6. -e rel_path [B1, B2]
print_subtest_title "-e rel_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_B1,$PID_B2")
actual_output=$("${EXEC}" -e "${PROG_B_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 7. -e rel_path [C1, C2]
print_subtest_title "-e rel_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=$(get_expected_output "$PID_C1,$PID_C2")
actual_output=$("${EXEC}" -e "${PROG_C_DIR}${PROG_C_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 8. -e rel_path []
print_subtest_title "-e rel_pot(path_null)"
expected_output=""
actual_output=$("${EXEC}" -e path_null)
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
