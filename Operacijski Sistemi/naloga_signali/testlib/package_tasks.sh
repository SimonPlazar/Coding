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
    # if task contains a trailing / this removes it
    task=$(basename "${task}")

    # check the current tag, if it's not the latest commit create a new one
    echo "Checking version via latest git tag"
    git_tag=$(git describe --tag --long osnova) || {
        echo "error reading latest git tag"
        exit 1
    }
    if [[ $git_tag =~ ^v([0-9]+)\.([0-9]+)-([0-9]+)-[a-z0-9]+$ ]]
    then
        major_version=${BASH_REMATCH[1]}
        minor_version=${BASH_REMATCH[2]}
        commits_since_tagged=${BASH_REMATCH[3]}

        if [[ $commits_since_tagged -gt 0 ]] 
        then
            echo "the latest commit is not tagged, creating new version tag"
            minor_version=$((minor_version+1))
            git tag "v${major_version}.${minor_version}" osnova || {
                echo "tagging latest commit failed"
                exit 1
            }
        else
            echo "latest commit is tagged and versioned"
        fi
    else
        echo "git tag '$git_tag' doesn't match expected pattern: v<minor>.<major>-<commits since>-<commit>"
        exit 1
    fi
    echo

    tmpdir=$(mktemp -d tmp_XXX) || {
        echo "could not create temporary directory"
        exit 1
    }

    git clone . --branch osnova "$tmpdir"
    cd "$tmpdir" || {
        echo "cannot move to temporary directory: $tmpdir"
        exit 1
    }
    cp -r testlib/ "$task"
    cp activate.sh "$task"

    echo "export TEST_VERSION='v${major_version}.${minor_version}'" >> "$task/test_config.sh"

    zip "$task.zip" -r "$task"

    if [[ -f "../$task.zip" ]]
    then
        echo "pakage already exists: $task.zip"
    else
        mv "$task.zip" ../ 
    fi

    cd ..
    rm -rf "$tmpdir/.git/" || {
        echo "could not clean temporary repository clone in: $tmpdir"
        exit 1
    }
    rm -r "$tmpdir" || {
        echo "could not clean temporary directory: $tmpdir"
        exit 1
    }
done
