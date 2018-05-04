#define STanalysis_cxx
#include "STanalysis.h"
#include <TStyle.h>
#include <TCanvas.h>

void STanalysis::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L STanalysis.C
//      Root > STanalysis t
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
  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("b1p0Ekin",1);
  fChain->SetBranchStatus("b2p0dE",1);
  fChain->SetBranchStatus("b2p0x",1);
  fChain->SetBranchStatus("b2p0y",1);
  fChain->SetBranchStatus("b3p0Ekin",1);
  fChain->SetBranchStatus("b3p0dE",1);
  fChain->SetBranchStatus("b3p0TP",1);
  fChain->SetBranchStatus("b4p0dE",1);
  fChain->SetBranchStatus("b4p0x",1);
  fChain->SetBranchStatus("b4p0y",1);
  fChain->SetBranchStatus("b5p0Ekin",1);
  fChain->SetBranchStatus("b5p0dE",1);
  fChain->SetBranchStatus("b5p0TP",1);
  fChain->SetBranchStatus("b6p0dE",1);
  fChain->SetBranchStatus("b6p0x",1);
  fChain->SetBranchStatus("b6p0y",1);
  fChain->SetBranchStatus("b7p0Ekin",1);
  fChain->SetBranchStatus("b7p0dE",1);
  fChain->SetBranchStatus("b7p0TP",1);
  fChain->SetBranchStatus("b8p0Ekin",1);
  fChain->SetBranchStatus("b8p0dE",1);
  fChain->SetBranchStatus("b8p0x",1);
  fChain->SetBranchStatus("b8p0y",1);
  fChain->SetBranchStatus("b10p0x",1);
  fChain->SetBranchStatus("b10p0tx",1);
  fChain->SetBranchStatus("b10p0y",1);
  fChain->SetBranchStatus("b10p0ty",1);
  fChain->SetBranchStatus("b12p0x",1);
  fChain->SetBranchStatus("b12p0tx",1);
  fChain->SetBranchStatus("b12p0y",1);
  fChain->SetBranchStatus("b12p0ty",1);
  fChain->SetBranchStatus("b13pgmultiplicity",1);
  fChain->SetBranchStatus("b13p1Ekin",1);
  fChain->SetBranchStatus("b13pg1x",1);
  fChain->SetBranchStatus("b13pg1y",1);
  fChain->SetBranchStatus("b13pg1z",1);
  fChain->SetBranchStatus("b13pg1t",1);
  fChain->SetBranchStatus("b13pg1light",1);
  fChain->SetBranchStatus("b13pg2t",1);
  fChain->SetBranchStatus("b13pg2light",1);

  // Physical Constants
  const Double_t C = 29.9792458;// [cm/ns]
  const Double_t amuM = 931.494088;// [MeV/c^2]
  const Double_t neutronMass = 939.56536;// [MeV/c^2]
  const Double_t nMamu= 1.0086650813;// [amu]
  const Double_t neutronBox = 1.00;// [m] neutron position gate
  const Double_t bp = 3.445;//[Tm] Sweeper production setting

  TRandom3 *r3 = new TRandom3();

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {// LOOP OVER ENTRIES
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    Reset();
    // Drift to thin
    const Double_t zThin = 0.8605;// [m]
    thin.x = b12p0x + zThin * tan(b12p0tx);// [m]
    thin.y = b12p0y + zThin * tan(b12p0ty);// [m]
    thinxy->Fill(1000.*thin.x,1000.*thin.y);

    if(b2p0x<0.02 && b2p0y>-0.017 &&
       thin.x>-0.275 && thin.x<0.275 && thin.y>-0.275 && thin.y<0.275 &&
       b13pg1x>-1.*neutronBox && b13pg1x<neutronBox &&
       b13pg1y>-1.*neutronBox && b13pg1y<neutronBox){// GLOBAL si && thin && MoNA acceptance
    if(b13pg1t>0){// MoNA 1n efficiency

// CRDC acceptance
//    if(b2p0x<0.02 && b2p0y>-0.017 &&
//       b10p0x<0.15 && b10p0x>-0.15 && b10p0y<0.1 && b12p0y>-0.1 &&
//       b12p0x<0.15 && b12p0x>-0.15 && b12p0y<0.1 && b12p0y>-0.1 &&
//       b13pg1x>-1.*neutronBox && b13pg1x<neutronBox &&
//       b13pg1y>-1.*neutronBox && b13pg1y<neutronBox){// GLOBAL si && crdc && MoNA acceptance

    if (
        (left->IsInside(b12p0x*1000.,b10p0x*1000.) ||
        mid->IsInside(b12p0x*1000.,b10p0x*1000.)  ||
        right->IsInside(b12p0x*1000.,b10p0x*1000.))){// GLOBAL crdc efficiency gates

    // Reject 26% of events in the range -36 mm < c2x < 10 mm
//    Double_t rejectThreshold = 1.;
//    if (b12p0x > -0.036 && b12p0x < 0.010){
//      rejectThreshold = 0.74;
//    }
    // Reject 50% of events in the range -90 mm < c2x < -50 mm
    Double_t rejectThreshold = 1.;
    if (b12p0x > -0.100 && b12p0x < -0.050){
      rejectThreshold = 0.50;
    }

    Double_t randomNumber = r3->Uniform(1.);
    if(randomNumber <=rejectThreshold){// GLOBAL isoID rejection

    /* --- Do analysis stuff --- */
    // beam velocity
    beam.gamma    = b1p0Ekin/(m_beamA*amuM) + 1.;
    beam.beta     = sqrt(1. - 1./(beam.gamma*beam.gamma));
    beam.v = beam.beta * C;
    hbeamV->Fill(beam.v);
    // fill BEAM structure

    // Silicon PSD positions and energy loss
    Double_t siDE[4];
    siDE[0] = b2p0dE+(r3->Gaus(0.,m_siDEres));
    siDE[1] = b4p0dE+(r3->Gaus(0.,m_siDEres));
    siDE[2] = b6p0dE+(r3->Gaus(0.,m_siDEres));
    siDE[3] = b8p0dE+(r3->Gaus(0.,m_siDEres));

    si0.de = siDE[0]; si1.de = siDE[1]; si2.de = siDE[2]; si3.de = siDE[3];
    si0.x  = b2p0x*1000.;si1.x  = b4p0x*1000.;si2.x  = b6p0x*1000.;si3.x  = b8p0x*1000.;
    si0.y  = b2p0y*1000.;si1.y  = b4p0y*1000.;si2.y  = b6p0y*1000.;si3.y  = b8p0y*1000.;

    Double_t psdx[4],psdy[4];
    psdx[0] = b2p0x; psdx[1] = b4p0x; psdx[2] = b6p0x; psdx[3] = b8p0x;
    psdy[0] = b2p0y; psdy[1] = b4p0y; psdy[2] = b6p0y; psdy[3] = b8p0y;
    for(int i=0;i<4;i++){
      sixy[i]->Fill(1000.*psdx[i],1000.*psdy[i]);
      side[i]->Fill(siDE[i]);
    }

    // CRDC positions
    crdcxy[0]->Fill(b10p0x*1000.,b10p0y*1000.);
    crdcxy[1]->Fill(b12p0x*1000.,b12p0y*1000.);
    crdctxty->Fill(b12p0tx*1000.,b12p0ty*1000.);
    crdc12x->Fill(b12p0x*1000.,b10p0x*1000.);
    crdcxtx->Fill(b12p0x*1000.,b12p0tx*1000.);
    // fill crdc data structures
    crdc1.x = b10p0x*1000.; crdc1.y = b10p0y*1000.;
    crdc1.tx = b10p0tx*1000.; crdc1.ty = b10p0ty*1000.;
    crdc2.x = b12p0x*1000.; crdc2.y = b12p0y*1000.;
    crdc2.tx = b12p0tx*1000.; crdc2.ty = b12p0ty*1000.;

    // Target ID
    for(int i=0;i<3;i++){tgtID[i]->Fill(siDE[i],siDE[i+1]);}

    // GEANT neutron velocity
    n0.x = 100.*b13pg1x; n0.y = 100.*b13pg1y; n0.z = 100.*b13pg1z; n0.t = b13pg1t;
    n0.dist     = sqrt(b13pg1x*b13pg1x + b13pg1y*b13pg1y + b13pg1z*b13pg1z);
    n0.cosTheta = b13pg1z / n0.dist;
    n0.v        = n0.dist*100. / b13pg1t;
    n0.beta     = n0.v/C;
    n0.gamma    = 1./sqrt(1. - n0.beta*n0.beta);
    n0.P        = (nMamu) * n0.beta * n0.gamma;
    n0.E        = (nMamu) * n0.gamma;
    n0.light    = b13pg1light;

    sumLight0->Fill(b13pg1light);
    if(b13pg2light>0){sumLight1->Fill(b13pg2light);}
    sumMult->Fill(b13pgmultiplicity);



    // Fragment Velocity
    frag.dist              =-9.;
    frag.gamma0            = b8p0Ekin/(m_fragA*amuM) + 1.;
    frag.beta0             = sqrt(1. - 1./(frag.gamma0*frag.gamma0));
    frag.v0                = frag.beta0*C;
    frag.ke0               = b8p0Ekin;
    Double_t fSi3Velocity = SiVelocity( Si3raw(b8p0dE) );// the Si 3 velocity correction is on the raw anode signal
    Double_t fracBrhoC2x  = (6.50072e-4)*(1000.*b12p0x) - (8.14186e-4);
    frag.Bp               = fracBrhoC2x*bp + bp;
    Double_t betaGamma0   = (frag.Bp / 3.107)*m_fragZ / m_fragA;
    Double_t bpGamma0     = sqrt(betaGamma0*betaGamma0 + 1.);
    Double_t bpBeta0      = betaGamma0/sqrt(1. + betaGamma0*betaGamma0);
    hvelBp->Fill(bpBeta0*C);// velocity from fracBp
    hvelsm->Fill(frag.v0);// simulated fragment velocity



    Double_t Addback=-77;
    Double_t fragBeta,fragGamma,fragVelocity;
    target = 9;
    // ... per target
    if(b4p0dE<b4dEgate){
      target = 1;
      Addback = m_addback[0];
      // FILL HISTOGRAMS
      hnvel[0]->Fill(n0.v);
      hfvel[0]->Fill(fragVelocity);
      hsvel[0]->Fill(fSi3Velocity);
      hrxnpos[0]->Fill(b3p0TP);
      hrvel[0]->Fill(n0.v - fragVelocity);
      hedecay[0]->Fill(edecay);
      // calculate velocity @ rxn point
      fragGamma    = (b3p0Ekin + b3p0dE)/(m_fragA*amuM) + 1.;
      fragBeta     = sqrt(1. - 1./(fragGamma*fragGamma));
      fragVelocity = fragBeta*C;
      hvrxp[0]->Fill(fragVelocity);
      h0lgt[0]->Fill(b13pg1light);
      if(b13pg2t>0){h1lgt[0]->Fill(b13pg2light);}
      hmult[0]->Fill(b13pgmultiplicity);
    }
    else if(b4p0dE>b4dEgate && b6p0dE<b6dEgate){
      target = 2;
      Addback = m_addback[1];
      hnvel[1]->Fill(n0.v);
      hfvel[1]->Fill(frag.v);
      hsvel[1]->Fill(fSi3Velocity);
      hrxnpos[1]->Fill(b5p0TP);
      hrvel[1]->Fill(n0.v - frag.v);
      hedecay[1]->Fill(edecay);
      // calculate velocity @ rxn point
      fragGamma    = (b5p0Ekin + b5p0dE)/(m_fragA*amuM) + 1.;
      fragBeta     = sqrt(1. - 1./(fragGamma*fragGamma));
      fragVelocity = fragBeta*C;
      hvrxp[1]->Fill(fragVelocity);
      h0lgt[1]->Fill(b13pg1light);
      if(b13pg2t>0){h1lgt[1]->Fill(b13pg2light);}
      hmult[1]->Fill(b13pgmultiplicity);
    }
    else if(b6p0dE>b6dEgate){
      target = 3;
      Addback = m_addback[2];
      hnvel[2]->Fill(n0.v);
      hfvel[2]->Fill(fragVelocity);
      hsvel[2]->Fill(fSi3Velocity);
      hrxnpos[2]->Fill(b7p0TP);
      hrvel[2]->Fill(n0.v - fragVelocity);
      hedecay[2]->Fill(edecay);
      // calculate velocity @ rxn point
      fragGamma    = (b7p0Ekin + b7p0dE)/(m_fragA*amuM) + 1.;
      fragBeta     = sqrt(1. - 1./(fragGamma*fragGamma));
      fragVelocity = fragBeta*C;
      hvrxp[2]->Fill(fragVelocity);
      h0lgt[2]->Fill(b13pg1light);
      if(b13pg2t>0){h1lgt[2]->Fill(b13pg2light);}
      hmult[2]->Fill(b13pgmultiplicity);
    }
    else{target=9;}

    frag.ke= b8p0Ekin+Addback;
    frag.gamma    = (frag.ke)/(m_fragA*amuM) + 1.;
    frag.beta     = sqrt(1. - 1./(frag.gamma*frag.gamma));
    frag.v = frag.beta*C;
    frag.P = m_fragA*frag.beta*frag.gamma;;
    frag.E = m_fragA*frag.gamma;
    // TWO-BODY DECAY ENERGY
    edecay = -77.;
    edecay = m_fragA*m_fragA + nMamu*nMamu + 2.*(frag.E*n0.E - frag.P*n0.P*n0.cosTheta);
    if(edecay>0&&target<=3&&Addback>0){
      edecay = sqrt(edecay) - m_fragA - nMamu;
      edecay*= amuM;
    }
    else if(edecay>0&&target>3){edecay=-66;}
    else{edecay = -77;}


  }// Close isoID rejection
  }// Close crdc efficiency gate
  }// MoNA 1n efficiency
  }// Close acceptance gate
    // if (Cut(ientry) < 0) continue;
  if(m_ATinit){at->Fill();}
  }// CLOSE LOOP OVER ENTRIES


  sumVR = (TH1D*)hrvel[0]->Clone();
  sumVR->Add(hrvel[1],1.); sumVR->Add(hrvel[2],1.);
  sumED = (TH1D*)hedecay[0]->Clone();
  sumED->Add(hedecay[1],1.); sumED->Add(hedecay[2],1.);
}// END STanalysis::Loop()


