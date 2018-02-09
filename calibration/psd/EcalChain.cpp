#include "EcalChain.hh"

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
  t = new TChain("t");
  m_goodFile=false;
  m_histsSet=false;
  m_beamSet=false;
  m_anodesFit=false;
  m_calibrated=false;

  beam[0] = "F27_tight";
  beam[1] = "Ne28_tight";
  beam[2] = "Ne29_tight";
  beam[3] = "Na30_tight";
  beam[4] = "beamO21";
  beam[5] = "beamO22";
  beam[6] = "beamO23";
  beam[7] = "beamO24";
  ictf[0] = "unr27F_ictof2";
  ictf[1] = "unr28Ne_ictof";
  ictf[2] = "unr29Ne_ictof3";
  ictf[3] = "unr30Na_ictof2";
  ictf[4] = "beamO21ic";
  ictf[5] = "beamO22ic";
  ictf[6] = "beamO23ic";
  ictf[7] = "beamO24ic";

  m_beamIndex=-999; m_beamColor=1;
  m_beamStyle = 1;

  rawBins=200; raw1=0; raw2=4000;
  calBins = 150; cal1=0.; cal2=30.;

  /* Unreacted beam dE (from LISE++)*/
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
  // O-21
  fragDE[4][0] = 9.8785; fragDE[4][1] = 10.177; fragDE[4][2] = 11.168; fragDE[4][3] = 12.425;
  // O-22
  fragDE[5][0] = 10.479; fragDE[5][1] = 10.887; fragDE[5][2] = 12.080; fragDE[5][3] = 13.654;
  // O-23
  fragDE[6][0] = 11.106; fragDE[6][1] = 11.651; fragDE[6][2] = 13.100; fragDE[6][3] = 15.093;
  // O-24
  fragDE[7][0] = 11.713; fragDE[7][1] = 12.409; fragDE[7][2] = 14.130; fragDE[7][3] = 16.659;
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
  // O-21
  varpDE[4][0] = 0.007157; varpDE[4][1] = 0.007468; varpDE[4][2] = 0.007342; varpDE[4][3] = 0.007485;
  // O-22
  varpDE[5][0] = 0.007157; varpDE[5][1] = 0.007532; varpDE[5][2] = 0.007533; varpDE[5][3] = 0.007544;
  // O-23
  varpDE[6][0] = 0.007113; varpDE[6][1] = 0.007553; varpDE[6][2] = 0.007557; varpDE[6][3] = 0.007686;
  // O-24
  varpDE[7][0] = 0.007172; varpDE[7][1] = 0.007575; varpDE[7][2] = 0.007643; varpDE[7][3] = 0.007804;

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
  // O-21
  varnDE[4][0] = -0.00716; varnDE[4][1] = -0.00757; varnDE[4][2] = -0.00734; varnDE[4][3] = -0.00748;
  // O-22
  varnDE[5][0] = -0.00716; varnDE[5][1] = -0.00744; varnDE[5][2] = -0.00753; varnDE[5][3] = -0.00754;
  // O-23
  varnDE[6][0] = -0.00711; varnDE[6][1] = -0.00755; varnDE[6][2] = -0.00756; varnDE[6][3] = -0.00769;
  // O-24
  varnDE[7][0] = -0.00717; varnDE[7][1] = -0.00758; varnDE[7][2] = -0.00764; varnDE[7][3] = -0.00786;


  /* Unreacted beam dE (from LISE++)
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
*/

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
  else if(beam.CompareTo("O21") == 0){
    m_beamIndex=4; m_beamStyle=35;
    m_beamSet=true; m_beamColor=4;
  }
  else if(beam.CompareTo("O22") == 0){
    m_beamIndex=5; m_beamStyle=35;
    m_beamSet=true; m_beamColor=4;
  }
  else if(beam.CompareTo("O23") == 0){
    m_beamIndex=6; m_beamStyle=35;
    m_beamSet=true; m_beamColor=4;
  }
  else if(beam.CompareTo("O24") == 0){
    m_beamIndex=7; m_beamStyle=36;
    m_beamSet=true; m_beamColor=4;
  }
  else{ cout << "Specify valid beam: F27, Ne28, Ne29, Na30, O21, O22, O23, O24." << endl; return;}
  printf("Beam: %s; Index = %i\n",beam.Data(),m_beamIndex);
}


