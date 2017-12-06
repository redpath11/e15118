//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 15 10:32:12 2017 by ROOT version 5.34/32
// from TTree t/Combined tree created from run-0203-00-lisa.root
// found on file: run-0203-lisa_15Nov2017.root
//////////////////////////////////////////////////////////

#ifndef MonaBar_h
#define MonaBar_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TGraph.h>
#include <TString.h>
#include <TColor.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.
#include "/projects/e15118/n2analysis/src/./mona.hh"

// Fixed size dimensions of array or collections stored in the TTree if any.

class MonaBar {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   int runCount;
   const char *layer[18];

   // Layer summaries
   TH2F *Rtq[18];
   TH2F *Ltq[18];
   TH1F *Xps[18];
   TH1F *Htx[18];
   TH2F *QTc[18];

   // Indv bars
   TH2F *rtq[18][16];
   TH2F *ltq[18][16];
   TH1F *xps[18][16];
   TH1F *htx[18][16];
   TH2F *qtc[18][16];

   TCanvas *c0;
   TCanvas *c1;
   TCanvas *c2;
   TCanvas *c3;


   // Declaration of leaf types
 //cal::mona       *cal__mona;
   Int_t           mult;
   Double_t        l_tcal[18][16];
   Double_t        l_qcal[18][16];
   Double_t        r_tcal[18][16];
   Double_t        r_qcal[18][16];
   Double_t        xpos[18][16];
   Double_t        tmean[18][16];
   Double_t        qmean[18][16];
   Double_t        hit_x[10];
   Double_t        hit_y[10];
   Double_t        hit_z[10];
   Double_t        hit_rho[10];
   Double_t        hit_phi[10];
   Double_t        hit_theta[10];
   Double_t        hit_t[10];
   Double_t        hit_v[10];
   Double_t        hit_ke[10];
   Double_t        hit_q[10];
   Int_t           hit_wall[10];
   Int_t           hit_bar[10];
   Double_t        x;
   Double_t        y;
   Double_t        z;
   Double_t        rho;
   Double_t        phi;
   Double_t        theta;
   Double_t        t;
   Double_t        v;
   Double_t        ke;
   Double_t        q;
 //raw::mona       *raw__mona;
   Short_t         trigger_monapattern;
   Short_t         trigger_monahits;
   Short_t         trigger_monacount_pattern[3];
   Short_t         trigger_monatimestamp[4];
   Short_t         trigger_lisapattern;
   Short_t         trigger_lisahits;
   Short_t         trigger_lisacount_pattern[3];
   Short_t         trigger_lisatimestamp[4];
   Short_t         l_traw[18][16];
   Short_t         l_qraw[18][16];
   Short_t         r_traw[18][16];
   Short_t         r_qraw[18][16];
   UInt_t          runnum;

