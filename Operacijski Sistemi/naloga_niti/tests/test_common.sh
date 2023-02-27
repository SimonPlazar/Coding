#!/usr/bin/env bash

function server_start
{
    pkill -SIGKILL -f "${EXEC_SERVER}"
    pkill -SIGKILL -f "${EXEC_CLIENT}"

    "${EXEC_SERVER}" 1> /dev/null 2> /dev/null &
    SERVER_PID="${!}"
    sleep 0.5
}

function server_stop
{
    kill "${SERVER_PID}"
    sleep 0.5
}
