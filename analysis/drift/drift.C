// Function for Chaining together all ROOT files
// Will cout names of all files included in chain
// ______________________________________________


void LoadProduction(){//34 runs
    char buffer[1024];

/**/
    for(int i=1038;i<1043;i++)
    {
      sprintf(buffer,"t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");",i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
    }


    for(int i=1051;i<1087;i++)
    {
      if(i!=1075 && i!=1080 && i!=1081)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    /* runs with bad crdc 2 */
    for(int i=1089;i<1120;i++)
    {
      if(i!=1099 && i!=1115 && i!=1116)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }
    }
    

    for(int i=1125;i<1160;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    for(int i=1164;i<1180;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }




}

void LoadProduction1(){//34 runs
    char buffer[1024];
  
    for(int i=1051;i<1087;i++)
    {
      if(i!=1075 && i!=1080 && i!=1081)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    /* runs with bad crdc 2*/
    for(int i=1089;i<1120;i++)
    {
      if(i!=1099 && i!=1115 && i!=1116)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }
    }
    

}
void LoadProduction2(){//34 runs
    char buffer[1024];
  
    for(int i=1125;i<1159;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    for(int i=1164;i<1180;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

}


void LoadProductionRaw(){//34 runs
    char buffer[1024];
  
    for(int i=1051;i<1087;i++)
    {
      if(i!=1075 && i!=1080 && i!=1081)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    // runs with bad crdc 2
    for(int i=1089;i<1120;i++)
    {
      if(i!=1099 && i!=1115 && i!=1116)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }
    }

    for(int i=1125;i<1159;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }

    for(int i=1164;i<1179;i++)
    {
      if(1)
      {
      sprintf(buffer, "t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged.root\");", i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
      }

    }




}


void SelectProduction(int runlo,int runhi)
{
  char buffer[1024];

  for(int i=runlo;i<runhi+1;i++)
  {
    if(i!=1075 && i!=1080 && i!=1081 &&
    i!=1087 && i!=1088 && i!=1099 &&
    i!=1115 && i!=1116 && i!=1120 && i!=1121 &&
    i!=1122 && i!=1123 && i!=1124 &&
    i!=1160 && i!=1161 && i!=1162 &&
    i!=1163)
    {
      sprintf(buffer,"t.Add(\"/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root\");",i);
      cout << buffer << endl;
        gROOT->ProcessLine(buffer);
    }

  }

}



void plot_drift(const char* det,
		const char* hname,
		const char* gate,
		Int_t binsy,
		Double_t ylo,
		Double_t yhi)
{
  const int runbins = 145;
  const int runlow = 3035;
  const int runhi = 3180;
  char buf1[1024];
  char buf2[1024];

  TChain t("t");
//  SelectProduction(1051,1159);
  LoadProduction();
//  LoadProductionRaw();
//  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/THR_chainaliases.C");
  SetAliases();

  TCanvas *c1 = new TCanvas("c1","c1",1600,500);
  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);

  sprintf(buf1,"%s:runnum>>%s(%i,%i,%i,%i,%g,%g)",det,hname,runbins,runlow,runhi,binsy,ylo,yhi);
  t.Draw(buf1,gate,"COLZ");

  c1->cd(2);
  sprintf(buf2,"%s->ProfileX(\"_pfx\",1,%i,\"do\")",hname,binsy);
    gROOT->ProcessLine(buf2);



}


void SetAliases()
{
  t->SetAlias("validcrdc1","crdc1.x!=-1 && crdc1.y!=-1");
  t->SetAlias("validcrdc2","crdc2.x!=-1 && crdc2.y!=-1");
  t->SetAlias("crdc2cnter","crdc2.x>-10. && crdc2.x<10. && crdc2.y>-10. && crdc2.y<10.");
  t->SetAlias("validcrdcs","validcrdc1 && validcrdc2");
  t->SetAlias("validtofs", "tof.a1900_pot!=-1&&tof.pot_thin!=-1");

//  t->SetAlias("ic_sum","(ic.cal[0]+ic.cal[1]+ic.cal[2]+ic.cal[3]+ic.cal[4]+ic.cal[5]+ic.cal[6]+ic.cal[7]+ic.cal[8]+ic.cal[9]+ic.cal[10]+ic.cal[11]+ic.cal[12]+ic.cal[13]+ic.cal[14]+ic.cal[15])/16");
//  t->SetAlias("ic_sum_raw","(raw::sweeper.ic.raw[1]+raw::sweeper.ic.raw[2]+raw::sweeper.ic.raw[3]+raw::sweeper.ic.raw[5]+raw::sweeper.ic.raw[6]+raw::sweeper.ic.raw[8]+raw::sweeper.ic.raw[9]+raw::sweeper.ic.raw[10]+raw::sweeper.ic.raw[11]+raw::sweeper.ic.raw[12]+raw::sweeper.ic.raw[13]+raw::sweeper.ic.raw[14])/12");
  t->SetAlias("ic_sum","(ic.cal[1]+ic.cal[2]+ic.cal[3]+ic.cal[5]+ic.cal[6]+ic.cal[8]+ic.cal[9]+ic.cal[10]+ic.cal[11]+ic.cal[12]+ic.cal[13]+ic.cal[14])/12");
  t->SetAlias("ic_sum_raw","(raw::sweeper.ic.raw[1]+raw::sweeper.ic.raw[2]+raw::sweeper.ic.raw[3]+raw::sweeper.ic.raw[5]+raw::sweeper.ic.raw[6]+raw::sweeper.ic.raw[8]+raw::sweeper.ic.raw[9]+raw::sweeper.ic.raw[10]+raw::sweeper.ic.raw[11]+raw::sweeper.ic.raw[12]+raw::sweeper.ic.raw[13]+raw::sweeper.ic.raw[14])/12");

  /* Graphical (2D) cuts */
  // Beam ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/F27_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Ne28_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Ne29_tight.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/Obeam.C");
  // Element ID
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/r1060_unrO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/AllO_ictof2.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/unr27F_ictof.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/unr27F_ictof2.C");
  gROOT->ProcessLine(".x /projects/e15118/redpath/analysis/aliases/unr28Ne_ictof.C");

  // Segmented Target
  // detector 0
  t->SetAlias("LU0","raw::sweeper.st.raw[4]");
  t->SetAlias("RU0","raw::sweeper.st.raw[5]");
  t->SetAlias("RD0","raw::sweeper.st.raw[6]");
  t->SetAlias("LD0","raw::sweeper.st.raw[7]");
  /*
  t->SetAlias("LU0","st.corner[0][0]");
  t->SetAlias("RU0","st.corner[0][1]");
  t->SetAlias("RD0","st.corner[0][2]");
  t->SetAlias("LD0","st.corner[0][3]");
  */
  t->SetAlias("S0","LU0+RU0+RD0+LD0");
  t->SetAlias("SL0","LU0+LD0");
  t->SetAlias("SR0","RU0+RD0");
  t->SetAlias("Sup0","LU0+RU0");
  t->SetAlias("Sdn0","LD0+RD0");
  t->SetAlias("x0","(SL0-SR0)/S0");
  t->SetAlias("y0","(Sup0-Sdn0)/S0");

  // Segmented Target
  // detector 1
  t->SetAlias("LU1","raw::sweeper.st.raw[0]");
  t->SetAlias("RU1","raw::sweeper.st.raw[1]");
  t->SetAlias("RD1","raw::sweeper.st.raw[2]");
  t->SetAlias("LD1","raw::sweeper.st.raw[3]");
  /*
  t->SetAlias("LU1","st.corner[1][0]");
  t->SetAlias("RU1","st.corner[1][1]");
  t->SetAlias("RD1","st.corner[1][2]");
  t->SetAlias("LD1","st.corner[1][3]");
  */
  t->SetAlias("S1","LU1+RU1+RD1+LD1");
  t->SetAlias("SL1","LU1+LD1");
  t->SetAlias("SR1","RU1+RD1");
  t->SetAlias("Sup1","LU1+RU1");
  t->SetAlias("Sdn1","LD1+RD1");
  t->SetAlias("x1","(SL1-SR1)/S1");
  t->SetAlias("y1","(Sup1-Sdn1)/S1");

  // Segmented Target
  // detector 2
  t->SetAlias("LU2","raw::sweeper.st.raw[12]");
  t->SetAlias("RU2","raw::sweeper.st.raw[13]");
  t->SetAlias("RD2","raw::sweeper.st.raw[14]");
  t->SetAlias("LD2","raw::sweeper.st.raw[15]");
  /*
  t->SetAlias("LU2","st.corner[2][0]");
  t->SetAlias("RU2","st.corner[2][1]");
  t->SetAlias("RD2","st.corner[2][2]");
  t->SetAlias("LD2","st.corner[2][3]");
  */
  t->SetAlias("S2","LU2+RU2+RD2+LD2");
  t->SetAlias("SL2","LU2+LD2");
  t->SetAlias("SR2","RU2+RD2");
  t->SetAlias("Sup2","LU2+RU2");
  t->SetAlias("Sdn2","LD2+RD2");
  t->SetAlias("x2","(SL2-SR2)/S2");
  t->SetAlias("y2","(Sup2-Sdn2)/S2");

  // Segmented Target
  // detector 3
  t->SetAlias("LU3","raw::sweeper.st.raw[8]");
  t->SetAlias("RU3","raw::sweeper.st.raw[9]");
  t->SetAlias("RD3","raw::sweeper.st.raw[10]");
  t->SetAlias("LD3","raw::sweeper.st.raw[11]");
  /*
  t->SetAlias("LU3","st.corner[3][0]");
  t->SetAlias("RU3","st.corner[3][1]");
  t->SetAlias("RD3","st.corner[3][2]");
  t->SetAlias("LD3","st.corner[3][3]");
  */
  t->SetAlias("S3","LU3+RU3+RD3+LD3");
  t->SetAlias("SL3","LU3+LD3");
  t->SetAlias("SR3","RU3+RD3");
  t->SetAlias("Sup3","LU3+RU3");
  t->SetAlias("Sdn3","LD3+RD3");
  t->SetAlias("x3","(SL3-SR3)/S3");
  t->SetAlias("y3","(Sup3-Sdn3)/S3");


}

TCanvas* filtered_plot_drift(const char* det,
			const char* hname,
			const char* gate,
			Int_t binsy,
			Double_t ylo,
			Double_t yhi,
			Double_t pfxlo,
			Double_t pfxhi)
{
  const int runbins = 145;
  const int runlow = 3035;
  const int runhi = 3180;
  char buf1[1024];
  char buf2[1024];

//  gStyle->SetOptFit(0011);

  SetAliases();

  TCanvas *c1 = new TCanvas("c1","c1",1600,500);
  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);

  sprintf(buf1,"%s:runnum>>%s(%i,%i,%i,%i,%g,%g)",det,hname,runbins,runlow,runhi,binsy,ylo,yhi);
  t->Draw(buf1,gate,"COLZ");

  c1->cd(2);
  sprintf(buf2,"%s->ProfileX(\"_pfx\",1,%i,\"do\")",hname,binsy);
    gROOT->ProcessLine(buf2);
  sprintf(buf1,"%s_pfx->GetYaxis()->SetRangeUser(%g,%g)",hname,pfxlo,pfxhi);
    gROOT->ProcessLine(buf1);
//  sprintf(buf1,"%s_pfx->Fit(\"pol1\")",hname);
//    gROOT->ProcessLine(buf1);
//  c1->Update();
//  sprintf(buf1,"%s_pfx->SetStats(0)",hname);
//  sprintf(buf1,"TPaveStats *st = (TPaveStats*)%s_pfx->FindObject(\"stats\"); st->SetOptStats(0);",hname);
//  sprintf(buf1,"TPaveStats *st = (TPaveStats*)%s_pfx->FindObject(\"stats\");",hname);
//    gROOT->ProcessLine(buf1);
//    gROOT->ProcessLine("st->SetOptStats(\"n\");");
//  c1->Update();
 // c1->Modified();

  return c1;

}


TCanvas* tproj_filetered_plot_drift(const char* det,
				const char* gate,
				Int_t binsy,
				Double_t ylo,
				Double_t yhi,
				Double_t pfxlo,
				Double_t pfxhi)
{
//  TString filename = "/mnt/analysis/e15118/playground/all_unr27F.root";
//  TString filename = "/mnt/analysis/e15118/playground/allO.root";
  TString filename = "/mnt/analysis/e15118/playground/NSCL_all_Ne28_O.root";
  f = new TFile(filename, "READ");
  t = (TTree*)f->Get("t");

  const Int_t runbins = 145;
  const Int_t runlow = 3035;
  const Int_t runhi = 3180;

  gStyle->SetOptFit(0011);
/*
  Double_t x1 = (Double_t)runhi-25;
  Double_t x2 = (Double_t)runhi;
  Double_t y1 = ylo;
  Double_t y2 = ylo + 0.2*(yhi-ylo);
  Double_t yp1 = pfxlo;
  Double_t yp2 = pfxlo + 0.2*(pfxhi-pfxlo);
*/
  gStyle->SetStatX(0.3);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.10);
  gStyle->SetStatH(0.10);


  SetAliases();

  TCanvas* c1 = new TCanvas("c1","c1",1600,500);

  TH2D* drift = new TH2D("drift",Form("%s drift;run number;%s",det,det),runbins,runlow,runhi,binsy,ylo,yhi);
  t->Project("drift",Form("%s:runnum",det),gate);
  drift->ProfileX("_pfx",1,binsy,"do");
  drift_pfx->GetYaxis()->SetRangeUser(pfxlo,pfxhi);

  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);
  drift->Draw("COLZ");
  c1->cd(2);
  drift_pfx->Draw();
  drift_pfx->Fit("pol1");
/*
  c1->Update();
  TPaveStats *st = (TPaveStats*)drift->GetListOfFunctions()->FindObject("stats");
  TPaveStats *stpfx = (TPaveStats*)drift_pfx->FindObject("stats");
//  st->SetOptStats("n");
  st->SetX1NDC(x1);
  st->SetX2NDC(x2);
  st->SetY1NDC(y1);
  st->SetY2NDC(y2);

  stpfx->SetX1NDC(x1);
  stpfx->SetX2NDC(x2);
  stpfx->SetY1NDC(yp1);
  stpfx->SetY2NDC(yp2);

  c1->Update();
  c1->Modified();
*/

  return c1;

  f->Close();

}


