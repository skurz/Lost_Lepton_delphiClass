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
#include "TStyle.h"

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder);
UShort_t getMergedBinQCD(UShort_t BinQCD, Int_t NJets);
UShort_t getHTMHTBox(Double_t HT, Double_t MHT);
void SetBinLabel(TH1D* hist);
void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir);
void addUncertainties(TH1D* total, std::vector<TH1D*> uncertainties, bool upperUnc);
void SavePlot(TProfile* plot);

const int nTemplateBins(13);

using std::string;

void ResultPlot(string InputPath_Expectation="Expectation.root",
    string InputPath_Efficiencies="Efficiencies.root",
    string InputPath_Prediction="Prediction.root",
    string InputPath_Prediction_Data="Prediction_data.root", // Use same path as above if pure MC prediction wanted
    string OutputPath_Closure="Closure.root",
    string OutputPath_Prediction="LLPrediction_ResultsPlot.root")
{
  
  // Present output in QCD binning
  bool doQCDbinning = false;  //<-check------------------------

  // Weight MC events with bTag probabilities
  bool doBtagProbabilities = true;

  // Prepare Code for Extrapolation Method
  bool doExtrapolation = false; // fixes for additional NJets bins have to bin done

  // If you want to compare MC to MC set this to true. E.g. prediction with and without signal contamination
  bool useMCForDataTree = false;

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 35862.351;  //in units of [pb] //<-check------------------------

  // Do approximation of statistical uncertainties if full MC statistics are used (stat. unc. then refers to a given luminosity of data)
  // Leave at 'false' if doing a closure test so stat. uncertainty is the one using full MC statistics
  bool approxStatUncertainty = false;


  //Merge QCDbins (bTags) = 55 bins // only works if doQCDbinning = true;
  //BUT: Output table does not work! However, histograms are filled properly
  bool mergeQCDbins = false; 

  // Histograms for Readiness Talk
  bool doMergedHistograms = false;


  // Begin of Code
  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);
  int nSearchBinsTotal = SearchBins_->GetNbins();

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
  TBranch* b_Muons=0;
  TBranch* b_Electrons=0;
  
  std::vector<Float_t>* MuonsPTW=0;
  std::vector<Float_t>* ElectronsPTW=0;
  TBranch* b_MuonsPTW=0;
  TBranch* b_ElectronsPTW=0;

  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<TLorentzVector> *GenElectrons=0;
  TBranch* b_GenMuons=0;
  TBranch* b_GenElectrons=0;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReduced;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;
  std::vector<Float_t>*        totalWeight_BTags=0;
  std::vector<Float_t>*        totalWeight_BTags_noIsoTrack=0;

  std::vector<Float_t>* totalWeight_BTags_MTW=0;
  std::vector<Float_t>* totalWeight_BTags_MuAcc=0;
  std::vector<Float_t>* totalWeight_BTags_MuReco=0;
  std::vector<Float_t>* totalWeight_BTags_MuIso=0;
  std::vector<Float_t>* totalWeight_BTags_ElecAcc=0;
  std::vector<Float_t>* totalWeight_BTags_ElecReco=0;
  std::vector<Float_t>* totalWeight_BTags_ElecIso=0;


  Float_t         muTotalWeightDiLepIsoTrackReduced;
  Float_t         elecTotalWeightDiLepIsoTrackReduced;
  
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

  // Uncertainties
  Float_t isoTrackStatUp;
  Float_t isoTrackStatDown;
  Float_t muIsoTrackStatUp;
  Float_t muIsoTrackStatDown;
  Float_t elecIsoTrackStatUp;
  Float_t elecIsoTrackStatDown;
  Float_t pionIsoTrackStatUp;
  Float_t pionIsoTrackStatDown;
  Float_t MTWStatUp;
  Float_t MTWStatDown;
  Float_t purityStatUp;
  Float_t purityStatDown;
  Float_t singleLepPurityStatUp;
  Float_t singleLepPurityStatDown;
  Float_t diLepFoundStatUp;
  Float_t diLepFoundStatDown;
  Float_t muIsoStatUp;
  Float_t muIsoStatDown;
  Float_t muRecoStatUp;
  Float_t muRecoStatDown;
  Float_t muAccStatUp;
  Float_t muAccStatDown;
  Float_t elecIsoStatUp;
  Float_t elecIsoStatDown;
  Float_t elecRecoStatUp;
  Float_t elecRecoStatDown;
  Float_t elecAccStatUp;
  Float_t elecAccStatDown;

  Float_t isoTrackSysUp;
  Float_t isoTrackSysDown;
  Float_t muIsoTrackSysUp;
  Float_t muIsoTrackSysDown;
  Float_t elecIsoTrackSysUp;
  Float_t elecIsoTrackSysDown;
  Float_t pionIsoTrackSysUp;
  Float_t pionIsoTrackSysDown;
  Float_t MTWSysUp;
  Float_t MTWSysDown;
  Float_t puritySysUp;
  Float_t puritySysDown;
  Float_t singleLepPuritySysUp;
  Float_t singleLepPuritySysDown;
  Float_t diLepFoundSysUp;
  Float_t diLepFoundSysDown;
  Float_t muIsoSysUp;
  Float_t muIsoSysDown;
  Float_t muRecoSysUp;
  Float_t muRecoSysDown;
  Float_t muAccSysUp;
  Float_t muAccSysDown;
  Float_t muAccQsquareSysUp;
  Float_t muAccQsquareSysDown;
  Float_t elecIsoSysUp;
  Float_t elecIsoSysDown;
  Float_t elecRecoSysUp;
  Float_t elecRecoSysDown;
  Float_t elecAccSysUp;
  Float_t elecAccSysDown;
  Float_t elecAccQsquareSysUp;
  Float_t elecAccQsquareSysDown;

  Float_t totalPropSysUp;
  Float_t totalPropSysDown;

  //closure test
  TFile *outPutFile = new TFile(OutputPath_Closure.c_str(),"RECREATE"); 
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
  
  TH1D* ControlSampleMu_ = new TH1D("ControlSampleMu", "ControlSampleMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* ControlSampleElec_ = new TH1D("ControlSampleElec", "ControlSampleElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectation_ = new TH1D("TotalLostLeptonExpectation", "TotalLostLeptonExpectation", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPrediction_ = new TH1D("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMu_ = new TH1D("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElec_ = new TH1D("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationIsoTrackReduction_ = new TH1D("TotalLostLeptonExpectationIsoTrackReduction", "TotalLostLeptonExpectationIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionIsoTrackReduction", "TotalLostLeptonPredictionIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionMuIsoTrackReduction", "TotalLostLeptonPredictionMuIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionElecIsoTrackReduction", "TotalLostLeptonPredictionElecIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  // separted closure
  TH1D* totalExpectationMuAcc_ = new TH1D("TotalLostLeptonExpectationMuAcc", "TotalLostLeptonExpectationMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuAcc_ = new TH1D("TotalLostLeptonPredictionMuCSMuAcc", "TotalLostLeptonPredictionMuCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuAcc_ = new TH1D("TotalLostLeptonPredictionElecCSMuAcc", "TotalLostLeptonPredictionElecCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationMuReco_ = new TH1D("TotalLostLeptonExpectationMuReco", "TotalLostLeptonExpectationMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuReco_ = new TH1D("TotalLostLeptonPredictionMuCSMuReco", "TotalLostLeptonPredictionMuCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuReco_ = new TH1D("TotalLostLeptonPredictionElecCSMuReco", "TotalLostLeptonPredictionElecCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationMuIso_ = new TH1D("TotalLostLeptonExpectationMuIso", "TotalLostLeptonExpectationMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuIso_ = new TH1D("TotalLostLeptonPredictionMuCSMuIso", "TotalLostLeptonPredictionMuCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuIso_ = new TH1D("TotalLostLeptonPredictionElecCSMuIso", "TotalLostLeptonPredictionElecCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);  
  
  TH1D* totalExpectationElecAcc_ = new TH1D("TotalLostLeptonExpectationElecAcc", "TotalLostLeptonExpectationElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecAcc_ = new TH1D("TotalLostLeptonPredictionMuCSElecAcc", "TotalLostLeptonPredictionMuCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecAcc_ = new TH1D("TotalLostLeptonPredictionElecCSElecAcc", "TotalLostLeptonPredictionElecCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationElecReco_ = new TH1D("TotalLostLeptonExpectationElecReco", "TotalLostLeptonExpectationElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecReco_ = new TH1D("TotalLostLeptonPredictionMuCSElecReco", "TotalLostLeptonPredictionMuCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecReco_ = new TH1D("TotalLostLeptonPredictionElecCSElecReco", "TotalLostLeptonPredictionElecCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  
  TH1D* totalExpectationElecIso_ = new TH1D("TotalLostLeptonExpectationElecIso", "TotalLostLeptonExpectationElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecIso_ = new TH1D("TotalLostLeptonPredictionMuCSElecIso", "TotalLostLeptonPredictionMuCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecIso_ = new TH1D("TotalLostLeptonPredictionElecCSElecIso", "TotalLostLeptonPredictionElecCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalExpectationMuAccNJets_ = new TH1D("TotalLostLeptonExpectationMuAccNJets", "TotalLostLeptonExpectationMuAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuAccNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccNJets", "TotalLostLeptonPredictionMuCSMuAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuAccNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccNJets", "TotalLostLeptonPredictionElecCSMuAccNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationMuRecoNJets_ = new TH1D("TotalLostLeptonExpectationMuRecoNJets", "TotalLostLeptonExpectationMuRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuRecoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoNJets", "TotalLostLeptonPredictionMuCSMuRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuRecoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoNJets", "TotalLostLeptonPredictionElecCSMuRecoNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationMuIsoNJets_ = new TH1D("TotalLostLeptonExpectationMuIsoNJets", "TotalLostLeptonExpectationMuIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSMuIsoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoNJets", "TotalLostLeptonPredictionMuCSMuIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSMuIsoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoNJets", "TotalLostLeptonPredictionElecCSMuIsoNJets", 9, 1.5, 10.5);  
  
  TH1D* totalExpectationElecAccNJets_ = new TH1D("TotalLostLeptonExpectationElecAccNJets", "TotalLostLeptonExpectationElecAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecAccNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccNJets", "TotalLostLeptonPredictionMuCSElecAccNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecAccNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccNJets", "TotalLostLeptonPredictionElecCSElecAccNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationElecRecoNJets_ = new TH1D("TotalLostLeptonExpectationElecRecoNJets", "TotalLostLeptonExpectationElecRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecRecoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoNJets", "TotalLostLeptonPredictionMuCSElecRecoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecRecoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoNJets", "TotalLostLeptonPredictionElecCSElecRecoNJets", 9, 1.5, 10.5);
  
  TH1D* totalExpectationElecIsoNJets_ = new TH1D("TotalLostLeptonExpectationElecIsoNJets", "TotalLostLeptonExpectationElecIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionMuCSElecIsoNJets_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoNJets", "TotalLostLeptonPredictionMuCSElecIsoNJets", 9, 1.5, 10.5);
  TH1D* totalPredictionElecCSElecIsoNJets_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoNJets", "TotalLostLeptonPredictionElecCSElecIsoNJets", 9, 1.5, 10.5);

  TH1D* totalExpectationMuAccHT_ = new TH1D("TotalLostLeptonExpectationMuAccHT", "TotalLostLeptonExpectationMuAccHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuAccHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccHT", "TotalLostLeptonPredictionMuCSMuAccHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuAccHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccHT", "TotalLostLeptonPredictionElecCSMuAccHT", 18, 250., 2500.);
  
  TH1D* totalExpectationMuRecoHT_ = new TH1D("TotalLostLeptonExpectationMuRecoHT", "TotalLostLeptonExpectationMuRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuRecoHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoHT", "TotalLostLeptonPredictionMuCSMuRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuRecoHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoHT", "TotalLostLeptonPredictionElecCSMuRecoHT", 18, 250., 2500.);
  
  TH1D* totalExpectationMuIsoHT_ = new TH1D("TotalLostLeptonExpectationMuIsoHT", "TotalLostLeptonExpectationMuIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSMuIsoHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoHT", "TotalLostLeptonPredictionMuCSMuIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSMuIsoHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoHT", "TotalLostLeptonPredictionElecCSMuIsoHT", 18, 250., 2500.);  
  
  TH1D* totalExpectationElecAccHT_ = new TH1D("TotalLostLeptonExpectationElecAccHT", "TotalLostLeptonExpectationElecAccHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecAccHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccHT", "TotalLostLeptonPredictionMuCSElecAccHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecAccHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccHT", "TotalLostLeptonPredictionElecCSElecAccHT", 18, 250., 2500.);
  
  TH1D* totalExpectationElecRecoHT_ = new TH1D("TotalLostLeptonExpectationElecRecoHT", "TotalLostLeptonExpectationElecRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecRecoHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoHT", "TotalLostLeptonPredictionMuCSElecRecoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecRecoHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoHT", "TotalLostLeptonPredictionElecCSElecRecoHT", 18, 250., 2500.);
  
  TH1D* totalExpectationElecIsoHT_ = new TH1D("TotalLostLeptonExpectationElecIsoHT", "TotalLostLeptonExpectationElecIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionMuCSElecIsoHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoHT", "TotalLostLeptonPredictionMuCSElecIsoHT", 18, 250., 2500.);
  TH1D* totalPredictionElecCSElecIsoHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoHT", "TotalLostLeptonPredictionElecCSElecIsoHT", 18, 250., 2500.);

  TH1D* totalExpectationMuAccMHT_ = new TH1D("TotalLostLeptonExpectationMuAccMHT", "TotalLostLeptonExpectationMuAccMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuAccMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccMHT", "TotalLostLeptonPredictionMuCSMuAccMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuAccMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccMHT", "TotalLostLeptonPredictionElecCSMuAccMHT", 12, 250., 850.);
  
  TH1D* totalExpectationMuRecoMHT_ = new TH1D("TotalLostLeptonExpectationMuRecoMHT", "TotalLostLeptonExpectationMuRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuRecoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoMHT", "TotalLostLeptonPredictionMuCSMuRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuRecoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoMHT", "TotalLostLeptonPredictionElecCSMuRecoMHT", 12, 250., 850.);
  
  TH1D* totalExpectationMuIsoMHT_ = new TH1D("TotalLostLeptonExpectationMuIsoMHT", "TotalLostLeptonExpectationMuIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSMuIsoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoMHT", "TotalLostLeptonPredictionMuCSMuIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSMuIsoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoMHT", "TotalLostLeptonPredictionElecCSMuIsoMHT", 12, 250., 850.);  
  
  TH1D* totalExpectationElecAccMHT_ = new TH1D("TotalLostLeptonExpectationElecAccMHT", "TotalLostLeptonExpectationElecAccMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecAccMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccMHT", "TotalLostLeptonPredictionMuCSElecAccMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecAccMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccMHT", "TotalLostLeptonPredictionElecCSElecAccMHT", 12, 250., 850.);
  
  TH1D* totalExpectationElecRecoMHT_ = new TH1D("TotalLostLeptonExpectationElecRecoMHT", "TotalLostLeptonExpectationElecRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecRecoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoMHT", "TotalLostLeptonPredictionMuCSElecRecoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecRecoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoMHT", "TotalLostLeptonPredictionElecCSElecRecoMHT", 12, 250., 850.);
  
  TH1D* totalExpectationElecIsoMHT_ = new TH1D("TotalLostLeptonExpectationElecIsoMHT", "TotalLostLeptonExpectationElecIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionMuCSElecIsoMHT_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoMHT", "TotalLostLeptonPredictionMuCSElecIsoMHT", 12, 250., 850.);
  TH1D* totalPredictionElecCSElecIsoMHT_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoMHT", "TotalLostLeptonPredictionElecCSElecIsoMHT", 12, 250., 850.);

  TH1D* totalExpectationMuAccBTag_ = new TH1D("TotalLostLeptonExpectationMuAccBTag", "TotalLostLeptonExpectationMuAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuAccBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuAccBTag", "TotalLostLeptonPredictionMuCSMuAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuAccBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuAccBTag", "TotalLostLeptonPredictionElecCSMuAccBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationMuRecoBTag_ = new TH1D("TotalLostLeptonExpectationMuRecoBTag", "TotalLostLeptonExpectationMuRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuRecoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuRecoBTag", "TotalLostLeptonPredictionMuCSMuRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuRecoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuRecoBTag", "TotalLostLeptonPredictionElecCSMuRecoBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationMuIsoBTag_ = new TH1D("TotalLostLeptonExpectationMuIsoBTag", "TotalLostLeptonExpectationMuIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSMuIsoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSMuIsoBTag", "TotalLostLeptonPredictionMuCSMuIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSMuIsoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSMuIsoBTag", "TotalLostLeptonPredictionElecCSMuIsoBTag", 7, -0.5, 6.5);  
  
  TH1D* totalExpectationElecAccBTag_ = new TH1D("TotalLostLeptonExpectationElecAccBTag", "TotalLostLeptonExpectationElecAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecAccBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecAccBTag", "TotalLostLeptonPredictionMuCSElecAccBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecAccBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecAccBTag", "TotalLostLeptonPredictionElecCSElecAccBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationElecRecoBTag_ = new TH1D("TotalLostLeptonExpectationElecRecoBTag", "TotalLostLeptonExpectationElecRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecRecoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecRecoBTag", "TotalLostLeptonPredictionMuCSElecRecoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecRecoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecRecoBTag", "TotalLostLeptonPredictionElecCSElecRecoBTag", 7, -0.5, 6.5);
  
  TH1D* totalExpectationElecIsoBTag_ = new TH1D("TotalLostLeptonExpectationElecIsoBTag", "TotalLostLeptonExpectationElecIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionMuCSElecIsoBTag_ = new TH1D("TotalLostLeptonPredictionMuCSElecIsoBTag", "TotalLostLeptonPredictionMuCSElecIsoBTag", 7, -0.5, 6.5);
  TH1D* totalPredictionElecCSElecIsoBTag_ = new TH1D("TotalLostLeptonPredictionElecCSElecIsoBTag", "TotalLostLeptonPredictionElecCSElecIsoBTag", 7, -0.5, 6.5);



  // Define histrograms to do totalPrediction per SearchBin
  TH1D* totalExp_LL_ = new TH1D("totalExp_LL","totalExp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalExpwoIso_LL_ = new TH1D("totalExpwoIso_LL","totalExpwoIso_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  //  TH1D* totalExp_LL_NoTk_ = new TH1D("totalExp_LL_NoTk","totalExp_LL_NoTk", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsExp_LL_ = new TH1D("nEvtsExp_LL","nEvtsExp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalExp_HT_LL_ = new TH1D("totalExp_HT_LL","totalExp_HT_LL;H_{T} [GeV]", 18, 250., 2500.);
  TH1D* totalExp_MHT_LL_ = new TH1D("totalExp_MHT_LL","totalExp_MHT_LL;H_{T}^{miss} [GeV]", 12, 250., 850.);
  TH1D* totalExp_NJets_LL_ = new TH1D("totalExp_NJets_LL","totalExp_NJets_LL;N_{jet} (p_{T} > 30 GeV)", 9, 1.5, 10.5);
  TH1D* totalExp_BTags_LL_ = new TH1D("totalExp_BTags_LL","totalExp_BTags_LL;N_{b-jet} (p_{T} > 30 GeV)", 7, -0.5, 6.5);

  // JACK--debug PTW measurement
  TH1D* totalExp_PTW_LL_ = new TH1D("totalExp_PTW_LL","totalExp_PTW_LL;p_{T}^{W} [GeV]", 38, 0, 950);
  TH1D* totalExp_PTW_LL_0b_ = new TH1D("totalExp_PTW_LL_0b","totalExp_PTW_LL_0b;p_{T}^{W} [GeV]", 38, 0, 950);
  TH1D* totalExp_PTW_LL_1b_ = new TH1D("totalExp_PTW_LL_1b","totalExp_PTW_LL_1b;p_{T}^{W} [GeV]", 38, 0, 950);
  TH1D* totalExp_PTW_LL_2b_ = new TH1D("totalExp_PTW_LL_2b","totalExp_PTW_LL_2b;p_{T}^{W} [GeV]", 38, 0, 950);
  TH1D* totalExp_PTL_LL_ = new TH1D("totalExp_PTL_LL","totalExp_PTL_LL;p_{T}^{e/#mu} [GeV]", 51, 0., 510.);
  TH1D* totalExp_ETAL_LL_ = new TH1D("totalExp_ETAL_LL","totalExp_ETAL_LL;#eta^{e/#mu} [GeV]", 60, -3., 3.);

 
  // JACK--comparing classical and extrapolated MHT predictions
  TH1D* totalExp_MHT_Normal_HT12_LL_[12];
  TH1D* totalExp_MHT_Normal_HT3_LL_[12];
  TH1D* totalExp_MHT_Normal_HT23_LL_[12];
  TH1D* totalPred_MHT_Normal_HT12_LL_[12];
  TH1D* totalPred_MHT_Normal_HT3_LL_[12];
  TH1D* totalPred_MHT_Normal_HT23_LL_[12];
  TH1D* totalPred_MHT_Normal_HT12_LL_MC_[12];
  TH1D* totalPred_MHT_Normal_HT3_LL_MC_[12];
  TH1D* totalPred_MHT_Normal_HT23_LL_MC_[12];
  // These store the extrpolated predicitons in the high-MHT bins
  TH1D* totalPred_MHT_EXTRAP_HT12_LL_[12];
  TH1D* totalPred_MHT_EXTRAP_HT3_LL_[12];
  TH1D* totalPred_MHT_EXTRAP_HT23_LL_[12];
  TH1D* totalPred_MHT_EXTRAP_HT12_LL_MC_[12];
  TH1D* totalPred_MHT_EXTRAP_HT3_LL_MC_[12];
  TH1D* totalPred_MHT_EXTRAP_HT23_LL_MC_[12];
  // these are for calculating the new average weight
  TH1D* totalCR_MHT_HT12_LL_[12];
  TH1D* totalCR_MHT_HT3_LL_[12];
  TH1D* totalCR_MHT_HT23_LL_[12];
  TH1D* totalCR_MHT_HT12_LL_MC_[12];
  TH1D* totalCR_MHT_HT3_LL_MC_[12];
  TH1D* totalCR_MHT_HT23_LL_MC_[12];
  TH1D* totalCR_PTW_HT12_LL_[12];
  TH1D* totalCR_PTW_HT3_LL_[12];
  TH1D* totalCR_PTW_HT23_LL_[12];
  TH1D* totalCR_PTW_HT12_LL_MC_[12];
  TH1D* totalCR_PTW_HT3_LL_MC_[12];
  TH1D* totalCR_PTW_HT23_LL_MC_[12];
  
  TFile* EffFile = new TFile(InputPath_Efficiencies.c_str(), "read");
  // these are the MHT/PTW templates
  TH1D* LostMuRATIO_HT12[9];
  TH1D* LostElecRATIO_HT12[9];
  TH1D* LostLepRATIO_HT12[9];
  TH1D* LostMuRATIO_HT3[9];
  TH1D* LostElecRATIO_HT3[9];
  TH1D* LostLepRATIO_HT3[9];
  TH1D* LostMuRATIO_HT23[9];
  TH1D* LostElecRATIO_HT23[9];
  TH1D* LostLepRATIO_HT23[9];

  // note the additional slices--this is to account for the MHT/PTW > 1 tail
  Double_t mht_bins[6] = {200, 400, 500, 600, 750, 10000};
  Double_t ptw_bins[6] = {200, 400, 500, 600, 750, 10000}; 
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<4; inb++) {
      totalExp_MHT_Normal_HT12_LL_[inj*4+inb] = new TH1D(Form("totalExp_MHT_Normal_HT12_NJ%d_NB%d_LL", inj+1, inb), Form("totalExp_MHT_Normal_HT12_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalExp_MHT_Normal_HT3_LL_[inj*4+inb] = new TH1D(Form("totalExp_MHT_Normal_HT3_NJ%d_NB%d_LL", inj+1, inb), Form("totalExp_MHT_Normal_HT3_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalExp_MHT_Normal_HT23_LL_[inj*4+inb] = new TH1D(Form("totalExp_MHT_Normal_HT23_NJ%d_NB%d_LL", inj+1, inb), Form("totalExp_MHT_Normal_HT23_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);

      totalPred_MHT_Normal_HT12_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT12_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_Normal_HT12_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalPred_MHT_Normal_HT3_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT3_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_Normal_HT3_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalPred_MHT_Normal_HT23_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT23_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_Normal_HT23_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);

      totalPred_MHT_Normal_HT12_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_Normal_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);
      totalPred_MHT_Normal_HT3_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_Normal_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);
      totalPred_MHT_Normal_HT23_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_Normal_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_Normal_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);

      totalPred_MHT_EXTRAP_HT12_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT12_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT12_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalPred_MHT_EXTRAP_HT3_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT3_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT3_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);
      totalPred_MHT_EXTRAP_HT23_LL_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT23_NJ%d_NB%d_LL", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT23_NJ%d_NB%d_LL", inj+1, inb), 4, mht_bins);

      totalPred_MHT_EXTRAP_HT12_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);
      totalPred_MHT_EXTRAP_HT3_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);
      totalPred_MHT_EXTRAP_HT23_LL_MC_[inj*4+inb] = new TH1D(Form("totalPred_MHT_EXTRAP_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalPred_MHT_EXTRAP_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), 4, mht_bins);
     
      totalCR_MHT_HT12_LL_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT12_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_MHT_HT12_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_MHT_HT3_LL_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT3_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_MHT_HT3_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_MHT_HT23_LL_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT23_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_MHT_HT23_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_MHT_HT12_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_MHT_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);
      totalCR_MHT_HT3_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_MHT_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);
      totalCR_MHT_HT23_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_MHT_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_MHT_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);

      totalCR_PTW_HT12_LL_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT12_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_PTW_HT12_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_PTW_HT3_LL_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT3_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_PTW_HT3_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_PTW_HT23_LL_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT23_NJ%d_NB%d_LL", inj+1, inb), Form("totalCR_PTW_HT23_NJ%d_NB%d_LL", inj+1, inb), 4, ptw_bins);
      totalCR_PTW_HT12_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_PTW_HT12_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);
      totalCR_PTW_HT3_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_PTW_HT3_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);
      totalCR_PTW_HT23_LL_MC_[inj*4+inb] = new TH1D(Form("totalCR_PTW_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), Form("totalCR_PTW_HT23_NJ%d_NB%d_LL_MC", inj+1, inb), 4, ptw_bins);
      // THE templates
      if (inb>3) continue;
      LostMuRATIO_HT12[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostMuRATIO_HT12_NJ%d_NB%d", inj+1, inb)); 
      LostElecRATIO_HT12[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostElecRATIO_HT12_NJ%d_NB%d", inj+1, inb));
      LostLepRATIO_HT12[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostLepRATIO_HT12_NJ%d_NB%d", inj+1, inb));
      LostMuRATIO_HT3[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostMuRATIO_HT3_NJ%d_NB%d", inj+1, inb)); 
      LostElecRATIO_HT3[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostElecRATIO_HT3_NJ%d_NB%d", inj+1, inb));
      LostLepRATIO_HT3[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostLepRATIO_HT3_NJ%d_NB%d", inj+1, inb));
      LostMuRATIO_HT23[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostMuRATIO_HT23_NJ%d_NB%d", inj+1, inb)); 
      LostElecRATIO_HT23[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostElecRATIO_HT23_NJ%d_NB%d", inj+1, inb));
      LostLepRATIO_HT23[inj*3+inb] = (TH1D*)EffFile->Get(Form("ExtrapPDFs/LostLepRATIO_HT23_NJ%d_NB%d", inj+1, inb));
    }
  }
  

  TH1D* totalPred_LL_ = new TH1D("totalPred_LL","totalPred_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPred_EXTRAP_LL_ = new TH1D("totalPred_EXTRAP_LL","totalPred_EXTRAP_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPred_HT_LL_ = new TH1D("totalPred_HT_LL","totalPred_HT_LL", 18, 250., 2500.);
  TH1D* totalPred_MHT_LL_ = new TH1D("totalPred_MHT_LL","totalPred_MHT_LL", 12, 250., 1200.);
  TH1D* totalPred_NJets_LL_ = new TH1D("totalPred_NJets_LL","totalPred_NJets_LL", 9, 1.5, 10.5);
  TH1D* totalPred_BTags_LL_ = new TH1D("totalPred_BTags_LL","totalPred_BTags_LL", 7, -0.5, 6.5);

  TH1D* totalPredIsoTrackSysUp_LL_ = new TH1D("totalPredIsoTrackSysUp_LL","totalPredIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysDown_LL_ = new TH1D("totalPredIsoTrackSysDown_LL","totalPredIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysUp_LL_ = new TH1D("totalPredMuIsoTrackSysUp_LL","totalPredMuIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysDown_LL_ = new TH1D("totalPredMuIsoTrackSysDown_LL","totalPredMuIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysUp_LL_ = new TH1D("totalPredElecIsoTrackSysUp_LL","totalPredElecIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysDown_LL_ = new TH1D("totalPredElecIsoTrackSysDown_LL","totalPredElecIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysUp_LL_ = new TH1D("totalPredPionIsoTrackSysUp_LL","totalPredPionIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysDown_LL_ = new TH1D("totalPredPionIsoTrackSysDown_LL","totalPredPionIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysUp_LL_ = new TH1D("totalPredMTWSysUp_LL","totalPredMTWSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysDown_LL_ = new TH1D("totalPredMTWSysDown_LL","totalPredMTWSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysUp_LL_ = new TH1D("totalPredPuritySysUp_LL","totalPredPuritySysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysDown_LL_ = new TH1D("totalPredPuritySysDown_LL","totalPredPuritySysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysUp_LL_ = new TH1D("totalPredSingleLepPuritySysUp_LL","totalPredSingleLepPuritySysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysDown_LL_ = new TH1D("totalPredSingleLepPuritySysDown_LL","totalPredSingleLepPuritySysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysUp_LL_ = new TH1D("totalPredDiLepFoundSysUp_LL","totalPredDiLepFoundSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysDown_LL_ = new TH1D("totalPredDiLepFoundSysDown_LL","totalPredDiLepFoundSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysUp_LL_ = new TH1D("totalPredMuIsoSysUp_LL","totalPredMuIsoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysDown_LL_ = new TH1D("totalPredMuIsoSysDown_LL","totalPredMuIsoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysUp_LL_ = new TH1D("totalPredMuRecoSysUp_LL","totalPredMuRecoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysDown_LL_ = new TH1D("totalPredMuRecoSysDown_LL","totalPredMuRecoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysUp_LL_ = new TH1D("totalPredMuAccSysUp_LL","totalPredMuAccSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysDown_LL_ = new TH1D("totalPredMuAccSysDown_LL","totalPredMuAccSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysUp_LL_ = new TH1D("totalPredMuAccQsquareSysUp_LL","totalPredMuAccQsquareSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysDown_LL_ = new TH1D("totalPredMuAccQsquareSysDown_LL","totalPredMuAccQsquareSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysUp_LL_ = new TH1D("totalPredElecIsoSysUp_LL","totalPredElecIsoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysDown_LL_ = new TH1D("totalPredElecIsoSysDown_LL","totalPredElecIsoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysUp_LL_ = new TH1D("totalPredElecRecoSysUp_LL","totalPredElecRecoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysDown_LL_ = new TH1D("totalPredElecRecoSysDown_LL","totalPredElecRecoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysUp_LL_ = new TH1D("totalPredElecAccSysUp_LL","totalPredElecAccSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysDown_LL_ = new TH1D("totalPredElecAccSysDown_LL","totalPredElecAccSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysUp_LL_ = new TH1D("totalPredElecAccQsquareSysUp_LL","totalPredElecAccQsquareSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysDown_LL_ = new TH1D("totalPredElecAccQsquareSysDown_LL","totalPredElecAccQsquareSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureUp_LL_ = new TH1D("totalPredNonClosureUp_LL","totalPredNonClosureUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureDown_LL_ = new TH1D("totalPredNonClosureDown_LL","totalPredNonClosureDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredIsoTrackStatUp_LL_ = new TH1D("totalPredIsoTrackStatUp_LL","totalPredIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackStatDown_LL_ = new TH1D("totalPredIsoTrackStatDown_LL","totalPredIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatUp_LL_ = new TH1D("totalPredMuIsoTrackStatUp_LL","totalPredMuIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatDown_LL_ = new TH1D("totalPredMuIsoTrackStatDown_LL","totalPredMuIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatUp_LL_ = new TH1D("totalPredElecIsoTrackStatUp_LL","totalPredElecIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatDown_LL_ = new TH1D("totalPredElecIsoTrackStatDown_LL","totalPredElecIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatUp_LL_ = new TH1D("totalPredPionIsoTrackStatUp_LL","totalPredPionIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatDown_LL_ = new TH1D("totalPredPionIsoTrackStatDown_LL","totalPredPionIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatUp_LL_ = new TH1D("totalPredMTWStatUp_LL","totalPredMTWStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatDown_LL_ = new TH1D("totalPredMTWStatDown_LL","totalPredMTWStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatUp_LL_ = new TH1D("totalPredPurityStatUp_LL","totalPredPurityStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatDown_LL_ = new TH1D("totalPredPurityStatDown_LL","totalPredPurityStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatUp_LL_ = new TH1D("totalPredSingleLepPurityStatUp_LL","totalPredSingleLepPurityStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatDown_LL_ = new TH1D("totalPredSingleLepPurityStatDown_LL","totalPredSingleLepPurityStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatUp_LL_ = new TH1D("totalPredDiLepFoundStatUp_LL","totalPredDiLepFoundStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatDown_LL_ = new TH1D("totalPredDiLepFoundStatDown_LL","totalPredDiLepFoundStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatUp_LL_ = new TH1D("totalPredMuIsoStatUp_LL","totalPredMuIsoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatDown_LL_ = new TH1D("totalPredMuIsoStatDown_LL","totalPredMuIsoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatUp_LL_ = new TH1D("totalPredMuRecoStatUp_LL","totalPredMuRecoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatDown_LL_ = new TH1D("totalPredMuRecoStatDown_LL","totalPredMuRecoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatUp_LL_ = new TH1D("totalPredMuAccStatUp_LL","totalPredMuAccStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatDown_LL_ = new TH1D("totalPredMuAccStatDown_LL","totalPredMuAccStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatUp_LL_ = new TH1D("totalPredElecIsoStatUp_LL","totalPredElecIsoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatDown_LL_ = new TH1D("totalPredElecIsoStatDown_LL","totalPredElecIsoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatUp_LL_ = new TH1D("totalPredElecRecoStatUp_LL","totalPredElecRecoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatDown_LL_ = new TH1D("totalPredElecRecoStatDown_LL","totalPredElecRecoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatUp_LL_ = new TH1D("totalPredElecAccStatUp_LL","totalPredElecAccStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatDown_LL_ = new TH1D("totalPredElecAccStatDown_LL","totalPredElecAccStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPropSysUp_LL_ = new TH1D("totalPropSysUp_LL","totalPropSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPropSysDown_LL_ = new TH1D("totalPropSysDown_LL","totalPropSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_LL_ = new TH1D("totalCS_LL","totalCS_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsCS_LL_ = new TH1D("nEvtsCS_LL","nEvtsCS_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_mu_HT_LL_ = new TH1D("totalCS_mu_HT_LL","totalCS_mu_HT_LL", 20, 300, 2300);
  TH1D* totalCS_mu_MHT_LL_ = new TH1D("totalCS_mu_MHT_LL","totalCS_mu_MHT_LL", 16, 300, 1100);
  TH1D* totalCS_mu_NJets_LL_ = new TH1D("totalCS_mu_NJets_LL","totalCS_mu_NJets_LL", 8, 2.5, 10.5);
  TH1D* totalCS_mu_BTags_LL_ = new TH1D("totalCS_mu_BTags_LL","totalCS_mu_BTags_LL", 6, -0.5, 5.5);
  TH1D* totalCS_mu_pT_LL_ = new TH1D("totalCS_mu_pT_LL","totalCS_mu_pT_LL", 12, 0, 300);

  TH1D* totalCS_elec_HT_LL_ = new TH1D("totalCS_elec_HT_LL","totalCS_elec_HT_LL", 20, 300, 2300);
  TH1D* totalCS_elec_MHT_LL_ = new TH1D("totalCS_elec_MHT_LL","totalCS_elec_MHT_LL", 16, 300, 1100);
  TH1D* totalCS_elec_NJets_LL_ = new TH1D("totalCS_elec_NJets_LL","totalCS_elec_NJets_LL", 8, 2.5, 10.5);
  TH1D* totalCS_elec_BTags_LL_ = new TH1D("totalCS_elec_BTags_LL","totalCS_elec_BTags_LL", 6, -0.5, 5.5);
  TH1D* totalCS_elec_pT_LL_ = new TH1D("totalCS_elec_pT_LL","totalCS_elec_pT_LL", 12, 0, 300);

  TProfile* avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* EXTRAP_weight_SF_LL_ = new TH1D("EXTRAP_weight_SF_LL","EXTRAP_weight_SF_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);


  // Define histrograms to do totalPrediction per SearchBin (MC)
  TH1D* totalPred_LL_MC_ = new TH1D("totalPred_LL_MC","totalPred_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredwoIso_LL_MC_ = new TH1D("totalPredwoIso_LL_MC","totalPredwoIso_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPred_EXTRAP_LL_MC_ = new TH1D("totalPred_EXTRAP_LL_MC","totalPred_EXTRAP_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPred_HT_LL_MC_ = new TH1D("totalPred_HT_LL_MC","totalPred_HT_LL_MC", 18, 250., 2500.);
  TH1D* totalPred_MHT_LL_MC_ = new TH1D("totalPred_MHT_LL_MC","totalPred_MHT_LL_MC", 12, 250., 850.);
  TH1D* totalPred_NJets_LL_MC_ = new TH1D("totalPred_NJets_LL_MC","totalPred_NJets_LL_MC", 9, 1.5, 10.5);
  TH1D* totalPred_BTags_LL_MC_ = new TH1D("totalPred_BTags_LL_MC","totalPred_BTags_LL_MC", 7, -0.5, 6.5);

  TH1D* totalPred_PTW_LL_MC_ = new TH1D("totalPred_PTW_LL_MC","totalPred_PTW_LL_MC", 38, 0, 950);
  TH1D* totalPred_PTW_LL_0b_MC_ = new TH1D("totalPred_PTW_LL_0b_MC","totalPred_PTW_LL_0b_MC", 38, 0, 950);
  TH1D* totalPred_PTW_LL_1b_MC_ = new TH1D("totalPred_PTW_LL_1b_MC","totalPred_PTW_LL_1b_MC", 38, 0, 950);
  TH1D* totalPred_PTW_LL_2b_MC_ = new TH1D("totalPred_PTW_LL_2b_MC","totalPred_PTW_LL_2b_MC", 38, 0, 950);
  TH1D* totalPred_PTL_LL_MC_ = new TH1D("totalPred_PTL_LL_MC","totalPred_PTL_LL_MC", 51, 0., 510.);
  TH1D* totalPred_ETAL_LL_MC_ = new TH1D("totalPred_ETAL_LL_MC","totalPred_ETAL_LL_MC;#eta^{e/#mu} [GeV]", 60, -3., 3.);

  
  TH1D* totalPredIsoTrackSysUp_LL_MC_ = new TH1D("totalPredIsoTrackSysUp_LL_MC","totalPredIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysDown_LL_MC_ = new TH1D("totalPredIsoTrackSysDown_LL_MC","totalPredIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysUp_LL_MC_ = new TH1D("totalPredMuIsoTrackSysUp_LL_MC","totalPredMuIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysDown_LL_MC_ = new TH1D("totalPredMuIsoTrackSysDown_LL_MC","totalPredMuIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysUp_LL_MC_ = new TH1D("totalPredElecIsoTrackSysUp_LL_MC","totalPredElecIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysDown_LL_MC_ = new TH1D("totalPredElecIsoTrackSysDown_LL_MC","totalPredElecIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysUp_LL_MC_ = new TH1D("totalPredPionIsoTrackSysUp_LL_MC","totalPredPionIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysDown_LL_MC_ = new TH1D("totalPredPionIsoTrackSysDown_LL_MC","totalPredPionIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysUp_LL_MC_ = new TH1D("totalPredMTWSysUp_LL_MC","totalPredMTWSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysDown_LL_MC_ = new TH1D("totalPredMTWSysDown_LL_MC","totalPredMTWSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysUp_LL_MC_ = new TH1D("totalPredPuritySysUp_LL_MC","totalPredPuritySysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysDown_LL_MC_ = new TH1D("totalPredPuritySysDown_LL_MC","totalPredPuritySysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysUp_LL_MC_ = new TH1D("totalPredSingleLepPuritySysUp_LL_MC","totalPredSingleLepPuritySysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysDown_LL_MC_ = new TH1D("totalPredSingleLepPuritySysDown_LL_MC","totalPredSingleLepPuritySysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysUp_LL_MC_ = new TH1D("totalPredDiLepFoundSysUp_LL_MC","totalPredDiLepFoundSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysDown_LL_MC_ = new TH1D("totalPredDiLepFoundSysDown_LL_MC","totalPredDiLepFoundSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysUp_LL_MC_ = new TH1D("totalPredMuIsoSysUp_LL_MC","totalPredMuIsoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysDown_LL_MC_ = new TH1D("totalPredMuIsoSysDown_LL_MC","totalPredMuIsoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysUp_LL_MC_ = new TH1D("totalPredMuRecoSysUp_LL_MC","totalPredMuRecoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysDown_LL_MC_ = new TH1D("totalPredMuRecoSysDown_LL_MC","totalPredMuRecoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysUp_LL_MC_ = new TH1D("totalPredMuAccSysUp_LL_MC","totalPredMuAccSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysDown_LL_MC_ = new TH1D("totalPredMuAccSysDown_LL_MC","totalPredMuAccSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysUp_LL_MC_ = new TH1D("totalPredMuAccQsquareSysUp_LL_MC","totalPredMuAccQsquareSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysDown_LL_MC_ = new TH1D("totalPredMuAccQsquareSysDown_LL_MC","totalPredMuAccQsquareSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysUp_LL_MC_ = new TH1D("totalPredElecIsoSysUp_LL_MC","totalPredElecIsoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysDown_LL_MC_ = new TH1D("totalPredElecIsoSysDown_LL_MC","totalPredElecIsoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysUp_LL_MC_ = new TH1D("totalPredElecRecoSysUp_LL_MC","totalPredElecRecoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysDown_LL_MC_ = new TH1D("totalPredElecRecoSysDown_LL_MC","totalPredElecRecoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysUp_LL_MC_ = new TH1D("totalPredElecAccSysUp_LL_MC","totalPredElecAccSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysDown_LL_MC_ = new TH1D("totalPredElecAccSysDown_LL_MC","totalPredElecAccSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysUp_LL_MC_ = new TH1D("totalPredElecAccQsquareSysUp_LL_MC","totalPredElecAccQsquareSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysDown_LL_MC_ = new TH1D("totalPredElecAccQsquareSysDown_LL_MC","totalPredElecAccQsquareSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureUp_LL_MC_ = new TH1D("totalPredNonClosureUp_LL_MC","totalPredNonClosureUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureDown_LL_MC_ = new TH1D("totalPredNonClosureDown_LL_MC","totalPredNonClosureDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredIsoTrackStatUp_LL_MC_ = new TH1D("totalPredIsoTrackStatUp_LL_MC","totalPredIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackStatDown_LL_MC_ = new TH1D("totalPredIsoTrackStatDown_LL_MC","totalPredIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatUp_LL_MC_ = new TH1D("totalPredMuIsoTrackStatUp_LL_MC","totalPredMuIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatDown_LL_MC_ = new TH1D("totalPredMuIsoTrackStatDown_LL_MC","totalPredMuIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatUp_LL_MC_ = new TH1D("totalPredElecIsoTrackStatUp_LL_MC","totalPredElecIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatDown_LL_MC_ = new TH1D("totalPredElecIsoTrackStatDown_LL_MC","totalPredElecIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatUp_LL_MC_ = new TH1D("totalPredPionIsoTrackStatUp_LL_MC","totalPredPionIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatDown_LL_MC_ = new TH1D("totalPredPionIsoTrackStatDown_LL_MC","totalPredPionIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatUp_LL_MC_ = new TH1D("totalPredMTWStatUp_LL_MC","totalPredMTWStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatDown_LL_MC_ = new TH1D("totalPredMTWStatDown_LL_MC","totalPredMTWStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatUp_LL_MC_ = new TH1D("totalPredPurityStatUp_LL_MC","totalPredPurityStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatDown_LL_MC_ = new TH1D("totalPredPurityStatDown_LL_MC","totalPredPurityStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatUp_LL_MC_ = new TH1D("totalPredSingleLepPurityStatUp_LL_MC","totalPredSingleLepPurityStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatDown_LL_MC_ = new TH1D("totalPredSingleLepPurityStatDown_LL_MC","totalPredSingleLepPurityStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatUp_LL_MC_ = new TH1D("totalPredDiLepFoundStatUp_LL_MC","totalPredDiLepFoundStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatDown_LL_MC_ = new TH1D("totalPredDiLepFoundStatDown_LL_MC","totalPredDiLepFoundStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatUp_LL_MC_ = new TH1D("totalPredMuIsoStatUp_LL_MC","totalPredMuIsoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatDown_LL_MC_ = new TH1D("totalPredMuIsoStatDown_LL_MC","totalPredMuIsoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatUp_LL_MC_ = new TH1D("totalPredMuRecoStatUp_LL_MC","totalPredMuRecoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatDown_LL_MC_ = new TH1D("totalPredMuRecoStatDown_LL_MC","totalPredMuRecoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatUp_LL_MC_ = new TH1D("totalPredMuAccStatUp_LL_MC","totalPredMuAccStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatDown_LL_MC_ = new TH1D("totalPredMuAccStatDown_LL_MC","totalPredMuAccStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatUp_LL_MC_ = new TH1D("totalPredElecIsoStatUp_LL_MC","totalPredElecIsoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatDown_LL_MC_ = new TH1D("totalPredElecIsoStatDown_LL_MC","totalPredElecIsoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatUp_LL_MC_ = new TH1D("totalPredElecRecoStatUp_LL_MC","totalPredElecRecoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatDown_LL_MC_ = new TH1D("totalPredElecRecoStatDown_LL_MC","totalPredElecRecoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatUp_LL_MC_ = new TH1D("totalPredElecAccStatUp_LL_MC","totalPredElecAccStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatDown_LL_MC_ = new TH1D("totalPredElecAccStatDown_LL_MC","totalPredElecAccStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPropSysUp_LL_MC_ = new TH1D("totalPropSysUp_LL_MC","totalPropSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPropSysDown_LL_MC_ = new TH1D("totalPropSysDown_LL_MC","totalPropSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_LL_MC_ = new TH1D("totalCS_LL_MC","totalCS_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsCS_LL_MC_ = new TH1D("nEvtsCS_LL_MC","nEvtsCS_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_mu_HT_LL_MC_ = new TH1D("totalCS_mu_HT_LL_MC","totalCS_mu_HT_LL_MC", 20, 300, 2300);
  TH1D* totalCS_mu_MHT_LL_MC_ = new TH1D("totalCS_mu_MHT_LL_MC","totalCS_mu_MHT_LL_MC", 16, 300, 1100);
  TH1D* totalCS_mu_NJets_LL_MC_ = new TH1D("totalCS_mu_NJets_LL_MC","totalCS_mu_NJets_LL_MC", 8, 2.5, 10.5);
  TH1D* totalCS_mu_BTags_LL_MC_ = new TH1D("totalCS_mu_BTags_LL_MC","totalCS_mu_BTags_LL_MC", 6, -0.5, 5.5);
  TH1D* totalCS_mu_pT_LL_MC_ = new TH1D("totalCS_mu_pT_LL_MC","totalCS_mu_pT_LL_MC", 12, 0, 300);

  TH1D* totalCS_elec_HT_LL_MC_ = new TH1D("totalCS_elec_HT_LL_MC","totalCS_elec_HT_LL_MC", 20, 300, 2300);
  TH1D* totalCS_elec_MHT_LL_MC_ = new TH1D("totalCS_elec_MHT_LL_MC","totalCS_elec_MHT_LL_MC", 16, 300, 1100);
  TH1D* totalCS_elec_NJets_LL_MC_ = new TH1D("totalCS_elec_NJets_LL_MC","totalCS_elec_NJets_LL_MC", 8, 2.5, 10.5);
  TH1D* totalCS_elec_BTags_LL_MC_ = new TH1D("totalCS_elec_BTags_LL_MC","totalCS_elec_BTags_LL_MC", 6, -0.5, 5.5);
  TH1D* totalCS_elec_pT_LL_MC_ = new TH1D("totalCS_elec_pT_LL_MC","totalCS_elec_pT_LL_MC", 12, 0, 300);


  TProfile* avgWeight_LL_MC_ = new TProfile("avgWeight_LL_MC","avgWeight_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* EXTRAP_weight_SF_LL_MC_ = new TH1D("EXTRAP_weight_SF_LL_MC","EXTRAP_weight_SF_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TProfile* avgWeight_HT_LL_MC_ = new TProfile("avgWeight_HT_LL_MC","avgWeight_HT_LL_MC", 18, 250., 2500.);
  TProfile* avgWeight_MHT_LL_MC_ = new TProfile("avgWeight_MHT_LL_MC","avgWeight_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_NJets_LL_MC_ = new TProfile("avgWeight_NJets_LL_MC","avgWeight_NJets_LL_MC", 9, 1.5, 10.5);
  TProfile* avgWeight_BTags_LL_MC_ = new TProfile("avgWeight_BTags_LL_MC","avgWeight_BTags_LL_MC", 7, -0.5, 6.5);
  TProfile* avgWeight_MHT_HT500_800_LL_MC_ = new TProfile("avgWeight_HT500_800_MHT_LL_MC","avgWeight_HT500_800_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT800_1200_LL_MC_ = new TProfile("avgWeight_HT800_1200_MHT_LL_MC","avgWeight_HT800_1200_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT1200_Inf_LL_MC_ = new TProfile("avgWeight_HT1200_Inf_MHT_LL_MC","avgWeight_HT1200_Inf_MHT_LL_MC", 12, 250., 850.);

  TProfile* avgWeight_MHT_HT300_500_NJets34_LL_MC_ = new TProfile("avgWeight_HT300_500_NJets34_MHT_LL_MC","avgWeight_HT300_500_NJets34_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT500_800_NJets34_LL_MC_ = new TProfile("avgWeight_HT500_800_NJets34_MHT_LL_MC","avgWeight_HT500_800_NJets34_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT800_1200_NJets34_LL_MC_ = new TProfile("avgWeight_HT800_1200_NJets34_MHT_LL_MC","avgWeight_HT800_1200_NJets34_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT1200_Inf_NJets34_LL_MC_ = new TProfile("avgWeight_HT1200_Inf_NJets34_MHT_LL_MC","avgWeight_HT1200_Inf_NJets34_MHT_LL_MC", 12, 250., 850.);
 
  TProfile* avgWeight_MHT_HT300_500_NJets56_LL_MC_ = new TProfile("avgWeight_HT300_500_NJets56_MHT_LL_MC","avgWeight_HT300_500_NJets56_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT500_800_NJets56_LL_MC_ = new TProfile("avgWeight_HT500_800_NJets56_MHT_LL_MC","avgWeight_HT500_800_NJets56_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT800_1200_NJets56_LL_MC_ = new TProfile("avgWeight_HT800_1200_NJets56_MHT_LL_MC","avgWeight_HT800_1200_NJets56_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT1200_Inf_NJets56_LL_MC_ = new TProfile("avgWeight_HT1200_Inf_NJets56_MHT_LL_MC","avgWeight_HT1200_Inf_NJets56_MHT_LL_MC", 12, 250., 850.);

  TProfile* avgWeight_MHT_HT300_500_NJets7Inf_LL_MC_ = new TProfile("avgWeight_HT300_500_NJets7Inf_MHT_LL_MC","avgWeight_HT300_500_NJets7Inf_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT500_800_NJets7Inf_LL_MC_ = new TProfile("avgWeight_HT500_800_NJets7Inf_MHT_LL_MC","avgWeight_HT500_800_NJets7Inf_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT800_1200_NJets7Inf_LL_MC_ = new TProfile("avgWeight_HT800_1200_NJets7Inf_MHT_LL_MC","avgWeight_HT800_1200_NJets7Inf_MHT_LL_MC", 12, 250., 850.);
  TProfile* avgWeight_MHT_HT1200_Inf_NJets7Inf_LL_MC_ = new TProfile("avgWeight_HT1200_Inf_NJets7Inf_MHT_LL_MC","avgWeight_HT1200_Inf_NJets7Inf_MHT_LL_MC", 12, 250., 850.);
 

  // Histograms for Readiness Talk
  TH1D* hPredAllBins = new TH1D("hPredAllBins", ";Bin;Events / Bin", nSearchBinsTotal, 0.5, double(nSearchBinsTotal)+0.5);
  TH1D* hExpAllBins = new TH1D("hExpAllBins", ";Bin;Events / Bin", nSearchBinsTotal, 0.5, double(nSearchBinsTotal)+0.5);
  TProfile* hAvgWeightAllBins = new TProfile("hAvgWeightAllBins", ";Bin;avgWeight / Bin", nSearchBinsTotal, 0.5, double(nSearchBinsTotal)+0.5);

  TH1D* hPredHTMHT0b = new TH1D("hPredHTMHT0b", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hPredHTMHTwb = new TH1D("hPredHTMHTwb", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hExpHTMHT0b = new TH1D("hExpHTMHT0b", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hExpHTMHTwb = new TH1D("hExpHTMHTwb", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TProfile* hAvgWeightHTMHT0b = new TProfile("hAvgWeightHTMHT0b", ";HTMHT Box;avgWeight / Bin", 6, 0.5, 6.5);
  TProfile* hAvgWeightHTMHTwb = new TProfile("hAvgWeightHTMHTwb", ";HTMHT Box;avgWeight / Bin", 6, 0.5, 6.5);

  Double_t njetbins[4] = {3.5, 6.5, 8.5, 11.5};
  TH1D* hPredNJetBins = new TH1D("hPredNJetBins", ";N_{jets} (p_{T} > 30 GeV);Events / Bin", 3, njetbins);
  TH1D* hExpNJetBins = new TH1D("hExpNJetBins", ";N_{jets} (p_{T} > 30 GeV);Events / Bin", 3, njetbins);
  TProfile* hAvgWeightNJetBins = new TProfile("hAvgWeightNJetBins", ";N_{jets} (p_{T} > 30 GeV);avgWeight / Bin", 3, njetbins);

  TH1D* hPredNbBins = new TH1D("hPredNbBins", ";N_{b-jets} (p_{T} > 30 GeV);Events / Bin", 4, -0.5, 3.5);
  TH1D* hExpNbBins = new TH1D("hExpNbBins", ";N_{b-jets} (p_{T} > 30 GeV);Events / Bin", 4, -0.5, 3.5);
  TProfile* hAvgWeightNbBins = new TProfile("hAvgWeightNbBins", ";N_{b-jets} (p_{T} > 30 GeV);avgWeight / Bin", 4, -0.5, 3.5);

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
  LostLeptonExpectation->SetBranchStatus("MHT",1);
  LostLeptonExpectation->SetBranchStatus("MHTPhi",1);
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
  LostLeptonExpectation->SetBranchStatus("isoTracksNum",1);
  LostLeptonExpectation->SetBranchStatus("ExpectationDiLep",1);
  LostLeptonExpectation->SetBranchStatus("GenMuons",1);
  LostLeptonExpectation->SetBranchStatus("bTagProb",1);

  LostLeptonExpectation->SetBranchAddress("HT",&HT);
  LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
  LostLeptonExpectation->SetBranchAddress("MHTPhi",&MHTPhi);
  LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
  LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
  LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
  LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
  LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);

  LostLeptonExpectation->SetBranchStatus("GenMuons",1);
  LostLeptonExpectation->SetBranchAddress("GenMuons",&GenMuons, &b_GenMuons);
  LostLeptonExpectation->SetBranchStatus("GenElectrons",1);
  LostLeptonExpectation->SetBranchAddress("GenElectrons",&GenElectrons, &b_GenElectrons);
  
  LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
  LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);

  LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
  LostLeptonExpectation->SetBranchAddress("muReco",&muReco);
  LostLeptonExpectation->SetBranchAddress("muIso",&muIso);
  
  LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
  LostLeptonExpectation->SetBranchAddress("elecReco",&elecReco);
  LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);
  
  LostLeptonExpectation->SetBranchAddress("isoTracksNum",&isoTracksNum);
  LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);

  LostLeptonExpectation->SetBranchAddress("bTagProb",&bTagProb);
  

  std::cout<<"Loop on Expectation"<<std::endl;
  Long64_t nentries = LostLeptonExpectation->GetEntries();  

  Long64_t nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonExpectation->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
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
          if(NJets > 2){
            scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
          }else{
            if(i < 2){
              scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
            }else{
              scaledWeight = Weight * scaleFactorWeight * (bTagProb->at(i)+bTagProb->at(i+1));
            }
          }
        }else{
          scaledWeight = Weight * scaleFactorWeight;
        }

        if(Expectation==1)
          {
          totalExpectation_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExp+=scaledWeight;
          totalExpError+= scaledWeight*scaledWeight;
          totalExpwoIso_LL_->Fill(Bin_bTags.at(i), scaledWeight);

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
          totalExpectationIsoTrackReduction_->Fill(Bin_bTags.at(i), scaledWeight);
          totalExpIsoTrack+=scaledWeight;
          totalExpIsoTrackError+= scaledWeight*scaledWeight;
          totalExp_LL_->Fill(Bin_bTags.at(i), scaledWeight);

          totalExp_HT_LL_->Fill(HT, scaledWeight);
          totalExp_MHT_LL_->Fill(MHT, scaledWeight);
          totalExp_NJets_LL_->Fill(NJets, scaledWeight);
          totalExp_BTags_LL_->Fill(i, scaledWeight);


          nEvtsExp_LL_->Fill(Bin_bTags.at(i));

          hExpAllBins->Fill(Bin_bTags.at(i), scaledWeight);
          if(i==0) hExpHTMHT0b->Fill(getHTMHTBox(HT, MHT), scaledWeight);
          else hExpHTMHTwb->Fill(getHTMHTBox(HT, MHT), scaledWeight);
          hExpNJetBins->Fill(NJets, scaledWeight);
          hExpNbBins->Fill(i, scaledWeight);
      }
    }

  if(Expectation==1 && ExpectationReductionIsoTrack==0){
  // stuff to compare to extrapolated predictions
  int INJ(-1);
  if (NJets>=4&&NJets<=6) INJ=0;
  else if (NJets>=7&&NJets<=8) INJ=1;
  else if (NJets>=9) INJ=2;
  int INB(BTags);
  if (INB>3) INB=3;
  int IHT(-1);
  if (HT>500&&HT<800) IHT=0;
  else if (HT>800&&HT<1200) IHT=1;
  else if (HT>1200) IHT=2;
  if (HT<800&&MHT>750) IHT=-1;
        if (INJ>=0&&INB>=0&&IHT>=0) {
    if (HT>500&&HT<1200) {
      totalExp_MHT_Normal_HT12_LL_[INJ*4+INB]->Fill(MHT, scaledWeight);
    }
    if (HT>1200) {
      totalExp_MHT_Normal_HT3_LL_[INJ*4+INB]->Fill(MHT, scaledWeight);
    }
    if (HT>800) {
      totalExp_MHT_Normal_HT23_LL_[INJ*4+INB]->Fill(MHT, scaledWeight);
    }
  }
  // debug PTW modeling
  // to get lost-lepton ptw, need the gen lepton...
  double PXL(0.), PYL(0.), ETAL(0.); // always pick lead lepton pt...
  unsigned int GenMuNum=GenMuons->size(), GenElecNum=GenElectrons->size();
  if (GenMuNum>=1&&GenElecNum==0) {PXL=GenMuons->at(0).Px(); PYL=GenMuons->at(0).Py(); ETAL=GenMuons->at(0).Eta();}
  else if (GenMuNum==0&&GenElecNum>=1) {PXL=GenElectrons->at(0).Px(); PYL=GenElectrons->at(0).Py(); ETAL=GenElectrons->at(0).Eta();}
  else if (GenMuNum>=1&&GenElecNum>=1) {
    PXL = (GenMuons->at(0).Pt()>GenElectrons->at(0).Pt()) ? GenMuons->at(0).Px() : GenElectrons->at(0).Px();
    PYL = (GenMuons->at(0).Pt()>GenElectrons->at(0).Pt()) ? GenMuons->at(0).Py() : GenElectrons->at(0).Py();
    ETAL = (GenMuons->at(0).Pt()>GenElectrons->at(0).Pt()) ? GenMuons->at(0).Eta() : GenElectrons->at(0).Eta();
  }
  totalExp_PTL_LL_->Fill(sqrt(PXL*PXL+PYL*PYL), scaledWeight);
  totalExp_ETAL_LL_->Fill(ETAL, scaledWeight);
  
  double PXW(MHT*cos(MHTPhi)+PXL), PYW(MHT*sin(MHTPhi)+PYL);
  double PTW = sqrt(PXW*PXW+PYW*PYW);
  totalExp_PTW_LL_->Fill(PTW, scaledWeight);
  if (BTags==0) totalExp_PTW_LL_0b_->Fill(PTW, scaledWeight);
  else if (BTags==1) totalExp_PTW_LL_1b_->Fill(PTW, scaledWeight);
  else if (BTags>=2) totalExp_PTW_LL_2b_->Fill(PTW, scaledWeight);
    }
 
  }
  
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
  LostLeptonPrediction->SetBranchStatus("MHT",1);
  LostLeptonPrediction->SetBranchStatus("NJets",1);
  LostLeptonPrediction->SetBranchStatus("BTags",1);
  LostLeptonPrediction->SetBranchStatus("Weight",1);
  LostLeptonPrediction->SetBranchStatus("Bin",1);
  LostLeptonPrediction->SetBranchStatus("BinQCD",1);
  LostLeptonPrediction->SetBranchStatus("MTW",1);
  LostLeptonPrediction->SetBranchStatus("MuonsNum",1);
  LostLeptonPrediction->SetBranchStatus("Muons",1);
  LostLeptonPrediction->SetBranchStatus("ElectronsNum",1);
  LostLeptonPrediction->SetBranchStatus("Electrons",1);
  LostLeptonPrediction->SetBranchStatus("MuonsPTW",1);
  LostLeptonPrediction->SetBranchStatus("ElectronsPTW",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_noIsoTrack",1);
  LostLeptonPrediction->SetBranchStatus("muTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchStatus("elecTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchStatus("muIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("bTagProb",1);

  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MTW",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuAcc",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuReco",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_MuIso",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecAcc",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecReco",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_ElecIso",1);

  LostLeptonPrediction->SetBranchStatus("isoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("isoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("MTWSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("MTWSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("puritySysUp", 1);
  LostLeptonPrediction->SetBranchStatus("puritySysDown", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPuritySysUp", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPuritySysDown", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccQsquareSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccQsquareSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccQsquareSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccQsquareSysDown", 1);

  LostLeptonPrediction->SetBranchStatus("isoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("isoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("MTWStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("MTWStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("purityStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("purityStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPurityStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPurityStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccStatDown", 1);
  
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
  LostLeptonPrediction->SetBranchAddress("BinQCD",&BinQCD);
  LostLeptonPrediction->SetBranchAddress("bTagProb",&bTagProb);

  LostLeptonPrediction->SetBranchAddress("MTW",&MTW);
  LostLeptonPrediction->SetBranchAddress("MuonsNum",&MuonsNum);
  LostLeptonPrediction->SetBranchAddress("Muons",&Muons,&b_Muons);
  LostLeptonPrediction->SetBranchAddress("MuonsPTW",&MuonsPTW, &b_MuonsPTW);
  LostLeptonPrediction->SetBranchAddress("ElectronsNum",&ElectronsNum);
  LostLeptonPrediction->SetBranchAddress("Electrons",&Electrons,&b_Electrons);
  LostLeptonPrediction->SetBranchAddress("ElectronsPTW",&ElectronsPTW, &b_ElectronsPTW);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags",&totalWeight_BTags);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack);
  LostLeptonPrediction->SetBranchAddress("muTotalWeightDiLepIsoTrackReduced",&muTotalWeightDiLepIsoTrackReduced);
  LostLeptonPrediction->SetBranchAddress("elecTotalWeightDiLepIsoTrackReduced",&elecTotalWeightDiLepIsoTrackReduced);

  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MTW",&totalWeight_BTags_MTW);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuAcc",&totalWeight_BTags_MuAcc);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuReco",&totalWeight_BTags_MuReco);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_MuIso",&totalWeight_BTags_MuIso);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecAcc",&totalWeight_BTags_ElecAcc);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecReco",&totalWeight_BTags_ElecReco);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_ElecIso",&totalWeight_BTags_ElecIso);
  
  LostLeptonPrediction->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPrediction->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPrediction->SetBranchAddress("muAccWeight",&muAccWeight);
  
  LostLeptonPrediction->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPrediction->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPrediction->SetBranchAddress("elecIsoWeight",&elecIsoWeight);

  LostLeptonPrediction->SetBranchAddress("isoTrackSysUp", &isoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("isoTrackSysDown", &isoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackSysUp", &muIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackSysDown", &muIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("MTWSysUp", &MTWSysUp);
  LostLeptonPrediction->SetBranchAddress("MTWSysDown", &MTWSysDown);
  LostLeptonPrediction->SetBranchAddress("puritySysUp", &puritySysUp);
  LostLeptonPrediction->SetBranchAddress("puritySysDown", &puritySysDown);
  LostLeptonPrediction->SetBranchAddress("singleLepPuritySysUp", &singleLepPuritySysUp);
  LostLeptonPrediction->SetBranchAddress("singleLepPuritySysDown", &singleLepPuritySysDown);
  LostLeptonPrediction->SetBranchAddress("diLepFoundSysUp", &diLepFoundSysUp);
  LostLeptonPrediction->SetBranchAddress("diLepFoundSysDown", &diLepFoundSysDown);
  LostLeptonPrediction->SetBranchAddress("muIsoSysUp", &muIsoSysUp);
  LostLeptonPrediction->SetBranchAddress("muIsoSysDown", &muIsoSysDown);
  LostLeptonPrediction->SetBranchAddress("muRecoSysUp", &muRecoSysUp);
  LostLeptonPrediction->SetBranchAddress("muRecoSysDown", &muRecoSysDown);
  LostLeptonPrediction->SetBranchAddress("muAccSysUp", &muAccSysUp);
  LostLeptonPrediction->SetBranchAddress("muAccSysDown", &muAccSysDown);
  LostLeptonPrediction->SetBranchAddress("muAccQsquareSysUp", &muAccQsquareSysUp);
  LostLeptonPrediction->SetBranchAddress("muAccQsquareSysDown", &muAccQsquareSysDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoSysUp", &elecIsoSysUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoSysDown", &elecIsoSysDown);
  LostLeptonPrediction->SetBranchAddress("elecRecoSysUp", &elecRecoSysUp);
  LostLeptonPrediction->SetBranchAddress("elecRecoSysDown", &elecRecoSysDown);
  LostLeptonPrediction->SetBranchAddress("elecAccSysUp", &elecAccSysUp);
  LostLeptonPrediction->SetBranchAddress("elecAccSysDown", &elecAccSysDown);
  LostLeptonPrediction->SetBranchAddress("elecAccQsquareSysUp", &elecAccQsquareSysUp);
  LostLeptonPrediction->SetBranchAddress("elecAccQsquareSysDown", &elecAccQsquareSysDown);

  LostLeptonPrediction->SetBranchAddress("isoTrackStatUp", &isoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("isoTrackStatDown", &isoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackStatUp", &muIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackStatDown", &muIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("MTWStatUp", &MTWStatUp);
  LostLeptonPrediction->SetBranchAddress("MTWStatDown", &MTWStatDown);
  LostLeptonPrediction->SetBranchAddress("purityStatUp", &purityStatUp);
  LostLeptonPrediction->SetBranchAddress("purityStatDown", &purityStatDown);
  LostLeptonPrediction->SetBranchAddress("singleLepPurityStatUp", &singleLepPurityStatUp);
  LostLeptonPrediction->SetBranchAddress("singleLepPurityStatDown", &singleLepPurityStatDown);
  LostLeptonPrediction->SetBranchAddress("diLepFoundStatUp", &diLepFoundStatUp);
  LostLeptonPrediction->SetBranchAddress("diLepFoundStatDown", &diLepFoundStatDown);
  LostLeptonPrediction->SetBranchAddress("muIsoStatUp", &muIsoStatUp);
  LostLeptonPrediction->SetBranchAddress("muIsoStatDown", &muIsoStatDown);
  LostLeptonPrediction->SetBranchAddress("muRecoStatUp", &muRecoStatUp);
  LostLeptonPrediction->SetBranchAddress("muRecoStatDown", &muRecoStatDown);
  LostLeptonPrediction->SetBranchAddress("muAccStatUp", &muAccStatUp);
  LostLeptonPrediction->SetBranchAddress("muAccStatDown", &muAccStatDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoStatUp", &elecIsoStatUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoStatDown", &elecIsoStatDown);
  LostLeptonPrediction->SetBranchAddress("elecRecoStatUp", &elecRecoStatUp);
  LostLeptonPrediction->SetBranchAddress("elecRecoStatDown", &elecRecoStatDown);
  LostLeptonPrediction->SetBranchAddress("elecAccStatUp", &elecAccStatUp);
  LostLeptonPrediction->SetBranchAddress("elecAccStatDown", &elecAccStatDown);


  std::cout<<"Loop on Prediction (MC)"<<std::endl;
  
  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
    }
    else SearchBin = Bin;

    if(SearchBin > 900) continue;
    if(MTW>100)continue;
    if(MuonsNum+ElectronsNum!=1)continue;


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

        //totalPred_LL_MC_->Fill( Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
        totalPred_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        //totalPredwoIso_LL_MC_->Fill( Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
        totalPredwoIso_LL_MC_->Fill( Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2);
        //    totalPred_LL_NoTk_MC_->Fill( Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
        totalPred_HT_LL_MC_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        totalPred_MHT_LL_MC_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        totalPred_NJets_LL_MC_->Fill(NJets, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
        totalPred_BTags_LL_MC_->Fill(i, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);

          if(MuonsNum == 1){
            totalPredictionMuCSMuAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccNJets_->Fill(NJets, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoNJets_->Fill(NJets, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoNJets_->Fill(NJets, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccBTag_->Fill(i, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoBTag_->Fill(i, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoBTag_->Fill(i, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccHT_->Fill(HT, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoHT_->Fill(HT, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoHT_->Fill(HT, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuAccMHT_->Fill(MHT, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuRecoMHT_->Fill(MHT, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSMuIsoMHT_->Fill(MHT, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPreMuAcc+=totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuMuAcc+=totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb;
            totalPreMuMuReco+=totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb;
            totalPreMuMuIso+=totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb;
                
            totalPredictionMuCSElecAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccNJets_->Fill(NJets, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoNJets_->Fill(NJets, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoNJets_->Fill(NJets, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccBTag_->Fill(i, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoBTag_->Fill(i, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoBTag_->Fill(i, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccHT_->Fill(HT, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoHT_->Fill(HT, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoHT_->Fill(HT, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecAccMHT_->Fill(MHT, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecRecoMHT_->Fill(MHT, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionMuCSElecIsoMHT_->Fill(MHT, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPreElecAcc+=totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuElecAcc+=totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb;
            totalPreMuElecReco+=totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb;
            totalPreMuElecIso+=totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb;

          }if(ElectronsNum == 1){
            totalPredictionElecCSElecAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccNJets_->Fill(NJets, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoNJets_->Fill(NJets, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoNJets_->Fill(NJets, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccBTag_->Fill(i, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoBTag_->Fill(i, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoBTag_->Fill(i, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccHT_->Fill(HT, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoHT_->Fill(HT, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoHT_->Fill(HT, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecAccMHT_->Fill(MHT, totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecRecoMHT_->Fill(MHT, totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSElecIsoMHT_->Fill(MHT, totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb);
            totalPreElecAcc+=totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecReco+=totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecIso+=totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecElecAcc+=totalWeight_BTags_ElecAcc->at(i)*scaleFactorWeightBtagProb;
            totalPreElecElecReco+=totalWeight_BTags_ElecReco->at(i)*scaleFactorWeightBtagProb;
            totalPreElecElecIso+=totalWeight_BTags_ElecIso->at(i)*scaleFactorWeightBtagProb;
                    
            totalPredictionElecCSMuAcc_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuReco_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIso_->Fill(Bin_bTags.at(i), totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccNJets_->Fill(NJets, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoNJets_->Fill(NJets, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoNJets_->Fill(NJets, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccBTag_->Fill(i, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoBTag_->Fill(i, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoBTag_->Fill(i, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccHT_->Fill(HT, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoHT_->Fill(HT, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoHT_->Fill(HT, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuAccMHT_->Fill(MHT, totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuRecoMHT_->Fill(MHT, totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb);
            totalPredictionElecCSMuIsoMHT_->Fill(MHT, totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb);
            totalPreMuAcc+=totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuReco+=totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb/2;
            totalPreMuIso+=totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb/2;
            totalPreElecMuAcc+=totalWeight_BTags_MuAcc->at(i)*scaleFactorWeightBtagProb;
            totalPreElecMuReco+=totalWeight_BTags_MuReco->at(i)*scaleFactorWeightBtagProb;
            totalPreElecMuIso+=totalWeight_BTags_MuIso->at(i)*scaleFactorWeightBtagProb;
          }
    }

    double PTW(0.), PTL(0.), ETAL(0.);
    if (MuonsNum==1) {
      PTW=PTWCalculator(MHT, MHTPhi, Muons->at(0).Pt(), Muons->at(0).Phi());
      PTL=Muons->at(0).Pt();
      ETAL=Muons->at(0).Eta();
    }
    else if (ElectronsNum==1) {
      PTW=PTWCalculator(MHT, MHTPhi, Electrons->at(0).Pt(), Electrons->at(0).Phi());
      PTL=Electrons->at(0).Pt();
      ETAL=Electrons->at(0).Eta();
    }
    totalPred_PTW_LL_MC_->Fill(PTW, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    if (BTags==0) totalPred_PTW_LL_0b_MC_->Fill(PTW, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    else if (BTags==1) totalPred_PTW_LL_1b_MC_->Fill(PTW, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    else if (BTags>=2) totalPred_PTW_LL_2b_MC_->Fill(PTW, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);

    totalPred_PTL_LL_MC_->Fill(PTL, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    totalPred_ETAL_LL_MC_->Fill(ETAL, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);

    // extrapolated predictions

    // first reset the holders
    for (unsigned int inj(0); inj<3; inj++) {
      for (unsigned int inb(0); inb<4; inb++) {
  totalPred_MHT_EXTRAP_HT12_LL_MC_[inj*4+inb]->Reset();
  totalPred_MHT_EXTRAP_HT3_LL_MC_[inj*4+inb]->Reset();
  totalPred_MHT_EXTRAP_HT23_LL_MC_[inj*4+inb]->Reset();
      }
    }
    
    int INJ(-1);
    if (NJets>=4&&NJets<=6) INJ=0;
    else if (NJets>=7&&NJets<=8) INJ=1;
    else if (NJets>=9) INJ=2;
    int INB(BTags);
    if (INB>3) INB=3;
    int INB_EXTRAP=INB;
    if (INB_EXTRAP>2) INB_EXTRAP=2;
    int IHT(-1);
    if (HT>500&&HT<800) IHT=0;
    else if (HT>800&&HT<1200) IHT=1;
    else if (HT>1200) IHT=2;
    if (HT<800&&MHT>750) IHT=-1;

if(doExtrapolation){
    if (INJ>=0&&INB>=0&&IHT>=0) {
      if (HT>500&&HT<1200) {
  totalPred_MHT_Normal_HT12_LL_MC_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
  totalCR_MHT_HT12_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
  totalCR_PTW_HT12_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
      }
      if (HT>1200) {
  totalPred_MHT_Normal_HT3_LL_MC_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
  totalCR_MHT_HT3_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
  totalCR_PTW_HT3_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
      }
      if (HT>800) {
  totalPred_MHT_Normal_HT23_LL_MC_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
  totalCR_MHT_HT23_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
  totalCR_PTW_HT23_LL_MC_[INJ*4+INB]->Fill(PTW, scaleFactorWeight);
      }
      for (int template_bin=0; template_bin<nTemplateBins; template_bin++) { // now loop over bins of MHT/PTW PDFs to do the extrapolation
  if (HT>500&&HT<1200) {
    totalPred_MHT_EXTRAP_HT12_LL_MC_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                   (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2.)*LostLepRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // NOTE: using the combined e/mu weight for now--should look into separating the flavors, commented out below
    // totalPred_MHT_EXTRAP_HT12_LL_MC_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //               (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostMuRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT12_LL_MC_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //               (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostElecRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
  }
  if (HT>1200) {
    totalPred_MHT_EXTRAP_HT3_LL_MC_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                  (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2.)*LostLepRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT3_LL_MC_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //              (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostMuRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT3_LL_MC_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //                (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostElecRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
  }
  if (HT>800) {
    totalPred_MHT_EXTRAP_HT23_LL_MC_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                   (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2.)*LostLepRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT23_LL_MC_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //               (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostMuRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT23_LL_MC_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //               (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight)*LostElecRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
  }
      }
    }
}
    
    totalPredIsoTrackSysUp_LL_MC_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_MC_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredIsoTrackSysUp_LL_MC_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_MC_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredIsoTrackSysUp_LL_MC_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_MC_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);

    totalPredMuIsoTrackSysUp_LL_MC_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredMuIsoTrackSysDown_LL_MC_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredElecIsoTrackSysUp_LL_MC_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredElecIsoTrackSysDown_LL_MC_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredPionIsoTrackSysUp_LL_MC_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredPionIsoTrackSysDown_LL_MC_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);
    totalPredMTWSysUp_LL_MC_->Fill(SearchBin, MTWSysUp*scaleFactorWeight/2);
    totalPredMTWSysDown_LL_MC_->Fill(SearchBin, MTWSysDown*scaleFactorWeight/2);
    totalPredPuritySysUp_LL_MC_->Fill(SearchBin, puritySysUp*scaleFactorWeight/2);
    totalPredPuritySysDown_LL_MC_->Fill(SearchBin, puritySysDown*scaleFactorWeight/2);
    totalPredSingleLepPuritySysUp_LL_MC_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeight/2);
    totalPredSingleLepPuritySysDown_LL_MC_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeight/2);
    totalPredDiLepFoundSysUp_LL_MC_->Fill(SearchBin, diLepFoundSysUp*scaleFactorWeight/2);
    totalPredDiLepFoundSysDown_LL_MC_->Fill(SearchBin, diLepFoundSysDown*scaleFactorWeight/2);
    totalPredMuIsoSysUp_LL_MC_->Fill(SearchBin, muIsoSysUp*scaleFactorWeight/2);
    totalPredMuIsoSysDown_LL_MC_->Fill(SearchBin, muIsoSysDown*scaleFactorWeight/2);
    totalPredMuRecoSysUp_LL_MC_->Fill(SearchBin, muRecoSysUp*scaleFactorWeight/2);
    totalPredMuRecoSysDown_LL_MC_->Fill(SearchBin, muRecoSysDown*scaleFactorWeight/2);
    totalPredMuAccSysUp_LL_MC_->Fill(SearchBin, muAccSysUp*scaleFactorWeight/2);
    totalPredMuAccSysDown_LL_MC_->Fill(SearchBin, muAccSysDown*scaleFactorWeight/2);
    totalPredMuAccQsquareSysUp_LL_MC_->Fill(SearchBin, muAccQsquareSysUp*scaleFactorWeight/2);
    totalPredMuAccQsquareSysDown_LL_MC_->Fill(SearchBin, muAccQsquareSysDown*scaleFactorWeight/2);
    totalPredElecIsoSysUp_LL_MC_->Fill(SearchBin, elecIsoSysUp*scaleFactorWeight/2);
    totalPredElecIsoSysDown_LL_MC_->Fill(SearchBin, elecIsoSysDown*scaleFactorWeight/2);
    totalPredElecRecoSysUp_LL_MC_->Fill(SearchBin, elecRecoSysUp*scaleFactorWeight/2);
    totalPredElecRecoSysDown_LL_MC_->Fill(SearchBin, elecRecoSysDown*scaleFactorWeight/2);
    totalPredElecAccSysUp_LL_MC_->Fill(SearchBin, elecAccSysUp*scaleFactorWeight/2);
    totalPredElecAccSysDown_LL_MC_->Fill(SearchBin, elecAccSysDown*scaleFactorWeight/2);
    totalPredElecAccQsquareSysUp_LL_MC_->Fill(SearchBin, elecAccQsquareSysUp*scaleFactorWeight/2);
    totalPredElecAccQsquareSysDown_LL_MC_->Fill(SearchBin, elecAccQsquareSysDown*scaleFactorWeight/2);

    totalPredIsoTrackStatUp_LL_MC_->Fill(SearchBin, isoTrackStatUp*scaleFactorWeight/2);
    totalPredIsoTrackStatDown_LL_MC_->Fill(SearchBin, isoTrackStatDown*scaleFactorWeight/2);
    /*    totalPredIsoTrackStatUp_LL_MC_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2);
    totalPredIsoTrackStatDown_LL_MC_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2);
    totalPredIsoTrackStatUp_LL_MC_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2);
    totalPredIsoTrackStatDown_LL_MC_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2);
    totalPredIsoTrackStatUp_LL_MC_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2);
    totalPredIsoTrackStatDown_LL_MC_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2);
    */
    totalPredMuIsoTrackStatUp_LL_MC_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2);
    totalPredMuIsoTrackStatDown_LL_MC_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2);
    totalPredElecIsoTrackStatUp_LL_MC_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2);
    totalPredElecIsoTrackStatDown_LL_MC_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2);
    totalPredPionIsoTrackStatUp_LL_MC_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2);
    totalPredPionIsoTrackStatDown_LL_MC_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2);
    totalPredMTWStatUp_LL_MC_->Fill(SearchBin, MTWStatUp*scaleFactorWeight/2);
    totalPredMTWStatDown_LL_MC_->Fill(SearchBin, MTWStatDown*scaleFactorWeight/2);
    totalPredPurityStatUp_LL_MC_->Fill(SearchBin, purityStatUp*scaleFactorWeight/2);
    totalPredPurityStatDown_LL_MC_->Fill(SearchBin, purityStatDown*scaleFactorWeight/2);
    totalPredSingleLepPurityStatUp_LL_MC_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeight/2);
    totalPredSingleLepPurityStatDown_LL_MC_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeight/2);
    totalPredDiLepFoundStatUp_LL_MC_->Fill(SearchBin, diLepFoundStatUp*scaleFactorWeight/2);
    totalPredDiLepFoundStatDown_LL_MC_->Fill(SearchBin, diLepFoundStatDown*scaleFactorWeight/2);
    totalPredMuIsoStatUp_LL_MC_->Fill(SearchBin, muIsoStatUp*scaleFactorWeight/2);
    totalPredMuIsoStatDown_LL_MC_->Fill(SearchBin, muIsoStatDown*scaleFactorWeight/2);
    totalPredMuRecoStatUp_LL_MC_->Fill(SearchBin, muRecoStatUp*scaleFactorWeight/2);
    totalPredMuRecoStatDown_LL_MC_->Fill(SearchBin, muRecoStatDown*scaleFactorWeight/2);
    totalPredMuAccStatUp_LL_MC_->Fill(SearchBin, muAccStatUp*scaleFactorWeight/2);
    totalPredMuAccStatDown_LL_MC_->Fill(SearchBin, muAccStatDown*scaleFactorWeight/2);
    totalPredElecIsoStatUp_LL_MC_->Fill(SearchBin, elecIsoStatUp*scaleFactorWeight/2);
    totalPredElecIsoStatDown_LL_MC_->Fill(SearchBin, elecIsoStatDown*scaleFactorWeight/2);
    totalPredElecRecoStatUp_LL_MC_->Fill(SearchBin, elecRecoStatUp*scaleFactorWeight/2);
    totalPredElecRecoStatDown_LL_MC_->Fill(SearchBin, elecRecoStatDown*scaleFactorWeight/2);
    totalPredElecAccStatUp_LL_MC_->Fill(SearchBin, elecAccStatUp*scaleFactorWeight/2);
    totalPredElecAccStatDown_LL_MC_->Fill(SearchBin, elecAccStatDown*scaleFactorWeight/2);

    //totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    //totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

    //totalPropSysUp_LL_MC_->Fill(SearchBin, totalPropSysUp*scaleFactorWeight/2);
    //totalPropSysDown_LL_MC_->Fill(SearchBin, totalPropSysDown*scaleFactorWeight/2);

    for(int i = 0; i < 4; i++){
      if(doBtagProbabilities){
        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
      }else{
        Bin_bTags.at(i)=SearchBin;
      }
    }

    nLoops = 4;
    if(!doBtagProbabilities){
      nLoops = 1;
    }else if(NJets < 3){
      nLoops = 3;
    }

      //fill event 4 times weighting with the btag probability
      for(int i = 0; i < nLoops; i++){
        if(doBtagProbabilities){
          scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
        }else{
          scaledWeight = Weight * scaleFactorWeight;
        }

        totalCS_LL_MC_->Fill(Bin_bTags.at(i), scaledWeight);
        nEvtsCS_LL_MC_->Fill(Bin_bTags.at(i));

        if(MuonsNum==1){
          totalCS_mu_HT_LL_MC_->Fill(HT, scaledWeight);
          totalCS_mu_MHT_LL_MC_->Fill(MHT, scaledWeight);
          totalCS_mu_NJets_LL_MC_->Fill(NJets, scaledWeight);
          totalCS_mu_BTags_LL_MC_->Fill(i, scaledWeight);
          totalCS_mu_pT_LL_MC_->Fill(Muons->at(0).Pt(), scaledWeight);
        }else if(ElectronsNum==1){
          totalCS_elec_HT_LL_MC_->Fill(HT, scaledWeight);
          totalCS_elec_MHT_LL_MC_->Fill(MHT, scaledWeight);
          totalCS_elec_NJets_LL_MC_->Fill(NJets, scaledWeight);
          totalCS_elec_BTags_LL_MC_->Fill(i, scaledWeight);
          totalCS_elec_pT_LL_MC_->Fill(Electrons->at(0).Pt(), scaledWeight);
        }
      }
    

if(doExtrapolation){
    // fill 72-bin histogram for extrapolation method
    if (SearchBin%6 > 0 && SearchBin%6 < 4) {
      // for low-mht bins, use the regular prediction
      totalPred_EXTRAP_LL_MC_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    } else { // otherwise take new prediction from the histograms we filled earlier
      int iSB = INJ*24+INB*6;
      //  Double_t mht_bins[6] = {200, 400, 500, 600, 750, 10000};
      totalPred_EXTRAP_LL_MC_->Fill(iSB+4, totalPred_MHT_EXTRAP_HT12_LL_MC_[INJ*4+INB]->Integral(3,4));
      totalPred_EXTRAP_LL_MC_->Fill(iSB+5, totalPred_MHT_EXTRAP_HT3_LL_MC_[INJ*4+INB]->Integral(3,4));
      totalPred_EXTRAP_LL_MC_->Fill(iSB+6, totalPred_MHT_EXTRAP_HT23_LL_MC_[INJ*4+INB]->Integral(5,6));
    }
}
    
    avgWeight_LL_MC_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    avgWeight_HT_LL_MC_->Fill(HT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    avgWeight_MHT_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    avgWeight_NJets_LL_MC_->Fill(NJets, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    avgWeight_BTags_LL_MC_->Fill(BTags, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);

    if(NJets < 6.5){
      if(HT<800) avgWeight_MHT_HT500_800_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<1200) avgWeight_MHT_HT800_1200_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else avgWeight_MHT_HT1200_Inf_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    }

    if(NJets < 4.5){
      if(HT<500) avgWeight_MHT_HT300_500_NJets34_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<800) avgWeight_MHT_HT500_800_NJets34_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<1200) avgWeight_MHT_HT800_1200_NJets34_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else avgWeight_MHT_HT1200_Inf_NJets34_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    }else if(NJets < 6.5){
      if(HT<500) avgWeight_MHT_HT300_500_NJets56_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<800) avgWeight_MHT_HT500_800_NJets56_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<1200) avgWeight_MHT_HT800_1200_NJets56_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else avgWeight_MHT_HT1200_Inf_NJets56_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    }else{
      if(HT<500) avgWeight_MHT_HT300_500_NJets7Inf_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<800) avgWeight_MHT_HT500_800_NJets7Inf_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else if(HT<1200) avgWeight_MHT_HT800_1200_NJets7Inf_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
      else avgWeight_MHT_HT1200_Inf_NJets7Inf_LL_MC_->Fill(MHT, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    }
    
    hAvgWeightAllBins->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    if(BTags==0) hAvgWeightHTMHT0b->Fill(getHTMHTBox(HT, MHT), abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    else hAvgWeightHTMHTwb->Fill(getHTMHTBox(HT, MHT), abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    hAvgWeightNJetBins->Fill(NJets, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    hAvgWeightNbBins->Fill(BTags, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));

  }

  std::cout<<"Finished"<<std::endl;

  //Prediction Data Tree
  gROOT->Reset();
  TFile *fPre = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction_Data.c_str());
  if (!fPre) {
    fPre = new TFile(InputPath_Prediction_Data.c_str());
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
  LostLeptonPredictionData->SetBranchStatus("MuonsNum",1);
  LostLeptonPredictionData->SetBranchStatus("Muons",1);
  LostLeptonPredictionData->SetBranchStatus("ElectronsNum",1);
  LostLeptonPredictionData->SetBranchStatus("Electrons",1);
  LostLeptonPredictionData->SetBranchStatus("MuonsPTW",1);
  LostLeptonPredictionData->SetBranchStatus("ElectronsPTW",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPredictionData->SetBranchStatus("muTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPredictionData->SetBranchStatus("elecTotalWeightDiLepIsoTrackReduced",1);
  LostLeptonPredictionData->SetBranchStatus("muIsoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoWeight",1);

  LostLeptonPredictionData->SetBranchStatus("isoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("isoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("puritySysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("puritySysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPuritySysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPuritySysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccQsquareSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccQsquareSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccQsquareSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccQsquareSysDown", 1);

  LostLeptonPredictionData->SetBranchStatus("isoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("isoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("purityStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("purityStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPurityStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPurityStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccStatDown", 1);

  LostLeptonPredictionData->SetBranchAddress("HT",&HT);
  LostLeptonPredictionData->SetBranchAddress("MHT",&MHT);
  LostLeptonPredictionData->SetBranchAddress("NJets",&NJets);
  LostLeptonPredictionData->SetBranchAddress("BTags",&BTags);
  LostLeptonPredictionData->SetBranchAddress("Weight",&Weight);
  LostLeptonPredictionData->SetBranchAddress("Bin",&Bin);
  LostLeptonPredictionData->SetBranchAddress("BinQCD",&BinQCD);
  
  LostLeptonPredictionData->SetBranchAddress("MTW",&MTW);
  LostLeptonPredictionData->SetBranchAddress("MuonsNum",&MuonsNum);
  LostLeptonPredictionData->SetBranchAddress("Muons",&Muons,&b_Muons);
  LostLeptonPredictionData->SetBranchAddress("ElectronsNum",&ElectronsNum);
  LostLeptonPredictionData->SetBranchAddress("Electrons",&Electrons,&b_Electrons);
  LostLeptonPredictionData->SetBranchAddress("MuonsPTW",&MuonsPTW, &b_MuonsPTW);
  LostLeptonPredictionData->SetBranchAddress("ElectronsPTW",&ElectronsPTW, &b_ElectronsPTW);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
  LostLeptonPredictionData->SetBranchAddress("muTotalWeightDiLepIsoTrackReduced",&muTotalWeightDiLepIsoTrackReduced);
  LostLeptonPredictionData->SetBranchAddress("elecTotalWeightDiLepIsoTrackReduced",&elecTotalWeightDiLepIsoTrackReduced);
  
  LostLeptonPredictionData->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPredictionData->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("muAccWeight",&muAccWeight);
  
  LostLeptonPredictionData->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPredictionData->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("elecIsoWeight",&elecIsoWeight);

  LostLeptonPredictionData->SetBranchAddress("isoTrackSysUp", &isoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("isoTrackSysDown", &isoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackSysUp", &muIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackSysDown", &muIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("MTWSysUp", &MTWSysUp);
  LostLeptonPredictionData->SetBranchAddress("MTWSysDown", &MTWSysDown);
  LostLeptonPredictionData->SetBranchAddress("puritySysUp", &puritySysUp);
  LostLeptonPredictionData->SetBranchAddress("puritySysDown", &puritySysDown);
  LostLeptonPredictionData->SetBranchAddress("singleLepPuritySysUp", &singleLepPuritySysUp);
  LostLeptonPredictionData->SetBranchAddress("singleLepPuritySysDown", &singleLepPuritySysDown);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundSysUp", &diLepFoundSysUp);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundSysDown", &diLepFoundSysDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoSysUp", &muIsoSysUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoSysDown", &muIsoSysDown);
  LostLeptonPredictionData->SetBranchAddress("muRecoSysUp", &muRecoSysUp);
  LostLeptonPredictionData->SetBranchAddress("muRecoSysDown", &muRecoSysDown);
  LostLeptonPredictionData->SetBranchAddress("muAccSysUp", &muAccSysUp);
  LostLeptonPredictionData->SetBranchAddress("muAccSysDown", &muAccSysDown);
  LostLeptonPredictionData->SetBranchAddress("muAccQsquareSysUp", &muAccQsquareSysUp);
  LostLeptonPredictionData->SetBranchAddress("muAccQsquareSysDown", &muAccQsquareSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoSysUp", &elecIsoSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoSysDown", &elecIsoSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecRecoSysUp", &elecRecoSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecRecoSysDown", &elecRecoSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccSysUp", &elecAccSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccSysDown", &elecAccSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccQsquareSysUp", &elecAccQsquareSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccQsquareSysDown", &elecAccQsquareSysDown);

  LostLeptonPredictionData->SetBranchAddress("isoTrackStatUp", &isoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("isoTrackStatDown", &isoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackStatUp", &muIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackStatDown", &muIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("MTWStatUp", &MTWStatUp);
  LostLeptonPredictionData->SetBranchAddress("MTWStatDown", &MTWStatDown);
  LostLeptonPredictionData->SetBranchAddress("purityStatUp", &purityStatUp);
  LostLeptonPredictionData->SetBranchAddress("purityStatDown", &purityStatDown);
  LostLeptonPredictionData->SetBranchAddress("singleLepPurityStatUp", &singleLepPurityStatUp);
  LostLeptonPredictionData->SetBranchAddress("singleLepPurityStatDown", &singleLepPurityStatDown);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundStatUp", &diLepFoundStatUp);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundStatDown", &diLepFoundStatDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoStatUp", &muIsoStatUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoStatDown", &muIsoStatDown);
  LostLeptonPredictionData->SetBranchAddress("muRecoStatUp", &muRecoStatUp);
  LostLeptonPredictionData->SetBranchAddress("muRecoStatDown", &muRecoStatDown);
  LostLeptonPredictionData->SetBranchAddress("muAccStatUp", &muAccStatUp);
  LostLeptonPredictionData->SetBranchAddress("muAccStatDown", &muAccStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoStatUp", &elecIsoStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoStatDown", &elecIsoStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecRecoStatUp", &elecRecoStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecRecoStatDown", &elecRecoStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccStatUp", &elecAccStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccStatDown", &elecAccStatDown);


  std::cout<<"Loop on Prediction (Data)"<<std::endl;
  
  nentries = LostLeptonPredictionData->GetEntries();
  nbytes = 0;
  double scaleMC = 1.0;
  if(!useMCForDataTree && InputPath_Prediction_Data != InputPath_Prediction) scaleFactorWeight = 1.0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPredictionData->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
    }
    else SearchBin = Bin;
    
    if(SearchBin > 900) continue;
    if(MTW>100)continue;
    if(MuonsNum+ElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(!useMCForDataTree && InputPath_Prediction_Data != InputPath_Prediction) scaleMC = Weight;

    totalPred_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    totalPred_HT_LL_->Fill(HT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    totalPred_MHT_LL_->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    totalPred_NJets_LL_->Fill(NJets, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    totalPred_BTags_LL_->Fill(BTags, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);

    double PTW(0.);
    if (MuonsNum==1) PTW=PTWCalculator(MHT, MHTPhi, Muons->at(0).Pt(), Muons->at(0).Phi());
    if (ElectronsNum==1) PTW=PTWCalculator(MHT, MHTPhi, Electrons->at(0).Pt(), Electrons->at(0).Phi());


    // extrapolation predictions

    // first reset holders
    for (unsigned int inj(0); inj<3; inj++) {
      for (unsigned int inb(0); inb<4; inb++) {
  totalPred_MHT_EXTRAP_HT12_LL_[inj*4+inb]->Reset();
  totalPred_MHT_EXTRAP_HT3_LL_[inj*4+inb]->Reset();
  totalPred_MHT_EXTRAP_HT23_LL_[inj*4+inb]->Reset();
      }
    }
    
    int INJ(-1);
    if (NJets>=4&&NJets<=6) INJ=0;
    else if (NJets>=7&&NJets<=8) INJ=1;
    else if (NJets>=9) INJ=2;
    int INB(BTags);
    if (INB>3) INB=3;
    int INB_EXTRAP=INB;
    if (INB_EXTRAP>2) INB_EXTRAP=2;
    int IHT(-1);
    if (HT>500&&HT<800) IHT=0;
    else if (HT>800&&HT<1200) IHT=1;
    else if (HT>1200) IHT=2;
    if (HT<800&&MHT>750) IHT=-1;

if(doExtrapolation){
    if (INJ>=0&&INB>=0&&IHT>=0) {
      if (HT>500&&HT<1200) {
  totalPred_MHT_Normal_HT12_LL_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
  totalCR_MHT_HT12_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
  totalCR_PTW_HT12_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
      }
      if (HT>1200) {
  totalPred_MHT_Normal_HT3_LL_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
  totalCR_MHT_HT3_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
  totalCR_PTW_HT3_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
      }
      if (HT>800) {
  totalPred_MHT_Normal_HT23_LL_[INJ*4+INB]->Fill(MHT, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
  totalCR_MHT_HT23_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
  totalCR_PTW_HT23_LL_[INJ*4+INB]->Fill(PTW, scaleFactorWeight/scaleMC);
      }
      for (int template_bin=0; template_bin<nTemplateBins; template_bin++) {
  if (HT>500&&HT<1200) {
    // NOTE: using the combined e/mu weight for now--should look into separating the flavors, commented out below
    totalPred_MHT_EXTRAP_HT12_LL_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                   (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC)*LostLepRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT12_LL_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //              (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostMuRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT12_LL_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //              (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostElecRATIO_HT12[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));   
  }
  if (HT>1200) {
    totalPred_MHT_EXTRAP_HT3_LL_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                   (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC)*LostLepRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT3_LL_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //             (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostMuRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT3_LL_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //             (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostElecRATIO_HT3[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));   
  }
  if (HT>800) {
    totalPred_MHT_EXTRAP_HT23_LL_[INJ*4+INB]->Fill( PTW*LostLepRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
                   (totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC)*LostLepRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT23_LL_[INJ*4+INB]->Fill( PTW*LostMuRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //              (muTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostMuRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
    // totalPred_MHT_EXTRAP_HT23_LL_[INJ*4+INB]->Fill( PTW*LostElecRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinCenter(template_bin+1),
    //              (elecTotalWeightDiLepIsoTrackReduced*scaleFactorWeight/scaleMC)*LostElecRATIO_HT23[INJ*3+INB_EXTRAP]->GetBinContent(template_bin+1));
  }
      }
    }
}

    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);

    totalPredMuIsoTrackSysUp_LL_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredMuIsoTrackSysDown_LL_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredElecIsoTrackSysUp_LL_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredElecIsoTrackSysDown_LL_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredPionIsoTrackSysUp_LL_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredPionIsoTrackSysDown_LL_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);
    totalPredMTWSysUp_LL_->Fill(SearchBin, MTWSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMTWSysDown_LL_->Fill(SearchBin, MTWSysDown*scaleFactorWeight/2/scaleMC);
    totalPredPuritySysUp_LL_->Fill(SearchBin, puritySysUp*scaleFactorWeight/2/scaleMC);
    totalPredPuritySysDown_LL_->Fill(SearchBin, puritySysDown*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPuritySysUp_LL_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPuritySysDown_LL_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundSysUp_LL_->Fill(SearchBin, diLepFoundSysUp*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundSysDown_LL_->Fill(SearchBin, diLepFoundSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoSysUp_LL_->Fill(SearchBin, muIsoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoSysDown_LL_->Fill(SearchBin, muIsoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoSysUp_LL_->Fill(SearchBin, muRecoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoSysDown_LL_->Fill(SearchBin, muRecoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccSysUp_LL_->Fill(SearchBin, muAccSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccSysDown_LL_->Fill(SearchBin, muAccSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccQsquareSysUp_LL_->Fill(SearchBin, muAccQsquareSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccQsquareSysDown_LL_->Fill(SearchBin, muAccQsquareSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoSysUp_LL_->Fill(SearchBin, elecIsoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoSysDown_LL_->Fill(SearchBin, elecIsoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoSysUp_LL_->Fill(SearchBin, elecRecoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoSysDown_LL_->Fill(SearchBin, elecRecoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccSysUp_LL_->Fill(SearchBin, elecAccSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccSysDown_LL_->Fill(SearchBin, elecAccSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccQsquareSysUp_LL_->Fill(SearchBin, elecAccQsquareSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccQsquareSysDown_LL_->Fill(SearchBin, elecAccQsquareSysDown*scaleFactorWeight/2/scaleMC);

    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, isoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, isoTrackStatDown*scaleFactorWeight/2/scaleMC);
    /*    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    */
    totalPredMuIsoTrackStatUp_LL_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoTrackStatDown_LL_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoTrackStatUp_LL_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoTrackStatDown_LL_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredPionIsoTrackStatUp_LL_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredPionIsoTrackStatDown_LL_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMTWStatUp_LL_->Fill(SearchBin, MTWStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMTWStatDown_LL_->Fill(SearchBin, MTWStatDown*scaleFactorWeight/2/scaleMC);
    totalPredPurityStatUp_LL_->Fill(SearchBin, purityStatUp*scaleFactorWeight/2/scaleMC);
    totalPredPurityStatDown_LL_->Fill(SearchBin, purityStatDown*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPurityStatUp_LL_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPurityStatDown_LL_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundStatUp_LL_->Fill(SearchBin, diLepFoundStatUp*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundStatDown_LL_->Fill(SearchBin, diLepFoundStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoStatUp_LL_->Fill(SearchBin, muIsoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoStatDown_LL_->Fill(SearchBin, muIsoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoStatUp_LL_->Fill(SearchBin, muRecoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoStatDown_LL_->Fill(SearchBin, muRecoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccStatUp_LL_->Fill(SearchBin, muAccStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccStatDown_LL_->Fill(SearchBin, muAccStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoStatUp_LL_->Fill(SearchBin, elecIsoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoStatDown_LL_->Fill(SearchBin, elecIsoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoStatUp_LL_->Fill(SearchBin, elecRecoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoStatDown_LL_->Fill(SearchBin, elecRecoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccStatUp_LL_->Fill(SearchBin, elecAccStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccStatDown_LL_->Fill(SearchBin, elecAccStatDown*scaleFactorWeight/2/scaleMC);

    //totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    //totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

    //totalPropSysUp_LL_->Fill(SearchBin, totalPropSysUp*scaleFactorWeight/2/scaleMC);
    //totalPropSysDown_LL_->Fill(SearchBin, totalPropSysDown*scaleFactorWeight/2/scaleMC);

    totalCS_LL_->Fill(SearchBin, scaledWeight/scaleMC);
    nEvtsCS_LL_->Fill(SearchBin);

    if(MuonsNum==1){
        totalCS_mu_HT_LL_->Fill(HT, scaledWeight/scaleMC);
        totalCS_mu_MHT_LL_->Fill(MHT, scaledWeight/scaleMC);
        totalCS_mu_NJets_LL_->Fill(NJets, scaledWeight/scaleMC);
        totalCS_mu_BTags_LL_->Fill(BTags, scaledWeight/scaleMC);
        totalCS_mu_pT_LL_->Fill(Muons->at(0).Pt(), scaledWeight/scaleMC);
    }else if(ElectronsNum==1){
        totalCS_elec_HT_LL_->Fill(HT, scaledWeight/scaleMC);
        totalCS_elec_MHT_LL_->Fill(MHT, scaledWeight/scaleMC);
        totalCS_elec_NJets_LL_->Fill(NJets, scaledWeight/scaleMC);
        totalCS_elec_BTags_LL_->Fill(BTags, scaledWeight/scaleMC);
        totalCS_elec_pT_LL_->Fill(Electrons->at(0).Pt(), scaledWeight/scaleMC);
    }

if(doExtrapolation){
    // fill 72-bin histogram for extrapolation method
    if (SearchBin%6 > 0 && SearchBin%6 < 4) {
      totalPred_EXTRAP_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC); // lowest-MHT, use classical prediction
    } else {
      int iSB = INJ*24+INB*6;
      //  Double_t mht_bins[6] = {200, 400, 500, 600, 750, 10000};
      totalPred_EXTRAP_LL_->Fill(iSB+4, totalPred_MHT_EXTRAP_HT12_LL_[INJ*4+INB]->Integral(3,4));
      totalPred_EXTRAP_LL_->Fill(iSB+5, totalPred_MHT_EXTRAP_HT3_LL_[INJ*4+INB]->Integral(3,4));
      totalPred_EXTRAP_LL_->Fill(iSB+6, totalPred_MHT_EXTRAP_HT23_LL_[INJ*4+INB]->Integral(5,6));
    }
}

    avgWeight_LL_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);


    hPredAllBins->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    if(BTags==0) hPredHTMHT0b->Fill(getHTMHTBox(HT, MHT), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    else hPredHTMHTwb->Fill(getHTMHTBox(HT, MHT), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    hPredNJetBins->Fill(NJets, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    hPredNbBins->Fill(BTags, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);


    if(MuonsNum==1 && ElectronsNum==0){
      ControlSampleMu_->Fill(SearchBin, scaledWeight/scaleMC);
          
      totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
      totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
      totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionMu_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
      totalPreMu+=totalWeightDiLep*scaleFactorWeight/scaleMC;
      totalPreMuError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
      // isotrackveto applied
      totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionMuIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC);
      totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC;
      totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC/scaleMC;

    }
    if(MuonsNum==0 && ElectronsNum==1){
      ControlSampleElec_->Fill(SearchBin, scaledWeight/scaleMC);
          
      totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
      totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
      totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElec_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
      totalPreElec+=totalWeightDiLep*scaleFactorWeight/scaleMC;
      totalPreElecError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
      // isotrackveto applied
      totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElecIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC);
      totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC;
      totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC/scaleMC;
    }
  }

  std::cout<<"Finished"<<std::endl;

  
  TH1D* FullClosure = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosure->Divide(totalPredictionIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosure->SetName("LostLeptonClosure");
  FullClosure->SetTitle("Closure of lost-lepton method");
  
  TH1D* FullClosureMu = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureMu->Divide(totalPredictionMuIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureMu->SetName("LostLeptonClosureMuCS");
  FullClosureMu->SetTitle("Closure of lost-lepton method #mu control-sample");
  
  TH1D* FullClosureElec = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureElec->Divide(totalPredictionElecIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureElec->SetName("LostLeptonClosureElecCS");
  FullClosureElec->SetTitle("Closure of lost-lepton method elec control-sample");

  TH1D* ClosureWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureWoIsoTrack->Divide(totalPrediction_,totalExpectation_,1,1,"");
  ClosureWoIsoTrack->SetName("ClosureWoIsoTrack");
  ClosureWoIsoTrack->SetTitle("Closure of lost-lepton method (wo IsotrackVeto)");
  
  TH1D* ClosureMuWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureMuWoIsoTrack->Divide(totalPredictionMu_,totalExpectation_,1,1,"");
  ClosureMuWoIsoTrack->SetName("ClosureMuWoIsoTrack");
  ClosureMuWoIsoTrack->SetTitle("Closure of lost-lepton method #mu control-sample (wo IsotrackVeto)");
  
  TH1D* ClosureElecWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureElecWoIsoTrack->Divide(totalPredictionElec_,totalExpectation_,1,1,"");
  ClosureElecWoIsoTrack->SetName("ClosureElecWoIsoTrack");
  ClosureElecWoIsoTrack->SetTitle("Closure of lost-lepton method elec control-sample (wo IsotrackVeto)");


  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";
  std::cout<<"\n Muon and Electron CS:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack (from Data): "<<totalPreIsoTrack<<" +- "<<sqrt(totalPreIsoTrackError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction (from Data): "<<totalPre<<" +- "<<sqrt(totalPreError)<<std::endl;
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre (from Data): "<<totalPreMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre (from Data): "<<totalPreMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre (from Data): "<<totalPreMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre (from Data): "<<totalPreElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: (from Data) "<<totalPreElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre (from Data): "<<totalPreElecIso<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

  std::cout<<"\n Muon CS only:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack (from Data): "<<totalPreIsoTrackMu<<" +- "<<sqrt(totalPreIsoTrackMuError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction (from Data): "<<totalPreMu<<" +- "<<sqrt(totalPreMuError)<<std::endl; 
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre (from Data): "<<totalPreMuMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre (from Data): "<<totalPreMuMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre (from Data): "<<totalPreMuMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre (from Data): "<<totalPreMuElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre (from Data): "<<totalPreMuElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre (from Data): "<<totalPreMuElecIso<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

  std::cout<<"\n Elec CS only:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack (from Data): "<<totalPreIsoTrackElec<<" +- "<<sqrt(totalPreIsoTrackElecError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction (from Data): "<<totalPreElec<<" +- "<<sqrt(totalPreElecError)<<std::endl; 
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre (from Data): "<<totalPreElecMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre (from Data): "<<totalPreElecMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre (from Data): "<<totalPreElecMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre (from Data): "<<totalPreElecElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre (from Data): "<<totalPreElecElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre (from Data): "<<totalPreElecElecIso<<std::endl;
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

  SaveClosure(totalPredictionMuCSMuAccNJets_, totalExpectationMuAccNJets_, dClosures);
  SaveClosure(totalPredictionMuCSMuRecoNJets_, totalExpectationMuRecoNJets_, dClosures);
  SaveClosure(totalPredictionMuCSMuIsoNJets_, totalExpectationMuIsoNJets_, dClosures);
  
  SaveClosure(totalPredictionMuCSElecAccNJets_, totalExpectationElecAccNJets_, dClosures);
  SaveClosure(totalPredictionMuCSElecRecoNJets_, totalExpectationElecRecoNJets_, dClosures);
  SaveClosure(totalPredictionMuCSElecIsoNJets_, totalExpectationElecIsoNJets_, dClosures);
  
  SaveClosure(totalPredictionElecCSMuAccNJets_, totalExpectationMuAccNJets_, dClosures);
  SaveClosure(totalPredictionElecCSMuRecoNJets_, totalExpectationMuRecoNJets_, dClosures);
  SaveClosure(totalPredictionElecCSMuIsoNJets_, totalExpectationMuIsoNJets_, dClosures);
  
  SaveClosure(totalPredictionElecCSElecAccNJets_, totalExpectationElecAccNJets_, dClosures);
  SaveClosure(totalPredictionElecCSElecRecoNJets_, totalExpectationElecRecoNJets_, dClosures);
  SaveClosure(totalPredictionElecCSElecIsoNJets_, totalExpectationElecIsoNJets_, dClosures);

  SaveClosure(totalPredictionMuCSMuAccHT_, totalExpectationMuAccHT_, dClosures);
  SaveClosure(totalPredictionMuCSMuRecoHT_, totalExpectationMuRecoHT_, dClosures);
  SaveClosure(totalPredictionMuCSMuIsoHT_, totalExpectationMuIsoHT_, dClosures);
  
  SaveClosure(totalPredictionMuCSElecAccHT_, totalExpectationElecAccHT_, dClosures);
  SaveClosure(totalPredictionMuCSElecRecoHT_, totalExpectationElecRecoHT_, dClosures);
  SaveClosure(totalPredictionMuCSElecIsoHT_, totalExpectationElecIsoHT_, dClosures);
  
  SaveClosure(totalPredictionElecCSMuAccHT_, totalExpectationMuAccHT_, dClosures);
  SaveClosure(totalPredictionElecCSMuRecoHT_, totalExpectationMuRecoHT_, dClosures);
  SaveClosure(totalPredictionElecCSMuIsoHT_, totalExpectationMuIsoHT_, dClosures);
  
  SaveClosure(totalPredictionElecCSElecAccHT_, totalExpectationElecAccHT_, dClosures);
  SaveClosure(totalPredictionElecCSElecRecoHT_, totalExpectationElecRecoHT_, dClosures);
  SaveClosure(totalPredictionElecCSElecIsoHT_, totalExpectationElecIsoHT_, dClosures);

  SaveClosure(totalPredictionMuCSMuAccMHT_, totalExpectationMuAccMHT_, dClosures);
  SaveClosure(totalPredictionMuCSMuRecoMHT_, totalExpectationMuRecoMHT_, dClosures);
  SaveClosure(totalPredictionMuCSMuIsoMHT_, totalExpectationMuIsoMHT_, dClosures);
  
  SaveClosure(totalPredictionMuCSElecAccMHT_, totalExpectationElecAccMHT_, dClosures);
  SaveClosure(totalPredictionMuCSElecRecoMHT_, totalExpectationElecRecoMHT_, dClosures);
  SaveClosure(totalPredictionMuCSElecIsoMHT_, totalExpectationElecIsoMHT_, dClosures);
  
  SaveClosure(totalPredictionElecCSMuAccMHT_, totalExpectationMuAccMHT_, dClosures);
  SaveClosure(totalPredictionElecCSMuRecoMHT_, totalExpectationMuRecoMHT_, dClosures);
  SaveClosure(totalPredictionElecCSMuIsoMHT_, totalExpectationMuIsoMHT_, dClosures);
  
  SaveClosure(totalPredictionElecCSElecAccMHT_, totalExpectationElecAccMHT_, dClosures);
  SaveClosure(totalPredictionElecCSElecRecoMHT_, totalExpectationElecRecoMHT_, dClosures);
  SaveClosure(totalPredictionElecCSElecIsoMHT_, totalExpectationElecIsoMHT_, dClosures);

  SaveClosure(totalPredictionMuCSMuAccBTag_, totalExpectationMuAccBTag_, dClosures);
  SaveClosure(totalPredictionMuCSMuRecoBTag_, totalExpectationMuRecoBTag_, dClosures);
  SaveClosure(totalPredictionMuCSMuIsoBTag_, totalExpectationMuIsoBTag_, dClosures);
  
  SaveClosure(totalPredictionMuCSElecAccBTag_, totalExpectationElecAccBTag_, dClosures);
  SaveClosure(totalPredictionMuCSElecRecoBTag_, totalExpectationElecRecoBTag_, dClosures);
  SaveClosure(totalPredictionMuCSElecIsoBTag_, totalExpectationElecIsoBTag_, dClosures);
  
  SaveClosure(totalPredictionElecCSMuAccBTag_, totalExpectationMuAccBTag_, dClosures);
  SaveClosure(totalPredictionElecCSMuRecoBTag_, totalExpectationMuRecoBTag_, dClosures);
  SaveClosure(totalPredictionElecCSMuIsoBTag_, totalExpectationMuIsoBTag_, dClosures);
  
  SaveClosure(totalPredictionElecCSElecAccBTag_, totalExpectationElecAccBTag_, dClosures);
  SaveClosure(totalPredictionElecCSElecRecoBTag_, totalExpectationElecRecoBTag_, dClosures);
  SaveClosure(totalPredictionElecCSElecIsoBTag_, totalExpectationElecIsoBTag_, dClosures);
  
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



  TFile *LLoutPutFile = new TFile(OutputPath_Prediction.c_str(),"RECREATE");

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("DataMCFullStatus");
  TDirectory *dDataMCFullStatus = (TDirectory*)LLoutPutFile->Get("DataMCFullStatus");
  dDataMCFullStatus->cd();

  totalCS_mu_HT_LL_MC_->Write();
  totalCS_mu_MHT_LL_MC_->Write();
  totalCS_mu_NJets_LL_MC_->Write();
  totalCS_mu_BTags_LL_MC_->Write();
  totalCS_mu_pT_LL_MC_->Write();

  totalCS_elec_HT_LL_MC_->Write();
  totalCS_elec_MHT_LL_MC_->Write();
  totalCS_elec_NJets_LL_MC_->Write();
  totalCS_elec_BTags_LL_MC_->Write();
  totalCS_elec_pT_LL_MC_->Write();

  totalCS_mu_HT_LL_->Write();
  totalCS_mu_MHT_LL_->Write();
  totalCS_mu_NJets_LL_->Write();
  totalCS_mu_BTags_LL_->Write();
  totalCS_mu_pT_LL_->Write();

  totalCS_elec_HT_LL_->Write();
  totalCS_elec_MHT_LL_->Write();
  totalCS_elec_NJets_LL_->Write();
  totalCS_elec_BTags_LL_->Write();
  totalCS_elec_pT_LL_->Write();

  TH1D* muOverE_HT_LL_ = (TH1D*) totalCS_mu_HT_LL_->Clone("muOverE_HT_LL_");
  muOverE_HT_LL_->Divide(totalCS_mu_HT_LL_, totalCS_elec_HT_LL_, 1., totalCS_mu_HT_LL_->Integral()/totalCS_elec_HT_LL_->Integral());
  muOverE_HT_LL_->Write();

  TH1D* muOverE_MHT_LL_ = (TH1D*) totalCS_mu_MHT_LL_->Clone("muOverE_MHT_LL_");
  muOverE_MHT_LL_->Divide(totalCS_mu_MHT_LL_, totalCS_elec_MHT_LL_, 1., totalCS_mu_MHT_LL_->Integral()/totalCS_elec_MHT_LL_->Integral());
  muOverE_MHT_LL_->Write();

  TH1D* muOverE_NJets_LL_ = (TH1D*) totalCS_mu_NJets_LL_->Clone("muOverE_NJets_LL_");
  muOverE_NJets_LL_->Divide(totalCS_mu_NJets_LL_, totalCS_elec_NJets_LL_, 1., totalCS_mu_NJets_LL_->Integral()/totalCS_elec_NJets_LL_->Integral());
  muOverE_NJets_LL_->Write();

  TH1D* muOverE_BTags_LL_ = (TH1D*) totalCS_mu_BTags_LL_->Clone("muOverE_BTags_LL_");
  muOverE_BTags_LL_->Divide(totalCS_mu_BTags_LL_, totalCS_elec_BTags_LL_, 1., totalCS_mu_BTags_LL_->Integral()/totalCS_elec_BTags_LL_->Integral());
  muOverE_BTags_LL_->Write();


  TH1D* muOverE_HT_LL_MC_ = (TH1D*) totalCS_mu_HT_LL_MC_->Clone("muOverE_HT_LL_MC_");
  muOverE_HT_LL_MC_->Divide(totalCS_mu_HT_LL_MC_, totalCS_elec_HT_LL_MC_, 1., totalCS_mu_HT_LL_MC_->Integral()/totalCS_elec_HT_LL_MC_->Integral());
  muOverE_HT_LL_MC_->Write();

  TH1D* muOverE_MHT_LL_MC_ = (TH1D*) totalCS_mu_MHT_LL_MC_->Clone("muOverE_MHT_LL_MC_");
  muOverE_MHT_LL_MC_->Divide(totalCS_mu_MHT_LL_MC_, totalCS_elec_MHT_LL_MC_, 1., totalCS_mu_MHT_LL_MC_->Integral()/totalCS_elec_MHT_LL_MC_->Integral());
  muOverE_MHT_LL_MC_->Write();

  TH1D* muOverE_NJets_LL_MC_ = (TH1D*) totalCS_mu_NJets_LL_MC_->Clone("muOverE_NJets_LL_MC_");
  muOverE_NJets_LL_MC_->Divide(totalCS_mu_NJets_LL_MC_, totalCS_elec_NJets_LL_MC_, 1., totalCS_mu_NJets_LL_MC_->Integral()/totalCS_elec_NJets_LL_MC_->Integral());
  muOverE_NJets_LL_MC_->Write();

  TH1D* muOverE_BTags_LL_MC_ = (TH1D*) totalCS_mu_BTags_LL_MC_->Clone("muOverE_BTags_LL_MC_");
  muOverE_BTags_LL_MC_->Divide(totalCS_mu_BTags_LL_MC_, totalCS_elec_BTags_LL_MC_, 1., totalCS_mu_BTags_LL_MC_->Integral()/totalCS_elec_BTags_LL_MC_->Integral());
  muOverE_BTags_LL_MC_->Write();


  TH1D* muOverE_HT_DoubleRatio = (TH1D*) totalCS_mu_HT_LL_MC_->Clone("muOverE_HT_DoubleRatio");
  muOverE_HT_DoubleRatio->SetTitle(";H_{T};DoubleRatio: #mu CS(data/MC) / e CS(data/MC)");
  TH1D* muCS_HT= (TH1D*) totalCS_mu_HT_LL_MC_->Clone("muCS_HT");
  TH1D* elecCS_HT = (TH1D*) totalCS_mu_HT_LL_MC_->Clone("elecCS_HT");
  muCS_HT->Divide(totalCS_mu_HT_LL_, totalCS_mu_HT_LL_MC_, 1., totalCS_mu_HT_LL_->Integral()/totalCS_mu_HT_LL_MC_->Integral());
  elecCS_HT->Divide(totalCS_elec_HT_LL_, totalCS_elec_HT_LL_MC_, 1., totalCS_elec_HT_LL_->Integral()/totalCS_elec_HT_LL_MC_->Integral());
  muOverE_HT_DoubleRatio->Divide(muCS_HT, elecCS_HT);
  muOverE_HT_DoubleRatio->Write();

  TH1D* muOverE_MHT_DoubleRatio = (TH1D*) totalCS_mu_MHT_LL_MC_->Clone("muOverE_MHT_DoubleRatio");
  muOverE_MHT_DoubleRatio->SetTitle(";#slash{H}_{T};DoubleRatio: #mu CS(data/MC) / e CS(data/MC)");
  TH1D* muCS_MHT= (TH1D*) totalCS_mu_MHT_LL_MC_->Clone("muCS_MHT");
  TH1D* elecCS_MHT = (TH1D*) totalCS_mu_MHT_LL_MC_->Clone("elecCS_MHT");
  muCS_MHT->Divide(totalCS_mu_MHT_LL_, totalCS_mu_MHT_LL_MC_, 1., totalCS_mu_MHT_LL_->Integral()/totalCS_mu_MHT_LL_MC_->Integral());
  elecCS_MHT->Divide(totalCS_elec_MHT_LL_, totalCS_elec_MHT_LL_MC_, 1., totalCS_elec_MHT_LL_->Integral()/totalCS_elec_MHT_LL_MC_->Integral());
  muOverE_MHT_DoubleRatio->Divide(muCS_MHT, elecCS_MHT);
  muOverE_MHT_DoubleRatio->Write();

  TH1D* muOverE_NJets_DoubleRatio = (TH1D*) totalCS_mu_NJets_LL_MC_->Clone("muOverE_NJets_DoubleRatio");
  muOverE_NJets_DoubleRatio->SetTitle(";N_{Jets};DoubleRatio: #mu CS(data/MC) / e CS(data/MC)");
  TH1D* muCS_NJets= (TH1D*) totalCS_mu_NJets_LL_MC_->Clone("muCS_NJets");
  TH1D* elecCS_NJets = (TH1D*) totalCS_mu_NJets_LL_MC_->Clone("elecCS_NJets");
  muCS_NJets->Divide(totalCS_mu_NJets_LL_, totalCS_mu_NJets_LL_MC_, 1., totalCS_mu_NJets_LL_->Integral()/totalCS_mu_NJets_LL_MC_->Integral());
  elecCS_NJets->Divide(totalCS_elec_NJets_LL_, totalCS_elec_NJets_LL_MC_, 1., totalCS_elec_NJets_LL_->Integral()/totalCS_elec_NJets_LL_MC_->Integral());
  muOverE_NJets_DoubleRatio->Divide(muCS_NJets, elecCS_NJets);
  muOverE_NJets_DoubleRatio->Write();

  TH1D* muOverE_BTags_DoubleRatio = (TH1D*) totalCS_mu_BTags_LL_MC_->Clone("muOverE_BTags_DoubleRatio");
  muOverE_BTags_DoubleRatio->SetTitle(";B_{Tags};DoubleRatio: #mu CS(data/MC) / e CS(data/MC)");
  TH1D* muCS_BTags= (TH1D*) totalCS_mu_BTags_LL_MC_->Clone("muCS_BTags");
  TH1D* elecCS_BTags = (TH1D*) totalCS_mu_BTags_LL_MC_->Clone("elecCS_BTags");
  muCS_BTags->Divide(totalCS_mu_BTags_LL_, totalCS_mu_BTags_LL_MC_, 1., totalCS_mu_BTags_LL_->Integral()/totalCS_mu_BTags_LL_MC_->Integral());
  elecCS_BTags->Divide(totalCS_elec_BTags_LL_, totalCS_elec_BTags_LL_MC_, 1., totalCS_elec_BTags_LL_->Integral()/totalCS_elec_BTags_LL_MC_->Integral());
  muOverE_BTags_DoubleRatio->Divide(muCS_BTags, elecCS_BTags);
  muOverE_BTags_DoubleRatio->Write();

  TH1D* muOverE_pT_DoubleRatio = (TH1D*) totalCS_mu_pT_LL_MC_->Clone("muOverE_pT_DoubleRatio");
  muOverE_pT_DoubleRatio->SetTitle(";B_{Tags};DoubleRatio: #mu CS(data/MC) / e CS(data/MC)");
  TH1D* muCS_pT= (TH1D*) totalCS_mu_pT_LL_MC_->Clone("muCS_pT");
  TH1D* elecCS_pT = (TH1D*) totalCS_mu_pT_LL_MC_->Clone("elecCS_pT");
  muCS_pT->Divide(totalCS_mu_pT_LL_, totalCS_mu_pT_LL_MC_, 1., totalCS_mu_pT_LL_->Integral()/totalCS_mu_pT_LL_MC_->Integral());
  elecCS_pT->Divide(totalCS_elec_pT_LL_, totalCS_elec_pT_LL_MC_, 1., totalCS_elec_pT_LL_->Integral()/totalCS_elec_pT_LL_MC_->Integral());
  muOverE_pT_DoubleRatio->Divide(muCS_pT, elecCS_pT);
  muOverE_pT_DoubleRatio->Write();


  LLoutPutFile->cd();
  LLoutPutFile->mkdir("SearchVariables");
  TDirectory *dSearchVariables = (TDirectory*)LLoutPutFile->Get("SearchVariables");
  dSearchVariables->cd();

  totalExp_HT_LL_->Write();
  totalExp_MHT_LL_->Write();
  totalExp_NJets_LL_->Write();
  totalExp_BTags_LL_->Write();

  totalExp_PTW_LL_->Write();
  totalExp_PTW_LL_0b_->Write();
  totalExp_PTW_LL_1b_->Write();
  totalExp_PTW_LL_2b_->Write();

  totalExp_PTL_LL_->Write();
  totalExp_ETAL_LL_->Write();


  totalPred_HT_LL_MC_->Write();
  totalPred_MHT_LL_MC_->Write();
  totalPred_NJets_LL_MC_->Write();
  totalPred_BTags_LL_MC_->Write();

  totalPred_PTW_LL_MC_->Write();
  totalPred_PTW_LL_0b_MC_->Write();
  totalPred_PTW_LL_1b_MC_->Write();
  totalPred_PTW_LL_2b_MC_->Write();

  totalPred_PTL_LL_MC_->Write();
  totalPred_ETAL_LL_MC_->Write();


  totalPred_HT_LL_->Write();
  totalPred_MHT_LL_->Write();
  totalPred_NJets_LL_->Write();
  totalPred_BTags_LL_->Write();
  
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<4; inb++) {
      totalExp_MHT_Normal_HT12_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT12_LL_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT12_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT12_LL_MC_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT12_LL_MC_[inj*4+inb]->Write();
      totalExp_MHT_Normal_HT3_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT3_LL_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT3_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT3_LL_MC_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT3_LL_MC_[inj*4+inb]->Write();
      totalExp_MHT_Normal_HT23_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT23_LL_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT23_LL_[inj*4+inb]->Write();
      totalPred_MHT_Normal_HT23_LL_MC_[inj*4+inb]->Write();
      totalPred_MHT_EXTRAP_HT23_LL_MC_[inj*4+inb]->Write();
    }
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Closure");
  TDirectory *dClosure = (TDirectory*)LLoutPutFile->Get("Closure");
  dClosure->cd();

  TH1D *ClosureTest = (TH1D*) totalExp_LL_->Clone("ClosureTest");
  ClosureTest->Divide(totalPred_LL_MC_);
  ClosureTest->SetTitle("Expectation / Prediction");
  SetBinLabel(ClosureTest);
  ClosureTest->Write();

  TH1D *ClosureTest_woIso = (TH1D*) totalExpwoIso_LL_->Clone("ClosureTest_woIso");
  ClosureTest_woIso->Divide(totalPredwoIso_LL_MC_);
  ClosureTest_woIso->SetTitle("Expectation / Prediction");
  SetBinLabel(ClosureTest_woIso);
  ClosureTest_woIso->Write();

  // TH1D *ClosureTest_NoTk = (TH1D*) totalExp_LL_NoTk_->Clone("ClosureTest_NoTk");
  // ClosureTest_NoTk->Divide(totalPred_LL_NoTk_MC_);
  // ClosureTest_NoTk->SetTitle("Expectation / Prediction");
  // SetBinLabel(ClosureTest_NoTk);
  // ClosureTest_NoTk->Write();

  TH1D *ClosureTest_HT = (TH1D*) totalExp_HT_LL_->Clone("ClosureTest_HT");
  ClosureTest_HT->Divide(totalPred_HT_LL_MC_);
  ClosureTest_HT->SetTitle("Expectation / Prediction");
  ClosureTest_HT->Write();

  TH1D *ClosureTest_MHT = (TH1D*) totalExp_MHT_LL_->Clone("ClosureTest_MHT");
  ClosureTest_MHT->Divide(totalPred_MHT_LL_MC_);
  ClosureTest_MHT->SetTitle("Expectation / Prediction");
  ClosureTest_MHT->Write();

  TH1D *ClosureTest_NJets = (TH1D*) totalExp_NJets_LL_->Clone("ClosureTest_NJets");
  ClosureTest_NJets->Divide(totalPred_NJets_LL_MC_);
  ClosureTest_NJets->SetTitle("Expectation / Prediction");
  ClosureTest_NJets->Write();

  TH1D *ClosureTest_BTags = (TH1D*) totalExp_BTags_LL_->Clone("ClosureTest_BTags");
  ClosureTest_BTags->Divide(totalPred_BTags_LL_MC_);
  ClosureTest_BTags->SetTitle("Expectation / Prediction");
  ClosureTest_BTags->Write();

  TH1D *ClosureTest_PTL = (TH1D*) totalExp_PTL_LL_->Clone("ClosureTest_PTL");
  ClosureTest_PTL->Divide(totalPred_PTL_LL_MC_);
  ClosureTest_PTL->SetTitle("Expectation / Prediction");
  ClosureTest_PTL->Write();
  TH1D *ClosureTest_PTW = (TH1D*) totalExp_PTW_LL_->Clone("ClosureTest_PTW");
  ClosureTest_PTW->Divide(totalPred_PTW_LL_MC_);
  ClosureTest_PTW->SetTitle("Expectation / Prediction");
  ClosureTest_PTW->Write();
  TH1D *ClosureTest_PTW_0b = (TH1D*) totalExp_PTW_LL_0b_->Clone("ClosureTest_PTW_0b");
  ClosureTest_PTW_0b->Divide(totalPred_PTW_LL_0b_MC_);
  ClosureTest_PTW_0b->SetTitle("Expectation / Prediction");
  ClosureTest_PTW_0b->Write();
  TH1D *ClosureTest_PTW_1b = (TH1D*) totalExp_PTW_LL_1b_->Clone("ClosureTest_PTW_1b");
  ClosureTest_PTW_1b->Divide(totalPred_PTW_LL_1b_MC_);
  ClosureTest_PTW_1b->SetTitle("Expectation / Prediction");
  ClosureTest_PTW_1b->Write();
  TH1D *ClosureTest_PTW_2b = (TH1D*) totalExp_PTW_LL_2b_->Clone("ClosureTest_PTW_2b");
  ClosureTest_PTW_2b->Divide(totalPred_PTW_LL_2b_MC_);
  ClosureTest_PTW_2b->SetTitle("Expectation / Prediction");
  ClosureTest_PTW_2b->Write();

  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<4; inb++) {
      TH1D* ClosureTest_Normal_HT12_MC = (TH1D*) totalExp_MHT_Normal_HT12_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_Normal_HT12_NJ%d_NB%dLL_MC", inj+1, inb));
      ClosureTest_Normal_HT12_MC->Divide(totalPred_MHT_Normal_HT12_LL_MC_[inj*4+inb]);
      ClosureTest_Normal_HT12_MC->SetTitle("Expectation / Prediction");
      ClosureTest_Normal_HT12_MC->Write();
      TH1D* ClosureTest_EXTRAP_HT12_MC = (TH1D*) totalExp_MHT_Normal_HT12_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_EXTRAP_HT12_NJ%d_NB%d_LL_MC", inj+1, inb));
      ClosureTest_EXTRAP_HT12_MC->Divide(totalPred_MHT_EXTRAP_HT12_LL_MC_[inj*4+inb]);
      ClosureTest_EXTRAP_HT12_MC->SetTitle("Expectation / Prediction");
      ClosureTest_EXTRAP_HT12_MC->Write();
      TH1D* ClosureTest_Normal_HT3_MC = (TH1D*) totalExp_MHT_Normal_HT3_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_Normal_HT3_NJ%d_NB%dLL_MC", inj+1, inb));
      ClosureTest_Normal_HT3_MC->Divide(totalPred_MHT_Normal_HT3_LL_MC_[inj*4+inb]);
      ClosureTest_Normal_HT3_MC->SetTitle("Expectation / Prediction");
      ClosureTest_Normal_HT3_MC->Write();
      TH1D* ClosureTest_EXTRAP_HT3_MC = (TH1D*) totalExp_MHT_Normal_HT3_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_EXTRAP_HT3_NJ%d_NB%d_LL_MC", inj+1, inb));
      ClosureTest_EXTRAP_HT3_MC->Divide(totalPred_MHT_EXTRAP_HT3_LL_MC_[inj*4+inb]);
      ClosureTest_EXTRAP_HT3_MC->SetTitle("Expectation / Prediction");
      ClosureTest_EXTRAP_HT3_MC->Write();
      TH1D* ClosureTest_Normal_HT23_MC = (TH1D*) totalExp_MHT_Normal_HT23_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_Normal_HT23_NJ%d_NB%dLL_MC", inj+1, inb));
      ClosureTest_Normal_HT23_MC->Divide(totalPred_MHT_Normal_HT23_LL_MC_[inj*4+inb]);
      ClosureTest_Normal_HT23_MC->SetTitle("Expectation / Prediction");
      ClosureTest_Normal_HT23_MC->Write();
      TH1D* ClosureTest_EXTRAP_HT23_MC = (TH1D*) totalExp_MHT_Normal_HT23_LL_[inj*4+inb]->Clone(Form("ClosureTest_MHT_EXTRAP_HT23_NJ%d_NB%d_LL_MC", inj+1, inb));
      ClosureTest_EXTRAP_HT23_MC->Divide(totalPred_MHT_EXTRAP_HT23_LL_MC_[inj*4+inb]);
      ClosureTest_EXTRAP_HT23_MC->SetTitle("Expectation / Prediction");
      ClosureTest_EXTRAP_HT23_MC->Write();
    }
  }
  
  TH1D *nonClosureSysUp = (TH1D*) ClosureTest->Clone("nonClosureSysUp");
  nonClosureSysUp->Reset();
  nonClosureSysUp->SetTitle("nonClosureSysUp");
  TH1D *nonClosureSysDown = (TH1D*) ClosureTest->Clone("nonClosureSysDown");
  nonClosureSysDown->Reset();
  nonClosureSysDown->SetTitle("nonClosureSysUp");

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Expectation");
  TDirectory *dExp = (TDirectory*)LLoutPutFile->Get("Expectation");
  dExp->cd();

  SetBinLabel(totalExp_LL_);
  totalExp_LL_->Write();
  SetBinLabel(totalExpwoIso_LL_);
  totalExpwoIso_LL_->Write();
  // SetBinLabel(totalExp_LL_NoTk_);
  // totalExp_LL_NoTk_->Write();
  SetBinLabel(nEvtsExp_LL_);
  nEvtsExp_LL_->Write();

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_data");
  TDirectory *dPreData = (TDirectory*)LLoutPutFile->Get("Prediction_data");
  dPreData->cd();

  SetBinLabel(totalPred_LL_);
  totalPred_LL_->Write();
  SetBinLabel(totalPred_EXTRAP_LL_);
  totalPred_EXTRAP_LL_->Write();
  
  std::vector<TH1D*> allUncUp_LL_;
  allUncUp_LL_.push_back(totalPredIsoTrackSysUp_LL_);
  allUncUp_LL_.push_back(totalPredMTWSysUp_LL_);
  allUncUp_LL_.push_back(totalPredPuritySysUp_LL_);
  allUncUp_LL_.push_back(totalPredSingleLepPuritySysUp_LL_);
  allUncUp_LL_.push_back(totalPredDiLepFoundSysUp_LL_);
  allUncUp_LL_.push_back(totalPredMuIsoSysUp_LL_);
  allUncUp_LL_.push_back(totalPredMuRecoSysUp_LL_);
  allUncUp_LL_.push_back(totalPredMuAccSysUp_LL_);
  allUncUp_LL_.push_back(totalPredMuAccQsquareSysUp_LL_);
  allUncUp_LL_.push_back(totalPredElecIsoSysUp_LL_);
  allUncUp_LL_.push_back(totalPredElecRecoSysUp_LL_);
  allUncUp_LL_.push_back(totalPredElecAccSysUp_LL_);
  allUncUp_LL_.push_back(totalPredElecAccQsquareSysUp_LL_);
  allUncUp_LL_.push_back(totalPredIsoTrackStatUp_LL_);
  allUncUp_LL_.push_back(totalPredMTWStatUp_LL_);
  allUncUp_LL_.push_back(totalPredPurityStatUp_LL_);
  allUncUp_LL_.push_back(totalPredSingleLepPurityStatUp_LL_);
  allUncUp_LL_.push_back(totalPredDiLepFoundStatUp_LL_);
  allUncUp_LL_.push_back(totalPredMuIsoStatUp_LL_);
  allUncUp_LL_.push_back(totalPredMuRecoStatUp_LL_);
  allUncUp_LL_.push_back(totalPredMuAccStatUp_LL_);
  allUncUp_LL_.push_back(totalPredElecIsoStatUp_LL_);
  allUncUp_LL_.push_back(totalPredElecRecoStatUp_LL_);
  allUncUp_LL_.push_back(totalPredElecAccStatUp_LL_);

  addUncertainties(totalPropSysUp_LL_, allUncUp_LL_, true);

  std::vector<TH1D*> allUncDown_LL_;
  allUncDown_LL_.push_back(totalPredIsoTrackSysDown_LL_);
  allUncDown_LL_.push_back(totalPredMTWSysDown_LL_);
  allUncDown_LL_.push_back(totalPredPuritySysDown_LL_);
  allUncDown_LL_.push_back(totalPredSingleLepPuritySysDown_LL_);
  allUncDown_LL_.push_back(totalPredDiLepFoundSysDown_LL_);
  allUncDown_LL_.push_back(totalPredMuIsoSysDown_LL_);
  allUncDown_LL_.push_back(totalPredMuRecoSysDown_LL_);
  allUncDown_LL_.push_back(totalPredMuAccSysDown_LL_);
  allUncDown_LL_.push_back(totalPredMuAccQsquareSysDown_LL_);
  allUncDown_LL_.push_back(totalPredElecIsoSysDown_LL_);
  allUncDown_LL_.push_back(totalPredElecRecoSysDown_LL_);
  allUncDown_LL_.push_back(totalPredElecAccSysDown_LL_);
  allUncDown_LL_.push_back(totalPredElecAccQsquareSysDown_LL_);
  allUncDown_LL_.push_back(totalPredIsoTrackStatDown_LL_);
  allUncDown_LL_.push_back(totalPredMTWStatDown_LL_);
  allUncDown_LL_.push_back(totalPredPurityStatDown_LL_);
  allUncDown_LL_.push_back(totalPredSingleLepPurityStatDown_LL_);
  allUncDown_LL_.push_back(totalPredDiLepFoundStatDown_LL_);
  allUncDown_LL_.push_back(totalPredMuIsoStatDown_LL_);
  allUncDown_LL_.push_back(totalPredMuRecoStatDown_LL_);
  allUncDown_LL_.push_back(totalPredMuAccStatDown_LL_);
  allUncDown_LL_.push_back(totalPredElecIsoStatDown_LL_);
  allUncDown_LL_.push_back(totalPredElecRecoStatDown_LL_);
  allUncDown_LL_.push_back(totalPredElecAccStatDown_LL_);

  addUncertainties(totalPropSysDown_LL_, allUncDown_LL_, false);
  
  SaveFraction(totalPredIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
  /*  SaveFraction(totalPredMuIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredMuIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredElecIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredElecIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredPionIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredPionIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
  */  SaveFraction(totalPredMTWSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMTWSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredPuritySysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredPuritySysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredSingleLepPuritySysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredSingleLepPuritySysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredDiLepFoundSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredDiLepFoundSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuIsoSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuIsoSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuRecoSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuRecoSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccQsquareSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccQsquareSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecIsoSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecIsoSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecRecoSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecRecoSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccSysDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccQsquareSysUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccQsquareSysDown_LL_, totalPred_LL_, dPreData);

  SaveFraction(totalPredIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
  /*  SaveFraction(totalPredMuIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredMuIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredElecIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredElecIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredPionIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
      SaveFraction(totalPredPionIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
  */  SaveFraction(totalPredMTWStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMTWStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredPurityStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredPurityStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredSingleLepPurityStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredSingleLepPurityStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredDiLepFoundStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredDiLepFoundStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuIsoStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuIsoStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuRecoStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuRecoStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredMuAccStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecIsoStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecIsoStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecRecoStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecRecoStatDown_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccStatUp_LL_, totalPred_LL_, dPreData);
  SaveFraction(totalPredElecAccStatDown_LL_, totalPred_LL_, dPreData);

  for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
    totalPredNonClosureUp_LL_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
    totalPredNonClosureDown_LL_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
  }
  SetBinLabel(totalPredNonClosureUp_LL_);
  totalPredNonClosureUp_LL_->Write();
  SetBinLabel(totalPredNonClosureDown_LL_);
  totalPredNonClosureDown_LL_->Write();

  SetBinLabel(totalCS_LL_);
  totalCS_LL_->Write();
  SetBinLabel(nEvtsCS_LL_);
  nEvtsCS_LL_->Write();


  SetBinLabel(avgWeight_LL_);
  avgWeight_LL_->Write();

if(doExtrapolation){ 
  // now calculated the modified average weight for the extrapolation method
  for (int ibin(0); ibin<avgWeight_LL_->GetNbinsX(); ibin++) {
    EXTRAP_weight_SF_LL_->SetBinError(ibin+1, 0); 
    if (ibin%6 < 3) { // lowest-MHT, use classical weight
      EXTRAP_weight_SF_LL_->SetBinContent(ibin+1, 1);
    } else {
      unsigned int INJ(ibin/24); 
      unsigned int INB(ibin);
      if (INB>=24) INB-=24;
      if (INB>=24) INB-=24;
      INB=INB/6;
      // [new weight] = [normal weight] X N(min < MHT < max) / N(PTW > min)
      //  Double_t ptw_bins[6] = {200, 400, 500, 600, 750, 10000};
      double SF12 = (totalCR_PTW_HT12_LL_[INJ*4+INB]->Integral(2,6)>0) ? totalCR_MHT_HT12_LL_[INJ*4+INB]->Integral(3,4)/totalCR_PTW_HT12_LL_[INJ*4+INB]->Integral(2,6):0;
      double SF3 = (totalCR_PTW_HT3_LL_[INJ*4+INB]->Integral(2,6)>0) ? totalCR_MHT_HT3_LL_[INJ*4+INB]->Integral(3,4)/totalCR_PTW_HT3_LL_[INJ*4+INB]->Integral(2,6):0;
      double SF23 = (totalCR_PTW_HT23_LL_[INJ*4+INB]->Integral(4,6)>0) ? totalCR_MHT_HT23_LL_[INJ*4+INB]->Integral(5,6)/totalCR_PTW_HT23_LL_[INJ*4+INB]->Integral(4,6):0;
      if (ibin%6==3) {
  EXTRAP_weight_SF_LL_->SetBinContent(ibin+1, SF12); 
      } else if (ibin%6==4) {
  EXTRAP_weight_SF_LL_->SetBinContent(ibin+1, SF3); 
      } else if (ibin%6==5) {
  EXTRAP_weight_SF_LL_->SetBinContent(ibin+1, SF23); 
      }
    }
  }
  SetBinLabel(EXTRAP_weight_SF_LL_);
  EXTRAP_weight_SF_LL_->Write();
}


  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_MC");
  TDirectory *dPreMC = (TDirectory*)LLoutPutFile->Get("Prediction_MC");
  dPreMC->cd();

  SetBinLabel(totalPred_LL_MC_);
  totalPred_LL_MC_->Write();

  SetBinLabel(totalPredwoIso_LL_MC_);
  totalPredwoIso_LL_MC_->Write();

if(doExtrapolation){
  for (int ibin(0); ibin<avgWeight_LL_MC_->GetNbinsX(); ibin++) {
    EXTRAP_weight_SF_LL_MC_->SetBinError(ibin+1, 0); 
    if (ibin%6 < 3) { // lowest-MHT, use classical prediction
      EXTRAP_weight_SF_LL_MC_->SetBinContent(ibin+1, 1); 
    } else {
      unsigned int INJ(ibin/24); 
      unsigned int INB(ibin);
      if (INB>=24) INB-=24;
      if (INB>=24) INB-=24;
      INB=INB/6;
      //  Double_t ptw_bins[6] = {200, 400, 500, 600, 750, 10000};
      double SF12 = (totalCR_PTW_HT12_LL_MC_[INJ*4+INB]->Integral(2,6)>0) ? totalCR_MHT_HT12_LL_MC_[INJ*4+INB]->Integral(3,4)/totalCR_PTW_HT12_LL_MC_[INJ*4+INB]->Integral(2,6):0;
      double SF3 = (totalCR_PTW_HT3_LL_MC_[INJ*4+INB]->Integral(2,6)>0) ? totalCR_MHT_HT3_LL_MC_[INJ*4+INB]->Integral(3,4)/totalCR_PTW_HT3_LL_MC_[INJ*4+INB]->Integral(2,6):0;
      double SF23 = (totalCR_PTW_HT23_LL_MC_[INJ*4+INB]->Integral(4,6)>0) ? totalCR_MHT_HT23_LL_MC_[INJ*4+INB]->Integral(5,6)/totalCR_PTW_HT23_LL_MC_[INJ*4+INB]->Integral(4,6):0;
      if (ibin%6==3) {
  EXTRAP_weight_SF_LL_MC_->SetBinContent(ibin+1, SF12); 
      } else if (ibin%6==4) {
  EXTRAP_weight_SF_LL_MC_->SetBinContent(ibin+1, SF3); 
      } else if (ibin%6==5) {
  EXTRAP_weight_SF_LL_MC_->SetBinContent(ibin+1, SF23); 
      }
    }
  }
  SetBinLabel(totalPred_EXTRAP_LL_MC_);
  totalPred_EXTRAP_LL_MC_->Write();
}


  std::vector<TH1D*> allUncUp_LL_MC_;
  allUncUp_LL_MC_.push_back(totalPredIsoTrackSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMTWSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredPuritySysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredSingleLepPuritySysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredDiLepFoundSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuIsoSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuRecoSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuAccSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuAccQsquareSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecIsoSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecRecoSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecAccSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecAccQsquareSysUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredIsoTrackStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMTWStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredPurityStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredSingleLepPurityStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredDiLepFoundStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuIsoStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuRecoStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredMuAccStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecIsoStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecRecoStatUp_LL_MC_);
  allUncUp_LL_MC_.push_back(totalPredElecAccStatUp_LL_MC_);

  addUncertainties(totalPropSysUp_LL_MC_, allUncUp_LL_MC_, true);

  std::vector<TH1D*> allUncDown_LL_MC_;
  allUncDown_LL_MC_.push_back(totalPredIsoTrackSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMTWSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredPuritySysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredSingleLepPuritySysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredDiLepFoundSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuIsoSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuRecoSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuAccSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuAccQsquareSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecIsoSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecRecoSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecAccSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecAccQsquareSysDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredIsoTrackStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMTWStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredPurityStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredSingleLepPurityStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredDiLepFoundStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuIsoStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuRecoStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredMuAccStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecIsoStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecRecoStatDown_LL_MC_);
  allUncDown_LL_MC_.push_back(totalPredElecAccStatDown_LL_MC_);

  addUncertainties(totalPropSysDown_LL_MC_, allUncDown_LL_MC_, false);

  
  SaveFraction(totalPredIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  /*  SaveFraction(totalPredMuIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredMuIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredElecIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredElecIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredPionIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredPionIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  */  SaveFraction(totalPredMTWSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMTWSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredSingleLepPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredSingleLepPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredDiLepFoundSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredDiLepFoundSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);

  SaveFraction(totalPredIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  /*  SaveFraction(totalPredMuIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredMuIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredElecIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredElecIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredPionIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
      SaveFraction(totalPredPionIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  */  SaveFraction(totalPredMTWStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMTWStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredSingleLepPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredSingleLepPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredDiLepFoundStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredDiLepFoundStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredMuAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
  SaveFraction(totalPredElecAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);

  for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
    totalPredNonClosureUp_LL_MC_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
    totalPredNonClosureDown_LL_MC_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
  }
  SetBinLabel(totalPredNonClosureUp_LL_MC_);
  totalPredNonClosureUp_LL_MC_->Write();
  SetBinLabel(totalPredNonClosureDown_LL_MC_);
  totalPredNonClosureDown_LL_MC_->Write();

  SetBinLabel(totalCS_LL_MC_);
  totalCS_LL_MC_->Write();
  SetBinLabel(nEvtsCS_LL_MC_);
  nEvtsCS_LL_MC_->Write();

  SetBinLabel(avgWeight_LL_MC_);
  avgWeight_LL_MC_->Write();
  SetBinLabel( EXTRAP_weight_SF_LL_MC_);
  EXTRAP_weight_SF_LL_MC_->Write();
  
  LLoutPutFile->cd();
  LLoutPutFile->mkdir("AvgWeight_MC");
  TDirectory *dAvgWeight = (TDirectory*)LLoutPutFile->Get("AvgWeight_MC");
  dAvgWeight->cd();

  SetBinLabel(avgWeight_LL_MC_);
  avgWeight_LL_MC_->Write();
  SetBinLabel(EXTRAP_weight_SF_LL_MC_);
  EXTRAP_weight_SF_LL_MC_->Write();
  
  avgWeight_HT_LL_MC_->Write();
  avgWeight_MHT_LL_MC_->Write();
  avgWeight_NJets_LL_MC_->Write();
  avgWeight_BTags_LL_MC_->Write();

  avgWeight_MHT_HT500_800_LL_MC_->Write();
  avgWeight_MHT_HT800_1200_LL_MC_->Write();
  avgWeight_MHT_HT1200_Inf_LL_MC_->Write();

  avgWeight_MHT_HT300_500_NJets34_LL_MC_->Write();
  avgWeight_MHT_HT500_800_NJets34_LL_MC_->Write();
  avgWeight_MHT_HT800_1200_NJets34_LL_MC_->Write();
  avgWeight_MHT_HT1200_Inf_NJets34_LL_MC_->Write();

  avgWeight_MHT_HT300_500_NJets56_LL_MC_->Write();
  avgWeight_MHT_HT500_800_NJets56_LL_MC_->Write();
  avgWeight_MHT_HT800_1200_NJets56_LL_MC_->Write();
  avgWeight_MHT_HT1200_Inf_NJets56_LL_MC_->Write();

  avgWeight_MHT_HT300_500_NJets7Inf_LL_MC_->Write();
  avgWeight_MHT_HT500_800_NJets7Inf_LL_MC_->Write();
  avgWeight_MHT_HT800_1200_NJets7Inf_LL_MC_->Write();
  avgWeight_MHT_HT1200_Inf_NJets7Inf_LL_MC_->Write();

  SavePlot(avgWeight_MHT_HT300_500_NJets34_LL_MC_);
  SavePlot(avgWeight_MHT_HT500_800_NJets34_LL_MC_);
  SavePlot(avgWeight_MHT_HT800_1200_NJets34_LL_MC_);
  SavePlot(avgWeight_MHT_HT1200_Inf_NJets34_LL_MC_);

  SavePlot(avgWeight_MHT_HT300_500_NJets56_LL_MC_);
  SavePlot(avgWeight_MHT_HT500_800_NJets56_LL_MC_);
  SavePlot(avgWeight_MHT_HT800_1200_NJets56_LL_MC_);
  SavePlot(avgWeight_MHT_HT1200_Inf_NJets56_LL_MC_);

  SavePlot(avgWeight_MHT_HT300_500_NJets7Inf_LL_MC_);
  SavePlot(avgWeight_MHT_HT500_800_NJets7Inf_LL_MC_);
  SavePlot(avgWeight_MHT_HT800_1200_NJets7Inf_LL_MC_);
  SavePlot(avgWeight_MHT_HT1200_Inf_NJets7Inf_LL_MC_);

  TH1D* PredOverCS_LL_MC = (TH1D*) totalPred_LL_MC_->Clone("PredOverCS_LL_MC");
  PredOverCS_LL_MC->Divide(totalCS_LL_MC_);
  PredOverCS_LL_MC->SetTitle("Prediction / CS (=0L/1L)");
  PredOverCS_LL_MC->Write();


  if(doMergedHistograms){
    LLoutPutFile->cd();
    LLoutPutFile->mkdir("Readiness");
    TDirectory *dReadiness = (TDirectory*)LLoutPutFile->Get("Readiness");
    dReadiness->cd();

    hPredAllBins->Write();
    hAvgWeightAllBins->Write();
    hPredHTMHT0b->Write();
    hPredHTMHTwb->Write();    
    hAvgWeightHTMHT0b->Write();
    hAvgWeightHTMHTwb->Write();
    hPredNJetBins->Write();
    hAvgWeightNJetBins->Write();
    hPredNbBins->Write();
    hAvgWeightNbBins->Write();

    LLoutPutFile->cd();
    LLoutPutFile->mkdir("Readiness_additional");
    TDirectory *Readiness_additional = (TDirectory*)LLoutPutFile->Get("Readiness_additional");
    Readiness_additional->cd();

    hExpAllBins->Write();
    hExpHTMHT0b->Write();
    hExpHTMHTwb->Write();
    hExpNJetBins->Write();
    hExpNbBins->Write();

    TH1D *hDataMCAllBins = (TH1D*) hPredAllBins->Clone("hDataMCAllBins");
    hDataMCAllBins->Divide(hExpAllBins);
    hDataMCAllBins->SetTitle("Prediction / Expectation");
    hDataMCAllBins->Write();

    TH1D *hDataMCHTMHT0b = (TH1D*) hPredHTMHT0b->Clone("hDataMCHTMHT0b");
    hDataMCHTMHT0b->Divide(hExpHTMHT0b);
    hDataMCHTMHT0b->SetTitle("Prediction / Expectation");
    hDataMCHTMHT0b->Write();

    TH1D *hDataMCHTMHTwb = (TH1D*) hPredHTMHTwb->Clone("hDataMCHTMHTwb");
    hDataMCHTMHTwb->Divide(hExpHTMHTwb);
    hDataMCHTMHTwb->SetTitle("Prediction / Expectation");
    hDataMCHTMHTwb->Write();

    TH1D *hDataMCNJetBins = (TH1D*) hPredNJetBins->Clone("hDataMCNJetBins");
    hDataMCNJetBins->Divide(hExpNJetBins);
    hDataMCNJetBins->SetTitle("Prediction / Expectation");
    hDataMCNJetBins->Write();

    TH1D *hDataMCNbBins = (TH1D*) hPredNbBins->Clone("hDataMCNbBins");
    hDataMCNbBins->Divide(hExpNbBins);
    hDataMCNbBins->SetTitle("Prediction / Expectation");
    hDataMCNbBins->Write();  
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_Data_MC");
  TDirectory *dDataMC = (TDirectory*)LLoutPutFile->Get("Prediction_Data_MC");
  dDataMC->cd();

  TH1D *Prediction_Data_MC = (TH1D*) totalPred_LL_->Clone("Prediction_Data_MC");
  Prediction_Data_MC->Divide(totalPred_LL_MC_);
  Prediction_Data_MC->SetTitle("Prediction Data / Prediction MC");
  SetBinLabel(Prediction_Data_MC);
  Prediction_Data_MC->Write();


  LLoutPutFile->cd();
  LLoutPutFile->mkdir("AdditionalContent");
  TDirectory *dAdd = (TDirectory*)LLoutPutFile->Get("AdditionalContent");
  dAdd->cd();

  SaveFraction(totalPropSysUp_LL_MC_, totalPred_LL_MC_, dAdd);
  SaveFraction(totalPropSysDown_LL_MC_, totalPred_LL_MC_, dAdd);
  SaveFraction(totalPropSysUp_LL_, totalPred_LL_, dAdd);
  SaveFraction(totalPropSysDown_LL_, totalPred_LL_, dAdd);

  LLoutPutFile->Close();

  double LLexpErr = 0;
  double LLexp = totalExp_LL_->IntegralAndError(1, nSearchBinsTotal, LLexpErr);
  double LLpreErr = 0;
  double LLpre = totalPred_LL_->IntegralAndError(1, nSearchBinsTotal, LLpreErr);

  //printf("Total: & & & & & & & $%3.3f\\pm$%3.3f & $%3.3f\\pm$%3.3f \\\\\n", LLexp, LLexpErr, LLpre, LLpreErr);

  //if(!useMCForDataTree && InputPath_Prediction_Data == InputPath_Prediction) std::cout<<"ATTENTION: Full MC statistics used to do prediction! Only approx. stat. unc. (~sqrt(n)) shown on prediction!"<<std::endl;

  if(InputPath_Prediction_Data != InputPath_Prediction) printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & CS\\_data & avg. weight (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");
  else printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");
/*
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
    printf("%3.3f & ", totalCS_LL_MC_->GetBinContent(i));
    //printf("%3.3f (%1.0f) & ", totalCS_LL_MC_->GetBinContent(i), nEvtsCS_LL_MC_->GetBinContent(i));
 
    // Average weight per Bin (MC)
    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", avgWeight_LL_MC_->GetBinContent(i), avgWeight_LL_MC_->GetBinError(i), (totalPropSysUp_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPropSysDown_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPredNonClosureUp_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPredNonClosureDown_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i));
    
    // CS events (data)
    if(InputPath_Prediction_Data != InputPath_Prediction) printf("%1.0f & ", totalCS_LL_->GetBinContent(i));

    // Average weight per Bin (data)
    //if(InputPath_Prediction_Data != InputPath_Prediction) printf("$%3.3f\\pm%3.3f^{+%3.3f}_{-%3.3f}{}^{+%3.3f}_{-%3.3f}{}^{+%3.3f}_{-%3.3f}$ & ", avgWeight_LL_->GetBinContent(i), avgWeight_LL_->GetBinError(i), avgWeightStatUp_LL_->GetBinContent(i), avgWeightStatDown_LL_->GetBinContent(i), avgWeightSysUp_LL_->GetBinContent(i), avgWeightSysDown_LL_->GetBinContent(i), avgWeightNonClosureUp_LL_->GetBinContent(i), avgWeightNonClosureDown_LL_->GetBinContent(i));

    // Prediction
    // Correct estimate of stat. uncertainty on prediction only possible if data is used or limited MC statistics (e.g. number of events corresponding to 3fb-1)
    // For approximation of stat. uncertainty on prediction using full MC statistics use:
    //if(!useMCForDataTree && InputPath_Prediction_Data == InputPath_Prediction && approxStatUncertainty) if(totalCS_LL_->GetBinContent(i)>0.00001) totalPred_LL_->SetBinError(i, sqrt(totalPred_LL_->GetBinContent(i)*totalPred_LL_->GetBinContent(i)/totalCS_LL_->GetBinContent(i)));

    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", totalPred_LL_->GetBinContent(i), totalPred_LL_->GetBinError(i), (totalPropSysUp_LL_MC_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPropSysDown_LL_MC_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPredNonClosureUp_LL_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPredNonClosureDown_LL_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i));

    // Expectation
    printf("$%3.3f\\pm%3.3f$ \\\\\n", totalExp_LL_->GetBinContent(i), totalExp_LL_->GetBinError(i));

  }
*/
}


void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder) // prediction over expectation
{
  Folder->cd();

  prediction->Write(prediction->GetName(),TObject::kOverwrite);
  expectation->Write(expectation->GetName(),TObject::kOverwrite);

  TString title = prediction->GetTitle();
  title +="_closure";
  TH1D* Closure = (TH1D*) prediction->Clone(title);
  Closure->Divide(prediction,expectation,1,1,"B");
  //  title = "#mu & e Control-Sample Ratio in Search Bins; Search bins; #mu / e CS";
  Closure->SetTitle(title);
  title = prediction->GetName();
  title+="_closure";
  Closure->SetName(title);
  
  Closure->Write();
}

void SavePlot(TProfile* plot){

  TString name(plot->GetName());
  plot->GetXaxis()->SetTitle("MHT");

  gROOT->SetBatch(true);
  TCanvas *c1 = new TCanvas(name,name,1);
  c1->cd();

  gStyle->SetOptStat(0);
  plot->Draw();
  c1->SaveAs(TString("Teruki/")+name+TString(".pdf"));

  gROOT->SetBatch(false);
}

UShort_t getMergedBinQCD(UShort_t BinQCD, Int_t NJets){
  if(BinQCD > 900) return 900;
  if(NJets < 4) return 900;

  UShort_t bin = 0;

  switch(NJets){
  case 4:
    bin = BinQCD % 11;
    if(bin == 0) bin = 11;
    break;
  case 5:
    bin = BinQCD % 11 + 11;
    if(bin == 11) bin = 22;
    break;
  case 6:
    bin = BinQCD % 11 + 22;
    if(bin == 22) bin = 33;
    break;
  case 7:
  case 8:
    bin = BinQCD % 11 + 33;
    if(bin == 33) bin = 44;
    break;
  default:
    bin = BinQCD % 11 + 44;
    if(bin == 44) bin = 55;
    break;
  }

  return bin;
}

UShort_t getHTMHTBox(Double_t HT, Double_t MHT){
  if(MHT < 200 || HT < 500) return -1;
  if(MHT >= 750 && HT < 800) return -1;

  if(MHT < 500){
    if(HT < 800) return 1;
    if(HT < 1200) return 2;
    else return 3;
  }else if(MHT < 750){
    if(HT < 1200) return 4;
    else return 5;
  }else{
    return 6;
  }

  return -1; // Should not be reached
}

void SetBinLabel(TH1D* hist){
  if(hist->GetNbinsX()==72)
    for(int nji = 0; nji<3; ++nji){
      for(int nbi = 0; nbi<4; ++nbi){
        for(int hti = 0; hti<6; ++hti){
          int mhti =0;
          if(hti >=0 && hti <=2) mhti = 0;
          else if(hti >=3 && hti <=4) mhti = 1;
          else mhti = 2;
          char binlabel[100];
          int bi = nji * 24 + nbi * 6 + hti + 1;
          //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
          sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
          hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
        }
      }
    }

  if(hist->GetNbinsX()==220)
    for(int nji = 0; nji<5; ++nji){
      for(int nbi = 0; nbi<4; ++nbi){
        for(int mhti = 0; mhti<4; ++mhti){
          int htiMin = 0;
          if(mhti==3) htiMin = 1;
          for(int hti = htiMin; hti<3; ++hti){
            char binlabel[100];
            int bi = nji * 44 + nbi * 11 + mhti * 3 + hti + 1;
            if(htiMin==1) bi = nji * 44 + nbi * 11 + mhti * 3 + hti;
            //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
            sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
            hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
          }
        }
      }
    }

  if(hist->GetNbinsX()==190){
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
  }
  
  if(hist->GetNbinsX()==72 || hist->GetNbinsX()==220 || hist->GetNbinsX()==190) hist -> GetXaxis() -> LabelsOption("v");
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

void addUncertainties(TH1D* total, std::vector<TH1D*> uncertainties, bool upperUnc){
  for(int i = 0; i <= total->GetNbinsX(); i++){
    Double_t sumSq = 0.;

    for (std::vector<TH1D*>::iterator it = uncertainties.begin() ; it != uncertainties.end(); ++it){
      sumSq += (*it)->GetBinContent(i) * (*it)->GetBinContent(i);
    }

    if(upperUnc) total->SetBinContent(i, std::sqrt(sumSq));
    else total->SetBinContent(i, -std::sqrt(sumSq));
  }

}
