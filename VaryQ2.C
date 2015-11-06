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


TH2D* saveEff(TH2D* h_ratio){
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
  	h_ratio->Draw("ColZ,Text,E");
  	c1->SaveAs(TString("AcceptanceQ2/")+name+TString(".pdf"));
  	delete c1;
  	gROOT->SetBatch(false);

  	return h_ratio;
}

TH2D* divideEff(TH2D* h_pass, TH2D* h_fail){
	TString name(h_pass->GetName());	
	name = name(0, name.Length()-5);

	TH2D* h_ratio = (TH2D*) h_pass->Clone(name);
	h_ratio->Add(h_fail);

	h_ratio->Divide(h_pass, h_ratio, 1, 1, "B");
	h_ratio->SetName(name);

	saveEff(h_ratio);

  	return h_ratio;
}

double calcUnc(TH1D* hist, bool lower){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(0, nBinGes+1);
    
    if(lower){
	    nBinTest = 0;
	    while(hist->Integral(0, nBinTest) / total < 0.16 && nBinTest < nBinGes){
	        nBinTest++;
	    }
	}else{
	    nBinTest = hist->GetNbinsX();
	    while(hist->Integral(nBinTest, nBinGes+1) / total < 0.16 && nBinTest > 0){
	        nBinTest--;
	    }
	}

	return std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());
}

double calcEnv(TH1D* hist, bool lower){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(0, nBinGes+1);
    
    if(lower){
	    nBinTest = 0;
	    while(hist->Integral(0, nBinTest) / total < 0.01 && nBinTest < nBinGes){
	        nBinTest++;
	    }
	}else{
	    nBinTest = hist->GetNbinsX();
	    while(hist->Integral(nBinTest, nBinGes+1) / total < 0.01 && nBinTest > 0){
	        nBinTest--;
	    }
	}

	return std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());
}


