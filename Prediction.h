//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 24 09:51:04 2014 by ROOT version 5.34/04
// from TTree RA2PreSelection/RA2PreSelection
// found on file: /nfs/dust/cms/user/adraeger/CSA2014/mc/wjetHT600-Inf.root
//////////////////////////////////////////////////////////

#ifndef Prediction_h
#define Prediction_h

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
const bool runOnNtuples = true;
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

// CSCTightHaloFilterUpdate from list
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Extract csc2015.tar.gz! Txt file > 100MB!
const string path_evtListFilter("eventFilter/csc2015.txt");

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

//Acceptance uncertainty maps
const TString path_AccPDF_up("AcceptanceUncertainty/PDFuncertainty_up.root");
const TString path_AccPDF_down("AcceptanceUncertainty/PDFuncertainty_down.root");
const TString path_AccQ2("AcceptanceUncertainty/Q2uncertainty.root");

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

// ScaleFactors from SUSY lepton SG groups: presentation from Oct 23 (preliminary!!)
// NOT USED ANYMORE
const bool usePrelimSFs = false;
// Those are the SFs you want! Read from root file
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

// scaleMet = 0: keep things the way they are
// scaleMet = +-: scale MET up/down for MTW calculation (only!) by 30%// NOT USED ANYMORE
const int scaleMet = 0;

// useAsymmErrors = true; use assym. uncertainties in efficiency histograms
const bool useAsymmErrors = true;
const bool applyDiLepCorrection_=true;
const bool applyFilters_=true;


////////////////////////
//////// Don't change anything below
///////////////////////

// Fixed size dimensions of array or collections stored in the TTree if any.
// use gen infomation to fix purityy of muon controlsample
const bool useGenInfoToMatchCSMuonToGen_=0; // changed 20 Nov from 1 to 0
const double maxDeltaRGenToRecoIsoMuon_=0.3;
const double maxDiffPtGenToRecoIsoMuon_=0.3;
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
const double muIsoTrackUncertaintyUp_ = 8; // dummies as long as TAP is not available 20
const double muIsoTrackUncertaintyDown_ = 8; // dummies as long as TAP is not available 20
const double elecIsoTrackUncertaintyUp_ = 15; // dummies as long as TAP is not available 20
const double elecIsoTrackUncertaintyDown_ = 15; // dummies as long as TAP is not available 20
const double pionIsoTrackUncertaintyUp_ = 10; // dummies as long as TAP is not available 20
const double pionIsoTrackUncertaintyDown_ = 10; // dummies as long as TAP is not available 20
const double isoTrackUncertaintyUp_ = 10; // inclusive Isotracks (if used)
const double isoTrackUncertaintyDown_ = 10; // inclusive Isotracks (if used)

const double MuMTWUncertaintyUp_ = 5;  //5
const double MuMTWUncertaintyDown_ = 5;
const double ElecMTWUncertaintyUp_ = 5;
const double ElecMTWUncertaintyDown_ = 5;

const double ElecPurityUncertaintyUp_ = 20; // no purity correction for muCS (>99%)
const double ElecPurityUncertaintyDown_ = 20; // no purity correction for muCS (>99%)

const double MuSingleLepPurityUp_ = 50;
const double MuSingleLepPurityDown_ = 50;
const double ElecSingleLepPurityUp_ = 50;
const double ElecSingleLepPurityDown_ = 50;

const double MuDiLepFoundUp_ = 20;
const double MuDiLepFoundDown_ = 20;
const double ElecDiLepFoundUp_ = 20;
const double ElecDiLepFoundDown_ = 20;

