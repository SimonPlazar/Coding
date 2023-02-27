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
printf_local "  - missing required argument"; echo

################################################################################
# Subtests
################################################################################

print_subtest_title "manjkajoč obvezen argument"
rm -f "$output_path"
rm -f "$stderr_path"
${VALGRIND} "$EXEC" > "$output_path" 2>"$stderr_path"
check_status "$?" 1 "$(< $stderr_path)" "Opozorilo o manjkajočem obveznem argumentu."

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
