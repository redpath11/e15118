#include "Ecal.hh"

Double_t fGaus(Double_t *x, Double_t *par){
  Double_t xx = x[0];
  Double_t arg = 0.;
  if(par[2] != 0) arg = (xx - par[1])/par[2];
  Double_t f = par[0]*TMath::Exp(-0.5*arg*arg);
  return f;
}


Double_t fTwoGauss(Double_t *x, Double_t *par){
  Double_t f = fGaus(x,&par[0]) + fGaus(x,&par[3]);
  return f;
}


SiEcal::SiEcal(){
  m_goodFile=false;
  m_histsSet=false;
  m_beamSet=false;
  m_anodesFit=false;
  m_calibrated=false;

  beam[0] = "F27_tight";
  beam[1] = "Ne28_tight";
  beam[2] = "Ne29_tight";
  beam[3] = "Na30_tight";
  ictf[0] = "unr27F_ictof2";
  ictf[1] = "unr28Ne_ictof";
  ictf[2] = "unr29Ne_ictof3";
  ictf[3] = "unr30Na_ictof2";

  m_beamIndex=-999; m_beamColor=1;
  m_beamStyle = 1;

  rawBins=200; raw1=0; raw2=4000;
  calBins = 150; cal1=0.; cal2=30.;

  /* Unreacted beam dE (from LISE++)
  // 1 February 2018
  // Si thicknesses: 140 135 138 142 (+/- 1) um
  // Be thicknesses: 4100 um, 3736 um, 3102 um (+/- 4 um)
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  fragDE[0][0] = 14.826; fragDE[0][1] = 15.916; fragDE[0][2] = 18.554; fragDE[0][3] = 22.619;
  // Ne-28
  fragDE[1][0] = 16.757; fragDE[1][1] = 17.852; fragDE[1][2] = 20.606; fragDE[1][3] = 24.706;
  // Ne-29
  fragDE[2][0] = 17.556; fragDE[2][1] = 18.897; fragDE[2][2] = 22.102; fragDE[2][3] = 27.336;
  // Na-30
  fragDE[3][0] = 19.752; fragDE[3][1] = 21.179; fragDE[3][2] = 24.649; fragDE[3][3] = 30.147;
  // 
  // Variation to thinner targets (less dE) relative to dE calculated above. 29 January 2018
  // (x0 - x) / x0
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  varpDE[0][0] = 0.00715; varpDE[0][1] = 0.007540;  varpDE[0][2] = 0.007707; varpDE[0][3] = 0.008046;
  // Ne-28
  varpDE[1][0] = 0.007161; varpDE[1][1] = 0.007562; varpDE[1][2] = 0.007668; varpDE[1][3] = 0.007933;
  // Ne-29
  varpDE[2][0] = 0.007177; varpDE[2][1] = 0.007567; varpDE[2][2] = 0.007782; varpDE[2][3] = 0.008231;
  // Na-30
  varpDE[3][0] = 0.007189; varpDE[3][1] = 0.007602; varpDE[3][2] = 0.007708; varpDE[3][3] = 0.008061;
  // 
  // Variation to thicker targets (more dE) relative to dE calculated above. 29 January 2018
  // (x0 - x) / x0
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  varnDE[0][0] = -0.00715; varnDE[0][1] = -0.00760; varnDE[0][2] = -0.00771; varnDE[0][3] = -0.00805;
  // Ne-28
  varnDE[1][0] = -0.00716; varnDE[1][1] = -0.00756; varnDE[1][2] = -0.00767; varnDE[1][3] = -0.00797;
  // Ne-29
  varnDE[2][0] = -0.00718; varnDE[2][1] = -0.00762; varnDE[2][2] = -0.00778; varnDE[2][3] = -0.00827;
  // Na-30
  varnDE[3][0] = -0.00714; varnDE[3][1] = -0.00755; varnDE[3][2] = -0.00775; varnDE[3][3] = -0.00806;
*/

  /* Unreacted beam dE (from LISE++)*/
  // Si thicknesses: 138.75 um
  // Be thicknesses: 4100 um, 3736 um, 3102 um
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  fragDE[0][0] = 14.671; fragDE[0][1] = 16.304; fragDE[0][2] = 18.57; fragDE[0][3] = 21.947;
  // Ne-28
  fragDE[1][0] = 16.565; fragDE[1][1] = 18.288; fragDE[1][2] = 20.629; fragDE[1][3] = 23.99;
  // Ne-29
  fragDE[2][0] = 17.353; fragDE[2][1] = 19.356; fragDE[2][2] = 22.145; fragDE[2][3] = 26.494;
  // Na-30
  fragDE[3][0] = 19.524; fragDE[3][1] = 21.695; fragDE[3][2] = 24.662; fragDE[3][3] = 29.252;
  // 
  // Variation to thinner targets (less dE) relative to dE calculated above. 29 January 2018
  // (x0 - x) / x0
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  varpDE[0][0] = 0.02706; varpDE[0][1] = 0.027294; varpDE[0][2] = 0.027787; varpDE[0][3] = 0.028751;
  // Ne-28
  varpDE[1][0] = 0.027045; varpDE[1][1] = 0.02734; varpDE[1][2] = 0.027776; varpDE[1][3] = 0.028554;
  // Ne-29
  varpDE[2][0] = 0.027085; varpDE[2][1] = 0.02733; varpDE[2][2] = 0.02741; varpDE[2][3] = 0.029025;
  // Na-30
  varpDE[3][0] = 0.027095; varpDE[3][1] = 0.027333; varpDE[3][2] = 0.027897; varpDE[3][3] = 0.02875;
  // 
  // Variation to thicker targets (more dE) relative to dE calculated above. 29 January 2018
  // (x0 - x) / x0
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  varnDE[0][0] = -0.02345; varnDE[0][1] = -0.02374; varnDE[0][2] = -0.02423; varnDE[0][3] = -0.02511;
  // Ne-28
  varnDE[1][0] = -0.02348; varnDE[1][1] = -0.02373; varnDE[1][2] = -0.02414; varnDE[1][3] = -0.02493;
  // Ne-29
  varnDE[2][0] = -0.02351; varnDE[2][1] = -0.02371; varnDE[2][2] = -0.02389; varnDE[2][3] = -0.02536;
  // Na-30
  varnDE[3][0] = -0.02346; varnDE[3][1] = -0.02374; varnDE[3][2] = -0.02425; varnDE[3][3] = -0.02509;


  /* Unreacted beam dE (from LISE++)
  // Si thicknesses: 142 um, 138 um, 140 um, 135 um
  // Be thicknesses: 4104 um, 3744 um, 3106 um
  //       Si 0       |        Si 1         |         Si 2        |         Si 3        |
  // F-27
  fragDE[0][0] = 15.02; fragDE[0][1] = 16.22; fragDE[0][2] = 18.76; fragDE[0][3] = 21.39;
  // Ne-28
  fragDE[1][0] = 16.88; fragDE[1][1] = 18.06; fragDE[1][2] = 20.60; fragDE[1][3] = 23.00;
  // Ne-29
  fragDE[2][0] = 17.70; fragDE[2][1] = 19.17; fragDE[2][2] = 22.26; fragDE[2][3] = 25.52;
  // Na-30
  fragDE[3][0] = 19.73; fragDE[3][1] = 21.17; fragDE[3][2] = 24.34; fragDE[3][3] = 27.38;
  */
}