const double MuAccUncertaintyUp_LowMHT_ = 0.7;  // pdf //  MHT < 500
const double MuAccUncertaintyDown_LowMHT_ = 0.7;  // pdf
const double ElecAccUncertaintyUp_LowMHT_ = 0.7;  // pdf
const double ElecAccUncertaintyDown_LowMHT_ = 0.7;  // pdf
const double MuAccUncertaintyUp_HighMHT_ = 1.9;  // pdf // MHT > 500
const double MuAccUncertaintyDown_HighMHT_ = 1.9;  // pdf
const double ElecAccUncertaintyUp_HighMHT_ = 1.9;  // pdf
const double ElecAccUncertaintyDown_HighMHT_ = 1.9;  // pdf
const double MuAccQsquareUncertaintyUp_ = 0.7;  // Q^2
const double MuAccQsquareUncertaintyDown_ = 0.7;  // Q^2
const double ElecAccQsquareUncertaintyUp_ = 0.7;  // Q^2
const double ElecAccQsquareUncertaintyDown_ = 0.7;  // Q^2

const double MuRecoUncertaintyUp_ = 5;  // dummies as long as TAP is not available 10
const double MuRecoUncertaintyDown_ = 5;  // dummies as long as TAP is not available
const double ElecRecoUncertaintyUp_ = 5;  // dummies as long as TAP is not available
const double ElecRecoUncertaintyDown_ = 5;  // dummies as long as TAP is not available
const double MuIsoUncertaintyUp_ = 5;  // dummies as long as TAP is not available
const double MuIsoUncertaintyDown_ = 5;  // dummies as long as TAP is not available
const double ElecIsoUncertaintyUp_ = 5;  // dummies as long as TAP is not available
const double ElecIsoUncertaintyDown_ = 5;  // dummies as long as TAP is not available


// input jet definitions
const double jetCone_=0.4;
const double jetMinPt_ = 30;

// actity around lepton
const double maxDeltaRMuActivity_=1.0;
const double maxDeltaRElecActivity_=1.0;
const double maxDeltaRIsoTrackActivity_=1.0;
const unsigned int elecActivityMethod_=0;               // ###############
const unsigned int muActivityMethod_=0;                 // ###############
const unsigned int isoTrackActivityMethod_=0;

// isolated track prediction
const double maxDeltaRRecoIsoMuToTack_ = 0.2;
const double maxDiffPtRecoIsoMuToTack_ = 0.5;

const double maxDeltaRRecoIsoElecToTack_ = 0.3;
const double maxDiffPtRecoIsoElecToTack_ = 0.5;


class Prediction : public TSelector {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  void resetValues();
  bool FiltersPass();
  double getEff(TH2F* effTH2F, double xValue, double yValue);
  double getEff(TH1F* effTH2F, double xValue);
  double MuActivity(double muEta, double muPhi, unsigned int method);
  double ElecActivity( double elecEta, double elecPhi, unsigned int method);
  double IsoTrackActivityCalc( double isoTrackEta, double isoTrackPhi, unsigned int method);
  std::pair <double,double> minDeltaRLepJet(double lepPT, double lepEta, double lepPhi);

  std::vector <int> GetPTWBin(int, double, double);

  
  //Options
  bool useTrigger = false;
  bool useTriggerEffWeight = false;
  bool doPUreweighting = false;
  bool doBTagCorr = false;
  bool doISRcorr = false; 
  bool useFilterData = false;
  bool useFilterList = false;

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


  EventListFilter *evtListFilter = 0;

  TH2F* h_muIDSF = 0;
  TH2F* h_muIsoSF = 0;
  TH2F* h_elecIsoSF = 0;
  TH2F* h_elecIDSF = 0;

  std::vector<TH2D*> h_muAccPDF_up;
  std::vector<TH2D*> h_elecAccPDF_up;
  std::vector<TH2D*> h_muAccPDF_down;
  std::vector<TH2D*> h_elecAccPDF_down;
  std::vector<TH2D*> h_muAccQ2;
  std::vector<TH2D*> h_elecAccQ2;


  TString treeName = " ";


  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;
  SearchBins *SearchBinsEff_;

