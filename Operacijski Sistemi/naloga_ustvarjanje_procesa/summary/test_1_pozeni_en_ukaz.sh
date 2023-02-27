#!/usr/bin/env bash

source test_common_lib.sh
source test_format_lib.sh
source test_localization_lib.sh

################################################################################
# Header
################################################################################

echo_test_title "$0"; echo
printf_local "This test checks:"; echo
printf_local "  - running a single process"; echo
printf_local "  - with an absolute program path"; echo
printf_local "  - running a command in system PATH"; echo
printf_local "  - with and without arguments"; echo
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

cat > my_file <<end
echo "you're not supposed to execute this"
end

echo "hello" > in.txt
echo "world" >> in.txt
echo "!" >> in.txt


cmd_abs_path="$(which cat)" || {
    { printf_local "could not locate command cat"; echo; } >&2
    exit 2
}

subtest_titles=(
    "absolute path"
    "with arguments"
    "program in PATH"
    "failure"
    "wrong path"
    "not executable"
    )

cmd_list=(
    "${cmd_abs_path}"
    "${cmd_abs_path} -b"
    "cat -b"
    "cat -1"
    "./qwert"
    "./my_file"
)

cat in.txt | cat -b > out1_ref.txt
touch empty.txt
cat in.txt | cat -1 2> err1_ref.txt 1>/dev/null

{ printf_local "Expected a warning that the path does not exists."; echo; } > err2_ref.txt
{ printf_local "Expected a warning that the path is not executable."; echo; } > err3_ref.txt

input_list=(
    in.txt
    in.txt
    in.txt
    in.txt
    in.txt
    in.txt
)
output_ref_list=(
    in.txt
    out1_ref.txt
    out1_ref.txt
    empty.txt
    ""
    ""
)

error_ref_list=(
    ""
    ""
    ""
    err1_ref.txt
    err2_ref.txt
    err3_ref.txt
)

status_ref_list=(
    0
    0
    0
    1
    255
    255
)

manual_check_list=(
    ""
    ""
    ""
    ""
    T
    T
)


#
################################################################################
# Sub-tests
################################################################################

for n in $(seq "${#subtest_titles[@]}")
do
    n=$((n-1)) # seq starts with 1 and includes end

    sub_title="${subtest_titles[$n]}"
    cmd="${cmd_list[$n]}"
    input=${input_list[$n]}
    out_ref=${output_ref_list[$n]}
    err_ref=${error_ref_list[$n]}
    status_ref=${status_ref_list[$n]}
    manual_check=${manual_check_list[$n]}

    print_subtest_title "$(printf_local "${sub_title}")"

    printf_local "pipeline commands:"; echo
    echo "${cmd}"
    echo

    echo "${cmd}" | $VALGRIND "${EXEC}" -i "${input}" -o out.txt -e error.txt &> pipe_output
    status=$?
    pipe_output_format < pipe_output
    echo

    if [[ -n "${manual_check}" ]]
    then
        ## manual check routine
        printf_local "pipeline input:"; echo
        cat "${input}"
        echo

        manual_out_err_status out.txt "$out_ref" error.txt "$err_ref" "$status" "$status_ref"

    else
        # automatic check routine
        check_out_err_status out.txt "$out_ref" error.txt "$err_ref" "$status" "$status_ref"
    fi

done

print_footer

exit "$TEST_RESULT"
