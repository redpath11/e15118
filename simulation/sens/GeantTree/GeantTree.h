//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 24 12:22:14 2017 by ROOT version 5.34/32
// from TTree t/Simulation Output
// found on file: O26_O24+2n-geant_3body.root
//////////////////////////////////////////////////////////

#ifndef GeantTree_h
#define GeantTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class GeantTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TH1D* tof;
   TH1D* fvel;
   TH1D* ke0;
   TH1D* nvel;
   TH1D* vrel;

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
   Double_t        b2p0R_pz;
   Double_t        b2p0R_exen;
   Double_t        b2p0R_exen2;
   Double_t        b2p0R_ph;
   Double_t        b2p0R_ph2;
   Double_t        b2p0R_th;
   Double_t        b2p0R_th2;
   Double_t        b7p0x;
   Double_t        b7p0tx;
   Double_t        b7p0y;
   Double_t        b7p0ty;
   Double_t        b7p0t;
   Double_t        b7p0Ekin;
   Double_t        b7p0path;
   Double_t        b9p0x;
   Double_t        b9p0tx;
   Double_t        b9p0y;
   Double_t        b9p0ty;
   Double_t        b9p0Ekin;
   Double_t        b9p0path;
   Double_t        b13p1t;
   Double_t        b13p1x;
   Double_t        b13p1y;
   Double_t        b13p1z;
   Double_t        b13p1Ekin;
   Double_t        b13p2t;
   Double_t        b13p2x;
   Double_t        b13p2y;
   Double_t        b13p2z;
   Double_t        b13p2Ekin;
   Int_t           b13pn1gmultiplicity;
   Int_t           b13pn1gZ1Mult;
   Int_t           b13pn1gZ2Mult;
   Int_t           b13pn1gZGt2Mult;
   Int_t           b13pn1gGammaMult;
   Double_t        b13pn1g1Edep;
   Double_t        b13pn1g1light;
   Double_t        b13pn1g1t;
   Double_t        b13pn1g1x;
   Double_t        b13pn1g1y;
   Double_t        b13pn1g1z;
   Double_t        b13pn1g2Edep;
   Double_t        b13pn1g2light;
   Double_t        b13pn1g2t;
   Double_t        b13pn1g2x;
   Double_t        b13pn1g2y;
   Double_t        b13pn1g2z;
   Double_t        b13pn1g3Edep;
   Double_t        b13pn1g3light;
   Double_t        b13pn1g3t;
   Double_t        b13pn1g3x;
   Double_t        b13pn1g3y;
   Double_t        b13pn1g3z;
   Double_t        b13pn1g4Edep;
   Double_t        b13pn1g4light;
   Double_t        b13pn1g4t;
   Double_t        b13pn1g4x;
   Double_t        b13pn1g4y;
   Double_t        b13pn1g4z;
   Double_t        b13pn1g5Edep;
   Double_t        b13pn1g5light;
   Double_t        b13pn1g5t;
   Double_t        b13pn1g5x;
   Double_t        b13pn1g5y;
   Double_t        b13pn1g5z;
   Double_t        b13pn1g6Edep;
   Double_t        b13pn1g6light;
   Double_t        b13pn1g6t;
   Double_t        b13pn1g6x;
   Double_t        b13pn1g6y;
   Double_t        b13pn1g6z;
   Double_t        b13pn1g7Edep;
   Double_t        b13pn1g7light;
   Double_t        b13pn1g7t;
   Double_t        b13pn1g7x;
   Double_t        b13pn1g7y;
   Double_t        b13pn1g7z;
   Double_t        b13pn1g8Edep;
   Double_t        b13pn1g8light;
   Double_t        b13pn1g8t;
   Double_t        b13pn1g8x;
   Double_t        b13pn1g8y;
   Double_t        b13pn1g8z;
   Double_t        b13pn1g9Edep;
   Double_t        b13pn1g9light;
   Double_t        b13pn1g9t;
   Double_t        b13pn1g9x;
   Double_t        b13pn1g9y;
   Double_t        b13pn1g9z;
   Double_t        b13pn1g10Edep;
   Double_t        b13pn1g10light;
   Double_t        b13pn1g10t;
   Double_t        b13pn1g10x;
   Double_t        b13pn1g10y;
   Double_t        b13pn1g10z;
   Int_t           b13pn2gmultiplicity;
   Int_t           b13pn2gZ1Mult;
   Int_t           b13pn2gZ2Mult;
   Int_t           b13pn2gZGt2Mult;
   Int_t           b13pn2gGammaMult;
   Double_t        b13pn2g1Edep;
   Double_t        b13pn2g1light;
   Double_t        b13pn2g1t;
   Double_t        b13pn2g1x;
   Double_t        b13pn2g1y;
   Double_t        b13pn2g1z;
   Double_t        b13pn2g2Edep;
   Double_t        b13pn2g2light;
   Double_t        b13pn2g2t;
   Double_t        b13pn2g2x;
   Double_t        b13pn2g2y;
   Double_t        b13pn2g2z;
   Double_t        b13pn2g3Edep;
   Double_t        b13pn2g3light;
   Double_t        b13pn2g3t;
   Double_t        b13pn2g3x;
   Double_t        b13pn2g3y;
   Double_t        b13pn2g3z;
   Double_t        b13pn2g4Edep;
   Double_t        b13pn2g4light;
   Double_t        b13pn2g4t;
   Double_t        b13pn2g4x;
   Double_t        b13pn2g4y;
   Double_t        b13pn2g4z;
   Double_t        b13pn2g5Edep;
   Double_t        b13pn2g5light;
   Double_t        b13pn2g5t;
   Double_t        b13pn2g5x;
   Double_t        b13pn2g5y;
   Double_t        b13pn2g5z;
   Double_t        b13pn2g6Edep;
   Double_t        b13pn2g6light;
   Double_t        b13pn2g6t;
   Double_t        b13pn2g6x;
   Double_t        b13pn2g6y;
   Double_t        b13pn2g6z;
   Double_t        b13pn2g7Edep;
   Double_t        b13pn2g7light;
   Double_t        b13pn2g7t;
   Double_t        b13pn2g7x;
   Double_t        b13pn2g7y;
   Double_t        b13pn2g7z;
   Double_t        b13pn2g8Edep;
   Double_t        b13pn2g8light;
   Double_t        b13pn2g8t;
   Double_t        b13pn2g8x;
   Double_t        b13pn2g8y;
   Double_t        b13pn2g8z;
   Double_t        b13pn2g9Edep;
   Double_t        b13pn2g9light;
   Double_t        b13pn2g9t;
   Double_t        b13pn2g9x;
   Double_t        b13pn2g9y;
   Double_t        b13pn2g9z;
   Double_t        b13pn2g10Edep;
   Double_t        b13pn2g10light;
   Double_t        b13pn2g10t;
   Double_t        b13pn2g10x;
   Double_t        b13pn2g10y;
   Double_t        b13pn2g10z;
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
   Double_t        b13pg11Edep;
   Double_t        b13pg11light;
   Double_t        b13pg11t;
   Double_t        b13pg11x;
   Double_t        b13pg11y;
   Double_t        b13pg11z;
   Double_t        b13pg12Edep;
   Double_t        b13pg12light;
   Double_t        b13pg12t;
   Double_t        b13pg12x;
   Double_t        b13pg12y;
   Double_t        b13pg12z;
   Double_t        b13pg13Edep;
   Double_t        b13pg13light;
   Double_t        b13pg13t;
   Double_t        b13pg13x;
   Double_t        b13pg13y;
   Double_t        b13pg13z;
   Double_t        b13pg14Edep;
   Double_t        b13pg14light;
   Double_t        b13pg14t;
   Double_t        b13pg14x;
   Double_t        b13pg14y;
   Double_t        b13pg14z;
   Double_t        b13pg15Edep;
   Double_t        b13pg15light;
   Double_t        b13pg15t;
   Double_t        b13pg15x;
   Double_t        b13pg15y;
   Double_t        b13pg15z;
   Double_t        b13pg16Edep;
   Double_t        b13pg16light;
   Double_t        b13pg16t;
   Double_t        b13pg16x;
   Double_t        b13pg16y;
   Double_t        b13pg16z;
   Double_t        b13pg17Edep;
   Double_t        b13pg17light;
   Double_t        b13pg17t;
   Double_t        b13pg17x;
   Double_t        b13pg17y;
   Double_t        b13pg17z;
   Double_t        b13pg18Edep;
   Double_t        b13pg18light;
   Double_t        b13pg18t;
   Double_t        b13pg18x;
   Double_t        b13pg18y;
   Double_t        b13pg18z;
   Double_t        b13pg19Edep;
   Double_t        b13pg19light;
   Double_t        b13pg19t;
   Double_t        b13pg19x;
   Double_t        b13pg19y;
   Double_t        b13pg19z;
   Double_t        b13pg20Edep;
   Double_t        b13pg20light;
   Double_t        b13pg20t;
   Double_t        b13pg20x;
   Double_t        b13pg20y;
   Double_t        b13pg20z;

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
   TBranch        *b_b2p0R_pz;   //!
   TBranch        *b_b2p0R_exen;   //!
   TBranch        *b_b2p0R_exen2;   //!
   TBranch        *b_b2p0R_ph;   //!
   TBranch        *b_b2p0R_ph2;   //!
   TBranch        *b_b2p0R_th;   //!
   TBranch        *b_b2p0R_th2;   //!
   TBranch        *b_b7p0x;   //!
   TBranch        *b_b7p0tx;   //!
   TBranch        *b_b7p0y;   //!
   TBranch        *b_b7p0ty;   //!
   TBranch        *b_b7p0t;   //!
   TBranch        *b_b7p0Ekin;   //!
   TBranch        *b_b7p0path;   //!
   TBranch        *b_b9p0x;   //!
   TBranch        *b_b9p0tx;   //!
   TBranch        *b_b9p0y;   //!
   TBranch        *b_b9p0ty;   //!
   TBranch        *b_b9p0Ekin;   //!
   TBranch        *b_b9p0path;   //!
   TBranch        *b_b13p1t;   //!
   TBranch        *b_b13p1x;   //!
   TBranch        *b_b13p1y;   //!
   TBranch        *b_b13p1z;   //!
   TBranch        *b_b13p1Ekin;   //!
   TBranch        *b_b13p2t;   //!
   TBranch        *b_b13p2x;   //!
   TBranch        *b_b13p2y;   //!
   TBranch        *b_b13p2z;   //!
   TBranch        *b_b13p2Ekin;   //!
   TBranch        *b_b13pn1gmultiplicity;   //!
   TBranch        *b_b13pn1gZ1Mult;   //!
   TBranch        *b_b13pn1gZ2Mult;   //!
   TBranch        *b_b13pn1gZGt2Mult;   //!
   TBranch        *b_b13pn1gGammaMult;   //!
   TBranch        *b_b13pn1g1Edep;   //!
   TBranch        *b_b13pn1g1light;   //!
   TBranch        *b_b13pn1g1t;   //!
   TBranch        *b_b13pn1g1x;   //!
   TBranch        *b_b13pn1g1y;   //!
   TBranch        *b_b13pn1g1z;   //!
   TBranch        *b_b13pn1g2Edep;   //!
   TBranch        *b_b13pn1g2light;   //!
   TBranch        *b_b13pn1g2t;   //!
   TBranch        *b_b13pn1g2x;   //!
   TBranch        *b_b13pn1g2y;   //!
   TBranch        *b_b13pn1g2z;   //!
   TBranch        *b_b13pn1g3Edep;   //!
   TBranch        *b_b13pn1g3light;   //!
   TBranch        *b_b13pn1g3t;   //!
   TBranch        *b_b13pn1g3x;   //!
   TBranch        *b_b13pn1g3y;   //!
   TBranch        *b_b13pn1g3z;   //!
   TBranch        *b_b13pn1g4Edep;   //!
   TBranch        *b_b13pn1g4light;   //!
   TBranch        *b_b13pn1g4t;   //!
   TBranch        *b_b13pn1g4x;   //!
   TBranch        *b_b13pn1g4y;   //!
   TBranch        *b_b13pn1g4z;   //!
   TBranch        *b_b13pn1g5Edep;   //!
   TBranch        *b_b13pn1g5light;   //!
   TBranch        *b_b13pn1g5t;   //!
   TBranch        *b_b13pn1g5x;   //!
   TBranch        *b_b13pn1g5y;   //!
   TBranch        *b_b13pn1g5z;   //!
   TBranch        *b_b13pn1g6Edep;   //!
   TBranch        *b_b13pn1g6light;   //!
   TBranch        *b_b13pn1g6t;   //!
   TBranch        *b_b13pn1g6x;   //!
   TBranch        *b_b13pn1g6y;   //!
   TBranch        *b_b13pn1g6z;   //!
   TBranch        *b_b13pn1g7Edep;   //!
   TBranch        *b_b13pn1g7light;   //!
   TBranch        *b_b13pn1g7t;   //!
   TBranch        *b_b13pn1g7x;   //!
   TBranch        *b_b13pn1g7y;   //!
   TBranch        *b_b13pn1g7z;   //!
   TBranch        *b_b13pn1g8Edep;   //!
   TBranch        *b_b13pn1g8light;   //!
   TBranch        *b_b13pn1g8t;   //!
   TBranch        *b_b13pn1g8x;   //!
   TBranch        *b_b13pn1g8y;   //!
   TBranch        *b_b13pn1g8z;   //!
   TBranch        *b_b13pn1g9Edep;   //!
   TBranch        *b_b13pn1g9light;   //!
   TBranch        *b_b13pn1g9t;   //!
   TBranch        *b_b13pn1g9x;   //!
   TBranch        *b_b13pn1g9y;   //!
   TBranch        *b_b13pn1g9z;   //!
   TBranch        *b_b13pn1g10Edep;   //!
   TBranch        *b_b13pn1g10light;   //!
   TBranch        *b_b13pn1g10t;   //!
   TBranch        *b_b13pn1g10x;   //!
   TBranch        *b_b13pn1g10y;   //!
   TBranch        *b_b13pn1g10z;   //!
   TBranch        *b_b13pn2gmultiplicity;   //!
   TBranch        *b_b13pn1gZ1Mult;   //!
   TBranch        *b_b13pn1gZ2Mult;   //!
   TBranch        *b_b13pn1gZGt2Mult;   //!
   TBranch        *b_b13pn1gGammaMult;   //!
   TBranch        *b_b13pn2g1Edep;   //!
   TBranch        *b_b13pn2g1light;   //!
   TBranch        *b_b13pn2g1t;   //!
   TBranch        *b_b13pn2g1x;   //!
   TBranch        *b_b13pn2g1y;   //!
   TBranch        *b_b13pn2g1z;   //!
   TBranch        *b_b13pn2g2Edep;   //!
   TBranch        *b_b13pn2g2light;   //!
   TBranch        *b_b13pn2g2t;   //!
   TBranch        *b_b13pn2g2x;   //!
   TBranch        *b_b13pn2g2y;   //!
   TBranch        *b_b13pn2g2z;   //!
   TBranch        *b_b13pn2g3Edep;   //!
   TBranch        *b_b13pn2g3light;   //!
   TBranch        *b_b13pn2g3t;   //!
   TBranch        *b_b13pn2g3x;   //!
   TBranch        *b_b13pn2g3y;   //!
   TBranch        *b_b13pn2g3z;   //!
   TBranch        *b_b13pn2g4Edep;   //!
   TBranch        *b_b13pn2g4light;   //!
   TBranch        *b_b13pn2g4t;   //!
   TBranch        *b_b13pn2g4x;   //!
   TBranch        *b_b13pn2g4y;   //!
   TBranch        *b_b13pn2g4z;   //!
   TBranch        *b_b13pn2g5Edep;   //!
   TBranch        *b_b13pn2g5light;   //!
   TBranch        *b_b13pn2g5t;   //!
   TBranch        *b_b13pn2g5x;   //!
   TBranch        *b_b13pn2g5y;   //!
   TBranch        *b_b13pn2g5z;   //!
   TBranch        *b_b13pn2g6Edep;   //!
   TBranch        *b_b13pn2g6light;   //!
   TBranch        *b_b13pn2g6t;   //!
   TBranch        *b_b13pn2g6x;   //!
   TBranch        *b_b13pn2g6y;   //!
   TBranch        *b_b13pn2g6z;   //!
   TBranch        *b_b13pn2g7Edep;   //!
   TBranch        *b_b13pn2g7light;   //!
   TBranch        *b_b13pn2g7t;   //!
   TBranch        *b_b13pn2g7x;   //!
   TBranch        *b_b13pn2g7y;   //!
   TBranch        *b_b13pn2g7z;   //!
   TBranch        *b_b13pn2g8Edep;   //!
   TBranch        *b_b13pn2g8light;   //!
   TBranch        *b_b13pn2g8t;   //!
   TBranch        *b_b13pn2g8x;   //!
   TBranch        *b_b13pn2g8y;   //!
   TBranch        *b_b13pn2g8z;   //!
   TBranch        *b_b13pn2g9Edep;   //!
   TBranch        *b_b13pn2g9light;   //!
   TBranch        *b_b13pn2g9t;   //!
   TBranch        *b_b13pn2g9x;   //!
   TBranch        *b_b13pn2g9y;   //!
   TBranch        *b_b13pn2g9z;   //!
   TBranch        *b_b13pn2g10Edep;   //!
   TBranch        *b_b13pn2g10light;   //!
   TBranch        *b_b13pn2g10t;   //!
   TBranch        *b_b13pn2g10x;   //!
   TBranch        *b_b13pn2g10y;   //!
   TBranch        *b_b13pn2g10z;   //!
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
   TBranch        *b_b13pg11Edep;   //!
   TBranch        *b_b13pg11light;   //!
   TBranch        *b_b13pg11t;   //!
   TBranch        *b_b13pg11x;   //!
   TBranch        *b_b13pg11y;   //!
   TBranch        *b_b13pg11z;   //!
   TBranch        *b_b13pg12Edep;   //!
   TBranch        *b_b13pg12light;   //!
   TBranch        *b_b13pg12t;   //!
   TBranch        *b_b13pg12x;   //!
   TBranch        *b_b13pg12y;   //!
   TBranch        *b_b13pg12z;   //!
   TBranch        *b_b13pg13Edep;   //!
   TBranch        *b_b13pg13light;   //!
   TBranch        *b_b13pg13t;   //!
   TBranch        *b_b13pg13x;   //!
   TBranch        *b_b13pg13y;   //!
   TBranch        *b_b13pg13z;   //!
   TBranch        *b_b13pg14Edep;   //!
   TBranch        *b_b13pg14light;   //!
   TBranch        *b_b13pg14t;   //!
   TBranch        *b_b13pg14x;   //!
   TBranch        *b_b13pg14y;   //!
   TBranch        *b_b13pg14z;   //!
   TBranch        *b_b13pg15Edep;   //!
   TBranch        *b_b13pg15light;   //!
   TBranch        *b_b13pg15t;   //!
   TBranch        *b_b13pg15x;   //!
   TBranch        *b_b13pg15y;   //!
   TBranch        *b_b13pg15z;   //!
   TBranch        *b_b13pg16Edep;   //!
   TBranch        *b_b13pg16light;   //!
   TBranch        *b_b13pg16t;   //!
   TBranch        *b_b13pg16x;   //!
   TBranch        *b_b13pg16y;   //!
   TBranch        *b_b13pg16z;   //!
   TBranch        *b_b13pg17Edep;   //!
   TBranch        *b_b13pg17light;   //!
   TBranch        *b_b13pg17t;   //!
   TBranch        *b_b13pg17x;   //!
   TBranch        *b_b13pg17y;   //!
   TBranch        *b_b13pg17z;   //!
   TBranch        *b_b13pg18Edep;   //!
   TBranch        *b_b13pg18light;   //!
   TBranch        *b_b13pg18t;   //!
   TBranch        *b_b13pg18x;   //!
   TBranch        *b_b13pg18y;   //!
   TBranch        *b_b13pg18z;   //!
   TBranch        *b_b13pg19Edep;   //!
   TBranch        *b_b13pg19light;   //!
   TBranch        *b_b13pg19t;   //!
   TBranch        *b_b13pg19x;   //!
   TBranch        *b_b13pg19y;   //!
   TBranch        *b_b13pg19z;   //!
   TBranch        *b_b13pg20Edep;   //!
   TBranch        *b_b13pg20light;   //!
   TBranch        *b_b13pg20t;   //!
   TBranch        *b_b13pg20x;   //!
   TBranch        *b_b13pg20y;   //!
   TBranch        *b_b13pg20z;   //!

   GeantTree(TTree *tree=0);
   virtual ~GeantTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef GeantTree_cxx