  Int_t           isoTracksNum;
  UShort_t JetsNum_;
  UShort_t MuonsNoIsoNum_, MuonsNum_;
  UShort_t ElectronsNoIsoNum_, ElectronsNum_;
  Float_t MuonsPt_, MuonsEta_;
  Float_t ElectronsPt_, ElectronsEta_;
  Float_t mtw;
  Float_t muPurityCorrection_;
  Float_t muMTWEff_, elecMTWEff_, mtwCorrectedWeight_;
  Float_t muDiLepContributionMTWAppliedEff_, mtwDiLepCorrectedWeight_;
  Float_t muIsoEff_, muIsoWeight_;
  Float_t muRecoEff_, muRecoWeight_;
  Float_t muAccEff_, muAccWeight_;
  Float_t muTotalWeight_, totalMuons_;
  Float_t elecPurityCorrection_, purityCorrectedWeight_, elecDiLepContributionMTWAppliedEff_;
  Float_t elecIsoEff_, elecIsoWeight_;
  Float_t elecRecoEff_, elecRecoWeight_;
  Float_t elecAccEff_, elecAccWeight_;
  Float_t elecTotalWeight_, totalElectrons_;
  Float_t muDiLepEffMTWAppliedEff_, elecDiLepEffMTWAppliedEff_;
  Float_t expectationReductionIsoTrackEff_;
  Float_t expectationReductionMuIsoTrackEff_,expectationReductionElecIsoTrackEff_,expectationReductionPionIsoTrackEff_, expectationReductionIsoTrackEffCombined_;
  Float_t diLepLostWeight_;

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
  
  Float_t diBosonUp;
  Float_t diBosonDown;
  Float_t nonClosureUp;
  Float_t nonClosureDown;

  Float_t totalStatUp;
  Float_t totalSysUp;
  Float_t totalUncUp;

  Float_t totalStatDown;
  Float_t totalSysDown;
  Float_t totalUncDown;

  effVec muPurityCorrectionVec_;
  effVec muMTWEffVec_, elecMTWEffVec_;
  effVec muDiLepContributionMTWAppliedEffVec_;
  effVec muIsoEffVec_;
  effVec muRecoEffVec_;
  effVec muAccEffVec_;
  effVec elecPurityCorrectionVec_, elecDiLepContributionMTWAppliedEffVec_;
  effVec elecIsoEffVec_;
  effVec elecRecoEffVec_;
  effVec elecAccEffVec_;
  effVec muDiLepEffMTWAppliedEffVec_, elecDiLepEffMTWAppliedEffVec_;
  effVec expectationReductionIsoTrackEffVec_;
  effVec expectationReductionMuIsoTrackEffVec_,expectationReductionElecIsoTrackEffVec_,expectationReductionPionIsoTrackEffVec_, expectationReductionIsoTrackEffCombinedVec_;

  
  Float_t totalWeight_, totalWeightDiLep_, totalWeightDiLepIsoTrackReduced_,totalWeightDiLepIsoMuTrackReduced_,totalWeightDiLepIsoElecTrackReduced_,totalWeightDiLepIsoPionTrackReduced_,totalWeightDiLepIsoTrackReducedCombined_;
  std::vector<Float_t> totalWeight_BTags_;
  std::vector<Float_t> totalWeight_BTags_noIsoTrack_;
  Float_t muTotalWeightDiLep_, muTotalWeightDiLepIsoTrackReduced_;
  Float_t elecTotalWeightDiLep_, elecTotalWeightDiLepIsoTrackReduced_;
  std::vector<Float_t> MuonsDeltaRJet, MuonsRelPTJet;
  std::vector<Float_t> ElectronsDeltaRJet, ElectronsRelPTJet;
  std::vector<Float_t>         MuonsPTW;
  std::vector<Float_t>         ElectronsPTW;

  std::vector<int> ptw_bins;
  
  UShort_t Bin_, BinQCD_;
  
  // TProfiles
  TProfile *MuMeanWeight_;
  TProfile *ElecMeanWeight_;
  TProfile *CombinedMeanWeight_;

  // TH1s for distributions of efficiencies per bin
  TH1 *MuWeightPerBin_[108];
  TH1 *ElecWeightPerBin_[108];
  TH1 *CombinedWeightPerBin_[108];

