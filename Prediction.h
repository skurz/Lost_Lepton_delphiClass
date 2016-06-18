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

// Only needed if running on full nTuples not on Skims
const bool runOnNtuples = true;
const string path_toSkims("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_");

// PU
const TString path_puHist("PU/PileupHistograms_1117.root");
// bTag corrections
const string path_bTagCalib("btag/CSVv2_mod.csv");
const string path_bTagCalibFastSim("btag/CSV_13TEV_Combined_20_11_2015.csv");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ISR corrections: NOT RECOMMENDED FOR JAMBOREE -> Might change for Moriond! Just uncomment in Prediction::Init(Tree*) of this file
const TString path_ISRcorr("isr_corrections/ISRWeights.root");
// Signal x-sec: "dict_xsec.txt" for gluino pair prod; "dict_xsec_T2.txt" for (anti)stop pair prod.
const string path_xsec("xsec/dict_xsec.txt");

// CSCTightHaloFilterUpdate from list
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Extract csc2015.tar.gz! Txt file > 100MB!
const string path_evtListFilter("eventFilter/csc2015.txt");

const TString path_elecID("SFs/kinematicBinSFele.root");
const TString hist_elecID("CutBasedVeto");
const TString path_elecIso("SFs/kinematicBinSFele.root");
const TString hist_elecIso("MiniIso0p1_vs_RelActivity");