SiEcal::~SiEcal(){};


void SiEcal::SetBeam(TString beam){
  if(beam.CompareTo("F27") == 0){
    m_beamIndex=0; m_beamStyle=20;
    m_beamSet=true; m_beamColor=810;
  }
  else if(beam.CompareTo("Ne28") == 0){
    m_beamIndex=1; m_beamStyle=21;
    m_beamSet=true; m_beamColor=4;
  }
  else if(beam.CompareTo("Ne29") == 0){
    m_beamIndex=2; m_beamSet=true;
    m_beamStyle=22;m_beamColor=38;
  }
  else if(beam.CompareTo("Na30") == 0){
    m_beamIndex=3; m_beamStyle=23;
    m_beamSet=true; m_beamColor=8;
  }
  else{ cout << "Specify valid beam: F27, Ne28, Ne29, Na30." << endl; return;}
  printf("Beam: %s; Index = %i\n",beam.Data(),m_beamIndex);
}


void SiEcal::SetFile(Int_t run){
  TString filename = Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",run);
  ifstream test; test.open(filename.Data());
  if(test.fail()){
    cout << "Error opening " << filename.Data() << endl;
    m_goodFile=false;
    return;
  }
  else{
    f = new TFile(filename,"READ");
    t = (TTree*)f->Get("t");
    m_goodFile = true;
    m_run=run;
    printf("File: %s\n",filename.Data());
  }
  test.close();

}


void SiEcal::SetFiltered(TString file){
  ifstream test; test.open(file.Data());
  if(test.fail()){
    cout << "Error opening " << file.Data() << endl;
    m_goodFile=false;
    return;
  }
  else{
    f = new TFile(file,"READ");
    t = (TTree*)f->Get("t");
    m_goodFile = true;
    m_run=999;
    printf("File: %s\n",file.Data());
  }
  test.close();
}


void SiEcal::SetHistograms(){
char gate[4096];
sprintf(gate,"tof.a1900_pot!=-1 && %s && %s",beam[m_beamIndex],ictf[m_beamIndex]);
if(m_goodFile && m_beamSet && !m_histsSet){
  BeamCuts(beamCut);
  ElementCuts(icCut);
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);


  for(int i=0;i<4;i++){
    dE[i] = new TH1D(Form("dE%i",i),Form("Si %i dE;ADC channel",i),rawBins,raw1,raw2);
    t->Project(Form("dE%i",i),Form("st.anode[%i]",i),Form("st.anode[%i]!=-1 && %s",i,gate));
  }
  if(m_calibrated){
    cout << "Filling calibrated spectra." << endl;
    for(int i=0;i<4;i++){
      dEcal[i] = new TH1D(Form("dEcal%i",i),Form("Si %i dEcal;dE [MeV];Counts / %3.1f MeV",
        i,(cal2-cal1)/Double_t(calBins)),
        calBins,cal1,cal2);
      t->Project(Form("dEcal%i",i),Form("de%i",i),Form("st.anode[%i]!=-1 && %s",i,gate));
    }
  }
  m_histsSet=true;
}
else if(!m_goodFile){cout << "No file set." << endl; return;}
else if(!m_beamSet) {cout << "No beam set." << endl; return;}
else if(m_histsSet) {cout << "Histograms already filled." << endl;return;}
else cout << "Shit's broke." << endl; return;
}


