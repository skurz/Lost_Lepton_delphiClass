
#include <iostream>
#include <vector>
#include <math.h> 
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TChain.h"
#include "TTree.h"
#include "TCut.h"
#include "THStack.h"
#include "TLine.h"
#include "TFileCollection.h"
#include "TLorentzVector.h"
#include "TPaveText.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "jack_macros/jack_style.h"
#include <tdrstyle.C>
#include <CMS_lumi.C>

using namespace std;

TString plotdir = "jack_macros/plots/data/";


void MakePlot(int htmht_box, TH1D* hNormal, TH1D* hEXTRAP, TGraphAsymmErrors* gNormal, TGraphAsymmErrors* gEXTRAP,
	      TString plot_title="default", bool logy=false
	      )
{


  // Book histograms

  TH1D* hNormalBoxes = new TH1D("hNormalBoxes", "", 12, 0.5, 12.5);
  hNormalBoxes->Sumw2();
  TH1D* hEXTRAPBoxes = new TH1D("hEXTRAPBoxes", "", 12, 0.5, 12.5);
  hEXTRAPBoxes->Sumw2();
  
  // hNormal->SetFillColor(14);
  // hNormal->SetMarkerSize(0);
  // hNormal->SetLineWidth(1);
  // hNormal->SetLineColor(4);
  // hNormal->SetFillStyle(3445);

  set_style_lite(hNormalBoxes, "lost_lep");
  hNormalBoxes->GetYaxis()->SetTitleOffset(1.3);
  hNormalBoxes->GetYaxis()->SetTitle("Events");
  hNormalBoxes->SetMarkerSize(0);
  hNormalBoxes->SetMarkerColor(0);

  set_style(hEXTRAP, "lost_lep"); 
  hEXTRAP->SetMarkerSize(1.);
  hEXTRAP->SetLineWidth(3);
  hEXTRAP->SetMarkerStyle(20);
  hEXTRAP->SetLineColor(1);

  const int nbins=12;

  Double_t x[nbins];
  Double_t xl[nbins];
  Double_t xh[nbins];

  
  Double_t pred_cv[nbins];
  Double_t full_err_up[nbins];
  Double_t full_err_down[nbins];
  Double_t pred_cv_extrap[nbins];
  Double_t full_err_up_extrap[nbins];
  Double_t full_err_down_extrap[nbins];

  TString labels[nbins] = {"#splitline{4-6 jets}{0 b-jets}", "#splitline{4-6 jets}{1 b-jet}", "#splitline{4-6 jets}{2 b-jets}", "#splitline{4-6 jets}{3+ b-jets}",
			   "#splitline{7-8 jets}{0 b-jets}", "#splitline{7-8 jets}{1 b-jet}", "#splitline{7-8 jets}{2 b-jets}", "#splitline{7-8 jets}{3+ b-jets}",
			   "#splitline{9+ jets}{0 b-jets}", "#splitline{9+ jets}{1 b-jet}", "#splitline{9+ jets}{2 b-jets}", "#splitline{9+ jets}{3+ b-jets}"};
 for (int index(0); index<nbins; index++) {
    x[index]=index+1;
    xl[index]=0.5;
    xh[index]=0.5;
    hNormalBoxes->SetBinContent(index+1, hNormal->GetBinContent(index*6+htmht_box));
    hNormalBoxes->SetBinError(index+1, 0);
    pred_cv[index]=hNormal->GetBinContent(index*6+htmht_box);
    hEXTRAPBoxes->SetBinContent(index+1, hEXTRAP->GetBinContent(index*6+htmht_box));
    hEXTRAPBoxes->SetBinError(index+1, 0);   
    pred_cv_extrap[index]=hEXTRAP->GetBinContent(index*6+htmht_box);
    full_err_up[index] = gNormal->GetErrorYhigh(index*6+htmht_box-1);
    full_err_down[index] = gNormal->GetErrorYlow(index*6+htmht_box-1);
    full_err_up_extrap[index] = gEXTRAP->GetErrorYhigh(index*6+htmht_box-1);
    full_err_down_extrap[index] = gEXTRAP->GetErrorYlow(index*6+htmht_box-1);
  }

  TGraphAsymmErrors* gBGErr = new TGraphAsymmErrors(nbins, x, pred_cv, xl, xh, full_err_down, full_err_up);
  TGraphAsymmErrors* gEXTRAP_boxes = new TGraphAsymmErrors(nbins, x, pred_cv_extrap, xl, xh, full_err_down_extrap, full_err_up_extrap);
  
  gEXTRAP_boxes->SetLineWidth(3);
  gEXTRAP_boxes->SetMarkerSize(1.);
  gEXTRAP_boxes->SetMarkerStyle(20);
  gEXTRAP_boxes->SetMarkerColor(1);
  gEXTRAP_boxes->SetLineColor(1);
    
  gBGErr->SetFillColor(kRed+3);
  gBGErr->SetMarkerSize(0);
  gBGErr->SetLineWidth(0);
  gBGErr->SetLineColor(0);
  gBGErr->SetFillStyle(3445);
 

//cout << "Compute ratio hist..." << endl;
  TH1D * ratio = (TH1D *) hEXTRAPBoxes->Clone("ratio");
  TH1D * hratiogerr = (TH1D *) hEXTRAPBoxes->Clone("hratiogerr");
  TLine* ratiounity = new TLine(0.5,0,12.5,0);

  TGraphAsymmErrors* ratioderr = new TGraphAsymmErrors(gBGErr->GetN(), gBGErr->GetX(), gBGErr->GetY(), gBGErr->GetEXlow(), gBGErr->GetEXhigh(), gBGErr->GetEYlow(), gBGErr->GetEYhigh());
  TGraphAsymmErrors* ratiogerr = new TGraphAsymmErrors(gBGErr->GetN(), gBGErr->GetX(), gBGErr->GetY(), gBGErr->GetEXlow(), gBGErr->GetEXhigh(), gBGErr->GetEYlow(), gBGErr->GetEYhigh());
  for (Int_t i = 0; i < gBGErr->GetN(); i++) {
    ratiogerr->SetPoint(i, ratio->GetBinCenter(i+1), 0.);
    if (hNormalBoxes->GetBinContent(i+1)>0) {
      ratiogerr->SetPointError(i, ratio->GetBinWidth(i+1)/2., ratio->GetBinWidth(i+1)/2., ratiogerr->GetErrorYlow(i)/hNormalBoxes->GetBinContent(i+1), ratiogerr->GetErrorYhigh(i)/hNormalBoxes->GetBinContent(i+1));
      if (hEXTRAPBoxes->GetBinContent(i+1)>0) {
	ratio->SetBinContent(i+1, (hEXTRAPBoxes->GetBinContent(i+1)-hNormalBoxes->GetBinContent(i+1))/hNormalBoxes->GetBinContent(i+1));
	ratioderr->SetPoint(i, ratio->GetBinCenter(i+1), (hEXTRAPBoxes->GetBinContent(i+1)-hNormalBoxes->GetBinContent(i+1))/hNormalBoxes->GetBinContent(i+1));
	ratioderr->SetPointError(i, ratio->GetBinWidth(i+1)/1000., ratio->GetBinWidth(i+1)/1000., gEXTRAP_boxes->GetErrorYlow(i)/hNormalBoxes->GetBinContent(i+1), gEXTRAP_boxes->GetErrorYhigh(i)/hNormalBoxes->GetBinContent(i+1));
      }
      else {
	ratioderr->SetPoint(i, ratio->GetBinCenter(i+1), 0);
	ratioderr->SetPointError(i, ratio->GetBinWidth(i+1)/1000., ratio->GetBinWidth(i+1)/1000., gEXTRAP_boxes->GetErrorYlow(i), gEXTRAP_boxes->GetErrorYhigh(i));
      }
    }
    else {
      ratiogerr->SetPointError(i, ratio->GetBinWidth(i+1)/2., ratio->GetBinWidth(i+1)/2., 0., ratiogerr->GetErrorYhigh(i));
      ratioderr->SetPoint(i, ratio->GetBinCenter(i+1), 0.);
      ratioderr->SetPointError(i, ratio->GetBinWidth(i+1)/1000., ratio->GetBinWidth(i+1)/1000., gEXTRAP_boxes->GetErrorYlow(i), gEXTRAP_boxes->GetErrorYhigh(i));
     }
    //    printf("Bin %d: pred = %3.2f + %3.2f - %3.2f; ratiogerr: + %3.2f - %3.2f\n", i+1, hNormalBoxes->GetBinContent(i+1), gBGerr->GetErrorYhigh(i), gBGerr->GetErrorYlow(i), ratiogerr->GetErrorYhigh(i), ratiogerr->GetErrorYlow(i));
    ratio->GetXaxis()->SetBinLabel(i+1, labels[i].Data());
  }

  ratio->LabelsOption("h","X");
  
  set_style(ratio, "data_obs");
  ratioderr->SetLineWidth(3);
  ratioderr->SetMarkerStyle(20);
  ratioderr->SetMarkerSize(1.);
  ratioderr->SetLineColor(1);
  hratiogerr->SetStats(0);
  ratio->SetTitle("");
  ratio->GetYaxis()->SetTitle("#frac{N(#Delta#theta_{T})-N(nom.)}{N(nom.)}");
  ratio->SetMaximum(1.15);
  ratio->SetMinimum(-1.15);
  ratio->SetMarkerSize(0);
  hratiogerr->SetFillColor(0);
  hratiogerr->SetFillStyle(0);

  ratiogerr->SetFillColor(kRed+3);
  ratiogerr->SetMarkerSize(0);
  ratiogerr->SetLineWidth(1504);
  ratiogerr->SetLineColor(0);
  //ratiogerr->SetFillStyle(3004);
  ratiogerr->SetFillStyle(3445);
    
  ratio->GetXaxis()->SetLabelSize(0.05);
  ratio->GetXaxis()->SetLabelOffset(0.03);
  ratio->GetXaxis()->SetTitleSize(0.15);
  ratio->GetXaxis()->SetTitleOffset(0.95);
  ratio->GetYaxis()->SetLabelSize(0.10);
  ratio->GetYaxis()->SetNdivisions(505);
  ratiounity->SetLineStyle(2);
 
  

  // Setup legends
  TLegend * leg1 = new TLegend(0.37, 0.55, 0.82, 0.85);
  set_style(leg1,0.035);
  leg1->AddEntry(hNormalBoxes, "H_{T}^{miss} measured directly in CR (nominal)", "f");
  leg1->AddEntry(gBGErr, "Nominal uncertainty", "f");
  leg1->AddEntry(hEXTRAP, "H_{T}^{miss} = p_{T}^{W}#times#left(#frac{H_{T}^{miss}}{p_{T}^{W}}#right)_{MC}", "lpe");


  double ymax=hNormalBoxes->GetMaximum();
  //  if (hEXTRAP->GetMaximum()>ymax) ymax=hEXTRAP->GetMaximum();

  if (logy) {
    hNormalBoxes->SetMaximum(ymax*200);
    hNormalBoxes->SetMinimum(0.007);
  } else {
    hNormalBoxes->SetMaximum(ymax*2.5);
    hNormalBoxes->SetMinimum(0.);
  } 

  // if (hNormalBoxes->GetMaximum()<10) hNormalBoxes->SetMaximum(10);
  
 // Setup canvas and pads

  int W = 1000;
  int H = 800;

  // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  // Updated by:   Dinko Ferencek (Rutgers)
  //
  int H_ref = 800; 
  int W_ref = 1000; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.1*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TCanvas* canv = new TCanvas("canvName","canvName",50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);

  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.2;  // please tune the font size parameter for bottom figure
  double dw_height     = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.02; // KH, added to put the bottom one closer to the top panel

  // Luminosity information for scaling
  double lumi     = 2.3; // normaliza to this lumi (fb-1)
  double lumi_ref = 2.3; // normaliza to 3 (fb-1)
  TString line = "";
  char tempname[200];  
  sprintf(tempname,"%8.1f",lumi);
  line+=tempname;
  line+=" fb^{-1} (13 TeV)";
  
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos=0;
    
  writeExtraText = true;  
  extraText   = "        Internal";
  TString lumi_sqrtS = line;

  TPad * pad1 = new TPad("pad1", "top pad" , 0.0, 0.4, 1.0, 1.0);
  TPad * pad2 = new TPad("pad2", "bottom pad", 0.0, 0.0, 1.0, 0.2);

  pad1->SetTickx(0);
  pad1->SetTicky(0);
  pad1->SetPad(0., 1 - up_height,    1., 1.00);
  //
  pad1->SetFrameFillColor(0);
  pad1->SetFillColor(0);
  pad1->SetTopMargin(0.12);
  pad1->SetLeftMargin(0.15);
  // pad1->SetBottomMargin(0.0);
  pad1->Draw();

  pad2->SetPad(0., 0., 1., dw_height+dw_height_offset);
  pad2->SetFillColor(0);
  pad2->SetFrameFillColor(0);
  pad2->SetBottomMargin(0.38);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->Draw();
  pad1->cd();
  pad1->SetLogy(logy);
  
  // Draw hists

  hNormalBoxes->GetYaxis()->SetLabelSize(0.035*1.4);
  hNormalBoxes->GetYaxis()->SetTitleSize(0.04*1.34);
  hNormalBoxes->GetYaxis()->SetTitleOffset(0.9);
  hNormalBoxes->GetYaxis()->SetTitleFont(42);
  hNormalBoxes->GetXaxis()->SetLabelSize(0);
  
  hNormalBoxes->Draw("f");
  gBGErr->Draw("2 same");
  gEXTRAP_boxes->SetMarkerStyle(20);
  gEXTRAP_boxes->Draw("p same");

  // Draw legends
  leg1->Draw();


   

  gPad->RedrawAxis();
  gPad->Modified();
  gPad->Update();

  pad2->cd();
  pad2->SetGridy(0);

  set_style(ratio, "data_obs");
  ratio->Draw("axis");

  ratio->GetXaxis()->SetLabelSize(0.1025*1.15);
  ratio->GetXaxis()->SetTitleSize(0.14*1.2);
  ratio->GetXaxis()->SetTitleOffset(1.);
  ratio->GetXaxis()->SetTitleFont(42);
  ratio->GetYaxis()->SetTitleSize(0.1*1.18);
  ratio->GetYaxis()->SetLabelSize(0.1*1.18);
  ratio->GetYaxis()->SetTitleOffset(0.56);
  ratio->GetYaxis()->SetTitleFont(42);
  ratio->GetYaxis()->SetNdivisions(505);
  ratio->GetYaxis()->SetTickLength(0.015);
  ratio->GetXaxis()->SetTickLength(0.08);
  ratiounity->Draw();
  ratiogerr->Draw("2 same");
  ratioderr->Draw("p same");

  pad1->cd();
  gPad->RedrawAxis();
  gPad->Modified();
  gPad->Update();
  pad2->cd();
  gPad->RedrawAxis();
  gPad->Modified();
  gPad->Update();
  
  canv->cd();
  CMS_lumi(canv, iPeriod, iPos, lumi_sqrtS);

  gPad->Print(plotdir+plot_title+"_extrap_vs_normal_nj_nb_groups.pdf");


  delete hNormalBoxes;
  delete hEXTRAPBoxes;
  delete leg1;
  delete canv;

  cout << "MakePlots(): DONE!" << endl;


  return;
}

