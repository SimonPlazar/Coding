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
printf_local "  - performance of past and future jobs"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 years")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 days")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 seconds")

job_4_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-3 seconds")

job_5_time_exp=$(date +"%s" -d "+3 seconds")
job_6_time_exp=$(date +"%s" -d "+5 seconds")
job_7_time_exp=$(date +"%s" -d "+10 seconds")
job_5_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_5_time_exp}")
job_6_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_6_time_exp}")
job_7_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_7_time_exp}")

job_8_time_exp=$(date +"%s" -d "+12 seconds")
job_8_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_8_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
${job_3_time} $(build_cmd job_3)
${job_4_time} $(build_cmd job_4)
${job_4_time} $(build_cmd job_4)
${job_4_time} $(build_cmd job_4)
${job_5_time} $(build_cmd job_5)
${job_6_time} $(build_cmd job_6)
${job_7_time} $(build_cmd job_7)
${job_8_time} $(build_cmd job_8)
${job_8_time} $(build_cmd job_8)
${job_8_time} $(build_cmd job_8)
EOF

print_subtest_title "Pretekli in prihodnji posli (naraščajoče)"
time_now=$(date +%s)
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "\
job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}\n\
job_4 ${time_now}\njob_4 ${time_now}\njob_4 ${time_now}\n\
job_5 ${job_5_time_exp}\njob_6 ${job_6_time_exp}\njob_7 ${job_7_time_exp}\n\
job_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 2
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 years")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 days")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 seconds")

job_4_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-3 seconds")

job_5_time_exp=$(date +"%s" -d "+3 seconds")
job_6_time_exp=$(date +"%s" -d "+5 seconds")
job_7_time_exp=$(date +"%s" -d "+10 seconds")
job_5_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_5_time_exp}")
job_6_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_6_time_exp}")
job_7_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_7_time_exp}")

job_8_time_exp=$(date +"%s" -d "+12 seconds")
job_8_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_8_time_exp}")

cat << EOF > simplecron.conf
${job_8_time} $(build_cmd job_8)
${job_8_time} $(build_cmd job_8)
${job_8_time} $(build_cmd job_8)
${job_7_time} $(build_cmd job_7)
${job_6_time} $(build_cmd job_6)
${job_5_time} $(build_cmd job_5)
${job_4_time} $(build_cmd job_4)
${job_4_time} $(build_cmd job_4)
${job_4_time} $(build_cmd job_4)
${job_3_time} $(build_cmd job_3)
${job_2_time} $(build_cmd job_2)
${job_1_time} $(build_cmd job_1)
EOF

print_subtest_title "Pretekli in prihodnji posli (padajoče)"
time_now=$(date +%s)
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "\
job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}\n\
job_4 ${time_now}\njob_4 ${time_now}\njob_4 ${time_now}\n\
job_5 ${job_5_time_exp}\njob_6 ${job_6_time_exp}\njob_7 ${job_7_time_exp}\n\
job_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 3
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 years")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 days")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-5 seconds")

job_4_time=$(date +"%-S %-M %-H %-d %-m %-y" -d "-3 seconds")

job_5_time_exp=$(date +"%s" -d "+3 seconds")
job_6_time_exp=$(date +"%s" -d "+5 seconds")
job_7_time_exp=$(date +"%s" -d "+10 seconds")
job_5_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_5_time_exp}")
job_6_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_6_time_exp}")
job_7_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_7_time_exp}")

job_8_time_exp=$(date +"%s" -d "+12 seconds")
job_8_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_8_time_exp}")

cat << EOF > simplecron.conf
${job_4_time} $(build_cmd job_4)
${job_7_time} $(build_cmd job_7)
${job_1_time} $(build_cmd job_1)
${job_4_time} $(build_cmd job_4)
${job_3_time} $(build_cmd job_3)
${job_6_time} $(build_cmd job_6)
${job_8_time} $(build_cmd job_8)
${job_5_time} $(build_cmd job_5)
${job_8_time} $(build_cmd job_8)
${job_2_time} $(build_cmd job_2)
${job_8_time} $(build_cmd job_8)
${job_4_time} $(build_cmd job_4)
EOF

print_subtest_title "Pretekli in prihodnji posli (naključno)"
time_now=$(date +%s)
actual_output=$(${VALGRIND} "${EXEC}" simplecron.conf)
result="$?"
expected_output=$(echo -e "\
job_1 ${time_now}\njob_2 ${time_now}\njob_3 ${time_now}\n\
job_4 ${time_now}\njob_4 ${time_now}\njob_4 ${time_now}\n\
job_5 ${job_5_time_exp}\njob_6 ${job_6_time_exp}\njob_7 ${job_7_time_exp}\n\
job_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}\njob_8 ${job_8_time_exp}")
check_tolerance "$result" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "$TEST_RESULT"
