#!/bin/bash
# Sets up the ProDG compilers + SCE Runtime Library to build the project.
set -e

TOP=$(cd "$(dirname "$0")"; pwd)/..

# downloads files without checking integrity
download() {
	echo "Downloading $1..."
	wget -qP /tmp $1
}

echo Starting ProDG setup script...

# download required files (registry + SDK package)
download "https://github.com/TheOnlyZac/compilers/releases/download/ee-gcc2.95.2-SN-v2.73a/ee-gcc2.95.2-SN-v2.73a.tar.gz"

# Extract the compiler into the tools dir
echo "Extracting compiler to $TOP/tools..."
tar -xzf /tmp/ee-gcc2.95.2-SN-v2.73a.tar.gz -C $TOP/tools

echo "Removing temporary files..."
rm /tmp/ee-gcc2.95.2-SN-v2.73a.tar.gz

echo "ProDG setup complete!"