void SiEcal::PlotDEfiltered(){
if(m_goodFile && m_run==999 && m_calibrated){
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);
  TCanvas *c10 = new TCanvas("c10","c10",1800,400);c10->Divide(4,1);
  TCanvas *c11 = new TCanvas("c11","c11",1800,400);c11->Divide(4,1);
  for(int i=0;i<4;i++){
    dE[i]    = new TH1D(Form("dE%i",i),   Form("Si %i dE;ADC channel",i),rawBins,raw1,raw2);
    dEcal[i] = new TH1D(Form("dEcal%i",i),Form("Si %i dEcal;dE [MeV];Counts / %3.1f MeV",
      i,(cal2-cal1)/Double_t(calBins)),calBins,cal1,cal2);
    t->Project(Form("dE%i",i),Form("st.anode[%i]",i),"");
    t->Project(Form("dEcal%i",i),Form("de%i",i),"");
    c10->cd(i+1); dE[i]->GetYaxis()->SetTitleOffset(1.4); dE[i]->Draw();
    c11->cd(i+1); dEcal[i]->GetYaxis()->SetTitleOffset(1.4); dEcal[i]->Draw();
  }

  TCanvas *c12 = new TCanvas("c12","c12",1500,400);c12->Divide(3,1);
  for(int i=0;i<3;i++){
    tgtCal[i] = new TH2D(Form("tgtCal%i",i),
      Form("Si %i : Si %i de;dE %i [MeV];dE %i [MeV]",i+1,i,i,i+1),
      calBins,cal1,cal2,calBins,cal1,cal2);
    t->Project(Form("tgtCal%i",i),Form("de%i:de%i",i+1,i),"");
    c12->cd(i+1); tgtCal[i]->Draw("COLZ");
  }

  /* Fit raw*/
  c10->cd(1); dE[0]->Fit("gaus","R","",1200.,1700.);
  Double_t *parameters = new Double_t[6];
  parameters[0] = 150.; parameters[1] = 1310; parameters[2] = 50.;
  parameters[3] = 250.; parameters[4] = 1680; parameters[5] = 50.;
  TF1  *f2r[3];

  for(int i=1;i<4;i++){
    int index=i-1;

    f2r[index] = new TF1(Form("f2r%i",i),fTwoGauss,1000.,2500.,6);
    f2r[index]->SetParNames("Const1","Mean1","Sigma1","Const2","Mean2","Sigma2");
    f2r[index]->SetParameters(parameters);
    c10->cd(i+1); dE[i]->Fit(Form("f2r%i",i),"R");
    
  }
//  c10->cd(4);dEcal[3]->Fit("gaus","R","",10.,20.);// O-22 case

  // Fit calibrated with calibration parameters set here
  c11->cd(1); dEcal[0]->Fit("gaus","R","",10.,20.);
//  Double_t *parameters = new Double_t[6];
  parameters[0] = 100.; parameters[1] = 13.1; parameters[2] = 1.;
  parameters[3] = 100.; parameters[4] = 15.8; parameters[5] = 1.;
  TF1  *f2g[3];


  const Double_t const1[3] = {80.0,120.,140.};
  const Double_t mean1[3] = {13.1,14.8,16.7};
  const Double_t const2[3] = {120.,78.0,32.0};
  const Double_t mean2[3] = {16.0,18.3,21.1};

  cout << endl << endl << "Fits to calibrated dE spectra." << endl << endl;

  for(int i=1;i<4;i++){
    int index=i-1;

    parameters[0] = const1[index]; parameters[1] = mean1[index]; parameters[2] = 1.;
    parameters[3] = const2[index]; parameters[4] = mean2[index]; parameters[5] = 1.;
    
    f2g[index] = new TF1(Form("f2gaus%i",i),fTwoGauss,10.,25.,6);
    f2g[index]->SetParNames("Const1","Mean1","Sigma1","Const2","Mean2","Sigma2");
    f2g[index]->SetParameters(parameters);
    c11->cd(i+1); dEcal[i]->Fit(Form("f2gaus%i",i),"R");
    
  }
  c11->cd(4);dEcal[3]->Fit("gaus","R","",10.,20.);// O-22 case

}
else if(m_goodFile && m_run==999 && !m_calibrated){
  cout << "Plotting raw anode spectra." << endl;
  TCanvas *c10 = new TCanvas("c10","c10",1800,400);c10->Divide(4,1);
  for(int i=0;i<4;i++){
    dE[i]    = new TH1D(Form("dE%i",i),   Form("Si %i dE;ADC channel",i),rawBins,raw1,raw2);
    t->Project(Form("dE%i",i),Form("st.anode[%i]",i),"");
    c10->cd(i+1); dE[i]->Draw();
  }
}
else if(!m_goodFile){cout << "Set valid file." << endl;return;}
else if(m_run!=999){cout  << "Filtered file not set." << endl;return;}
else{cout << "Shit's broke." << endl;}
}


/* Plot d1, d2 w/ gate, d3 w/gate */
void SiEcal::PlotDEfilteredGated(Double_t s1,
				Double_t s2,
				TCanvas *c){
  Double_t gate[3] = {5.,s1,s2};
  TH1D *h[3];
  TLine *l[3];
  TCanvas *c13 = new TCanvas("c13","c13",1500,400);c13->Divide(3,1);
  for(int i=1;i<4;i++){
    h[i-1] = new TH1D(Form("h%i",i),
      Form("Si %i dE;dE [MeV];Counts / %3.1f MeV",i,(cal2-cal1)/Double_t(calBins)),
      calBins,cal1,cal2);
    t->Project(Form("h%i",i),Form("de%i",i),Form("de%i>%g",i-1,gate[i-1]));
    c13->cd(i);h[i-1]->Draw();
    l[i-1] = new TLine(gate[i-1],cal1,gate[i-1],cal2);
    l[i-1]->SetLineColor(2); l[i-1]->SetLineWidth(2);
    c->cd(i);l[i-1]->Draw("SAME");
  }

  cout << endl << endl << "Fits to gated tgt 2 tgt 3 spectra." << endl << endl;
  // Fit spectra for rxns in last two targets
  /* O-24
  const Double_t const1[3] = {120.,95.,60.};
  const Double_t const2[3] = {240.,115.,45.};
  const Double_t mean1[3]  = {12.9,14.7,17.1};
  const Double_t mean2[3]  = {16.2,18.3,21.4};
  */
  /* O-22 */
  const Double_t const1[3] = {65.,115.,60.};
  const Double_t const2[3] = {85.,27. ,45.};
  const Double_t mean1[3]  = {12.8,14.3,17.1};
  const Double_t mean2[3]  = {16.2,18.2,21.4};
  
  Double_t *parameters = new Double_t[6];
  TF1  *f2g[3];
  for(int i=1;i<3;i++){
  int index = i-1;
    parameters[0] = const1[index]; parameters[1] = mean1[index]; parameters[2] = 1.;
    parameters[3] = const2[index]; parameters[4] = mean2[index]; parameters[5] = 1.;
    f2g[index] = new TF1(Form("f2g%i",i),fTwoGauss,10.,25.,6);
    f2g[index]->SetParNames("Const1","Mean1","Sigma1","Const2","Mean2","Sigma2");
    f2g[index]->SetParameters(parameters);
    c13->cd(i); h[i-1]->Fit(Form("f2g%i",i),"R");
  }
  c13->cd(3); h[2]->Fit("gaus","R","",10.,25.);
}



