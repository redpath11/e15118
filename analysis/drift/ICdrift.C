#include"TROOT.h"
#include"TFile.h"
#include"TChain.h"
#include"TTree.h"
#include"TH1.h"
#include"TH2.h"
#include"TF1.h"
#include"TProfile.h"
#include"TAxis.h"
#include"TCanvas.h"
#include<iostream>
#include<fstream>

using namespace std;

/* Function Declarations */
void SetAliases(TTree* t);
TProfile* PlotDrift(const char* det,
			const char* hname,
			const char* gate,
			Int_t binsy,
			Double_t ylo,
			Double_t yhi,
			Double_t pfxlo,
			Double_t pfxhi);
void CalculateOffsets(TProfile* h,int ch,Double_t bref);
void SetReferenceRun(int runnum,const char* gate);
int ICdrift(int ch);// MAIN FUNCTION

/* Function Definitions */

int ICdrift(int ch)
{
  char buf[1024];
  Double_t ref[16];

  // Make sure you've selected a reference and run the SetReferenceRun macro first!
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/ic/ic_drift_ref.out");
  std::ifstream infile;
  infile.open(buf);

  for(int i=0;i<16;i++)
  {
    infile >> ref[i];
    std::cout << "ch = " << i << "; ref = " << ref[i] << endl;
  }

  TProfile* dhist = PlotDrift(Form("raw::sweeper.ic.raw[%i]",ch),Form("ic%i",ch),"",500,0,1000,100,900);
  CalculateOffsets(dhist,ch,ref[ch]);

  return 1;

  infile.close();

}

void CalculateOffsets(TProfile* h,int ch,Double_t bref)
{
  char buf[1024];
//  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/ic/ic%i_drift_offsets.txt",ch);
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/ic/IC%idrift.h",ch);
  std::ofstream outfile;
//  outfile.open("/projects/e15118/redpath/analysis/calibrations/ic/ic_drift_offsets.txt");
  outfile.open(buf);
  outfile << "#ifndef __HAVE_IC1_DRIFT" << endl;
  outfile << "#define __HAVE_IC1_DRIFT" << endl << endl;
  outfile << Form("class IC%idrift",ch) << endl;
  outfile << "{" << endl;
  outfile << "public:" << endl << "void set_offset(int runnum)" << endl;
  outfile << "{" << endl << endl << "switch(runnum)" << endl << "{" << endl;

  Int_t nbins = h->GetNbinsX();
  Double_t bc=0.;
//  Double_t bref=0.;
  Double_t off=0.;
  int run=0;

  for(Int_t i=3178;i>3050;i--)
  {
    Int_t bin = h->GetXaxis()->FindBin(i);
    bc = h->GetBinContent(bin);
//    bc = h->GetBinContent(i);
//    run = (int) h->GetXaxis()->GetBinUpEdge(i);
    if(bc>0)
    {
//      if(i==3178){ bref=bc; }
//      if(i==3179){ std::cout << "i " << i << "bc: " << bc << endl; bref=bc; }
      off = bref - bc;
      outfile << "case " << i << ":" << endl;
      outfile << "	offset = " << off << ";" << endl;
      outfile << "	break;" << endl;
    }

  }

  outfile << "default:" << endl;
  outfile << "	offset = 0.;" << endl;
  outfile << "	break;" << endl << "}" << endl << "};" << endl;
  outfile << "double GetValue(){ return (offset); };" << endl << endl;
  outfile << "private:" << endl << "	double offset;" << endl;
  outfile << "};" << endl << "#endif" << endl;
  outfile.close();

}


TProfile* PlotDrift(const char* det,
			const char* hname,
			const char* gate,
			Int_t binsy,
			Double_t ylo,
			Double_t yhi,
			Double_t pfxlo,
			Double_t pfxhi)
{

  TString filename = "/mnt/analysis/e15118/playground/all_unr27F.root";
//  TString filename = "/mnt/analysis/e15118/playground/ictof_unr27F.root";
  TFile* f = new TFile(filename, "READ");
  TTree* t = (TTree*)f->Get("t");

  const Int_t runbins = 145;
  const Int_t runlow = 3035;
  const Int_t runhi = 3180;

  SetAliases(t);

  TCanvas* c1 = new TCanvas("c1","c1",1600,500);

  TH2D* drift = new TH2D("drift",Form("%s drift;run number;%s",det,det),runbins,runlow,runhi,binsy,ylo,yhi);
  TProfile* drift_pfx = new TProfile("drift_pfx",Form("%s_pfx",hname),runbins,runlow,runhi);
  t->Project("drift",Form("%s:runnum",det),gate);
  drift->ProfileX("drift_pfx",1,binsy,"do");
  drift_pfx->GetYaxis()->SetRangeUser(pfxlo,pfxhi);

  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);
  drift->Draw("COLZ");
  c1->cd(2);
  drift_pfx->Draw();
  drift_pfx->Fit("pol1");
