#!/usr/bin/env bash

source test_common.sh
source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

actual_output_path="./actual_output.txt"

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - performance of signals SIGTERM and SIGINT"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
job_1_time_exp=$(date +"%s" -d "+10 seconds")
job_2_time_exp=$(date +"%s" -d "+20 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} echo job_1
${job_2_time} echo job_2
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGTERM (noben posel se ne izvede)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGTERM "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "${job_1_time_exp} echo job_1\n${job_2_time_exp} echo job_2\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 2
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+20 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} echo job_2
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGTERM (dva posla se ne izvedeta)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGTERM "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "job_1 ${job_1_time_exp}\n${job_2_time_exp} echo job_2\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 3
job_1_time_exp=$(date +"%s" -d "+2 seconds")
job_2_time_exp=$(date +"%s" -d "+3 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGTERM (en posel se ne izvede)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGTERM "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 4
job_1_time_exp=$(date +"%s" -d "+10 seconds")
job_2_time_exp=$(date +"%s" -d "+20 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} echo job_1
${job_2_time} echo job_2
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGINT (noben posel se ne izvede)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGINT "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "${job_1_time_exp} echo job_1\n${job_2_time_exp} echo job_2\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 5
job_1_time_exp=$(date +"%s" -d "+3 seconds")
job_2_time_exp=$(date +"%s" -d "+20 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} echo job_2
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGINT (dva posla se ne izvedeta)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGINT "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "job_1 ${job_1_time_exp}\n${job_2_time_exp} echo job_2\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

# Subtest 6
job_1_time_exp=$(date +"%s" -d "+2 seconds")
job_2_time_exp=$(date +"%s" -d "+3 seconds")
job_3_time_exp=$(date +"%s" -d "+30 seconds")
job_1_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_1_time_exp}")
job_2_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_2_time_exp}")
job_3_time=$(date +"%-S %-M %-H %-d %-m %-y" -d @"${job_3_time_exp}")

cat << EOF > simplecron.conf
${job_1_time} $(build_cmd job_1)
${job_2_time} $(build_cmd job_2)
${job_3_time} echo job_3
EOF

print_subtest_title "Signal SIGINT (en posel se ne izvede)"
rm -f "${actual_output_path}"
${VALGRIND} "${EXEC}" simplecron.conf > "${actual_output_path}" &
sleep 5
kill -SIGINT "${!}"
wait
actual_output=$(<"${actual_output_path}")
expected_output=$(echo -e "job_1 ${job_1_time_exp}\njob_2 ${job_2_time_exp}\n${job_3_time_exp} echo job_3")
check_tolerance "$?" 0 "$actual_output" "$expected_output" "$TOLERANCE_POS" "$TOLERANCE"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

rm -f "${actual_output_path}"

exit "$TEST_RESULT"
