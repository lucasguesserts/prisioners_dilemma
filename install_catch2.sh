#!/bin/bash

MAJOR_VERSION=2.11
SPECIFIC_VERSION=$MAJOR_VERSION.1
CATCH2_DIR=Catch2-$SPECIFIC_VERSION
COMPRESSED_FILE=v$SPECIFIC_VERSION.tar.gz
SUB_DIR=build_catch2
SOURCE_DIR=`pwd`

# Subfolder
mkdir $SUB_DIR
cd $SUB_DIR

# Download and extract
wget https://github.com/catchorg/Catch2/archive/$COMPRESSED_FILE
tar xf ${COMPRESSED_FILE}

# Config
cd $CATCH2_DIR/
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/libs/catch2-$SPECIFIC_VERSION/ ..

# Build
NUMBER_OF_PROCESSSORS=`nproc --all`
make -j $NUMBER_OF_PROCESSORS
make install

# Delete
cd $SOURCE_DIR
rm -rf $SUB_DIR