void STanalysis::Reset(){
  beam.beta=-1;
  beam.gamma=-1;
  beam.v=-1;
  si0.x=-1; si0.y=-1; si0.de=-1;
  si1.x=-1; si1.y=-1; si1.de=-1;
  si2.x=-1; si2.y=-1; si2.de=-1;
  si3.x=-1; si3.y=-1; si3.de=-1;
  crdc1.x=-1;crdc1.y=-1;crdc1.tx=-1;crdc1.ty=-1;crdc1.path=-1;
  crdc2.x=-1;crdc2.y=-1;crdc2.tx=-1;crdc2.ty=-1;crdc2.path=-1;
  thin.x=-1;thin.y=-1;
  n0.x=-1;n0.y=-1;n0.z=-1;n0.t=-1;n0.dist=-1;
  n0.cosTheta=-1;n0.v=-1;n0.beta=-1;n0.gamma=-1;n0.P=-1;n0.E=-1;
  n0.light=-1;
  frag.dist=-1;frag.beta0=-1;frag.gamma0=-1;frag.v0=-1;frag.ke0=-1;
  frag.Bp=-1;frag.beta=-1;frag.gamma=-1;frag.v=-1;frag.ke=-1;frag.E=-1;
  frag.P=-1;
}


TH1D * STanalysis::GetNeutronVelocity(TH1D *h[3]){
  for(int i=0;i<3;i++){h[i] = hnvel[i];}
}