  //NEW
  TH1Eff *MuAccSearchBins_;
  TH1Eff *ElecAccSearchBins_;
  TH1Eff *MuMTWSearchBins_;
  TH1Eff *ElecMTWSearchBins_;
  TH1Eff *IsoTrackVetoSearchBins_;
  TH1Eff *MuIsoTrackVetoSearchBins_;
  TH1Eff *ElecIsoTrackVetoSearchBins_;
  TH1Eff *PionIsoTrackVetoSearchBins_;
  TH1Eff *MuDiLepContributionSearchBins_;
  TH1Eff *ElecDiLepContributionSearchBins_;
  
  // Effiecineices
  TH2Eff *MuMTWPTActivity_;
  TH1Eff *MuMTWNJets_;
  TH2Eff *MuMTWHTNJets_;
  TH2Eff *MuMTWMHTNJets_;
  TH2Eff *MuMTWHTMHT_;
  TH2Eff *MuMTWHTMHT_NJets24_;
  TH2Eff *MuMTWHTMHT_NJets56_;
  TH2Eff *MuMTWHTMHT_NJets7Inf_;
  TH1Eff *MuMTWPT_;
  TH2Eff *MuMTWHTMHT_NJets2_;
  TH2Eff *MuMTWHTMHT_NJets3_;
  TH2Eff *MuMTWHTMHT_NJets4_;
  TH2Eff *MuMTWHTMHT_NJets5_;
  TH2Eff *MuMTWHTMHT_NJets6_;
  TH2Eff *MuMTWHTMHT_NJets78_;
  TH2Eff *MuMTWHTMHT_NJets9Inf_;


  TH1Eff *MuDiLepContributionMTWAppliedNJets_;
  TH2Eff *MuDiLepContributionMTWAppliedMHTNJets_;
  TH2Eff *MuDiLepContributionMTWAppliedNJetsBTags_;
  TH1Eff *MuDiLepEffMTWAppliedNJets_;
  TH2Eff *MuDiLepEffMTWAppliedNJetsBTags_;

  TH2Eff *MuIsoActivityPT_;
  TH2Eff *MuIsoRelPTDeltaRJet_;
  TH2Eff *MuRecoActivityPT_;
  TH2Eff *MuRecoPTEta_;
  TH2Eff *MuAccBTagNJets_;
  TH2Eff *MuAccMHTNJets_;
  TH2Eff *MuAccHTNJets_;
  TH2Eff *MuAccHTMHT_;
  TH2Eff *MuPurityMHTNJets_; 
  TH2Eff *MuPurityHTMHT_; 

  TH2Eff *MuAccMHTNJetsB0_;
  TH2Eff *MuAccMHTNJetsB1_Inf_;
  TH2Eff *MuAccHTMHT_NJets26_;
  TH2Eff *MuAccHTMHT_NJets2_;
  TH2Eff *MuAccHTMHT_NJets3_;
  TH2Eff *MuAccHTMHT_NJets4_;
  TH2Eff *MuAccHTMHT_NJets5_;
  TH2Eff *MuAccHTMHT_NJets6_;
  TH2Eff *MuAccHTMHT_NJets78_;
  TH2Eff *MuAccHTMHT_NJets9Inf_;
  TH2Eff *MuAccHTMHT_NJets7Inf_;
  TH2Eff *MuAccHTMHTB0_;
  TH2Eff *MuAccHTMHTB1_Inf_;

