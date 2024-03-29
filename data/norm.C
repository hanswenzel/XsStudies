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

void norm()
{

  TFile *_file1 = TFile::Open("G4Elastic_proton_1000MeV_G4C.root");
  TH1D* hist1 = (TH1D*)_file1->Get("diff");
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  TFile *_file2 = TFile::Open("G4DiffuseElastic_proton_1000MeV_G4C.root");
  TH1D* hist2 = (TH1D*)_file2->Get("diff");
  for (int i=1;i<hist2->GetNbinsX()+1;i++)
    {
      hist2->SetBinContent(i, ((1e27*convert)/nevts)*(hist2->GetBinContent(i)/sterad(hist2->GetXaxis()->GetBinLowEdge(i),hist2->GetXaxis()->GetBinUpEdge(i))));
    }
  TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();


  Double_t Graph1D_y1_fx3001[45] = {
   5.23,
   5.49,
   5.78,
   6.36,
   6.64,
   6.93,
   7.22,
   7.51,
   7.79,
   8.08,
   8.37,
   8.94,
   9.52,
   9.81,
   10.09,
   10.38,
   10.67,
   10.96,
   11.24,
   11.53,
   11.82,
   12.1,
   12.39,
   12.68,
   12.97,
   13.54,
   14.11,
   14.69,
   15.26,
   15.83,
   16.41,
   16.98,
   17.55,
   18.13,
   18.7,
   19.27,
   19.84,
   20.7,
   21.27,
   21.56,
   22.13,
   22.7,
   23.27,
   24.41,
   25.55};
   Double_t Graph1D_y1_fy3001[45] = {
   1397,
   1205,
   1025,
   698,
   614,
   506,
   399,
   323,
   266,
   207,
   162,
   89.8,
   43.6,
   24,
   18.8,
   11.08,
   7.41,
   5.3,
   4.09,
   3.6,
   3.73,
   4.42,
   5.19,
   6.13,
   6.77,
   7.89,
   7.96,
   7.01,
   6.67,
   5.68,
   4.2,
   3.2,
   2.31,
   1.46,
   0.9,
   0.62,
   0.42,
   0.16,
   0.12,
   0.11,
   0.11,
   0.108,
   0.1,
   0.1,
   0.08};
   Double_t Graph1D_y1_felx3001[45] = {
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
   Double_t Graph1D_y1_fely3001[45] = {
   145.877,
   121.6933,
   104.8344,
   98.85363,
   62.37756,
   51.22851,
   43.37061,
   33.81257,
   27.2683,
   21.55203,
   16.47544,
   9.139497,
   5.849752,
   2.683282,
   1.973423,
   1.228236,
   1.068635,
   0.6090156,
   0.558284,
   0.4440721,
   0.4141606,
   0.5341947,
   0.6150293,
   0.8103512,
   0.8357206,
   0.9235372,
   1.053431,
   0.8384515,
   0.7355195,
   0.6569049,
   0.4695743,
   0.3417601,
   0.2754288,
   0.1715109,
   0.1204159,
   0.0688767,
   0.1366163,
   0.01835756,
   0.01442221,
   0.01421267,
   0.01252996,
   0.01344024,
   0.01486607,
   0.01280625,
   0.01442221};
   Double_t Graph1D_y1_fehx3001[45] = {
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
   Double_t Graph1D_y1_fehy3001[45] = {
   145.877,
   121.6933,
   104.8344,
   98.85363,
   62.37756,
   51.22851,
   43.37061,
   33.81257,
   27.2683,
   21.55203,
   16.47544,
   9.139497,
   5.849752,
   2.683282,
   1.973423,
   1.228236,
   1.068635,
   0.6090156,
   0.558284,
   0.4440721,
   0.4141606,
   0.5341947,
   0.6150293,
   0.8103512,
   0.8357206,
   0.9235372,
   1.053431,
   0.8384515,
   0.7355195,
   0.6569049,
   0.4695743,
   0.3417601,
   0.2754288,
   0.1715109,
   0.1204159,
   0.0688767,
   0.1366163,
   0.01835756,
   0.01442221,
   0.01421267,
   0.01252996,
   0.01344024,
   0.01486607,
   0.01280625,
   0.01442221};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(45,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
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


   hist1->SetTitle("1GeV proton on G4C" ); 
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
   legend->AddEntry(grae,"Phys.Rept. 42 (1978) 89-144, 1978" );
   legend->Draw();

}