void STanalysis::PlotIncidentBeam(){
  TCanvas *c00 = new TCanvas("c00","c00",1000,800);c00->Divide(2,2);
  c00->cd(3); hbeamV->Draw();
  c00->cd(2); sixy[0]->Draw("COLZ");
  c00->cd(4); TH1D *si0x = (TH1D*)sixy[0]->ProjectionX("si0x"); si0x->Draw();
  c00->cd(1); TH1D *si0y = (TH1D*)sixy[0]->ProjectionY("si0y"); si0y->Draw();
}

void STanalysis::PlotSiPositions(){
  TCanvas *c0[4];
  TH1D *px[4];
  TH1D *py[4];
  for(int i=0;i<4;i++){
    c0[i] = new TCanvas(Form("c0_%i",i),Form("c0_%i",i),1000,800);
    c0[i]->Divide(2,2);
    c0[i]->cd(2); sixy[i]->Draw("COLZ");
    c0[i]->cd(1);
    py[i] = (TH1D*)sixy[i]->ProjectionY();
    py[i]->Draw();
    c0[i]->cd(4);
    px[i] = (TH1D*)sixy[i]->ProjectionX();
    px[i]->Draw();
  }
}


void STanalysis::PlotCRDC(){
  TCanvas *c1 = new TCanvas("c1","c1",1000,400);c1->Divide(2,1);
  for(int i=0;i<2;i++){c1->cd(i+1); crdcxy[i]->Draw("COLZ");}

  TCanvas *c2 = new TCanvas("c2","c2",1500,400);c2->Divide(3,1);
  c2->cd(1); crdctxty->Draw("COLZ");
  c2->cd(2); crdc12x->Draw("COLZ");
  c2->cd(3); crdcxtx->Draw("COLZ");

  TCanvas *c3 = new TCanvas("c3","c3",1000,800);c3->Divide(2,2);
  c3->cd(2); thinxy->Draw("COLZ");
  c3->cd(4); TH1D *projx = (TH1D*)thinxy->ProjectionX(); projx->Draw();
  c3->cd(1); TH1D *projy = (TH1D*)thinxy->ProjectionY(); projy->Draw();
}


