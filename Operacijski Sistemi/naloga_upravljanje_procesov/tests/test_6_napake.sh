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

################################################################################
# Subtests
################################################################################

# Invalid flag
print_subtest_title "neveljavna zastavica"
rm -f "$output_path"
rm -f "$stderr_path"
"$EXEC" -a > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o neveljavni zastavici."

# Flag missing argument
print_subtest_title "zastavici manjka argument"
rm -f "$output_path"
rm -f "$stderr_path"
"$EXEC" -c > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o manjkajočem argumentu zastavice."

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