/*
  c1->Update();
  TPaveStats *st = (TPaveStats*)drift->GetListOfFunctions()->FindObject("stats");
  TPaveStats *stpfx = (TPaveStats*)drift_pfx->FindObject("stats");
//  st->SetOptStats("n");
  st->SetX1NDC(x1);
  st->SetX2NDC(x2);
  st->SetY1NDC(y1);
  st->SetY2NDC(y2);

  stpfx->SetX1NDC(x1);
  stpfx->SetX2NDC(x2);
  stpfx->SetY1NDC(yp1);
  stpfx->SetY2NDC(yp2);

  c1->Update();
  c1->Modified();
*/

  return drift_pfx;

  f->Close();

}


// Specify the reference run and gate for drift correction.
// This macro will generate a file containing distribution
// means for each IC channel. This file can then be read
// into the main function to set the reference value for
// which the offsets are calculated.
void SetReferenceRun(Int_t runnum,const char* gate)
{
//  TFile* f = new TFile(Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",runnum));
  TFile* f = new TFile(Form("/mnt/analysis/e15118/root_sweeper/run-%i-sweeper_cal.root",runnum));
  TTree* t = (TTree*)f->Get("t");
  SetAliases(t);

  char buf[1024];

  TH1D* ic[16];
  TF1* fPk[16];

  // file to write out reference means
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/ic/ic_drift_ref.out");
  std::ofstream outfile;
  outfile.open(buf);

  // Declare badpads
  const int ic_badpads[4] = {0,4,7,15};
  int idx=0;

  TCanvas* c1 = new TCanvas("c1","c1",1600,900);
  c1->Divide(4,4);

  // Increment through IC chs and fit
  for(int ch=0;ch<16;ch++)
  {
    ic[ch] = new TH1D(Form("ic%i",ch),Form("IC ch%i;dE (arb)",ch),500,0,1000);
    fPk[ch]= new TF1(Form("fPk%i",ch),"gaus",100,900);

    if(ch!=ic_badpads[idx])
    {
      c1->cd(ch+1);
      t->Project(Form("ic%i",ch),Form("raw::sweeper.ic.raw[%i]",ch),gate);
      ic[ch]->Draw();
      ic[ch]->Fit(fPk[ch],"R");

      Double_t mean = fPk[ch]->GetParameter(1);

      outfile << mean << endl;
    }
    else
    {
      outfile << 1. << endl;
      idx++;
    }
    
  }

  outfile.close();

  c1->Print("/projects/e15118/redpath/analysis/calibrations/ic/ic_drift_ref.png");

}




