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
  Double_t scaleFactorWeight = 2262;  //in units of [pb]

  // Begin of Code
  int nSearchBinsTotal = 190;
  if(doQCDbinning){
    nSearchBinsTotal = 190;
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
  UShort_t        selectedIDIsoMuonsNum;
  UShort_t        selectedIDIsoElectronsNum;

  std::vector<TLorentzVector>* selectedIDIsoMuons=0;
  std::vector<TLorentzVector>* selectedIDIsoElectrons=0;
  std::vector<TLorentzVector> *GenMus=0;
  std::vector<TLorentzVector> *GenEls=0;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReduced;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;
  Float_t         totalWeight_BTags0;
  Float_t         totalWeight_BTags1Inf;
  Float_t         totalWeight_BTags0_noIsoTrack;
  Float_t         totalWeight_BTags1Inf_noIsoTrack;

  Float_t         muTotalWeightDiLepIsoTrackReduced;
  Float_t         elecTotalWeightDiLepIsoTrackReduced;
  
  Float_t         muIsoWeight;
  Float_t         muRecoWeight;
  Float_t         muAccWeight;

  Float_t         elecAccWeight;
  Float_t         elecRecoWeight;
  Float_t         elecIsoWeight;

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

  
  TH1D* totalExpectation_ = new TH1D("TotalLostLeptonExpecation", "TotalLostLeptonExpecation", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalExpectationWoIso_ = new TH1D("TotalExpectationWoIso", "TotalExpectationWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalExpectation_HT_ = new TH1D("totalExpectation_HT","totalExpectation_HT", 18, 25., 2500.);
  TH1D* totalExpectation_MHT_ = new TH1D("totalExpectation_MHT","totalExpectation_MHT", 12, 250., 1200.);
  TH1D* totalExpectation_NJets_ = new TH1D("totalExpectation_NJets","totalExpectation_NJets", 9, 1.5, 10.5);
  TH1D* totalExpectation_BTags_ = new TH1D("totalExpectation_BTags","totalExpectation_BTags", 7, -0.5, 6.5);

  TH1D* totalPrediction_ = new TH1D("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionWoIso_ = new TH1D("TotalLostLeptonPredictionWoIso", "TotalLostLeptonPredictionWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredictionMu_ = new TH1D("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElec_ = new TH1D("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuWoIso_ = new TH1D("TotalLostLeptonPredictionMuWoIso", "TotalLostLeptonPredictionMuWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecWoIso_ = new TH1D("TotalLostLeptonPredictionElecWoIso", "TotalLostLeptonPredictionElecWoIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPrediction_HT_ = new TH1D("totalPrediction_HT","totalPrediction_HT", 18, 25., 2500.);
  TH1D* totalPrediction_MHT_ = new TH1D("totalPrediction_MHT","totalPrediction_MHT", 12, 250., 1200.);
  TH1D* totalPrediction_NJets_ = new TH1D("totalPrediction_NJets","totalPrediction_NJets", 9, 1.5, 10.5);
  TH1D* totalPrediction_BTags_ = new TH1D("totalPrediction_BTags","totalPrediction_BTags", 7, -0.5, 6.5);
    
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
  LostLeptonExpectation->SetBranchStatus("GenMus",1);
  LostLeptonExpectation->SetBranchAddress("GenMus",&GenMus);
  LostLeptonExpectation->SetBranchStatus("GenEls",1);
  LostLeptonExpectation->SetBranchAddress("GenEls",&GenEls);
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
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonExpectation->GetEntry(i);

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
      }else{
        scaledWeight = Weight * scaleFactorWeight;
      }

      if(Expectation==1)
        {
        totalExpectationWoIso_->Fill(Bin_bTags.at(i), scaledWeight);
        totalExp+=scaledWeight;
        totalExpError+= scaledWeight*scaledWeight;

        if(muAcc==0)
          {
          totalExpectationMuAcc_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuAccNJets_->Fill(NJets, scaledWeight);
          totalExpectationMuAccBTag_->Fill(i, scaledWeight);
          totalExpectationMuAccHT_->Fill(HT, scaledWeight);
          totalExpectationMuAccMHT_->Fill(MHT, scaledWeight);
          totalExpMuAcc+=scaledWeight;
          }
        if(muReco==0)
          {
          totalExpectationMuReco_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuRecoNJets_->Fill(NJets, scaledWeight);
          totalExpectationMuRecoBTag_->Fill(i, scaledWeight);
          totalExpectationMuRecoHT_->Fill(HT, scaledWeight);
          totalExpectationMuRecoMHT_->Fill(MHT, scaledWeight);
          totalExpMuReco+=scaledWeight;
          }
        if(muIso==0)
          {
          totalExpectationMuIso_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationMuIsoNJets_->Fill(NJets, scaledWeight);
          totalExpectationMuIsoBTag_->Fill(i, scaledWeight);
          totalExpectationMuIsoHT_->Fill(HT, scaledWeight);
          totalExpectationMuIsoMHT_->Fill(MHT, scaledWeight);
          totalExpMuIso+=scaledWeight;
          }
              
        if(elecAcc==0)
          {
          totalExpectationElecAcc_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecAccNJets_->Fill(NJets, scaledWeight);
          totalExpectationElecAccBTag_->Fill(i, scaledWeight);
          totalExpectationElecAccHT_->Fill(HT, scaledWeight);
          totalExpectationElecAccMHT_->Fill(MHT, scaledWeight);
          totalExpElecAcc+=scaledWeight;

          }
        if(elecReco==0)
          {
          totalExpectationElecReco_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecRecoNJets_->Fill(NJets, scaledWeight);
          totalExpectationElecRecoBTag_->Fill(i, scaledWeight);
          totalExpectationElecRecoHT_->Fill(HT, scaledWeight);
          totalExpectationElecRecoMHT_->Fill(MHT, scaledWeight);
          totalExpElecReco+=scaledWeight;
          }
        if(elecIso==0)
          {
          totalExpectationElecIso_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpectationElecIsoNJets_->Fill(NJets, scaledWeight);
          totalExpectationElecIsoBTag_->Fill(i, scaledWeight);
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
        totalExpectation_BTags_->Fill(i, scaledWeight);
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
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoMuons",1);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoMuons",&selectedIDIsoMuons);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoElectrons",1);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoElectrons",&selectedIDIsoElectrons);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags0",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags0",&totalWeight_BTags0);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags1Inf",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags1Inf",&totalWeight_BTags1Inf);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags0_noIsoTrack",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags0_noIsoTrack",&totalWeight_BTags0_noIsoTrack);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags1Inf_noIsoTrack",1);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags1Inf_noIsoTrack",&totalWeight_BTags1Inf_noIsoTrack);
  LostLeptonPrediction->SetBranchStatus("muTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchAddress("muTotalWeightDiLepIsoTrackReduced",&muTotalWeightDiLepIsoTrackReduced);
  LostLeptonPrediction->SetBranchStatus("elecTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchAddress("elecTotalWeightDiLepIsoTrackReduced",&elecTotalWeightDiLepIsoTrackReduced);
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

  std::cout<<"Loop on Prediction (MC)"<<std::endl;

  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
    }
    else SearchBin = Bin;

    if(SearchBin > 900) continue;
    if(MTW>100) continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1) continue;


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
/*
        totalPrediction_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);        
        totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2;
        totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2;       

        totalPredictionWoIso_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
        totalPre+=totalWeightDiLep*scaleFactorWeightBtagProb/2;
        totalPreError+= totalWeightDiLep*scaleFactorWeightBtagProb/2*totalWeightDiLep*scaleFactorWeightBtagProb/2;         
            
        totalPrediction_HT_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_MHT_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_NJets_->Fill(NJets, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPrediction_BTags_->Fill(i, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
*/
        if(i==0){
          totalPrediction_->Fill(Bin_bTags.at(i), totalWeight_BTags0*scaleFactorWeightBtagProb/2);
          totalPreIsoTrack+=totalWeight_BTags0*scaleFactorWeightBtagProb/2;
          totalPreIsoTrackError+=totalWeight_BTags0*scaleFactorWeightBtagProb/2*totalWeight_BTags0*scaleFactorWeightBtagProb/2;

          totalPredictionWoIso_->Fill(Bin_bTags.at(i), totalWeight_BTags0_noIsoTrack*scaleFactorWeightBtagProb/2);
          totalPre+=totalWeight_BTags0_noIsoTrack*scaleFactorWeightBtagProb/2;
          totalPreError+= totalWeight_BTags0_noIsoTrack*scaleFactorWeightBtagProb/2*totalWeight_BTags0_noIsoTrack*scaleFactorWeightBtagProb/2;         
              
          totalPrediction_HT_->Fill(HT, totalWeight_BTags0*scaleFactorWeightBtagProb/2);
          totalPrediction_MHT_->Fill(MHT, totalWeight_BTags0*scaleFactorWeightBtagProb/2);
          totalPrediction_NJets_->Fill(NJets, totalWeight_BTags0*scaleFactorWeightBtagProb/2);
          totalPrediction_BTags_->Fill(i, totalWeight_BTags0*scaleFactorWeightBtagProb/2);
        }else{
          totalPrediction_->Fill(Bin_bTags.at(i), totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2);
          totalPreIsoTrack+=totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2;
          totalPreIsoTrackError+=totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2*totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2;

          totalPredictionWoIso_->Fill(Bin_bTags.at(i), totalWeight_BTags1Inf_noIsoTrack*scaleFactorWeightBtagProb/2);
          totalPre+=totalWeight_BTags1Inf_noIsoTrack*scaleFactorWeightBtagProb/2;
          totalPreError+= totalWeight_BTags1Inf_noIsoTrack*scaleFactorWeightBtagProb/2*totalWeight_BTags1Inf_noIsoTrack*scaleFactorWeightBtagProb/2;         
              
          totalPrediction_HT_->Fill(HT, totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2);
          totalPrediction_MHT_->Fill(MHT, totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2);
          totalPrediction_NJets_->Fill(NJets, totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2);
          totalPrediction_BTags_->Fill(i, totalWeight_BTags1Inf*scaleFactorWeightBtagProb/2);
        }

          if(selectedIDIsoMuonsNum == 1){
            totalPredictionMu_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb);
            totalPredictionMuWoIso_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb);

            totalPreMu+=totalWeightDiLep*scaleFactorWeightBtagProb;
            totalPreMuError+= totalWeightDiLep*scaleFactorWeightBtagProb*totalWeightDiLep*scaleFactorWeightBtagProb;
            // isotrackveto applied
            totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb;
            totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb;


            totalPredictionMuCSMuAcc_->Fill(Bin_bTags.at(i), muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuReco_->Fill(Bin_bTags.at(i), muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIso_->Fill(Bin_bTags.at(i), muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccNJets_->Fill(NJets, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoNJets_->Fill(NJets, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoNJets_->Fill(NJets, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccBTag_->Fill(i, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoBTag_->Fill(i, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoBTag_->Fill(i, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccHT_->Fill(HT, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoHT_->Fill(HT, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoHT_->Fill(HT, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccMHT_->Fill(MHT, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoMHT_->Fill(MHT, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoMHT_->Fill(MHT, muIsoWeight*scaleFactorWeightBtagProb);
            totalPreMuAcc+=muAccWeight*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=muRecoWeight*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=muIsoWeight*scaleFactorWeightBtagProb/2;
            totalPreMuMuAcc+=muAccWeight*scaleFactorWeightBtagProb;
            totalPreMuMuReco+=muRecoWeight*scaleFactorWeightBtagProb;
            totalPreMuMuIso+=muIsoWeight*scaleFactorWeightBtagProb;
                
            totalPredictionMuCSElecAcc_->Fill(Bin_bTags.at(i), elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecReco_->Fill(Bin_bTags.at(i), elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIso_->Fill(Bin_bTags.at(i), elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccNJets_->Fill(NJets, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoNJets_->Fill(NJets, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoNJets_->Fill(NJets, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccBTag_->Fill(i, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoBTag_->Fill(i, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoBTag_->Fill(i, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccHT_->Fill(HT, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoHT_->Fill(HT, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoHT_->Fill(HT, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccMHT_->Fill(MHT, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoMHT_->Fill(MHT, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoMHT_->Fill(MHT, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPreElecAcc+=elecAccWeight*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=elecRecoWeight*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=elecIsoWeight*scaleFactorWeightBtagProb/2;
            totalPreMuElecAcc+=elecAccWeight*scaleFactorWeightBtagProb;
            totalPreMuElecReco+=elecRecoWeight*scaleFactorWeightBtagProb;
            totalPreMuElecIso+=elecIsoWeight*scaleFactorWeightBtagProb;

          }if(selectedIDIsoElectronsNum == 1){
            totalPredictionElec_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb);
            totalPredictionElecWoIso_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb);

            totalPreElec+=totalWeightDiLep*scaleFactorWeightBtagProb;
            totalPreElecError+= totalWeightDiLep*scaleFactorWeightBtagProb*totalWeightDiLep*scaleFactorWeightBtagProb;
            // isotrackveto applied
            totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb;
            totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb;


            totalPredictionElecCSElecAcc_->Fill(Bin_bTags.at(i), elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecReco_->Fill(Bin_bTags.at(i), elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIso_->Fill(Bin_bTags.at(i), elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccNJets_->Fill(NJets, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoNJets_->Fill(NJets, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoNJets_->Fill(NJets, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccBTag_->Fill(i, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoBTag_->Fill(i, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoBTag_->Fill(i, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccHT_->Fill(HT, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoHT_->Fill(HT, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoHT_->Fill(HT, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccMHT_->Fill(MHT, elecAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoMHT_->Fill(MHT, elecRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoMHT_->Fill(MHT, elecIsoWeight*scaleFactorWeightBtagProb);
            totalPreElecAcc+=elecAccWeight*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=elecRecoWeight*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=elecIsoWeight*scaleFactorWeightBtagProb/2;
            totalPreElecElecAcc+=elecAccWeight*scaleFactorWeightBtagProb;
            totalPreElecElecReco+=elecRecoWeight*scaleFactorWeightBtagProb;
            totalPreElecElecIso+=elecIsoWeight*scaleFactorWeightBtagProb;
                    
            totalPredictionElecCSMuAcc_->Fill(Bin_bTags.at(i), muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuReco_->Fill(Bin_bTags.at(i), muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIso_->Fill(Bin_bTags.at(i), muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccNJets_->Fill(NJets, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoNJets_->Fill(NJets, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoNJets_->Fill(NJets, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccBTag_->Fill(i, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoBTag_->Fill(i, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoBTag_->Fill(i, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccHT_->Fill(HT, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoHT_->Fill(HT, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoHT_->Fill(HT, muIsoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccMHT_->Fill(MHT, muAccWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoMHT_->Fill(MHT, muRecoWeight*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoMHT_->Fill(MHT, muIsoWeight*scaleFactorWeightBtagProb);
            totalPreMuAcc+=muAccWeight*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=muRecoWeight*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=muIsoWeight*scaleFactorWeightBtagProb/2;
            totalPreElecMuAcc+=muAccWeight*scaleFactorWeightBtagProb;
            totalPreElecMuReco+=muRecoWeight*scaleFactorWeightBtagProb;
            totalPreElecMuIso+=muIsoWeight*scaleFactorWeightBtagProb;
          }
      }
    }

  fPreMC->Close();
  std::cout<<"Finished"<<std::endl;

  //closure test
  TFile *outPutFile = new TFile(OutputPath_Closure.c_str(),"RECREATE"); 
  outPutFile->cd();

  outPutFile->mkdir("Closures");
  TDirectory *dClosures = (TDirectory*)outPutFile->Get("Closures");

  SaveClosure(totalPrediction_, totalExpectation_, dClosures);
  SaveClosure(totalPredictionMu_, totalExpectation_, dClosures);
  SaveClosure(totalPredictionElec_, totalExpectation_, dClosures);

  SaveClosure(totalPredictionWoIso_, totalExpectationWoIso_, dClosures);
  SaveClosure(totalPredictionMuWoIso_, totalExpectationWoIso_, dClosures);
  SaveClosure(totalPredictionElecWoIso_, totalExpectationWoIso_, dClosures);

  SaveClosure(totalPrediction_HT_, totalExpectation_HT_, dClosures);    
  SaveClosure(totalPrediction_MHT_, totalExpectation_MHT_, dClosures);    
  SaveClosure(totalPrediction_NJets_, totalExpectation_NJets_, dClosures);    
  SaveClosure(totalPrediction_BTags_, totalExpectation_BTags_, dClosures);    

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
  if(Closure->GetNbinsX()==190) SetBinLabel(Closure);
  Folder->cd();
  Closure->Write();
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