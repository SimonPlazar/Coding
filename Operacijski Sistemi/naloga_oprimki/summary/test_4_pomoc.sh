#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

output_path="./ouput.txt"

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - help of the program"; echo
if [[ ! -v VALGRIND ]]
then
    VALGRIND=""
    echo_warn $(printf_local "Could not find valgrind, test will be incomplete.")
fi

################################################################################
# Subtests
################################################################################

print_subtest_title "pomoč"
rm -f "$output_path"
$VALGRIND "$EXEC" -h > "$output_path"
check_status "$?" 0 "$(< $output_path)" "Izpis pomoči z vsemi zastavicami in njihovimi opisi."

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

rm -f "$output_path"

exit "$TEST_RESULT"
