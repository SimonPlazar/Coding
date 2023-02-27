#!/usr/bin/env bash

BEGIN_STRACE="mmap(NULL, 0, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = -1 EINVAL"

function run_strace
{
    strace -qq --trace=mmap,munmap "${@}" 2>&1
    exit "${?}"
}
