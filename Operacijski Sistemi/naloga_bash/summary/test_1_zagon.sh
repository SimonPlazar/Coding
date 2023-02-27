#!/usr/bin/bash

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running jobs in the current path and subpaths,'; echo
printf_local 'not running jobs with incorrect names,'; echo
printf_local 'running jobs with correctly matching names,'; echo
printf_local 'running jobs with hashbang comment present'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

mkdir -p A/posel_mapa/
touch flag.out
FLAG_FILE="$(realpath flag.out)" || exit 1

cat > posel_p1.sh <<end
#!/bin/bash
echo 1 >> "${FLAG_FILE}"
echo Ok
end

cat > A/posel_p2.sh <<end
#!/bin/bash
echo 2 >> "${FLAG_FILE}"
echo Ok
end

cat > A/posel_mapa/posel_p3.sh <<end
#!/bin/bash
echo 3 >> "${FLAG_FILE}"
echo Ok
end

cat > A/niposel_p4.sh <<end
#!/bin/bash
echo 4 >> "${FLAG_FILE}"
echo Ok
end

cat > posel_p5.sh <<end
# komentar tukaj ne bo na pravem mestu, posel se ne sme zagnati
echo 5 >> "${FLAG_FILE}"
#!/bin/bash 
echo Ok
end


echo_section "$(printf_local 'Running %s' "${EXEC}")"
if ! bash "$EXEC_FULL" &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=1
fi
pipe_output_format < run.output
echo

if ! grep "^1$" flag.out -q
then
    echo_fail "$(printf_local 'Job with a matching name was not run: %s' "posel_p1.sh")"
    TEST_RESULT=1
fi

if ! grep "^2$" flag.out -q
then
    echo_fail "$(printf_local 'Job with a matching name was not run: %s' "A/posel_p2.sh")"
    TEST_RESULT=1
fi

if ! grep "^3$" flag.out -q
then
    echo_fail "$(printf_local 'Job with a matching name was not run: %s' "A/b/posel_p3.sh")"
    TEST_RESULT=1
fi

if grep "^4$" flag.out -q
then
    echo_fail "$(printf_local 'Job with a non-matching name was run: %s' "A/niposel_p4.sh")"
    TEST_RESULT=1
fi

if grep "^5$" flag.out -q
then
    echo_fail "$(printf_local 'Job without the expected hashbang comment was run: %s' "posel_5.sh")"
    TEST_RESULT=1
fi

if [ "${TEST_RESULT}" == 0 ]
then
    echo_ok "$(printf_local 'Test was successful')"
fi

exit ${TEST_RESULT}
