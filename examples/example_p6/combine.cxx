#include "TPythia6.h"
#include "TParticle.h"
#include "TClonesArray.h"
#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <fstream>
#include <TString.h>
#include "TPRegexp.h"
#include "TFile.h"
#include "TH1D.h"

using namespace fastjet;
using namespace std;

// File handle to save historgram with root
TFile *outRoot = new TFile("out.root","RECREATE");
// Book Histgram with root
TH1D * hJetPt = new TH1D("hJetPt","Jet Pt Spectra", 1000,0,100);
int jetReco( int iEvent, vector<PseudoJet> & particles );

int main () {

    vector<PseudoJet> particles;

    // File handle to read data ( common c++ )
    ifstream infile("in.dat",ifstream::in);


    TString line;
    TPMERegexp field("\\s+");
    int iEvent;
    int index, pid;
    double px,py,pz,E;

    while( infile.good() ){
        line.ReadLine( infile );
        field.Split(line);
        if( !field[0].IsDigit() ) continue; 

        if( field.NMatches() < 5 ) {
            if( iEvent > 0 )jetReco( iEvent,particles );
            iEvent = field[0].Atoi();
            particles.clear();
        }else{
            index   = field[0].Atoi();
            pid     = field[1].Atoi();
            px      = field[2].Atof();
            py      = field[3].Atof();
            pz      = field[4].Atof();
            E       = field[5].Atof();
            particles.push_back( PseudoJet(px,py,pz,E));
        }
    }
    outRoot->Write();
    outRoot->Close();
}

int jetReco( int iEvent, vector<PseudoJet> & particles ){

    //======================================
    //    FASTJET
    //======================================

    // choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    // print out some infos
    cout<< "\n\n\n"<<endl;
    cout<<" ========================= iEvent = "<<iEvent<<" ===============================\n"<<endl;
    cout << "Clustering with " << jet_def.description() << endl;

    // print the jets
    cout <<   "        pt y phi" << endl;
    for (unsigned i = 0; i < jets.size(); i++) {
        hJetPt->Fill( jets[i].perp()) ;
        cout << "jet " << i << ": "<< jets[i].perp() << " " 
            << jets[i].rap() << " " << jets[i].phi() << endl;
        vector<PseudoJet> constituents = jets[i].constituents();
        for (unsigned j = 0; j < constituents.size(); j++) {
            cout << "    constituent " << j << "'s pt: " << constituents[j].perp()
                << endl;
        }
    }
    return 0;
} 
