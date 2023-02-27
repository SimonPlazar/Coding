#!/usr/bin/bash

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running jobs within their path'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

mkdir "A/"
cat > "A/posel_A.sh" <<end
#!/bin/bash
pwd
echo Ok
end

echo_section "$(printf_local 'Running %s' "${EXEC}")"
if ! bash "$EXEC_FULL" &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=1
fi
pipe_output_format < run.output

if ! [ -a "A/posel_A.out" ] 
then
    echo_fail "$(printf_local 'Missing output file %s.' \"A/posel_A.out\")"
    TEST_RESULT=1
else
    expected_working_dir=$(pwd)/A
    working_dir=$(head -n 1  A/posel_A.out)

    if ! [ "${expected_working_dir}" -ef "${working_dir}" ]
    then
        echo_fail "$(printf_local 'Working directory: %s does not match expected %s.' "\"${working_dir}\"" "\"${expected_working_dir}\"")"
        TEST_RESULT=1
    fi
fi

echo_ok "$(printf_local 'Test was successful')"

exit ${TEST_RESULT}
