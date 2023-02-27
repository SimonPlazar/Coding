#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - running two process"; echo
printf_local "  - the input, output and standard error"; echo
printf_local "  - return value on success and failure"; echo

################################################################################
# Init
################################################################################
#

if [[ ! -v VALGRIND ]]
then
    VALGRIND=""
    echo_warn "$(printf_local "Could not find valgrind, test will be incomplete.")"
fi

cat > in.txt <<end
3 three
2 two
5 five
4 four
1 one
end

subtest_titles=(
    "pipeline of two commands"
    "error in first command"
    "error in second command"
    "first command invalid"
    "second command invalid"
    )

cmd_list=(
    "grep f \nsort"
    "grep f --not-a-flag \nsort"
    "grep f \nsort --not-a-flag "
    "invalid_command f \nsort"
    "grep f \ninvalid_command"
)

{ cat in.txt | grep f | sort; } 2>err1_ref.txt >out1_ref.txt
{ cat in.txt | grep f --not-a-flag | sort; } 2>err2_ref.txt >out2_ref.txt
{ cat in.txt | grep f | sort --not-a-flag; } 2>err3_ref.txt >out3_ref.txt
{ cat in.txt | invalid_command f | sort; } 2>err4_ref.txt >out4_ref.txt
{ cat in.txt | grep f | invalid_command; } 2>err5_ref.txt >out5_ref.txt


input_list=(
    in.txt
    in.txt
    in.txt
    in.txt
    in.txt
)
output_ref_list=(
    out1_ref.txt
    out2_ref.txt
    out3_ref.txt
    out4_ref.txt
    out5_ref.txt
)

error_ref_list=(
    err1_ref.txt
    err2_ref.txt
    err3_ref.txt
    ""
    ""
)

status_ref_list=(
    0
    2
    ""
    255
    255
)

manual_check_list=(
    ""
    ""
    ""
    ""
    ""
)

#
################################################################################
# Sub-tests
################################################################################

for n in $(seq "${#subtest_titles[@]}")
do
    i=$((n-1)) # seq starts with 1 and includes end

    sub_title="${subtest_titles[$i]}"
    cmd="${cmd_list[$i]}"
    input=${input_list[$i]}
    out_ref=${output_ref_list[$i]}
    err_ref=${error_ref_list[$i]}
    status_ref=${status_ref_list[$i]}
    manual_check=${manual_check_list[$i]}

    out_file="out${n}.txt"
    err_file="error${n}.txt"

    print_subtest_title "$(printf_local "${sub_title}")"

    printf_local "pipeline commands:"; echo
    echo -e "${cmd}"
    echo

    echo -e "${cmd}" | $VALGRIND "${EXEC}" -i "${input}" -o "$out_file" -e "$err_file" &> pipe_output
    status=$?
    pipe_output_format < pipe_output
    echo

    if [[ -n "${manual_check}" ]]
    then
        ## manual check routine
        printf_local "pipeline input:"; echo
        cat "${input}"
        echo

        manual_out_err_status "$out_file" "$out_ref" "$err_file" "$err_ref" "$status" "$status_ref"

    else
        # automatic check routine
        check_out_err_status "$out_file" "$out_ref" "$err_file" "$err_ref" "$status" "$status_ref"
    fi

done

print_footer

exit "$TEST_RESULT"
