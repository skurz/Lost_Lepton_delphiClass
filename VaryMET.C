#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <vector>
#include "LLTools.h"
#include "THEff.h"
#include "TStyle.h"
#include <cmath>


TH2D* saveEff(TH2D* h_ratio, TFile *outFile){
	if(outFile) outFile->cd();

	h_ratio->SetMarkerSize(1.2);
	h_ratio->GetZaxis()->SetRangeUser(0., 1.5);

	h_ratio->GetXaxis()->SetTitle("HT");
	if(h_ratio->GetYaxis()->GetXmax() > 100) h_ratio->GetYaxis()->SetTitle("MHT");
	else h_ratio->GetYaxis()->SetTitle("NJets");

  	TString name(h_ratio->GetName());

  	gROOT->SetBatch(true);
  	TCanvas *c1 = new TCanvas(name,name,1);
	c1->cd();
	c1->SetLogx();
	if(h_ratio->GetYaxis()->GetXmax() > 100) c1->SetLogy();
	gStyle->SetOptStat(0);
	gStyle->SetPaintTextFormat("5.4f");
  	gStyle->SetStatW(0.1);
  	gStyle->SetStatH(0.1);
  	gStyle->SetStatY(202);
  	gStyle->SetTitleYOffset(1.3);

  	gStyle->SetPalette(56);
  	gStyle->SetMarkerSize(1.5);
  	if(h_ratio->GetBinError(2,2) > 0) h_ratio->Draw("ColZ,Text,E");
  	else h_ratio->Draw("ColZ,Text");
  	c1->SaveAs(TString("MTWUncertainty/")+name+TString(".pdf"));
  	delete c1;
  	gROOT->SetBatch(false);

  	if(outFile) h_ratio->Write();

  	return h_ratio;
}

TH1D* saveEff(TH1D* h_ratio, TFile *outFile){
	if(outFile) outFile->cd();

	h_ratio->SetMarkerSize(1.2);
	h_ratio->GetZaxis()->SetRangeUser(0., 1.5);

	h_ratio->GetXaxis()->SetTitle("NJets");
  	TString name(h_ratio->GetName());

  	gROOT->SetBatch(true);
  	TCanvas *c1 = new TCanvas(name,name,1);
	c1->cd();

	gStyle->SetOptStat(0);
	gStyle->SetPaintTextFormat("5.4f");
  	gStyle->SetStatW(0.1);
  	gStyle->SetStatH(0.1);
  	gStyle->SetStatY(202);
  	gStyle->SetTitleYOffset(1.3);

  	gStyle->SetPalette(56);
  	gStyle->SetMarkerSize(1.5);
  	h_ratio->Draw("Text,E");
  	c1->SaveAs(TString("MTWUncertainty/")+name+TString(".pdf"));
  	delete c1;
  	gROOT->SetBatch(false);

  	if(outFile) h_ratio->Write();

  	return h_ratio;
}

TH2D* divideEff(TH2D* h_pass, TH2D* h_fail){
	TString name(h_pass->GetName());	
	name = name(0, name.Length()-5);

	TH2D* h_ratio = (TH2D*) h_pass->Clone(name);
	h_ratio->Add(h_fail);

	h_ratio->Divide(h_pass, h_ratio, 1, 1, "B");
	h_ratio->SetName(name);

	saveEff(h_ratio, 0);

  	return h_ratio;
}

TH1D* divideEff(TH1D* h_pass, TH1D* h_fail){
	TString name(h_pass->GetName());	
	name = name(0, name.Length()-5);

	TH1D* h_ratio = (TH1D*) h_pass->Clone(name);
	h_ratio->Add(h_fail);

	h_ratio->Divide(h_pass, h_ratio, 1, 1, "B");
	h_ratio->SetName(name);

	saveEff(h_ratio, 0);

  	return h_ratio;
}


