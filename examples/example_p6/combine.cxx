#include "TPythia6.h"
#include "TParticle.h"
#include "TClonesArray.h"
#include "fastjet/ClusterSequence.hh"
#include <iostream>
using namespace fastjet;
using namespace std;

int main () {

  vector<PseudoJet> particles;
  //======================================
  //    PYTHIA6
  //======================================
  TPythia6* pythia = new TPythia6;
  pythia->Initialize("cms", "p", "p", 200);
  TClonesArray* parts = (TClonesArray*)pythia->GetListOfParticles();
  pythia->GenerateEvent();
  for( int ip=0;ip<parts->GetEntriesFast();ip++){
      TParticle * part = (TParticle*) parts->At(ip);
//cout<<"part => "<<ip<<"\t"<<part->Px()<<"\t"<<part->GetStatusCode()<<"\t"<<part->GetFirstDaughter()<<endl;
      part->Print();
      particles.push_back( PseudoJet( part->Px(), part->Py(), part->Pz(), part->Energy()));
  }

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
  cout << "Clustering with " << jet_def.description() << endl;

  // print the jets
  cout <<   "        pt y phi" << endl;
  for (unsigned i = 0; i < jets.size(); i++) {
      cout << "jet " << i << ": "<< jets[i].perp() << " " 
          << jets[i].rap() << " " << jets[i].phi() << endl;
      vector<PseudoJet> constituents = jets[i].constituents();
      for (unsigned j = 0; j < constituents.size(); j++) {
          cout << "    constituent " << j << "'s pt: " << constituents[j].perp()
              << endl;
      }
  }
} 
