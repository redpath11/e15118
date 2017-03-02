#define PreGeant_cxx
#include "PreGeant.h"
#include "Coefficients.h"
#include "Binning.h"
#include "thr_cosy_map.hh"
#include "UtilFunctions.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void PreGeant::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L PreGeant.C
//      Root > PreGeant t
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
   fChain->SetBranchStatus("b4p0x",1);
   fChain->SetBranchStatus("b4p0tx",1);
   fChain->SetBranchStatus("b4p0y",1);
   fChain->SetBranchStatus("b4p0ty",1);
   fChain->SetBranchStatus("b6p0x",1);
   fChain->SetBranchStatus("b6p0tx",1);
   fChain->SetBranchStatus("b6p0y",1);
   fChain->SetBranchStatus("b6p0ty",1);
   fChain->SetBranchStatus("b6p0path",1);

   // Set branch states

   // Constants
//   const Double_t n_M   = 939.565560;// [MeV/c^2]
   const Double_t amu_M = 931.494088;// MeV/c^2
   const Double_t     C = 29.9792458;// cm/ns
   const Double_t fA = 24.;
   // Remember that K0 is the KE for O-24 reference ptcl on the
   // magnet central track
   const Double_t K0 = 61.5;//MeV/u thin target to get Bp to match
//   const Double_t K0 = 63.3359;//MeV/u after thick target
   const Double_t t3eloss = 0.;// O-24 through thin target
