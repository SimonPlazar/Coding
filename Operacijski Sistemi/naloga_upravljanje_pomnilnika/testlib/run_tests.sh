#!/usr/bin/env bash

# load test configuration, specific for each task
[[ -f  test_config.sh ]] || {
    echo "ERROR: could not find test_config.sh, are you in a project directory?"
    exit 1
}
[[ -d src ]] || {
    echo "ERROR: could not find src/ folder, are you in a project directory?"
    exit 1
}
[[ -d tests ]] || {
    echo "ERROR: could not find tests/ folder, are you in a project directory?"
    exit 1
}

# load task specific test configuration 
source test_config.sh

if ! [[ -v TEST_VERSION ]]
then
    TEST_VERSION='development'
fi

# clean-up summary folder
if [[ -d summary ]]
then
    rm -r summary/ || {
        echo "could not cleanup summary/ folder"
        exit 1
    }
fi

mkdir summary/ || {
    echo "could not create summary/ folder"
    exit 1
}

cp tests/* -r summary/ || {
    echo "could not copy tests to summary/ folder"
    exit 1
}
cd summary/ || {
    echo "could not move to summary/ folder"
    exit 1
}


# load formating and locatization libraries
source test_format_lib.sh || {
    echo "ERROR: could not source test_format_lib.sh, maybe testlib/ is not added to PATH"
    exit 1
}
source test_localization_lib.sh || {
    echo "ERROR: could not source test_localization_lib.sh, maybe testlib/ is not added to PATH"
    exit 1
}

echo_section "version: ${TEST_VERSION}"

# redirect standard error output from here on out, 
# to give it extra formating
exec 2> >(pipe_stderr_format)

if ! [ -a test_0_checks.sh ]
then
    printf_local 'Could not find %s test. Make sure to run this from the tests/ folder.' test_0_checks.sh >&2
    echo >&2
    sleep 0.1
    exit 1
fi

if ! bash test_0_checks.sh
then
    sleep 0.1
    exit 1    
fi

TEST_FILES=()
TEST_RESULTS=()
TEST_FILENAME_MAX_LEN=0
RETURN_VALUE=0

# Get test files provided as command line arguments if there are any, otherwise
# find all test files in current folder.
if [[ "$#" -gt 0 ]]
then
    for test_file in "$@"
    do
        # Strip directory name from path and keep only file name
        TEST_FILES+=("${test_file##*/}")
    done
else
    TEST_FILES=($(
        find . -regex './test_[0-9]+_.*\.sh' -not -name 'test_0_checks.sh' \
        | sort -t _ -k 2n
    ))
fi

for test_file in "${TEST_FILES[@]}"
do
    bash "${test_file}"
    return_value="$?"
    TEST_RESULTS+=("${return_value}")
    TEST_FILENAME_MAX_LEN=$(("${#test_file}" > "${TEST_FILENAME_MAX_LEN}" \
                              ? "${#test_file}" : "${TEST_FILENAME_MAX_LEN}"))
    RETURN_VALUE=$(("${return_value}" > "${RETURN_VALUE}" \
                     ? "${return_value}" : "${RETURN_VALUE}"))
done

echo_test_title "$(printf_local "TEST RESULTS")"

for i in "${!TEST_FILES[@]}"
do
    printf "%s" "${TEST_FILES[i]}"

    space_count=$(("${TEST_FILENAME_MAX_LEN}" - "${#TEST_FILES[i]}" + 4))
    printf "%${space_count}s"

    if [[ "${TEST_RESULTS[i]}" -eq 0 ]]
    then
        echo_ok "$(printf_local "TEST PASSED")"
    elif [[ "${TEST_RESULTS[i]}" -eq 1 ]]
    then
        echo_warn "$(printf_local "TEST TO BE CHECKED MANUALLY")"
    else
        echo_fail "$(printf_local "TEST FAILED")"
    fi
done

sleep 0.1
if [[ ${RETURN_VALUE} -le 1 ]]
then
	exit 0
else
	exit "${RETURN_VALUE}"
fi
