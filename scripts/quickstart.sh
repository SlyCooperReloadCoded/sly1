#!/bin/bash

set -e

# Get script directory
script_dir=$(dirname $0)
pushd $script_dir > /dev/null

pip install -U -r ../requirements.txt

# Elevate privileges
sudo -v

# Check if sudo
if [ "$EUID" -ne 0 ]
  then echo "Installing dependencies requires sudo. Please enter your password."
fi

# Update apt packages
sudo apt-get update

# Setup wine
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install -y wine32

# Install MIPS assembler
sudo apt-get install -y binutils-mips-linux-gnu

# Install Ninja build system
sudo apt-get install -y ninja-build

# Setup compiler
./setup_prodg_linux.sh

# Check if disc/SCUS_971.98 exists
echo "Setup complete!"
if [ ! -f ../disc/SCUS_971.98 ]; then
  echo "Now, copy SCUS_971.98 from your copy of the game to the 'disc' directory of this project."
fi
echo "To build the project, run the 'build.sh' script."

popd > /dev/null
