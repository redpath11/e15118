#define AnalyzedData_cxx
// The class definition in AnalyzedData.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("AnalyzedData.C")
// Root > T->Process("AnalyzedData.C","some options")
// Root > T->Process("AnalyzedData.C+")
//

#include "AnalyzedData.h"


void AnalyzedData::Begin(TTree *tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

  t_slope = 0.0625;// [ns/cm] mTDC conversion
  bp = 3.445;// [Tm] Sweeper production setting
  C = 29.9792458;// [cm/ns]
  amuM = 931.494088;
  nMamu= 1.0086650813;

  mona_tshift[0] = 1.0;// [ns]
  mona_tshift[1] = 1.0;// [ns]
  mona_tshift[2] = 1.0;// [ns]
//  mona_tshift[1] = 0.136;
//  mona_tshift[2] = 0.284;

  mona_zshift[0] = 0.0;// [cm]
  mona_zshift[1] = 0.0;// [cm]
  mona_zshift[2] = 0.0;// [cm]
//  mona_zshift[1] = -1.676;
//  mona_zshift[2] = -3.352;

  Init(tree);

  SetBeam("F27");
//  SetBeam("Ne29");
  
//  SetFragment("unr");
//  SetFragment("F27");
//  SetFragment("O24");
//  SetFragment("O23");
  SetFragment("O22");
  GraphicalCuts();

  outFile = new TFile(
    Form("/mnt/analysis/e15118/analyzed/%s%s_tshift1.0ns_THLDfixLISAxpos.root",m_beam.Data(),m_fragment.Data()),
    "RECREATE");

  InitAnalyzedTree();

  // Thin calibration
  ReadCorrections();

  // Si dE calibration
  siSlope[0] = 0.0104436; siOffst[0] = -0.859119;
  siSlope[1] = 0.0103797; siOffst[1] = -0.994990;
  siSlope[2] = 0.0119746; siOffst[2] = -1.298600;
  siSlope[3] = 0.0117145; siOffst[3] = -1.523150;
  // Si raw channel mapping
  // left upper  | right upper  | right down     | left down
  index[0][0]=4;  index[0][1]=5;  index[0][2]=6;  index[0][3]=7;
  index[1][0]=0;  index[1][1]=1;  index[1][2]=2;  index[1][3]=3;
  index[2][0]=12; index[2][1]=13; index[2][2]=14; index[2][3]=15;
  index[3][0]=8;  index[3][1]=9;  index[3][2]=10; index[3][3]=11;


  TString option = GetOption();

}

void AnalyzedData::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t AnalyzedData::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either AnalyzedData::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  Reset();

  fChain->GetEntry(entry);

  /* Apply tof.pot_thin corrections and calculate fragment velocity */
  tof.un=0.; tof.pt=0.;
  for(int i=0;i<4;i++){
    Double_t tofpt = 0.;
    tofpt = t_slope*(thin_traw[i] - pot_traw);
    if(thin_traw[i]!=-1){
      tof.un+=tofpt;
      tof.nfired++;
      tof.q[i]   = tofpt - (FirstPol(q0[i],q1[i],thin_qraw[i]));
      tof.qx[i]  = tof.q[i] - (ThirdPol(x0[i],x1[i],x2[i],x3[i],crdc2_x));
      tof.qxy[i] = tof.qx[i] - (FirstPol(y0[i],y1[i],crdc2_y));
      tof.pt += tof.qxy[i];
    }
  }// Close loop over PMTs

  tof.un /= (Double_t)tof.nfired;
  tof.pt /= (Double_t)tof.nfired;

  tof.frag = tof.pt + tof_offset;
  frag.dist = Distance(crdc2_x);
  frag.v0 = frag.dist / tof.frag;

  /* Apply silicon dE calibration */
  for(int i=0;i<4;i++){
    si_de[i]    = siSlope[i]*st_anode[i] + siOffst[i];
    si_sum[i]   = st_raw[index[i][0]]+st_raw[index[i][1]]+st_raw [index[i][2]]+st_raw [index[i][3]];
    si_left[i]  = st_raw[index[i][0]]+st_raw[index[i][3]];
    si_right[i] = st_raw[index[i][1]]+st_raw[index[i][2]];
    si_up[i]    = st_raw[index[i][0]]+st_raw[index[i][1]];
    si_down[i]  = st_raw[index[i][2]]+st_raw[index[i][3]];
    si_x[i]     = 30.*(si_left[i]-si_right[i])/si_sum[i];
    si_y[i]     = 30.*(si_up[i] - si_down[i])/si_sum[i];
  }
  si0.x=si_x[0]; si0.y=si_y[0]; si0.de = si_de[0];
  si1.x=si_x[1]; si1.y=si_y[1]; si1.de = si_de[1];
  si2.x=si_x[2]; si2.y=si_y[2]; si2.de = si_de[2];
  si3.x=si_x[3]; si3.y=si_y[3]; si3.de = si_de[3];

  crdc1.x = crdc1_x; crdc1.y = crdc1_y; crdc1.tx = crdc1_tx; crdc1.ty = crdc1_ty;
  crdc2.x = crdc2_x; crdc2.y = crdc2_y; crdc2.tx = crdc2_tx; crdc2.ty = crdc2_ty;
  crdc1.path=0.; crdc2.path=0.;

  /* Reconstruct fragment from fractional brho */
  Double_t frag_bp_fracBrho  = (6.50072e-4)*crdc2_x - (8.14186e-4);
  frag_bp.Bp      = frag_bp_fracBrho*bp + bp;
  frag.Bp = frag_bp.Bp;
  Double_t frag_bp_betaGamma = (frag_bp.Bp / 3.107)*fragZ / fragA;
  frag_bp.gamma0    = sqrt(frag_bp_betaGamma*frag_bp_betaGamma + 1.);
  frag_bp.beta0     = frag_bp_betaGamma/sqrt(1. + frag_bp_betaGamma*frag_bp_betaGamma);
  frag_bp.v0 = frag_bp.beta0*C;
  frag_bp.ke0       = fragA*amuM*(frag_bp.gamma0 - 1.);

