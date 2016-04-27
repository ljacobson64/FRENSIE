#!/bin/bash

EXTRA_ARGS=$@

TRILINOS_INSTALL=
TRILINOS_SRC=
MPI_DIR=
LAPACK_DIR=
BOOST_DIR=

source $HOME/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$TRILINOS_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D Trilinos_VERBOSE_CONFIGURE:BOOL=ON \
    -D CMAKE_CXX_FLAGS:STRING="-D_GLIBCXX_USE_CXX11_ABI=0" \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D Trilinos_ASSERT_MISSING_PACKAGES:BOOL=OFF \
    -D BUILD_SHARED_LIBS:BOOL=ON \
    -D Trilinos_LINK_SEARCH_START_STATIC:BOOL=OFF \
    -D TPL_FIND_SHARED_LIBS:BOOL=ON \
    -D Trilinos_ENABLE_CXX11:BOOL=ON \
    -D Trilinos_ENABLE_EXPLICIT_INSTANTIATION:BOOL=ON \
    -D Trilinos_ENABLE_DEBUG:BOOL=OFF \
    -D Trilinos_ENABLE_ALL_PACKAGES:BOOL=OFF \
    -D Trilinos_ENABLE_Teuchos:BOOL=ON \
    -D Trilinos_ENABLE_PyTrilinos:BOOL=ON \
    -D Trilinos_ENABLE_Amesos=OFF \
    -D Trilinos_ENABLE_Amesos2=OFF \
    -D Trilinos_ENABLE_Anasazi=OFF \
    -D Trilinos_ENABLE_AztecOO=OFF \
    -D Trilinos_ENABLE_Belos=OFF \
    -D Trilinos_ENABLE_Epetra=OFF \
    -D Trilinos_ENABLE_EpetraExt=OFF \
    -D Trilinos_ENABLE_Galeri=OFF \
    -D Trilinos_ENABLE_Ifpack=OFF \
    -D Trilinos_ENABLE_Ifpack2=OFF \
    -D Trilinos_ENABLE_Intrepid=OFF \
    -D Trilinos_ENABLE_Isorropia=OFF \
    -D Trilinos_ENABLE_Kokkos=OFF \
    -D Trilinos_ENABLE_ML=OFF \
    -D Trilinos_ENABLE_MueLu=OFF \
    -D Trilinos_ENABLE_NOX=OFF \
    -D Trilinos_ENABLE_ROL=OFF \
    -D Trilinos_ENABLE_Sacado=OFF \
    -D Trilinos_ENABLE_Shards=OFF \
    -D Trilinos_ENABLE_STK=OFF \
    -D Trilinos_ENABLE_Stokhos=OFF \
    -D Trilinos_ENABLE_Stratimikos=OFF \
    -D Trilinos_ENABLE_Thyra=OFF \
    -D Trilinos_ENABLE_Tpetra=OFF \
    -D Trilinos_ENABLE_TrilinosCouplings=OFF \
    -D Trilinos_ENABLE_Triutils=OFF \
    -D Trilinos_ENABLE_Xpetra=OFF \
    -D Trilinos_ENABLE_Zoltan=OFF \
    -D Trilinos_ENABLE_Zoltan2=OFF \
    -D Trilinos_ENABLE_TESTS:BOOL=ON \
    -D Trilinos_ENABLE_EXAMPLES:BOOL=ON \
    -D Trilinos_ENABLE_DEVELOPMENT_MODE:BOOL=OFF \
    -D Teuchos_ENABLE_DEBUG_RCP_NODE_TRACING:BOOL=OFF \
    -D Teuchos_ENABLE_ABC:BOOL=OFF \
    -D Teuchos_ENABLE_LONG_LONG_INT:BOOL=ON \
    -D TPL_ENABLE_MPI:BOOL=ON \
    -D MPI_BASE_DIR:PATH=$MPI_DIR \
    -D TPL_BLAS_LIBRARIES:PATH=$LAPACK_DIR/lib/libblas.so \
    -D TPL_LAPACK_LIBRARIES:PATH=$LAPACK_DIR/lib/liblapack.so \
    -D TPL_ENABLE_Boost:BOOL=ON \
    -D Boost_INCLUDE_DIRS:PATH=$BOOST_DIR/include \
    -D Boost_LIBRARY_DIRS:PATH=$BOOST_DIR/lib \
    -D TPL_ENABLE_BoostLib:BOOL=ON \
    -D BoostLib_INCLUDE_DIRS:PATH=$BOOST_DIR/include \
    -D BoostLib_LIBRARY_DIRS:PATH=$BOOST_DIR/lib \
    -D TPL_ENABLE_Netcdf:BOOL=OFF \
    $EXTRA_ARGS \
    $TRILINOS_SRC