void SetAliases(TTree* t)
{
  t->SetAlias("validcrdc1","crdc1.x!=-1 && crdc1.y!=-1");
  t->SetAlias("validcrdc2","crdc2.x!=-1 && crdc2.y!=-1");
  t->SetAlias("crdc2cnter","crdc2.x>-10. && crdc2.x<10. && crdc2.y>-10. && crdc2.y<10.");  
  t->SetAlias("validcrdcs","validcrdc1 && validcrdc2");

  t->SetAlias("ic_sum","(ic.cal[0]+ic.cal[1]+ic.cal[2]+ic.cal[3]+ic.cal[4]+ic.cal[5]+ic.cal[6]+ic.cal[7]+ic.cal[8]+ic.cal[9]+ic.cal[10]+ic.cal[11]+ic.cal[12]+ic.cal[13]+ic.cal[14]+ic.cal[15])/16");
  t->SetAlias("ic_sum_raw","(raw::sweeper.ic.raw[1]+raw::sweeper.ic.raw[2]+raw::sweeper.ic.raw[3]+raw::sweeper.ic.raw[5]+raw::sweeper.ic.raw[6]+raw::sweeper.ic.raw[8]+raw::sweeper.ic.raw[9]+raw::sweeper.ic.raw[10]+raw::sweeper.ic.raw[11]+raw::sweeper.ic.raw[12]+raw::sweeper.ic.raw[13]+raw::sweeper.ic.raw[14])/12");

  /* Graphical (2D) cuts */
  // Beam ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/F27_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Ne28_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Obeam.C");
  // Element ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/r1060_unrO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO_ictof.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/unr27F_ictof.C");

  // Segmented Target
  // detector 0
  t->SetAlias("LU0","raw::sweeper.st.raw[4]");
  t->SetAlias("RU0","raw::sweeper.st.raw[5]");
  t->SetAlias("RD0","raw::sweeper.st.raw[6]");
  t->SetAlias("LD0","raw::sweeper.st.raw[7]");
  /*
  t->SetAlias("LU0","st.corner[0][0]");
  t->SetAlias("RU0","st.corner[0][1]");
  t->SetAlias("RD0","st.corner[0][2]");
  t->SetAlias("LD0","st.corner[0][3]");
  */
  t->SetAlias("S0","LU0+RU0+RD0+LD0");
  t->SetAlias("SL0","LU0+LD0");
  t->SetAlias("SR0","RU0+RD0");
  t->SetAlias("Sup0","LU0+RU0");
  t->SetAlias("Sdn0","LD0+RD0");
  t->SetAlias("x0","(SL0-SR0)/S0");
  t->SetAlias("y0","(Sup0-Sdn0)/S0");

  // Segmented Target
  // detector 1
  t->SetAlias("LU1","raw::sweeper.st.raw[0]");
  t->SetAlias("RU1","raw::sweeper.st.raw[1]");
  t->SetAlias("RD1","raw::sweeper.st.raw[2]");
  t->SetAlias("LD1","raw::sweeper.st.raw[3]");
  /*
  t->SetAlias("LU1","st.corner[1][0]");
  t->SetAlias("RU1","st.corner[1][1]");
  t->SetAlias("RD1","st.corner[1][2]");
  t->SetAlias("LD1","st.corner[1][3]");
  */
  t->SetAlias("S1","LU1+RU1+RD1+LD1");
  t->SetAlias("SL1","LU1+LD1");
  t->SetAlias("SR1","RU1+RD1");
  t->SetAlias("Sup1","LU1+RU1");
  t->SetAlias("Sdn1","LD1+RD1");
  t->SetAlias("x1","(SL1-SR1)/S1");
  t->SetAlias("y1","(Sup1-Sdn1)/S1");

  // Segmented Target
  // detector 2
  t->SetAlias("LU2","raw::sweeper.st.raw[12]");
  t->SetAlias("RU2","raw::sweeper.st.raw[13]");
  t->SetAlias("RD2","raw::sweeper.st.raw[14]");
  t->SetAlias("LD2","raw::sweeper.st.raw[15]");
  /*
  t->SetAlias("LU2","st.corner[2][0]");
  t->SetAlias("RU2","st.corner[2][1]");
  t->SetAlias("RD2","st.corner[2][2]");
  t->SetAlias("LD2","st.corner[2][3]");
  */
  t->SetAlias("S2","LU2+RU2+RD2+LD2");
  t->SetAlias("SL2","LU2+LD2");
  t->SetAlias("SR2","RU2+RD2");
  t->SetAlias("Sup2","LU2+RU2");
  t->SetAlias("Sdn2","LD2+RD2");
  t->SetAlias("x2","(SL2-SR2)/S2");
  t->SetAlias("y2","(Sup2-Sdn2)/S2");

  // Segmented Target
  // detector 3
  t->SetAlias("LU3","raw::sweeper.st.raw[8]");
  t->SetAlias("RU3","raw::sweeper.st.raw[9]");
  t->SetAlias("RD3","raw::sweeper.st.raw[10]");
  t->SetAlias("LD3","raw::sweeper.st.raw[11]");
  /*
  t->SetAlias("LU3","st.corner[3][0]");
  t->SetAlias("RU3","st.corner[3][1]");
  t->SetAlias("RD3","st.corner[3][2]");
  t->SetAlias("LD3","st.corner[3][3]");
  */
  t->SetAlias("S3","LU3+RU3+RD3+LD3");
  t->SetAlias("SL3","LU3+LD3");
  t->SetAlias("SR3","RU3+RD3");
  t->SetAlias("Sup3","LU3+RU3");
  t->SetAlias("Sdn3","LD3+RD3");
  t->SetAlias("x3","(SL3-SR3)/S3");
  t->SetAlias("y3","(Sup3-Sdn3)/S3");

}




