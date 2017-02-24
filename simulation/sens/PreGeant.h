//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  9 18:18:57 2017 by ROOT version 5.34/32
// from TTree t/simple-track tree
// found on file: O26_O24+2n_PencilBeam_3bodyMresOFF.root
//////////////////////////////////////////////////////////

#ifndef PreGeant_h
#define PreGeant_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PreGeant {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   // histograms for fragment position and angles after target
   TH2D* hxy2;
   TH2D* htxty2;
   TH1D* hfke2;
   TH1D* hfvel2;
   // histograms for fragment position, angles, KE at CRDC 1
   TH2D* hxy4,htxty4
   TH1D* hke4;
   // histograms for fragment forward tracked comparison (forward
   // matrix as ST MoNA does it
   TH2D* hFwrdMxy; TH2D* hFwrdMtxty;
   // histograms for fragment position and angles at CRDC 1 as ST MoNA calculates
   TH2D* hxy4o;
   TH2D* htxty4o;
   // histograms for itracked position and angles after target
   TH2D* hxy2i;
   TH2D* htxty2i;
   TH1D* hfke2i;
   // histograms for fragment position and angles at CRDC 2 drifted from c1
   TH2D* hxy6;
   TH2D* htxty6;
   // histograms for fragment position and angles at CRDC 2 as ST MoNA calculates
   TH2D* hxy6o;
   TH2D* htxty6o;
   // histograms for partial inverse tracked stuff
   TH1D* hdeC;// changed to DE from delta
   TH2D* htxtyC;
   TH1D* hfvelC;
   // histograms for neutron stuff
   TH1D* hn0v;
   TH1D* hn0ke;
   // histograms to check ToF hack fragment stuff
   TH1D* hfdist;
   TH1D* hc2path;
   TH1D* hsToF;
   TH1D* hfvelT;
   TH1D* hfkeT;
   TH2D* hc2pathdist;
   // relative velocities
   TH1D* hvr2;
   TH1D* hvrC;
   TH1D* hvrT;
