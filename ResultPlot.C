#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <vector>

TH1F* ratioCalculator(TH1F* passTH1, TH1F* failTH1)
{
	passTH1->Sumw2();
	TH1F *sum = (TH1F*)passTH1->Clone();
	failTH1->Sumw2();
	
	sum->Add(failTH1);
	passTH1->Divide(passTH1,sum,1,1,"B");
	return passTH1;
}

void SaveClosure(TH1F* prediction, TH1F* expectation, TDirectory* Folder) // prediction durch expectation
{
	TH1F* Closure = (TH1F*) prediction->Clone();
	Closure->Divide(prediction,expectation,1,1,"B");
	TString title = prediction->GetTitle();
	title +="_closure";
// 	title = "#mu & e Control-Sample Ratio in Search Bins; Search bins; #mu / e CS";
	Closure->SetTitle(title);
 	title = prediction->GetName();
 	title+="_closure";
	Closure->SetName(title);
	Folder->cd();
	Closure->Write();
}


class Bin
{
public:
	Bin(){}
	Bin(double HTmin, double HTmax, double MHTmin, double MHTmax, int NJetsmin, int NJetsmax, int BTagsmin, int BTagsmax)
	{
		HTmin_=HTmin;
		HTmax_=HTmax;
		MHTmin_=MHTmin;
		MHTmax_=MHTmax;
		NJetsmin_=NJetsmin;
		NJetsmax_=NJetsmax;
		BTagsmin_=BTagsmin;
		BTagsmax_=BTagsmax;
	}
	double HTmin_, HTmax_, MHTmin_, MHTmax_;
	int NJetsmin_, NJetsmax_, BTagsmin_, BTagsmax_;
	~Bin(){}
private:
};

class SearchBins
{
public:
	SearchBins();
	unsigned int GetBinNumber(double HT, double MHT, int NJets, int BTags);
	Bin* GetSearchBin(int i);
	
	~SearchBins(){}
protected:
	std::vector<Bin> bins_;
};

class SearchBinEventCount : public SearchBins
{
public:
	SearchBinEventCount(){}
	SearchBinEventCount(const char*);
	void Fill(double HT, double MHT, int NJets, int BTags, double Weight);
	void saveResults(TDirectory* MainDirectory);
	TH1F* getFullTH1F(){return fullTH1F_;}
	~SearchBinEventCount(){}
private:
	TH1F* fullTH1F_;
	std::vector<TH1F*> splitTH1F_;
	unsigned int splitAfter_;
	const char* name_;
};

