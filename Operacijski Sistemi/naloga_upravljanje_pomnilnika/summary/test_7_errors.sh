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
printf_local "  - mymalloc returns NULL on error"; echo
printf_local "  - myfree works with NULL"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "alociraj 0 B"
"${EXEC}" "test_error_0_B"
actual_exit_status="${?}"
if [[ "${actual_exit_status}" -eq 0 ]]
then
    actual_output="Funkcija mymmalloc vrne NULL"
else
    actual_output="Funkcija mymmalloc ne vrne NULL"
fi
check "${actual_exit_status}" 0 "${actual_output}" "Funkcija mymmalloc vrne NULL"

# Subtest 2
print_subtest_title "alociraj 1 TB"
"${EXEC}" "test_error_1_TB"
actual_exit_status="${?}"
if [[ "${actual_exit_status}" -eq 0 ]]
then
    actual_output="Funkcija mymmalloc vrne NULL"
else
    actual_output="Funkcija mymmalloc ne vrne NULL"
fi
check "${actual_exit_status}" 0 "${actual_output}" "Funkcija mymmalloc vrne NULL"

# Subtest 3
print_subtest_title "dealociraj NULL"
"${EXEC}" "test_error_NULL"
actual_exit_status="${?}"
if [[ "${actual_exit_status}" -eq 0 ]]
then
    actual_output="Funkcija myfree deluje z NULL"
else
    actual_output="Funkcija myfree ne deluje z NULL"
fi
check "${actual_exit_status}" 0 "${actual_output}" "Funkcija myfree deluje z NULL"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "${TEST_RESULT}"
