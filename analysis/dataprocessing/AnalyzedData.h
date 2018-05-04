//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  4 09:17:23 2018 by ROOT version 5.34/32
// from TTree t/Combined tree created from /mnt/analysis/e15118/root_merged/run-1038-merged.root
// found on file: all_F27-O24_28jan.root
//////////////////////////////////////////////////////////

#ifndef AnalyzedData_h
#define AnalyzedData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2.h>
#include <TCutG.h>
#include <TStyle.h>
#include <iostream>
#include <iomanip>

// Header file for the classes stored in the TTree if any.
#include "/projects/e15118/n2analysis/src/./sweeper.hh"
#include "/projects/e15118/n2analysis/src/./mona.hh"
//#include "/projects/e15118/redpath/analysis/lifetime/analysistree.hh"
#include "/projects/e15118/redpath/simulation/histograms/STanalysis/src/AnalysisStructures.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class AnalyzedData : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  /* output a file containing the raw, calibrated and analyzed trees */
  TFile *outFile;
  TTree *at;

  /* Physical constants, settings */
  Double_t C;
  Double_t amuM;
  Double_t nMamu;
  Double_t t_slope;
  Double_t bp;

  /* control parameters for beam/fragment */
  TString m_beam; TString m_fragment;
  Double_t tof_offset;
  Int_t m_beamIndex;
  Int_t m_elmtIndex;
  Double_t beamA; Double_t beamZ;
  Double_t fragA; Double_t fragZ;

  /* arrays to hold correction parameters */
  Double_t q0[4]; Double_t q1[4];
  Double_t x0[4]; Double_t x1[4]; Double_t x2[4]; Double_t x3[4];
  Double_t y0[4]; Double_t y1[4];
  int index[4][4];

  Double_t siSlope[4]; Double_t siOffst[4];

  /* 2d graphical cuts */
  TCutG *Beam; TCutG *elmt;
  TCutG *tgt1; TCutG *tgt2; TCutG* tgt3;

  /* adjustments */
  Double_t mona_tshift[3];
  Double_t mona_zshift[3];
  Double_t addback[3];

  /* leaf types for analyzed tree - defined by class AnalysisStructures.h */
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
  FRAGMENT frag_bp;
  TOF tof;

  UShort_t target;
  Double_t edecay;

  /* uncooperative variables 
  // tof branch
  UShort_t tof_nfired;// number of thin PMTs with a valid signal
  Double_t tof_un;// uncorrected average of thin times
  Double_t tof_q[4];// q corrected tof per PMT
  Double_t tof_qx[4];// q and x corrected tof per PMT
  Double_t tof_qxy[4];// q,x,y corrected (final) ToF
  Double_t tof_pt;// arithmetic mean of PMT signals
  Double_t tof_frag;// corrected and offset ToF signal
*/
  // silicon branch
  Double_t si_de[4];// si calibrated dE
  Double_t si_sum[4];// sum of corner signals
  Double_t si_left[4];// sum of 2 left corners
  Double_t si_right[4];// sum of 2 right corners
  Double_t si_up[4];// sum of 2 upper corners
  Double_t si_down[4];// sum of 2 lower corners
  Double_t si_x[4];// crude x position calculation
  Double_t si_y[4];// curde y position calculation



   // Declaration of leaf types
 //cal::sweeper    *cal__sweeper;
   Double_t        v;
   Double_t        e;
   Double_t        p;
   Int_t           crdc1_pad_fcpy[128];
   Double_t        crdc1_pad_cal[128];
   Int_t           crdc1_padmax;
   Double_t        crdc1_padsum;
   Double_t        crdc1_sigma;
   Double_t        crdc1_x_gravity;
   Double_t        crdc1_x_fit;
   Double_t        crdc1_x_chi2;
   Double_t        crdc1_x;
   Double_t        crdc1_tx;
   Double_t        crdc1_y;
   Double_t        crdc1_ty;
   Int_t           crdc2_pad_fcpy[128];
   Double_t        crdc2_pad_cal[128];
   Int_t           crdc2_padmax;
   Double_t        crdc2_padsum;
   Double_t        crdc2_sigma;
   Double_t        crdc2_x_gravity;
   Double_t        crdc2_x_fit;
   Double_t        crdc2_x_chi2;
   Double_t        crdc2_x;
   Double_t        crdc2_tx;
   Double_t        crdc2_y;
   Double_t        crdc2_ty;
   Double_t        tcrdc1_pad_cal[64];
   Int_t           tcrdc1_padmax;
   Double_t        tcrdc1_padsum;
   Double_t        tcrdc1_sigma;
   Double_t        tcrdc1_x_gravity;
   Double_t        tcrdc1_x_fit;
   Double_t        tcrdc1_x_chi2;
   Double_t        tcrdc1_x;
   Double_t        tcrdc1_tx;
   Double_t        tcrdc1_y;
   Double_t        tcrdc1_ty;
   Double_t        tcrdc2_pad_cal[64];
   Int_t           tcrdc2_padmax;
   Double_t        tcrdc2_padsum;
   Double_t        tcrdc2_sigma;
   Double_t        tcrdc2_x_gravity;
   Double_t        tcrdc2_x_fit;
   Double_t        tcrdc2_x_chi2;
   Double_t        tcrdc2_x;
   Double_t        tcrdc2_tx;
   Double_t        tcrdc2_y;
   Double_t        tcrdc2_ty;
   Double_t        ic_cal[16];
   Double_t        ic_sum;
   Double_t        ic_de;
   Double_t        ic_corr[16];
   Double_t        ic_de_corr;
   Double_t        thin_tcal[4];
   Double_t        thin_qcal[4];
   Double_t        thin_e;
   Double_t        thin_ecorr;
   Double_t        thin_t;
   Double_t        thin_xpos;
   Double_t        thin_ypos;
   Double_t        thin_x;
   Double_t        thin_tx;
   Double_t        thin_y;
   Double_t        thin_ty;
   Double_t        st_anode[4];
   Double_t        st_corner[4][4];
   Double_t        st_x[4];
   Double_t        st_y[4];
   Double_t        st_ecal[4];
   Double_t        hodo_cal[25];
   Double_t        hodo_sum;
   Int_t           hodo_maxcrystal;
   Int_t           hodo_mult;
   Double_t        hodo_x;
   Double_t        hodo_tx;
   Double_t        hodo_y;
   Double_t        hodo_ty;
   Double_t        pot_tcal;
   Double_t        pot_qcal;
   Double_t        rf_tcal;
   Double_t        a1900_tcal;
   Double_t        tof_rf_a1900;
   Double_t        tof_rf_pot;
   Double_t        tof_rf_thin;
   Double_t        tof_a1900_pot;
   Double_t        tof_a1900_thin;
   Double_t        tof_pot_thin;
   Double_t        tof_rf_diamond;
   Double_t        tof_a1900_diamond;
   Double_t        tof_pot_diamond;
   Double_t        tof_diamond_thin;
   Double_t        tofcorr_rf_thin;
   Double_t        tofcorr_a1900_thin;
   Double_t        tofcorr_pot_thin;
   Double_t        focus_x;
   Double_t        focus_tx;
   Double_t        focus_y;
   Double_t        focus_ty;
   Double_t        ftrack_x;
   Double_t        ftrack_tx;
   Double_t        ftrack_y;
   Double_t        ftrack_ty;
   Double_t        itrack_x;
   Double_t        itrack_tx;
   Double_t        itrack_y;
   Double_t        itrack_ty;
   Double_t        itrack_len;
   Double_t        itrack_de;
   Double_t        itrack_e;
   Double_t        itrack_p;
   Double_t        diamond_tcal[4];
   Double_t        diamond_qcal[4];
   Double_t        diamond_t_hit;
   Short_t         diamond_strip;
   Short_t         diamond_nhits;
 //raw::sweeper    *raw__sweeper;
   UShort_t        tdc_data[32][32];
   UShort_t        tdc_raw[32];
   Short_t         tdc_hits[32];
   Short_t         trigger_registr;
   Short_t         trigger_sweeper;
   Short_t         trigger_external1;
   Short_t         trigger_external2;
   Short_t         trigger_secondary;
   Short_t         trigger_pattern;
   Short_t         trigger_timestamp[4];
   Short_t         crdc1_anode;
   Short_t         crdc1_tac;
   Short_t         crdc1_sample_width;
   Short_t         crdc1_pad_nsamples[128];
   Short_t         crdc1_pad_raw[128];
   Short_t         crdc1_pad_sample[128][32];
   Short_t         crdc2_anode;
   Short_t         crdc2_tac;
   Short_t         crdc2_sample_width;
   Short_t         crdc2_pad_nsamples[128];
   Short_t         crdc2_pad_raw[128];
   Short_t         crdc2_pad_sample[128][32];
   Short_t         tcrdc1_anode;
   Short_t         tcrdc1_tac;
   Short_t         tcrdc1_sample_width;
   Short_t         tcrdc1_pad_nsamples[64];
   Short_t         tcrdc1_pad_raw[64];
   Short_t         tcrdc1_pad_sample[64][32];
   Short_t         tcrdc2_anode;
   Short_t         tcrdc2_tac;
   Short_t         tcrdc2_sample_width;
   Short_t         tcrdc2_pad_nsamples[64];
   Short_t         tcrdc2_pad_raw[64];
   Short_t         tcrdc2_pad_sample[64][32];
   Short_t         ic_raw[16];
   Short_t         thin_qraw[4];
   Short_t         thin_traw[4];
   Short_t         st_raw[32];
   Short_t         hodo_raw[25];
   Short_t         pot_traw;
   Short_t         pot_qraw;
   Short_t         a1900_traw;
   Short_t         rf_traw;
   Short_t         diamond_traw[4];
   Short_t         diamond_qraw[4];
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
//   Double_t        v;
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
   TBranch        *b_cal__sweeper_v;   //!
   TBranch        *b_cal__sweeper_e;   //!
   TBranch        *b_cal__sweeper_p;   //!
   TBranch        *b_cal__sweeper_crdc1_pad_fcpy;   //!
   TBranch        *b_cal__sweeper_crdc1_pad_cal;   //!
   TBranch        *b_cal__sweeper_crdc1_padmax;   //!
   TBranch        *b_cal__sweeper_crdc1_padsum;   //!
   TBranch        *b_cal__sweeper_crdc1_sigma;   //!
   TBranch        *b_cal__sweeper_crdc1_x_gravity;   //!
   TBranch        *b_cal__sweeper_crdc1_x_fit;   //!
   TBranch        *b_cal__sweeper_crdc1_x_chi2;   //!
   TBranch        *b_cal__sweeper_crdc1_x;   //!
   TBranch        *b_cal__sweeper_crdc1_tx;   //!
   TBranch        *b_cal__sweeper_crdc1_y;   //!
   TBranch        *b_cal__sweeper_crdc1_ty;   //!
   TBranch        *b_cal__sweeper_crdc2_pad_fcpy;   //!
   TBranch        *b_cal__sweeper_crdc2_pad_cal;   //!
   TBranch        *b_cal__sweeper_crdc2_padmax;   //!
   TBranch        *b_cal__sweeper_crdc2_padsum;   //!
   TBranch        *b_cal__sweeper_crdc2_sigma;   //!
   TBranch        *b_cal__sweeper_crdc2_x_gravity;   //!
   TBranch        *b_cal__sweeper_crdc2_x_fit;   //!
   TBranch        *b_cal__sweeper_crdc2_x_chi2;   //!
   TBranch        *b_cal__sweeper_crdc2_x;   //!
   TBranch        *b_cal__sweeper_crdc2_tx;   //!
   TBranch        *b_cal__sweeper_crdc2_y;   //!
   TBranch        *b_cal__sweeper_crdc2_ty;   //!
   TBranch        *b_cal__sweeper_tcrdc1_pad_cal;   //!
   TBranch        *b_cal__sweeper_tcrdc1_padmax;   //!
   TBranch        *b_cal__sweeper_tcrdc1_padsum;   //!
   TBranch        *b_cal__sweeper_tcrdc1_sigma;   //!
   TBranch        *b_cal__sweeper_tcrdc1_x_gravity;   //!
   TBranch        *b_cal__sweeper_tcrdc1_x_fit;   //!
   TBranch        *b_cal__sweeper_tcrdc1_x_chi2;   //!
   TBranch        *b_cal__sweeper_tcrdc1_x;   //!
   TBranch        *b_cal__sweeper_tcrdc1_tx;   //!
   TBranch        *b_cal__sweeper_tcrdc1_y;   //!
   TBranch        *b_cal__sweeper_tcrdc1_ty;   //!
   TBranch        *b_cal__sweeper_tcrdc2_pad_cal;   //!
   TBranch        *b_cal__sweeper_tcrdc2_padmax;   //!
   TBranch        *b_cal__sweeper_tcrdc2_padsum;   //!
   TBranch        *b_cal__sweeper_tcrdc2_sigma;   //!
   TBranch        *b_cal__sweeper_tcrdc2_x_gravity;   //!
   TBranch        *b_cal__sweeper_tcrdc2_x_fit;   //!
   TBranch        *b_cal__sweeper_tcrdc2_x_chi2;   //!
   TBranch        *b_cal__sweeper_tcrdc2_x;   //!
   TBranch        *b_cal__sweeper_tcrdc2_tx;   //!
   TBranch        *b_cal__sweeper_tcrdc2_y;   //!
   TBranch        *b_cal__sweeper_tcrdc2_ty;   //!
   TBranch        *b_cal__sweeper_ic_cal;   //!
   TBranch        *b_cal__sweeper_ic_sum;   //!
   TBranch        *b_cal__sweeper_ic_de;   //!
   TBranch        *b_cal__sweeper_ic_corr;   //!
   TBranch        *b_cal__sweeper_ic_de_corr;   //!
   TBranch        *b_cal__sweeper_thin_tcal;   //!
   TBranch        *b_cal__sweeper_thin_qcal;   //!
   TBranch        *b_cal__sweeper_thin_e;   //!
   TBranch        *b_cal__sweeper_thin_ecorr;   //!
   TBranch        *b_cal__sweeper_thin_t;   //!
   TBranch        *b_cal__sweeper_thin_xpos;   //!
   TBranch        *b_cal__sweeper_thin_ypos;   //!
   TBranch        *b_cal__sweeper_thin_x;   //!
   TBranch        *b_cal__sweeper_thin_tx;   //!
   TBranch        *b_cal__sweeper_thin_y;   //!
   TBranch        *b_cal__sweeper_thin_ty;   //!
   TBranch        *b_cal__sweeper_st_anode;   //!
   TBranch        *b_cal__sweeper_st_corner;   //!
   TBranch        *b_cal__sweeper_st_x;   //!
   TBranch        *b_cal__sweeper_st_y;   //!
   TBranch        *b_cal__sweeper_st_ecal;   //!
   TBranch        *b_cal__sweeper_hodo_cal;   //!
   TBranch        *b_cal__sweeper_hodo_sum;   //!
   TBranch        *b_cal__sweeper_hodo_maxcrystal;   //!
   TBranch        *b_cal__sweeper_hodo_mult;   //!
   TBranch        *b_cal__sweeper_hodo_x;   //!
   TBranch        *b_cal__sweeper_hodo_tx;   //!
   TBranch        *b_cal__sweeper_hodo_y;   //!
   TBranch        *b_cal__sweeper_hodo_ty;   //!
   TBranch        *b_cal__sweeper_pot_tcal;   //!
   TBranch        *b_cal__sweeper_pot_qcal;   //!
   TBranch        *b_cal__sweeper_rf_tcal;   //!
   TBranch        *b_cal__sweeper_a1900_tcal;   //!
   TBranch        *b_cal__sweeper_tof_rf_a1900;   //!
   TBranch        *b_cal__sweeper_tof_rf_pot;   //!
   TBranch        *b_cal__sweeper_tof_rf_thin;   //!
   TBranch        *b_cal__sweeper_tof_a1900_pot;   //!
   TBranch        *b_cal__sweeper_tof_a1900_thin;   //!
   TBranch        *b_cal__sweeper_tof_pot_thin;   //!
   TBranch        *b_cal__sweeper_tof_rf_diamond;   //!
   TBranch        *b_cal__sweeper_tof_a1900_diamond;   //!
   TBranch        *b_cal__sweeper_tof_pot_diamond;   //!
   TBranch        *b_cal__sweeper_tof_diamond_thin;   //!
   TBranch        *b_cal__sweeper_tofcorr_rf_thin;   //!
   TBranch        *b_cal__sweeper_tofcorr_a1900_thin;   //!
   TBranch        *b_cal__sweeper_tofcorr_pot_thin;   //!
   TBranch        *b_cal__sweeper_focus_x;   //!
   TBranch        *b_cal__sweeper_focus_tx;   //!
   TBranch        *b_cal__sweeper_focus_y;   //!
   TBranch        *b_cal__sweeper_focus_ty;   //!
   TBranch        *b_cal__sweeper_ftrack_x;   //!
   TBranch        *b_cal__sweeper_ftrack_tx;   //!
   TBranch        *b_cal__sweeper_ftrack_y;   //!
   TBranch        *b_cal__sweeper_ftrack_ty;   //!
   TBranch        *b_cal__sweeper_itrack_x;   //!
   TBranch        *b_cal__sweeper_itrack_tx;   //!
   TBranch        *b_cal__sweeper_itrack_y;   //!
   TBranch        *b_cal__sweeper_itrack_ty;   //!
   TBranch        *b_cal__sweeper_itrack_len;   //!
   TBranch        *b_cal__sweeper_itrack_de;   //!
   TBranch        *b_cal__sweeper_itrack_e;   //!
   TBranch        *b_cal__sweeper_itrack_p;   //!
   TBranch        *b_cal__sweeper_diamond_tcal;   //!
   TBranch        *b_cal__sweeper_diamond_qcal;   //!
   TBranch        *b_cal__sweeper_diamond_t_hit;   //!
   TBranch        *b_cal__sweeper_diamond_strip;   //!
   TBranch        *b_cal__sweeper_diamond_nhits;   //!
   TBranch        *b_raw__sweeper_tdc_data;   //!
   TBranch        *b_raw__sweeper_tdc_raw;   //!
   TBranch        *b_raw__sweeper_tdc_hits;   //!
   TBranch        *b_raw__sweeper_trigger_registr;   //!
   TBranch        *b_raw__sweeper_trigger_sweeper;   //!
   TBranch        *b_raw__sweeper_trigger_external1;   //!
   TBranch        *b_raw__sweeper_trigger_external2;   //!
   TBranch        *b_raw__sweeper_trigger_secondary;   //!
   TBranch        *b_raw__sweeper_trigger_pattern;   //!
   TBranch        *b_raw__sweeper_trigger_timestamp;   //!
   TBranch        *b_raw__sweeper_crdc1_anode;   //!
   TBranch        *b_raw__sweeper_crdc1_tac;   //!
   TBranch        *b_raw__sweeper_crdc1_sample_width;   //!
   TBranch        *b_raw__sweeper_crdc1_pad_nsamples;   //!
   TBranch        *b_raw__sweeper_crdc1_pad_raw;   //!
   TBranch        *b_raw__sweeper_crdc1_pad_sample;   //!
   TBranch        *b_raw__sweeper_crdc2_anode;   //!
   TBranch        *b_raw__sweeper_crdc2_tac;   //!
   TBranch        *b_raw__sweeper_crdc2_sample_width;   //!
   TBranch        *b_raw__sweeper_crdc2_pad_nsamples;   //!
   TBranch        *b_raw__sweeper_crdc2_pad_raw;   //!
   TBranch        *b_raw__sweeper_crdc2_pad_sample;   //!
   TBranch        *b_raw__sweeper_tcrdc1_anode;   //!
   TBranch        *b_raw__sweeper_tcrdc1_tac;   //!
   TBranch        *b_raw__sweeper_tcrdc1_sample_width;   //!
   TBranch        *b_raw__sweeper_tcrdc1_pad_nsamples;   //!
   TBranch        *b_raw__sweeper_tcrdc1_pad_raw;   //!
   TBranch        *b_raw__sweeper_tcrdc1_pad_sample;   //!
   TBranch        *b_raw__sweeper_tcrdc2_anode;   //!
   TBranch        *b_raw__sweeper_tcrdc2_tac;   //!
   TBranch        *b_raw__sweeper_tcrdc2_sample_width;   //!
   TBranch        *b_raw__sweeper_tcrdc2_pad_nsamples;   //!
   TBranch        *b_raw__sweeper_tcrdc2_pad_raw;   //!
   TBranch        *b_raw__sweeper_tcrdc2_pad_sample;   //!
   TBranch        *b_raw__sweeper_ic_raw;   //!
   TBranch        *b_raw__sweeper_thin_qraw;   //!
   TBranch        *b_raw__sweeper_thin_traw;   //!
   TBranch        *b_raw__sweeper_st_raw;   //!
   TBranch        *b_raw__sweeper_hodo_raw;   //!
   TBranch        *b_raw__sweeper_pot_traw;   //!
   TBranch        *b_raw__sweeper_pot_qraw;   //!
   TBranch        *b_raw__sweeper_a1900_traw;   //!
   TBranch        *b_raw__sweeper_rf_traw;   //!
   TBranch        *b_raw__sweeper_diamond_traw;   //!
   TBranch        *b_raw__sweeper_diamond_qraw;   //!
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
//   TBranch        *b_cal__mona_v;   //!
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

   AnalyzedData(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~AnalyzedData() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   void SetBeam(TString beam);
   void SetFragment(TString frag);

   void InitAnalyzedTree();

   void ReadCorrections();
   void GraphicalCuts();

   void Reset();

   ClassDef(AnalyzedData,0);
};

