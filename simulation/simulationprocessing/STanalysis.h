//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 23 11:11:58 2018 by ROOT version 5.34/32
// from TTree t/Simulation Output
// found on file: F27O24-geant.root
//////////////////////////////////////////////////////////

#ifndef STanalysis_h
#define STanalysis_h

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TCutG.h>
#include <TRandom3.h>
#include <iostream>
#include "/projects/e15118/redpath/simulation/histograms/STanalysis/src/AnalysisStructures.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class STanalysis {
protected :
  Bool_t m_histogramsSet;
  Bool_t m_ATinit;

  TString m_beam;
  TString m_frag;

  Double_t m_beamA,m_beamZ;
  Double_t m_fragA,m_fragZ;

  Double_t m_siDEres;

  TCutG *left,*mid,*right;

  Double_t m_addback[3];
  Double_t b4dEgate,b6dEgate;

  Double_t m_qCut;

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  /* Analysis tree */
  TFile *outFile;
  TTree *at;
  /**/
  BEAM beam;
  SILICON si0;
  SILICON si1;
  SILICON si2;
  SILICON si3;
  CRDC crdc1;
  CRDC crdc2;
  THIN thin;
  NEUTRON n0;
  FRAGMENT frag;



  // --- HISTOGRAMS --- //
  TH1D *hbeamV;
  TH1D *hvelsm;
  TH1D *hvelBp;
  // aggregate
  TH2D *crdcxy[2];
  TH2D *crdctxty;
  TH2D *crdc12x;
  TH2D *crdcxtx;
  TH2D *thinxy;
  // silicon
  TH2D *sixy[4];
  TH1D *side[4];
  // per target
  TH1D *hftof[3];
  TH1D *hfdst[3];
  TH1D *hfvl0[3];
  TH1D *hsvel[3];
  TH1D *hfvel[3];
  TH1D *hnvel[3];
  TH1D *hbvel[3];
  TH1D *hrvel[3];
  TH1D *hvrbp[3];
  TH1D *hvrxp[3];// fragment velocity at rxn pt
  TH1D *hedecay[3];
  TH1D *hrxnpos[3];
  TH1D *h0lgt[3];
  TH1D *h1lgt[3];
  TH1I *hmult[3];

  TH2D *tgtID[3];

  TH2F *hhNxy[3];

  TH1D *sumVR;
  TH1D *sumED;
  TH1I *sumMult;
  TH1D *sumLight0;
  TH1D *sumLight1;

  UShort_t target;
  Double_t edecay;
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
   Double_t        b2p0z;
   Double_t        b2p0dE;
   Double_t        b2p0Ekin;
   Double_t        b3p0x;
   Double_t        b3p0tx;
   Double_t        b3p0y;
   Double_t        b3p0ty;
   Double_t        b3p0TP;
   Double_t        b3p0dE;
   Double_t        b3p0Ekin;
   Double_t        b3p1Ekin;
   Double_t        b3p1tx;
   Double_t        b3p1ty;
   Double_t        b4p0x;
   Double_t        b4p0tx;
   Double_t        b4p0y;
   Double_t        b4p0ty;
   Double_t        b4p0z;
   Double_t        b4p0dE;
   Double_t        b4p0Ekin;
   Double_t        b5p0x;
   Double_t        b5p0tx;
   Double_t        b5p0y;
   Double_t        b5p0ty;
   Double_t        b5p0TP;
   Double_t        b5p0dE;
   Double_t        b5p0Ekin;
   Double_t        b5p1Ekin;
   Double_t        b5p1tx;
   Double_t        b5p1ty;
   Double_t        b6p0x;
   Double_t        b6p0tx;
   Double_t        b6p0y;
   Double_t        b6p0ty;
   Double_t        b6p0z;
   Double_t        b6p0dE;
   Double_t        b6p0Ekin;
   Double_t        b7p0x;
   Double_t        b7p0tx;
   Double_t        b7p0y;
   Double_t        b7p0ty;
   Double_t        b7p0TP;
   Double_t        b7p0dE;
   Double_t        b7p0Ekin;
   Double_t        b7p1Ekin;
   Double_t        b7p1tx;
   Double_t        b7p1ty;
   Double_t        b8p0x;
   Double_t        b8p0tx;
   Double_t        b8p0y;
   Double_t        b8p0ty;
   Double_t        b8p0z;
   Double_t        b8p0dE;
   Double_t        b8p0Ekin;
   Double_t        b10p0x;
   Double_t        b10p0tx;
   Double_t        b10p0y;
   Double_t        b10p0ty;
   Double_t        b10p0Ekin;
   Double_t        b12p0x;
   Double_t        b12p0tx;
   Double_t        b12p0y;
   Double_t        b12p0ty;
   Double_t        b12p0Ekin;
   Double_t        b13p1t;
   Double_t        b13p1x;
   Double_t        b13p1y;
   Double_t        b13p1z;
   Double_t        b13p1Ekin;
   Int_t           b13pgmultiplicity;
   Int_t           b13pg1gZ1Mult;
   Int_t           b13pg1gZ2Mult;
   Int_t           b13pg1gZGt2Mult;
   Int_t           b13pg1gGammaMult;
   Double_t        b13pg1Edep;
   Double_t        b13pg1light;
   Double_t        b13pg1t;
   Double_t        b13pg1x;
   Double_t        b13pg1y;
   Double_t        b13pg1z;
   Double_t        b13pg2Edep;
   Double_t        b13pg2light;
   Double_t        b13pg2t;
   Double_t        b13pg2x;
   Double_t        b13pg2y;
   Double_t        b13pg2z;
   Double_t        b13pg3Edep;
   Double_t        b13pg3light;
   Double_t        b13pg3t;
   Double_t        b13pg3x;
   Double_t        b13pg3y;
   Double_t        b13pg3z;
   Double_t        b13pg4Edep;
   Double_t        b13pg4light;
   Double_t        b13pg4t;
   Double_t        b13pg4x;
   Double_t        b13pg4y;
   Double_t        b13pg4z;
   Double_t        b13pg5Edep;
   Double_t        b13pg5light;
   Double_t        b13pg5t;
   Double_t        b13pg5x;
   Double_t        b13pg5y;
   Double_t        b13pg5z;
   Double_t        b13pg6Edep;
   Double_t        b13pg6light;
   Double_t        b13pg6t;
   Double_t        b13pg6x;
   Double_t        b13pg6y;
   Double_t        b13pg6z;
   Double_t        b13pg7Edep;
   Double_t        b13pg7light;
   Double_t        b13pg7t;
   Double_t        b13pg7x;
   Double_t        b13pg7y;
   Double_t        b13pg7z;
   Double_t        b13pg8Edep;
   Double_t        b13pg8light;
   Double_t        b13pg8t;
   Double_t        b13pg8x;
   Double_t        b13pg8y;
   Double_t        b13pg8z;
   Double_t        b13pg9Edep;
   Double_t        b13pg9light;
   Double_t        b13pg9t;
   Double_t        b13pg9x;
   Double_t        b13pg9y;
   Double_t        b13pg9z;
   Double_t        b13pg10Edep;
   Double_t        b13pg10light;
   Double_t        b13pg10t;
   Double_t        b13pg10x;
   Double_t        b13pg10y;
   Double_t        b13pg10z;

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
   TBranch        *b_b2p0z;   //!
   TBranch        *b_b2p0dE;   //!
   TBranch        *b_b2p0Ekin;   //!
   TBranch        *b_b3p0x;   //!
   TBranch        *b_b3p0tx;   //!
   TBranch        *b_b3p0y;   //!
   TBranch        *b_b3p0ty;   //!
   TBranch        *b_b3p0TP;   //!
   TBranch        *b_b3p0dE;   //!
   TBranch        *b_b3p0Ekin;   //!
   TBranch        *b_b3p1Ekin;   //!
   TBranch        *b_b3p1tx;   //!
   TBranch        *b_b3p1ty;   //!
   TBranch        *b_b4p0x;   //!
   TBranch        *b_b4p0tx;   //!
   TBranch        *b_b4p0y;   //!
   TBranch        *b_b4p0ty;   //!
   TBranch        *b_b4p0z;   //!
   TBranch        *b_b4p0dE;   //!
   TBranch        *b_b4p0Ekin;   //!
   TBranch        *b_b5p0x;   //!
   TBranch        *b_b5p0tx;   //!
   TBranch        *b_b5p0y;   //!
   TBranch        *b_b5p0ty;   //!
   TBranch        *b_b5p0TP;   //!
   TBranch        *b_b5p0dE;   //!
   TBranch        *b_b5p0Ekin;   //!
   TBranch        *b_b5p1Ekin;   //!
   TBranch        *b_b5p1tx;   //!
   TBranch        *b_b5p1ty;   //!
   TBranch        *b_b6p0x;   //!
   TBranch        *b_b6p0tx;   //!
   TBranch        *b_b6p0y;   //!
   TBranch        *b_b6p0ty;   //!
   TBranch        *b_b6p0z;   //!
   TBranch        *b_b6p0dE;   //!
   TBranch        *b_b6p0Ekin;   //!
   TBranch        *b_b7p0x;   //!
   TBranch        *b_b7p0tx;   //!
   TBranch        *b_b7p0y;   //!
   TBranch        *b_b7p0ty;   //!
   TBranch        *b_b7p0TP;   //!
   TBranch        *b_b7p0dE;   //!
   TBranch        *b_b7p0Ekin;   //!
   TBranch        *b_b7p1Ekin;   //!
   TBranch        *b_b7p1tx;   //!
   TBranch        *b_b7p1ty;   //!
   TBranch        *b_b8p0x;   //!
   TBranch        *b_b8p0tx;   //!
   TBranch        *b_b8p0y;   //!
   TBranch        *b_b8p0ty;   //!
   TBranch        *b_b8p0z;   //!
   TBranch        *b_b8p0dE;   //!
   TBranch        *b_b8p0Ekin;   //!
   TBranch        *b_b10p0x;   //!
   TBranch        *b_b10p0tx;   //!
   TBranch        *b_b10p0y;   //!
   TBranch        *b_b10p0ty;   //!
   TBranch        *b_b10p0Ekin;   //!
   TBranch        *b_b12p0x;   //!
   TBranch        *b_b12p0tx;   //!
   TBranch        *b_b12p0y;   //!
   TBranch        *b_b12p0ty;   //!
   TBranch        *b_b12p0Ekin;   //!
   TBranch        *b_b13p1t;   //!
   TBranch        *b_b13p1x;   //!
   TBranch        *b_b13p1y;   //!
   TBranch        *b_b13p1z;   //!
   TBranch        *b_b13p1Ekin;   //!
   TBranch        *b_b13pgmultiplicity;   //!
   TBranch        *b_b13pg1gZ1Mult;   //!
   TBranch        *b_b13pg1gZ2Mult;   //!
   TBranch        *b_b13pg1gZGt2Mult;   //!
   TBranch        *b_b13pg1gGammaMult;   //!
   TBranch        *b_b13pg1Edep;   //!
   TBranch        *b_b13pg1light;   //!
   TBranch        *b_b13pg1t;   //!
   TBranch        *b_b13pg1x;   //!
   TBranch        *b_b13pg1y;   //!
   TBranch        *b_b13pg1z;   //!
   TBranch        *b_b13pg2Edep;   //!
   TBranch        *b_b13pg2light;   //!
   TBranch        *b_b13pg2t;   //!
   TBranch        *b_b13pg2x;   //!
   TBranch        *b_b13pg2y;   //!
   TBranch        *b_b13pg2z;   //!
   TBranch        *b_b13pg3Edep;   //!
   TBranch        *b_b13pg3light;   //!
   TBranch        *b_b13pg3t;   //!
   TBranch        *b_b13pg3x;   //!
   TBranch        *b_b13pg3y;   //!
   TBranch        *b_b13pg3z;   //!
   TBranch        *b_b13pg4Edep;   //!
   TBranch        *b_b13pg4light;   //!
   TBranch        *b_b13pg4t;   //!
   TBranch        *b_b13pg4x;   //!
   TBranch        *b_b13pg4y;   //!
   TBranch        *b_b13pg4z;   //!
   TBranch        *b_b13pg5Edep;   //!
   TBranch        *b_b13pg5light;   //!
   TBranch        *b_b13pg5t;   //!
   TBranch        *b_b13pg5x;   //!
   TBranch        *b_b13pg5y;   //!
   TBranch        *b_b13pg5z;   //!
   TBranch        *b_b13pg6Edep;   //!
   TBranch        *b_b13pg6light;   //!
   TBranch        *b_b13pg6t;   //!
   TBranch        *b_b13pg6x;   //!
   TBranch        *b_b13pg6y;   //!
   TBranch        *b_b13pg6z;   //!
   TBranch        *b_b13pg7Edep;   //!
   TBranch        *b_b13pg7light;   //!
   TBranch        *b_b13pg7t;   //!
   TBranch        *b_b13pg7x;   //!
   TBranch        *b_b13pg7y;   //!
   TBranch        *b_b13pg7z;   //!
   TBranch        *b_b13pg8Edep;   //!
   TBranch        *b_b13pg8light;   //!
   TBranch        *b_b13pg8t;   //!
   TBranch        *b_b13pg8x;   //!
   TBranch        *b_b13pg8y;   //!
   TBranch        *b_b13pg8z;   //!
   TBranch        *b_b13pg9Edep;   //!
   TBranch        *b_b13pg9light;   //!
   TBranch        *b_b13pg9t;   //!
   TBranch        *b_b13pg9x;   //!
   TBranch        *b_b13pg9y;   //!
   TBranch        *b_b13pg9z;   //!
   TBranch        *b_b13pg10Edep;   //!
   TBranch        *b_b13pg10light;   //!
   TBranch        *b_b13pg10t;   //!
   TBranch        *b_b13pg10x;   //!
   TBranch        *b_b13pg10y;   //!
   TBranch        *b_b13pg10z;   //!

   STanalysis(TTree *tree=0);
   virtual ~STanalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

  TString GetBeam(){return m_beam;}
  TString GetFragment(){return m_frag;}

  void SetQcut(double q){m_qCut=q;printf("qCut: %g\n",m_qCut);}

  TH1D *GetNeutronVelocity(TH1D *h[3]);

  void Reset();

  void PlotIncidentBeam();
  void PlotSiPositions();
  void PlotCRDC();
  void PlotTargetID();
  void PlotNeutronVelocity();
  void PlotFragmentVelocity();
  void PlotSiEloss();
  void PlotRxnPosition();
  void PlotRelativeVelocity();

  void WriteHistograms();
  void WriteVelocity(TString);
  void WriteUnrHistograms();

  void InitAnalysisTree(TString);
  void WriteAT();

};

