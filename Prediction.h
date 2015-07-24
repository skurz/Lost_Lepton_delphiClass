//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 24 09:51:04 2014 by ROOT version 5.34/04
// from TTree RA2PreSelection/RA2PreSelection
// found on file: /nfs/dust/cms/user/adraeger/CSA2014/mc/wjetHT600-Inf.root
//////////////////////////////////////////////////////////

#ifndef Prediction_h
#define Prediction_h

#include <LLTools.h>
#include <THEff.h>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include "TVector2.h"
#include <cmath>
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"
// Header file for the classes stored in the TTree if any.

const bool useAsymmErrors = true;
const bool useFilterData = false;
const bool useTrigger = false;

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
const bool applyFilters_=true;
const bool applyDiLepCorrection_=true;

const UShort_t NJetsLow_=2;
const UShort_t NJetsMedium_=5;
const UShort_t NJetsMedium2_=7;
const UShort_t NJetsHigh_=8;

// uncertainties
const double MuAccUncertaintyDown_ = 9;  // pdf

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
//using either oldschool th1/2 which have wrong error calculations or the updated tefficneices
const bool UseUpdatedTEfficiencies_=false;
const bool UseTagAndProbeEffIso_=false; // warning overriges all other choices for isolation efficiency
const bool UseTagAndProbeEffReco_=false; // warning overriges all other choices for reconstruction efficiency

