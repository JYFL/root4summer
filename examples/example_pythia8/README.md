    source $HOME/root4summer/script/setup_base.sh
    source $HOME/root4summer/script/setup_pythia8.sh
    make
    ./pythia8_pT out.root 911
