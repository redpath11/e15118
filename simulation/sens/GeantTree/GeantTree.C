#define GeantTree_cxx
#include "GeantTree.h"
#include "UtilFunctions.hh"
#include "Binning.h"
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
   fChain->SetBranchStatus("b2p0x",1);
   fChain->SetBranchStatus("b2p0tx",1);
   fChain->SetBranchStatus("b2p0y",1);
   fChain->SetBranchStatus("b2p0ty",1);
   fChain->SetBranchStatus("b2p0Ekin",1);
   fChain->SetBranchStatus("b2p1Ekin",1);
   fChain->SetBranchStatus("b7p0x",1);
   fChain->SetBranchStatus("b7p0tx",1);
   fChain->SetBranchStatus("b7p0y",1);
   fChain->SetBranchStatus("b7p0ty",1);
   fChain->SetBranchStatus("b9p0x",1);
   fChain->SetBranchStatus("b9p0tx",1);
   fChain->SetBranchStatus("b9p0y",1);
   fChain->SetBranchStatus("b9p0ty",1);
   fChain->SetBranchStatus("b9p0path",1);
   fChain->SetBranchStatus("b13p1Ekin",1);
   fChain->SetBranchStatus("b13pn1g1x",1);
   fChain->SetBranchStatus("b13pn1g1y",1);
   fChain->SetBranchStatus("b13pn1g1z",1);
   fChain->SetBranchStatus("b13pn1g1t",1);

   /*
   fChain->SetBranchStatus("b7p0Ekin",1);
   fChain->SetBranchStatus("b9p0x",1);
   fChain->SetBranchStatus("b9p0tx",1);
   fChain->SetBranchStatus("b9p0Ekin",1);
   fChain->SetBranchStatus("b9p0path",1);
   fChain->SetBranchStatus("b13pn1g1x",1);
   fChain->SetBranchStatus("b13pn1g1y",1);
   fChain->SetBranchStatus("b13pn1g1z",1);
   fChain->SetBranchStatus("b13pn1g1t",1);
   */

   // Constants
   const Double_t amu_M = 931.494008;// [MeV/c^2]
   const Double_t n_M   = 939.565560;// [MeV/c^2]
   const Double_t C     = 29.9792458;// [cm/ns]
   const Double_t mona_tshift = -0.235;
   const Double_t fA = 24.;
   // Remember that K0 is the KE for O-24 reference ptcl on the
   // magnet central track
   const Double_t K0 = 61.5;//[MeV/u] thin target to get Bp to match
//   const Double_t K0 = 63.3359;//MeV/u after thick target
   const Double_t t3eloss = 0.;// O-24 through thin target
