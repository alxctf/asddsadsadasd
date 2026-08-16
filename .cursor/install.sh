#!/usr/bin/env bash
# Idempotent environment bootstrap for the car-registration console program.
#
# The sources are a Windows C++ console app, so we install the MinGW-w64
# cross-compiler and Wine, initialise a Wine prefix, then cross-compile the
# program into a Windows executable that runs under Wine.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

echo "==> Installing system packages (mingw-w64, wine)"
export DEBIAN_FRONTEND=noninteractive
sudo apt-get update -qq
sudo apt-get install -y --no-install-recommends mingw-w64 wine wine64

echo "==> Initialising Wine prefix"
# Suppress the Mono/Gecko install dialogs; safe to re-run.
export WINEDEBUG=-all WINEDLLOVERRIDES="mscoree=d;mshtml=d"
wineboot -i >/dev/null 2>&1 || true

echo "==> Building the program"
make clean
make all

echo "==> Environment ready. Build artifact:"
ls -la program.exe
