#ifndef THINTOF_HH
#define THINTOF_HH
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TTree.h>
#include <TF1.h>
#include <TH2.h>
#include <TSpectrum.h>
#include <TMath.h>
#include <TBox.h>
#include <TLine.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TString.h>
#include <TCutG.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <fstream>
#include <iostream>
#include <iomanip>

class ThinToF
{
private:
  bool m_goodFile;
  bool m_calibrated;

  const char *raw;

  Int_t tBins;
  Double_t t1,t2;
  Int_t qBins;
  Double_t q1,q2;

  TFile *f;
  TTree *t;

  double t_slope,t_offset[4];
  double q_slope[4],q_offset[4];

  TH1D *tcal[4];
  TH1D *ptcal;
  TH1D *tofpt[4];

  TH2D *tofq[4];
  TH2D *tofx[4];

public:
  TCanvas *c0,*c1;
  TCanvas *c2;
  TCanvas *c3;
  TCanvas *c4;

  ThinToF();
  virtual ~ThinToF();

  void SetFile(Int_t);
  void Calibrate();
  void PotThin();

  void ToFq();
//  void ToFx();


};
#endif

Double_t fGaus(Double_t*,Double_t*);
Double_t fTwoGaus(Double_t*,Double_t*);