#endif

#ifdef STanalysis_cxx
STanalysis::STanalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//  TString filename = "/mnt/simulations/MoNAsims/O26_analysis/F27_unr-geant.root";
//  TString filename = "/mnt/simulations/MoNAsims/O26_analysis/Ne29_unr-geant.root";
//  TString filename = "/mnt/simulations/MoNAsims/O26_analysis/Ne29_F27-geant.root";
//  TString filename = "/mnt/simulations/MoNAsims/O26_analysis/F27_O22-geantGlaub11.root";
  TString filename = "/mnt/simulations/MoNAsims/O26_analysis/F27_O22-geant0ps.root";
  Ssiz_t pt1 = filename.Last('/'); Ssiz_t pt2 = filename.Last('_');
  Ssiz_t len = pt2 - pt1-1;
  m_beam = filename(pt1+1,len);
  pt1 = filename.Last('_'); pt2 = filename.First('-');
  len = pt2 - pt1-1;
  m_frag = filename(pt1+1,len);

  if(m_beam.CompareTo("F27")==0){m_beamA = 27.; m_beamZ = 9.;}
  else if(m_beam.CompareTo("F26")==0){m_beamA = 26.; m_beamZ = 7.;}
  else if(m_beam.CompareTo("Ne28")==0){m_beamA = 28.; m_beamZ = 10.;}
  else if(m_beam.CompareTo("Ne29")==0){m_beamA = 29.; m_beamZ = 10.;}
  else if(m_beam.CompareTo("Na30")==0){m_beamA = 30.; m_beamZ = 11.;}
  else{cout << "Didn't recognize the beam. Check file name format." << endl;
       cout << "Expected Beams: F-27, Ne-28, Ne-29, Na-30" << endl;}

