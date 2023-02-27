#!/usr/bin/bash

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running with individual long flags'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

echo_section "$(printf_local 'Running: %s' "${EXEC} --help")"
if ! "${EXEC_FULL}" -h &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=2
fi
pipe_output_format < run.output
echo

declare -A ref_outputs
ref_outputs["--letters"]="$(cat <<end
b: 1
d: 1
e: 1
g: 1
o: 2
y: 1
end
)"

ref_outputs["--numbers"]="$(cat <<end
7: 1
8: 1
9: 2
end
)"

ref_outputs["--hex"]="$(cat <<end
0x20: 2
0x37: 1
0x38: 1
0x39: 2
0x3f: 3
0x62: 1
0x64: 1
0x65: 1
0x67: 1
0x6f: 2
0x79: 1
end
)"

ref_outputs["--select e8l"]="$(cat <<end
e: 1
8: 1
l: 0
end
)"

for flags in --letters --numbers --hex "--select e8l"
do
    echo_section "$(printf_local 'Running: %s' "echo -n \"goodbye 9987 ???\" | ${EXEC} $flags")"
    if ! echo -n "goodbye 9987 ???" | "${EXEC_FULL}" $flags &> run.output
    then
        echo_fail "$(printf_local 'A non-zero status was returned')"
        TEST_RESULT=2
    fi
    pipe_output_format < run.output
    echo
    printf_local "Looking for expected outputs"
    echo

    ALL_FOUND=0
    readarray -t exp_lines < <(echo "${ref_outputs["${flags}"]}")
    for exp_line in "${exp_lines[@]}"
    do
        if ! grep -F "${exp_line}" run.output -q
        then
            echo_fail "$(printf_local "Could not find: %s" "\"${exp_line}\"")"
            TEST_RESULT=2
            ALL_FOUND=1
        fi
    done
    if [ ${ALL_FOUND} == 0 ]
    then
        echo_ok "$(printf_local "Found all expected outputs")"
    fi
done

echo_warn "$(printf_local 'The outputs will be checked manually.')"

exit ${TEST_RESULT}
