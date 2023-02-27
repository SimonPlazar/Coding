#!/usr/bin/bash


source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'printing a list of failed jobs,'; echo
printf_local 'checking the output of jobs (tested indirectly)'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

cat > posel_p1.sh <<end
#!/bin/bash
echo Ok
end

cat > posel_p2.sh <<end
#!/bin/bash
echo Fail
end

cat > posel_p3.sh <<end
#!/bin/bash
echo Ok
echo other things go here
echo Fail
end

cat > posel_p4.sh <<end
#!/bin/bash
echo "hello world!!!"
echo "hello world!!!"
echo "hello world!!!"
echo Fail
echo Ok
end

echo_section "$(printf_local 'Running %s' "${EXEC}")"
if ! bash "$EXEC_FULL" &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=1
fi
pipe_output_format < run.output


echo_section "$(printf_local 'Looking for %s in output:' "(\"posel_p2.sh\", \"posel_p3.sh\")")"
if ! tail -n 10 run.output | grep "posel_p[23]\.sh" -B 2 -A 2 --color
then
    echo_fail "$(printf_local 'Did not find expected string in result')"
    TEST_RESULT=1
else
    echo_ok "$(printf_local 'The expected string was found')"
    echo_warn "$(printf_local 'Correctness will be checked manually')"
fi

exit ${TEST_RESULT}