void SiEcal::ClearHistograms(){
  for(int i=0;i<4;i++){
    dE[i]->~TH1D();
  }
  m_histsSet=false;
}


/*
void SiEcal::BeamsAnode(){
if(m_goodFile){
  BeamCuts(beamCut);
  ElementCuts(icCut);
  gStyle->SetStatX(0.9); gStyle->SetStatY(0.9); gStyle->SetStatH(0.2); gStyle->SetStatW(0.2);

  char gate[4096];
  for(int b=0;b<4;b++){
    for(int a=0;a<4;a++){
      sprintf(gate,"tof.a1900_pot!=-1 && %s && %s",beam[b],ictf[b]);
      beamAnode[b][a] = new TH1D(Form("b%ia%i",b,a),
        Form("anode%i {%s&&%s}",a,beam[b],ictf[b]),rawBins,raw1,raw2);
      t->Project(Form("b%ia%i",b,a),Form("st.anode[%i]",a),
        Form("st.anode[%i]!=-1 && %s",a,gate));
    }
  }

}
}
*/


void SiEcal::FitHistograms(){
if(m_histsSet){
  TF1 *fit;

  TCanvas *c0 = new TCanvas("c0","c0",1800,400);c0->Divide(4,1);

  for(int i=0;i<4;i++){
    c0->cd(i+1);
    anodeMean[m_beamIndex][i]=0.; anodeSigm[m_beamIndex][i]=0.;
    dE[i]->Fit("gaus","R","",100.,3000.);
    fit = dE[i]->GetFunction("gaus");
    anodeMean[m_beamIndex][i] = fit->GetParameter(1);
    anodeMerr[m_beamIndex][i] = fit->GetParError(1);
    anodeSigm[m_beamIndex][i] = fit->GetParameter(2);
    anodeSerr[m_beamIndex][i] = fit->GetParError(2);
  }
  m_anodesFit=true;

  c0->SaveAs(Form("/projects/e15118/redpath/analysis/calibrations/psd/r%i_anodeFits_%s%s.png",
    m_run,beam[m_beamIndex],ictf[m_beamIndex]));
}
}


void SiEcal::AnodeSummary(){
if(m_anodesFit){
  aSummary[m_beamIndex] = new TGraph(4,anodeMean[m_beamIndex],fragDE[m_beamIndex]);
  aSummary[m_beamIndex]->SetMarkerColor(m_beamColor);
  aSummary[m_beamIndex]->SetMarkerSize(1.);
  aSummary[m_beamIndex]->SetMarkerStyle(m_beamStyle);


  c1 = new TCanvas("c1","c1",500,400);c1->SetObjectStat(1);

  aSummary[m_beamIndex]->Draw("AP");

}
}


