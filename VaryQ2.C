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

	h_ratio->SetMarkerSize(2.0);
	h_ratio->GetZaxis()->SetRangeUser(0., 1.5);

	h_ratio->GetXaxis()->SetTitle("HT");
	h_ratio->GetYaxis()->SetTitle("MHT");

  	TString name(h_ratio->GetName());

  	gROOT->SetBatch(true);
  	TCanvas *c1 = new TCanvas(name,name,1);
	c1->cd();
	c1->SetLogx();
	c1->SetLogy();
	gStyle->SetOptStat(0);
	gStyle->SetPaintTextFormat("5.4f");
  	gStyle->SetStatW(0.1);
  	gStyle->SetStatH(0.1);
  	gStyle->SetStatY(202);
  	gStyle->SetTitleYOffset(1.3);

  	gStyle->SetPalette(56);
  	gStyle->SetMarkerSize(2.0);
  	if(h_ratio->GetBinError(2,2) > 0) h_ratio->Draw("ColZ,Text,E");
  	else h_ratio->Draw("ColZ,Text");
  	c1->SaveAs(TString("AcceptanceUncertainty/")+name+TString(".pdf"));
  	delete c1;
  	gROOT->SetBatch(false);

  	if(outFile) h_ratio->Write();

  	return h_ratio;
}

TH1D* saveEff(TH1D* h_ratio, TFile *outFile){
	if(outFile) outFile->cd();

	h_ratio->SetMarkerSize(2.0);
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
  	gStyle->SetMarkerSize(2.0);
  	h_ratio->Draw("Text,E");
  	c1->SaveAs(TString("AcceptanceUncertainty/")+name+TString(".pdf"));
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

double calcUnc(TH1D* hist, bool lower){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(1, nBinGes);
    
    if(lower){
	    nBinTest = 1;
	    while(hist->Integral(1, nBinTest) / total < 0.16 && nBinTest < nBinGes){
	        nBinTest++;
	    }
	}else{
	    nBinTest = hist->GetNbinsX();
	    while(hist->Integral(nBinTest, nBinGes) / total < 0.16 && nBinTest > 0){
	        nBinTest--;
	    }
	}

	return std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());
}

double calcEnv(TH1D* hist, bool lower){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(1, nBinGes);
    
    if(lower){
	    nBinTest = 1;
	    while(hist->Integral(1, nBinTest) / total < 0.01 && nBinTest < nBinGes){
	        nBinTest++;
	    }
	}else{
	    nBinTest = hist->GetNbinsX();
	    while(hist->Integral(nBinTest, nBinGes) / total < 0.01 && nBinTest > 0){
	        nBinTest--;
	    }
	}

	return std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());
}

double calcUncMax(TH1D* hist){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(1, nBinGes);
    
    nBinTest = 1;
    while(hist->Integral(1, nBinTest) / total < 0.16 && nBinTest < nBinGes){
        nBinTest++;
    }
    double lower = std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());

    nBinTest = hist->GetNbinsX();
    while(hist->Integral(nBinTest, nBinGes) / total < 0.16 && nBinTest > 0){
        nBinTest--;
    }
    double higher = std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());

	return std::max(lower, higher);
}

double calcEnvMax(TH1D* hist){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(0, nBinGes+1);
    
    nBinTest = 1;
    while(hist->Integral(1, nBinTest) / total < 0.01 && nBinTest < nBinGes){
        nBinTest++;
    }
    double lower = std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());

    nBinTest = hist->GetNbinsX();
    while(hist->Integral(nBinTest, nBinGes) / total < 0.01 && nBinTest > 0){
        nBinTest--;
    }
    double higher = std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());

	return std::max(lower, higher);
}


