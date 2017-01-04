#ifndef Prediction_isoTrackFact_h
#define Prediction_isoTrackFact_h

#include "LLTools.h"
#include "THEff.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include <fstream>
#include "isr_corrections/ISRCorrector.h"
#include "btag/BTagCorrector.h"
#include "eventFilter/EventListFilter.h"


////////////////////////
//////// Options
//////// SET DEPENDING ON SAMPLE: data, MC, signal!
///////////////////////

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;  //<-check------------------------

const bool runOnData = false;  //<-check------------------------
const bool runOnStandardModelMC = true;  //<-check------------------------
const bool runOnSignalMC = false;  //<-check------------------------

// Only needed if running on full nTuples not on Skims (bTag reweighting)
// Does not matter for Data
const bool runOnNtuples = false;
const string path_toSkims("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/SLe/tree_");

// Useful for T2tt corridor studies
const bool useGenHTMHT = false;

// Do top-pt reweightung
const bool topPTreweight = false;

// Fill event seperately to the tree for each bTag multiplicity (size x4!). Mainly useful for plotting
// Not fully implemented yet! Only working for CS not for prediction!
const bool fillEventSeperateBTags = false;

// PU
const TString path_puHist("PU/PileupHistograms_0721_63mb_pm5.root");
// bTag corrections
const string path_bTagCalib("btag/CSVv2_ichep.csv");
const string path_bTagCalibFastSim("btag/CSV_13TEV_Combined_20_11_2015.csv");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ISR corrections: NOT RECOMMENDED FOR JAMBOREE -> Might change for Moriond! Just uncomment in Prediction::Init(Tree*) of this file
const TString path_ISRcorr("isr_corrections/ISRWeights.root");
// Signal x-sec: "dict_xsec.txt" for gluino pair prod; "dict_xsec_T2.txt" for (anti)stop pair prod.
const string path_xsecT1T5("xsec/dict_xsec.txt");
const string path_xsecT2("xsec/dict_xsec_T2.txt");

const TString path_elecID("SFs/scaleFactors_electrons.root");
const TString hist_elecID("GsfElectronToVeto");
const TString path_elecIso("SFs/scaleFactors_electrons.root");
const TString hist_elecIso("MVAVLooseElectronToMini");

const TString path_muID("SFs/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root");
const TString hist_muID("pt_abseta_PLOT_pair_probeMultiplicity_bin0");
// for muons: add 3% systematic to uncertainty -> set boolean to true in GetSF function
const TString path_muIso("SFs/TnP_MuonID_NUM_MiniIsoTight_DENOM_MediumID_VAR_map_pt_eta.root");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// muIso: still binned in pt/eta since this was recommended! Has to be changed for Moriond (also in Prediction.C when getting the uncertainties)!
const TString hist_muIso("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_Medium2016_pass");

//Uncertainty maps
const TString path_AccPDF_up("AcceptanceUncertainty/PDFuncertainty_up.root");
const TString path_AccPDF_down("AcceptanceUncertainty/PDFuncertainty_down.root");
const TString path_AccQ2_up("AcceptanceUncertainty/Q2uncertainty_up.root");
const TString path_AccQ2_down("AcceptanceUncertainty/Q2uncertainty_down.root");
const TString path_MTWunc("MTWUncertainty/MTWuncertainty.root");
const TString path_isoTrackunc("IsoTrackUncertainty/NJets_uncertainty.root");

// Muon tracking inefficiency
const TString path_muonTrk("SFs/general_tracks_and_early_general_tracks_corr_ratio.root");
const TString hist_muonTrkHighPt("mutrksfptg10");
const TString hist_muonTrkLowPt("mutrksfptl10");

// Electron tracking inefficiency
const TString path_elecTrk("SFs/egammaEffi.txt_SF2D.root");
const TString hist_elecTrk("EGamma_SF2D");


////////////////////////
//////// Usually don't have to be changed
///////////////////////

// ScaleFactors from SUSY lepton SG groups:
const bool useSFs = true;
// Apply corrections on ID/Iso based on SFs. Used to correct for systematic offsets
const bool correctElectronID = true;
const bool correctElectronIso = false;
const bool correctMuonID = true;
const bool correctMuonIso = false;

// Correction for tracking inefficiency due to high luminosity (on muon ID efficiency)
const bool doTrackingCorrection = true;

// Flat uncertainties for acceptance efficiency. Just for testing
const bool useFlatAccUnc = false;
const bool useFlatMTWUnc = false;
const bool useFlatIsoTrackUnc = false;


// useAsymmErrors = true; use assym. uncertainties in efficiency histograms
const bool useAsymmErrors = true;
const bool applyFilters_=true;


////////////////////////
//////// Don't change anything below
///////////////////////

const double minHT_=300;
//const double minHT_=250;
const double minMHT_=250;
const double minNJets_=1.5;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;

// Directly use TAP efficiencies: NOT IMPLEMENTED!
const bool UseTagAndProbeEffIso_=false; // warning overriges all other choices for isolation efficiency
const bool UseTagAndProbeEffReco_=false; // warning overriges all other choices for reconstruction efficiency

