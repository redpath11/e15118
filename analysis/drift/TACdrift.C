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
void LoadProduction();
TProfile* PlotDrift(const char* det,
			const char* hname,
			const char* gate,
			Int_t binsy,
			Double_t ylo,
			Double_t yhi,
			Double_t pfxlo,
			Double_t pfxhi);
void CalculateOffsets(TProfile* h,int dev,Double_t bref,int part);
int TACdrift(int dev,double ref,int part);// MAIN FUNCTION

/* Function Definitions */

int TACdrift(int dev,double ref,int part)
{
  char buf[1024];

  std::cout << "tac refernce = " << ref << endl;
  

  TProfile* dhist = PlotDrift(Form("raw::sweeper.crdc%i.tac",dev),
    Form("c%itac",dev),
    Form("raw::sweeper.crdc%i.tac>=500",dev),400,0,4000,1000,1700);
  CalculateOffsets(dhist,dev,ref,part);

  return 1;

}

void CalculateOffsets(TProfile* h,int dev,Double_t bref,int part)
{
  char buf[1024];
  if(part==1){
    sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/crdc/TAC%idrift1.h",dev);
  }
  else{
    sprintf(buf,"/projects/e15118/redpath/analysis/calibrations/crdc/TAC%idrift2.h",dev);
  }

  std::ofstream outfile;
  outfile.open(buf);
  outfile << Form("#ifndef __HAVE_TAC%i_DRIFT",dev) << endl;
  outfile << Form("#define __HAVE_TAC%i_DRIFT",dev) << endl << endl;
  outfile << Form("class TAC%idrift",dev) << endl;
  outfile << "{" << endl;
  outfile << "public:" << endl << "void set_offset(int runnum)" << endl;
  outfile << "{" << endl << endl << "switch(runnum)" << endl << "{" << endl;

  Int_t nbins = h->GetNbinsX();
  Double_t bc=0.;
//  Double_t bref=0.;
  Double_t off=0.;
  int run=0;

if(part==1){

  for(Int_t i=3038;i<3122;i++)
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
}
else{
  for(Int_t i=3125;i<3180;i++)
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

  TCanvas* c1 = new TCanvas("c1","c1",1000,400);

/**/
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