  TH2Eff *MuAccHTMHT_NJets2_BTags0_;
  TH2Eff *MuAccHTMHT_NJets3_BTags0_;
  TH2Eff *MuAccHTMHT_NJets4_BTags0_;
  TH2Eff *MuAccHTMHT_NJets5_BTags0_;
  TH2Eff *MuAccHTMHT_NJets6_BTags0_;
  TH2Eff *MuAccHTMHT_NJets78_BTags0_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags0_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags0_;
  TH2Eff *MuAccHTMHT_NJets2_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets3_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets4_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets5_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets6_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets78_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets2_BTags1_;
  TH2Eff *MuAccHTMHT_NJets3_BTags1_;
  TH2Eff *MuAccHTMHT_NJets4_BTags1_;
  TH2Eff *MuAccHTMHT_NJets5_BTags1_;
  TH2Eff *MuAccHTMHT_NJets6_BTags1_;
  TH2Eff *MuAccHTMHT_NJets78_BTags1_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags1_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags1_;
  TH2Eff *MuAccHTMHT_NJets2_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets3_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets4_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets5_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets6_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets78_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags2Inf_;
  TH2Eff *MuAccHTMHT_NJets3_BTags2_;
  TH2Eff *MuAccHTMHT_NJets4_BTags2_;
  TH2Eff *MuAccHTMHT_NJets5_BTags2_;
  TH2Eff *MuAccHTMHT_NJets6_BTags2_;
  TH2Eff *MuAccHTMHT_NJets78_BTags2_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags2_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags2_;
  TH2Eff *MuAccHTMHT_NJets3_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets4_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets5_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets6_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets78_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags3Inf_;
  TH2Eff *MuAccHTMHT_NJets7Inf_BTags3Inf_;

  
  TH2Eff *ElecIsoActivityPT_;
  TH2Eff *ElecIsoRelPTDeltaRJet_;
  TH2Eff *ElecRecoActivityPT_;
  TH2Eff *ElecRecoPTEta_;
  TH2Eff *ElecAccBTagNJets_;
  TH2Eff *ElecAccMHTNJets_;
  TH2Eff *ElecAccHTNJets_;
  TH2Eff *ElecAccHTMHT_;

  TH2Eff *ElecPurityMHTNJets_;
  TH2Eff *ElecPurityHTMHT_; 
  TH2Eff *ElecMTWPTActivity_;
  TH1Eff *ElecMTWNJets_;
  TH2Eff *ElecMTWHTNJets_;
  TH2Eff *ElecMTWMHTNJets_;
  TH2Eff *ElecMTWHTMHT_;
  TH2Eff *ElecMTWHTMHT_NJets24_;
  TH2Eff *ElecMTWHTMHT_NJets56_;
  TH2Eff *ElecMTWHTMHT_NJets7Inf_;
  TH1Eff *ElecMTWPT_;
  TH2Eff *ElecMTWHTMHT_NJets2_;
  TH2Eff *ElecMTWHTMHT_NJets3_;
  TH2Eff *ElecMTWHTMHT_NJets4_;
  TH2Eff *ElecMTWHTMHT_NJets5_;
  TH2Eff *ElecMTWHTMHT_NJets6_;
  TH2Eff *ElecMTWHTMHT_NJets78_;
  TH2Eff *ElecMTWHTMHT_NJets9Inf_;


  TH1Eff *ElecDiLepContributionMTWAppliedNJets_;
  TH2Eff *ElecDiLepContributionMTWAppliedMHTNJets_;
  TH2Eff *ElecDiLepContributionMTWAppliedNJetsBTags_;
  TH1Eff *ElecDiLepEffMTWAppliedNJets_;
  TH2Eff *ElecDiLepEffMTWAppliedNJetsBTags_;

  TH2Eff *ElecAccHTMHT_NJets26_;
  TH2Eff *ElecAccHTMHT_NJets2_;
  TH2Eff *ElecAccHTMHT_NJets3_;
  TH2Eff *ElecAccHTMHT_NJets4_;
  TH2Eff *ElecAccHTMHT_NJets5_;
  TH2Eff *ElecAccHTMHT_NJets6_;
  TH2Eff *ElecAccHTMHT_NJets78_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_;
  TH2Eff *ElecAccMHTNJetsB0_;
  TH2Eff *ElecAccMHTNJetsB1_Inf_; 
  TH2Eff *ElecAccHTMHTB0_;
  TH2Eff *ElecAccHTMHTB1_Inf_;

  TH2Eff *ElecAccHTMHT_NJets2_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets2_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets2_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags1_;
  TH2Eff *ElecAccHTMHT_NJets2_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags2Inf_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags2_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags3Inf_;
  TH2Eff *ElecAccHTMHT_NJets7Inf_BTags3Inf_;
  
