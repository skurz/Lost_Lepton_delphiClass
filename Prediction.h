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
// Header file for the classes stored in the TTree if any.

const bool useAsymmErrors = true;
const bool useFilterData = true;
const bool applyFilters_=true;
const bool applyDiLepCorrection_=true;
const bool useTrigger = false;

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;

// Fixed size dimensions of array or collections stored in the TTree if any.
// use gen infomation to fix purityy of muon controlsample
const bool useGenInfoToMatchCSMuonToGen_=0; // changed 20 Nov from 1 to 0
const double maxDeltaRGenToRecoIsoMuon_=0.3;
const double maxDiffPtGenToRecoIsoMuon_=0.3;
const double minHT_=500;
const double minMHT_=200;
const double minNJets_=3.5;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double minDeltaPhiN_=4.0;

const UShort_t NJetsLow_=2;
const UShort_t NJetsMedium_=5;
const UShort_t NJetsMedium2_=7;
const UShort_t NJetsHigh_=8;

// TAP
const bool UseTagAndProbeEffIso_=false; // warning overriges all other choices for isolation efficiency
const bool UseTagAndProbeEffReco_=false; // warning overriges all other choices for reconstruction efficiency


// uncertainties
const double isoTrackUncertaintyUp_ = 20; // dummies as long as TAP is not available
const double isoTrackUncertaintyDown_ = 20; // dummies as long as TAP is not available

const double MuMTWUncertaintyUp_ = 40;
const double MuMTWUncertaintyDown_ = 40;
const double ElecMTWUncertaintyUp_ = 40;
const double ElecMTWUncertaintyDown_ = 40;

const double ElecPurityUncertaintyUp_ = 40; // no purity correction for muCS (>99%)
const double ElecPurityUncertaintyDown_ = 40; // no purity correction for muCS (>99%)

const double MuSingleLepPurityUp_ = 50;
const double MuSingleLepPurityDown_ = 50;
const double ElecSingleLepPurityUp_ = 50;
const double ElecSingleLepPurityDown_ = 50;

const double MuDiLepFoundUp_ = 20;
const double MuDiLepFoundDown_ = 20;
const double ElecDiLepFoundUp_ = 20;
const double ElecDiLepFoundDown_ = 20;

const double MuAccUncertaintyUp_ = 9;  // pdf
const double MuAccUncertaintyDown_ = 9;  // pdf
const double ElecAccUncertaintyUp_ = 9;  // pdf
const double ElecAccUncertaintyDown_ = 9;  // pdf

const double MuRecoUncertaintyUp_ = 10;  // dummies as long as TAP is not available
const double MuRecoUncertaintyDown_ = 10;  // dummies as long as TAP is not available
const double ElecRecoUncertaintyUp_ = 10;  // dummies as long as TAP is not available
const double ElecRecoUncertaintyDown_ = 10;  // dummies as long as TAP is not available
const double MuIsoUncertaintyUp_ = 10;  // dummies as long as TAP is not available
const double MuIsoUncertaintyDown_ = 10;  // dummies as long as TAP is not available
const double ElecIsoUncertaintyUp_ = 10;  // dummies as long as TAP is not available
const double ElecIsoUncertaintyDown_ = 10;  // dummies as long as TAP is not available

const double diBosonContributionUp_ = 3;
const double diBosonContributionDown_ = 3;

