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

declare -A exp_outputs
declare -A unexp_outputs

exp_outputs["-l -h"]=""
unexp_outputs["-l -h"]="$(cat <<end
e: 1
h: 1
l: 2
o: 1
end
)"
exp_outputs["-ln"]="$(cat <<end
1: 1
2: 1
3: 1
e: 1
h: 1
l: 2
o: 1
end
)"
exp_outputs["-nl"]="${exp_outputs["-ln"]}"
exp_outputs["-n -l"]="${exp_outputs["-ln"]}"
exp_outputs["--letters -n"]="${exp_outputs["-ln"]}"
exp_outputs["-xs 1l"]="$(cat <<end
0x31: 1
0x6c: 2
end
)"
unexp_outputs["-xs 1l"]="$(cat <<end
0x0a: 1
0x32: 1
0x33: 1
0x65: 1
0x68: 1
0x6f: 1
end
)"
exp_outputs["-xl -s 1l"]="${exp_outputs["-xs 1l"]}"
unexp_outputs["-xl -s 1l"]="${unexp_outputs["-xs 1l"]}"

flags_list=(
    "-l -h"
    "-ln"
    "-nl"
    "-n -l"
    "--letters -n"
    "-xs 1l"
    )

# TEST starts here
for flags in "${flags_list[@]}"
do
    echo_section "$(printf_local 'Running: %s' "echo -n \"hello123?\" | ${EXEC} ${flags}")"
    if ! echo -n "hello123?" | "${EXEC_FULL}" ${flags} &> run.output
    then
        echo_fail "$(printf_local 'A non-zero status was returned')"
        TEST_RESULT=2
    fi
    pipe_output_format < run.output
    echo
    printf_local "Looking for expected and incorrect outputs"
    echo

    ALL_FOUND=0
    # referece data is set here
    readarray -t exp_lines < <(echo "${exp_outputs[${flags}]}")
    readarray -t unexp_lines < <(echo "${unexp_outputs[${flags}]}")

    # output is checked here
    for exp_line in "${exp_lines[@]}"
    do
        if [[ -z "${exp_line}" ]]
        then
            continue
        fi
        if ! grep -F "${exp_line}" run.output -q
        then
            echo_fail "$(printf_local "Could not find: %s" "\"${exp_line}\"")"
            TEST_RESULT=2
            ALL_FOUND=1
        fi
    done
    for unexp_line in "${unexp_lines[@]}"
    do
        if [[ -z "${unexp_line}" ]]
        then
            continue
        fi
        if grep -F "${unexp_line}" run.output -q
        then
            echo_fail "$(printf_local "Found incorrect string: %s" "\"${unexp_line}\"")"
            TEST_RESULT=2
            ALL_FOUND=1
        fi
    done
    if [ ${ALL_FOUND} == 0 ]
    then
        echo_ok "$(printf_local "Output verified")"
    fi
done
echo_warn "$(printf_local 'The outputs will be checked manually.')"

exit ${TEST_RESULT}
