#!/usr/bin/bash
TEST_LOCALIZATIONS_FILE="$(realpath ./test_localizations_slo.sh)"
EXEC="${EXEC:-../exec/pipeline}"
export TEST_LOCALIZATIONS_FILE
export EXEC
