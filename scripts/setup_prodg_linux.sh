#!/bin/bash
# Sets up the ProDG compilers + SCE Runtime Library to build the project.
set -e

PROJECT_DIR="$(dirname "$0")/.."
TOOLS_DIR="$PROJECT_DIR/tools"
DOWNLOAD_URL="https://github.com/TheOnlyZac/compilers/releases/download/ee-gcc2.95.2-SN-v2.73a/ee-gcc2.95.2-SN-v2.73a.tar.gz"

echo "Downloading compiler..."
wget -q -O - "$DOWNLOAD_URL" | tar -xz -C "$TOOLS_DIR"
echo "ProDG setup complete!"
