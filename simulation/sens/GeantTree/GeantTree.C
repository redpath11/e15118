#define GeantTree_cxx
#include "GeantTree.h"
//#include "DefHists.h"
#include "thr_cosy_map.hh"
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
//   const Double_t K0 = 61.5037;//[MeV/u] thin target to get Bp to match
   const Double_t K0 = 61.5806;//[MeV/u] thin target to get Bp to match
//   const K0 = 1477.934;// total reference ptcl KE the way stmona calculates it
//   const Double_t K0 = 63.3359;//MeV/u after thick target
   const Double_t t3eloss = 0.;// O-24 through thin target
//   const Double_t t3eloss = 157.87;// O-24 through half Be3
   const Double_t c2z=1.588;// [m]

   // Random number generator
   TRandom* r2 = new TRandom2();

   /* xy,txty plots: pointer arrays
    *   0: b2 profile
    *   1: GT CRDC1 xy,txty
    *   2: ST CRDC1 xy,txty
    *   3: GT CRDC2 xy,txty
    *   4: ST CRDC2 xy,txty*/
   hxy[0] = new TH2D("hxy2","Post-Tgt3 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[0] = new TH2D("htxty2","Post-Tgt3 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[0]->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty[0]->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy[1]  = new TH2D("hxy7", "CRDC1 x vs y;x [mm];y [mm]",   nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[1]= new TH2D("htxty7","CRDC1 tx vs ty",              nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[1]->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty[1]->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy[2]   = new TH2D("hxy7o","ST CRDC1 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[2] = new TH2D("htxty7o","ST CRDC1 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[2]->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty[2]->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy[3]    = new TH2D("hxy9", "CRDC2 x vs y;x [mm];y [mm]",   nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[3]  = new TH2D("htxty9","CRDC2 tx vs ty",              nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[3]->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty[3]->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy[4]   = new TH2D("hxy9o","ST CRDC2 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[4] = new TH2D("htxty9o","ST CRDC2 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty[4]->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty[4]->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   
   h2fke = new TH1D("h2fke","Post-Tgt3 Fragment KE;KE [MeV/u]",nbinske,ke1,ke2);
   h2fv  = new TH1D("h2fv", "Post-Tgt3 Fragment velocity;velocity [cm/ns]",nbinsv,v1,v2);
   // Neutrons !! //
   h2n0ke = new TH1D("h2n0ke","First Neutron KE;First Neutron KE [MeV/u]",nbinske,ke1,ke2);
   h2n0v  = new TH1D("h2n0v","First Neutron Velocity;velocity [cm/ns]",nbinsv,v1,v2);
//   h13n0ke = new TH1D("h13n0ke","b13Ekin",nbinske,ke1,ke2);
   hgn0ke = new TH1D("hgn0ke","GEANT n0 KE;KE [MeV/u]",nbinske,ke1,ke2);
   hgn0v  = new TH1D("hgn0v" ,"GEANT n0 velocity;velocity [cm/ns]",nbinsv,v1,v2);
   // ToF //
   hfvel  = new TH1D("hfvel" ,"ToF frag velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hfke   = new TH1D("hfke"  ,"ToF frag KE;KE [MeV/u]",nbinske,ke1,ke2);
   hTrfv  = new TH1D("hTrfv" ,"ToF + res frag velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hTrfke = new TH1D("hTrfke","ToF + res frag KE;KE [MeV/u]",nbinske,ke1,ke2);
   // P-Inv //
   hPfv   = new TH1D("hPfv"  ,"P-Inv frag velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hPfke  = new TH1D("hPfke" ,"P-Inv frag KE;KE [MeV/u]",nbinske,ke1,ke2);
   // Relative Velocities //
   h22vrel = new TH1D("h22vrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
   h2Tvrel = new TH1D("h2Tvrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
   hg2vrel = new TH1D("hg2vrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
   hgTvrel = new TH1D("hgTvrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
   hgPvrel = new TH1D("hgPvrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
   hgTrvrel= new TH1D("hgTrvrel","Relative Velocity;relative velocity [cm/ns]",nbinsvr,vr1,vr2);
 

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

  /* Set up full ion-optical matrix for forward tracking */
  string ffilename = "/projects/e15118/n2analysis/maps/z8a24_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.map";
  int fnlines = get_nlines(ffilename);
  int fncol   = get_collumns(ffilename);
  int fncoef  = fncol-1;
  int fnpar   = get_npar(ffilename,fncoef);

  double ** fCoef = AllocateMatrix(fnlines,fncoef);
  double ** fPower= AllocateMatrix(fnlines,fnpar);
  initialize(ffilename,fCoef,fPower);

//  WriteMatrix(fCoef,fnlines,fncoef);
//  WriteMatrix(fPower,fnlines,fnpar);

  // i/o arrays for forward tracking
  Double_t finput[6]  = {0.,0.,0.,0.,0.,0.};
  Double_t foutput[6] = {0.,0.,0.,0.,0.,0.};


  /* Set up partial inverse ion-optical matrix */
  string filename = "/projects/e15118/n2analysis/maps/z8a24_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.imap";
  int nlines = get_nlines(filename);
  int ncol   = get_collumns(filename);
  int ncoef  = ncol-1;
  int npar   = get_npar(filename,ncoef);

  double ** Coeff = AllocateMatrix(nlines,ncoef);
  double ** Power = AllocateMatrix(nlines,npar);
  initialize(filename,Coeff,Power);

  // i/o arrays for partial inverse tracking
  Double_t input[4]  = {0.,0.,0.,0.};
  Double_t output[4] = {0.,0.,0.,0.};





   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {// FOR LOOP OVER ENTRIES
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // reset //
      for(int i=0;i<index;i++)
      {
	x[i]=0.;tx[i]=0.;a[i]=0.;y[i]=0.;ty[i]=0.;b[i]=0.;dt[i]=0.;d[i]=0.;
	finput[i]=0.; foutput[i]=0.;
      }
      for(int i=0;i<4;i++){input[i]=0.;output[i]=0.;}
      x[0] = b2p0x; tx[0] = b2p0tx; y[0] = b2p0y; ty[0] = b2p0ty;
      a[0] = TMath::Tan(tx[0]); b[0] = TMath::Tan(ty[0]);
      x[3] = b7p0x; tx[3] = b7p0tx; y[3] = b7p0y; ty[3] = b7p0ty;
      x[5] = b9p0x; tx[5] = b9p0tx; y[5] = b9p0y; ty[5] = b9p0ty;
      d[0] = (b2p0Ekin/fA)/K0 - 1.;// delta for [MeV/u] KE
//      d[0] = b2p0Ekin/K0 - 1.;// delta for TKE
      Double_t K = 0.;


      hxy[0]->Fill(1000.*x[0],1000.*y[0]); htxty[0]->Fill(1000.*tx[0],1000.*ty[0]);
      hxy[2]->Fill(1000.*x[3],1000.*y[3]); htxty[2]->Fill(1000.*tx[3],1000.*ty[3]);
      hxy[4]->Fill(1000.*x[5],1000.*y[5]); htxty[4]->Fill(1000.*tx[5],1000.*ty[5]);


      /* Transform forward with full ion-optical matrix
       * input is target coordinates
       * output is crdc1 coordinates
      */
/**/
      finput[0] = x[0];  finput[1] = a[0];
      finput[2] = y[0];  finput[3] = b[0];
      finput[4] = dt[0]; finput[5] = d[0];


      for(int i=0;i<fnlines;i++)
      {
        double factor = 1.;
        for(int j=0;j<6;j++){factor *= pow(finput[j],fPower[i][j]);}
	for(int k=0;k<5;k++){foutput[k] += fCoef[i][k] * factor;}
      }

      x[1] = foutput[0]; a[1] = foutput[1];
      y[1] = foutput[2]; b[1] = foutput[3];
      dt[1]= foutput[4]; d[1] = d[0];// KE doesn't change
      Double_t K = K0*(d[1]+1.);


      // Recover angles
      tx[1] = TMath::ATan(a[1]);
      ty[1] = TMath::ATan(b[1]);

      // drift to CRDC 2
      x[4] = x[1]+c2z*a[1]; tx[4]=tx[1];// angles don't change
      y[4] = y[1]+c2z*b[1]; ty[4]=ty[1];// angles don't change

/*
      hxy[1]->Fill(1000.*x[1],1000.*y[1]); htxty[1]->Fill(1000.*tx[1],1000.*ty[1]);
      hxy[3]->Fill(1000.*x[4],1000.*y[4]); htxty[3]->Fill(1000.*tx[4],1000.*ty[4]);
*/
      hxy[1]->Fill(1000.*foutput[0],1000.*foutput[2]); htxty[1]->Fill(1000.*tx[1],1000.*ty[1]);
      hxy[3]->Fill(1000.*x[4],1000.*y[4]); htxty[3]->Fill(1000.*tx[4],1000.*ty[4]);

      /* Transform with partial inverse matrix
       * input is CRDC1 positions and angles
       * ouput is target parameters
      */

      input[0] = x[1]; input[1] = tx[1]; input[2] = y[1]; input[3] = ty[1];
      for(int i=0;i<4;i++){output[i]=0.;}
      factor = 1.;
      for(int i=0;i<nlines;i++)
      {
        factor=1.;
	for(int j=0;j<npar;j++){factor *= pow(input[j], Power[i][j]);}
	for(int k=0;k<ncoef;k++){output[k] += factor * Coeff[i][k];}
      }

      K = 0.;
      K = K0*(output[3]+1.);
      K += (t3eloss/fA);// energy add back
      Double_t fgamPI = (K/amu_M)+1.;
      if(fgamPI>0.)
      {
      Double_t fbetPI = 1. - 1./(fgamPI*fgamPI);
      Double_t fvelPI = C * sqrt(fbetPI);
      hPfv->Fill(fvelPI);
      hPfke->Fill(K);
      }




    /* Neutrons !! */
//    Double_t b2n0ke  = b2p1Ekin * (amu_M/n_M);
//    Double_t n0gamma = (b2p1Ekin / n_M) + 1.;
    Double_t n0gamma = (b2p1Ekin / amu_M) + 1.;
//    Double_t b2n0ke = amu_M*(n0gamma-1.);// MeV/u
    Double_t n0beta  = 1. - 1./(n0gamma*n0gamma);
    Double_t n2vel   = C * sqrt(n0beta);
    h2n0ke->Fill(b2p1Ekin); h2n0v->Fill(n2vel);

    /* GEANT Neutrons !!! */
//    h13n0ke->Fill(b13p1Ekin);
    Double_t n0xx   = b13pn1g1x*b13pn1g1x;
    Double_t n0yy   = b13pn1g1y*b13pn1g1y;
    Double_t n0zz   = b13pn1g1z*b13pn1g1z;
    Double_t n0dist = sqrt(n0xx + n0yy + n0zz);
    Double_t ngvel  = (100.*n0dist)/(b13pn1g1t+mona_tshift);
    Double_t n0beta = ngvel/C;
    Double_t n0gama = 1./sqrt(1. - (n0beta*n0beta));
    Double_t n0ke   = (amu_M*(n0gama-1.));// MeV/u
    hgn0ke->Fill(n0ke); hgn0v->Fill(ngvel);

    /* Fragments */
//    Double_t b2fgama = (b2p0Ekin / (fA * amu_M)) + 1.;
    Double_t b2fgama = (b2p0Ekin+t3eloss)/(fA*amu_M) + 1.;
    Double_t b2fke   = amu_M*(b2fgama-1.);//MeV/u
//    Double_t b2fke   = b2p0Ekin/fA;
//    Double_t b2fgama = (b2fke/amu_M) + 1.;
    Double_t b2fbeta = 1. - 1./(b2fgama*b2fgama);
    Double_t b2fvel  = C * sqrt(b2fbeta);
    Double_t vrel = ngvel - b2fvel;
    hg2vrel->Fill(vrel);
    h2fke->Fill(b2fke); h2fv->Fill(b2fvel);
    /* Fragment velocity */
    // Determine ToF target scint to crdc2 //
    Double_t c2path = (b9p0path*100.);// + 102.3239;
//    Double_t fthin  = (c2path+102.3239) + (90.2/cos(tx[1]));
//    Double_t sToF   = fthin/fvel;
    // Recalculate w/out eloss for ToF
    b2fgama = (b2p0Ekin)/(fA*amu_M) + 1.;
    b2fke   = amu_M*(b2fgama-1.);//MeV/u
    b2fbeta = 1. - 1./(b2fgama*b2fgama);
    b2fvel  = C * sqrt(b2fbeta);
    Double_t sToF   = c2path/b2fvel;
    // Estimate distance from crdc 2 x //
//    Double_t fdist = (x[4]*1000.)*0.06832 + 425.1;
//    Double_t fdist = (x[4]*1000.)*0.06832 + 322.7;
    Double_t fdist = (x[4]*1000.)*0.06832 + 322.7;
    Double_t fvelocity = fdist/(sToF);
    Double_t fbeta0    = fvelocity/C;
    Double_t fgamma0   = 1./sqrt(1. - (fbeta0*fbeta0));
    Double_t fkenergy0 = (amu_M*(fgamma0-1.));//MeV/u
    fkenergy0         += t3eloss/fA;// add back O-24 energy loss through 1/2 Be3
    fgamma0            = fkenergy0 / amu_M + 1.;
    fbeta0             = 1. - (1./(fgamma0*fgamma0));
    fvelocity          = sqrt(fbeta0)*C;
    hfke->Fill(fkenergy0); hfvel->Fill(fvelocity);
    // Add ToF resolution
    Double_t res = r2->Gaus(0.,0.465030);
    Double_t fvelocityR = fdist/(sToF + res);
    fbeta0    = fvelocityR/C;
    fgamma0   = 1./sqrt(1. - (fbeta0*fbeta0));
    fkenergy0 = (amu_M*(fgamma0-1.));//MeV/u
    fkenergy0         += t3eloss/fA;// add back O-24 energy loss through 1/2 Be3
    fgamma0            = fkenergy0 / amu_M + 1.;
    fbeta0             = 1. - (1./(fgamma0*fgamma0));
    fvelocityR          = sqrt(fbeta0)*C;
    hTrfke->Fill(fkenergy0); hTrfv->Fill(fvelocityR);


    vrel=0.; vrel    = n2vel - b2fvel;
    h22vrel->Fill(vrel);
    vrel=0.; vrel = n2vel - fvelocity;
    h2Tvrel->Fill(vrel);

    vrel=0.; vrel = ngvel - fvelocity;
    hgTvrel->Fill(vrel);
    vrel=0.; vrel = ngvel - fvelPI;
    hgPvrel->Fill(vrel);
    vrel=0.; vrel = ngvel - fvelocityR;
    hgTrvrel->Fill(vrel);

   }// CLOSE FOR LOOP OVER ENTIRES

  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.22);
  gStyle->SetStatH(0.15);
  
  TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1);
  c1->cd(1); hxy[0]->Draw("COLZ");
  c1->cd(2); htxty[0]->Draw("COLZ");

  TCanvas *c7 = new TCanvas("c7","c7",1000,500);
  c7->Divide(2,1);
  c7->cd(1); hxy[1]->Draw("COLZ");
  c7->cd(2); htxty[1]->Draw("COLZ");

  TCanvas *c8 = new TCanvas("c8","c8",1000,500);
  c8->Divide(2,1);
  c8->cd(1); hxy[2]->Draw("COLZ");
  c8->cd(2); htxty[2]->Draw("COLZ");

  TCanvas *c9 = new TCanvas("c9","c9",1000,500);
  c9->Divide(2,1);
  c9->cd(1); hxy[3]->Draw("COLZ");
  c9->cd(2); htxty[3]->Draw("COLZ");

  TCanvas *c10 = new TCanvas("c10","c10",1000,500);
  c10->Divide(2,1);
  c10->cd(1); hxy[4]->Draw("COLZ");
  c10->cd(2); htxty[4]->Draw("COLZ");

  // KE and velocity
  TCanvas *c22 = new TCanvas("c22","c22",1000,500);
  c22->Divide(2,1);
  const Int_t hc[5] = {1,38,4,2,28};//{frag,b2n0,gn0,ToFfrag,PInvfrag}
  ModHistogram(h2n0ke,hc[1],2); ModHistogram(hgn0ke,hc[2],2);
  ModHistogram(h2fke,hc[0],4);  ModHistogram(hfke,hc[3],4);
  ModHistogram(hPfke,hc[4],2);  ModHistogram(hTrfke,hc[3],2);
  h2fke->SetLineStyle(2); hfke->SetLineStyle(2);
  TPaveText *csb[17];
  csb[0] = CustomStatsBoxL(h2fke ,1,hc[0],0);
  csb[1] = CustomStatsBoxL(hPfke, 1,hc[4],1);
  csb[2] = CustomStatsBoxL(hfke,  1,hc[3],2);
  csb[3] = CustomStatsBoxL(hTrfke,1,hc[3],3);
  csb[4] = CustomStatsBoxL(h2n0ke,1,hc[1],4);
  csb[5] = CustomStatsBoxL(hgn0ke,1,hc[2],5);
  c22->cd(1);
  h2fke->Draw();
  hfke ->Draw("SAME");
  hTrfke->Draw("SAME");
  hPfke->Draw("SAME");
  h2n0ke->Draw("SAME");
  hgn0ke->Draw("SAME");
  for(int i=0;i<6;i++){csb[i]->Draw("SAME");}

  ModHistogram(h2n0v,hc[1],2); ModHistogram(hgn0v,hc[2],2);
  ModHistogram(h2fv,hc[0],4);  ModHistogram(hfvel,hc[3],2);
  ModHistogram(hPfv,hc[4],2);  ModHistogram(hTrfv,hc[3],2);
  h2fv->SetLineStyle(2); hfvel->SetLineStyle(2);
  csb[6] = CustomStatsBoxL(h2fv, 1,hc[0],0);
  csb[7] = CustomStatsBoxL(hPfv ,1,hc[4],1);
  csb[8] = CustomStatsBoxL(hfvel,1,hc[3],2);
  csb[9] = CustomStatsBoxL(hTrfv,1,hc[3],3);
  csb[10] = CustomStatsBoxL(h2n0v,1,hc[1],4);
  csb[11] = CustomStatsBoxL(hgn0v,1,hc[2],5);
  c22->cd(2);
  h2fv->Draw();
  hfvel->Draw("SAME"); hTrfv->Draw("SAME");
  hPfv->Draw("SAME");
  hgn0v->Draw("SAME"); h2n0v->Draw("SAME"); 
//  h2fv->Draw();
  for(int i=6;i<12;i++){csb[i]->Draw("SAME");}

/* Relative Velocity 1
  TCanvas *c23 = new TCanvas("c23","c23",700,500);
  const Int_t vrc[5] = {1,807,13,2,28};//(neutron,fragment){22,2T,g2,gT}
  ModHistogram(h22vrel,vrc[0],4); ModHistogram(h2Tvrel,vrc[1],2);
  ModHistogram(hg2vrel,vrc[2],2); ModHistogram(hgTvrel,vrc[3],2);
  ModHistogram(hgPvrel,vrc[4],2);
  h22vrel->SetLineStyle(2);
  csb[12] = CustomStatsBox(h22vrel,1,vrc[0],0);
  csb[13] = CustomStatsBox(h2Tvrel,1,vrc[1],1);
  csb[14] = CustomStatsBox(hg2vrel,1,vrc[2],2);
  csb[15] = CustomStatsBox(hgPvrel,1,vrc[4],3);
  csb[16] = CustomStatsBox(hgTvrel,1,vrc[3],4);
  h22vrel->Draw(); h2Tvrel->Draw("SAME");
  hg2vrel->Draw("SAME"); hgTvrel->Draw("SAME");
  hgPvrel->Draw("SAME");
  for(int i=12;i<17;i++){csb[i]->Draw("SAME");}
*/

  /* Relative Velocity 2 */
  TCanvas *c24 = new TCanvas("c24","c24",700,500);
  const Int_t vr2c[] = {1,28,2};// (n,f){(g2),(gP),(gTr)}
  ModHistogram(hg2vrel,vr2c[0],2);
  ModHistogram(hgPvrel,vr2c[1],2);
  ModHistogram(hgTrvrel,vr2c[2],2);
  csb[12] = CustomStatsBox(hg2vrel,1,vr2c[0],0);
  csb[13] = CustomStatsBox(hgPvrel,1,vr2c[1],1);
  csb[14] = CustomStatsBox(hgTrvrel,1,vr2c[2],2);
  hg2vrel->Draw(); hgPvrel->Draw("SAME"); hgTrvrel->Draw("SAME");
  for(int i=12;i<15;i++){csb[i]->Draw("SAME");}


  TCanvas *c20 = new TCanvas("c20","c20",1000,500);
  c20->Divide(2,1);
  c20->cd(1); h2fke->DrawCopy(); hfke->DrawCopy("SAME");
  hPfke->DrawCopy("SAME"); h2n0ke->DrawCopy("SAME");
  for(int i=0;i<4;i++){csb[i]->Draw("SAME");}
  c20->cd(2); h2fv->DrawCopy(); hfvel->DrawCopy("SAME");
  hPfv->DrawCopy("SAME"); hgn0v->DrawCopy("SAME");
  for(int i=5;i<9;i++){csb[i]->Draw("SAME");}

  // Free memory
  DeallocateMatrix(fCoef,fnlines,fncoef);
  DeallocateMatrix(fPower,fnlines,fncoef);
  DeallocateMatrix(Coeff,nlines,ncoef);
  DeallocateMatrix(Power,nlines,npar);


}
