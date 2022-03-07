#include <iostream>
#include <TFile.h>
#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TFrame.h>
#include <TH1D.h>
#include <TH2D.h>
using namespace std;
// convert into steradians 
const double avogadro=6.02214e23;
// Pb:
//const double rho=11.35;
//const double A = 207.217;
// C
//const double rho=2.;
//const double A = 12.011;
// G4_Ar
//const double rho=0.00166201; // gas
const double rho= 1.396;     // liquid
const double A=39.948;
const double nevts = 1000000000;
const double thickness=1;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(cos(tmin*degtorad)-cos(tmax*degtorad));
  return sr;
}

void plotpi()
{
  TH2D  *hist2D = new  TH2D("hist2d", "differential cross section pi- on Argon",150, 0.,40., 13, 75., 725.);
  hist2D->GetZaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist2D->GetXaxis()->SetTitle("#theta");
  hist2D->GetYaxis()->SetTitle(" kinetic Energy [MeV]");
  hist2D->SetMinimum(0.01);
  hist2D->SetMaximum(1000000);
  hist2D->SetStats(0);
  
  const int points=13;
  TFile *_file[points];
  TH1D* hist[points];
  int j=0;
  TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();
  TLegend *legend = new TLegend(0.6,0.6,0.86,0.88);
  for (int j=0;j<13;j++)
    {
      int i=700-j*50;
      string str ="G4Elastic_pi-_"+ std::to_string(i)+"MeV_G4Ar.root";
      _file[j]= TFile::Open(str.c_str());
      hist[j]= (TH1D*)_file[j]->Get("diff2");
      for (int ii=1;ii<hist[j]->GetNbinsX()+1;ii++)
	{
	  hist[j]->SetBinContent(ii, ((1e27*convert)/nevts)*(hist[j]->GetBinContent(ii)/sterad(hist[j]->GetXaxis()->GetBinLowEdge(ii),hist[j]->GetXaxis()->GetBinUpEdge(ii))));
	  hist2D->SetBinContent(ii,13-j, ((1e27*convert)/nevts)*(hist[j]->GetBinContent(ii)/sterad(hist[j]->GetXaxis()->GetBinLowEdge(ii),hist[j]->GetXaxis()->GetBinUpEdge(ii))));
	}
      string str2="G4Elastic pi- on Ar "+std::to_string(i)+"MeV";
      hist[j]->SetTitle(str2.c_str() ); 
      legend->AddEntry(hist[j],str2.c_str());
      hist[j]->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
      hist[j]->GetXaxis()->SetTitle("#theta");
      //      hist[j]->SetMarkerColor(j+1);
      hist[j]->SetLineColor(j+1);
      //hist[j]->SetMarkerStyle(20+j);
      //hist[j]->SetMarkerSize(1.5);
      hist[j]->SetLineWidth (2);
      hist[j]->SetMinimum(0.01);
      hist[j]->SetMaximum(100000);
      hist[j] ->SetStats(0);
      if (j==0)
	{
	  hist[j]->Draw("HIST");
	} else
	{
	  hist[j]->Draw("SAMEHIST");
	}
    }
   legend->Draw();
   TCanvas *c2 = new TCanvas("c2","elastic scattering",1000,800);
   c2->cd();
   //  c2->SetGrid();
   c2->SetLogz();
   hist2D->Draw("surf1");
}