#endif

#ifdef AnalyzedData_cxx
void AnalyzedData::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("v", &v, &b_cal__sweeper_v);
   fChain->SetBranchAddress("e", &e, &b_cal__sweeper_e);
   fChain->SetBranchAddress("p", &p, &b_cal__sweeper_p);
   fChain->SetBranchAddress("crdc1.pad.fcpy[128]", crdc1_pad_fcpy, &b_cal__sweeper_crdc1_pad_fcpy);
   fChain->SetBranchAddress("crdc1.pad.cal[128]", crdc1_pad_cal, &b_cal__sweeper_crdc1_pad_cal);
   fChain->SetBranchAddress("crdc1.padmax", &crdc1_padmax, &b_cal__sweeper_crdc1_padmax);
   fChain->SetBranchAddress("crdc1.padsum", &crdc1_padsum, &b_cal__sweeper_crdc1_padsum);
   fChain->SetBranchAddress("crdc1.sigma", &crdc1_sigma, &b_cal__sweeper_crdc1_sigma);
   fChain->SetBranchAddress("crdc1.x_gravity", &crdc1_x_gravity, &b_cal__sweeper_crdc1_x_gravity);
   fChain->SetBranchAddress("crdc1.x_fit", &crdc1_x_fit, &b_cal__sweeper_crdc1_x_fit);
   fChain->SetBranchAddress("crdc1.x_chi2", &crdc1_x_chi2, &b_cal__sweeper_crdc1_x_chi2);
   fChain->SetBranchAddress("crdc1.x", &crdc1_x, &b_cal__sweeper_crdc1_x);
   fChain->SetBranchAddress("crdc1.tx", &crdc1_tx, &b_cal__sweeper_crdc1_tx);
   fChain->SetBranchAddress("crdc1.y", &crdc1_y, &b_cal__sweeper_crdc1_y);
   fChain->SetBranchAddress("crdc1.ty", &crdc1_ty, &b_cal__sweeper_crdc1_ty);
   fChain->SetBranchAddress("crdc2.pad.fcpy[128]", crdc2_pad_fcpy, &b_cal__sweeper_crdc2_pad_fcpy);
   fChain->SetBranchAddress("crdc2.pad.cal[128]", crdc2_pad_cal, &b_cal__sweeper_crdc2_pad_cal);
   fChain->SetBranchAddress("crdc2.padmax", &crdc2_padmax, &b_cal__sweeper_crdc2_padmax);
   fChain->SetBranchAddress("crdc2.padsum", &crdc2_padsum, &b_cal__sweeper_crdc2_padsum);
   fChain->SetBranchAddress("crdc2.sigma", &crdc2_sigma, &b_cal__sweeper_crdc2_sigma);
   fChain->SetBranchAddress("crdc2.x_gravity", &crdc2_x_gravity, &b_cal__sweeper_crdc2_x_gravity);
   fChain->SetBranchAddress("crdc2.x_fit", &crdc2_x_fit, &b_cal__sweeper_crdc2_x_fit);
   fChain->SetBranchAddress("crdc2.x_chi2", &crdc2_x_chi2, &b_cal__sweeper_crdc2_x_chi2);
   fChain->SetBranchAddress("crdc2.x", &crdc2_x, &b_cal__sweeper_crdc2_x);
   fChain->SetBranchAddress("crdc2.tx", &crdc2_tx, &b_cal__sweeper_crdc2_tx);
   fChain->SetBranchAddress("crdc2.y", &crdc2_y, &b_cal__sweeper_crdc2_y);
   fChain->SetBranchAddress("crdc2.ty", &crdc2_ty, &b_cal__sweeper_crdc2_ty);
   fChain->SetBranchAddress("tcrdc1.pad.cal[64]", tcrdc1_pad_cal, &b_cal__sweeper_tcrdc1_pad_cal);
   fChain->SetBranchAddress("tcrdc1.padmax", &tcrdc1_padmax, &b_cal__sweeper_tcrdc1_padmax);
   fChain->SetBranchAddress("tcrdc1.padsum", &tcrdc1_padsum, &b_cal__sweeper_tcrdc1_padsum);
   fChain->SetBranchAddress("tcrdc1.sigma", &tcrdc1_sigma, &b_cal__sweeper_tcrdc1_sigma);
   fChain->SetBranchAddress("tcrdc1.x_gravity", &tcrdc1_x_gravity, &b_cal__sweeper_tcrdc1_x_gravity);
   fChain->SetBranchAddress("tcrdc1.x_fit", &tcrdc1_x_fit, &b_cal__sweeper_tcrdc1_x_fit);
   fChain->SetBranchAddress("tcrdc1.x_chi2", &tcrdc1_x_chi2, &b_cal__sweeper_tcrdc1_x_chi2);
   fChain->SetBranchAddress("tcrdc1.x", &tcrdc1_x, &b_cal__sweeper_tcrdc1_x);
   fChain->SetBranchAddress("tcrdc1.tx", &tcrdc1_tx, &b_cal__sweeper_tcrdc1_tx);
   fChain->SetBranchAddress("tcrdc1.y", &tcrdc1_y, &b_cal__sweeper_tcrdc1_y);
   fChain->SetBranchAddress("tcrdc1.ty", &tcrdc1_ty, &b_cal__sweeper_tcrdc1_ty);
   fChain->SetBranchAddress("tcrdc2.pad.cal[64]", tcrdc2_pad_cal, &b_cal__sweeper_tcrdc2_pad_cal);
   fChain->SetBranchAddress("tcrdc2.padmax", &tcrdc2_padmax, &b_cal__sweeper_tcrdc2_padmax);
   fChain->SetBranchAddress("tcrdc2.padsum", &tcrdc2_padsum, &b_cal__sweeper_tcrdc2_padsum);
   fChain->SetBranchAddress("tcrdc2.sigma", &tcrdc2_sigma, &b_cal__sweeper_tcrdc2_sigma);
   fChain->SetBranchAddress("tcrdc2.x_gravity", &tcrdc2_x_gravity, &b_cal__sweeper_tcrdc2_x_gravity);
   fChain->SetBranchAddress("tcrdc2.x_fit", &tcrdc2_x_fit, &b_cal__sweeper_tcrdc2_x_fit);
   fChain->SetBranchAddress("tcrdc2.x_chi2", &tcrdc2_x_chi2, &b_cal__sweeper_tcrdc2_x_chi2);
   fChain->SetBranchAddress("tcrdc2.x", &tcrdc2_x, &b_cal__sweeper_tcrdc2_x);
   fChain->SetBranchAddress("tcrdc2.tx", &tcrdc2_tx, &b_cal__sweeper_tcrdc2_tx);
   fChain->SetBranchAddress("tcrdc2.y", &tcrdc2_y, &b_cal__sweeper_tcrdc2_y);
   fChain->SetBranchAddress("tcrdc2.ty", &tcrdc2_ty, &b_cal__sweeper_tcrdc2_ty);
   fChain->SetBranchAddress("ic.cal[16]", ic_cal, &b_cal__sweeper_ic_cal);
   fChain->SetBranchAddress("ic.sum", &ic_sum, &b_cal__sweeper_ic_sum);
   fChain->SetBranchAddress("ic.de", &ic_de, &b_cal__sweeper_ic_de);
   fChain->SetBranchAddress("ic.corr[16]", ic_corr, &b_cal__sweeper_ic_corr);
   fChain->SetBranchAddress("ic.de_corr", &ic_de_corr, &b_cal__sweeper_ic_de_corr);
   fChain->SetBranchAddress("thin.tcal[4]", thin_tcal, &b_cal__sweeper_thin_tcal);
   fChain->SetBranchAddress("thin.qcal[4]", thin_qcal, &b_cal__sweeper_thin_qcal);
   fChain->SetBranchAddress("thin.e", &thin_e, &b_cal__sweeper_thin_e);
   fChain->SetBranchAddress("thin.ecorr", &thin_ecorr, &b_cal__sweeper_thin_ecorr);
   fChain->SetBranchAddress("thin.t", &thin_t, &b_cal__sweeper_thin_t);
   fChain->SetBranchAddress("thin.xpos", &thin_xpos, &b_cal__sweeper_thin_xpos);
   fChain->SetBranchAddress("thin.ypos", &thin_ypos, &b_cal__sweeper_thin_ypos);
   fChain->SetBranchAddress("thin.x", &thin_x, &b_cal__sweeper_thin_x);
   fChain->SetBranchAddress("thin.tx", &thin_tx, &b_cal__sweeper_thin_tx);
   fChain->SetBranchAddress("thin.y", &thin_y, &b_cal__sweeper_thin_y);
   fChain->SetBranchAddress("thin.ty", &thin_ty, &b_cal__sweeper_thin_ty);
   fChain->SetBranchAddress("st.anode[4]", st_anode, &b_cal__sweeper_st_anode);
   fChain->SetBranchAddress("st.corner[4][4]", st_corner, &b_cal__sweeper_st_corner);
   fChain->SetBranchAddress("st.x[4]", st_x, &b_cal__sweeper_st_x);
   fChain->SetBranchAddress("st.y[4]", st_y, &b_cal__sweeper_st_y);
   fChain->SetBranchAddress("st.ecal[4]", st_ecal, &b_cal__sweeper_st_ecal);
   fChain->SetBranchAddress("hodo.cal[25]", hodo_cal, &b_cal__sweeper_hodo_cal);
   fChain->SetBranchAddress("hodo.sum", &hodo_sum, &b_cal__sweeper_hodo_sum);
   fChain->SetBranchAddress("hodo.maxcrystal", &hodo_maxcrystal, &b_cal__sweeper_hodo_maxcrystal);
   fChain->SetBranchAddress("hodo.mult", &hodo_mult, &b_cal__sweeper_hodo_mult);
   fChain->SetBranchAddress("hodo.x", &hodo_x, &b_cal__sweeper_hodo_x);
   fChain->SetBranchAddress("hodo.tx", &hodo_tx, &b_cal__sweeper_hodo_tx);
   fChain->SetBranchAddress("hodo.y", &hodo_y, &b_cal__sweeper_hodo_y);
   fChain->SetBranchAddress("hodo.ty", &hodo_ty, &b_cal__sweeper_hodo_ty);
   fChain->SetBranchAddress("pot.tcal", &pot_tcal, &b_cal__sweeper_pot_tcal);
   fChain->SetBranchAddress("pot.qcal", &pot_qcal, &b_cal__sweeper_pot_qcal);
   fChain->SetBranchAddress("rf.tcal", &rf_tcal, &b_cal__sweeper_rf_tcal);
   fChain->SetBranchAddress("a1900.tcal", &a1900_tcal, &b_cal__sweeper_a1900_tcal);
   fChain->SetBranchAddress("tof.rf_a1900", &tof_rf_a1900, &b_cal__sweeper_tof_rf_a1900);
   fChain->SetBranchAddress("tof.rf_pot", &tof_rf_pot, &b_cal__sweeper_tof_rf_pot);
   fChain->SetBranchAddress("tof.rf_thin", &tof_rf_thin, &b_cal__sweeper_tof_rf_thin);
   fChain->SetBranchAddress("tof.a1900_pot", &tof_a1900_pot, &b_cal__sweeper_tof_a1900_pot);
   fChain->SetBranchAddress("tof.a1900_thin", &tof_a1900_thin, &b_cal__sweeper_tof_a1900_thin);
   fChain->SetBranchAddress("tof.pot_thin", &tof_pot_thin, &b_cal__sweeper_tof_pot_thin);
   fChain->SetBranchAddress("tof.rf_diamond", &tof_rf_diamond, &b_cal__sweeper_tof_rf_diamond);
   fChain->SetBranchAddress("tof.a1900_diamond", &tof_a1900_diamond, &b_cal__sweeper_tof_a1900_diamond);
   fChain->SetBranchAddress("tof.pot_diamond", &tof_pot_diamond, &b_cal__sweeper_tof_pot_diamond);
   fChain->SetBranchAddress("tof.diamond_thin", &tof_diamond_thin, &b_cal__sweeper_tof_diamond_thin);
   fChain->SetBranchAddress("tofcorr.rf_thin", &tofcorr_rf_thin, &b_cal__sweeper_tofcorr_rf_thin);
   fChain->SetBranchAddress("tofcorr.a1900_thin", &tofcorr_a1900_thin, &b_cal__sweeper_tofcorr_a1900_thin);
   fChain->SetBranchAddress("tofcorr.pot_thin", &tofcorr_pot_thin, &b_cal__sweeper_tofcorr_pot_thin);
   fChain->SetBranchAddress("focus.x", &focus_x, &b_cal__sweeper_focus_x);
   fChain->SetBranchAddress("focus.tx", &focus_tx, &b_cal__sweeper_focus_tx);
   fChain->SetBranchAddress("focus.y", &focus_y, &b_cal__sweeper_focus_y);
   fChain->SetBranchAddress("focus.ty", &focus_ty, &b_cal__sweeper_focus_ty);
   fChain->SetBranchAddress("ftrack.x", &ftrack_x, &b_cal__sweeper_ftrack_x);
   fChain->SetBranchAddress("ftrack.tx", &ftrack_tx, &b_cal__sweeper_ftrack_tx);
   fChain->SetBranchAddress("ftrack.y", &ftrack_y, &b_cal__sweeper_ftrack_y);
   fChain->SetBranchAddress("ftrack.ty", &ftrack_ty, &b_cal__sweeper_ftrack_ty);
   fChain->SetBranchAddress("itrack.x", &itrack_x, &b_cal__sweeper_itrack_x);
   fChain->SetBranchAddress("itrack.tx", &itrack_tx, &b_cal__sweeper_itrack_tx);
   fChain->SetBranchAddress("itrack.y", &itrack_y, &b_cal__sweeper_itrack_y);
   fChain->SetBranchAddress("itrack.ty", &itrack_ty, &b_cal__sweeper_itrack_ty);
   fChain->SetBranchAddress("itrack.len", &itrack_len, &b_cal__sweeper_itrack_len);
   fChain->SetBranchAddress("itrack.de", &itrack_de, &b_cal__sweeper_itrack_de);
   fChain->SetBranchAddress("itrack.e", &itrack_e, &b_cal__sweeper_itrack_e);
   fChain->SetBranchAddress("itrack.p", &itrack_p, &b_cal__sweeper_itrack_p);
   fChain->SetBranchAddress("diamond.tcal[4]", diamond_tcal, &b_cal__sweeper_diamond_tcal);
   fChain->SetBranchAddress("diamond.qcal[4]", diamond_qcal, &b_cal__sweeper_diamond_qcal);
   fChain->SetBranchAddress("diamond.t_hit", &diamond_t_hit, &b_cal__sweeper_diamond_t_hit);
   fChain->SetBranchAddress("diamond.strip", &diamond_strip, &b_cal__sweeper_diamond_strip);
   fChain->SetBranchAddress("diamond.nhits", &diamond_nhits, &b_cal__sweeper_diamond_nhits);
   fChain->SetBranchAddress("tdc.data[32][32]", tdc_data, &b_raw__sweeper_tdc_data);
   fChain->SetBranchAddress("tdc.raw[32]", tdc_raw, &b_raw__sweeper_tdc_raw);
   fChain->SetBranchAddress("tdc.hits[32]", tdc_hits, &b_raw__sweeper_tdc_hits);
   fChain->SetBranchAddress("trigger.registr", &trigger_registr, &b_raw__sweeper_trigger_registr);
   fChain->SetBranchAddress("trigger.sweeper", &trigger_sweeper, &b_raw__sweeper_trigger_sweeper);
   fChain->SetBranchAddress("trigger.external1", &trigger_external1, &b_raw__sweeper_trigger_external1);
   fChain->SetBranchAddress("trigger.external2", &trigger_external2, &b_raw__sweeper_trigger_external2);
   fChain->SetBranchAddress("trigger.secondary", &trigger_secondary, &b_raw__sweeper_trigger_secondary);
   fChain->SetBranchAddress("trigger.pattern", &trigger_pattern, &b_raw__sweeper_trigger_pattern);
   fChain->SetBranchAddress("trigger.timestamp[4]", trigger_timestamp, &b_raw__sweeper_trigger_timestamp);
   fChain->SetBranchAddress("crdc1.anode", &crdc1_anode, &b_raw__sweeper_crdc1_anode);
   fChain->SetBranchAddress("crdc1.tac", &crdc1_tac, &b_raw__sweeper_crdc1_tac);
   fChain->SetBranchAddress("crdc1.sample_width", &crdc1_sample_width, &b_raw__sweeper_crdc1_sample_width);
   fChain->SetBranchAddress("crdc1.pad.nsamples[128]", crdc1_pad_nsamples, &b_raw__sweeper_crdc1_pad_nsamples);
   fChain->SetBranchAddress("crdc1.pad.raw[128]", crdc1_pad_raw, &b_raw__sweeper_crdc1_pad_raw);
   fChain->SetBranchAddress("crdc1.pad.sample[128][32]", crdc1_pad_sample, &b_raw__sweeper_crdc1_pad_sample);
   fChain->SetBranchAddress("crdc2.anode", &crdc2_anode, &b_raw__sweeper_crdc2_anode);
   fChain->SetBranchAddress("crdc2.tac", &crdc2_tac, &b_raw__sweeper_crdc2_tac);
   fChain->SetBranchAddress("crdc2.sample_width", &crdc2_sample_width, &b_raw__sweeper_crdc2_sample_width);
   fChain->SetBranchAddress("crdc2.pad.nsamples[128]", crdc2_pad_nsamples, &b_raw__sweeper_crdc2_pad_nsamples);
   fChain->SetBranchAddress("crdc2.pad.raw[128]", crdc2_pad_raw, &b_raw__sweeper_crdc2_pad_raw);
   fChain->SetBranchAddress("crdc2.pad.sample[128][32]", crdc2_pad_sample, &b_raw__sweeper_crdc2_pad_sample);
   fChain->SetBranchAddress("tcrdc1.anode", &tcrdc1_anode, &b_raw__sweeper_tcrdc1_anode);
   fChain->SetBranchAddress("tcrdc1.tac", &tcrdc1_tac, &b_raw__sweeper_tcrdc1_tac);
   fChain->SetBranchAddress("tcrdc1.sample_width", &tcrdc1_sample_width, &b_raw__sweeper_tcrdc1_sample_width);
   fChain->SetBranchAddress("tcrdc1.pad.nsamples[64]", tcrdc1_pad_nsamples, &b_raw__sweeper_tcrdc1_pad_nsamples);
   fChain->SetBranchAddress("tcrdc1.pad.raw[64]", tcrdc1_pad_raw, &b_raw__sweeper_tcrdc1_pad_raw);
   fChain->SetBranchAddress("tcrdc1.pad.sample[64][32]", tcrdc1_pad_sample, &b_raw__sweeper_tcrdc1_pad_sample);
   fChain->SetBranchAddress("tcrdc2.anode", &tcrdc2_anode, &b_raw__sweeper_tcrdc2_anode);
   fChain->SetBranchAddress("tcrdc2.tac", &tcrdc2_tac, &b_raw__sweeper_tcrdc2_tac);
   fChain->SetBranchAddress("tcrdc2.sample_width", &tcrdc2_sample_width, &b_raw__sweeper_tcrdc2_sample_width);
   fChain->SetBranchAddress("tcrdc2.pad.nsamples[64]", tcrdc2_pad_nsamples, &b_raw__sweeper_tcrdc2_pad_nsamples);
   fChain->SetBranchAddress("tcrdc2.pad.raw[64]", tcrdc2_pad_raw, &b_raw__sweeper_tcrdc2_pad_raw);
   fChain->SetBranchAddress("tcrdc2.pad.sample[64][32]", tcrdc2_pad_sample, &b_raw__sweeper_tcrdc2_pad_sample);
   fChain->SetBranchAddress("ic.raw[16]", ic_raw, &b_raw__sweeper_ic_raw);
   fChain->SetBranchAddress("thin.qraw[4]", thin_qraw, &b_raw__sweeper_thin_qraw);
   fChain->SetBranchAddress("thin.traw[4]", thin_traw, &b_raw__sweeper_thin_traw);
   fChain->SetBranchAddress("st.raw[32]", st_raw, &b_raw__sweeper_st_raw);
   fChain->SetBranchAddress("hodo.raw[25]", hodo_raw, &b_raw__sweeper_hodo_raw);
   fChain->SetBranchAddress("pot.traw", &pot_traw, &b_raw__sweeper_pot_traw);
   fChain->SetBranchAddress("pot.qraw", &pot_qraw, &b_raw__sweeper_pot_qraw);
   fChain->SetBranchAddress("a1900.traw", &a1900_traw, &b_raw__sweeper_a1900_traw);
   fChain->SetBranchAddress("rf.traw", &rf_traw, &b_raw__sweeper_rf_traw);
   fChain->SetBranchAddress("diamond.traw[4]", diamond_traw, &b_raw__sweeper_diamond_traw);
   fChain->SetBranchAddress("diamond.qraw[4]", diamond_qraw, &b_raw__sweeper_diamond_qraw);
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
//    fChain->SetBranchAddress("v", &v, &b_cal__mona_v);
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
}