void SiEcal::DetectorSummary(){
if(m_anodesFit){
  ofstream calOutput("/projects/e15118/redpath/analysis/calibrations/psd/siCalibration.txt");
  Double_t dEslope[4]={0.,0.,0.,0.};
  Double_t dEoffst[4]={0.,0.,0.,0.};
  Double_t fitSlopeError[4]={0.,0.,0.,0.};
  Double_t fitOffstError[4]={0.,0.,0.,0.};
  TF1 *fit;
  TF1 *LoCalibration[4]; TF1 *HiCalibration[4];
  TH2I *frame[4];

  TCanvas *c2 = new TCanvas("c2","c2",1800,400);c2->Divide(4,1);
  for(int det=0;det<4;det++){
    Double_t x[4]={0.,0.,0.,0.};
    Double_t y[4]={0.,0.,0.,0.};
    Double_t xerr[4]={0.,0.,0.,0.};
    Double_t yerr1[4]={0.,0.,0.,0.};
    Double_t yerr2[4]={0.,0.,0.,0.};

    // sum over data points
    // (for a single detector)
    // used for plotting 1-sigma
    // calibration range
    Double_t sumX = 0.;
    Double_t sumY = 0.;

    for(int beam=0;beam<4;beam++){
      x[beam] = anodeMean[beam][det];
      xerr[beam] = anodeMerr[beam][det];
      y[beam] = fragDE[beam][det];
      yerr1[beam] = fragDE[beam][det]*varpDE[beam][det];// lower
      yerr2[beam] = TMath::Abs(fragDE[beam][det]*varnDE[beam][det]);// upper
      sumX += x[beam];
      sumY += y[beam];
    }

//    detSummary[det] = new TGraphErrors(4,x,y,xerr,yerr);
    detSummary[det] = new TGraphAsymmErrors(4,x,y,xerr,xerr,yerr1,yerr2);
    detSummary[det]->SetMarkerStyle(20);
    detSummary[det]->SetTitle(Form("Si%i;Raw dE [adc];dE [MeV]",det));
    c2->cd(det+1);
    detSummary[det]->Draw("AP");
    detSummary[det]->Fit("pol1");
    fit = (TF1*)detSummary[det]->GetFunction("pol1");
    dEslope[det] = fit->GetParameter(1);
    fitSlopeError[det] = fit->GetParError(1);
    dEoffst[det] = fit->GetParameter(0);
    fitOffstError[det] = fit->GetParError(0);

    LoCalibration[det] = new TF1(Form("lc%i",det),"[0]+[1]*x",1200,2900);
    HiCalibration[det] = new TF1(Form("hc%i",det),"[0]+[1]*x",1200,2900);
    // set parameters for edge functions
    Double_t lB = dEslope[det] + fitSlopeError[det];
    Double_t hB = dEslope[det] - fitSlopeError[det];
    Double_t lA = (sumY - lB*sumX)/4.;
    Double_t hA = (sumY - hB*sumX)/4.;
    LoCalibration[det]->SetParameter(0,lA);
    LoCalibration[det]->SetParameter(1,lB);
    HiCalibration[det]->SetParameter(0,hA);
    HiCalibration[det]->SetParameter(1,hB);
    LoCalibration[det]->SetLineColor(4); HiCalibration[det]->SetLineColor(4);

    frame[det] = new TH2I(Form("frame%i",det),
      Form("Si %i;Raw dE (adc);dE [MeV]",det),2,1000,3000,2,10,35);
    frame[det]->SetStats(0);
    c2->cd(det+1);
    frame[det]->Draw();
    detSummary[det]->Draw("SAMEP");
    LoCalibration[det]->Draw("SAME"); HiCalibration[det]->Draw("SAME");

  }

  cout << endl << setw(18) << "Detector |"
  		<< setw(36)<< "Slope (error) |"
		<< setw(36)<< "Offset (error) |" << endl;
  for(int i=0;i<4;i++){
    cout << setw(18) << i
    	<< setw(18) << dEslope[i] << "(" << fitSlopeError[i] << ")"
	<< setw(18) << dEoffst[i] << "(" << fitOffstError[i] << ")"
	<< endl;
    calOutput << i
    	<< setw(18) << dEslope[i]
	<< setw(18) << dEoffst[i] << endl;
  }

  calOutput.close();

  // Plot calibrated dE
  TCanvas *c3 = new TCanvas("c3","c3",1800,400);c3->Divide(4,1);
  TH1D *deCal[4];
  for(int det=0;det<4;det++){
    t->SetAlias(Form("de%i",det),Form("%g*st.anode[%i] + %g",dEslope[det],det,dEoffst[det]));
    deCal[det] = new TH1D(Form("deCal%i",det),
      Form("Si %i deCal;dE [MeV];Counts / 0.1 MeV",det),
      300,0,30);
    t->Project(Form("deCal%i",det),Form("de%i",det),
      Form("st.anode[%i]!=-1&&%s&&%s",det,beam[0],ictf[0]));
    c3->cd(det+1); deCal[det]->Draw();
  }

}
}


void SiEcal::ReadCalibration(){
if(!m_calibrated){
//  ifstream in("/projects/e15118/redpath/analysis/calibrations/psd/siCalibration.txt");

  int index=999;
  Double_t m[4]={0.0102815,
  	0.0103446,
	0.011704,
	0.0113039};
  Double_t off[4]={-0.822313,
  	-0.58409,
	-0.880354,
	-1.47755};

  Int_t nlines=0;
/*
  while(1){
    Double_t slope=0.; Double_t offset=0.;
//    in >> index >> m[index] >> off[index];
    in >> index >> slope >> offset;
    m[index]=slope; off[index]=offset;
    if(!in.good()){break;}
    nlines++;
  }
  in.close();
*/
  for(int i=0;i<4;i++){
    cout << setw(18) << m[i]
	<< setw(18) << off[i] << endl;
  }

  cout << nlines << " lines read." << endl;

  for(int det=0;det<4;det++){
    t->SetAlias(Form("de%i",det),Form("%g*st.anode[%i] + %g",m[det],det,off[det]));
  }
  m_calibrated=true;
}
else{cout << "Calibration aliases already set." << endl;}
}


void SiEcal::PlotDEcal(){
if(m_histsSet && !m_calibrated){
  TCanvas *c0 = new TCanvas("c0","c0",1800,400); c0->Divide(4,1);
  for(int i=0;i<4;i++){c0->cd(i+1); dE[i]->Draw();}
  cout << "Run SiEcal.ReadCalibration() or SiEcal.DetectorSummary() to plot dEcal." << endl;
}
else if(m_histsSet && m_calibrated){
  TCanvas *c0 = new TCanvas("c0","c0",1800,400); c0->Divide(4,1);
  for(int i=0;i<4;i++){c0->cd(i+1); dE[i]->Draw();}
  TCanvas *c1 = new TCanvas("c1","c1",1800,400); c1->Divide(4,1);
  for(int i=0;i<4;i++){c1->cd(i+1); dEcal[i]->GetYaxis()->SetTitleOffset(1.5); dEcal[i]->Draw();}
}
else{cout << "Run SiEcal.SetHistograms() first." << endl;}
}


