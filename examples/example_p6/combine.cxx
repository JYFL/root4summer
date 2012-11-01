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
#include "TProfile.h"

using namespace fastjet;
using namespace std;

// File handle to save histogram with root
TFile *outRoot = NULL;
TH1D * hJetPt = NULL;
TProfile * hEnergyInR = NULL;
TProfile * hEnergyInPhi = NULL;
TH1D * hJetEnergyFraction = NULL;
TH1D * hDPhiJets = NULL;

// Function Decl
int jetReco( int iEvent, double inputEnergy, vector<PseudoJet> & particles );

int main ( int argc, char* argv[]) {
    if( argc != 4 ){
        cout<<"USAGE : ./combine.exe inputEnergy inputFileName outputFileName"<<endl;
        exit(1);
    }

    double inputEnergy = atof(argv[1])/2.;
    TString inputFileName = argv[2];
    TString outputFileName = argv[3];

    //====  File handle to read data ( common c++ )
    ifstream infile( inputFileName ,ifstream::in);

    //====  BOOK output root and histogram
    outRoot = new TFile(outputFileName,"RECREATE");
    hJetPt = new TH1D("hJetPt","Jet Pt Spectra", 1000,0,100);
    hEnergyInR = new TProfile("hEnergyInR","Energy-R/R0",100,0,10 );
    hEnergyInPhi = new TProfile("hEnergyInPhi","Energy-Phi/Phi0",100,0,10 );
    hJetEnergyFraction = new TH1D("hJetEnergyFraction","Jet Energy / Input Energy",10,0,1 );
    hDPhiJets = new TH1D("hDPhiJets","hDPhiJets",1000,-10,10);


    vector<PseudoJet> particles;
    //====  READ OSCAR
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
            if( iEvent > 0 )jetReco( iEvent,inputEnergy, particles );
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

int jetReco( int iEvent, double inputEnergy, vector<PseudoJet> & particles ){
    if( particles.size() < 1 ) return 0;

    //======================================
    //    FASTJET
    //======================================

    // choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    //vector<PseudoJet> jets = sorted_by_E(cs.inclusive_jets());
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    hDPhiJets->Fill( jets[0].delta_phi_to(jets[1]));
    hJetEnergyFraction->Fill( jets[0].e()/inputEnergy );
    TH1D * hEnergyFracInRbin = new TH1D("hEnergyFracInRbin","",100,0,10);
    TH1D * hEnergyFracInPhibin = new TH1D("hEnergyFracInPhibin","",100,0,10);
    for( UInt_t ip=0;ip<particles.size();ip++ ){
        double deltaR = jets[0].delta_R(particles[ip]);
        hEnergyFracInRbin->Fill( deltaR, particles[ip].e()/inputEnergy );
        double deltaPhi = jets[0].delta_phi_to(particles[ip]);
        hEnergyFracInPhibin->Fill( TMath::Abs(deltaPhi), particles[ip].e()/inputEnergy );
    }

    double energyInR = 0;
    double energyInPhi = 0;
    for( int ib=1;ib<hEnergyFracInRbin->GetNbinsX();ib++ ){
        energyInR += hEnergyFracInRbin->GetBinContent(ib);
        hEnergyInR->Fill( hEnergyInR->GetBinCenter(ib), energyInR );
        energyInPhi += hEnergyFracInPhibin->GetBinContent(ib);
        hEnergyInPhi->Fill( hEnergyInPhi->GetBinCenter(ib), energyInPhi );
    }
    delete hEnergyFracInRbin;
    delete hEnergyFracInPhibin;



    /*  
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
    */
    return 0;
} 
