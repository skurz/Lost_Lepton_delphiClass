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
  	c1->SaveAs(TString("AcceptanceUncertaintyNEW/")+name+TString(".pdf"));
  	delete c1;
  	gROOT->SetBatch(false);

  	if(outFile) h_ratio->Write();

  	return h_ratio;
}

TH1D* saveEff(TH1D* h_ratio, TFile *outFile){
	if(outFile) outFile->cd();

	h_ratio->GetXaxis()->SetTitle("SearchBin");
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
  	//gStyle->SetMarkerSize(2.0);
  	h_ratio->GetYaxis()->SetRangeUser(0.001, 1.05);
  	h_ratio->Draw("Text,E");
  	c1->SaveAs(TString("AcceptanceUncertaintyNEW/")+name+TString(".pdf"));
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

double calcUnc2(TH1D* hist, bool lower){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(1, nBinGes);
    
    if(lower){
	    nBinTest = 1;
	    while(hist->Integral(1, nBinTest) / total < 0.05 && nBinTest < nBinGes){
	        nBinTest++;
	    }
	}else{
	    nBinTest = hist->GetNbinsX();
	    while(hist->Integral(nBinTest, nBinGes) / total < 0.05 && nBinTest > 0){
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
	    nBinTest = 1;
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

double calcUnc2Max(TH1D* hist){
	int nBinGes = hist->GetNbinsX();
    int nBinTest;
    Double_t total = hist->Integral(1, nBinGes);
    
    nBinTest = 1;
    while(hist->Integral(1, nBinTest) / total < 0.05 && nBinTest < nBinGes){
        nBinTest++;
    }
    double lower = std::abs(hist->GetBinCenter(nBinTest)-hist->GetMean());

    nBinTest = hist->GetNbinsX();
    while(hist->Integral(nBinTest, nBinGes) / total < 0.05 && nBinTest > 0){
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


void VaryPDFsSearchBins(){
	TString outName("AcceptanceUncertaintyNEW/PDFuncertainty_up.root");
	// lower/upper uncertainty
	bool lower = false;

	bool showRatio = true;

	UShort_t        Bin;
	UShort_t        BinQCD;
	Double_t        Weight;
	Double_t        HT;
	Double_t        MHT;
	Int_t           NJets;
	Int_t           BTags;
    std::vector<double> *bTagProb=0;

	UShort_t		muAcc;
	UShort_t		elecAcc;

	std::vector<double>  *PDFweights=0;

	SearchBins* SearchBins_ = new SearchBins(true);

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
	LostLeptonExpectation->SetBranchStatus("PDFweights",1);
	LostLeptonExpectation->SetBranchStatus("bTagProb",1);

	LostLeptonExpectation->SetBranchAddress("HT",&HT);
	LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
	LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
	LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
	LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
	LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
	LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
	LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
	LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
	LostLeptonExpectation->SetBranchAddress("PDFweights",&PDFweights);
  	LostLeptonExpectation->SetBranchAddress("bTagProb",&bTagProb);

	TH1::SetDefaultSumw2();

	TH1D* MuAccControl_SearchBins_pass = new TH1D("MuAccControl_SearchBins_pass","MuAccControl_SearchBins_pass", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
	TH1D* MuAccControl_SearchBins_fail = new TH1D("MuAccControl_SearchBins_fail","MuAccControl_SearchBins_fail", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

	TH1D* MuAccUnc_SearchBins = new TH1D("MuAccPDFUnc_SearchBins","MuAccPDFUnc_SearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

	TH1D* ElecAccControl_SearchBins_pass = new TH1D("ElecAccControl_SearchBins_pass","ElecAccControl_SearchBins_pass", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
	TH1D* ElecAccControl_SearchBins_fail = new TH1D("ElecAccControl_SearchBins_fail","ElecAccControl_SearchBins_fail", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

	TH1D* ElecAccUnc_SearchBins = new TH1D("ElecAccPDFUnc_SearchBins","ElecAccPDFUnc_SearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

	Double_t mu_pass_central = 0;
	Double_t mu_fail_central = 0;

	std::vector<double> mu_pass(100, 0);
	std::vector<double> mu_fail(100, 0);

	std::vector<TH1D*> h_mu_passSB(100, 0);
	std::vector<TH1D*> h_mu_failSB(100, 0);

	Double_t elec_pass_central = 0;
	Double_t elec_fail_central = 0;

	std::vector<double> elec_pass(100, 0);
	std::vector<double> elec_fail(100, 0);

	std::vector<TH1D*> h_elec_passSB(100, 0);
	std::vector<TH1D*> h_elec_failSB(100, 0);


	for(unsigned i = 0; i<h_mu_passSB.size(); ++i){
		h_mu_passSB.at(i) = new TH1D(TString("mu_passSB_")+TString(std::to_string(i)),TString("mu_passSB_")+TString(std::to_string(i)), SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
		h_mu_failSB.at(i) = new TH1D(TString("mu_failSB_")+TString(std::to_string(i)),TString("mu_failSB_")+TString(std::to_string(i)), SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

		h_elec_passSB.at(i) = new TH1D(TString("elec_passSB_")+TString(std::to_string(i)),TString("elec_passSB_")+TString(std::to_string(i)), SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
		h_elec_failSB.at(i) = new TH1D(TString("elec_failSB_")+TString(std::to_string(i)),TString("elec_failSB_")+TString(std::to_string(i)), SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
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
    	for(unsigned i = 1; i<PDFweights->size(); ++i){
    		if(std::isnan(PDFweights->at(i))){
    			nanEvts++;
    			skipEvent = true;
    			break;
    		}
    		else if(std::abs(PDFweights->at(i)) > 100){
    			hugeEvts++;
    			skipEvent = true;
    			break;
    		}
    	}
    	if(skipEvent) continue;

    	int nLoops = NJets < 2.5 ? 3 : 4;
  		for(int btag = 0; btag < nLoops; btag++){
		    BTags = btag;
		    BinQCD = SearchBins_->GetBinNumber(HT,MHT,NJets,btag);
		    double WeightBTagProb = Weight * bTagProb->at(btag);

		    if(muAcc==2){
    			mu_pass_central += WeightBTagProb;
    			MuAccControl_SearchBins_pass->Fill(BinQCD,WeightBTagProb);
    			for(unsigned i = 1; i<PDFweights->size(); ++i){
    				mu_pass.at(i-1) += std::abs(PDFweights->at(i)*WeightBTagProb);
    				h_mu_passSB.at(i-1)->Fill(BinQCD,std::abs(PDFweights->at(i)*WeightBTagProb));
    			}
    		}else if(muAcc==0){
    			mu_fail_central += WeightBTagProb;
    			MuAccControl_SearchBins_fail->Fill(BinQCD,WeightBTagProb);
    			for(unsigned i = 1; i<PDFweights->size(); ++i){
    				mu_fail.at(i-1) += std::abs(PDFweights->at(i)*WeightBTagProb);
    				h_mu_failSB.at(i-1)->Fill(BinQCD,std::abs(PDFweights->at(i)*WeightBTagProb));
    			}
    		}

    		if(elecAcc==2){
    			elec_pass_central += WeightBTagProb;
    			ElecAccControl_SearchBins_pass->Fill(BinQCD,WeightBTagProb);
    			for(unsigned i = 1; i<PDFweights->size(); ++i){
    				elec_pass.at(i-1) += std::abs(PDFweights->at(i)*WeightBTagProb);
    				h_elec_passSB.at(i-1)->Fill(BinQCD,std::abs(PDFweights->at(i)*WeightBTagProb));
    			}
    		}else if(elecAcc==0){
    			elec_fail_central += WeightBTagProb;
    			ElecAccControl_SearchBins_fail->Fill(BinQCD,WeightBTagProb);
    			for(unsigned i = 1; i<PDFweights->size(); ++i){
    				elec_fail.at(i-1) += std::abs(PDFweights->at(i)*WeightBTagProb);
    				h_elec_failSB.at(i-1)->Fill(BinQCD,std::abs(PDFweights->at(i)*WeightBTagProb));
    			}
    		}

    	}
   	}


	std::cout << "Invalid weights: " << nanEvts << std::endl;
	std::cout << "Huge weights: " << hugeEvts << std::endl;
	std::cout << "Total Evts: " << allEvts << std::endl;


	TH1D* h_mu_ratio = new TH1D("h_mu_ratio", "h_mu_ratio", 10000, 0., 1.);
	std::vector<TH1D*> h_mu_ratioSB(SearchBins_->GetNbins(), 0);

	TH1D* h_elec_ratio = new TH1D("h_elec_ratio", "h_elec_ratio", 10000, 0., 1.);
	std::vector<TH1D*> h_elec_ratioSB(SearchBins_->GetNbins(), 0);

	for(unsigned i = 0; i<h_mu_ratioSB.size(); ++i){
		h_mu_ratioSB.at(i) = new TH1D(TString("h_mu_ratioSB_")+TString(std::to_string(i)),TString("h_mu_ratioSB_")+TString(std::to_string(i)), 10000, 0., 1.);
		h_elec_ratioSB.at(i) = new TH1D(TString("h_elec_ratioSB_")+TString(std::to_string(i)),TString("h_elec_ratioSB_")+TString(std::to_string(i)), 10000, 0., 1.);
	}

	for(unsigned i = 0; i<mu_pass.size(); ++i){
    	h_mu_ratio->Fill(mu_pass.at(i)/(mu_pass.at(i)+mu_fail.at(i)));
		h_elec_ratio->Fill(elec_pass.at(i)/(elec_pass.at(i)+elec_fail.at(i)));

		for(unsigned bin = 1; bin <= SearchBins_->GetNbins(); bin++){
    		h_mu_ratioSB.at(bin-1)->Fill(h_mu_passSB.at(i)->GetBinContent(bin)/(h_mu_passSB.at(i)->GetBinContent(bin)+h_mu_failSB.at(i)->GetBinContent(bin)));
    		h_elec_ratioSB.at(bin-1)->Fill(h_elec_passSB.at(i)->GetBinContent(bin)/(h_elec_passSB.at(i)->GetBinContent(bin)+h_elec_failSB.at(i)->GetBinContent(bin)));
		}
    }
/*
  	TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  	c1->Divide(2,1);
  	c1->cd(1);
  	c1->SetLogx();
  	c1->SetLogy();
    h_mu_ratio7Inf.at(0)->Draw("");
    std::cout<<h_mu_ratio7Inf.at(0)->GetMean()<<"+-"<<calcUnc(h_mu_ratio7Inf.at(0),false)<<std::endl;
  	c1->cd(2);
  	c1->SetLogx();
  	c1->SetLogy();
    h_mu_ratio7Inf.at(1)->Draw("");
    std::cout<<h_mu_ratio7Inf.at(1)->GetMean()<<"+-"<<calcUnc(h_mu_ratio7Inf.at(1),false)<<std::endl;
*/
	std::cout<<"Mu: Center: "<<mu_pass_central/(mu_pass_central+mu_fail_central)<<std::endl;
    std::cout<<"Mu: RMS: "<<h_mu_ratio->GetMean()<<"+-"<<h_mu_ratio->GetRMS()<<std::endl;
    std::cout<<"Mu: Assym: "<<h_mu_ratio->GetMean()<<"+"<<calcUnc(h_mu_ratio, false)<<"-"<<calcUnc(h_mu_ratio, true)<<std::endl;
    std::cout<<"Mu: Env: "<<h_mu_ratio->GetMean()<<"+"<<calcEnv(h_mu_ratio, false)<<"-"<<calcEnv(h_mu_ratio, true)<<std::endl;
    std::cout<<"Elec: Center: "<<elec_pass_central/(elec_pass_central+elec_fail_central)<<std::endl;
    std::cout<<"Elec: RMS: "<<h_elec_ratio->GetMean()<<"+-"<<h_elec_ratio->GetRMS()<<std::endl;
    std::cout<<"Elec: Assym: "<<h_elec_ratio->GetMean()<<"+"<<calcUnc(h_elec_ratio, false)<<"-"<<calcUnc(h_elec_ratio, true)<<std::endl;
    std::cout<<"Elec: Env: "<<h_elec_ratio->GetMean()<<"+"<<calcEnv(h_elec_ratio, false)<<"-"<<calcEnv(h_elec_ratio, true)<<std::endl;


    for(unsigned bin = 1; bin <= SearchBins_->GetNbins(); bin++){
    	MuAccUnc_SearchBins->SetBinContent(bin, h_mu_ratioSB.at(bin-1)->GetMean());
    	MuAccUnc_SearchBins->SetBinError(bin, calcUnc2(h_mu_ratioSB.at(bin-1), lower));

    	ElecAccUnc_SearchBins->SetBinContent(bin, h_elec_ratioSB.at(bin-1)->GetMean());
    	ElecAccUnc_SearchBins->SetBinError(bin, calcUnc2(h_elec_ratioSB.at(bin-1), lower));
	}


    if(showRatio)
    for(unsigned bin = 1; bin <= SearchBins_->GetNbins(); bin++){
			MuAccUnc_SearchBins->SetBinContent(bin, MuAccUnc_SearchBins->GetBinError(bin)/MuAccUnc_SearchBins->GetBinContent(bin));
			ElecAccUnc_SearchBins->SetBinContent(bin, ElecAccUnc_SearchBins->GetBinError(bin)/ElecAccUnc_SearchBins->GetBinContent(bin));

			MuAccUnc_SearchBins->SetBinError(bin, 0);
			ElecAccUnc_SearchBins->SetBinError(bin, 0);  	
    }

    TFile *outPutFile = new TFile(outName,"RECREATE"); 
	outPutFile->cd();

    saveEff(MuAccUnc_SearchBins, outPutFile);
    saveEff(ElecAccUnc_SearchBins, outPutFile);

	divideEff(MuAccControl_SearchBins_pass, MuAccControl_SearchBins_fail);
	divideEff(ElecAccControl_SearchBins_pass, ElecAccControl_SearchBins_fail);

}