const double nonClosureLowNJets_ = 25;
const double nonClosureHighNJets_ = 50;

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
  // output variables
  TTree *tPrediction_;
  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;

  Int_t           isoTracks;
  Float_t mtw;
  Float_t muPurityCorrection_;
  Float_t muMTWEff_, elecMTWEff_, mtwCorrectedWeight_;
  Float_t muDiLepContributionMTWAppliedEff_, mtwDiLepCorrectedWeight_;
  Float_t muIsoEff_, muIsoWeight_;
  Float_t muIsoOnlyWeight_, elecIsoOnlyWeight_;
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
  Float_t elecIsoSysUp;
  Float_t elecIsoSysDown;
  Float_t elecRecoSysUp;
  Float_t elecRecoSysDown;
  Float_t elecAccSysUp;
  Float_t elecAccSysDown;
  
  Float_t diBosonUp;
  Float_t diBosonDown;
  Float_t nonClosureUp;
  Float_t nonClosureDown;

  Float_t totalStat;
  Float_t totalSys;
  Float_t totalUnc;

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
  Float_t         selectedIDIsoMuonsActivity[400];
  Float_t         selectedIDIsoElectronsActivity[400];
  Float_t         selectedIDIsoMuonsDeltaRJet[400];
  Float_t         selectedIDIsoMuonsRelPTJet[400];
  Float_t         selectedIDIsoElectronsDeltaRJet[400];
  Float_t         selectedIDIsoElectronsRelPTJet[400];

  UShort_t Bin_, BinQCD_;
  
  // isolated track prediction
  bool IsolatedTracksMuMatched_, IsolatedTracksElecMatched_;

  // TProfiles
  TProfile *MuMeanWeight_;
  TProfile *ElecMeanWeight_;
  TProfile *CombinedMeanWeight_;

  // TH1s for distributions of efficiencies per bin
  TH1 *MuWeightPerBin_[300];
  TH1 *ElecWeightPerBin_[300];
  TH1 *CombinedWeightPerBin_[300];
  
  // Effiecineices
  // TAP
  TH2F *MuIsoPTActivityTAPMC_;
  TH2F *ElecIsoPTActivityTAPMC_;
  TH2F *MuRecoPTActivityTAPMC_;
  TH2F *ElecRecoPTActivityTAPMC_;

  // new Efficiency Maps
  TH2Eff *MuMTWPTActivity_;
  TH1Eff *MuMTWNJets_;
  TH1Eff *MuDiLepContributionMTWAppliedNJets_;
  TH2Eff *MuIsoPTActivity_;
  TH2Eff *MuIsoRelPTDeltaRJet_;
  TH2Eff *MuRecoPTActivity_;
  TH2Eff *MuAccBTagNJets_;
  TH2Eff *MuAccMHTNJets_;
  TH2Eff *MuAccHTNJets_;
  TH2Eff *MuAccHTMHT_;

  TH1Eff *MuDiLepEffMTWAppliedNJets_;
  TH2Eff *MuPurityMHTNJets_; 

  TH2Eff *MuAccMHTNJetsB0_;
  TH2Eff *MuAccMHTNJetsB1_Inf_;
  TH2Eff *MuAccHTMHT_NJetsLow_;
  TH2Eff *MuAccHTMHT_NJetsHigh_;
  TH2Eff *MuAccHTMHTB0_;
  TH2Eff *MuAccHTMHTB1_Inf_;

  
  TH2Eff *ElecIsoPTActivity_;
  TH2Eff *ElecIsoRelPTDeltaRJet_;
  TH2Eff *ElecRecoPTActivity_;
  TH2Eff *ElecAccBTagNJets_;
  TH2Eff *ElecAccMHTNJets_;
  TH2Eff *ElecAccHTNJets_;
  TH2Eff *ElecAccHTMHT_;

  TH2Eff *ElecPurityMHTNJets_;
  TH1Eff *ElecMTWNJets_;
  TH1Eff *ElecDiLepContributionMTWAppliedNJets_;
  TH1Eff *ElecDiLepEffMTWAppliedNJets_;

  TH2Eff *ElecAccHTMHT_NJetsLow_;
  TH2Eff *ElecAccHTMHT_NJetsHigh_;
  TH2Eff *ElecAccMHTNJetsB0_;
  TH2Eff *ElecAccMHTNJetsB1_Inf_; 
  TH2Eff *ElecAccHTMHTB0_;
  TH2Eff *ElecAccHTMHTB1_Inf_;
  
  // expectation reduction by the isolated track veto
  TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionMuIsoTrackBTagsNJetsEff_, *ExpectationReductionElecIsoTrackBTagsNJetsEff_, *ExpectationReductionPionIsoTrackBTagsNJetsEff_;

  
  UShort_t elecActivityMethod, muActivityMethod, isoTrackActivityMethod;
  
  
  // Declaration of leaf types
  UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   UInt_t          EvtNum;
   Int_t           NVtx;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Int_t           Leptons;
   Int_t           TagLeptonHighPT;
   Int_t           NumPhotons;
   Int_t           METFilters;
   Int_t           CSCTightHaloFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         MHT_Phi;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN;
   Float_t         DeltaPhiN1;
   Float_t         DeltaPhiN2;
   Float_t         DeltaPhiN3;
   Float_t         METPt;
   Float_t         METPhi;
   UChar_t         GoodVtx;
   UChar_t         JetID;
   UChar_t         PassHFVeto;
   UChar_t         HBHENoiseFilter;
   UShort_t        MuonsNum;
   Float_t         MuonsPt[100];   //[MuonsNum]
   Float_t         MuonsEta[100];   //[MuonsNum]
   Float_t         MuonsPhi[100];   //[MuonsNum]
   Float_t         MuonsE[100];   //[MuonsNum]
   UShort_t        ElectronsNum;
   Float_t         ElectronsPt[100];   //[ElectronsNum]
   Float_t         ElectronsEta[100];   //[ElectronsNum]
   Float_t         ElectronsPhi[100];   //[ElectronsNum]
   Float_t         ElectronsE[100];   //[ElectronsNum]
   UShort_t        IsolatedElectronTracksVetoNum;
   Float_t         IsolatedElectronTracksVetoPt[100];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVetoEta[100];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVetoPhi[100];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVetoE[100];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVeto_MT[100];   //[IsolatedElectronTracksVetoNum]
   UShort_t        IsolatedMuonTracksVetoNum;
   Float_t         IsolatedMuonTracksVetoPt[100];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVetoEta[100];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVetoPhi[100];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVetoE[100];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVeto_MT[100];   //[IsolatedMuonTracksVetoNum]
   UShort_t        IsolatedPionTracksVetoNum;
   Float_t         IsolatedPionTracksVetoPt[100];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVetoEta[100];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVetoPhi[100];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVetoE[100];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVeto_MT[100];   //[IsolatedPionTracksVetoNum]
   UShort_t        selectedIDIsoMuonsNum;
   Float_t         selectedIDIsoMuonsPt[100];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsEta[100];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsPhi[100];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsE[100];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuons_MTW[100];   //[selectedIDIsoMuonsNum]
   UShort_t        selectedIDMuonsNum;
   Float_t         selectedIDMuonsPt[100];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsEta[100];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsPhi[100];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsE[100];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuons_MTW[100];   //[selectedIDMuonsNum]
   UShort_t        selectedIDIsoElectronsNum;
   Float_t         selectedIDIsoElectronsPt[100];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsEta[100];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsPhi[100];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsE[100];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectrons_MTW[100];   //[selectedIDIsoElectronsNum]
   UShort_t        selectedIDElectronsNum;
   Float_t         selectedIDElectronsPt[100];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsEta[100];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsPhi[100];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsE[100];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectrons_MTW[100];   //[selectedIDElectronsNum]
   UShort_t        SelectedPFCandidatesNum;
   Float_t         SelectedPFCandidatesPt[600];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesEta[600];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesPhi[600];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesE[600];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Charge[600];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Typ[600];   //[SelectedPFCandidatesNum]
   UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
   Float_t         selectedIDIsoMuonsNoMiniIsoPt[100];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoEta[100];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoPhi[100];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoE[100];   //[selectedIDIsoMuonsNoMiniIsoNum]
   UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
   Float_t         selectedIDIsoElectronsNoMiniIsoPt[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoEta[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoPhi[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoE[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
   UShort_t        JetsNum;
   Float_t         JetsPt[400];   //[JetsNum]
   Float_t         JetsEta[400];   //[JetsNum]
   Float_t         JetsPhi[400];   //[JetsNum]
   Float_t         JetsE[400];   //[JetsNum]
   Float_t         Jets_bDiscriminator[400];   //[JetsNum]
   Float_t         Jets_chargedEmEnergyFraction[400];   //[JetsNum]
   Float_t         Jets_chargedHadronEnergyFraction[400];   //[JetsNum]
   Int_t           Jets_chargedHadronMultiplicity[400];   //[JetsNum]
   Int_t           Jets_electronMultiplicity[400];   //[JetsNum]
   Float_t         Jets_jetArea[400];   //[JetsNum]
   Float_t         Jets_muonEnergyFraction[400];   //[JetsNum]
   Int_t           Jets_muonMultiplicity[400];   //[JetsNum]
   Float_t         Jets_neutralEmEnergyFraction[400];   //[JetsNum]
   Int_t           Jets_neutralHadronMultiplicity[400];   //[JetsNum]
   Float_t         Jets_photonEnergyFraction[400];   //[JetsNum]
   Int_t           Jets_photonMultiplicity[400];   //[JetsNum]
   UShort_t        slimmedElectronsNum;
   Float_t         slimmedElectronsPt[200];   //[slimmedElectronsNum]
   Float_t         slimmedElectronsEta[200];   //[slimmedElectronsNum]
   Float_t         slimmedElectronsPhi[200];   //[slimmedElectronsNum]
   Float_t         slimmedElectronsE[200];   //[slimmedElectronsNum]
   UShort_t        slimmedMuonsNum;
   Float_t         slimmedMuonsPt[200];   //[slimmedMuonsNum]
   Float_t         slimmedMuonsEta[200];   //[slimmedMuonsNum]
   Float_t         slimmedMuonsPhi[200];   //[slimmedMuonsNum]
   Float_t         slimmedMuonsE[200];   //[slimmedMuonsNum]
   UShort_t        SelectedPFElecCandidatesNum;
   Float_t         SelectedPFElecCandidatesPt[200];   //[SelectedPFElecCandidatesNum]
   Float_t         SelectedPFElecCandidatesEta[200];   //[SelectedPFElecCandidatesNum]
   Float_t         SelectedPFElecCandidatesPhi[200];   //[SelectedPFElecCandidatesNum]
   Float_t         SelectedPFElecCandidatesE[200];   //[SelectedPFElecCandidatesNum]
   UShort_t        SelectedPFMuCandidatesNum;
   Float_t         SelectedPFMuCandidatesPt[200];   //[SelectedPFMuCandidatesNum]
   Float_t         SelectedPFMuCandidatesEta[200];   //[SelectedPFMuCandidatesNum]
   Float_t         SelectedPFMuCandidatesPhi[200];   //[SelectedPFMuCandidatesNum]
   Float_t         SelectedPFMuCandidatesE[200];   //[SelectedPFMuCandidatesNum]
   UShort_t        SelectedPFPionCandidatesNum;
   Float_t         SelectedPFPionCandidatesPt[200];   //[SelectedPFPionCandidatesNum]
   Float_t         SelectedPFPionCandidatesEta[200];   //[SelectedPFPionCandidatesNum]
   Float_t         SelectedPFPionCandidatesPhi[200];   //[SelectedPFPionCandidatesNum]
   Float_t         SelectedPFPionCandidatesE[200];   //[SelectedPFPionCandidatesNum]
   vector<int>     *PassTrigger = 0;
   vector<string>  *TriggerNames = 0;
   vector<TLorentzVector> *bestPhoton = 0;

  
  // List of branches
  TBranch        *b_RunNum  = 0;   //!
   TBranch        *b_LumiBlockNum  = 0;   //!
   TBranch        *b_EvtNum  = 0;   //!
   TBranch        *b_NVtx  = 0;   //!
   TBranch        *b_isoElectronTracks  = 0;   //!
   TBranch        *b_isoMuonTracks  = 0;   //!
   TBranch        *b_isoPionTracks  = 0;   //!
   TBranch        *b_Leptons  = 0;   //!
   TBranch        *b_TagLeptonHighPT  = 0;   //!
   TBranch        *b_NumPhotons  = 0;   //!
   TBranch        *b_METFilters  = 0;   //!
   TBranch        *b_CSCTightHaloFilter  = 0;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter  = 0;   //!
   TBranch        *b_eeBadScFilter  = 0;   //!
   TBranch        *b_NJets  = 0;   //!
   TBranch        *b_BTags  = 0;   //!
   TBranch        *b_Weight  = 0;   //!
   TBranch        *b_HT  = 0;   //!
   TBranch        *b_MHT  = 0;   //!
   TBranch        *b_MHT_Phi  = 0;   //!
   TBranch        *b_DeltaPhi1  = 0;   //!
   TBranch        *b_DeltaPhi2  = 0;   //!
   TBranch        *b_DeltaPhi3  = 0;   //!
   TBranch        *b_minDeltaPhiN  = 0;   //!
   TBranch        *b_DeltaPhiN1  = 0;   //!
   TBranch        *b_DeltaPhiN2  = 0;   //!
   TBranch        *b_DeltaPhiN3  = 0;   //!
   TBranch        *b_METPt  = 0;   //!
   TBranch        *b_METPhi  = 0;   //!
   TBranch        *b_GoodVtx  = 0;   //!
   TBranch        *b_JetID  = 0;   //!
   TBranch        *b_PassHFVeto  = 0;   //!
   TBranch        *b_HBHENoiseFilter  = 0;   //!
   TBranch        *b_MuonsNum  = 0;   //!
   TBranch        *b_MuonsPt  = 0;   //!
   TBranch        *b_MuonsEta  = 0;   //!
   TBranch        *b_MuonsPhi  = 0;   //!
   TBranch        *b_MuonsE  = 0;   //!
   TBranch        *b_ElectronsNum  = 0;   //!
   TBranch        *b_ElectronsPt  = 0;   //!
   TBranch        *b_ElectronsEta  = 0;   //!
   TBranch        *b_ElectronsPhi  = 0;   //!
   TBranch        *b_ElectronsE  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoNum  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoPt  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoEta  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoPhi  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoE  = 0;   //!
   TBranch        *b_IsolatedElectronTracksVeto_MT  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoNum  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoPt  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoEta  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoPhi  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoE  = 0;   //!
   TBranch        *b_IsolatedMuonTracksVeto_MT  = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoNum  = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoPt  = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoEta  = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoPhi  = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoE  = 0;   //!
   TBranch        *b_IsolatedPionTracksVeto_MT  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNum  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsPt  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsEta  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsPhi  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsE  = 0;   //!
   TBranch        *b_selectedIDIsoMuons_MTW  = 0;   //!
   TBranch        *b_selectedIDMuonsNum  = 0;   //!
   TBranch        *b_selectedIDMuonsPt  = 0;   //!
   TBranch        *b_selectedIDMuonsEta  = 0;   //!
   TBranch        *b_selectedIDMuonsPhi  = 0;   //!
   TBranch        *b_selectedIDMuonsE  = 0;   //!
   TBranch        *b_selectedIDMuons_MTW  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNum  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsPt  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsEta  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsPhi  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsE  = 0;   //!
   TBranch        *b_selectedIDIsoElectrons_MTW  = 0;   //!
   TBranch        *b_selectedIDElectronsNum  = 0;   //!
   TBranch        *b_selectedIDElectronsPt  = 0;   //!
   TBranch        *b_selectedIDElectronsEta  = 0;   //!
   TBranch        *b_selectedIDElectronsPhi  = 0;   //!
   TBranch        *b_selectedIDElectronsE  = 0;   //!
   TBranch        *b_selectedIDElectrons_MTW  = 0;   //!
   TBranch        *b_SelectedPFCandidatesNum  = 0;   //!
   TBranch        *b_SelectedPFCandidatesPt  = 0;   //!
   TBranch        *b_SelectedPFCandidatesEta  = 0;   //!
   TBranch        *b_SelectedPFCandidatesPhi  = 0;   //!
   TBranch        *b_SelectedPFCandidatesE  = 0;   //!
   TBranch        *b_SelectedPFCandidates_Charge  = 0;   //!
   TBranch        *b_SelectedPFCandidates_Typ  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoNum  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPt  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoEta  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPhi  = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoE  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoNum  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPt  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoEta  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPhi  = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoE  = 0;   //!
   TBranch        *b_JetsNum  = 0;   //!
   TBranch        *b_JetsPt  = 0;   //!
   TBranch        *b_JetsEta  = 0;   //!
   TBranch        *b_JetsPhi  = 0;   //!
   TBranch        *b_JetsE  = 0;   //!
   TBranch        *b_Jets_bDiscriminator  = 0;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction  = 0;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction  = 0;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity  = 0;   //!
   TBranch        *b_Jets_electronMultiplicity  = 0;   //!
   TBranch        *b_Jets_jetArea  = 0;   //!
   TBranch        *b_Jets_muonEnergyFraction  = 0;   //!
   TBranch        *b_Jets_muonMultiplicity  = 0;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction  = 0;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity  = 0;   //!
   TBranch        *b_Jets_photonEnergyFraction  = 0;   //!
   TBranch        *b_Jets_photonMultiplicity  = 0;   //!
   TBranch        *b_slimmedElectronsNum  = 0;   //!
   TBranch        *b_slimmedElectronsPt  = 0;   //!
   TBranch        *b_slimmedElectronsEta  = 0;   //!
   TBranch        *b_slimmedElectronsPhi  = 0;   //!
   TBranch        *b_slimmedElectronsE  = 0;   //!
   TBranch        *b_slimmedMuonsNum  = 0;   //!
   TBranch        *b_slimmedMuonsPt  = 0;   //!
   TBranch        *b_slimmedMuonsEta  = 0;   //!
   TBranch        *b_slimmedMuonsPhi  = 0;   //!
   TBranch        *b_slimmedMuonsE  = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesNum  = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesPt  = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesEta  = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesPhi  = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesE  = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesNum  = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesPt  = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesEta  = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesPhi  = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesE  = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesNum  = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesPt  = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesEta  = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesPhi  = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesE  = 0;   //!
   TBranch        *b_PassTrigger  = 0;   //!
   TBranch        *b_TriggerNames  = 0;   //!
   TBranch        *b_bestPhoton  = 0;   //!
  
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
  
  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
   fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT, &b_TagLeptonHighPT);
   fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
   fChain->SetBranchAddress("METFilters", &METFilters, &b_METFilters);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHT_Phi", &MHT_Phi, &b_MHT_Phi);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
   fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
   fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
   fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
   fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("GoodVtx", &GoodVtx, &b_GoodVtx);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("PassHFVeto", &PassHFVeto, &b_PassHFVeto);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("MuonsNum", &MuonsNum, &b_MuonsNum);
   fChain->SetBranchAddress("MuonsPt", MuonsPt, &b_MuonsPt);
   fChain->SetBranchAddress("MuonsEta", MuonsEta, &b_MuonsEta);
   fChain->SetBranchAddress("MuonsPhi", MuonsPhi, &b_MuonsPhi);
   fChain->SetBranchAddress("MuonsE", MuonsE, &b_MuonsE);
   fChain->SetBranchAddress("ElectronsNum", &ElectronsNum, &b_ElectronsNum);
   fChain->SetBranchAddress("ElectronsPt", ElectronsPt, &b_ElectronsPt);
   fChain->SetBranchAddress("ElectronsEta", ElectronsEta, &b_ElectronsEta);
   fChain->SetBranchAddress("ElectronsPhi", ElectronsPhi, &b_ElectronsPhi);
   fChain->SetBranchAddress("ElectronsE", ElectronsE, &b_ElectronsE);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoNum", &IsolatedElectronTracksVetoNum, &b_IsolatedElectronTracksVetoNum);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoPt", IsolatedElectronTracksVetoPt, &b_IsolatedElectronTracksVetoPt);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoEta", IsolatedElectronTracksVetoEta, &b_IsolatedElectronTracksVetoEta);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoPhi", IsolatedElectronTracksVetoPhi, &b_IsolatedElectronTracksVetoPhi);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoE", IsolatedElectronTracksVetoE, &b_IsolatedElectronTracksVetoE);
   fChain->SetBranchAddress("IsolatedElectronTracksVeto_MT", IsolatedElectronTracksVeto_MT, &b_IsolatedElectronTracksVeto_MT);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoNum", &IsolatedMuonTracksVetoNum, &b_IsolatedMuonTracksVetoNum);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoPt", IsolatedMuonTracksVetoPt, &b_IsolatedMuonTracksVetoPt);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoEta", IsolatedMuonTracksVetoEta, &b_IsolatedMuonTracksVetoEta);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoPhi", IsolatedMuonTracksVetoPhi, &b_IsolatedMuonTracksVetoPhi);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoE", IsolatedMuonTracksVetoE, &b_IsolatedMuonTracksVetoE);
   fChain->SetBranchAddress("IsolatedMuonTracksVeto_MT", IsolatedMuonTracksVeto_MT, &b_IsolatedMuonTracksVeto_MT);
   fChain->SetBranchAddress("IsolatedPionTracksVetoNum", &IsolatedPionTracksVetoNum, &b_IsolatedPionTracksVetoNum);
   fChain->SetBranchAddress("IsolatedPionTracksVetoPt", IsolatedPionTracksVetoPt, &b_IsolatedPionTracksVetoPt);
   fChain->SetBranchAddress("IsolatedPionTracksVetoEta", IsolatedPionTracksVetoEta, &b_IsolatedPionTracksVetoEta);
   fChain->SetBranchAddress("IsolatedPionTracksVetoPhi", IsolatedPionTracksVetoPhi, &b_IsolatedPionTracksVetoPhi);
   fChain->SetBranchAddress("IsolatedPionTracksVetoE", IsolatedPionTracksVetoE, &b_IsolatedPionTracksVetoE);
   fChain->SetBranchAddress("IsolatedPionTracksVeto_MT", IsolatedPionTracksVeto_MT, &b_IsolatedPionTracksVeto_MT);
   fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
   fChain->SetBranchAddress("selectedIDIsoMuonsPt", selectedIDIsoMuonsPt, &b_selectedIDIsoMuonsPt);
   fChain->SetBranchAddress("selectedIDIsoMuonsEta", selectedIDIsoMuonsEta, &b_selectedIDIsoMuonsEta);
   fChain->SetBranchAddress("selectedIDIsoMuonsPhi", selectedIDIsoMuonsPhi, &b_selectedIDIsoMuonsPhi);
   fChain->SetBranchAddress("selectedIDIsoMuonsE", selectedIDIsoMuonsE, &b_selectedIDIsoMuonsE);
   fChain->SetBranchAddress("selectedIDIsoMuons_MTW", selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
   fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
   fChain->SetBranchAddress("selectedIDMuonsPt", selectedIDMuonsPt, &b_selectedIDMuonsPt);
   fChain->SetBranchAddress("selectedIDMuonsEta", selectedIDMuonsEta, &b_selectedIDMuonsEta);
   fChain->SetBranchAddress("selectedIDMuonsPhi", selectedIDMuonsPhi, &b_selectedIDMuonsPhi);
   fChain->SetBranchAddress("selectedIDMuonsE", selectedIDMuonsE, &b_selectedIDMuonsE);
   fChain->SetBranchAddress("selectedIDMuons_MTW", selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
   fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
   fChain->SetBranchAddress("selectedIDIsoElectronsPt", selectedIDIsoElectronsPt, &b_selectedIDIsoElectronsPt);
   fChain->SetBranchAddress("selectedIDIsoElectronsEta", selectedIDIsoElectronsEta, &b_selectedIDIsoElectronsEta);
   fChain->SetBranchAddress("selectedIDIsoElectronsPhi", selectedIDIsoElectronsPhi, &b_selectedIDIsoElectronsPhi);
   fChain->SetBranchAddress("selectedIDIsoElectronsE", selectedIDIsoElectronsE, &b_selectedIDIsoElectronsE);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
   fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
   fChain->SetBranchAddress("selectedIDElectronsPt", selectedIDElectronsPt, &b_selectedIDElectronsPt);
   fChain->SetBranchAddress("selectedIDElectronsEta", selectedIDElectronsEta, &b_selectedIDElectronsEta);
   fChain->SetBranchAddress("selectedIDElectronsPhi", selectedIDElectronsPhi, &b_selectedIDElectronsPhi);
   fChain->SetBranchAddress("selectedIDElectronsE", selectedIDElectronsE, &b_selectedIDElectronsE);
   fChain->SetBranchAddress("selectedIDElectrons_MTW", selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
   fChain->SetBranchAddress("SelectedPFCandidatesNum", &SelectedPFCandidatesNum, &b_SelectedPFCandidatesNum);
   fChain->SetBranchAddress("SelectedPFCandidatesPt", SelectedPFCandidatesPt, &b_SelectedPFCandidatesPt);
   fChain->SetBranchAddress("SelectedPFCandidatesEta", SelectedPFCandidatesEta, &b_SelectedPFCandidatesEta);
   fChain->SetBranchAddress("SelectedPFCandidatesPhi", SelectedPFCandidatesPhi, &b_SelectedPFCandidatesPhi);
   fChain->SetBranchAddress("SelectedPFCandidatesE", SelectedPFCandidatesE, &b_SelectedPFCandidatesE);
   fChain->SetBranchAddress("SelectedPFCandidates_Charge", SelectedPFCandidates_Charge, &b_SelectedPFCandidates_Charge);
   fChain->SetBranchAddress("SelectedPFCandidates_Typ", SelectedPFCandidates_Typ, &b_SelectedPFCandidates_Typ);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoNum", &selectedIDIsoMuonsNoMiniIsoNum, &b_selectedIDIsoMuonsNoMiniIsoNum);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoPt", selectedIDIsoMuonsNoMiniIsoPt, &b_selectedIDIsoMuonsNoMiniIsoPt);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoEta", selectedIDIsoMuonsNoMiniIsoEta, &b_selectedIDIsoMuonsNoMiniIsoEta);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoPhi", selectedIDIsoMuonsNoMiniIsoPhi, &b_selectedIDIsoMuonsNoMiniIsoPhi);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoE", selectedIDIsoMuonsNoMiniIsoE, &b_selectedIDIsoMuonsNoMiniIsoE);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoNum", &selectedIDIsoElectronsNoMiniIsoNum, &b_selectedIDIsoElectronsNoMiniIsoNum);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoPt", selectedIDIsoElectronsNoMiniIsoPt, &b_selectedIDIsoElectronsNoMiniIsoPt);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoEta", selectedIDIsoElectronsNoMiniIsoEta, &b_selectedIDIsoElectronsNoMiniIsoEta);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoPhi", selectedIDIsoElectronsNoMiniIsoPhi, &b_selectedIDIsoElectronsNoMiniIsoPhi);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoE", selectedIDIsoElectronsNoMiniIsoE, &b_selectedIDIsoElectronsNoMiniIsoE);
   fChain->SetBranchAddress("JetsNum", &JetsNum, &b_JetsNum);
   fChain->SetBranchAddress("JetsPt", JetsPt, &b_JetsPt);
   fChain->SetBranchAddress("JetsEta", JetsEta, &b_JetsEta);
   fChain->SetBranchAddress("JetsPhi", JetsPhi, &b_JetsPhi);
   fChain->SetBranchAddress("JetsE", JetsE, &b_JetsE);
   fChain->SetBranchAddress("Jets_bDiscriminator", Jets_bDiscriminator, &b_Jets_bDiscriminator);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_electronMultiplicity", Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_jetArea", Jets_jetArea, &b_Jets_jetArea);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("slimmedElectronsNum", &slimmedElectronsNum, &b_slimmedElectronsNum);
   fChain->SetBranchAddress("slimmedElectronsPt", slimmedElectronsPt, &b_slimmedElectronsPt);
   fChain->SetBranchAddress("slimmedElectronsEta", slimmedElectronsEta, &b_slimmedElectronsEta);
   fChain->SetBranchAddress("slimmedElectronsPhi", slimmedElectronsPhi, &b_slimmedElectronsPhi);
   fChain->SetBranchAddress("slimmedElectronsE", slimmedElectronsE, &b_slimmedElectronsE);
   fChain->SetBranchAddress("slimmedMuonsNum", &slimmedMuonsNum, &b_slimmedMuonsNum);
   fChain->SetBranchAddress("slimmedMuonsPt", slimmedMuonsPt, &b_slimmedMuonsPt);
   fChain->SetBranchAddress("slimmedMuonsEta", slimmedMuonsEta, &b_slimmedMuonsEta);
   fChain->SetBranchAddress("slimmedMuonsPhi", slimmedMuonsPhi, &b_slimmedMuonsPhi);
   fChain->SetBranchAddress("slimmedMuonsE", slimmedMuonsE, &b_slimmedMuonsE);
   fChain->SetBranchAddress("SelectedPFElecCandidatesNum", &SelectedPFElecCandidatesNum, &b_SelectedPFElecCandidatesNum);
   fChain->SetBranchAddress("SelectedPFElecCandidatesPt", SelectedPFElecCandidatesPt, &b_SelectedPFElecCandidatesPt);
   fChain->SetBranchAddress("SelectedPFElecCandidatesEta", SelectedPFElecCandidatesEta, &b_SelectedPFElecCandidatesEta);
   fChain->SetBranchAddress("SelectedPFElecCandidatesPhi", SelectedPFElecCandidatesPhi, &b_SelectedPFElecCandidatesPhi);
   fChain->SetBranchAddress("SelectedPFElecCandidatesE", SelectedPFElecCandidatesE, &b_SelectedPFElecCandidatesE);
   fChain->SetBranchAddress("SelectedPFMuCandidatesNum", &SelectedPFMuCandidatesNum, &b_SelectedPFMuCandidatesNum);
   fChain->SetBranchAddress("SelectedPFMuCandidatesPt", SelectedPFMuCandidatesPt, &b_SelectedPFMuCandidatesPt);
   fChain->SetBranchAddress("SelectedPFMuCandidatesEta", SelectedPFMuCandidatesEta, &b_SelectedPFMuCandidatesEta);
   fChain->SetBranchAddress("SelectedPFMuCandidatesPhi", SelectedPFMuCandidatesPhi, &b_SelectedPFMuCandidatesPhi);
   fChain->SetBranchAddress("SelectedPFMuCandidatesE", SelectedPFMuCandidatesE, &b_SelectedPFMuCandidatesE);
   fChain->SetBranchAddress("SelectedPFPionCandidatesNum", &SelectedPFPionCandidatesNum, &b_SelectedPFPionCandidatesNum);
   fChain->SetBranchAddress("SelectedPFPionCandidatesPt", SelectedPFPionCandidatesPt, &b_SelectedPFPionCandidatesPt);
   fChain->SetBranchAddress("SelectedPFPionCandidatesEta", SelectedPFPionCandidatesEta, &b_SelectedPFPionCandidatesEta);
   fChain->SetBranchAddress("SelectedPFPionCandidatesPhi", SelectedPFPionCandidatesPhi, &b_SelectedPFPionCandidatesPhi);
   fChain->SetBranchAddress("SelectedPFPionCandidatesE", SelectedPFPionCandidatesE, &b_SelectedPFPionCandidatesE);
   fChain->SetBranchAddress("PassTrigger", &PassTrigger, &b_PassTrigger);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("bestPhoton", &bestPhoton, &b_bestPhoton);

   fChain->SetBranchStatus("Gen*",0);
   fChain->SetBranchStatus("gen*",0);
   fChain->SetBranchStatus("Tau*",0);
   //fChain->SetBranchStatus("tau*",0);
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
