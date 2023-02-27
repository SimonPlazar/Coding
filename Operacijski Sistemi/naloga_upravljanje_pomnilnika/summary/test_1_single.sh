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
printf_local "  - single allocations"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "alociraj 10 B"
read -r -d '' expected_output << EOF
mmap 1 11
munmap 1 11
EOF
actual_output=$(run_strace "${EXEC}" "test_10B")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 2
print_subtest_title "alociraj 1 kB"
read -r -d '' expected_output << EOF
mmap 1 1025
munmap 1 1025
EOF
actual_output=$(run_strace "${EXEC}" "test_1kB")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 3
print_subtest_title "alociraj 4 kB"
read -r -d '' expected_output << EOF
mmap 1 4097
munmap 1 4097
EOF
actual_output=$(run_strace "${EXEC}" "test_4kB")
actual_exit_status="${?}"
check_strace "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 4
print_subtest_title "alociraj 1 MB"
read -r -d '' expected_output << EOF
mmap 1 1048577
munmap 1 1048577
EOF
actual_output=$(run_strace "${EXEC}" "test_1MB")
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