/*
  // for dealing with oxygen & nitrogen rxn products
  b4dEgate = 14.;b6dEgate=16.5;
  // for dealing with fluorine rxn products
  b4dEgate = 17.;b6dEgate=20.0;
*/

  if(m_frag.CompareTo("O24")==0){m_fragA = 24.; m_fragZ = 8.;
    if(m_beam.CompareTo("F27")==0){
    m_addback[0]=785.001; m_addback[1]=488.710; m_addback[2]=177.599;// [MeV] O-24 m_addback
    }
    else if(m_beam.CompareTo("Ne29")==0){
    m_addback[0] = 706.518; m_addback[1] = 465.995; m_addback[2] = 172.138;// [MeV] O-24 from Ne-29
    }
    else{cout << endl << "No addback set." << endl;}
    b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("O23")==0){m_fragA = 23.; m_fragZ = 8.;
    if(m_beam.CompareTo("F27")==0){
    m_addback[0] = 791.409; m_addback[1] = 491.331; m_addback[2] = 177.974;// [MeV] O-23 m_addback
    }
    else if(m_beam.CompareTo("Ne29")==0){
    m_addback[0] = 744.361; m_addback[1] = 468.174; m_addback[2] = 172.443;// [MeV] O-23 from Ne-29
    }
    else{cout << endl << "No addback set." << endl;}
    b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("O22")==0){m_fragA = 22.; m_fragZ = 8.;
    if(m_beam.CompareTo("F27")==0){
    m_addback[0] = 798.852; m_addback[1] = 494.317; m_addback[2] = 178.397;// [MeV] O-22 m_addback
    }
    else if(m_beam.CompareTo("Ne29")==0){
    m_addback[0] = 750.173; m_addback[1] = 470.654; m_addback[2] = 172.785;// [MeV] O-22 from Ne-29
    }
    else{cout << endl << "No addback set." << endl;}
    b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("F27")==0){m_fragA = 27.; m_fragZ = 9.;
  m_addback[0] = 948.586; m_addback[1]=597.923; m_addback[2]=218.961;// [MeV] F-27 from Ne-29
  b4dEgate = 17.;b6dEgate=20.0;
  }
  else if(m_frag.CompareTo("F26")==0){m_fragA = 26.; m_fragZ = 9.;
  m_addback[0] = 953.299; m_addback[1]=600.887; m_addback[2]=219.376;// [MeV] F-26 from Ne-29
  b4dEgate = 17.;b6dEgate=20.0;
  }
  else if(m_frag.CompareTo("F25")==0){m_fragA = 25.; m_fragZ = 9.;
  m_addback[0] = 970.06; m_addback[1] = 604.096; m_addback[2] = 219.838;// [MeV] F-25 from Ne-29
  b4dEgate = 17.;b6dEgate=20.0;
  }
  else if(m_frag.CompareTo("N23")==0){m_fragA = 23.; m_fragZ = 7.;}
  else if(m_frag.CompareTo("N21")==0){m_fragA = 21.; m_fragZ = 7.;
  m_addback[0] = 587.787; m_addback[1] = 368.689; m_addback[2] = 135.185;// [MeV] N-21 m_addback
  b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("N20")==0){m_fragA = 20.; m_fragZ = 7.;
  m_addback[0] = 592.168; m_addback[1] = 370.601; m_addback[2] = 135.463;// [MeV] N-20 m_addback
  b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("N19")==0){m_fragA = 19.; m_fragZ = 7.;
  m_addback[0] = 597.297; m_addback[1] = 372.698; m_addback[2] = 135.777;// [MeV] N-19 m_addback
  b4dEgate = 14.;b6dEgate=16.5;
  }
  else if(m_frag.CompareTo("unr")==0){m_fragA = m_beamA; m_fragZ = m_beamZ;
  m_addback[0] = 0.; m_addback[1] = 0.; m_addback[2] = 0.;// no addback
  }
  else{cout << "Didn't recognize fragment. Check file name format." << endl;
       cout << "Expected fragments:" << endl;
       cout << "N-21, N-20, N-19" << endl;
       cout << "O-24, O-23, O-22, F-27, F-26, F-25, unr" << endl;}
  
  printf("Beam: %s, A = %3.0f, Z = %3.0f\n",m_beam.Data(),m_beamA,m_beamZ);
  printf("Fragment: %s, A = %3.0f, Z = %3.0f\n",m_frag.Data(),m_fragA,m_fragZ);

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