// uncertainties
const double muIsoTrackUncertaintyUp_ = 0.08; 
const double muIsoTrackUncertaintyDown_ = 0.08; 
const double elecIsoTrackUncertaintyUp_ = 0.15; 
const double elecIsoTrackUncertaintyDown_ = 0.15; 
const double pionIsoTrackUncertaintyUp_ = 0.10; 
const double pionIsoTrackUncertaintyDown_ = 0.10; 
const double isoTrackUncertaintyUp_ = 0.10; // inclusive Isotracks (if used)
const double isoTrackUncertaintyDown_ = 0.10; // inclusive Isotracks (if used)

const double MuMTWUncertaintyUp_ = 0.05;  //5
const double MuMTWUncertaintyDown_ = 0.05;
const double ElecMTWUncertaintyUp_ = 0.05;
const double ElecMTWUncertaintyDown_ = 0.05;

const double ElecPurityUncertaintyUp_ = 0.20;
const double ElecPurityUncertaintyDown_ = 0.20;
const double MuPurityUncertaintyUp_ = 0.20;
const double MuPurityUncertaintyDown_ = 0.20;

const double MuSingleLepPurityUp_ = 0.50;
const double MuSingleLepPurityDown_ = 0.50;
const double ElecSingleLepPurityUp_ = 0.50;
const double ElecSingleLepPurityDown_ = 0.50;

const double MuDiLepSRUp_ = 0.50;
const double MuDiLepSRDown_ = 0.50;
const double ElecDiLepSRUp_ = 0.50;
const double ElecDiLepSRDown_ = 0.50;

const double MuAccUncertaintyUp_LowMHT_ = 0.007;  // pdf //  MHT < 500
const double MuAccUncertaintyDown_LowMHT_ = 0.007;  // pdf
const double ElecAccUncertaintyUp_LowMHT_ = 0.007;  // pdf
const double ElecAccUncertaintyDown_LowMHT_ = 0.007;  // pdf
const double MuAccUncertaintyUp_HighMHT_ = 0.019;  // pdf // MHT > 500
const double MuAccUncertaintyDown_HighMHT_ = 0.019;  // pdf
const double ElecAccUncertaintyUp_HighMHT_ = 0.019;  // pdf
const double ElecAccUncertaintyDown_HighMHT_ = 0.019;  // pdf
const double MuAccQsquareUncertaintyUp_ = 0.007;  // Q^2
const double MuAccQsquareUncertaintyDown_ = 0.007;  // Q^2
const double ElecAccQsquareUncertaintyUp_ = 0.007;  // Q^2
const double ElecAccQsquareUncertaintyDown_ = 0.007;  // Q^2

const double MuRecoUncertaintyUp_ = 0.05; 
const double MuRecoUncertaintyDown_ = 0.05;  
const double ElecRecoUncertaintyUp_ = 0.05;  
const double ElecRecoUncertaintyDown_ = 0.05;  
const double MuIsoUncertaintyUp_ = 0.05;  
const double MuIsoUncertaintyDown_ = 0.05;  
const double ElecIsoUncertaintyUp_ = 0.05;  
const double ElecIsoUncertaintyDown_ = 0.05;  


class Prediction_isoTrackFact : public TSelector {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  void resetValues();
  bool FiltersPass();
  double getEff(TH2F* effTH2F, double xValue, double yValue);
  double getEff(TH1F* effTH2F, double xValue);
  double MuActivity(double muEta, double muPhi, unsigned int method);
  double ElecActivity( double elecEta, double elecPhi, unsigned int method);
  double doMuUnc(double relUnc, std::string type);
  double doElecUnc(double relUnc, std::string type);

  std::vector <int> GetPTWBin(int, double, double);

  
  //Options
  bool useTrigger = false;
  bool useTriggerEffWeight = false;
  bool doPUreweighting = false;
  bool doBTagCorr = false;
  bool doISRcorr = false; 
  bool useFilterData = false;

  // output variables
  TTree *tPrediction_ = 0;

  std::string fname; // for fetching file name
  TString fileName;
  Double_t HTgen_cut = 0;
  TFile* pufile = 0;
  TH1* puhist = 0;

  TH1D * h_muTrkLowPtSF = 0;
  TH1D * h_muTrkHighPtSF = 0;
  TH2F * h_elecTrkSF = 0;


  std::vector<std::pair<double, double>> xsecsT1T5;
  std::vector<std::pair<double, double>> xsecsT2;
  std::vector<std::pair<double, double>> *xsecs = 0;


    //open skim file as skimfile
  TH1* h_njetsisr = 0;
  double nEvtsTotal;
  Double_t xsec;
  ISRCorrector *isrcorr = 0;
  TFile* isrfile = 0;
  TH1* h_isr = 0;
  Double_t w_isr;
  Double_t w_pu;
  BTagCorrector *btagcorr = 0;
  std::vector<double> bTagProb;
  Double_t        Weight_bTagCorr;
  Double_t        bTagCorr_cut;
  Double_t		  recoSF;
  Double_t		  isoSF;
  Double_t		  trackingSF;
  Double_t      WeightCorr;
  Double_t      WeightTrackingCorr;
  Double_t		  topPtSF;
  std::vector<double> topPt;

  TH2F* h_muIDSF = 0;
  TH2F* h_muIsoSF = 0;
  TH2F* h_elecIsoSF = 0;
  TH2F* h_elecIDSF = 0;