void ResultPlot()
{
	//Reset ROOT and connect tree file
	gROOT->Reset();
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Expectation.root");
	if (!f) {
		f = new TFile("Expectation.root");
	}
	// output tree
	TFile *outPutFile = new TFile("Closure.root","RECREATE"); 
	outPutFile->cd();
	TTree* OutPutTreeExp_ = new TTree("ResultExp","Result Lost-Lepton Tree for plotting tool");
	TTree* OutPutTreePre_ = new TTree("ResultPre","Result Lost-Lepton Tree for plotting tool");
	UShort_t Bin=0;
	Float_t Weight_=0, PredictionWeight_=0; 
	
	OutPutTreeExp_->Branch("Weight", &Weight_, "Weight/F");
	OutPutTreePre_->Branch("Weight", &Weight_, "Weight/F");
	OutPutTreePre_->Branch("totalWeightDiLep", &PredictionWeight_, "totalWeightDiLep/F");
	OutPutTreeExp_->Branch("Bin",&Bin,"Bin/s");
	OutPutTreePre_->Branch("Bin",&Bin,"Bin/s");
	//
	UShort_t muAcc_=0, muIso_=0, muReco_=0;
	OutPutTreeExp_->Branch("muAcc",&muAcc_,"muAcc/s");
	OutPutTreeExp_->Branch("muReco",&muReco_,"muReco/s");
	OutPutTreeExp_->Branch("muIso",&muIso_,"muIso/s");
	
	UShort_t elecAcc_=0, elecIso_=0, elecReco_=0;
	OutPutTreeExp_->Branch("elecAcc",&elecAcc_,"elecAcc/s");
	OutPutTreeExp_->Branch("elecReco",&elecReco_,"elecReco/s");
	OutPutTreeExp_->Branch("elecIso",&elecIso_,"elecIso/s");
	//
	Float_t muIsoWeight_=0, muRecoWeight_=0, muAccWeight_=0;
	OutPutTreePre_->Branch("muIsoWeight", &muIsoWeight_, "muIsoWeight/F");
	OutPutTreePre_->Branch("muRecoWeight", &muRecoWeight_, "muRecoWeight/F");
	OutPutTreePre_->Branch("muAccWeight", &muAccWeight_, "muAccWeight/F");
	
	Float_t elecIsoWeight_=0, elecRecoWeight_=0, elecAccWeight_=0;
	OutPutTreePre_->Branch("elecIsoWeight", &elecIsoWeight_, "elecIsoWeight/F");
	OutPutTreePre_->Branch("elecRecoWeight", &elecRecoWeight_, "elecRecoWeight/F");
	OutPutTreePre_->Branch("elecAccWeight", &elecAccWeight_, "elecAccWeight/F");
	
	UShort_t selectedIDIsoMuonsNum_=0, selectedIDIsoElectronsNum_=0;
	OutPutTreePre_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum_,"selectedIDIsoMuonsNum/s");
	OutPutTreePre_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum_,"selectedIDIsoElectronsNum/s");
	
	TTree* LostLeptonExpectation = (TTree*) f->Get("LostLeptonExpectation");

	
	SearchBinEventCount * ControlSampleMu_ = new SearchBinEventCount("ControlSampleMu");
	SearchBinEventCount * ControlSampleElec_ = new SearchBinEventCount("ControlSampleElec");
	
	SearchBinEventCount * totalExpectation_ = new SearchBinEventCount("TotalLostLeptonExpecation");
	SearchBinEventCount * totalPrediction_ = new SearchBinEventCount("TotalLostLeptonPrediction");
	SearchBinEventCount * totalPredictionMu_ = new SearchBinEventCount("TotalLostLeptonPredictionMu");
	SearchBinEventCount * totalPredictionElec_ = new SearchBinEventCount("TotalLostLeptonPredictionElec");
	
	SearchBinEventCount * totalExpectationIsoTrackReduction_ = new SearchBinEventCount("TotalLostLeptonExpecationIsoTrackReduction");
	SearchBinEventCount * totalPredictionIsoTrackReduction_ = new SearchBinEventCount("TotalLostLeptonPredictionIsoTrackReduction");
	SearchBinEventCount * totalPredictionMuIsoTrackReduction_ = new SearchBinEventCount("TotalLostLeptonPredictionMuIsoTrackReduction");
	SearchBinEventCount * totalPredictionElecIsoTrackReduction_ = new SearchBinEventCount("TotalLostLeptonPredictionElecIsoTrackReduction");
	
	// separted closure
	SearchBinEventCount * totalExpectationMuAcc_ = new SearchBinEventCount("TotalLostLeptonExpecationMuAcc");
	SearchBinEventCount * totalPredictionMuCSMuAcc_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSMuAcc");
	SearchBinEventCount * totalPredictionElecCSMuAcc_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSMuAcc");
	
	SearchBinEventCount * totalExpectationMuReco_ = new SearchBinEventCount("TotalLostLeptonExpecationMuReco");
	SearchBinEventCount * totalPredictionMuCSMuReco_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSMuReco");
	SearchBinEventCount * totalPredictionElecCSMuReco_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSMuReco");
	
	SearchBinEventCount * totalExpectationMuIso_ = new SearchBinEventCount("TotalLostLeptonExpecationMuIso");
	SearchBinEventCount * totalPredictionMuCSMuIso_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSMuIso");
	SearchBinEventCount * totalPredictionElecCSMuIso_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSMuIso");
	
	
	
	SearchBinEventCount * totalExpectationElecAcc_ = new SearchBinEventCount("TotalLostLeptonExpecationElecAcc");
	SearchBinEventCount * totalPredictionMuCSElecAcc_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSElecAcc");
	SearchBinEventCount * totalPredictionElecCSElecAcc_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSElecAcc");
	
	SearchBinEventCount * totalExpectationElecReco_ = new SearchBinEventCount("TotalLostLeptonExpecationElecReco");
	SearchBinEventCount * totalPredictionMuCSElecReco_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSElecReco");
	SearchBinEventCount * totalPredictionElecCSElecReco_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSElecReco");
	
	SearchBinEventCount * totalExpectationElecIso_ = new SearchBinEventCount("TotalLostLeptonExpecationElecIso");
	SearchBinEventCount * totalPredictionMuCSElecIso_ = new SearchBinEventCount("TotalLostLeptonPredictionMuCSElecIso");
	SearchBinEventCount * totalPredictionElecCSElecIso_ = new SearchBinEventCount("TotalLostLeptonPredictionElecCSElecIso");
	
	double totalExp=0, totalPre=0;
	double totalExpError=0, totalPreError=0;
	double totalPreMu=0, totalPreMuError=0;
	double totalPreElec=0, totalPreElecError=0;
	double totalExpIsoTrack=0, totalExpIsoTrackError=0;

	double totalPreIsoTrack=0, totalPreIsoTrackError=0;
	double totalPreIsoTrackMu=0, totalPreIsoTrackMuError=0;
	double totalPreIsoTrackElec=0, totalPreIsoTrackElecError=0;
	
	double totalExpMuAcc=0, totalExpMuReco=0, totalExpMuIso=0;
	
	double totalPreMuAcc=0, totalPreMuReco=0, totalPreMuIso=0;
	double totalPreMuMuAcc=0, totalPreMuMuReco=0, totalPreMuMuIso=0;
	double totalPreMuElecAcc=0, totalPreMuElecReco=0, totalPreMuElecIso=0;
	
	
	double totalExpElecAcc=0, totalExpElecReco=0, totalExpElecIso=0;
	
	double totalPreElecAcc=0, totalPreElecReco=0, totalPreElecIso=0;
	double totalPreElecMuAcc=0, totalPreElecMuReco=0, totalPreElecMuIso=0;
	double totalPreElecElecAcc=0, totalPreElecElecReco=0, totalPreElecElecIso=0;
	
	//Declaration of leaves types
	Float_t         HT;
	Float_t         MHT;
	UShort_t        NJets;
	UShort_t        BTags;
	Float_t         Weight;
	
	UShort_t        Expectation;
	UShort_t        muAcc;
	UShort_t        muReco;
	UShort_t        muIso;
	UShort_t        elecAcc;
	UShort_t        elecReco;
	UShort_t        elecIso;
	UShort_t        IsolatedTracksNum;
	UShort_t        ExpectationDiLep;
	UShort_t        ExpectationReductionIsoTrack;
	
	// Set branch addresses.
	LostLeptonExpectation->SetBranchAddress("HT",&HT);
	LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
	LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
	LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
	LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
	
	LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
	LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
	LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
	LostLeptonExpectation->SetBranchAddress("muReco",&muReco);
	LostLeptonExpectation->SetBranchAddress("muIso",&muIso);
	
	LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
	LostLeptonExpectation->SetBranchAddress("elecReco",&elecReco);
	LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);
	
	LostLeptonExpectation->SetBranchAddress("IsolatedTracksNum",&IsolatedTracksNum);
	LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);
	
	
	Long64_t nentries = LostLeptonExpectation->GetEntries();
	
	SearchBins *SearchBins_ = new SearchBins();
	
	Long64_t nbytes = 0;
	   for (Long64_t i=0; i<nentries;i++) {
		      nbytes += LostLeptonExpectation->GetEntry(i);
					// total expectation
					if(NJets<3.6) continue;
					if(Expectation==1 && NJets>3.1)
					{
						totalExpectation_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExp+=Weight;
						totalExpError+= Weight*Weight;
						Bin = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
						Weight_=Weight;
						muAcc_=muAcc; muReco_=muReco; muIso_=muIso; elecAcc_=elecAcc; elecReco_=elecReco; elecIso_=elecIso;
						OutPutTreeExp_->Fill();
					}
					if(Expectation==1 && ExpectationReductionIsoTrack==0 && NJets>3.1)
					{
						totalExpectationIsoTrackReduction_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpIsoTrack+=Weight;
						totalExpIsoTrackError+= Weight*Weight;
					}
					if(muAcc==0)
					{
						totalExpectationMuAcc_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpMuAcc+=Weight;
					}
					if(muReco==0)
					{
						totalExpectationMuReco_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpMuReco+=Weight;
					}
					if(muIso==0)
					{
						totalExpectationMuIso_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpMuIso+=Weight;
					}
					
					if(elecAcc==0)
					{
						totalExpectationElecAcc_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpElecAcc+=Weight;
					}
					if(elecReco==0)
					{
						totalExpectationElecReco_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpElecReco+=Weight;
					}
					if(elecIso==0)
					{
						totalExpectationElecIso_->Fill(HT,MHT,NJets,BTags,Weight);
						totalExpElecIso+=Weight;
					}
	   }
	   
	  // loop on prediction
	gROOT->Reset();
	TFile *f1 = (TFile*)gROOT->GetListOfFiles()->FindObject("Prediction.root");
	if (!f1) {
		f1 = new TFile("Prediction.root");
	}
	TTree* LostLeptonPrediction = (TTree*) f1->Get("LostLeptonPrediction");
	
	Float_t         MTW;
	UShort_t        selectedIDIsoMuonsNum;
	UShort_t        selectedIDIsoElectronsNum;
	
	Float_t         totalWeightDiLep;
	Float_t         totalWeightDiLepIsoTrackReduced;
	
	Float_t         muIsoWeight;
	Float_t         muRecoWeight;
	Float_t         muAccWeight;

	Float_t         elecAccWeight;
	Float_t         elecRecoWeight;
	Float_t         elecIsoWeight;
	
	
	
	LostLeptonPrediction->SetBranchAddress("HT",&HT);
	LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
	LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
	LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
	LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
	
	LostLeptonPrediction->SetBranchAddress("MTW",&MTW);
	LostLeptonPrediction->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
	LostLeptonPrediction->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
	LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
	LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
	
	LostLeptonPrediction->SetBranchAddress("muIsoWeight",&muIsoWeight);
	LostLeptonPrediction->SetBranchAddress("muRecoWeight",&muRecoWeight);
	LostLeptonPrediction->SetBranchAddress("muAccWeight",&muAccWeight);
	
	LostLeptonPrediction->SetBranchAddress("elecAccWeight",&elecAccWeight);
	LostLeptonPrediction->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
	LostLeptonPrediction->SetBranchAddress("elecIsoWeight",&elecIsoWeight);


	TDirectory *EffInputFolder =   (TDirectory*)f1->Get("Efficiencies");
	TProfile *CombinedMeanWeightDiLep_ = (TProfile*) EffInputFolder->Get("CombinedMeanWeightDiLep");
	TProfile *MuMeanWeightDiLep_ = (TProfile*) EffInputFolder->Get("MuMeanWeightDiLep");
	TProfile *ElecMeanWeightDiLep_ = (TProfile*) EffInputFolder->Get("ElecMeanWeightDiLep");

	TH1 *MuWeightDiLepPerBin_[100];
	TH1 *ElecWeightDiLepPerBin_[100];
	TH1 *CombinedWeightDiLepPerBin_[100];
	TDirectory *EffperBinInputFolder =   (TDirectory*)f1->Get("EfficienciesPerBin");
	for(int b = 0; b <100; b++){
		MuWeightDiLepPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("MuWeightDiLepPerBin_")+TString(to_string(b+1)));
		ElecWeightDiLepPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("ElecWeightDiLepPerBin_")+TString(to_string(b+1)));
		CombinedWeightDiLepPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("CombinedWeightDiLepPerBin_")+TString(to_string(b+1)));
	}
	
	nentries = LostLeptonPrediction->GetEntries();
	nbytes = 0;
	for (Long64_t i=0; i<nentries;i++) {
		nbytes += LostLeptonPrediction->GetEntry(i);
		// total expectation
		if(MTW>100 || NJets<3.7)continue;
		Bin = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
		Weight_=Weight;
		selectedIDIsoMuonsNum_=selectedIDIsoMuonsNum;
		selectedIDIsoElectronsNum_=selectedIDIsoElectronsNum;
		if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0)
		{
			ControlSampleMu_->Fill(HT,MHT,NJets,BTags,Weight);
			
			totalPrediction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLep/2);
			totalPredictionMu_->Fill(HT,MHT,NJets,BTags,totalWeightDiLep);
			totalPre+=totalWeightDiLep;
			totalPreError+= totalWeightDiLep*totalWeightDiLep;
			totalPreMu+=totalWeightDiLep;
			totalPreMuError+= totalWeightDiLep*totalWeightDiLep;
			// isotrackveto applied
			totalPredictionIsoTrackReduction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLepIsoTrackReduced/2);
			totalPredictionMuIsoTrackReduction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLepIsoTrackReduced);
			totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReduced*totalWeightDiLepIsoTrackReduced;

			// separted closure
			totalPredictionMuCSMuAcc_->Fill(HT,MHT,NJets,BTags,muAccWeight);
			totalPredictionMuCSMuReco_->Fill(HT,MHT,NJets,BTags,muRecoWeight);
			totalPredictionMuCSMuIso_->Fill(HT,MHT,NJets,BTags,muIsoWeight);
			totalPreMuAcc+=muAccWeight/2;
			totalPreMuReco+=muRecoWeight/2;
			totalPreMuIso+=muIsoWeight/2;
			totalPreMuMuAcc+=muAccWeight;
			totalPreMuMuReco+=muRecoWeight;
			totalPreMuMuIso+=muIsoWeight;
			
			totalPredictionMuCSElecAcc_->Fill(HT,MHT,NJets,BTags,elecAccWeight);
			totalPredictionMuCSElecReco_->Fill(HT,MHT,NJets,BTags,elecRecoWeight);
			totalPredictionMuCSElecIso_->Fill(HT,MHT,NJets,BTags,elecIsoWeight);
			totalPreElecAcc+=elecAccWeight/2;
			totalPreElecReco+=elecRecoWeight/2;
			totalPreElecIso+=elecIsoWeight/2;
			totalPreMuElecAcc+=elecAccWeight;
			totalPreMuElecReco+=elecRecoWeight;
			totalPreMuElecIso+=elecIsoWeight;

			muIsoWeight_=muIsoWeight; muRecoWeight_=muRecoWeight; muAccWeight_=muAccWeight;  elecIsoWeight_=elecIsoWeight; elecRecoWeight_=elecRecoWeight; elecAccWeight_=elecAccWeight; 
			PredictionWeight_= totalWeightDiLep;
			OutPutTreePre_->Fill();
		}
		if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
		{
			ControlSampleElec_->Fill(HT,MHT,NJets,BTags,Weight);
			
			totalPrediction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLep/2);
			totalPredictionElec_->Fill(HT,MHT,NJets,BTags,totalWeightDiLep);
			totalPre+=totalWeightDiLep;
			totalPreError+= totalWeightDiLep*totalWeightDiLep;
			totalPreElec+=totalWeightDiLep;
			totalPreElecError+= totalWeightDiLep*totalWeightDiLep;
			// isotrackveto applied
			totalPredictionIsoTrackReduction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLepIsoTrackReduced/2);
			totalPredictionElecIsoTrackReduction_->Fill(HT,MHT,NJets,BTags,totalWeightDiLepIsoTrackReduced);
			totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReduced;
			totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReduced*totalWeightDiLepIsoTrackReduced;
			// separted closure
			totalPredictionElecCSMuAcc_->Fill(HT,MHT,NJets,BTags,muAccWeight);
			totalPredictionElecCSMuReco_->Fill(HT,MHT,NJets,BTags,muRecoWeight);
			totalPredictionElecCSMuIso_->Fill(HT,MHT,NJets,BTags,muIsoWeight);
			totalPreMuAcc+=muAccWeight/2;
			totalPreMuReco+=muRecoWeight/2;
			totalPreMuIso+=muIsoWeight/2;
			totalPreElecMuAcc+=muAccWeight;
			totalPreElecMuReco+=muRecoWeight;
			totalPreElecMuIso+=muIsoWeight;
			
			totalPredictionElecCSElecAcc_->Fill(HT,MHT,NJets,BTags,elecAccWeight);
			totalPredictionElecCSElecReco_->Fill(HT,MHT,NJets,BTags,elecRecoWeight);
			totalPredictionElecCSElecIso_->Fill(HT,MHT,NJets,BTags,elecIsoWeight);
			totalPreElecAcc+=elecAccWeight/2;
			totalPreElecReco+=elecRecoWeight/2;
			totalPreElecIso+=elecIsoWeight/2;
			totalPreElecElecAcc+=elecAccWeight;
			totalPreElecElecReco+=elecRecoWeight;
			totalPreElecElecIso+=elecIsoWeight;

			PredictionWeight_= totalWeightDiLep;
			OutPutTreePre_->Fill();
		}
	}
	
	TH1F* expectationTH1 = (TH1F*) totalExpectation_->getFullTH1F();
	TH1F* predictionTH1 = (TH1F*) totalPrediction_->getFullTH1F();
	TH1F* FullClosure = (TH1F*) expectationTH1->Clone();
	FullClosure->Divide(predictionTH1,expectationTH1,1,1,"B");
	FullClosure->SetName("LostLeptonClosure");
	FullClosure->SetTitle("Closure of lost-lepton method");
	
	TH1F* predictionTH1Mu = (TH1F*) totalPredictionMu_->getFullTH1F();
	TH1F* FullClosureMu = (TH1F*) expectationTH1->Clone();
	FullClosureMu->Divide(predictionTH1Mu,expectationTH1,1,1,"B");
	FullClosureMu->SetName("LostLeptonClosureMuCS");
	FullClosureMu->SetTitle("Closure of lost-lepton method #mu control-sample");
	
	TH1F* predictionTH1Elec = (TH1F*) totalPredictionElec_->getFullTH1F();
	TH1F* FullClosureElec = (TH1F*) expectationTH1->Clone();
	FullClosureElec->Divide(predictionTH1Elec,expectationTH1,1,1,"B");
	FullClosureElec->SetName("LostLeptonClosureElecCS");
	FullClosureElec->SetTitle("Closure of lost-lepton method elec control-sample");

	std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";
	std::cout<<"\n Muon and Electron CS:"<<std::endl;
	std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrack/2<<" +- "<<sqrt(totalPreIsoTrackError)/2<<std::endl;
	std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPre/2<<" +- "<<sqrt(totalPreError)/2<<std::endl;
	std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreMuAcc<<std::endl;
	std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreMuReco<<std::endl;
	std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreMuIso<<std::endl;
	std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreElecAcc<<std::endl;
	std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreElecReco<<std::endl;
	std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreElecIso<<std::endl;
	std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

	std::cout<<"\n Muon CS only:"<<std::endl;
	std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrackMu<<" +- "<<sqrt(totalPreIsoTrackMuError)<<std::endl;
	std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPreMu<<" +- "<<sqrt(totalPreMuError)<<std::endl;	
	std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreMuMuAcc<<std::endl;
	std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreMuMuReco<<std::endl;
	std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreMuMuIso<<std::endl;
	std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreMuElecAcc<<std::endl;
	std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreMuElecReco<<std::endl;
	std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreMuElecIso<<std::endl;
	std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

	std::cout<<"\n Elec CS only:"<<std::endl;
	std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrackElec<<" +- "<<sqrt(totalPreIsoTrackElecError)<<std::endl;
	std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPreElec<<" +- "<<sqrt(totalPreElecError)<<std::endl;	
	std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreElecMuAcc<<std::endl;
	std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreElecMuReco<<std::endl;
	std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreElecMuIso<<std::endl;
	std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreElecElecAcc<<std::endl;
	std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreElecElecReco<<std::endl;
	std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreElecElecIso<<std::endl;
	std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

	
	outPutFile->cd();
	OutPutTreeExp_->Write();
	OutPutTreePre_->Write();
	FullClosure->Write();
	FullClosureMu->Write();
	FullClosureElec->Write();
	outPutFile->mkdir("Closures");
	TDirectory *dClosures = (TDirectory*)outPutFile->Get("Closures");
	SaveClosure(totalPredictionMuCSMuAcc_->getFullTH1F(), totalExpectationMuAcc_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionMuCSMuReco_->getFullTH1F(), totalExpectationMuReco_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionMuCSMuIso_->getFullTH1F(), totalExpectationMuIso_->getFullTH1F(), dClosures);
	
	SaveClosure(totalPredictionMuCSElecAcc_->getFullTH1F(), totalExpectationElecAcc_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionMuCSElecReco_->getFullTH1F(), totalExpectationElecReco_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionMuCSElecIso_->getFullTH1F(), totalExpectationElecIso_->getFullTH1F(), dClosures);
	
	SaveClosure(totalPredictionElecCSMuAcc_->getFullTH1F(), totalExpectationMuAcc_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionElecCSMuReco_->getFullTH1F(), totalExpectationMuReco_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionElecCSMuIso_->getFullTH1F(), totalExpectationMuIso_->getFullTH1F(), dClosures);
	
	SaveClosure(totalPredictionElecCSElecAcc_->getFullTH1F(), totalExpectationElecAcc_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionElecCSElecReco_->getFullTH1F(), totalExpectationElecReco_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionElecCSElecIso_->getFullTH1F(), totalExpectationElecIso_->getFullTH1F(), dClosures);
	
	SaveClosure(totalPredictionIsoTrackReduction_->getFullTH1F(), totalExpectationIsoTrackReduction_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionMuIsoTrackReduction_->getFullTH1F(), totalExpectationIsoTrackReduction_->getFullTH1F(), dClosures);
	SaveClosure(totalPredictionElecIsoTrackReduction_->getFullTH1F(), totalExpectationIsoTrackReduction_->getFullTH1F(), dClosures);
	
	
	outPutFile->mkdir("Expectation");
	TDirectory *dExpectation = (TDirectory*)outPutFile->Get("Expectation");
	dExpectation->cd();
	totalExpectation_->saveResults(dExpectation);
	outPutFile->mkdir("Prediction");
	TDirectory *dPrediction = (TDirectory*)outPutFile->Get("Prediction");
	dPrediction->cd();
	totalPrediction_->saveResults(dPrediction);
	totalPredictionMu_->saveResults(dPrediction);
	totalPredictionElec_->saveResults(dPrediction);
	
	outPutFile->mkdir("ControlSample");
	TDirectory *dControlSample = (TDirectory*)outPutFile->Get("ControlSample");
	SaveClosure(ControlSampleElec_->getFullTH1F(), ControlSampleMu_->getFullTH1F(), dControlSample);
	dControlSample->cd();
	ControlSampleMu_->saveResults(dControlSample);
	ControlSampleElec_->saveResults(dControlSample);
	
	TH1F* h_exp = (TH1F*) totalExpectationIsoTrackReduction_->getFullTH1F();
	TH1F* h_pred = (TH1F*) totalPredictionIsoTrackReduction_->getFullTH1F();
	TH1F* h_pred_mu = (TH1F*) totalPredictionMuIsoTrackReduction_->getFullTH1F();
	TH1F* h_pred_elec = (TH1F*) totalPredictionElecIsoTrackReduction_->getFullTH1F();
	

	TH1F* h_cs_mu = (TH1F*) ControlSampleMu_->getFullTH1F();
	TH1F* h_cs_elec = (TH1F*) ControlSampleElec_->getFullTH1F();

	TH1F* fullPred_LL_ = new TH1F("fullPred_LL","fullPred_LL", 220, 1, 221);
	TH1F* fullPredSysUp_LL_ = new TH1F("fullPredSysUp_LL","fullPredSysUp_LL", 220, 1, 221);
	TH1F* fullPredSysDown_LL_ = new TH1F("fullPredSysDown_LL","fullPredSysDown_LL", 220, 1, 221);
	TH1F* fullCS_LL_ = new TH1F("fullCS_LL","fullCS_LL", 220, 1, 221);
	TH1F* fullWeight_LL_ = new TH1F("fullWeight_LL","fullWeight_LL", 220, 1, 221);
	TH1F* fullWeightSysUp_LL_ = new TH1F("fullWeightSysUp_LL","fullWeightSysDown_LL", 220, 1, 221);
	TH1F* fullWeightSysDown_LL_ = new TH1F("fullWeightSysUp_LL","fullWeightSysDown_LL", 220, 1, 221);

	for(int i = 1; i<h_pred->GetNbinsX()+1; ++i){
		double N_predicted = h_pred->GetBinContent(i);
		double N_expected = h_exp->GetBinContent(i);

		double weight_mu = MuMeanWeightDiLep_->GetBinContent(i+1);
		double weight_elec = ElecMeanWeightDiLep_->GetBinContent(i+1);		

		double weight_mu_err = MuMeanWeightDiLep_->GetBinError(i+1);
		double weight_elec_err = ElecMeanWeightDiLep_->GetBinError(i+1);

		double weight_combined = CombinedMeanWeightDiLep_->GetBinContent(i+1);
		double weight_combined_err = CombinedMeanWeightDiLep_->GetBinError(i+1);

		double N_cs_mu = h_cs_mu->GetBinContent(i);
		double N_cs_elec = h_cs_elec->GetBinContent(i);
		double Err_cs_mu = sqrt(N_cs_mu);
		double Err_cs_elec = sqrt(N_cs_elec);

		if(CombinedWeightDiLepPerBin_[i-1]->GetEntries()<0.5 && i > 37){
			weight_combined = CombinedMeanWeightDiLep_->GetBinContent(i+1-18);
			weight_combined_err = CombinedMeanWeightDiLep_->GetBinError(i+1-18);
			fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.2);
			fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.2);
			if(i > 55 && CombinedWeightDiLepPerBin_[i-1-18]->GetEntries()<0.5){
				weight_combined = CombinedMeanWeightDiLep_->GetBinContent(i+1-18);
				weight_combined_err = CombinedMeanWeightDiLep_->GetBinError(i+1-18);
				fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.3);
				fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.3);
			}
		}else{
			fullWeightSysUp_LL_->SetBinContent(i,0);
			fullWeightSysDown_LL_->SetBinContent(i,0);
		}


		if(CombinedWeightDiLepPerBin_[i-1]->GetEntries()<0.5 && i > 56){
			weight_combined = fullWeight_LL_->GetBinContent(i+1-55);
			weight_combined_err = fullWeight_LL_->GetBinError(i+1-55);
			fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.2);
			fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.2);
			if(CombinedWeightDiLepPerBin_[i-1-55]->GetEntries()<0.5 && i > 111){
				weight_combined = fullWeight_LL_->GetBinContent(i+1-110);
				weight_combined_err = fullWeight_LL_->GetBinError(i+1-110);
				fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.3);
				fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.3);
				if(CombinedWeightDiLepPerBin_[i-1-110]->GetEntries()<0.5 && i > 166){
					weight_combined = fullWeight_LL_->GetBinContent(i+1-165);
					weight_combined_err = fullWeight_LL_->GetBinError(i+1-165);
					fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.5);
					fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.5);
				}
			}
		}else{
			fullWeightSysUp_LL_->SetBinContent(i,0);
			fullWeightSysDown_LL_->SetBinContent(i,0);
		}
		if(weight_combined<0.01 && i < 220){
				weight_combined = CombinedMeanWeightDiLep_->GetBinContent(i+1+1);
				weight_combined_err = CombinedMeanWeightDiLep_->GetBinError(i+1+1);
				fullWeightSysUp_LL_->SetBinContent(i,weight_combined*0.3);
				fullWeightSysDown_LL_->SetBinContent(i,weight_combined*0.3);
		}

		//std::cout<<weight_combined<<"; "<<CombinedWeightDiLepPerBin_[i-1]->GetMean()<<std::endl;
