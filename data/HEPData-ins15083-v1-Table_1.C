void HEPData-ins15083-v1-Table_1()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Fri Mar  4 16:43:23 2022) by ROOT version 6.24/06
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",259,99,538,329);
   Canvas_1->Range(-2.725,-1.668714,45.905,3.387802);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetLogy();
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
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
   grae->SetTitle("doi:10.17182/hepdata.26285.v1/t1");
   grae->SetFillStyle(1000);
   
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.26285.v1/t1",100,2.138,41.042);
   Graph_Graph1D_y13001->SetMinimum(0.06869697);
   Graph_Graph1D_y13001->SetMaximum(762.3422);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y13001->SetLineColor(ci);
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("THETA [DEG]");
   Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("D(SIG)/D(OMEGA) [MB]");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   
   grae->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.2427985,0.9326147,0.7572015,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("doi:10.17182/hepdata.26285.v1/t1");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