  std::vector<TH2D*> h_muAccPDF_up;
  std::vector<TH2D*> h_elecAccPDF_up;
  std::vector<TH2D*> h_muAccPDF_down;
  std::vector<TH2D*> h_elecAccPDF_down;
  std::vector<TH2D*> h_muAccQ2_up;
  std::vector<TH2D*> h_muAccQ2_down;
  std::vector<TH2D*> h_elecAccQ2_up;
  std::vector<TH2D*> h_elecAccQ2_down;
  std::vector<TH2D*> h_muMTW_up;
  std::vector<TH2D*> h_muMTW_down;
  std::vector<TH2D*> h_elecMTW_up;
  std::vector<TH2D*> h_elecMTW_down;
  TH1D* h_muIsoTrack_NJetsunc = 0;
  TH1D* h_elecIsoTrack_NJetsunc = 0;
  TH1D* h_pionIsoTrack_NJetsunc = 0;


  TString treeName = " ";


  SearchBins *SearchBins_ =0;
  SearchBins *SearchBinsQCD_ =0;
  SearchBins *SearchBinsEff_ =0;

  Int_t           isoTracksNum;
  UShort_t JetsNum_;
  UShort_t MuonsNoIsoNum_, MuonsNum_;
  UShort_t ElectronsNoIsoNum_, ElectronsNum_;
  Float_t MuonsPt_, MuonsEta_;
  Float_t ElectronsPt_, ElectronsEta_;
  Float_t mtw;
  Float_t muPurityEff_;
  Float_t muMTWEff_, elecMTWEff_, mtwCorrectedWeight_;
  Float_t muDiLepCREff_, mtwDiLepCorrectedWeight_;
  Float_t muIsoEff_, muIsoWeight_;
  Float_t muRecoEff_, muRecoWeight_;
  Float_t muAccEff_, muAccWeight_;
  Float_t muTotalWeight_, totalMuons_;
  Float_t elecPurityEff_, purityCorrectedWeight_, elecDiLepCREff_;
  Float_t elecIsoEff_, elecIsoWeight_;
  Float_t elecRecoEff_, elecRecoWeight_;
  Float_t elecAccEff_, elecAccWeight_;
  Float_t elecTotalWeight_, totalElectrons_;
  Float_t muDiLepSREff_, elecDiLepSREff_;
  Float_t muDiLepSRwoVetoEff_, elecDiLepSRwoVetoEff_;
  Float_t diLepLostWeight_;
  Float_t diLepLostVetoWeight_;
  Float_t isotrkMuAccEff_;
  Float_t muIsotrkMuAccEff_,elecIsotrkMuAccEff_,pionIsotrkMuAccEff_;
  Float_t isotrkMuIDEff_;
  Float_t muIsotrkMuIDEff_,elecIsotrkMuIDEff_,pionIsotrkMuIDEff_;
  Float_t isotrkMuIsoEff_;
  Float_t muIsotrkMuIsoEff_,elecIsotrkMuIsoEff_,pionIsotrkMuIsoEff_;
  Float_t isotrkElecAccEff_;
  Float_t muIsotrkElecAccEff_,elecIsotrkElecAccEff_,pionIsotrkElecAccEff_;
  Float_t isotrkElecIDEff_;
  Float_t muIsotrkElecIDEff_,elecIsotrkElecIDEff_,pionIsotrkElecIDEff_;
  Float_t isotrkElecIsoEff_;
  Float_t muIsotrkElecIsoEff_,elecIsotrkElecIsoEff_,pionIsotrkElecIsoEff_;

  // Uncertainties
  Float_t isoTrackMuAccStatUp;
  Float_t isoTrackMuAccStatDown;
  Float_t isoTrackMuIDStatUp;
  Float_t isoTrackMuIDStatDown;
  Float_t isoTrackMuIsoStatUp;
  Float_t isoTrackMuIsoStatDown;
  Float_t isoTrackElecAccStatUp;
  Float_t isoTrackElecAccStatDown;
  Float_t isoTrackElecIDStatUp;
  Float_t isoTrackElecIDStatDown;
  Float_t isoTrackElecIsoStatUp;
  Float_t isoTrackElecIsoStatDown;
  Float_t MTWStatUp;
  Float_t MTWStatDown;
  Float_t purityStatUp;
  Float_t purityStatDown;
  Float_t singleLepPurityStatUp;
  Float_t singleLepPurityStatDown;
  Float_t diLepSRStatUp;
  Float_t diLepSRStatDown;
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

  Float_t isoTrackMuAccSysUp;
  Float_t isoTrackMuAccSysDown;
  Float_t isoTrackMuIDSysUp;
  Float_t isoTrackMuIDSysDown;
  Float_t isoTrackMuIsoSysUp;
  Float_t isoTrackMuIsoSysDown;
  Float_t isoTrackElecAccSysUp;
  Float_t isoTrackElecAccSysDown;
  Float_t isoTrackElecIDSysUp;
  Float_t isoTrackElecIDSysDown;
  Float_t isoTrackElecIsoSysUp;
  Float_t isoTrackElecIsoSysDown;
  Float_t MTWSysUp;
  Float_t MTWSysDown;
  Float_t puritySysUp;
  Float_t puritySysDown;
  Float_t singleLepPuritySysUp;
  Float_t singleLepPuritySysDown;
  Float_t diLepSRSysUp;
  Float_t diLepSRSysDown;
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

