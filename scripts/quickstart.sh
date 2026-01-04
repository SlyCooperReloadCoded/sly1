#!/bin/bash
set -e

### Install Dependencies ###

PACKAGES="binutils-mips-linux-gnu ninja-build python3 python3-pip python3-venv wine32"

# Install missing dependencies
if ! sudo -n true 2>/dev/null; then
    echo "Root privileges are required to install dependencies. Please enter your password."
fi

if ! sudo -v; then
    echo "Error: Unable to obtain root privileges"
    exit 1
fi

echo "Adding i386 architecture support..."
sudo dpkg --add-architecture i386

echo "Updating package lists..."
sudo apt-get update -qq > /dev/null

echo "Dependencies: $PACKAGES"
echo "Installing missing dependencies..."
sudo apt-get install -y -qq $PACKAGES > /dev/null

PROJECT_DIR="$(dirname "$0")/.."

pushd $PROJECT_DIR > /dev/null
trap "popd > /dev/null" EXIT

# Set up Python virtual environment
echo "Setting up Python virtual environment..."
python3 -m venv env
source env/bin/activate
echo "Installing Python packages..."
pip install -q -U -r requirements.txt

### Download ProDG compilers and runtimes ###

echo "Starting ProDG setup script..."
./scripts/setup_prodg_linux.sh

popd > /dev/null
trap - EXIT

### Final Instructions ###

echo ""
echo "Quickstart complete!"
if [ ! -f $PROJECT_DIR/disc/SCUS_971.98 ]; then
    echo "Now, copy SCUS_971.98 from your copy of the game to the 'disc' directory of this project."
fi
echo ""
echo "To build the project, run '$(dirname "$0")/build.sh'"
