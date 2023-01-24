#!/usr/bin/env bash

set -exu

# where this .sh file lives
DIRNAME=$(dirname "$0")
SCRIPT_DIR=$(cd "$DIRNAME" || exit 1; pwd)

export RIOTBASE="${SCRIPT_DIR}/riot"
export EXTERNAL_BOARD_DIRS="${SCRIPT_DIR}/ladybug/boards"

