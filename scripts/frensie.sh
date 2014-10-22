#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

# Export a python script to convert relative paths to absoulte paths.
# Delete this python script before this bash script exits
ABSPATHEXE="__abspath.py"
echo "import os; import sys; sys.stdout.write(os.path.abspath(sys.argv[1]))" > $ABSPATHEXE

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/trilinos")
TRILINOS_SOURCE_PATH=$(python $ABSPATHEXE "../deps/builds/trilinos")
HDF5_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/hdf5")
MOAB_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/moab")
ODEPACK_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/odepack")
BOOST_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/boost")
GSL_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/gsl")
MPI_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/mpi")
DOXYGEN_PREFIX_PATH=$(python $ABSPATHEXE "../deps/install/doxygen")
FRENSIE_SRC=$(python $ABSPATHEXE "../src")
FRENSIE_INSTALL=$(python $ABSPATHEXE "../frensie_install")

# No longer needed after this point.
# Move lower if $ABSPATHEXE needs to be used below this.
rm "__abspath.py"


##---------------------------------------------------------------------------##
## The Teuchos_TwoDArray class has a bug that needs to be fixed. This patch
## will work as a temporary solution.
patch -s -f $TRILINOS_PREFIX_PATH/include/Teuchos_TwoDArray.hpp \
   $FRENSIE_SRC/patches/Teuchos_TwoDArray_patch

source ~/.bashrc
`python ../src/scripts/prefix.py ../deps/install`

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$FRENSIE_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=OFF \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FRENSIE_ENABLE_DBC:BOOL=ON \
    -D FRENSIE_ENABLE_OPENMP:BOOL=ON \
    -D FRENSIE_ENABLE_MPI:BOOL=ON \
    -D FRENSIE_ENABLE_DAGMC:BOOL=OFF \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D TRILINOS_SOURCE:PATH=$TRILINOS_SOURCE_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D ODEPACK_PREFIX:PATH=$ODEPACK_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D GSL_PREFIX:PATH=$GSL_PREFIX_PATH \
    -D MPI_PREFIX:PATH=$MPI_PREFIX_PATH \
    -D DOXYGEN_PREFIX:PATH=$DOXYGEN_PREFIX_PATH \
    $EXTRA_ARGS \
    $FRENSIE_SRC

 