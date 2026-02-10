#!/bin/bash
set -e

PROJECT_DIR="$(dirname "$0")/.."

# Ensure disc/SCUS_971.98 exists
if [ ! -f "$PROJECT_DIR/disc/SCUS_971.98" ]; then
    echo "Error: SCUS_971.98 not found. Copy it from your own game disc to the 'disc' directory of this project." >&2
    exit 1
fi

pushd $PROJECT_DIR > /dev/null
trap "popd > /dev/null" EXIT

if [ -z "$VIRTUAL_ENV" ]; then
    source "env/bin/activate"
fi
python3 "configure.py" --clean
ninja