TCanvas* chk_gate(int runnum,
		const char* xdet,
		const char* ydet,
		const char* gate,
		Int_t binsx,
		Double_t xlo,
		Double_t xhi,
		Int_t binsy,
		Double_t ylo,
		Double_t yhi)
{
  TString filename = Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",runnum);
  f = new TFile(filename, "READ");
  t = (TTree*)f->Get("t");
  char buf1[1024];
  char buf2[1024];

  SetAliases();

  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.18);
  gStyle->SetStatH(0.18);
  
  TCanvas* out = new TCanvas("out","check gate",1200,500);
  out->Clear();
  out->Divide(2,1);
  out->cd(1);

  sprintf(buf1,"%s:%s>>h2d(%i,%g,%g,%i,%g,%g)",ydet,xdet,binsx,xlo,xhi,binsy,ylo,yhi);
  t->Draw(buf1,"","COLZ");
  sprintf(buf2,"%s->Draw(\"SAME\")",gate);
    gROOT->ProcessLine(buf2);

  out->cd(2);
  sprintf(buf1,"%s:%s>>h2dg(%i,%g,%g,%i,%g,%g)",ydet,xdet,binsx,xlo,xhi,binsy,ylo,yhi);
  t->Draw(buf1,gate,"COLZ");

  return out;

  f->Close();

}


