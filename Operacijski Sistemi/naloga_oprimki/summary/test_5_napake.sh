#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

output_path="./ouput.txt"
stderr_path="./stderr.txt"

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - invalid flag"; echo
printf_local "  - flag missing argument"; echo
printf_local "  - input file does not exist"; echo
printf_local "  - output file already exists"; echo
printf_local "  - input file descriptor is not a valid number"; echo
printf_local "  - output file descriptor is not a valid number"; echo
printf_local "  - reading error"; echo
printf_local "  - writing error"; echo

################################################################################
# Subtests
################################################################################

# Invalid flag
print_subtest_title "neveljavna zastavica"
rm -f "$output_path"
"$EXEC" -a > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o neveljavni zastavici."

# Flag missing argument
print_subtest_title "zastavici manjka argument"
rm -f "$output_path"
"$EXEC" -i > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o manjkajočem argumentu zastavice."

# Input File
print_subtest_title "vhodna zbirka ne obstaja"
rm -f "$output_path"
"$EXEC" -i "NULL" > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo, da vhodna zbirka ne obstaja."

# Output File
print_subtest_title "izhodna zbirka že obstaja"
rm -f "$output_path"
touch "$output_path"
echo -n abcjkl | "$EXEC" -o "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo, da izhodna zbirka že obstaja."

# Input File Descriptor
print_subtest_title "oprimek za branje ni veljavno število"
rm -f "$output_path"
"$EXEC" -I abc > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo, da oprimek za branje ni veljavno število."

# Output File Descriptor
print_subtest_title "oprimek za pisanje ni veljavno število"
rm -f "$output_path"
echo -n abcjkl | "$EXEC" -O abc > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo, da oprimek za pisanje ni veljavno število."

# Reading
print_subtest_title "napaka pri branju"
rm -f "$output_path"
"$EXEC" -I 8 > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o napaki pri branju."

# Writing
print_subtest_title "napaka pri pisanju"
rm -f "$output_path"
echo -n abcjkl | "$EXEC" -O 8 > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o napaki pri pisanju."

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

rm -f "$output_path"
rm -f "$stderr_path"

exit "$TEST_RESULT"
