#!/usr/bin/bash
TESTLIBPATH=$(realpath ./testlib/)
export TESTLIBPATH


[[ -d $TESTLIBPATH ]] || {
    echo "testlib $TESTLIBPATH does not exists, cant setup environment"
    exit 1
}

[[ -f "$TESTLIBPATH/run_tests.sh" ]] || {
    echo "missing testlib/run_tests.sh, cant setup environment"
    exit 1
}
run_tests() {
    bash run_tests.sh "$@"
}
export -f run_tests

if [[ -f "$TESTLIBPATH/check_translations.sh" ]] 
then
    check_translations() {
        bash check_translations.sh "$@"
    }
    export -f check_translations
else
    echo "missing testlib/check_translations.sh, please check your testlib"
fi

if [[ -f "$TESTLIBPATH/package_tasks.sh" ]] 
then
    package_tasks() {
        bash package_tasks.sh "$@"
    }
    export -f package_tasks
else
    echo "missing testlib/check_translations.sh, please check your testlib"
fi

export PATH=$PATH:$TESTLIBPATH
export PYTHONPATH=$PYTHONPATH:$TESTLIBPATH

# this checks if the file has been source
# if it hasn't been, open a new shell
[[ ! $0 = "${BASH_SOURCE[0]}" ]] || {
    bash
}

