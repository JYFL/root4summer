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
// Performance Histogram
TH1D * hJetPt = NULL;
TH1D * hJetEnergyFraction = NULL;
TH1D * hDPhiJets = NULL;
// Physics Histogram
TProfile * hREnergy[10]; 

// Variables
int     EnergyFractionBin[] = { 10,20,30,40,50,60,70,80,90 }; // 
int     nEnergyFractionBin = sizeof( EnergyFractionBin )/sizeof(int);

int     NbinE = 1000;
double  MinE  = 0;
double  MaxE  = 1000;
double  BinSizeE = ( MaxE - MinE ) / NBinE;

int     NbinR = 1000;
double  MinR  = 0;
double  MaxR  = 1;


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
    hJetEnergyFraction = new TH1D("hJetEnergyFraction","Jet Energy / Input Energy",10,0,1 );
    hDPhiJets = new TH1D("hDPhiJets","hDPhiJets",1000,-10,10);
    for( int i=0;i<nEnergyFractionBin;i++ ){
        nEnergyFractionBin = new TProfile( Form("hREnergy%02d",EnergyFractionBin[i]),Form("R/R0 vs Energy in %d%%",EnergyFractionBin[i]),1000,0,1000 );
    }


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
    double R = 1;
    JetDefinition jet_def(antikt_algorithm, R);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    //vector<PseudoJet> jets = sorted_by_E(cs.inclusive_jets());
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    // Fill Performance Hist
    hDPhiJets->Fill( jets[0].delta_phi_to(jets[1]));
    hJetEnergyFraction->Fill( jets[0].e()/inputEnergy );

    double  binWidthR = 0.001;
    double  minR = 0;
    double  maxR = 1;
    int     nRbin = (maxR-minR)/binWidthR;
    vector<double> energyInRbin(nRbin,0);
    // QUESTION : check All particles or constituents? 
    vector<PseudoJet>& constituents = jets[0].constituents();
    for( UInt_t ip=0;ip<constituents.size();ip++ ){
        double deltaR = jets[0].delta_R(constituents[ip]);
        int ibin = ( deltaR - minR ) / binWidthR;
        energyInRbin[ibin] += constituents[ip]/jets[0].e();
    }

    TGraph gEnergyInR( nRbin );
    double energyInR = 0;
    for( int ib=0;ib<nRbin;ib++ ){
        energyInR += energyInRbin[ib];
        gEnergyInR.SetPoint(ib, minR + (ib+.5)*binWidthR, energyInR );
    }

    for( int i=0;i<10;i++ ){
        hEnergyFractionRadious[i]->Fill( jets[0].e(), gEnergyInR.Eval(i/10.) );
    }

    return 0;
} 
