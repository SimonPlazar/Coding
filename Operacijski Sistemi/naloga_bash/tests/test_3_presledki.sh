#!/usr/bin/bash

# test preveri:
# zagon poslov s presledki v poti ali imenu

source test_format_lib.sh
source test_localization_lib.sh

echo_test_title "$0"
printf_local 'This test checks:'; echo
printf_local 'running jobs with spaces in path and file names'; echo

if ! TMP_DIR=$(mktemp -d test_dir_XXX)
then
    printf_local "Creating temporary directory failed." >&2
    exit 1
fi

TEST_RESULT=0
EXEC_FULL="$(realpath "$EXEC")" || exit 1
cd "${TMP_DIR}" || exit 1

echo_section "$(printf_local 'Setting up test folder %s' "${TMP_DIR}")"

mkdir "A B"
mkdir "AB"
cat > "A B/posel_AB.sh" <<end
#!/bin/bash
echo "... ... ..."
echo Ok
end
cat > "AB/posel_A B.sh" <<end
#!/bin/bash
echo "..........."
echo Ok
end

cat > ref_AB.out <<end
... ... ...
Ok
end
cat > "ref_A B.out" <<end
...........
Ok
end

echo_section "$(printf_local 'Running %s' "${EXEC}")"
if ! bash "$EXEC_FULL" &> run.output
then
    echo_fail "$(printf_local 'A non-zero status was returned')"
    TEST_RESULT=1
fi
pipe_output_format < run.output

echo_section "$(printf_local 'Comparing output with reference')"
printf_local 'output:'
cat "AB/posel_A B.out"
echo
printf_local 'reference:'
cat "ref_A B.out"
echo
if ! ( [ -a "AB/posel_A B.out" ] && cmp "ref_A B.out" "AB/posel_A B.out" )
then
    echo_fail "$(printf_local 'Output differs from reference.')"
    TEST_RESULT=1
else
    echo_ok "$(printf_local 'Output matches the reference.')"
fi

echo_section "$(printf_local 'Comparing output with reference')"
echo "output:"
cat "A B/posel_AB.out"
echo
echo "reference:"
cat "ref_AB.out"
echo
if ! ( [ -a "A B/posel_AB.out" ] && cmp "ref_AB.out" "A B/posel_AB.out" )
then
    echo_fail "$(printf_local 'Output differs from reference.')"
    TEST_RESULT=1
else
    echo_ok "$(printf_local 'Output matches the reference.')"
fi




exit ${TEST_RESULT}