void AnalyzedData::InitAnalyzedTree(){
  at = new TTree("at","Analyzed tree");

  /* Analyzed data structures */
  at->Branch("beam",&beam,"beta/D:gamma:v");
  at->Branch("si0",&si0,"x/D:y:de");
  at->Branch("si1",&si1,"x/D:y:de");
  at->Branch("si2",&si2,"x/D:y:de");
  at->Branch("si3",&si3,"x/D:y:de");
  at->Branch("crdc1",&crdc1,"x/D:y:tx:ty:path");
  at->Branch("crdc2",&crdc2,"x/D:y:tx:ty:path");
  at->Branch("thin",&thin,"x/D:y");
  at->Branch("mult",&mult);
  at->Branch("n0",&n0,"x/D:y:z:t:dist:cosTheta:v:beta:gamma:E:P:light");
  at->Branch("frag",&frag,"dist/D:beta0/D:gamma0:v0:ke0:Bp:beta:gamma:v:ke:E:P");
//  at->Branch("tof",&tof,"nfired/s:un/D:pt/D:frag/D:q[4]/D:qx[4]/D:qxy[4]/D");
  at->Branch("target",&target);
  at->Branch("edecay",&edecay);

  /* tof branch*/
  at->Branch("tof.nfired", &tof.nfired,"tof.nfired/s");
  at->Branch("tof.un", &tof.un, "tof.un/D");
  at->Branch("tof.q", tof.q, "tof.q[4]/D");
  at->Branch("tof.qx", tof.qx, "qx[4]/D");
  at->Branch("tof.qxy", tof.qxy, "qxy[4]/D");
  at->Branch("tof.pt", &tof.pt, "tof.pt/D");
  at->Branch("tof.frag", &tof.frag, "tof.frag/D");
  

cout << "Analysis tree initialized." << endl;

}

Bool_t AnalyzedData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef AnalyzedData_cxx

inline Double_t FirstPol(double,double,double);
inline Double_t ThirdPol(double,double,double,double,double);
inline Double_t Distance(double);

