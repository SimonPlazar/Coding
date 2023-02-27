#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

input_path="./input.txt"
output_path="./output.txt"
read -r -d '' expected_output << EOM
0x61
0x62
0x63
0x6A
0x6B
0x6C
EOM
echo -n "abcjkl" > "$input_path"

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - reading of standard input and writing to standard output"; echo
printf_local "  - reading and writing of files"; echo
printf_local "  - reading and writing of file descriptors"; echo
printf_local "  - all possible combinations between them"; echo

if [[ ! -v VALGRIND ]]
then
    VALGRIND=""
    echo_warn $(printf_local "Could not find valgrind, test will be incomplete.")
fi

################################################################################
# Subtests
################################################################################

# Standard Input
# ==============

# std in, std out
print_subtest_title "std in, std out"
rm -f "$output_path"
echo -n abcjkl | $VALGRIND "$EXEC" > "$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# std in, file out
print_subtest_title "std in, file out"
rm -f "$output_path"
echo -n abcjkl | $VALGRIND "$EXEC" -o "$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# std in, fd out
print_subtest_title "std in, fd out"
rm -f "$output_path"
echo -n abcjkl | $VALGRIND "$EXEC" -O 5 5>"$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# File Input
# ==========

# file in, std out
print_subtest_title "file in, std out"
rm -f "$output_path"
$VALGRIND "$EXEC" -i "$input_path" > "$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# file in, file out
print_subtest_title "file in, file out"
rm -f "$output_path"
$VALGRIND "$EXEC" -i "$input_path" -o "$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# file in, fd out
print_subtest_title "file in, fd out"
rm -f "$output_path"
$VALGRIND "$EXEC" -i "$input_path" -O 5 5>"$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# File Descriptor Input
# =====================

# fd in, std out
print_subtest_title "fd in, std out"
rm -f "$output_path"
$VALGRIND "$EXEC" -I 5 5<"$input_path" > "$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# fd in, file out
print_subtest_title "fd in, file out"
rm -f "$output_path"
$VALGRIND "$EXEC" -I 5 -o "$output_path" 5<"$input_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

# fd in, fd out
print_subtest_title "fd in, fd out"
rm -f "$output_path"
$VALGRIND "$EXEC" -I 5 -O 6 5<"$input_path" 6>"$output_path"
check "$?" 0 "$(< $output_path)" "$expected_output"

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