  effVec muPurityEffVec_;
  effVec muMTWEffVec_, elecMTWEffVec_;
  effVec muDiLepCREffVec_;
  effVec muIsoEffVec_;
  effVec muRecoEffVec_;
  effVec muAccEffVec_;
  effVec elecPurityEffVec_, elecDiLepCREffVec_;
  effVec elecIsoEffVec_;
  effVec elecRecoEffVec_;
  effVec elecAccEffVec_;
  effVec muDiLepSREffVec_, elecDiLepSREffVec_;
  effVec muDiLepSRwoVetoEffVec_, elecDiLepSRwoVetoEffVec_;
  effVec isotrkMuAccEffVec_;
  effVec muIsotrkMuAccEffVec_,elecIsotrkMuAccEffVec_,pionIsotrkMuAccEffVec_;
  effVec isotrkMuIDEffVec_;
  effVec muIsotrkMuIDEffVec_,elecIsotrkMuIDEffVec_,pionIsotrkMuIDEffVec_;
  effVec isotrkMuIsoEffVec_;
  effVec muIsotrkMuIsoEffVec_,elecIsotrkMuIsoEffVec_,pionIsotrkMuIsoEffVec_;
  effVec isotrkElecAccEffVec_;
  effVec muIsotrkElecAccEffVec_,elecIsotrkElecAccEffVec_,pionIsotrkElecAccEffVec_;
  effVec isotrkElecIDEffVec_;
  effVec muIsotrkElecIDEffVec_,elecIsotrkElecIDEffVec_,pionIsotrkElecIDEffVec_;
  effVec isotrkElecIsoEffVec_;
  effVec muIsotrkElecIsoEffVec_,elecIsotrkElecIsoEffVec_,pionIsotrkElecIsoEffVec_;

  
  Float_t totalWeight_, totalWeightDiLep_, totalWeightDiLepIsoTrackReduced_,totalWeightDiLepIsoMuTrackReduced_,totalWeightDiLepIsoElecTrackReduced_,totalWeightDiLepIsoPionTrackReduced_,totalWeightDiLepIsoTrackReducedCombined_;
  std::vector<Float_t> totalWeight_BTags_;
  std::vector<Float_t> totalWeight_BTags_noIsoTrack_;
  Float_t muTotalWeightDiLep_, muTotalWeightDiLepIsoTrackReduced_;
  Float_t elecTotalWeightDiLep_, elecTotalWeightDiLepIsoTrackReduced_;
  std::vector<Float_t>         MuonsPTW;
  std::vector<Float_t>         ElectronsPTW;

  std::vector<int> ptw_bins;
  
  UShort_t Bin_, BinQCD_;
  
  //NEW
  TH1Eff *MuAccSearchBins_=0;
  TH1Eff *ElecAccSearchBins_=0;
  TH1Eff *MuMTWSearchBins_=0;
  TH1Eff *ElecMTWSearchBins_=0;
  TH1Eff *IsoTrackVetoSearchBins_=0;
  TH1Eff *MuIsoTrackVetoSearchBins_=0;
  TH1Eff *ElecIsoTrackVetoSearchBins_=0;
  TH1Eff *PionIsoTrackVetoSearchBins_=0;
  TH1Eff *MuDiLepCRSearchBins_=0;
  TH1Eff *ElecDiLepCRSearchBins_=0;
  
  // Effiecineices
  TH1Eff *MuMTWNJets=0;
  TH2Eff *MuMTWHTNJets_=0;
  TH2Eff *MuMTWMHTNJets_=0;
  TH2Eff *MuMTWHTMHT_=0;
  TH2Eff *MuMTWHTMHT_NJets24_=0;
  TH2Eff *MuMTWHTMHT_NJets56_=0;
  TH2Eff *MuMTWHTMHT_NJets7Inf_=0;
  TH2Eff *MuMTWHTMHT_NJets2_=0;
  TH2Eff *MuMTWHTMHT_NJets3_=0;
  TH2Eff *MuMTWHTMHT_NJets4_=0;
  TH2Eff *MuMTWHTMHT_NJets5_=0;
  TH2Eff *MuMTWHTMHT_NJets6_=0;
  TH2Eff *MuMTWHTMHT_NJets78_=0;
  TH2Eff *MuMTWHTMHT_NJets9Inf_=0;


  TH1Eff *MuDiLepCRNJets_=0;
  TH2Eff *MuDiLepCRMHTNJets_=0;
  TH2Eff *MuDiLepCRNJetsBTags_=0;

  TH2Eff *MuIsoActivityPT_=0;
  TH2Eff *MuRecoActivityPT_=0;
  TH2Eff *MuRecoPTEta_=0;
  TH2Eff *MuPurityMHTNJets_=0; 
  TH2Eff *MuPurityHTMHT_=0; 
  
  TH2Eff *ElecIsoActivityPT_=0;
  TH2Eff *ElecRecoActivityPT_=0;
  TH2Eff *ElecRecoPTEta_=0;

