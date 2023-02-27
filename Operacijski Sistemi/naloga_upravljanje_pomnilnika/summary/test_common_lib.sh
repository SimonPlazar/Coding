#!/usr/bin/env bash

# Test exit status
#   0 - PASSED
#   1 - TO BE CHECKED MANUALLY
#   2 - FAILED
TEST_RESULT=0

# The number of subtests
SUBTEST_COUNT=0

################################################################################
# BEGIN: Public Functions
################################################################################

function check
{
    local actual_exit_status="$1"
    local expected_exit_status="$2"
    local actual_output="$3"
    local expected_output="$4"

    printf_local "Actual exit status: "; printf "${actual_exit_status}\n"
    printf_local "Expected exit status: "; printf "${expected_exit_status}\n"

    printf_local "Actual output:"; printf "\n"
    echo "${actual_output}" | pipe_output_format
    printf_local "Expected output:"; printf "\n"
    echo "${expected_output}" | pipe_format_wordwrap

    if [[ "${actual_exit_status}" == "${expected_exit_status}" ]] \
    && [[ "${actual_output}" == "${expected_output}" ]]
    then
        _update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else        
        _update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

function check_status
{
    local actual_exit_status="$1"
    local expected_exit_status="$2"
    local actual_output="$3"
    local expected_output="$4"

    printf_local "Actual exit status: "; printf "${actual_exit_status}\n"
    printf_local "Expected exit status: "; printf "${expected_exit_status}\n"

    printf_local "Actual output:"; printf "\n"
    echo "${actual_output}" | pipe_output_format
    printf_local "Expected output:"; printf "\n"
    echo "${expected_output}" | pipe_format_wordwrap

    if [[ "${actual_exit_status}" == "${expected_exit_status}" ]]
    then
        _update_test_result 1
        echo_warn "$(printf_local "SUBTEST TO BE CHECKED MANUALLY")"
    else
        _update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

function check_strace
{
    local actual_exit_status="$1"
    local expected_exit_status="$2"
    local actual_output="$3"
    local expected_output="$4"

    actual_output=$(_strace_transform_actual_output "${actual_output}")
    expected_output=$(_strace_transform_expected_output "${expected_output}" "${actual_output}")

    printf_local "Actual exit status: "; printf "${actual_exit_status}\n"
    printf_local "Expected exit status: "; printf "${expected_exit_status}\n"

    printf_local "Actual output:"; printf "\n"
    echo "${actual_output}" | pipe_output_format
    printf_local "Expected output:"; printf "\n"
    echo "${expected_output}" | pipe_format_wordwrap

    if [[ "${actual_exit_status}" == "${expected_exit_status}" ]] \
    && [[ "${actual_output}" == "${expected_output}" ]]
    then
        _update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else        
        _update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

function check_diff
{
    local actual_exit_status="$1"
    local expected_exit_status="$2"
    local actual_output="$3"
    local expected_output="$4"

    printf_local "Actual exit status: "; printf "${actual_exit_status}\n"
    printf_local "Expected exit status: "; printf "${expected_exit_status}\n"

    if [[ "${actual_exit_status}" == "${expected_exit_status}" ]] \
    && [[ "${actual_output}" == "${expected_output}" ]]
    then
        printf_local "Actual output:"; printf "\n"
        printf_local "Is the same as expected output."; printf "\n"
        printf_local "Expected output:"; printf "\n"
        printf_local "Is the same as actual output."; printf "\n"

        _update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else
        printf_local "Diff between actual and expected outputs:"; printf "\n"
        diff -y --left-column --expand-tabs --tabsize 4 --width 100 --color=always <(echo "$actual_output") <(echo "$expected_output") | cat -n | grep -v -e '($' | head

        _update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

function print_subtest_title
{
    SUBTEST_COUNT=$((SUBTEST_COUNT + 1))
    local title="$(printf_local "Subtest") ${SUBTEST_COUNT}: $1"

    printf "\n%s\n" "${title}"
    printf -- "-%.0s" $(seq 1 ${#title}); printf "\n"
}

function print_footer
{
    echo
    if [ "${TEST_RESULT}" == 0 ]
    then
        echo_ok "$(printf_local "TEST PASSED: All subtests passed.")"
    elif [ "${TEST_RESULT}" == 1 ]
    then
        echo_warn "$(printf_local "TEST TO BE CHECKED MANUALLY: At least one subtest to be checked manually.")"
    else
        echo_fail "$(printf_local "TEST FAILED: At least one subtest failed.")"
    fi
}

################################################################################
# END: Public Functions
################################################################################

################################################################################
# BEGIN: Private Functions
################################################################################

function _update_test_result
{
    TEST_RESULT=$(("$1" > "${TEST_RESULT}" ? "$1" : "${TEST_RESULT}"))
}

function _strace_transform_actual_output
{
    local actual_output="${1}"

    # Select only lines after BEGIN_STRACE
    #   sed -n : do not print by default
    #   sed /${BEGIN_STRACE}/,\$p : print all lines (p) from the one matching
    #                               ${BEGIN_STRACE} until the end ($)
    #   tail -n +2 : skip first line which is ${BEGIN_STRACE}
    actual_output=$(echo "${actual_output}" \
        | sed -n "/${BEGIN_STRACE}/,\$p" \
        | tail -n +2)

    # Select only syscall name (mmap, munmap), address and length
    #   awk -F "[(), ]" : field separators as regular expression
    actual_output=$(echo "${actual_output}" \
        | awk -F "[(), ]" '{ if($1=="mmap") { print $1 " " $NF " " $4 } \
                             else if ($1=="munmap") { print $1 " " $2 " " $4 } }')

    echo "${actual_output}"
}

function _strace_transform_expected_output
{
    local expected_output="${1}"
    local actual_output="${2}"

    # Assign consequent index to each mmap address
    # Example:
    #   1 0x7f75ba6b5000
    #   2 0x7f75ba6b5000
    #   3 0x7f75ba383000
    addrs_map=$(echo "${actual_output}" \
        | awk '{ if ($1 == "mmap") print ++count[$1] " " $2 }')

    # Get page size (usually 4096 bytes)
    page_size=$(getconf PAGESIZE)

    # Round length up to the nearest multiple of a page size
    # Example:
    #   mmap 1 4096
    #   munmap 1 4096
    #   mmap 2 4096
    #   munmap 2 4096
    #   mmap 3 1052672
    #   munmap 3 1052672
    expected_output=$(echo "${expected_output}" \
        | awk -v page_size="${page_size}" \
            'function round(alloc_size) { \
                alloc_over = alloc_size % page_size; \
                if (alloc_over > 0) alloc_size += page_size - alloc_over; \
                return alloc_size } \
            { $NF = round($NF); print }')

    # Replace mmap and munmap address indices with actual addresses
    #   FNR==NR { ... } : while processing first file (addrs_map)
    #   map[$1]=$2 : create a map where map[index]=address
    #   next : go to the next record
    #   FNR!=NR { ... } : while processing second file (expected_output)
    #   map[$2] : print address from map at index $2
    #
    # expected_output example:
    #   mmap 1 4096
    #   munmap 1 4096
    #   mmap 2 4096
    #   munmap 2 4096
    #   mmap 3 1052672
    #   munmap 3 1052672
    #
    # addrs_map example:
    #   1 0x7f75ba6b5000
    #   2 0x7f75ba6b5000
    #   3 0x7f75ba383000
    #
    # expected_output result example:
    #   mmap 0x7f75ba6b5000 4096
    #   munmap 0x7f75ba6b5000 4096
    #   mmap 0x7f75ba6b5000 4096
    #   munmap 0x7f75ba6b5000 4096
    #   mmap 0x7f75ba383000 1052672
    #   munmap 0x7f75ba383000 1052672
    expected_output=$(awk 'FNR==NR { map[$1]=$2; next } \
        FNR!=NR { print $1 " " map[$2] " " $3 }' \
        <(echo "${addrs_map}") <(echo "${expected_output}"))

    echo "${expected_output}"
}

################################################################################
# END: Private Functions
################################################################################
