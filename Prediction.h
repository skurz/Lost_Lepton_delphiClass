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
const bool useTriggerEffWeight = true;

// Fix for central production v3
const bool dividePUweight = true;

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;

// scaleMet = 0: keep things the way they are
// scaleMet = +-: scale MET up/down for MTW calculation (only!) by 30%
const int scaleMet = 0;

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
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;

const UShort_t NJetsLow_=2;
const UShort_t NJetsMedium_=5;
const UShort_t NJetsMedium2_=7;
const UShort_t NJetsHigh_=8;

// TAP
const bool UseTagAndProbeEffIso_=false; // warning overriges all other choices for isolation efficiency
const bool UseTagAndProbeEffReco_=false; // warning overriges all other choices for reconstruction efficiency


// uncertainties
const double muIsoTrackUncertaintyUp_ = 10; // dummies as long as TAP is not available 20
const double muIsoTrackUncertaintyDown_ = 10; // dummies as long as TAP is not available 20
const double elecIsoTrackUncertaintyUp_ = 10; // dummies as long as TAP is not available 20
const double elecIsoTrackUncertaintyDown_ = 10; // dummies as long as TAP is not available 20
const double pionIsoTrackUncertaintyUp_ = 10; // dummies as long as TAP is not available 20
const double pionIsoTrackUncertaintyDown_ = 10; // dummies as long as TAP is not available 20
const double isoTrackUncertaintyUp_ = 10; // inclusive Isotracks. Not used any more
const double isoTrackUncertaintyDown_ = 10; // inclusive Isotracks. Not used any more

const double MuMTWUncertaintyUp_ = 40;  //40
const double MuMTWUncertaintyDown_ = 40;
const double ElecMTWUncertaintyUp_ = 40;
const double ElecMTWUncertaintyDown_ = 40;

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

