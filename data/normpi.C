#include <iostream>
#include <TFile.h>
#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
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
const double nevts = 1000000000;
const double thickness=1;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(cos(tmin*degtorad)-cos(tmax*degtorad));
  return sr;
}

void normpi()
{

  TFile *_file1 = TFile::Open("G4Elastic_pi-_800MeV_G4C.root");
  TH1D* hist1 = (TH1D*)_file1->Get("diff2");
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  TFile *_file2 = TFile::Open("G4DiffuseElastic_pi-_800MeV_G4C.root");
  TH1D* hist2 = (TH1D*)_file2->Get("diff2");
  for (int i=1;i<hist2->GetNbinsX()+1;i++)
    {
      hist2->SetBinContent(i, ((1e27*convert)/nevts)*(hist2->GetBinContent(i)/sterad(hist2->GetXaxis()->GetBinLowEdge(i),hist2->GetXaxis()->GetBinUpEdge(i))));
    }
  TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();
  Double_t Graph1D_y1_fx3001[31] = {
   5.38,
   6.45,
   6.96,
   8.03,
   9.1,
   10.2,
   11.2,
   12.3,
   13.4,
   14.4,
   15.5,
   16.6,
   17.6,
   18.7,
   19.8,
   20.8,
   21.9,
   23,
   24,
   25.1,
   26.2,
   27.2,
   28.3,
   30.4,
   31.5,
   32.5,
   33.6,
   34.7,
   35.7,
   36.8,
   37.8};
   Double_t Graph1D_y1_fy3001[31] = {
   587,
   526,
   500,
   423,
   364,
   278,
   252,
   191,
   137,
   102,
   72.6,
   47.7,
   29.6,
   18,
   9.63,
   4.94,
   2.02,
   0.725,
   0.174,
   0.214,
   0.444,
   0.57,
   0.751,
   0.814,
   0.793,
   0.702,
   0.543,
   0.507,
   0.332,
   0.25,
   0.139};
   Double_t Graph1D_y1_felx3001[31] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fely3001[31] = {
   106.0453,
   86.03313,
   79.61087,
   66.26245,
   56.49257,
   42.8637,
   38.52523,
   29.07618,
   20.83428,
   15.49969,
   11.05623,
   7.245248,
   4.541124,
   2.763925,
   1.489169,
   0.7755785,
   0.3350493,
   0.133947,
   0.04936416,
   0.05438401,
   0.0877918,
   0.1050298,
   0.1309157,
   0.1382297,
   0.1354553,
   0.1246474,
   0.1040824,
   0.09749155,
   0.07301781,
   0.06839656,
   0.06267003};
   Double_t Graph1D_y1_fehx3001[31] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fehy3001[31] = {
   106.0453,
   86.03313,
   79.61087,
   66.26245,
   56.49257,
   42.8637,
   38.52523,
   29.07618,
   20.83428,
   15.49969,
   11.05623,
   7.245248,
   4.541124,
   2.763925,
   1.489169,
   0.7755785,
   0.3350493,
   0.133947,
   0.04936416,
   0.05438401,
   0.0877918,
   0.1050298,
   0.1309157,
   0.1382297,
   0.1354553,
   0.1246474,
   0.1040824,
   0.09749155,
   0.07301781,
   0.06839656,
   0.06267003};


  
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(31,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.70484.v1/t1");
   grae->SetFillStyle(1000);
   
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.70484.v1/t1",100,3.198,27.582);
   Graph_Graph1D_y13001->SetMinimum(0.01);
   Graph_Graph1D_y13001->SetMaximum(10000);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y13001->SetLineColor(7);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("#theta");
   //   Graph_Graph1D_y13001->GetXaxis()->SetTitle("THETA(P=3,RF=CM) [DEG]");
     Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   //Graph_Graph1D_y13001->GetYaxis()->SetTitle("D(SIG)/D(OMEGA(P=3,RF=CM)) [MB/SR]");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   grae->SetMarkerColor(2);
   grae->SetLineColor(2);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(1.5);
   grae->SetLineWidth (2);
   grae->SetMinimum(0.01);
   grae->SetMaximum(10000);


   hist1->SetTitle("800 MeV pi- on G4C" ); 
  hist1->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist1->GetXaxis()->SetTitle("#theta");
  hist1->SetMarkerColor(4);
  hist1->SetLineColor(4);
  hist1->SetMarkerStyle(20);
  hist1->SetMarkerSize(1);
  hist1->SetLineWidth (2);
  hist1->SetMinimum(0.01);
  hist1->SetMaximum(10000);
  hist1 ->SetStats(0);
  hist2->SetMarkerColor(3);
  hist2->SetLineColor(3);
  hist2->SetMarkerStyle(21);
  hist2->SetMarkerSize(1);
  hist2->SetLineWidth (2);
  hist1->Draw("HIST");
  hist2->Draw("SAMEHIST");
  grae->Draw("SAME");
   TLegend *legend = new TLegend(0.5,0.5,0.86,0.88);
   legend->AddEntry(hist1,"Geant4_11_0 G4Elastic");
   legend->AddEntry(hist2,"Gent4_11_0 G4DiffuseElastic");
   legend->AddEntry(grae,"Phys.Rev.C 30 (1984) 1662, 1984." );
   legend->Draw();

}
