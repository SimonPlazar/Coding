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
printf_local "  - performance of past jobs with simultaneous execution time"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-3 seconds")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_1_time} $(build_cmd job_1)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Pretekli posli (hkratno - 1 1 1)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_1 ${time_now}\njob_1 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "$TEST_RESULT"
