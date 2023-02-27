#!/usr/bin/bash

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running without flags'; echo
printf_local 'running with individual short flags'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

echo_section "$(printf_local 'Running: %s' "${EXEC} -h")"
if ! "${EXEC_FULL}" -h &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=2
fi
pipe_output_format < run.output
echo

declare -A ref_outputs
ref_outputs[" "]="$(cat <<end
 : 2
1: 2
2: 1
3: 1
d: 1
e: 1
h: 1
l: 3
o: 2
r: 1
w: 1
end
)"

ref_outputs["-l"]="$(cat <<end
d: 1
e: 1
h: 1
l: 3
o: 2
r: 1
w: 1
end
)"

ref_outputs["-n"]="$(cat <<end
1: 2
2: 1
3: 1
end
)"

ref_outputs["-x"]="$(cat <<end
0x20: 2
0x31: 2
0x32: 1
0x33: 1
0x64: 1
0x65: 1
0x68: 1
0x6c: 3
0x6f: 2
0x72: 1
0x77: 1
end
)"

ref_outputs["-s lwz1"]="$(cat <<end
l: 3
w: 1
z: 0
1: 2
end
)"

for flags in ' ' -l -n -x "-s lwz1"
do
    echo_section "$(printf_local 'Running: %s' "echo -n \"hello world 1123\" | ${EXEC} $flags")"
    if ! echo -n "hello world 1123" | "${EXEC_FULL}" $flags &> run.output
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
