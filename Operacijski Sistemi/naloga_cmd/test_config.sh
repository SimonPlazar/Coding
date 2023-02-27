#!/usr/bin/bash
TEST_LOCALIZATIONS_FILE="$(realpath ./tests/test_localizations_slo.sh)"
EXEC="${EXEC:-$(realpath ./exec/countbytes)}"
export TEST_LOCALIZATIONS_FILE
export EXEC
