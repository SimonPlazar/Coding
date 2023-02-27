#!/usr/bin/env bash

tasks=(
    naloga_bash
    naloga_cmd
    )

if [[ -d $1 ]]
then
    tasks=("$1")
fi


for task in "${tasks[@]}"
do
    if ! [[ -d $task ]] 
    then
        echo "missing task: $task"
        continue
    fi

    tmpdir=$(mktemp -d tmp_XXX) || {
        echo "could not create temporary directory"
        exit 1
    }

    cp -r "$task" "$tmpdir"
    cp -r testlib/ "$tmpdir/$task"
    cp activate.sh "$tmpdir/$task"

    cd "$tmpdir" || {
        echo "cannot move to temporary directory: $tmpdir"
        exit 1
    }

    zip "$task.zip" -r "$task" \
        --exclude "*__pycache__/*"\
        --exclude "*summary/*"\
        --exclude "*build/*"\
        --exclude "*exec/*"

    unzip -l "$task.zip" 

    if [[ -f "../$task.zip" ]]
    then
        echo "pakage already exists: $task.zip"
    else
        mv "$task.zip" ../ 
    fi

    cd ..
    rm -r "$tmpdir" || {
        echo "could not clean temporary directory: $tmpdir"
        exit 1
    }
done