const TString path_muID("SFs/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root");
const TString hist_muID("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
// for muons: add 1% systematic to uncertainty -> set boolean to true in GetSF function
const TString path_muIso("SFs/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// muIso: still binned in pt/eta since this was recommended! Has to be changed for Moriond (also in Prediction.C when getting the uncertainties)!
const TString hist_muIso("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");


////////////////////////
//////// Usually don't have to be changed
///////////////////////

// ScaleFactors from SUSY lepton SG groups: presentation from Oct 23 (preliminary!!)
// NOT USED ANYMORE
const bool usePrelimSFs = false;
// Those are the SFs you want! Read from root file
const bool useSFs = true;

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
const double minMHT_=250;
const double minNJets_=2.5;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;

const UShort_t NJetsLow_=2;
const UShort_t NJetsMedium_=5;
const UShort_t NJetsMedium2_=7;
const UShort_t NJetsHigh_=8;

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
  TTree *tPrediction_;

  std::string fname; // for fetching file name
  TString fileName;
  Double_t HTgen_cut = 0;
  TFile* pufile = 0;
  TH1* puhist = 0;

  std::vector<std::pair<double, double>> xsecs;

    //open skim file as skimfile
  TH1* h_genpt;
  double nEvtsTotal;
  Double_t xsec;
  ISRCorrector *isrcorr = 0;
  TFile* isrfile;
  TH1* h_isr;
  Double_t w_isr;
  Double_t w_pu;
  BTagCorrector *btagcorr = 0;
  std::vector<double> bTagProb;

  EventListFilter *evtListFilter = 0;

  TH2F* h_muIDSF;
  TH2F* h_muIsoSF;
  TH2D* h_elecIsoSF;
  TH2D* h_elecIDSF;

  TString treeName = " ";


  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;

  Int_t           isoTracksNum;
  UShort_t JetsNum_;
  UShort_t selectedIDMuonsNum_, selectedIDIsoMuonsNum_;
  UShort_t selectedIDElectronsNum_, selectedIDIsoElectronsNum_;
  Float_t selectedIDIsoMuonsPt_, selectedIDIsoMuonsEta_;
  Float_t selectedIDIsoElectronsPt_, selectedIDIsoElectronsEta_;
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
  Float_t totalWeight_BTags0_, totalWeight_BTags1Inf_;
  Float_t totalWeight_BTags0_noIsoTrack_, totalWeight_BTags1Inf_noIsoTrack_;
  Float_t muTotalWeightDiLep_, muTotalWeightDiLepIsoTrackReduced_;
  Float_t elecTotalWeightDiLep_, elecTotalWeightDiLepIsoTrackReduced_;
  std::vector<Float_t> selectedIDIsoMuonsDeltaRJet, selectedIDIsoMuonsRelPTJet;
  std::vector<Float_t> selectedIDIsoElectronsDeltaRJet, selectedIDIsoElectronsRelPTJet;
  std::vector<Float_t>         selectedIDIsoMuonsPTW;
  std::vector<Float_t>         selectedIDIsoElectronsPTW;

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
  
  // Effiecineices
  TH2Eff *MuMTWPTActivity_;
  TH1Eff *MuMTWNJets_;
  TH2Eff *MuMTWHTNJets_;
  TH2Eff *MuMTWMHTNJets_;

  TH1Eff *MuDiLepContributionMTWAppliedNJets_;
  TH2Eff *MuDiLepContributionMTWAppliedMHTNJets_;
  TH2Eff *MuIsoActivityPT_;
  TH2Eff *MuIsoRelPTDeltaRJet_;
  TH2Eff *MuRecoActivityPT_;
  TH2Eff *MuRecoPTEta_;
  TH2Eff *MuAccBTagNJets_;
  TH2Eff *MuAccMHTNJets_;
  TH2Eff *MuAccHTNJets_;
  TH2Eff *MuAccHTMHT_;

  TH1Eff *MuDiLepEffMTWAppliedNJets_;
  TH2Eff *MuPurityMHTNJets_; 

  TH2Eff *MuAccMHTNJetsB0_;
  TH2Eff *MuAccMHTNJetsB1_Inf_;
  TH2Eff *MuAccHTMHT_NJetsLow_;
  TH2Eff *MuAccHTMHT_NJets2_;
  TH2Eff *MuAccHTMHT_NJets3_;
  TH2Eff *MuAccHTMHT_NJets4_;
  TH2Eff *MuAccHTMHT_NJets5_;
  TH2Eff *MuAccHTMHT_NJets6_;
  TH2Eff *MuAccHTMHT_NJets78_;
  TH2Eff *MuAccHTMHT_NJets9Inf_;
  TH2Eff *MuAccHTMHT_NJetsHigh_;
  TH2Eff *MuAccHTMHTB0_;
  TH2Eff *MuAccHTMHTB1_Inf_;

  TH2Eff *MuAccHTMHT_NJets2_BTags0_;
  TH2Eff *MuAccHTMHT_NJets3_BTags0_;
  TH2Eff *MuAccHTMHT_NJets4_BTags0_;
  TH2Eff *MuAccHTMHT_NJets5_BTags0_;
  TH2Eff *MuAccHTMHT_NJets6_BTags0_;
  TH2Eff *MuAccHTMHT_NJets78_BTags0_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags0_;
  TH2Eff *MuAccHTMHT_NJetsHigh_BTags0_;
  TH2Eff *MuAccHTMHT_NJets2_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets3_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets4_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets5_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets6_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets78_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJets9Inf_BTags1Inf_;
  TH2Eff *MuAccHTMHT_NJetsHigh_BTags1Inf_;

  
  TH2Eff *ElecIsoActivityPT_;
  TH2Eff *ElecIsoRelPTDeltaRJet_;
  TH2Eff *ElecRecoActivityPT_;
  TH2Eff *ElecRecoPTEta_;
  TH2Eff *ElecAccBTagNJets_;
  TH2Eff *ElecAccMHTNJets_;
  TH2Eff *ElecAccHTNJets_;
  TH2Eff *ElecAccHTMHT_;

  TH2Eff *ElecPurityMHTNJets_;
  TH1Eff *ElecMTWNJets_;
  TH2Eff *ElecMTWHTNJets_;
  TH2Eff *ElecMTWMHTNJets_;


  TH1Eff *ElecDiLepContributionMTWAppliedNJets_;
  TH2Eff *ElecDiLepContributionMTWAppliedMHTNJets_;
  TH1Eff *ElecDiLepEffMTWAppliedNJets_;

  TH2Eff *ElecAccHTMHT_NJetsLow_;
  TH2Eff *ElecAccHTMHT_NJets2_;
  TH2Eff *ElecAccHTMHT_NJets3_;
  TH2Eff *ElecAccHTMHT_NJets4_;
  TH2Eff *ElecAccHTMHT_NJets5_;
  TH2Eff *ElecAccHTMHT_NJets6_;
  TH2Eff *ElecAccHTMHT_NJets78_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_;
  TH2Eff *ElecAccHTMHT_NJetsHigh_;
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
  TH2Eff *ElecAccHTMHT_NJetsHigh_BTags0_;
  TH2Eff *ElecAccHTMHT_NJets2_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets3_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets4_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets5_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets6_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets78_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_BTags1Inf_;
  TH2Eff *ElecAccHTMHT_NJetsHigh_BTags1Inf_;
  
  // expectation reduction by the isolated track veto
  TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackMHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJetsVeryLowEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJetsLowEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets4Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets5Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets6Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJetsHighEff_;
  TH2Eff *ExpectationReductionMuIsoTrackBTagsNJetsEff_, *ExpectationReductionElecIsoTrackBTagsNJetsEff_, *ExpectationReductionPionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJetsVeryLowEff_, *ExpectationReductionElecIsoTrackHTMHT_NJetsVeryLowEff_, *ExpectationReductionPionIsoTrackHTMHT_NJetsVeryLowEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJetsLowEff_, *ExpectationReductionElecIsoTrackHTMHT_NJetsLowEff_, *ExpectationReductionPionIsoTrackHTMHT_NJetsLowEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJetsHighEff_, *ExpectationReductionElecIsoTrackHTMHT_NJetsHighEff_, *ExpectationReductionPionIsoTrackHTMHT_NJetsHighEff_;

  
  // Declaration of leaf types
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  Int_t           BTags;
  Int_t          CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  Bool_t           eeBadSc4Filter;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<TLorentzVector> *GenEls=0;
  std::vector<TLorentzVector> *GenMus=0;
  Int_t          HBHENoiseFilter;
  Int_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<bool>    *HTJetsMask=0;
  Double_t        METPhi;
  Double_t        MET;
  Double_t        MHT;
  Double_t        MHTPhi;
  std::vector<TLorentzVector> *Muons=0;
  Int_t           NJets;
  Int_t           NVtx;
  std::vector<TLorentzVector> *selectedIDElectrons=0;
  std::vector<TLorentzVector> *selectedIDIsoElectrons=0;
  std::vector<TLorentzVector> *selectedIDIsoMuons=0;
  std::vector<TLorentzVector> *selectedIDMuons=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  Double_t        Weight;
  Double_t        puWeight;
  Double_t        madHT;
  Double_t        SusyLSPMass;
  Double_t        SusyMotherMass;
  Double_t        TrueNumInteractions;
  std::vector<double>  *selectedIDElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDMuons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoMuons_MT2Activity=0;
  std::vector<TLorentzVector> *genParticles=0;
  std::vector<int> *genParticles_PDGid=0;


  // List of branches
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  TBranch        *b_eeBadSc4Filter=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_hadronFlavor=0;   //!
  TBranch        *b_HTJetsMask=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_selectedIDElectrons=0;   //!
  TBranch        *b_selectedIDIsoElectrons=0;   //!
  TBranch        *b_selectedIDIsoMuons=0;   //!
  TBranch        *b_selectedIDMuons=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_puWeight=0;   //!
  TBranch        *b_madHT=0;
  TBranch        *b_SusyLSPMass=0;
  TBranch        *b_SusyMotherMass=0;
  TBranch        *b_TrueNumInteractions=0;
  TBranch        *b_genParticles=0;
  TBranch        *b_genParticles_PDGid=0;
  TBranch        *b_selectedIDElectrons_MT2Activity=0;   //!
  TBranch        *b_selectedIDIsoElectrons_MT2Activity=0;   //!
  TBranch        *b_selectedIDIsoMuons_MT2Activity=0;   //!
  TBranch        *b_selectedIDMuons_MT2Activity=0;   //!

  
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
  if(runOnStandardModelMC || runOnSignalMC) useTriggerEffWeight = false;

  // Do PU reweighting. true for signal scan
  if(runOnSignalMC) doPUreweighting = true;
  // bTag corrections. Use for signal scan
  if(!runOnData) doBTagCorr = true;
  // ISR corrections. NOT RECOMMENDED FOR JAMBOREE -> Might change for Moriond
  //if(runOnSignalMC) doISRcorr = true; //<-check---------------------------------------

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

  std::ifstream signal_xsec(path_xsec);
  std::string str_xsec;
  while (std::getline(signal_xsec, str_xsec))
  {
    TObjArray *tokens = TString(str_xsec).Tokenize(",");
    //std::cout<<((TObjString *)(tokens->At(0)))->String()<<"; "<<((TObjString *)(tokens->At(1)))->String()<<";"<<std::endl;
    xsecs.push_back(std::make_pair(std::atof(((TObjString *)(tokens->At(0)))->String()), std::atof(((TObjString *)(tokens->At(1)))->String())));
  }

  // Open histograms for SFs
  TFile *muIDSF_histFile = TFile::Open(path_muID, "READ");
  h_muIDSF = (TH2F*) muIDSF_histFile->Get(hist_muID)->Clone();

  TFile *muIsoSF_histFile = TFile::Open(path_muIso, "READ");
  h_muIsoSF = (TH2F*) muIsoSF_histFile->Get(hist_muIso)->Clone();

  TFile *elecIDSF_histFile = TFile::Open(path_elecID, "READ");
  h_elecIDSF = (TH2D*) elecIDSF_histFile->Get(hist_elecID)->Clone();

  TFile *elecIsoSF_histFile = TFile::Open(path_elecIso, "READ");
  h_elecIsoSF = (TH2D*) elecIsoSF_histFile->Get(hist_elecIso)->Clone();

  if(runOnSignalMC){
    // ISR setup
    isrfile = TFile::Open(path_ISRcorr, "READ");
    h_isr = (TH1*)isrfile->Get("isr_weights_central");
    // everything else: done in loop!
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
    fChain->SetBranchStatus("CSCTightHaloFilter", 1);
    fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
    fChain->SetBranchStatus("eeBadScFilter", 1);
    fChain->SetBranchStatus("eeBadSc4Filter", 1);
    fChain->SetBranchStatus("HBHENoiseFilter", 1);
    fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
  }
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("HTJetsMask", 1);
  fChain->SetBranchStatus("METPhi", 1);
  fChain->SetBranchStatus("MET", 1);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchStatus("MHTPhi", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("selectedIDElectrons", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("selectedIDMuons", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  if(!runOnData){
    fChain->SetBranchStatus("Weight", 1);
    fChain->SetBranchStatus("Jets_hadronFlavor", 1);
    fChain->SetBranchStatus("madHT", 1);
  } 
  if(runOnSignalMC){
    fChain->SetBranchStatus("SusyLSPMass", 1);
    fChain->SetBranchStatus("SusyMotherMass", 1);
    fChain->SetBranchStatus("TrueNumInteractions", 1);
    fChain->SetBranchStatus("genParticles",1);
    fChain->SetBranchStatus("genParticles_PDGid",1);
  }
  fChain->SetBranchStatus("selectedIDElectrons_MT2Activity",1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_MT2Activity", 1);
  fChain->SetBranchStatus("selectedIDIsoMuons_MT2Activity",1);
  fChain->SetBranchStatus("selectedIDMuons_MT2Activity", 1);

  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  if(!runOnSignalMC){
    fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
    fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
    fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
  }
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("HTJetsMask", &HTJetsMask, &b_HTJetsMask);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
  fChain->SetBranchAddress("Electrons", &selectedIDIsoElectrons, &b_selectedIDIsoElectrons);
  fChain->SetBranchAddress("Muons", &selectedIDIsoMuons, &b_selectedIDIsoMuons);
  fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  if(!runOnData){
    fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
    fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
    fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
  }
  if(runOnSignalMC){
    fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
    fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
    fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
    fChain->SetBranchAddress("genParticles", &genParticles, &b_genParticles);
    fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid, &b_genParticles_PDGid);
  }
  fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
  fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
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