TCanvas* dE_width(int runnum,
		const char* det,
		Int_t binsx,
		Double_t xlo,
		Double_t xhi,
		Double_t toflo,
		Double_t tofhi)//,
//		Double_t flo,
//		Double_t fhi)
{

  TString filename = Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",runnum);
  f = new TFile(filename, "READ");
  t = (TTree*)f->Get("t");
  char buf1[1024];
  char buf2[1024];

  SetAliases();
  sprintf(buf1,"tof.a1900_pot>%g && tof.a1900_pot<%g",toflo,tofhi);
  t->SetAlias("tof_gate",buf1);

  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.18);
  gStyle->SetStatH(0.18);

  TCanvas* out = new TCanvas("out","cheak peak",700,500);

  sprintf(buf1,"%s>>h(%i,%g,%g)",det,binsx,xlo,xhi);
//  t->Draw(buf1,"tof_gate");
  t->Draw(buf1,"F27_tight");

/*
  sprintf(buf2,"h->Fit(\"gaus\",\"R\",\"\",%g,%g)",flo,fhi);
    gROOT->ProcessLine(buf2);
  Double_t mean = gaus->GetParameter(1);
  Double_t sigm = gaus->GetParameter(2);

  cout << "Resolution: " << (2.35*sigm)/mean << endl;
*/

  return out;
}