   // List of branches
   TBranch        *b_cal__mona_mult;   //!
   TBranch        *b_cal__mona_l_tcal;   //!
   TBranch        *b_cal__mona_l_qcal;   //!
   TBranch        *b_cal__mona_r_tcal;   //!
   TBranch        *b_cal__mona_r_qcal;   //!
   TBranch        *b_cal__mona_xpos;   //!
   TBranch        *b_cal__mona_tmean;   //!
   TBranch        *b_cal__mona_qmean;   //!
   TBranch        *b_cal__mona_hit_x;   //!
   TBranch        *b_cal__mona_hit_y;   //!
   TBranch        *b_cal__mona_hit_z;   //!
   TBranch        *b_cal__mona_hit_rho;   //!
   TBranch        *b_cal__mona_hit_phi;   //!
   TBranch        *b_cal__mona_hit_theta;   //!
   TBranch        *b_cal__mona_hit_t;   //!
   TBranch        *b_cal__mona_hit_v;   //!
   TBranch        *b_cal__mona_hit_ke;   //!
   TBranch        *b_cal__mona_hit_q;   //!
   TBranch        *b_cal__mona_hit_wall;   //!
   TBranch        *b_cal__mona_hit_bar;   //!
   TBranch        *b_cal__mona_x;   //!
   TBranch        *b_cal__mona_y;   //!
   TBranch        *b_cal__mona_z;   //!
   TBranch        *b_cal__mona_rho;   //!
   TBranch        *b_cal__mona_phi;   //!
   TBranch        *b_cal__mona_theta;   //!
   TBranch        *b_cal__mona_t;   //!
   TBranch        *b_cal__mona_v;   //!
   TBranch        *b_cal__mona_ke;   //!
   TBranch        *b_cal__mona_q;   //!
   TBranch        *b_raw__mona_trigger_monapattern;   //!
   TBranch        *b_raw__mona_trigger_monahits;   //!
   TBranch        *b_raw__mona_trigger_monacount_pattern;   //!
   TBranch        *b_raw__mona_trigger_monatimestamp;   //!
   TBranch        *b_raw__mona_trigger_lisapattern;   //!
   TBranch        *b_raw__mona_trigger_lisahits;   //!
   TBranch        *b_raw__mona_trigger_lisacount_pattern;   //!
   TBranch        *b_raw__mona_trigger_lisatimestamp;   //!
   TBranch        *b_raw__mona_l_traw;   //!
   TBranch        *b_raw__mona_l_qraw;   //!
   TBranch        *b_raw__mona_r_traw;   //!
   TBranch        *b_raw__mona_r_qraw;   //!
   TBranch        *b_runnum;   //!

   MonaBar(TTree *tree=0);
   virtual ~MonaBar();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void PlotLayer(int);
   void PlotLayerSummary();
};

#endif

#ifdef MonaBar_cxx
MonaBar::MonaBar(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run-0203-lisa_15Nov2017.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("run-0203-lisa_15Nov2017.root");
      }
      f->GetObject("t",tree);
#else
  TChain *chain = new TChain("t","Cosmic");
  char buffer[512];
  runCount=0;
  /*
  sprintf(buffer,"/mnt/analysis/e15118/root_mona/run-0103-mona_15Nov2017.root");
  cout << buffer << endl;
  chain->Add(buffer);
  sprintf(buffer,"/mnt/analysis/e15118/root_lisa/run-0203-lisa_15Nov2017.root");
  cout << buffer << endl;
  chain->Add(buffer);
  
  sprintf(buffer,"/mnt/analysis/e15118/root_lisa/run-4173-00-lisa_15Nov2017.root");
  cout << buffer << endl;
  chain->Add(buffer);
  */
  sprintf(buffer,"/mnt/analysis/e15118/playground/recal_F27_AllProducts.root");
  cout << buffer << endl;
  chain->Add(buffer);
  
  tree = chain;

#endif// SINGLE_TREE

   }
   Init(tree);
}