if(hit_t[0]!=-1){// valid neutron time
  /* Set target flag and addback */
  // neutron adjustments
  Double_t tshift = 0.;
  Double_t zshift = 0.;
  // fragment add back
  Double_t KEaddback = 0.;
  if(tgt1->IsInside(st_anode[0],st_anode[1])){
    target=1;
    tshift = mona_tshift[0];
    zshift = mona_zshift[0];
    KEaddback = addback[0];
  }
  else if(tgt2->IsInside(st_anode[1],st_anode[2])){
    target=2;
    tshift = mona_tshift[1];
    zshift = mona_zshift[1];
    KEaddback = addback[1];
  }
  else if(tgt3->IsInside(st_anode[2],st_anode[3])){
    target=3;
    tshift = mona_tshift[2];
    zshift = mona_zshift[2];
    KEaddback = addback[2];
  }
  else{target=9;}


  /* Reconstruct neutron */
  n0.x            = hit_x[0];
  n0.y            = hit_y[0];
  n0.z            = hit_z[0] + zshift;
  n0.dist         = sqrt(hit_x[0]*hit_x[0]+hit_y[0]*hit_y[0]+n0.z*n0.z);
  n0.t            = hit_t[0] + tshift;
  n0.v            = n0.dist / n0.t;
  n0.beta         = n0.v / C;
  n0.gamma        = 1. / sqrt(1. - n0.beta*n0.beta);
  n0.cosTheta     = (n0.z) / n0.dist;
  n0.P            = (nMamu) * n0.beta * n0.gamma;
  n0.E            = (nMamu) * n0.gamma;
  n0.light        = hit_q[0];

  /* Reconstruct fragment from dist / tof */
  frag.beta0    = frag.v0 / C;
  frag.gamma0   = 1. / sqrt(1. - frag.beta0*frag.beta0);
  frag.ke0      = fragA*amuM*(frag.gamma0-1.);
  frag.ke       = frag.ke0 + KEaddback;
  frag.gamma    = frag.ke/(fragA*amuM) + 1.;
  frag.beta     = sqrt(1. - 1./(frag.gamma*frag.gamma));
  frag.v        = frag.beta * C;
  frag.P        = fragA*frag.beta*frag.gamma;
  frag.E        = fragA*frag.gamma;

  /* Two-body decay energy */
  edecay = fragA*fragA + nMamu*nMamu + 2.*(frag.E*n0.E - frag.P*n0.P*n0.cosTheta);
  edecay = sqrt(edecay) - fragA - nMamu;
  edecay *= amuM;
}// valid neutron time

  at->Fill();
  return kTRUE;
}

void AnalyzedData::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void AnalyzedData::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  at->Write();
//  fChain->Write();
  outFile->Close();
}

