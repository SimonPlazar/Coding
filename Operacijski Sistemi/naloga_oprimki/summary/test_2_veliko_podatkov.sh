#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

input_path="./input.txt"
output_path="./ouput.txt"

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - reading and writing larger amounts of data"; echo

if [[ ! -v VALGRIND ]]
then
    VALGRIND=""
    echo_warn $(printf_local "Could not find valgrind, test will be incomplete.")
fi

################################################################################
# Subtests
################################################################################

print_subtest_title "branje in pisanje 1 kB podatkov"
rm -f "$input_path"
rm -f "$output_path"
tr -dc A-Za-z0-9 </dev/urandom | head -c 1000 > "$input_path"
expected_output=$(xxd -p -u -c 1 < $input_path | sed -e "s/^/0x/")
$VALGRIND "$EXEC" -i "$input_path" -o "$output_path"
check_diff "$?" 0 "$(< $output_path)" "$expected_output"

print_subtest_title "branje in pisanje 10 kB podatkov"
rm -f "$input_path"
rm -f "$output_path"
tr -dc A-Za-z0-9 </dev/urandom | head -c 10000 > "$input_path"
expected_output=$(xxd -p -u -c 1 < $input_path | sed -e "s/^/0x/")
$VALGRIND "$EXEC" -i "$input_path" -o "$output_path"
check_diff "$?" 0 "$(< $output_path)" "$expected_output"

print_subtest_title "branje in pisanje 100 kB podatkov"
rm -f "$input_path"
rm -f "$output_path"
tr -dc A-Za-z0-9 </dev/urandom | head -c 100000 > "$input_path"
expected_output=$(xxd -p -u -c 1 < $input_path | sed -e "s/^/0x/")
$VALGRIND "$EXEC" -i "$input_path" -o "$output_path"
check_diff "$?" 0 "$(< $output_path)" "$expected_output"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

rm -f "$input_path"
rm -f "$output_path"

exit "$TEST_RESULT"
