#!/usr/bin/env bash

PROG_AB_NAME="prog__AB"
PROG_C_NAME="prog  C"
PROG_A_DIR="./bin/path_A/"
PROG_B_DIR="./bin/path_B/"
PROG_C_DIR="./bin/path_C/"

function init_common
{
    local prog_A_source="#include <unistd.h>
                         int main() { for (volatile unsigned long long int i=0; i<100000000000; ) { }; return 0; }"

    local prog_B_source="#include <stdlib.h>
                         #include <unistd.h>
                         int main() { char *t = malloc(1024); pause(); free(t); return 0; }"

    local prog_C_source="#include <stdlib.h>
                         #include <unistd.h>
                         int main() { char *t = malloc(1024 * 1024); pause(); free(t); return 0; }"

    mkdir -p "${PROG_A_DIR}"
    mkdir -p "${PROG_B_DIR}"
    mkdir -p "${PROG_C_DIR}"

    echo "${prog_A_source}" | gcc -x c -o "${PROG_A_DIR}${PROG_AB_NAME}" -
    echo "${prog_B_source}" | gcc -x c -o "${PROG_B_DIR}${PROG_AB_NAME}" -
    echo "${prog_C_source}" | gcc -x c -o "${PROG_C_DIR}${PROG_C_NAME}" -

    # A1: -c "prog__AB" -d ./bin/        -e ./bin/path_A/prog__AB
    # A2: -c "prog__AB" -d ./bin/path_A/ -e ./bin/path_A/prog__AB
    # B1: -c "prog__AB" -d ./bin/        -e ./bin/path_B/prog__AB
    # B2: -c "prog__AB" -d ./bin/path_B/ -e ./bin/path_B/prog__AB
    # C1: -c "prog  C"  -d ./bin/        -e ./bin/path_C/"prog  C"
    # C2: -c "prog  C"  -d ./bin/path_C/ -e ./bin/path_C/"prog  C"

    (cd "$(dirname ${PROG_A_DIR})" && exec "./$(basename ${PROG_A_DIR})/${PROG_AB_NAME}") &
    PID_A1="$!"
    (cd "${PROG_A_DIR}" && exec "./${PROG_AB_NAME}") &
    PID_A2="$!"
    (cd "$(dirname ${PROG_B_DIR})" && exec "./$(basename ${PROG_B_DIR})/${PROG_AB_NAME}") &
    PID_B1="$!"
    (cd "${PROG_B_DIR}" && exec "./${PROG_AB_NAME}") &
    PID_B2="$!"
    (cd "$(dirname ${PROG_C_DIR})" && exec "./$(basename ${PROG_C_DIR})/${PROG_C_NAME}") &
    PID_C1="$!"
    (cd "${PROG_C_DIR}" && exec "./${PROG_C_NAME}") &
    PID_C2="$!"
}

function deinit_common
{
    pkill -f "${PROG_AB_NAME}"
    pkill -f "${PROG_C_NAME}"

    if [ -d "$(dirname "${PROG_A_DIR}")" ]; then rm -r "$(dirname "${PROG_A_DIR}")"; fi
    if [ -d "$(dirname "${PROG_B_DIR}")" ]; then rm -r "$(dirname "${PROG_B_DIR}")"; fi
    if [ -d "$(dirname "${PROG_C_DIR}")" ]; then rm -r "$(dirname "${PROG_C_DIR}")"; fi
}

function get_expected_output
{
    local pid_list="$1"
    local expected_output
    expected_output=$(ps -e -q "${pid_list}" -o pid:1=,state:1=,vsize:1=,comm:1=\
        | awk -F '[ ]' '{$3=$3*1024; print}'\
        | sed -e 's/ /:/' -e 's/ /:/' -e 's/ /:/')
    echo "${expected_output}"
}
