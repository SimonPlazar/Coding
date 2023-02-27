#!/usr/bin/env bash

TOLERANCE_POS=2
TOLERANCE=1

function build_cmd
{
    echo "echo $1 \$(date +%s)"
}
