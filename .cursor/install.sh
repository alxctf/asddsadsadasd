#!/usr/bin/env bash
# Idempotent bootstrap for the "Avto" car-registration console app.
#
# The sources target Windows (<windows.h>, SetConsoleCP/SetConsoleOutputCP and
# the MSVC-only _stricmp), so we cross-compile with MinGW-w64 and run the
# resulting .exe headlessly under Wine. Everything is installed here so the
# environment is self-contained and reproducible on the default base image.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

# 1. Ensure the Windows cross-toolchain + Wine are present (idempotent).
if ! command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1 || ! command -v wine >/dev/null 2>&1; then
    export DEBIAN_FRONTEND=noninteractive
    sudo apt-get update -qq
    sudo apt-get install -y -qq --no-install-recommends \
        g++-mingw-w64-x86-64 \
        wine \
        wine64
fi

# 2. Prepare a dedicated, headless Wine prefix (no Gecko/Mono download prompts).
export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-avto}"
export WINEDEBUG=-all
export WINEDLLOVERRIDES="mscoree,mshtml="
export DISPLAY=""
if [ ! -f "$WINEPREFIX/system.reg" ]; then
    wineboot --init >/dev/null 2>&1 || true
fi

# 3. Cross-compile the Windows console executable.
x86_64-w64-mingw32-g++ -std=c++17 -static -O2 -o avto.exe \
    main.cpp \
    file_io.cpp \
    search_core.cpp \
    search_by_field.cpp \
    export_all.cpp

# 4. The app reads registrations from "regs.txt" (Text::FILE_REGS), but the repo
#    ships the same data as "registrations.txt". Provide the expected file name.
#    This is a runtime data alias only; no application source is modified.
if [ ! -f regs.txt ] && [ -f registrations.txt ]; then
    cp registrations.txt regs.txt
fi

echo "install.sh: toolchain ready, built avto.exe, Wine prefix at $WINEPREFIX"
