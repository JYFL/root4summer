#MY_LIB_DIR=$HOME/root4summer
#MY_PYTHIA_VERSION='pythia8165' 
#wget http://home.thep.lu.se/~torbjorn/pythia8/$MY_PYTHIA_VERSION.tgz
#tar -zxf $MY_PYTHIA_VERSION.tgz
#rm $MY_PYTHIA_VERSION.tgz

cd $MY_LIB_DIR
curl http://home.thep.lu.se/~torbjorn/pythia8/$MY_PYTHIA_VERSION.tgz | tar -zx
cd $MY_PYTHIA_VERSION
./configure --enable-shared
make -j3
