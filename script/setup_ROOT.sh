export MY_LIB_DIR=${MY_LIB_DIR:-"$HOME/root4summer"}
export MY_BUILD_DIR=${MY_BUILD_DIR:-"$MY_LIB_DIR/BUILD"}
export MY_ROOT_VERSION=${MY_ROOT_VERSION:-'trunk'}
#export MY_ROOT_VERSION=${MY_ROOT_VERSION:-'v5-34-02'}
export ROOTSYS=$MY_LIB_DIR/root/$MY_ROOT_VERSION
export PATH=$ROOTSYS/bin:$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
source $ROOTSYS/bin/thisroot.sh