void VaryQ2(){
	TString outName("AcceptanceUncertainty/Q2uncertainty_down.root");
	// lower/upper uncertainty
	bool lower = true;

	bool showRatio = true;

	UShort_t        Bin;
	UShort_t        BinQCD;
	Double_t        Weight;
	Double_t        HT;
	Double_t        MHT;
	Int_t           NJets;
	Int_t           BTags;

	UShort_t		muAcc;
	UShort_t		elecAcc;

	std::vector<double>  *ScaleWeights=0;

	gROOT->Reset();
	TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject("Expectation.root");
	//TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/dust/cms/user/kurzsimo/LostLepton/Expectation_woExo.root");
	if (!fExp) {
    	//fExp = new TFile("/nfs/dust/cms/user/kurzsimo/LostLepton/Expectation_woExo.root");
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
	LostLeptonExpectation->SetBranchStatus("muAcc",1);
	LostLeptonExpectation->SetBranchStatus("elecAcc",1);
	LostLeptonExpectation->SetBranchStatus("ScaleWeights",1);

	LostLeptonExpectation->SetBranchAddress("HT",&HT);
	LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
	LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
	LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
	LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
	LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
	LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
	LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
	LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
	LostLeptonExpectation->SetBranchAddress("ScaleWeights",&ScaleWeights);

	TH1::SetDefaultSumw2();

	const int threeDHT_=4;
	double ThreeDHT_[threeDHT_] = {300,500,1000,10000};
	const int threeDMHT_=4;
	double ThreeDMHT_[threeDMHT_] = {250,350,500,10000};
	const int twoDNJets_=8;
	double TwoDNJets_[twoDNJets_] = {1.5,2.5,3.5,4.5,5.5,6.5,8.5,21.5};
	TH2D* MuAccControl_NJets2_pass = new TH2D("MuAccControl_NJets2_pass","MuAccControl_NJets2_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets2_fail = new TH2D("MuAccControl_NJets2_fail","MuAccControl_NJets2_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets3_pass = new TH2D("MuAccControl_NJets3_pass","MuAccControl_NJets3_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets3_fail = new TH2D("MuAccControl_NJets3_fail","MuAccControl_NJets3_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets4_pass = new TH2D("MuAccControl_NJets4_pass","MuAccControl_NJets4_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets4_fail = new TH2D("MuAccControl_NJets4_fail","MuAccControl_NJets4_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets5_pass = new TH2D("MuAccControl_NJets5_pass","MuAccControl_NJets5_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets5_fail = new TH2D("MuAccControl_NJets5_fail","MuAccControl_NJets5_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets6_pass = new TH2D("MuAccControl_NJets6_pass","MuAccControl_NJets6_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets6_fail = new TH2D("MuAccControl_NJets6_fail","MuAccControl_NJets6_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets78_pass = new TH2D("MuAccControl_NJets78_pass"," MuAccControl_NJets78_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets78_fail = new TH2D("MuAccControl_NJets78_fail"," MuAccControl_NJets78_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets9Inf_pass = new TH2D("MuAccControl_NJets9Inf_pass"," MuAccControl_NJets9Inf_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets9Inf_fail = new TH2D("MuAccControl_NJets9Inf_fail"," MuAccControl_NJets9Inf_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets7Inf_pass = new TH2D("MuAccControl_NJets7Inf_pass"," MuAccControl_NJets7Inf_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccControl_NJets7Inf_fail = new TH2D("MuAccControl_NJets7Inf_fail"," MuAccControl_NJets7Inf_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH2D* MuAccUnc_NJets2 = new TH2D("MuAccQ2Unc_NJets2","MuAccQ2Unc_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets3 = new TH2D("MuAccQ2Unc_NJets3","MuAccQ2Unc_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets4 = new TH2D("MuAccQ2Unc_NJets4","MuAccQ2Unc_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets5 = new TH2D("MuAccQ2Unc_NJets5","MuAccQ2Unc_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets6 = new TH2D("MuAccQ2Unc_NJets6","MuAccQ2Unc_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets78 = new TH2D("MuAccQ2Unc_NJets78","MuAccQ2Unc_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets9Inf = new TH2D("MuAccQ2Unc_NJets9Inf","MuAccQ2Unc_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* MuAccUnc_NJets7Inf = new TH2D("MuAccQ2Unc_NJets7Inf","MuAccQ2Unc_NJets7Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH2D* ElecAccControl_NJets2_pass = new TH2D("ElecAccControl_NJets2_pass","ElecAccControl_NJets2_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets2_fail = new TH2D("ElecAccControl_NJets2_fail","ElecAccControl_NJets2_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets3_pass = new TH2D("ElecAccControl_NJets3_pass","ElecAccControl_NJets3_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets3_fail = new TH2D("ElecAccControl_NJets3_fail","ElecAccControl_NJets3_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets4_pass = new TH2D("ElecAccControl_NJets4_pass","ElecAccControl_NJets4_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets4_fail = new TH2D("ElecAccControl_NJets4_fail","ElecAccControl_NJets4_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets5_pass = new TH2D("ElecAccControl_NJets5_pass","ElecAccControl_NJets5_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets5_fail = new TH2D("ElecAccControl_NJets5_fail","ElecAccControl_NJets5_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets6_pass = new TH2D("ElecAccControl_NJets6_pass","ElecAccControl_NJets6_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets6_fail = new TH2D("ElecAccControl_NJets6_fail","ElecAccControl_NJets6_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets78_pass = new TH2D("ElecAccControl_NJets78_pass"," ElecAccControl_NJets78_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets78_fail = new TH2D("ElecAccControl_NJets78_fail"," ElecAccControl_NJets78_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets9Inf_pass = new TH2D("ElecAccControl_NJets9Inf_pass"," ElecAccControl_NJets9Inf_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets9Inf_fail = new TH2D("ElecAccControl_NJets9Inf_fail"," ElecAccControl_NJets9Inf_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets7Inf_pass = new TH2D("ElecAccControl_NJets7Inf_pass"," ElecAccControl_NJets7Inf_pass",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccControl_NJets7Inf_fail = new TH2D("ElecAccControl_NJets7Inf_fail"," ElecAccControl_NJets7Inf_fail",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH2D* ElecAccUnc_NJets2 = new TH2D("ElecAccQ2Unc_NJets2","ElecAccQ2Unc_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets3 = new TH2D("ElecAccQ2Unc_NJets3","ElecAccQ2Unc_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets4 = new TH2D("ElecAccQ2Unc_NJets4","ElecAccQ2Unc_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets5 = new TH2D("ElecAccQ2Unc_NJets5","ElecAccQ2Unc_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets6 = new TH2D("ElecAccQ2Unc_NJets6","ElecAccQ2Unc_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets78 = new TH2D("ElecAccQ2Unc_NJets78","ElecAccQ2Unc_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets9Inf = new TH2D("ElecAccQ2Unc_NJets9Inf","ElecAccQ2Unc_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_NJets7Inf = new TH2D("ElecAccQ2Unc_NJets7Inf","ElecAccQ2Unc_NJets7Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH2D* MuAccUnc_Avg = new TH2D("MuAccQ2Unc_Avg","MuAccQ2Unc_Avg",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
	TH2D* ElecAccUnc_Avg = new TH2D("ElecAccQ2Unc_Avg","ElecAccQ2Unc_Avg",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

	TH1D* MuAccUnc_NJets = new TH1D("MuAccQ2Unc_NJets","MuAccQ2Unc_NJets",twoDNJets_-1,TwoDNJets_);
	TH1D* ElecAccUnc_NJets = new TH1D("ElecAccQ2Unc_NJets","ElecAccQ2Unc_NJets",twoDNJets_-1,TwoDNJets_);

	Double_t mu_pass_central = 0;
	Double_t mu_fail_central = 0;

	std::vector<double> mu_pass(9, 0);
	std::vector<double> mu_fail(9, 0);

	std::vector<TH2D*> h_mu_pass2(9, 0);
	std::vector<TH2D*> h_mu_fail2(9, 0);
	std::vector<TH2D*> h_mu_pass3(9, 0);
	std::vector<TH2D*> h_mu_fail3(9, 0);
	std::vector<TH2D*> h_mu_pass4(9, 0);
	std::vector<TH2D*> h_mu_fail4(9, 0);
	std::vector<TH2D*> h_mu_pass5(9, 0);
	std::vector<TH2D*> h_mu_fail5(9, 0);
	std::vector<TH2D*> h_mu_pass6(9, 0);
	std::vector<TH2D*> h_mu_fail6(9, 0);
	std::vector<TH2D*> h_mu_pass78(9, 0);
	std::vector<TH2D*> h_mu_fail78(9, 0);
	std::vector<TH2D*> h_mu_pass9Inf(9, 0);
	std::vector<TH2D*> h_mu_fail9Inf(9, 0);
	std::vector<TH2D*> h_mu_pass7Inf(9, 0);
	std::vector<TH2D*> h_mu_fail7Inf(9, 0);

	Double_t elec_pass_central = 0;
	Double_t elec_fail_central = 0;

	std::vector<double> elec_pass(9, 0);
	std::vector<double> elec_fail(9, 0);

	std::vector<TH2D*> h_elec_pass2(9, 0);
	std::vector<TH2D*> h_elec_fail2(9, 0);
	std::vector<TH2D*> h_elec_pass3(9, 0);
	std::vector<TH2D*> h_elec_fail3(9, 0);
	std::vector<TH2D*> h_elec_pass4(9, 0);
	std::vector<TH2D*> h_elec_fail4(9, 0);
	std::vector<TH2D*> h_elec_pass5(9, 0);
	std::vector<TH2D*> h_elec_fail5(9, 0);
	std::vector<TH2D*> h_elec_pass6(9, 0);
	std::vector<TH2D*> h_elec_fail6(9, 0);
	std::vector<TH2D*> h_elec_pass78(9, 0);
	std::vector<TH2D*> h_elec_fail78(9, 0);
	std::vector<TH2D*> h_elec_pass9Inf(9, 0);
	std::vector<TH2D*> h_elec_fail9Inf(9, 0);
	std::vector<TH2D*> h_elec_pass7Inf(9, 0);
	std::vector<TH2D*> h_elec_fail7Inf(9, 0);

	std::vector<TH2D*> h_mu_passAvg(9, 0);
	std::vector<TH2D*> h_mu_failAvg(9, 0);
	std::vector<TH2D*> h_elec_passAvg(9, 0);
	std::vector<TH2D*> h_elec_failAvg(9, 0);

	std::vector<TH1D*> h_mu_passNJets(9, 0);
	std::vector<TH1D*> h_mu_failNJets(9, 0);
	std::vector<TH1D*> h_elec_passNJets(9, 0);
	std::vector<TH1D*> h_elec_failNJets(9, 0);


	for(unsigned i = 0; i<h_mu_pass4.size(); ++i){
		h_mu_pass2.at(i) = new TH2D(TString("mu_pass2_")+TString(std::to_string(i)),TString("mu_pass2_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail2.at(i) = new TH2D(TString("mu_fail2_")+TString(std::to_string(i)),TString("mu_fail2_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass3.at(i) = new TH2D(TString("mu_pass3_")+TString(std::to_string(i)),TString("mu_pass3_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail3.at(i) = new TH2D(TString("mu_fail3_")+TString(std::to_string(i)),TString("mu_fail3_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass4.at(i) = new TH2D(TString("mu_pass4_")+TString(std::to_string(i)),TString("mu_pass4_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail4.at(i) = new TH2D(TString("mu_fail4_")+TString(std::to_string(i)),TString("mu_fail4_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass5.at(i) = new TH2D(TString("mu_pass5_")+TString(std::to_string(i)),TString("mu_pass5_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail5.at(i) = new TH2D(TString("mu_fail5_")+TString(std::to_string(i)),TString("mu_fail5_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass6.at(i) = new TH2D(TString("mu_pass6_")+TString(std::to_string(i)),TString("mu_pass6_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail6.at(i) = new TH2D(TString("mu_fail6_")+TString(std::to_string(i)),TString("mu_fail6_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass78.at(i) = new TH2D(TString("mu_pass78_")+TString(std::to_string(i)),TString("mu_pass78_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail78.at(i) = new TH2D(TString("mu_fail78_")+TString(std::to_string(i)),TString("mu_fail78_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass9Inf.at(i) = new TH2D(TString("mu_pass9Inf_")+TString(std::to_string(i)),TString("mu_pass9Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail9Inf.at(i) = new TH2D(TString("mu_fail9Inf_")+TString(std::to_string(i)),TString("mu_fail9Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_pass7Inf.at(i) = new TH2D(TString("mu_pass7Inf_")+TString(std::to_string(i)),TString("mu_pass7Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_fail7Inf.at(i) = new TH2D(TString("mu_fail7Inf_")+TString(std::to_string(i)),TString("mu_fail7Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

		h_elec_pass2.at(i) = new TH2D(TString("elec_pass2_")+TString(std::to_string(i)),TString("elec_pass2_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail2.at(i) = new TH2D(TString("elec_fail2_")+TString(std::to_string(i)),TString("elec_fail2_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass3.at(i) = new TH2D(TString("elec_pass3_")+TString(std::to_string(i)),TString("elec_pass3_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail3.at(i) = new TH2D(TString("elec_fail3_")+TString(std::to_string(i)),TString("elec_fail3_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass4.at(i) = new TH2D(TString("elec_pass4_")+TString(std::to_string(i)),TString("elec_pass4_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail4.at(i) = new TH2D(TString("elec_fail4_")+TString(std::to_string(i)),TString("elec_fail4_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass5.at(i) = new TH2D(TString("elec_pass5_")+TString(std::to_string(i)),TString("elec_pass5_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail5.at(i) = new TH2D(TString("elec_fail5_")+TString(std::to_string(i)),TString("elec_fail5_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass6.at(i) = new TH2D(TString("elec_pass6_")+TString(std::to_string(i)),TString("elec_pass6_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail6.at(i) = new TH2D(TString("elec_fail6_")+TString(std::to_string(i)),TString("elec_fail6_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass78.at(i) = new TH2D(TString("elec_pass78_")+TString(std::to_string(i)),TString("elec_pass78_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail78.at(i) = new TH2D(TString("elec_fail78_")+TString(std::to_string(i)),TString("elec_fail78_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_pass9Inf.at(i) = new TH2D(TString("elec_pass9Inf_")+TString(std::to_string(i)),TString("elec_pass9Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail9Inf.at(i) = new TH2D(TString("elec_fail9Inf_")+TString(std::to_string(i)),TString("elec_fail9Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
    	h_elec_pass7Inf.at(i) = new TH2D(TString("elec_pass7Inf_")+TString(std::to_string(i)),TString("elec_pass7Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_fail7Inf.at(i) = new TH2D(TString("elec_fail7Inf_")+TString(std::to_string(i)),TString("elec_fail7Inf_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
    
		h_mu_passAvg.at(i) = new TH2D(TString("mu_passAvg_")+TString(std::to_string(i)),TString("mu_passAvg_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_mu_failAvg.at(i) = new TH2D(TString("mu_failAvg_")+TString(std::to_string(i)),TString("mu_failAvg_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_passAvg.at(i) = new TH2D(TString("elec_passAvg_")+TString(std::to_string(i)),TString("elec_passAvg_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
		h_elec_failAvg.at(i) = new TH2D(TString("elec_failAvg_")+TString(std::to_string(i)),TString("elec_failAvg_")+TString(std::to_string(i)),threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

		h_mu_passNJets.at(i) = new TH1D(TString("mu_passNJets_")+TString(std::to_string(i)),TString("mu_passNJets_")+TString(std::to_string(i)),twoDNJets_-1,TwoDNJets_);
		h_mu_failNJets.at(i) = new TH1D(TString("mu_failNJets_")+TString(std::to_string(i)),TString("mu_failNJets_")+TString(std::to_string(i)),twoDNJets_-1,TwoDNJets_);
		h_elec_passNJets.at(i) = new TH1D(TString("elec_passNJets_")+TString(std::to_string(i)),TString("elec_passNJets_")+TString(std::to_string(i)),twoDNJets_-1,TwoDNJets_);
		h_elec_failNJets.at(i) = new TH1D(TString("elec_failNJets_")+TString(std::to_string(i)),TString("elec_failNJets_")+TString(std::to_string(i)),twoDNJets_-1,TwoDNJets_);		
    }

    Long64_t allEvts = 0;
    Long64_t nanEvts = 0;
    Long64_t hugeEvts = 0;
	Long64_t nentries = LostLeptonExpectation->GetEntries();
	for (Long64_t i=0; i<nentries;i++) {
    	LostLeptonExpectation->GetEntry(i);
    	if(HT<300 || MHT<250 || NJets<1.5) continue;

    	if(Weight<0) Weight*=-1;

    	allEvts++;

    	bool skipEvent = false;
    	for(unsigned i = 1; i<ScaleWeights->size(); ++i){
    		if(std::isnan(ScaleWeights->at(i))){
    			nanEvts++;
    			skipEvent = true;
    			break;
    		}
    		else if(std::abs(ScaleWeights->at(i)) > 100){
    			hugeEvts++;
    			skipEvent = true;
    			break;
    		}
    	}
    	if(skipEvent) continue;

    	if(muAcc==2){
    		mu_pass_central += Weight;
	    	switch(NJets){
	    		case 2:
	        		MuAccControl_NJets2_pass->Fill(HT,MHT,Weight);
		            break;
	        	case 3:
	        		MuAccControl_NJets3_pass->Fill(HT,MHT,Weight);
		            break;
		        case 4:
		        	MuAccControl_NJets4_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 5:
		        	MuAccControl_NJets5_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 6:
		        	MuAccControl_NJets6_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 7:
		        case 8:
		        	MuAccControl_NJets78_pass->Fill(HT,MHT,Weight);
		        	break;
		        default:
		        	MuAccControl_NJets9Inf_pass->Fill(HT,MHT,Weight);
		        	break;
		    }

	  		for(unsigned i = 1; i<ScaleWeights->size(); ++i){
    			mu_pass.at(i-1) += std::abs(ScaleWeights->at(i)*Weight);
    			h_mu_passAvg.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
    			h_mu_passNJets.at(i-1)->Fill(NJets, std::abs(ScaleWeights->at(i)*Weight));
			    switch(NJets){
			    	case 2:
		        		h_mu_pass2.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
		        	case 3:
		        		h_mu_pass3.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
			        case 4:
			        	h_mu_pass4.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 5:
			        	h_mu_pass5.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 6:
			        	h_mu_pass6.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 7:
			        case 8:
			        	h_mu_pass78.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_mu_pass7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        default:
			        	h_mu_pass9Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_mu_pass7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			    }
    		}
  		}else if(muAcc==0){
  			mu_fail_central += Weight;
	    	switch(NJets){
	    		case 2:
	        		MuAccControl_NJets2_fail->Fill(HT,MHT,Weight);
		            break;
	        	case 3:
	        		MuAccControl_NJets3_fail->Fill(HT,MHT,Weight);
		            break;
		        case 4:
		        	MuAccControl_NJets4_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 5:
		        	MuAccControl_NJets5_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 6:
		        	MuAccControl_NJets6_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 7:
		        case 8:
		        	MuAccControl_NJets78_fail->Fill(HT,MHT,Weight);
		        	break;
		        default:
		        	MuAccControl_NJets9Inf_fail->Fill(HT,MHT,Weight);
		        	break;
		    }

	  		for(unsigned i = 1; i<ScaleWeights->size(); ++i){
    			mu_fail.at(i-1) += std::abs(ScaleWeights->at(i)*Weight);
    			h_mu_failAvg.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
    			h_mu_failNJets.at(i-1)->Fill(NJets, std::abs(ScaleWeights->at(i)*Weight));
    			switch(NJets){
    				case 2:
		        		h_mu_fail2.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
		        	case 3:
		        		h_mu_fail3.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
			        case 4:
			        	h_mu_fail4.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 5:
			        	h_mu_fail5.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 6:
			        	h_mu_fail6.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 7:
			        case 8:
			        	h_mu_fail78.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_mu_fail7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        default:
			        	h_mu_fail9Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_mu_fail7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			    }
    		}
  		}

    	if(elecAcc==2){
    		elec_pass_central += Weight;
	    	switch(NJets){
	    		case 2:
	        		ElecAccControl_NJets2_pass->Fill(HT,MHT,Weight);
		            break;
	        	case 3:
	        		ElecAccControl_NJets3_pass->Fill(HT,MHT,Weight);
		            break;
		        case 4:
		        	ElecAccControl_NJets4_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 5:
		        	ElecAccControl_NJets5_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 6:
		        	ElecAccControl_NJets6_pass->Fill(HT,MHT,Weight);
		        	break;
		        case 7:
		        case 8:
		        	ElecAccControl_NJets78_pass->Fill(HT,MHT,Weight);
		        	break;
		        default:
		        	ElecAccControl_NJets9Inf_pass->Fill(HT,MHT,Weight);
		        	break;
		    }

	  		for(unsigned i = 1; i<ScaleWeights->size(); ++i){
    			elec_pass.at(i-1) += std::abs(ScaleWeights->at(i)*Weight);
    			h_elec_passAvg.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
    			h_elec_passNJets.at(i-1)->Fill(NJets, std::abs(ScaleWeights->at(i)*Weight));
			    switch(NJets){
			    	case 2:
		        		h_elec_pass2.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
		        	case 3:
		        		h_elec_pass3.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
			        case 4:
			        	h_elec_pass4.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 5:
			        	h_elec_pass5.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 6:
			        	h_elec_pass6.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 7:
			        case 8:
			        	h_elec_pass78.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_elec_pass7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        default:
			        	h_elec_pass9Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_elec_pass7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			    }
    		}
  		}else if(elecAcc==0){
  			elec_fail_central += Weight;
	    	switch(NJets){
	    		case 2:
	        		ElecAccControl_NJets2_fail->Fill(HT,MHT,Weight);
		            break;
	        	case 3:
	        		ElecAccControl_NJets3_fail->Fill(HT,MHT,Weight);
		            break;
		        case 4:
		        	ElecAccControl_NJets4_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 5:
		        	ElecAccControl_NJets5_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 6:
		        	ElecAccControl_NJets6_fail->Fill(HT,MHT,Weight);
		        	break;
		        case 7:
		        case 8:
		        	ElecAccControl_NJets78_fail->Fill(HT,MHT,Weight);
		        	break;
		        default:
		        	ElecAccControl_NJets9Inf_fail->Fill(HT,MHT,Weight);
		        	break;
		    }

	  		for(unsigned i = 1; i<ScaleWeights->size(); ++i){
    			elec_fail.at(i-1) += std::abs(ScaleWeights->at(i)*Weight);
    			h_elec_failAvg.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
    			h_elec_failNJets.at(i-1)->Fill(NJets, std::abs(ScaleWeights->at(i)*Weight));
    			switch(NJets){
    				case 2:
		        		h_elec_fail2.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
		        	case 3:
		        		h_elec_fail3.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			            break;
			        case 4:
			        	h_elec_fail4.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 5:
			        	h_elec_fail5.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 6:
			        	h_elec_fail6.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        case 7:
			        case 8:
			        	h_elec_fail78.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_elec_fail7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			        default:
			        	h_elec_fail9Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	h_elec_fail7Inf.at(i-1)->Fill(HT,MHT,std::abs(ScaleWeights->at(i)*Weight));
			        	break;
			    }
    		}
  		}
	}

	std::cout << "Invalid weights: " << nanEvts << std::endl;
	std::cout << "Huge weights: " << hugeEvts << std::endl;
	std::cout << "Total Evts: " << allEvts << std::endl;



	TH1D* h_mu_ratio = new TH1D("h_mu_ratio", "h_mu_ratio", 10000, 0., 1.);
	std::vector<TH1D*> h_mu_ratio2(8, 0);
	std::vector<TH1D*> h_mu_ratio3(8, 0);
	std::vector<TH1D*> h_mu_ratio4(8, 0);
	std::vector<TH1D*> h_mu_ratio5(8, 0);
	std::vector<TH1D*> h_mu_ratio6(8, 0);
	std::vector<TH1D*> h_mu_ratio78(8, 0);
	std::vector<TH1D*> h_mu_ratio9Inf(8, 0);
	std::vector<TH1D*> h_mu_ratio7Inf(8, 0);

	TH1D* h_elec_ratio = new TH1D("h_elec_ratio", "h_elec_ratio", 10000, 0., 1.);
	std::vector<TH1D*> h_elec_ratio2(8, 0);
	std::vector<TH1D*> h_elec_ratio3(8, 0);
	std::vector<TH1D*> h_elec_ratio4(8, 0);
	std::vector<TH1D*> h_elec_ratio5(8, 0);
	std::vector<TH1D*> h_elec_ratio6(8, 0);
	std::vector<TH1D*> h_elec_ratio78(8, 0);
	std::vector<TH1D*> h_elec_ratio9Inf(8, 0);
	std::vector<TH1D*> h_elec_ratio7Inf(8, 0);

	std::vector<TH1D*> h_mu_ratioAvg(8, 0);
	std::vector<TH1D*> h_elec_ratioAvg(8, 0);

	std::vector<TH1D*> h_mu_ratioNJets(7, 0);
	std::vector<TH1D*> h_elec_ratioNJets(7, 0);


	for(unsigned i = 0; i<h_mu_ratio4.size(); ++i){
		h_mu_ratio2.at(i) = new TH1D(TString("h_mu_ratio2_")+TString(std::to_string(i)),TString("h_mu_ratio2_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio3.at(i) = new TH1D(TString("h_mu_ratio3_")+TString(std::to_string(i)),TString("h_mu_ratio3_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio4.at(i) = new TH1D(TString("h_mu_ratio4_")+TString(std::to_string(i)),TString("h_mu_ratio4_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio5.at(i) = new TH1D(TString("h_mu_ratio5_")+TString(std::to_string(i)),TString("h_mu_ratio5_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio6.at(i) = new TH1D(TString("h_mu_ratio6_")+TString(std::to_string(i)),TString("h_mu_ratio6_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio78.at(i) = new TH1D(TString("h_mu_ratio78_")+TString(std::to_string(i)),TString("h_mu_ratio78_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio9Inf.at(i) = new TH1D(TString("h_mu_ratio9Inf_")+TString(std::to_string(i)),TString("h_mu_ratio9Inf_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio7Inf.at(i) = new TH1D(TString("h_mu_ratio7Inf_")+TString(std::to_string(i)),TString("h_mu_ratio7Inf_")+TString(std::to_string(i)), 10000, 0., 1.);

		h_elec_ratio2.at(i) = new TH1D(TString("h_elec_ratio2_")+TString(std::to_string(i)),TString("h_elec_ratio2_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio3.at(i) = new TH1D(TString("h_elec_ratio3_")+TString(std::to_string(i)),TString("h_elec_ratio3_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio4.at(i) = new TH1D(TString("h_elec_ratio4_")+TString(std::to_string(i)),TString("h_elec_ratio4_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio5.at(i) = new TH1D(TString("h_elec_ratio5_")+TString(std::to_string(i)),TString("h_elec_ratio5_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio6.at(i) = new TH1D(TString("h_elec_ratio6_")+TString(std::to_string(i)),TString("h_elec_ratio6_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio78.at(i) = new TH1D(TString("h_elec_ratio78_")+TString(std::to_string(i)),TString("h_elec_ratio78_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio9Inf.at(i) = new TH1D(TString("h_elec_ratio9Inf_")+TString(std::to_string(i)),TString("h_elec_ratio9Inf_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratio7Inf.at(i) = new TH1D(TString("h_elec_ratio7Inf_")+TString(std::to_string(i)),TString("h_elec_ratio7Inf_")+TString(std::to_string(i)), 10000, 0., 1.);
	
		h_mu_ratioAvg.at(i) = new TH1D(TString("h_mu_ratioAvg_")+TString(std::to_string(i)),TString("h_mu_ratioAvg_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratioAvg.at(i) = new TH1D(TString("h_elec_ratioAvg_")+TString(std::to_string(i)),TString("h_elec_ratioAvg_")+TString(std::to_string(i)), 10000, 0., 1.);
	}

	for(unsigned i = 0; i<h_mu_ratioNJets.size(); ++i){
		h_mu_ratioNJets.at(i) = new TH1D(TString("h_mu_ratioNJets_")+TString(std::to_string(i)),TString("h_mu_ratioNJets_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratioNJets.at(i) = new TH1D(TString("h_elec_ratioNJets_")+TString(std::to_string(i)),TString("h_elec_ratioNJets_")+TString(std::to_string(i)), 10000, 0., 1.);
	}

	for(unsigned i = 0; i<mu_pass.size(); ++i){
    	h_mu_ratio->Fill(mu_pass.at(i)/(mu_pass.at(i)+mu_fail.at(i)));
    	h_mu_ratio2.at(0)->Fill(h_mu_pass2.at(i)->GetBinContent(1,1)/(h_mu_pass2.at(i)->GetBinContent(1,1)+h_mu_fail2.at(i)->GetBinContent(1,1)));
		h_mu_ratio2.at(1)->Fill(h_mu_pass2.at(i)->GetBinContent(2,1)/(h_mu_pass2.at(i)->GetBinContent(2,1)+h_mu_fail2.at(i)->GetBinContent(2,1)));
		h_mu_ratio2.at(2)->Fill(h_mu_pass2.at(i)->GetBinContent(3,1)/(h_mu_pass2.at(i)->GetBinContent(3,1)+h_mu_fail2.at(i)->GetBinContent(3,1)));
		h_mu_ratio2.at(3)->Fill(h_mu_pass2.at(i)->GetBinContent(1,2)/(h_mu_pass2.at(i)->GetBinContent(1,2)+h_mu_fail2.at(i)->GetBinContent(1,2)));
		h_mu_ratio2.at(4)->Fill(h_mu_pass2.at(i)->GetBinContent(2,2)/(h_mu_pass2.at(i)->GetBinContent(2,2)+h_mu_fail2.at(i)->GetBinContent(2,2)));
		h_mu_ratio2.at(5)->Fill(h_mu_pass2.at(i)->GetBinContent(3,2)/(h_mu_pass2.at(i)->GetBinContent(3,2)+h_mu_fail2.at(i)->GetBinContent(3,2)));
		h_mu_ratio2.at(6)->Fill(h_mu_pass2.at(i)->GetBinContent(2,3)/(h_mu_pass2.at(i)->GetBinContent(2,3)+h_mu_fail2.at(i)->GetBinContent(2,3)));
		h_mu_ratio2.at(7)->Fill(h_mu_pass2.at(i)->GetBinContent(3,3)/(h_mu_pass2.at(i)->GetBinContent(3,3)+h_mu_fail2.at(i)->GetBinContent(3,3)));
    	h_mu_ratio3.at(0)->Fill(h_mu_pass3.at(i)->GetBinContent(1,1)/(h_mu_pass3.at(i)->GetBinContent(1,1)+h_mu_fail3.at(i)->GetBinContent(1,1)));
		h_mu_ratio3.at(1)->Fill(h_mu_pass3.at(i)->GetBinContent(2,1)/(h_mu_pass3.at(i)->GetBinContent(2,1)+h_mu_fail3.at(i)->GetBinContent(2,1)));
		h_mu_ratio3.at(2)->Fill(h_mu_pass3.at(i)->GetBinContent(3,1)/(h_mu_pass3.at(i)->GetBinContent(3,1)+h_mu_fail3.at(i)->GetBinContent(3,1)));
		h_mu_ratio3.at(3)->Fill(h_mu_pass3.at(i)->GetBinContent(1,2)/(h_mu_pass3.at(i)->GetBinContent(1,2)+h_mu_fail3.at(i)->GetBinContent(1,2)));
		h_mu_ratio3.at(4)->Fill(h_mu_pass3.at(i)->GetBinContent(2,2)/(h_mu_pass3.at(i)->GetBinContent(2,2)+h_mu_fail3.at(i)->GetBinContent(2,2)));
		h_mu_ratio3.at(5)->Fill(h_mu_pass3.at(i)->GetBinContent(3,2)/(h_mu_pass3.at(i)->GetBinContent(3,2)+h_mu_fail3.at(i)->GetBinContent(3,2)));
		h_mu_ratio3.at(6)->Fill(h_mu_pass3.at(i)->GetBinContent(2,3)/(h_mu_pass3.at(i)->GetBinContent(2,3)+h_mu_fail3.at(i)->GetBinContent(2,3)));
		h_mu_ratio3.at(7)->Fill(h_mu_pass3.at(i)->GetBinContent(3,3)/(h_mu_pass3.at(i)->GetBinContent(3,3)+h_mu_fail3.at(i)->GetBinContent(3,3)));
		h_mu_ratio4.at(0)->Fill(h_mu_pass4.at(i)->GetBinContent(1,1)/(h_mu_pass4.at(i)->GetBinContent(1,1)+h_mu_fail4.at(i)->GetBinContent(1,1)));
		h_mu_ratio4.at(1)->Fill(h_mu_pass4.at(i)->GetBinContent(2,1)/(h_mu_pass4.at(i)->GetBinContent(2,1)+h_mu_fail4.at(i)->GetBinContent(2,1)));
		h_mu_ratio4.at(2)->Fill(h_mu_pass4.at(i)->GetBinContent(3,1)/(h_mu_pass4.at(i)->GetBinContent(3,1)+h_mu_fail4.at(i)->GetBinContent(3,1)));
		h_mu_ratio4.at(3)->Fill(h_mu_pass4.at(i)->GetBinContent(1,2)/(h_mu_pass4.at(i)->GetBinContent(1,2)+h_mu_fail4.at(i)->GetBinContent(1,2)));
		h_mu_ratio4.at(4)->Fill(h_mu_pass4.at(i)->GetBinContent(2,2)/(h_mu_pass4.at(i)->GetBinContent(2,2)+h_mu_fail4.at(i)->GetBinContent(2,2)));
		h_mu_ratio4.at(5)->Fill(h_mu_pass4.at(i)->GetBinContent(3,2)/(h_mu_pass4.at(i)->GetBinContent(3,2)+h_mu_fail4.at(i)->GetBinContent(3,2)));
		h_mu_ratio4.at(6)->Fill(h_mu_pass4.at(i)->GetBinContent(2,3)/(h_mu_pass4.at(i)->GetBinContent(2,3)+h_mu_fail4.at(i)->GetBinContent(2,3)));
		h_mu_ratio4.at(7)->Fill(h_mu_pass4.at(i)->GetBinContent(3,3)/(h_mu_pass4.at(i)->GetBinContent(3,3)+h_mu_fail4.at(i)->GetBinContent(3,3)));
		h_mu_ratio5.at(0)->Fill(h_mu_pass5.at(i)->GetBinContent(1,1)/(h_mu_pass5.at(i)->GetBinContent(1,1)+h_mu_fail5.at(i)->GetBinContent(1,1)));
		h_mu_ratio5.at(1)->Fill(h_mu_pass5.at(i)->GetBinContent(2,1)/(h_mu_pass5.at(i)->GetBinContent(2,1)+h_mu_fail5.at(i)->GetBinContent(2,1)));
		h_mu_ratio5.at(2)->Fill(h_mu_pass5.at(i)->GetBinContent(3,1)/(h_mu_pass5.at(i)->GetBinContent(3,1)+h_mu_fail5.at(i)->GetBinContent(3,1)));
		h_mu_ratio5.at(3)->Fill(h_mu_pass5.at(i)->GetBinContent(1,2)/(h_mu_pass5.at(i)->GetBinContent(1,2)+h_mu_fail5.at(i)->GetBinContent(1,2)));
		h_mu_ratio5.at(4)->Fill(h_mu_pass5.at(i)->GetBinContent(2,2)/(h_mu_pass5.at(i)->GetBinContent(2,2)+h_mu_fail5.at(i)->GetBinContent(2,2)));
		h_mu_ratio5.at(5)->Fill(h_mu_pass5.at(i)->GetBinContent(3,2)/(h_mu_pass5.at(i)->GetBinContent(3,2)+h_mu_fail5.at(i)->GetBinContent(3,2)));
		h_mu_ratio5.at(6)->Fill(h_mu_pass5.at(i)->GetBinContent(2,3)/(h_mu_pass5.at(i)->GetBinContent(2,3)+h_mu_fail5.at(i)->GetBinContent(2,3)));
		h_mu_ratio5.at(7)->Fill(h_mu_pass5.at(i)->GetBinContent(3,3)/(h_mu_pass5.at(i)->GetBinContent(3,3)+h_mu_fail5.at(i)->GetBinContent(3,3)));
		h_mu_ratio6.at(0)->Fill(h_mu_pass6.at(i)->GetBinContent(1,1)/(h_mu_pass6.at(i)->GetBinContent(1,1)+h_mu_fail6.at(i)->GetBinContent(1,1)));
		h_mu_ratio6.at(1)->Fill(h_mu_pass6.at(i)->GetBinContent(2,1)/(h_mu_pass6.at(i)->GetBinContent(2,1)+h_mu_fail6.at(i)->GetBinContent(2,1)));
		h_mu_ratio6.at(2)->Fill(h_mu_pass6.at(i)->GetBinContent(3,1)/(h_mu_pass6.at(i)->GetBinContent(3,1)+h_mu_fail6.at(i)->GetBinContent(3,1)));
		h_mu_ratio6.at(3)->Fill(h_mu_pass6.at(i)->GetBinContent(1,2)/(h_mu_pass6.at(i)->GetBinContent(1,2)+h_mu_fail6.at(i)->GetBinContent(1,2)));
		h_mu_ratio6.at(4)->Fill(h_mu_pass6.at(i)->GetBinContent(2,2)/(h_mu_pass6.at(i)->GetBinContent(2,2)+h_mu_fail6.at(i)->GetBinContent(2,2)));
		h_mu_ratio6.at(5)->Fill(h_mu_pass6.at(i)->GetBinContent(3,2)/(h_mu_pass6.at(i)->GetBinContent(3,2)+h_mu_fail6.at(i)->GetBinContent(3,2)));
		h_mu_ratio6.at(6)->Fill(h_mu_pass6.at(i)->GetBinContent(2,3)/(h_mu_pass6.at(i)->GetBinContent(2,3)+h_mu_fail6.at(i)->GetBinContent(2,3)));
		h_mu_ratio6.at(7)->Fill(h_mu_pass6.at(i)->GetBinContent(3,3)/(h_mu_pass6.at(i)->GetBinContent(3,3)+h_mu_fail6.at(i)->GetBinContent(3,3)));
		h_mu_ratio78.at(0)->Fill(h_mu_pass78.at(i)->GetBinContent(1,1)/(h_mu_pass78.at(i)->GetBinContent(1,1)+h_mu_fail78.at(i)->GetBinContent(1,1)));
		h_mu_ratio78.at(1)->Fill(h_mu_pass78.at(i)->GetBinContent(2,1)/(h_mu_pass78.at(i)->GetBinContent(2,1)+h_mu_fail78.at(i)->GetBinContent(2,1)));
		h_mu_ratio78.at(2)->Fill(h_mu_pass78.at(i)->GetBinContent(3,1)/(h_mu_pass78.at(i)->GetBinContent(3,1)+h_mu_fail78.at(i)->GetBinContent(3,1)));
		h_mu_ratio78.at(3)->Fill(h_mu_pass78.at(i)->GetBinContent(1,2)/(h_mu_pass78.at(i)->GetBinContent(1,2)+h_mu_fail78.at(i)->GetBinContent(1,2)));
		h_mu_ratio78.at(4)->Fill(h_mu_pass78.at(i)->GetBinContent(2,2)/(h_mu_pass78.at(i)->GetBinContent(2,2)+h_mu_fail78.at(i)->GetBinContent(2,2)));
		h_mu_ratio78.at(5)->Fill(h_mu_pass78.at(i)->GetBinContent(3,2)/(h_mu_pass78.at(i)->GetBinContent(3,2)+h_mu_fail78.at(i)->GetBinContent(3,2)));
		h_mu_ratio78.at(6)->Fill(h_mu_pass78.at(i)->GetBinContent(2,3)/(h_mu_pass78.at(i)->GetBinContent(2,3)+h_mu_fail78.at(i)->GetBinContent(2,3)));
		h_mu_ratio78.at(7)->Fill(h_mu_pass78.at(i)->GetBinContent(3,3)/(h_mu_pass78.at(i)->GetBinContent(3,3)+h_mu_fail78.at(i)->GetBinContent(3,3)));
		h_mu_ratio9Inf.at(0)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(1,1)/(h_mu_pass9Inf.at(i)->GetBinContent(1,1)+h_mu_fail9Inf.at(i)->GetBinContent(1,1)));
		h_mu_ratio9Inf.at(1)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(2,1)/(h_mu_pass9Inf.at(i)->GetBinContent(2,1)+h_mu_fail9Inf.at(i)->GetBinContent(2,1)));
		h_mu_ratio9Inf.at(2)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(3,1)/(h_mu_pass9Inf.at(i)->GetBinContent(3,1)+h_mu_fail9Inf.at(i)->GetBinContent(3,1)));
		h_mu_ratio9Inf.at(3)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(1,2)/(h_mu_pass9Inf.at(i)->GetBinContent(1,2)+h_mu_fail9Inf.at(i)->GetBinContent(1,2)));
		h_mu_ratio9Inf.at(4)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(2,2)/(h_mu_pass9Inf.at(i)->GetBinContent(2,2)+h_mu_fail9Inf.at(i)->GetBinContent(2,2)));
		h_mu_ratio9Inf.at(5)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(3,2)/(h_mu_pass9Inf.at(i)->GetBinContent(3,2)+h_mu_fail9Inf.at(i)->GetBinContent(3,2)));
		h_mu_ratio9Inf.at(6)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(2,3)/(h_mu_pass9Inf.at(i)->GetBinContent(2,3)+h_mu_fail9Inf.at(i)->GetBinContent(2,3)));
		h_mu_ratio9Inf.at(7)->Fill(h_mu_pass9Inf.at(i)->GetBinContent(3,3)/(h_mu_pass9Inf.at(i)->GetBinContent(3,3)+h_mu_fail9Inf.at(i)->GetBinContent(3,3)));
		h_mu_ratio7Inf.at(0)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(1,1)/(h_mu_pass7Inf.at(i)->GetBinContent(1,1)+h_mu_fail7Inf.at(i)->GetBinContent(1,1)));
		h_mu_ratio7Inf.at(1)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(2,1)/(h_mu_pass7Inf.at(i)->GetBinContent(2,1)+h_mu_fail7Inf.at(i)->GetBinContent(2,1)));
		h_mu_ratio7Inf.at(2)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(3,1)/(h_mu_pass7Inf.at(i)->GetBinContent(3,1)+h_mu_fail7Inf.at(i)->GetBinContent(3,1)));
		h_mu_ratio7Inf.at(3)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(1,2)/(h_mu_pass7Inf.at(i)->GetBinContent(1,2)+h_mu_fail7Inf.at(i)->GetBinContent(1,2)));
		h_mu_ratio7Inf.at(4)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(2,2)/(h_mu_pass7Inf.at(i)->GetBinContent(2,2)+h_mu_fail7Inf.at(i)->GetBinContent(2,2)));
		h_mu_ratio7Inf.at(5)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(3,2)/(h_mu_pass7Inf.at(i)->GetBinContent(3,2)+h_mu_fail7Inf.at(i)->GetBinContent(3,2)));
		h_mu_ratio7Inf.at(6)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(2,3)/(h_mu_pass7Inf.at(i)->GetBinContent(2,3)+h_mu_fail7Inf.at(i)->GetBinContent(2,3)));
		h_mu_ratio7Inf.at(7)->Fill(h_mu_pass7Inf.at(i)->GetBinContent(3,3)/(h_mu_pass7Inf.at(i)->GetBinContent(3,3)+h_mu_fail7Inf.at(i)->GetBinContent(3,3)));

		h_elec_ratio->Fill(elec_pass.at(i)/(elec_pass.at(i)+elec_fail.at(i)));
		h_elec_ratio2.at(0)->Fill(h_elec_pass2.at(i)->GetBinContent(1,1)/(h_elec_pass2.at(i)->GetBinContent(1,1)+h_elec_fail2.at(i)->GetBinContent(1,1)));
		h_elec_ratio2.at(1)->Fill(h_elec_pass2.at(i)->GetBinContent(2,1)/(h_elec_pass2.at(i)->GetBinContent(2,1)+h_elec_fail2.at(i)->GetBinContent(2,1)));
		h_elec_ratio2.at(2)->Fill(h_elec_pass2.at(i)->GetBinContent(3,1)/(h_elec_pass2.at(i)->GetBinContent(3,1)+h_elec_fail2.at(i)->GetBinContent(3,1)));
		h_elec_ratio2.at(3)->Fill(h_elec_pass2.at(i)->GetBinContent(1,2)/(h_elec_pass2.at(i)->GetBinContent(1,2)+h_elec_fail2.at(i)->GetBinContent(1,2)));
		h_elec_ratio2.at(4)->Fill(h_elec_pass2.at(i)->GetBinContent(2,2)/(h_elec_pass2.at(i)->GetBinContent(2,2)+h_elec_fail2.at(i)->GetBinContent(2,2)));
		h_elec_ratio2.at(5)->Fill(h_elec_pass2.at(i)->GetBinContent(3,2)/(h_elec_pass2.at(i)->GetBinContent(3,2)+h_elec_fail2.at(i)->GetBinContent(3,2)));
		h_elec_ratio2.at(6)->Fill(h_elec_pass2.at(i)->GetBinContent(2,3)/(h_elec_pass2.at(i)->GetBinContent(2,3)+h_elec_fail2.at(i)->GetBinContent(2,3)));
		h_elec_ratio2.at(7)->Fill(h_elec_pass2.at(i)->GetBinContent(3,3)/(h_elec_pass2.at(i)->GetBinContent(3,3)+h_elec_fail2.at(i)->GetBinContent(3,3)));
    	h_elec_ratio3.at(0)->Fill(h_elec_pass3.at(i)->GetBinContent(1,1)/(h_elec_pass3.at(i)->GetBinContent(1,1)+h_elec_fail3.at(i)->GetBinContent(1,1)));
		h_elec_ratio3.at(1)->Fill(h_elec_pass3.at(i)->GetBinContent(2,1)/(h_elec_pass3.at(i)->GetBinContent(2,1)+h_elec_fail3.at(i)->GetBinContent(2,1)));
		h_elec_ratio3.at(2)->Fill(h_elec_pass3.at(i)->GetBinContent(3,1)/(h_elec_pass3.at(i)->GetBinContent(3,1)+h_elec_fail3.at(i)->GetBinContent(3,1)));
		h_elec_ratio3.at(3)->Fill(h_elec_pass3.at(i)->GetBinContent(1,2)/(h_elec_pass3.at(i)->GetBinContent(1,2)+h_elec_fail3.at(i)->GetBinContent(1,2)));
		h_elec_ratio3.at(4)->Fill(h_elec_pass3.at(i)->GetBinContent(2,2)/(h_elec_pass3.at(i)->GetBinContent(2,2)+h_elec_fail3.at(i)->GetBinContent(2,2)));
		h_elec_ratio3.at(5)->Fill(h_elec_pass3.at(i)->GetBinContent(3,2)/(h_elec_pass3.at(i)->GetBinContent(3,2)+h_elec_fail3.at(i)->GetBinContent(3,2)));
		h_elec_ratio3.at(6)->Fill(h_elec_pass3.at(i)->GetBinContent(2,3)/(h_elec_pass3.at(i)->GetBinContent(2,3)+h_elec_fail3.at(i)->GetBinContent(2,3)));
		h_elec_ratio3.at(7)->Fill(h_elec_pass3.at(i)->GetBinContent(3,3)/(h_elec_pass3.at(i)->GetBinContent(3,3)+h_elec_fail3.at(i)->GetBinContent(3,3)));
		h_elec_ratio4.at(0)->Fill(h_elec_pass4.at(i)->GetBinContent(1,1)/(h_elec_pass4.at(i)->GetBinContent(1,1)+h_elec_fail4.at(i)->GetBinContent(1,1)));
		h_elec_ratio4.at(1)->Fill(h_elec_pass4.at(i)->GetBinContent(2,1)/(h_elec_pass4.at(i)->GetBinContent(2,1)+h_elec_fail4.at(i)->GetBinContent(2,1)));
		h_elec_ratio4.at(2)->Fill(h_elec_pass4.at(i)->GetBinContent(3,1)/(h_elec_pass4.at(i)->GetBinContent(3,1)+h_elec_fail4.at(i)->GetBinContent(3,1)));
		h_elec_ratio4.at(3)->Fill(h_elec_pass4.at(i)->GetBinContent(1,2)/(h_elec_pass4.at(i)->GetBinContent(1,2)+h_elec_fail4.at(i)->GetBinContent(1,2)));
		h_elec_ratio4.at(4)->Fill(h_elec_pass4.at(i)->GetBinContent(2,2)/(h_elec_pass4.at(i)->GetBinContent(2,2)+h_elec_fail4.at(i)->GetBinContent(2,2)));
		h_elec_ratio4.at(5)->Fill(h_elec_pass4.at(i)->GetBinContent(3,2)/(h_elec_pass4.at(i)->GetBinContent(3,2)+h_elec_fail4.at(i)->GetBinContent(3,2)));
		h_elec_ratio4.at(6)->Fill(h_elec_pass4.at(i)->GetBinContent(2,3)/(h_elec_pass4.at(i)->GetBinContent(2,3)+h_elec_fail4.at(i)->GetBinContent(2,3)));
		h_elec_ratio4.at(7)->Fill(h_elec_pass4.at(i)->GetBinContent(3,3)/(h_elec_pass4.at(i)->GetBinContent(3,3)+h_elec_fail4.at(i)->GetBinContent(3,3)));
		h_elec_ratio5.at(0)->Fill(h_elec_pass5.at(i)->GetBinContent(1,1)/(h_elec_pass5.at(i)->GetBinContent(1,1)+h_elec_fail5.at(i)->GetBinContent(1,1)));
		h_elec_ratio5.at(1)->Fill(h_elec_pass5.at(i)->GetBinContent(2,1)/(h_elec_pass5.at(i)->GetBinContent(2,1)+h_elec_fail5.at(i)->GetBinContent(2,1)));
		h_elec_ratio5.at(2)->Fill(h_elec_pass5.at(i)->GetBinContent(3,1)/(h_elec_pass5.at(i)->GetBinContent(3,1)+h_elec_fail5.at(i)->GetBinContent(3,1)));
		h_elec_ratio5.at(3)->Fill(h_elec_pass5.at(i)->GetBinContent(1,2)/(h_elec_pass5.at(i)->GetBinContent(1,2)+h_elec_fail5.at(i)->GetBinContent(1,2)));
		h_elec_ratio5.at(4)->Fill(h_elec_pass5.at(i)->GetBinContent(2,2)/(h_elec_pass5.at(i)->GetBinContent(2,2)+h_elec_fail5.at(i)->GetBinContent(2,2)));
		h_elec_ratio5.at(5)->Fill(h_elec_pass5.at(i)->GetBinContent(3,2)/(h_elec_pass5.at(i)->GetBinContent(3,2)+h_elec_fail5.at(i)->GetBinContent(3,2)));
		h_elec_ratio5.at(6)->Fill(h_elec_pass5.at(i)->GetBinContent(2,3)/(h_elec_pass5.at(i)->GetBinContent(2,3)+h_elec_fail5.at(i)->GetBinContent(2,3)));
		h_elec_ratio5.at(7)->Fill(h_elec_pass5.at(i)->GetBinContent(3,3)/(h_elec_pass5.at(i)->GetBinContent(3,3)+h_elec_fail5.at(i)->GetBinContent(3,3)));
		h_elec_ratio6.at(0)->Fill(h_elec_pass6.at(i)->GetBinContent(1,1)/(h_elec_pass6.at(i)->GetBinContent(1,1)+h_elec_fail6.at(i)->GetBinContent(1,1)));
		h_elec_ratio6.at(1)->Fill(h_elec_pass6.at(i)->GetBinContent(2,1)/(h_elec_pass6.at(i)->GetBinContent(2,1)+h_elec_fail6.at(i)->GetBinContent(2,1)));
		h_elec_ratio6.at(2)->Fill(h_elec_pass6.at(i)->GetBinContent(3,1)/(h_elec_pass6.at(i)->GetBinContent(3,1)+h_elec_fail6.at(i)->GetBinContent(3,1)));
		h_elec_ratio6.at(3)->Fill(h_elec_pass6.at(i)->GetBinContent(1,2)/(h_elec_pass6.at(i)->GetBinContent(1,2)+h_elec_fail6.at(i)->GetBinContent(1,2)));
		h_elec_ratio6.at(4)->Fill(h_elec_pass6.at(i)->GetBinContent(2,2)/(h_elec_pass6.at(i)->GetBinContent(2,2)+h_elec_fail6.at(i)->GetBinContent(2,2)));
		h_elec_ratio6.at(5)->Fill(h_elec_pass6.at(i)->GetBinContent(3,2)/(h_elec_pass6.at(i)->GetBinContent(3,2)+h_elec_fail6.at(i)->GetBinContent(3,2)));
		h_elec_ratio6.at(6)->Fill(h_elec_pass6.at(i)->GetBinContent(2,3)/(h_elec_pass6.at(i)->GetBinContent(2,3)+h_elec_fail6.at(i)->GetBinContent(2,3)));
		h_elec_ratio6.at(7)->Fill(h_elec_pass6.at(i)->GetBinContent(3,3)/(h_elec_pass6.at(i)->GetBinContent(3,3)+h_elec_fail6.at(i)->GetBinContent(3,3)));
		h_elec_ratio78.at(0)->Fill(h_elec_pass78.at(i)->GetBinContent(1,1)/(h_elec_pass78.at(i)->GetBinContent(1,1)+h_elec_fail78.at(i)->GetBinContent(1,1)));
		h_elec_ratio78.at(1)->Fill(h_elec_pass78.at(i)->GetBinContent(2,1)/(h_elec_pass78.at(i)->GetBinContent(2,1)+h_elec_fail78.at(i)->GetBinContent(2,1)));
		h_elec_ratio78.at(2)->Fill(h_elec_pass78.at(i)->GetBinContent(3,1)/(h_elec_pass78.at(i)->GetBinContent(3,1)+h_elec_fail78.at(i)->GetBinContent(3,1)));
		h_elec_ratio78.at(3)->Fill(h_elec_pass78.at(i)->GetBinContent(1,2)/(h_elec_pass78.at(i)->GetBinContent(1,2)+h_elec_fail78.at(i)->GetBinContent(1,2)));
		h_elec_ratio78.at(4)->Fill(h_elec_pass78.at(i)->GetBinContent(2,2)/(h_elec_pass78.at(i)->GetBinContent(2,2)+h_elec_fail78.at(i)->GetBinContent(2,2)));
		h_elec_ratio78.at(5)->Fill(h_elec_pass78.at(i)->GetBinContent(3,2)/(h_elec_pass78.at(i)->GetBinContent(3,2)+h_elec_fail78.at(i)->GetBinContent(3,2)));
		h_elec_ratio78.at(6)->Fill(h_elec_pass78.at(i)->GetBinContent(2,3)/(h_elec_pass78.at(i)->GetBinContent(2,3)+h_elec_fail78.at(i)->GetBinContent(2,3)));
		h_elec_ratio78.at(7)->Fill(h_elec_pass78.at(i)->GetBinContent(3,3)/(h_elec_pass78.at(i)->GetBinContent(3,3)+h_elec_fail78.at(i)->GetBinContent(3,3)));
		h_elec_ratio9Inf.at(0)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(1,1)/(h_elec_pass9Inf.at(i)->GetBinContent(1,1)+h_elec_fail9Inf.at(i)->GetBinContent(1,1)));
		h_elec_ratio9Inf.at(1)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(2,1)/(h_elec_pass9Inf.at(i)->GetBinContent(2,1)+h_elec_fail9Inf.at(i)->GetBinContent(2,1)));
		h_elec_ratio9Inf.at(2)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(3,1)/(h_elec_pass9Inf.at(i)->GetBinContent(3,1)+h_elec_fail9Inf.at(i)->GetBinContent(3,1)));
		h_elec_ratio9Inf.at(3)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(1,2)/(h_elec_pass9Inf.at(i)->GetBinContent(1,2)+h_elec_fail9Inf.at(i)->GetBinContent(1,2)));
		h_elec_ratio9Inf.at(4)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(2,2)/(h_elec_pass9Inf.at(i)->GetBinContent(2,2)+h_elec_fail9Inf.at(i)->GetBinContent(2,2)));
		h_elec_ratio9Inf.at(5)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(3,2)/(h_elec_pass9Inf.at(i)->GetBinContent(3,2)+h_elec_fail9Inf.at(i)->GetBinContent(3,2)));
		h_elec_ratio9Inf.at(6)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(2,3)/(h_elec_pass9Inf.at(i)->GetBinContent(2,3)+h_elec_fail9Inf.at(i)->GetBinContent(2,3)));
		h_elec_ratio9Inf.at(7)->Fill(h_elec_pass9Inf.at(i)->GetBinContent(3,3)/(h_elec_pass9Inf.at(i)->GetBinContent(3,3)+h_elec_fail9Inf.at(i)->GetBinContent(3,3)));
    	h_elec_ratio7Inf.at(0)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(1,1)/(h_elec_pass7Inf.at(i)->GetBinContent(1,1)+h_elec_fail7Inf.at(i)->GetBinContent(1,1)));
		h_elec_ratio7Inf.at(1)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(2,1)/(h_elec_pass7Inf.at(i)->GetBinContent(2,1)+h_elec_fail7Inf.at(i)->GetBinContent(2,1)));
		h_elec_ratio7Inf.at(2)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(3,1)/(h_elec_pass7Inf.at(i)->GetBinContent(3,1)+h_elec_fail7Inf.at(i)->GetBinContent(3,1)));
		h_elec_ratio7Inf.at(3)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(1,2)/(h_elec_pass7Inf.at(i)->GetBinContent(1,2)+h_elec_fail7Inf.at(i)->GetBinContent(1,2)));
		h_elec_ratio7Inf.at(4)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(2,2)/(h_elec_pass7Inf.at(i)->GetBinContent(2,2)+h_elec_fail7Inf.at(i)->GetBinContent(2,2)));
		h_elec_ratio7Inf.at(5)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(3,2)/(h_elec_pass7Inf.at(i)->GetBinContent(3,2)+h_elec_fail7Inf.at(i)->GetBinContent(3,2)));
		h_elec_ratio7Inf.at(6)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(2,3)/(h_elec_pass7Inf.at(i)->GetBinContent(2,3)+h_elec_fail7Inf.at(i)->GetBinContent(2,3)));
		h_elec_ratio7Inf.at(7)->Fill(h_elec_pass7Inf.at(i)->GetBinContent(3,3)/(h_elec_pass7Inf.at(i)->GetBinContent(3,3)+h_elec_fail7Inf.at(i)->GetBinContent(3,3)));
    
		h_mu_ratioAvg.at(0)->Fill(h_mu_passAvg.at(i)->GetBinContent(1,1)/(h_mu_passAvg.at(i)->GetBinContent(1,1)+h_mu_failAvg.at(i)->GetBinContent(1,1)));
		h_mu_ratioAvg.at(1)->Fill(h_mu_passAvg.at(i)->GetBinContent(2,1)/(h_mu_passAvg.at(i)->GetBinContent(2,1)+h_mu_failAvg.at(i)->GetBinContent(2,1)));
		h_mu_ratioAvg.at(2)->Fill(h_mu_passAvg.at(i)->GetBinContent(3,1)/(h_mu_passAvg.at(i)->GetBinContent(3,1)+h_mu_failAvg.at(i)->GetBinContent(3,1)));
		h_mu_ratioAvg.at(3)->Fill(h_mu_passAvg.at(i)->GetBinContent(1,2)/(h_mu_passAvg.at(i)->GetBinContent(1,2)+h_mu_failAvg.at(i)->GetBinContent(1,2)));
		h_mu_ratioAvg.at(4)->Fill(h_mu_passAvg.at(i)->GetBinContent(2,2)/(h_mu_passAvg.at(i)->GetBinContent(2,2)+h_mu_failAvg.at(i)->GetBinContent(2,2)));
		h_mu_ratioAvg.at(5)->Fill(h_mu_passAvg.at(i)->GetBinContent(3,2)/(h_mu_passAvg.at(i)->GetBinContent(3,2)+h_mu_failAvg.at(i)->GetBinContent(3,2)));
		h_mu_ratioAvg.at(6)->Fill(h_mu_passAvg.at(i)->GetBinContent(2,3)/(h_mu_passAvg.at(i)->GetBinContent(2,3)+h_mu_failAvg.at(i)->GetBinContent(2,3)));
		h_mu_ratioAvg.at(7)->Fill(h_mu_passAvg.at(i)->GetBinContent(3,3)/(h_mu_passAvg.at(i)->GetBinContent(3,3)+h_mu_failAvg.at(i)->GetBinContent(3,3)));
		h_elec_ratioAvg.at(0)->Fill(h_elec_passAvg.at(i)->GetBinContent(1,1)/(h_elec_passAvg.at(i)->GetBinContent(1,1)+h_elec_failAvg.at(i)->GetBinContent(1,1)));
		h_elec_ratioAvg.at(1)->Fill(h_elec_passAvg.at(i)->GetBinContent(2,1)/(h_elec_passAvg.at(i)->GetBinContent(2,1)+h_elec_failAvg.at(i)->GetBinContent(2,1)));
		h_elec_ratioAvg.at(2)->Fill(h_elec_passAvg.at(i)->GetBinContent(3,1)/(h_elec_passAvg.at(i)->GetBinContent(3,1)+h_elec_failAvg.at(i)->GetBinContent(3,1)));
		h_elec_ratioAvg.at(3)->Fill(h_elec_passAvg.at(i)->GetBinContent(1,2)/(h_elec_passAvg.at(i)->GetBinContent(1,2)+h_elec_failAvg.at(i)->GetBinContent(1,2)));
		h_elec_ratioAvg.at(4)->Fill(h_elec_passAvg.at(i)->GetBinContent(2,2)/(h_elec_passAvg.at(i)->GetBinContent(2,2)+h_elec_failAvg.at(i)->GetBinContent(2,2)));
		h_elec_ratioAvg.at(5)->Fill(h_elec_passAvg.at(i)->GetBinContent(3,2)/(h_elec_passAvg.at(i)->GetBinContent(3,2)+h_elec_failAvg.at(i)->GetBinContent(3,2)));
		h_elec_ratioAvg.at(6)->Fill(h_elec_passAvg.at(i)->GetBinContent(2,3)/(h_elec_passAvg.at(i)->GetBinContent(2,3)+h_elec_failAvg.at(i)->GetBinContent(2,3)));
		h_elec_ratioAvg.at(7)->Fill(h_elec_passAvg.at(i)->GetBinContent(3,3)/(h_elec_passAvg.at(i)->GetBinContent(3,3)+h_elec_failAvg.at(i)->GetBinContent(3,3)));

		h_mu_ratioNJets.at(0)->Fill(h_mu_passNJets.at(i)->GetBinContent(1)/(h_mu_passNJets.at(i)->GetBinContent(1)+h_mu_failNJets.at(i)->GetBinContent(1)));
		h_mu_ratioNJets.at(1)->Fill(h_mu_passNJets.at(i)->GetBinContent(2)/(h_mu_passNJets.at(i)->GetBinContent(2)+h_mu_failNJets.at(i)->GetBinContent(2)));
		h_mu_ratioNJets.at(2)->Fill(h_mu_passNJets.at(i)->GetBinContent(3)/(h_mu_passNJets.at(i)->GetBinContent(3)+h_mu_failNJets.at(i)->GetBinContent(3)));
		h_mu_ratioNJets.at(3)->Fill(h_mu_passNJets.at(i)->GetBinContent(4)/(h_mu_passNJets.at(i)->GetBinContent(4)+h_mu_failNJets.at(i)->GetBinContent(4)));
		h_mu_ratioNJets.at(4)->Fill(h_mu_passNJets.at(i)->GetBinContent(5)/(h_mu_passNJets.at(i)->GetBinContent(5)+h_mu_failNJets.at(i)->GetBinContent(5)));
		h_mu_ratioNJets.at(5)->Fill(h_mu_passNJets.at(i)->GetBinContent(6)/(h_mu_passNJets.at(i)->GetBinContent(6)+h_mu_failNJets.at(i)->GetBinContent(6)));
		h_mu_ratioNJets.at(6)->Fill(h_mu_passNJets.at(i)->GetBinContent(7)/(h_mu_passNJets.at(i)->GetBinContent(7)+h_mu_failNJets.at(i)->GetBinContent(7)));

		h_elec_ratioNJets.at(0)->Fill(h_elec_passNJets.at(i)->GetBinContent(1)/(h_elec_passNJets.at(i)->GetBinContent(1)+h_elec_failNJets.at(i)->GetBinContent(1)));
		h_elec_ratioNJets.at(1)->Fill(h_elec_passNJets.at(i)->GetBinContent(2)/(h_elec_passNJets.at(i)->GetBinContent(2)+h_elec_failNJets.at(i)->GetBinContent(2)));
		h_elec_ratioNJets.at(2)->Fill(h_elec_passNJets.at(i)->GetBinContent(3)/(h_elec_passNJets.at(i)->GetBinContent(3)+h_elec_failNJets.at(i)->GetBinContent(3)));
		h_elec_ratioNJets.at(3)->Fill(h_elec_passNJets.at(i)->GetBinContent(4)/(h_elec_passNJets.at(i)->GetBinContent(4)+h_elec_failNJets.at(i)->GetBinContent(4)));
		h_elec_ratioNJets.at(4)->Fill(h_elec_passNJets.at(i)->GetBinContent(5)/(h_elec_passNJets.at(i)->GetBinContent(5)+h_elec_failNJets.at(i)->GetBinContent(5)));
		h_elec_ratioNJets.at(5)->Fill(h_elec_passNJets.at(i)->GetBinContent(6)/(h_elec_passNJets.at(i)->GetBinContent(6)+h_elec_failNJets.at(i)->GetBinContent(6)));
		h_elec_ratioNJets.at(6)->Fill(h_elec_passNJets.at(i)->GetBinContent(7)/(h_elec_passNJets.at(i)->GetBinContent(7)+h_elec_failNJets.at(i)->GetBinContent(7)));
    }
    /*
  	TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  	c1->Divide(2,1);
  	c1->cd(1);
  	c1->SetLogx();
  	c1->SetLogy();
    h_mu_ratio7Inf.at(0)->Draw("");
    std::cout<<h_mu_ratio7Inf.at(0)->GetMean()<<"+-"<<calcEnv(h_mu_ratio7Inf.at(0),false)<<std::endl;
  	c1->cd(2);
  	c1->SetLogx();
  	c1->SetLogy();
    h_mu_ratio7Inf.at(1)->Draw("");
    std::cout<<h_mu_ratio7Inf.at(1)->GetMean()<<"+-"<<calcEnv(h_mu_ratio7Inf.at(1),false)<<std::endl;
*/

	std::cout<<"Mu: Center: "<<mu_pass_central/(mu_pass_central+mu_fail_central)<<std::endl;
    std::cout<<"Mu: RMS: "<<h_mu_ratio->GetMean()<<"+-"<<h_mu_ratio->GetRMS()<<std::endl;
    std::cout<<"Mu: Assym: "<<h_mu_ratio->GetMean()<<"+"<<calcUnc(h_mu_ratio, false)<<"-"<<calcUnc(h_mu_ratio, true)<<std::endl;
    std::cout<<"Mu: Env: "<<h_mu_ratio->GetMean()<<"+"<<calcEnv(h_mu_ratio, false)<<"-"<<calcEnv(h_mu_ratio, true)<<std::endl;
    std::cout<<"Elec: Center: "<<elec_pass_central/(elec_pass_central+elec_fail_central)<<std::endl;
    std::cout<<"Elec: RMS: "<<h_elec_ratio->GetMean()<<"+-"<<h_elec_ratio->GetRMS()<<std::endl;
    std::cout<<"Elec: Assym: "<<h_elec_ratio->GetMean()<<"+"<<calcUnc(h_elec_ratio, false)<<"-"<<calcUnc(h_elec_ratio, true)<<std::endl;
    std::cout<<"Elec: Env: "<<h_elec_ratio->GetMean()<<"+"<<calcEnv(h_elec_ratio, false)<<"-"<<calcEnv(h_elec_ratio, true)<<std::endl;

    MuAccUnc_NJets2->SetBinContent(1,1, h_mu_ratio2.at(0)->GetMean());
    MuAccUnc_NJets2->SetBinError(1,1, calcEnv(h_mu_ratio2.at(0), lower));
    MuAccUnc_NJets2->SetBinContent(2,1, h_mu_ratio2.at(1)->GetMean());
    MuAccUnc_NJets2->SetBinError(2,1, calcEnv(h_mu_ratio2.at(1), lower));
    MuAccUnc_NJets2->SetBinContent(3,1, h_mu_ratio2.at(2)->GetMean());
    MuAccUnc_NJets2->SetBinError(3,1, calcEnv(h_mu_ratio2.at(2), lower));
    MuAccUnc_NJets2->SetBinContent(1,2, h_mu_ratio2.at(3)->GetMean());
    MuAccUnc_NJets2->SetBinError(1,2, calcEnv(h_mu_ratio2.at(3), lower));
    MuAccUnc_NJets2->SetBinContent(2,2, h_mu_ratio2.at(4)->GetMean());
    MuAccUnc_NJets2->SetBinError(2,2, calcEnv(h_mu_ratio2.at(4), lower));
    MuAccUnc_NJets2->SetBinContent(3,2, h_mu_ratio2.at(5)->GetMean());
    MuAccUnc_NJets2->SetBinError(3,2, calcEnv(h_mu_ratio2.at(5), lower));
    MuAccUnc_NJets2->SetBinContent(2,3, h_mu_ratio2.at(6)->GetMean());
    MuAccUnc_NJets2->SetBinError(2,3, calcEnv(h_mu_ratio2.at(6), lower));
    MuAccUnc_NJets2->SetBinContent(3,3, h_mu_ratio2.at(7)->GetMean());
    MuAccUnc_NJets2->SetBinError(3,3, calcEnv(h_mu_ratio2.at(7), lower));
    MuAccUnc_NJets3->SetBinContent(1,1, h_mu_ratio3.at(0)->GetMean());
    MuAccUnc_NJets3->SetBinError(1,1, calcEnv(h_mu_ratio3.at(0), lower));
    MuAccUnc_NJets3->SetBinContent(2,1, h_mu_ratio3.at(1)->GetMean());
    MuAccUnc_NJets3->SetBinError(2,1, calcEnv(h_mu_ratio3.at(1), lower));
    MuAccUnc_NJets3->SetBinContent(3,1, h_mu_ratio3.at(2)->GetMean());
    MuAccUnc_NJets3->SetBinError(3,1, calcEnv(h_mu_ratio3.at(2), lower));
    MuAccUnc_NJets3->SetBinContent(1,2, h_mu_ratio3.at(3)->GetMean());
    MuAccUnc_NJets3->SetBinError(1,2, calcEnv(h_mu_ratio3.at(3), lower));
    MuAccUnc_NJets3->SetBinContent(2,2, h_mu_ratio3.at(4)->GetMean());
    MuAccUnc_NJets3->SetBinError(2,2, calcEnv(h_mu_ratio3.at(4), lower));
    MuAccUnc_NJets3->SetBinContent(3,2, h_mu_ratio3.at(5)->GetMean());
    MuAccUnc_NJets3->SetBinError(3,2, calcEnv(h_mu_ratio3.at(5), lower));
    MuAccUnc_NJets3->SetBinContent(2,3, h_mu_ratio3.at(6)->GetMean());
    MuAccUnc_NJets3->SetBinError(2,3, calcEnv(h_mu_ratio3.at(6), lower));
    MuAccUnc_NJets3->SetBinContent(3,3, h_mu_ratio3.at(7)->GetMean());
    MuAccUnc_NJets3->SetBinError(3,3, calcEnv(h_mu_ratio3.at(7), lower));
    MuAccUnc_NJets4->SetBinContent(1,1, h_mu_ratio4.at(0)->GetMean());
    MuAccUnc_NJets4->SetBinError(1,1, calcEnv(h_mu_ratio4.at(0), lower));
    MuAccUnc_NJets4->SetBinContent(2,1, h_mu_ratio4.at(1)->GetMean());
    MuAccUnc_NJets4->SetBinError(2,1, calcEnv(h_mu_ratio4.at(1), lower));
    MuAccUnc_NJets4->SetBinContent(3,1, h_mu_ratio4.at(2)->GetMean());
    MuAccUnc_NJets4->SetBinError(3,1, calcEnv(h_mu_ratio4.at(2), lower));
    MuAccUnc_NJets4->SetBinContent(1,2, h_mu_ratio4.at(3)->GetMean());
    MuAccUnc_NJets4->SetBinError(1,2, calcEnv(h_mu_ratio4.at(3), lower));
    MuAccUnc_NJets4->SetBinContent(2,2, h_mu_ratio4.at(4)->GetMean());
    MuAccUnc_NJets4->SetBinError(2,2, calcEnv(h_mu_ratio4.at(4), lower));
    MuAccUnc_NJets4->SetBinContent(3,2, h_mu_ratio4.at(5)->GetMean());
    MuAccUnc_NJets4->SetBinError(3,2, calcEnv(h_mu_ratio4.at(5), lower));
    MuAccUnc_NJets4->SetBinContent(2,3, h_mu_ratio4.at(6)->GetMean());
    MuAccUnc_NJets4->SetBinError(2,3, calcEnv(h_mu_ratio4.at(6), lower));
    MuAccUnc_NJets4->SetBinContent(3,3, h_mu_ratio4.at(7)->GetMean());
    MuAccUnc_NJets4->SetBinError(3,3, calcEnv(h_mu_ratio4.at(7), lower));
    MuAccUnc_NJets5->SetBinContent(1,1, h_mu_ratio5.at(0)->GetMean());
    MuAccUnc_NJets5->SetBinError(1,1, calcEnv(h_mu_ratio5.at(0), lower));
    MuAccUnc_NJets5->SetBinContent(2,1, h_mu_ratio5.at(1)->GetMean());
    MuAccUnc_NJets5->SetBinError(2,1, calcEnv(h_mu_ratio5.at(1), lower));
    MuAccUnc_NJets5->SetBinContent(3,1, h_mu_ratio5.at(2)->GetMean());
    MuAccUnc_NJets5->SetBinError(3,1, calcEnv(h_mu_ratio5.at(2), lower));
    MuAccUnc_NJets5->SetBinContent(1,2, h_mu_ratio5.at(3)->GetMean());
    MuAccUnc_NJets5->SetBinError(1,2, calcEnv(h_mu_ratio5.at(3), lower));
    MuAccUnc_NJets5->SetBinContent(2,2, h_mu_ratio5.at(4)->GetMean());
    MuAccUnc_NJets5->SetBinError(2,2, calcEnv(h_mu_ratio5.at(4), lower));
    MuAccUnc_NJets5->SetBinContent(3,2, h_mu_ratio5.at(5)->GetMean());
    MuAccUnc_NJets5->SetBinError(3,2, calcEnv(h_mu_ratio5.at(5), lower));
    MuAccUnc_NJets5->SetBinContent(2,3, h_mu_ratio5.at(6)->GetMean());
    MuAccUnc_NJets5->SetBinError(2,3, calcEnv(h_mu_ratio5.at(6), lower));
    MuAccUnc_NJets5->SetBinContent(3,3, h_mu_ratio5.at(7)->GetMean());
    MuAccUnc_NJets5->SetBinError(3,3, calcEnv(h_mu_ratio5.at(7), lower));
    MuAccUnc_NJets6->SetBinContent(1,1, h_mu_ratio6.at(0)->GetMean());
    MuAccUnc_NJets6->SetBinError(1,1, calcEnv(h_mu_ratio6.at(0), lower));
    MuAccUnc_NJets6->SetBinContent(2,1, h_mu_ratio6.at(1)->GetMean());
    MuAccUnc_NJets6->SetBinError(2,1, calcEnv(h_mu_ratio6.at(1), lower));
    MuAccUnc_NJets6->SetBinContent(3,1, h_mu_ratio6.at(2)->GetMean());
    MuAccUnc_NJets6->SetBinError(3,1, calcEnv(h_mu_ratio6.at(2), lower));
    MuAccUnc_NJets6->SetBinContent(1,2, h_mu_ratio6.at(3)->GetMean());
    MuAccUnc_NJets6->SetBinError(1,2, calcEnv(h_mu_ratio6.at(3), lower));
    MuAccUnc_NJets6->SetBinContent(2,2, h_mu_ratio6.at(4)->GetMean());
    MuAccUnc_NJets6->SetBinError(2,2, calcEnv(h_mu_ratio6.at(4), lower));
    MuAccUnc_NJets6->SetBinContent(3,2, h_mu_ratio6.at(5)->GetMean());
    MuAccUnc_NJets6->SetBinError(3,2, calcEnv(h_mu_ratio6.at(5), lower));
    MuAccUnc_NJets6->SetBinContent(2,3, h_mu_ratio6.at(6)->GetMean());
    MuAccUnc_NJets6->SetBinError(2,3, calcEnv(h_mu_ratio6.at(6), lower));
    MuAccUnc_NJets6->SetBinContent(3,3, h_mu_ratio6.at(7)->GetMean());
    MuAccUnc_NJets6->SetBinError(3,3, calcEnv(h_mu_ratio6.at(7), lower));
    MuAccUnc_NJets78->SetBinContent(1,1, h_mu_ratio78.at(0)->GetMean());
    MuAccUnc_NJets78->SetBinError(1,1, calcEnv(h_mu_ratio78.at(0), lower));
    MuAccUnc_NJets78->SetBinContent(2,1, h_mu_ratio78.at(1)->GetMean());
    MuAccUnc_NJets78->SetBinError(2,1, calcEnv(h_mu_ratio78.at(1), lower));
    MuAccUnc_NJets78->SetBinContent(3,1, h_mu_ratio78.at(2)->GetMean());
    MuAccUnc_NJets78->SetBinError(3,1, calcEnv(h_mu_ratio78.at(2), lower));
    MuAccUnc_NJets78->SetBinContent(1,2, h_mu_ratio78.at(3)->GetMean());
    MuAccUnc_NJets78->SetBinError(1,2, calcEnv(h_mu_ratio78.at(3), lower));
    MuAccUnc_NJets78->SetBinContent(2,2, h_mu_ratio78.at(4)->GetMean());
    MuAccUnc_NJets78->SetBinError(2,2, calcEnv(h_mu_ratio78.at(4), lower));
    MuAccUnc_NJets78->SetBinContent(3,2, h_mu_ratio78.at(5)->GetMean());
    MuAccUnc_NJets78->SetBinError(3,2, calcEnv(h_mu_ratio78.at(5), lower));
    MuAccUnc_NJets78->SetBinContent(2,3, h_mu_ratio78.at(6)->GetMean());
    MuAccUnc_NJets78->SetBinError(2,3, calcEnv(h_mu_ratio78.at(6), lower));
    MuAccUnc_NJets78->SetBinContent(3,3, h_mu_ratio78.at(7)->GetMean());
    MuAccUnc_NJets78->SetBinError(3,3, calcEnv(h_mu_ratio78.at(7), lower));
    MuAccUnc_NJets9Inf->SetBinContent(1,1, h_mu_ratio9Inf.at(0)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(1,1, calcEnv(h_mu_ratio9Inf.at(0), lower));
    MuAccUnc_NJets9Inf->SetBinContent(2,1, h_mu_ratio9Inf.at(1)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(2,1, calcEnv(h_mu_ratio9Inf.at(1), lower));
    MuAccUnc_NJets9Inf->SetBinContent(3,1, h_mu_ratio9Inf.at(2)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(3,1, calcEnv(h_mu_ratio9Inf.at(2), lower));
    MuAccUnc_NJets9Inf->SetBinContent(1,2, h_mu_ratio9Inf.at(3)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(1,2, calcEnv(h_mu_ratio9Inf.at(3), lower));
    MuAccUnc_NJets9Inf->SetBinContent(2,2, h_mu_ratio9Inf.at(4)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(2,2, calcEnv(h_mu_ratio9Inf.at(4), lower));
    MuAccUnc_NJets9Inf->SetBinContent(3,2, h_mu_ratio9Inf.at(5)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(3,2, calcEnv(h_mu_ratio9Inf.at(5), lower));
    MuAccUnc_NJets9Inf->SetBinContent(2,3, h_mu_ratio9Inf.at(6)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(2,3, calcEnv(h_mu_ratio9Inf.at(6), lower));
    MuAccUnc_NJets9Inf->SetBinContent(3,3, h_mu_ratio9Inf.at(7)->GetMean());
    MuAccUnc_NJets9Inf->SetBinError(3,3, calcEnv(h_mu_ratio9Inf.at(7), lower));
    MuAccUnc_NJets7Inf->SetBinContent(1,1, h_mu_ratio7Inf.at(0)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(1,1, calcEnv(h_mu_ratio7Inf.at(0), lower));
    MuAccUnc_NJets7Inf->SetBinContent(2,1, h_mu_ratio7Inf.at(1)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(2,1, calcEnv(h_mu_ratio7Inf.at(1), lower));
    MuAccUnc_NJets7Inf->SetBinContent(3,1, h_mu_ratio7Inf.at(2)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(3,1, calcEnv(h_mu_ratio7Inf.at(2), lower));
    MuAccUnc_NJets7Inf->SetBinContent(1,2, h_mu_ratio7Inf.at(3)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(1,2, calcEnv(h_mu_ratio7Inf.at(3), lower));
    MuAccUnc_NJets7Inf->SetBinContent(2,2, h_mu_ratio7Inf.at(4)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(2,2, calcEnv(h_mu_ratio7Inf.at(4), lower));
    MuAccUnc_NJets7Inf->SetBinContent(3,2, h_mu_ratio7Inf.at(5)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(3,2, calcEnv(h_mu_ratio7Inf.at(5), lower));
    MuAccUnc_NJets7Inf->SetBinContent(2,3, h_mu_ratio7Inf.at(6)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(2,3, calcEnv(h_mu_ratio7Inf.at(6), lower));
    MuAccUnc_NJets7Inf->SetBinContent(3,3, h_mu_ratio7Inf.at(7)->GetMean());
    MuAccUnc_NJets7Inf->SetBinError(3,3, calcEnv(h_mu_ratio7Inf.at(7), lower));

    ElecAccUnc_NJets2->SetBinContent(1,1, h_elec_ratio2.at(0)->GetMean());
    ElecAccUnc_NJets2->SetBinError(1,1, calcEnv(h_elec_ratio2.at(0), lower));
    ElecAccUnc_NJets2->SetBinContent(2,1, h_elec_ratio2.at(1)->GetMean());
    ElecAccUnc_NJets2->SetBinError(2,1, calcEnv(h_elec_ratio2.at(1), lower));
    ElecAccUnc_NJets2->SetBinContent(3,1, h_elec_ratio2.at(2)->GetMean());
    ElecAccUnc_NJets2->SetBinError(3,1, calcEnv(h_elec_ratio2.at(2), lower));
    ElecAccUnc_NJets2->SetBinContent(1,2, h_elec_ratio2.at(3)->GetMean());
    ElecAccUnc_NJets2->SetBinError(1,2, calcEnv(h_elec_ratio2.at(3), lower));
    ElecAccUnc_NJets2->SetBinContent(2,2, h_elec_ratio2.at(4)->GetMean());
    ElecAccUnc_NJets2->SetBinError(2,2, calcEnv(h_elec_ratio2.at(4), lower));
    ElecAccUnc_NJets2->SetBinContent(3,2, h_elec_ratio2.at(5)->GetMean());
    ElecAccUnc_NJets2->SetBinError(3,2, calcEnv(h_elec_ratio2.at(5), lower));
    ElecAccUnc_NJets2->SetBinContent(2,3, h_elec_ratio2.at(6)->GetMean());
    ElecAccUnc_NJets2->SetBinError(2,3, calcEnv(h_elec_ratio2.at(6), lower));
    ElecAccUnc_NJets2->SetBinContent(3,3, h_elec_ratio2.at(7)->GetMean());
    ElecAccUnc_NJets2->SetBinError(3,3, calcEnv(h_elec_ratio2.at(7), lower));
    ElecAccUnc_NJets3->SetBinContent(1,1, h_elec_ratio3.at(0)->GetMean());
    ElecAccUnc_NJets3->SetBinError(1,1, calcEnv(h_elec_ratio3.at(0), lower));
    ElecAccUnc_NJets3->SetBinContent(2,1, h_elec_ratio3.at(1)->GetMean());
    ElecAccUnc_NJets3->SetBinError(2,1, calcEnv(h_elec_ratio3.at(1), lower));
    ElecAccUnc_NJets3->SetBinContent(3,1, h_elec_ratio3.at(2)->GetMean());
    ElecAccUnc_NJets3->SetBinError(3,1, calcEnv(h_elec_ratio3.at(2), lower));
    ElecAccUnc_NJets3->SetBinContent(1,2, h_elec_ratio3.at(3)->GetMean());
    ElecAccUnc_NJets3->SetBinError(1,2, calcEnv(h_elec_ratio3.at(3), lower));
    ElecAccUnc_NJets3->SetBinContent(2,2, h_elec_ratio3.at(4)->GetMean());
    ElecAccUnc_NJets3->SetBinError(2,2, calcEnv(h_elec_ratio3.at(4), lower));
    ElecAccUnc_NJets3->SetBinContent(3,2, h_elec_ratio3.at(5)->GetMean());
    ElecAccUnc_NJets3->SetBinError(3,2, calcEnv(h_elec_ratio3.at(5), lower));
    ElecAccUnc_NJets3->SetBinContent(2,3, h_elec_ratio3.at(6)->GetMean());
    ElecAccUnc_NJets3->SetBinError(2,3, calcEnv(h_elec_ratio3.at(6), lower));
    ElecAccUnc_NJets3->SetBinContent(3,3, h_elec_ratio3.at(7)->GetMean());
    ElecAccUnc_NJets3->SetBinError(3,3, calcEnv(h_elec_ratio3.at(7), lower));
    ElecAccUnc_NJets4->SetBinContent(1,1, h_elec_ratio4.at(0)->GetMean());
    ElecAccUnc_NJets4->SetBinError(1,1, calcEnv(h_elec_ratio4.at(0), lower));
    ElecAccUnc_NJets4->SetBinContent(2,1, h_elec_ratio4.at(1)->GetMean());
    ElecAccUnc_NJets4->SetBinError(2,1, calcEnv(h_elec_ratio4.at(1), lower));
    ElecAccUnc_NJets4->SetBinContent(3,1, h_elec_ratio4.at(2)->GetMean());
    ElecAccUnc_NJets4->SetBinError(3,1, calcEnv(h_elec_ratio4.at(2), lower));
    ElecAccUnc_NJets4->SetBinContent(1,2, h_elec_ratio4.at(3)->GetMean());
    ElecAccUnc_NJets4->SetBinError(1,2, calcEnv(h_elec_ratio4.at(3), lower));
    ElecAccUnc_NJets4->SetBinContent(2,2, h_elec_ratio4.at(4)->GetMean());
    ElecAccUnc_NJets4->SetBinError(2,2, calcEnv(h_elec_ratio4.at(4), lower));
    ElecAccUnc_NJets4->SetBinContent(3,2, h_elec_ratio4.at(5)->GetMean());
    ElecAccUnc_NJets4->SetBinError(3,2, calcEnv(h_elec_ratio4.at(5), lower));
    ElecAccUnc_NJets4->SetBinContent(2,3, h_elec_ratio4.at(6)->GetMean());
    ElecAccUnc_NJets4->SetBinError(2,3, calcEnv(h_elec_ratio4.at(6), lower));
    ElecAccUnc_NJets4->SetBinContent(3,3, h_elec_ratio4.at(7)->GetMean());
    ElecAccUnc_NJets4->SetBinError(3,3, calcEnv(h_elec_ratio4.at(7), lower));
    ElecAccUnc_NJets5->SetBinContent(1,1, h_elec_ratio5.at(0)->GetMean());
    ElecAccUnc_NJets5->SetBinError(1,1, calcEnv(h_elec_ratio5.at(0), lower));
    ElecAccUnc_NJets5->SetBinContent(2,1, h_elec_ratio5.at(1)->GetMean());
    ElecAccUnc_NJets5->SetBinError(2,1, calcEnv(h_elec_ratio5.at(1), lower));
    ElecAccUnc_NJets5->SetBinContent(3,1, h_elec_ratio5.at(2)->GetMean());
    ElecAccUnc_NJets5->SetBinError(3,1, calcEnv(h_elec_ratio5.at(2), lower));
    ElecAccUnc_NJets5->SetBinContent(1,2, h_elec_ratio5.at(3)->GetMean());
    ElecAccUnc_NJets5->SetBinError(1,2, calcEnv(h_elec_ratio5.at(3), lower));
    ElecAccUnc_NJets5->SetBinContent(2,2, h_elec_ratio5.at(4)->GetMean());
    ElecAccUnc_NJets5->SetBinError(2,2, calcEnv(h_elec_ratio5.at(4), lower));
    ElecAccUnc_NJets5->SetBinContent(3,2, h_elec_ratio5.at(5)->GetMean());
    ElecAccUnc_NJets5->SetBinError(3,2, calcEnv(h_elec_ratio5.at(5), lower));
    ElecAccUnc_NJets5->SetBinContent(2,3, h_elec_ratio5.at(6)->GetMean());
    ElecAccUnc_NJets5->SetBinError(2,3, calcEnv(h_elec_ratio5.at(6), lower));
    ElecAccUnc_NJets5->SetBinContent(3,3, h_elec_ratio5.at(7)->GetMean());
    ElecAccUnc_NJets5->SetBinError(3,3, calcEnv(h_elec_ratio5.at(7), lower));
    ElecAccUnc_NJets6->SetBinContent(1,1, h_elec_ratio6.at(0)->GetMean());
    ElecAccUnc_NJets6->SetBinError(1,1, calcEnv(h_elec_ratio6.at(0), lower));
    ElecAccUnc_NJets6->SetBinContent(2,1, h_elec_ratio6.at(1)->GetMean());
    ElecAccUnc_NJets6->SetBinError(2,1, calcEnv(h_elec_ratio6.at(1), lower));
    ElecAccUnc_NJets6->SetBinContent(3,1, h_elec_ratio6.at(2)->GetMean());
    ElecAccUnc_NJets6->SetBinError(3,1, calcEnv(h_elec_ratio6.at(2), lower));
    ElecAccUnc_NJets6->SetBinContent(1,2, h_elec_ratio6.at(3)->GetMean());
    ElecAccUnc_NJets6->SetBinError(1,2, calcEnv(h_elec_ratio6.at(3), lower));
    ElecAccUnc_NJets6->SetBinContent(2,2, h_elec_ratio6.at(4)->GetMean());
    ElecAccUnc_NJets6->SetBinError(2,2, calcEnv(h_elec_ratio6.at(4), lower));
    ElecAccUnc_NJets6->SetBinContent(3,2, h_elec_ratio6.at(5)->GetMean());
    ElecAccUnc_NJets6->SetBinError(3,2, calcEnv(h_elec_ratio6.at(5), lower));
    ElecAccUnc_NJets6->SetBinContent(2,3, h_elec_ratio6.at(6)->GetMean());
    ElecAccUnc_NJets6->SetBinError(2,3, calcEnv(h_elec_ratio6.at(6), lower));
    ElecAccUnc_NJets6->SetBinContent(3,3, h_elec_ratio6.at(7)->GetMean());
    ElecAccUnc_NJets6->SetBinError(3,3, calcEnv(h_elec_ratio6.at(7), lower));
    ElecAccUnc_NJets78->SetBinContent(1,1, h_elec_ratio78.at(0)->GetMean());
    ElecAccUnc_NJets78->SetBinError(1,1, calcEnv(h_elec_ratio78.at(0), lower));
    ElecAccUnc_NJets78->SetBinContent(2,1, h_elec_ratio78.at(1)->GetMean());
    ElecAccUnc_NJets78->SetBinError(2,1, calcEnv(h_elec_ratio78.at(1), lower));
    ElecAccUnc_NJets78->SetBinContent(3,1, h_elec_ratio78.at(2)->GetMean());
    ElecAccUnc_NJets78->SetBinError(3,1, calcEnv(h_elec_ratio78.at(2), lower));
    ElecAccUnc_NJets78->SetBinContent(1,2, h_elec_ratio78.at(3)->GetMean());
    ElecAccUnc_NJets78->SetBinError(1,2, calcEnv(h_elec_ratio78.at(3), lower));
    ElecAccUnc_NJets78->SetBinContent(2,2, h_elec_ratio78.at(4)->GetMean());
    ElecAccUnc_NJets78->SetBinError(2,2, calcEnv(h_elec_ratio78.at(4), lower));
    ElecAccUnc_NJets78->SetBinContent(3,2, h_elec_ratio78.at(5)->GetMean());
    ElecAccUnc_NJets78->SetBinError(3,2, calcEnv(h_elec_ratio78.at(5), lower));
    ElecAccUnc_NJets78->SetBinContent(2,3, h_elec_ratio78.at(6)->GetMean());
    ElecAccUnc_NJets78->SetBinError(2,3, calcEnv(h_elec_ratio78.at(6), lower));
    ElecAccUnc_NJets78->SetBinContent(3,3, h_elec_ratio78.at(7)->GetMean());
    ElecAccUnc_NJets78->SetBinError(3,3, calcEnv(h_elec_ratio78.at(7), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(1,1, h_elec_ratio9Inf.at(0)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(1,1, calcEnv(h_elec_ratio9Inf.at(0), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(2,1, h_elec_ratio9Inf.at(1)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(2,1, calcEnv(h_elec_ratio9Inf.at(1), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(3,1, h_elec_ratio9Inf.at(2)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(3,1, calcEnv(h_elec_ratio9Inf.at(2), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(1,2, h_elec_ratio9Inf.at(3)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(1,2, calcEnv(h_elec_ratio9Inf.at(3), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(2,2, h_elec_ratio9Inf.at(4)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(2,2, calcEnv(h_elec_ratio9Inf.at(4), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(3,2, h_elec_ratio9Inf.at(5)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(3,2, calcEnv(h_elec_ratio9Inf.at(5), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(2,3, h_elec_ratio9Inf.at(6)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(2,3, calcEnv(h_elec_ratio9Inf.at(6), lower));
    ElecAccUnc_NJets9Inf->SetBinContent(3,3, h_elec_ratio9Inf.at(7)->GetMean());
    ElecAccUnc_NJets9Inf->SetBinError(3,3, calcEnv(h_elec_ratio9Inf.at(7), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(1,1, h_elec_ratio7Inf.at(0)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(1,1, calcEnv(h_elec_ratio7Inf.at(0), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(2,1, h_elec_ratio7Inf.at(1)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(2,1, calcEnv(h_elec_ratio7Inf.at(1), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(3,1, h_elec_ratio7Inf.at(2)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(3,1, calcEnv(h_elec_ratio7Inf.at(2), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(1,2, h_elec_ratio7Inf.at(3)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(1,2, calcEnv(h_elec_ratio7Inf.at(3), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(2,2, h_elec_ratio7Inf.at(4)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(2,2, calcEnv(h_elec_ratio7Inf.at(4), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(3,2, h_elec_ratio7Inf.at(5)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(3,2, calcEnv(h_elec_ratio7Inf.at(5), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(2,3, h_elec_ratio7Inf.at(6)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(2,3, calcEnv(h_elec_ratio7Inf.at(6), lower));
    ElecAccUnc_NJets7Inf->SetBinContent(3,3, h_elec_ratio7Inf.at(7)->GetMean());
    ElecAccUnc_NJets7Inf->SetBinError(3,3, calcEnv(h_elec_ratio7Inf.at(7), lower));

    MuAccUnc_Avg->SetBinContent(1,1, h_mu_ratioAvg.at(0)->GetMean());
    MuAccUnc_Avg->SetBinError(1,1, calcEnv(h_mu_ratioAvg.at(0), lower));
    MuAccUnc_Avg->SetBinContent(2,1, h_mu_ratioAvg.at(1)->GetMean());
    MuAccUnc_Avg->SetBinError(2,1, calcEnv(h_mu_ratioAvg.at(1), lower));
    MuAccUnc_Avg->SetBinContent(3,1, h_mu_ratioAvg.at(2)->GetMean());
    MuAccUnc_Avg->SetBinError(3,1, calcEnv(h_mu_ratioAvg.at(2), lower));
    MuAccUnc_Avg->SetBinContent(1,2, h_mu_ratioAvg.at(3)->GetMean());
    MuAccUnc_Avg->SetBinError(1,2, calcEnv(h_mu_ratioAvg.at(3), lower));
    MuAccUnc_Avg->SetBinContent(2,2, h_mu_ratioAvg.at(4)->GetMean());
    MuAccUnc_Avg->SetBinError(2,2, calcEnv(h_mu_ratioAvg.at(4), lower));
    MuAccUnc_Avg->SetBinContent(3,2, h_mu_ratioAvg.at(5)->GetMean());
    MuAccUnc_Avg->SetBinError(3,2, calcEnv(h_mu_ratioAvg.at(5), lower));
    MuAccUnc_Avg->SetBinContent(2,3, h_mu_ratioAvg.at(6)->GetMean());
    MuAccUnc_Avg->SetBinError(2,3, calcEnv(h_mu_ratioAvg.at(6), lower));
    MuAccUnc_Avg->SetBinContent(3,3, h_mu_ratioAvg.at(7)->GetMean());
    MuAccUnc_Avg->SetBinError(3,3, calcEnv(h_mu_ratioAvg.at(7), lower));
    ElecAccUnc_Avg->SetBinContent(1,1, h_elec_ratioAvg.at(0)->GetMean());
    ElecAccUnc_Avg->SetBinError(1,1, calcEnv(h_elec_ratioAvg.at(0), lower));
    ElecAccUnc_Avg->SetBinContent(2,1, h_elec_ratioAvg.at(1)->GetMean());
    ElecAccUnc_Avg->SetBinError(2,1, calcEnv(h_elec_ratioAvg.at(1), lower));
    ElecAccUnc_Avg->SetBinContent(3,1, h_elec_ratioAvg.at(2)->GetMean());
    ElecAccUnc_Avg->SetBinError(3,1, calcEnv(h_elec_ratioAvg.at(2), lower));
    ElecAccUnc_Avg->SetBinContent(1,2, h_elec_ratioAvg.at(3)->GetMean());
    ElecAccUnc_Avg->SetBinError(1,2, calcEnv(h_elec_ratioAvg.at(3), lower));
    ElecAccUnc_Avg->SetBinContent(2,2, h_elec_ratioAvg.at(4)->GetMean());
    ElecAccUnc_Avg->SetBinError(2,2, calcEnv(h_elec_ratioAvg.at(4), lower));
    ElecAccUnc_Avg->SetBinContent(3,2, h_elec_ratioAvg.at(5)->GetMean());
    ElecAccUnc_Avg->SetBinError(3,2, calcEnv(h_elec_ratioAvg.at(5), lower));
    ElecAccUnc_Avg->SetBinContent(2,3, h_elec_ratioAvg.at(6)->GetMean());
    ElecAccUnc_Avg->SetBinError(2,3, calcEnv(h_elec_ratioAvg.at(6), lower));
    ElecAccUnc_Avg->SetBinContent(3,3, h_elec_ratioAvg.at(7)->GetMean());
    ElecAccUnc_Avg->SetBinError(3,3, calcEnv(h_elec_ratioAvg.at(7), lower));

    MuAccUnc_NJets->SetBinContent(1, h_mu_ratioNJets.at(0)->GetMean());
    MuAccUnc_NJets->SetBinError(1, calcEnv(h_mu_ratioNJets.at(0), lower));
    MuAccUnc_NJets->SetBinContent(2, h_mu_ratioNJets.at(1)->GetMean());
    MuAccUnc_NJets->SetBinError(2, calcEnv(h_mu_ratioNJets.at(1), lower));
    MuAccUnc_NJets->SetBinContent(3, h_mu_ratioNJets.at(2)->GetMean());
    MuAccUnc_NJets->SetBinError(3, calcEnv(h_mu_ratioNJets.at(2), lower));
    MuAccUnc_NJets->SetBinContent(4, h_mu_ratioNJets.at(3)->GetMean());
    MuAccUnc_NJets->SetBinError(4, calcEnv(h_mu_ratioNJets.at(3), lower));
    MuAccUnc_NJets->SetBinContent(5, h_mu_ratioNJets.at(4)->GetMean());
    MuAccUnc_NJets->SetBinError(5, calcEnv(h_mu_ratioNJets.at(4), lower));
    MuAccUnc_NJets->SetBinContent(6, h_mu_ratioNJets.at(5)->GetMean());
    MuAccUnc_NJets->SetBinError(6, calcEnv(h_mu_ratioNJets.at(5), lower));
    MuAccUnc_NJets->SetBinContent(7, h_mu_ratioNJets.at(6)->GetMean());
    MuAccUnc_NJets->SetBinError(7, calcEnv(h_mu_ratioNJets.at(6), lower));

    ElecAccUnc_NJets->SetBinContent(1, h_elec_ratioNJets.at(0)->GetMean());
    ElecAccUnc_NJets->SetBinError(1, calcEnv(h_elec_ratioNJets.at(0), lower));
    ElecAccUnc_NJets->SetBinContent(2, h_elec_ratioNJets.at(1)->GetMean());
    ElecAccUnc_NJets->SetBinError(2, calcEnv(h_elec_ratioNJets.at(1), lower));
    ElecAccUnc_NJets->SetBinContent(3, h_elec_ratioNJets.at(2)->GetMean());
    ElecAccUnc_NJets->SetBinError(3, calcEnv(h_elec_ratioNJets.at(2), lower));
    ElecAccUnc_NJets->SetBinContent(4, h_elec_ratioNJets.at(3)->GetMean());
    ElecAccUnc_NJets->SetBinError(4, calcEnv(h_elec_ratioNJets.at(3), lower));
    ElecAccUnc_NJets->SetBinContent(5, h_elec_ratioNJets.at(4)->GetMean());
    ElecAccUnc_NJets->SetBinError(5, calcEnv(h_elec_ratioNJets.at(4), lower));
    ElecAccUnc_NJets->SetBinContent(6, h_elec_ratioNJets.at(5)->GetMean());
    ElecAccUnc_NJets->SetBinError(6, calcEnv(h_elec_ratioNJets.at(5), lower));
    ElecAccUnc_NJets->SetBinContent(7, h_elec_ratioNJets.at(6)->GetMean());
    ElecAccUnc_NJets->SetBinError(7, calcEnv(h_elec_ratioNJets.at(6), lower));

    if(showRatio)
    for(int xb = 1; xb <= 3; xb++){
		for(int yb = 1; yb <= 3; yb++){
			if(xb == 1 && yb == 3) continue;

			MuAccUnc_NJets2->SetBinContent(xb, yb, MuAccUnc_NJets2->GetBinError(xb, yb)/MuAccUnc_NJets2->GetBinContent(xb, yb));
			MuAccUnc_NJets3->SetBinContent(xb, yb, MuAccUnc_NJets3->GetBinError(xb, yb)/MuAccUnc_NJets3->GetBinContent(xb, yb));
			MuAccUnc_NJets4->SetBinContent(xb, yb, MuAccUnc_NJets4->GetBinError(xb, yb)/MuAccUnc_NJets4->GetBinContent(xb, yb));
			MuAccUnc_NJets5->SetBinContent(xb, yb, MuAccUnc_NJets5->GetBinError(xb, yb)/MuAccUnc_NJets5->GetBinContent(xb, yb));
			MuAccUnc_NJets6->SetBinContent(xb, yb, MuAccUnc_NJets6->GetBinError(xb, yb)/MuAccUnc_NJets6->GetBinContent(xb, yb));
			MuAccUnc_NJets78->SetBinContent(xb, yb, MuAccUnc_NJets78->GetBinError(xb, yb)/MuAccUnc_NJets78->GetBinContent(xb, yb));
			MuAccUnc_NJets9Inf->SetBinContent(xb, yb, MuAccUnc_NJets9Inf->GetBinError(xb, yb)/MuAccUnc_NJets9Inf->GetBinContent(xb, yb));
			MuAccUnc_NJets7Inf->SetBinContent(xb, yb, MuAccUnc_NJets7Inf->GetBinError(xb, yb)/MuAccUnc_NJets7Inf->GetBinContent(xb, yb));

			ElecAccUnc_NJets2->SetBinContent(xb, yb, ElecAccUnc_NJets2->GetBinError(xb, yb)/ElecAccUnc_NJets2->GetBinContent(xb, yb));
			ElecAccUnc_NJets3->SetBinContent(xb, yb, ElecAccUnc_NJets3->GetBinError(xb, yb)/ElecAccUnc_NJets3->GetBinContent(xb, yb));
			ElecAccUnc_NJets4->SetBinContent(xb, yb, ElecAccUnc_NJets4->GetBinError(xb, yb)/ElecAccUnc_NJets4->GetBinContent(xb, yb));
			ElecAccUnc_NJets5->SetBinContent(xb, yb, ElecAccUnc_NJets5->GetBinError(xb, yb)/ElecAccUnc_NJets5->GetBinContent(xb, yb));
			ElecAccUnc_NJets6->SetBinContent(xb, yb, ElecAccUnc_NJets6->GetBinError(xb, yb)/ElecAccUnc_NJets6->GetBinContent(xb, yb));
			ElecAccUnc_NJets78->SetBinContent(xb, yb, ElecAccUnc_NJets78->GetBinError(xb, yb)/ElecAccUnc_NJets78->GetBinContent(xb, yb));
			ElecAccUnc_NJets9Inf->SetBinContent(xb, yb, ElecAccUnc_NJets9Inf->GetBinError(xb, yb)/ElecAccUnc_NJets9Inf->GetBinContent(xb, yb));
			ElecAccUnc_NJets7Inf->SetBinContent(xb, yb, ElecAccUnc_NJets7Inf->GetBinError(xb, yb)/ElecAccUnc_NJets7Inf->GetBinContent(xb, yb));

			MuAccUnc_NJets2->SetBinError(xb, yb, 0);
			MuAccUnc_NJets3->SetBinError(xb, yb, 0);
			MuAccUnc_NJets4->SetBinError(xb, yb, 0);
			MuAccUnc_NJets5->SetBinError(xb, yb, 0);
			MuAccUnc_NJets6->SetBinError(xb, yb, 0);
			MuAccUnc_NJets78->SetBinError(xb, yb, 0);
			MuAccUnc_NJets9Inf->SetBinError(xb, yb, 0);
			MuAccUnc_NJets7Inf->SetBinError(xb, yb, 0);

			ElecAccUnc_NJets2->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets3->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets4->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets5->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets6->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets78->SetBinError(xb, yb, 0);
			ElecAccUnc_NJets9Inf->SetBinError(xb, yb, 0);			
			ElecAccUnc_NJets7Inf->SetBinError(xb, yb, 0);			

			MuAccUnc_Avg->SetBinContent(xb, yb, MuAccUnc_Avg->GetBinError(xb, yb)/MuAccUnc_Avg->GetBinContent(xb, yb));
			ElecAccUnc_Avg->SetBinContent(xb, yb, ElecAccUnc_Avg->GetBinError(xb, yb)/ElecAccUnc_Avg->GetBinContent(xb, yb));
			MuAccUnc_Avg->SetBinError(xb, yb, 0);
			ElecAccUnc_Avg->SetBinError(xb, yb, 0);
		}    	
    }

    if(showRatio)
    for(int xb = 1; xb <= 7; xb++){
    	MuAccUnc_NJets->SetBinContent(xb, MuAccUnc_NJets->GetBinError(xb)/MuAccUnc_NJets->GetBinContent(xb));
		ElecAccUnc_NJets->SetBinContent(xb, ElecAccUnc_NJets->GetBinError(xb)/ElecAccUnc_NJets->GetBinContent(xb));
		MuAccUnc_NJets->SetBinError(xb, 0);
		ElecAccUnc_NJets->SetBinError(xb, 0);
    }

    TFile *outPutFile = new TFile(outName,"RECREATE"); 
	outPutFile->cd();


    saveEff(MuAccUnc_NJets2, outPutFile);
    saveEff(MuAccUnc_NJets3, outPutFile);
    saveEff(MuAccUnc_NJets4, outPutFile);
    saveEff(MuAccUnc_NJets5, outPutFile);
    saveEff(MuAccUnc_NJets6, outPutFile);
    saveEff(MuAccUnc_NJets78, outPutFile);
    saveEff(MuAccUnc_NJets9Inf, outPutFile);
    saveEff(MuAccUnc_NJets7Inf, outPutFile);

    saveEff(ElecAccUnc_NJets2, outPutFile);
    saveEff(ElecAccUnc_NJets3, outPutFile);
    saveEff(ElecAccUnc_NJets4, outPutFile);
    saveEff(ElecAccUnc_NJets5, outPutFile);
    saveEff(ElecAccUnc_NJets6, outPutFile);
    saveEff(ElecAccUnc_NJets78, outPutFile);
    saveEff(ElecAccUnc_NJets9Inf, outPutFile);
    saveEff(ElecAccUnc_NJets7Inf, outPutFile);

    saveEff(MuAccUnc_Avg, outPutFile);
    saveEff(ElecAccUnc_Avg, outPutFile);

    saveEff(MuAccUnc_NJets, outPutFile);
    saveEff(ElecAccUnc_NJets, outPutFile);

	divideEff(MuAccControl_NJets2_pass, MuAccControl_NJets2_fail);
	divideEff(MuAccControl_NJets3_pass, MuAccControl_NJets3_fail);
	divideEff(MuAccControl_NJets4_pass, MuAccControl_NJets4_fail);
	divideEff(MuAccControl_NJets5_pass, MuAccControl_NJets5_fail);
	divideEff(MuAccControl_NJets6_pass, MuAccControl_NJets6_fail);
	divideEff(MuAccControl_NJets78_pass, MuAccControl_NJets78_fail);
	divideEff(MuAccControl_NJets9Inf_pass, MuAccControl_NJets9Inf_fail);
	divideEff(ElecAccControl_NJets2_pass, ElecAccControl_NJets2_fail);
	divideEff(ElecAccControl_NJets3_pass, ElecAccControl_NJets3_fail);
	divideEff(ElecAccControl_NJets4_pass, ElecAccControl_NJets4_fail);
	divideEff(ElecAccControl_NJets5_pass, ElecAccControl_NJets5_fail);
	divideEff(ElecAccControl_NJets6_pass, ElecAccControl_NJets6_fail);
	divideEff(ElecAccControl_NJets78_pass, ElecAccControl_NJets78_fail);
	divideEff(ElecAccControl_NJets9Inf_pass, ElecAccControl_NJets9Inf_fail);
}