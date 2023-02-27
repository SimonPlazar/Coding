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
printf "  - %s\n" "$(printf_local "WAIT waits SET")"
printf "  - %s\n" "$(printf_local "WAIT waits UNSET")"

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "$(printf_local "WAIT waits SET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
sleep 0.5
"${EXEC_CLIENT}" WAIT "var_a" -t 3000 1> /dev/null 2> /dev/null &
pid="${!}"
sleep 2
echo "123" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
wait "${pid}"
ACTUAL_EXIT_STATUS="${?}"
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 3 "WAIT čaka SET." "WAIT ne čaka SET."

# Subtest 2
print_subtest_title "$(printf_local "WAIT waits UNSET")"
server_start
echo "abc" | "${EXEC_CLIENT}" SET "var_a" 1> /dev/null 2> /dev/null
sleep 0.5
"${EXEC_CLIENT}" WAIT "var_a" -t 3000 1> /dev/null 2> /dev/null &
pid="${!}"
sleep 2
"${EXEC_CLIENT}" UNSET "var_a" 1> /dev/null 2> /dev/null
wait "${pid}"
ACTUAL_EXIT_STATUS="${?}"
server_stop
check_with_msg "${ACTUAL_EXIT_STATUS}" 4 "WAIT čaka UNSET." "WAIT ne čaka UNSET."

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
