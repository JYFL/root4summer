#include <iostream>
#include "TMath.h"
#include "TF1.h"

using namespace std;

double digamma(double xx, double d=1e-1){
	return 1./TMath::Gamma(xx)*( TMath::Gamma(xx+d) - TMath::Gamma(xx-d) )/(2*d);
}
double digammaFuncWraper( double *xx, double *par){
	return digamma( xx[0], par[0]);
}

class MyFormular {
public:
	MyFormular();
	double Nc      ;
	double Nf      ; // # of fermions, 3, 4, 5
	double b       ; // //first coeff of the QCD beta func_
	double Gamma_e ;
	double Ns      ; // the medium parameter
	double LambdaQCD ; // MeV
	double R0;
	double x;
	double Ca;
	TF1 * fDigmmaFunc;

	double ROverR0(double e ){return TMath::Power(e*R0/LambdaQCD, - gammaA());}
	double gammaA(){ 
		return 1-TMath::Exp( -b/4/(Ca*Ns)*fDigmmaFunc->GetX( TMath::Log(1-x)+3./4./Ns-Gamma_e) ); 
	}
};

MyFormular::MyFormular(){
	Nc        = 3.;
	Nf        = 3.;
	b         = 11 - 2.*Nf/Nc;
	Gamma_e   = 0.5772;
	Ns        = 1;
	LambdaQCD = 250;
	R0        = 1;
	x         = 0.9 ;
	Ca        = 3;
	fDigmmaFunc = new TF1("fDigammaFunc", digammaFuncWraper, 0, 10, 1);
	fDigmmaFunc->SetParameter( 0,1e-10 );
}

void formular2(double e=200 ){
	MyFormular myfunc;

	
	double result = myfunc.ROverR0( e );
	cout<< result <<endl;

}	