/*
		if(weight_mu < 0.1){
			if(i > 19) weight_mu = MuMeanWeightDiLep_->GetBinContent(i-18);
			else std::cout<<"Mu: Error using weight from lower N_BJets"<<std::endl;
			if(weight_mu < 0.1){
				if(i > 37) weight_mu = MuMeanWeightDiLep_->GetBinContent(i-18);
				else std::cout<<"Mu: Error using weight from 2xlower N_BJets"<<std::endl;
			}
			if(weight_mu < 0.1) weight_mu = 0.1;
		}

		if(N_cs_mu < 1.0){
			Err_cs_mu = 1.84;
		}

		double Err_pred_mu = Err_cs_mu * weight_mu;


		if(weight_elec < 0.1){
			if(i > 19) weight_elec = ElecMeanWeightDiLep_->GetBinContent(i-18);
			else std::cout<<"El: Error using weight from lower N_BJets"<<std::endl;
			if(weight_elec < 0.1){
				if(i > 37) weight_elec = ElecMeanWeightDiLep_->GetBinContent(i-18);
				else std::cout<<"El: Error using weight from 2xlower N_BJets"<<std::endl;
			}
			if(weight_elec < 0.1) weight_elec = 0.1;
		}

		if(N_cs_elec < 1.0){
			Err_cs_elec = 1.84;
		}

		double Err_pred_elec = Err_cs_elec * weight_elec;


		double Err_pred_ges = (Err_pred_mu + Err_pred_elec) / 2;
*/
		/*std::cout<<"Bin["<<i<<"]:"<<std::endl;
		std::cout<<"   HT: "<<SearchBins_->GetSearchBin(i-1)->HTmin_<<"-"<<SearchBins_->GetSearchBin(i-1)->HTmax_;
		std::cout<<"   MHT: "<<SearchBins_->GetSearchBin(i-1)->MHTmin_<<"-"<<SearchBins_->GetSearchBin(i-1)->MHTmax_;
		std::cout<<"   NJets: "<<SearchBins_->GetSearchBin(i-1)->NJetsmin_<<"-"<<SearchBins_->GetSearchBin(i-1)->NJetsmax_;
		std::cout<<"   BTags: "<<SearchBins_->GetSearchBin(i-1)->BTagsmin_<<"-"<<SearchBins_->GetSearchBin(i-1)->BTagsmax_;
		std::cout<<std::endl;
		std::cout<<"   "<<N_predicted<<"+-"<<sqrt(Err_pred_ges*Err_pred_ges+0.4*0.4*N_predicted*N_predicted)<<std::endl;
*/
		std::cout.unsetf ( std::ios::floatfield );
  		std::cout.precision(5);
		//std::cout<<i<<" & ";

		if(SearchBins_->GetSearchBin(i-1)->NJetsmin_<SearchBins_->GetSearchBin(i-1)->NJetsmax_ && SearchBins_->GetSearchBin(i-1)->NJetsmin_>=0){
			std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmin_<<"-";
			if(SearchBins_->GetSearchBin(i-1)->NJetsmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmax_<<" & ";
			else std::cout<<"Inf"<<" & ";
		}else{
			std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmax_<<" & ";
		}

		if(SearchBins_->GetSearchBin(i-1)->BTagsmin_<SearchBins_->GetSearchBin(i-1)->BTagsmax_ && SearchBins_->GetSearchBin(i-1)->BTagsmin_>=0){
			if(SearchBins_->GetSearchBin(i-1)->BTagsmax_>=0) std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmin_<<"-";
			else std::cout<<"0"<<"-";
			if(SearchBins_->GetSearchBin(i-1)->BTagsmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmax_<<" & ";
			else std::cout<<"Inf"<<" & ";
		}else{
			std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmax_<<" & ";
		}

		std::cout<<SearchBins_->GetSearchBin(i-1)->HTmin_<<"-";
		if(SearchBins_->GetSearchBin(i-1)->HTmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->HTmax_<<" & ";
		else std::cout<<"Inf"<<" & ";

		std::cout<<SearchBins_->GetSearchBin(i-1)->MHTmin_<<"-";
		if(SearchBins_->GetSearchBin(i-1)->MHTmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->MHTmax_<<" & ";
		else std::cout<<"Inf"<<" & ";

		std::cout<<0.1*((int)((N_cs_mu+N_cs_elec)*10))<<" & ";//<<" ("<<CombinedWeightDiLepPerBin_[i-1]->GetEntries()<<") & ";

		std::cout.precision(3);
		std::cout<<"$"<<weight_combined<<"\\pm"<<0.001*((int)(weight_combined_err*1000))<<"^{+"<<fullWeightSysUp_LL_->GetBinContent(i)<<"}_{-"<<fullWeightSysDown_LL_->GetBinContent(i)<<"}$ & ";
		std::cout.precision(5);
 //		std::cout<<CombinedWeightDiLepPerBin_[i-1]->GetRMS()<<" ("<<CombinedWeightDiLepPerBin_[i-1]->GetBinCenter(CombinedWeightDiLepPerBin_[i-1]->FindFirstBinAbove())<<"/"<<CombinedWeightDiLepPerBin_[i-1]->GetBinCenter(CombinedWeightDiLepPerBin_[i-1]->FindLastBinAbove())<<") & ";
//		std::cout<<N_predicted<<"+-"<<sqrt(Err_pred_ges*Err_pred_ges+0.4*0.4*N_predicted*N_predicted)<<" \\\\"<<std::endl;
	if(N_predicted>0.00001)	std::cout<<"$"<<0.1*((int)(N_predicted*10))<<"\\pm"<<0.1*((int)(sqrt(N_predicted*N_predicted/(N_cs_mu+N_cs_elec))*10))<<"^{+"<<0.1*((int)(0.3*N_predicted*10))<<"}_{-"<<0.1*((int)(0.3*N_predicted*10))<<"}$ \\\\"<<std::endl;
	else	std::cout<<"$"<<0<<"\\pm"<<0<<"^{+"<<0<<"}_{-"<<0<<"}$ \\\\"<<std::endl;

		fullCS_LL_->SetBinContent(i,N_cs_mu+N_cs_elec);

		fullWeight_LL_->SetBinContent(i,weight_combined);
		fullWeight_LL_->SetBinError(i,weight_combined_err);

		fullPred_LL_->SetBinContent(i,N_predicted);
		if((N_cs_mu+N_cs_elec)>0) fullPred_LL_->SetBinError(i,sqrt(N_predicted*N_predicted/(N_cs_mu+N_cs_elec)));
		if((N_cs_mu+N_cs_elec)>0) fullPredSysUp_LL_->SetBinContent(i,0.3*N_predicted);
		if((N_cs_mu+N_cs_elec)>0) fullPredSysDown_LL_->SetBinContent(i,0.3*N_predicted);

		//std::cout<<"Bin["<<i<<"]: "<<N_predicted<<"+-"<<Err_pred_ges<<std::endl;
		//std::cout<<"Bin["<<i<<"]: "<<N_predicted<<"+-"<<sqrt(Err_pred_ges*Err_pred_ges+0.4*0.4*N_predicted*N_predicted)<<std::endl;
	}




/*		std::cout<<"Baseline & & & & "<<totalExpIsoTrack<<"$\\pm$"<<sqrt(totalExpIsoTrackError)<<" & "<<totalPreElec/2<<"$\\pm$"<<sqrt(totalPreElecError)/2<<" & "<<totalPreMu/2<<"$\\pm$"<<sqrt(totalPreMuError)/2<<" & "<<totalPre/2<<"$\\pm$"<<sqrt(totalPreError)/2<<" \\\\ "<<std::endl;

	for(int i = 1; i<h_pred->GetNbinsX()+1; ++i){
		if(SearchBins_->GetSearchBin(i-1)->NJetsmin_<SearchBins_->GetSearchBin(i-1)->NJetsmax_ && SearchBins_->GetSearchBin(i-1)->NJetsmin_>=0){
			std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmin_<<"-";
			if(SearchBins_->GetSearchBin(i-1)->NJetsmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmax_<<" & ";
			else std::cout<<"Inf"<<" & ";
		}else{
			std::cout<<SearchBins_->GetSearchBin(i-1)->NJetsmax_<<" & ";
		}

		if(SearchBins_->GetSearchBin(i-1)->BTagsmin_<SearchBins_->GetSearchBin(i-1)->BTagsmax_ && SearchBins_->GetSearchBin(i-1)->BTagsmin_>=0){
			if(SearchBins_->GetSearchBin(i-1)->BTagsmax_>=0) std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmin_<<"-";
			else std::cout<<"0"<<"-";
			if(SearchBins_->GetSearchBin(i-1)->BTagsmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmax_<<" & ";
			else std::cout<<"Inf"<<" & ";
		}else{
			std::cout<<SearchBins_->GetSearchBin(i-1)->BTagsmax_<<" & ";
		}

		std::cout<<SearchBins_->GetSearchBin(i-1)->HTmin_<<"-";
		if(SearchBins_->GetSearchBin(i-1)->HTmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->HTmax_<<" & ";
		else std::cout<<"Inf"<<" & ";

		std::cout<<SearchBins_->GetSearchBin(i-1)->MHTmin_<<"-";
		if(SearchBins_->GetSearchBin(i-1)->MHTmax_<9999) std::cout<<SearchBins_->GetSearchBin(i-1)->MHTmax_<<" & ";
		else std::cout<<"Inf"<<" & ";

		std::cout<<h_exp->GetBinContent(i)<<"$\\pm$"<<h_exp->GetBinError(i)<<" & ";
		std::cout<<h_pred_elec->GetBinContent(i)/2<<"$\\pm$"<<h_pred_elec->GetBinError(i)/2<<" & ";
		std::cout<<h_pred_mu->GetBinContent(i)/2<<"$\\pm$"<<h_pred_mu->GetBinError(i)/2<<" & ";
		std::cout<<h_pred->GetBinContent(i)<<"$\\pm$"<<h_pred->GetBinError(i)<<" \\\\ "<<std::endl;
	}
*/

	TFile *LLoutPutFile = new TFile("LLPrediction.root","RECREATE"); 
	LLoutPutFile->cd();
	fullPred_LL_->Write();
	fullCS_LL_->Write();
	fullWeight_LL_->Write();
	fullPredSysUp_LL_->Write();
	fullPredSysDown_LL_->Write();
	fullWeightSysUp_LL_->Write();
	fullWeightSysDown_LL_->Write();
	LLoutPutFile->Close();
	
}
	
}


SearchBins::SearchBins()
{
	
	// HTmin,HTmax,MHTmin,MHTmax,NJetsmin,NJetsmax,BTagsmin,BTagsmax
	// NJets 4,6 BTags=0
	// fixed ht Njets btags all MHT bins
	bins_.push_back( Bin(500,800,200,500,4,6,-1,0) );
	bins_.push_back( Bin(800,1200,200,500,4,6,-1,0) );
	bins_.push_back( Bin(1200,99999,200,500,4,6,-1,0) );
	
	bins_.push_back( Bin(500,1200,500,750,4,6,-1,0) );
	bins_.push_back( Bin(1200,99999,500,750,4,6,-1,0) );
	
	bins_.push_back( Bin(800,99999,750,9999,4,6,-1,0) );
	
		// NJets 4,6 BTags=1
	// fixed ht Njets btags all MHT bins
	bins_.push_back( Bin(500,800,200,500,4,6,1,1) );
	bins_.push_back( Bin(800,1200,200,500,4,6,1,1) );
	bins_.push_back( Bin(1200,99999,200,500,4,6,1,1) );
	
	bins_.push_back( Bin(500,1200,500,750,4,6,1,1) );
	bins_.push_back( Bin(1200,99999,500,750,4,6,1,1) );
	
	bins_.push_back( Bin(800,99999,750,9999,4,6,1,1) );

  // NJets 4,6 BTags=2
  // fixed ht Njets btags all MHT bins
  bins_.push_back( Bin(500,800,200,500,4,6,2,2) );
  bins_.push_back( Bin(800,1200,200,500,4,6,2,2) );
  bins_.push_back( Bin(1200,99999,200,500,4,6,2,2) );
  
  bins_.push_back( Bin(500,1200,500,750,4,6,2,2) );
  bins_.push_back( Bin(1200,99999,500,750,4,6,2,2) );
  
  bins_.push_back( Bin(800,99999,750,9999,4,6,2,2) );

  // NJets 4,6 BTags=>3
  // fixed ht Njets btags all MHT bins
  bins_.push_back( Bin(500,800,200,500,4,6,3,9999) );
  bins_.push_back( Bin(800,1200,200,500,4,6,3,9999) );
  bins_.push_back( Bin(1200,99999,200,500,4,6,3,9999) );
  
  bins_.push_back( Bin(500,1200,500,750,4,6,3,9999) );
  bins_.push_back( Bin(1200,99999,500,750,4,6,3,9999) );
  
  bins_.push_back( Bin(800,99999,750,9999,4,6,3,9999) );

  // NJewts 7,8 BTags=0
  bins_.push_back( Bin(500,800,200,500,7,8,-1,0) );
  bins_.push_back( Bin(800,1200,200,500,7,8,-1,0) );
  bins_.push_back( Bin(1200,99999,200,500,7,8,-1,0) );
  
  bins_.push_back( Bin(500,1200,500,750,7,8,-1,0) );
  bins_.push_back( Bin(1200,99999,500,750,7,8,-1,0) );
  
  bins_.push_back( Bin(800,99999,750,9999,7,8,-1,0) );
	
	// NJewts 7,8 BTags=1
	bins_.push_back( Bin(500,800,200,500,7,8,1,1) );
	bins_.push_back( Bin(800,1200,200,500,7,8,1,1) );
	bins_.push_back( Bin(1200,99999,200,500,7,8,1,1) );
	
	bins_.push_back( Bin(500,1200,500,750,7,8,1,1) );
	bins_.push_back( Bin(1200,99999,500,750,7,8,1,1) );
	
	bins_.push_back( Bin(800,99999,750,9999,7,8,1,1) );

    // NJewts 7,8 BTags=2
  bins_.push_back( Bin(500,800,200,500,7,8,2,2) );
  bins_.push_back( Bin(800,1200,200,500,7,8,2,2) );
  bins_.push_back( Bin(1200,99999,200,500,7,8,2,2) );
  
  bins_.push_back( Bin(500,1200,500,750,7,8,2,2) );
  bins_.push_back( Bin(1200,99999,500,750,7,8,2,2) );
  
  bins_.push_back( Bin(800,99999,750,9999,7,8,2,2) );

    // NJewts 7,8 BTags=>3
  bins_.push_back( Bin(500,800,200,500,7,8,3,9999) );
  bins_.push_back( Bin(800,1200,200,500,7,8,3,9999) );
  bins_.push_back( Bin(1200,99999,200,500,7,8,3,9999) );
  
  bins_.push_back( Bin(500,1200,500,750,7,8,3,9999) );
  bins_.push_back( Bin(1200,99999,500,750,7,8,3,9999) );
  
  bins_.push_back( Bin(800,99999,750,9999,7,8,3,9999) );


  // NJewts 9,9999 BTags=0
  bins_.push_back( Bin(500,800,200,500,9,9999,-1,0) );
  bins_.push_back( Bin(800,1200,200,500,9,9999,-1,0) );
  bins_.push_back( Bin(1200,99999,200,500,9,9999,-1,0) );
  
  bins_.push_back( Bin(500,1200,500,750,9,9999,-1,0) );
  bins_.push_back( Bin(1200,99999,500,750,9,9999,-1,0) );
  
  bins_.push_back( Bin(800,99999,750,9999,9,9999,-1,0) );
	
	
	// NJewts 9,9999 BTags=1
	bins_.push_back( Bin(500,800,200,500,9,9999,1,1) );
	bins_.push_back( Bin(800,1200,200,500,9,9999,1,1) );
	bins_.push_back( Bin(1200,99999,200,500,9,9999,1,1) );
	
	bins_.push_back( Bin(500,1200,500,750,9,9999,1,1) );
	bins_.push_back( Bin(1200,99999,500,750,9,9999,1,1) );
	
	bins_.push_back( Bin(800,99999,750,9999,9,9999,1,1) );

	
  	// NJewts 9,9999 BTags=2
	bins_.push_back( Bin(500,800,200,500,9,9999,2,2) );
	bins_.push_back( Bin(800,1200,200,500,9,9999,2,2) );
	bins_.push_back( Bin(1200,99999,200,500,9,9999,2,2) );
	
	bins_.push_back( Bin(500,1200,500,750,9,9999,2,2) );
	bins_.push_back( Bin(1200,99999,500,750,9,9999,2,2) );
	
	bins_.push_back( Bin(800,99999,750,9999,9,9999,2,2) );
	

	// NJewts 9,9999 BTags=>3
	bins_.push_back( Bin(500,800,200,500,9,9999,3,9999) );
	bins_.push_back( Bin(800,1200,200,500,9,9999,3,9999) );
	bins_.push_back( Bin(1200,99999,200,500,9,9999,3,9999) );
	
	bins_.push_back( Bin(500,1200,500,750,9,9999,3,9999) );
	bins_.push_back( Bin(1200,99999,500,750,9,9999,3,9999) );
	
	bins_.push_back( Bin(800,99999,750,9999,9,9999,3,9999) );
}

Bin* SearchBins::GetSearchBin(int i){
	return &(bins_.at(i));
}

unsigned int SearchBins::GetBinNumber(double HT, double MHT, int NJets, int BTags)
{
	unsigned int result =999;
	int match =-1;
	for(unsigned int i=0; i<bins_.size();i++)
	{
		// 		std::cout<<"Bin["<<i<<"]: HT["<<bins_[i].HTmin_<<","<<bins_[i].HTmax_<<"] MHT["<<bins_[i].MHTmin_<<","<<bins_[i].MHTmax_<<"] NJets["<<bins_[i].NJetsmin_<<","<<bins_[i].NJetsmax_<<"] BTags["<<bins_[i].BTagsmin_<<","<<bins_[i].BTagsmax_<<"]\n";
		if(HT>bins_[i].HTmin_ && 
			HT<bins_[i].HTmax_ &&
			MHT>bins_[i].MHTmin_ && 
			MHT<bins_[i].MHTmax_ &&
			NJets+0.1>bins_[i].NJetsmin_ && 
			NJets-0.1<bins_[i].NJetsmax_ &&
			BTags+0.1>bins_[i].BTagsmin_ && 
			BTags-0.1<bins_[i].BTagsmax_
		)
		{
			result=i;
			match++;
		}
	}
	if(match==-1)
	{
		  		std::cout<<"Error event fits in no bin!!! HT: "<<HT<<", MHT: "<<MHT<<", NJets: "<<NJets<<", BTags: "<<BTags<<std::endl;
		result=999;
	}
// 	if(result<18 && result>16)
// 	{
// 		std::cout<<"ResultBin: "<<result+1<<" HT: "<<HT<<", MHT: "<<MHT<<", NJets: "<<NJets<<", BTags: "<<BTags<<std::endl;
// 	}
	if(match>0)
	{
		std::cout<<"Error event fits in more than one bin!!!! HT: "<<HT<<", MHT: "<<MHT<<", NJets: "<<NJets<<", BTags: "<<BTags<<std::endl;
	}
	return result+1; // to not use the 0 bin but start counting at 1
}


SearchBinEventCount::SearchBinEventCount(const char* name)
{
	fullTH1F_ = new 	TH1F(name, name, bins_.size(),0,bins_.size()+1);
	fullTH1F_->Sumw2();
	name_=name;
	splitAfter_=18;
	unsigned int plotsNumber= bins_.size()/splitAfter_;
	// 	std::cout<<"Efficiency::Efficiency plotsNumber="<<plotsNumber<<" number of bins: "<<bins_.size()<<std::endl;
	if(plotsNumber * splitAfter_<bins_.size() )
	{
		
		plotsNumber++;
		for(unsigned int i=0; i < plotsNumber;i++)
		{
			
			TString temp2 (Form ("_%d",(int)i+1));
			TString temp1 = name;
			temp1+=temp2;
			temp2 = name + temp2;
			const char* name1=temp1;
			const char* title1=temp2;
			
			if(i+1==plotsNumber)
			{
				// 				std::cout<<"titlelast["<<i<<"]: "<<temp1<<std::endl;
				unsigned int tempBins = bins_.size() - plotsNumber * splitAfter_;
				splitTH1F_.push_back( new TH1F (name1,title1,tempBins,0,tempBins+1) );
				splitTH1F_[i]->Sumw2();
				continue;
			}
			// 			std::cout<<"title["<<i<<"]: "<<temp1<<std::endl;
			splitTH1F_.push_back( new TH1F (name1,title1,splitAfter_,0,splitAfter_+1) );
			splitTH1F_[i]->Sumw2();
		}
	}
	else
	{
		for(unsigned int i=0; i < plotsNumber;i++)
		{
			
			TString temp2 (Form ("_%d",(int)i+1));
			TString temp1 = name;
			temp1+=temp2;
			
			const char* name1=temp1;
			TH1F* tempeff2 = new  TH1F (name1,name1,splitAfter_,0,splitAfter_+1);
			splitTH1F_.push_back( tempeff2 );
			splitTH1F_[i]->Sumw2();
		}
	}
}


void SearchBinEventCount::Fill(double HT, double MHT, int NJets, int BTags, double Weight)
{
	double bin = GetBinNumber(HT,MHT,NJets,BTags);
	
	if(bin<bins_.size()+2) 
	{
		fullTH1F_->Fill(bin-0.01, Weight);
		unsigned int splitHist=0;
		// 	std::cout<<"bin before split: "<<bin<<std::endl;
		for(int ii=0;bin>splitAfter_;ii++)
		{
			splitHist++;
			bin = bin-splitAfter_;
		}
		// 		if(splitHist==3)std::cout<<"BinForSplit: "<<bin<<" with splitHistNumber "<<splitHist<<" and TH1FSearchBinsSplit_.size(): "<<TH1FSearchBinsSplit_.size()<<std::endl;
		
		splitTH1F_[splitHist]->Fill(bin-0.1, Weight);
	}
}
void SearchBinEventCount::saveResults(TDirectory* MainDirectory)
{
	MainDirectory->mkdir(name_);
	// 	std::cout<<"name: "<<name_<<std::endl;
	TDirectory *dir = (TDirectory*)MainDirectory->Get(name_);
	dir->cd();
	fullTH1F_->Write();
	for(unsigned int i=0; i<splitTH1F_.size();i++) 
	{
		TString temp2 (Form ("_%d",(int)i+1));
		TString temp1 = name_;
		temp1+=temp2;
		temp2 = name_ + temp2;
		const char* name1=temp1;
		const char* title1=temp2;
		splitTH1F_[i]->SetTitle(title1);
		splitTH1F_[i]->SetName(name1);
		splitTH1F_[i]->Write();
	}
}
