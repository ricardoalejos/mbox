#!/usr/bin/env bash

SCRIPTS_DIR=$(dirname "$0")
ROOT_DIR=$(readlink -f "${SCRIPTS_DIR}"/..)
OUTPUT_DIR="${ROOT_DIR}"/out
BUILD_DIR="${OUTPUT_DIR}"/build

make -C "${BUILD_DIR}" install
