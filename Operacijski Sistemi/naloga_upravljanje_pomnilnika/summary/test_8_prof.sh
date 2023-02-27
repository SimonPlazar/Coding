#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Init
################################################################################

function get_expected_output
{
    local prof_file_path="$1"
    local expected_output_file_path="$2"

    local expected_output="$(cat "${prof_file_path}" \
        | tail -n +2 \
        | paste -d " " - "${expected_output_file_path}" \
        | awk '$1 == "ALLO" { printf "mymalloc(%d)[%d] - razlika alociranih strani: %s\n", $3, $2, $4 } \
               $1 == "FREE" { printf "myfree()[%d] - razlika alociranih strani: %s\n", $2, $3 }' )"

    echo "${expected_output}"
}

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - different memory alocation profiles"; echo
printf_local "  - different memory related errors"; echo

################################################################################
# Subtests
################################################################################

# Subtest 1
print_subtest_title "profiliranje osnovno"
expected_output="$(get_expected_output "profiles/mem_alloc_prof_basic.txt" \
    "profiles/mem_alloc_prof_basic_expected_output.txt")"
actual_output=$("${EXEC}" "run_mem_alloc_prof" "profiles/mem_alloc_prof_basic.txt")
actual_exit_status="${?}"
check "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 2
print_subtest_title "profiliranje dodajanje na konec"
expected_output="$(get_expected_output "profiles/mem_alloc_prof_append.txt" \
    "profiles/mem_alloc_prof_append_expected_output.txt")"
actual_output=$("${EXEC}" "run_mem_alloc_prof" "profiles/mem_alloc_prof_append.txt")
actual_exit_status="${?}"
check "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 3
print_subtest_title "profiliranje ponovna uporaba"
expected_output="$(get_expected_output "profiles/mem_alloc_prof_reuse.txt" \
    "profiles/mem_alloc_prof_reuse_expected_output.txt")"
actual_output=$("${EXEC}" "run_mem_alloc_prof" "profiles/mem_alloc_prof_reuse.txt")
actual_exit_status="${?}"
check "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 4
print_subtest_title "profiliranje dolgo"
expected_output="$(get_expected_output "profiles/mem_alloc_prof_long.txt" \
    "profiles/mem_alloc_prof_long_expected_output.txt")"
actual_output=$("${EXEC}" "run_mem_alloc_prof" "profiles/mem_alloc_prof_long.txt")
actual_exit_status="${?}"
check_diff "${actual_exit_status}" 0 "${actual_output}" "${expected_output}"

# Subtest 5
print_subtest_title "profiliranje valgrind"
actual_output=$(${VALGRIND} "${EXEC}" "run_mem_alloc_prof" "profiles/mem_alloc_prof_long.txt")
actual_exit_status="${?}"
if [[ "${actual_exit_status}" -eq 0 ]]
then
    actual_output="Valgrind ni našel napak"
else
    actual_output="Valgrind je našel napake"
fi
check "${actual_exit_status}" 0 "${actual_output}" "Valgrind ni našel napak"

################################################################################
# Footer
################################################################################

print_footer

################################################################################
# Deinit
################################################################################

exit "${TEST_RESULT}"