GeantTree::GeantTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("O26_O24+2n-geant_3body.root");
      if (!f || !f->IsOpen()) {
//         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n-geant_3body.root");
         f = new TFile("/mnt/simulations/MoNAsims/O26_analysis/O26_O24+2n-geant_3bodyNoMres.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

GeantTree::~GeantTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GeantTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GeantTree::LoadTree(Long64_t entry)
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

void GeantTree::Init(TTree *tree)
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
   fChain->SetBranchAddress("b2p0R_pz", &b2p0R_pz, &b_b2p0R_pz);
   fChain->SetBranchAddress("b2p0R_exen", &b2p0R_exen, &b_b2p0R_exen);
   fChain->SetBranchAddress("b2p0R_exen2", &b2p0R_exen2, &b_b2p0R_exen2);
   fChain->SetBranchAddress("b2p0R_ph", &b2p0R_ph, &b_b2p0R_ph);
   fChain->SetBranchAddress("b2p0R_ph2", &b2p0R_ph2, &b_b2p0R_ph2);
   fChain->SetBranchAddress("b2p0R_th", &b2p0R_th, &b_b2p0R_th);
   fChain->SetBranchAddress("b2p0R_th2", &b2p0R_th2, &b_b2p0R_th2);
   fChain->SetBranchAddress("b7p0x", &b7p0x, &b_b7p0x);
   fChain->SetBranchAddress("b7p0tx", &b7p0tx, &b_b7p0tx);
   fChain->SetBranchAddress("b7p0y", &b7p0y, &b_b7p0y);
   fChain->SetBranchAddress("b7p0ty", &b7p0ty, &b_b7p0ty);
   fChain->SetBranchAddress("b7p0t", &b7p0t, &b_b7p0t);
   fChain->SetBranchAddress("b7p0Ekin", &b7p0Ekin, &b_b7p0Ekin);
   fChain->SetBranchAddress("b7p0path", &b7p0path, &b_b7p0path);
   fChain->SetBranchAddress("b9p0x", &b9p0x, &b_b9p0x);
   fChain->SetBranchAddress("b9p0tx", &b9p0tx, &b_b9p0tx);
   fChain->SetBranchAddress("b9p0y", &b9p0y, &b_b9p0y);
   fChain->SetBranchAddress("b9p0ty", &b9p0ty, &b_b9p0ty);
   fChain->SetBranchAddress("b9p0Ekin", &b9p0Ekin, &b_b9p0Ekin);
   fChain->SetBranchAddress("b9p0path", &b9p0path, &b_b9p0path);
   fChain->SetBranchAddress("b13p1t", &b13p1t, &b_b13p1t);
   fChain->SetBranchAddress("b13p1x", &b13p1x, &b_b13p1x);
   fChain->SetBranchAddress("b13p1y", &b13p1y, &b_b13p1y);
   fChain->SetBranchAddress("b13p1z", &b13p1z, &b_b13p1z);
   fChain->SetBranchAddress("b13p1Ekin", &b13p1Ekin, &b_b13p1Ekin);
   fChain->SetBranchAddress("b13p2t", &b13p2t, &b_b13p2t);
   fChain->SetBranchAddress("b13p2x", &b13p2x, &b_b13p2x);
   fChain->SetBranchAddress("b13p2y", &b13p2y, &b_b13p2y);
   fChain->SetBranchAddress("b13p2z", &b13p2z, &b_b13p2z);
   fChain->SetBranchAddress("b13p2Ekin", &b13p2Ekin, &b_b13p2Ekin);
   fChain->SetBranchAddress("b13pn1gmultiplicity", &b13pn1gmultiplicity, &b_b13pn1gmultiplicity);
   fChain->SetBranchAddress("b13pn1gZ1Mult", &b13pn1gZ1Mult, &b_b13pn1gZ1Mult);
   fChain->SetBranchAddress("b13pn1gZ2Mult", &b13pn1gZ2Mult, &b_b13pn1gZ2Mult);
   fChain->SetBranchAddress("b13pn1gZGt2Mult", &b13pn1gZGt2Mult, &b_b13pn1gZGt2Mult);
   fChain->SetBranchAddress("b13pn1gGammaMult", &b13pn1gGammaMult, &b_b13pn1gGammaMult);
   fChain->SetBranchAddress("b13pn1g1Edep", &b13pn1g1Edep, &b_b13pn1g1Edep);
   fChain->SetBranchAddress("b13pn1g1light", &b13pn1g1light, &b_b13pn1g1light);
   fChain->SetBranchAddress("b13pn1g1t", &b13pn1g1t, &b_b13pn1g1t);
   fChain->SetBranchAddress("b13pn1g1x", &b13pn1g1x, &b_b13pn1g1x);
   fChain->SetBranchAddress("b13pn1g1y", &b13pn1g1y, &b_b13pn1g1y);
   fChain->SetBranchAddress("b13pn1g1z", &b13pn1g1z, &b_b13pn1g1z);
   fChain->SetBranchAddress("b13pn1g2Edep", &b13pn1g2Edep, &b_b13pn1g2Edep);
   fChain->SetBranchAddress("b13pn1g2light", &b13pn1g2light, &b_b13pn1g2light);
   fChain->SetBranchAddress("b13pn1g2t", &b13pn1g2t, &b_b13pn1g2t);
   fChain->SetBranchAddress("b13pn1g2x", &b13pn1g2x, &b_b13pn1g2x);
   fChain->SetBranchAddress("b13pn1g2y", &b13pn1g2y, &b_b13pn1g2y);
   fChain->SetBranchAddress("b13pn1g2z", &b13pn1g2z, &b_b13pn1g2z);
   fChain->SetBranchAddress("b13pn1g3Edep", &b13pn1g3Edep, &b_b13pn1g3Edep);
   fChain->SetBranchAddress("b13pn1g3light", &b13pn1g3light, &b_b13pn1g3light);
   fChain->SetBranchAddress("b13pn1g3t", &b13pn1g3t, &b_b13pn1g3t);
   fChain->SetBranchAddress("b13pn1g3x", &b13pn1g3x, &b_b13pn1g3x);
   fChain->SetBranchAddress("b13pn1g3y", &b13pn1g3y, &b_b13pn1g3y);
   fChain->SetBranchAddress("b13pn1g3z", &b13pn1g3z, &b_b13pn1g3z);
   fChain->SetBranchAddress("b13pn1g4Edep", &b13pn1g4Edep, &b_b13pn1g4Edep);
   fChain->SetBranchAddress("b13pn1g4light", &b13pn1g4light, &b_b13pn1g4light);
   fChain->SetBranchAddress("b13pn1g4t", &b13pn1g4t, &b_b13pn1g4t);
   fChain->SetBranchAddress("b13pn1g4x", &b13pn1g4x, &b_b13pn1g4x);
   fChain->SetBranchAddress("b13pn1g4y", &b13pn1g4y, &b_b13pn1g4y);
   fChain->SetBranchAddress("b13pn1g4z", &b13pn1g4z, &b_b13pn1g4z);
   fChain->SetBranchAddress("b13pn1g5Edep", &b13pn1g5Edep, &b_b13pn1g5Edep);
   fChain->SetBranchAddress("b13pn1g5light", &b13pn1g5light, &b_b13pn1g5light);
   fChain->SetBranchAddress("b13pn1g5t", &b13pn1g5t, &b_b13pn1g5t);
   fChain->SetBranchAddress("b13pn1g5x", &b13pn1g5x, &b_b13pn1g5x);
   fChain->SetBranchAddress("b13pn1g5y", &b13pn1g5y, &b_b13pn1g5y);
   fChain->SetBranchAddress("b13pn1g5z", &b13pn1g5z, &b_b13pn1g5z);
   fChain->SetBranchAddress("b13pn1g6Edep", &b13pn1g6Edep, &b_b13pn1g6Edep);
   fChain->SetBranchAddress("b13pn1g6light", &b13pn1g6light, &b_b13pn1g6light);
   fChain->SetBranchAddress("b13pn1g6t", &b13pn1g6t, &b_b13pn1g6t);
   fChain->SetBranchAddress("b13pn1g6x", &b13pn1g6x, &b_b13pn1g6x);
   fChain->SetBranchAddress("b13pn1g6y", &b13pn1g6y, &b_b13pn1g6y);
   fChain->SetBranchAddress("b13pn1g6z", &b13pn1g6z, &b_b13pn1g6z);
   fChain->SetBranchAddress("b13pn1g7Edep", &b13pn1g7Edep, &b_b13pn1g7Edep);
   fChain->SetBranchAddress("b13pn1g7light", &b13pn1g7light, &b_b13pn1g7light);
   fChain->SetBranchAddress("b13pn1g7t", &b13pn1g7t, &b_b13pn1g7t);
   fChain->SetBranchAddress("b13pn1g7x", &b13pn1g7x, &b_b13pn1g7x);
   fChain->SetBranchAddress("b13pn1g7y", &b13pn1g7y, &b_b13pn1g7y);
   fChain->SetBranchAddress("b13pn1g7z", &b13pn1g7z, &b_b13pn1g7z);
   fChain->SetBranchAddress("b13pn1g8Edep", &b13pn1g8Edep, &b_b13pn1g8Edep);
   fChain->SetBranchAddress("b13pn1g8light", &b13pn1g8light, &b_b13pn1g8light);
   fChain->SetBranchAddress("b13pn1g8t", &b13pn1g8t, &b_b13pn1g8t);
   fChain->SetBranchAddress("b13pn1g8x", &b13pn1g8x, &b_b13pn1g8x);
   fChain->SetBranchAddress("b13pn1g8y", &b13pn1g8y, &b_b13pn1g8y);
   fChain->SetBranchAddress("b13pn1g8z", &b13pn1g8z, &b_b13pn1g8z);
   fChain->SetBranchAddress("b13pn1g9Edep", &b13pn1g9Edep, &b_b13pn1g9Edep);
   fChain->SetBranchAddress("b13pn1g9light", &b13pn1g9light, &b_b13pn1g9light);
   fChain->SetBranchAddress("b13pn1g9t", &b13pn1g9t, &b_b13pn1g9t);
   fChain->SetBranchAddress("b13pn1g9x", &b13pn1g9x, &b_b13pn1g9x);
   fChain->SetBranchAddress("b13pn1g9y", &b13pn1g9y, &b_b13pn1g9y);
   fChain->SetBranchAddress("b13pn1g9z", &b13pn1g9z, &b_b13pn1g9z);
   fChain->SetBranchAddress("b13pn1g10Edep", &b13pn1g10Edep, &b_b13pn1g10Edep);
   fChain->SetBranchAddress("b13pn1g10light", &b13pn1g10light, &b_b13pn1g10light);
   fChain->SetBranchAddress("b13pn1g10t", &b13pn1g10t, &b_b13pn1g10t);
   fChain->SetBranchAddress("b13pn1g10x", &b13pn1g10x, &b_b13pn1g10x);
   fChain->SetBranchAddress("b13pn1g10y", &b13pn1g10y, &b_b13pn1g10y);
   fChain->SetBranchAddress("b13pn1g10z", &b13pn1g10z, &b_b13pn1g10z);
   fChain->SetBranchAddress("b13pn2gmultiplicity", &b13pn2gmultiplicity, &b_b13pn2gmultiplicity);
   fChain->SetBranchAddress("b13pn2gZ1Mult", &b13pn2gZ1Mult, &b_b13pn1gZ1Mult);
   fChain->SetBranchAddress("b13pn2gZ2Mult", &b13pn2gZ2Mult, &b_b13pn1gZ2Mult);
   fChain->SetBranchAddress("b13pn2gZGt2Mult", &b13pn2gZGt2Mult, &b_b13pn1gZGt2Mult);
   fChain->SetBranchAddress("b13pn2gGammaMult", &b13pn2gGammaMult, &b_b13pn1gGammaMult);
   fChain->SetBranchAddress("b13pn2g1Edep", &b13pn2g1Edep, &b_b13pn2g1Edep);
   fChain->SetBranchAddress("b13pn2g1light", &b13pn2g1light, &b_b13pn2g1light);
   fChain->SetBranchAddress("b13pn2g1t", &b13pn2g1t, &b_b13pn2g1t);
   fChain->SetBranchAddress("b13pn2g1x", &b13pn2g1x, &b_b13pn2g1x);
   fChain->SetBranchAddress("b13pn2g1y", &b13pn2g1y, &b_b13pn2g1y);
   fChain->SetBranchAddress("b13pn2g1z", &b13pn2g1z, &b_b13pn2g1z);
   fChain->SetBranchAddress("b13pn2g2Edep", &b13pn2g2Edep, &b_b13pn2g2Edep);
   fChain->SetBranchAddress("b13pn2g2light", &b13pn2g2light, &b_b13pn2g2light);
   fChain->SetBranchAddress("b13pn2g2t", &b13pn2g2t, &b_b13pn2g2t);
   fChain->SetBranchAddress("b13pn2g2x", &b13pn2g2x, &b_b13pn2g2x);
   fChain->SetBranchAddress("b13pn2g2y", &b13pn2g2y, &b_b13pn2g2y);
   fChain->SetBranchAddress("b13pn2g2z", &b13pn2g2z, &b_b13pn2g2z);
   fChain->SetBranchAddress("b13pn2g3Edep", &b13pn2g3Edep, &b_b13pn2g3Edep);
   fChain->SetBranchAddress("b13pn2g3light", &b13pn2g3light, &b_b13pn2g3light);
   fChain->SetBranchAddress("b13pn2g3t", &b13pn2g3t, &b_b13pn2g3t);
   fChain->SetBranchAddress("b13pn2g3x", &b13pn2g3x, &b_b13pn2g3x);
   fChain->SetBranchAddress("b13pn2g3y", &b13pn2g3y, &b_b13pn2g3y);
   fChain->SetBranchAddress("b13pn2g3z", &b13pn2g3z, &b_b13pn2g3z);
   fChain->SetBranchAddress("b13pn2g4Edep", &b13pn2g4Edep, &b_b13pn2g4Edep);
   fChain->SetBranchAddress("b13pn2g4light", &b13pn2g4light, &b_b13pn2g4light);
   fChain->SetBranchAddress("b13pn2g4t", &b13pn2g4t, &b_b13pn2g4t);
   fChain->SetBranchAddress("b13pn2g4x", &b13pn2g4x, &b_b13pn2g4x);
   fChain->SetBranchAddress("b13pn2g4y", &b13pn2g4y, &b_b13pn2g4y);
   fChain->SetBranchAddress("b13pn2g4z", &b13pn2g4z, &b_b13pn2g4z);
   fChain->SetBranchAddress("b13pn2g5Edep", &b13pn2g5Edep, &b_b13pn2g5Edep);
   fChain->SetBranchAddress("b13pn2g5light", &b13pn2g5light, &b_b13pn2g5light);
   fChain->SetBranchAddress("b13pn2g5t", &b13pn2g5t, &b_b13pn2g5t);
   fChain->SetBranchAddress("b13pn2g5x", &b13pn2g5x, &b_b13pn2g5x);
   fChain->SetBranchAddress("b13pn2g5y", &b13pn2g5y, &b_b13pn2g5y);
   fChain->SetBranchAddress("b13pn2g5z", &b13pn2g5z, &b_b13pn2g5z);
   fChain->SetBranchAddress("b13pn2g6Edep", &b13pn2g6Edep, &b_b13pn2g6Edep);
   fChain->SetBranchAddress("b13pn2g6light", &b13pn2g6light, &b_b13pn2g6light);
   fChain->SetBranchAddress("b13pn2g6t", &b13pn2g6t, &b_b13pn2g6t);
   fChain->SetBranchAddress("b13pn2g6x", &b13pn2g6x, &b_b13pn2g6x);
   fChain->SetBranchAddress("b13pn2g6y", &b13pn2g6y, &b_b13pn2g6y);
   fChain->SetBranchAddress("b13pn2g6z", &b13pn2g6z, &b_b13pn2g6z);
   fChain->SetBranchAddress("b13pn2g7Edep", &b13pn2g7Edep, &b_b13pn2g7Edep);
   fChain->SetBranchAddress("b13pn2g7light", &b13pn2g7light, &b_b13pn2g7light);
   fChain->SetBranchAddress("b13pn2g7t", &b13pn2g7t, &b_b13pn2g7t);
   fChain->SetBranchAddress("b13pn2g7x", &b13pn2g7x, &b_b13pn2g7x);
   fChain->SetBranchAddress("b13pn2g7y", &b13pn2g7y, &b_b13pn2g7y);
   fChain->SetBranchAddress("b13pn2g7z", &b13pn2g7z, &b_b13pn2g7z);
   fChain->SetBranchAddress("b13pn2g8Edep", &b13pn2g8Edep, &b_b13pn2g8Edep);
   fChain->SetBranchAddress("b13pn2g8light", &b13pn2g8light, &b_b13pn2g8light);
   fChain->SetBranchAddress("b13pn2g8t", &b13pn2g8t, &b_b13pn2g8t);
   fChain->SetBranchAddress("b13pn2g8x", &b13pn2g8x, &b_b13pn2g8x);
   fChain->SetBranchAddress("b13pn2g8y", &b13pn2g8y, &b_b13pn2g8y);
   fChain->SetBranchAddress("b13pn2g8z", &b13pn2g8z, &b_b13pn2g8z);
   fChain->SetBranchAddress("b13pn2g9Edep", &b13pn2g9Edep, &b_b13pn2g9Edep);
   fChain->SetBranchAddress("b13pn2g9light", &b13pn2g9light, &b_b13pn2g9light);
   fChain->SetBranchAddress("b13pn2g9t", &b13pn2g9t, &b_b13pn2g9t);
   fChain->SetBranchAddress("b13pn2g9x", &b13pn2g9x, &b_b13pn2g9x);
   fChain->SetBranchAddress("b13pn2g9y", &b13pn2g9y, &b_b13pn2g9y);
   fChain->SetBranchAddress("b13pn2g9z", &b13pn2g9z, &b_b13pn2g9z);
   fChain->SetBranchAddress("b13pn2g10Edep", &b13pn2g10Edep, &b_b13pn2g10Edep);
   fChain->SetBranchAddress("b13pn2g10light", &b13pn2g10light, &b_b13pn2g10light);
   fChain->SetBranchAddress("b13pn2g10t", &b13pn2g10t, &b_b13pn2g10t);
   fChain->SetBranchAddress("b13pn2g10x", &b13pn2g10x, &b_b13pn2g10x);
   fChain->SetBranchAddress("b13pn2g10y", &b13pn2g10y, &b_b13pn2g10y);
   fChain->SetBranchAddress("b13pn2g10z", &b13pn2g10z, &b_b13pn2g10z);
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
   fChain->SetBranchAddress("b13pg11Edep", &b13pg11Edep, &b_b13pg11Edep);
   fChain->SetBranchAddress("b13pg11light", &b13pg11light, &b_b13pg11light);
   fChain->SetBranchAddress("b13pg11t", &b13pg11t, &b_b13pg11t);
   fChain->SetBranchAddress("b13pg11x", &b13pg11x, &b_b13pg11x);
   fChain->SetBranchAddress("b13pg11y", &b13pg11y, &b_b13pg11y);
   fChain->SetBranchAddress("b13pg11z", &b13pg11z, &b_b13pg11z);
   fChain->SetBranchAddress("b13pg12Edep", &b13pg12Edep, &b_b13pg12Edep);
   fChain->SetBranchAddress("b13pg12light", &b13pg12light, &b_b13pg12light);
   fChain->SetBranchAddress("b13pg12t", &b13pg12t, &b_b13pg12t);
   fChain->SetBranchAddress("b13pg12x", &b13pg12x, &b_b13pg12x);
   fChain->SetBranchAddress("b13pg12y", &b13pg12y, &b_b13pg12y);
   fChain->SetBranchAddress("b13pg12z", &b13pg12z, &b_b13pg12z);
   fChain->SetBranchAddress("b13pg13Edep", &b13pg13Edep, &b_b13pg13Edep);
   fChain->SetBranchAddress("b13pg13light", &b13pg13light, &b_b13pg13light);
   fChain->SetBranchAddress("b13pg13t", &b13pg13t, &b_b13pg13t);
   fChain->SetBranchAddress("b13pg13x", &b13pg13x, &b_b13pg13x);
   fChain->SetBranchAddress("b13pg13y", &b13pg13y, &b_b13pg13y);
   fChain->SetBranchAddress("b13pg13z", &b13pg13z, &b_b13pg13z);
   fChain->SetBranchAddress("b13pg14Edep", &b13pg14Edep, &b_b13pg14Edep);
   fChain->SetBranchAddress("b13pg14light", &b13pg14light, &b_b13pg14light);
   fChain->SetBranchAddress("b13pg14t", &b13pg14t, &b_b13pg14t);
   fChain->SetBranchAddress("b13pg14x", &b13pg14x, &b_b13pg14x);
   fChain->SetBranchAddress("b13pg14y", &b13pg14y, &b_b13pg14y);
   fChain->SetBranchAddress("b13pg14z", &b13pg14z, &b_b13pg14z);
   fChain->SetBranchAddress("b13pg15Edep", &b13pg15Edep, &b_b13pg15Edep);
   fChain->SetBranchAddress("b13pg15light", &b13pg15light, &b_b13pg15light);
   fChain->SetBranchAddress("b13pg15t", &b13pg15t, &b_b13pg15t);
   fChain->SetBranchAddress("b13pg15x", &b13pg15x, &b_b13pg15x);
   fChain->SetBranchAddress("b13pg15y", &b13pg15y, &b_b13pg15y);
   fChain->SetBranchAddress("b13pg15z", &b13pg15z, &b_b13pg15z);
   fChain->SetBranchAddress("b13pg16Edep", &b13pg16Edep, &b_b13pg16Edep);
   fChain->SetBranchAddress("b13pg16light", &b13pg16light, &b_b13pg16light);
   fChain->SetBranchAddress("b13pg16t", &b13pg16t, &b_b13pg16t);
   fChain->SetBranchAddress("b13pg16x", &b13pg16x, &b_b13pg16x);
   fChain->SetBranchAddress("b13pg16y", &b13pg16y, &b_b13pg16y);
   fChain->SetBranchAddress("b13pg16z", &b13pg16z, &b_b13pg16z);
   fChain->SetBranchAddress("b13pg17Edep", &b13pg17Edep, &b_b13pg17Edep);
   fChain->SetBranchAddress("b13pg17light", &b13pg17light, &b_b13pg17light);
   fChain->SetBranchAddress("b13pg17t", &b13pg17t, &b_b13pg17t);
   fChain->SetBranchAddress("b13pg17x", &b13pg17x, &b_b13pg17x);
   fChain->SetBranchAddress("b13pg17y", &b13pg17y, &b_b13pg17y);
   fChain->SetBranchAddress("b13pg17z", &b13pg17z, &b_b13pg17z);
   fChain->SetBranchAddress("b13pg18Edep", &b13pg18Edep, &b_b13pg18Edep);
   fChain->SetBranchAddress("b13pg18light", &b13pg18light, &b_b13pg18light);
   fChain->SetBranchAddress("b13pg18t", &b13pg18t, &b_b13pg18t);
   fChain->SetBranchAddress("b13pg18x", &b13pg18x, &b_b13pg18x);
   fChain->SetBranchAddress("b13pg18y", &b13pg18y, &b_b13pg18y);
   fChain->SetBranchAddress("b13pg18z", &b13pg18z, &b_b13pg18z);
   fChain->SetBranchAddress("b13pg19Edep", &b13pg19Edep, &b_b13pg19Edep);
   fChain->SetBranchAddress("b13pg19light", &b13pg19light, &b_b13pg19light);
   fChain->SetBranchAddress("b13pg19t", &b13pg19t, &b_b13pg19t);
   fChain->SetBranchAddress("b13pg19x", &b13pg19x, &b_b13pg19x);
   fChain->SetBranchAddress("b13pg19y", &b13pg19y, &b_b13pg19y);
   fChain->SetBranchAddress("b13pg19z", &b13pg19z, &b_b13pg19z);
   fChain->SetBranchAddress("b13pg20Edep", &b13pg20Edep, &b_b13pg20Edep);
   fChain->SetBranchAddress("b13pg20light", &b13pg20light, &b_b13pg20light);
   fChain->SetBranchAddress("b13pg20t", &b13pg20t, &b_b13pg20t);
   fChain->SetBranchAddress("b13pg20x", &b13pg20x, &b_b13pg20x);
   fChain->SetBranchAddress("b13pg20y", &b13pg20y, &b_b13pg20y);
   fChain->SetBranchAddress("b13pg20z", &b13pg20z, &b_b13pg20z);
   Notify();
}

Bool_t GeantTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GeantTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GeantTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GeantTree_cxx
