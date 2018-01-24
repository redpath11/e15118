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

/* Mapping of ADC channel to detector */
const int chMap[4] = {16,20,24,31};
/* Function Declarations */
//void SetAliases(TChain t);
void SetTreeAliases(TTree *t);
void LoadProduction();
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
int SIdrift(int det);// MAIN FUNCTION

/* Function Definitions */

int SIdrift(int det)
{
  char buf[1024];
  Double_t ref[4];

  // Make sure you've selected a reference and run the SetReferenceRun macro first!
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/psd/si_drift_ref.out");
  std::ifstream infile;
  infile.open(buf);

  for(int i=0;i<4;i++)
  {
    infile >> ref[i];
    std::cout << "ch = " << chMap[i] << "; ref = " << ref[i] << endl;
  }

  TProfile* dhist = PlotDrift(Form("raw::sweeper.st.raw[%i]",chMap[det]),
    Form("st.%i",chMap[det]),
    Form("raw::sweeper.st.raw[%i]>100 && F27_tight",chMap[det]),400,0,4000,0,4000);
  CalculateOffsets(dhist,det,ref[det]);

  infile.close();

  return 1;

}

void CalculateOffsets(TProfile* h,int ch,Double_t bref)
{
  char buf[1024];
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/psd/SI%idrift.h",ch);
  std::ofstream outfile;
  outfile.open(buf);
  outfile << Form("#ifndef __HAVE_SI%i_DRIFT",ch) << endl;
  outfile << Form("#define __HAVE_IC%i_DRIFT",ch) << endl << endl;
  outfile << Form("class SI%idrift",ch) << endl;
  outfile << "{" << endl;
  outfile << "public:" << endl << "void set_offset(int runnum)" << endl;
  outfile << "{" << endl << endl << "switch(runnum)" << endl << "{" << endl;

  Int_t nbins = h->GetNbinsX();
  Double_t bc=0.;
//  Double_t bref=0.;
  Double_t off=0.;
  int run=0;

  for(Int_t i=3038;i<3180;i++)
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
  TChain t("t");
  LoadProduction();

  const Int_t runbins = 145;
  const Int_t runlow = 3035;
  const Int_t runhi = 3180;

//  SetAliases(t);
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


  TCanvas* c1 = new TCanvas("c1","c1",1000,400);

  TH2D* drift = new TH2D("drift",Form("%s drift;run number;%s",det,det),runbins,runlow,runhi,binsy,ylo,yhi);
  TProfile* drift_pfx = new TProfile("drift_pfx",Form("%s_pfx",hname),runbins,runlow,runhi);
  t.Project("drift",Form("%s:runnum",det),gate);
  drift->ProfileX("drift_pfx",1,binsy,"do");
  drift_pfx->GetYaxis()->SetRangeUser(pfxlo,pfxhi);

  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);
  drift->Draw("COLZ");
  c1->cd(2);
  drift_pfx->Draw();
//  drift_pfx->Fit("pol1");
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

}


// Specify the reference run and gate for drift correction.
// This macro will generate a file containing distribution
// means for each IC channel. This file can then be read
// into the main function to set the reference value for
// which the offsets are calculated.
void SetReferenceRun(Int_t runnum,const char* gate)
{
//  TFile* f = new TFile(Form("/mnt/analysis/e15118/root_sweeper/run-%i-sweeper_cal.root",runnum));
  TFile* f = new TFile(Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",runnum));
  TTree* t = (TTree*)f->Get("t");
  SetTreeAliases(t);

  char buf[1024];

  TH1D* st[4];
  TF1* fPk[4];

  // file to write out reference means
  sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/psd/si_drift_ref.out");
  std::ofstream outfile;
  outfile.open(buf);

  TCanvas* c1 = new TCanvas("c1","c1",1800,400);
  c1->Divide(4,1);

  // Increment through IC chs and fit
  for(int ch=0;ch<4;ch++){
    st[ch] = new TH1D(Form("st%i",ch),Form("si %i;dE (arb)",ch),400,0,4000);
    fPk[ch]= new TF1(Form("fPk%i",ch),"gaus",500,3500);

    c1->cd(ch+1);
    t->Project(Form("st%i",ch),Form("raw::sweeper.st.raw[%i]",chMap[ch]),
      Form("raw::sweeper.st.raw[%i]>100&&%s",chMap[ch],gate));
    st[ch]->Draw();
    st[ch]->Fit(fPk[ch],"R");

    Double_t mean = fPk[ch]->GetParameter(1);

    outfile << mean << endl;
    
  }

  outfile.close();

  c1->Print("/projects/e15118/redpath/analysis/calibrations/psd/si_drift_ref.png");

}



/*
void SetAliases(TChain t)
{
  t.SetAlias("validcrdc1","crdc1.x!=-1 && crdc1.y!=-1");
  t.SetAlias("validcrdc2","crdc2.x!=-1 && crdc2.y!=-1");
  t.SetAlias("crdc2cnter","crdc2.x>-10. && crdc2.x<10. && crdc2.y>-10. && crdc2.y<10.");  
  t.SetAlias("validcrdcs","validcrdc1 && validcrdc2");

  t.SetAlias("ic_sum","(ic.cal[0]+ic.cal[1]+ic.cal[2]+ic.cal[3]+ic.cal[4]+ic.cal[5]+ic.cal[6]+ic.cal[7]+ic.cal[8]+ic.cal[9]+ic.cal[10]+ic.cal[11]+ic.cal[12]+ic.cal[13]+ic.cal[14]+ic.cal[15])/16");
  t.SetAlias("ic_sum_raw","(raw::sweeper.ic.raw[1]+raw::sweeper.ic.raw[2]+raw::sweeper.ic.raw[3]+raw::sweeper.ic.raw[5]+raw::sweeper.ic.raw[6]+raw::sweeper.ic.raw[8]+raw::sweeper.ic.raw[9]+raw::sweeper.ic.raw[10]+raw::sweeper.ic.raw[11]+raw::sweeper.ic.raw[12]+raw::sweeper.ic.raw[13]+raw::sweeper.ic.raw[14])/12");

  // Beam ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/F27_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Ne28_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Obeam.C");
  // Element ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/r1060_unrO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO_ictof.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/unr27F_ictof.C");


}
*/

void SetTreeAliases(TTree *t)
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


}





void LoadProduction(){//34 runs
    char buffer[1024];

/**/
    for(int i=1038;i<1043;i++)
    {
      sprintf(buffer,"t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");",i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
    }


    for(int i=1051;i<1087;i++)
    {
      if(i!=1075 && i!=1080 && i!=1081)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    /* runs with bad crdc 2 */
    for(int i=1089;i<1120;i++)
    {
      if(i!=1099 && i!=1115 && i!=1116)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }
    }
    

    for(int i=1125;i<1160;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    for(int i=1164;i<1180;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }




}
