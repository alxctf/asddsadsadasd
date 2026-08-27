#!/usr/bin/env bash
# Idempotent repository bootstrap for the "Avto" car-registration console app.
# Cross-compiles the Windows sources with MinGW-w64 and prepares a Wine prefix
# so the resulting .exe can be run headlessly on Linux.
set -euo pipefail

# Resolve the repository root regardless of the caller's working directory.
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

# Dedicated Wine prefix so we never touch a user's default ~/.wine.
export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-avto}"
export WINEDEBUG=-all
# Never prompt to download Gecko/Mono; this is a plain console app.
export WINEDLLOVERRIDES="mscoree,mshtml="
export DISPLAY=""

# Initialize the Wine prefix once (safe to re-run).
if [ ! -f "$WINEPREFIX/system.reg" ]; then
    wineboot --init >/dev/null 2>&1 || true
fi

# Cross-compile the Windows console executable.
x86_64-w64-mingw32-g++ -std=c++17 -static -O2 -o avto.exe \
    main.cpp \
    file_io.cpp \
    search_core.cpp \
    search_by_field.cpp \
    export_all.cpp

# The program reads its registrations from "regs.txt" (Text::FILE_REGS), but the
# repository ships the same data as "registrations.txt". Provide the expected
# file name so the app can load data. This is a runtime data alias only; it does
# not modify any application source.
if [ ! -f regs.txt ] && [ -f registrations.txt ]; then
    cp registrations.txt regs.txt
fi

echo "install.sh: built avto.exe and prepared Wine prefix at $WINEPREFIX"