const double MuAccUncertaintyUp_ = 5;  // pdf // 9
const double MuAccUncertaintyDown_ = 5;  // pdf
const double ElecAccUncertaintyUp_ = 5;  // pdf
const double ElecAccUncertaintyDown_ = 5;  // pdf

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
  // output variables
  TTree *tPrediction_;

  std::string fname; // for fetching file name
  TString fileName;
  Double_t HTgen_cut = 0;


  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;

  Int_t           isoTracks;
  UShort_t JetsNum_;
  UShort_t selectedIDMuonsNum_, selectedIDIsoMuonsNum_;
  UShort_t selectedIDElectronsNum_, selectedIDIsoElectronsNum_;
  Float_t mtw;
  Float_t ptw;
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
  Float_t muTotalWeightDiLep_, muTotalWeightDiLepIsoTrackReduced_;
  Float_t elecTotalWeightDiLep_, elecTotalWeightDiLepIsoTrackReduced_;
  std::vector<Float_t> selectedIDIsoMuonsDeltaRJet, selectedIDIsoMuonsRelPTJet;
  std::vector<Float_t> selectedIDIsoElectronsDeltaRJet, selectedIDIsoElectronsRelPTJet;

  UShort_t Bin_, BinQCD_;
  
  // isolated track prediction
  bool IsolatedTracksMuMatched_, IsolatedTracksElecMatched_;
  std::vector<Float_t> IsolatedMuonTracksVetoActivity,IsolatedElectronTracksVetoActivity,IsolatedPionTracksVetoActivity;
  std::vector<Float_t> IsolatedMuonTracksVetoMTW,IsolatedElectronTracksVetoMTW,IsolatedPionTracksVetoMTW;

  // TProfiles
  TProfile *MuMeanWeight_;
  TProfile *ElecMeanWeight_;
  TProfile *CombinedMeanWeight_;

  // TH1s for distributions of efficiencies per bin
  TH1 *MuWeightPerBin_[72];
  TH1 *ElecWeightPerBin_[72];
  TH1 *CombinedWeightPerBin_[72];
  
  // Effiecineices
  // TAP
  TH2D *MuIsoPTActivityTAPMC_;
  TH2D *ElecIsoPTActivityTAPMC_;
  TH2D *MuRecoPTActivityTAPMC_;
  TH2D *ElecRecoPTActivityTAPMC_;

  // new Efficiency Maps
  TH2Eff *MuMTWPTActivity_;
  TH1Eff *MuMTWNJets_;
  TH2Eff *MuMTWHTNJets_;

  TH1Eff *MuDiLepContributionMTWAppliedNJets_;
  TH2Eff *MuIsoActivityPT_;
  TH2Eff *MuIsoRelPTDeltaRJet_;
  TH2Eff *MuRecoActivityPT_;
  TH2Eff *MuAccBTagNJets_;
  TH2Eff *MuAccMHTNJets_;
  TH2Eff *MuAccHTNJets_;
  TH2Eff *MuAccHTMHT_;

  TH1Eff *MuDiLepEffMTWAppliedNJets_;
  TH2Eff *MuPurityMHTNJets_; 

  TH2Eff *MuAccMHTNJetsB0_;
  TH2Eff *MuAccMHTNJetsB1_Inf_;
  TH2Eff *MuAccHTMHT_NJetsLow_;
  TH2Eff *MuAccHTMHT_NJets4_;
  TH2Eff *MuAccHTMHT_NJets5_;
  TH2Eff *MuAccHTMHT_NJets6_;
  TH2Eff *MuAccHTMHT_NJetsHigh_;
  TH2Eff *MuAccHTMHTB0_;
  TH2Eff *MuAccHTMHTB1_Inf_;

  
  TH2Eff *ElecIsoActivityPT_;
  TH2Eff *ElecIsoRelPTDeltaRJet_;
  TH2Eff *ElecRecoActivityPT_;
  TH2Eff *ElecAccBTagNJets_;
  TH2Eff *ElecAccMHTNJets_;
  TH2Eff *ElecAccHTNJets_;
  TH2Eff *ElecAccHTMHT_;

  TH2Eff *ElecPurityMHTNJets_;
  TH1Eff *ElecMTWNJets_;
  TH2Eff *ElecMTWHTNJets_;


  TH1Eff *ElecDiLepContributionMTWAppliedNJets_;
  TH1Eff *ElecDiLepEffMTWAppliedNJets_;

  TH2Eff *ElecAccHTMHT_NJetsLow_;
  TH2Eff *ElecAccHTMHT_NJets4_;
  TH2Eff *ElecAccHTMHT_NJets5_;
  TH2Eff *ElecAccHTMHT_NJets6_;
  TH2Eff *ElecAccHTMHT_NJetsHigh_;
  TH2Eff *ElecAccMHTNJetsB0_;
  TH2Eff *ElecAccMHTNJetsB1_Inf_; 
  TH2Eff *ElecAccHTMHTB0_;
  TH2Eff *ElecAccHTMHTB1_Inf_;
  
  // expectation reduction by the isolated track veto
  TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackMHTNJetsEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJetsLowEff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets4Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets5Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJets6Eff_;
  TH2Eff *ExpectationReductionIsoTrackHTMHT_NJetsHighEff_;
  TH2Eff *ExpectationReductionMuIsoTrackBTagsNJetsEff_, *ExpectationReductionElecIsoTrackBTagsNJetsEff_, *ExpectationReductionPionIsoTrackBTagsNJetsEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJetsLowEff_, *ExpectationReductionElecIsoTrackHTMHT_NJetsLowEff_, *ExpectationReductionPionIsoTrackHTMHT_NJetsLowEff_;
  TH2Eff *ExpectationReductionMuIsoTrackHTMHT_NJetsHighEff_, *ExpectationReductionElecIsoTrackHTMHT_NJetsHighEff_, *ExpectationReductionPionIsoTrackHTMHT_NJetsHighEff_;

  
  UShort_t elecActivityMethod, muActivityMethod, isoTrackActivityMethod;
  
  
  // Declaration of leaf types
  std::vector<double>  *GenElec_MT2Activity=0;
  std::vector<double>  *GenElec_RA2Activity=0;
  std::vector<double>  *GenMu_MT2Activity=0;
  std::vector<double>  *GenMu_RA2Activity=0;
  std::vector<double>  *GenTau_MT2Activity=0;
  std::vector<double>  *GenTau_RA2Activity=0;
  std::vector<double>  *selectedIDElectrons_MiniIso=0;
  std::vector<double>  *selectedIDElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDElectrons_RA2Activity=0;
  std::vector<double>  *selectedIDIsoElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoElectrons_PTW=0;
  std::vector<double>  *selectedIDIsoElectrons_RA2Activity=0;
  std::vector<double>  *selectedIDMuons_MiniIso=0;
  std::vector<double>  *selectedIDMuons_MT2Activity=0;
  std::vector<double>  *selectedIDMuons_RA2Activity=0;
  std::vector<double>  *selectedIDIsoMuons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoMuons_PTW=0;
  std::vector<double>  *selectedIDIsoMuons_RA2Activity=0;
  
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  UInt_t          EvtNum;
  std::vector<TLorentzVector> *bestPhoton=0;
  Int_t           BTags;
  Int_t           CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Double_t        DeltaPhiN1;
  Double_t        DeltaPhiN2;
  Double_t        DeltaPhiN3;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  std::vector<int>     *ElectronCharge=0;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<int>     *GenElec_GenElecFromTau=0;
  std::vector<TLorentzVector> *GenEls=0;
  std::vector<int>     *GenMu_GenMuFromTau=0;
  std::vector<TLorentzVector> *GenMus=0;
  std::vector<int>     *GenTau_GenTauHad=0;
  std::vector<TLorentzVector> *GenTauNu=0;
  std::vector<TLorentzVector> *GenTaus=0;
  Bool_t          HBHENoiseFilter;
  Bool_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Int_t           isoElectronTracks;
  std::vector<TLorentzVector> *IsolatedElectronTracksVeto=0;
  std::vector<double>  *IsolatedElectronTracksVeto_MTW=0;
  std::vector<TLorentzVector> *IsolatedMuonTracksVeto=0;
  std::vector<double>  *IsolatedMuonTracksVeto_MTW=0;
  std::vector<TLorentzVector> *IsolatedPionTracksVeto=0;
  std::vector<double>  *IsolatedPionTracksVeto_MTW=0;
  Int_t           isoMuonTracks;
  Int_t           isoPionTracks;
  Bool_t          JetID;
  Bool_t          JetIDloose;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>  *Jets_bDiscriminatorCSV=0;
  std::vector<double>  *Jets_bDiscriminatorMVA=0;
  std::vector<double>  *Jets_chargedEmEnergyFraction=0;
  std::vector<double>  *Jets_chargedHadronEnergyFraction=0;
  std::vector<int>     *Jets_chargedHadronMultiplicity=0;
  std::vector<int>     *Jets_electronMultiplicity=0;
  std::vector<int>     *Jets_flavor=0;
  std::vector<double>  *Jets_jetArea=0;
  std::vector<double>  *Jets_muonEnergyFraction=0;
  std::vector<int>     *Jets_muonMultiplicity=0;
  std::vector<double>  *Jets_neutralEmEnergyFraction=0;
  std::vector<int>     *Jets_neutralHadronMultiplicity=0;
  std::vector<double>  *Jets_photonEnergyFraction=0;
  std::vector<int>     *Jets_photonMultiplicity=0;
  Int_t           Leptons;
  Int_t           METFilters;
  Double_t        METPhi;
  Double_t        METPt;
  Double_t        MHT;
  Double_t        MHT_Phi;
  Double_t        minDeltaPhiN;
  std::vector<int>     *MuonCharge=0;
  std::vector<TLorentzVector> *Muons=0;
  Int_t           nAllVertices;
  Int_t           NJets;
  Int_t           NumPhotons;
  Int_t           NVtx;
  std::vector<TLorentzVector> *selectedIDElectrons=0;
  std::vector<double>  *selectedIDElectrons_MTW=0;
  std::vector<TLorentzVector> *selectedIDIsoElectrons=0;
  std::vector<double>  *selectedIDIsoElectrons_MTW=0;
  std::vector<TLorentzVector> *selectedIDIsoMuons=0;
  std::vector<double>  *selectedIDIsoMuons_MTW=0;
  std::vector<TLorentzVector> *selectedIDMuons=0;
  std::vector<double>  *selectedIDMuons_MTW=0;
  Int_t           TagLeptonHighPT;
  std::vector<TLorentzVector> *TauDecayCands=0;
  std::vector<int>     *TauDecayCands_pdgID=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  Double_t        Weight;
  Double_t        puWeight;
  Double_t        genHT;


  // List of branches
  TBranch        *b_GenElec_MT2Activity=0;   //!
  TBranch        *b_GenElec_RA2Activity=0;
  TBranch        *b_GenMu_MT2Activity=0;   //!
  TBranch        *b_GenMu_RA2Activity=0;   //!
  TBranch        *b_GenTau_MT2Activity=0;   //!
  TBranch        *b_GenTau_RA2Activity=0;   //!
  TBranch        *b_selectedIDElectrons_MiniIso=0;   //!
  TBranch        *b_selectedIDElectrons_MT2Activity=0;   //!
  TBranch        *b_selectedIDElectrons_RA2Activity=0;   //!
  TBranch        *b_selectedIDIsoElectrons_MT2Activity=0;   //!
  TBranch        *b_selectedIDIsoElectrons_PTW=0;   //!
  TBranch        *b_selectedIDIsoElectrons_RA2Activity=0;   //!
  TBranch        *b_selectedIDIsoMuons_MT2Activity=0;   //!
  TBranch        *b_selectedIDIsoMuons_PTW=0;   //!
  TBranch        *b_selectedIDIsoMuons_RA2Activity=0;   //!
  TBranch        *b_selectedIDMuons_MiniIso=0;   //!
  TBranch        *b_selectedIDMuons_MT2Activity=0;   //!
  TBranch        *b_selectedIDMuons_RA2Activity=0;   //!
  
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_bestPhoton=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!
  TBranch        *b_DeltaPhiN1=0;   //!
  TBranch        *b_DeltaPhiN2=0;   //!
  TBranch        *b_DeltaPhiN3=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  TBranch        *b_ElectronCharge=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_GenElec_GenElecFromTau=0;   //!
  TBranch        *b_GenEls=0;   //!
  TBranch        *b_GenMu_GenMuFromTau=0;   //!
  TBranch        *b_GenMus=0;   //!
  TBranch        *b_GenTau_GenTauHad=0;   //!
  TBranch        *b_GenTauNu=0;   //!
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_isoElectronTracks=0;   //!
  TBranch        *b_IsolatedElectronTracksVeto=0;   //!
  TBranch        *b_IsolatedElectronTracksVeto_MTW=0;   //!
  TBranch        *b_IsolatedMuonTracksVeto=0;   //!
  TBranch        *b_IsolatedMuonTracksVeto_MTW=0;   //!
  TBranch        *b_IsolatedPionTracksVeto=0;   //!
  TBranch        *b_IsolatedPionTracksVeto_MTW=0;   //!
  TBranch        *b_isoMuonTracks=0;   //!
  TBranch        *b_isoPionTracks=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_JetIDloose=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_bDiscriminatorMVA=0;   //!
  TBranch        *b_Jets_chargedEmEnergyFraction=0;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction=0;   //!
  TBranch        *b_Jets_chargedHadronMultiplicity=0;   //!
  TBranch        *b_Jets_electronMultiplicity=0;   //!
  TBranch        *b_Jets_flavor=0;   //!
  TBranch        *b_Jets_jetArea=0;   //!
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_muonMultiplicity=0;   //!
  TBranch        *b_Jets_neutralEmEnergyFraction=0;   //!
  TBranch        *b_Jets_neutralHadronMultiplicity=0;   //!
  TBranch        *b_Jets_photonEnergyFraction=0;   //!
  TBranch        *b_Jets_photonMultiplicity=0;   //!
  TBranch        *b_Leptons=0;   //!
  TBranch        *b_METFilters=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_METPt=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHT_Phi=0;   //!
  TBranch        *b_minDeltaPhiN=0;   //!
  TBranch        *b_MuonCharge=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_nAllVertices=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_NumPhotons=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_selectedIDElectrons=0;   //!
  TBranch        *b_selectedIDElectrons_MTW=0;   //!
  TBranch        *b_selectedIDIsoElectrons=0;   //!
  TBranch        *b_selectedIDIsoElectrons_MTW=0;   //!
  TBranch        *b_selectedIDIsoMuons=0;   //!
  TBranch        *b_selectedIDIsoMuons_MTW=0;   //!
  TBranch        *b_selectedIDMuons=0;   //!
  TBranch        *b_selectedIDMuons_MTW=0;   //!
  TBranch        *b_TagLeptonHighPT=0;   //!
  TBranch        *b_TauDecayCands=0;   //!
  TBranch        *b_TauDecayCands_pdgID=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_puWeight=0;   //!
  TBranch        *b_genHT=0;

  
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

  TChain* temp = (TChain*)fChain;
  std::string infname=temp->GetFile()->GetName();

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

  std::cout << "genHT cut: " << HTgen_cut << std::endl;

  std::cout << "Saving file to: " << fileName << std::endl;

  fChain->SetBranchStatus("*",0);