  TH2Eff *ElecPurityMHTNJets_=0;
  TH2Eff *ElecPurityHTMHT_=0; 
  TH1Eff *ElecMTWNJets=0;
  TH2Eff *ElecMTWHTNJets_=0;
  TH2Eff *ElecMTWMHTNJets_=0;
  TH2Eff *ElecMTWHTMHT_=0;
  TH2Eff *ElecMTWHTMHT_NJets24_=0;
  TH2Eff *ElecMTWHTMHT_NJets56_=0;
  TH2Eff *ElecMTWHTMHT_NJets7Inf_=0;
  TH2Eff *ElecMTWHTMHT_NJets2_=0;
  TH2Eff *ElecMTWHTMHT_NJets3_=0;
  TH2Eff *ElecMTWHTMHT_NJets4_=0;
  TH2Eff *ElecMTWHTMHT_NJets5_=0;
  TH2Eff *ElecMTWHTMHT_NJets6_=0;
  TH2Eff *ElecMTWHTMHT_NJets78_=0;
  TH2Eff *ElecMTWHTMHT_NJets9Inf_=0;

  TH1Eff *ElecDiLepCRNJets_=0;
  TH2Eff *ElecDiLepCRMHTNJets_=0;
  TH2Eff *ElecDiLepCRNJetsBTags_=0;

  TH1Eff *MuDiLepSRNJets_=0;
  TH2Eff *MuDiLepSRNJetsBTags_=0;  
  TH1Eff *ElecDiLepSRNJets_=0;
  TH2Eff *ElecDiLepSRNJetsBTags_=0;

  TH1Eff *MuDiLepSRwoVetoNJets_=0;
  TH2Eff *MuDiLepSRwoVetoNJetsBTags_=0;  
  TH1Eff *ElecDiLepSRwoVetoNJets_=0;
  TH2Eff *ElecDiLepSRwoVetoNJetsBTags_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsAcc_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsAcc_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsAcc_=0;
  TH1Eff *IsoTrackVetoSearchBinsAcc_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsIDIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsIDIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsIDIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsIDIso_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsID_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsID_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsID_=0;
  TH1Eff *IsoTrackVetoSearchBinsID_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsIso_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsMuAcc_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsMuAcc_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsMuAcc_=0;
  TH1Eff *IsoTrackVetoSearchBinsMuAcc_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsMuIDIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsMuIDIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsMuIDIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsMuIDIso_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsMuID_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsMuID_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsMuID_=0;
  TH1Eff *IsoTrackVetoSearchBinsMuID_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsMuIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsMuIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsMuIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsMuIso_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsElecAcc_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsElecAcc_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsElecAcc_=0;
  TH1Eff *IsoTrackVetoSearchBinsElecAcc_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsElecIDIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsElecIDIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsElecIDIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsElecIDIso_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsElecID_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsElecID_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsElecID_=0;
  TH1Eff *IsoTrackVetoSearchBinsElecID_=0;

  TH1Eff *MuIsoTrackVetoSearchBinsElecIso_=0;
  TH1Eff *ElecIsoTrackVetoSearchBinsElecIso_=0;
  TH1Eff *PionIsoTrackVetoSearchBinsElecIso_=0;
  TH1Eff *IsoTrackVetoSearchBinsElecIso_=0;


  TH2Eff *MuIsoTrackVetoActivityPtMuIDIso_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtMuIDIso_=0;
  TH2Eff *PionIsoTrackVetoActivityPtMuIDIso_=0;
  TH2Eff *IsoTrackVetoActivityPtMuIDIso_=0;

  TH2Eff *MuIsoTrackVetoActivityPtMuID_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtMuID_=0;
  TH2Eff *PionIsoTrackVetoActivityPtMuID_=0;
  TH2Eff *IsoTrackVetoActivityPtMuID_=0;

  TH2Eff *MuIsoTrackVetoActivityPtMuIso_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtMuIso_=0;
  TH2Eff *PionIsoTrackVetoActivityPtMuIso_=0;
  TH2Eff *IsoTrackVetoActivityPtMuIso_=0;

  TH2Eff *MuIsoTrackVetoActivityPtElecIDIso_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtElecIDIso_=0;
  TH2Eff *PionIsoTrackVetoActivityPtElecIDIso_=0;
  TH2Eff *IsoTrackVetoActivityPtElecIDIso_=0;

  TH2Eff *MuIsoTrackVetoActivityPtElecID_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtElecID_=0;
  TH2Eff *PionIsoTrackVetoActivityPtElecID_=0;
  TH2Eff *IsoTrackVetoActivityPtElecID_=0;

  TH2Eff *MuIsoTrackVetoActivityPtElecIso_=0;
  TH2Eff *ElecIsoTrackVetoActivityPtElecIso_=0;
  TH2Eff *PionIsoTrackVetoActivityPtElecIso_=0;
  TH2Eff *IsoTrackVetoActivityPtElecIso_=0;


  
  // Declaration of leaf types
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  Bool_t           BadChargedCandidateFilter;
  Bool_t           BadPFMuonFilter;
  Int_t           BTags;
  Int_t          CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Int_t           globalTightHalo2016Filter;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  //Bool_t           eeBadSc4Filter;
  std::vector<TLorentzVector> *GenElectrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  Int_t          HBHENoiseFilter;
  Int_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Double_t        GenHT;
  Double_t        GenMHT;
  std::vector<TLorentzVector> *GenJets=0;
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>     *Jets_muonEnergyFraction=0;
  std::vector<double>     *Jets_bDiscriminatorCSV=0;
  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<int>     *Jets_chargedHadronEnergyFraction=0;
  std::vector<bool>    *Jets_HTMask=0;
  Double_t        METPhi;
  Double_t        MET;
  Double_t        PFCaloMETRatio;
  Double_t        MHT;
  Double_t        MHTPhi;
  Int_t           NJets;
  Int_t           NVtx;
  std::vector<TLorentzVector> *ElectronsNoIso=0;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<TLorentzVector> *Muons=0;
  std::vector<TLorentzVector> *MuonsNoIso=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  Double_t        Weight;
  Double_t        puWeight;
  Double_t        madHT;
  Double_t        SusyLSPMass;
  Double_t        SusyMotherMass;
  Double_t        TrueNumInteractions;
  std::vector<double>  *ElectronsNoIso_MT2Activity=0;
  std::vector<double>  *Electrons_MT2Activity=0;
  std::vector<double>  *MuonsNoIso_MT2Activity=0;
  std::vector<double>  *Muons_MT2Activity=0;
  Int_t           NJetsISR;
  vector<TLorentzVector> *GenParticles = 0;
  vector<int>     *GenParticles_PdgId = 0;
  std::vector<double>  *Muons_MTW=0;
  std::vector<double>  *Electrons_MTW=0;
  vector<bool>    *Muons_tightID=0;
  vector<bool>    *Electrons_mediumID=0;
  vector<bool>    *Electrons_tightID=0;



