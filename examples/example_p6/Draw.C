int gColor[] = { kBlack, kRed, kBlue, kMagenta, kGreen };
void Draw(){
    const int nEnergy = 3;
    int EnergyBin[nEnergy] = { 150, 200, 300 };
    TFile * inRoot[nEnergy];
    TH1D * hEnergyInR[nEnergy];
    TH1D * hEnergyInPhi[nEnergy];
    TGraph * gEnergyInR[nEnergy];
    for( int i=0;i<nEnergy;i++ ){
        inRoot[i] = new TFile(Form("out%d.root",EnergyBin[i]));
        hEnergyInR[i] = (TH1D*)inRoot[i]->Get("hEnergyInR");
        gEnergyInR[i] = new TGraph( hEnergyInR[i]->GetNbinsX() );
        for( int ib=1;ib<hEnergyInR[i]->GetNbinsX();ib++ ){
            gEnergyInR[i]->SetPoint(ib-1, hEnergyInR[i]->GetBinContent(ib), hEnergyInR[i]->GetBinCenter(ib));
        }
        hEnergyInPhi[i] = (TH1D*)inRoot[i]->Get("hEnergyInPhi");
    }

    TCanvas *c1 = new TCanvas();
    TH2F * hfr1 = new TH2F("hfr1","Energy in R / E_{all}",10,0,4,10,0,1);
    hfr1->Draw();
    gPad->SetGridx(1);
    gPad->SetGridy(1);
    TLegend *leg = new TLegend(.5,.5,.8,.8);
    for( int i=0;i<nEnergy;i++ ){
        hEnergyInR[i]->SetLineColor( gColor[i] );
        hEnergyInR[i]->Draw("same");
        leg->AddEntry(hEnergyInR[i],Form("%dGeV",EnergyBin[i]),"l");
    }
    leg->Draw();

    /* 
    TCanvas *c2 = new TCanvas();
    TH2F * hfr2 = new TH2F("hfr2","Energy in Phi / E_{all}",10,0,4,10,0,1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);
    hfr2->Draw();
    TLegend *leg2 = new TLegend(.5,.5,.8,.8);
    for( int i=0;i<nEnergy;i++ ){
        hEnergyInPhi[i]->SetLineColor( gColor[i] );
        hEnergyInPhi[i]->Draw("same");
        leg2->AddEntry(hEnergyInPhi[i],Form("%dGeV",EnergyBin[i]),"l");
    }
    leg2->Draw();
    */

    TCanvas *cRE = new TCanvas();
    //TH2F * hfrRE = new TH2F("hfrRE","",10,EnergyBin[0]*.9,EnergyBin[nEnergy-1]*1.2,10,1e-2,1e1);
    TH2F * hfrRE = new TH2F("hfrRE","",10,1e1, 1e6, 10 ,1e-2,1e1);
    hfrRE->Draw();
    gPad->SetGridx(1);
    gPad->SetGridy(1);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    TLegend * legRE = new TLegend(.5,.5,.8,.8);
    double frac[] = { 0.1, 0.3,0.5,0.7, 0.9 };
    int nFrac  = sizeof(frac)/sizeof(double);
    TGraph * gREnergy[10];
    for( int ifrac=0;ifrac<nFrac;ifrac++ ){
        gREnergy[ifrac] = new TGraph(nEnergy);
        gREnergy[ifrac]->SetName( Form("%.0f%%",frac[ifrac]*100));
        cRE->cd( ifrac+1 );
        for( int i=0;i<nEnergy;i++ ){
            double r = gEnergyInR[i]->Eval( frac[ifrac] );
            gREnergy[ifrac]->SetPoint(i, EnergyBin[i], r );
        }
        gREnergy[ifrac]->SetLineColor(gColor[ifrac]);
        gREnergy[ifrac]->Draw("pl");
        legRE->AddEntry( gREnergy[ifrac], Form("%.0f%%",frac[ifrac]*100),"lp");
        //TF1 * func = gREnergy[ifrac]->GetFunction(Form("fitFunc%d",frac[ifrac]*100));
        //TF1 * func = gREnergy[ifrac]->GetFunction("pol1");
        TF1 * func = new TF1("loglog","TMath::Exp([0]*TMath::Log(x)+[1])");
        gREnergy[ifrac]->Fit(func);
        func->SetLineColor(gColor[ifrac]);
        func->SetRange( 1e1, 1e6 );
        func->Draw("same");
    }
    legRE->Draw();

}
