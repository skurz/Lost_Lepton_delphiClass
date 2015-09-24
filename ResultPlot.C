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
  TString InputPath_Prediction_Data("Prediction.root"); // Use same path as above if pure MC prediction wanted
  TString OutputPath_Closure("Closure.root");
  TString OutputPath_Prediction("LLPrediction.root");

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 3000; // only used for MC prediction! Not data tree!

  // Prepare Code for Extrapolation Method
  bool doExtrapolation = false; 

  // Present output in QCD binning
  bool doQCDbinning = false;

  int nSearchBinsTotal = 72;
  if(doQCDbinning) nSearchBinsTotal = 220;
  UShort_t         SearchBin=0;


  //Declaration of leaves types for both trees (Expectation/Prediction)
  UShort_t         Bin;
  UShort_t         BinQCD;
  Double_t         Weight;
  Double_t         scaledWeight;
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
  Float_t         nonClosureUp;
  Float_t         nonClosureDown;
  Float_t         diBosonUp;
  Float_t         diBosonDown;
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
	
  TH1F* ControlSampleMu_ = new TH1F("ControlSampleMu", "ControlSampleMu", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* ControlSampleElec_ = new TH1F("ControlSampleElec", "ControlSampleElec", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectation_ = new TH1F("TotalLostLeptonExpecation", "TotalLostLeptonExpecation", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPrediction_ = new TH1F("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMu_ = new TH1F("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElec_ = new TH1F("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectationIsoTrackReduction_ = new TH1F("TotalLostLeptonExpecationIsoTrackReduction", "TotalLostLeptonExpecationIsoTrackReduction", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionIsoTrackReduction", "TotalLostLeptonPredictionIsoTrackReduction", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionMuIsoTrackReduction", "TotalLostLeptonPredictionMuIsoTrackReduction", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecIsoTrackReduction_ = new TH1F("TotalLostLeptonPredictionElecIsoTrackReduction", "TotalLostLeptonPredictionElecIsoTrackReduction", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  // separted closure
  TH1F* totalExpectationMuAcc_ = new TH1F("TotalLostLeptonExpecationMuAcc", "TotalLostLeptonExpecationMuAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSMuAcc_ = new TH1F("TotalLostLeptonPredictionMuCSMuAcc", "TotalLostLeptonPredictionMuCSMuAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSMuAcc_ = new TH1F("TotalLostLeptonPredictionElecCSMuAcc", "TotalLostLeptonPredictionElecCSMuAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectationMuReco_ = new TH1F("TotalLostLeptonExpecationMuReco", "TotalLostLeptonExpecationMuReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSMuReco_ = new TH1F("TotalLostLeptonPredictionMuCSMuReco", "TotalLostLeptonPredictionMuCSMuReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSMuReco_ = new TH1F("TotalLostLeptonPredictionElecCSMuReco", "TotalLostLeptonPredictionElecCSMuReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectationMuIso_ = new TH1F("TotalLostLeptonExpecationMuIso", "TotalLostLeptonExpecationMuIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSMuIso_ = new TH1F("TotalLostLeptonPredictionMuCSMuIso", "TotalLostLeptonPredictionMuCSMuIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSMuIso_ = new TH1F("TotalLostLeptonPredictionElecCSMuIso", "TotalLostLeptonPredictionElecCSMuIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);	
	
  TH1F* totalExpectationElecAcc_ = new TH1F("TotalLostLeptonExpecationElecAcc", "TotalLostLeptonExpecationElecAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSElecAcc_ = new TH1F("TotalLostLeptonPredictionMuCSElecAcc", "TotalLostLeptonPredictionMuCSElecAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSElecAcc_ = new TH1F("TotalLostLeptonPredictionElecCSElecAcc", "TotalLostLeptonPredictionElecCSElecAcc", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectationElecReco_ = new TH1F("TotalLostLeptonExpecationElecReco", "TotalLostLeptonExpecationElecReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSElecReco_ = new TH1F("TotalLostLeptonPredictionMuCSElecReco", "TotalLostLeptonPredictionMuCSElecReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSElecReco_ = new TH1F("TotalLostLeptonPredictionElecCSElecReco", "TotalLostLeptonPredictionElecCSElecReco", nSearchBinsTotal, 1, nSearchBinsTotal+1);
	
  TH1F* totalExpectationElecIso_ = new TH1F("TotalLostLeptonExpecationElecIso", "TotalLostLeptonExpecationElecIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionMuCSElecIso_ = new TH1F("TotalLostLeptonPredictionMuCSElecIso", "TotalLostLeptonPredictionMuCSElecIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredictionElecCSElecIso_ = new TH1F("TotalLostLeptonPredictionElecCSElecIso", "TotalLostLeptonPredictionElecCSElecIso", nSearchBinsTotal, 1, nSearchBinsTotal+1);


  // Define histrograms to do totalPrediction per SearchBin
  TH1F* totalExp_LL_ = new TH1F("totalExp_LL","totalExp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TH1F* totalPred_LL_ = new TH1F("totalPred_LL","totalPred_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredStatUp_LL_ = new TH1F("totalPredStatUp_LL","totalPredStatUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredStatDown_LL_ = new TH1F("totalPredStatDown_LL","totalPredStatDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredSysUp_LL_ = new TH1F("totalPredSysUp_LL","totalPredSysUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredSysDown_LL_ = new TH1F("totalPredSysDown_LL","totalPredSysDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredNonClosureUp_LL_ = new TH1F("totalPredNonClosureUp_LL","totalPredNonClosureUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredNonClosureDown_LL_ = new TH1F("totalPredNonClosureDown_LL","totalPredNonClosureDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredDiBosonUp_LL_ = new TH1F("totalPredDiBosonUp_LL","totalPredDiBosonUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredDiBosonDown_LL_ = new TH1F("totalPredDiBosonDown_LL","totalPredDiBosonDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TH1F* totalCS_LL_ = new TH1F("totalCS_LL","totalCS_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* nEvtsCS_LL_ = new TH1F("nEvtsCS_LL","nEvtsCS_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TProfile* avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightStatUp_LL_ = new TProfile("avgWeightStatUp_LL","avgWeightStatUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightStatDown_LL_ = new TProfile("avgWeightStatDown_LL","avgWeightStatDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightSysUp_LL_ = new TProfile("avgWeightSysUp_LL","avgWeightSysUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightSysDown_LL_ = new TProfile("avgWeightSysDown_LL","avgWeightSysDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightNonClosureUp_LL_ = new TProfile("avgWeightNonClosureUp_LL","avgWeightNonClosureUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightNonClosureDown_LL_ = new TProfile("avgWeightNonClosureDown_LL","avgWeightNonClosureDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightDiBosonUp_LL_ = new TProfile("avgWeightDiBosonUp_LL","avgWeightDiBosonUp_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightDiBosonDown_LL_ = new TProfile("avgWeightDiBosonDown_LL","avgWeightDiBosonDown_LL", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  totalPred_LL_->Sumw2();
  totalPredStatUp_LL_->Sumw2();
  totalPredStatDown_LL_->Sumw2();
  totalPredSysUp_LL_->Sumw2();
  totalPredSysDown_LL_->Sumw2();
  totalPredNonClosureUp_LL_->Sumw2();
  totalPredNonClosureDown_LL_->Sumw2();
  totalPredDiBosonUp_LL_->Sumw2();
  totalPredDiBosonDown_LL_->Sumw2();

  totalCS_LL_->Sumw2();

  avgWeight_LL_->Sumw2();
  avgWeightStatUp_LL_->Sumw2();
  avgWeightStatDown_LL_->Sumw2();
  avgWeightSysUp_LL_->Sumw2();
  avgWeightSysDown_LL_->Sumw2();
  avgWeightNonClosureUp_LL_->Sumw2();
  avgWeightNonClosureDown_LL_->Sumw2();
  avgWeightDiBosonUp_LL_->Sumw2();
  avgWeightDiBosonDown_LL_->Sumw2();

  // Define histrograms to do totalPrediction per SearchBin (MC)
  TH1F* totalExp_LL_MC_ = new TH1F("totalExp_LL_MC","totalExp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TH1F* totalPred_LL_MC_ = new TH1F("totalPred_LL_MC","totalPred_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredStatUp_LL_MC_ = new TH1F("totalPredStatUp_LL_MC","totalPredStatUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredStatDown_LL_MC_ = new TH1F("totalPredStatDown_LL_MC","totalPredStatDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredSysUp_LL_MC_ = new TH1F("totalPredSysUp_LL_MC","totalPredSysUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredSysDown_LL_MC_ = new TH1F("totalPredSysDown_LL_MC","totalPredSysDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredNonClosureUp_LL_MC_ = new TH1F("totalPredNonClosureUp_LL_MC","totalPredNonClosureUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredNonClosureDown_LL_MC_ = new TH1F("totalPredNonClosureDown_LL_MC","totalPredNonClosureDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredDiBosonUp_LL_MC_ = new TH1F("totalPredDiBosonUp_LL_MC","totalPredDiBosonUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* totalPredDiBosonDown_LL_MC_ = new TH1F("totalPredDiBosonDown_LL_MC","totalPredDiBosonDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TH1F* totalCS_LL_MC_ = new TH1F("totalCS_LL_MC","totalCS_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TH1F* nEvtsCS_LL_MC_ = new TH1F("nEvtsCS_LL_MC","nEvtsCS_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  TProfile* avgWeight_LL_MC_ = new TProfile("avgWeight_LL_MC","avgWeight_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightStatUp_LL_MC_ = new TProfile("avgWeightStatUp_LL_MC","avgWeightStatUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightStatDown_LL_MC_ = new TProfile("avgWeightStatDown_LL_MC","avgWeightStatDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightSysUp_LL_MC_ = new TProfile("avgWeightSysUp_LL_MC","avgWeightSysUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightSysDown_LL_MC_ = new TProfile("avgWeightSysDown_LL_MC","avgWeightSysDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightNonClosureUp_LL_MC_ = new TProfile("avgWeightNonClosureUp_LL_MC","avgWeightNonClosureUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightNonClosureDown_LL_MC_ = new TProfile("avgWeightNonClosureDown_LL_MC","avgWeightNonClosureDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightDiBosonUp_LL_MC_ = new TProfile("avgWeightDiBosonUp_LL_MC","avgWeightDiBosonUp_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);
  TProfile* avgWeightDiBosonDown_LL_MC_ = new TProfile("avgWeightDiBosonDown_LL_MC","avgWeightDiBosonDown_LL_MC", nSearchBinsTotal, 1, nSearchBinsTotal+1);

  totalPred_LL_MC_->Sumw2();
  totalPredStatUp_LL_MC_->Sumw2();
  totalPredStatDown_LL_MC_->Sumw2();
  totalPredSysUp_LL_MC_->Sumw2();
  totalPredSysDown_LL_MC_->Sumw2();
  totalPredNonClosureUp_LL_MC_->Sumw2();
  totalPredNonClosureDown_LL_MC_->Sumw2();
  totalPredDiBosonUp_LL_MC_->Sumw2();
  totalPredDiBosonDown_LL_MC_->Sumw2();

  totalCS_LL_MC_->Sumw2();

  avgWeight_LL_MC_->Sumw2();
  avgWeightStatUp_LL_MC_->Sumw2();
  avgWeightStatDown_LL_MC_->Sumw2();
  avgWeightSysUp_LL_MC_->Sumw2();
  avgWeightSysDown_LL_MC_->Sumw2();
  avgWeightNonClosureUp_LL_MC_->Sumw2();
  avgWeightNonClosureDown_LL_MC_->Sumw2();
  avgWeightDiBosonUp_LL_MC_->Sumw2();
  avgWeightDiBosonDown_LL_MC_->Sumw2();


	
  //Expectation Tree
  gROOT->Reset();
  TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation);
  if (!fExp) {
    fExp = new TFile(InputPath_Expectation);
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
  LostLeptonExpectation->SetBranchStatus("BinQCD",1);
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
  LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
	
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

    if(doQCDbinning) SearchBin = BinQCD;
    else SearchBin = Bin;

    // total expectation
    if(doExtrapolation || SearchBin > 900) continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(Expectation==1 && NJets>3.1)
    {
    	totalExpectation_->Fill(SearchBin, scaledWeight);
    	totalExp+=scaledWeight;
    	totalExpError+= scaledWeight*scaledWeight;
    }
    if(Expectation==1 && ExpectationReductionIsoTrack==0 && NJets>3.1)
    {
    	totalExpectationIsoTrackReduction_->Fill(SearchBin, scaledWeight);
    	totalExpIsoTrack+=scaledWeight;
    	totalExpIsoTrackError+= scaledWeight*scaledWeight;
      totalExp_LL_->Fill(SearchBin, scaledWeight);
    }
    if(muAcc==0)
    {
    	totalExpectationMuAcc_->Fill(SearchBin, scaledWeight);
    	totalExpMuAcc+=scaledWeight;
    }
    if(muReco==0)
    {
    	totalExpectationMuReco_->Fill(SearchBin, scaledWeight);
    	totalExpMuReco+=scaledWeight;
    }
    if(muIso==0)
    {
    	totalExpectationMuIso_->Fill(SearchBin, scaledWeight);
    	totalExpMuIso+=scaledWeight;
    }
					
    if(elecAcc==0)
    {
    	totalExpectationElecAcc_->Fill(SearchBin, scaledWeight);
    	totalExpElecAcc+=scaledWeight;
    }
    if(elecReco==0)
    {
    	totalExpectationElecReco_->Fill(SearchBin, scaledWeight);
    	totalExpElecReco+=scaledWeight;
    }
    if(elecIso==0)
    {
    	totalExpectationElecIso_->Fill(SearchBin, scaledWeight);
    	totalExpElecIso+=scaledWeight;
    }
  }
	
  std::cout<<"Finished"<<std::endl;

  //Prediction MC Tree
  gROOT->Reset();
  TFile *fPreMC = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction);
  if (!fPreMC) {
    fPreMC = new TFile(InputPath_Prediction);
  }
  TTree* LostLeptonPrediction = (TTree*) fPreMC->Get("LostLeptonPrediction");

  LostLeptonPrediction->SetBranchStatus("*",0);
  LostLeptonPrediction->SetBranchStatus("HT",1);
  LostLeptonPrediction->SetBranchStatus("MHT",1);
  LostLeptonPrediction->SetBranchStatus("NJets",1);
  LostLeptonPrediction->SetBranchStatus("BTags",1);
  LostLeptonPrediction->SetBranchStatus("Weight",1);
  LostLeptonPrediction->SetBranchStatus("Bin",1);
  LostLeptonPrediction->SetBranchStatus("BinQCD",1);
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
  LostLeptonPrediction->SetBranchStatus("nonClosureUp",1);
  LostLeptonPrediction->SetBranchStatus("diBosonUp",1);
  LostLeptonPrediction->SetBranchStatus("totalUncUp",1);
  LostLeptonPrediction->SetBranchStatus("totalStatDown",1);
  LostLeptonPrediction->SetBranchStatus("totalSysDown",1);
  LostLeptonPrediction->SetBranchStatus("nonClosureDown",1);
  LostLeptonPrediction->SetBranchStatus("diBosonDown",1);
  LostLeptonPrediction->SetBranchStatus("totalUncDown",1);
  
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
  LostLeptonPrediction->SetBranchAddress("BinQCD",&BinQCD);
  
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
  LostLeptonPrediction->SetBranchAddress("nonClosureUp",&nonClosureUp);
  LostLeptonPrediction->SetBranchAddress("diBosonUp", &diBosonUp);
  LostLeptonPrediction->SetBranchAddress("totalUncUp", &totalUncUp);

  LostLeptonPrediction->SetBranchAddress("totalStatDown", &totalStatDown);
  LostLeptonPrediction->SetBranchAddress("totalSysDown", &totalSysDown);
  LostLeptonPrediction->SetBranchAddress("nonClosureDown",&nonClosureDown);
  LostLeptonPrediction->SetBranchAddress("diBosonDown", &diBosonDown);
  LostLeptonPrediction->SetBranchAddress("totalUncDown", &totalUncDown);


  std::cout<<"Loop on Prediction (MC)"<<std::endl;
  
  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);

    if(doQCDbinning) SearchBin = BinQCD;
    else SearchBin = Bin;
    
    if(doExtrapolation || SearchBin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    totalPred_LL_MC_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2);
    totalPredStatUp_LL_MC_->Fill(SearchBin, totalStatUp*scaleFactorWeight/2);
    totalPredStatDown_LL_MC_->Fill(SearchBin, totalStatDown*scaleFactorWeight/2);
    totalPredSysUp_LL_MC_->Fill(SearchBin, totalSysUp*scaleFactorWeight/2);
    totalPredSysDown_LL_MC_->Fill(SearchBin, totalSysDown*scaleFactorWeight/2);
    totalPredNonClosureUp_LL_MC_->Fill(SearchBin, nonClosureUp*scaleFactorWeight/2);
    totalPredNonClosureDown_LL_MC_->Fill(SearchBin, nonClosureDown*scaleFactorWeight/2);
    totalPredDiBosonUp_LL_MC_->Fill(SearchBin, diBosonUp*scaleFactorWeight/2);
    totalPredDiBosonDown_LL_MC_->Fill(SearchBin, diBosonDown*scaleFactorWeight/2);

    totalCS_LL_MC_->Fill(SearchBin, scaledWeight);
    nEvtsCS_LL_MC_->Fill(SearchBin);

    avgWeight_LL_MC_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced/Weight/2);
    avgWeightStatUp_LL_MC_->Fill(SearchBin, totalStatUp/Weight/2);
    avgWeightStatDown_LL_MC_->Fill(SearchBin, totalStatDown/Weight/2);
    avgWeightSysUp_LL_MC_->Fill(SearchBin, totalSysUp/Weight/2);
    avgWeightSysDown_LL_MC_->Fill(SearchBin, totalSysDown/Weight/2);
    avgWeightNonClosureUp_LL_MC_->Fill(SearchBin, nonClosureUp/Weight/2);
    avgWeightNonClosureDown_LL_MC_->Fill(SearchBin, nonClosureDown/Weight/2);
    avgWeightDiBosonUp_LL_MC_->Fill(SearchBin, diBosonUp/Weight/2);
    avgWeightDiBosonDown_LL_MC_->Fill(SearchBin, diBosonDown/Weight/2);
  }

  std::cout<<"Finished"<<std::endl;

  //Prediction Data Tree
  gROOT->Reset();
  TFile *fPre = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction_Data);
  if (!fPre) {
    fPre = new TFile(InputPath_Prediction_Data);
  }
  TTree* LostLeptonPredictionData = (TTree*) fPre->Get("LostLeptonPrediction");

  LostLeptonPredictionData->SetBranchStatus("*",0);
  LostLeptonPredictionData->SetBranchStatus("HT",1);
  LostLeptonPredictionData->SetBranchStatus("MHT",1);
  LostLeptonPredictionData->SetBranchStatus("NJets",1);
  LostLeptonPredictionData->SetBranchStatus("BTags",1);
  LostLeptonPredictionData->SetBranchStatus("Weight",1);
  LostLeptonPredictionData->SetBranchStatus("Bin",1);
  LostLeptonPredictionData->SetBranchStatus("BinQCD",1);
  LostLeptonPredictionData->SetBranchStatus("MTW",1);
  LostLeptonPredictionData->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPredictionData->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPredictionData->SetBranchStatus("muIsoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("totalStatUp",1);
  LostLeptonPredictionData->SetBranchStatus("totalSysUp",1);
  LostLeptonPredictionData->SetBranchStatus("nonClosureUp",1);
  LostLeptonPredictionData->SetBranchStatus("diBosonUp",1);
  LostLeptonPredictionData->SetBranchStatus("totalUncUp",1);
  LostLeptonPredictionData->SetBranchStatus("totalStatDown",1);
  LostLeptonPredictionData->SetBranchStatus("totalSysDown",1);
  LostLeptonPredictionData->SetBranchStatus("nonClosureDown",1);
  LostLeptonPredictionData->SetBranchStatus("diBosonDown",1);
  LostLeptonPredictionData->SetBranchStatus("totalUncDown",1);
  
  LostLeptonPredictionData->SetBranchAddress("HT",&HT);
  LostLeptonPredictionData->SetBranchAddress("MHT",&MHT);
  LostLeptonPredictionData->SetBranchAddress("NJets",&NJets);
  LostLeptonPredictionData->SetBranchAddress("BTags",&BTags);
  LostLeptonPredictionData->SetBranchAddress("Weight",&Weight);
  LostLeptonPredictionData->SetBranchAddress("Bin",&Bin);
  LostLeptonPredictionData->SetBranchAddress("BinQCD",&BinQCD);
	
  LostLeptonPredictionData->SetBranchAddress("MTW",&MTW);
  LostLeptonPredictionData->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  LostLeptonPredictionData->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
	
  LostLeptonPredictionData->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPredictionData->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("muAccWeight",&muAccWeight);
	
  LostLeptonPredictionData->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPredictionData->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("elecIsoWeight",&elecIsoWeight);

  LostLeptonPredictionData->SetBranchAddress("totalStatUp", &totalStatUp);
  LostLeptonPredictionData->SetBranchAddress("totalSysUp", &totalSysUp);
  LostLeptonPredictionData->SetBranchAddress("nonClosureUp",&nonClosureUp);
  LostLeptonPredictionData->SetBranchAddress("diBosonUp", &diBosonUp);
  LostLeptonPredictionData->SetBranchAddress("totalUncUp", &totalUncUp);

  LostLeptonPredictionData->SetBranchAddress("totalStatDown", &totalStatDown);
  LostLeptonPredictionData->SetBranchAddress("totalSysDown", &totalSysDown);
  LostLeptonPredictionData->SetBranchAddress("nonClosureDown",&nonClosureDown);
  LostLeptonPredictionData->SetBranchAddress("diBosonDown", &diBosonDown);
  LostLeptonPredictionData->SetBranchAddress("totalUncDown", &totalUncDown);

/*
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
*/
  std::cout<<"Loop on Prediction (Data)"<<std::endl;
	
  nentries = LostLeptonPredictionData->GetEntries();
  nbytes = 0;
  double scaleMC = 1.0;
  if(InputPath_Prediction_Data != InputPath_Prediction) scaleFactorWeight = 1.0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPredictionData->GetEntry(i);

    if(doQCDbinning) SearchBin = BinQCD;
    else SearchBin = Bin;
    
    if(doExtrapolation || SearchBin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(InputPath_Prediction_Data != InputPath_Prediction) scaleMC = Weight;

    totalPred_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC);
    totalPredStatUp_LL_->Fill(SearchBin, totalStatUp*scaleFactorWeight/2/scaleMC);
    totalPredStatDown_LL_->Fill(SearchBin, totalStatDown*scaleFactorWeight/2/scaleMC);
    totalPredSysUp_LL_->Fill(SearchBin, totalSysUp*scaleFactorWeight/2/scaleMC);
    totalPredSysDown_LL_->Fill(SearchBin, totalSysDown*scaleFactorWeight/2/scaleMC);
    totalPredNonClosureUp_LL_->Fill(SearchBin, nonClosureUp*scaleFactorWeight/2/scaleMC);
    totalPredNonClosureDown_LL_->Fill(SearchBin, nonClosureDown*scaleFactorWeight/2/scaleMC);
    totalPredDiBosonUp_LL_->Fill(SearchBin, diBosonUp*scaleFactorWeight/2/scaleMC);
    totalPredDiBosonDown_LL_->Fill(SearchBin, diBosonDown*scaleFactorWeight/2/scaleMC);

    totalCS_LL_->Fill(SearchBin, scaledWeight/scaleMC);
    nEvtsCS_LL_->Fill(SearchBin);

    avgWeight_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced/Weight/2);
    avgWeightStatUp_LL_->Fill(SearchBin, totalStatUp/Weight/2);
    avgWeightStatDown_LL_->Fill(SearchBin, totalStatDown/Weight/2);
    avgWeightSysUp_LL_->Fill(SearchBin, totalSysUp/Weight/2);
    avgWeightSysDown_LL_->Fill(SearchBin, totalSysDown/Weight/2);
    avgWeightNonClosureUp_LL_->Fill(SearchBin, nonClosureUp/Weight/2);
    avgWeightNonClosureDown_LL_->Fill(SearchBin, nonClosureDown/Weight/2);
    avgWeightDiBosonUp_LL_->Fill(SearchBin, diBosonUp/Weight/2);
    avgWeightDiBosonDown_LL_->Fill(SearchBin, diBosonDown/Weight/2);

    if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0){

    	ControlSampleMu_->Fill(SearchBin, scaledWeight/scaleMC);
    			
    	totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
    	totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
    	totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionMu_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
    	totalPreMu+=totalWeightDiLep*scaleFactorWeight/scaleMC;
    	totalPreMuError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
    	// isotrackveto applied
    	totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC/scaleMC;
    	totalPredictionMuIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC);
    	totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC;
    	totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC/scaleMC;

    	// separted closure
    	totalPredictionMuCSMuAcc_->Fill(SearchBin, muAccWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSMuReco_->Fill(SearchBin, muRecoWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSMuIso_->Fill(SearchBin, muIsoWeight*scaleFactorWeight/scaleMC);
    	totalPreMuAcc+=muAccWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuReco+=muRecoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuIso+=muIsoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuMuAcc+=muAccWeight*scaleFactorWeight/scaleMC;
    	totalPreMuMuReco+=muRecoWeight*scaleFactorWeight/scaleMC;
    	totalPreMuMuIso+=muIsoWeight*scaleFactorWeight/scaleMC;
    			
    	totalPredictionMuCSElecAcc_->Fill(SearchBin, elecAccWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSElecReco_->Fill(SearchBin, elecRecoWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSElecIso_->Fill(SearchBin, elecIsoWeight*scaleFactorWeight/scaleMC);
    	totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2/scaleMC;
    	totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuElecAcc+=elecAccWeight*scaleFactorWeight/scaleMC;
    	totalPreMuElecReco+=elecRecoWeight*scaleFactorWeight/scaleMC;
    	totalPreMuElecIso+=elecIsoWeight*scaleFactorWeight/scaleMC;
    }
    if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
    {
    	ControlSampleElec_->Fill(SearchBin, scaledWeight/scaleMC);
          
      totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
      totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
      totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElec_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
      totalPreElec+=totalWeightDiLep*scaleFactorWeight/scaleMC;
      totalPreElecError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
      // isotrackveto applied
      totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElecIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC);
      totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC;
      totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReduced*scaleFactorWeight*totalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC/scaleMC;

      // separted closure
      totalPredictionElecCSElecAcc_->Fill(SearchBin, elecAccWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSElecReco_->Fill(SearchBin, elecRecoWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSElecIso_->Fill(SearchBin, elecIsoWeight*scaleFactorWeight/scaleMC);
      totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecElecAcc+=elecAccWeight*scaleFactorWeight/scaleMC;
      totalPreElecElecReco+=elecRecoWeight*scaleFactorWeight/scaleMC;
      totalPreElecElecIso+=elecIsoWeight*scaleFactorWeight/scaleMC;
          
      totalPredictionElecCSMuAcc_->Fill(SearchBin, muAccWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSMuReco_->Fill(SearchBin, muRecoWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSMuIso_->Fill(SearchBin, muIsoWeight*scaleFactorWeight/scaleMC);
      totalPreMuAcc+=muAccWeight*scaleFactorWeight/2/scaleMC;
      totalPreMuReco+=muRecoWeight*scaleFactorWeight/2/scaleMC;
      totalPreMuIso+=muIsoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecMuAcc+=muAccWeight*scaleFactorWeight/scaleMC;
      totalPreElecMuReco+=muRecoWeight*scaleFactorWeight/scaleMC;
      totalPreElecMuIso+=muIsoWeight*scaleFactorWeight/scaleMC;
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


  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);

  double LLexpErr = 0;
  double LLexp = totalExp_LL_->IntegralAndError(1, 72, LLexpErr);
  double LLpreErr = 0;
  double LLpre = totalPred_LL_->IntegralAndError(1, 72, LLpreErr);

  //printf("Total: & & & & & & & $%3.3f\\pm$%3.3f & $%3.3f\\pm$%3.3f \\\\\n", LLexp, LLexpErr, LLpre, LLpreErr);

  if(InputPath_Prediction_Data == InputPath_Prediction) std::cout<<"ATTENTION: Full MC statistics used to do prediction! Only approx. stat. unc. (~sqrt(n)) shown on prediction!"<<std::endl;

  if(InputPath_Prediction_Data != InputPath_Prediction) printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & CS\\_data & avg. weight (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");
  else printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");

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

    // CS events (MC)
    printf("%3.3f (%1.0f) & ", totalCS_LL_MC_->GetBinContent(i), nEvtsCS_LL_MC_->GetBinContent(i));
 
    // Average weight per Bin (MC)
    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", avgWeight_LL_MC_->GetBinContent(i), avgWeight_LL_MC_->GetBinError(i), avgWeightStatUp_LL_MC_->GetBinContent(i), avgWeightStatDown_LL_MC_->GetBinContent(i), avgWeightSysUp_LL_MC_->GetBinContent(i), avgWeightSysDown_LL_MC_->GetBinContent(i), avgWeightNonClosureUp_LL_MC_->GetBinContent(i), avgWeightNonClosureDown_LL_MC_->GetBinContent(i));
    
    // CS events (data)
    if(InputPath_Prediction_Data != InputPath_Prediction) printf("%1.0f & ", totalCS_LL_->GetBinContent(i));

    // Average weight per Bin (data)
    if(InputPath_Prediction_Data != InputPath_Prediction) printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", avgWeight_LL_->GetBinContent(i), avgWeight_LL_->GetBinError(i), avgWeightStatUp_LL_->GetBinContent(i), avgWeightStatDown_LL_->GetBinContent(i), avgWeightSysUp_LL_->GetBinContent(i), avgWeightSysDown_LL_->GetBinContent(i), avgWeightNonClosureUp_LL_->GetBinContent(i), avgWeightNonClosureDown_LL_->GetBinContent(i));

    // Prediction
    // Correct estimate of stat. uncertainty on prediction only possible if data is used or limited MC statistics (e.g. number of events corresponding to 3fb-1)
    // For approximation of stat. uncertainty on prediction using full MC statistics use:
    if(InputPath_Prediction_Data == InputPath_Prediction) if(totalCS_LL_->GetBinContent(i)>0.00001) totalPred_LL_->SetBinError(i, sqrt(totalPred_LL_->GetBinContent(i)*totalPred_LL_->GetBinContent(i)/totalCS_LL_->GetBinContent(i)));

    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", totalPred_LL_->GetBinContent(i), totalPred_LL_->GetBinError(i), totalPredStatUp_LL_->GetBinContent(i), totalPredStatDown_LL_->GetBinContent(i), totalPredSysUp_LL_->GetBinContent(i), totalPredSysDown_LL_->GetBinContent(i), totalPredNonClosureUp_LL_->GetBinContent(i), totalPredNonClosureDown_LL_->GetBinContent(i));

    // Expectation
    printf("$%3.3f\\pm%3.3f$ \\\\\n", totalExp_LL_->GetBinContent(i), totalExp_LL_->GetBinError(i));

  }


  TFile *LLoutPutFile = new TFile(OutputPath_Prediction,"RECREATE");

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Expectation");
  TDirectory *dExp = (TDirectory*)LLoutPutFile->Get("Expectation");
  dExp->cd();

  totalExp_LL_->Write();

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_data");
  TDirectory *dPreData = (TDirectory*)LLoutPutFile->Get("Prediction_data");
  dPreData->cd();

  totalPred_LL_->Write();
  totalPredStatUp_LL_->Write();
  totalPredStatDown_LL_->Write();
  totalPredSysUp_LL_->Write();
  totalPredSysDown_LL_->Write();
  totalPredNonClosureUp_LL_->Write();
  totalPredNonClosureDown_LL_->Write();
  totalPredDiBosonUp_LL_->Write();
  totalPredDiBosonDown_LL_->Write();

  totalCS_LL_->Write();
  nEvtsCS_LL_->Write();

  avgWeight_LL_->Write();
  avgWeightStatUp_LL_->Write();
  avgWeightStatDown_LL_->Write();  
  avgWeightSysUp_LL_->Write();
  avgWeightSysDown_LL_->Write();
  avgWeightNonClosureUp_LL_->Write();
  avgWeightNonClosureDown_LL_->Write();
  avgWeightDiBosonUp_LL_->Write();
  avgWeightDiBosonDown_LL_->Write();

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_MC");
  TDirectory *dPreMC = (TDirectory*)LLoutPutFile->Get("Prediction_MC");
  dPreMC->cd();

  totalPred_LL_MC_->Write();
  totalPredStatUp_LL_MC_->Write();
  totalPredStatDown_LL_MC_->Write();
  totalPredSysUp_LL_MC_->Write();
  totalPredSysDown_LL_MC_->Write();
  totalPredNonClosureUp_LL_MC_->Write();
  totalPredNonClosureDown_LL_MC_->Write();
  totalPredDiBosonUp_LL_MC_->Write();
  totalPredDiBosonDown_LL_MC_->Write();

  totalCS_LL_MC_->Write();
  nEvtsCS_LL_MC_->Write();

  avgWeight_LL_MC_->Write();
  avgWeightStatUp_LL_MC_->Write();
  avgWeightStatDown_LL_MC_->Write();  
  avgWeightSysUp_LL_MC_->Write();
  avgWeightSysDown_LL_MC_->Write();
  avgWeightNonClosureUp_LL_MC_->Write();
  avgWeightNonClosureDown_LL_MC_->Write();
  avgWeightDiBosonUp_LL_MC_->Write();
  avgWeightDiBosonDown_LL_MC_->Write();

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Closure");
  TDirectory *dClosure = (TDirectory*)LLoutPutFile->Get("Closure");
  dClosure->cd();

  TH1F *ClosureTest = (TH1F*) totalPred_LL_MC_->Clone("ClosureTest");
  ClosureTest->Divide(totalExp_LL_);
  ClosureTest->SetTitle("Prediction / Expectation");
  ClosureTest->Write();

  LLoutPutFile->Close();
	
}