STanalysis::~STanalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t STanalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t STanalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
//      Notify();
   }
   return centry;
}

void STanalysis::Init(TTree *tree)
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
   fChain->SetBranchAddress("b2p0z", &b2p0z, &b_b2p0z);
   fChain->SetBranchAddress("b2p0dE", &b2p0dE, &b_b2p0dE);
   fChain->SetBranchAddress("b2p0Ekin", &b2p0Ekin, &b_b2p0Ekin);
   fChain->SetBranchAddress("b3p0x", &b3p0x, &b_b3p0x);
   fChain->SetBranchAddress("b3p0tx", &b3p0tx, &b_b3p0tx);
   fChain->SetBranchAddress("b3p0y", &b3p0y, &b_b3p0y);
   fChain->SetBranchAddress("b3p0ty", &b3p0ty, &b_b3p0ty);
   fChain->SetBranchAddress("b3p0TP", &b3p0TP, &b_b3p0TP);
   fChain->SetBranchAddress("b3p0dE", &b3p0dE, &b_b3p0dE);
   fChain->SetBranchAddress("b3p0Ekin", &b3p0Ekin, &b_b3p0Ekin);
   fChain->SetBranchAddress("b3p1Ekin", &b3p1Ekin, &b_b3p1Ekin);
   fChain->SetBranchAddress("b3p1tx", &b3p1tx, &b_b3p1tx);
   fChain->SetBranchAddress("b3p1ty", &b3p1ty, &b_b3p1ty);
   fChain->SetBranchAddress("b4p0x", &b4p0x, &b_b4p0x);
   fChain->SetBranchAddress("b4p0tx", &b4p0tx, &b_b4p0tx);
   fChain->SetBranchAddress("b4p0y", &b4p0y, &b_b4p0y);
   fChain->SetBranchAddress("b4p0ty", &b4p0ty, &b_b4p0ty);
   fChain->SetBranchAddress("b4p0z", &b4p0z, &b_b4p0z);
   fChain->SetBranchAddress("b4p0dE", &b4p0dE, &b_b4p0dE);
   fChain->SetBranchAddress("b4p0Ekin", &b4p0Ekin, &b_b4p0Ekin);
   fChain->SetBranchAddress("b5p0x", &b5p0x, &b_b5p0x);
   fChain->SetBranchAddress("b5p0tx", &b5p0tx, &b_b5p0tx);
   fChain->SetBranchAddress("b5p0y", &b5p0y, &b_b5p0y);
   fChain->SetBranchAddress("b5p0ty", &b5p0ty, &b_b5p0ty);
   fChain->SetBranchAddress("b5p0TP", &b5p0TP, &b_b5p0TP);
   fChain->SetBranchAddress("b5p0dE", &b5p0dE, &b_b5p0dE);
   fChain->SetBranchAddress("b5p0Ekin", &b5p0Ekin, &b_b5p0Ekin);
   fChain->SetBranchAddress("b5p1Ekin", &b5p1Ekin, &b_b5p1Ekin);
   fChain->SetBranchAddress("b5p1tx", &b5p1tx, &b_b5p1tx);
   fChain->SetBranchAddress("b5p1ty", &b5p1ty, &b_b5p1ty);
   fChain->SetBranchAddress("b6p0x", &b6p0x, &b_b6p0x);
   fChain->SetBranchAddress("b6p0tx", &b6p0tx, &b_b6p0tx);
   fChain->SetBranchAddress("b6p0y", &b6p0y, &b_b6p0y);
   fChain->SetBranchAddress("b6p0ty", &b6p0ty, &b_b6p0ty);
   fChain->SetBranchAddress("b6p0z", &b6p0z, &b_b6p0z);
   fChain->SetBranchAddress("b6p0dE", &b6p0dE, &b_b6p0dE);
   fChain->SetBranchAddress("b6p0Ekin", &b6p0Ekin, &b_b6p0Ekin);
   fChain->SetBranchAddress("b7p0x", &b7p0x, &b_b7p0x);
   fChain->SetBranchAddress("b7p0tx", &b7p0tx, &b_b7p0tx);
   fChain->SetBranchAddress("b7p0y", &b7p0y, &b_b7p0y);
   fChain->SetBranchAddress("b7p0ty", &b7p0ty, &b_b7p0ty);
   fChain->SetBranchAddress("b7p0TP", &b7p0TP, &b_b7p0TP);
   fChain->SetBranchAddress("b7p0dE", &b7p0dE, &b_b7p0dE);
   fChain->SetBranchAddress("b7p0Ekin", &b7p0Ekin, &b_b7p0Ekin);
   fChain->SetBranchAddress("b7p1Ekin", &b7p1Ekin, &b_b7p1Ekin);
   fChain->SetBranchAddress("b7p1tx", &b7p1tx, &b_b7p1tx);
   fChain->SetBranchAddress("b7p1ty", &b7p1ty, &b_b7p1ty);
   fChain->SetBranchAddress("b8p0x", &b8p0x, &b_b8p0x);
   fChain->SetBranchAddress("b8p0tx", &b8p0tx, &b_b8p0tx);
   fChain->SetBranchAddress("b8p0y", &b8p0y, &b_b8p0y);
   fChain->SetBranchAddress("b8p0ty", &b8p0ty, &b_b8p0ty);
   fChain->SetBranchAddress("b8p0z", &b8p0z, &b_b8p0z);
   fChain->SetBranchAddress("b8p0dE", &b8p0dE, &b_b8p0dE);
   fChain->SetBranchAddress("b8p0Ekin", &b8p0Ekin, &b_b8p0Ekin);
   fChain->SetBranchAddress("b10p0x", &b10p0x, &b_b10p0x);
   fChain->SetBranchAddress("b10p0tx", &b10p0tx, &b_b10p0tx);
   fChain->SetBranchAddress("b10p0y", &b10p0y, &b_b10p0y);
   fChain->SetBranchAddress("b10p0ty", &b10p0ty, &b_b10p0ty);
   fChain->SetBranchAddress("b10p0Ekin", &b10p0Ekin, &b_b10p0Ekin);
   fChain->SetBranchAddress("b12p0x", &b12p0x, &b_b12p0x);
   fChain->SetBranchAddress("b12p0tx", &b12p0tx, &b_b12p0tx);
   fChain->SetBranchAddress("b12p0y", &b12p0y, &b_b12p0y);
   fChain->SetBranchAddress("b12p0ty", &b12p0ty, &b_b12p0ty);
   fChain->SetBranchAddress("b12p0Ekin", &b12p0Ekin, &b_b12p0Ekin);
   fChain->SetBranchAddress("b13p1t", &b13p1t, &b_b13p1t);
   fChain->SetBranchAddress("b13p1x", &b13p1x, &b_b13p1x);
   fChain->SetBranchAddress("b13p1y", &b13p1y, &b_b13p1y);
   fChain->SetBranchAddress("b13p1z", &b13p1z, &b_b13p1z);
   fChain->SetBranchAddress("b13p1Ekin", &b13p1Ekin, &b_b13p1Ekin);
   fChain->SetBranchAddress("b13pgmultiplicity", &b13pgmultiplicity, &b_b13pgmultiplicity);
   fChain->SetBranchAddress("b13pg1gZ1Mult", &b13pg1gZ1Mult, &b_b13pg1gZ1Mult);
   fChain->SetBranchAddress("b13pg1gZ2Mult", &b13pg1gZ2Mult, &b_b13pg1gZ2Mult);
   fChain->SetBranchAddress("b13pg1gZGt2Mult", &b13pg1gZGt2Mult, &b_b13pg1gZGt2Mult);
   fChain->SetBranchAddress("b13pg1gGammaMult", &b13pg1gGammaMult, &b_b13pg1gGammaMult);
   fChain->SetBranchAddress("b13pg1Edep", &b13pg1Edep, &b_b13pg1Edep);
   fChain->SetBranchAddress("b13pg1light", &b13pg1light, &b_b13pg1light);
   fChain->SetBranchAddress("b13pg1t", &b13pg1t, &b_b13pg1t);
   fChain->SetBranchAddress("b13pg1x", &b13pg1x, &b_b13pg1x);
   fChain->SetBranchAddress("b13pg1y", &b13pg1y, &b_b13pg1y);
   fChain->SetBranchAddress("b13pg1z", &b13pg1z, &b_b13pg1z);
   fChain->SetBranchAddress("b13pg2Edep", &b13pg2Edep, &b_b13pg2Edep);
   fChain->SetBranchAddress("b13pg2light", &b13pg2light, &b_b13pg2light);
   fChain->SetBranchAddress("b13pg2t", &b13pg2t, &b_b13pg2t);
   fChain->SetBranchAddress("b13pg2x", &b13pg2x, &b_b13pg2x);
   fChain->SetBranchAddress("b13pg2y", &b13pg2y, &b_b13pg2y);
   fChain->SetBranchAddress("b13pg2z", &b13pg2z, &b_b13pg2z);
   fChain->SetBranchAddress("b13pg3Edep", &b13pg3Edep, &b_b13pg3Edep);
   fChain->SetBranchAddress("b13pg3light", &b13pg3light, &b_b13pg3light);
   fChain->SetBranchAddress("b13pg3t", &b13pg3t, &b_b13pg3t);
   fChain->SetBranchAddress("b13pg3x", &b13pg3x, &b_b13pg3x);
   fChain->SetBranchAddress("b13pg3y", &b13pg3y, &b_b13pg3y);
   fChain->SetBranchAddress("b13pg3z", &b13pg3z, &b_b13pg3z);
   fChain->SetBranchAddress("b13pg4Edep", &b13pg4Edep, &b_b13pg4Edep);
   fChain->SetBranchAddress("b13pg4light", &b13pg4light, &b_b13pg4light);
   fChain->SetBranchAddress("b13pg4t", &b13pg4t, &b_b13pg4t);
   fChain->SetBranchAddress("b13pg4x", &b13pg4x, &b_b13pg4x);
   fChain->SetBranchAddress("b13pg4y", &b13pg4y, &b_b13pg4y);
   fChain->SetBranchAddress("b13pg4z", &b13pg4z, &b_b13pg4z);
   fChain->SetBranchAddress("b13pg5Edep", &b13pg5Edep, &b_b13pg5Edep);
   fChain->SetBranchAddress("b13pg5light", &b13pg5light, &b_b13pg5light);
   fChain->SetBranchAddress("b13pg5t", &b13pg5t, &b_b13pg5t);
   fChain->SetBranchAddress("b13pg5x", &b13pg5x, &b_b13pg5x);
   fChain->SetBranchAddress("b13pg5y", &b13pg5y, &b_b13pg5y);
   fChain->SetBranchAddress("b13pg5z", &b13pg5z, &b_b13pg5z);
   fChain->SetBranchAddress("b13pg6Edep", &b13pg6Edep, &b_b13pg6Edep);
   fChain->SetBranchAddress("b13pg6light", &b13pg6light, &b_b13pg6light);
   fChain->SetBranchAddress("b13pg6t", &b13pg6t, &b_b13pg6t);
   fChain->SetBranchAddress("b13pg6x", &b13pg6x, &b_b13pg6x);
   fChain->SetBranchAddress("b13pg6y", &b13pg6y, &b_b13pg6y);
   fChain->SetBranchAddress("b13pg6z", &b13pg6z, &b_b13pg6z);
   fChain->SetBranchAddress("b13pg7Edep", &b13pg7Edep, &b_b13pg7Edep);
   fChain->SetBranchAddress("b13pg7light", &b13pg7light, &b_b13pg7light);
   fChain->SetBranchAddress("b13pg7t", &b13pg7t, &b_b13pg7t);
   fChain->SetBranchAddress("b13pg7x", &b13pg7x, &b_b13pg7x);
   fChain->SetBranchAddress("b13pg7y", &b13pg7y, &b_b13pg7y);
   fChain->SetBranchAddress("b13pg7z", &b13pg7z, &b_b13pg7z);
   fChain->SetBranchAddress("b13pg8Edep", &b13pg8Edep, &b_b13pg8Edep);
   fChain->SetBranchAddress("b13pg8light", &b13pg8light, &b_b13pg8light);
   fChain->SetBranchAddress("b13pg8t", &b13pg8t, &b_b13pg8t);
   fChain->SetBranchAddress("b13pg8x", &b13pg8x, &b_b13pg8x);
   fChain->SetBranchAddress("b13pg8y", &b13pg8y, &b_b13pg8y);
   fChain->SetBranchAddress("b13pg8z", &b13pg8z, &b_b13pg8z);
   fChain->SetBranchAddress("b13pg9Edep", &b13pg9Edep, &b_b13pg9Edep);
   fChain->SetBranchAddress("b13pg9light", &b13pg9light, &b_b13pg9light);
   fChain->SetBranchAddress("b13pg9t", &b13pg9t, &b_b13pg9t);
   fChain->SetBranchAddress("b13pg9x", &b13pg9x, &b_b13pg9x);
   fChain->SetBranchAddress("b13pg9y", &b13pg9y, &b_b13pg9y);
   fChain->SetBranchAddress("b13pg9z", &b13pg9z, &b_b13pg9z);
   fChain->SetBranchAddress("b13pg10Edep", &b13pg10Edep, &b_b13pg10Edep);
   fChain->SetBranchAddress("b13pg10light", &b13pg10light, &b_b13pg10light);
   fChain->SetBranchAddress("b13pg10t", &b13pg10t, &b_b13pg10t);
   fChain->SetBranchAddress("b13pg10x", &b13pg10x, &b_b13pg10x);
   fChain->SetBranchAddress("b13pg10y", &b13pg10y, &b_b13pg10y);
   fChain->SetBranchAddress("b13pg10z", &b13pg10z, &b_b13pg10z);



  m_histogramsSet = Notify();
}

