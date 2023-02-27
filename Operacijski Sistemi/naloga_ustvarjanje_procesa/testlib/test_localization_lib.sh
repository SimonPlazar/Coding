#!/usr/bin/bash

if [ -v TEST_LOCALIZATIONS_FILE ]
then
    source "$TEST_LOCALIZATIONS_FILE"
else
    declare -A TEST_LOCALIZATIONS
fi


printf_local () {
    str=$1
    shift
    if [[ -v TEST_LOCALIZATIONS["$str"] ]]
    then
        str=${TEST_LOCALIZATIONS["$str"]}
    elif [ -v TEST_DEBUG ]
    then
        echo "missing translation: ${str}" >&2
    fi
    printf "$str" "$@"
}
