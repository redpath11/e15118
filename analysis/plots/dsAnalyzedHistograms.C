#include<TFile.h>
#include<THStack.h>
#include<TLegend.h>
#include "/projects/e15118/redpath/analysis/utilities/dsHist.C"

const Int_t siBins = 30;
const Double_t si1 = -30.;
const Double_t si2 =  30.;

const Int_t cBins = 75;
const Double_t c1 = -150.;
const Double_t c2 =  150.;

const Int_t deBins=200;
const Double_t de1=5.;
const Double_t de2=35.;

const Int_t vBins=50;
const Double_t v1=8.;
const Double_t v2=13.;

const Int_t fvBins=35;
const Double_t fv1=8.;
const Double_t fv2=15.;

const Int_t nxBins=20;
const Double_t nx1=-100.;
const Double_t nx2= 100.;

const Int_t nyBins=17;
const Double_t ny1=-89.25;
const Double_t ny2= 89.25;

const Int_t nctBins=100;
const Double_t nct1=0.9;
const Double_t nct2=1.1;

const Int_t nvBins=14;
const Double_t nv1=8.;
const Double_t nv2=15.;

const Int_t rvBins=10;
const Double_t rv1= -1.0;
const Double_t rv2=  1.0;

const Int_t edBins=30;
const Double_t ed1=0.;
const Double_t ed2=3.;


//const char *valid = "si0.x!=-1&&si0.y!=-1&&crdc1.x!=-1&&crdc1.y!=-1&&crdc2.x!=-1&&crdc2.y!=-1&&crdc2.tx!=-1&&crdc2.ty!=-1&&si0.de!=-1&&si1.de!=-1&&si2.de!=-1&&si3.de!=-1";// fragment efficiency only gate
const char *valid = "si0.x!=-1&&si0.y!=-1&&crdc1.x!=-1&&crdc1.y!=-1&&crdc2.x!=-1&&crdc2.y!=-1&&crdc2.tx!=-1&&crdc2.ty!=-1&&si0.de!=-1&&si1.de!=-1&&si2.de!=-1&&si3.de!=-1 && n0.t>0 && n0.x>-100. && n0.x<100. && n0.y>-90. && n0.y<90. && n0.light>=0.95";// fragment && neutron efficiency + q-gate

