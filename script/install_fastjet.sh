#!/bin/bash
MY_BUILD_DIR_FASTJET=$MY_BUILD_DIR/fastjet
FASTJET=${MY_LIB_DIR}/fastjet/fastjet-${MY_FASTJET_VER}
mkdir -p $MY_BUILD_DIR_FASTJET
cd $MY_BUILD_DIR_FASTJET
wget http://fastjet.fr/repo/fastjet-${MY_FASTJET_VER}.tar.gz
tar -zxf fastjet-${MY_FASTJET_VER}.tar.gz 
cd fastjet-${MY_FASTJET_VER}

./configure --prefix=$FASTJET
make clean
make -j2
make install

