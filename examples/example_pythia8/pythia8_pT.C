// main03.cc is a part of the PYTHIA event generator.
// Copyright (C) 2009 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program. 
// It illustrates a simple analysis of QCD jet events.
// All input is specified in the main03.cmnd file.

#include "TH1.h"
#include "TFile.h"
#include <TROOT.h>
#include <TStopwatch.h>
#include <TDatime.h>
#include <iostream>



#include "Pythia.h"

using namespace Pythia8; 

int main(int argc, char **argv)
{

  TROOT root("pythia","run pythia");

  // CONSTANT
  if( argc < 3 ){
    std::cout<<Form("usage : ./%s <output> <random_seed>",argv[0])<<std::endl;
    exit(1);


  }
  char *outFile = argv[1];
  Int_t random_seed = atoi(argv[2]);
  TFile *fout = new TFile(outFile,"recreate");

  // Generator.
  Pythia pythia;

  // Shorthand for some public members of pythia (also static ones).
  Event& event = pythia.event;
  //ParticleDataTable& pdt = pythia.particleData;
  Info& info = pythia.info;

  // Read in commands from external file.
  pythia.readFile("main03.cmnd");    

  // Extract settings to be used in the main program.
  int    nEvent  = pythia.mode("Main:numberOfEvents");
  int    nList   = pythia.mode("Main:numberToList");
  int    nShow   = pythia.mode("Main:timesToShow");
  bool   showCS  = pythia.flag("Main:showChangedSettings");
  //bool   showCPD = pythia.flag("Main:showChangedParticleData");

  pythia.readString(Form("Random:seed=%d",random_seed));


  // Initialize. Beam parameters set in .cmnd file.
  pythia.init();

  // List changed data.
  if (showCS) pythia.settings.listChanged();
  //if (showCPD) pdt.listChanged();

  // Book histograms.
  TH1D *pThard = new TH1D("pThard","process pT scale", 100, 0., 200.); pThard->Sumw2();
  TH1D *mult   = new TH1D("mult","charged particle multiplicity", 100, -0.5, 799.5);mult->Sumw2();
  TH1D *dndy   = new TH1D("dndy","dn/dy for charged particles", 100, -10., 10.);dndy->Sumw2();

  TH1D *dndpT_hadron  = new TH1D("dndpT_hadron","dn/dpT for charged particles", 500, 0., 50.);dndpT_hadron->Sumw2();
  TH1D *dndpT_pion  = new TH1D("dndpT_pion","dn/dpT for pions", 500, 0., 50.);dndpT_pion->Sumw2();
  TH1D *dndpT_kaon  = new TH1D("dndpT_kaon","dn/dpT for kaons", 500, 0., 50.);dndpT_kaon->Sumw2();
  TH1D *dndpT_proton  = new TH1D("dndpT_proton","dn/dpT for protons", 500, 0., 50.);dndpT_proton->Sumw2();
  TH1D *dndpT_antiproton  = new TH1D("dndpT_antiproton","dn/dpT for antiprotons", 500, 0., 50.);dndpT_antiproton->Sumw2();
  TH1D *dndpT_k0s  = new TH1D("dndpT_k0s","dn/dpT for k0s", 500, 0., 50.);dndpT_k0s->Sumw2();

  TH1D *dndpT_infly_hadron  = new TH1D("dndpT_infly_hadron","dn/dpT for charged particles", 500, 0., 50.);dndpT_infly_hadron->Sumw2();
  TH1D *dndpT_infly_pion  = new TH1D("dndpT_infly_pion","dn/dpT for pions", 500, 0., 50.);dndpT_infly_pion->Sumw2();
  TH1D *dndpT_infly_kaon  = new TH1D("dndpT_infly_kaon","dn/dpT for kaons", 500, 0., 50.);dndpT_infly_kaon->Sumw2();
  TH1D *dndpT_infly_proton  = new TH1D("dndpT_infly_proton","dn/dpT for protons", 500, 0., 50.);dndpT_infly_proton->Sumw2();
  TH1D *dndpT_infly_antiproton  = new TH1D("dndpT_infly_antiproton","dn/dpT for antiprotons", 500, 0., 50.);dndpT_infly_antiproton->Sumw2();

  TH1D *dndpT_hadron_mid  = new TH1D("dndpT_hadron_mid","dn/dpT for charged particles |eta|<0.35", 500, 0., 50.);dndpT_hadron_mid->Sumw2();
  TH1D *dndpT_pion_mid  = new TH1D("dndpT_pion_mid","dn/dpT for pions |eta|<0.35", 500, 0., 50.);dndpT_pion_mid->Sumw2();
  TH1D *dndpT_kaon_mid  = new TH1D("dndpT_kaon_mid","dn/dpT for kaon |eta|<0.35", 500, 0., 50.);dndpT_kaon_mid->Sumw2();
  TH1D *dndpT_proton_mid  = new TH1D("dndpT_proton_mid","dn/dpT for proton |eta|<0.35", 500, 0., 50.);dndpT_proton_mid->Sumw2();
  TH1D *dndpT_antiproton_mid  = new TH1D("dndpT_antiproton_mid","dn/dpT for antiproton |eta|<0.35", 500, 0., 50.);dndpT_antiproton_mid->Sumw2();

  TH1D *dndpT_infly_hadron_mid  = new TH1D("dndpT_infly_hadron_mid","dn/dpT for charged particles |eta|<0.35", 500, 0., 50.);dndpT_infly_hadron_mid->Sumw2();
  TH1D *dndpT_infly_pion_mid  = new TH1D("dndpT_infly_pion_mid","dn/dpT for pions |eta|<0.35", 500, 0., 50.);dndpT_infly_pion_mid->Sumw2();
  TH1D *dndpT_infly_kaon_mid  = new TH1D("dndpT_infly_kaon_mid","dn/dpT for kaon |eta|<0.35", 500, 0., 50.);dndpT_infly_kaon_mid->Sumw2();
  TH1D *dndpT_infly_proton_mid  = new TH1D("dndpT_infly_proton_mid","dn/dpT for proton |eta|<0.35", 500, 0., 50.);dndpT_infly_proton_mid->Sumw2();
  TH1D *dndpT_infly_antiproton_mid  = new TH1D("dndpT_infly_antiproton_mid","dn/dpT for antiproton |eta|<0.35", 500, 0., 50.);dndpT_infly_antiproton_mid->Sumw2();

  TH1D *dndpT_k0s_mid  = new TH1D("dndpT_k0s_mid","dn/dpT for k0s |eta|<0.35", 500, 0., 50.);dndpT_k0s_mid->Sumw2();


  TStopwatch timer;
  timer.Start();


  // Begin event loop.
  int nPace = max(1, nEvent / max(1, nShow) ); 
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (nShow > 0 && iEvent%nPace == 0) 
      cout << " Now begin event " << iEvent << endl;

    // Generate events. Quit if failure.
    if (!pythia.next()) {
      cout << " Event generation aborted prematurely, owing to error!\n"; 
      break;
    }
 
    // List first few events, both info, hard process and complete events.
    if (iEvent < nList) { 
      info.list();
      pythia.process.list();
      event.list();
    }

    // Fill hard scale of event.
    pThard->Fill( info. pTHat() );

    // Loop over final charged particles in the event. 
    int nCharged = 0;
    for (int i = 0; i < event.size(); ++i) { 
      // for k0s
      if (event[i].id()==310 )  dndpT_k0s->Fill(event[i].pT());
      if(event[i].eta()>-0.35&&event[i].eta()<0.35) {
        if (event[i].id()==310 )  dndpT_k0s_mid->Fill(event[i].pT());
      }
      // Infly decay
      dndpT_infly_hadron->Fill( event[i].pT() );
      if (event[i].id()==211 || event[i].id()==-211 )  dndpT_infly_pion->Fill(event[i].pT());
      if (event[i].id()==321 || event[i].id()==-321 )  dndpT_infly_kaon->Fill(event[i].pT());
      if (event[i].id()==2212)  dndpT_infly_proton->Fill(event[i].pT());
      if (event[i].id()==-2212 )  dndpT_infly_antiproton->Fill(event[i].pT());
      if(event[i].eta()>-0.35&&event[i].eta()<0.35) {
        dndpT_infly_hadron_mid->Fill( event[i].pT() );
        if (event[i].id()==211 || event[i].id()==-211 )  dndpT_infly_pion_mid->Fill(event[i].pT());
        if (event[i].id()==321 || event[i].id()==-321 )  dndpT_infly_kaon_mid->Fill(event[i].pT());
        if (event[i].id()==2212)  dndpT_infly_proton_mid->Fill(event[i].pT());
        if (event[i].id()==-2212)  dndpT_infly_antiproton_mid->Fill(event[i].pT());
      }

      // hadron in final state
      if (event[i].isFinal()&&event[i].isCharged()) {
        dndpT_hadron->Fill( event[i].pT() );
        if (event[i].id()==211 || event[i].id()==-211 )  dndpT_pion->Fill(event[i].pT());
        if (event[i].id()==321 || event[i].id()==-321 )  dndpT_kaon->Fill(event[i].pT());
        if (event[i].id()==2212)  dndpT_proton->Fill(event[i].pT());
        if (event[i].id()==-2212 )  dndpT_antiproton->Fill(event[i].pT());
      }
      if(event[i].isFinal()&&event[i].isCharged()&&event[i].eta()>-0.35&&event[i].eta()<0.35) {
        dndpT_hadron_mid->Fill( event[i].pT() );
        if (event[i].id()==211 || event[i].id()==-211 )  dndpT_pion_mid->Fill(event[i].pT());
        if (event[i].id()==321 || event[i].id()==-321 )  dndpT_kaon_mid->Fill(event[i].pT());
        if (event[i].id()==2212)  dndpT_proton_mid->Fill(event[i].pT());
        if (event[i].id()==-2212)  dndpT_antiproton_mid->Fill(event[i].pT());
      }
      // Analyze charged particles and fill histograms.
      if(event[i].isFinal()&&event[i].isCharged()) {
        ++nCharged;
        dndy->Fill( event[i].y() );
      }
      // End of particle and event loops. Fill charged multiplicity.
    }
    mult->Fill( nCharged );
  }

  // Final statistics. Normalize and output histograms.
  pythia.statistics();
  timer.Stop(); timer.Print();

  fout->cd();
  pThard->Write();
  mult->Write();
  dndy->Write();
  dndpT_hadron->Write();
  dndpT_pion->Write();
  dndpT_kaon->Write();
  dndpT_proton->Write();
  dndpT_antiproton->Write();

  dndpT_infly_hadron->Write();
  dndpT_infly_pion->Write();
  dndpT_infly_kaon->Write();
  dndpT_infly_proton->Write();
  dndpT_infly_antiproton->Write();
  dndpT_k0s->Write();

  dndpT_hadron_mid->Write();
  dndpT_pion_mid->Write();
  dndpT_kaon_mid->Write();
  dndpT_proton_mid->Write();
  dndpT_antiproton_mid->Write();

  dndpT_infly_hadron_mid->Write();
  dndpT_infly_pion_mid->Write();
  dndpT_infly_kaon_mid->Write();
  dndpT_infly_proton_mid->Write();
  dndpT_infly_antiproton_mid->Write();
  dndpT_k0s_mid->Write();
  fout->Write();
  fout->Close();

  // Done.
  return 0;
}