Bool_t STanalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

  // Silicon dE resolution
  m_siDEres = 0.90;
  cout << "Si dE resolution: " << m_siDEres << " MeV." << endl;

  m_qCut=0.;
  m_ATinit=false;

  /* Binning */
#ifndef READ_BINNING
#define READ_BINNING
#endif
#ifdef READ_BINNING
#include "/projects/e15118/redpath/analysis/histograms/binning.h"
#else
  Int_t qBins = 200;
  Double_t q1 = 0.; Double_t q2 = 1000.;
  Int_t tBins = 100;
//  Double_t t1 = -12.5; Double_t t2 = 12.5;
  Double_t t1 = 30; Double_t t2 = 55.;
  Int_t dBins = 50;
  Double_t d1 = 420.; Double_t d2 = 440.;
  Int_t xBins = 60;
  Double_t x1=-60.; Double_t x2=60.;
  Int_t yBins = 60;
  Double_t y1 = -60.; Double_t y2 = 60.;
  Int_t deBins = 100;
  Double_t de1 = 0.; Double_t de2 = 20.;
//  Int_t vBins = 150;
//  Double_t v1 = 5.; Double_t v2 = 20.;
  Int_t bvBins=48;
  Double_t bv1=12.; Double_t bv2=15.;
  Int_t vBins = 20;
  Double_t v1 = 8.; Double_t v2 = 12.;
  Int_t rvBins = 30;
  Double_t rv1 = -3.; Double_t rv2 = 3.;
  Int_t edBins = 50;
  Double_t ed1=0.; Double_t ed2=5.;
