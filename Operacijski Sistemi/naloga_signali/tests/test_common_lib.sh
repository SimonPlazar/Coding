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

function check_tolerance
{
    local actual_exit_status="$1"
    local expected_exit_status="$2"
    local actual_output="$3"
    local expected_output="$4"
    local tolerance_pos="$5"
    local tolerance="$6"

    printf_local "Actual exit status: "; printf "${actual_exit_status}\n"
    printf_local "Expected exit status: "; printf "${expected_exit_status}\n"

    printf_local "Actual output:"; printf "\n"
    echo "${actual_output}" | pipe_output_format
    printf_local "Expected output:"; printf "\n"
    echo "${expected_output}" | pipe_format_wordwrap

    if [[ "${actual_exit_status}" == "${expected_exit_status}" ]] \
    && _is_within_tolerance "${actual_output}" "${expected_output}" "${tolerance_pos}" "${tolerance}"
    then
        _update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else
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

function _is_within_tolerance
{
    local actual_output=$1
    local expected_output=$2
    local tolerance_pos=$3
    local tolerance=$4

    # Check if number of lines is not equal
    local num_lines_actual=$(echo -n "${actual_output}" | grep -c '^')
    local num_lines_expected=$(echo -n "${expected_output}" | grep -c '^')
    if [ "${num_lines_actual}" -ne "${num_lines_expected}" ]
    then
        return 1
    fi

    # Check if number of characters is not equal
    if [ "${#actual_output}" -ne "${#expected_output}" ]
    then
        return 1
    fi

    for i in $(seq 1 $num_lines_actual)
    do
        local actual_time=$(echo "${actual_output}" | awk -v row=${i} -v col=${tolerance_pos} 'NR==row{print $col}')
        local expected_time=$(echo "${expected_output}" | awk -v row=${i} -v col=${tolerance_pos} 'NR==row{print $col}')
        local diff_time=$((actual_time-expected_time))

        if [ "${diff_time#-}" -gt "$tolerance" ]
        then
            return 1
        fi

        local actual_without_time=$(echo "${actual_output}" | awk -v row=${i} -v col=${tolerance_pos} 'NR==row{$col=""; print $0}')
        local expected_without_time=$(echo "${expected_output}" | awk -v row=${i} -v col=${tolerance_pos} 'NR==row{$col=""; print $0}')

        if [ "$actual_without_time" != "$expected_without_time" ]
        then
            return 1
        fi
    done

    return 0
}

################################################################################
# END: Private Functions
################################################################################