//void run_loop(int ch)
TCanvas* run_loop(int ch)
{
  int runs[6]={1051,1090,1118,1127,1150,1179};
  char buf[512];

/* anode channels
  for(int i=0;i<6;i++)
  {
    sprintf(buf,"st.anode[%i]",ch);
    TCanvas* c1 = dE_width(runs[i],buf,100,1200,2200,78,80);
    sprintf(buf,"/user/redpath/research/notebook/2016/11November/figures/r%i_a%icheck.png",runs[i],ch);
    c1->Print(buf);
    c1->~TCanvas();
  }
*/
/* IC
  for(int i=0;i<6;i++)
  {
    TCanvas* c1 = chk_gate(runs[i],"tof.pot_thin","ic_sum","unr27F_ictof",240,0,15,250,0,500);
    sprintf(buf,"/user/redpath/research/notebook/2016/11November/figures/r%i_ICtof.png",runs[i]);
    c1->Print(buf);
    c1->~TCanvas();
  }
*/
/* anode channels v2 
  for(int i=0;i<6;i++)
  {
    TCanvas* c1 = thrh_anode(runs[i],ch,"tof.a1900_pot>78 && tof.a1900_pot<80",150.);
    sprintf(buf,"/user/redpath/research/notebook/2016/11November/figures/r%i_a%icheck.png",runs[i],ch);
    c1->Print(buf);
    c1->~TCanvas();
  }
*/

/* anode channels v3 */
  Double_t x[6]={0.,0.,0.,0.,0.,0.};
  Double_t y[6]={0.,0.,0.,0.,0.,0.};
  for(int i=0;i<6;i++)
  {
    x[i] = (Double_t) runs[i];
    y[i]=thrh_anode(runs[i],ch,"tof.a1900_pot>78 && tof.a1900_pot<80",150.);
  }

  TGraph* gr = new TGraph(6,runs,y);

  TCanvas* cgr = new TCanvas("cgr","cgr",700,500);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(4);
  gr->Draw("AP");

  return cgr;

}