void SiEcal::Velocity(){
if(m_calibrated){
  BeamCuts(beamCut);
  ElementCuts(icCut);
  TH1D *velocity[4];
  TH2D *hh = new TH2D("hh","\% velocity : crdc2.x",150,-150,150,100,-0.1,0.1);
  TCanvas *c12 = new TCanvas("c12","c12",1000,400);c12->Divide(2,1);
  for(int det=0;det<4;det++){
    t->SetAlias(Form("d%ibetaSq",det),Form("2.81/(de%i)",det));
    t->SetAlias(Form("d%ivelocity",det),Form("29.99792458 * sqrt(d%ibetaSq)",det));
    velocity[det] = new TH1D(Form("d%iv",det),"F-27 velocity;velocity [cm/ns]",120,9,15);
    t->Project(Form("d%iv",det),Form("d%ivelocity",det),
      Form("st.anode[%i]!=-1 &&%s&&%s",det,beam[0],ictf[0]));
  }
  t->Project("hh","((d3velocity) - 10.98) / 10.98:crdc2.x",
    "crdc2.x!=-1&&st.anode[3]!=-1&&F27_tight&&unr27F_ictof2");

  TLine *fLine = new TLine(-150.,-0.08334,150.,0.089135);// % velocity
  fLine->SetLineColor(4); fLine->SetLineWidth(3);

  c12->cd(2);
  velocity[3]->Draw();
  c12->cd(1);
  hh->Draw("COLZ");
  fLine->Draw("SAME");


}
else{cout << "Read in calibration parameters first." << endl;}
}


void r1051f27(){
  SiEcal s;
  s.SetBeam("F27");
  s.SetFile(1051);
  s.ReadCalibration();
  s.SetHistograms();
  s.PlotDEcal();
}


void r1179f27(){
  SiEcal ss;
  ss.SetBeam("F27");
  ss.SetFile(1179);
  ss.ReadCalibration();
  ss.SetHistograms();
  ss.PlotDEcal();
}


void r1051beams(){
  SiEcal s;
  s.SetFile(1051);
  s.SetBeam("F27");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("Ne28");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("Ne29");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("Na30");
  s.SetHistograms();
  s.FitHistograms();

  s.DetectorSummary();
}


void F27OisoCal(){
  SiEcal s;
  s.SetFiltered("/mnt/analysis/e15118/playground/all_27F_24O_28jan.root");
//  s.SetFiltered("/mnt/analysis/e15118/playground/all_27F_22O_28jan.root");
  s.ReadCalibration();
  s.PlotDEfiltered();
}


void F27OxygenCal(){
  SiEcal s;
  s.SetFiltered("/mnt/analysis/e15118/playground/all_27F_O_28jan.root");
  s.ReadCalibration();
  s.PlotDEfiltered();
}


void r1051f27velocity(){
  SiEcal s;
  s.SetFile(1051);
  s.SetBeam("F27");
  s.ReadCalibration();
  s.Velocity();
}



/*
Double_t SiEcal::fGaus(Double_t *x,Double_t *par){
  Double_t xx = x[0];
  Double_t arg = 0.;
  if(par[2]!=0) arg = (xx - par[1])/par[2];
  Double_t f = par[0]*TMath::Exp(-0.5*arg*arg);
  return f;
}
*/