//   const Double_t t3eloss = 157.87;// O-24 through half Be3
   const Double_t c2z=1.588;// [m]

   /* Kinematic factor for dt variable
   // For the reference particle O-24 at Bp = 3.445
   const Double_t g0 = 1.066027; const Double_t v0 = 10.3868;
   const Double_t kappa = (-v0*g0)/(1.+g0);
*/

   // Random number generator for ToF resolution
   TRandom *r2 = new TRandom2();

   // Define histograms
   // Binning parameters moved to Binning.h

   hxy2 = new TH2D("hxy2","Post-Target x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy2->SetTitle("Post-Tgt3 x vs. y");
   hxy2->GetXaxis()->SetTitle("x [mm]");
   hxy2->GetYaxis()->SetTitle("y [mm]");
   htxty2 = new TH2D("htxty2","Post-Target tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty2->SetTitle("Post-Tgt3 #theta_{x} vs. #theta_{y}");
   htxty2->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty2->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hfvel2 = new TH1D("hfvel2","Post-Target Fragment Velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hfke2 = new TH1D("hfke2","Post-Target KE;KE [MeV/u]",nbinske,ke1,ke2);
   hxy4 = new TH2D("hxy4","CRDC 1 x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy4->SetTitle("CRDC 1 x vs. y");
   hxy4->GetXaxis()->SetTitle("x [mm]");
   hxy4->GetYaxis()->SetTitle("y [mm]");
   htxty4 = new TH2D("htxty4","CRDC 1 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty4->SetTitle("CRDC 1 #theta_{x} vs. #theta_{y}");
   htxty4->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty4->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hxy4o = new TH2D("hxy4o","ST CRDC 1 x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy4o->SetTitle("ST CRDC 1 x vs. y");
   hxy4o->GetXaxis()->SetTitle("x [mm]");
   hxy4o->GetYaxis()->SetTitle("y [mm]");
   htxty4o = new TH2D("htxty4o","ST CRDC 1 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty4o->SetTitle("ST CRDC 1 #theta_{x} vs. #theta_{y}");
   htxty4o->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty4o->GetYaxis()->SetTitle("#theta_{y} [mrad]");
//   h4time = new TH1D("h4time","h4time",150,-15,15);
//   hFwrdMxy = new TH2D("hFwrdMxy","Mtx CRDC 1 x vs y;x [mm];y [mm]",nbinsx,x1,x2,nbinsy,y1,y2);
//   hFwrdMxy->SetTitle("Mtx CRDC 1 x vs. y");
//   hFwrdMtxty = new TH2D("hFwrdMtxty","Mtx CRDC 1 tx vs ty;#theta_{x} [mrad];#theta_{y} [mrad]",
//   nbinsx,x1,x2,nbinsy,y1,y2);
//   hFwrdMtxty->SetTitle("Mtx CRDC 1 #theta_{x} vs. #theta_{y}");
   hxy2i = new TH2D("hxy2i","itrack Post-Target x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy2i->SetTitle("itrack Post-Tgt3 x vs. y");
   hxy2i->GetXaxis()->SetTitle("x [mm]");
   hxy2i->GetYaxis()->SetTitle("y [mm]");
   htxty2i = new TH2D("htxty2i","itrack Post-Target tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty2i->SetTitle("itrack Post-Tgt3 #theta_{x} vs. #theta_{y}");
   htxty2i->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty2i->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   // KE //
   hke4 = new TH1D("hke4","C1 KE",nbinske,ke1,ke2);
   hke4->SetTitle("Forward mapped KE");
   hke4->GetXaxis()->SetTitle("KE [MeV/u]");
   // drifted CRDC 2 //
   hxy6 = new TH2D("hxy6","drifted CRDC 2 x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy6->SetTitle("Drifted CRDC 2 x vs. y");
   hxy6->GetXaxis()->SetTitle("x [mm]");
   hxy6->GetYaxis()->SetTitle("y [mm]");
   htxty6 = new TH2D("htxty6","drifted CRDC 2 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty6->SetTitle("Drifted CRDC 2 #theta_{x} vs. #theta_{y}");
   htxty6->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty6->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   // ST CRDC 2 //
   hxy6o = new TH2D("hxy6o","ST CRDC 2 x vs y",nbinsx,x1,x2,nbinsy,y1,y2);
   hxy6o->SetTitle("ST CRDC 2 x vs. y");
   hxy6o->GetXaxis()->SetTitle("x [mm]");
   hxy6o->GetYaxis()->SetTitle("y [mm]");
   htxty6o = new TH2D("htxty6o","ST CRDC 2 tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxty6o->SetTitle("ST CRDC 2 #theta_{x} vs. #theta_{y}");
   htxty6o->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxty6o->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   // Partial inverse tracking //
   htxtyC = new TH2D("htxtyC","COSY part inv tracked tx vs ty",nbinsx,x1,x2,nbinsy,y1,y2);
   htxtyC->SetTitle("COSY PInv #theta_{x} vs. #theta_{y}");
   htxtyC->GetXaxis()->SetTitle("#theta_{x} [mrad]");
   htxtyC->GetYaxis()->SetTitle("#theta_{y} [mrad]");
   hdeC = new TH1D("hfkePI","COSY part inv tracked KE;KE [MeV/u]",nbinske,ke1,ke2);
   hfvelC = new TH1D("hfvelPI","COSY part inv tracked vel;velocity [cm/ns]",nbinsv,v1,v2);
   // Neutrons !! //
   hn0ke = new TH1D("hn0ke","First Neutron KE",nbinske,ke1,ke2);
   hn0ke->GetXaxis()->SetTitle("First Neutron KE [MeV/u]");
   hn0v  = new TH1D("hn0v","First Neutron Velocity;First Neutron velocity [cm/ns]",nbinsv,v1,v2);
   // Fragment ToF hack //
   hsToF  = new TH1D("hsToF","Fragment ToF;stof.pot_thin [ns]",nbinst,t1,t2);
   hsToFres  = new TH1D("hsToFres","Fragment ToF (w/ resolution);stof.pot_thin [ns]",nbinst,t1,t2);
   hfdist = new TH1D("hfdist","Fragment Distance (via c2x);Distance [cm]",150,310,340);
   hc2path= new TH1D("hc2path","Simulation tracked c2 path;Distance [cm]",150,310,340);
   hfvelT = new TH1D("hfvelT","Fragment velocity;velocity [cm/ns]",nbinsv,v1,v2);
   hfkeT  = new TH1D("hfkeT","Fragment KE;KE [MeV/u]",nbinske,ke1,ke2);
   hc2pathdist = new TH2D("hc2pd","Path vs. est. distance;fdist;c2path",150,310,340,150,310,340);

   // Relative Velocities //
   hvr2 = new TH1D("hvr2","Relative velocity;v_{rel} [cm/ns]",nbinsvr,vr1,vr2);
   hvrC = new TH1D("hvrC","Relative velocity;v_{rel} [cm/ns]",nbinsvr,vr1,vr2);
   hvrT = new TH1D("hvrT","Relative velocity;v_{rel} [cm/ns]",nbinsvr,vr1,vr2);

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
   /* test drift to CRDC 1
   Double_t c1x=0.,c1y=0.,z1=1.25;*/
   // CRDC 2 drift
   // Fragment KE after magnet
//   Double_t terms[32];

  /* Set up full ion-optical matrix for forward tracking */
  string ffilename = "/projects/e15118/n2analysis/maps/z8a24_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.map";
  int fnlines = get_nlines(ffilename);
  int fncol   = get_collumns(ffilename);
  int fncoef  = fncol-1;
  int fnpar   = get_npar(ffilename,fncoef);

  double ** fCoef = AllocateMatrix(fnlines,fncoef);
  double ** fPower= AllocateMatrix(fnlines,fnpar);
  initialize(ffilename,fCoef,fPower);

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


   /* ----- LOOP OVER ENTRIES ----- */
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      // reset
      for(int i=0;i<index;i++){x[i]=0.;tx[i]=0.;a[i]=0.;y[i]=0.;ty[i]=0.;b[i]=0.;dt[i]=0.;d[i]=0.;
      			       finput[i]=0.; foutput[i]=0.;}
      for(int i=0;i<4;i++){input[i]=0.;output[i]=0.;}
      // resolution for ToF measurement
      Double_t res = r2->Gaus(0.,0.465030);
      x[0] = b2p0x; tx[0] = b2p0tx; y[0] = b2p0y; ty[0] = b2p0ty;
      x[3] = b4p0x; tx[3] = b4p0tx; y[3] = b4p0y; ty[3] = b4p0ty;
      x[5] = b6p0x; tx[5] = b6p0tx; y[5] = b6p0y; ty[5] = b6p0ty;
      hxy4o->Fill(1000.*x[3],1000.*y[3]); htxty4o->Fill(1000.*tx[3],1000.*ty[3]);
//      hxy4o->Fill(1000.*b4p0x,1000.*b4p0y); htxty4o->Fill(1000.*b4p0tx,1000.*b4p0ty);
      hxy6o->Fill(1000.*x[5],1000.*y[5]); htxty6o->Fill(1000.*tx[5],1000.*ty[5]);
      a[0] = TMath::Tan(tx[0]);
      b[0] = TMath::Tan(ty[0]);
      //dt[0]= ???;
      d[0] = ((b2p0Ekin/fA)-K0)/K0;
      Double_t K = 0.;

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
      dt[1]= foutput[4];





      d[1] = d[0];// KE doesn't change
      K = K0*(d[1]+1.);
      hke4->Fill(K);

      // Recover angles
      tx[1] = TMath::ATan(a[1]);
      ty[1] = TMath::ATan(b[1]);

//      Double_t flighttime = dt[1] / kappa;
//      h4time->Fill(flighttime);

//      hFwrdMxy->Fill(foutput[0]*1000.,foutput[2]*1000.);
//      hFwrdMtxty->Fill(tx[1]*1000.,ty[1]*1000.);

      // drift to CRDC 2
      x[4] = x[1]+c2z*a[1]; tx[4]=tx[1];
      y[4] = y[1]+c2z*b[1]; ty[4]=ty[1];

//  c1x = z1*a[1]; c1y = z1*b[1]; hxyC1->Fill(c1x*1000.,c1y*1000.);

      // Transform back.

      x[2] = xCoefI[0]*x[1] + xCoefI[1]*a[1] + xCoefI[2]*d[1] + xCoefI[3]*x[1]*x[1] + xCoefI[4]*x[1]*a[1] + xCoefI[5]*a[1]*a[1] + xCoefI[6]*y[1]*y[1] + xCoefI[7]*y[1]*b[1] + xCoefI[8]*x[1]*d[1] + xCoefI[9]*a[1]*d[1] + xCoefI[10]*b[1]*b[1] + xCoefI[11]*d[1]*d[1] + xCoefI[12]*x[1]*x[1]*x[1] + xCoefI[13]*x[1]*x[1]*a[1] + xCoefI[14]*x[1]*a[1]*a[1] + xCoefI[15]*a[1]*a[1]*a[1] + xCoefI[16]*x[1]*y[1]*y[1] + xCoefI[17]*a[1]*y[1]*y[1] + xCoefI[18]*x[1]*y[1]*b[1] + xCoefI[19]*a[1]*y[1]*b[1] + xCoefI[20]*x[1]*x[1]*d[1] + xCoefI[21]*x[1]*a[1]*d[1] + xCoefI[22]*a[1]*a[1]*d[1] + xCoefI[23]*y[1]*y[1]*d[1] + xCoefI[24]*x[1]*b[1]*b[1] + xCoefI[25]*a[1]*b[1]*b[1] + xCoefI[26]*y[1]*b[1]*d[1] + xCoefI[27]*x[1]*d[1]*d[1] + xCoefI[28]*a[1]*d[1]*d[1] + xCoefI[29]*b[1]*b[1]*d[1] + xCoefI[30]*d[1]*d[1]*d[1];

      a[2] = aCoefI[0]*x[1] + aCoefI[1]*a[1] + aCoefI[2]*d[1] + aCoefI[3]*x[1]*x[1] + aCoefI[4]*x[1]*a[1] + aCoefI[5]*a[1]*a[1] + aCoefI[6]*y[1]*y[1] + aCoefI[7]*y[1]*b[1] + aCoefI[8]*x[1]*d[1] + aCoefI[9]*a[1]*d[1] + aCoefI[10]*b[1]*b[1] + aCoefI[11]*d[1]*d[1] + aCoefI[12]*x[1]*x[1]*x[1] + aCoefI[13]*x[1]*x[1]*a[1] + aCoefI[14]*x[1]*a[1]*a[1] + aCoefI[15]*a[1]*a[1]*a[1] + aCoefI[16]*x[1]*y[1]*y[1] + aCoefI[17]*a[1]*y[1]*y[1] + aCoefI[18]*x[1]*y[1]*b[1] + aCoefI[19]*a[1]*y[1]*b[1] + aCoefI[20]*x[1]*x[1]*d[1] + aCoefI[21]*x[1]*a[1]*d[1] + aCoefI[22]*a[1]*a[1]*d[1] + aCoefI[23]*y[1]*y[1]*d[1] + aCoefI[24]*x[1]*b[1]*b[1] + aCoefI[25]*a[1]*b[1]*b[1] + aCoefI[26]*y[1]*b[1]*d[1] + aCoefI[27]*x[1]*d[1]*d[1] + aCoefI[28]*a[1]*d[1]*d[1] + aCoefI[29]*b[1]*b[1]*d[1] + aCoefI[30]*d[1]*d[1]*d[1];

      y[2] = yCoefI[0]*y[1] + yCoefI[1]*b[1] + yCoefI[2]*x[1]*y[1] + yCoefI[3]*a[1]*y[1] + yCoefI[4]*x[1]*b[1] + yCoefI[5]*a[1]*b[1] + yCoefI[6]*y[1]*d[1] + yCoefI[7]*b[1]*d[1] + yCoefI[8]*x[1]*x[1]*y[1] + yCoefI[9]*x[1]*a[1]*y[1] + yCoefI[10]*a[1]*a[1]*y[1] + yCoefI[11]*y[1]*y[1]*y[1] + yCoefI[12]*x[1]*x[1]*b[1] + yCoefI[13]*x[1]*a[1]*b[1] + yCoefI[14]*a[1]*b[1]*b[1] + yCoefI[15]*y[1]*y[1]*b[1] + yCoefI[16]*x[1]*y[1]*d[1] + yCoefI[17]*a[1]*y[1]*d[1] + yCoefI[18]*y[1]*b[1]*b[1] + yCoefI[19]*x[1]*b[1]*d[1] + yCoefI[20]*a[1]*b[1]*d[1] + yCoefI[21]*y[1]*d[1]*d[1] + yCoefI[22]*b[1]*b[1]*b[1] + yCoefI[23]*b[1]*d[1]*d[1];

      b[2] = bCoefI[0]*y[1] + bCoefI[1]*b[1] + bCoefI[2]*x[1]*y[1] + bCoefI[3]*a[1]*y[1] + bCoefI[4]*x[1]*b[1] + bCoefI[5]*a[1]*b[1] + bCoefI[6]*y[1]*d[1] + bCoefI[7]*b[1]*d[1] + bCoefI[8]*x[1]*x[1]*y[1] + bCoefI[9]*x[1]*a[1]*y[1] + bCoefI[10]*a[1]*a[1]*y[1] + bCoefI[11]*y[1]*y[1]*y[1] + bCoefI[12]*x[1]*x[1]*b[1] + bCoefI[13]*x[1]*a[1]*b[1] + bCoefI[14]*a[1]*b[1]*b[1] + bCoefI[15]*y[1]*y[1]*b[1] + bCoefI[16]*x[1]*y[1]*d[1] + bCoefI[17]*a[1]*y[1]*d[1] + bCoefI[18]*y[1]*b[1]*b[1] + bCoefI[19]*x[1]*b[1]*d[1] + bCoefI[20]*a[1]*b[1]*d[1] + bCoefI[21]*y[1]*d[1]*d[1] + bCoefI[22]*b[1]*b[1]*b[1] + bCoefI[23]*b[1]*d[1]*d[1];

      d[2] = d[1];


      // itracked back to target
      tx[2] = TMath::ATan(a[2]);
      ty[2] = TMath::ATan(b[2]);



      if(x[1]< 0.15 && y[1]< 0.15 && x[4]< 0.15 && y[4]< 0.15 &&
         x[1]>-0.15 && y[1]>-0.15 && x[4]>-0.15 && y[4]>-0.15)
      {// IF FOR CRDC ACCEPTANCES: based on tracking done here, NOT in st_mona
      hxy2->Fill(1000.*x[0],1000.*y[0]); htxty2->Fill(1000.*tx[0],1000.*ty[0]);
      hxy2i->Fill(1000.*x[2],1000.*y[2]); htxty2i->Fill(1000.*tx[2],1000.*ty[2]);
      hxy4->Fill(1000.*x[1],1000.*y[1]); htxty4->Fill(1000.*tx[1],1000.*ty[1]);
      hxy6->Fill(1000.*x[4],1000.*y[4]); htxty6->Fill(1000.*tx[4],1000.*ty[4]);
      // Post-target fragment calculations
      Double_t b2ke = b2p0Ekin/fA;
      b2ke += (t3eloss/fA);// energy add back
      hfke2->Fill(b2ke);

      Double_t fgam2 = (b2ke/amu_M) + 1.;
      if(fgam2>0.)
        {
        Double_t fbet2 = 1. - 1./(fgam2*fgam2);
        Double_t fvel2 = C * sqrt(fbet2);

        hfvel2->Fill(fvel2);
        }

      /* Transform with partial inverse matrix
       * input[0] = crdc1.x
       * input[1] = crdc1.tx
       * input[2] = crdc1.y
       * input[3] = crdc1.ty
       *
       * at the target:
       * output[0] = tx
       * output[1] = y
       * output[2] = ty
       * output[3] = de
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
      hfvelC->Fill(fvelPI);
      }

      hdeC->Fill(K);
      htxtyC->Fill(output[0]*1000.,output[2]*1000.);



    /* Neutrons !! */
    Double_t n0ke    = b2p1Ekin;
    Double_t n0gamma = (n0ke / amu_M) + 1.;
//    Double_t n0gamma = (b2p1Ekin/n_M)+1.;
//    Double_t n0ke    = amu_M*(n0gamma-1.);
    Double_t n0beta  = 1. - 1./(n0gamma*n0gamma);
    Double_t n0vel   = C * sqrt(n0beta);
    hn0ke->Fill(n0ke); hn0v->Fill(n0vel);


    /* Fragment velocity */
    // Determine ToF target scint to crdc2 //
    Double_t c2path = (b6p0path*100.);// + 102.3239;
//    Double_t fthin  = (c2path+102.3239) + (90.2/cos(tx[1]));
    Double_t fgamma = ((b2p0Ekin/fA) / amu_M) + 1.0;
    Double_t fbeta  = 1. - (1./(fgamma*fgamma));
    Double_t fvel   = C * sqrt(fbeta);
//    Double_t sToF   = fthin/fvel;
    Double_t sToF   = c2path/fvel;
    // Estimate distance from crdc 2 x //
//    Double_t fdist = (x[4]*1000.)*0.06832 + 425.1;
//    Double_t fdist = (x[4]*1000.)*0.06832 + 322.7;
    Double_t fdist = (x[4]*1000.)*0.06832 + 322.7;
    Double_t fvelocity = fdist/(sToF + res);
    Double_t fbeta0    = fvelocity/C;
    Double_t fgamma0   = 1./sqrt(1. - (fbeta0*fbeta0));
    Double_t fkenergy0 = (amu_M*(fgamma0-1.));//MeV/u
    fkenergy0         += t3eloss/fA;// add back O-24 energy loss through 1/2 Be3
    fgamma0            = fkenergy0 / amu_M + 1.;
    fbeta0             = 1. - (1./(fgamma0*fgamma0));
    fvelocity          = sqrt(fbeta0)*C;

    /* ADD ENERGY ADDBACK HERE */
//    Double_t fkenergy  = fkenergy0 + (t3eloss/fA);// MeV/u

/**/
    hsToF->Fill(sToF);
    hsToFres->Fill(sToF + res);
    hfdist->Fill(fdist);
    hc2path->Fill(c2path);
    hfvelT->Fill(fvelocity);
    hfkeT->Fill(fkenergy0);
    hc2pathdist->Fill(fdist,c2path);

    Double_t vrel = n0vel - fvelocity;
    hvrT->Fill(vrel);
    vrel = n0vel - fvelPI;
    hvrC->Fill(vrel);
    vrel = n0vel - fvel2;
    hvr2->Fill(vrel);


    }// END IF FOR CRDC ACCEPTANCES


   }/* ----- END LOOP OVER ENTRIES ----- */

  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.22);
  gStyle->SetStatH(0.15);
  
  // For scaling
  Double_t max1,max2;

  /* Plot fragment profile after target */
  TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1);
  c1->cd(1); hxy2->Draw("COLZ");
  c1->cd(2); htxty2->Draw("COLZ");

  /* Plot fragment profile from full
   * inverse tracking back to target
  */
  TCanvas *c8 = new TCanvas("c8","c8",1000,500);
  c8->Divide(2,1);
  c8->cd(1); hxy2i->Draw("COLZ");
  c8->cd(2); htxty2i->Draw("COLZ");
  

  // Plot fragment profile on CRDC 1 (DV)
  TCanvas *c2 = new TCanvas("c2","c2",1000,500);
  c2->Divide(2,1);
  c2->cd(1); hxy4->Draw("COLZ");
  c2->cd(2); htxty4->Draw("COLZ");

  /* Plot fragment profile on CRDC 1 (ST)*/
  TCanvas *c3 = new TCanvas("c3","c3",1000,500);
  c3->Divide(2,1);
  c3->cd(1); hxy4o->Draw("COLZ");
  c3->cd(2); htxty4o->Draw("COLZ");

  /* Plot fragment profile on CRDC 1 (ST here) 
  TCanvas *c7 = new TCanvas("c7","c7",1000,500);
  c7->Divide(2,1);
  c7->cd(1); hFwrdMxy->Draw("COLZ");
  c7->cd(2); hFwrdMtxty->Draw("COLZ");
*/


  // Plot fragment profile on CRDC 2 (DV)
  TCanvas *c4 = new TCanvas("c4","c4",1000,500);
  c4->Divide(2,1);
  c4->cd(1); hxy6->Draw("COLZ");
  c4->cd(2); htxty6->Draw("COLZ");

  /* Plot fragment profile on CRDC 2 (ST)*/
  TCanvas *c5 = new TCanvas("c5","c5",1000,500);
  c5->Divide(2,1);
  c5->cd(1); hxy6o->Draw("COLZ");
  c5->cd(2); htxty6o->Draw("COLZ");


  // Compare tx ty: post-tgt, inv itracked, p-inv itracked
  TCanvas *c6 = new TCanvas("c6","c6",1500,500);
  c6->Divide(3,1);
  c6->cd(1); htxty2->Draw("COLZ");
  c6->cd(2); htxty2i->Draw("COLZ");
  c6->cd(3); htxtyC->Draw("COLZ");

/**/

  // Check number of entires before scaling
  cout << "Nentries(KE): " << endl;
  printf("  %6.0d %6.0d %6.0d %6.0d\n",hfke2->GetEntries(),hdeC->GetEntries(),
  hfkeT->GetEntries(),hn0ke->GetEntries());
  cout << endl << "Nentries(vel): " << endl;
  printf("  %6.0d %6.0d %6.0d %6.0d\n",hfvel2->GetEntries(),hfvelC->GetEntries(),
  hfvelT->GetEntries(),hn0v->GetEntries());

  // Plot fragment vel and KE at target/reconstructed
  TCanvas *c20 = new TCanvas("c20","c20",1000,500);
  c20->Divide(2,1);
  // KE: post-tgt, p-inv recon, ToF recon
  TPaveText *csb[13]; Int_t hcolors[4] = {1,28,2,4};
  ModHistogram(hfke2,hcolors[0],4); ModHistogram(hdeC,hcolors[1],1);
  ModHistogram(hfkeT,hcolors[2],1); ModHistogram(hn0ke,hcolors[3],1);
  csb[0] = CustomStatsBox(hfke2,1,hcolors[0],0);
  csb[1] = CustomStatsBox(hdeC, 1,hcolors[1],1);
  csb[2] = CustomStatsBox(hfkeT,1,hcolors[2],2);
  csb[3] = CustomStatsBox(hn0ke,1,hcolors[3],3);
  hfke2->SetLineStyle(2);
  c20->cd(1); hfke2->Draw(); hdeC->Draw("SAME"); hfkeT->Draw("SAME");
  hn0ke->Draw("SAME");
  for(int i=0;i<4;i++){csb[i]->Draw("SAME");}
  ModHistogram(hfvel2,hcolors[0],4); ModHistogram(hfvelC,hcolors[1],1);
  ModHistogram(hfvelT,hcolors[2],1); ModHistogram(hn0v,hcolors[3],1);
  csb[4] = CustomStatsBox(hfvel2,1,hcolors[0],0);
  csb[5] = CustomStatsBox(hfvelC,1,hcolors[1],1);
  csb[6] = CustomStatsBox(hfvelT,1,hcolors[2],2);
  csb[7] = CustomStatsBox(hn0v  ,1,hcolors[3],3);
  hfvel2->SetLineStyle(2);
  c20->cd(2);hfvel2->Draw();hfvelC->Draw("SAME");hfvelT->Draw("SAME");
  hn0v->Draw("SAME");
  for(int i=4;i<8;i++){csb[i]->Draw("SAME");}

  cout << endl << "Nentries(vrel): " << endl;
  printf("  %6.0d %6.0d %6.0d\n",hvr2->GetEntries(),hvrC->GetEntries(),
  hvrT->GetEntries());

  // Plot relative velocities
  TCanvas *c21 = new TCanvas("c21","c21",700,500);
  ModHistogram(hvr2,hcolors[0],4); ModHistogram(hvrC,hcolors[1],1);
  ModHistogram(hvrT,hcolors[2],1);
  csb[8]  = CustomStatsBox(hvr2,1,hcolors[0],0);
  csb[9]  = CustomStatsBox(hvrC,1,hcolors[1],1);
  csb[10] = CustomStatsBox(hvrT,1,hcolors[2],2);
  hvr2->SetLineStyle(2);
  hvr2->Draw(); hvrC->Draw("SAME"); hvrT->Draw("SAME");
//  hvrC->Draw(); hvrT->Draw("SAME");
  for(int i=8;i<11;i++){csb[i]->Draw("SAME");}



//  hvrT->Fit("gaus");
  /* Check statistics
  CheckHistStats(hvr2);
  CheckHistStats(hvrT);
*/


  /* Check Fragment KE ToF hack stuff */
  TCanvas *c30 = new TCanvas("c30","c30",1000,500);
  c30->Divide(2,1);
  c30->cd(1); hfdist->Draw();
  c30->cd(2); hc2path->Draw();

  TCanvas *c31 = new TCanvas("c31","c31",700,500);
  hc2pathdist->Draw("COLZ");

  TCanvas *c32 = new TCanvas("c32","c32",700,500);
  ModHistogram(hsToF,1,2); ModHistogram(hsToFres,2,2);
  csb[11] = CustomStatsBox(hsToF,1,1,0);
  csb[12] = CustomStatsBox(hsToFres,1,2,1);
  hsToF->Draw();
  hsToFres->Draw("SAME");
  for(int i=11;i<13;i++){csb[i]->Draw("SAME");}

  DeallocateMatrix(Coeff,nlines,ncoef);
  DeallocateMatrix(Power,nlines,npar);
  DeallocateMatrix(fCoef,fnlines,fncoef);
  DeallocateMatrix(fPower,fnlines,fncoef);

}
