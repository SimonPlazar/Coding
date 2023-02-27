#!/usr/bin/env bash
TEST_LOCALIZATIONS_FILE="$(realpath ./tests/test_localizations_slo.sh)"
EXEC="${EXEC:-$(realpath ./exec/listproc)}"
export TEST_LOCALIZATIONS_FILE
export EXEC
export TEST_VERSION='v1.4'
