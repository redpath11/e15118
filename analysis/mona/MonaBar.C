#define MonaBar_cxx
#include "MonaBar.h"

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
  fChain->SetBranchStatus("tmean[18][16]",1);
  fChain->SetBranchStatus("qmean[18][16]",1);
  fChain->SetBranchStatus("xpos[18][16]",1);
  fChain->SetBranchStatus("hit.wall[10]",1);
  fChain->SetBranchStatus("hit.bar[10]",1);
  fChain->SetBranchStatus("hit.x[10]",1);
  fChain->SetBranchStatus("mult",1);


  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    for(int layer=0;layer<18;layer++){
      for(int bar=0;bar<16;bar++){
      if(mult>=1 && qmean[layer][bar]>10.){
//        if(l_traw[layer][bar]!=-1 && l_qraw[layer][bar]>100.)
	{
	  ltq[layer][bar]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	  Ltq[layer]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	}
//	if(r_traw[layer][bar]!=-1 && r_qraw[layer][bar]>100.)
	{
	  rtq[layer][bar]->Fill(r_traw[layer][bar],r_qraw[layer][bar]);
	  Rtq[layer]->Fill(l_traw[layer][bar],l_qraw[layer][bar]);
	}
	if(xpos[layer][bar]!=-1){
	  xps[layer][bar]->Fill(xpos[layer][bar]);
	  Xps[layer]->Fill(xpos[layer][bar]);
	}
	if(hit_wall[0]==layer && hit_bar[0]==bar){
	  htx[layer][bar]->Fill(hit_x[0]);
	  Htx[layer]->Fill(hit_x[0]);
	}
	if(tmean[layer][bar]!=-1){
	  qtc[layer][bar]->Fill(tmean[layer][bar],qmean[layer][bar]);
	  QTc[layer]->Fill(tmean[layer][bar],qmean[layer][bar]);
	}
      }
      }
    }


    // if (Cut(ientry) < 0) continue;
  }
}


void MonaBar::PlotLayer(int layer){
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);
  palettea();

  TCanvas *c0 = new TCanvas("c0","c0",1800,1000);c0->Divide(4,4);
  TCanvas *c1 = new TCanvas("c1","c1",1800,1000);c1->Divide(4,4);
  TCanvas *c2 = new TCanvas("c2","c2",1800,1000);c2->Divide(4,4);
  TCanvas *c3 = new TCanvas("c3","c3",1800,1000);c3->Divide(4,4);
  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,4);

  for(int i=0;i<16;i++){
//    rtq[layer][i]->GetZaxis()->SetRangeUser(0.,60.);
//    ltq[layer][i]->GetZaxis()->SetRangeUser(0.,60.);
    c0->cd(i+1); rtq[layer][i]->Draw("COLZ");
    c1->cd(i+1); ltq[layer][i]->Draw("COLZ");
    c2->cd(i+1); xps[layer][i]->Draw();
    c3->cd(i+1); htx[layer][i]->Draw();
    c4->cd(i+1); qtc[layer][i]->Draw("COLZ");
  }
}


void MonaBar::PlotLayerSummary(){
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);
  
  TCanvas *c0 = new TCanvas("c0","c0",1800,1000);c0->Divide(4,4);
  TCanvas *c1 = new TCanvas("c1","c1",1800,1000);c1->Divide(4,4);
  TCanvas *c2 = new TCanvas("c2","c2",1800,1000);c2->Divide(4,4);
  TCanvas *c3 = new TCanvas("c3","c3",1800,1000);c3->Divide(4,4);
  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,4);
  TCanvas *c5 = new TCanvas("c5","c5",500,400);

  int pad=1;
  for(int i=1;i<18;i++){
  if(i!=8){
    c0->cd(pad); Rtq[i]->Draw("COLZ");
    c1->cd(pad); Ltq[i]->Draw("COLZ");
    c2->cd(pad); Xps[i]->Draw();
    c3->cd(pad); Htx[i]->Draw();
    c4->cd(pad); QTc[i]->Draw("COLZ");
    pad++;
  }
  }

  Double_t layerXposMean[16];
  Double_t layerHitxMean[16];
  Double_t yPt[16];

  TH2F *frame = new TH2F("frame","Summary;x [cm];Layer",2,-25,25,18,0,18);
  frame->SetStats(0); frame->GetYaxis()->SetLabelSize(0.08);
  for(int i=0;i<8;i++){
    layerXposMean[i] = Xps[i]->GetMean();
//    printf("Xpos %s Mean: %g\n",layer[i],Xps[i]->GetMean());
    printf("Xpos %s Mean: %g\n",layer[i],layerXposMean[i]);
    layerHitxMean[i] = Htx[i]->GetMean();
    yPt[i] = Double_t(i+1) + 0.5;
    frame->GetYaxis()->SetBinLabel(i+2,layer[i]);
  }
  for(int i=9;i<18;i++){
    layerXposMean[i-1] = Xps[i]->GetMean();
    printf("Xpos %s Mean: %g\n",layer[i],Xps[i]->GetMean());
    layerHitxMean[i-1] = Htx[i]->GetMean();
    yPt[i-1] = Double_t(i) + 0.5;
    frame->GetYaxis()->SetBinLabel(i+1,layer[i]);
  }
  yPt[0] = 1.5;
  yPt[16]= 17.5;

  TGraph *sumXpos = new TGraph(16,layerXposMean,yPt);
  TGraph *sumHitx = new TGraph(16,layerHitxMean,yPt);
  sumXpos->SetMarkerStyle(20); sumHitx->SetMarkerStyle(22);
  sumXpos->SetMarkerColor(2);  sumHitx->SetMarkerColor(4);

  c5->cd(); frame->Draw(); sumXpos->Draw("P");// sumHitx->Draw("SAMEP");
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
  const Double_t max=100.;// allO, F-27 in Si 2 && Si [i] vs. IC
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


