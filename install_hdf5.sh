#!/bin/bash

MAJOR_VERSION=1.10
SPECIFIC_VERSION=$MAJOR_VERSION.3
HDF5_DIR=CMake-hdf5-$SPECIFIC_VERSION
COMPRESSED_FILE=$HDF5_DIR.tar.gz
SUB_DIR=build_hdf5
SOURCE_DIR=`pwd`

# Subfolder
mkdir $SUB_DIR
cd $SUB_DIR

# Download and extract
wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-${MAJOR_VERSION}/hdf5-${SPECIFIC_VERSION}/src/${COMPRESSED_FILE}
tar xf ${COMPRESSED_FILE}

# Config
cd $HDF5_DIR/hdf5-$SPECIFIC_VERSION
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/libs/hdf5-$SPECIFIC_VERSION/ ..

# Build
NUMBER_OF_PROCESSSORS=`nproc --all`
make -j $NUMBER_OF_PROCESSORS
make install

# Delete
cd $SOURCE_DIR
rm -rf $SUB_DIR