const bool MuMTWSearchBinUse_=false; // warning overwrites UseUpdatedTEfficiencies_
const bool MuDiLepContributionMTWAppliedEffSearchBinUse_=false;
const bool MuIsoSearchBinUse_=false; 
const bool MuRecoSearchBinUse_=false; 
const bool MuAccSearchBinUse_=false;  


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
  
  Float_t totalWeight_, totalWeightDiLep_, totalWeightDiLepIsoTrackReduced_,totalWeightDiLepIsoMuTrackReduced_,totalWeightDiLepIsoElecTrackReduced_,totalWeightDiLepIsoPionTrackReduced_,totalWeightDiLepIsoTrackReducedCombined_;
  Float_t         selectedIDIsoMuonsActivity[5];
  Float_t         selectedIDIsoElectronsActivity[5];
  Float_t         selectedIDIsoMuonsDeltaRJet[5];
  Float_t         selectedIDIsoMuonsRelPTJet[5];
  Float_t         selectedIDIsoElectronsDeltaRJet[5];
  Float_t         selectedIDIsoElectronsRelPTJet[5];
  UShort_t searchBin_, Bin_;
  
  // search bin definition
  SearchBins* searchBinsRef_;
  
  // isolated track prediction
  bool IsolatedTracksMuMatched_, IsolatedTracksElecMatched_;
  
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
  Int_t           METFilters;
  Int_t           CSCTightHaloFilter;
  Int_t           HBHENoiseFilter;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           NVtx;
  Int_t           isoTracks;
  Int_t           isoElectronTracks;
  Int_t           isoMuonTracks;
  Int_t           isoPionTracks;
  Int_t           Leptons;
  Int_t           TagLeptonHighPT;
  Int_t           NJets;
  Int_t           BTags;
  Float_t         Weight;
  Float_t         HT;
  Float_t         MHT;
  Float_t         DeltaPhi1;
  Float_t         DeltaPhi2;
  Float_t         DeltaPhi3;
  Float_t         minDeltaPhiN;
  Float_t         DeltaPhiN1;
  Float_t         DeltaPhiN2;
  Float_t         DeltaPhiN3;
  Float_t         METPt;
  Float_t         METPhi;
  UChar_t         JetID;
  UShort_t        MuonsNum;
  Float_t         MuonsPt[3];   //[MuonsNum]
  Float_t         MuonsEta[3];   //[MuonsNum]
  Float_t         MuonsPhi[3];   //[MuonsNum]
  Float_t         MuonsE[3];   //[MuonsNum]
  UShort_t        ElectronsNum;
  Float_t         ElectronsPt[4];   //[ElectronsNum]
  Float_t         ElectronsEta[4];   //[ElectronsNum]
  Float_t         ElectronsPhi[4];   //[ElectronsNum]
  Float_t         ElectronsE[4];   //[ElectronsNum]
  UShort_t        IsolatedElectronTracksVetoNum;
  Float_t         IsolatedElectronTracksVetoPt[2];   //[IsolatedElectronTracksVetoNum]
  Float_t         IsolatedElectronTracksVetoEta[2];   //[IsolatedElectronTracksVetoNum]
  Float_t         IsolatedElectronTracksVetoPhi[2];   //[IsolatedElectronTracksVetoNum]
  Float_t         IsolatedElectronTracksVetoE[2];   //[IsolatedElectronTracksVetoNum]
  Float_t         IsolatedElectronTracksVeto_MT[2];   //[IsolatedElectronTracksVetoNum]
  UShort_t        IsolatedMuonTracksVetoNum;
  Float_t         IsolatedMuonTracksVetoPt[2];   //[IsolatedMuonTracksVetoNum]
  Float_t         IsolatedMuonTracksVetoEta[2];   //[IsolatedMuonTracksVetoNum]
  Float_t         IsolatedMuonTracksVetoPhi[2];   //[IsolatedMuonTracksVetoNum]
  Float_t         IsolatedMuonTracksVetoE[2];   //[IsolatedMuonTracksVetoNum]
  Float_t         IsolatedMuonTracksVeto_MT[2];   //[IsolatedMuonTracksVetoNum]
  UShort_t        IsolatedPionTracksVetoNum;
  Float_t         IsolatedPionTracksVetoPt[2];   //[IsolatedPionTracksVetoNum]
  Float_t         IsolatedPionTracksVetoEta[2];   //[IsolatedPionTracksVetoNum]
  Float_t         IsolatedPionTracksVetoPhi[2];   //[IsolatedPionTracksVetoNum]
  Float_t         IsolatedPionTracksVetoE[2];   //[IsolatedPionTracksVetoNum]
  Float_t         IsolatedPionTracksVeto_MT[2];   //[IsolatedPionTracksVetoNum]
  UShort_t        selectedIDIsoMuonsNum;
  Float_t         selectedIDIsoMuonsPt[3];   //[selectedIDIsoMuonsNum]
  Float_t         selectedIDIsoMuonsEta[3];   //[selectedIDIsoMuonsNum]
  Float_t         selectedIDIsoMuonsPhi[3];   //[selectedIDIsoMuonsNum]
  Float_t         selectedIDIsoMuonsE[3];   //[selectedIDIsoMuonsNum]
  Float_t         selectedIDIsoMuons_MTW[3];   //[selectedIDIsoMuonsNum]
  UShort_t        selectedIDMuonsNum;
  Float_t         selectedIDMuonsPt[5];   //[selectedIDMuonsNum]
  Float_t         selectedIDMuonsEta[5];   //[selectedIDMuonsNum]
  Float_t         selectedIDMuonsPhi[5];   //[selectedIDMuonsNum]
  Float_t         selectedIDMuonsE[5];   //[selectedIDMuonsNum]
  Float_t         selectedIDMuons_MTW[5];   //[selectedIDMuonsNum]
  UShort_t        selectedIDIsoElectronsNum;
  Float_t         selectedIDIsoElectronsPt[4];   //[selectedIDIsoElectronsNum]
  Float_t         selectedIDIsoElectronsEta[4];   //[selectedIDIsoElectronsNum]
  Float_t         selectedIDIsoElectronsPhi[4];   //[selectedIDIsoElectronsNum]
  Float_t         selectedIDIsoElectronsE[4];   //[selectedIDIsoElectronsNum]
  Float_t         selectedIDIsoElectrons_MTW[4];   //[selectedIDIsoElectronsNum]
  UShort_t        selectedIDElectronsNum;
  Float_t         selectedIDElectronsPt[5];   //[selectedIDElectronsNum]
  Float_t         selectedIDElectronsEta[5];   //[selectedIDElectronsNum]
  Float_t         selectedIDElectronsPhi[5];   //[selectedIDElectronsNum]
  Float_t         selectedIDElectronsE[5];   //[selectedIDElectronsNum]
  Float_t         selectedIDElectrons_MTW[5];   //[selectedIDElectronsNum]
  UShort_t        SelectedPFCandidatesNum;
  Float_t         SelectedPFCandidatesPt[182];   //[SelectedPFCandidatesNum]
  Float_t         SelectedPFCandidatesEta[182];   //[SelectedPFCandidatesNum]
  Float_t         SelectedPFCandidatesPhi[182];   //[SelectedPFCandidatesNum]
  Float_t         SelectedPFCandidatesE[182];   //[SelectedPFCandidatesNum]
  Int_t           SelectedPFCandidates_Charge[182];   //[SelectedPFCandidatesNum]
  Int_t           SelectedPFCandidates_Typ[182];   //[SelectedPFCandidatesNum]
  UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
  Float_t         selectedIDIsoMuonsNoMiniIsoPt[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
  Float_t         selectedIDIsoMuonsNoMiniIsoEta[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
  Float_t         selectedIDIsoMuonsNoMiniIsoPhi[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
  Float_t         selectedIDIsoMuonsNoMiniIsoE[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
  UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
  Float_t         selectedIDIsoElectronsNoMiniIsoPt[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
  Float_t         selectedIDIsoElectronsNoMiniIsoEta[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
  Float_t         selectedIDIsoElectronsNoMiniIsoPhi[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
  Float_t         selectedIDIsoElectronsNoMiniIsoE[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
  UShort_t        JetsNum;
  Float_t         JetsPt[17];   //[JetsNum]
  Float_t         JetsEta[17];   //[JetsNum]
  Float_t         JetsPhi[17];   //[JetsNum]
  Float_t         JetsE[17];   //[JetsNum]
  Float_t         Jets_bDiscriminator[17];   //[JetsNum]
  Float_t         Jets_chargedEmEnergyFraction[17];   //[JetsNum]
  Float_t         Jets_chargedHadronEnergyFraction[17];   //[JetsNum]
  Int_t           Jets_chargedHadronMultiplicity[17];   //[JetsNum]
  Int_t           Jets_electronMultiplicity[17];   //[JetsNum]
  Float_t         Jets_jetArea[17];   //[JetsNum]
  Float_t         Jets_muonEnergyFraction[17];   //[JetsNum]
  Int_t           Jets_muonMultiplicity[17];   //[JetsNum]
  Float_t         Jets_neutralEmEnergyFraction[17];   //[JetsNum]
  Int_t           Jets_neutralHadronMultiplicity[17];   //[JetsNum]
  Float_t         Jets_photonEnergyFraction[17];   //[JetsNum]
  Int_t           Jets_photonMultiplicity[17];   //[JetsNum]
  UShort_t        slimmedElectronsNum;
  Float_t         slimmedElectronsPt[10];   //[slimmedElectronsNum]
  Float_t         slimmedElectronsEta[10];   //[slimmedElectronsNum]
  Float_t         slimmedElectronsPhi[10];   //[slimmedElectronsNum]
  Float_t         slimmedElectronsE[10];   //[slimmedElectronsNum]
  UShort_t        slimmedMuonsNum;
  Float_t         slimmedMuonsPt[29];   //[slimmedMuonsNum]
  Float_t         slimmedMuonsEta[29];   //[slimmedMuonsNum]
  Float_t         slimmedMuonsPhi[29];   //[slimmedMuonsNum]
  Float_t         slimmedMuonsE[29];   //[slimmedMuonsNum]
  std::vector<string>         *TriggerNames = 0;
  std::vector<Int_t>           *PassTrigger = 0;
  
  // List of branches
  TBranch        *b_RunNum;   //!
  TBranch        *b_LumiBlockNum;   //!
  TBranch        *b_EvtNum;   //!
  TBranch        *b_METFilters;
  TBranch        *b_CSCTightHaloFilter;
  TBranch        *b_HBHENoiseFilter;
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;
  TBranch        *b_NVtx;   //!
  TBranch        *b_isoElectronTracks;   //!
  TBranch        *b_isoMuonTracks;   //!
  TBranch        *b_isoPionTracks;   //!
  TBranch        *b_Leptons;   //!
  TBranch        *b_TagLeptonHighPT;   //!
  TBranch        *b_NJets;   //!
  TBranch        *b_BTags;   //!
  TBranch        *b_Weight;   //!
  TBranch        *b_HT;   //!
  TBranch        *b_MHT;   //!
  TBranch        *b_DeltaPhi1;   //!
  TBranch        *b_DeltaPhi2;   //!
  TBranch        *b_DeltaPhi3;   //!
  TBranch        *b_minDeltaPhiN;   //!
  TBranch        *b_DeltaPhiN1;   //!
  TBranch        *b_DeltaPhiN2;   //!
  TBranch        *b_DeltaPhiN3;   //!
  TBranch        *b_METPt;   //!
  TBranch        *b_METPhi;   //!
  TBranch        *b_JetID;   //!
  TBranch        *b_MuonsNum;   //!
  TBranch        *b_MuonsPt;   //!
  TBranch        *b_MuonsEta;   //!
  TBranch        *b_MuonsPhi;   //!
  TBranch        *b_MuonsE;   //!
  TBranch        *b_ElectronsNum;   //!
  TBranch        *b_ElectronsPt;   //!
  TBranch        *b_ElectronsEta;   //!
  TBranch        *b_ElectronsPhi;   //!
  TBranch        *b_ElectronsE;   //!
  TBranch        *b_IsolatedElectronTracksVetoNum;   //!
  TBranch        *b_IsolatedElectronTracksVetoPt;   //!
  TBranch        *b_IsolatedElectronTracksVetoEta;   //!
  TBranch        *b_IsolatedElectronTracksVetoPhi;   //!
  TBranch        *b_IsolatedElectronTracksVetoE;   //!
  TBranch        *b_IsolatedElectronTracksVeto_MT;   //!
  TBranch        *b_IsolatedMuonTracksVetoNum;   //!
  TBranch        *b_IsolatedMuonTracksVetoPt;   //!
  TBranch        *b_IsolatedMuonTracksVetoEta;   //!
  TBranch        *b_IsolatedMuonTracksVetoPhi;   //!
  TBranch        *b_IsolatedMuonTracksVetoE;   //!
  TBranch        *b_IsolatedMuonTracksVeto_MT;   //!
  TBranch        *b_IsolatedPionTracksVetoNum;   //!
  TBranch        *b_IsolatedPionTracksVetoPt;   //!
  TBranch        *b_IsolatedPionTracksVetoEta;   //!
  TBranch        *b_IsolatedPionTracksVetoPhi;   //!
  TBranch        *b_IsolatedPionTracksVetoE;   //!
  TBranch        *b_IsolatedPionTracksVeto_MT;   //!
  TBranch        *b_selectedIDIsoMuonsNum;   //!
  TBranch        *b_selectedIDIsoMuonsPt;   //!
  TBranch        *b_selectedIDIsoMuonsEta;   //!
  TBranch        *b_selectedIDIsoMuonsPhi;   //!
  TBranch        *b_selectedIDIsoMuonsE;   //!
  TBranch        *b_selectedIDIsoMuons_MTW;   //!
  TBranch        *b_selectedIDMuonsNum;   //!
  TBranch        *b_selectedIDMuonsPt;   //!
  TBranch        *b_selectedIDMuonsEta;   //!
  TBranch        *b_selectedIDMuonsPhi;   //!
  TBranch        *b_selectedIDMuonsE;   //!
  TBranch        *b_selectedIDMuons_MTW;   //!
  TBranch        *b_selectedIDIsoElectronsNum;   //!
  TBranch        *b_selectedIDIsoElectronsPt;   //!
  TBranch        *b_selectedIDIsoElectronsEta;   //!
  TBranch        *b_selectedIDIsoElectronsPhi;   //!
  TBranch        *b_selectedIDIsoElectronsE;   //!
  TBranch        *b_selectedIDIsoElectrons_MTW;   //!
  TBranch        *b_selectedIDElectronsNum;   //!
  TBranch        *b_selectedIDElectronsPt;   //!
  TBranch        *b_selectedIDElectronsEta;   //!
  TBranch        *b_selectedIDElectronsPhi;   //!
  TBranch        *b_selectedIDElectronsE;   //!
  TBranch        *b_selectedIDElectrons_MTW;   //!
  TBranch        *b_SelectedPFCandidatesNum;   //!
  TBranch        *b_SelectedPFCandidatesPt;   //!
  TBranch        *b_SelectedPFCandidatesEta;   //!
  TBranch        *b_SelectedPFCandidatesPhi;   //!
  TBranch        *b_SelectedPFCandidatesE;   //!
  TBranch        *b_SelectedPFCandidates_Charge;   //!
  TBranch        *b_SelectedPFCandidates_Typ;   //!
  TBranch        *b_selectedIDIsoMuonsNoMiniIsoNum;   //!
  TBranch        *b_selectedIDIsoMuonsNoMiniIsoPt;   //!
  TBranch        *b_selectedIDIsoMuonsNoMiniIsoEta;   //!
  TBranch        *b_selectedIDIsoMuonsNoMiniIsoPhi;   //!
  TBranch        *b_selectedIDIsoMuonsNoMiniIsoE;   //!
  TBranch        *b_selectedIDIsoElectronsNoMiniIsoNum;   //!
  TBranch        *b_selectedIDIsoElectronsNoMiniIsoPt;   //!
  TBranch        *b_selectedIDIsoElectronsNoMiniIsoEta;   //!
  TBranch        *b_selectedIDIsoElectronsNoMiniIsoPhi;   //!
  TBranch        *b_selectedIDIsoElectronsNoMiniIsoE;   //!
  TBranch        *b_JetsNum;   //!
  TBranch        *b_JetsPt;   //!
  TBranch        *b_JetsEta;   //!
  TBranch        *b_JetsPhi;   //!
  TBranch        *b_JetsE;   //!
  TBranch        *b_Jets_bDiscriminator;   //!
  TBranch        *b_Jets_chargedEmEnergyFraction;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
  TBranch        *b_Jets_chargedHadronMultiplicity;   //!
  TBranch        *b_Jets_electronMultiplicity;   //!
  TBranch        *b_Jets_jetArea;   //!
  TBranch        *b_Jets_muonEnergyFraction;   //!
  TBranch        *b_Jets_muonMultiplicity;   //!
  TBranch        *b_Jets_neutralEmEnergyFraction;   //!
  TBranch        *b_Jets_neutralHadronMultiplicity;   //!
  TBranch        *b_Jets_photonEnergyFraction;   //!
  TBranch        *b_Jets_photonMultiplicity;   //!
  TBranch        *b_slimmedElectronsNum;   //!
  TBranch        *b_slimmedElectronsPt;   //!
  TBranch        *b_slimmedElectronsEta;   //!
  TBranch        *b_slimmedElectronsPhi;   //!
  TBranch        *b_slimmedElectronsE;   //!
  TBranch        *b_slimmedMuonsNum;   //!
  TBranch        *b_slimmedMuonsPt;   //!
  TBranch        *b_slimmedMuonsEta;   //!
  TBranch        *b_slimmedMuonsPhi;   //!
  TBranch        *b_slimmedMuonsE;   //!
  TBranch        *b_TriggerNames;   //!
  TBranch        *b_PassTrigger;   //!
  
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
  if(useFilterData){
    fChain->SetBranchAddress("METFilters", &METFilters, &b_METFilters);
    fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
  }
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
  fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
  fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT, &b_TagLeptonHighPT);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
  fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
  fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
  fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
  fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
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
  if(useTrigger){
    fChain->SetBranchAddress("PassTrigger", &PassTrigger, &b_PassTrigger);
    fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  }
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
