#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "usage:"
    echo "$0 <path to translations script>"
    exit 1
fi

mapfile -d '' -t translation_keys < <(
grep -e "((?<=printf_local )(['\"]).*?\2)"  . --include="*.sh" --recursive --no-filename --only-matching --perl-regexp --null-data \
    | sort --zero-terminated \
    | uniq --zero-terminated \
)

if ! source "$1"
then
    echo "Could not load translation file." >&2
    exit 1
fi

if ! [[ -v TEST_LOCALIZATIONS ]]
then
    declare -A TEST_LOCALIZATIONS
fi

declare -A USED_TEST_LOCALIZATIONS

echo 
echo "Missing key:"
for k in "${translation_keys[@]}"
do
    k="${k:1:-1}"
    if [[ -v TEST_LOCALIZATIONS["$k"] ]]
    then
        USED_TEST_LOCALIZATIONS[$k]=''
    else
        echo "['${k}']=''"
    fi
done

echo
echo "Unused keys:"
for k in "${!TEST_LOCALIZATIONS[@]}"
do
    if ! [[ -v USED_TEST_LOCALIZATIONS[\'$k\'] ]]
    then

        echo "['${k}']='${TEST_LOCALIZATIONS["$k"]}'"
    fi
done