void SiEcal::SetChain(){
  BeamCuts(beamCut);
  ElementCuts(icCut);
  char buffer[4096];
  int count=0;
  for(int i=1038;i<1043;i++)
  {
    sprintf(buffer, "/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root", i);
    cout << buffer << endl;
    t->Add(buffer);
    count++;
  }

  for(int i=1051;i<1120;i++)
  {
    if(i!=1075 && i!=1080 && i!=1081 && i!=1087 && i!=1088 && i!=1099 && i!=1115 && i!=1116)
    {
      sprintf(buffer, "/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root", i);
      cout << buffer << endl;
      t->Add(buffer);
      count++;
    }

  }
  for(int i=1125;i<1160;i++)
  {
    if(1)
    {
      sprintf(buffer, "/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root", i);
      cout << buffer << endl;
      t->Add(buffer);
      count++;
    }

  }

  for(int i=1164;i<1180;i++)
  {
    if(1)
    {
      sprintf(buffer, "/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root", i);
      cout << buffer << endl;
      t->Add(buffer);
      count++;
    }

  }
  printf("  %i runs loaded.\n",count);
  m_goodFile=true;m_run=999;

}


void SiEcal::SetHistograms(){
char gate[4096];
sprintf(gate,"tof.a1900_pot!=-1 && %s && %s",beam[m_beamIndex],ictf[m_beamIndex]);
if(m_goodFile && m_beamSet && !m_histsSet){
//  BeamCuts(beamCut);
//  ElementCuts(icCut);
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
  c0->~TCanvas();
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
    Double_t x[8]={0.,0.,0.,0.,0.,0.,0.,0.};
    Double_t y[8]={0.,0.,0.,0.,0.,0.,0.,0.};
    Double_t xerr[8]={0.,0.,0.,0.,0.,0.,0.,0.};
    Double_t yerr1[8]={0.,0.,0.,0.,0.,0.,0.,0.};
    Double_t yerr2[8]={0.,0.,0.,0.,0.,0.,0.,0.};

    // sum over data points
    // (for a single detector)
    // used for plotting 1-sigma
    // calibration range
    Double_t sumX = 0.;
    Double_t sumY = 0.;

    for(int beam=0;beam<8;beam++){
      x[beam] = anodeMean[beam][det];
      xerr[beam] = anodeMerr[beam][det];
      y[beam] = fragDE[beam][det];
      yerr1[beam] = fragDE[beam][det]*varpDE[beam][det];// lower
      yerr2[beam] = TMath::Abs(fragDE[beam][det]*varnDE[beam][det]);// upper
      sumX += x[beam];
      sumY += y[beam];
    }

//    detSummary[det] = new TGraphErrors(4,x,y,xerr,yerr);
    detSummary[det] = new TGraphAsymmErrors(8,x,y,xerr,xerr,yerr1,yerr2);
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

    LoCalibration[det] = new TF1(Form("lc%i",det),"[0]+[1]*x",500,2900);
    HiCalibration[det] = new TF1(Form("hc%i",det),"[0]+[1]*x",500,2900);
    // set parameters for edge functions
    Double_t lB = dEslope[det] + fitSlopeError[det];
    Double_t hB = dEslope[det] - fitSlopeError[det];
    Double_t lA = (sumY - lB*sumX)/8.;
    Double_t hA = (sumY - hB*sumX)/8.;
    LoCalibration[det]->SetParameter(0,lA);
    LoCalibration[det]->SetParameter(1,lB);
    HiCalibration[det]->SetParameter(0,hA);
    HiCalibration[det]->SetParameter(1,hB);
    LoCalibration[det]->SetLineColor(4); HiCalibration[det]->SetLineColor(4);

    frame[det] = new TH2I(Form("frame%i",det),
      Form("Si %i Calibration;Raw dE (adc);dE [MeV]",det),2,500,3000,2,5,35);
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


void chainf27(){
  SiEcal s;
  s.SetBeam("F27");
  s.SetChain();
//  s.ReadCalibration();
  s.SetHistograms();
//  s.PlotDEcal();
}


void cchainf27(){
  SiEcal ss;
  ss.SetBeam("F27");
  ss.SetChain();
  ss.ReadCalibration();
  ss.SetHistograms();
  ss.PlotDEcal();
}


void ChainBeams(){
  SiEcal s;
  s.SetChain();
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
  s.ClearHistograms();
  s.SetBeam("O21");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("O22");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("O23");
  s.SetHistograms();
  s.FitHistograms();
  s.ClearHistograms();
  s.SetBeam("O24");
  s.SetHistograms();
  s.FitHistograms();

  s.DetectorSummary();
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

/*
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
*/

   cutg[4] = new TCutG("beamO21",13);
   cutg[4]->SetVarX("tof.a1900_pot");
   cutg[4]->SetVarY("st.anode[0]");
   cutg[4]->SetTitle("Graph");
   cutg[4]->SetFillColor(1);
   cutg[4]->SetLineColor(2);
   cutg[4]->SetLineWidth(2);
   cutg[4]->SetPoint(0,71.8594,946.573);
   cutg[4]->SetPoint(1,72.2699,911.29);
   cutg[4]->SetPoint(2,72.6805,926.411);
   cutg[4]->SetPoint(3,72.8858,976.815);
   cutg[4]->SetPoint(4,72.964,1017.14);
   cutg[4]->SetPoint(5,72.8956,1072.58);
   cutg[4]->SetPoint(6,72.7783,1133.06);
   cutg[4]->SetPoint(7,72.5241,1173.39);
   cutg[4]->SetPoint(8,72.3775,1173.39);
   cutg[4]->SetPoint(9,72.0842,1122.98);
   cutg[4]->SetPoint(10,71.8398,1052.42);
   cutg[4]->SetPoint(11,71.7909,966.734);
   cutg[4]->SetPoint(12,71.8594,946.573);

   cutg[5] = new TCutG("beamO22",16);
   cutg[5]->SetVarX("tof.a1900_pot");
   cutg[5]->SetVarY("st.anode[0]");
   cutg[5]->SetTitle("Graph");
   cutg[5]->SetFillColor(1);
   cutg[5]->SetLineColor(2);
   cutg[5]->SetLineWidth(2);
   cutg[5]->SetPoint(0,74.3522,1243.95);
   cutg[5]->SetPoint(1,73.7852,1218.75);
   cutg[5]->SetPoint(2,73.4333,1102.82);
   cutg[5]->SetPoint(3,73.4724,986.895);
   cutg[5]->SetPoint(4,73.883,936.492);
   cutg[5]->SetPoint(5,74.2349,951.613);
   cutg[5]->SetPoint(6,75.1343,946.573);
   cutg[5]->SetPoint(7,75.4275,996.976);
   cutg[5]->SetPoint(8,75.623,1067.54);
   cutg[5]->SetPoint(9,75.623,1128.02);
   cutg[5]->SetPoint(10,75.5057,1183.47);
   cutg[5]->SetPoint(11,75.3004,1238.91);
   cutg[5]->SetPoint(12,75.1636,1259.07);
   cutg[5]->SetPoint(13,74.8019,1238.91);
   cutg[5]->SetPoint(14,74.5184,1238.91);
   cutg[5]->SetPoint(15,74.3522,1243.95);

   cutg[6] = new TCutG("beamO23",21);
   cutg[6]->SetVarX("tof.a1900_pot");
   cutg[6]->SetVarY("st.anode[0]");
   cutg[6]->SetTitle("Graph");
   cutg[6]->SetFillColor(1);
   cutg[6]->SetLineColor(2);
   cutg[6]->SetLineWidth(2);
   cutg[6]->SetPoint(0,76.2585,991.935);
   cutg[6]->SetPoint(1,76.7473,981.855);
   cutg[6]->SetPoint(2,77.021,996.976);
   cutg[6]->SetPoint(3,77.6075,1032.26);
   cutg[6]->SetPoint(4,77.8617,1067.54);
   cutg[6]->SetPoint(5,77.979,1128.02);
   cutg[6]->SetPoint(6,78.0083,1158.27);
   cutg[6]->SetPoint(7,77.979,1203.63);
   cutg[6]->SetPoint(8,77.8715,1248.99);
   cutg[6]->SetPoint(9,77.7248,1274.19);
   cutg[6]->SetPoint(10,77.5587,1279.23);
   cutg[6]->SetPoint(11,77.2947,1279.23);
   cutg[6]->SetPoint(12,76.9819,1274.19);
   cutg[6]->SetPoint(13,76.7473,1259.07);
   cutg[6]->SetPoint(14,76.4833,1254.03);
   cutg[6]->SetPoint(15,76.2682,1259.07);
   cutg[6]->SetPoint(16,75.9652,1198.59);
   cutg[6]->SetPoint(17,75.7795,1128.02);
   cutg[6]->SetPoint(18,75.8968,1057.46);
   cutg[6]->SetPoint(19,76.1021,1037.3);
   cutg[6]->SetPoint(20,76.2585,991.935);


   cutg[7] = new TCutG("beamO24",14);
   cutg[7]->SetVarX("tof.a1900_pot");
   cutg[7]->SetVarY("st.anode[0]");
   cutg[7]->SetTitle("Graph");
   cutg[7]->SetFillColor(1);
   cutg[7]->SetLineColor(2);
   cutg[7]->SetLineWidth(2);
   cutg[7]->SetPoint(0,78.3896,1059.59);
   cutg[7]->SetPoint(1,78.8393,1038.86);
   cutg[7]->SetPoint(2,79.3379,1033.68);
   cutg[7]->SetPoint(3,79.7973,1095.85);
   cutg[7]->SetPoint(4,80.159,1183.94);
   cutg[7]->SetPoint(5,80.2177,1235.75);
   cutg[7]->SetPoint(6,79.9928,1297.93);
   cutg[7]->SetPoint(7,79.6996,1297.93);
   cutg[7]->SetPoint(8,79.3476,1303.11);
   cutg[7]->SetPoint(9,78.8393,1282.38);
   cutg[7]->SetPoint(10,78.3603,1282.38);
   cutg[7]->SetPoint(11,78.1452,1147.67);
   cutg[7]->SetPoint(12,78.1354,1080.31);
   cutg[7]->SetPoint(13,78.3896,1059.59);


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

   cutg[4] = new TCutG("beamO21ic",13);
   cutg[4]->SetVarX("tof.pot_thin");
   cutg[4]->SetVarY("ic_sum");
   cutg[4]->SetTitle("Graph");
   cutg[4]->SetFillColor(1);
   cutg[4]->SetLineColor(2);
   cutg[4]->SetLineWidth(2);
   cutg[4]->SetPoint(0,-0.613921,211.917);
   cutg[4]->SetPoint(1,-0.6628,198.446);
   cutg[4]->SetPoint(2,-0.418405,188.083);
   cutg[4]->SetPoint(3,0.0377997,188.083);
   cutg[4]->SetPoint(4,0.379953,191.192);
   cutg[4]->SetPoint(5,0.559176,199.482);
   cutg[4]->SetPoint(6,0.591762,208.808);
   cutg[4]->SetPoint(7,0.542883,220.207);
   cutg[4]->SetPoint(8,0.36366,229.534);
   cutg[4]->SetPoint(9,0.0703857,230.57);
   cutg[4]->SetPoint(10,-0.190303,228.497);
   cutg[4]->SetPoint(11,-0.483577,219.171);
   cutg[4]->SetPoint(12,-0.613921,211.917);

   cutg[5] = new TCutG("beamO22ic",13);
   cutg[5]->SetVarX("tof.pot_thin");
   cutg[5]->SetVarY("ic_sum");
   cutg[5]->SetTitle("Graph");
   cutg[5]->SetFillColor(1);
   cutg[5]->SetLineColor(2);
   cutg[5]->SetLineWidth(2);
   cutg[5]->SetPoint(0,1.69969,264.919);
   cutg[5]->SetPoint(1,1.08055,241.734);
   cutg[5]->SetPoint(2,0.836157,217.54);
   cutg[5]->SetPoint(3,1.03167,209.476);
   cutg[5]->SetPoint(4,1.27607,206.452);
   cutg[5]->SetPoint(5,1.73227,211.492);
   cutg[5]->SetPoint(6,2.07443,214.516);
   cutg[5]->SetPoint(7,2.48175,220.565);
   cutg[5]->SetPoint(8,2.72615,231.653);
   cutg[5]->SetPoint(9,2.74244,244.758);
   cutg[5]->SetPoint(10,2.67727,260.887);
   cutg[5]->SetPoint(11,2.38399,271.976);
   cutg[5]->SetPoint(12,1.69969,264.919);

   cutg[6] = new TCutG("beamO23ic",15);
   cutg[6]->SetVarX("tof.pot_thin");
   cutg[6]->SetVarY("ic_sum");
   cutg[6]->SetTitle("Graph");
   cutg[6]->SetFillColor(1);
   cutg[6]->SetLineColor(2);
   cutg[6]->SetLineWidth(2);
   cutg[6]->SetPoint(0,2.75873,244.041);
   cutg[6]->SetPoint(1,3.0683,232.642);
   cutg[6]->SetPoint(2,3.68743,238.86);
   cutg[6]->SetPoint(3,4.06217,244.041);
   cutg[6]->SetPoint(4,4.42062,256.477);
   cutg[6]->SetPoint(5,4.79536,269.948);
   cutg[6]->SetPoint(6,4.90941,281.347);
   cutg[6]->SetPoint(7,4.86053,294.819);
   cutg[6]->SetPoint(8,4.55096,300);
   cutg[6]->SetPoint(9,4.2251,297.927);
   cutg[6]->SetPoint(10,3.85036,293.782);
   cutg[6]->SetPoint(11,3.47563,285.492);
   cutg[6]->SetPoint(12,3.0683,273.057);
   cutg[6]->SetPoint(13,2.72615,258.549);
   cutg[6]->SetPoint(14,2.75873,244.041);

   cutg[7] = new TCutG("beamO24ic",16);
   cutg[7]->SetVarX("tof.pot_thin");
   cutg[7]->SetVarY("ic_sum");
   cutg[7]->SetTitle("Graph");
   cutg[7]->SetFillColor(1);
   cutg[7]->SetLineColor(2);
   cutg[7]->SetLineWidth(2);
   cutg[7]->SetPoint(0,5.74035,316.331);
   cutg[7]->SetPoint(1,5.20269,305.242);
   cutg[7]->SetPoint(2,4.87682,294.153);
   cutg[7]->SetPoint(3,4.82795,285.081);
   cutg[7]->SetPoint(4,4.82795,272.984);
   cutg[7]->SetPoint(5,4.95829,261.895);
   cutg[7]->SetPoint(6,5.36562,260.887);
   cutg[7]->SetPoint(7,6.27802,270.968);
   cutg[7]->SetPoint(8,6.91345,291.129);
   cutg[7]->SetPoint(9,7.22302,304.234);
   cutg[7]->SetPoint(10,7.22302,314.315);
   cutg[7]->SetPoint(11,7.10897,325.403);
   cutg[7]->SetPoint(12,6.89716,333.468);
   cutg[7]->SetPoint(13,6.3432,329.435);
   cutg[7]->SetPoint(14,6.00104,321.371);
   cutg[7]->SetPoint(15,5.74035,316.331);


}
