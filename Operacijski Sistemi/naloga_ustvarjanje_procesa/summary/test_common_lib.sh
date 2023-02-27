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

check () {
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
        echo "${actual_output}" | pipe_output_format 
        printf_local "Expected output:"; printf "\n"
        echo "${expected_output}" | pipe_format_wordwrap 

        update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else
        printf_local "Actual output:"; printf "\n"
        echo "${actual_output}" | pipe_output_format
        printf_local "Expected output:"; printf "\n"
        echo "${expected_output}" | pipe_format_wordwrap
        
        update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

check_diff () {
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

        update_test_result 0
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else
        printf_local "Diff between actual and expected outputs:"; printf "\n"
        diff -y --left-column --expand-tabs --tabsize 4 --width 80 --color=always <(echo "$actual_output") <(echo "$expected_output") | cat -n | grep -v -e '($' | head

        update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

check_status () {
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
        update_test_result 1
        echo_warn "$(printf_local "SUBTEST TO BE CHECKED MANUALLY")"
    else
        update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

check_out_err_status () {
    local actual_output="$1"
    local expected_output="$2"
    local actual_error="$3"
    local expected_error="$4"
    local actual_exit_status="$5"
    local expected_exit_status="$6"
    local failed_flag=0

    if [[ -e "$expected_output" ]] \
    && ! cmp -s "$actual_output" "$expected_output"
    then
        echo_fail "$(printf_local "standard output doesn't match expected")"
        printf_local "Diff between actual and expected outputs:"; printf "\n"
        diff -y --left-column --expand-tabs --tabsize 4 --width 80 --color=always "$actual_output"  "$expected_output" | cat -n | grep -v -e '($' | head
        update_test_result 2
        failed_flag=1
    fi
    if [[ -e $expected_error ]] \
    && ! cmp -s "$actual_error" "$expected_error"
    then
        echo_fail "$(printf_local "standard error doesn't match expected")"
        printf_local "Diff between actual and expected errors:"; printf "\n"
        diff -y --left-column --expand-tabs --tabsize 4 --width 80 --color=always "$actual_error"  "$expected_error" | cat -n | grep -v -e '($' | head
        update_test_result 2
        failed_flag=1
    fi
    if [[ -n $expected_exit_status ]] \
    && [[ "$actual_exit_status" -ne "$expected_exit_status" ]] 
    then
        echo_fail "$(printf_local "exit status does not match")"
        printf_local "Actual exit status: %s" "$actual_exit_status"; echo
        printf_local "Expected exit status: %s" "$expected_exit_status"; echo 
        update_test_result 2
        failed_flag=1
    fi
    if [[ $failed_flag == 0 ]]
    then 
        echo_ok "$(printf_local "SUBTEST PASSED")"
    else
        echo_fail "$(printf_local "SUBTEST FAILED")"
    fi
}

manual_out_err_status () {
    local actual_output="$1"
    local expected_output="$2"
    local actual_error="$3"
    local expected_error="$4"
    local actual_exit_status="$5"
    local expected_exit_status="$6"

    if [[ -e "$expected_output" ]]
    then
        printf_local "pipeline output:"; echo
        cat "$actual_output"
        echo
        printf_local "expected output:"; echo
        cat "$expected_output"
        echo
    fi

    if [[ -e "$expected_error" ]]
    then
        printf_local "pipeline error:"; echo
        cat "$actual_error"
        echo
        printf_local "expected error:"; echo
        cat "$expected_error"
        echo
    fi

    if [[ -n "$expected_exit_status" ]] \
    && [[ "$actual_exit_status" -ne "$expected_exit_status" ]] 
    then
        echo_fail "$(printf_local "exit status does not match")"
        printf_local "Actual exit status: %s" "$status"; echo
        printf_local "Expected exit status: %s" "$status_ref"; echo
        update_test_result 2
        echo_fail "$(printf_local "SUBTEST FAILED")"
    else
        update_test_result 1
        echo_warn "$(printf_local "SUBTEST TO BE CHECKED MANUALLY")"
    fi

}

update_test_result () {
        TEST_RESULT=$(($1 > "${TEST_RESULT}" ? $1 : "${TEST_RESULT}"))
}

print_subtest_title () {
    SUBTEST_COUNT=$((SUBTEST_COUNT + 1))
    local title="$(printf_local "Subtest") ${SUBTEST_COUNT}: $1"

    printf "\n%s\n" "${title}"
    printf -- "-%.0s" $(seq 1 ${#title}); printf "\n"
}

print_footer () {
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