#endif

  /* Set up histograms */
  hbeamV = new TH1D("hbeamV",Form("Beam Velocity;v [cm/ns];Counts per %4.2f cm/ns",(bv2-bv1)/Float_t(bvBins)),
    bvBins,bv1,bv2);
  // aggregate
  for(int i=0;i<2;i++){
    crdcxy[i] = new TH2D(Form("crdcxy%i",i),Form("CRDC %i;x [mm];y [mm]",i+1),150,-150,150,100,-100,100);
  }
  thinxy   = new TH2D("thinxy","Thin position;x [mm];y [mm]",300,-300,300,300,-300,300);
  crdctxty = new TH2D("crdctxty","CRDC angles;#theta_{x} [mrad];#theta_{y}[mrad]",
    cxBins,cx1,cx2,cyBins,cy1,cy2);
  crdc12x  = new TH2D("crdc12x","CRDC x1:x2;crdc2.x [mm];crdc1.x [mm]",cxBins,cx1,cx2,cxBins,cx1,cx2);
  crdcxtx  = new TH2D("hhc2xtx","CRDC xtx;crdc2.x [mm];crdc2.tx [mrad]",cxBins,cx1,cx2,cxBins,cx1,cx2);
  hvelsm   = new TH1D("hvelsm","Velocity (simulated);velocity [cm/ns]", fvBins,fv1,fv2);
  hvelBp   = new TH1D("hvelBp","Velocity (frac B#rho);velocity [cm/ns]",fvBins,fv1,fv2);
  sumMult  = new TH1I("sumMult","Neutron Multiplicity",mBins,m1,m2);
  sumLight0= new TH1D("sh0q",
    Form("Hit 0 q (all tgts);q [MeVee];Counts / %4.2f MeVee",(l2-l1)/Double_t(lBins)),lBins,l1,l2);
  sumLight1= new TH1D("sh1q",
    Form("Hit 1 q (all tgts);q [MeVee];Counts / %4.2f MeVee",(l2-l1)/Double_t(lBins)),lBins,l1,l2);
  // silicon
  for(int i=0;i<4;i++){
    sixy[i] = new TH2D(Form("sixy%i",i),Form("Si %i position;x [mm];y [mm]",i),xBins,x1,x2,yBins,y1,y2);
    side[i] = new TH1D(Form("side%i",i),
      Form("Si %i dE;dE [MeV];Counts / %4.2f MeV",i,(de2-de1)/Double_t(deBins)),
      deBins,de1,de2);
  }

  for(int i=0;i<3;i++){
    hrxnpos[i] = new TH1D(Form("hrxnpos%i",i),
      Form("Reaction position (tgt%i);reaction point [mg/cm^{2} Be]",i),25,0,800);
    tgtID[i] = new TH2D(Form("tgtID%i",i),
      Form("Si %i dE : Si %i dE;Si %i dE [MeV];Si %i dE [MeV]",i+1,i,i,i+1),deBins,de1,de2,deBins,de1,de2);
    hftof[i] = new TH1D(Form("hftof%i",i),
      Form("Fragment ToF (tgt%i);ToF [ns];Counts / %3.2f ns",i+1,(t2-t1)/Double_t(tBins)),
      tBins,t1,t2);
    hfdst[i] = new TH1D(Form("hfdst%i",i),
      Form("Fragment Distance (tgt%i);Distance [cm];Counts / %3.2f cm",i+1,(d2-d1)/Double_t(dBins)),
      dBins,d1,d2);
    hfvl0[i] = new TH1D(Form("hfvl0%i",i+1),
      Form("Fragment Velocity (no addback,tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(fv2-fv1)/Double_t(fvBins)),fvBins,fv1,fv2);
    hsvel[i] = new TH1D(Form("hsvel%i",i+1),
      Form("Si 3 Fragment Velocity (no addback,tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(fv2-fv1)/Double_t(fvBins)),fvBins,fv1,fv2);
//    hsvel[i] = new TH1D(Form("hsvel%i",i+1),
//      Form("Si 3 Fragment Velocity (no addback,tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
//        i+1,(v2-v1)/Double_t(vBins)),300,1000,4000);
    hfvel[i] = new TH1D(Form("hfvel%i",i+1),
      Form("Fragment Velocity (tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(fv2-fv1)/Double_t(fvBins)),fvBins,fv1,fv2);
    hnvel[i] = new TH1D(Form("hnvel%i",i+1),
      Form("Neutron Velocity (tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(nv2-nv1)/Double_t(nvBins)),nvBins,nv1,nv2);
    hbvel[i] = new TH1D(Form("hbvel%i",i+1),
      Form("fracB#rho Fragment Velocity (tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(fv2-fv1)/Double_t(fvBins)),fvBins,fv1,fv2);
    hhNxy[i] = new TH2F(Form("hhNxy%i",i+1),
      Form("Neutron xy (tgt%i);x [cm];y [cm]",i+1),30,-150,150,20,-100,100);
    hrvel[i] = new TH1D(Form("hrvel%i",i+1),
      Form("Relative Velocity (tgt%i);v_{n-f} [cm/ns];Counts per %4.2f cm/ns",
        i+1,(rv2-rv1)/Double_t(rvBins)),rvBins,rv1,rv2);
    hvrbp[i] = new TH1D(Form("hvrbp%i",i+1),
      Form("fracB#rho Relative Velocity (tgt%i);v_{n-f} [cm/ns];Counts per %4.2f cm/ns",
        i+1,(rv2-rv1)/Double_t(rvBins)),rvBins,rv1,rv2);
    hedecay[i] = new TH1D(Form("edecay%i",i+1),
      Form("Edecay (tgt%i);E_{d} [MeV];Counts / %3.2f MeV",i+1,(ed2-ed1)/edBins),
      edBins,ed1,ed2);
    hvrxp[i] = new TH1D(Form("hfvrp%i",i+1),
      Form("Fragment Rxn Pt Velocity (tgt%i);velocity [cm/ns];Counts / %4.2f cm/ns",
        i+1,(fv2-fv1)/Double_t(fvBins)),fvBins,fv1,fv2);
    h0lgt[i] = new TH1D(Form("h0lgt%i",i+1),
      Form("b13pg1light (tgt%i);Light Depositied [MeVee];Counts / %4.2f MeVee",i+1,(l2-l1)/Double_t(lBins)),
      lBins,l1,l2);
    h1lgt[i] = new TH1D(Form("h1lgt%i",i+1),
      Form("b13pg2light (tgt%i);Light Depositied [MeVee];Counts / %4.2f MeVee",i+1,(l2-l1)/Double_t(lBins)),
      lBins,l1,l2);
    hmult[i] = new TH1I(Form("sMult%i",i+1),Form("Neutron Multiplicity (tgt%i)",i+1),mBins,m1,m2);

  }

  cout << "Setting crdc efficiency gates." << endl;
  #include"../gates/c1xc2x_left.h"
  #include"../gates/c1xc2x_mid.h"
  #include"../gates/c1xc2x_right.h"

  return kTRUE;
}

void STanalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t STanalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


void STanalysis::InitAnalysisTree(TString filename){
//  TString filename = Form("/mnt/simulations/MoNAsims/O26_analysis/analyzed/%s%sat.root",
//    m_beam.Data(),m_frag.Data());
  
  cout << "Analyzed tree will be written to " << filename.Data() << endl;
  outFile = new TFile(filename,"RECREATE");

  /* Analyzed data structures */
  at = new TTree("sat","Segmented target simulation analysis");
  at->Branch("beam",&beam,"beta/D:gamma:v");
  at->Branch("si0",&si0,"x/D:y:de");
  at->Branch("si1",&si1,"x/D:y:de");
  at->Branch("si2",&si2,"x/D:y:de");
  at->Branch("si3",&si3,"x/D:y:de");
  at->Branch("crdc1",&crdc1,"x/D:y:tx:ty:path");
  at->Branch("crdc2",&crdc2,"x/D:y:tx:ty:path");
  at->Branch("thin",&thin,"x/D:y");
  at->Branch("smult",&b13pgmultiplicity);
  at->Branch("n0",&n0,"x/D:y:z:t:dist:cosTheta:v:beta:gamma:E:P:light");
  at->Branch("frag",&frag,"dist/D:beta0/D:gamma0:v0:ke0:Bp:beta:gamma:v:ke:E:P");
  at->Branch("target",&target);
  at->Branch("edecay",&edecay);

cout << "Analysis tree initialized." << endl;
m_ATinit=true;

}
#endif // #ifdef STanalysis_cxx

inline Double_t SiVelocity(double);
inline Double_t Si3raw(double);