/**/

   // Declaration of leaf types
   Double_t        b1p0x;
   Double_t        b1p0tx;
   Double_t        b1p0y;
   Double_t        b1p0ty;
   Double_t        b1p0Ekin;
   Double_t        b2p0x;
   Double_t        b2p0tx;
   Double_t        b2p0y;
   Double_t        b2p0ty;
   Double_t        b2p0t;
   Double_t        b2p0z;
   Double_t        b2p0TP;
   Double_t        b2p0dE;
   Double_t        b2p0Ekin;
   Double_t        b2p0R_exen;
   Double_t        b2p0R_ph;
   Double_t        b2p0R_th;
   Double_t        b2p1Ekin;
   Double_t        b2p2Ekin;
   Double_t        b2p0R_exen2;
   Double_t        b2p0R_ph2;
   Double_t        b2p0R_th2;
   Double_t        b4p0x;
   Double_t        b4p0tx;
   Double_t        b4p0y;
   Double_t        b4p0ty;
   Double_t        b4p0t;
   Double_t        b4p0Ekin;
   Double_t        b4p0path;
   Double_t        b6p0Ekin;
   Double_t        b6p0x;
   Double_t        b6p0tx;
   Double_t        b6p0y;
   Double_t        b6p0ty;
   Double_t        b6p0path;
   Double_t        b9p1t;
   Double_t        b9p1x;
   Double_t        b9p1y;
   Double_t        b9p1z;
   Double_t        b9p1Ekin;
   Double_t        b9p2t;
   Double_t        b9p2x;
   Double_t        b9p2y;
   Double_t        b9p2z;
   Double_t        b9p2Ekin;

   // List of branches
   TBranch        *b_b1p0x;   //!
   TBranch        *b_b1p0tx;   //!
   TBranch        *b_b1p0y;   //!
   TBranch        *b_b1p0ty;   //!
   TBranch        *b_b1p0Ekin;   //!
   TBranch        *b_b2p0x;   //!
   TBranch        *b_b2p0tx;   //!
   TBranch        *b_b2p0y;   //!
   TBranch        *b_b2p0ty;   //!
   TBranch        *b_b2p0t;   //!
   TBranch        *b_b2p0z;   //!
   TBranch        *b_b2p0TP;   //!
   TBranch        *b_b2p0dE;   //!
   TBranch        *b_b2p0Ekin;   //!
   TBranch        *b_b2p0R_exen;   //!
   TBranch        *b_b2p0R_ph;   //!
   TBranch        *b_b2p0R_th;   //!
   TBranch        *b_b2p1Ekin;   //!
   TBranch        *b_b2p2Ekin;   //!
   TBranch        *b_b2p0R_exen2;   //!
   TBranch        *b_b2p0R_ph2;   //!
   TBranch        *b_b2p0R_th2;   //!
   TBranch        *b_b4p0x;   //!
   TBranch        *b_b4p0tx;   //!
   TBranch        *b_b4p0y;   //!
   TBranch        *b_b4p0ty;   //!
   TBranch        *b_b4p0t;   //!
   TBranch        *b_b4p0Ekin;   //!
   TBranch        *b_b4p0path;   //!
   TBranch        *b_b6p0Ekin;   //!
   TBranch        *b_b6p0x;   //!
   TBranch        *b_b6p0tx;   //!
   TBranch        *b_b6p0y;   //!
   TBranch        *b_b6p0ty;   //!
   TBranch        *b_b6p0path;   //!
   TBranch        *b_b9p1t;   //!
   TBranch        *b_b9p1x;   //!
   TBranch        *b_b9p1y;   //!
   TBranch        *b_b9p1z;   //!
   TBranch        *b_b9p1Ekin;   //!
   TBranch        *b_b9p2t;   //!
   TBranch        *b_b9p2x;   //!
   TBranch        *b_b9p2y;   //!
   TBranch        *b_b9p2z;   //!
   TBranch        *b_b9p2Ekin;   //!

   PreGeant(TTree *tree=0);
   virtual ~PreGeant();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PreGeant_cxx