  // List of branches
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_BadChargedCandidateFilter=0;   //!
  TBranch        *b_BadPFMuonFilter=0;   //!
  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!
  TBranch        *b_globalTightHalo2016Filter=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  //TBranch        *b_eeBadSc4Filter=0;   //!
  TBranch        *b_GenElectrons=0;   //!
  TBranch        *b_GenMuons=0;   //!
  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_GenHT=0;   //!
  TBranch        *b_GenMHT=0;   //!
  TBranch        *b_GenJets=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_hadronFlavor=0;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction=0;   //!
  TBranch        *b_Jets_HTMask=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch        *b_PFCaloMETRatio=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_ElectronsNoIso=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_MuonsNoIso=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_puWeight=0;   //!
  TBranch        *b_madHT=0;
  TBranch        *b_SusyLSPMass=0;
  TBranch        *b_SusyMotherMass=0;
  TBranch        *b_TrueNumInteractions=0;
  TBranch        *b_ElectronsNoIso_MT2Activity=0;   //!
  TBranch        *b_Electrons_MT2Activity=0;   //!
  TBranch        *b_Muons_MT2Activity=0;   //!
  TBranch        *b_MuonsNoIso_MT2Activity=0;   //!
  TBranch        *b_NJetsISR=0;
  TBranch        *b_GenParticles=0;
  TBranch        *b_GenParticles_PdgId=0;
  TBranch        *b_Muons_MTW=0;
  TBranch        *b_Electrons_MTW=0;
  TBranch        *b_Muons_tightID=0;   //!
  TBranch        *b_Electrons_mediumID=0;   //!
  TBranch        *b_Electrons_tightID=0;   //!


  
 Prediction_isoTrackFact(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~Prediction_isoTrackFact() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  
  ClassDef(Prediction_isoTrackFact,0);
};

#endif

#ifdef Prediction_isoTrackFact_cxx
void Prediction_isoTrackFact::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);


  ////////////////////////
  //////// Options
  ///////////////////////

  if(!((runOnData && !runOnStandardModelMC && !runOnSignalMC) || (!runOnData && runOnStandardModelMC && !runOnSignalMC) || (!runOnData && !runOnStandardModelMC && runOnSignalMC))){
    fprintf(stderr, "CHECK OPTIONS! EITHER RUN ON DATA, MC, OR SIGNAL!!!");
    return;
  }

  // Seta data specific options, e.g. Trigger
  // Apply trigger
  if(runOnData) useTrigger = true;
  // Apply weights if trigger not simulated
  //if(runOnStandardModelMC) useTriggerEffWeight = true; // not derived yet
  if(runOnSignalMC && !useGenHTMHT) useTriggerEffWeight = true;
  // Do PU reweighting. true for signal scan
  if(runOnSignalMC) doPUreweighting = true;
  //if(runOnStandardModelMC) doPUreweighting = true;
  // bTag corrections. Use for signal scan
  if(!runOnData) doBTagCorr = true;
  // ISR corrections.
  if(runOnSignalMC) doISRcorr = true; //<-check---------------------------------------

  // useFilterData = true; unless you want to run without MET filters
  // useFilterData = false; For FastSim Samples, e.g. Signal Scans! Met filters not simulated
  if(runOnStandardModelMC || runOnData) useFilterData = true;



  ////////////////////////
  //////// End Options
  ///////////////////////


  TChain* temp = (TChain*)fChain;
  std::string infname=temp->GetFile()->GetName();

  TFile* skimfile = temp->GetFile();

  std::string baseName(infname);
  size_t pos=baseName.rfind("/");
  if(pos!=std::string::npos){
    if(pos!=baseName.size()-1){
      baseName.erase(0,pos+1);
    }
  }
  pos=baseName.rfind(".root");
  if(pos!=std::string::npos){
    if(pos!=baseName.size()-1){
      baseName.erase(pos);
    }
  }
 
  fname = baseName+"_Exp.root";

  TString option = GetOption();
  TObjArray *optionArray = option.Tokenize(",");
  fileName = fname.c_str();

  TString fileNameString = "";
  TString HTcutString = "";

  if(!optionArray->IsEmpty()){
    fileNameString = ((TObjString *)(optionArray->At(0)))->String();
    if(optionArray->GetEntries() > 1) HTcutString = ((TObjString *)(optionArray->At(1)))->String();
  }

  fileNameString = fileNameString.Strip(TString::kBoth, ' ').String();
  HTcutString = HTcutString.Strip(TString::kBoth, ' ').String();

  if(fileNameString!="*" && fileNameString!="") fileName = fileNameString;
  if(HTcutString!="" && HTcutString.IsFloat()) HTgen_cut = HTcutString.Atof();

  std::cout << "madHT cut: " << HTgen_cut << std::endl;

  std::cout << "Saving file to: " << fileName << std::endl;

  std::ifstream signal_xsecT1T5(path_xsecT1T5);
  std::string str_xsecT1T5;
  while (std::getline(signal_xsecT1T5, str_xsecT1T5))
  {
    TObjArray *tokens = TString(str_xsecT1T5).Tokenize(",");
    //std::cout<<((TObjString *)(tokens->At(0)))->String()<<"; "<<((TObjString *)(tokens->At(1)))->String()<<";"<<std::endl;
    xsecsT1T5.push_back(std::make_pair(std::atof(((TObjString *)(tokens->At(0)))->String()), std::atof(((TObjString *)(tokens->At(1)))->String())));
  }

  std::ifstream signal_xsecT2(path_xsecT2);
  std::string str_xsecT2;
  while (std::getline(signal_xsecT2, str_xsecT2))
  {
    TObjArray *tokens = TString(str_xsecT2).Tokenize(",");
    //std::cout<<((TObjString *)(tokens->At(0)))->String()<<"; "<<((TObjString *)(tokens->At(1)))->String()<<";"<<std::endl;
    xsecsT2.push_back(std::make_pair(std::atof(((TObjString *)(tokens->At(0)))->String()), std::atof(((TObjString *)(tokens->At(1)))->String())));
  }

  // Open histograms for SFs
  TFile *muIDSF_histFile = TFile::Open(path_muID, "READ");
  h_muIDSF = (TH2F*) muIDSF_histFile->Get(hist_muID)->Clone();

  TFile *muIsoSF_histFile = TFile::Open(path_muIso, "READ");
  h_muIsoSF = (TH2F*) muIsoSF_histFile->Get(hist_muIso)->Clone();

  TFile *elecIDSF_histFile = TFile::Open(path_elecID, "READ");
  h_elecIDSF = (TH2F*) elecIDSF_histFile->Get(hist_elecID)->Clone();

  TFile *elecIsoSF_histFile = TFile::Open(path_elecIso, "READ");
  h_elecIsoSF = (TH2F*) elecIsoSF_histFile->Get(hist_elecIso)->Clone();

  //Open histograms for Acceptance uncertainties
  TFile *accPDF_histFile_up = TFile::Open(path_AccPDF_up, "READ");
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets2")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets3")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets4")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets5")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets6")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets78")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets9Inf")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets2")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets3")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets4")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets5")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets6")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets78")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets9Inf")->Clone());

  TFile *accPDF_histFile_down = TFile::Open(path_AccPDF_down, "READ");
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets2")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets3")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets4")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets5")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets6")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets78")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets9Inf")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets2")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets3")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets4")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets5")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets6")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets78")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets9Inf")->Clone());

  TFile *accQ2_histFile_up = TFile::Open(path_AccQ2_up, "READ");
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets2")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets3")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets4")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets5")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets6")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets78")->Clone());
  h_muAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("MuAccQ2Unc_NJets9Inf")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets2")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets3")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets4")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets5")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets6")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets78")->Clone());
  h_elecAccQ2_up.push_back((TH2D*) accQ2_histFile_up->Get("ElecAccQ2Unc_NJets9Inf")->Clone());

  TFile *accQ2_histFile_down = TFile::Open(path_AccQ2_down, "READ");
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets2")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets3")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets4")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets5")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets6")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets78")->Clone());
  h_muAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("MuAccQ2Unc_NJets9Inf")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets2")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets3")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets4")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets5")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets6")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets78")->Clone());
  h_elecAccQ2_down.push_back((TH2D*) accQ2_histFile_down->Get("ElecAccQ2Unc_NJets9Inf")->Clone());

  TFile *MTWunc_histFile = TFile::Open(path_MTWunc, "READ");
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets2_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets3_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets4_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets5_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets6_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets78_METup")->Clone());
  h_muMTW_up.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets9Inf_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets2_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets3_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets4_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets5_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets6_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets78_METup")->Clone());
  h_elecMTW_up.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets9Inf_METup")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets2_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets3_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets4_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets5_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets6_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets78_METdown")->Clone());
  h_muMTW_down.push_back((TH2D*) MTWunc_histFile->Get("MuMTWHTMHT_NJets9Inf_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets2_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets3_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets4_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets5_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets6_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets78_METdown")->Clone());
  h_elecMTW_down.push_back((TH2D*) MTWunc_histFile->Get("ElecMTWHTMHT_NJets9Inf_METdown")->Clone());

  TFile *isoTrackunc_histFile = TFile::Open(path_isoTrackunc, "READ");
  h_muIsoTrack_NJetsunc = (TH1D*) isoTrackunc_histFile->Get("muon_trkveto_syst")->Clone();
  h_elecIsoTrack_NJetsunc = (TH1D*) isoTrackunc_histFile->Get("electron_trkveto_syst")->Clone();
  h_pionIsoTrack_NJetsunc = (TH1D*) isoTrackunc_histFile->Get("pion_trkveto_syst")->Clone(); 


  TFile *muTrkSF_histFile = TFile::Open(path_muonTrk, "READ");
  h_muTrkLowPtSF = (TH1D*) muTrkSF_histFile->Get(hist_muonTrkLowPt)->Clone();
  h_muTrkHighPtSF = (TH1D*) muTrkSF_histFile->Get(hist_muonTrkHighPt)->Clone();

  TFile *elecTrkSF_histFile = TFile::Open(path_elecTrk, "READ");
  h_elecTrkSF = (TH2F*) elecTrkSF_histFile->Get(hist_elecTrk)->Clone();  

  if(runOnSignalMC){
    // ISR setup
    isrfile = TFile::Open(path_ISRcorr, "READ");
    h_isr = (TH1*)isrfile->Get("isr_weights_central");
  }

  if(doPUreweighting){
    pufile = TFile::Open(path_puHist,"READ");
    puhist = (TH1*)pufile->Get("pu_weights_central");
  }

  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("RunNum", 1);
  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  if(!runOnSignalMC){
    //fChain->SetBranchStatus("CSCTightHaloFilter", 1);
    fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
    fChain->SetBranchStatus("eeBadScFilter", 1);
    //fChain->SetBranchStatus("eeBadSc4Filter", 1);    
    fChain->SetBranchStatus("HBHENoiseFilter", 1);
    fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
    if(runOnData){
      fChain->SetBranchStatus("globalTightHalo2016Filter", 1);
      fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
      fChain->SetBranchStatus("BadPFMuonFilter", 1);
    }
  }
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_HTMask", 1);
  fChain->SetBranchStatus("METPhi", 1);
  fChain->SetBranchStatus("MET", 1);
  fChain->SetBranchStatus("PFCaloMETRatio", 1);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchStatus("MHTPhi", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("ElectronsNoIso", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("MuonsNoIso", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
  if(topPTreweight){
    fChain->SetBranchStatus("GenParticles", 1);
    fChain->SetBranchStatus("GenParticles_PdgId", 1);
    fChain->SetBranchStatus("GenElectrons", 1);
    fChain->SetBranchStatus("GenMuons", 1);
  }  
  

  if(!runOnData){
    fChain->SetBranchStatus("Weight", 1);
    fChain->SetBranchStatus("Jets_hadronFlavor", 1);
    fChain->SetBranchStatus("madHT", 1);
    fChain->SetBranchStatus("TrueNumInteractions", 1);
  } 
  if(runOnSignalMC){
    fChain->SetBranchStatus("SusyLSPMass", 1);
    fChain->SetBranchStatus("SusyMotherMass", 1);
    fChain->SetBranchStatus("NJetsISR", 1);
    fChain->SetBranchStatus("GenJets", 1);
    fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  }

  //if(useGenHTMHT){
  //  fChain->SetBranchStatus("GenHT", 1);
  //  fChain->SetBranchStatus("GenMHT", 1);
  //}

  fChain->SetBranchStatus("ElectronsNoIso_MT2Activity",1);
  fChain->SetBranchStatus("Electrons_MT2Activity", 1);
  fChain->SetBranchStatus("Muons_MT2Activity",1);
  fChain->SetBranchStatus("MuonsNoIso_MT2Activity", 1);
  fChain->SetBranchStatus("Muons_MTW", 1);
  fChain->SetBranchStatus("Electrons_MTW", 1);
  fChain->SetBranchStatus("Muons_tightID", 1);
  fChain->SetBranchStatus("Electrons_mediumID", 1);
  fChain->SetBranchStatus("Electrons_tightID", 1);

  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  if(!runOnSignalMC){
    //fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
    fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
    //fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);    
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
    if(runOnData){
      fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
      fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
      fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
    }
  }
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("ElectronsNoIso", &ElectronsNoIso, &b_ElectronsNoIso);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("MuonsNoIso", &MuonsNoIso, &b_MuonsNoIso);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
  if(topPTreweight){
    fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
    fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
    fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
    fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
  }  
  if(!runOnData){
    fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
    fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
    fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
    fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
  }
  if(runOnSignalMC){
    fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
    fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
    fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
    fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
    fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  }

  //if(useGenHTMHT){
  //  fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
  //  fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
  //}

  fChain->SetBranchAddress("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity, &b_ElectronsNoIso_MT2Activity);
  fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
  fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
  fChain->SetBranchAddress("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity, &b_MuonsNoIso_MT2Activity);
  fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
  fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
  fChain->SetBranchAddress("Muons_tightID", &Muons_tightID, &b_Muons_tightID);
  fChain->SetBranchAddress("Electrons_mediumID", &Electrons_mediumID, &b_Electrons_mediumID);
  fChain->SetBranchAddress("Electrons_tightID", &Electrons_tightID, &b_Electrons_tightID);
}


Bool_t Prediction_isoTrackFact::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

#endif // #ifdef Prediction_isoTrackFact_cxx