void VaryQ2(){

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

	const int accHT_ = 4;
	double AccHT_ [accHT_] = {500,800,1200,10000};
	const int accMHT2D_ = 3;
	double AccMHT2D_ [accMHT2D_] = {200,500,1900};
	TH2D* MuAccControl_NJets4_pass = new TH2D("MuAccControl_NJets4_pass","MuAccControl_NJets4_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJets4_fail = new TH2D("MuAccControl_NJets4_fail","MuAccControl_NJets4_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJets5_pass = new TH2D("MuAccControl_NJets5_pass","MuAccControl_NJets5_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJets5_fail = new TH2D("MuAccControl_NJets5_fail","MuAccControl_NJets5_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJets6_pass = new TH2D("MuAccControl_NJets6_pass","MuAccControl_NJets6_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJets6_fail = new TH2D("MuAccControl_NJets6_fail","MuAccControl_NJets6_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJetsHigh_pass = new TH2D("MuAccControl_NJetsHigh_pass"," MuAccControl_NJetsHigh_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccControl_NJetsHigh_fail = new TH2D("MuAccControl_NJetsHigh_fail"," MuAccControl_NJetsHigh_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);

	TH2D* MuAccUnc_NJets4 = new TH2D("MuAccUnc_NJets4_pass","MuAccUnc_NJets4_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccUnc_NJets5 = new TH2D("MuAccUnc_NJets5_pass","MuAccUnc_NJets5_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccUnc_NJets6 = new TH2D("MuAccUnc_NJets6_pass","MuAccUnc_NJets6_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* MuAccUnc_NJetsHigh = new TH2D("MuAccUnc_NJetsHigh_pass","MuAccUnc_NJetsHigh_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);

	TH2D* ElecAccControl_NJets4_pass = new TH2D("ElecAccControl_NJets4_pass","ElecAccControl_NJets4_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJets4_fail = new TH2D("ElecAccControl_NJets4_fail","ElecAccControl_NJets4_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJets5_pass = new TH2D("ElecAccControl_NJets5_pass","ElecAccControl_NJets5_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJets5_fail = new TH2D("ElecAccControl_NJets5_fail","ElecAccControl_NJets5_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJets6_pass = new TH2D("ElecAccControl_NJets6_pass","ElecAccControl_NJets6_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJets6_fail = new TH2D("ElecAccControl_NJets6_fail","ElecAccControl_NJets6_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJetsHigh_pass = new TH2D("ElecAccControl_NJetsHigh_pass"," ElecAccControl_NJetsHigh_pass",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
	TH2D* ElecAccControl_NJetsHigh_fail = new TH2D("ElecAccControl_NJetsHigh_fail"," ElecAccControl_NJetsHigh_fail",accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);

	Double_t mu_pass_central = 0;
	Double_t mu_fail_central = 0;

	std::vector<double> mu_pass(9, 0);
	std::vector<double> mu_fail(9, 0);

	std::vector<TH2D*> h_mu_pass4(9, 0);
	std::vector<TH2D*> h_mu_fail4(9, 0);
	std::vector<TH2D*> h_mu_pass5(9, 0);
	std::vector<TH2D*> h_mu_fail5(9, 0);
	std::vector<TH2D*> h_mu_pass6(9, 0);
	std::vector<TH2D*> h_mu_fail6(9, 0);
	std::vector<TH2D*> h_mu_passHigh(9, 0);
	std::vector<TH2D*> h_mu_failHigh(9, 0);

	for(int i = 0; i<h_mu_pass4.size(); ++i){
    			h_mu_pass4.at(i) = new TH2D(TString("mu_pass4_")+TString(std::to_string(i)),TString("mu_pass4_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_fail4.at(i) = new TH2D(TString("mu_fail4_")+TString(std::to_string(i)),TString("mu_fail4_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_pass5.at(i) = new TH2D(TString("mu_pass5_")+TString(std::to_string(i)),TString("mu_pass5_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_fail5.at(i) = new TH2D(TString("mu_fail5_")+TString(std::to_string(i)),TString("mu_fail5_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_pass6.at(i) = new TH2D(TString("mu_pass6_")+TString(std::to_string(i)),TString("mu_pass6_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_fail6.at(i) = new TH2D(TString("mu_fail6_")+TString(std::to_string(i)),TString("mu_fail6_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_passHigh.at(i) = new TH2D(TString("mu_passHigh_")+TString(std::to_string(i)),TString("mu_passHigh_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    			h_mu_failHigh.at(i) = new TH2D(TString("mu_failHigh_")+TString(std::to_string(i)),TString("mu_failHigh_")+TString(std::to_string(i)),accHT_-1,AccHT_, accMHT2D_-1,AccMHT2D_);
    }

	nentries = LostLeptonExpectation->GetEntries();
	nbytes = 0;
	for (Long64_t i=0; i<nentries;i++) {
    	nbytes += LostLeptonExpectation->GetEntry(i);
    	if(HT<500 || MHT<200 || NJets<3.5) continue;

    	if(Weight<0) continue;

/*    	std::cout<<ScaleWeights->size()<<std::endl;
    	for(int i = 0; i<ScaleWeights->size(); ++i){
    		std::cout<<ScaleWeights->at(i)<<std::endl;
    	}
*/
    	if(muAcc==2){
    		mu_pass_central += Weight;
	    	if(NJets > 3.5 && NJets < 4.5) MuAccControl_NJets4_pass->Fill(HT,MHT,Weight);
	  		else if(NJets > 4.5 && NJets < 5.5) MuAccControl_NJets5_pass->Fill(HT,MHT,Weight);
	  		else if(NJets > 5.5 && NJets < 6.5) MuAccControl_NJets6_pass->Fill(HT,MHT,Weight);
	  		else MuAccControl_NJetsHigh_pass->Fill(HT,MHT,Weight);

	  		for(int i = 0; i<ScaleWeights->size(); ++i){
    			mu_pass.at(i) += ScaleWeights->at(i)*Weight;
    			if(NJets > 3.5 && NJets < 4.5) h_mu_pass4.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else if(NJets > 4.5 && NJets < 5.5) h_mu_pass5.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else if(NJets > 5.5 && NJets < 6.5) h_mu_pass6.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else h_mu_passHigh.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
    		}
  		}else if(muAcc==0){
  			mu_fail_central +=Weight;
  			if(NJets > 3.5 && NJets < 4.5) MuAccControl_NJets4_fail->Fill(HT,MHT,Weight);
	  		else if(NJets > 4.5 && NJets < 5.5) MuAccControl_NJets5_fail->Fill(HT,MHT,Weight);
	  		else if(NJets > 5.5 && NJets < 6.5) MuAccControl_NJets6_fail->Fill(HT,MHT,Weight);
	  		else MuAccControl_NJetsHigh_fail->Fill(HT,MHT,Weight);

	  		for(int i = 0; i<ScaleWeights->size(); ++i){
    			mu_fail.at(i) += ScaleWeights->at(i)*Weight;
    			if(NJets > 3.5 && NJets < 4.5) h_mu_fail4.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else if(NJets > 4.5 && NJets < 5.5) h_mu_fail5.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else if(NJets > 5.5 && NJets < 6.5) h_mu_fail6.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
		  		else h_mu_failHigh.at(i)->Fill(HT,MHT,ScaleWeights->at(i)*Weight);
    		}
  		}

  		if(elecAcc==2){
	    	if(NJets > 3.5 && NJets < 4.5) ElecAccControl_NJets4_pass->Fill(HT,MHT,Weight);
	  		else if(NJets > 4.5 && NJets < 5.5) ElecAccControl_NJets5_pass->Fill(HT,MHT,Weight);
	  		else if(NJets > 5.5 && NJets < 6.5) ElecAccControl_NJets6_pass->Fill(HT,MHT,Weight);
	  		else ElecAccControl_NJetsHigh_pass->Fill(HT,MHT,Weight);
  		}else if(elecAcc==0){
  			if(NJets > 3.5 && NJets < 4.5) ElecAccControl_NJets4_fail->Fill(HT,MHT,Weight);
	  		else if(NJets > 4.5 && NJets < 5.5) ElecAccControl_NJets5_fail->Fill(HT,MHT,Weight);
	  		else if(NJets > 5.5 && NJets < 6.5) ElecAccControl_NJets6_fail->Fill(HT,MHT,Weight);
	  		else ElecAccControl_NJetsHigh_fail->Fill(HT,MHT,Weight);
  		}
	}

	std::cout<<"Center: "<<mu_pass_central/(mu_pass_central+mu_fail_central)<<std::endl;

	TH1D* h_mu_ratio = new TH1D("h_mu_ratio", "h_mu_ratio", 10000, 0., 1.);
	std::vector<TH1D*> h_mu_ratio4(6, 0);
	std::vector<TH1D*> h_mu_ratio5(6, 0);
	std::vector<TH1D*> h_mu_ratio6(6, 0);
	std::vector<TH1D*> h_mu_ratioHigh(6, 0);
	for(int i = 0; i<h_mu_ratio4.size(); ++i){
		h_mu_ratio4.at(i) = new TH1D(TString("h_mu_ratio4_")+TString(std::to_string(i)),TString("h_mu_ratio4_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio5.at(i) = new TH1D(TString("h_mu_ratio5_")+TString(std::to_string(i)),TString("h_mu_ratio5_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratio6.at(i) = new TH1D(TString("h_mu_ratio6_")+TString(std::to_string(i)),TString("h_mu_ratio6_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_mu_ratioHigh.at(i) = new TH1D(TString("h_mu_ratioHigh_")+TString(std::to_string(i)),TString("h_mu_ratioHigh_")+TString(std::to_string(i)), 10000, 0., 1.);
	}

	for(int i = 0; i<mu_pass.size(); ++i){
    	h_mu_ratio->Fill(mu_pass.at(i)/(mu_pass.at(i)+mu_fail.at(i)));
    	h_mu_ratio4.at(0)->Fill(h_mu_pass4.at(i)->GetBinContent(1,1)/(h_mu_pass4.at(i)->GetBinContent(1,1)+h_mu_fail4.at(i)->GetBinContent(1,1)));
		h_mu_ratio4.at(1)->Fill(h_mu_pass4.at(i)->GetBinContent(2,1)/(h_mu_pass4.at(i)->GetBinContent(2,1)+h_mu_fail4.at(i)->GetBinContent(2,1)));
		h_mu_ratio4.at(2)->Fill(h_mu_pass4.at(i)->GetBinContent(3,1)/(h_mu_pass4.at(i)->GetBinContent(3,1)+h_mu_fail4.at(i)->GetBinContent(3,1)));
		h_mu_ratio4.at(3)->Fill(h_mu_pass4.at(i)->GetBinContent(1,2)/(h_mu_pass4.at(i)->GetBinContent(1,2)+h_mu_fail4.at(i)->GetBinContent(1,2)));
		h_mu_ratio4.at(4)->Fill(h_mu_pass4.at(i)->GetBinContent(2,2)/(h_mu_pass4.at(i)->GetBinContent(2,2)+h_mu_fail4.at(i)->GetBinContent(2,2)));
		h_mu_ratio4.at(5)->Fill(h_mu_pass4.at(i)->GetBinContent(3,2)/(h_mu_pass4.at(i)->GetBinContent(3,2)+h_mu_fail4.at(i)->GetBinContent(3,2)));
		h_mu_ratio5.at(0)->Fill(h_mu_pass5.at(i)->GetBinContent(1,1)/(h_mu_pass5.at(i)->GetBinContent(1,1)+h_mu_fail5.at(i)->GetBinContent(1,1)));
		h_mu_ratio5.at(1)->Fill(h_mu_pass5.at(i)->GetBinContent(2,1)/(h_mu_pass5.at(i)->GetBinContent(2,1)+h_mu_fail5.at(i)->GetBinContent(2,1)));
		h_mu_ratio5.at(2)->Fill(h_mu_pass5.at(i)->GetBinContent(3,1)/(h_mu_pass5.at(i)->GetBinContent(3,1)+h_mu_fail5.at(i)->GetBinContent(3,1)));
		h_mu_ratio5.at(3)->Fill(h_mu_pass5.at(i)->GetBinContent(1,2)/(h_mu_pass5.at(i)->GetBinContent(1,2)+h_mu_fail5.at(i)->GetBinContent(1,2)));
		h_mu_ratio5.at(4)->Fill(h_mu_pass5.at(i)->GetBinContent(2,2)/(h_mu_pass5.at(i)->GetBinContent(2,2)+h_mu_fail5.at(i)->GetBinContent(2,2)));
		h_mu_ratio5.at(5)->Fill(h_mu_pass5.at(i)->GetBinContent(3,2)/(h_mu_pass5.at(i)->GetBinContent(3,2)+h_mu_fail5.at(i)->GetBinContent(3,2)));
		h_mu_ratio6.at(0)->Fill(h_mu_pass6.at(i)->GetBinContent(1,1)/(h_mu_pass6.at(i)->GetBinContent(1,1)+h_mu_fail6.at(i)->GetBinContent(1,1)));
		h_mu_ratio6.at(1)->Fill(h_mu_pass6.at(i)->GetBinContent(2,1)/(h_mu_pass6.at(i)->GetBinContent(2,1)+h_mu_fail6.at(i)->GetBinContent(2,1)));
		h_mu_ratio6.at(2)->Fill(h_mu_pass6.at(i)->GetBinContent(3,1)/(h_mu_pass6.at(i)->GetBinContent(3,1)+h_mu_fail6.at(i)->GetBinContent(3,1)));
		h_mu_ratio6.at(3)->Fill(h_mu_pass6.at(i)->GetBinContent(1,2)/(h_mu_pass6.at(i)->GetBinContent(1,2)+h_mu_fail6.at(i)->GetBinContent(1,2)));
		h_mu_ratio6.at(4)->Fill(h_mu_pass6.at(i)->GetBinContent(2,2)/(h_mu_pass6.at(i)->GetBinContent(2,2)+h_mu_fail6.at(i)->GetBinContent(2,2)));
		h_mu_ratio6.at(5)->Fill(h_mu_pass6.at(i)->GetBinContent(3,2)/(h_mu_pass6.at(i)->GetBinContent(3,2)+h_mu_fail6.at(i)->GetBinContent(3,2)));
		h_mu_ratioHigh.at(0)->Fill(h_mu_passHigh.at(i)->GetBinContent(1,1)/(h_mu_passHigh.at(i)->GetBinContent(1,1)+h_mu_failHigh.at(i)->GetBinContent(1,1)));
		h_mu_ratioHigh.at(1)->Fill(h_mu_passHigh.at(i)->GetBinContent(2,1)/(h_mu_passHigh.at(i)->GetBinContent(2,1)+h_mu_failHigh.at(i)->GetBinContent(2,1)));
		h_mu_ratioHigh.at(2)->Fill(h_mu_passHigh.at(i)->GetBinContent(3,1)/(h_mu_passHigh.at(i)->GetBinContent(3,1)+h_mu_failHigh.at(i)->GetBinContent(3,1)));
		h_mu_ratioHigh.at(3)->Fill(h_mu_passHigh.at(i)->GetBinContent(1,2)/(h_mu_passHigh.at(i)->GetBinContent(1,2)+h_mu_failHigh.at(i)->GetBinContent(1,2)));
		h_mu_ratioHigh.at(4)->Fill(h_mu_passHigh.at(i)->GetBinContent(2,2)/(h_mu_passHigh.at(i)->GetBinContent(2,2)+h_mu_failHigh.at(i)->GetBinContent(2,2)));
		h_mu_ratioHigh.at(5)->Fill(h_mu_passHigh.at(i)->GetBinContent(3,2)/(h_mu_passHigh.at(i)->GetBinContent(3,2)+h_mu_failHigh.at(i)->GetBinContent(3,2)));
    }

    std::cout<<"RMS: "<<h_mu_ratio->GetMean()<<"+-"<<h_mu_ratio->GetRMS()<<std::endl;
    std::cout<<"Assym: "<<h_mu_ratio->GetMean()<<"+"<<calcUnc(h_mu_ratio, false)<<"-"<<calcUnc(h_mu_ratio, true)<<std::endl;
    std::cout<<"Env: "<<h_mu_ratio->GetMean()<<"+"<<calcEnv(h_mu_ratio, false)<<"-"<<calcEnv(h_mu_ratio, true)<<std::endl;

    bool lower = false;
    MuAccUnc_NJets4->SetBinContent(1,1, h_mu_ratio4.at(0)->GetMean());
    MuAccUnc_NJets4->SetBinError(1,1, calcEnv(h_mu_ratio4.at(0),lower));
    MuAccUnc_NJets4->SetBinContent(2,1, h_mu_ratio4.at(1)->GetMean());
    MuAccUnc_NJets4->SetBinError(2,1, calcEnv(h_mu_ratio4.at(1),lower));
    MuAccUnc_NJets4->SetBinContent(3,1, h_mu_ratio4.at(2)->GetMean());
    MuAccUnc_NJets4->SetBinError(3,1, calcEnv(h_mu_ratio4.at(2),lower));
    MuAccUnc_NJets4->SetBinContent(1,2, h_mu_ratio4.at(3)->GetMean());
    MuAccUnc_NJets4->SetBinError(1,2, calcEnv(h_mu_ratio4.at(3),lower));
    MuAccUnc_NJets4->SetBinContent(2,2, h_mu_ratio4.at(4)->GetMean());
    MuAccUnc_NJets4->SetBinError(2,2, calcEnv(h_mu_ratio4.at(4),lower));
    MuAccUnc_NJets4->SetBinContent(3,2, h_mu_ratio4.at(5)->GetMean());
    MuAccUnc_NJets4->SetBinError(3,2, calcEnv(h_mu_ratio4.at(5),lower));
    MuAccUnc_NJets5->SetBinContent(1,1, h_mu_ratio5.at(0)->GetMean());
    MuAccUnc_NJets5->SetBinError(1,1, calcEnv(h_mu_ratio5.at(0),lower));
    MuAccUnc_NJets5->SetBinContent(2,1, h_mu_ratio5.at(1)->GetMean());
    MuAccUnc_NJets5->SetBinError(2,1, calcEnv(h_mu_ratio5.at(1),lower));
    MuAccUnc_NJets5->SetBinContent(3,1, h_mu_ratio5.at(2)->GetMean());
    MuAccUnc_NJets5->SetBinError(3,1, calcEnv(h_mu_ratio5.at(2),lower));
    MuAccUnc_NJets5->SetBinContent(1,2, h_mu_ratio5.at(3)->GetMean());
    MuAccUnc_NJets5->SetBinError(1,2, calcEnv(h_mu_ratio5.at(3),lower));
    MuAccUnc_NJets5->SetBinContent(2,2, h_mu_ratio5.at(4)->GetMean());
    MuAccUnc_NJets5->SetBinError(2,2, calcEnv(h_mu_ratio5.at(4),lower));
    MuAccUnc_NJets5->SetBinContent(3,2, h_mu_ratio5.at(5)->GetMean());
    MuAccUnc_NJets5->SetBinError(3,2, calcEnv(h_mu_ratio5.at(5),lower));
    MuAccUnc_NJets6->SetBinContent(1,1, h_mu_ratio6.at(0)->GetMean());
    MuAccUnc_NJets6->SetBinError(1,1, calcEnv(h_mu_ratio6.at(0),lower));
    MuAccUnc_NJets6->SetBinContent(2,1, h_mu_ratio6.at(1)->GetMean());
    MuAccUnc_NJets6->SetBinError(2,1, calcEnv(h_mu_ratio6.at(1),lower));
    MuAccUnc_NJets6->SetBinContent(3,1, h_mu_ratio6.at(2)->GetMean());
    MuAccUnc_NJets6->SetBinError(3,1, calcEnv(h_mu_ratio6.at(2),lower));
    MuAccUnc_NJets6->SetBinContent(1,2, h_mu_ratio6.at(3)->GetMean());
    MuAccUnc_NJets6->SetBinError(1,2, calcEnv(h_mu_ratio6.at(3),lower));
    MuAccUnc_NJets6->SetBinContent(2,2, h_mu_ratio6.at(4)->GetMean());
    MuAccUnc_NJets6->SetBinError(2,2, calcEnv(h_mu_ratio6.at(4),lower));
    MuAccUnc_NJets6->SetBinContent(3,2, h_mu_ratio6.at(5)->GetMean());
    MuAccUnc_NJets6->SetBinError(3,2, calcEnv(h_mu_ratio6.at(5),lower));
    MuAccUnc_NJetsHigh->SetBinContent(1,1, h_mu_ratioHigh.at(0)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(1,1, calcEnv(h_mu_ratioHigh.at(0),lower));
    MuAccUnc_NJetsHigh->SetBinContent(2,1, h_mu_ratioHigh.at(1)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(2,1, calcEnv(h_mu_ratioHigh.at(1),lower));
    MuAccUnc_NJetsHigh->SetBinContent(3,1, h_mu_ratioHigh.at(2)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(3,1, calcEnv(h_mu_ratioHigh.at(2),lower));
    MuAccUnc_NJetsHigh->SetBinContent(1,2, h_mu_ratioHigh.at(3)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(1,2, calcEnv(h_mu_ratioHigh.at(3),lower));
    MuAccUnc_NJetsHigh->SetBinContent(2,2, h_mu_ratioHigh.at(4)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(2,2, calcEnv(h_mu_ratioHigh.at(4),lower));
    MuAccUnc_NJetsHigh->SetBinContent(3,2, h_mu_ratioHigh.at(5)->GetMean());
    MuAccUnc_NJetsHigh->SetBinError(3,2, calcEnv(h_mu_ratioHigh.at(5),lower));

    saveEff(MuAccUnc_NJets4);
    saveEff(MuAccUnc_NJets5);
    saveEff(MuAccUnc_NJets6);
    saveEff(MuAccUnc_NJetsHigh);

	divideEff(MuAccControl_NJets4_pass, MuAccControl_NJets4_fail);
	divideEff(MuAccControl_NJets5_pass, MuAccControl_NJets5_fail);
	divideEff(MuAccControl_NJets6_pass, MuAccControl_NJets6_fail);
	divideEff(MuAccControl_NJetsHigh_pass, MuAccControl_NJetsHigh_fail);
	divideEff(ElecAccControl_NJets4_pass, ElecAccControl_NJets4_fail);
	divideEff(ElecAccControl_NJets5_pass, ElecAccControl_NJets5_fail);
	divideEff(ElecAccControl_NJets6_pass, ElecAccControl_NJets6_fail);
	divideEff(ElecAccControl_NJetsHigh_pass, ElecAccControl_NJetsHigh_fail);
}