MonaBar::~MonaBar()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MonaBar::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MonaBar::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MonaBar::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mult", &mult, &b_cal__mona_mult);
   fChain->SetBranchAddress("l.tcal[18][16]", l_tcal, &b_cal__mona_l_tcal);
   fChain->SetBranchAddress("l.qcal[18][16]", l_qcal, &b_cal__mona_l_qcal);
   fChain->SetBranchAddress("r.tcal[18][16]", r_tcal, &b_cal__mona_r_tcal);
   fChain->SetBranchAddress("r.qcal[18][16]", r_qcal, &b_cal__mona_r_qcal);
   fChain->SetBranchAddress("xpos[18][16]", xpos, &b_cal__mona_xpos);
   fChain->SetBranchAddress("tmean[18][16]", tmean, &b_cal__mona_tmean);
   fChain->SetBranchAddress("qmean[18][16]", qmean, &b_cal__mona_qmean);
   fChain->SetBranchAddress("hit.x[10]", hit_x, &b_cal__mona_hit_x);
   fChain->SetBranchAddress("hit.y[10]", hit_y, &b_cal__mona_hit_y);
   fChain->SetBranchAddress("hit.z[10]", hit_z, &b_cal__mona_hit_z);
   fChain->SetBranchAddress("hit.rho[10]", hit_rho, &b_cal__mona_hit_rho);
   fChain->SetBranchAddress("hit.phi[10]", hit_phi, &b_cal__mona_hit_phi);
   fChain->SetBranchAddress("hit.theta[10]", hit_theta, &b_cal__mona_hit_theta);
   fChain->SetBranchAddress("hit.t[10]", hit_t, &b_cal__mona_hit_t);
   fChain->SetBranchAddress("hit.v[10]", hit_v, &b_cal__mona_hit_v);
   fChain->SetBranchAddress("hit.ke[10]", hit_ke, &b_cal__mona_hit_ke);
   fChain->SetBranchAddress("hit.q[10]", hit_q, &b_cal__mona_hit_q);
   fChain->SetBranchAddress("hit.wall[10]", hit_wall, &b_cal__mona_hit_wall);
   fChain->SetBranchAddress("hit.bar[10]", hit_bar, &b_cal__mona_hit_bar);
   fChain->SetBranchAddress("x", &x, &b_cal__mona_x);
   fChain->SetBranchAddress("y", &y, &b_cal__mona_y);
   fChain->SetBranchAddress("z", &z, &b_cal__mona_z);
   fChain->SetBranchAddress("rho", &rho, &b_cal__mona_rho);
   fChain->SetBranchAddress("phi", &phi, &b_cal__mona_phi);
   fChain->SetBranchAddress("theta", &theta, &b_cal__mona_theta);
   fChain->SetBranchAddress("t", &t, &b_cal__mona_t);
   fChain->SetBranchAddress("v", &v, &b_cal__mona_v);
   fChain->SetBranchAddress("ke", &ke, &b_cal__mona_ke);
   fChain->SetBranchAddress("q", &q, &b_cal__mona_q);
   fChain->SetBranchAddress("trigger.monapattern", &trigger_monapattern, &b_raw__mona_trigger_monapattern);
   fChain->SetBranchAddress("trigger.monahits", &trigger_monahits, &b_raw__mona_trigger_monahits);
   fChain->SetBranchAddress("trigger.monacount_pattern[3]", trigger_monacount_pattern, &b_raw__mona_trigger_monacount_pattern);
   fChain->SetBranchAddress("trigger.monatimestamp[4]", trigger_monatimestamp, &b_raw__mona_trigger_monatimestamp);
   fChain->SetBranchAddress("trigger.lisapattern", &trigger_lisapattern, &b_raw__mona_trigger_lisapattern);
   fChain->SetBranchAddress("trigger.lisahits", &trigger_lisahits, &b_raw__mona_trigger_lisahits);
   fChain->SetBranchAddress("trigger.lisacount_pattern[3]", trigger_lisacount_pattern, &b_raw__mona_trigger_lisacount_pattern);
   fChain->SetBranchAddress("trigger.lisatimestamp[4]", trigger_lisatimestamp, &b_raw__mona_trigger_lisatimestamp);
   fChain->SetBranchAddress("l.traw[18][16]", l_traw, &b_raw__mona_l_traw);
   fChain->SetBranchAddress("l.qraw[18][16]", l_qraw, &b_raw__mona_l_qraw);
   fChain->SetBranchAddress("r.traw[18][16]", r_traw, &b_raw__mona_r_traw);
   fChain->SetBranchAddress("r.qraw[18][16]", r_qraw, &b_raw__mona_r_qraw);
   fChain->SetBranchAddress("runnum", &runnum, &b_runnum);

   Int_t tBins = 255;
   Float_t t1=-100.; Float_t t2=5000.;
   Int_t qBins = 255;
   Float_t q1=-100.; Float_t q2=5000.;
   Int_t xBins=200;
   Float_t x1=-200.; Float_t x2 = 200.;
   Int_t tcBins = 250;
   Float_t tc1=0.; Float_t tc2 = 150.;
   Int_t qcBins = 100;
   Float_t qc1=0.; Float_t qc2 = 100.;

   layer[0] = "A";
   layer[1] = "B";
   layer[2] = "C";
   layer[3] = "D";
   layer[4] = "E";
   layer[5] = "F";
   layer[6] = "G";
   layer[7] = "H";
   layer[8] = "I";
   layer[9] = "J";
   layer[10]= "K";
   layer[11]= "L";
   layer[12]= "M";
   layer[13]= "N";
   layer[14]= "O";
   layer[15]= "P";
   layer[16]= "Q";
   layer[17]= "R";

  for(int i=0;i<18;i++){
    for(int j=0;j<16;j++){
      // raw q vs. t plots - indv bars
      rtq[i][j] = new TH2F(Form("rtq_%s_%i",layer[i],j),
        Form("Layer %s (right) Bar %i Raw t : Raw q;r.traw (ch);r.qraw (ch)",layer[i],j),
          tBins,t1,t2,qBins,q1,q2);
      ltq[i][j] = new TH2F(Form("ltq_%s_%i",layer[i],j),
        Form("Layer %s (left) Bar %i Raw t : Raw q;l.traw (ch);l.qraw (ch)",layer[i],j),
	tBins,t1,t2,qBins,q1,q2);
      // xpos - indv bars
      xps[i][j] = new TH1F(Form("xps_%s_%i",layer[i],j),
        Form("Layer %s Bar %i xpos;xpos [cm];Counts / %3.2f cm",
	  layer[i],j,(x2-x1)/Double_t(xBins)),
	xBins,x1,x2);
      // hit.x[0] - indv bars
      htx[i][j] = new TH1F(Form("htx_%s_%i",layer[i],j),
        Form("hit.x[0] %s%i;hit.x[0] [cm];Counts / %3.2f cm",layer[i],j,(x2-x1)/Double_t(xBins)),
	xBins,x1,x2);
      qtc[i][j] = new TH2F(Form("qtc_%s_%i",layer[i],j),
        Form("Layer %s Bar %i qmean:tmean;tmean [ns];qmean [MeVee]",layer[i],j),
	tcBins,tc1,tc2,qcBins,qc1,qc2);
     }
     // raw q vs. t plots - layer summaries
     Rtq[i] = new TH2F(Form("Rtq_%s",layer[i]),
       Form("Right Layer %s Raw t : Raw q;r.traw (ch);r.qraw (ch)",layer[i]),
       tBins,t1,t2,qBins,q1,q2);
     Ltq[i] = new TH2F(Form("Ltq_%s",layer[i]),
       Form("Left Layer %s Raw t : Raw q;l.traw (ch);l.qraw (ch)",layer[i]),
       tBins,t1,t2,qBins,q1,q2);
     // layer summary xpos
     Xps[i] = new TH1F(Form("Lxp_%s",layer[i]),
       Form("Layer %s xpos;xpos [cm];Counts / %3.2f cm",layer[i],(x2-x1)/Double_t(xBins)),
       xBins,x1,x2);
     Htx[i] = new TH1F(Form("Htx_%s",layer[i]),
       Form("Layer %s hit.x[0];hit.x[0] [cm];Counts / %3.2f cm",layer[i],(x2-x1)/Double_t(xBins)),
       xBins,x1,x2);
     QTc[i] = new TH2F(Form("QTc_%s",layer[i]),
       Form("Layer %s qmean : tmean;tmean [ns];qmean [??]",layer[i]),tcBins,tc1,tc2,qcBins,qc1,qc2);
   }

   Notify();
}

Bool_t MonaBar::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MonaBar::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MonaBar::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void palettea();
#endif // #ifdef MonaBar_cxx