  // expectation reduction by the isolated track veto
  TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackMHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets24Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets56Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets2Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets3Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets4Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets5Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets6Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets7InfEff_;
  TH2Eff *ExpectationReductionMuIsoTrackBTagsNJetsEff_, *ExpectationReductionElecIsoTrackBTagsNJetsEff_, *ExpectationReductionPionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets24Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets24Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets24Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets56Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets56Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets56Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets7InfEff_, *ExpectationReductionElecIsoTrackHTMHT_NJets7InfEff_, *ExpectationReductionPionIsoTrackHTMHT_NJets7InfEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets2Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets2Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets2Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets3Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets3Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets3Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets4Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets4Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets4Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets5Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets5Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets5Eff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJets6Eff_, *ExpectationReductionElecIsoTrackHTMHT_NJets6Eff_, *ExpectationReductionPionIsoTrackHTMHT_NJets6Eff_;


  
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
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>     *Jets_muonEnergyFraction=0;
  std::vector<double>     *Jets_bDiscriminatorCSV=0;
  std::vector<int>     *Jets_hadronFlavor=0;
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
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_hadronFlavor=0;   //!
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


  
 Prediction(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~Prediction() { }
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
  
  ClassDef(Prediction,0);
};

#endif

#ifdef Prediction_cxx
void Prediction::Init(TTree *tree)
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

  // CSCTightHaloFilterUpdate from list
  // True if running on data
  // 2015 data only:  if(runOnData) useFilterList = true;  



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
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets3")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets4")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets5")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets6")->Clone());
  h_muAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("MuAccPDFUnc_NJets7Inf")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets3")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets4")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets5")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets6")->Clone());
  h_elecAccPDF_up.push_back((TH2D*) accPDF_histFile_up->Get("ElecAccPDFUnc_NJets7Inf")->Clone());

  TFile *accPDF_histFile_down = TFile::Open(path_AccPDF_down, "READ");
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets3")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets4")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets5")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets6")->Clone());
  h_muAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("MuAccPDFUnc_NJets7Inf")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets3")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets4")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets5")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets6")->Clone());
  h_elecAccPDF_down.push_back((TH2D*) accPDF_histFile_down->Get("ElecAccPDFUnc_NJets7Inf")->Clone());

  TFile *accQ2_histFile = TFile::Open(path_AccQ2, "READ");
  h_muAccQ2.push_back((TH2D*) accQ2_histFile->Get("MuAccQ2Unc_NJets3")->Clone());
  h_muAccQ2.push_back((TH2D*) accQ2_histFile->Get("MuAccQ2Unc_NJets4")->Clone());
  h_muAccQ2.push_back((TH2D*) accQ2_histFile->Get("MuAccQ2Unc_NJets5")->Clone());
  h_muAccQ2.push_back((TH2D*) accQ2_histFile->Get("MuAccQ2Unc_NJets6")->Clone());
  h_muAccQ2.push_back((TH2D*) accQ2_histFile->Get("MuAccQ2Unc_NJets7Inf")->Clone());
  h_elecAccQ2.push_back((TH2D*) accQ2_histFile->Get("ElecAccQ2Unc_NJets3")->Clone());
  h_elecAccQ2.push_back((TH2D*) accQ2_histFile->Get("ElecAccQ2Unc_NJets4")->Clone());
  h_elecAccQ2.push_back((TH2D*) accQ2_histFile->Get("ElecAccQ2Unc_NJets5")->Clone());
  h_elecAccQ2.push_back((TH2D*) accQ2_histFile->Get("ElecAccQ2Unc_NJets6")->Clone());
  h_elecAccQ2.push_back((TH2D*) accQ2_histFile->Get("ElecAccQ2Unc_NJets7Inf")->Clone());

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

  if(useFilterList) evtListFilter = new EventListFilter(path_evtListFilter);

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


Bool_t Prediction::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

#endif // #ifdef Prediction_cxx
