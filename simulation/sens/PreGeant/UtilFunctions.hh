void ModHistogram(TH1D* h,Int_t color,Int_t width)
{
  Double_t max = h->GetMaximum();
  h->Scale(1./max);
  h->SetLineColor(color);
  h->SetLineWidth(width);
  h->SetStats(0);
//  h->SetStatTextColor(color);

/*
  TCanvas *ctemp = new TCanvas;
  h->Draw();
  TPaveStats *p = (TPaveStats*)h->GetListOfFunction()->FindObject("stats");
  h->GetListOfFunctions()->Remove(p);
  p->GetLineWith("Entries")->SetTextColor(color);
  p->GetLineWith("Mean")->SetTextColor(color);
  p->GetLineWith("RMS")->SetTextColor(color);
  p->Draw();
*/
}



TPaveText* CustomStatsBox(TH1D* h,Int_t axis,Int_t color,int idx)
{
  // Get numbers for stats
  TString  name = h->GetName();
//  Double_t ents = h->GetEntries();
  Double_t mean = h->GetMean(axis);
  Double_t rms  = h->GetRMS(axis);
  // Get numbers for positioning stats box
  Double_t xmax = (h->GetXaxis()->GetXmax());
  Double_t xrng = (h->GetXaxis()->GetXmax())-(h->GetXaxis()->GetXmin());
  Double_t ymax = h->GetMaximum();
  Double_t yrng = ymax;
  Double_t space= 0.15;
           ymax = 1.05*ymax - space*(Double_t)(idx);

  TPaveText *pt = new TPaveText(xmax-0.25*xrng,ymax-space*yrng,xmax,ymax);
  TText *txn    = pt->AddText(name);
//  TText *txe    = pt->AddText(Form("Entries: %5i",ents));
  TText *txm    = pt->AddText(Form("Mean: %4.4f",mean));
  TText *txr    = pt->AddText(Form("RMS: %4.4f",rms));
  txn->SetTextColor(color);
//  txe->SetTextColor(color);
  txm->SetTextColor(color);
  txr->SetTextColor(color);

  return pt;

}


TPaveText* CustomStatsBoxL(TH1D* h,Int_t axis,Int_t color,int idx)
{
  // Get numbers for stats
  TString  name = h->GetName();
//  Double_t ents = h->GetEntries();
  Double_t mean = h->GetMean(axis);
  Double_t rms  = h->GetRMS(axis);
  // Get numbers for positioning stats box
  Double_t xmin = (h->GetXaxis()->GetXmin());
  Double_t xrng = (h->GetXaxis()->GetXmax())-(h->GetXaxis()->GetXmin());
  Double_t ymax = h->GetMaximum();
  Double_t yrng = ymax;
  Double_t space= 0.15;
           ymax = 1.05*ymax - space*(Double_t)(idx);

  TPaveText *pt = new TPaveText(xmin+0.05*xrng,ymax-space*yrng,xmin+0.30*xrng,ymax);
  TText *txn    = pt->AddText(name);
//  TText *txe    = pt->AddText(Form("Entries: %5i",ents));
  TText *txm    = pt->AddText(Form("Mean: %4.4f",mean));
  TText *txr    = pt->AddText(Form("RMS: %4.4f",rms));
  txn->SetTextColor(color);
//  txe->SetTextColor(color);
  txm->SetTextColor(color);
  txr->SetTextColor(color);

  return pt;

}


void CheckHistStats(TH1D* h)
{
  TString name = h->GetName();
//  Double_t N = h->GetEntries();
  Double_t N = 0.;
  Double_t mean = 0.;
  Double_t sig2 = 0.;
  Int_t nbins = h->GetNbinsX();

  for(Int_t i=1;i<=nbins;i++)
  {
    Double_t bc = h->GetBinContent(i);
    Double_t x  = h->GetBinCenter(i);
    mean += (bc*x);
    N += bc;
  }

  mean = mean/N;

  for(Int_t i=1;i<=nbins;i++)
  {
    Double_t bc = h->GetBinContent(i);
    Double_t x  = h->GetBinCenter(i);
    sig2 += bc*((x-mean)*(x-mean));
  }

  sig2 = sqrt(sig2/(N-1));

  cout << endl;
  cout << Form("%s Mean: ",name.Data()) << mean << endl;
  cout << Form("%s RMS:  ",name.Data()) << sqrt(sig2) << endl;

}