/*  fChain->SetBranchStatus("GenElec_MT2Activity",1);
  fChain->SetBranchStatus("GenElec_RA2Activity",1);
  fChain->SetBranchStatus("GenMu_MT2Activity", 1);
  fChain->SetBranchStatus("GenMu_RA2Activity",1);
  fChain->SetBranchStatus("GenTau_MT2Activity",1);
  fChain->SetBranchStatus("GenTau_RA2Activity", 1);
*/  fChain->SetBranchStatus("selectedIDElectrons_MiniIso", 1);
  fChain->SetBranchStatus("selectedIDElectrons_MT2Activity",1);
  //fChain->SetBranchStatus("selectedIDElectrons_RA2Activity", 1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_MT2Activity", 1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_PTW", 1);
  //fChain->SetBranchStatus("selectedIDIsoElectrons_RA2Activity",1);
  fChain->SetBranchStatus("selectedIDIsoMuons_MT2Activity",1);
  fChain->SetBranchStatus("selectedIDIsoMuons_PTW",1);
  //fChain->SetBranchStatus("selectedIDIsoMuons_RA2Activity", 1);
  fChain->SetBranchStatus("selectedIDMuons_MiniIso",1);
  fChain->SetBranchStatus("selectedIDMuons_MT2Activity", 1);
  fChain->SetBranchStatus("selectedIDMuons_MTW",1);
  //fChain->SetBranchStatus("selectedIDMuons_RA2Activity", 1);
  
  fChain->SetBranchStatus("RunNum", 1);
  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchStatus("CSCTightHaloFilter", 1);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
  fChain->SetBranchStatus("eeBadScFilter", 1);
  fChain->SetBranchStatus("ElectronCharge", 1);
  fChain->SetBranchStatus("Electrons", 1);
