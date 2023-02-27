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
printf_local "  - working of the flag -d"; echo

################################################################################
# Subtests
################################################################################

# 1. -d abs_path [A1, B1, C1]
print_subtest_title "-d abs_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_A1,$PID_B1,$PID_C1")
actual_output=$("${EXEC}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")")
check "$?" 0 "$actual_output" "$expected_output"

# 2. -d abs_path [A2]
print_subtest_title "-d abs_pot(${PROG_A_DIR})"
expected_output=$(get_expected_output "$PID_A2")
actual_output=$("${EXEC}" -d "$(realpath "${PROG_A_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 3. -d abs_path [B2]
print_subtest_title "-d abs_pot(${PROG_B_DIR})"
expected_output=$(get_expected_output "$PID_B2")
actual_output=$("${EXEC}" -d "$(realpath "${PROG_B_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 4. -d abs_path [C2]
print_subtest_title "-d abs_pot(${PROG_C_DIR})"
expected_output=$(get_expected_output "$PID_C2")
actual_output=$("${EXEC}" -d "$(realpath "${PROG_C_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 5. -d abs_path []
print_subtest_title "-d abs_pot(path_null)"
expected_output=""
actual_output=$("${EXEC}" -d "$(realpath path_null)")
check "$?" 0 "$actual_output" "$expected_output"

# 6. -d rel_path [A1, B1, C1]
print_subtest_title "-d rel_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_A1,$PID_B1,$PID_C1")
actual_output=$("${EXEC}" -d "$(dirname "${PROG_A_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 7. -d rel_path [A2]
print_subtest_title "-d rel_pot(${PROG_A_DIR})"
expected_output=$(get_expected_output "$PID_A2")
actual_output=$("${EXEC}" -d "${PROG_A_DIR}")
check "$?" 0 "$actual_output" "$expected_output"

# 8. -d rel_path [B2]
print_subtest_title "-d rel_pot(${PROG_B_DIR})"
expected_output=$(get_expected_output "$PID_B2")
actual_output=$("${EXEC}" -d "${PROG_B_DIR}")
check "$?" 0 "$actual_output" "$expected_output"

# 9. -d rel_path [C2]
print_subtest_title "-d rel_pot(${PROG_C_DIR})"
expected_output=$(get_expected_output "$PID_C2")
actual_output=$("${EXEC}" -d "${PROG_C_DIR}")
check "$?" 0 "$actual_output" "$expected_output"

# 10. -d rel_path []
print_subtest_title "-d rel_pot(path_null)"
expected_output=""
actual_output=$("${EXEC}" -d path_null)
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
