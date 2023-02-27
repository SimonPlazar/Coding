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

cp tests/* -r summary/
cd summary/


# load formating and locatization libraries
source test_format_lib.sh || {
    echo "ERROR: could not source test_format_lib.sh, maybe testlib/ is not added to PATH"
    exit 1
}
source test_localization_lib.sh || {
    echo "ERROR: could not source test_localization_lib.sh, maybe testlib/ is not added to PATH"
    exit 1
}

# redirect standard error output from here on out, 
# to give it extra formating
exec 2> >(pipe_stderr_format)

TEST_RESULT=0

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

# Get test files provided as command line arguments if there are any, otherwise
# find all test files in current folder.
if [[ "$#" -gt 0 ]]
then
    for test_file in "$@"
    do
        # Strip directory name from path and keep only file name
        test_files+=("${test_file##*/}")
    done
else
    test_files=($(
        find . -regex './test_[0-9]+_.*\.sh' -not -name 'test_0_checks.sh' \
        | sort -t _ -k 2n
    ))
fi

for test_file in "${test_files[@]}"
do
    bash "${test_file}"
    TEST_RESULT="$(($?||TEST_RESULT))"
done

if [[ ${TEST_RESULT} != 0 ]]
then
    echo_fail "$(printf_local "One or more tests failed")"
fi

sleep 0.1
exit "${TEST_RESULT}"
