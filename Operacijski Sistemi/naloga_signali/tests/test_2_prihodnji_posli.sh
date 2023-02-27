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
printf_local "  - performance of future jobs in ascending, descending and random order"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
${job_3_time} $(build_cmd job_3)
EOF

print_subtest_title "Prihodnji posli (naraščajoče - 1 2 3)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 2
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_3_time} $(build_cmd job_3)
${job_2_time} $(build_cmd job_2)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Prihodnji posli (padajoče - 3 2 1)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 3
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_3_time} $(build_cmd job_3)
${job_2_time} $(build_cmd job_2)
EOF

print_subtest_title "Prihodnji posli (naključno - 1 3 2)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 4
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_2_time} $(build_cmd job_2)
${job_1_time} $(build_cmd job_1)
${job_3_time} $(build_cmd job_3)
EOF

print_subtest_title "Prihodnji posli (naključno - 2 1 3)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 5
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_2_time} $(build_cmd job_2)
${job_3_time} $(build_cmd job_3)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Prihodnji posli (naključno - 2 3 1)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 6
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+5 seconds")
job_3_time_exp=$(date +"%s" -d "+10 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_3_time} $(build_cmd job_3)
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
EOF

print_subtest_title "Prihodnji posli (naključno - 3 1 2)"
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\njob_3 ${job_3_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "$TEST_RESULT"
