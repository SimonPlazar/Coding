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
printf_local "  - performance of past jobs in ascending, descending and random order"; echo

################################################################################
# Subtests
################################################################################

job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-1 years")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-1 days")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-1 seconds")

# Subtest 1
cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
${job_3_time} $(build_cmd job_3)
EOF

print_subtest_title "Pretekli posli (naraščajoče - 1 2 3)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result=$?
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 2
cat << EOF > simplecron.conf
${job_3_time} $(build_cmd job_3)
${job_2_time} $(build_cmd job_2)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Pretekli posli (padajoče - 3 2 1)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 3
cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_3_time} $(build_cmd job_3)
${job_2_time} $(build_cmd job_2)
EOF

print_subtest_title "Pretekli posli (naključno - 1 3 2)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 4
cat << EOF > simplecron.conf
${job_2_time} $(build_cmd job_2)
${job_1_time} $(build_cmd job_1)
${job_3_time} $(build_cmd job_3)
EOF

print_subtest_title "Pretekli posli (naključno - 2 1 3)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 5
cat << EOF > simplecron.conf
${job_2_time} $(build_cmd job_2)
${job_3_time} $(build_cmd job_3)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Pretekli posli (naključno - 2 3 1)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 6
cat << EOF > simplecron.conf
${job_3_time} $(build_cmd job_3)
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
EOF

print_subtest_title "Pretekli posli (naključno - 3 1 2)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
time_now=$(date +%s)
expected_output=$(echo -e "job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "$TEST_RESULT"