void SiEcal::BeamCuts(TCutG *cutg[4]){
/* From files:
 * /projects/e15118/redpath/analysis/aliases/F27_tight.C
 * /projects/e15118/redpath/analysis/aliases/Ne28_tight.C
 * /projects/e15118/redpath/analysis/aliases/Ne29_tight.C
 * /projects/e15118/redpath/analysis/aliases/Na30_tight.C
*/
   cutg[0] = new TCutG("F27_tight",12);
   cutg[0]->SetVarX("tof.a1900_pot");
   cutg[0]->SetVarY("st.anode[0]");
   cutg[0]->SetTitle("Graph");
   cutg[0]->SetFillColor(1);
   cutg[0]->SetPoint(0,77.8896,1411.88);
   cutg[0]->SetPoint(1,78.3625,1304.18);
   cutg[0]->SetPoint(2,79.0738,1338.45);
   cutg[0]->SetPoint(3,79.6568,1367.82);
   cutg[0]->SetPoint(4,80.0455,1455.94);
   cutg[0]->SetPoint(5,80.1445,1563.64);
   cutg[0]->SetPoint(6,79.8328,1656.66);
   cutg[0]->SetPoint(7,79.4332,1676.24);
   cutg[0]->SetPoint(8,78.8685,1671.34);
   cutg[0]->SetPoint(9,78.2599,1641.97);
   cutg[0]->SetPoint(10,77.9885,1495.1);
   cutg[0]->SetPoint(11,77.8896,1411.88);
//   cutg[0].Draw("");
   cutg[0]->SetLineColor(2);
   cutg[0]->SetLineWidth(2);

   cutg[1] = new TCutG("Ne28_tight",14);
   cutg[1]->SetVarX("tof.a1900_pot");
   cutg[1]->SetVarY("st.anode[0]");
   cutg[1]->SetTitle("Graph");
   cutg[1]->SetFillColor(1);
   cutg[1]->SetPoint(0,74.7568,1870.01);
   cutg[1]->SetPoint(1,74.1352,1783.4);
   cutg[1]->SetPoint(2,73.7999,1624.62);
   cutg[1]->SetPoint(3,73.8244,1552.44);
   cutg[1]->SetPoint(4,74.2661,1513.95);
   cutg[1]->SetPoint(5,74.8304,1489.89);
   cutg[1]->SetPoint(6,75.3292,1513.95);
   cutg[1]->SetPoint(7,75.6073,1586.12);
   cutg[1]->SetPoint(8,75.7627,1658.3);
   cutg[1]->SetPoint(9,75.7218,1788.21);
   cutg[1]->SetPoint(10,75.5173,1874.82);
   cutg[1]->SetPoint(11,75.2393,1903.69);
   cutg[1]->SetPoint(12,74.7404,1884.44);
   cutg[1]->SetPoint(13,74.7568,1870.01);
//   cutg[1].Draw("");
   cutg[1]->SetLineColor(2);
   cutg[1]->SetLineWidth(2);

   
   cutg[2] = new TCutG("Ne29_tight",16);
   cutg[2]->SetVarX("tof.a1900_pot");
   cutg[2]->SetVarY("st.anode[0]");
   cutg[2]->SetTitle("Graph");
   cutg[2]->SetFillColor(1);
   cutg[2]->SetLineColor(2);
   cutg[2]->SetLineWidth(2);
   cutg[2]->SetPoint(0,75.993,1714.48);
   cutg[2]->SetPoint(1,76.1067,1626.85);
   cutg[2]->SetPoint(2,76.3865,1594.56);
   cutg[2]->SetPoint(3,76.7625,1617.62);
   cutg[2]->SetPoint(4,77.156,1636.07);
   cutg[2]->SetPoint(5,77.4751,1631.46);
   cutg[2]->SetPoint(6,77.7374,1677.58);
   cutg[2]->SetPoint(7,77.9691,1765.22);
   cutg[2]->SetPoint(8,77.956,1875.92);
   cutg[2]->SetPoint(9,77.7156,1908.21);
   cutg[2]->SetPoint(10,77.3134,1903.6);
   cutg[2]->SetPoint(11,76.9111,1903.6);
   cutg[2]->SetPoint(12,76.5439,1875.92);
   cutg[2]->SetPoint(13,76.1067,1843.63);
   cutg[2]->SetPoint(14,76.0367,1788.28);
   cutg[2]->SetPoint(15,75.993,1714.48);
//   cutg[2].Draw("");
  cutg[2]->SetLineColor(2);
  cutg[2]->SetLineWidth(2);


   
   cutg[3] = new TCutG("Na30_tight",20);
   cutg[3]->SetVarX("tof.a1900_pot");
   cutg[3]->SetVarY("st.anode[0]");
   cutg[3]->SetTitle("Graph");
   cutg[3]->SetFillColor(1);
   cutg[3]->SetLineColor(2);
   cutg[3]->SetLineWidth(2);
   cutg[3]->SetPoint(0,72.7015,1903.55);
   cutg[3]->SetPoint(1,72.8897,1847.9);
   cutg[3]->SetPoint(2,73.2638,1812.35);
   cutg[3]->SetPoint(3,73.6571,1816.99);
   cutg[3]->SetPoint(4,73.9684,1829.36);
   cutg[3]->SetPoint(5,74.1639,1898.91);
   cutg[3]->SetPoint(6,74.2242,1960.73);
   cutg[3]->SetPoint(7,74.2362,2039.56);
   cutg[3]->SetPoint(8,74.2049,2102.93);
   cutg[3]->SetPoint(9,74.077,2141.57);
   cutg[3]->SetPoint(10,73.9129,2169.39);
   cutg[3]->SetPoint(11,73.7416,2161.66);
   cutg[3]->SetPoint(12,73.5992,2144.66);
   cutg[3]->SetPoint(13,73.522,2130.75);
   cutg[3]->SetPoint(14,73.3386,2085.93);
   cutg[3]->SetPoint(15,73.1745,2055.02);
   cutg[3]->SetPoint(16,73.0176,2011.74);
   cutg[3]->SetPoint(17,72.8149,1953.01);
   cutg[3]->SetPoint(18,72.7353,1926.73);
   cutg[3]->SetPoint(19,72.7015,1903.55);
   //cutg[3].Draw("");
  cutg[3]->SetLineColor(2);
  cutg[3]->SetLineWidth(2);

   cutg[4] = new TCutG("AllO_ictof2",16);
   cutg[4]->SetVarX("tof.pot_thin");
   cutg[4]->SetVarY("ic_sum");
   cutg[4]->SetTitle("AllO_ictof2");
   cutg[4]->SetFillColor(1);
   cutg[4]->SetLineColor(2);
   cutg[4]->SetLineWidth(2);
   cutg[4]->SetPoint(0,3.99107,285.045);
   cutg[4]->SetPoint(1,5.16964,328.501);
   cutg[4]->SetPoint(2,6.61607,356.285);
   cutg[4]->SetPoint(3,8.91964,385.493);
   cutg[4]->SetPoint(4,10.2321,397.604);
   cutg[4]->SetPoint(5,12.5625,411.14);
   cutg[4]->SetPoint(6,12.4286,399.741);
   cutg[4]->SetPoint(7,11.3036,369.821);
   cutg[4]->SetPoint(8,9.83036,335.625);
   cutg[4]->SetPoint(9,8.19643,306.417);
   cutg[4]->SetPoint(10,7.52679,294.306);
   cutg[4]->SetPoint(11,6.1875,272.934);
   cutg[4]->SetPoint(12,4.63393,260.823);
   cutg[4]->SetPoint(13,4.04464,262.96);
   cutg[4]->SetPoint(14,3.83036,272.934);
   cutg[4]->SetPoint(15,3.99107,285.045);


}