void AnalyzedData::Reset(){

  beam.v=-1.;
  beam.beta=-1.;
  beam.gamma=-1.;
  tof.nfired=0;
  tof.un=-1.;
  tof.pt=-1.;
  tof.frag=-1.;
  for(int i=0;i<4;i++){
    tof.q[i]=-1.;
    tof.qx[i]=-1.;
    tof.qxy[i]=-1.;
    si_de[i]=-1.;
    si_sum[i]=-1.;
    si_left[i]=-1.;
    si_right[i]=-1.;
    si_up[i]=-1.;
    si_down[i]=-1.;
    si_x[i]=-1.;
    si_y[i]=-1.;
  }

  frag.dist=-1.;
  frag.beta0=-1.;
  frag.gamma0=-1.;
  frag.v0=-1.;
  frag.Bp=-1.;
  frag.beta=-1.;
  frag.gamma=-1.;
  frag.v=-1.;
  frag.E=-1.;
  frag.P=-1.;

  frag_bp.dist=-1.;
  frag_bp.beta0=-1.;
  frag_bp.gamma0=-1.;
  frag_bp.v0=-1.;
  frag_bp.Bp=-1.;
  frag_bp.beta=-1.;
  frag_bp.gamma=-1.;
  frag_bp.v=-1.;
  frag_bp.E=-1.;
  frag_bp.P=-1.;

  n0.x=-1.;
  n0.y=-1.;
  n0.z=-1.;
  n0.dist=-1.;
  n0.t=-1.;
  n0.v=-1.;
  n0.beta=-1.;
  n0.gamma=-1.;
  n0.cosTheta=-1.;
  n0.E=-1.;
  n0.P=-1.;

  edecay=-1.;
  target=9;

}


void AnalyzedData::SetBeam(TString beam){
  m_beam = beam;cout << m_beam.Data() << endl;
  if(m_beam.CompareTo("F27") == 0){
    m_beamIndex=0;
    tof_offset = 41.6564;
    beamA = 27.; beamZ = 9.;
  }
  else if(m_beam.CompareTo("Ne29") == 0){
    m_beamIndex=2;
    tof_offset = 42.55;
    beamA=29.; beamZ=10.;
  }
  else{cout << "Beam must be F27 or Ne29." << endl;return;}
  cout << endl << "tof offset = " << tof_offset << endl;
}


void AnalyzedData::SetFragment(TString frag){
  m_fragment = frag;cout << m_fragment.Data() << endl;

if(m_fragment.CompareTo("O24") == 0 && m_beamIndex==0){
  fragA = 24.; fragZ=8.;
  m_elmtIndex=0;
  addback[0]=785.001; addback[1]=488.710; addback[2]=177.599;// [MeV] O-24 addback
}
else if(m_fragment.CompareTo("O23") == 0 && m_beamIndex==0){
//  m_elmtIndex=0;
//  m_fragColor=4;
//  m_fragment = frag;
  fragA = 23.; fragZ=8.;
  m_elmtIndex=0;
  addback[0] = 791.409; addback[1] = 491.331; addback[2] = 177.974;// [MeV] O-23 addback
}
else if(m_fragment.CompareTo("O22") == 0 && m_beamIndex==0){
//  m_elmtIndex=0;
//  m_fragColor=4;
//  m_fragment = frag;
  fragA = 22.; fragZ=8.;
  m_elmtIndex=0;
  addback[0] = 798.852; addback[1] = 494.317; addback[2] = 178.397;// [MeV] O-22 addback
}
else if(m_fragment.CompareTo("N21") == 0 && m_beamIndex==0){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=2;
//  m_fragColor=28;
//  m_fragment = frag;
  fragA = 21.; fragZ=7.;
  addback[0] = 587.787; addback[1] = 368.689; addback[2] = 135.185;// [MeV] N-21 addback
}
else if(m_fragment.CompareTo("N20") == 0 && m_beamIndex==0){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=2;
//  m_fragColor=28;
//  m_fragment = frag;
  fragA = 20.; fragZ=7.;
  addback[0] = 592.168; addback[1] = 370.601; addback[2] = 135.463;// [MeV] N-20 addback
}
else if(m_fragment.CompareTo("N19") == 0 && m_beamIndex==0){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=2;
//  m_fragColor=28;
//  m_fragment = frag;
  fragA = 19.; fragZ=7.;
  addback[0] = 597.297; addback[1] = 372.698; addback[2] = 135.777;// [MeV] N-19 addback
}
else if(m_fragment.CompareTo("F27") == 0 && m_beamIndex==2){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=1;
//  m_fragColor=810;
//  m_fragment = frag;
  fragA = 27.; fragZ=9.;
  addback[0] = 948.586; addback[1]=597.923; addback[2]=218.961;// [MeV] F-27 from Ne-29
}
else if(m_fragment.CompareTo("F26") == 0 && m_beamIndex==2){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=1;
//  m_fragColor=810;
//  m_fragment = frag;
  fragA = 26.; fragZ=9.;
  addback[0] = 953.299; addback[1]=600.887; addback[2]=219.376;// [MeV] F-26 from Ne-29
}
else if(m_fragment.CompareTo("F25") == 0 && m_beamIndex==2){
  cout << "Fragment: " << m_fragment.Data() << endl;
  m_elmtIndex=1;
//  m_fragColor=810;
//  m_fragment = frag;
  fragA=25.; fragZ=9.;
  addback[0] = 970.06; addback[1] = 604.096; addback[2] = 219.838;// [MeV] F-25 from Ne-29
}

else{
  fragA = beamA;
  fragZ = beamZ;
  m_elmtIndex=9;
  addback[0]=0.; addback[1]=0.; addback[2]=0.;
}


}