/*  fChain->SetBranchStatus("GenElec_GenElecFromTau", 1);
  fChain->SetBranchStatus("GenEls", 1);
  fChain->SetBranchStatus("GenMu_GenMuFromTau", 1);
  fChain->SetBranchStatus("GenMus", 1);
  fChain->SetBranchStatus("GenTau_GenTauHad", 1);
  fChain->SetBranchStatus("GenTauNu", 1);
  fChain->SetBranchStatus("GenTaus", 1);
*/  fChain->SetBranchStatus("HBHENoiseFilter", 1);
  fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("IsolatedElectronTracksVeto", 1);
  fChain->SetBranchStatus("IsolatedElectronTracksVeto_MTW", 1);
  fChain->SetBranchStatus("IsolatedMuonTracksVeto", 1);
  fChain->SetBranchStatus("IsolatedMuonTracksVeto_MTW", 1);
  fChain->SetBranchStatus("IsolatedPionTracksVeto", 1);
  fChain->SetBranchStatus("IsolatedPionTracksVeto_MTW", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("JetIDloose", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorMVA", 1);
  fChain->SetBranchStatus("Jets_chargedEmEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_chargedHadronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_electronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_flavor", 1);
  fChain->SetBranchStatus("Jets_jetArea", 1);
  fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_muonMultiplicity", 1);
  fChain->SetBranchStatus("Jets_neutralEmEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_neutralHadronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_photonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_photonMultiplicity", 1);
  fChain->SetBranchStatus("Leptons", 1);
  fChain->SetBranchStatus("METFilters", 1);
  fChain->SetBranchStatus("METPhi", 1);
  fChain->SetBranchStatus("METPt", 1);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchStatus("MHT_Phi", 1);
  fChain->SetBranchStatus("MuonCharge", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("nAllVertices", 1);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchStatus("NumPhotons", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("selectedIDElectrons", 1);
  fChain->SetBranchStatus("selectedIDElectrons_MTW", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_MTW", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("selectedIDIsoMuons_MTW", 1);
  fChain->SetBranchStatus("selectedIDMuons", 1);
  fChain->SetBranchStatus("selectedIDMuons_MTW", 1);
  fChain->SetBranchStatus("TagLeptonHighPT", 1);
//  fChain->SetBranchStatus("TauDecayCands", 1);
//  fChain->SetBranchStatus("TauDecayCands_pdgID", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Weight", 1);
  fChain->SetBranchStatus("puWeight", 1);
  if(HTgen_cut>0.01)  fChain->SetBranchStatus("genHT", 1);



/*  fChain->SetBranchAddress("GenElec_MT2Activity", &GenElec_MT2Activity, &b_GenElec_MT2Activity);
  fChain->SetBranchAddress("GenElec_RA2Activity", &GenElec_RA2Activity, &b_GenElec_RA2Activity);
  fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity, &b_GenMu_MT2Activity);
  fChain->SetBranchAddress("GenMu_RA2Activity", &GenMu_RA2Activity, &b_GenMu_RA2Activity);
  fChain->SetBranchAddress("GenTau_MT2Activity", &GenTau_MT2Activity, &b_GenTau_MT2Activity);
  fChain->SetBranchAddress("GenTau_RA2Activity", &GenTau_RA2Activity, &b_GenTau_RA2Activity);
*/  fChain->SetBranchAddress("selectedIDElectrons_MiniIso", &selectedIDElectrons_MiniIso, &b_selectedIDElectrons_MiniIso);
  fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
  //fChain->SetBranchAddress("selectedIDElectrons_RA2Activity", &selectedIDElectrons_RA2Activity, &b_selectedIDElectrons_RA2Activity);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoElectrons_PTW", &selectedIDIsoElectrons_PTW, &b_selectedIDIsoElectrons_PTW);
  //fChain->SetBranchAddress("selectedIDIsoElectrons_RA2Activity", &selectedIDIsoElectrons_RA2Activity, &b_selectedIDIsoElectrons_RA2Activity);
  fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoMuons_PTW", &selectedIDIsoMuons_PTW, &b_selectedIDIsoMuons_PTW);
  //fChain->SetBranchAddress("selectedIDIsoMuons_RA2Activity", &selectedIDIsoMuons_RA2Activity, &b_selectedIDIsoMuons_RA2Activity);
  fChain->SetBranchAddress("selectedIDMuons_MiniIso", &selectedIDMuons_MiniIso, &b_selectedIDMuons_MiniIso);
  fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
  fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
  //fChain->SetBranchAddress("selectedIDMuons_RA2Activity", &selectedIDMuons_RA2Activity, &b_selectedIDMuons_RA2Activity);

  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
  fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
  fChain->SetBranchAddress("ElectronCharge", &ElectronCharge, &b_ElectronCharge);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
/*  fChain->SetBranchAddress("GenElec_GenElecFromTau", &GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
  fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
  fChain->SetBranchAddress("GenMu_GenMuFromTau", &GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
  fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
  fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad, &b_GenTau_GenTauHad);
  fChain->SetBranchAddress("GenTauNu", &GenTauNu, &b_GenTauNu);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
*/  fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
  fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
  fChain->SetBranchAddress("IsolatedElectronTracksVeto", &IsolatedElectronTracksVeto, &b_IsolatedElectronTracksVeto);
  fChain->SetBranchAddress("IsolatedElectronTracksVeto_MTW", &IsolatedElectronTracksVeto_MTW, &b_IsolatedElectronTracksVeto_MTW);
  fChain->SetBranchAddress("IsolatedMuonTracksVeto", &IsolatedMuonTracksVeto, &b_IsolatedMuonTracksVeto);
  fChain->SetBranchAddress("IsolatedMuonTracksVeto_MTW", &IsolatedMuonTracksVeto_MTW, &b_IsolatedMuonTracksVeto_MTW);
  fChain->SetBranchAddress("IsolatedPionTracksVeto", &IsolatedPionTracksVeto, &b_IsolatedPionTracksVeto);
  fChain->SetBranchAddress("IsolatedPionTracksVeto_MTW", &IsolatedPionTracksVeto_MTW, &b_IsolatedPionTracksVeto_MTW);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("JetIDloose", &JetIDloose, &b_JetIDloose);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
  fChain->SetBranchAddress("Jets_bDiscriminatorMVA", &Jets_bDiscriminatorMVA, &b_Jets_bDiscriminatorMVA);
  fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
  fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
  fChain->SetBranchAddress("Jets_flavor", &Jets_flavor, &b_Jets_flavor);
  fChain->SetBranchAddress("Jets_jetArea", &Jets_jetArea, &b_Jets_jetArea);
  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
  fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
  fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
  fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
  fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
  fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
  fChain->SetBranchAddress("METFilters", &METFilters, &b_METFilters);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHT_Phi", &MHT_Phi, &b_MHT_Phi);
  fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
  fChain->SetBranchAddress("selectedIDElectrons_MTW", &selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
  fChain->SetBranchAddress("Electrons", &selectedIDIsoElectrons, &b_selectedIDIsoElectrons);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
  fChain->SetBranchAddress("Muons", &selectedIDIsoMuons, &b_selectedIDIsoMuons);
  fChain->SetBranchAddress("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
  fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
  fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
  fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT, &b_TagLeptonHighPT);
//  fChain->SetBranchAddress("TauDecayCands", &TauDecayCands, &b_TauDecayCands);
//  fChain->SetBranchAddress("TauDecayCands_pdgID", &TauDecayCands_pdgID, &b_TauDecayCands_pdgID);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
  if(HTgen_cut>0.01) fChain->SetBranchAddress("genHT", &genHT, &b_genHT);

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