void SiEcal::ElementCuts(TCutG *cutg[4]){

/*
 * /projects/e15118/redpath/analysis/aliases/unr27F_ictof2.C
 * /projects/e15118/redpath/analysis/aliases/unr28Ne_ictof.C
 * /projects/e15118/redpath/analysis/aliases/unr29Ne_ictof3.C
 * /projects/e15118/redpath/analysis/aliases/unr30Na_ictof2.C
*/
  t->SetAlias("ic_sum","(ic.cal[1]+ic.cal[2]+ic.cal[3]+ic.cal[5]+ic.cal[6]+ic.cal[8]+ic.cal[9]+ic.cal[10]+ic.cal[11]+ic.cal[12]+ic.cal[13]+ic.cal[14])/12");

   cutg[0] = new TCutG("unr27F_ictof2",16);
   cutg[0]->SetVarX("tof.pot_thin");
   cutg[0]->SetVarY("ic_sum");
   cutg[0]->SetTitle("Graph");
   cutg[0]->SetFillColor(1);
   cutg[0]->SetLineColor(2);
   cutg[0]->SetLineWidth(2);
   cutg[0]->SetPoint(0,6.29119,426.16);
   cutg[0]->SetPoint(1,6.69413,439.346);
   cutg[0]->SetPoint(2,8.81626,478.903);
   cutg[0]->SetPoint(3,8.97744,473.629);
   cutg[0]->SetPoint(4,9.08489,465.717);
   cutg[0]->SetPoint(5,9.13861,449.895);
   cutg[0]->SetPoint(6,9.03116,434.072);
   cutg[0]->SetPoint(7,8.92371,420.886);
   cutg[0]->SetPoint(8,8.25215,405.063);
   cutg[0]->SetPoint(9,6.66726,370.781);
   cutg[0]->SetPoint(10,6.37178,368.143);
   cutg[0]->SetPoint(11,6.07629,376.055);
   cutg[0]->SetPoint(12,5.9957,399.789);
   cutg[0]->SetPoint(13,6.13001,418.249);
   cutg[0]->SetPoint(14,6.26433,423.523);
   cutg[0]->SetPoint(15,6.29119,426.16);

   cutg[1] = new TCutG("unr28Ne_ictof",15);
   cutg[1]->SetVarX("tof.pot_thin");
   cutg[1]->SetVarY("ic_sum");
   cutg[1]->SetTitle("Graph");
   cutg[1]->SetFillColor(1);
   cutg[1]->SetLineColor(2);
   cutg[1]->SetLineWidth(2);
   cutg[1]->SetPoint(0,3.40326,425.505);
   cutg[1]->SetPoint(1,3.60047,419.192);
   cutg[1]->SetPoint(2,3.94112,425.505);
   cutg[1]->SetPoint(3,4.56863,444.444);
   cutg[1]->SetPoint(4,4.85549,453.283);
   cutg[1]->SetPoint(5,4.96307,463.384);
   cutg[1]->SetPoint(6,4.99892,474.747);
   cutg[1]->SetPoint(7,4.96307,486.111);
   cutg[1]->SetPoint(8,4.81964,489.899);
   cutg[1]->SetPoint(9,4.56863,491.162);
   cutg[1]->SetPoint(10,4.31763,481.061);
   cutg[1]->SetPoint(11,3.85148,467.172);
   cutg[1]->SetPoint(12,3.47497,450.758);
   cutg[1]->SetPoint(13,3.40326,433.081);
   cutg[1]->SetPoint(14,3.40326,425.505);

   cutg[2] = new TCutG("unr29Ne_ictof3",17);
   cutg[2]->SetVarX("tof.pot_thin");
   cutg[2]->SetVarY("ic_sum");
   cutg[2]->SetTitle("Graph");
   cutg[2]->SetFillColor(1);
   cutg[2]->SetLineColor(2);
   cutg[2]->SetLineWidth(2);
   cutg[2]->SetPoint(0,5.85526,528.92);
   cutg[2]->SetPoint(1,5.69862,523.693);
   cutg[2]->SetPoint(2,5.26786,513.24);
   cutg[2]->SetPoint(3,4.99373,502.787);
   cutg[2]->SetPoint(4,5.03289,480.139);
   cutg[2]->SetPoint(5,5.2287,460.976);
   cutg[2]->SetPoint(6,5.65946,460.976);
   cutg[2]->SetPoint(7,6.44267,481.882);
   cutg[2]->SetPoint(8,7.65664,508.014);
   cutg[2]->SetPoint(9,8.40069,530.662);
   cutg[2]->SetPoint(10,8.43985,553.31);
   cutg[2]->SetPoint(11,8.24405,567.247);
   cutg[2]->SetPoint(12,7.8916,572.474);
   cutg[2]->SetPoint(13,7.57832,568.99);
   cutg[2]->SetPoint(14,7.03008,560.279);
   cutg[2]->SetPoint(15,5.89442,532.404);
   cutg[2]->SetPoint(16,5.85526,528.92);

   cutg[3] = new TCutG("unr30Na_ictof2",19);
   cutg[3]->SetVarX("tof.pot_thin");
   cutg[3]->SetVarY("ic_sum");
   cutg[3]->SetTitle("Graph");
   cutg[3]->SetFillColor(1);
   cutg[3]->SetLineColor(2);
   cutg[3]->SetLineWidth(2);
   cutg[3]->SetPoint(0,2.78311,517.22);
   cutg[3]->SetPoint(1,2.97842,517.22);
   cutg[3]->SetPoint(2,3.25744,519.963);
   cutg[3]->SetPoint(3,3.72247,529.841);
   cutg[3]->SetPoint(4,4.1224,540.268);
   cutg[3]->SetPoint(5,4.46652,550.695);
   cutg[3]->SetPoint(6,4.79204,567.159);
   cutg[3]->SetPoint(7,4.84784,578.683);
   cutg[3]->SetPoint(8,4.82924,591.854);
   cutg[3]->SetPoint(9,4.75484,600.634);
   cutg[3]->SetPoint(10,4.56882,604.476);
   cutg[3]->SetPoint(11,4.34561,601.732);
   cutg[3]->SetPoint(12,3.97359,591.305);
   cutg[3]->SetPoint(13,3.55506,575.939);
   cutg[3]->SetPoint(14,3.00632,555.085);
   cutg[3]->SetPoint(15,2.78311,540.268);
   cutg[3]->SetPoint(16,2.71801,531.488);
   cutg[3]->SetPoint(17,2.73661,522.159);
   cutg[3]->SetPoint(18,2.78311,517.22);

}
