#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

echo "==> Configuring Slitherer"

cmake \
    -S "${ROOT_DIR}" \
    -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE=Release

echo "==> Building Slitherer"

cmake \
    --build "${BUILD_DIR}" \
    --config Release \
    --parallel

echo
echo "==> Build complete"
echo "Executable: ${BUILD_DIR}/bin/Slitherer"
