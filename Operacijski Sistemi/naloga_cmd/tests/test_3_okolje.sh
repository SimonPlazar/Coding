#!/usr/bin/bash

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running with environmental variable set'; echo
printf_local 'running with flag and environmental variable set'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

echo_section "$(printf_local 'Running: %s' "echo -n \"banana\" | SELECT=ba ${EXEC}")"
if ! echo -n "banana" | SELECT=ba "${EXEC_FULL}" &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=2
fi
pipe_output_format < run.output
echo
printf_local "Looking for expected and incorrect outputs"
echo

ALL_FOUND=0
readarray -t exp_lines <<end
b: 1
a: 3
end
readarray -t unexp_lines <<end
n: 2
end
for exp_line in "${exp_lines[@]}"
do
    if ! grep -F "${exp_line}" run.output -q
    then
        echo_fail "$(printf_local "Could not find: %s" "\"${exp_line}\"")"
        TEST_RESULT=2
        ALL_FOUND=1
    fi
done
for unexp_line in "${unexp_lines[@]}"
do
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

echo_section "$(printf_local 'Running: %s' "echo -n \"banana\" | SELECT=bn ${EXEC} -s bn")"
if ! echo -n "banana" | SELECT=bn "${EXEC_FULL}" -s bn &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=2
fi
pipe_output_format < run.output
echo
printf_local "Looking for expected and incorrect outputs"
echo

ALL_FOUND=0
readarray -t exp_lines <<end
b: 1
n: 2
end
readarray -t unexp_lines <<end
a: 3
end
for exp_line in "${exp_lines[@]}"
do
    if ! grep -F "${exp_line}" run.output -q
    then
        echo_fail "$(printf_local "Could not find: %s" "\"${exp_line}\"")"
        TEST_RESULT=2
        ALL_FOUND=1
    fi
done
for unexp_line in "${unexp_lines[@]}"
do
    if grep -F "${unexp_line}" run.output -q
    then
        echo_fail "$(printf_local "Found incorrect string: %s" "\"${exp_line}\"")"
        TEST_RESULT=2
        ALL_FOUND=1
    fi
done
if [ ${ALL_FOUND} == 0 ]
then
    echo_ok "$(printf_local "Output verified")"
fi

echo_warn "$(printf_local 'The outputs will be checked manually.')"

exit ${TEST_RESULT}
