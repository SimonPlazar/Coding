#!/usr/bin/env bash

source test_common.sh
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
printf_local "  - multiple sequential allocations"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "alociraj 3 x 10 B zaporedno"
read -r -d '' expected_output << EOF
mmap 1 11
munmap 1 11
mmap 2 11
munmap 2 11
mmap 3 11
munmap 3 11
EOF
actual_output=$(run_strace "${EXEC}" "test_3x10B_sequential")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 2
print_subtest_title "alociraj 3 x 1 kB zaporedno"
read -r -d '' expected_output << EOF
mmap 1 1025
munmap 1 1025
mmap 2 1025
munmap 2 1025
mmap 3 1025
munmap 3 1025
EOF
actual_output=$(run_strace "${EXEC}" "test_3x1kB_sequential")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 3
print_subtest_title "alociraj 3 x 4 kB zaporedno"
read -r -d '' expected_output << EOF
mmap 1 4097
munmap 1 4097
mmap 2 4097
munmap 2 4097
mmap 3 4097
munmap 3 4097
EOF
actual_output=$(run_strace "${EXEC}" "test_3x4kB_sequential")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 4
print_subtest_title "alociraj 3 x 1 MB zaporedno"
read -r -d '' expected_output << EOF
mmap 1 1048577
munmap 1 1048577
mmap 2 1048577
munmap 2 1048577
mmap 3 1048577
munmap 3 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_3x1MB_sequential")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "${TEST_RESULT}"