void CompareExtrapData_perNjNb() {

  TH1::SetDefaultSumw2(1);
  //gROOT->SetBatch(1);


  if (gSystem->AccessPathName(plotdir))
    gSystem->mkdir(plotdir);
  // gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  // Setup style
  cout << "Setting tdr style."  << endl;
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  setTDRStyle(tdrStyle);
  tdrStyle->cd();

  gStyle->SetHatchesLineWidth(1);
  gStyle->SetHatchesSpacing(1);


  
  TFile* infile = new TFile("LLPrediction.root","read");

  TH1D* hin = (TH1D*)infile->Get("Prediction_data/totalPred_LL");
  TH1D* hin_extrap = (TH1D*)infile->Get("Prediction_data/totalPred_EXTRAP_LL");
  TH1D* hsystup = (TH1D*)infile->Get("AdditionalContent/totalPropSysUp_LL");
  TH1D* hsystdown = (TH1D*)infile->Get("AdditionalContent/totalPropSysDown_LL");
  TH1D* hnonclosureup = (TH1D*)infile->Get("Prediction_data/totalPredNonClosureUp_LL");
  TH1D* hnonclosuredown = (TH1D*)infile->Get("Prediction_data/totalPredNonClosureDown_LL");

  TProfile* hAvgWeight = (TProfile*)infile->Get("Prediction_MC/avgWeight_LL_MC");
  TProfile* hAvgWeight_extrap = (TProfile*)infile->Get("Prediction_MC/avgWeight_EXTRAP_LL_MC");
  TH1D* hWeightSF = (TH1D*)infile->Get("AvgWeight_MC/EXTRAP_weight_SF_LL_MC");

  Double_t pred_cv[72];
  Double_t pred_cv_extrap[72];
  Double_t x[72];
  Double_t xl[72];
  Double_t xh[72];
  Double_t stat_up[72];
  Double_t stat_down[72];
  Double_t stat_up_extrap[72];
  Double_t stat_down_extrap[72];
  Double_t syst_up[72];
  Double_t syst_down[72];
  Double_t syst_up_extrap[72];
  Double_t syst_down_extrap[72];
  Double_t full_err_up[72];
  Double_t full_err_down[72];
  Double_t full_err_up_extrap[72];
  Double_t full_err_down_extrap[72];

  TH1D* hNormal = new TH1D("hNormal","",72, 0.5, 72.5);
  TH1D* hEXTRAP = new TH1D("hEXTRAP","",72, 0.5, 72.5);

  for (unsigned int bin(0); bin<72; bin++) {
    pred_cv[bin] = hin->GetBinContent(bin+1);
    pred_cv_extrap[bin] = hin_extrap->GetBinContent(bin+1);
    hNormal->SetBinContent(bin+1,hin->GetBinContent(bin+1));
    hEXTRAP->SetBinContent(bin+1,hin_extrap->GetBinContent(bin+1));
    hNormal->SetBinError(bin+1,0);
    hEXTRAP->SetBinError(bin+1,0);
    x[bin] = bin+1;
    xl[bin]=0.5;
    xh[bin]=0.5;
    stat_up[bin] = pow(hAvgWeight->GetBinContent(bin+1)*1.84102, 2.);
    stat_up[bin] += pow(hin->GetBinError(bin+1), 2.);
    stat_down[bin] = pow(hin->GetBinError(bin+1), 2.);
    stat_up_extrap[bin] = pow(hWeightSF->GetBinContent(bin+1)*hAvgWeight->GetBinContent(bin+1)*1.84102, 2.);
    stat_up_extrap[bin] += pow(hin_extrap->GetBinError(bin+1), 2.);
    stat_down_extrap[bin] = pow(hin_extrap->GetBinError(bin+1), 2.);
    syst_up[bin] = 0.;
    syst_down[bin] = 0.;
    syst_up_extrap[bin] = 0.;
    syst_down_extrap[bin] = 0.;
    if (hsystup->GetBinContent(bin+1)>0) {
      syst_up[bin] += pow((hsystup->GetBinContent(bin+1)-1.)*hin->GetBinContent(bin+1), 2.);
      syst_up_extrap[bin] += pow((hsystup->GetBinContent(bin+1)-1.)*hin_extrap->GetBinContent(bin+1), 2.);
    }
    if (hsystdown->GetBinContent(bin+1)>0) {
      syst_down[bin] += pow((1.-hsystdown->GetBinContent(bin+1))*hin->GetBinContent(bin+1), 2.);
      syst_down_extrap[bin] += pow((1.-hsystdown->GetBinContent(bin+1))*hin_extrap->GetBinContent(bin+1), 2.);
    }
    syst_up[bin] += pow((hnonclosureup->GetBinContent(bin+1)-1.)*hin->GetBinContent(bin+1), 2.);
    syst_down[bin] += pow((1.-hnonclosuredown->GetBinContent(bin+1))*hin->GetBinContent(bin+1), 2.);
    syst_up_extrap[bin] += pow((hnonclosureup->GetBinContent(bin+1)-1.)*hin_extrap->GetBinContent(bin+1), 2.);
    syst_down_extrap[bin] += pow((1.-hnonclosuredown->GetBinContent(bin+1))*hin_extrap->GetBinContent(bin+1), 2.);
    
    stat_up[bin]=sqrt(stat_up[bin]);
    stat_down[bin]=sqrt(stat_down[bin]);
    syst_up[bin]=sqrt(syst_up[bin]);
    syst_down[bin]=sqrt(syst_down[bin]);
    stat_up_extrap[bin]=sqrt(stat_up_extrap[bin]);
    stat_down_extrap[bin]=sqrt(stat_down_extrap[bin]);
    syst_up_extrap[bin]=sqrt(syst_up_extrap[bin]);
    syst_down_extrap[bin]=sqrt(syst_down_extrap[bin]);
    if (stat_down[bin]==pred_cv[bin]) syst_down[bin]=0;
    if (stat_down[bin]+syst_down[bin]>pred_cv[bin]) syst_down[bin]=pred_cv[bin]-stat_down[bin];
    if (stat_down_extrap[bin]==pred_cv_extrap[bin]) syst_down_extrap[bin]=0;
    if (stat_down_extrap[bin]+syst_down_extrap[bin]>pred_cv_extrap[bin]) syst_down_extrap[bin]=pred_cv_extrap[bin]-stat_down_extrap[bin];

    full_err_up[bin]=sqrt(stat_up[bin]*stat_up[bin]+syst_up[bin]*syst_up[bin]);
    full_err_down[bin]=sqrt(stat_down[bin]*stat_down[bin]+syst_down[bin]*syst_down[bin]);
    full_err_up_extrap[bin]=sqrt(stat_up_extrap[bin]*stat_up_extrap[bin]+syst_up_extrap[bin]*syst_up_extrap[bin]);
    full_err_down_extrap[bin]=sqrt(stat_down_extrap[bin]*stat_down_extrap[bin]+syst_down_extrap[bin]*syst_down_extrap[bin]);
    
    printf("Bin %d\n\t(normal): %3.5f + %3.5f + %3.5f - %3.5f - %3.5f\n\t(extrap): %3.5f + %3.5f + %3.5f - %3.5f - %3.5f\n", bin+1, pred_cv[bin], stat_up[bin], syst_up[bin], stat_down[bin], syst_down[bin], pred_cv_extrap[bin], stat_up_extrap[bin], syst_up_extrap[bin], stat_down_extrap[bin], syst_down_extrap[bin]);
  }

  TGraphAsymmErrors* gNormal = new TGraphAsymmErrors(72, x, pred_cv, xl, xh, full_err_down, full_err_up);
  TGraphAsymmErrors* gEXTRAP = new TGraphAsymmErrors(72, x, pred_cv_extrap, xl, xh, full_err_down_extrap, full_err_up_extrap);

  MakePlot(4, hNormal, hEXTRAP, gNormal, gEXTRAP, "box4");
  MakePlot(4, hNormal, hEXTRAP, gNormal, gEXTRAP, "box4_log", true);
  MakePlot(5, hNormal, hEXTRAP, gNormal, gEXTRAP, "box5");
  MakePlot(5, hNormal, hEXTRAP, gNormal, gEXTRAP, "box5_log", true);
  MakePlot(6, hNormal, hEXTRAP, gNormal, gEXTRAP, "box6");
  MakePlot(6, hNormal, hEXTRAP, gNormal, gEXTRAP, "box6_log", true);
	 
  
  return;
  
}

