/* 
   Script for drawing a branch from reduec trees with a set of cuts.
*/

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
#include "jack_style.h"
#include <../tdrstyle.C>
// #include <../CMS_lumi.C>

using namespace std;

TString plotdir = "plots/shapes/wRatio/";


void MakePlot(TChain* ch, TString var1, TString var2, TCut common_cuts, TCut cut1, TCut cut2, TCut cut3, TString label1, TString label2, TString label3, TH1D* hTemp, TString plot_title, bool logy=false)
{


  // Book histograms

  TH1D* h1 = (TH1D*) hTemp->Clone("h1");
  TH1D* h2 = (TH1D*) hTemp->Clone("h2");
  TH1D* h3 = (TH1D*) hTemp->Clone("h3");
  TH1D* h4 = (TH1D*) hTemp->Clone("h4");
  TH1D* h5 = (TH1D*) hTemp->Clone("h5");
  TH1D* h6 = (TH1D*) hTemp->Clone("h6");

  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h5->Sumw2();
  h6->Sumw2();
  
  int nbinsx=h2->GetNbinsX();
  double xlow = h2->GetBinLowEdge(1);
  double xup = h2->GetBinLowEdge(nbinsx+1);


  h2->SetLineColor(2000);
  h2->SetMarkerSize(0);
  h2->SetLineWidth(3);

  h1->SetLineColor(2004);
  h1->SetMarkerSize(0);
  h1->SetLineWidth(3);

  h3->SetLineColor(2002);
  h3->SetMarkerSize(0);
  h3->SetLineWidth(3);

  h5->SetLineColor(2000);
  h5->SetMarkerSize(0);
  h5->SetLineWidth(3);
  h5->SetLineStyle(3);

  h4->SetLineColor(2004);
  h4->SetMarkerSize(0);
  h4->SetLineWidth(3);
  h4->SetLineStyle(3);

  h6->SetLineColor(2002);
  h6->SetMarkerSize(0);
  h6->SetLineWidth(3);
  h6->SetLineStyle(3);
 
  h2->GetYaxis()->SetTitleSize(0.035);
  h2->GetYaxis()->SetLabelSize(0.035);
  h2->GetYaxis()->SetTitleOffset(1.3);
  h2->GetXaxis()->SetTitleSize(0.035);
  h2->GetXaxis()->SetLabelSize(0.035);
  h2->GetXaxis()->SetTitleOffset(1.2);

  
  ch->Project("h1",var1,(common_cuts+cut1)*"(Weight)");
  ch->Project("h2",var1,(common_cuts+cut2)*"(Weight)");
  ch->Project("h3",var1,(common_cuts+cut3)*"(Weight)");
  ch->Project("h4",var2,(common_cuts+cut1)*"(Weight)");
  ch->Project("h5",var2,(common_cuts+cut2)*"(Weight)");
  ch->Project("h6",var2,(common_cuts+cut3)*"(Weight)");

  // double mu1=h1->GetMean();
  // double mu_err1=h1->GetMeanError();
  // double mu2=h2->GetMean();
  // double mu_err2=h2->GetMeanError();
  // double mu3=h3->GetMean();
  // double mu_err3=h3->GetMeanError();

  // double mu4=h4->GetMean();
  // double mu_err4=h4->GetMeanError();
  // double mu5=h5->GetMean();
  // double mu_err2=h2->GetMeanError();
  // double mu3=h3->GetMean();
  // double mu_err3=h3->GetMeanError();

  h2->Scale(1/h2->Integral());
  h1->Scale(1/h1->Integral());
  h3->Scale(1/h3->Integral());

  h5->Scale(1/h5->Integral());
  h4->Scale(1/h4->Integral());
  h6->Scale(1/h6->Integral());

  // Setup legends
  TLegend * leg1 = new TLegend(0.17, 0.65, 0.77, 0.85);
  set_style(leg1,0.035);
  leg1->SetHeader("H_{T}^{miss}/p_{T}^{W}");
  leg1->AddEntry(h1, label1.Data(), "le");
  leg1->AddEntry(h2, label2.Data(), "le");
  leg1->AddEntry(h3, label3.Data(), "le");
  // leg1->AddEntry(h1, Form("%s [#mu = %3.2f #pm %3.2f]", label1.Data(), mu1, mu_err1), "le");
  // leg1->AddEntry(h2, Form("%s [#mu = %3.2f #pm %3.2f]", label2.Data(), mu2, mu_err2), "le");
  // leg1->AddEntry(h3, Form("%s [#mu = %3.2f #pm %3.2f]", label3.Data(), mu3, mu_err3), "le");

  TLegend * leg2 = new TLegend(0.17, 0.45, 0.77, 0.65);
  set_style(leg2,0.035);
  leg2->SetHeader("#frac{1}{2}(1-cos#Delta#theta_{T})");
  leg2->AddEntry(h4, label1.Data(), "le");
  leg2->AddEntry(h5, label2.Data(), "le");
  leg2->AddEntry(h6, label3.Data(), "le");

  

  double ymax=h2->GetMaximum();
  if (h1->GetMaximum()>ymax) ymax=h1->GetMaximum();
  if (h3->GetMaximum()>ymax) ymax=h3->GetMaximum();

  if (logy) {
    h2->SetMaximum(ymax*200);
    h2->SetMinimum(0.007);
  } else {
    h2->SetMaximum(ymax*1.3);
    h2->SetMinimum(0.);
  }



 // Setup canvas and pads

  int W = 800;
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
  int W_ref = 800; 

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


  // h2->GetYaxis()->SetLabelSize(0.035*1.4);
  // h2->GetYaxis()->SetTitleSize(0.04*1.34);
  // h2->GetYaxis()->SetTitleOffset(0.9);
  // h2->GetYaxis()->SetTitleFont(42);
  // h2->GetXaxis()->SetLabelSize(0);
  
  h2->Draw("hist e1");
  h1->Draw("hist e1 same");
  h3->Draw("hist e1 same");

  h5->Draw("hist e1 same");
  h4->Draw("hist e1 same");
  h6->Draw("hist e1 same");

  // Draw legends
  leg1->Draw();
  leg2->Draw();

 

  gPad->RedrawAxis();
  gPad->Modified();
  gPad->Update();

  canv->cd();

  gPad->Print(plotdir+"cdtt_"+plot_title+".pdf");


  delete h2;
  delete h1;
  delete h3;

  delete h5;
  delete h4;
  delete h6;


  delete leg1;
  delete canv;

  cout << "MakePlots(): DONE!" << endl;


  return;
}

