#!/bin/bash
set -e

ISO_FILE="$1"

# Check for ISO
[ -z "$ISO_FILE" ] && {
    echo "Error: No ISO path provided." >&2;
    echo "Usage: $0 /path/to/game.iso" >&2;
    exit 1;
}

[ ! -f "$ISO_FILE" ] && {
    echo "Error: ISO file not found: $ISO_FILE" >&2;
    exit 1;
}

PROJECT_DIR="$(dirname "$0")/.."
ELF_FILE="$PROJECT_DIR/disc/SCUS_971.98"
CHECKSUM="57dc305db57932ad3f1122966cdb695d2e62a47a"

# Extract SCUS_971.98
echo "Extracting from $ISO_FILE..."
if command -v bsdtar &>/dev/null; then
    bsdtar --no-same-permissions --no-same-owner -xf "$ISO_FILE" -C "$PROJECT_DIR/disc" SCUS_971.98
    elif command -v 7z &>/dev/null; then
    7z e "$ISO_FILE" -o"$PROJECT_DIR/disc" SCUS_971.98 -y
    elif command -v isoinfo &>/dev/null; then
    isoinfo -i "$ISO_FILE" -x /SCUS_971.98 > "$ELF_FILE"
else
    echo "Error: No extraction tool found. Install bsdtar, 7z, or isoinfo." >&2
    exit 1
fi

[ ! -f "$ELF_FILE" ] && { echo "Extraction failed." >&2; exit 1; }
chmod 644 "$ELF_FILE"

# Verify checksum
echo "Verifying SCUS_971.98..."
ACTUAL=$(sha1sum "$ELF_FILE" | awk '{print $1}')
if [ "$ACTUAL" != "$CHECKSUM" ]; then
    echo "Error: Checksum mismatch! Expected: $CHECKSUM, Got: $ACTUAL" >&2
    echo "Please ensure you have the correct version of the game (NTSC-U)." >&2
    exit 1
fi

echo "SCUS_971.98 is ready!"
