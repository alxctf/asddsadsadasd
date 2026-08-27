FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Toolchain for this project:
# - g++-mingw-w64-x86-64: cross-compiles the Windows console app (the sources use
#   <windows.h>, SetConsoleCP/SetConsoleOutputCP and the MSVC-only _stricmp).
# - wine64: runs the resulting Windows .exe headlessly on Linux.
# git and curl are included because this is a fully custom base image.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        curl \
        git \
        g++-mingw-w64-x86-64 \
        wine \
        wine64 \
    && rm -rf /var/lib/apt/lists/*

USER ubuntu
WORKDIR /home/ubuntu