void AnalyzedData::ReadCorrections(){

  /* Read files to set calibrated ToFs based on corrections
   * against Q, X , Y
  */
  Int_t ch=-99;
  double Read0,Read1,Read2,Read3;

  ifstream qCor;
  streampos q;
  qCor.open("/projects/e15118/redpath/analysis/calibrations/thin/pmtFits/tofQcor.txt");
  if(qCor.fail()){cout << "Error opening qCor file." << endl;return;}

  Int_t nlines=0;
  while(1){
    qCor >> ch >> Read0 >> Read1;
    q0[ch]=Read0; q1[ch]=Read1;
    if(!qCor.good()){break;}
    nlines++;
    cout << setw(8) << ch
    	<< setw(18) << q0[ch]
	<< setw(18) << q1[ch] << endl;
  }
  qCor.close();
/**/
  nlines=0;
  ifstream xCor;
  xCor.open("/projects/e15118/redpath/analysis/calibrations/thin/pmtFits/tofXcor.txt");
  if(xCor.fail()){cout << "Error opening xCor file." << endl;return;}
  while(1){
    xCor >> ch >> Read0 >> Read1 >> Read2 >> Read3;
    x0[ch]=Read0; x1[ch]=Read1; x2[ch]=Read2; x3[ch]=Read3;
    if(!xCor.good()){break;}
    cout << setw(8) << ch
    	<< setw(18) << x0[ch]
	<< setw(18) << x1[ch]
	<< setw(18) << x2[ch]
	<< setw(18) << x3[ch] << endl;
  }
  xCor.close();

  nlines=0;
  ifstream yCor;
  yCor.open("/projects/e15118/redpath/analysis/calibrations/thin/pmtFits/tofYcor.txt");
  if(yCor.fail()){cout << "Error opening yCor file." << endl;return;}
  while(1){
    yCor >> ch >> Read0 >> Read1;
    y0[ch]=Read0; y1[ch]=Read1;
    if(!yCor.good()){break;}
    cout << setw(8) << ch
    	<< setw(18) << y0[ch]
	<< setw(18) << y1[ch] << endl;

  }
  yCor.close();

}


void AnalyzedData::GraphicalCuts(){
if(m_beamIndex==0){
cout << "Beam: F27" << endl;
  if(m_elmtIndex==0){
  #include "F27_tight.h"
  #include "AllO_ictof2.h"

  #include "/projects/e15118/redpath/analysis/lifetime/target1.h"
  #include "target2.h"
  #include "target3.h"
  cout << "Oxygen target gates set." << endl;
  }
  else if(m_elmtIndex==2){
  cout << "Nitrogen target gates set." << endl;
  #include "F27N_tgt1.h"
  #include "F27N_tgt2.h"
  #include "F27N_tgt3.h"
  }
  else{
  #include "/projects/e15118/redpath/analysis/lifetime/target1.h"
  #include "target2.h"
  #include "target3.h"
  }
}
else if(m_beamIndex==2){
cout << "Beam: Ne29" << endl;
  if(m_elmtIndex==1){
  #include "Ne29F_tgt1.h"
  #include "Ne29F_tgt2.h"
  #include "Ne29F_tgt3.h"
  cout << "Fluorine target gates set." << endl;
  }
  else if(m_elmtIndex==0){
  #include "Ne29O_tgt1.h"
  #include "Ne29O_tgt2.h"
  #include "Ne29O_tgt3.h"
  cout << "Oxygen target gates set." << endl;
  }
  else{
  #include "/projects/e15118/redpath/analysis/lifetime/target1.h"
  #include "target2.h"
  #include "target3.h"
  }
}

}




// correction functions for tof.pot_thin
inline Double_t FirstPol(double a,double b,double x){
  return a + b*x;
}
inline Double_t ThirdPol(double a,double b,double c,double d,double x){
  return a + b*x + c*x*x + d*x*x*x;
}
inline Double_t Distance(double x){
  return (3.41507e-2)*x + 428.502;
}