void CompareExtrapolationShapes() {

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

  TChain* ttbar = new TChain("LostLeptonExpectation");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_0_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_0_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_1_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_1_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_4_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_6_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_2_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_3_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_3_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_5_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_6_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_2_2.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_4_1.root");
  ttbar->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_5_2.root");
  TChain* wjets = new TChain("LostLeptonExpectation");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_7_1.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_7_2.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_8_1.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_8_2.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_9_1.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_9_2.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_10_1.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_10_2.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_11_1.root");
  wjets->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_12_1.root");
  TChain* ST = new TChain("LostLeptonExpectation");
  ST->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_13_1.root");
  ST->Add("root://cmseos.fnal.gov//store/user/jbradmil/LL2016/Expectation_separate/Expectation_13_2.root");

  
  TCut lost_lep="Expectation==1&&ExpectationReductionIsoTrack==0";
  TCut SL="GenMuNum+GenElecNum==1";
  TCut lost_mu=lost_lep+"GenMuNum==1&&GenElecNum==0";
  TCut lost_el=lost_lep+"GenMuNum==0&&GenElecNum==1";

  TH1D* hTemplate= new TH1D("hTemplate",";Extrapolation variable;Fraction of events", 13, 0, 1.3);

  TString CDTTmu = "0.5*(1-GenMuCDTT[0])";
  TString CDTTel = "0.5*(1-GenElecCDTT[0])";
  TString RATIOmu = "MHT/sqrt( (GenMus[0].Px()+MHT*cos(MHT_Phi))*(GenMus[0].Px()+MHT*cos(MHT_Phi)) +  (GenMus[0].Py()+MHT*sin(MHT_Phi))*(GenMus[0].Py()+MHT*sin(MHT_Phi)) )";
  TString RATIOel = "MHT/sqrt( (GenEls[0].Px()+MHT*cos(MHT_Phi))*(GenEls[0].Px()+MHT*cos(MHT_Phi)) +  (GenEls[0].Py()+MHT*sin(MHT_Phi))*(GenEls[0].Py()+MHT*sin(MHT_Phi)) )";
  TString PTWmu = "sqrt( (GenMus[0].Px()+MHT*cos(MHT_Phi))*(GenMus[0].Px()+MHT*cos(MHT_Phi)) +  (GenMus[0].Py()+MHT*sin(MHT_Phi))*(GenMus[0].Py()+MHT*sin(MHT_Phi)) )";
  TString PTWel = "sqrt( (GenEls[0].Px()+MHT*cos(MHT_Phi))*(GenEls[0].Px()+MHT*cos(MHT_Phi)) +  (GenEls[0].Py()+MHT*sin(MHT_Phi))*(GenEls[0].Py()+MHT*sin(MHT_Phi)) )";

  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, Form("200<%s&&%s<400", PTWmu.Data(), PTWmu.Data()), Form("400<%s&&%s<750", PTWmu.Data(),PTWmu.Data()), Form("%s>750", PTWmu.Data()), "200< p_{T}^{W} < 400", "400 < p_{T}^{W} < 750", "p_{T}^{W} > 750", hTemplate, "all_mu_ttbar_vs_ptw");

    MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, "200<MHT&&MHT<500", "500<MHT&&MHT<750", "MHT>750", "200 < H_{T}^{miss} < 500", "500 < H_{T}^{miss} < 750", "H_{T}^{miss} > 750", hTemplate, "all_mu_ttbar_vs_mht");

  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu+"MHT>500", "GenMus[0].Pt()<10", "GenMus[0].Pt()>10&&GenMus[0].Pt()<100", "GenMus[0].Pt()>100", "p_{T}^{#mu} < 10", "10 < p_{T}^{#mu} < 100", "p_{T}^{#mu} > 100", hTemplate, "lost_mu_ttbar_vs_pt_MHT500");
  
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu+"MHT>500", "muAcc==0", "muReco==0", "muIso==0", "Out-of-acceptance", "Fails RECO/ID", "Fails isolation", hTemplate, "all_mu_ttbar_vs_category_MHT500");

  
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, "muAcc==0", "muReco==0", "muIso==0", "Out-of-acceptance", "Fails RECO/ID", "Fails isolation", hTemplate, "all_mu_ttbar_vs_category");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el, "elecAcc==0", "elecReco==0", "elecIso==0", "Out-of-acceptance", "Fails RECO/ID", "Fails isolation", hTemplate, "all_el_ttbar_vs_category");


  MakePlot(ttbar, CDTTmu, RATIOmu, SL, "GenMus[0].Pt()<10", "GenMus[0].Pt()>10&&GenMus[0].Pt()<100", "GenMus[0].Pt()>100", "p_{T}^{#mu} < 10", "10 < p_{T}^{#mu} < 100", "p_{T}^{#mu} > 100", hTemplate, "all_mu_ttbar_vs_pt");
  MakePlot(ttbar, CDTTel, RATIOel, SL, "GenEls[0].Pt()<10", "GenEls[0].Pt()>10&&GenEls[0].Pt()<100", "GenEls[0].Pt()>100", "p_{T}^{e} < 10", "10 < p_{T}^{e} < 100", "p_{T}^{e} > 100", hTemplate, "all_el_ttbar_vs_pt");
  
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_ttbar_vs_nb-jets");
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu+"NJets==4", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_ttbar_vs_nb-jets_4j");
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu+"NJets==4&&HT>500&&HT<800", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_ttbar_vs_nb-jets_4j_ht1");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el, "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_ttbar_vs_nb-jets");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el+"NJets==4", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_ttbar_vs_nb-jets_4j");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el+"NJets==4&&HT>500&&HT<800", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_ttbar_vs_nb-jets_4j_ht1");
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, "NJets>3&&NJets<7", "NJets>6&&NJets<9", "NJets>8", "4-6 jets", "7-8 jets", "9+ jets", hTemplate, "lost_mu_ttbar_vs_njets");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el, "NJets>3&&NJets<7", "NJets>6&&NJets<9", "NJets>8", "4-6 jets", "7-8 jets", "9+ jets", hTemplate, "lost_el_ttbar_vs_njets");
  MakePlot(ttbar, CDTTmu, RATIOmu, lost_mu, "HT>500&&HT<800", "HT>800&&HT<1200", "HT>1200", "500 < H_{T} < 800", "800 < H_{T} < 1200", "H_{T} > 1200", hTemplate, "lost_mu_ttbar_vs_ht");
  MakePlot(ttbar, CDTTel, RATIOel, lost_el, "HT>500&&HT<800", "HT>800&&HT<1200", "HT>1200", "500 < H_{T} < 800", "800 < H_{T} < 1200", "H_{T} > 1200", hTemplate, "lost_el_ttbar_vs_ht");

  MakePlot(wjets, CDTTmu, RATIOmu, lost_mu, "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_wjets_vs_nb-jets");
  MakePlot(wjets, CDTTmu, RATIOmu, lost_mu+"NJets==4", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_wjets_vs_nb-jets_4j");
  MakePlot(wjets, CDTTmu, RATIOmu, lost_mu+"NJets==4&&HT>500&&HT<800", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_mu_wjets_vs_nb-jets_4j_ht1");
  MakePlot(wjets, CDTTel, RATIOel, lost_el, "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_wjets_vs_nb-jets");
  MakePlot(wjets, CDTTel, RATIOel, lost_el+"NJets==4", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_wjets_vs_nb-jets_4j");
  MakePlot(wjets, CDTTel, RATIOel, lost_el+"NJets==4&&HT>500&&HT<800", "BTags==0", "BTags==1", "BTags>=2", "0 b-jets", "1 b-jets", "2+ b-jets", hTemplate, "lost_el_wjets_vs_nb-jets_4j_ht1");
  MakePlot(wjets, CDTTmu, RATIOmu, lost_mu, "NJets>3&&NJets<7", "NJets>6&&NJets<9", "NJets>8", "4-6 jets", "7-8 jets", "9+ jets", hTemplate, "lost_mu_wjets_vs_njets");
  MakePlot(wjets, CDTTel, RATIOel, lost_el, "NJets>3&&NJets<7", "NJets>6&&NJets<9", "NJets>8", "4-6 jets", "7-8 jets", "9+ jets", hTemplate, "lost_el_wjets_vs_njets");
  MakePlot(wjets, CDTTmu, RATIOmu, lost_mu, "HT>500&&HT<800", "HT>800&&HT<1200", "HT>1200", "500 < H_{T} < 800", "800 < H_{T} < 1200", "H_{T} > 1200", hTemplate, "lost_mu_wjets_vs_ht");
  MakePlot(wjets, CDTTel, RATIOel, lost_el, "HT>500&&HT<800", "HT>800&&HT<1200", "HT>1200", "500 < H_{T} < 800", "800 < H_{T} < 1200", "H_{T} > 1200", hTemplate, "lost_el_wjets_vs_ht");


  
  return;
  
}

