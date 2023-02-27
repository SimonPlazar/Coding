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
printf "  - %s\n" "$(printf_local "SET waits SET")"
printf "  - %s\n" "$(printf_local "SET waits GET")"

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "$(printf_local "SET waits SET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" -d 2000 1> /dev/null 2> /dev/null &
sleep 0.5
echo "123" | "${EXEC_CLIENT}" SET "var_a" -t 500 1> /dev/null 2> /dev/null
ACTUAL_EXIT_STATUS="${?}"
sleep 3
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 5 "SET čaka SET." "SET ne čaka SET."

# Subtest 2
print_subtest_title "$(printf_local "SET waits GET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
sleep 0.5
"${EXEC_CLIENT}" GET "var_a" -d 2000 1> /dev/null 2> /dev/null &
sleep 0.5
echo "123" | "${EXEC_CLIENT}" SET "var_a" -t 500 1> /dev/null 2> /dev/null
ACTUAL_EXIT_STATUS="${?}"
sleep 3
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 5 "SET čaka GET." "SET ne čaka GET."

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

pkill -SIGKILL -f "${EXEC_SERVER}"
pkill -SIGKILL -f "${EXEC_CLIENT}"

exit "${TEST_RESULT}"
