#include "ThinToF.hh"

ThinToF::ThinToF(){
  TGaxis::SetMaxDigits(4);
  m_goodFile=false;
  m_calibrated=false;

  raw = "raw::sweeper.";

  t_slope = 0.0625;

  t_offset[0] = -0.8;
  t_offset[1] = -1.0404;
  t_offset[2] = 2.6626;
  t_offset[3] = -0.598611;

  q_slope[0] = 0.698995;
  q_slope[1] = 0.424234;
  q_slope[2] = 1.01571;
  q_slope[3] = 1.0;

  q_offset[0] = 72.4834;
  q_offset[1] = 175.016;
  q_offset[2] = 17.6865;
  q_offset[3] = 0.;

  tBins = 800;
  t1=-25.; t2 = 25.;

  qBins=400;
  q1=0.; q2=4000;


}


ThinToF::~ThinToF(){};


Double_t fGaus(Double_t *x, Double_t *par){
  Double_t xx = x[0];
  Double_t arg = 0.;
  if(par[2] != 0) arg = (xx - par[1])/par[2];
  Double_t f = par[0]*TMath::Exp(-0.5*arg*arg);
  return f;
}


Double_t fTwoGaus(Double_t *x, Double_t *par){
  Double_t f = fGaus(x,&par[0]) + fGaus(x,&par[3]);
  return f;
}


//void ThinToF::SetFile(TString filename){
void ThinToF::SetFile(Int_t run){
  TString filename = Form("/mnt/analysis/e15118/root_merged/run-%i-merged.root",run);
  ifstream test; test.open(filename.Data());
  if(test.fail()){
    cout << "Error opening " << filename.Data() << endl;
    m_goodFile=false;
    return;
  }
  else{
    f = new TFile(filename,"READ");
    t = (TTree*)f->Get("t");
    m_goodFile=true;
    printf("File: %s\n",filename.Data());
  }
  test.close();
}


void ThinToF::Calibrate(){
if(!m_calibrated){
  t->SetAlias("js",Form("thin.traw[0] * %g",t_slope));
  char gate[4096];
  // prepare canvas
  c0 = new TCanvas("c0","c0",1800,400);c0->Divide(4,1);
  c0->SetObjectStat(1);
  // calibrate thin times
  for(int i=0;i<4;i++){
    // set alias for calibrated time
//    t->SetAlias(Form("tcal%i",i),Form("(thin.traw[%i] * %g) - js + %g",i,t_slope,t_offset[i]));
    t->SetAlias(Form("tcal%i",i),Form("(thin.traw[%i] * %g) - js",i,t_slope));// no offset
    // plot calibrated time
    sprintf(gate,"thin.traw[%i]!=-1",i);
    tcal[i] = new TH1D(Form("tcal%i",i),Form("tcal[%i] {%s};tcal[%i] [ns];Counts / 0.0625 ns",i,gate,i),
      tBins,t1,t2);
    tcal[i]->GetYaxis()->SetTitleOffset(1.4);
    t->Project(Form("tcal%i",i),Form("tcal%i",i),gate);
    c0->cd(i+1); tcal[i]->Draw();
  }

  c1 = new TCanvas("c1","c1",500,400);
  c1->SetObjectStat(1);

  t->SetAlias("ptcal",Form("pot.traw * %g - js",t_slope));
  ptcal = new TH1D("ptcal","Pot tcal {pot.traw!=-1};tcal [ns];Counts / 0.0625 ns",
    tBins,t1,t2);
  ptcal->GetYaxis()->SetTitleOffset(1.4);
  t->Project("ptcal","ptcal","pot.traw!=-1");
  ptcal->Draw();

  m_calibrated=true;

}
else{cout << "Calibrations applied." << endl;return;}
}


void ThinToF::PotThin(){
if(m_calibrated){
  c2 = new TCanvas("c2","c2",1800,400);c2->Divide(4,1);
  c2->SetObjectStat(1);

  char gate[4096];
  for(int i=0;i<4;i++){
    t->SetAlias(Form("tofpt%i",i),Form("ptcal - tcal%i",i));
    sprintf(gate,"thin.traw[%i]!=-1 && pot.traw!=-1",i);
    tofpt[i] = new TH1D(Form("tofpt%i",i),Form("ToF (pot - thin%i) {%s};ToF [ns];Counts / 0.0625 ns"
      ,i,gate),tBins,t1,t2);
    tofpt[i]->GetYaxis()->SetTitleOffset(1.4);
    t->Project(Form("tofpt%i",i),Form("tofpt%i",i),gate);
    c2->cd(i+1); tofpt[i]->Draw();
  }
}
else{cout << "Run ThinToF::Calibrate() first." << endl;}
}


void ThinToF::ToFq(){
if(m_calibrated){
  c3 = new TCanvas("c3","c3",1800,400);c3->Divide(4,1);
  c3->SetObjectStat(1);

  char gate[4096];
  for(int i=0;i<4;i++){
    sprintf(gate,"thin.traw[%i]!=-1 && pot.traw!=-1",i);
    tofq[i] = new TH2D(Form("tofq%i",i),Form("ToF : thin q (ch%i) {%s};ToF [ns]; q (arb)",i,gate),
      tBins,t1,t2,qBins,q1,q2);
    tofq[i]->GetYaxis()->SetTitleOffset(1.4);
    t->Project(Form("tofq%i",i),Form("thin.qraw[%i]:tofpt%i",i,i),gate);
    c3->cd(i+1); tofq[i]->Draw("COLZ");
  }
}
}


void run(){
  ThinToF t;
  t.SetFile(1051);
  t.Calibrate();
  t.PotThin();
  t.ToFq();
}
