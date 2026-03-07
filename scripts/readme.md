# Scripts

This directory contains the following scripts used to setup and build the project. There are a few others, but they are not used in the normal contributing workflow.

## Setup scripts

### quickstart.sh

Installs the necessary dependencies using pip/apt and sets up the build environment. This will run all the other setup scripts for you. You only need to run this script once.

### setup_prodg_linux.sh

Installs the compiler needed to build the project on Linux. `quickstart.sh` will run this script for you, so you don't need to run both.

There is an equivalent script for Windows, but the assembler does not work on Windows, so you can't build the project on Windows. You must use Linux or WSL.

## Utility scripts

### build.sh

Runs a clean reconfigure (deletes build files and splits the binary), then builds the project. Will warn you if `disc/SCUS_971.98` is not present.

### diff.sh

Compares a decompiled function against the original using objdiff. Takes a function name as a required argument and an optional object name.

### run.sh

Runs the last successful build in an emulator. Before using, you must install PCSX2, build the project, and either place an ISO in the `disc` directory or specify one as an argument. The script will boot the emulator using the compiled elf, and load the assets from the provided ISO.

PCSX2 will be auto detected in this order:
* System PATH
* Flatpak
* AppImage in the `tools` directory with "pcsx2" in the file name
* XDG Desktop entry with "pcsx2" in the file name

### checks.sh

Runs the same build commands that GitHub actions uses to verify that the project builds successfully. This must pass before a pull request will be merged. If the argument `--report` is passed it outputs the current project progress to `report.json`.

### check_progress.py

Prints the current project progress based on the data in `report.json`.