/**/
void ch_loop(const char* det,
		Int_t binsx,
		Double_t xlo,
		Double_t xhi,
		Double_t pfxlo,
		Double_t pfxhi)
{
  char buf[1024];

  for(int i=0;i<4;i++)
  {
    sprintf(buf,"%s%i",det,i);
    TCanvas* c1 = filtered_plot_drift(buf,buf,"",binsx,xlo,xhi);
    sprintf(buf,"%s%i_pfx->GetYaxis()->SetRangeUser(%g,%g)",det,i,pfxlo,pfxhi);
      gROOT->ProcessLine(buf);
    c1->Update();
    c1->Modified();
    sprintf(buf,"/user/redpath/research/notebook/2016/11November/figures/CornerDrift/%s%i.png",det,i);
    c1->Print(buf);
    c1->~TCanvas();
  }

}


//TCanvas* thrh_anode(int runnum,int anode_ch,const char* gate,Double_t thrh)
Double_t thrh_anode(int runnum,int anode_ch,const char* gate,Double_t thrh)
{
  TString filename = Form("/mnt/analysis/e15118/root_merged/run-%i-merged_allc.root",runnum);
  f = new TFile(filename, "READ");
  t = (TTree*)f->Get("t");

  SetAliases();

  Int_t bins=300;
  TH1D* anode = new TH1D("anode","anode",bins,0,3000);
  t->Project("anode",Form("st.anode[%i]",anode_ch),gate);

  Double_t axismin = anode->GetXaxis()->GetBinLowEdge(1);
  Double_t axismax = anode->GetXaxis()->GetBinUpEdge(bins);
  TLine* threshold = new TLine(axismin,thrh,axismax,thrh);
  threshold->SetLineWidth(2);

  Double_t tINT=0.0;
  Double_t pINT=0.0;
  Int_t b1=0;
  Int_t b2=0;

  Int_t nbins = anode->GetNbinsX();
  for(Int_t i=1;i<nbins+1;i++)
  {
    Double_t bc = anode->GetBinContent(i);
    if(bc<thrh)
    {
//      anode->SetBinContent(i,0.);
      tINT+=bc;
      if(b1>0 && b2==0){b2=i;}
    }
    else
    {
      pINT+=bc;
      if(b1==0){b1=i;}  
    }
  }


/*
  Double_t maxx = anode->GetXaxis()->GetBinCenter(anode->GetMaximumBin());
  anode->Fit("gaus","R","",maxx-400,maxx+400);
*/

  TCanvas* c1 = new TCanvas("c1","c1",700,500);
  anode->SetTitle(Form("Run %i anode%i",runnum,anode_ch));
  anode->GetXaxis()->SetTitle(Form("Si %i dE (arb)",anode_ch));
  anode->Draw();
  threshold->Draw("SAME");

  TH1D* a1 = (TH1D*)anode->Clone("a1");
  a1->SetFillColor(2);
  a1->GetXaxis()->SetRange(0,b1);
  a1->Draw("same");

  TH1D* a2 = (TH1D*)anode->Clone("a2");
  a2->SetFillColor(4);
  a2->GetXaxis()->SetRange(b1,b2);
  a2->Draw("same");

  TH1D* a3 = (TH1D*)anode->Clone("a3");
  a3->SetFillColor(2);
  a3->GetXaxis()->SetRange(b2,bins);
  a3->DrawCopy("same");

  TPaveText *pt = new TPaveText(100,2000,700,2500);
  TText *t1 = pt->AddText(Form("Integral tails: %g",tINT));
  t1->SetTextColor(2);
  TText *t2 = pt->AddText(Form("Integral peak: %g",pINT));
  t2->SetTextColor(4);
  pt->AddLine(0.,0.3,1.,0.3);
  pt->AddText(Form("Ratio: %g",tINT/pINT));
  pt->Draw();



//  return c1;
  return tINT/pINT;

  f->Close();

}
