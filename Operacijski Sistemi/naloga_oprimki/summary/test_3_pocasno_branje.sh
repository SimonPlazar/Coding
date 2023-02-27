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
printf_local "  - slow reading"; echo
if [[ ! -v VALGRIND ]]
then
    VALGRIND=""
    echo_warn $(printf_local "Could not find valgrind, test will be incomplete.")
fi

################################################################################
# Subtests
################################################################################

print_subtest_title "počasno branje"
rm -f "$output_path"
mkfifo input_pipe
$VALGRIND "$EXEC" -i input_pipe -o "$output_path" &
exec 3>input_pipe
rm -f input_pipe
echo -n "abcjkl" >&3
sleep 1
echo -n "123MNO" >&3
exec 3>&-
expected_output=$(echo -n "abcjkl123MNO" | xxd -p -u -c 1 | sed -e "s/^/0x/")
check "$?" 0 "$(< $output_path)" "$expected_output"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

rm -f "$output_path"

exit "$TEST_RESULT"
