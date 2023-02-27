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
printf_local "  - multiple simultaneous sequential allocations"; echo
printf_local "  - multiple simultaneous parallel allocations"; echo
printf_local "  - multiple simultaneous parallel reversed allocations"; echo
printf_local "  - multiple simultaneous parallel random allocations"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "alociraj zaporedno 3 x 10 B, 3 x 1 kB, 3 x 4 kB in 3 x 1 MB"
read -r -d '' expected_output << EOF
mmap 1 11
munmap 1 11
mmap 2 11
munmap 2 11
mmap 3 11
munmap 3 11
mmap 4 1025
munmap 4 1025
mmap 5 1025
munmap 5 1025
mmap 6 1025
munmap 6 1025
mmap 7 4097
munmap 7 4097
mmap 8 4097
munmap 8 4097
mmap 9 4097
munmap 9 4097
mmap 10 1048577
munmap 10 1048577
mmap 11 1048577
munmap 11 1048577
mmap 12 1048577
munmap 12 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_multiple_3x_sequential")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 2
print_subtest_title "alociraj vzporedno 3 x 10 B, 3 x 1 kB, 3 x 4 kB in 3 x 1 MB"
read -r -d '' expected_output << EOF
mmap 1 33
munmap 1 33
mmap 2 3075
munmap 2 3075
mmap 3 4097
mmap 4 4097
mmap 5 4097
munmap 3 4097
munmap 4 4097
munmap 5 4097
mmap 6 1048577
mmap 7 1048577
mmap 8 1048577
munmap 6 1048577
munmap 7 1048577
munmap 8 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_multiple_3x_parallel")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 3
print_subtest_title "alociraj vzporedno obratno 3 x 10 B, 3 x 1 kB, 3 x 4 kB in 3 x 1 MB"
read -r -d '' expected_output << EOF
mmap 1 33
munmap 1 33
mmap 2 3075
munmap 2 3075
mmap 3 4097
mmap 4 4097
mmap 5 4097
munmap 5 4097
munmap 4 4097
munmap 3 4097
mmap 6 1048577
mmap 7 1048577
mmap 8 1048577
munmap 8 1048577
munmap 7 1048577
munmap 6 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_multiple_3x_parallel_reversed")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 4
print_subtest_title "alociraj vzporedno naključno 3 x 10 B, 3 x 1 kB, 3 x 4 kB in 3 x 1 MB"
read -r -d '' expected_output << EOF
mmap 1 33
munmap 1 33
mmap 2 3075
munmap 2 3075
mmap 3 4097
mmap 4 4097
mmap 5 4097
munmap 4 4097
munmap 5 4097
munmap 3 4097
mmap 6 1048577
mmap 7 1048577
mmap 8 1048577
munmap 7 1048577
munmap 8 1048577
munmap 6 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_multiple_3x_parallel_random")
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
