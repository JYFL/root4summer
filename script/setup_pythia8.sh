export MY_LIB_DIR=${MY_LIB_DIR:-"$HOME/root4summer"}
export MY_PYTHIA_VERSION=${MY_PYTHIA_VERSION:-'pythia8165'} 
export PYTHIA8=$MY_LIB_DIR/$MY_PYTHIA_VERSION
export PYTHIA8DATA=$PYTHIA8/xmldoc
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH
