#!/bin/bash
mkdir -p $MY_BUILD_DIR/root/
cd $MY_BUILD_DIR/root/
svn co https://root.cern.ch/svn/root/$([ $MY_ROOT_VERSION == 'trunk' ] || echo tags/)$MY_ROOT_VERSION $MY_ROOT_VERSION
cd $MY_ROOT_VERSION

make clean

echo =========== CONFIGURE

./configure \
--prefix=$ROOTSYS \
--etcdir=$ROOTSYS/etc \
--with-f77=gfortran \
--with-pythia6-uscore=SINGLE \
--enable-roofit \
--enable-minuit2 \
--enable-alien \
--enable-xrootd \
--enable-gsl-shared \
--disable-globus \
--enable-cocoa \
--build=debug

echo =========== MAKE
make -j2
echo =========== INSTALL
make install
