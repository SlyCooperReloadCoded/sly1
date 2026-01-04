#!/bin/bash
set -e

PROJECT_DIR="$(dirname "$0")/.."

pushd $PROJECT_DIR > /dev/null
trap "popd > /dev/null" EXIT

source "env/bin/activate"
python3 "configure.py" --clean && ninja
python3 "configure.py" --clean --objects && ninja

# Output the progress report to a file if --report is not passed, otherwise discard it.
if [[ "$1" == "--report" ]]; then
    ./tools/objdiff/objdiff-cli report generate > report.json
else
    ./tools/objdiff/objdiff-cli report generate > /dev/null
fi