void STanalysis::PlotTargetID(){
  TCanvas *c2 = new TCanvas("c2","c2",1500,400);c2->Divide(3,1);
  for(int i=0;i<3;i++){c2->cd(i+1); tgtID[i]->Draw("COLZ");}
}


void STanalysis::PlotNeutronVelocity(){
  TCanvas *c4 = new TCanvas("c4","c4",1500,400);c4->Divide(3,1);
  TCanvas *c4a = new TCanvas("c4a","c4a",1500,800);c4a->Divide(3,2);
  TCanvas *c4b = new TCanvas("c4b","c4b",1500,800);c4b->Divide(3,2);
  TCanvas *c4c = new TCanvas("c4c","c4c",1000,400);c4c->Divide(2,1);
  for(int i=0;i<3;i++){
    c4->cd(i+1);hnvel[i]->Draw();
    c4a->cd(i+1);h0lgt[i]->Draw();
    c4a->cd(i+4);h1lgt[i]->Draw();
    c4b->cd(i+1);hmult[i]->Draw();
  }
  c4b->cd(4); sumMult->Draw();
  c4c->cd(1); sumLight0->Draw();
  c4c->cd(2); sumLight1->Draw();
}


void STanalysis::PlotFragmentVelocity(){
  TCanvas *c3 = new TCanvas("c3","c3",1500,400);c3->Divide(3,1);
  for(int i=0;i<3;i++){c3->cd(i+1); hfvel[i]->Draw();}
}


