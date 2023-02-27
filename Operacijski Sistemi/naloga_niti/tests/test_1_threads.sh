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
printf "  - %s\n" "$(printf_local "threads performance with SET")"
printf "  - %s\n" "$(printf_local "threads performance with GET")"
printf "  - %s\n" "$(printf_local "threads performance with SET and GET")"

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "$(printf_local "threads performance with SET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" -d 2000 1> /dev/null 2> /dev/null &
sleep 0.5
echo "123" | "${EXEC_CLIENT}" SET "var_b" -t 1000 1> /dev/null 2> /dev/null
ACTUAL_EXIT_STATUS="${?}"
sleep 3
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 0 "Niti delujejo." "Niti ne delujejo."

# Subtest 2
print_subtest_title "$(printf_local "threads performance with GET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
sleep 0.5
echo "123" | "${EXEC_CLIENT}" SET "var_b" 1> /dev/null 2> /dev/null
sleep 0.5
"${EXEC_CLIENT}" GET "var_a" -d 2000 1> /dev/null 2> /dev/null &
sleep 0.5
"${EXEC_CLIENT}" GET "var_b" -t 1000 1> /dev/null 2> /dev/null
ACTUAL_EXIT_STATUS="${?}"
sleep 3
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 0 "Niti delujejo." "Niti ne delujejo."

# Subtest 3
print_subtest_title "$(printf_local "threads performance with SET and GET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
sleep 0.5
echo "123" | "${EXEC_CLIENT}" SET "var_b" -d 2000 1> /dev/null 2> /dev/null &
sleep 0.5
"${EXEC_CLIENT}" GET "var_a" -t 1000 1> /dev/null 2> /dev/null
ACTUAL_EXIT_STATUS="${?}"
sleep 3
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 0 "Niti delujejo." "Niti ne delujejo."

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
