#define MonaBar_cxx
#include "MonaBar.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MonaBar::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MonaBar.C
//      Root > MonaBar t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("l.traw[18][16]",1);
  fChain->SetBranchStatus("l.qraw[18][16]",1);
  fChain->SetBranchStatus("r.traw[18][16]",1);
  fChain->SetBranchStatus("r.qraw[18][16]",1);

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    for(int layer=0;layer<18;layer++){
      for(int bar=0;bar<16;bar++){
        if(l_traw[layer][bar]!=-1)// && l_qraw[layer][bar]>300.)
	{
	  ltq[layer][bar]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	  Ltq[layer]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	}
	if(r_traw[layer][bar]!=-1)// && r_qraw[layer][bar]>300.)
	{
	  rtq[layer][bar]->Fill(r_traw[layer][bar],r_qraw[layer][bar]);
	  Rtq[layer]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	}
	if(xpos[layer][bar]!=-1){
	  xps[layer][bar]->Fill(xpos[layer][bar]);
	  Xps[layer][bar]->Fill(xpos[layer][bar]);
	}
      }
    }
   // if (Cut(ientry) < 0) continue;
  }
}


void MonaBar::Plot(){
  TCanvas *c0 = new TCanvas("c0","c0",1800,1000);c0->Divide(4,4);
  TCanvas *c1 = new TCanvas("c1","c1",1800,1000);c1->Divide(4,4);
  TCanvas *c2 = new TCanvas("c2","c2",1800,1000);c2->Divide(4,4);
  TCanvas *c3 = new TCanvas("c3","c3",1800,1000);c3->Divide(4,4);

  Int_t pad = 1;
  for(int i=0;i<18;i++){
    for(int j=0;j<16;j++){
      c0->cd(j+1);
      rtq[i][j]->Draw("COLZ");
      c1->cd(j+1);
      ltq[i][j]->Draw("COLZ");
    }
    c0->Print(Form("/projects/e15118/redpath/analysis/mona/qtPlots/rLayer%s_tq.png",layer[i]));
    c1->Print(Form("/projects/e15118/redpath/analysis/mona/qtPlots/lLayer%s_tq.png",layer[i]));
    if(i>=1 && i!=8){c2->cd(pad); Rtq[i]->Draw("COLZ"); c3->cd(pad); Ltq[i]->Draw("COLZ");pad++;}
  }
}


void MonaBar::PlotLayer(int layer){
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);
  palettea();

  TCanvas *c0 = new TCanvas("c0","c0",1800,1000);c0->Divide(4,4);
  TCanvas *c1 = new TCanvas("c1","c1",1800,1000);c1->Divide(4,4);

  for(int i=0;i<16;i++){
    rtq[layer][i]->GetZaxis()->SetRangeUser(0.,60.);
    ltq[layer][i]->GetZaxis()->SetRangeUser(0.,60.);
    c0->cd(i+1); rtq[layer][i]->Draw("COLZ");
    c1->cd(i+1); ltq[layer][i]->Draw("COLZ");
  }
}


void MonaBar::DrawLayers(){
  TCanvas *c2 = new TCanvas("c2","c2",1800,1000);c2->Divide(4,4);
  TCanvas *c3 = new TCanvas("c3","c3",1800,1000);c3->Divide(4,4);

  for(int i=1;i<18;i++){
    if(i!=8){
    c2->cd(i); Rtq[i]->Draw("COLZ"); c3->cd(i); Ltq[i]->Draw("COLZ");
    }
  }
}


void palettea()
{
  const Int_t NRGBs = 6;
  const Int_t NCont = 999;

  Double_t stops[NRGBs] = { 0.00, 0.1, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.99, 0.0, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.0, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.99, 0.0, 1.00, 0.12, 0.00, 0.00 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  const Double_t min=0.0;
//  const Double_t max=55.;// allO, F-27 in Si 0
//  const Double_t max=50.;// allO, F-27 in Si 1
  const Double_t max=90.;// allO, F-27 in Si 2 && Si [i] vs. IC
//  const Double_t max=50.;// allO_Oic3, F-27 in Si 0
//  const Double_t max=25.;// allO_Oic3, F-27 in Si 2
//  const Double_t max=8.;// nvelRecal_27F_O, gated on O-24
//  const Double_t max=7.;// nvelRecal_27F_O, gated on O-23
//  const Double_t max=6.;// nvelRecal_27F_O, gated on O-22

  const Int_t nLevels = 999;
  Double_t levels[nLevels];

  for(int i=1;i<nLevels;i++)
  {  levels[i] = min + (max-min) / (nLevels-1) * (i);  }
  levels[0] = -1.;
}


