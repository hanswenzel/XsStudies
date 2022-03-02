#include <iostream>
#include <TFile.h>
#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TFrame.h>
using namespace std;
// convert into steradians 
const double avogadro=6.02214e23;
// Pb:
//const double rho=11.35;
//const double A = 207.217;
// C
const double rho=2.;
const double A = 12.011;
const double nevts = 100000000;
const double thickness=1;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(cos(tmin*degtorad)-cos(tmax*degtorad));
  return sr;
}

void norm()
{

  TFile *_file0 = TFile::Open("B5.root");
  TH1D* hist1 = (TH1D*)_file0->Get("diff");
  //cout<<hist1->GetMean()<<endl;
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      /*
      cout << i<< "  "<< hist1->GetXaxis()->GetBinLowEdge(i)
	   << "  "<< hist1->GetXaxis()->GetBinUpEdge(i)
	   <<endl;
      */
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  hist1->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist1->GetXaxis()->SetTitle("#theta");
  hist1->Draw();
}