void VaryMET(){

	bool showRatio = true;

	UShort_t        Bin;
	UShort_t        BinQCD;
	Double_t        Weight;
	Double_t        HT;
	Double_t        MHT;
	Int_t           NJets;
	Int_t           BTags;
  	Float_t         MTW;
  	Float_t         MTW_METup;
  	Float_t         MTW_METdown;
  	UShort_t        muIso;
  	UShort_t        elecIso;


	gROOT->Reset();
	TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject("Expectation.root");
	if (!fExp) {
    	fExp = new TFile("Expectation.root");
	}
	TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");

	LostLeptonExpectation->SetBranchStatus("*",0);
	LostLeptonExpectation->SetBranchStatus("HT",1);
	LostLeptonExpectation->SetBranchStatus("MHT",1);
	LostLeptonExpectation->SetBranchStatus("NJets",1);
	LostLeptonExpectation->SetBranchStatus("BTags",1);
	LostLeptonExpectation->SetBranchStatus("Weight",1);
	LostLeptonExpectation->SetBranchStatus("Bin",1);
	LostLeptonExpectation->SetBranchStatus("BinQCD",1);
	LostLeptonExpectation->SetBranchStatus("MTW",1);
	LostLeptonExpectation->SetBranchStatus("MTW_METup",1);
	LostLeptonExpectation->SetBranchStatus("MTW_METdown",1);
	LostLeptonExpectation->SetBranchStatus("muIso",1);
	LostLeptonExpectation->SetBranchStatus("elecIso",1);

	LostLeptonExpectation->SetBranchAddress("HT",&HT);
	LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
	LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
	LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
	LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
	LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
	LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
	LostLeptonExpectation->SetBranchAddress("MTW",&MTW);
	LostLeptonExpectation->SetBranchAddress("MTW_METup",&MTW_METup);
	LostLeptonExpectation->SetBranchAddress("MTW_METdown",&MTW_METdown);
	LostLeptonExpectation->SetBranchAddress("muIso",&muIso);
	LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);

	TH1::SetDefaultSumw2();

	const int threeDHT_=4;
	double ThreeDHT_[threeDHT_] = {300,500,1000,10000};
	const int threeDMHT_=4;
	double ThreeDMHT_[threeDMHT_] = {250,350,500,10000};
	const int twoDNJets_=8;
	double TwoDNJets_[twoDNJets_] = {1.5,2.5,3.5,4.5,5.5,6.5,8.5,21.5};
	const int twoDHT_=6;
	double TwoDHT_[twoDHT_] = {250,500,750,1000,1500,10000};
	TH2D* MuMTWHTNJets_ = new TH2D("MuMTWHTNJets","MuMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_METup_ = new TH2D("MuMTWHTNJets_METup","MuMTWHTNJets_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_METdown_ = new TH2D("MuMTWHTNJets_METdown","MuMTWHTNJets_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Pass_ = new TH2D("MuMTWHTNJets_Pass","MuMTWHTNJets_Pass",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Pass_METup_ = new TH2D("MuMTWHTNJets_Pass_METup","MuMTWHTNJets_Pass_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Pass_METdown_ = new TH2D("MuMTWHTNJets_Pass_METdown","MuMTWHTNJets_Pass_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Total_ = new TH2D("MuMTWHTNJets_Total","MuMTWHTNJets_Total",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Total_METup_ = new TH2D("MuMTWHTNJets_Total_METup","MuMTWHTNJets_Total_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* MuMTWHTNJets_Total_METdown_ = new TH2D("MuMTWHTNJets_Total_METdown","MuMTWHTNJets_Total_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);

	TH2D* ElecMTWHTNJets_ = new TH2D("ElecMTWHTNJets","ElecMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_METup_ = new TH2D("ElecMTWHTNJets_METup","ElecMTWHTNJets_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_METdown_ = new TH2D("ElecMTWHTNJets_METdown","ElecMTWHTNJets_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Pass_ = new TH2D("ElecMTWHTNJets_Pass","ElecMTWHTNJets_Pass",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Pass_METup_ = new TH2D("ElecMTWHTNJets_Pass_METup","ElecMTWHTNJets_Pass_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Pass_METdown_ = new TH2D("ElecMTWHTNJets_Pass_METdown","ElecMTWHTNJets_Pass_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Total_ = new TH2D("ElecMTWHTNJets_Total","ElecMTWHTNJets_Total",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Total_METup_ = new TH2D("ElecMTWHTNJets_Total_METup","ElecMTWHTNJets_Total_METup",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
	TH2D* ElecMTWHTNJets_Total_METdown_ = new TH2D("ElecMTWHTNJets_Total_METdown","ElecMTWHTNJets_Total_METdown",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);

	TH2D* MuMTWHTMHT_NJets2_ = new TH2D("MuMTWHTMHT_NJets2","MuMTWHTMHT_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_ = new TH2D("MuMTWHTMHT_NJets3","MuMTWHTMHT_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_ = new TH2D("MuMTWHTMHT_NJets4","MuMTWHTMHT_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_ = new TH2D("MuMTWHTMHT_NJets5","MuMTWHTMHT_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_ = new TH2D("MuMTWHTMHT_NJets6","MuMTWHTMHT_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_ = new TH2D("MuMTWHTMHT_NJets78"," MuMTWHTMHT_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_ = new TH2D("MuMTWHTMHT_NJets9Inf"," MuMTWHTMHT_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_ = new TH2D("MuMTWHTMHT_NJets7Inf"," MuMTWHTMHT_NJets7Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_METup_ = new TH2D("MuMTWHTMHT_NJets2_METup","MuMTWHTMHT_NJets2_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_METup_ = new TH2D("MuMTWHTMHT_NJets3_METup","MuMTWHTMHT_NJets3_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_METup_ = new TH2D("MuMTWHTMHT_NJets4_METup","MuMTWHTMHT_NJets4_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_METup_ = new TH2D("MuMTWHTMHT_NJets5_METup","MuMTWHTMHT_NJets5_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_METup_ = new TH2D("MuMTWHTMHT_NJets6_METup","MuMTWHTMHT_NJets6_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_METup_ = new TH2D("MuMTWHTMHT_NJets78_METup"," MuMTWHTMHT_NJets78_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_METup_ = new TH2D("MuMTWHTMHT_NJets9Inf_METup"," MuMTWHTMHT_NJets9Inf_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_METup_ = new TH2D("MuMTWHTMHT_NJets7Inf_METup"," MuMTWHTMHT_NJets7Inf_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_METdown_ = new TH2D("MuMTWHTMHT_NJets2_METdown","MuMTWHTMHT_NJets2_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_METdown_ = new TH2D("MuMTWHTMHT_NJets3_METdown","MuMTWHTMHT_NJets3_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_METdown_ = new TH2D("MuMTWHTMHT_NJets4_METdown","MuMTWHTMHT_NJets4_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_METdown_ = new TH2D("MuMTWHTMHT_NJets5_METdown","MuMTWHTMHT_NJets5_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_METdown_ = new TH2D("MuMTWHTMHT_NJets6_METdown","MuMTWHTMHT_NJets6_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_METdown_ = new TH2D("MuMTWHTMHT_NJets78_METdown"," MuMTWHTMHT_NJets78_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_METdown_ = new TH2D("MuMTWHTMHT_NJets9Inf_METdown"," MuMTWHTMHT_NJets9Inf_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_METdown_ = new TH2D("MuMTWHTMHT_NJets7Inf_METdown"," MuMTWHTMHT_NJets7Inf_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Pass_ = new TH2D("MuMTWHTMHT_NJets2_Pass","MuMTWHTMHT_NJets2_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Pass_ = new TH2D("MuMTWHTMHT_NJets3_Pass","MuMTWHTMHT_NJets3_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Pass_ = new TH2D("MuMTWHTMHT_NJets4_Pass","MuMTWHTMHT_NJets4_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Pass_ = new TH2D("MuMTWHTMHT_NJets5_Pass","MuMTWHTMHT_NJets5_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Pass_ = new TH2D("MuMTWHTMHT_NJets6_Pass","MuMTWHTMHT_NJets6_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Pass_ = new TH2D("MuMTWHTMHT_NJets78_Pass"," MuMTWHTMHT_NJets78_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Pass_ = new TH2D("MuMTWHTMHT_NJets9Inf_Pass"," MuMTWHTMHT_NJets9Inf_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Pass_ = new TH2D("MuMTWHTMHT_NJets7Inf_Pass"," MuMTWHTMHT_NJets7Inf_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets2_Pass_METup","MuMTWHTMHT_NJets2_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets3_Pass_METup","MuMTWHTMHT_NJets3_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets4_Pass_METup","MuMTWHTMHT_NJets4_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets5_Pass_METup","MuMTWHTMHT_NJets5_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets6_Pass_METup","MuMTWHTMHT_NJets6_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets78_Pass_METup"," MuMTWHTMHT_NJets78_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets9Inf_Pass_METup"," MuMTWHTMHT_NJets9Inf_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Pass_METup_ = new TH2D("MuMTWHTMHT_NJets7Inf_Pass_METup"," MuMTWHTMHT_NJets7Inf_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets2_Pass_METdown","MuMTWHTMHT_NJets2_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets3_Pass_METdown","MuMTWHTMHT_NJets3_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets4_Pass_METdown","MuMTWHTMHT_NJets4_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets5_Pass_METdown","MuMTWHTMHT_NJets5_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets6_Pass_METdown","MuMTWHTMHT_NJets6_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets78_Pass_METdown"," MuMTWHTMHT_NJets78_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets9Inf_Pass_METdown"," MuMTWHTMHT_NJets9Inf_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Pass_METdown_ = new TH2D("MuMTWHTMHT_NJets7Inf_Pass_METdown"," MuMTWHTMHT_NJets7Inf_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Total_ = new TH2D("MuMTWHTMHT_NJets2_Total","MuMTWHTMHT_NJets2_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Total_ = new TH2D("MuMTWHTMHT_NJets3_Total","MuMTWHTMHT_NJets3_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Total_ = new TH2D("MuMTWHTMHT_NJets4_Total","MuMTWHTMHT_NJets4_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Total_ = new TH2D("MuMTWHTMHT_NJets6_Total","MuMTWHTMHT_NJets6_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Total_ = new TH2D("MuMTWHTMHT_NJets5_Total","MuMTWHTMHT_NJets5_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Total_ = new TH2D("MuMTWHTMHT_NJets78_Total"," MuMTWHTMHT_NJets78_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Total_ = new TH2D("MuMTWHTMHT_NJets9Inf_Total"," MuMTWHTMHT_NJets9Inf_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Total_ = new TH2D("MuMTWHTMHT_NJets7Inf_Total"," MuMTWHTMHT_NJets7Inf_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Total_METup_ = new TH2D("MuMTWHTMHT_NJets2_Total_METup","MuMTWHTMHT_NJets2_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Total_METup_ = new TH2D("MuMTWHTMHT_NJets3_Total_METup","MuMTWHTMHT_NJets3_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Total_METup_ = new TH2D("MuMTWHTMHT_NJets4_Total_METup","MuMTWHTMHT_NJets4_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Total_METup_ = new TH2D("MuMTWHTMHT_NJets5_Total_METup","MuMTWHTMHT_NJets5_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Total_METup_ = new TH2D("MuMTWHTMHT_NJets6_Total_METup","MuMTWHTMHT_NJets6_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Total_METup_ = new TH2D("MuMTWHTMHT_NJets78_Total_METup"," MuMTWHTMHT_NJets78_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Total_METup_ = new TH2D("MuMTWHTMHT_NJets9Inf_Total_METup"," MuMTWHTMHT_NJets9Inf_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Total_METup_ = new TH2D("MuMTWHTMHT_NJets7Inf_Total_METup"," MuMTWHTMHT_NJets7Inf_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets2_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets2_Total_METdown","MuMTWHTMHT_NJets2_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets3_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets3_Total_METdown","MuMTWHTMHT_NJets3_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets4_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets4_Total_METdown","MuMTWHTMHT_NJets4_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets5_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets5_Total_METdown","MuMTWHTMHT_NJets5_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets6_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets6_Total_METdown","MuMTWHTMHT_NJets6_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets78_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets78_Total_METdown"," MuMTWHTMHT_NJets78_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets9Inf_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets9Inf_Total_METdown"," MuMTWHTMHT_NJets9Inf_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuMTWHTMHT_NJets7Inf_Total_METdown_ = new TH2D("MuMTWHTMHT_NJets7Inf_Total_METdown"," MuMTWHTMHT_NJets7Inf_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH2D* ElecMTWHTMHT_NJets2_ = new TH2D("ElecMTWHTMHT_NJets2","ElecMTWHTMHT_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_ = new TH2D("ElecMTWHTMHT_NJets3","ElecMTWHTMHT_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_ = new TH2D("ElecMTWHTMHT_NJets4","ElecMTWHTMHT_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_ = new TH2D("ElecMTWHTMHT_NJets5","ElecMTWHTMHT_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_ = new TH2D("ElecMTWHTMHT_NJets6","ElecMTWHTMHT_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_ = new TH2D("ElecMTWHTMHT_NJets78"," ElecMTWHTMHT_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_ = new TH2D("ElecMTWHTMHT_NJets9Inf"," ElecMTWHTMHT_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_ = new TH2D("ElecMTWHTMHT_NJets7Inf"," ElecMTWHTMHT_NJets7Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_METup_ = new TH2D("ElecMTWHTMHT_NJets2_METup","ElecMTWHTMHT_NJets2_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_METup_ = new TH2D("ElecMTWHTMHT_NJets3_METup","ElecMTWHTMHT_NJets3_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_METup_ = new TH2D("ElecMTWHTMHT_NJets4_METup","ElecMTWHTMHT_NJets4_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_METup_ = new TH2D("ElecMTWHTMHT_NJets5_METup","ElecMTWHTMHT_NJets5_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_METup_ = new TH2D("ElecMTWHTMHT_NJets6_METup","ElecMTWHTMHT_NJets6_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_METup_ = new TH2D("ElecMTWHTMHT_NJets78_METup"," ElecMTWHTMHT_NJets78_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_METup_ = new TH2D("ElecMTWHTMHT_NJets9Inf_METup"," ElecMTWHTMHT_NJets9Inf_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_METup_ = new TH2D("ElecMTWHTMHT_NJets7Inf_METup"," ElecMTWHTMHT_NJets7Inf_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_METdown_ = new TH2D("ElecMTWHTMHT_NJets2_METdown","ElecMTWHTMHT_NJets2_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_METdown_ = new TH2D("ElecMTWHTMHT_NJets3_METdown","ElecMTWHTMHT_NJets3_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_METdown_ = new TH2D("ElecMTWHTMHT_NJets4_METdown","ElecMTWHTMHT_NJets4_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_METdown_ = new TH2D("ElecMTWHTMHT_NJets5_METdown","ElecMTWHTMHT_NJets5_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_METdown_ = new TH2D("ElecMTWHTMHT_NJets6_METdown","ElecMTWHTMHT_NJets6_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_METdown_ = new TH2D("ElecMTWHTMHT_NJets78_METdown"," ElecMTWHTMHT_NJets78_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_METdown_ = new TH2D("ElecMTWHTMHT_NJets9Inf_METdown"," ElecMTWHTMHT_NJets9Inf_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_METdown_ = new TH2D("ElecMTWHTMHT_NJets7Inf_METdown"," ElecMTWHTMHT_NJets7Inf_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Pass_ = new TH2D("ElecMTWHTMHT_NJets2_Pass","ElecMTWHTMHT_NJets2_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Pass_ = new TH2D("ElecMTWHTMHT_NJets3_Pass","ElecMTWHTMHT_NJets3_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Pass_ = new TH2D("ElecMTWHTMHT_NJets4_Pass","ElecMTWHTMHT_NJets4_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Pass_ = new TH2D("ElecMTWHTMHT_NJets5_Pass","ElecMTWHTMHT_NJets5_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Pass_ = new TH2D("ElecMTWHTMHT_NJets6_Pass","ElecMTWHTMHT_NJets6_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Pass_ = new TH2D("ElecMTWHTMHT_NJets78_Pass"," ElecMTWHTMHT_NJets78_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Pass_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Pass"," ElecMTWHTMHT_NJets9Inf_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Pass_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Pass"," ElecMTWHTMHT_NJets7Inf_Pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets2_Pass_METup","ElecMTWHTMHT_NJets2_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets3_Pass_METup","ElecMTWHTMHT_NJets3_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets4_Pass_METup","ElecMTWHTMHT_NJets4_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets5_Pass_METup","ElecMTWHTMHT_NJets5_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets6_Pass_METup","ElecMTWHTMHT_NJets6_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets78_Pass_METup"," ElecMTWHTMHT_NJets78_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Pass_METup"," ElecMTWHTMHT_NJets9Inf_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Pass_METup_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Pass_METup"," ElecMTWHTMHT_NJets7Inf_Pass_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets2_Pass_METdown","ElecMTWHTMHT_NJets2_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets3_Pass_METdown","ElecMTWHTMHT_NJets3_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets4_Pass_METdown","ElecMTWHTMHT_NJets4_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets5_Pass_METdown","ElecMTWHTMHT_NJets5_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets6_Pass_METdown","ElecMTWHTMHT_NJets6_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets78_Pass_METdown"," ElecMTWHTMHT_NJets78_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Pass_METdown"," ElecMTWHTMHT_NJets9Inf_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Pass_METdown_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Pass_METdown"," ElecMTWHTMHT_NJets7Inf_Pass_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Total_ = new TH2D("ElecMTWHTMHT_NJets2_Total","ElecMTWHTMHT_NJets2_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Total_ = new TH2D("ElecMTWHTMHT_NJets3_Total","ElecMTWHTMHT_NJets3_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Total_ = new TH2D("ElecMTWHTMHT_NJets4_Total","ElecMTWHTMHT_NJets4_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Total_ = new TH2D("ElecMTWHTMHT_NJets6_Total","ElecMTWHTMHT_NJets6_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Total_ = new TH2D("ElecMTWHTMHT_NJets5_Total","ElecMTWHTMHT_NJets5_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Total_ = new TH2D("ElecMTWHTMHT_NJets78_Total"," ElecMTWHTMHT_NJets78_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Total_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Total"," ElecMTWHTMHT_NJets9Inf_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Total_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Total"," ElecMTWHTMHT_NJets7Inf_Total",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets2_Total_METup","ElecMTWHTMHT_NJets2_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets3_Total_METup","ElecMTWHTMHT_NJets3_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets4_Total_METup","ElecMTWHTMHT_NJets4_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets5_Total_METup","ElecMTWHTMHT_NJets5_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets6_Total_METup","ElecMTWHTMHT_NJets6_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets78_Total_METup"," ElecMTWHTMHT_NJets78_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Total_METup"," ElecMTWHTMHT_NJets9Inf_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Total_METup_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Total_METup"," ElecMTWHTMHT_NJets7Inf_Total_METup",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets2_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets2_Total_METdown","ElecMTWHTMHT_NJets2_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets3_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets3_Total_METdown","ElecMTWHTMHT_NJets3_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets4_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets4_Total_METdown","ElecMTWHTMHT_NJets4_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets5_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets5_Total_METdown","ElecMTWHTMHT_NJets5_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets6_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets6_Total_METdown","ElecMTWHTMHT_NJets6_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets78_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets78_Total_METdown"," ElecMTWHTMHT_NJets78_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets9Inf_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets9Inf_Total_METdown"," ElecMTWHTMHT_NJets9Inf_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecMTWHTMHT_NJets7Inf_Total_METdown_ = new TH2D("ElecMTWHTMHT_NJets7Inf_Total_METdown"," ElecMTWHTMHT_NJets7Inf_Total_METdown",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);



	Long64_t nentries = LostLeptonExpectation->GetEntries();
	for (Long64_t i=0; i<nentries;i++) {
    	LostLeptonExpectation->GetEntry(i);
    	if(HT<300 || MHT<250 || NJets<1.5) continue;

    	if(Weight<0) Weight*=-1;

	    if(muIso==2){
	    	if(MTW < 100){
	    		MuMTWHTNJets_Pass_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets2_Total_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets3_Total_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	MuMTWHTMHT_NJets4_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets4_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	MuMTWHTMHT_NJets5_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets5_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	MuMTWHTMHT_NJets6_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets6_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	MuMTWHTMHT_NJets78_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets78_Total_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	MuMTWHTMHT_NJets9Inf_Pass_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets9Inf_Total_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		MuMTWHTNJets_Total_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Total_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Total_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		MuMTWHTMHT_NJets4_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		MuMTWHTMHT_NJets5_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		MuMTWHTMHT_NJets6_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		MuMTWHTMHT_NJets78_Total_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		MuMTWHTMHT_NJets9Inf_Total_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    	if(MTW_METup < 100){
	    		MuMTWHTNJets_Pass_METup_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets2_Total_METup_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets3_Total_METup_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	MuMTWHTMHT_NJets4_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets4_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	MuMTWHTMHT_NJets5_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets5_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	MuMTWHTMHT_NJets6_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets6_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	MuMTWHTMHT_NJets78_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets78_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	MuMTWHTMHT_NJets9Inf_Pass_METup_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets9Inf_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		MuMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Total_METup_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Total_METup_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		MuMTWHTMHT_NJets4_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		MuMTWHTMHT_NJets5_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		MuMTWHTMHT_NJets6_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		MuMTWHTMHT_NJets78_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		MuMTWHTMHT_NJets9Inf_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    	if(MTW_METdown < 100){
	    		MuMTWHTNJets_Pass_METdown_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets2_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets3_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	MuMTWHTMHT_NJets4_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets4_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	MuMTWHTMHT_NJets5_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets5_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	MuMTWHTMHT_NJets6_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets6_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	MuMTWHTMHT_NJets78_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets78_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	MuMTWHTMHT_NJets9Inf_Pass_METdown_->Fill(HT,MHT,Weight);
		        		MuMTWHTMHT_NJets9Inf_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		MuMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		MuMTWHTMHT_NJets2_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		MuMTWHTMHT_NJets3_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		MuMTWHTMHT_NJets4_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		MuMTWHTMHT_NJets5_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		MuMTWHTMHT_NJets6_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		MuMTWHTMHT_NJets78_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		MuMTWHTMHT_NJets9Inf_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    }

	    if(elecIso==2){
	    	if(MTW < 100){
	    		ElecMTWHTNJets_Pass_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets2_Total_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets3_Total_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	ElecMTWHTMHT_NJets4_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets4_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	ElecMTWHTMHT_NJets5_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets5_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	ElecMTWHTMHT_NJets6_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets6_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	ElecMTWHTMHT_NJets78_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets78_Total_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	ElecMTWHTMHT_NJets9Inf_Pass_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets9Inf_Total_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		ElecMTWHTNJets_Total_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Total_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Total_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		ElecMTWHTMHT_NJets4_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		ElecMTWHTMHT_NJets5_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		ElecMTWHTMHT_NJets6_Total_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		ElecMTWHTMHT_NJets78_Total_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		ElecMTWHTMHT_NJets9Inf_Total_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    	if(MTW_METup < 100){
	    		ElecMTWHTNJets_Pass_METup_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets2_Total_METup_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets3_Total_METup_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	ElecMTWHTMHT_NJets4_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets4_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	ElecMTWHTMHT_NJets5_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets5_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	ElecMTWHTMHT_NJets6_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets6_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	ElecMTWHTMHT_NJets78_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets78_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	ElecMTWHTMHT_NJets9Inf_Pass_METup_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets9Inf_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		ElecMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Total_METup_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Total_METup_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		ElecMTWHTMHT_NJets4_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		ElecMTWHTMHT_NJets5_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		ElecMTWHTMHT_NJets6_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		ElecMTWHTMHT_NJets78_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		ElecMTWHTMHT_NJets9Inf_Total_METup_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    	if(MTW_METdown < 100){
	    		ElecMTWHTNJets_Pass_METdown_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets2_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets3_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
			        	ElecMTWHTMHT_NJets4_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets4_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
			        	ElecMTWHTMHT_NJets5_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets5_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
			        	ElecMTWHTMHT_NJets6_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets6_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
			        	ElecMTWHTMHT_NJets78_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets78_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        default:
			        	ElecMTWHTMHT_NJets9Inf_Pass_METdown_->Fill(HT,MHT,Weight);
		        		ElecMTWHTMHT_NJets9Inf_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}else{
	    		ElecMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);

	    		switch(NJets){
		    		case 2:
		        		ElecMTWHTMHT_NJets2_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
		        	case 3:
		        		ElecMTWHTMHT_NJets3_Total_METdown_->Fill(HT,MHT,Weight);
			            break;
			        case 4:
		        		ElecMTWHTMHT_NJets4_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 5:
		        		ElecMTWHTMHT_NJets5_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 6:
		        		ElecMTWHTMHT_NJets6_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        case 7:
			        case 8:
		        		ElecMTWHTMHT_NJets78_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
			        default:
		        		ElecMTWHTMHT_NJets9Inf_Total_METdown_->Fill(HT,MHT,Weight);
			        	break;
		    	}
	    	}
	    }
	}
	      

	MuMTWHTNJets_->Divide(MuMTWHTNJets_Pass_, MuMTWHTNJets_Total_, 1, 1, "B");
	MuMTWHTNJets_METup_->Divide(MuMTWHTNJets_Pass_METup_, MuMTWHTNJets_Total_METup_, 1, 1, "B");
	MuMTWHTNJets_METdown_->Divide(MuMTWHTNJets_Pass_METdown_, MuMTWHTNJets_Total_METdown_, 1, 1, "B");

	ElecMTWHTNJets_->Divide(ElecMTWHTNJets_Pass_, ElecMTWHTNJets_Total_, 1, 1, "B");
	ElecMTWHTNJets_METup_->Divide(ElecMTWHTNJets_Pass_METup_, ElecMTWHTNJets_Total_METup_, 1, 1, "B");
	ElecMTWHTNJets_METdown_->Divide(ElecMTWHTNJets_Pass_METdown_, ElecMTWHTNJets_Total_METdown_, 1, 1, "B");

	MuMTWHTMHT_NJets2_->Divide(MuMTWHTMHT_NJets2_Pass_, MuMTWHTMHT_NJets2_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets2_METup_->Divide(MuMTWHTMHT_NJets2_Pass_METup_, MuMTWHTMHT_NJets2_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets2_METdown_->Divide(MuMTWHTMHT_NJets2_Pass_METdown_, MuMTWHTMHT_NJets2_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets3_->Divide(MuMTWHTMHT_NJets3_Pass_, MuMTWHTMHT_NJets3_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets3_METup_->Divide(MuMTWHTMHT_NJets3_Pass_METup_, MuMTWHTMHT_NJets3_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets3_METdown_->Divide(MuMTWHTMHT_NJets3_Pass_METdown_, MuMTWHTMHT_NJets3_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets4_->Divide(MuMTWHTMHT_NJets4_Pass_, MuMTWHTMHT_NJets4_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets4_METup_->Divide(MuMTWHTMHT_NJets4_Pass_METup_, MuMTWHTMHT_NJets4_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets4_METdown_->Divide(MuMTWHTMHT_NJets4_Pass_METdown_, MuMTWHTMHT_NJets4_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets5_->Divide(MuMTWHTMHT_NJets5_Pass_, MuMTWHTMHT_NJets5_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets5_METup_->Divide(MuMTWHTMHT_NJets5_Pass_METup_, MuMTWHTMHT_NJets5_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets5_METdown_->Divide(MuMTWHTMHT_NJets5_Pass_METdown_, MuMTWHTMHT_NJets5_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets6_->Divide(MuMTWHTMHT_NJets6_Pass_, MuMTWHTMHT_NJets6_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets6_METup_->Divide(MuMTWHTMHT_NJets6_Pass_METup_, MuMTWHTMHT_NJets6_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets6_METdown_->Divide(MuMTWHTMHT_NJets6_Pass_METdown_, MuMTWHTMHT_NJets6_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets78_->Divide(MuMTWHTMHT_NJets78_Pass_, MuMTWHTMHT_NJets78_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets78_METup_->Divide(MuMTWHTMHT_NJets78_Pass_METup_, MuMTWHTMHT_NJets78_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets78_METdown_->Divide(MuMTWHTMHT_NJets78_Pass_METdown_, MuMTWHTMHT_NJets78_Total_METdown_, 1, 1, "B");
	MuMTWHTMHT_NJets9Inf_->Divide(MuMTWHTMHT_NJets9Inf_Pass_, MuMTWHTMHT_NJets9Inf_Total_, 1, 1, "B");
	MuMTWHTMHT_NJets9Inf_METup_->Divide(MuMTWHTMHT_NJets9Inf_Pass_METup_, MuMTWHTMHT_NJets9Inf_Total_METup_, 1, 1, "B");
	MuMTWHTMHT_NJets9Inf_METdown_->Divide(MuMTWHTMHT_NJets9Inf_Pass_METdown_, MuMTWHTMHT_NJets9Inf_Total_METdown_, 1, 1, "B");

	ElecMTWHTMHT_NJets2_->Divide(ElecMTWHTMHT_NJets2_Pass_, ElecMTWHTMHT_NJets2_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets2_METup_->Divide(ElecMTWHTMHT_NJets2_Pass_METup_, ElecMTWHTMHT_NJets2_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets2_METdown_->Divide(ElecMTWHTMHT_NJets2_Pass_METdown_, ElecMTWHTMHT_NJets2_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets3_->Divide(ElecMTWHTMHT_NJets3_Pass_, ElecMTWHTMHT_NJets3_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets3_METup_->Divide(ElecMTWHTMHT_NJets3_Pass_METup_, ElecMTWHTMHT_NJets3_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets3_METdown_->Divide(ElecMTWHTMHT_NJets3_Pass_METdown_, ElecMTWHTMHT_NJets3_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets4_->Divide(ElecMTWHTMHT_NJets4_Pass_, ElecMTWHTMHT_NJets4_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets4_METup_->Divide(ElecMTWHTMHT_NJets4_Pass_METup_, ElecMTWHTMHT_NJets4_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets4_METdown_->Divide(ElecMTWHTMHT_NJets4_Pass_METdown_, ElecMTWHTMHT_NJets4_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets5_->Divide(ElecMTWHTMHT_NJets5_Pass_, ElecMTWHTMHT_NJets5_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets5_METup_->Divide(ElecMTWHTMHT_NJets5_Pass_METup_, ElecMTWHTMHT_NJets5_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets5_METdown_->Divide(ElecMTWHTMHT_NJets5_Pass_METdown_, ElecMTWHTMHT_NJets5_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets6_->Divide(ElecMTWHTMHT_NJets6_Pass_, ElecMTWHTMHT_NJets6_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets6_METup_->Divide(ElecMTWHTMHT_NJets6_Pass_METup_, ElecMTWHTMHT_NJets6_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets6_METdown_->Divide(ElecMTWHTMHT_NJets6_Pass_METdown_, ElecMTWHTMHT_NJets6_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets78_->Divide(ElecMTWHTMHT_NJets78_Pass_, ElecMTWHTMHT_NJets78_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets78_METup_->Divide(ElecMTWHTMHT_NJets78_Pass_METup_, ElecMTWHTMHT_NJets78_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets78_METdown_->Divide(ElecMTWHTMHT_NJets78_Pass_METdown_, ElecMTWHTMHT_NJets78_Total_METdown_, 1, 1, "B");
	ElecMTWHTMHT_NJets9Inf_->Divide(ElecMTWHTMHT_NJets9Inf_Pass_, ElecMTWHTMHT_NJets9Inf_Total_, 1, 1, "B");
	ElecMTWHTMHT_NJets9Inf_METup_->Divide(ElecMTWHTMHT_NJets9Inf_Pass_METup_, ElecMTWHTMHT_NJets9Inf_Total_METup_, 1, 1, "B");
	ElecMTWHTMHT_NJets9Inf_METdown_->Divide(ElecMTWHTMHT_NJets9Inf_Pass_METdown_, ElecMTWHTMHT_NJets9Inf_Total_METdown_, 1, 1, "B");

	
    if(showRatio)
    for(int xb = 1; xb <= MuMTWHTNJets_->GetNbinsX(); xb++){
		for(int yb = 1; yb <= MuMTWHTNJets_->GetNbinsY(); yb++){
			MuMTWHTNJets_METup_->SetBinContent(xb, yb, std::abs(MuMTWHTNJets_METup_->GetBinContent(xb, yb)-MuMTWHTNJets_->GetBinContent(xb, yb))/(1.-MuMTWHTNJets_->GetBinContent(xb, yb)));
			MuMTWHTNJets_METdown_->SetBinContent(xb, yb, std::abs(MuMTWHTNJets_METdown_->GetBinContent(xb, yb)-MuMTWHTNJets_->GetBinContent(xb, yb))/(1.-MuMTWHTNJets_->GetBinContent(xb, yb)));

			MuMTWHTNJets_METup_->SetBinError(xb, yb, 0);
			MuMTWHTNJets_METdown_->SetBinError(xb, yb, 0);

			ElecMTWHTNJets_METup_->SetBinContent(xb, yb, std::abs(ElecMTWHTNJets_METup_->GetBinContent(xb, yb)-ElecMTWHTNJets_->GetBinContent(xb, yb))/(1.-ElecMTWHTNJets_->GetBinContent(xb, yb)));
			ElecMTWHTNJets_METdown_->SetBinContent(xb, yb, std::abs(ElecMTWHTNJets_METdown_->GetBinContent(xb, yb)-ElecMTWHTNJets_->GetBinContent(xb, yb))/(1.-ElecMTWHTNJets_->GetBinContent(xb, yb)));

			ElecMTWHTNJets_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTNJets_METdown_->SetBinError(xb, yb, 0);
		}    	
    }

    if(showRatio)
    for(int xb = 1; xb <= 3; xb++){
		for(int yb = 1; yb <= 3; yb++){
			if(xb == 1 && yb == 3) continue;

			MuMTWHTMHT_NJets2_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets2_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets2_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets3_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets3_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets3_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets4_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets4_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets4_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets5_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets5_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets5_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets6_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets6_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets6_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets78_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets78_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets78_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets9Inf_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets9Inf_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets9Inf_METup_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets7Inf_METup_->SetBinContent(xb, yb, MuMTWHTMHT_NJets7Inf_METup_->GetBinError(xb, yb)/MuMTWHTMHT_NJets7Inf_METup_->GetBinContent(xb, yb));

			ElecMTWHTMHT_NJets2_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets2_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets2_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets3_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets3_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets3_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets4_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets4_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets4_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets5_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets5_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets5_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets6_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets6_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets6_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets78_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets78_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets78_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets9Inf_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets9Inf_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets9Inf_METup_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets7Inf_METup_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets7Inf_METup_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets7Inf_METup_->GetBinContent(xb, yb));

			MuMTWHTMHT_NJets2_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets3_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets4_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets5_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets6_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets78_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets9Inf_METup_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets7Inf_METup_->SetBinError(xb, yb, 0);

			ElecMTWHTMHT_NJets2_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets3_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets4_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets5_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets6_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets78_METup_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets9Inf_METup_->SetBinError(xb, yb, 0);			
			ElecMTWHTMHT_NJets7Inf_METup_->SetBinError(xb, yb, 0);

			MuMTWHTMHT_NJets2_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets2_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets2_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets3_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets3_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets3_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets4_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets4_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets4_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets5_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets5_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets5_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets6_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets6_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets6_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets78_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets78_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets78_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets9Inf_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets9Inf_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets9Inf_METdown_->GetBinContent(xb, yb));
			MuMTWHTMHT_NJets7Inf_METdown_->SetBinContent(xb, yb, MuMTWHTMHT_NJets7Inf_METdown_->GetBinError(xb, yb)/MuMTWHTMHT_NJets7Inf_METdown_->GetBinContent(xb, yb));

			ElecMTWHTMHT_NJets2_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets2_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets2_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets3_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets3_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets3_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets4_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets4_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets4_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets5_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets5_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets5_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets6_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets6_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets6_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets78_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets78_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets78_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets9Inf_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets9Inf_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets9Inf_METdown_->GetBinContent(xb, yb));
			ElecMTWHTMHT_NJets7Inf_METdown_->SetBinContent(xb, yb, ElecMTWHTMHT_NJets7Inf_METdown_->GetBinError(xb, yb)/ElecMTWHTMHT_NJets7Inf_METdown_->GetBinContent(xb, yb));

			MuMTWHTMHT_NJets2_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets3_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets4_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets5_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets6_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets78_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets9Inf_METdown_->SetBinError(xb, yb, 0);
			MuMTWHTMHT_NJets7Inf_METdown_->SetBinError(xb, yb, 0);

			ElecMTWHTMHT_NJets2_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets3_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets4_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets5_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets6_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets78_METdown_->SetBinError(xb, yb, 0);
			ElecMTWHTMHT_NJets9Inf_METdown_->SetBinError(xb, yb, 0);			
			ElecMTWHTMHT_NJets7Inf_METdown_->SetBinError(xb, yb, 0);			
		}    	
    }


    TFile *outPutFile = new TFile("MTWUncertainty/MTWuncertainty.root","RECREATE"); 
	outPutFile->cd();

    saveEff(MuMTWHTNJets_, outPutFile);
    saveEff(MuMTWHTNJets_METup_, outPutFile);
    saveEff(MuMTWHTNJets_METdown_, outPutFile);

    saveEff(ElecMTWHTNJets_, outPutFile);
    saveEff(ElecMTWHTNJets_METup_, outPutFile);
    saveEff(ElecMTWHTNJets_METdown_, outPutFile);

    saveEff(MuMTWHTMHT_NJets2_, outPutFile);
    saveEff(MuMTWHTMHT_NJets2_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets2_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets3_, outPutFile);
    saveEff(MuMTWHTMHT_NJets3_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets3_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets4_, outPutFile);
    saveEff(MuMTWHTMHT_NJets4_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets4_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets5_, outPutFile);
    saveEff(MuMTWHTMHT_NJets5_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets5_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets6_, outPutFile);
    saveEff(MuMTWHTMHT_NJets6_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets6_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets78_, outPutFile);
    saveEff(MuMTWHTMHT_NJets78_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets78_METdown_, outPutFile);
    saveEff(MuMTWHTMHT_NJets9Inf_, outPutFile);
    saveEff(MuMTWHTMHT_NJets9Inf_METup_, outPutFile);
    saveEff(MuMTWHTMHT_NJets9Inf_METdown_, outPutFile);

    saveEff(ElecMTWHTMHT_NJets2_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets2_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets2_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets3_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets3_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets3_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets4_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets4_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets4_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets5_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets5_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets5_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets6_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets6_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets6_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets78_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets78_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets78_METdown_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets9Inf_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets9Inf_METup_, outPutFile);
    saveEff(ElecMTWHTMHT_NJets9Inf_METdown_, outPutFile);
}