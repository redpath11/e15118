#ifndef ECAL_HH
#define ECAL_HH
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TChain.h>
#include <TF1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TString.h>
#include <TCutG.h>
#include <TCanvas.h>
#include <TLine.h>
#include <fstream>
#include <iostream>
#include <iomanip>

class SiEcal: public TObject
{
protected:
  bool m_goodFile;
  bool m_histsSet;
  bool m_beamSet;
  bool m_anodesFit;
  bool m_calibrated;

  const char *beam[8];
  const char *ictf[8];

  int m_run;
  int m_beamIndex;

  Int_t m_beamColor; Int_t m_beamStyle;

  TCutG *beamCut[8];
  TCutG *icCut[8];

  Int_t rawBins;
  Double_t raw1,raw2;
  Int_t calBins;
  Double_t cal1,cal2;

  TFile *f;
//  TTree *t;
  TChain *t;

  TH1D *dE[4];
  TH1D *dEcal[4];

  TH2D *tgtCal[3];

  Double_t fragDE[8][4];
  Double_t varpDE[8][4];// lower limit
  Double_t varnDE[8][4];// upper limit

  Double_t anodeMean[8][4];
  Double_t anodeMerr[8][4];
  Double_t anodeSigm[8][4];
  Double_t anodeSerr[8][4];
  Double_t deMean[8][4];
  Double_t deSigm[8][4];

  TGraph *aSummary[4];
//  TGraphErrors *detSummary[4];
  TGraphAsymmErrors *detSummary[4];

public:
  TCanvas *c1;

  SiEcal();
  virtual ~SiEcal();

  void SetBeam(TString);
  void SetChain();

  void SetHistograms();
  void ClearHistograms();
  void FitHistograms();
  void PlotDEcal();
  void AnodeSummary();
  void DetectorSummary();
  void ReadCalibration();
  void Velocity();

  void BeamCuts(TCutG *cutg[8]);
  void ElementCuts(TCutG *cutg[8]);

//  Double_t fGaus(Double_t *x,Double_t *par);

  ClassDef(SiEcal,1)

};
#endif

Double_t fGaus(Double_t *x,Double_t *par);
Double_t fTwoGauss(Double_t *x,Double_t *par);