//   const Double_t t3eloss = 157.87;// O-24 through half Be3
   const Double_t c2z=1.588;// [m]

   // Random number generator
   TRandom* r2 = new TRandom2();

   // Post Target Stuff //
   hxy2 = new TH2D("hxy2","Post-Tgt3 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty2 = new TH2D("htxty2","Post-Tgt3 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty2->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty2->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy7o = new TH2D("hxy7o","ST CRDC1 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty7o = new TH2D("htxty7o","ST CRDC1 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty7o->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty7o->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy9o = new TH2D("hxy9o","ST CRDC2 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty9o = new TH2D("htxty9o","ST CRDC2 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty9o->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty9o->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   h2fke = new TH1D("h2fke","Post-Tgt3 Fragment KE;KE [MeV/u]",nbinske,ke1,ke2);
   h2fv  = new TH1D("h2fv", "Post-Tgt3 Fragment velocity;velocity [cm/ns]",nbinsv,v1,v2);
   // Neutrons !! //
   h2n0ke = new TH1D("h2n0ke","First Neutron KE;First Neutron KE [MeV/u]",nbinske,ke1,ke2);
   h2n0v  = new TH1D("h2n0v","First Neutron Velocity;velocity [cm/ns]",nbinsv,v1,v2);
//   h13n0ke = new TH1D("h13n0ke","b13Ekin",nbinske,ke1,ke2);
   hgn0ke = new TH1D("hgn0ke","GEANT n0 KE;KE [MeV/u]",nbinske,ke1,ke2);
   hgn0v  = new TH1D("hgn0v" ,"GEANT n0 velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hfvel  = new TH1D("hfvel" ,"ToF frag velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hfke   = new TH1D("hfke"  ,"ToF frag KE;KE [MeV/u]",nbinske,ke1,ke2);

   /* Indexes:  0 - starting after target
    * 		1 - forward mapped to CRDC 1
    * 		2 - inverse mapped to target
    * 		3 - st forward tracked to CRDC 1
    * 		4 - drifted to CRDC 2 from CRDC 1 forward
    * 		5 - st CRDC 2
   */
   const int index=6;
   Double_t x [index] = {0.,0.,0.,0.,0.,0.};
   Double_t tx[index] = {0.,0.,0.,0.,0.,0.};
   Double_t a [index] = {0.,0.,0.,0.,0.,0.};
   Double_t y [index] = {0.,0.,0.,0.,0.,0.};
   Double_t ty[index] = {0.,0.,0.,0.,0.,0.};
   Double_t b [index] = {0.,0.,0.,0.,0.,0.};
   Double_t dt[index] = {0.,0.,0.,0.,0.,0.};
   Double_t d [index] = {0.,0.,0.,0.,0.,0.};




   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {// FOR LOOP OVER ENTRIES
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // reset
      for(int i=0;i<index;i++){x[i]=0.;tx[i]=0.;a[i]=0.;y[i]=0.;ty[i]=0.;b[i]=0.;dt[i]=0.;d[i]=0.;}
      x[0] = b2p0x; tx[0] = b2p0tx; y[0] = b2p0y; ty[0] = b2p0ty;
      x[3] = b7p0x; tx[3] = b7p0tx; y[3] = b7p0y; ty[3] = b7p0ty;
      x[5] = b9p0x; tx[5] = b9p0tx; y[5] = b9p0y; ty[5] = b9p0ty;



      hxy2->Fill(1000.*x[0],1000.*y[0]); htxty2->Fill(1000.*tx[0],1000.*ty[0]);
      hxy7o->Fill(1000.*x[3],1000.*y[3]); htxty7o->Fill(1000.*tx[3],1000.*ty[3]);
      hxy9o->Fill(1000.*x[5],1000.*y[5]); htxty9o->Fill(1000.*tx[5],1000.*ty[5]);


    /* Fragments */
    Double_t b2fgama = (b2p0Ekin / (fA * amu_M)) + 1.;
    Double_t b2fke   = amu_M*(b2fgama-1.);//MeV/u
//    Double_t b2fke   = b2p0Ekin/fA;
//    Double_t b2fgama = (b2fke/amu_M) + 1.;
    Double_t b2fbeta = 1. - 1./(b2fgama*b2fgama);
    Double_t b2fvel  = C * sqrt(b2fbeta);
    h2fke->Fill(b2fke); h2fv->Fill(b2fvel);
    /* Fragment velocity */
    // Determine ToF target scint to crdc2 //
    Double_t c2path = (b9p0path*100.);// + 102.3239;
//    Double_t fthin  = (c2path+102.3239) + (90.2/cos(tx[1]));
//    Double_t sToF   = fthin/fvel;
    Double_t sToF   = c2path/b2fvel;
    // Estimate distance from crdc 2 x //
//    Double_t fdist = (x[1]*1000.)*0.06832 + 425.1;
//    Double_t fdist = (x[1]*1000.)*0.06832 + 322.7;
    Double_t fdist = (x[5]*1000.)*0.06832 + 322.7;
//    Double_t fvelocity = fdist/(sToF + res);
    Double_t fvelocity = fdist/(sToF);
    Double_t fbeta0    = fvelocity/C;
    Double_t fgamma0   = 1./sqrt(1. - (fbeta0*fbeta0));
    Double_t fkenergy0 = (amu_M*(fgamma0-1.));//MeV/u
    fkenergy0         += t3eloss/fA;// add back O-24 energy loss through 1/2 Be3
    fgamma0            = fkenergy0 / amu_M + 1.;
    fbeta0             = 1. - (1./(fgamma0*fgamma0));
    fvelocity          = sqrt(fbeta0)*C;
    hfke->Fill(fkenergy0); hfvel->Fill(fvelocity);



    /* Neutrons !! */
//    Double_t b2n0ke  = b2p1Ekin * (amu_M/n_M);
//    Double_t n0gamma = (b2p1Ekin / n_M) + 1.;
    Double_t n0gamma = (b2p1Ekin / amu_M) + 1.;
//    Double_t b2n0ke = amu_M*(n0gamma-1.);// MeV/u
    Double_t n0beta  = 1. - 1./(n0gamma*n0gamma);
    Double_t n0vel   = C * sqrt(n0beta);
    h2n0ke->Fill(b2p1Ekin); h2n0v->Fill(n0vel);

    /* Check Neutrons !!! */
//    h13n0ke->Fill(b13p1Ekin);
    Double_t n0xx   = b13pn1g1x*b13pn1g1x;
    Double_t n0yy   = b13pn1g1y*b13pn1g1y;
    Double_t n0zz   = b13pn1g1z*b13pn1g1z;
    Double_t n0dist = sqrt(n0xx + n0yy + n0zz);
    n0vel=0.; n0vel  = (100.*n0dist)/(b13pn1g1t+mona_tshift);
    Double_t n0beta = n0vel/C;
    Double_t n0gama = 1./sqrt(1. - (n0beta*n0beta));
    Double_t n0ke   = (amu_M*(n0gama-1.));// MeV/u
    hgn0ke->Fill(n0ke); hgn0v->Fill(n0vel);




   }// CLOSE FOR LOOP OVER ENTIRES

  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.22);
  gStyle->SetStatH(0.15);
  
  TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1);
  c1->cd(1); hxy2->Draw("COLZ");
  c1->cd(2); htxty2->Draw("COLZ");

  TCanvas *c8 = new TCanvas("c8","c8",1000,500);
  c8->Divide(2,1);
  c8->cd(1); hxy7o->Draw("COLZ");
  c8->cd(2); htxty7o->Draw("COLZ");

  TCanvas *c10 = new TCanvas("c10","c10",1000,500);
  c10->Divide(2,1);
  c10->cd(1); hxy9o->Draw("COLZ");
  c10->cd(2); htxty9o->Draw("COLZ");

  TCanvas *c100 = new TCanvas("c100","c100",700,500);
  const Int_t hc[4] = {1,38,4,2};//{frag,b2n0,gn0,ToFfrag}
  ModHistogram(h2n0ke,hc[1],2); ModHistogram(hgn0ke,hc[2],2);
  ModHistogram(h2fke,hc[0],4);  ModHistogram(hfke,hc[3],2);
  TPaveText *csb[8];
  csb[0] = CustomStatsBox(h2fke ,1,hc[0],0);
  csb[1] = CustomStatsBox(hfke,  1,hc[3],1);
  csb[2] = CustomStatsBox(h2n0ke,1,hc[1],2);
  csb[3] = CustomStatsBox(hgn0ke,1,hc[2],3);
  h2fke->Draw();
  hfke ->Draw("SAME");
  h2n0ke->Draw("SAME");
  hgn0ke->Draw("SAME");
  for(int i=0;i<4;i++){csb[i]->Draw("SAME");}

  TCanvas *c101 = new TCanvas("c101","c101",700,500);
  ModHistogram(h2n0v,hc[1],2); ModHistogram(hgn0v,hc[2],2);
  ModHistogram(h2fv,hc[0],2); ModHistogram(hfvel,hc[3],2);
  csb[4] = CustomStatsBox(h2fv, 1,hc[0],0);
  csb[5] = CustomStatsBox(hfvel,1,hc[3],1);
  csb[6] = CustomStatsBox(h2n0v,1,hc[1],2);
  csb[7] = CustomStatsBox(hgn0v,1,hc[2],3);
  h2n0v->Draw(); hfvel->Draw("SAME");
  hgn0v->Draw("SAME"); h2fv->Draw("SAME");
//  h2fv->Draw();
  for(int i=4;i<8;i++){csb[i]->Draw("SAME");}

}
