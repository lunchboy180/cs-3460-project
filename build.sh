#!/usr/bin/env bash

set -e

if [ -z "$VCPKG_ROOT" ]; then
    echo "Error: VCPKG_ROOT is not set."
    echo "Example:"
    echo "  export VCPKG_ROOT=\$HOME/vcpkg"
    exit 1
fi

cmake --preset default
cmake --build --preset default
