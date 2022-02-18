#!/usr/bin/env bash

SCRIPTS_DIR=$(dirname "$0")
ROOT_DIR=$(readlink -f "${SCRIPTS_DIR}"/..)
SOURCE_DIR="${ROOT_DIR}"/source
OUTPUT_DIR="${ROOT_DIR}"/out
BUILD_DIR="${OUTPUT_DIR}"/build

cmake \
    -S "${SOURCE_DIR}" \
    -B "${BUILD_DIR}" \
    -DCMAKE_INSTALL_PREFIX="${OUTPUT_DIR}"
