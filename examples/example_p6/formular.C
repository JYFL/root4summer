void formu(){
	double Nc      = 3.;
	double Nf      = 3.; // # of fermions, 3, 4, 5
	double b       = 11.-2.*Nf/Nc; // //first coeff of the QCD beta func_
	double Gamma_e = 0.5772;
	double Ns      = 1; // the medium parameter
	double LambdaQCD = 250; // MeV

	TF1 *fDgamma = new TF1("fDgamma", dgammaFunc, 0.5, 1, 2)
}


double ln(double x){ return TMath::Log(x);}
double digmma(double x, double d=1e-1){
	return 1./TMath::Gamma(x)*( TMath::Gamma(x+d) - TMath::Gamma(x-d) )/(2*d);
}
double deltaXi(double R, double Rprime, double E, doulble b, double LambdaQCD){
	return 1./b*ln(ln(E*R/LambdaQCD) / ln(E*Rprim/LambdaQCD) );
}

double solveFunc(){
	return digmma( 4*Ca*Ns*deltaXi ) - digammaRightFunc( x, Ns, Gamma_E);
}


double dgammaRightFuncWraper( Double_t *xx, Double_t *par ){
	dgammaFunc(xx[0], par[0], par[1]);
}

double dgammaRightFunc( Double_t x, Double_t  Ns, Double_t Gamma_E ){
	TMath::log( 1-x )+ 3./(4.*Ns) - Gamma_E;	
}

double dgammaLeftFunc( Double_t ){
}