void STanalysis::PlotSiEloss(){
  TCanvas *c5 = new TCanvas("c5","c5",1800,400);c5->Divide(4,1);
  for(int i=0;i<4;i++){c5->cd(i+1); side[i]->Draw();}
}


void STanalysis::PlotRxnPosition(){
  TCanvas *c6 = new TCanvas("c6","c6",1500,400);c6->Divide(3,1);
  for(int i=0;i<3;i++){c6->cd(i+1); hrxnpos[i]->Draw("PE1][");}
  TCanvas *c6a = new TCanvas("c6a","c6a",1500,400);c6a->Divide(3,1);
  for(int i=0;i<3;i++){c6a->cd(i+1); hvrxp[i]->Draw();}
}


void STanalysis::PlotRelativeVelocity(){
  TCanvas *c7 = new TCanvas("c7","c7",1500,800);c7->Divide(3,2);
  for(int i=0;i<3;i++){
    c7->cd(i+1);hrvel[i]->Draw();
    c7->cd(i+4);hedecay[i]->Draw();
  }
  TCanvas *c8 = new TCanvas("c8","c8",1000,400);c8->Divide(2,1);
  c8->cd(1); sumVR->Draw(); c8->cd(2); sumED->Draw();
}


void STanalysis::WriteHistograms(){
  TString histOutFile = Form("/projects/e15118/redpath/simulation/histograms/sim%s%s.root",
    m_beam.Data(),m_frag.Data());
  cout << "Histograms will be written to " << histOutFile << endl;

  TFile *hOut = new TFile(histOutFile,"RECREATE");
  // incident beam
  hbeamV->SetName("sbeamV");
  hbeamV->Write();
  // CRDCs
  crdctxty->SetName("scrdctxty");
  crdctxty->Write();
  crdc12x->SetName("scrdc12x");
  crdc12x->Write();
  crdcxtx->SetName("scrdcxtx");
  crdcxtx->Write();
  for(int i=0;i<2;i++){
    crdcxy[i]->SetName(Form("scrdc%ixy",i+1));
    crdcxy[i]->Write();
  }
  // silicon
  for(int i=0;i<4;i++){
    sixy[i]->SetName(Form("ssi%ixy",i));
    sixy[i]->Write();
    side[i]->SetName(Form("ssi%ide",i));
    side[i]->Write();
  }
  // per target
  for(int i=0;i<3;i++){
    hfvel[i]->SetName(Form("sfvel%i",i+1));// target indices
    hfvel[i]->Write();
    hsvel[i]->SetName(Form("sfs3v%i",i+1));// target indices
    hsvel[i]->Write();
    hnvel[i]->SetName(Form("snvel%i",i+1));// target indices
    hnvel[i]->Write();
    hhNxy[i]->SetName(Form("snxy%i",i+1));// target indices
    hhNxy[i]->Write();
    hrvel[i]->SetName(Form("srvel%i",i+1));//target indices
    hrvel[i]->Write();
    h0lgt[i]->SetName(Form("sh0lt%i",i+1));// target indices
    h0lgt[i]->Write();
    h1lgt[i]->SetName(Form("sh1lt%i",i+1));// target indices
    h1lgt[i]->Write();
    hmult[i]->SetName(Form("smult%i",i+1));// target indices
    hmult[i]->Write();
  }

  sumVR->SetName(Form("s%svrSum",m_frag.Data()));sumVR->Write();
  sumED->SetName(Form("s%sedSum",m_frag.Data())),sumED->Write();
  sumMult->SetName("sMultiplicity");sumMult->Write();
  sumLight0->SetName("sLight0");sumLight0->Write();
  sumLight1->SetName("sLight1");sumLight1->Write();

  cout << "Histograms written." << endl;
  hOut->Close();
}


