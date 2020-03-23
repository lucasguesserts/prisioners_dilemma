#!/bin/bash

# Setup
MAJOR_VERSION=2.11
SPECIFIC_VERSION=$MAJOR_VERSION.1
CATCH2_DIR=Catch2-$SPECIFIC_VERSION
COMPRESSED_FILE=v$SPECIFIC_VERSION.tar.gz
SUB_DIR=build_catch2
SOURCE_DIR=`pwd`
INSTALL_PREFIX=$HOME/libs/catch2-$SPECIFIC_VERSION
CATCH2_SYMLINK=$HOME/libs/catch2

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
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX ..

# Build
NUMBER_OF_PROCESSSORS=`nproc --all`
make -j $NUMBER_OF_PROCESSORS
make test
if [ $? -ne 0 ] ; then exit 1 ; fi
make install

# Delete
cd $SOURCE_DIR
rm -rf $SUB_DIR

# Symbolic link
ln -sf $INSTALL_PREFIX $CATCH2_SYMLINK
