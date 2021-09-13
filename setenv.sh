#!/usr/bin/env bash

export PROJECT_ROOT=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
export PROJECT_SOURCE=${PROJECT_ROOT}/source
export PROJECT_OUTPUT=${PROJECT_ROOT}/out
export PROJECT_BUILD=${PROJECT_OUTPUT}/build
export LD_LIBRARY_PATH=${PROJECT_OUTPUT}/lib:${LD_LIBRARY_PATH}

alias mbox_configure="cmake -S ${PROJECT_SOURCE} -B ${PROJECT_BUILD} -DCMAKE_INSTALL_PREFIX=${PROJECT_OUTPUT}"
alias mbox_dependencies="mbox_configure; make -C ${PROJECT_BUILD} install_dependencies"
alias mbox_test="make -C ${PROJECT_BUILD} test"
alias mbox_build="make -C ${PROJECT_BUILD} application; cmake --install ${PROJECT_BUILD}"
alias mbox_clean="rm -rf out"
