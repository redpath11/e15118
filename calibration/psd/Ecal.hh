#ifndef ECAL_HH
#define ECAL_HH
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TTree.h>
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

  const char *beam[4];
  const char *ictf[4];

  int m_run;
  int m_beamIndex;

  Int_t m_beamColor; Int_t m_beamStyle;

  TCutG *beamCut[4];
  TCutG *icCut[4];

  Int_t rawBins;
  Double_t raw1,raw2;
  Int_t calBins;
  Double_t cal1,cal2;

  TFile *f;
  TTree *t;

  TH1D *dE[4];
  TH1D *dEcal[4];

  TH2D *tgtCal[3];

  Double_t fragDE[4][4];
  Double_t varpDE[4][4];// lower limit
  Double_t varnDE[4][4];// upper limit

  Double_t anodeMean[4][4];
  Double_t anodeMerr[4][4];
  Double_t anodeSigm[4][4];
  Double_t anodeSerr[4][4];
  Double_t deMean[4][4];
  Double_t deSigm[4][4];

  TGraph *aSummary[4];
//  TGraphErrors *detSummary[4];
  TGraphAsymmErrors *detSummary[4];

public:
  TCanvas *c1;

  SiEcal();
  virtual ~SiEcal();

  void SetBeam(TString);
  void SetFile(Int_t);
  void SetFiltered(TString);

  void SetHistograms();
  void ClearHistograms();
  void FitHistograms();
  void PlotDEcal();
  void PlotDEfiltered();
  void PlotDEfilteredGated(Double_t,
  			Double_t,
			TCanvas *c);
  void AnodeSummary();
  void DetectorSummary();
  void ReadCalibration();
  void Velocity();

  void BeamCuts(TCutG *cutg[4]);
  void ElementCuts(TCutG *cutg[4]);

//  Double_t fGaus(Double_t *x,Double_t *par);

  ClassDef(SiEcal,1)

};
#endif

Double_t fGaus(Double_t *x,Double_t *par);
Double_t fTwoGauss(Double_t *x,Double_t *par);