void STanalysis::WriteUnrHistograms(){

  TString histOutFile = Form("/projects/e15118/redpath/simulation/histograms/simUnr%s.root",
    m_beam.Data());
  cout << "Histograms will be written to " << histOutFile << endl;

  TFile *hOut = new TFile(histOutFile,"RECREATE");
  // incident beam
  hbeamV->SetName("sbeamV");
  hbeamV->Write();
  // silicon
  for(int i=0;i<4;i++){
    sixy[i]->SetName(Form("ssi%ixy",i));
    sixy[i]->Write();
    side[i]->SetName(Form("ssi%ide",i));
    side[i]->Write();
  }
  // CRDCs
  for(int i=0;i<2;i++){
    crdcxy[i]->SetName(Form("scrdc%ixy",i+1));
    crdcxy[i]->Write();
  }
  crdctxty->SetName("scrdctxty");
  crdctxty->Write();
  crdc12x->SetName("scrdc12x");
  crdc12x->Write();
  crdcxtx->SetName("scrdcxtx");
  crdcxtx->Write();

  hvelsm->SetName("sV0");
  hvelsm->Write();
  hvelBp->SetName("sV0fracBp");
  hvelBp->Write();

  hOut->Close();

}


/* Here the fragment velocity histograms (per target) are written
 * to a single file across all rxns
*/
void STanalysis::WriteVelocity(TString hFile){
  TString histOutFile = "/projects/e15118/redpath/simulation/histograms/" + hFile;
  cout << "Fragment and neutron velocity histograms will be added to " << histOutFile << endl;

  TFile *hOut = new TFile(histOutFile,"UPDATE");
  for(int i=0;i<3;i++){
    hfvel[i]->SetName(Form("%s%ssfvel%i",m_beam.Data(),m_frag.Data(),i+1));// target indices
    hfvel[i]->Write();
//    hsvel[i]->SetName(Form("%s%sss3v0%i",m_beam.Data(),m_frag.Data(),i+1));// target indices
//    hsvel[i]->Write();
    hnvel[i]->SetName(Form("%s%ssnvel%i",m_beam.Data(),m_frag.Data(),i+1));// target indices
    hnvel[i]->Write();
    hvrxp[i]->SetName(Form("%s%ssfvrp%i",m_beam.Data(),m_frag.Data(),i+1));// target indices
    hvrxp[i]->Write();
    hmult[i]->SetName(Form("%s%ssmult%i",m_beam.Data(),m_frag.Data(),i+1));// target indices
    hmult[i]->Write();
  }

  hOut->Close();
}


void STanalysis::WriteAT(){
//    fChain->Write();
    at->Write();

    outFile->Close();
}


inline Double_t SiVelocity(double x){// ONLY WORKS FOR OXYGEN
  return (1.56838e3) / pow(x,0.677844);
}

inline Double_t Si3raw(double x){
  return (x + 1.523150) / 0.0117145;
}


void UpdateVelocityHistogramFile(){
  STanalysis s;
  s.Loop();
  s.WriteVelocity("velocitySimulation_accpt.root");
//  s.WriteVelocity("velocitySimulation_efficiency.root");
}


void MakeAnalyzedTree(){
  STanalysis s;
  TString b = s.GetBeam();
  TString f = s.GetFragment();
  s.InitAnalysisTree(Form("/mnt/simulations/MoNAsims/O26_analysis/analyzed/%s%sat_0ps.root",
    b.Data(),f.Data()));
  s.Loop();
  s.WriteAT();
}