void dsUnrF27(){
  /* Load in filtered, analyzed files */
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/r1051F27unr.root","READ");
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/1MF27unr.root","READ");
  TFile *sf = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27unrat.root","READ");

  TTree *dt = (TTree*)df->Get("at");
  TTree *st = (TTree*)sf->Get("sat");

//  TCanvas *c1 = dsH1(dt,st,
//  		"crdc2.x","crdc2.x",
//		150,-150,150,
//		"","crdc2.x!=-1","mm");
/*
  const Int_t siBins = 30;
  const Double_t si1 = -30.;
  const Double_t si2 =  30.;

  const Int_t cBins = 150;
  const Double_t c1 = -150.;
  const Double_t c2 =  150.;

  const Int_t deBins=200;
  const Double_t de1=5.;
  const Double_t de2=35.;

  const Int_t vBins=100;
  const Double_t v1=8.;
  const Double_t v2=13.;

  const char *valid = "si0.x!=-1&&si0.y!=-1&&crdc1.x!=-1&&crdc1.y!=-1&&crdc2.x!=-1&&crdc2.y!=-1&&crdc2.tx!=-1&&crdc2.ty!=-1&&si0.de!=-1&&si1.de!=-1&&si2.de!=-1&&si3.de!=-1";
*/

  // Si0 position
  TH1D *dsi0x = MakeH1(dt,"si0.x","dsi0x",siBins,si1,si2,valid,"mm");
  TH1D *ssi0x = MakeH1(st,"si0.x","ssi0x",siBins,si1,si2,valid,"mm");

  TH1D *dsi0y = MakeH1(dt,"si0.y","dsi0y",siBins,si1,si2,valid,"mm");
  TH1D *ssi0y = MakeH1(st,"si0.y","ssi0y",siBins,si1,si2,valid,"mm");

  // CRDC 1
  TH1D *dc1x = MakeH1(dt,"crdc1.x","dc1x",cBins,c1,c2,valid,"mm");
  TH1D *sc1x = MakeH1(st,"crdc1.x","sc1x",cBins,c1,c2,valid,"mm");
  
  TH1D *dc1y = MakeH1(dt,"crdc1.y","dc1y",cBins,c1,c2,valid,"mm");
  TH1D *sc1y = MakeH1(st,"crdc1.y","sc1y",cBins,c1,c2,valid,"mm");

  // CRDC 2
  TH1D *dc2x = MakeH1(dt,"crdc2.x","dc2x",cBins,c1,c2,valid,"mm");
  TH1D *sc2x = MakeH1(st,"crdc2.x","sc2x",cBins,c1,c2,valid,"mm");

  TH1D *dc2y = MakeH1(dt,"crdc2.y","dc2y",cBins,c1,c2,valid,"mm");
  TH1D *sc2y = MakeH1(st,"crdc2.y","sc2y",cBins,c1,c2,valid,"mm");

  // CRDC angles
  TH1D *dctx = MakeH1(dt,"crdc2.tx","dctx",cBins,c1,c2,valid,"mrad");
  TH1D *sctx = MakeH1(st,"crdc2.tx","sctx",cBins,c1,c2,valid,"mrad");

  TH1D *dcty = MakeH1(dt,"crdc2.ty","dcty",cBins,c1,c2,valid,"mrad");
  TH1D *scty = MakeH1(st,"crdc2.ty","scty",cBins,c1,c2,valid,"mrad");

  // Si dE
  TH1D *dsi0de = MakeH1(dt,"si0.de","dsi0de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi0de = MakeH1(st,"si0.de","ssi0de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi1de = MakeH1(dt,"si1.de","dsi1de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi1de = MakeH1(st,"si1.de","ssi1de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi2de = MakeH1(dt,"si2.de","dsi2de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi2de = MakeH1(st,"si2.de","ssi2de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi3de = MakeH1(dt,"si3.de","dsi3de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi3de = MakeH1(st,"si3.de","ssi3de",deBins,de1,de2,valid,"MeV");
  
  // fragment
  TH1D *dfv0 = MakeH1(dt,"frag.v0","dfv0",vBins,v1,v2,valid,"cm/ns");
  TH1D *sfv0 = MakeH1(st,"frag.v0","sfv0",vBins,v1,v2,valid,"cm/ns");

  // calculate normalization for crdc2.x
  Double_t simNormalization = dsNorm(dc2x,sc2x,cBins);
  cout << "sim -> data scaling: " << simNormalization << endl;

  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,3);
  // overlay data and simulation
  // si 0 position
  dsDraw(c4,1,dsi0x,ssi0x,simNormalization,"l");
  dsDraw(c4,2,dsi0y,ssi0y,simNormalization,"r");
  // CRDC 1 position
  dsDraw(c4,3,dc1x,sc1x,simNormalization,"r");
  dsDraw(c4,4,dc1y,sc1y,simNormalization,"r");
  // CRDC 2 position
  dsDraw(c4,5,dc2x,sc2x,simNormalization,"r");
  dsDraw(c4,6,dc2y,sc2y,simNormalization,"r");
  // CRDC angles
  dsDraw(c4,7,dctx,sctx,simNormalization,"r");
  dsDraw(c4,8,dcty,scty,simNormalization,"r");
  // fragment v0
  dsDraw(c4,9,dfv0,sfv0,simNormalization,"r");

  TCanvas *c4a = new TCanvas("c4a","c4a",1800,400);c4a->Divide(4,1);
  // Si dE
  dsDraw(c4a,1,dsi0de,ssi0de,simNormalization,"r");
  dsDraw(c4a,2,dsi1de,ssi1de,simNormalization,"r");
  dsDraw(c4a,3,dsi2de,ssi2de,simNormalization,"r");
  dsDraw(c4a,4,dsi3de,ssi3de,simNormalization,"r");
}// END FUNCTION dsUnrF27()


void dsUnrNe29(){
  /* Load in filtered, analyzed files */
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/r1051Ne29unr.root","READ");
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/selectNe29unr.root","READ");
  TFile *sf = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/Ne29unrat.root","READ");

  TTree *dt = (TTree*)df->Get("at");
  TTree *st = (TTree*)sf->Get("sat");

//  TCanvas *c1 = dsH1(dt,st,
//  		"crdc2.x","crdc2.x",
//		150,-150,150,
//		"","crdc2.x!=-1","mm");
/*
  const Int_t siBins = 30;
  const Double_t si1 = -30.;
  const Double_t si2 =  30.;

  const Int_t cBins = 150;
  const Double_t c1 = -150.;
  const Double_t c2 =  150.;

  const Int_t deBins=200;
  const Double_t de1=5.;
  const Double_t de2=35.;

  const Int_t vBins=100;
  const Double_t v1=8.;
  const Double_t v2=13.;

  const char *valid = "si0.x!=-1&&si0.y!=-1&&crdc1.x!=-1&&crdc1.y!=-1&&crdc2.x!=-1&&crdc2.y!=-1&&crdc2.tx!=-1&&crdc2.ty!=-1&&si0.de!=-1&&si1.de!=-1&&si2.de!=-1&&si3.de!=-1";
*/
  // Si0 position
  TH1D *dsi0x = MakeH1(dt,"si0.x","dsi0x",siBins,si1,si2,valid,"mm");
  TH1D *ssi0x = MakeH1(st,"si0.x","ssi0x",siBins,si1,si2,valid,"mm");

  TH1D *dsi0y = MakeH1(dt,"si0.y","dsi0y",siBins,si1,si2,valid,"mm");
  TH1D *ssi0y = MakeH1(st,"si0.y","ssi0y",siBins,si1,si2,valid,"mm");

  // CRDC 1
  TH1D *dc1x = MakeH1(dt,"crdc1.x","dc1x",cBins,c1,c2,valid,"mm");
  TH1D *sc1x = MakeH1(st,"crdc1.x","sc1x",cBins,c1,c2,valid,"mm");
  
  TH1D *dc1y = MakeH1(dt,"crdc1.y","dc1y",cBins,c1,c2,valid,"mm");
  TH1D *sc1y = MakeH1(st,"crdc1.y","sc1y",cBins,c1,c2,valid,"mm");

  // CRDC 2
  TH1D *dc2x = MakeH1(dt,"crdc2.x","dc2x",cBins,c1,c2,valid,"mm");
  TH1D *sc2x = MakeH1(st,"crdc2.x","sc2x",cBins,c1,c2,valid,"mm");

  TH1D *dc2y = MakeH1(dt,"crdc2.y","dc2y",cBins,c1,c2,valid,"mm");
  TH1D *sc2y = MakeH1(st,"crdc2.y","sc2y",cBins,c1,c2,valid,"mm");

  // CRDC angles
  TH1D *dctx = MakeH1(dt,"crdc2.tx","dctx",cBins,c1,c2,valid,"mrad");
  TH1D *sctx = MakeH1(st,"crdc2.tx","sctx",cBins,c1,c2,valid,"mrad");

  TH1D *dcty = MakeH1(dt,"crdc2.ty","dcty",cBins,c1,c2,valid,"mrad");
  TH1D *scty = MakeH1(st,"crdc2.ty","scty",cBins,c1,c2,valid,"mrad");

  // Si dE
  TH1D *dsi0de = MakeH1(dt,"si0.de","dsi0de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi0de = MakeH1(st,"si0.de","ssi0de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi1de = MakeH1(dt,"si1.de","dsi1de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi1de = MakeH1(st,"si1.de","ssi1de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi2de = MakeH1(dt,"si2.de","dsi2de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi2de = MakeH1(st,"si2.de","ssi2de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi3de = MakeH1(dt,"si3.de","dsi3de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi3de = MakeH1(st,"si3.de","ssi3de",deBins,de1,de2,valid,"MeV");
  
  // fragment
  TH1D *dfv0 = MakeH1(dt,"frag.v0","dfv0",vBins,v1,v2,valid,"cm/ns");
  TH1D *sfv0 = MakeH1(st,"frag.v0","sfv0",vBins,v1,v2,valid,"cm/ns");

  // calculate normalization for crdc2.x
  Double_t simNormalization = dsNorm(dc2x,sc2x,cBins);
  cout << "sim -> data scaling: " << simNormalization << endl;

  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,3);
  // overlay data and simulation
  // si 0 position
  dsDraw(c4,1,dsi0x,ssi0x,simNormalization,"l");
  dsDraw(c4,2,dsi0y,ssi0y,simNormalization,"r");
  // CRDC 1 position
  dsDraw(c4,3,dc1x,sc1x,simNormalization,"r");
  dsDraw(c4,4,dc1y,sc1y,simNormalization,"r");
  // CRDC 2 position
  dsDraw(c4,5,dc2x,sc2x,simNormalization,"r");
  dsDraw(c4,6,dc2y,sc2y,simNormalization,"r");
  // CRDC angles
  dsDraw(c4,7,dctx,sctx,simNormalization,"r");
  dsDraw(c4,8,dcty,scty,simNormalization,"r");
  // fragment v0
  dsDraw(c4,9,dfv0,sfv0,simNormalization,"r");

  TCanvas *c4a = new TCanvas("c4a","c4a",1800,400);c4a->Divide(4,1);
  // Si dE
  dsDraw(c4a,1,dsi0de,ssi0de,simNormalization,"r");
  dsDraw(c4a,2,dsi1de,ssi1de,simNormalization,"r");
  dsDraw(c4a,3,dsi2de,ssi2de,simNormalization,"r");
  dsDraw(c4a,4,dsi3de,ssi3de,simNormalization,"r");
}// END FUNCTION dsUnrNe29()


void dsF27O24(){
  /* Load in filtered, analyzed files */
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns.root","READ");
/* O-24 */
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns_THRHLDfix.root","READ");
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns_THLDfixLISAxpos.root","READ");
  TFile *sf = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O24at_0ps.root","READ");

  /* O-22 
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O22_tshift1.0ns.root","READ");
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O22_tshift1.0ns_THLDfixLISAxpos.root","READ");
  TFile *sf = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O22at.root","READ");
  */

  TTree *dt = (TTree*)df->Get("at");
  TTree *st = (TTree*)sf->Get("sat");

//  TCanvas *c1 = dsH1(dt,st,
//  		"crdc2.x","crdc2.x",
//		150,-150,150,
//		"","crdc2.x!=-1","mm");

  // Si0 position
  TH1D *dsi0x = MakeH1(dt,"si0.x","dsi0x",siBins,si1,si2,valid,"mm");
  TH1D *ssi0x = MakeH1(st,"si0.x","ssi0x",siBins,si1,si2,valid,"mm");

  TH1D *dsi0y = MakeH1(dt,"si0.y","dsi0y",siBins,si1,si2,valid,"mm");
  TH1D *ssi0y = MakeH1(st,"si0.y","ssi0y",siBins,si1,si2,valid,"mm");

  // CRDC 1
  TH1D *dc1x = MakeH1(dt,"crdc1.x","dc1x",cBins,c1,c2,valid,"mm");
  TH1D *sc1x = MakeH1(st,"crdc1.x","sc1x",cBins,c1,c2,valid,"mm");
  
  TH1D *dc1y = MakeH1(dt,"crdc1.y","dc1y",cBins,c1,c2,valid,"mm");
  TH1D *sc1y = MakeH1(st,"crdc1.y","sc1y",cBins,c1,c2,valid,"mm");

  // CRDC 2
  TH1D *dc2x = MakeH1(dt,"crdc2.x","dc2x",cBins,c1,c2,valid,"mm");
  TH1D *sc2x = MakeH1(st,"crdc2.x","sc2x",cBins,c1,c2,valid,"mm");

  TH1D *dc2y = MakeH1(dt,"crdc2.y","dc2y",cBins,c1,c2,valid,"mm");
  TH1D *sc2y = MakeH1(st,"crdc2.y","sc2y",cBins,c1,c2,valid,"mm");

  // CRDC angles
  TH1D *dctx = MakeH1(dt,"crdc2.tx","dctx",cBins,c1,c2,valid,"mrad");
  TH1D *sctx = MakeH1(st,"crdc2.tx","sctx",cBins,c1,c2,valid,"mrad");

  TH1D *dcty = MakeH1(dt,"crdc2.ty","dcty",cBins,c1,c2,valid,"mrad");
  TH1D *scty = MakeH1(st,"crdc2.ty","scty",cBins,c1,c2,valid,"mrad");

  // Si dE
  TH1D *dsi0de = MakeH1(dt,"si0.de","dsi0de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi0de = MakeH1(st,"si0.de","ssi0de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi1de = MakeH1(dt,"si1.de","dsi1de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi1de = MakeH1(st,"si1.de","ssi1de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi2de = MakeH1(dt,"si2.de","dsi2de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi2de = MakeH1(st,"si2.de","ssi2de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi3de = MakeH1(dt,"si3.de","dsi3de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi3de = MakeH1(st,"si3.de","ssi3de",deBins,de1,de2,valid,"MeV");

  // neutron space-like things
  TH1D *dn0x = MakeH1(dt,"n0.x","dn0x",nxBins,nx1,nx2,Form("%s && n0.t>0",valid),"cm");
  TH1D *sn0x = MakeH1(st,"n0.x","sn0x",nxBins,nx1,nx2,Form("%s && n0.t>0",valid),"cm");
  TH1D *dn0y = MakeH1(dt,"n0.y","dn0y",nyBins,ny1,ny2,Form("%s && n0.t>0",valid),"cm");
  TH1D *sn0y = MakeH1(st,"n0.y","sn0y",nyBins,ny1,ny2,Form("%s && n0.t>0",valid),"cm");
  TH1D *dn0costh = MakeH1(dt,"n0.cosTheta","dn0costh",nctBins,nct1,nct2,Form("%s && n0.t>0",valid),"");
  TH1D *sn0costh = MakeH1(st,"n0.cosTheta","sn0costh",nctBins,nct1,nct2,Form("%s && n0.t>0",valid),"");

  TH1I *dmult = MakeH1I(dt,"mult","dmult",10,0,10,Form("%s && n0.t>0",valid),"hits");
  TH1I *smult = MakeH1I(st,"smult","smult",10,0,10,Form("%s && n0.t>0",valid),"hits");

  // fragment
//  TH1D *dfv0[3];
//  TH1D *sfv0[3];
  TH1D *dfv[3];
  TH1D *sfv[3];

  // neutron
  TH1D *dnv[3];
  TH1D *snv[3];

  // relative velocity
  TH1D *drv[3];
  TH1D *srv[3];
  TH1D *drvSum;
  TH1D *srvSum;

  // decay energy
  TH1D *ded[3];
  TH1D *sed[3];

  for(int i=0;i<3;i++){
    TString targetGate = Form("%s && target==%i",valid,i+1);
    // fragment - v0
    /*
    dfv0[i] = MakeH1(dt,"frag.v0",Form("d%ifv0",i+1),vBins,v1,v2,targetGate.Data(),"cm/ns");
    sfv0[i] = MakeH1(st,"frag.v0",Form("s%ifv0",i+1),vBins,v1,v2,targetGate.Data(),"cm/ns");
    */
    targetGate = Form("%s && n0.t>0 && target==%i && edecay>0 && edecay < 0.4",valid,i+1);
    // fragment - v (w/ addback)
    dfv[i]  = MakeH1(dt,"frag.v",Form("d%ifv",i+1),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");
    sfv[i]  = MakeH1(st,"frag.v",Form("s%ifv",i+1),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");
    dfv[i]->SetTitle(Form("Fragment Velocity (tgt%i)",i+1));
    sfv[i]->SetTitle(Form("Fragment Velocity (tgt%i)",i+1));

    dnv[i]  = MakeH1(dt,"n0.v",Form("d%in0v",i+1),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");
    snv[i]  = MakeH1(st,"n0.v",Form("s%in0v",i+1),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");
    dnv[i]->SetTitle(Form("Neutron Velocity (tgt%i)",i+1));
    snv[i]->SetTitle(Form("Neutron Velocity (tgt%i)",i+1));

    drv[i]  = MakeH1(dt,"n0.v - frag.v",Form("d%irv",i+1),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");
    srv[i]  = MakeH1(st,"n0.v - frag.v",Form("s%irv",i+1),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");

    targetGate = Form("%s && n0.t>0 && target==%i",valid,i+1);
    ded[i]  = MakeH1(dt,"edecay",Form("d%iedecay",i+1),edBins,ed1,ed2,targetGate.Data(),"MeV");
    sed[i]  = MakeH1(st,"edecay",Form("s%iedecay",i+1),edBins,ed1,ed2,targetGate.Data(),"MeV");

  }

  // calculate normalization from crdc2.x
  Double_t simNormalization = dsNorm(dc2x,sc2x,cBins);
  cout << "sim -> data scaling: " << simNormalization << endl;

  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,3);
//  TCanvas *c4 = new TCanvas("c4","c4",1800,800);c4->Divide(4,2);
  // overlay data and simulation
  // si 0 position
  dsDraw(c4,1,dsi0x,ssi0x,simNormalization,"l");
  dsDraw(c4,2,dsi0y,ssi0y,simNormalization,"r");
  // CRDC 1 position
  dsDraw(c4,3,dc1x,sc1x,simNormalization,"r");
  dsDraw(c4,4,dc1y,sc1y,simNormalization,"r");
  // CRDC 2 position
  dsDraw(c4,5,dc2x,sc2x,simNormalization,"r");
  dsDraw(c4,6,dc2y,sc2y,simNormalization,"r");
  // CRDC angles
  dsDraw(c4,7,dctx,sctx,simNormalization,"r");
  dsDraw(c4,8,dcty,scty,simNormalization,"r");
  // neutron 0 space-like
  /**/
  simNormalization = dsNorm(dn0x,sn0x,nxBins);
  dsDraw(c4,9,dn0x,sn0x,simNormalization,"r");
  dsDraw(c4,10,dn0y,sn0y,simNormalization,"r");
  dsDraw(c4,11,dn0costh,sn0costh,simNormalization,"l");

  TCanvas *c5 = new TCanvas("c5","c5",500,400);
  dsDrawI(c5,1,dmult,smult,simNormalization,"r");
  
  // fragment v0
  /*
  simNormalization = dsNorm(dfv0[0],sfv0[0],vBins);
  dsDrawTitle(c4,9,dfv0[0],sfv0[0],simNormalization,"r","Fragment Velocity (tgt1)");
  simNormalization = dsNorm(dfv0[1],sfv0[1],vBins);
  dsDrawTitle(c4,10,dfv0[1],sfv0[1],simNormalization,"r","Fragment Velocity (tgt2)");
  simNormalization = dsNorm(dfv0[2],sfv0[2],vBins);
  dsDrawTitle(c4,11,dfv0[2],sfv0[2],simNormalization,"r","Fragment Velocity (tgt3)");
  */
  TCanvas *c4a = new TCanvas("c4a","c4a",1800,400);c4a->Divide(4,1);
  // Si dE
  dsDraw(c4a,1,dsi0de,ssi0de,simNormalization,"r");
  dsDraw(c4a,2,dsi1de,ssi1de,simNormalization,"r");
  dsDraw(c4a,3,dsi2de,ssi2de,simNormalization,"r");
  dsDraw(c4a,4,dsi3de,ssi3de,simNormalization,"r");

  TCanvas *c3 = new TCanvas("c3","c3",1500,800);c3->Divide(3,2);
  TCanvas *c6 = new TCanvas("c6","c6",1500,800);c6->Divide(3,2);
  TLine *edLine[3];
  for(int i=0;i<3;i++){
    simNormalization = dsNorm(dfv[i],sfv[i],fvBins);
    dsDrawTitle(c6,i+1,dnv[i],snv[i],simNormalization,"l",Form("Neutron Velocity (tgt%i)",i+1));
    dsDrawTitle(c6,i+4,dfv[i],sfv[i],simNormalization,"l",Form("Fragment Velocity (tgt%i)",i+1));
    dsDrawTitle(c3,i+4,drv[i],srv[i],simNormalization,"r",Form("Relative Velocity (tgt%i)",i+1));

    simNormalization = dsNormRng(ded[i],sed[i],0.4);
    dsDraw(c3,i+1,ded[i],sed[i],simNormalization,"r");

    c3->cd(i+1);
    edLine[i] = new TLine(0.4,0.,0.4,ded[i]->GetMaximum());
    edLine[i]->SetLineColor(1); edLine[i]->SetLineWidth(3);
    edLine[i]->Draw("SAME");

    if(i==0){
      drvSum = (TH1D*)drv[0]->Clone();
      srvSum = (TH1D*)srv[0]->Clone();
    }
    else{
      drvSum->Add(drv[i]);
      srvSum->Add(srv[i]);
    }
    TCanvas *c7 = new TCanvas("c7","c7",500,400);
    srvSum->Draw();
    drvSum->Draw("SAMESPE1][");
  }

}// END FUNCTION dsF27O24()


void dsLifetimes(){

  const int nPts=3;
  const Int_t Lifetimes[nPts] = {0,2,4};
  /* Load in filtered, analyzed files */
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns.root","READ");
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O22_tshift1.0ns.root","READ");
  TFile *sf[nPts];
  /* O-24 */
  sf[0] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O24at_0ps.root","READ");
  sf[1] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O24at_2ps.root","READ");
  sf[2] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O24at_4ps.root","READ");
  
  /* O-22 
  sf[0] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O22at.root","READ");
  sf[1] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O22at_2ps.root","READ");
  sf[2] = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/F27O22at_4ps.root","READ");
  */

  TTree *dt = (TTree*)df->Get("at");
  TTree *st[nPts];
  
  for(int i=0;i<nPts;i++){ st[i] = (TTree*)sf[i]->Get("sat"); }
  // fragment
  TH1D *dfv[3];
  TH1D *sfv[nPts][3];

  // neutron
  TH1D *dnv[3];
  TH1D *snv[nPts][3];

  // relative velocity
  TH1D *drv[3];
  TH1D *srv[nPts][3];

  // decay energy
  TH1D *ded[3];
  TH1D *sed[nPts][3];


  // Make Histograms
  for(int i=0;i<3;i++){
    TString targetGate = Form("%s && n0.t>0 && target==%i && edecay < 0.4",valid,i+1);
    dfv[i]  = MakeH1(dt,"frag.v",Form("d%ifv",i+1),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");
    dnv[i]  = MakeH1(dt,"n0.v",Form("d%in0v",i+1),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");
    drv[i]  = MakeH1(dt,"n0.v - frag.v",Form("d%irv",i+1),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");
    targetGate = Form("%s && n0.t>0 && target==%i",valid,i+1);
    ded[i]  = MakeH1(dt,"edecay",Form("d%iedecay",i+1),edBins,ed1,ed2,targetGate.Data(),"MeV");
    for(int j=0;j<nPts;j++){
      targetGate = Form("%s && n0.t>0 && target==%i && edecay < 0.4",valid,i+1);
      sfv[j][i]  = MakeH1(st[j],"frag.v",Form("s%ifv_lf%i",i+1,Lifetimes[j]),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");

      snv[j][i]  = MakeH1(st[j],"n0.v",Form("s%in0v_lf%i",i+1,Lifetimes[j]),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");

      srv[j][i]  = MakeH1(st[j],"n0.v - frag.v",Form("s%irv_lf%i",i+1,Lifetimes[j]),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");

      targetGate = Form("%s && n0.t>0 && target==%i",valid,i+1);
      sed[j][i]  = MakeH1(st[j],"edecay",Form("s%iedecay_lf%i",i+1,Lifetimes[j]),edBins,ed1,ed2,targetGate.Data(),"MeV");

    }
  }

  // Draw Histograms
  TCanvas *c4 = new TCanvas("c4","c4",1500,1000);c4->Divide(3,4);
  THStack *hs_edcy[3];
  THStack *hs_nv[3];
  THStack *hs_fv[3];
  THStack *hs_rv[3];
  Int_t color[nPts] = {1,600,880};
  TLine *edLine[3];

  for(int i=0;i<3;i++){
    hs_edcy[i] = new THStack(Form("hs_edcy%i",i),Form("Decay Energy (tgt%i);E_{d} [MeV]",i+1));
    hs_nv[i] = new THStack(Form("hs_nv%i",i),Form("Neutron Velocity (tgt%i);velocity [cm/ns]",i+1));
    hs_fv[i] = new THStack(Form("hs_fv%i",i),Form("Fragment Velocity (tgt%i);velocity [cm/ns]",i+1));
    hs_rv[i] = new THStack(Form("hs_rv%i",i),Form("Relative Velocity (tgt%i);v_{n} - v_{f} [cm/ns]",i+1));
    for(int j=0;j<nPts;j++){
      Double_t simNormalization = dsNormRng(ded[i],sed[j][i],0.4);
//      Double_t simNormalization = dsNorm(dfv[i],sfv[j][i],fvBins);
      dsDrawTitle(c4,i+4, dnv[i],snv[j][i],simNormalization,"l",Form("Neutron Velocity (tgt%i)",i+1));
      dsDrawTitle(c4,i+7, dfv[i],sfv[j][i],simNormalization,"l",Form("Fragment Velocity (tgt%i)",i+1));
      dsDrawTitle(c4,i+10,drv[i],srv[j][i],simNormalization,"r",Form("Relative Velocity (tgt%i)",i+1));
      snv[j][i]->SetLineColor(color[j]);
      sfv[j][i]->SetLineColor(color[j]);
      srv[j][i]->SetLineColor(color[j]);

      dsDraw(c4,i+1,ded[i],sed[j][i],simNormalization,"r");
      sed[j][i]->SetLineColor(color[j]);

      hs_edcy[i]->Add(sed[j][i]);
      hs_nv[i]->Add(snv[j][i]);
      hs_fv[i]->Add(sfv[j][i]);
      hs_rv[i]->Add(srv[j][i]);
    }
    hs_edcy[i]->Add(ded[i],"PE1][");
    c4->cd(i+1); hs_edcy[i]->Draw("nostack");
    edLine[i] = new TLine(0.4,0.,0.4,ded[i]->GetMaximum());
    edLine[i]->SetLineColor(1); edLine[i]->SetLineWidth(3);
    edLine[i]->Draw("SAME");

    hs_nv[i]->Add(dnv[i],"PE1][");
    c4->cd(i+4); hs_nv[i]->Draw("nostack");

    hs_fv[i]->Add(dfv[i],"PE1][");
    c4->cd(i+7); hs_fv[i]->Draw("nostack");

    hs_rv[i]->Add(drv[i],"PE1][");
    c4->cd(i+10); hs_rv[i]->Draw("nostack");

  }

  TH1D *dedSum = sumTargets(ded,"Decay Energy;E_{d} [MeV]");
  TH1D *drvSum = sumTargets(drv,"Relative Velocity;v_{n} - v_{f} [cm/ns]");

  THStack *hs_edSum = new THStack("hs_edSum","Decay Energy;E_{d} [MeV]");
//  hs_edSum->GetYaxis()->SetTitle(dedSum->GetYaxis()->GetTitle());
  THStack *hs_rvSum = new THStack("hs_rvSum","Relative Velocity;v_{n} - v_{f} [cm/ns]");
//  hs_rvSum->GetYaxis()->SetTitle(drvSum->GetYaxis()->GetTitle());

  hs_edSum->Add(dedSum,"PE1][");
  hs_rvSum->Add(drvSum,"PE1][");

  TH1D *sedSum[nPts];
  TH1D *srvSum[nPts];
  for(int j=0;j<nPts;j++){
    sedSum[j] = sumTargets(sed[j],"Decay Energy;E_{d} [MeV]");
    srvSum[j] = sumTargets(srv[j],"Relative Velocity;v_{f} - v_{n} [cm/ns]");
    hs_edSum->Add(sedSum[j],"L");
    hs_rvSum->Add(srvSum[j],"L");
  }


  TCanvas *c5 = new TCanvas("c5","c5",1000,400);c5->Divide(2,1);
  c5->cd(1); hs_edSum->Draw("nostack");//dedSum->Draw("PE1][");
  TLine *sumLine = new TLine(0.4,0.,0.4,dedSum->GetMaximum());sumLine->SetLineColor(1);sumLine->SetLineWidth(3);
  sumLine->Draw("SAME");
  c5->cd(2);hs_rvSum->Draw("nostack");//dvrSum->Draw("PE1][");

  TLegend *legend = new TLegend(0.75,0.7,0.9,0.9);
  legend->AddEntry(dedSum,"Data","LPE1][");
  legend->AddEntry(sedSum[0],"0 ps lifetime","l");
  legend->AddEntry(sedSum[1],"2 ps lifetime","l");
  legend->AddEntry(sedSum[2],"4 ps lifetime","l");
  legend->Draw("SAME");

  c5->cd(1); legend->Draw("SAME");


}// END FUNCTION dsF27O24Lifetimes()


void dsNe29F27(){
  /* Load in filtered, analyzed files */
//  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns.root","READ");
  TFile *df = new TFile("/mnt/analysis/e15118/analyzed/Ne29F27_tshift1.0ns_THRHLDfix.root","READ");
  TFile *sf = new TFile("/mnt/simulations/MoNAsims/O26_analysis/analyzed/Ne29F27at.root","READ");

  TTree *dt = (TTree*)df->Get("at");
  TTree *st = (TTree*)sf->Get("sat");

//  TCanvas *c1 = dsH1(dt,st,
//  		"crdc2.x","crdc2.x",
//		150,-150,150,
//		"","crdc2.x!=-1","mm");

  // Si0 position
  TH1D *dsi0x = MakeH1(dt,"si0.x","dsi0x",siBins,si1,si2,valid,"mm");
  TH1D *ssi0x = MakeH1(st,"si0.x","ssi0x",siBins,si1,si2,valid,"mm");

  TH1D *dsi0y = MakeH1(dt,"si0.y","dsi0y",siBins,si1,si2,valid,"mm");
  TH1D *ssi0y = MakeH1(st,"si0.y","ssi0y",siBins,si1,si2,valid,"mm");

  // CRDC 1
  TH1D *dc1x = MakeH1(dt,"crdc1.x","dc1x",cBins,c1,c2,valid,"mm");
  TH1D *sc1x = MakeH1(st,"crdc1.x","sc1x",cBins,c1,c2,valid,"mm");
  
  TH1D *dc1y = MakeH1(dt,"crdc1.y","dc1y",cBins,c1,c2,valid,"mm");
  TH1D *sc1y = MakeH1(st,"crdc1.y","sc1y",cBins,c1,c2,valid,"mm");

  // CRDC 2
  TH1D *dc2x = MakeH1(dt,"crdc2.x","dc2x",cBins,c1,c2,valid,"mm");
  TH1D *sc2x = MakeH1(st,"crdc2.x","sc2x",cBins,c1,c2,valid,"mm");

  TH1D *dc2y = MakeH1(dt,"crdc2.y","dc2y",cBins,c1,c2,valid,"mm");
  TH1D *sc2y = MakeH1(st,"crdc2.y","sc2y",cBins,c1,c2,valid,"mm");

  // CRDC angles
  TH1D *dctx = MakeH1(dt,"crdc2.tx","dctx",cBins,c1,c2,valid,"mrad");
  TH1D *sctx = MakeH1(st,"crdc2.tx","sctx",cBins,c1,c2,valid,"mrad");

  TH1D *dcty = MakeH1(dt,"crdc2.ty","dcty",cBins,c1,c2,valid,"mrad");
  TH1D *scty = MakeH1(st,"crdc2.ty","scty",cBins,c1,c2,valid,"mrad");

  // Si dE
  TH1D *dsi0de = MakeH1(dt,"si0.de","dsi0de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi0de = MakeH1(st,"si0.de","ssi0de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi1de = MakeH1(dt,"si1.de","dsi1de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi1de = MakeH1(st,"si1.de","ssi1de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi2de = MakeH1(dt,"si2.de","dsi2de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi2de = MakeH1(st,"si2.de","ssi2de",deBins,de1,de2,valid,"MeV");

  TH1D *dsi3de = MakeH1(dt,"si3.de","dsi3de",deBins,de1,de2,valid,"MeV");
  TH1D *ssi3de = MakeH1(st,"si3.de","ssi3de",deBins,de1,de2,valid,"MeV");
  
  // fragment
  TH1D *dfv0[3];
  TH1D *sfv0[3];
  TH1D *dfv[3];
  TH1D *sfv[3];

  // neutron
  TH1D *dnv[3];
  TH1D *snv[3];

  // relative velocity
  TH1D *drv[3];
  TH1D *srv[3];

  // decay energy
  TH1D *ded[3];
  TH1D *sed[3];

  for(int i=0;i<3;i++){
    TString targetGate = Form("%s && target==%i",valid,i+1);
    // fragment - v0
    dfv0[i] = MakeH1(dt,"frag.v0",Form("d%ifv0",i+1),vBins,v1,v2,targetGate.Data(),"cm/ns");
    sfv0[i] = MakeH1(st,"frag.v0",Form("s%ifv0",i+1),vBins,v1,v2,targetGate.Data(),"cm/ns");

    targetGate = Form("%s && n0.t>0 && target==%i && edecay < 0.4",valid,i+1);
    // fragment - v (w/ addback)
    dfv[i]  = MakeH1(dt,"frag.v",Form("d%ifv",i+1),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");
    sfv[i]  = MakeH1(st,"frag.v",Form("s%ifv",i+1),fvBins,fv1,fv2,targetGate.Data(),"cm/ns");
    dfv[i]->SetTitle(Form("Fragment Velocity (tgt%i)",i+1));
    sfv[i]->SetTitle(Form("Fragment Velocity (tgt%i)",i+1));

    dnv[i]  = MakeH1(dt,"n0.v",Form("d%in0v",i+1),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");
    snv[i]  = MakeH1(st,"n0.v",Form("s%in0v",i+1),nvBins,nv1,nv2,targetGate.Data(),"cm/ns");
    dnv[i]->SetTitle(Form("Neutron Velocity (tgt%i)",i+1));
    snv[i]->SetTitle(Form("Neutron Velocity (tgt%i)",i+1));

    drv[i]  = MakeH1(dt,"n0.v - frag.v",Form("d%irv",i+1),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");
    srv[i]  = MakeH1(st,"n0.v - frag.v",Form("s%irv",i+1),rvBins,rv1,rv2,targetGate.Data(),"cm/ns");

    targetGate = Form("%s && n0.t>0 && target==%i",valid,i+1);
    ded[i]  = MakeH1(dt,"edecay",Form("d%iedecay",i+1),edBins,ed1,ed2,targetGate.Data(),"MeV");
    sed[i]  = MakeH1(st,"edecay",Form("s%iedecay",i+1),edBins,ed1,ed2,targetGate.Data(),"MeV");
  }

  // calculate normalization for crdc2.x
  Double_t simNormalization = dsNorm(dc2x,sc2x,cBins);
  cout << "sim -> data scaling: " << simNormalization << endl;

  TCanvas *c4 = new TCanvas("c4","c4",1800,1000);c4->Divide(4,3);
  // overlay data and simulation
  // si 0 position
  dsDraw(c4,1,dsi0x,ssi0x,simNormalization,"l");
  dsDraw(c4,2,dsi0y,ssi0y,simNormalization,"r");
  // CRDC 1 position
  dsDraw(c4,3,dc1x,sc1x,simNormalization,"r");
  dsDraw(c4,4,dc1y,sc1y,simNormalization,"r");
  // CRDC 2 position
  dsDraw(c4,5,dc2x,sc2x,simNormalization,"r");
  dsDraw(c4,6,dc2y,sc2y,simNormalization,"r");
  // CRDC angles
  dsDraw(c4,7,dctx,sctx,simNormalization,"r");
  dsDraw(c4,8,dcty,scty,simNormalization,"r");
  // fragment v0
  simNormalization = dsNorm(dfv0[0],sfv0[0],vBins);
  dsDrawTitle(c4,9,dfv0[0],sfv0[0],simNormalization,"r","Fragment Velocity (tgt1)");
  simNormalization = dsNorm(dfv0[1],sfv0[1],vBins);
  dsDrawTitle(c4,10,dfv0[1],sfv0[1],simNormalization,"r","Fragment Velocity (tgt2)");
  simNormalization = dsNorm(dfv0[2],sfv0[2],vBins);
  dsDrawTitle(c4,11,dfv0[2],sfv0[2],simNormalization,"r","Fragment Velocity (tgt3)");

  TCanvas *c4a = new TCanvas("c4a","c4a",1800,400);c4a->Divide(4,1);
  // Si dE
  dsDraw(c4a,1,dsi0de,ssi0de,simNormalization,"r");
  dsDraw(c4a,2,dsi1de,ssi1de,simNormalization,"r");
  dsDraw(c4a,3,dsi2de,ssi2de,simNormalization,"r");
  dsDraw(c4a,4,dsi3de,ssi3de,simNormalization,"r");

  TCanvas *c3 = new TCanvas("c3","c3",1500,800);c3->Divide(3,2);
  TCanvas *c6 = new TCanvas("c6","c6",1500,800);c6->Divide(3,2);
  TLine *edLine[3];
  for(int i=0;i<3;i++){
    simNormalization = dsNorm(dfv[i],sfv[i],fvBins);
    dsDrawTitle(c6,i+1,dnv[i],snv[i],simNormalization,"l",Form("Neutron Velocity (tgt%i)",i+1));
    dsDrawTitle(c6,i+4,dfv[i],sfv[i],simNormalization,"l",Form("Fragment Velocity (tgt%i)",i+1));
    dsDrawTitle(c3,i+4,drv[i],srv[i],simNormalization,"r",Form("Relative Velocity (tgt%i)",i+1));

    simNormalization = dsNormRng(ded[i],sed[i],0.4);
    dsDraw(c3,i+1,ded[i],sed[i],simNormalization,"r");

    c3->cd(i+1);
    edLine[i] = new TLine(0.4,0.,0.4,ded[i]->GetMaximum());
    edLine[i]->SetLineColor(1); edLine[i]->SetLineWidth(3);
    edLine[i]->Draw("SAME");
  }

}// END FUNCTION dsF27O24()


void F27O24O22(){
  TFile *df1 = new TFile("/mnt/analysis/e15118/analyzed/F27O24_tshift1.0ns.root","READ");
  TFile *df2 = new TFile("/mnt/analysis/e15118/analyzed/F27O22_tshift1.0ns.root","READ");

  TTree *t1 = (TTree*)df1->Get("at");
  TTree *t2 = (TTree*)df2->Get("at");

  TH1D *hO24rv[3];
  TH1D *hO22rv[3];
  for(int i=0;i<3;i++){
    hO24rv[i] = MakeH1(t1,"n0.v - frag.v",Form("hO24rv%i",i+1),rvBins,rv1,rv2,Form("%s && edecay<0.4",valid),"cm/ns");
    hO22rv[i] = MakeH1(t2,"n0.v - frag.v",Form("hO22rv%i",i+1),rvBins,rv1,rv2,Form("%s && edecay<0.4",valid),"cm/ns");
  }

  TH1D *h24rv = sumTargets(hO24rv,"Relative Velocity {edecay < 400 keV};v_{n} - v_{f} [cm/ns]");
  TH1D *h22rv = sumTargets(hO22rv,"Relative Velocity {edecay < 400 keV};v_{n} - v_{f} [cm/ns]");

  h24rv->SetLineColor(2); h24rv->SetFillColor(2); h24rv->SetFillStyle(3345);
  h22rv->SetLineColor(1); h22rv->SetFillColor(1); h22rv->SetFillStyle(3354);

  h24rv->SetStats(0);
  h22rv->SetStats(0);

  TPaveText *pt24 = CustomStatsBox(h24rv,1,2,0,h24rv->GetMaximum());
  TPaveText *pt22 = CustomStatsBox(h22rv,1,1,1,h24rv->GetMaximum());

  TLegend *legend = new TLegend(0.15,0.7,0.35,0.9);
  legend->AddEntry(h24rv,"O-24","f");
  legend->AddEntry(h22rv,"O-22","f");

  TCanvas *c3 = new TCanvas("c3","c3",500,400);
  h24rv->Draw();
  h22rv->Draw("SAME");
  pt24->Draw("SAME");
  pt22->Draw("SAME");
  legend->Draw("SAME");

}
