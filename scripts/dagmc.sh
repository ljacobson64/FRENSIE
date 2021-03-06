#!/bin/bash

EXTRA_ARGS=$@

DAGMC_SRC=
DAGMC_INSTALL=

source $HOME/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$DAGMC_INSTALL \
    -D CMAKE_CXX_FLAGS:STRING="-D_GLIBCXX_USE_CXX11_ABI=0" \
    $EXTRA_ARGS \
    $DAGMC_SRC