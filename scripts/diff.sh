#!/bin/bash
set -e

if [ -z "$1" ]; then
	echo "Usage: $0 FunctionName [ObjectName]" >&2
	exit 1
fi

cd "$(dirname "$0")/.."
source env/bin/activate
python3 configure.py --objects
ninja

if [ -n "$2" ]; then
	./tools/objdiff/objdiff-cli diff --project . -u "$2" "$1"
else
	./tools/objdiff/objdiff-cli diff --project . "$1"
fi