PreGeant::PreGeant(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_1MeV3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_Glauber3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_GlauberTrans3bodyMresOFF.root");
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_txty3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_txty1MeV3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_dbe3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_dbe1MeV3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_dxy3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_dxy1MeV3bodyMresOFF.root");
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n_PencilBeam_Tgt3bodyMresOFF.root");
      if (!f || !f->IsOpen()) {
//         f = new TFile("O26_O24+2n_PencilBeam_3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_1MeV3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_Glauber3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_GlauberTrans3bodyMresOFF.root");
         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_txty3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_txty1MeV3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_dbe3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_dbe1MeV3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_dxy3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_dxy1MeV3bodyMresOFF.root");
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n_PencilBeam_Tgt3bodyMresOFF.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

PreGeant::~PreGeant()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PreGeant::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PreGeant::LoadTree(Long64_t entry)
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

void PreGeant::Init(TTree *tree)
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

   fChain->SetBranchAddress("b1p0x", &b1p0x, &b_b1p0x);
   fChain->SetBranchAddress("b1p0tx", &b1p0tx, &b_b1p0tx);
   fChain->SetBranchAddress("b1p0y", &b1p0y, &b_b1p0y);
   fChain->SetBranchAddress("b1p0ty", &b1p0ty, &b_b1p0ty);
   fChain->SetBranchAddress("b1p0Ekin", &b1p0Ekin, &b_b1p0Ekin);
   fChain->SetBranchAddress("b2p0x", &b2p0x, &b_b2p0x);
   fChain->SetBranchAddress("b2p0tx", &b2p0tx, &b_b2p0tx);
   fChain->SetBranchAddress("b2p0y", &b2p0y, &b_b2p0y);
   fChain->SetBranchAddress("b2p0ty", &b2p0ty, &b_b2p0ty);
   fChain->SetBranchAddress("b2p0t", &b2p0t, &b_b2p0t);
   fChain->SetBranchAddress("b2p0z", &b2p0z, &b_b2p0z);
   fChain->SetBranchAddress("b2p0TP", &b2p0TP, &b_b2p0TP);
   fChain->SetBranchAddress("b2p0dE", &b2p0dE, &b_b2p0dE);
   fChain->SetBranchAddress("b2p0Ekin", &b2p0Ekin, &b_b2p0Ekin);
   fChain->SetBranchAddress("b2p0R_exen", &b2p0R_exen, &b_b2p0R_exen);
   fChain->SetBranchAddress("b2p0R_ph", &b2p0R_ph, &b_b2p0R_ph);
   fChain->SetBranchAddress("b2p0R_th", &b2p0R_th, &b_b2p0R_th);
   fChain->SetBranchAddress("b2p1Ekin", &b2p1Ekin, &b_b2p1Ekin);
   fChain->SetBranchAddress("b2p2Ekin", &b2p2Ekin, &b_b2p2Ekin);
   fChain->SetBranchAddress("b2p0R_exen2", &b2p0R_exen2, &b_b2p0R_exen2);
   fChain->SetBranchAddress("b2p0R_ph2", &b2p0R_ph2, &b_b2p0R_ph2);
   fChain->SetBranchAddress("b2p0R_th2", &b2p0R_th2, &b_b2p0R_th2);
   fChain->SetBranchAddress("b4p0x", &b4p0x, &b_b4p0x);
   fChain->SetBranchAddress("b4p0tx", &b4p0tx, &b_b4p0tx);
   fChain->SetBranchAddress("b4p0y", &b4p0y, &b_b4p0y);
   fChain->SetBranchAddress("b4p0ty", &b4p0ty, &b_b4p0ty);
   fChain->SetBranchAddress("b4p0t", &b4p0t, &b_b4p0t);
   fChain->SetBranchAddress("b4p0Ekin", &b4p0Ekin, &b_b4p0Ekin);
   fChain->SetBranchAddress("b4p0path", &b4p0path, &b_b4p0path);
   fChain->SetBranchAddress("b6p0Ekin", &b6p0Ekin, &b_b6p0Ekin);
   fChain->SetBranchAddress("b6p0x", &b6p0x, &b_b6p0x);
   fChain->SetBranchAddress("b6p0tx", &b6p0tx, &b_b6p0tx);
   fChain->SetBranchAddress("b6p0y", &b6p0y, &b_b6p0y);
   fChain->SetBranchAddress("b6p0ty", &b6p0ty, &b_b6p0ty);
   fChain->SetBranchAddress("b6p0path", &b6p0path, &b_b6p0path);
   fChain->SetBranchAddress("b9p1t", &b9p1t, &b_b9p1t);
   fChain->SetBranchAddress("b9p1x", &b9p1x, &b_b9p1x);
   fChain->SetBranchAddress("b9p1y", &b9p1y, &b_b9p1y);
   fChain->SetBranchAddress("b9p1z", &b9p1z, &b_b9p1z);
   fChain->SetBranchAddress("b9p1Ekin", &b9p1Ekin, &b_b9p1Ekin);
   fChain->SetBranchAddress("b9p2t", &b9p2t, &b_b9p2t);
   fChain->SetBranchAddress("b9p2x", &b9p2x, &b_b9p2x);
   fChain->SetBranchAddress("b9p2y", &b9p2y, &b_b9p2y);
   fChain->SetBranchAddress("b9p2z", &b9p2z, &b_b9p2z);
   fChain->SetBranchAddress("b9p2Ekin", &b9p2Ekin, &b_b9p2Ekin);
   Notify();
}

Bool_t PreGeant::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PreGeant::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PreGeant::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PreGeant_cxx
