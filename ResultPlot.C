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
#include "LLTools.h"
#include "THEff.h"

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

void ResultPlot()
{

  // General Settings
  TString InputPath_Expectation("Expectation.root");
  TString InputPath_Prediction("Prediction.root");
  TString OutputPath_Closure("Closure.root");
  TString OutputPath_Prediction("LLPrediction.root");

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 1; 

  // Prepare Code for Extrapolation Method
  bool doExtrapolation = false; 


  //Declaration of leaves types for both trees (Expectation/Prediction)
  UShort_t         Bin;
  Double_t          Weight;
  Double_t          scaledWeight;
  Double_t         HT;
  Double_t         MHT;
  Int_t            NJets;
  Int_t            BTags;
  
  UShort_t        Expectation;
  UShort_t        muAcc;
  UShort_t        muReco;
  UShort_t        muIso;
  UShort_t        elecAcc;
  UShort_t        elecReco;
  UShort_t        elecIso;
  Int_t           isoTracks;
  UShort_t        ExpectationDiLep;
  UShort_t        ExpectationReductionIsoTrack;

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

  Float_t         totalStatUp;
  Float_t         totalStatDown;
  Float_t         totalSysUp;
  Float_t         totalSysDown;
  Float_t         totalUncUp;
  Float_t         totalUncDown;



  //closure test
  TFile *outPutFile = new TFile(OutputPath_Closure,"RECREATE"); 
  outPutFile->cd();

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
	
  TH1F* ControlSampleMu_ = new TH1F("ControlSampleMu", "ControlSampleMu", 72, 1., 73.);
  TH1F* ControlSampleElec_ = new TH1F("ControlSampleElec", "ControlSampleElec", 72, 1., 73.);
	
  TH1F* totalExpectation_ = new TH1F("TotalLostLeptonExpecation", "TotalLostLeptonExpecation", 72, 1., 73.);
  TH1F* totalPrediction_ = new TH1F("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", 72, 1., 73.);
  TH1F* totalPredictionMu_ = new TH1F("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", 72, 1., 73.);
  TH1F* totalPredictionElec_ = new TH1F("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", 72, 1., 73.);
	
  TH1F* totalExpectationIsoTrackReduction_ = new TH1F("TotalLostLeptonExpecationIsoTrackReduction", "TotalLostLeptonExpecationIsoTrackReduction", 72, 1., 73.);
  TH1F* totalPredictionIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionIsoTrackReduction", "TotalLostLeptonPredictionIsoTrackReduction", 72, 1., 73.);
  TH1F* totalPredictionMuIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionMuIsoTrackReduction", "TotalLostLeptonPredictionMuIsoTrackReduction", 72, 1., 73.);
  TH1F* totalPredictionElecIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionElecIsoTrackReduction", "TotalLostLeptonPredictionElecIsoTrackReduction", 72, 1., 73.);
	
  // separted closure
  TH1F* totalExpectationMuAcc_ = new TH1F("TotalLostLeptonExpecationMuAcc", "TotalLostLeptonExpecationMuAcc", 72, 1., 73.);
  TH1F* totalPredictionMuCSMuAcc_ = new TH1F("TotalLostLeptonPredictionMuCSMuAcc", "TotalLostLeptonPredictionMuCSMuAcc", 72, 1., 73.);
  TH1F* totalPredictionElecCSMuAcc_ = new TH1F("TotalLostLeptonPredictionElecCSMuAcc", "TotalLostLeptonPredictionElecCSMuAcc", 72, 1., 73.);
	
  TH1F* totalExpectationMuReco_ = new TH1F("TotalLostLeptonExpecationMuReco", "TotalLostLeptonExpecationMuReco", 72, 1., 73.);
  TH1F* totalPredictionMuCSMuReco_ = new TH1F("TotalLostLeptonPredictionMuCSMuReco", "TotalLostLeptonPredictionMuCSMuReco", 72, 1., 73.);
  TH1F* totalPredictionElecCSMuReco_ = new TH1F("TotalLostLeptonPredictionElecCSMuReco", "TotalLostLeptonPredictionElecCSMuReco", 72, 1., 73.);
	
  TH1F* totalExpectationMuIso_ = new TH1F("TotalLostLeptonExpecationMuIso", "TotalLostLeptonExpecationMuIso", 72, 1., 73.);
  TH1F* totalPredictionMuCSMuIso_ = new TH1F("TotalLostLeptonPredictionMuCSMuIso", "TotalLostLeptonPredictionMuCSMuIso", 72, 1., 73.);
  TH1F* totalPredictionElecCSMuIso_ = new TH1F("TotalLostLeptonPredictionElecCSMuIso", "TotalLostLeptonPredictionElecCSMuIso", 72, 1., 73.);	
	
  TH1F* totalExpectationElecAcc_ = new TH1F("TotalLostLeptonExpecationElecAcc", "TotalLostLeptonExpecationElecAcc", 72, 1., 73.);
  TH1F* totalPredictionMuCSElecAcc_ = new TH1F("TotalLostLeptonPredictionMuCSElecAcc", "TotalLostLeptonPredictionMuCSElecAcc", 72, 1., 73.);
  TH1F* totalPredictionElecCSElecAcc_ = new TH1F("TotalLostLeptonPredictionElecCSElecAcc", "TotalLostLeptonPredictionElecCSElecAcc", 72, 1., 73.);
	
  TH1F* totalExpectationElecReco_ = new TH1F("TotalLostLeptonExpecationElecReco", "TotalLostLeptonExpecationElecReco", 72, 1., 73.);
  TH1F* totalPredictionMuCSElecReco_ = new TH1F("TotalLostLeptonPredictionMuCSElecReco", "TotalLostLeptonPredictionMuCSElecReco", 72, 1., 73.);
  TH1F* totalPredictionElecCSElecReco_ = new TH1F("TotalLostLeptonPredictionElecCSElecReco", "TotalLostLeptonPredictionElecCSElecReco", 72, 1., 73.);
	
  TH1F* totalExpectationElecIso_ = new TH1F("TotalLostLeptonExpecationElecIso", "TotalLostLeptonExpecationElecIso", 72, 1., 73.);
  TH1F* totalPredictionMuCSElecIso_ = new TH1F("TotalLostLeptonPredictionMuCSElecIso", "TotalLostLeptonPredictionMuCSElecIso", 72, 1., 73.);
  TH1F* totalPredictionElecCSElecIso_ = new TH1F("TotalLostLeptonPredictionElecCSElecIso", "TotalLostLeptonPredictionElecCSElecIso", 72, 1., 73.);



  // Define histrograms to do totalPrediction per SearchBin
  TH1F* totalExp_LL_ = new TH1F("totalExp_LL","totalExp_LL", 72, 1, 73);

  TH1F* totalPred_LL_ = new TH1F("totalPred_LL","totalPred_LL", 72, 1, 73);
  TH1F* totalPredStatUp_LL_ = new TH1F("totalPredStatUp_LL","totalPredStatUp_LL", 72, 1, 73);
  TH1F* totalPredStatDown_LL_ = new TH1F("totalPredStatDown_LL","totalPredStatDown_LL", 72, 1, 73);
  TH1F* totalPredSysUp_LL_ = new TH1F("totalPredSysUp_LL","totalPredSysUp_LL", 72, 1, 73);
  TH1F* totalPredSysDown_LL_ = new TH1F("totalPredSysDown_LL","totalPredSysDown_LL", 72, 1, 73);

  TH1F* totalCS_LL_ = new TH1F("totalCS_LL","totalCS_LL", 72, 1, 73);
  TH1F* nEvtsCS_LL_ = new TH1F("nEvtsCS_LL","nEvtsCS_LL", 72, 1, 73);

  TProfile* avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", 72, 1, 73);
  TProfile* avgWeightStatUp_LL_ = new TProfile("avgWeightStatUp_LL","avgWeightStatUp_LL", 72, 1, 73);
  TProfile* avgWeightStatDown_LL_ = new TProfile("avgWeightStatDown_LL","avgWeightStatDown_LL", 72, 1, 73);
  TProfile* avgWeightSysUp_LL_ = new TProfile("avgWeightSysUp_LL","avgWeightSysUp_LL", 72, 1, 73);
  TProfile* avgWeightSysDown_LL_ = new TProfile("avgWeightSysDown_LL","avgWeightSysDown_LL", 72, 1, 73);

  totalPred_LL_->Sumw2();
  totalPredStatUp_LL_->Sumw2();
  totalPredStatDown_LL_->Sumw2();
  totalPredSysUp_LL_->Sumw2();
  totalPredSysDown_LL_->Sumw2();

  totalCS_LL_->Sumw2();

  avgWeight_LL_->Sumw2();
  avgWeightStatUp_LL_->Sumw2();
  avgWeightStatDown_LL_->Sumw2();
  avgWeightSysUp_LL_->Sumw2();
  avgWeightSysDown_LL_->Sumw2();



	
  //Expectation Tree
  gROOT->Reset();
  TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation);
  if (!fExp) {
    fExp = new TFile("Expectation.root");
  }
  
  TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");

	
  // Set branch addresses.
  LostLeptonExpectation->SetBranchStatus("*",0);
  LostLeptonExpectation->SetBranchStatus("HT",1);
  LostLeptonExpectation->SetBranchStatus("MHT",1);
  LostLeptonExpectation->SetBranchStatus("NJets",1);
  LostLeptonExpectation->SetBranchStatus("BTags",1);
  LostLeptonExpectation->SetBranchStatus("Weight",1);
  LostLeptonExpectation->SetBranchStatus("Bin",1);
  LostLeptonExpectation->SetBranchStatus("Expectation",1);
  LostLeptonExpectation->SetBranchStatus("ExpectationReductionIsoTrack",1);
  LostLeptonExpectation->SetBranchStatus("muAcc",1);
  LostLeptonExpectation->SetBranchStatus("muReco",1);
  LostLeptonExpectation->SetBranchStatus("muIso",1);
  LostLeptonExpectation->SetBranchStatus("elecAcc",1);
  LostLeptonExpectation->SetBranchStatus("elecReco",1);
  LostLeptonExpectation->SetBranchStatus("elecIso",1);
  LostLeptonExpectation->SetBranchStatus("isoTracks",1);
  LostLeptonExpectation->SetBranchStatus("ExpectationDiLep",1);


  LostLeptonExpectation->SetBranchAddress("HT",&HT);
  LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
  LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
  LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
  LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
  LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
	
  LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
  LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);

  LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
  LostLeptonExpectation->SetBranchAddress("muReco",&muReco);
  LostLeptonExpectation->SetBranchAddress("muIso",&muIso);
	
  LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
  LostLeptonExpectation->SetBranchAddress("elecReco",&elecReco);
  LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);
	
  LostLeptonExpectation->SetBranchAddress("isoTracks",&isoTracks);
  LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);
	

	std::cout<<"Loop on Expectation"<<std::endl;
  Long64_t nentries = LostLeptonExpectation->GetEntries();  

  Long64_t nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonExpectation->GetEntry(i);
    // total expectation
    if(doExtrapolation || Bin > 900) continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(Expectation==1 && NJets>3.1)
    {
    	totalExpectation_->Fill(Bin, scaledWeight);
    	totalExp+=scaledWeight;
    	totalExpError+= scaledWeight*scaledWeight;
    }
    if(Expectation==1 && ExpectationReductionIsoTrack==0 && NJets>3.1)
    {
    	totalExpectationIsoTrackReduction_->Fill(Bin, scaledWeight);
    	totalExpIsoTrack+=scaledWeight;
    	totalExpIsoTrackError+= scaledWeight*scaledWeight;
      totalExp_LL_->Fill(Bin, scaledWeight);
    }
    if(muAcc==0)
    {
    	totalExpectationMuAcc_->Fill(Bin, scaledWeight);
    	totalExpMuAcc+=scaledWeight;
    }
    if(muReco==0)
    {
    	totalExpectationMuReco_->Fill(Bin, scaledWeight);
    	totalExpMuReco+=scaledWeight;
    }
    if(muIso==0)
    {
    	totalExpectationMuIso_->Fill(Bin, scaledWeight);
    	totalExpMuIso+=scaledWeight;
    }
					
    if(elecAcc==0)
    {
    	totalExpectationElecAcc_->Fill(Bin, scaledWeight);
    	totalExpElecAcc+=scaledWeight;
    }
    if(elecReco==0)
    {
    	totalExpectationElecReco_->Fill(Bin, scaledWeight);
    	totalExpElecReco+=scaledWeight;
    }
    if(elecIso==0)
    {
    	totalExpectationElecIso_->Fill(Bin, scaledWeight);
    	totalExpElecIso+=scaledWeight;
    }
  }
	
  std::cout<<"Finished"<<std::endl;

  //Prediction Tree
  gROOT->Reset();
  TFile *fPre = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction);
  if (!fPre) {
    fPre = new TFile("Prediction.root");
  }
  TTree* LostLeptonPrediction = (TTree*) fPre->Get("LostLeptonPrediction");

  LostLeptonPrediction->SetBranchStatus("*",0);
  LostLeptonPrediction->SetBranchStatus("HT",1);
  LostLeptonPrediction->SetBranchStatus("MHT",1);
  LostLeptonPrediction->SetBranchStatus("NJets",1);
  LostLeptonPrediction->SetBranchStatus("BTags",1);
  LostLeptonPrediction->SetBranchStatus("Weight",1);
  LostLeptonPrediction->SetBranchStatus("Bin",1);
  LostLeptonPrediction->SetBranchStatus("MTW",1);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchStatus("muIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("totalStatUp",1);
  LostLeptonPrediction->SetBranchStatus("totalSysUp",1);
  LostLeptonPrediction->SetBranchStatus("totalUncUp",1);
  LostLeptonPrediction->SetBranchStatus("totalStatDown",1);
  LostLeptonPrediction->SetBranchStatus("totalSysDown",1);
  LostLeptonPrediction->SetBranchStatus("totalUncDown",1);
  
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
	
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

  LostLeptonPrediction->SetBranchAddress("totalStatUp", &totalStatUp);
  LostLeptonPrediction->SetBranchAddress("totalSysUp", &totalSysUp);
  LostLeptonPrediction->SetBranchAddress("totalUncUp", &totalUncUp);

  LostLeptonPrediction->SetBranchAddress("totalStatDown", &totalStatDown);
  LostLeptonPrediction->SetBranchAddress("totalSysDown", &totalSysDown);
  LostLeptonPrediction->SetBranchAddress("totalUncDown", &totalUncDown);


  TDirectory *EffInputFolder =   (TDirectory*)fPre->Get("MeanWeight");
  TProfile *CombinedMeanWeight_ = (TProfile*) EffInputFolder->Get("CombinedMeanWeight");
  TProfile *MuMeanWeight_ = (TProfile*) EffInputFolder->Get("MuMeanWeight");
  TProfile *ElecMeanWeight_ = (TProfile*) EffInputFolder->Get("ElecMeanWeight");

  TH1 *MuWeightPerBin_[72];
  TH1 *ElecWeightPerBin_[72];
  TH1 *CombinedWeightPerBin_[72];
  TDirectory *EffperBinInputFolder =   (TDirectory*)fPre->Get("WeightPerBin");
  for(int b = 0; b <72; b++){
    MuWeightPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("MuWeightPerBin_")+TString(to_string(b+1)));
    ElecWeightPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("ElecWeightPerBin_")+TString(to_string(b+1)));
    CombinedWeightPerBin_[b] = (TH1D*) EffperBinInputFolder->Get(TString("CombinedWeightPerBin_")+TString(to_string(b+1)));
  }

  std::cout<<"Loop on Prediction"<<std::endl;
	
  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);
    
    if(doExtrapolation || Bin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    totalPred_LL_->Fill(Bin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2);
    totalPredStatUp_LL_->Fill(Bin, totalStatUp*scaleFactorWeight/2);
    totalPredStatDown_LL_->Fill(Bin, totalStatDown*scaleFactorWeight/2);
    totalPredSysUp_LL_->Fill(Bin, totalSysUp*scaleFactorWeight/2);
    totalPredSysDown_LL_->Fill(Bin, totalSysDown*scaleFactorWeight/2);

    totalCS_LL_->Fill(Bin, scaledWeight);
    nEvtsCS_LL_->Fill(Bin);

    avgWeight_LL_->Fill(Bin, totalWeightDiLepIsoTrackReduced/Weight/2);
    avgWeightStatUp_LL_->Fill(Bin, totalStatUp/Weight/2);
    avgWeightStatDown_LL_->Fill(Bin, totalStatDown/Weight/2);
    avgWeightSysUp_LL_->Fill(Bin, totalSysUp/Weight/2);
    avgWeightSysDown_LL_->Fill(Bin, totalSysDown/Weight/2);

    if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0){

    	ControlSampleMu_->Fill(Bin, scaledWeight);
    			
    	totalPrediction_->Fill(Bin, totalWeightDiLep*scaleFactorWeight/2);
    	totalPre+=totalWeightDiLep*scaleFactorWeight/2;
    	totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2;
      totalPredictionMu_->Fill(Bin, totalWeightDiLep*scaleFactorWeight);
    	totalPreMu+=totalWeightDiLep*scaleFactorWeight;
    	totalPreMuError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight;
    	// isotrackveto applied
    	totalPredictionIsoTrackReduction_->Fill(Bin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2;
    	totalPredictionMuIsoTrackReduction_->Fill(Bin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight);
    	totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight;
    	totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight*totalWeightDiLepIsoTrackReduced*scaleFactorWeight;

    	// separted closure
    	totalPredictionMuCSMuAcc_->Fill(Bin, muAccWeight*scaleFactorWeight);
    	totalPredictionMuCSMuReco_->Fill(Bin, muRecoWeight*scaleFactorWeight);
    	totalPredictionMuCSMuIso_->Fill(Bin, muIsoWeight*scaleFactorWeight);
    	totalPreMuAcc+=muAccWeight*scaleFactorWeight/2;
    	totalPreMuReco+=muRecoWeight*scaleFactorWeight/2;
    	totalPreMuIso+=muIsoWeight*scaleFactorWeight/2;
    	totalPreMuMuAcc+=muAccWeight*scaleFactorWeight;
    	totalPreMuMuReco+=muRecoWeight*scaleFactorWeight;
    	totalPreMuMuIso+=muIsoWeight*scaleFactorWeight;
    			
    	totalPredictionMuCSElecAcc_->Fill(Bin, elecAccWeight*scaleFactorWeight);
    	totalPredictionMuCSElecReco_->Fill(Bin, elecRecoWeight*scaleFactorWeight);
    	totalPredictionMuCSElecIso_->Fill(Bin, elecIsoWeight*scaleFactorWeight);
    	totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2;
    	totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2;
    	totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2;
    	totalPreMuElecAcc+=elecAccWeight*scaleFactorWeight;
    	totalPreMuElecReco+=elecRecoWeight*scaleFactorWeight;
    	totalPreMuElecIso+=elecIsoWeight*scaleFactorWeight;
    }
    if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
    {
    	ControlSampleElec_->Fill(Bin, scaledWeight);
          
      totalPrediction_->Fill(Bin, totalWeightDiLep*scaleFactorWeight/2);
      totalPre+=totalWeightDiLep*scaleFactorWeight/2;
      totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2;
      totalPredictionElec_->Fill(Bin, totalWeightDiLep*scaleFactorWeight);
      totalPreElec+=totalWeightDiLep*scaleFactorWeight;
      totalPreElecError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight;
      // isotrackveto applied
      totalPredictionIsoTrackReduction_->Fill(Bin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2;
      totalPredictionElecIsoTrackReduction_->Fill(Bin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight);
      totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight;
      totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight*totalWeightDiLepIsoTrackReduced*scaleFactorWeight;

      // separted closure
      totalPredictionElecCSElecAcc_->Fill(Bin, elecAccWeight*scaleFactorWeight);
      totalPredictionElecCSElecReco_->Fill(Bin, elecRecoWeight*scaleFactorWeight);
      totalPredictionElecCSElecIso_->Fill(Bin, elecIsoWeight*scaleFactorWeight);
      totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2;
      totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2;
      totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2;
      totalPreElecElecAcc+=elecAccWeight*scaleFactorWeight;
      totalPreElecElecReco+=elecRecoWeight*scaleFactorWeight;
      totalPreElecElecIso+=elecIsoWeight*scaleFactorWeight;
          
      totalPredictionElecCSMuAcc_->Fill(Bin, muAccWeight*scaleFactorWeight);
      totalPredictionElecCSMuReco_->Fill(Bin, muRecoWeight*scaleFactorWeight);
      totalPredictionElecCSMuIso_->Fill(Bin, muIsoWeight*scaleFactorWeight);
      totalPreMuAcc+=muAccWeight*scaleFactorWeight/2;
      totalPreMuReco+=muRecoWeight*scaleFactorWeight/2;
      totalPreMuIso+=muIsoWeight*scaleFactorWeight/2;
      totalPreElecMuAcc+=muAccWeight*scaleFactorWeight;
      totalPreElecMuReco+=muRecoWeight*scaleFactorWeight;
      totalPreElecMuIso+=muIsoWeight*scaleFactorWeight;
      }
  }

  std::cout<<"Finished"<<std::endl;

	
  TH1F* FullClosure = (TH1F*) totalExpectationIsoTrackReduction_->Clone();
  FullClosure->Divide(totalPredictionIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosure->SetName("LostLeptonClosure");
  FullClosure->SetTitle("Closure of lost-lepton method");
	
  TH1F* FullClosureMu = (TH1F*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureMu->Divide(totalPredictionMuIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureMu->SetName("LostLeptonClosureMuCS");
  FullClosureMu->SetTitle("Closure of lost-lepton method #mu control-sample");
	
  TH1F* FullClosureElec = (TH1F*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureElec->Divide(totalPredictionElecIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureElec->SetName("LostLeptonClosureElecCS");
  FullClosureElec->SetTitle("Closure of lost-lepton method elec control-sample");

  TH1F* ClosureWoIsoTrack = (TH1F*) totalExpectation_->Clone();
  ClosureWoIsoTrack->Divide(totalPrediction_,totalExpectation_,1,1,"");
  ClosureWoIsoTrack->SetName("ClosureWoIsoTrack");
  ClosureWoIsoTrack->SetTitle("Closure of lost-lepton method (wo IsotrackVeto)");
  
  TH1F* ClosureMuWoIsoTrack = (TH1F*) totalExpectation_->Clone();
  ClosureMuWoIsoTrack->Divide(totalPredictionMu_,totalExpectation_,1,1,"");
  ClosureMuWoIsoTrack->SetName("ClosureMuWoIsoTrack");
  ClosureMuWoIsoTrack->SetTitle("Closure of lost-lepton method #mu control-sample (wo IsotrackVeto)");
  
  TH1F* ClosureElecWoIsoTrack = (TH1F*) totalExpectation_->Clone();
  ClosureElecWoIsoTrack->Divide(totalPredictionElec_,totalExpectation_,1,1,"");
  ClosureElecWoIsoTrack->SetName("ClosureElecWoIsoTrack");
  ClosureElecWoIsoTrack->SetTitle("Closure of lost-lepton method elec control-sample (wo IsotrackVeto)");


  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";
  std::cout<<"\n Muon and Electron CS:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrack<<" +- "<<sqrt(totalPreIsoTrackError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPre<<" +- "<<sqrt(totalPreError)<<std::endl;
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
  FullClosure->Write();
  FullClosureMu->Write();
  FullClosureElec->Write();
  ClosureWoIsoTrack->Write();
  ClosureMuWoIsoTrack->Write();
  ClosureElecWoIsoTrack->Write();
  outPutFile->mkdir("Closures");
  TDirectory *dClosures = (TDirectory*)outPutFile->Get("Closures");

  SaveClosure(totalPredictionMuCSMuAcc_, totalExpectationMuAcc_, dClosures);
  SaveClosure(totalPredictionMuCSMuReco_, totalExpectationMuReco_, dClosures);
  SaveClosure(totalPredictionMuCSMuIso_, totalExpectationMuIso_, dClosures);
	
  SaveClosure(totalPredictionMuCSElecAcc_, totalExpectationElecAcc_, dClosures);
  SaveClosure(totalPredictionMuCSElecReco_, totalExpectationElecReco_, dClosures);
  SaveClosure(totalPredictionMuCSElecIso_, totalExpectationElecIso_, dClosures);
	
  SaveClosure(totalPredictionElecCSMuAcc_, totalExpectationMuAcc_, dClosures);
  SaveClosure(totalPredictionElecCSMuReco_, totalExpectationMuReco_, dClosures);
  SaveClosure(totalPredictionElecCSMuIso_, totalExpectationMuIso_, dClosures);
	
  SaveClosure(totalPredictionElecCSElecAcc_, totalExpectationElecAcc_, dClosures);
  SaveClosure(totalPredictionElecCSElecReco_, totalExpectationElecReco_, dClosures);
  SaveClosure(totalPredictionElecCSElecIso_, totalExpectationElecIso_, dClosures);
	
  SaveClosure(totalPredictionIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
  SaveClosure(totalPredictionMuIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
  SaveClosure(totalPredictionElecIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
	
  outPutFile->mkdir("Expectation");
  TDirectory *dExpectation = (TDirectory*)outPutFile->Get("Expectation");
  dExpectation->cd();
  totalExpectation_->Write();
  outPutFile->mkdir("Prediction");
  TDirectory *dPrediction = (TDirectory*)outPutFile->Get("Prediction");
  dPrediction->cd();
  totalPrediction_->Write();
  totalPredictionMu_->Write();
  totalPredictionElec_->Write();
	
  outPutFile->mkdir("ControlSample");
  TDirectory *dControlSample = (TDirectory*)outPutFile->Get("ControlSample");
  SaveClosure(ControlSampleElec_, ControlSampleMu_, dControlSample);
  dControlSample->cd();
  ControlSampleMu_->Write();
  ControlSampleElec_->Write();


  SearchBins *SearchBins_ = new SearchBins();

  double LLexpErr = 0;
  double LLexp = totalExp_LL_->IntegralAndError(1, 72, LLexpErr);
  double LLpreErr = 0;
  double LLpre = totalPred_LL_->IntegralAndError(1, 72, LLpreErr);

  //printf("Total: & & & & & & & $%3.3f\\pm$%3.3f & $%3.3f\\pm$%3.3f \\\\\n", LLexp, LLexpErr, LLpre, LLpreErr);

  for(int i = 1; i<totalPred_LL_->GetNbinsX()+1; ++i){

    //SearchBin (Number, NJets, BTags, HT, MHT)
    printf("%1.0i & ", i);

    if(SearchBins_->GetSearchBin(i-1)->NJetsmin_<SearchBins_->GetSearchBin(i-1)->NJetsmax_ && SearchBins_->GetSearchBin(i-1)->NJetsmin_>=0){
      printf("%d-", SearchBins_->GetSearchBin(i-1)->NJetsmin_);
      if(SearchBins_->GetSearchBin(i-1)->NJetsmax_<9999) printf("%d & ", SearchBins_->GetSearchBin(i-1)->NJetsmax_);
      else printf("Inf & ");
    }else{
      printf("%d & ", SearchBins_->GetSearchBin(i-1)->NJetsmax_);
    }

    if(SearchBins_->GetSearchBin(i-1)->BTagsmin_<SearchBins_->GetSearchBin(i-1)->BTagsmax_ && SearchBins_->GetSearchBin(i-1)->BTagsmin_>=0){
      printf("%d-",SearchBins_->GetSearchBin(i-1)->BTagsmin_);
      if(SearchBins_->GetSearchBin(i-1)->BTagsmax_<9999) printf("%d & ",SearchBins_->GetSearchBin(i-1)->BTagsmax_);
      else printf("Inf & ");
    }else{
      printf("%d & ", SearchBins_->GetSearchBin(i-1)->BTagsmax_);
    }

    printf("%3.0f-",SearchBins_->GetSearchBin(i-1)->HTmin_);
    if(SearchBins_->GetSearchBin(i-1)->HTmax_<9999) printf("%3.0f & ",SearchBins_->GetSearchBin(i-1)->HTmax_);
    else printf("Inf & ");

    printf("%3.0f-",SearchBins_->GetSearchBin(i-1)->MHTmin_);
    if(SearchBins_->GetSearchBin(i-1)->MHTmax_<9999) printf("%3.0f & ",SearchBins_->GetSearchBin(i-1)->MHTmax_);
    else printf("Inf & ");

    // CS events
    printf("%3.3f (%1.0f) & ", totalCS_LL_->GetBinContent(i), nEvtsCS_LL_->GetBinContent(i));
 
    // Average weight per Bin
    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{-%3.3f}^{+%3.3f}_{-%3.3f}$ & ", avgWeight_LL_->GetBinContent(i), avgWeight_LL_->GetBinError(i), avgWeightStatUp_LL_->GetBinContent(i), avgWeightStatDown_LL_->GetBinContent(i), avgWeightSysUp_LL_->GetBinContent(i), avgWeightSysDown_LL_->GetBinContent(i));

    // Prediction
    // Correct estimate of stat. uncertainty on prediction only possible if data is used or limited MC statistics (e.g. number of events corresponding to 3fb-1)
    // For approximation of stat. uncertainty on prediction using full MC statistics use:
    if(totalCS_LL_->GetBinContent(i)>0.00001) totalPred_LL_->SetBinError(i, sqrt(totalPred_LL_->GetBinContent(i)*totalPred_LL_->GetBinContent(i)/totalCS_LL_->GetBinContent(i)));

    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{-%3.3f}^{+%3.3f}_{-%3.3f}$ & ", totalPred_LL_->GetBinContent(i), totalPred_LL_->GetBinError(i), totalPredStatUp_LL_->GetBinContent(i), totalPredStatDown_LL_->GetBinContent(i), totalPredSysUp_LL_->GetBinContent(i), totalPredSysDown_LL_->GetBinContent(i));

    // Expectation
    printf("$%3.3f\\pm%3.3f$ \\\\\n", totalExp_LL_->GetBinContent(i), totalExp_LL_->GetBinError(i));

  }


  TFile *LLoutPutFile = new TFile(OutputPath_Prediction,"RECREATE"); 
  LLoutPutFile->cd();

  totalExp_LL_->Write();

  totalPred_LL_->Write();
  totalPredStatUp_LL_->Write();
  totalPredStatDown_LL_->Write();
  totalPredSysUp_LL_->Write();
  totalPredSysDown_LL_->Write();

  totalCS_LL_->Write();
  nEvtsCS_LL_->Write();

  avgWeight_LL_->Write();
  avgWeightStatUp_LL_->Write();
  avgWeightStatDown_LL_->Write();  
  avgWeightSysUp_LL_->Write();
  avgWeightSysDown_LL_->Write();
  LLoutPutFile->Close();
	
}