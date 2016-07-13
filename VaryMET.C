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
	h_ratio->GetYaxis()->SetTitle("NJets");

  	TString name(h_ratio->GetName());

  	gROOT->SetBatch(true);
  	TCanvas *c1 = new TCanvas(name,name,1);
	c1->cd();
	c1->SetLogx();
	//c1->SetLogy();
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
	const int twoDNJets_=7;
	double TwoDNJets_[twoDNJets_] = {2.5,3.5,4.5,5.5,6.5,8.5,21.5};
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

	Long64_t nentries = LostLeptonExpectation->GetEntries();
	for (Long64_t i=0; i<nentries;i++) {
    	LostLeptonExpectation->GetEntry(i);
    	if(HT<300 || MHT<250 || NJets<2.5) continue;

    	if(Weight<0) Weight*=-1;

	    if(muIso==2){
	    	if(MTW < 100){
	    		MuMTWHTNJets_Pass_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_->Fill(HT, NJets, Weight);
	    	}else{
	    		MuMTWHTNJets_Total_->Fill(HT, NJets, Weight);
	    	}
	    	if(MTW_METup < 100){
	    		MuMTWHTNJets_Pass_METup_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);
	    	}else{
	    		MuMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);
	    	}
	    	if(MTW_METdown < 100){
	    		MuMTWHTNJets_Pass_METdown_->Fill(HT, NJets, Weight);
	    		MuMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);
	    	}else{
	    		MuMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);
	    	}
	    }

	    if(elecIso==2){
	    	if(MTW < 100){
	    		ElecMTWHTNJets_Pass_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_->Fill(HT, NJets, Weight);
	    	}else{
	    		ElecMTWHTNJets_Total_->Fill(HT, NJets, Weight);
	    	}
	    	if(MTW_METup < 100){
	    		ElecMTWHTNJets_Pass_METup_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);
	    	}else{
	    		ElecMTWHTNJets_Total_METup_->Fill(HT, NJets, Weight);
	    	}
	    	if(MTW_METdown < 100){
	    		ElecMTWHTNJets_Pass_METdown_->Fill(HT, NJets, Weight);
	    		ElecMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);
	    	}else{
	    		ElecMTWHTNJets_Total_METdown_->Fill(HT, NJets, Weight);
	    	}
	    }
	}
	      

	MuMTWHTNJets_->Divide(MuMTWHTNJets_Pass_, MuMTWHTNJets_Total_, 1, 1, "B");
	MuMTWHTNJets_METup_->Divide(MuMTWHTNJets_Pass_METup_, MuMTWHTNJets_Total_METup_, 1, 1, "B");
	MuMTWHTNJets_METdown_->Divide(MuMTWHTNJets_Pass_METdown_, MuMTWHTNJets_Total_METdown_, 1, 1, "B");

	ElecMTWHTNJets_->Divide(ElecMTWHTNJets_Pass_, ElecMTWHTNJets_Total_, 1, 1, "B");
	ElecMTWHTNJets_METup_->Divide(ElecMTWHTNJets_Pass_METup_, ElecMTWHTNJets_Total_METup_, 1, 1, "B");
	ElecMTWHTNJets_METdown_->Divide(ElecMTWHTNJets_Pass_METdown_, ElecMTWHTNJets_Total_METdown_, 1, 1, "B");

	
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


    TFile *outPutFile = new TFile("MTWUncertainty/MTWuncertainty.root","RECREATE"); 
	outPutFile->cd();

    saveEff(MuMTWHTNJets_, outPutFile);
    saveEff(MuMTWHTNJets_METup_, outPutFile);
    saveEff(MuMTWHTNJets_METdown_, outPutFile);

    saveEff(ElecMTWHTNJets_, outPutFile);
    saveEff(ElecMTWHTNJets_METup_, outPutFile);
    saveEff(ElecMTWHTNJets_METdown_, outPutFile);
}