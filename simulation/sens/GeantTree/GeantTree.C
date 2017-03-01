#define GeantTree_cxx
#include "GeantTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void GeantTree::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L GeantTree.C
//      Root > GeantTree t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   fChain->SetBranchStatus("*",0);// disable all branches
   fChain->SetBranchStatus("b7p0Ekin",1);
   fChain->SetBranchStatus("b9p0x",1);
   fChain->SetBranchStatus("b9p0tx",1);
   fChain->SetBranchStatus("b9p0Ekin",1);
   fChain->SetBranchStatus("b9p0path",1);
   fChain->SetBranchStatus("b13pn1g1x",1);
   fChain->SetBranchStatus("b13pn1g1y",1);
   fChain->SetBranchStatus("b13pn1g1z",1);
   fChain->SetBranchStatus("b13pn1g1t",1);

   // Constants
   const Double_t amu_M = 931.494008;
   const Double_t C     = 29.9792458;
   const Double_t monat_shift = -0.95;
   // Random number generator
   TRandom* r2 = new TRandom2();
   // Define histograms
   tof = new TH1D("tofres","tofres",100,36,46);
   fvel = new TH1D("fvelres","fvelres",100,10,12);
   ke0 = new TH1D("ke0res","ke0res",25,50,75);
   nvel= new TH1D("nvel","Neutron Velocity",80,9,13);
   vrel= new TH1D("vrel","(n-f) Velocity",100,-5,5);



   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (b7p0Ekin>1 && b9p0Ekin>1){
      // if (Cut(ientry) < 0) continue;
      Double_t res = r2->Gaus(0.,0.465030);

      // Fragment ToF
      Double_t c2path = (b9p0path+1.04)*100.;
      Double_t fthin = c2path + (90.2/TMath::Cos(b9p0tx));// extrapolate dist to thin

//      Double_t fthin = fdist + (90.2/TMath::Cos(b9p0tx));// extrapolate dist to thin
      Double_t fgama = ((b9p0Ekin/24.019861) / amu_M) + 1.0;
      Double_t fbeta = 1. - 1. / ((fgama)*(fgama));
      Double_t fvelo = C * TMath::Sqrt(fbeta);
      Double_t stof  = (fthin/fvelo) - 8.84;

      tof->Fill(stof + res);

      // Fragment distance from crdc2.x
      Double_t fdist = (b9p0x*1000.) * 0.06832 + 425.1;// distance to crdc2 as in data
      Double_t fvelocity = fdist/(stof+res);
      fvelocity += 0.5331;// add back velocity equivalent of energy lost through ST

      fvel->Fill(fvelocity);

      Double_t fbeta0  = fvelocity/C;
      Double_t fgamma0 = 1./TMath::Sqrt(1. - (fbeta0*fbeta0));
      Double_t fkener0 = amu_M*(fgamma0 - 1.);

      ke0->Fill(fkener0);

      // First neutron velocity
      Double_t nd = (b13pn1g1x*b13pn1g1x + b13pn1g1y*b13pn1g1y + b13pn1g1z*b13pn1g1z);
      nd = TMath::Sqrt(nd);
      Double_t monat = b13pn1g1t + monat_shift;
//      Double_t nv = (100.*nd)/b13pn1g1t;
      Double_t nv = (100.*nd)/monat;
      if(b13pn1g1t>1)
      { nvel->Fill(nv);//}

      // n0 - frag relative velocity
      Double_t vr = nv - fvelocity;
      vrel->Fill(vr);
      }
      }


   }
}
