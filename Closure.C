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
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <vector>
#include "LLTools.h"
#include "THEff.h"
#include "TROOT.h"
#include "TSystem.h"


//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder);
void SetBinLabel(TH1D* hist);
void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir);

using std::string;

void Closure(string InputPath_Expectation="Expectation.root",
		string InputPath_Efficiencies="Efficiencies.root",
		string InputPath_Prediction="Prediction.root",
		string OutputPath_Closure="Closure.root")
{
  // Weight MC events with bTag probabilities
  bool doBtagProbabilities = true;

  // Present output in QCD binning
  bool doQCDbinning = false;

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 35862;  //in units of [pb]

  // Begin of Code
  int nSearchBinsTotal = 174;
  if(doQCDbinning){
    nSearchBinsTotal = 223;
  }

  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);


  TH1::SetDefaultSumw2();

  UShort_t         SearchBin=0;


  //Declaration of leaves types for both trees (Expectation/Prediction)
  UShort_t         Bin;
  UShort_t         BinQCD;
  Double_t         Weight;
  Double_t         scaledWeight;
  Double_t         HT;
  Double_t         MHT;
  Double_t         MHTPhi;
  Int_t            NJets;
  Int_t            BTags;

  std::vector<UShort_t> Bin_bTags(4, 0.);
  std::vector<double> *bTagProb=0;
  
  UShort_t        Expectation;
  UShort_t        muAcc;
  UShort_t        muReco;
  UShort_t        muIso;
  UShort_t        elecAcc;
  UShort_t        elecReco;
  UShort_t        elecIso;
  Int_t           isoTracksNum;
  UShort_t        ExpectationDiLep;
  UShort_t        ExpectationReductionIsoTrack;

  Float_t         MTW;
  UShort_t        MuonsNum;
  UShort_t        ElectronsNum;

  std::vector<TLorentzVector>* Muons=0;
  std::vector<TLorentzVector>* Electrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<TLorentzVector> *GenElectrons=0;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReduced;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;
  std::vector<Float_t>*         totalWeight_BTags=0;
  std::vector<Float_t>*         totalWeight_BTags_noIsoTrack=0;
  std::vector<Float_t>*         totalWeight_BTags_MTW=0;
  std::vector<Float_t>* totalWeight_BTags_MuAcc_=0;
  std::vector<Float_t>* totalWeight_BTags_MuReco_=0;
  std::vector<Float_t>* totalWeight_BTags_MuIso_=0;
  std::vector<Float_t>* totalWeight_BTags_ElecAcc_=0;
  std::vector<Float_t>* totalWeight_BTags_ElecReco_=0;
  std::vector<Float_t>* totalWeight_BTags_ElecIso_=0;

  Float_t         muTotalWeightDiLepIsoTrackReduced;
  Float_t         elecTotalWeightDiLepIsoTrackReduced;
  
  Float_t         muIsoWeight;
  Float_t         muRecoWeight;
  Float_t         muAccWeight;

  Float_t         elecAccWeight;
  Float_t         elecRecoWeight;
  Float_t         elecIsoWeight;

  Float_t         diLepLostWeight;

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

  TH1D* totalMuons_ = new TH1D("totalMuons", "totalMuons", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalElectrons_ = new TH1D("totalElectrons", "totalElectrons", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectation_ = new TH1D("TotalLostLeptonExpectation", "TotalLostLeptonExpectation", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalExpectationWoIso_ = new TH1D("TotalExpectationWoIso", "TotalExpectationWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalExpectationDiLep_ = new TH1D("TotalExpectationDiLep", "TotalExpectationDiLep", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalExpectationMuMTW_ = new TH1D("TotalExpectationMuMTW", "TotalExpectationMuMTW", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalExpectationElecMTW_ = new TH1D("TotalExpectationElecMTW", "TotalExpectationElecMTW", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  // Equal dist:
  // HT:  0, 300., 2300.
  // MHT: 20, 250., 1250.
  // Search bins:
  // HT: nHTbins = 4 HTbins={300., 500., 1000., 2500.} fine: HTbins={300., 500., 750., 1000., 1500., 2500.}
  // MHT: nMHTbins = 6 MHTbins={250., 300., 350., 500., 750., 1250.}
  const int nHTbins = 6-1;
  const double HTbins[] = {300., 500., 750., 1000., 1500., 2500.};
  const int nMHTbins = 6-1;
  const double MHTbins[] = {250., 300., 350., 500., 750., 1250.};
  const int nNJetsbins = 6-1;
  const double NJetsbins[] = {1.5, 2.5, 4.5, 6.5, 8.5, 20.};
  TH1D* totalExpectation_HT_ = new TH1D("totalExpectation_HT","totalExpectation_HT", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_ = new TH1D("totalExpectation_MHT","totalExpectation_MHT", nMHTbins, MHTbins);
  TH1D* totalExpectation_NJets_ = new TH1D("totalExpectation_NJets","totalExpectation_NJets", nNJetsbins, NJetsbins);
  TH1D* totalExpectation_BTags_ = new TH1D("totalExpectation_BTags","totalExpectation_BTags", 7, -0.5, 6.5);

  TH1D* totalExpectation_HT_NJets2_ = new TH1D("totalExpectation_HT_NJets2","totalExpectation_HT_NJets2", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets2_ = new TH1D("totalExpectation_MHT_NJets2","totalExpectation_MHT_NJets2", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets2_BTags0_ = new TH1D("totalExpectation_HT_NJets2_BTags0","totalExpectation_HT_NJets2_BTags0", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets2_BTags0_ = new TH1D("totalExpectation_MHT_NJets2_BTags0","totalExpectation_MHT_NJets2_BTags0", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets2_BTags1_ = new TH1D("totalExpectation_HT_NJets2_BTags1","totalExpectation_HT_NJets2_BTags1", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets2_BTags1_ = new TH1D("totalExpectation_MHT_NJets2_BTags1","totalExpectation_MHT_NJets2_BTags1", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets2_BTags2Inf_ = new TH1D("totalExpectation_HT_NJets2_BTags2Inf","totalExpectation_HT_NJets2_BTags2Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets2_BTags2Inf_ = new TH1D("totalExpectation_MHT_NJets2_BTags2Inf","totalExpectation_MHT_NJets2_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalExpectation_HT_NJets34_ = new TH1D("totalExpectation_HT_NJets34","totalExpectation_HT_NJets34", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets34_ = new TH1D("totalExpectation_MHT_NJets34","totalExpectation_MHT_NJets34", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets34_BTags0_ = new TH1D("totalExpectation_HT_NJets34_BTags0","totalExpectation_HT_NJets34_BTags0", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets34_BTags0_ = new TH1D("totalExpectation_MHT_NJets34_BTags0","totalExpectation_MHT_NJets34_BTags0", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets34_BTags1_ = new TH1D("totalExpectation_HT_NJets34_BTags1","totalExpectation_HT_NJets34_BTags1", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets34_BTags1_ = new TH1D("totalExpectation_MHT_NJets34_BTags1","totalExpectation_MHT_NJets34_BTags1", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets34_BTags2Inf_ = new TH1D("totalExpectation_HT_NJets34_BTags2Inf","totalExpectation_HT_NJets34_BTags2Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets34_BTags2Inf_ = new TH1D("totalExpectation_MHT_NJets34_BTags2Inf","totalExpectation_MHT_NJets34_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalExpectation_HT_NJets56_ = new TH1D("totalExpectation_HT_NJets56","totalExpectation_HT_NJets56", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets56_ = new TH1D("totalExpectation_MHT_NJets56","totalExpectation_MHT_NJets56", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets56_BTags0_ = new TH1D("totalExpectation_HT_NJets56_BTags0","totalExpectation_HT_NJets56_BTags0", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets56_BTags0_ = new TH1D("totalExpectation_MHT_NJets56_BTags0","totalExpectation_MHT_NJets56_BTags0", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets56_BTags1_ = new TH1D("totalExpectation_HT_NJets56_BTags1","totalExpectation_HT_NJets56_BTags1", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets56_BTags1_ = new TH1D("totalExpectation_MHT_NJets56_BTags1","totalExpectation_MHT_NJets56_BTags1", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets56_BTags2Inf_ = new TH1D("totalExpectation_HT_NJets56_BTags2Inf","totalExpectation_HT_NJets56_BTags2Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets56_BTags2Inf_ = new TH1D("totalExpectation_MHT_NJets56_BTags2Inf","totalExpectation_MHT_NJets56_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalExpectation_HT_NJets78_ = new TH1D("totalExpectation_HT_NJets78","totalExpectation_HT_NJets78", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets78_ = new TH1D("totalExpectation_MHT_NJets78","totalExpectation_MHT_NJets78", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets78_BTags0_ = new TH1D("totalExpectation_HT_NJets78_BTags0","totalExpectation_HT_NJets78_BTags0", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets78_BTags0_ = new TH1D("totalExpectation_MHT_NJets78_BTags0","totalExpectation_MHT_NJets78_BTags0", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets78_BTags1_ = new TH1D("totalExpectation_HT_NJets78_BTags1","totalExpectation_HT_NJets78_BTags1", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets78_BTags1_ = new TH1D("totalExpectation_MHT_NJets78_BTags1","totalExpectation_MHT_NJets78_BTags1", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets78_BTags2Inf_ = new TH1D("totalExpectation_HT_NJets78_BTags2Inf","totalExpectation_HT_NJets78_BTags2Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets78_BTags2Inf_ = new TH1D("totalExpectation_MHT_NJets78_BTags2Inf","totalExpectation_MHT_NJets78_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalExpectation_HT_NJets9Inf_ = new TH1D("totalExpectation_HT_NJets9Inf","totalExpectation_HT_NJets9Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets9Inf_ = new TH1D("totalExpectation_MHT_NJets9Inf","totalExpectation_MHT_NJets9Inf", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets9Inf_BTags0_ = new TH1D("totalExpectation_HT_NJets9Inf_BTags0","totalExpectation_HT_NJets9Inf_BTags0", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets9Inf_BTags0_ = new TH1D("totalExpectation_MHT_NJets9Inf_BTags0","totalExpectation_MHT_NJets9Inf_BTags0", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets9Inf_BTags1_ = new TH1D("totalExpectation_HT_NJets9Inf_BTags1","totalExpectation_HT_NJets9Inf_BTags1", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets9Inf_BTags1_ = new TH1D("totalExpectation_MHT_NJets9Inf_BTags1","totalExpectation_MHT_NJets9Inf_BTags1", nMHTbins, MHTbins);
  TH1D* totalExpectation_HT_NJets9Inf_BTags2Inf_ = new TH1D("totalExpectation_HT_NJets9Inf_BTags2Inf","totalExpectation_HT_NJets9Inf_BTags2Inf", nHTbins, HTbins);
  TH1D* totalExpectation_MHT_NJets9Inf_BTags2Inf_ = new TH1D("totalExpectation_MHT_NJets9Inf_BTags2Inf","totalExpectation_MHT_NJets9Inf_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalPrediction_ = new TH1D("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionWoIso_ = new TH1D("TotalLostLeptonPredictionWoIso", "TotalLostLeptonPredictionWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionDiLep_ = new TH1D("TotalLostLeptonPredictionDiLep", "TotalLostLeptonPredictionDiLep", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredictionMu_ = new TH1D("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElec_ = new TH1D("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuWoIso_ = new TH1D("TotalLostLeptonPredictionMuWoIso", "TotalLostLeptonPredictionMuWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecWoIso_ = new TH1D("TotalLostLeptonPredictionElecWoIso", "TotalLostLeptonPredictionElecWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredictionMuMTW_ = new TH1D("TotalPredictionMuMTW", "TotalPredictionMuMTW", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecMTW_ = new TH1D("TotalPredictionElecMTW", "TotalPredictionElecMTW", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPrediction_HT_ = new TH1D("totalPrediction_HT","totalPrediction_HT", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_ = new TH1D("totalPrediction_MHT","totalPrediction_MHT", nMHTbins, MHTbins);
  TH1D* totalPrediction_NJets_ = new TH1D("totalPrediction_NJets","totalPrediction_NJets", nNJetsbins, NJetsbins);
  TH1D* totalPrediction_BTags_ = new TH1D("totalPrediction_BTags","totalPrediction_BTags", 7, -0.5, 6.5);

  TH1D* totalCS_HT_ = new TH1D("totalCS_HT","totalCS_HT", nHTbins, HTbins);
  TH1D* totalCS_MHT_ = new TH1D("totalCS_MHT","totalCS_MHT", nMHTbins, MHTbins);
  TH1D* totalCS_NJets_ = new TH1D("totalCS_NJets","totalCS_NJets", nNJetsbins, NJetsbins);
  TH1D* totalCS_BTags_ = new TH1D("totalCS_BTags","totalCS_BTags", 7, -0.5, 6.5);

  TH1D* totalPrediction_HT_NJets2_ = new TH1D("totalPrediction_HT_NJets2","totalPrediction_HT_NJets2", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets2_ = new TH1D("totalPrediction_MHT_NJets2","totalPrediction_MHT_NJets2", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets2_BTags0_ = new TH1D("totalPrediction_HT_NJets2_BTags0","totalPrediction_HT_NJets2_BTags0", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets2_BTags0_ = new TH1D("totalPrediction_MHT_NJets2_BTags0","totalPrediction_MHT_NJets2_BTags0", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets2_BTags1_ = new TH1D("totalPrediction_HT_NJets2_BTags1","totalPrediction_HT_NJets2_BTags1", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets2_BTags1_ = new TH1D("totalPrediction_MHT_NJets2_BTags1","totalPrediction_MHT_NJets2_BTags1", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets2_BTags2Inf_ = new TH1D("totalPrediction_HT_NJets2_BTags2Inf","totalPrediction_HT_NJets2_BTags2Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets2_BTags2Inf_ = new TH1D("totalPrediction_MHT_NJets2_BTags2Inf","totalPrediction_MHT_NJets2_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalPrediction_HT_NJets34_ = new TH1D("totalPrediction_HT_NJets34","totalPrediction_HT_NJets34", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets34_ = new TH1D("totalPrediction_MHT_NJets34","totalPrediction_MHT_NJets34", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets34_BTags0_ = new TH1D("totalPrediction_HT_NJets34_BTags0","totalPrediction_HT_NJets34_BTags0", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets34_BTags0_ = new TH1D("totalPrediction_MHT_NJets34_BTags0","totalPrediction_MHT_NJets34_BTags0", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets34_BTags1_ = new TH1D("totalPrediction_HT_NJets34_BTags1","totalPrediction_HT_NJets34_BTags1", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets34_BTags1_ = new TH1D("totalPrediction_MHT_NJets34_BTags1","totalPrediction_MHT_NJets34_BTags1", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets34_BTags2Inf_ = new TH1D("totalPrediction_HT_NJets34_BTags2Inf","totalPrediction_HT_NJets34_BTags2Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets34_BTags2Inf_ = new TH1D("totalPrediction_MHT_NJets34_BTags2Inf","totalPrediction_MHT_NJets34_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalPrediction_HT_NJets56_ = new TH1D("totalPrediction_HT_NJets56","totalPrediction_HT_NJets56", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets56_ = new TH1D("totalPrediction_MHT_NJets56","totalPrediction_MHT_NJets56", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets56_BTags0_ = new TH1D("totalPrediction_HT_NJets56_BTags0","totalPrediction_HT_NJets56_BTags0", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets56_BTags0_ = new TH1D("totalPrediction_MHT_NJets56_BTags0","totalPrediction_MHT_NJets56_BTags0", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets56_BTags1_ = new TH1D("totalPrediction_HT_NJets56_BTags1","totalPrediction_HT_NJets56_BTags1", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets56_BTags1_ = new TH1D("totalPrediction_MHT_NJets56_BTags1","totalPrediction_MHT_NJets56_BTags1", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets56_BTags2Inf_ = new TH1D("totalPrediction_HT_NJets56_BTags2Inf","totalPrediction_HT_NJets56_BTags2Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets56_BTags2Inf_ = new TH1D("totalPrediction_MHT_NJets56_BTags2Inf","totalPrediction_MHT_NJets56_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalPrediction_HT_NJets78_ = new TH1D("totalPrediction_HT_NJets78","totalPrediction_HT_NJets78", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets78_ = new TH1D("totalPrediction_MHT_NJets78","totalPrediction_MHT_NJets78", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets78_BTags0_ = new TH1D("totalPrediction_HT_NJets78_BTags0","totalPrediction_HT_NJets78_BTags0", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets78_BTags0_ = new TH1D("totalPrediction_MHT_NJets78_BTags0","totalPrediction_MHT_NJets78_BTags0", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets78_BTags1_ = new TH1D("totalPrediction_HT_NJets78_BTags1","totalPrediction_HT_NJets78_BTags1", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets78_BTags1_ = new TH1D("totalPrediction_MHT_NJets78_BTags1","totalPrediction_MHT_NJets78_BTags1", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets78_BTags2Inf_ = new TH1D("totalPrediction_HT_NJets78_BTags2Inf","totalPrediction_HT_NJets78_BTags2Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets78_BTags2Inf_ = new TH1D("totalPrediction_MHT_NJets78_BTags2Inf","totalPrediction_MHT_NJets78_BTags2Inf", nMHTbins, MHTbins);

  TH1D* totalPrediction_HT_NJets9Inf_ = new TH1D("totalPrediction_HT_NJets9Inf","totalPrediction_HT_NJets9Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets9Inf_ = new TH1D("totalPrediction_MHT_NJets9Inf","totalPrediction_MHT_NJets9Inf", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets9Inf_BTags0_ = new TH1D("totalPrediction_HT_NJets9Inf_BTags0","totalPrediction_HT_NJets9Inf_BTags0", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets9Inf_BTags0_ = new TH1D("totalPrediction_MHT_NJets9Inf_BTags0","totalPrediction_MHT_NJets9Inf_BTags0", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets9Inf_BTags1_ = new TH1D("totalPrediction_HT_NJets9Inf_BTags1","totalPrediction_HT_NJets9Inf_BTags1", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets9Inf_BTags1_ = new TH1D("totalPrediction_MHT_NJets9Inf_BTags1","totalPrediction_MHT_NJets9Inf_BTags1", nMHTbins, MHTbins);
  TH1D* totalPrediction_HT_NJets9Inf_BTags2Inf_ = new TH1D("totalPrediction_HT_NJets9Inf_BTags2Inf","totalPrediction_HT_NJets9Inf_BTags2Inf", nHTbins, HTbins);
  TH1D* totalPrediction_MHT_NJets9Inf_BTags2Inf_ = new TH1D("totalPrediction_MHT_NJets9Inf_BTags2Inf","totalPrediction_MHT_NJets9Inf_BTags2Inf", nMHTbins, MHTbins);
    
  // separted closure
  TH1D* totalExpectationMuAcc_ = new TH1D("TotalLostLeptonExpecationMuAcc", "TotalLostLeptonExpecationMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuAcc_ = new TH1D("TotalLostLeptonPredictionMuCSMuAcc", "TotalLostLeptonPredictionMuCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuAcc_ = new TH1D("TotalLostLeptonPredictionElecCSMuAcc", "TotalLostLeptonPredictionElecCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationMuReco_ = new TH1D("TotalLostLeptonExpecationMuReco", "TotalLostLeptonExpecationMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuReco_ = new TH1D("TotalLostLeptonPredictionMuCSMuReco", "TotalLostLeptonPredictionMuCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuReco_ = new TH1D("TotalLostLeptonPredictionElecCSMuReco", "TotalLostLeptonPredictionElecCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationMuIso_ = new TH1D("TotalLostLeptonExpecationMuIso", "TotalLostLeptonExpecationMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuIso_ = new TH1D("TotalLostLeptonPredictionMuCSMuIso", "TotalLostLeptonPredictionMuCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuIso_ = new TH1D("TotalLostLeptonPredictionElecCSMuIso", "TotalLostLeptonPredictionElecCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);  
  
  TH1D* totalExpectationElecAcc_ = new TH1D("TotalLostLeptonExpecationElecAcc", "TotalLostLeptonExpecationElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecAcc_ = new TH1D("TotalLostLeptonPredictionMuCSElecAcc", "TotalLostLeptonPredictionMuCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecAcc_ = new TH1D("TotalLostLeptonPredictionElecCSElecAcc", "TotalLostLeptonPredictionElecCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationElecReco_ = new TH1D("TotalLostLeptonExpecationElecReco", "TotalLostLeptonExpecationElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecReco_ = new TH1D("TotalLostLeptonPredictionMuCSElecReco", "TotalLostLeptonPredictionMuCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecReco_ = new TH1D("TotalLostLeptonPredictionElecCSElecReco", "TotalLostLeptonPredictionElecCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationElecIso_ = new TH1D("TotalLostLeptonExpecationElecIso", "TotalLostLeptonExpecationElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecIso_ = new TH1D("TotalLostLeptonPredictionMuCSElecIso", "TotalLostLeptonPredictionMuCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecIso_ = new TH1D("TotalLostLeptonPredictionElecCSElecIso", "TotalLostLeptonPredictionElecCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalExpectationMuAccNJets_ = new TH1D("TotalLostLeptonExpecationMuAccNJets", "TotalLostLeptonExpecationMuAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuAccNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccNJets", "TotalLostLeptonPredictionMuCSMuAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuAccNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccNJets", "TotalLostLeptonPredictionElecCSMuAccNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationMuRecoNJets_ = new TH1D("TotalLostLeptonExpecationMuRecoNJets", "TotalLostLeptonExpecationMuRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuRecoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoNJets", "TotalLostLeptonPredictionMuCSMuRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuRecoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoNJets", "TotalLostLeptonPredictionElecCSMuRecoNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationMuIsoNJets_ = new TH1D("TotalLostLeptonExpecationMuIsoNJets", "TotalLostLeptonExpecationMuIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuIsoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoNJets", "TotalLostLeptonPredictionMuCSMuIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuIsoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoNJets", "TotalLostLeptonPredictionElecCSMuIsoNJets", 9, 1.5, 10.5);  
  
  TH1D* totalExpectationElecAccNJets_ = new TH1D("TotalLostLeptonExpecationElecAccNJets", "TotalLostLeptonExpecationElecAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecAccNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccNJets", "TotalLostLeptonPredictionMuCSElecAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecAccNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccNJets", "TotalLostLeptonPredictionElecCSElecAccNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationElecRecoNJets_ = new TH1D("TotalLostLeptonExpecationElecRecoNJets", "TotalLostLeptonExpecationElecRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecRecoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoNJets", "TotalLostLeptonPredictionMuCSElecRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecRecoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoNJets", "TotalLostLeptonPredictionElecCSElecRecoNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationElecIsoNJets_ = new TH1D("TotalLostLeptonExpecationElecIsoNJets", "TotalLostLeptonExpecationElecIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecIsoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoNJets", "TotalLostLeptonPredictionMuCSElecIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecIsoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoNJets", "TotalLostLeptonPredictionElecCSElecIsoNJets", 9, 1.5, 10.5);

  TH1D* totalExpectationMuAccHT_ = new TH1D("TotalLostLeptonExpecationMuAccHT", "TotalLostLeptonExpecationMuAccHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuAccHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccHT", "TotalLostLeptonPredictionMuCSMuAccHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuAccHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccHT", "TotalLostLeptonPredictionElecCSMuAccHT", 18, 250., 2500.);
  
  TH1D* totalExpectationMuRecoHT_ = new TH1D("TotalLostLeptonExpecationMuRecoHT", "TotalLostLeptonExpecationMuRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuRecoHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoHT", "TotalLostLeptonPredictionMuCSMuRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuRecoHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoHT", "TotalLostLeptonPredictionElecCSMuRecoHT", 18, 250., 2500.);
  
  TH1D* totalExpectationMuIsoHT_ = new TH1D("TotalLostLeptonExpecationMuIsoHT", "TotalLostLeptonExpecationMuIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuIsoHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoHT", "TotalLostLeptonPredictionMuCSMuIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuIsoHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoHT", "TotalLostLeptonPredictionElecCSMuIsoHT", 18, 250., 2500.);  
  
  TH1D* totalExpectationElecAccHT_ = new TH1D("TotalLostLeptonExpecationElecAccHT", "TotalLostLeptonExpecationElecAccHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecAccHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccHT", "TotalLostLeptonPredictionMuCSElecAccHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecAccHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccHT", "TotalLostLeptonPredictionElecCSElecAccHT", 18, 250., 2500.);
  
  TH1D* totalExpectationElecRecoHT_ = new TH1D("TotalLostLeptonExpecationElecRecoHT", "TotalLostLeptonExpecationElecRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecRecoHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoHT", "TotalLostLeptonPredictionMuCSElecRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecRecoHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoHT", "TotalLostLeptonPredictionElecCSElecRecoHT", 18, 250., 2500.);
  
  TH1D* totalExpectationElecIsoHT_ = new TH1D("TotalLostLeptonExpecationElecIsoHT", "TotalLostLeptonExpecationElecIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecIsoHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoHT", "TotalLostLeptonPredictionMuCSElecIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecIsoHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoHT", "TotalLostLeptonPredictionElecCSElecIsoHT", 18, 250., 2500.);

  TH1D* totalExpectationMuAccMHT_ = new TH1D("TotalLostLeptonExpecationMuAccMHT", "TotalLostLeptonExpecationMuAccMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuAccMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccMHT", "TotalLostLeptonPredictionMuCSMuAccMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuAccMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccMHT", "TotalLostLeptonPredictionElecCSMuAccMHT", 12, 250., 850.);
  
  TH1D* totalExpectationMuRecoMHT_ = new TH1D("TotalLostLeptonExpecationMuRecoMHT", "TotalLostLeptonExpecationMuRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuRecoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoMHT", "TotalLostLeptonPredictionMuCSMuRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuRecoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoMHT", "TotalLostLeptonPredictionElecCSMuRecoMHT", 12, 250., 850.);
  
  TH1D* totalExpectationMuIsoMHT_ = new TH1D("TotalLostLeptonExpecationMuIsoMHT", "TotalLostLeptonExpecationMuIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuIsoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoMHT", "TotalLostLeptonPredictionMuCSMuIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuIsoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoMHT", "TotalLostLeptonPredictionElecCSMuIsoMHT", 12, 250., 850.);  
  
  TH1D* totalExpectationElecAccMHT_ = new TH1D("TotalLostLeptonExpecationElecAccMHT", "TotalLostLeptonExpecationElecAccMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecAccMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccMHT", "TotalLostLeptonPredictionMuCSElecAccMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecAccMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccMHT", "TotalLostLeptonPredictionElecCSElecAccMHT", 12, 250., 850.);
  
  TH1D* totalExpectationElecRecoMHT_ = new TH1D("TotalLostLeptonExpecationElecRecoMHT", "TotalLostLeptonExpecationElecRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecRecoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoMHT", "TotalLostLeptonPredictionMuCSElecRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecRecoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoMHT", "TotalLostLeptonPredictionElecCSElecRecoMHT", 12, 250., 850.);
  
  TH1D* totalExpectationElecIsoMHT_ = new TH1D("TotalLostLeptonExpecationElecIsoMHT", "TotalLostLeptonExpecationElecIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecIsoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoMHT", "TotalLostLeptonPredictionMuCSElecIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecIsoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoMHT", "TotalLostLeptonPredictionElecCSElecIsoMHT", 12, 250., 850.);

  TH1D* totalExpectationMuAccBTag_ = new TH1D("TotalLostLeptonExpecationMuAccBTag", "TotalLostLeptonExpecationMuAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuAccBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccBTag", "TotalLostLeptonPredictionMuCSMuAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuAccBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccBTag", "TotalLostLeptonPredictionElecCSMuAccBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationMuRecoBTag_ = new TH1D("TotalLostLeptonExpecationMuRecoBTag", "TotalLostLeptonExpecationMuRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuRecoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoBTag", "TotalLostLeptonPredictionMuCSMuRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuRecoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoBTag", "TotalLostLeptonPredictionElecCSMuRecoBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationMuIsoBTag_ = new TH1D("TotalLostLeptonExpecationMuIsoBTag", "TotalLostLeptonExpecationMuIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuIsoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoBTag", "TotalLostLeptonPredictionMuCSMuIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuIsoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoBTag", "TotalLostLeptonPredictionElecCSMuIsoBTag", 7, -0.5, 6.5);  
  
  TH1D* totalExpectationElecAccBTag_ = new TH1D("TotalLostLeptonExpecationElecAccBTag", "TotalLostLeptonExpecationElecAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecAccBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccBTag", "TotalLostLeptonPredictionMuCSElecAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecAccBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccBTag", "TotalLostLeptonPredictionElecCSElecAccBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationElecRecoBTag_ = new TH1D("TotalLostLeptonExpecationElecRecoBTag", "TotalLostLeptonExpecationElecRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecRecoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoBTag", "TotalLostLeptonPredictionMuCSElecRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecRecoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoBTag", "TotalLostLeptonPredictionElecCSElecRecoBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationElecIsoBTag_ = new TH1D("TotalLostLeptonExpecationElecIsoBTag", "TotalLostLeptonExpecationElecIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecIsoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoBTag", "TotalLostLeptonPredictionMuCSElecIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecIsoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoBTag", "TotalLostLeptonPredictionElecCSElecIsoBTag", 7, -0.5, 6.5);


  //Expectation Tree
  gROOT->Reset();
  TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation.c_str());
  if (!fExp) {
    fExp = new TFile(InputPath_Expectation.c_str());
  }
  
  TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");

  
  // Set branch addresses.
  LostLeptonExpectation->SetBranchStatus("*",0);
  LostLeptonExpectation->SetBranchStatus("HT",1);
  LostLeptonExpectation->SetBranchAddress("HT",&HT);
  LostLeptonExpectation->SetBranchStatus("MHT",1);
  LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
  LostLeptonExpectation->SetBranchStatus("NJets",1);
  LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
  LostLeptonExpectation->SetBranchStatus("BTags",1);
  LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
  LostLeptonExpectation->SetBranchStatus("Weight",1);
  LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
  LostLeptonExpectation->SetBranchStatus("Bin",1);
  LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
  LostLeptonExpectation->SetBranchStatus("BinQCD",1);
  LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
  LostLeptonExpectation->SetBranchStatus("GenMuons",1);
  LostLeptonExpectation->SetBranchAddress("GenMuons",&GenMuons);
  LostLeptonExpectation->SetBranchStatus("GenElectrons",1);
  LostLeptonExpectation->SetBranchAddress("GenElectrons",&GenElectrons);
  LostLeptonExpectation->SetBranchStatus("MTW",1);
  LostLeptonExpectation->SetBranchAddress("MTW",&MTW);
  LostLeptonExpectation->SetBranchStatus("Expectation",1);
  LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
  LostLeptonExpectation->SetBranchStatus("ExpectationReductionIsoTrack",1);
  LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  LostLeptonExpectation->SetBranchStatus("muAcc",1);
  LostLeptonExpectation->SetBranchStatus("muReco",1);
  LostLeptonExpectation->SetBranchStatus("muIso",1);
  LostLeptonExpectation->SetBranchStatus("elecAcc",1);
  LostLeptonExpectation->SetBranchStatus("elecReco",1);
  LostLeptonExpectation->SetBranchStatus("elecIso",1);
  LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
  LostLeptonExpectation->SetBranchAddress("muReco",&muReco);
  LostLeptonExpectation->SetBranchAddress("muIso",&muIso);  
  LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
  LostLeptonExpectation->SetBranchAddress("elecReco",&elecReco);
  LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);
  LostLeptonExpectation->SetBranchStatus("isoTracksNum",1);
  LostLeptonExpectation->SetBranchAddress("isoTracksNum",&isoTracksNum);
  LostLeptonExpectation->SetBranchStatus("ExpectationDiLep",1);
  LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);
  LostLeptonExpectation->SetBranchStatus("bTagProb",1);
  LostLeptonExpectation->SetBranchAddress("bTagProb",&bTagProb);


  std::cout<<"Loop on Expectation"<<std::endl;
  Long64_t nentries = LostLeptonExpectation->GetEntries();  

  Long64_t nbytes = 0;
  for (Long64_t j=0; j<nentries;j++) {
    nbytes += LostLeptonExpectation->GetEntry(j);

    if(doQCDbinning){
      SearchBin = BinQCD;
    }
    else SearchBin = Bin;

    // total expectation
    if(SearchBin > 900) continue;

    for(int i = 0; i < 4; i++){
      if(doBtagProbabilities){
        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
      }else{
        Bin_bTags.at(i)=SearchBin;
      }
    }

    // Fill events 4 times if using bTag probabilities
    int nLoops = 4;
    if(!doBtagProbabilities){
      nLoops = 1;
    }else if(NJets < 3){
      nLoops = 3;
    }

    for(int i = 0; i < nLoops; i++){
      if(doBtagProbabilities){
        scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
        BTags = i;
      }else{
        scaledWeight = Weight * scaleFactorWeight;
      }

      if(GenMuons->size()==1 && GenElectrons->size()==0){
        totalMuons_->Fill(Bin_bTags.at(i), scaledWeight);
      }else if(GenMuons->size()==0 && GenElectrons->size()==1){
        totalElectrons_->Fill(Bin_bTags.at(i), scaledWeight);
      }

      if(Expectation==2){
        if(muIso==2){
          totalExpectationMuMTW_->Fill(Bin_bTags.at(i), scaledWeight);
        }
        if(elecIso==2){
          totalExpectationElecMTW_->Fill(Bin_bTags.at(i), scaledWeight);
        }        
      }

      if(Expectation==1)
        {
        totalExpectationWoIso_->Fill(Bin_bTags.at(i), scaledWeight);
        totalExp+=scaledWeight;
        totalExpError+= scaledWeight*scaledWeight;

        if(ExpectationDiLep == 1) totalExpectationDiLep_->Fill(Bin_bTags.at(i), scaledWeight);

        if(muAcc==0)
          {
          totalExpectationMuAcc_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuAccNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationMuAccBTag_->Fill(BTags, scaledWeight);
          else totalExpectationMuAccBTag_->Fill(i, scaledWeight);
          totalExpectationMuAccHT_->Fill(HT, scaledWeight);
          totalExpectationMuAccMHT_->Fill(MHT, scaledWeight);
          totalExpMuAcc+=scaledWeight;
          }
        if(muReco==0)
          {
          totalExpectationMuReco_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuRecoNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationMuRecoBTag_->Fill(BTags, scaledWeight);
          else totalExpectationMuRecoBTag_->Fill(i, scaledWeight);
          totalExpectationMuRecoHT_->Fill(HT, scaledWeight);
          totalExpectationMuRecoMHT_->Fill(MHT, scaledWeight);
          totalExpMuReco+=scaledWeight;
          }
        if(muIso==0)
          {
          totalExpectationMuIso_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuIsoNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationMuIsoBTag_->Fill(BTags, scaledWeight);
          else totalExpectationMuIsoBTag_->Fill(i, scaledWeight);
          totalExpectationMuIsoHT_->Fill(HT, scaledWeight);
          totalExpectationMuIsoMHT_->Fill(MHT, scaledWeight);
          totalExpMuIso+=scaledWeight;
          }
              
        if(elecAcc==0)
          {
          totalExpectationElecAcc_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecAccNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationElecAccBTag_->Fill(BTags, scaledWeight);
          else totalExpectationElecAccBTag_->Fill(i, scaledWeight);
          totalExpectationElecAccHT_->Fill(HT, scaledWeight);
          totalExpectationElecAccMHT_->Fill(MHT, scaledWeight);
          totalExpElecAcc+=scaledWeight;

          }
        if(elecReco==0)
          {
          totalExpectationElecReco_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecRecoNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationElecRecoBTag_->Fill(BTags, scaledWeight);
          else totalExpectationElecRecoBTag_->Fill(i, scaledWeight);
          totalExpectationElecRecoHT_->Fill(HT, scaledWeight);
          totalExpectationElecRecoMHT_->Fill(MHT, scaledWeight);
          totalExpElecReco+=scaledWeight;
          }
        if(elecIso==0)
          {
          totalExpectationElecIso_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecIsoNJets_->Fill(NJets, scaledWeight);
          if(!doBtagProbabilities) totalExpectationElecIsoBTag_->Fill(BTags, scaledWeight);
          else totalExpectationElecIsoBTag_->Fill(i, scaledWeight);
          totalExpectationElecIsoHT_->Fill(HT, scaledWeight);
          totalExpectationElecIsoMHT_->Fill(MHT, scaledWeight);
          totalExpElecIso+=scaledWeight;
          }
      }
      if(Expectation==1 && ExpectationReductionIsoTrack==0)
      {
        totalExpectation_->Fill(Bin_bTags.at(i), scaledWeight);
        totalExpIsoTrack+=scaledWeight;
        totalExpIsoTrackError+= scaledWeight*scaledWeight;

        totalExpectation_HT_->Fill(HT, scaledWeight);
        totalExpectation_MHT_->Fill(MHT, scaledWeight);
        totalExpectation_NJets_->Fill(NJets, scaledWeight);
        if(!doBtagProbabilities) totalExpectation_BTags_->Fill(BTags, scaledWeight);
        else totalExpectation_BTags_->Fill(i, scaledWeight);

        int BTags_i = BTags;
        if(doBtagProbabilities) BTags_i = i;

        if(NJets < 2.5){
          	totalExpectation_HT_NJets2_->Fill(HT, scaledWeight);
            totalExpectation_MHT_NJets2_->Fill(MHT, scaledWeight);
          	if(BTags_i < 0.5){
          		totalExpectation_HT_NJets2_BTags0_->Fill(HT, scaledWeight);
    			    totalExpectation_MHT_NJets2_BTags0_->Fill(MHT, scaledWeight);
          	}else if(BTags_i < 1.5){
          		totalExpectation_HT_NJets2_BTags1_->Fill(HT, scaledWeight);
    			totalExpectation_MHT_NJets2_BTags1_->Fill(MHT, scaledWeight);
          	}else{
          		totalExpectation_HT_NJets2_BTags2Inf_->Fill(HT, scaledWeight);
    			    totalExpectation_MHT_NJets2_BTags2Inf_->Fill(MHT, scaledWeight);
          	}			
    		}else if(NJets < 4.5){
    			totalExpectation_HT_NJets34_->Fill(HT, scaledWeight);
    			totalExpectation_MHT_NJets34_->Fill(MHT, scaledWeight);
            	if(BTags_i < 0.5){
            		totalExpectation_HT_NJets34_BTags0_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets34_BTags0_->Fill(MHT, scaledWeight);
            	}else if(BTags_i < 1.5){
            		totalExpectation_HT_NJets34_BTags1_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets34_BTags1_->Fill(MHT, scaledWeight);
            	}else{
            		totalExpectation_HT_NJets34_BTags2Inf_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets34_BTags2Inf_->Fill(MHT, scaledWeight);
            	}	
    		}else if(NJets < 6.5){
    			totalExpectation_HT_NJets56_->Fill(HT, scaledWeight);
    			totalExpectation_MHT_NJets56_->Fill(MHT, scaledWeight);
            	if(BTags_i < 0.5){
            		totalExpectation_HT_NJets56_BTags0_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets56_BTags0_->Fill(MHT, scaledWeight);
            	}else if(BTags_i < 1.5){
            		totalExpectation_HT_NJets56_BTags1_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets56_BTags1_->Fill(MHT, scaledWeight);
            	}else{
            		totalExpectation_HT_NJets56_BTags2Inf_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets56_BTags2Inf_->Fill(MHT, scaledWeight);
            	}	
    		}else if(NJets < 8.5){
    			totalExpectation_HT_NJets78_->Fill(HT, scaledWeight);
    			totalExpectation_MHT_NJets78_->Fill(MHT, scaledWeight);
            	if(BTags_i < 0.5){
            		totalExpectation_HT_NJets78_BTags0_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets78_BTags0_->Fill(MHT, scaledWeight);
            	}else if(BTags_i < 1.5){
            		totalExpectation_HT_NJets78_BTags1_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets78_BTags1_->Fill(MHT, scaledWeight);
            	}else{
            		totalExpectation_HT_NJets78_BTags2Inf_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets78_BTags2Inf_->Fill(MHT, scaledWeight);
            	}	
    		}else{
    			   totalExpectation_HT_NJets9Inf_->Fill(HT, scaledWeight);
    			   totalExpectation_MHT_NJets9Inf_->Fill(MHT, scaledWeight);
            	if(BTags_i < 0.5){
            		totalExpectation_HT_NJets9Inf_BTags0_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets9Inf_BTags0_->Fill(MHT, scaledWeight);
            	}else if(BTags_i < 1.5){
            		totalExpectation_HT_NJets9Inf_BTags1_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets9Inf_BTags1_->Fill(MHT, scaledWeight);
            	}else{
            		totalExpectation_HT_NJets9Inf_BTags2Inf_->Fill(HT, scaledWeight);
    				    totalExpectation_MHT_NJets9Inf_BTags2Inf_->Fill(MHT, scaledWeight);
            	}	
    		}
      }
    }
  }

  fExp->Close();
  std::cout<<"Finished"<<std::endl;


  //Prediction MC Tree
  gROOT->Reset();
  TFile *fPreMC = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction.c_str());
  if (!fPreMC) {
    fPreMC = new TFile(InputPath_Prediction.c_str());
  }
  TTree* LostLeptonPrediction = (TTree*) fPreMC->Get("LostLeptonPrediction");

  LostLeptonPrediction->SetBranchStatus("*",0);
  LostLeptonPrediction->SetBranchStatus("HT",1);
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchStatus("MHT",1);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchStatus("NJets",1);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchStatus("BTags",1);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchStatus("Weight",1);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchStatus("Bin",1);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
  LostLeptonPrediction->SetBranchStatus("BinQCD",1);
  LostLeptonPrediction->SetBranchAddress("BinQCD",&BinQCD);
  LostLeptonPrediction->SetBranchStatus("bTagProb",1);
  LostLeptonPrediction->SetBranchAddress("bTagProb",&bTagProb);
  LostLeptonPrediction->SetBranchStatus("MTW",1);
  LostLeptonPrediction->SetBranchAddress("MTW",&MTW);
  LostLeptonPrediction->SetBranchStatus("MuonsNum",1);
  LostLeptonPrediction->SetBranchAddress("MuonsNum",&MuonsNum);
  LostLeptonPrediction->SetBranchStatus("Muons",1);
  LostLeptonPrediction->SetBranchAddress("Muons",&Muons);
  LostLeptonPrediction->SetBranchStatus("ElectronsNum",1);
  LostLeptonPrediction->SetBranchAddress("ElectronsNum",&ElectronsNum);
  LostLeptonPrediction->SetBranchStatus("Electrons",1);
  LostLeptonPrediction->SetBranchAddress("Electrons",&Electrons);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags",&totalWeight_BTags);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_noIsoTrack",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MTW",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MTW",&totalWeight_BTags_MTW);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuAcc",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuAcc",&totalWeight_BTags_MuAcc_);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuReco",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuReco",&totalWeight_BTags_MuReco_);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuIso",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuIso",&totalWeight_BTags_MuIso_);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecAcc",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecAcc",&totalWeight_BTags_ElecAcc_);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecReco",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecReco",&totalWeight_BTags_ElecReco_);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecIso",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecIso",&totalWeight_BTags_ElecIso_);
  LostLeptonPrediction->SetBranchStatus("muIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecIsoWeight",1);  
  LostLeptonPrediction->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPrediction->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPrediction->SetBranchAddress("muAccWeight",&muAccWeight);  
  LostLeptonPrediction->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPrediction->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPrediction->SetBranchAddress("elecIsoWeight",&elecIsoWeight);
  LostLeptonPrediction->SetBranchStatus("diLepLostWeight",1);
  LostLeptonPrediction->SetBranchAddress("diLepLostWeight",&diLepLostWeight);

  std::cout<<"Loop on Prediction (MC)"<<std::endl;

  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t j=0; j<nentries;j++) {
    nbytes += LostLeptonPrediction->GetEntry(j);

    if(doQCDbinning){
      SearchBin = BinQCD;
    }
    else SearchBin = Bin;

    if(SearchBin > 900) continue;
    if(MTW>100) continue;
    if(MuonsNum+ElectronsNum!=1) continue;


    for(int i = 0; i < 4; i++){
      if(doBtagProbabilities){
        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
      }else{
        Bin_bTags.at(i)=SearchBin;
      }
    }

    int nLoops = 4;
    if(!doBtagProbabilities){
      nLoops = 1;
    }else if(NJets < 3){
      nLoops = 3;
    }

	  //fill event 4 times weighting with the btag probability
	  for(int i = 0; i < nLoops; i++){
	    double scaleFactorWeightBtagProb;
	    if(doBtagProbabilities){
	      scaleFactorWeightBtagProb = scaleFactorWeight * bTagProb->at(i);
	      scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
	    }else{
	      scaleFactorWeightBtagProb = scaleFactorWeight;
	      scaledWeight = Weight * scaleFactorWeight;
	    }

    if(!doBtagProbabilities){
        totalPrediction_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);        
        totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2;
        totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2;       

        totalPredictionWoIso_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
        totalPre+=totalWeightDiLep*scaleFactorWeightBtagProb/2;
        totalPreError+= totalWeightDiLep*scaleFactorWeightBtagProb/2*totalWeightDiLep*scaleFactorWeightBtagProb/2;

        totalPredictionDiLep_->Fill(Bin_bTags.at(i), diLepLostWeight*scaleFactorWeightBtagProb/2);             
            
        totalPrediction_HT_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_MHT_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_NJets_->Fill(NJets, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_BTags_->Fill(BTags, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);

        totalCS_HT_->Fill(HT, scaleFactorWeightBtagProb/2);
        totalCS_MHT_->Fill(MHT, scaleFactorWeightBtagProb/2);
        totalCS_NJets_->Fill(NJets, scaleFactorWeightBtagProb/2);
        totalCS_BTags_->Fill(BTags, scaleFactorWeightBtagProb/2);

        if(NJets < 2.5){
        	totalPrediction_HT_NJets2_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
          totalPrediction_MHT_NJets2_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	if(BTags < 0.5){
        		totalPrediction_HT_NJets2_BTags0_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags0_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else if(BTags < 1.5){
        		totalPrediction_HT_NJets2_BTags1_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags1_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets2_BTags2Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags2Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}			
		    }else if(NJets < 4.5){
			     totalPrediction_HT_NJets34_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
			     totalPrediction_MHT_NJets34_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	if(BTags < 0.5){
        		totalPrediction_HT_NJets34_BTags0_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags0_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else if(BTags < 1.5){
        		totalPrediction_HT_NJets34_BTags1_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags1_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets34_BTags2Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags2Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}	
		    }else if(NJets < 6.5){
			     totalPrediction_HT_NJets56_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
			     totalPrediction_MHT_NJets56_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	if(BTags < 0.5){
        		totalPrediction_HT_NJets56_BTags0_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags0_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else if(BTags < 1.5){
        		totalPrediction_HT_NJets56_BTags1_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags1_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets56_BTags2Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags2Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}	
		    }else if(NJets < 8.5){
			   totalPrediction_HT_NJets78_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
			   totalPrediction_MHT_NJets78_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	if(BTags < 0.5){
        		totalPrediction_HT_NJets78_BTags0_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags0_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else if(BTags < 1.5){
        		totalPrediction_HT_NJets78_BTags1_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags1_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets78_BTags2Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags2Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}	
		    }else{
			     totalPrediction_HT_NJets9Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
			     totalPrediction_MHT_NJets9Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	if(BTags < 0.5){
        		totalPrediction_HT_NJets9Inf_BTags0_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags0_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else if(BTags < 1.5){
        		totalPrediction_HT_NJets9Inf_BTags1_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags1_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets9Inf_BTags2Inf_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags2Inf_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        	}	
		    }
    }else{
	      totalPrediction_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
	      totalPreIsoTrack+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2;
	      totalPreIsoTrackError+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2*totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2;

	      totalPredictionWoIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2);
	      totalPre+=totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2;
	      totalPreError+= totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2*totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2;

          totalPredictionDiLep_->Fill(Bin_bTags.at(i), diLepLostWeight*scaleFactorWeightBtagProb/2);     
	          
	      totalPrediction_HT_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
	      totalPrediction_MHT_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
	      totalPrediction_NJets_->Fill(NJets, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
	      totalPrediction_BTags_->Fill(i, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);

	      totalCS_HT_->Fill(HT, Weight*scaleFactorWeightBtagProb);
	      totalCS_MHT_->Fill(MHT, Weight*scaleFactorWeightBtagProb);
	      totalCS_NJets_->Fill(NJets, Weight*scaleFactorWeightBtagProb);
	      totalCS_BTags_->Fill(i, Weight*scaleFactorWeightBtagProb);

        if(MuonsNum==1){
          totalPredictionMuMTW_->Fill(Bin_bTags.at(i), totalWeight_BTags_MTW->at(i)*scaleFactorWeightBtagProb);
        }
        if(ElectronsNum==1){
          totalPredictionElecMTW_->Fill(Bin_bTags.at(i), totalWeight_BTags_MTW->at(i)*scaleFactorWeightBtagProb);
        }        

	    if(NJets < 2.5){
        	totalPrediction_HT_NJets2_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			    totalPrediction_MHT_NJets2_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	if(i < 0.5){
        		totalPrediction_HT_NJets2_BTags0_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags0_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else if(i < 1.5){
        		totalPrediction_HT_NJets2_BTags1_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags1_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets2_BTags2Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets2_BTags2Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}			
		}else if(NJets < 4.5){
			   totalPrediction_HT_NJets34_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			   totalPrediction_MHT_NJets34_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	if(i < 0.5){
        		totalPrediction_HT_NJets34_BTags0_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags0_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else if(i < 1.5){
        		totalPrediction_HT_NJets34_BTags1_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags1_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets34_BTags2Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets34_BTags2Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}	
		}else if(NJets < 6.5){
			   totalPrediction_HT_NJets56_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			   totalPrediction_MHT_NJets56_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	if(i < 0.5){
        		totalPrediction_HT_NJets56_BTags0_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags0_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else if(i < 1.5){
        		totalPrediction_HT_NJets56_BTags1_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags1_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets56_BTags2Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets56_BTags2Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}	
		}else if(NJets < 8.5){
			   totalPrediction_HT_NJets78_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			   totalPrediction_MHT_NJets78_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	if(i < 0.5){
        		totalPrediction_HT_NJets78_BTags0_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags0_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else if(i < 1.5){
        		totalPrediction_HT_NJets78_BTags1_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags1_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets78_BTags2Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets78_BTags2Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}	
		}else{
			   totalPrediction_HT_NJets9Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			   totalPrediction_MHT_NJets9Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	if(i < 0.5){
        		totalPrediction_HT_NJets9Inf_BTags0_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags0_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else if(i < 1.5){
        		totalPrediction_HT_NJets9Inf_BTags1_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags1_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}else{
        		totalPrediction_HT_NJets9Inf_BTags2Inf_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				    totalPrediction_MHT_NJets9Inf_BTags2Inf_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        	}	
		}
	}
          if(MuonsNum == 1){
            totalPredictionMu_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuWoIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb);

            totalPreMu+=totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb;
            totalPreMuError+= totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb*totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb;
            // isotrackveto applied
            totalPreIsoTrackMu+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb;
            totalPreIsoTrackMuError+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb*totalWeight_BTags->at(i)*scaleFactorWeightBtagProb;


            totalPredictionMuCSMuAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccNJets_->Fill(NJets, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoNJets_->Fill(NJets, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoNJets_->Fill(NJets, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccBTag_->Fill(i, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoBTag_->Fill(i, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoBTag_->Fill(i, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccHT_->Fill(HT, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoHT_->Fill(HT, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoHT_->Fill(HT, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccMHT_->Fill(MHT, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoMHT_->Fill(MHT, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoMHT_->Fill(MHT, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPreMuAcc+=totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuMuAcc+=totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb;
            totalPreMuMuReco+=totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb;
            totalPreMuMuIso+=totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb;
                
            totalPredictionMuCSElecAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccNJets_->Fill(NJets, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoNJets_->Fill(NJets, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoNJets_->Fill(NJets, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccBTag_->Fill(i, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoBTag_->Fill(i, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoBTag_->Fill(i, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccHT_->Fill(HT, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoHT_->Fill(HT, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoHT_->Fill(HT, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccMHT_->Fill(MHT, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoMHT_->Fill(MHT, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoMHT_->Fill(MHT, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPreElecAcc+=totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuElecAcc+=totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb;
            totalPreMuElecReco+=totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb;
            totalPreMuElecIso+=totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb;

          }if(ElectronsNum == 1){
            totalPredictionElec_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecWoIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb);

            totalPreElec+=totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb;
            totalPreElecError+= totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb*totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb;
            // isotrackveto applied
            totalPreIsoTrackElec+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb;
            totalPreIsoTrackElecError+=totalWeight_BTags->at(i)*scaleFactorWeightBtagProb*totalWeight_BTags->at(i)*scaleFactorWeightBtagProb;


            totalPredictionElecCSElecAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccNJets_->Fill(NJets, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoNJets_->Fill(NJets, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoNJets_->Fill(NJets, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccBTag_->Fill(i, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoBTag_->Fill(i, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoBTag_->Fill(i, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccHT_->Fill(HT, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoHT_->Fill(HT, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoHT_->Fill(HT, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccMHT_->Fill(MHT, totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoMHT_->Fill(MHT, totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoMHT_->Fill(MHT, totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb);
            totalPreElecAcc+=totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecElecAcc+=totalWeight_BTags_ElecAcc_->at(i)*scaleFactorWeightBtagProb;
            totalPreElecElecReco+=totalWeight_BTags_ElecReco_->at(i)*scaleFactorWeightBtagProb;
            totalPreElecElecIso+=totalWeight_BTags_ElecIso_->at(i)*scaleFactorWeightBtagProb;
                    
            totalPredictionElecCSMuAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccNJets_->Fill(NJets, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoNJets_->Fill(NJets, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoNJets_->Fill(NJets, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccBTag_->Fill(i, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoBTag_->Fill(i, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoBTag_->Fill(i, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccHT_->Fill(HT, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoHT_->Fill(HT, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoHT_->Fill(HT, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccMHT_->Fill(MHT, totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoMHT_->Fill(MHT, totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoMHT_->Fill(MHT, totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb);
            totalPreMuAcc+=totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecMuAcc+=totalWeight_BTags_MuAcc_->at(i)*scaleFactorWeightBtagProb;
            totalPreElecMuReco+=totalWeight_BTags_MuReco_->at(i)*scaleFactorWeightBtagProb;
            totalPreElecMuIso+=totalWeight_BTags_MuIso_->at(i)*scaleFactorWeightBtagProb;
          }
      }
    }

  fPreMC->Close();
  std::cout<<"Finished"<<std::endl;

  //closure test
  TFile *outPutFile = new TFile(OutputPath_Closure.c_str(),"RECREATE"); 
  outPutFile->cd();

  outPutFile->mkdir("Expectation");
  TDirectory *dExpectation = (TDirectory*)outPutFile->Get("Expectation");
  dExpectation->cd();
  totalExpectation_->Write();
  totalExpectationDiLep_->Write();
  totalExpectation_HT_->Write();
  totalMuons_->Write();
  totalElectrons_->Write();
  TH1D* totalMuonElectronRatio = (TH1D*) totalMuons_->Clone("totalMuonElectronRatio");
  totalMuonElectronRatio->SetTitle("totalMuonElectronRatio");
  totalMuonElectronRatio->Divide(totalMuons_, totalElectrons_);
  totalMuonElectronRatio->Write();

  TH1D* diLepFrac = (TH1D*) totalExpectation_->Clone("diLepFrac");
  diLepFrac->SetName("diLepFrac");
  diLepFrac->SetTitle("diLepFrac");
  SaveClosure(diLepFrac, totalExpectationDiLep_, dExpectation);

  outPutFile->mkdir("Prediction");
  TDirectory *dPrediction = (TDirectory*)outPutFile->Get("Prediction");
  dPrediction->cd();
  totalPrediction_->Write();
  totalPredictionDiLep_->Write();
  totalPredictionMu_->Write();
  totalPredictionElec_->Write();
  totalPrediction_HT_->Write();
  totalPrediction_MHT_->Write();
  totalPrediction_NJets_->Write();
  totalPrediction_BTags_->Write();
  totalCS_HT_->Write();
  totalCS_MHT_->Write();
  totalCS_NJets_->Write();
  totalCS_BTags_->Write();

  outPutFile->mkdir("avgWeight");
  TDirectory *davgWeight = (TDirectory*)outPutFile->Get("avgWeight");

  SaveClosure(totalCS_HT_, totalPrediction_HT_, davgWeight);    
  SaveClosure(totalCS_MHT_, totalPrediction_MHT_, davgWeight);    
  SaveClosure(totalCS_NJets_, totalPrediction_NJets_, davgWeight);    
  SaveClosure(totalCS_BTags_, totalPrediction_BTags_, davgWeight);

  outPutFile->mkdir("Closures");
  TDirectory *dClosures = (TDirectory*)outPutFile->Get("Closures");

  SaveClosure(totalPrediction_, totalExpectation_, dClosures);
  SaveClosure(totalPredictionMu_, totalExpectation_, dClosures);
  SaveClosure(totalPredictionElec_, totalExpectation_, dClosures);

  TH1D* totalPredictionMuonElectronRatio = (TH1D*) totalPredictionMu_->Clone("totalPredictionMuonElectronRatio");
  totalPredictionMuonElectronRatio->SetTitle("totalPredictionMuonElectronRatio");
  totalPredictionMuonElectronRatio->Divide(totalPredictionMu_, totalPredictionElec_);
  totalPredictionMuonElectronRatio->Write();

  SaveClosure(totalPredictionWoIso_, totalExpectationWoIso_, dClosures);
  SaveClosure(totalPredictionMuWoIso_, totalExpectationWoIso_, dClosures);
  SaveClosure(totalPredictionElecWoIso_, totalExpectationWoIso_, dClosures);

  SaveClosure(totalPredictionDiLep_, totalExpectationDiLep_, dClosures);

  SaveClosure(totalPredictionMuMTW_, totalExpectationMuMTW_, dClosures);
  SaveClosure(totalPredictionElecMTW_, totalExpectationElecMTW_, dClosures);

  SaveClosure(totalPrediction_HT_, totalExpectation_HT_, dClosures);    
  SaveClosure(totalPrediction_MHT_, totalExpectation_MHT_, dClosures);    
  SaveClosure(totalPrediction_NJets_, totalExpectation_NJets_, dClosures);    
  SaveClosure(totalPrediction_BTags_, totalExpectation_BTags_, dClosures);

  SaveClosure(totalPrediction_HT_NJets2_, totalExpectation_HT_NJets2_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets2_, totalExpectation_MHT_NJets2_, dClosures);
  SaveClosure(totalPrediction_HT_NJets2_BTags0_, totalExpectation_HT_NJets2_BTags0_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets2_BTags0_, totalExpectation_MHT_NJets2_BTags0_, dClosures);
  SaveClosure(totalPrediction_HT_NJets2_BTags1_, totalExpectation_HT_NJets2_BTags1_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets2_BTags1_, totalExpectation_MHT_NJets2_BTags1_, dClosures);
  SaveClosure(totalPrediction_HT_NJets2_BTags2Inf_, totalExpectation_HT_NJets2_BTags2Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets2_BTags2Inf_, totalExpectation_MHT_NJets2_BTags2Inf_, dClosures);

  SaveClosure(totalPrediction_HT_NJets34_, totalExpectation_HT_NJets34_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets34_, totalExpectation_MHT_NJets34_, dClosures);
  SaveClosure(totalPrediction_HT_NJets34_BTags0_, totalExpectation_HT_NJets34_BTags0_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets34_BTags0_, totalExpectation_MHT_NJets34_BTags0_, dClosures);
  SaveClosure(totalPrediction_HT_NJets34_BTags1_, totalExpectation_HT_NJets34_BTags1_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets34_BTags1_, totalExpectation_MHT_NJets34_BTags1_, dClosures);
  SaveClosure(totalPrediction_HT_NJets34_BTags2Inf_, totalExpectation_HT_NJets34_BTags2Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets34_BTags2Inf_, totalExpectation_MHT_NJets34_BTags2Inf_, dClosures);

  SaveClosure(totalPrediction_HT_NJets56_, totalExpectation_HT_NJets56_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets56_, totalExpectation_MHT_NJets56_, dClosures);
  SaveClosure(totalPrediction_HT_NJets56_BTags0_, totalExpectation_HT_NJets56_BTags0_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets56_BTags0_, totalExpectation_MHT_NJets56_BTags0_, dClosures);
  SaveClosure(totalPrediction_HT_NJets56_BTags1_, totalExpectation_HT_NJets56_BTags1_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets56_BTags1_, totalExpectation_MHT_NJets56_BTags1_, dClosures);
  SaveClosure(totalPrediction_HT_NJets56_BTags2Inf_, totalExpectation_HT_NJets56_BTags2Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets56_BTags2Inf_, totalExpectation_MHT_NJets56_BTags2Inf_, dClosures);

  SaveClosure(totalPrediction_HT_NJets78_, totalExpectation_HT_NJets78_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets78_, totalExpectation_MHT_NJets78_, dClosures);
  SaveClosure(totalPrediction_HT_NJets78_BTags0_, totalExpectation_HT_NJets78_BTags0_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets78_BTags0_, totalExpectation_MHT_NJets78_BTags0_, dClosures);
  SaveClosure(totalPrediction_HT_NJets78_BTags1_, totalExpectation_HT_NJets78_BTags1_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets78_BTags1_, totalExpectation_MHT_NJets78_BTags1_, dClosures);
  SaveClosure(totalPrediction_HT_NJets78_BTags2Inf_, totalExpectation_HT_NJets78_BTags2Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets78_BTags2Inf_, totalExpectation_MHT_NJets78_BTags2Inf_, dClosures);

  SaveClosure(totalPrediction_HT_NJets9Inf_, totalExpectation_HT_NJets9Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets9Inf_, totalExpectation_MHT_NJets9Inf_, dClosures);
  SaveClosure(totalPrediction_HT_NJets9Inf_BTags0_, totalExpectation_HT_NJets9Inf_BTags0_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets9Inf_BTags0_, totalExpectation_MHT_NJets9Inf_BTags0_, dClosures);
  SaveClosure(totalPrediction_HT_NJets9Inf_BTags1_, totalExpectation_HT_NJets9Inf_BTags1_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets9Inf_BTags1_, totalExpectation_MHT_NJets9Inf_BTags1_, dClosures);
  SaveClosure(totalPrediction_HT_NJets9Inf_BTags2Inf_, totalExpectation_HT_NJets9Inf_BTags2Inf_, dClosures);
  SaveClosure(totalPrediction_MHT_NJets9Inf_BTags2Inf_, totalExpectation_MHT_NJets9Inf_BTags2Inf_, dClosures);
	

  outPutFile->cd();
  outPutFile->mkdir("Steps");
  TDirectory *dSteps = (TDirectory*)outPutFile->Get("Steps");

  SaveClosure(totalPredictionMuCSMuAcc_, totalExpectationMuAcc_, dSteps);
  SaveClosure(totalPredictionMuCSMuReco_, totalExpectationMuReco_, dSteps);
  SaveClosure(totalPredictionMuCSMuIso_, totalExpectationMuIso_, dSteps);
  
  SaveClosure(totalPredictionMuCSElecAcc_, totalExpectationElecAcc_, dSteps);
  SaveClosure(totalPredictionMuCSElecReco_, totalExpectationElecReco_, dSteps);
  SaveClosure(totalPredictionMuCSElecIso_, totalExpectationElecIso_, dSteps);
  
  SaveClosure(totalPredictionElecCSMuAcc_, totalExpectationMuAcc_, dSteps);
  SaveClosure(totalPredictionElecCSMuReco_, totalExpectationMuReco_, dSteps);
  SaveClosure(totalPredictionElecCSMuIso_, totalExpectationMuIso_, dSteps);
  
  SaveClosure(totalPredictionElecCSElecAcc_, totalExpectationElecAcc_, dSteps);
  SaveClosure(totalPredictionElecCSElecReco_, totalExpectationElecReco_, dSteps);
  SaveClosure(totalPredictionElecCSElecIso_, totalExpectationElecIso_, dSteps);

  SaveClosure(totalPredictionMuCSMuAccNJets_, totalExpectationMuAccNJets_, dSteps);
  SaveClosure(totalPredictionMuCSMuRecoNJets_, totalExpectationMuRecoNJets_, dSteps);
  SaveClosure(totalPredictionMuCSMuIsoNJets_, totalExpectationMuIsoNJets_, dSteps);
  
  SaveClosure(totalPredictionMuCSElecAccNJets_, totalExpectationElecAccNJets_, dSteps);
  SaveClosure(totalPredictionMuCSElecRecoNJets_, totalExpectationElecRecoNJets_, dSteps);
  SaveClosure(totalPredictionMuCSElecIsoNJets_, totalExpectationElecIsoNJets_, dSteps);
  
  SaveClosure(totalPredictionElecCSMuAccNJets_, totalExpectationMuAccNJets_, dSteps);
  SaveClosure(totalPredictionElecCSMuRecoNJets_, totalExpectationMuRecoNJets_, dSteps);
  SaveClosure(totalPredictionElecCSMuIsoNJets_, totalExpectationMuIsoNJets_, dSteps);
  
  SaveClosure(totalPredictionElecCSElecAccNJets_, totalExpectationElecAccNJets_, dSteps);
  SaveClosure(totalPredictionElecCSElecRecoNJets_, totalExpectationElecRecoNJets_, dSteps);
  SaveClosure(totalPredictionElecCSElecIsoNJets_, totalExpectationElecIsoNJets_, dSteps);

  SaveClosure(totalPredictionMuCSMuAccHT_, totalExpectationMuAccHT_, dSteps);
  SaveClosure(totalPredictionMuCSMuRecoHT_, totalExpectationMuRecoHT_, dSteps);
  SaveClosure(totalPredictionMuCSMuIsoHT_, totalExpectationMuIsoHT_, dSteps);
  
  SaveClosure(totalPredictionMuCSElecAccHT_, totalExpectationElecAccHT_, dSteps);
  SaveClosure(totalPredictionMuCSElecRecoHT_, totalExpectationElecRecoHT_, dSteps);
  SaveClosure(totalPredictionMuCSElecIsoHT_, totalExpectationElecIsoHT_, dSteps);
  
  SaveClosure(totalPredictionElecCSMuAccHT_, totalExpectationMuAccHT_, dSteps);
  SaveClosure(totalPredictionElecCSMuRecoHT_, totalExpectationMuRecoHT_, dSteps);
  SaveClosure(totalPredictionElecCSMuIsoHT_, totalExpectationMuIsoHT_, dSteps);
  
  SaveClosure(totalPredictionElecCSElecAccHT_, totalExpectationElecAccHT_, dSteps);
  SaveClosure(totalPredictionElecCSElecRecoHT_, totalExpectationElecRecoHT_, dSteps);
  SaveClosure(totalPredictionElecCSElecIsoHT_, totalExpectationElecIsoHT_, dSteps);

  SaveClosure(totalPredictionMuCSMuAccMHT_, totalExpectationMuAccMHT_, dSteps);
  SaveClosure(totalPredictionMuCSMuRecoMHT_, totalExpectationMuRecoMHT_, dSteps);
  SaveClosure(totalPredictionMuCSMuIsoMHT_, totalExpectationMuIsoMHT_, dSteps);
  
  SaveClosure(totalPredictionMuCSElecAccMHT_, totalExpectationElecAccMHT_, dSteps);
  SaveClosure(totalPredictionMuCSElecRecoMHT_, totalExpectationElecRecoMHT_, dSteps);
  SaveClosure(totalPredictionMuCSElecIsoMHT_, totalExpectationElecIsoMHT_, dSteps);
  
  SaveClosure(totalPredictionElecCSMuAccMHT_, totalExpectationMuAccMHT_, dSteps);
  SaveClosure(totalPredictionElecCSMuRecoMHT_, totalExpectationMuRecoMHT_, dSteps);
  SaveClosure(totalPredictionElecCSMuIsoMHT_, totalExpectationMuIsoMHT_, dSteps);
  
  SaveClosure(totalPredictionElecCSElecAccMHT_, totalExpectationElecAccMHT_, dSteps);
  SaveClosure(totalPredictionElecCSElecRecoMHT_, totalExpectationElecRecoMHT_, dSteps);
  SaveClosure(totalPredictionElecCSElecIsoMHT_, totalExpectationElecIsoMHT_, dSteps);

  SaveClosure(totalPredictionMuCSMuAccBTag_, totalExpectationMuAccBTag_, dSteps);
  SaveClosure(totalPredictionMuCSMuRecoBTag_, totalExpectationMuRecoBTag_, dSteps);
  SaveClosure(totalPredictionMuCSMuIsoBTag_, totalExpectationMuIsoBTag_, dSteps);
  
  SaveClosure(totalPredictionMuCSElecAccBTag_, totalExpectationElecAccBTag_, dSteps);
  SaveClosure(totalPredictionMuCSElecRecoBTag_, totalExpectationElecRecoBTag_, dSteps);
  SaveClosure(totalPredictionMuCSElecIsoBTag_, totalExpectationElecIsoBTag_, dSteps);
  
  SaveClosure(totalPredictionElecCSMuAccBTag_, totalExpectationMuAccBTag_, dSteps);
  SaveClosure(totalPredictionElecCSMuRecoBTag_, totalExpectationMuRecoBTag_, dSteps);
  SaveClosure(totalPredictionElecCSMuIsoBTag_, totalExpectationMuIsoBTag_, dSteps);
  
  SaveClosure(totalPredictionElecCSElecAccBTag_, totalExpectationElecAccBTag_, dSteps);
  SaveClosure(totalPredictionElecCSElecRecoBTag_, totalExpectationElecRecoBTag_, dSteps);
  SaveClosure(totalPredictionElecCSElecIsoBTag_, totalExpectationElecIsoBTag_, dSteps);

  

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

}

void SaveClosure(TH1D* h1, TH1D* h2, TDirectory* Folder)
{
  TH1D* Closure = (TH1D*) h2->Clone();
  Closure->Divide(h2,h1,1,1,"B");
  TString title = h1->GetTitle();
  title +="_closure";
  Closure->SetTitle(title);
  title = h1->GetName();
  title+="_closure";
  Closure->SetName(title);
  Closure->GetYaxis()->SetRangeUser(0., 2.);
  double val1, err1, val2, err2;
  val1 = h1->IntegralAndError(1, h1->GetNbinsX(), err1);
  val2 = h2->IntegralAndError(1, h2->GetNbinsX(), err2);
  std::cout<<title<<"="<<val2/val1<<"+-"<<val2/(val1*val1)*err1+1/val1*err2<<std::endl;
  //std::cout<<h1->GetName()<<"="<<h1->Integral()<<std::endl;
  //std::cout<<h2->GetName()<<"="<<h2->Integral()<<std::endl;
  if(Closure->GetNbinsX()==190) SetBinLabel(Closure);
  Folder->cd();
  Closure->Write();

  //std::cout<<"Saved "<<Folder->GetName()<<"/"<<h1->GetName()<<std::endl;
}

void SetBinLabel(TH1D* hist){
  if(hist->GetNbinsX()==190)
    // only BTags=0,1,2 for NJets=2
    for(int nbi = 0; nbi<4; ++nbi){
      for(int hti = 0; hti<10; ++hti){
        int mhti =0;
        if(hti >=0 && hti <=2) mhti = 0;
        else if(hti >=3 && hti <=5) mhti = 1;
        else if(hti >=6 && hti <=7) mhti = 2;
        else mhti = 3;
        char binlabel[100];
        int bi = nbi * 10 + hti + 1;
        //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", 0, nbi, mhti, hti, bi);
        sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", 0, nbi, mhti, hti);
        hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
      }
    }

    //NJets>=3
    for(int nji = 1; nji<5; ++nji){
      for(int nbi = 0; nbi<4; ++nbi){
        for(int hti = 0; hti<10; ++hti){
          int mhti =0;
          if(hti >=0 && hti <=2) mhti = 0;
          else if(hti >=3 && hti <=5) mhti = 1;
          else if(hti >=6 && hti <=7) mhti = 2;
          else mhti = 3;
          char binlabel[100];
          int bi = 30 + (nji-1) * 40 + nbi * 10 + hti + 1;
          //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
          sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
          hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
        }
      }
    }
  
  if(hist->GetNbinsX()==190) hist -> GetXaxis() -> LabelsOption("v");
}

void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir){
  for(int i = 1; i<Bottom->GetNbinsX()+1; ++i){
    if(Bottom->GetBinContent(i)>0) Top->SetBinContent(i, 1.+Top->GetBinContent(i)/Bottom->GetBinContent(i));
    else Top->SetBinContent(i, -999);
    //else Top->SetBinContent(i, 0);
    Top->SetBinError(i, 0);
  } 

  SetBinLabel(Top);

  dir->cd();
  Top->Write();
}