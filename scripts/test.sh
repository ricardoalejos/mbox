#!/usr/bin/env bash

SCRIPTS_DIR=$(dirname "$0")
ROOT_DIR=$(readlink -f "${SCRIPTS_DIR}"/..)
OUTPUT_DIR="${ROOT_DIR}"/out
BUILD_DIR="${OUTPUT_DIR}"/build
export LD_LIBRARY_PATH="${OUTPUT_DIR}"/lib:"${OUTPUT_DIR}":"${LD_LIBRARY_PATH}"

make -C "${BUILD_DIR}" test
