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
printf_local "  - working of the mixed flags (-c, -d, -e)"; echo

################################################################################
# Subtests [-c -d]
################################################################################

# 1. -c -d abs_path [A1, B1]
# c_1 [A1, A2, B1, B2]
# d_1 [A1, B1, C1]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d abs_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_A1,$PID_B1")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")")
check "$?" 0 "$actual_output" "$expected_output"

# 2. -c -d abs_path []
# c_1 [A1, A2, B1, B2]
# d_4 [C2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d abs_pot(${PROG_C_DIR})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "$(realpath "${PROG_C_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 3. -c -d rel_path [A1, B1]
# c_1 [A1, A2, B1, B2]
# d_6 [A1, B1, C1]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d rel_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_A1,$PID_B1")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "$(dirname "${PROG_A_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

# 4. -c -d rel_path []
# c_1 [A1, A2, B1, B2]
# d_9 [C2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d rel_pot(${PROG_C_DIR})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "${PROG_C_DIR}")
check "$?" 0 "$actual_output" "$expected_output"

# 5. -c -d abs_path [C1]
# c_2 [C1, C2]
# d_1 [A1, B1, C1]
print_subtest_title "-c \"${PROG_C_NAME}\" -d abs_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_C1")
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")")
check "$?" 0 "$actual_output" "$expected_output"

# 6. -c -d rel_path [C1]
# c_2 [C1, C2]
# d_6 [A1, B1, C1]
print_subtest_title "-c \"${PROG_C_NAME}\" -d rel_pot($(dirname "${PROG_A_DIR}"))"
expected_output=$(get_expected_output "$PID_C1")
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -d "$(dirname "${PROG_A_DIR}")")
check "$?" 0 "$actual_output" "$expected_output"

################################################################################
# Subtests [-c -e]
################################################################################

# 7. -c -e abs_path [A1, A2]
# c_1 [A1, A2, B1, B2]
# e_1 [A1, A2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -e abs_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1,$PID_A2")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -e "$(realpath "${PROG_A_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 8. -c -e abs_path []
# c_1 [A1, A2, B1, B2]
# e_3 [C1, C2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -e abs_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -e "$(realpath "${PROG_C_DIR}${PROG_C_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 9. -c -e rel_path [A1, A2]
# c_1 [A1, A2, B1, B2]
# e_5 [A1, A2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -e rel_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1,$PID_A2")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -e "${PROG_A_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 10. -c -e rel_path []
# c_1 [A1, A2, B1, B2]
# e_7 [C1, C2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -e rel_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -e "${PROG_C_DIR}${PROG_C_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 11. -c -e abs_path
# c_2 [C1, C2]
# e_3 [C1, C2]
print_subtest_title "-c \"${PROG_C_NAME}\" -e abs_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=$(get_expected_output "$PID_C1,$PID_C2")
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -e "$(realpath "${PROG_C_DIR}${PROG_C_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 12. -c -e rel_path
# c_2 [C1, C2]
# e_7 [C1, C2]
print_subtest_title "-c \"${PROG_C_NAME}\" -e rel_pot(${PROG_C_DIR}${PROG_C_NAME})"
expected_output=$(get_expected_output "$PID_C1,$PID_C2")
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -e "${PROG_C_DIR}${PROG_C_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

################################################################################
# Subtests [-d -e]
################################################################################

# 13. -d abs_path -e abs_path [A1]
# d_1 [A1, B1, C1]
# e_1 [A1, A2]
print_subtest_title "-d abs_pot($(dirname "${PROG_A_DIR}")) -e abs_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")" -e "$(realpath "${PROG_A_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 14. -d abs_path -e rel_path [A1]
# d_1 [A1, B1, C1]
# e_5 [A1, A2]
print_subtest_title "-d abs_pot($(dirname "${PROG_A_DIR}")) -e rel_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")" -e "${PROG_A_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 15. -d rel_path -e abs_path [A1]
# d_6 [A1, B1, C1]
# e_1 [A1, A2]
print_subtest_title "-d rel_pot($(dirname "${PROG_A_DIR}")) -e abs_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -d "$(dirname "${PROG_A_DIR}")" -e "$(realpath "${PROG_A_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 16. -d rel_path -e rel_path [A1]
# d_6 [A1, B1, C1]
# e_5 [A1, A2]
print_subtest_title "-d rel_pot($(dirname "${PROG_A_DIR}")) -e rel_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -d "$(dirname "${PROG_A_DIR}")" -e "${PROG_A_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 17. -d abs_path -e abs_path []
# d_2 [A2]
# e_2 [B1, B2]
print_subtest_title "-d abs_pot(${PROG_A_DIR}) -e abs_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -d "$(realpath "${PROG_A_DIR}")" -e "$(realpath "${PROG_B_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 18. -d abs_path -e rel_path []
# d_2 [A2]
# e_6 [B1, B2]
print_subtest_title "-d abs_pot(${PROG_A_DIR}) -e rel_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -d "$(realpath "${PROG_A_DIR}")" -e "${PROG_B_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 19. -d rel_path -e abs_path []
# d_7 [A2]
# e_2 [B1, B2]
print_subtest_title "-d rel_pot(${PROG_A_DIR}) -e abs_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -d "${PROG_A_DIR}" -e "$(realpath "${PROG_B_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 20. -d rel_path -e rel_path []
# d_7 [A2]
# e_6 [B1, B2]
print_subtest_title "-d rel_pot(${PROG_A_DIR}) -e rel_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -d "${PROG_A_DIR}" -e "${PROG_B_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

################################################################################
# Subtests [-c -d -e]
################################################################################

# 21. -c -d abs_path -e abs_path [A1]
# c_1 [A1, A2, B1, B2]
# d_1 [A1, B1, C1]
# e_1 [A1, A2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d abs_pot($(dirname "${PROG_A_DIR}")) -e abs_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "$(realpath "$(dirname "${PROG_A_DIR}")")" -e "$(realpath "${PROG_A_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 22. -c -d rel_path -e rel_path [A1]
# c_1 [A1, A2, B1, B2]
# d_6 [A1, B1, C1]
# e_5 [A1, A2]
print_subtest_title "-c \"${PROG_AB_NAME}\" -d rel_pot($(dirname "${PROG_A_DIR}")) -e rel_pot(${PROG_A_DIR}${PROG_AB_NAME})"
expected_output=$(get_expected_output "$PID_A1")
actual_output=$("${EXEC}" -c "${PROG_AB_NAME}" -d "$(dirname "${PROG_A_DIR}")" -e "${PROG_A_DIR}${PROG_AB_NAME}")
check "$?" 0 "$actual_output" "$expected_output"

# 23. -c -d abs_path -e abs_path []
# c_2 [C1, C2]
# d_2 [A2]
# e_2 [B1, B2]
print_subtest_title "-c \"${PROG_C_NAME}\" -d abs_pot(${PROG_A_DIR}) -e abs_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -d "$(realpath "${PROG_A_DIR}")" -e "$(realpath "${PROG_B_DIR}${PROG_AB_NAME}")")
check "$?" 0 "$actual_output" "$expected_output"

# 24. -c -d rel_path -e rel_path []
# c_2 [C1, C2]
# d_7 [A2]
# e_6 [B1, B2]
print_subtest_title "-c \"${PROG_C_NAME}\" -d rel_pot(${PROG_A_DIR}) -e rel_pot(${PROG_B_DIR}${PROG_AB_NAME})"
expected_output=""
actual_output=$("${EXEC}" -c "${PROG_C_NAME}" -d "${PROG_A_DIR}" -e "${PROG_B_DIR}${PROG_AB_NAME}")
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
