//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 31 11:24:01 2015 by ROOT version 6.02/05
// from TChain TreeMaker2/PreSelection/
//////////////////////////////////////////////////////////

#ifndef ExpecMaker_h
#define ExpecMaker_h

#include "SearchBins.h"
//#include "/afs/desy.de/user/k/kurzsimo/xxl-af-cms/Lost_Lepton_delphiClass/SearchBins.h"
#include "LLTools.h"
//#include "/afs/desy.de/user/k/kurzsimo/xxl-af-cms/Lost_Lepton_delphiClass/LLTools.h"

#include <iostream>
#include <vector>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TProofServ.h"
#include "TProof.h"

TFile *outPutFile = 0;

using std::vector;
using std::cout;
using std::cerr;
using std::endl;
// useFilterData = true; unless you want to run without MET filters
const bool useFilterData = true;
// useTrigger = false; no simulated triggers in MC
const bool useTrigger = false;
// useTriggerEffWeight = true; correct for trigger inefficiency
const bool useTriggerEffWeight = true;

// Do PU reweighting. true for signal scan
const bool doPUreweighting = false;  //<-check------------------------


// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;  //<-check------------------------

// scaleMet = 0: keep things the way they are
// scaleMet = +-: scale MET up/down for MTW calculation (only!) by 30%
const int scaleMet = 0;
// propagate JEC only. +/-1 = up/down
const int propagateJECtoMET = 0;

// cuts baseline
const double minHT_=500;
const double minMHT_=200;
const double minNJets_=3.4;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;
const bool applyFilters_=true;
const bool DY_=false;
// lepton cuts
const double minMuPt_=10;
const double maxMuEta_=2.4;
const double minElecPt_=10;
const double maxElecEta_=2.5;
const double mtwCut_=100;
const double minTauPt_=10;
const double maxTauEta_=2.4;

// input jet definitions
const double jetCone_=0.4;
const double jetMinPt_ = 30;

// actity around lepton
const double maxDeltaRMuActivity_=1.0;
const double maxDeltaRElecActivity_=1.0;
const double maxDeltaRIsoTrackActivity_=1.0;
const unsigned int elecActivityMethod_=0;               // ###############
const unsigned int muActivityMethod_=0;                 // ###############
const unsigned int muIsoTrackActivityMethod_=0;					// ###############
const unsigned int elecIsoTrackActivityMethod_=0;				// ###############
const unsigned int pionIsoTrackActivityMethod_=0;				// ###############
// lepton matching
const double maxDeltaRGenToRecoMu_ =0.3;
const double maxDiffPtGenToRecoMu_ =0.5;
const double maxDeltaRRecoToIsoMu_ =0.1;
const double maxDiffPtRecoToIsoMu_ =0.1;
const double maxDeltaRIsoToGenMu_ = 0.3;
const double maxDiffPtIsoToGenMu_ = 0.5;

const double maxDeltaRGenToRecoElec_ =0.3;
const double maxDiffPtGenToRecoElec_ =0.3;
const double maxDeltaRRecoToIsoElec_ =0.1;
const double maxDiffPtRecoToIsoElec_ =0.1;
const double maxDeltaRIsoToGenElec_ = 0.3;
const double maxDiffPtIsoToGenElec_ = 0.3;

// isolated tracks
const double maxDeltaRGenMuToTack_ = 0.2;
const double maxDiffPtGenMuToTack_ = 0.5;
const double maxDeltaRRecoIsoMuToTack_ = 0.2;
const double maxDiffPtRecoIsoMuToTack_ = 0.5;

const double maxDeltaRGenElecToTack_ = 0.3;
const double maxDiffPtGenElecToTack_ = 0.5;
const double maxDeltaRRecoIsoElecToTack_ = 0.3;
const double maxDiffPtRecoIsoElecToTack_ = 0.5;

const double maxDeltaRGenTauToTack_ = 0.3;
const double maxDiffPtGenTauToTack_ = 0.5;

const double maxDeltaRGenToRecoIsoTrack_= 0.3;
const double maxDiffPtGenToRecoIsoTrack_=0.5;

// stand alone isolated track prediction

const double maxDeltaRIsoTrackToMu_= 0.3;
const double maxDiffPtIsoTrackToMu_= 0.5;

const double maxDeltaRIsoTrackToElec_= 0.3;
const double maxDiffPtIsoTrackToElec_= 0.5;


class ExpecMaker : public TSelector {
public :

  void resetValues();
  bool FiltersPass();
  double MuActivity(double muEta, double muPhi, unsigned int method);
  double ElecActivity( double elecEta, double elecPhi, unsigned int method);
  double PionActivity( double pionEta, double pionPhi, unsigned int method);
  std::pair <double,double> minDeltaRLepJet(double lepPT, double lepEta, double lepPhi);
  
  TTree          *fChain=0;   //!pointer to the analyzed TTree or TChain
  std::string fname; // for fetching file name
  TString fileName;
  Double_t HTgen_cut = 0;

  TFile* pufile = 0;
  TH1* puhist = 0;
  Double_t w_pu;


 // Storing stuff
  TTree *tExpectation_ = 0;

  //  template<> void TreeObject<TLorentzVector>::AddBranch() { tree->Branch(nameInTree.c_str(),nameInTree.c_str(),&value); }
  
  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;
// eff variables fot the tree
  UShort_t Expectation;
  UShort_t ExpectationReductionIsoTrack;
  UShort_t FallsVetoLep, FallsVetoIsoTrack;
  UShort_t FallsVetoIsoTrackPT10, FallsVetoIsoTrackPT10IsoCut08, FallsVetoIsoTrackPT10IsoCut12;
  UShort_t GenMuNum_, GenElecNum_, GenTauNum_;
  UShort_t muIso, muReco, muAcc, muMTW, muTotal;
  std::vector<UShort_t> muIsoMatched, muRecoMatched;
  UShort_t elecIso, elecReco, elecAcc, elecMTW, elecTotal;
  std::vector<UShort_t> elecIsoMatched, elecRecoMatched;
  UShort_t muIsoTrack, muIsoTrackMTW;
  std::vector<UShort_t> muIsoTrackMatchedToGenMu, elecIsoTrackMatchedToGenMu, pionIsoTrackMatchedToGenMu;
  std::vector<UShort_t> muIsoTrackMatchedToGenElec, elecIsoTrackMatchedToGenElec, pionIsoTrackMatchedToGenElec;
  std::vector<UShort_t> muIsoTrackMatchedToGenSingleProngTau, elecIsoTrackMatchedToGenSingleProngTau, pionIsoTrackMatchedToGenSingleProngTau;
  std::vector<Float_t> IsolatedMuonTracksVetoActivity,IsolatedElectronTracksVetoActivity,IsolatedPionTracksVetoActivity;
  std::vector<Float_t> IsolatedMuonTracksVetoMTW,IsolatedElectronTracksVetoMTW,IsolatedPionTracksVetoMTW;
  std::vector<UShort_t>         selectedIDIsoMuonsPromptMatched;
  std::vector<Float_t>         selectedIDIsoMuonsPromptMatchedDeltaR;
  std::vector<Float_t>         selectedIDIsoMuonsPromptMatchedRelPt;
  std::vector<UShort_t>         selectedIDIsoElectronsPromptMatched;
  std::vector<Float_t>         selectedIDIsoElectronsPromptMatchedDeltaR;
  std::vector<Float_t>         selectedIDIsoElectronsPromptMatchedRelPt;
  // isolated track studies
  std::vector<UShort_t> GenMuonIsoTrackMatched, selectedIDIsoMuonsIsoTrackMatched;
  std::vector<UShort_t> GenElecIsoTrackMatched, selectedIDIsoElectronsIsoTrackMatched;
  std::vector<Float_t> GenMuDeltaRJet_, GenMuRelPTJet_;
  std::vector<Float_t> GenElecDeltaRJet_, GenElecRelPTJet_;
  std::vector<UShort_t> GenTauIsoTrackMatched;
  std::vector<UShort_t> SelectedIsoTracksMatchedToGenLepton, SelectedIsoTracksMatchedToRecoIsoLepton;
  std::vector<Float_t> SelectedIsoTracksMatchedToGenDeltaR, SelectedIsoTracksMatchedToGenRelPT;
  std::vector<Float_t> SelectedIsoTracksMatchedToRecoIsoDeltaR, SelectedIsoTracksMatchedToRecoIsoRelPT;
  
  std::vector<UShort_t> GenMuonIsolatedTracksPT10Matched, selectedIDIsoMuonsIsolatedTracksPT10Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10Matched, selectedIDIsoElectronsIsolatedTracksPT10Matched;
  std::vector<UShort_t> GenTauIsolatedTracksPT10Matched;
  std::vector<UShort_t> IsolatedTracksPT10MatchedToGenLepton, IsolatedTracksPT10MatchedToRecoIsoLepton;
  std::vector<Float_t> IsolatedTracksPT10MatchedToGenDeltaR, IsolatedTracksPT10MatchedToGenRelPT;
  std::vector<Float_t> IsolatedTracksPT10MatchedToRecoIsoDeltaR, IsolatedTracksPT10MatchedToRecoIsoRelPT;
  
  std::vector<UShort_t> GenMuonIsolatedTracksPT10IsoCut08Matched, selectedIDIsoMuonsIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10IsoCut08Matched, selectedIDIsoElectronsIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> GenTauIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> IsolatedTracksPT10IsoCut08MatchedToGenLepton, IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton;
  std::vector<Float_t> IsolatedTracksPT10IsoCut08MatchedToGenDeltaR, IsolatedTracksPT10IsoCut08MatchedToGenRelPT;
  std::vector<Float_t> IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR, IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT;
  
  
  std::vector<UShort_t> GenMuonIsolatedTracksPT10IsoCut12Matched, selectedIDIsoMuonsIsolatedTracksPT10IsoCut12Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10IsoCut12Matched, selectedIDIsoElectronsIsolatedTracksPT10IsoCut12Matched;
  std::vector<UShort_t> GenTauIsolatedTracksPT10IsoCut12Matched;
  std::vector<UShort_t> IsolatedTracksPT10IsoCut12MatchedToGenLepton, IsolatedTracksPT10IsoCut12MatchedToRecoIsoLepton;
  std::vector<Float_t> IsolatedTracksPT10IsoCut12MatchedToGenDeltaR, IsolatedTracksPT10IsoCut12MatchedToGenRelPT;
  std::vector<Float_t> IsolatedTracksPT10IsoCut12MatchedToRecoIsoDeltaR, IsolatedTracksPT10IsoCut12MatchedToRecoIsoRelPT;
  // di lep
  UShort_t ExpectationDiLep_, MuDiLepControlSample_, ElecDiLepControlSample_;
  // stand alone isolated track prediction
  UShort_t StandAloneGenMuIsoTrackMatched_, StandAloneIsoTrackToMuMatched_;
  UShort_t StandAloneGenElecIsoTrackMatched_, StandAloneIsoTrackToElecMatched_;
  UShort_t StandAloneIsoTrackToRecoMuMatched_, StandAloneIsoTrackToRecoElecMatched_;
  UShort_t IsoTrackDiLepControlSampleElec_, IsoTrackDiLepControlSampleMu_, IsoTrackDiLepElec_, IsoTrackDiLepMu_;
  

  std::vector<Float_t> IsoTrackActivity;
  UShort_t elecActivityMethod, muActivityMethod, muIsoTrackActivityMethod, elecIsoTrackActivityMethod, pionIsoTrackActivityMethod;
  bool DY;
  
  UShort_t Bin_, BinQCD_; 
  
  UShort_t MuPurity_, ElecPurity_;
  
  
  Float_t mtw, isoTrackMTW_;
  Float_t ptw, gen_ptw;
  
  // w pt spectrum extrapolation studies
  Float_t GenMuWPt_, GenElecWPt_;
  Float_t GenMuWPhi_, GenElecWPhi_;

  UShort_t selectedIDMuonsNum_, selectedIDIsoMuonsNum_;
  UShort_t selectedIDElectronsNum_, selectedIDIsoElectronsNum_;

  
  Int_t   isoTracks;
  UInt_t JetsNum_;
  
  // MTW studies TH1D s
  TH1D *RecoMuonMTWPrompt_;
  TH1D *RecoMuonMTWNonPrompt_;
  TH1D *IsoMuonMTWPrompt_;
  TH1D *IsoMuonMTWNonPrompt_;
  
  TH1D *RecoElectronMTWPrompt_;
  TH1D *RecoElectronMTWNonPrompt_;
  TH1D *IsoElectronMTWPrompt_;
  TH1D *IsoElectronMTWNonPrompt_;
  
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
  std::vector<double>  *PDFweights=0;
  std::vector<double>  *ScaleWeights=0;

  Double_t        genHT;
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  std::vector<TLorentzVector> *bestPhoton=0;
  Int_t           BTags;
  Bool_t           CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Double_t        DeltaPhiN1;
  Double_t        DeltaPhiN2;
  Double_t        DeltaPhiN3;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  Bool_t           eeBadSc4Filter;
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
  std::vector<TLorentzVector> *IsolatedMuonTracksVeto=0;
  std::vector<TLorentzVector> *IsolatedPionTracksVeto=0;
  Int_t           isoMuonTracks;
  Int_t           isoPionTracks;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>  *Jets_bDiscriminatorCSV=0;
  std::vector<double>  *Jets_bDiscriminatorMVA=0;
  std::vector<double>  *Jets_chargedEmEnergyFraction=0;
  std::vector<double>  *Jets_chargedHadronEnergyFraction=0;
  std::vector<int>     *Jets_chargedHadronMultiplicity=0;
  std::vector<int>     *Jets_electronMultiplicity=0;
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
  std::vector<double>   *METPtUp=0;
  std::vector<double>   *METPtDown=0;
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
  Double_t        TrueNumInteractions;



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


  TBranch        *b_genHT=0;

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
  TBranch        *b_eeBadSc4Filter=0;   //!
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
  TBranch        *b_IsolatedMuonTracksVeto=0;   //!
  TBranch        *b_IsolatedPionTracksVeto=0;   //!
  TBranch        *b_isoMuonTracks=0;   //!
  TBranch        *b_isoPionTracks=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_bDiscriminatorMVA=0;   //!
  TBranch        *b_Jets_chargedEmEnergyFraction=0;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction=0;   //!
  TBranch        *b_Jets_chargedHadronMultiplicity=0;   //!
  TBranch        *b_Jets_electronMultiplicity=0;   //!
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
  TBranch        *b_METPtUp=0;   //!
  TBranch        *b_METPtDown=0;   //!
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
  TBranch        *b_PDFweights=0;   //!
  TBranch        *b_ScaleWeights=0;   //!
  TBranch        *b_TrueNumInteractions=0;   //!


 ExpecMaker(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~ExpecMaker() { }
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
  
  ClassDef(ExpecMaker,0);

};

#endif

#ifdef ExpecMaker_cxx

void ExpecMaker::Init(TTree *tree)
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

  if(doPUreweighting){
    pufile = TFile::Open("PU/PileupHistograms_1117.root","READ");
    puhist = (TH1*)pufile->Get("pu_weights_central");
  }


  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("GenElec_MT2Activity",1);
//  fChain->SetBranchStatus("GenElec_RA2Activity",1);
  fChain->SetBranchStatus("GenMu_MT2Activity", 1);
//  fChain->SetBranchStatus("GenMu_RA2Activity",1);
  fChain->SetBranchStatus("GenTau_MT2Activity",1);
 // fChain->SetBranchStatus("GenTau_RA2Activity", 1);
  fChain->SetBranchStatus("selectedIDElectrons_MiniIso", 1);
  fChain->SetBranchStatus("selectedIDElectrons_MT2Activity",1);
 // fChain->SetBranchStatus("selectedIDElectrons_RA2Activity", 1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_MT2Activity", 1);
  fChain->SetBranchStatus("selectedIDIsoElectrons_PTW", 1);
//  fChain->SetBranchStatus("selectedIDIsoElectrons_RA2Activity",1);
  fChain->SetBranchStatus("selectedIDIsoMuons_MT2Activity",1);
  fChain->SetBranchStatus("selectedIDIsoMuons_PTW",1);
//  fChain->SetBranchStatus("selectedIDIsoMuons_RA2Activity", 1);
  fChain->SetBranchStatus("selectedIDMuons_MiniIso",1);
  fChain->SetBranchStatus("selectedIDMuons_MT2Activity", 1);
  fChain->SetBranchStatus("selectedIDMuons_MTW",1);
//  fChain->SetBranchStatus("selectedIDMuons_RA2Activity", 1);
   
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
  fChain->SetBranchStatus("eeBadSc4Filter", 1);
  fChain->SetBranchStatus("ElectronCharge", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("GenElec_GenElecFromTau", 1);
  fChain->SetBranchStatus("GenEls", 1);
  fChain->SetBranchStatus("GenMu_GenMuFromTau", 1);
  fChain->SetBranchStatus("GenMus", 1);
  fChain->SetBranchStatus("GenTau_GenTauHad", 1);
  fChain->SetBranchStatus("GenTauNu", 1);
  fChain->SetBranchStatus("GenTaus", 1);
  fChain->SetBranchStatus("HBHENoiseFilter", 1);
  fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("IsolatedElectronTracksVeto", 1);
  fChain->SetBranchStatus("IsolatedMuonTracksVeto", 1);
  fChain->SetBranchStatus("IsolatedPionTracksVeto", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorMVA", 1);
  fChain->SetBranchStatus("Jets_chargedEmEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_chargedHadronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_electronMultiplicity", 1);
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
  fChain->SetBranchStatus("METPtUp", 1);
  fChain->SetBranchStatus("METPtDown", 1);
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
  fChain->SetBranchStatus("TauDecayCands", 1);
  fChain->SetBranchStatus("TauDecayCands_pdgID", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Weight", 1);
  fChain->SetBranchStatus("puWeight", 1);
  fChain->SetBranchStatus("PDFweights", 1);
  fChain->SetBranchStatus("ScaleWeights", 1);
  fChain->SetBranchStatus("selectedIDElectrons", 1);
  fChain->SetBranchStatus("genHT", 1);
  fChain->SetBranchStatus("TrueNumInteractions", 1);

  fChain->SetBranchAddress("GenElec_MT2Activity", &GenElec_MT2Activity, &b_GenElec_MT2Activity);
//  fChain->SetBranchAddress("GenElec_RA2Activity", &GenElec_RA2Activity, &b_GenElec_RA2Activity);
  fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity, &b_GenMu_MT2Activity);
//  fChain->SetBranchAddress("GenMu_RA2Activity", &GenMu_RA2Activity, &b_GenMu_RA2Activity);
  fChain->SetBranchAddress("GenTau_MT2Activity", &GenTau_MT2Activity, &b_GenTau_MT2Activity);
//  fChain->SetBranchAddress("GenTau_RA2Activity", &GenTau_RA2Activity, &b_GenTau_RA2Activity);
  fChain->SetBranchAddress("selectedIDElectrons_MiniIso", &selectedIDElectrons_MiniIso, &b_selectedIDElectrons_MiniIso);
  fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
//  fChain->SetBranchAddress("selectedIDElectrons_RA2Activity", &selectedIDElectrons_RA2Activity, &b_selectedIDElectrons_RA2Activity);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoElectrons_PTW", &selectedIDIsoElectrons_PTW, &b_selectedIDIsoElectrons_PTW);
//  fChain->SetBranchAddress("selectedIDIsoElectrons_RA2Activity", &selectedIDIsoElectrons_RA2Activity, &b_selectedIDIsoElectrons_RA2Activity);
  fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
  fChain->SetBranchAddress("selectedIDIsoMuons_PTW", &selectedIDIsoMuons_PTW, &b_selectedIDIsoMuons_PTW);
//  fChain->SetBranchAddress("selectedIDIsoMuons_RA2Activity", &selectedIDIsoMuons_RA2Activity, &b_selectedIDIsoMuons_RA2Activity);
  fChain->SetBranchAddress("selectedIDMuons_MiniIso", &selectedIDMuons_MiniIso, &b_selectedIDMuons_MiniIso);
  fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
  fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
//  fChain->SetBranchAddress("selectedIDMuons_RA2Activity", &selectedIDMuons_RA2Activity, &b_selectedIDMuons_RA2Activity);

  fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
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
  fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);
  fChain->SetBranchAddress("ElectronCharge", &ElectronCharge, &b_ElectronCharge);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("GenElec_GenElecFromTau", &GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
  fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
  fChain->SetBranchAddress("GenMu_GenMuFromTau", &GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
  fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
  fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad, &b_GenTau_GenTauHad);
  fChain->SetBranchAddress("GenTauNu", &GenTauNu, &b_GenTauNu);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
  fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
  fChain->SetBranchAddress("IsolatedElectronTracksVeto", &IsolatedElectronTracksVeto, &b_IsolatedElectronTracksVeto);
  fChain->SetBranchAddress("IsolatedMuonTracksVeto", &IsolatedMuonTracksVeto, &b_IsolatedMuonTracksVeto);
  fChain->SetBranchAddress("IsolatedPionTracksVeto", &IsolatedPionTracksVeto, &b_IsolatedPionTracksVeto);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
  fChain->SetBranchAddress("Jets_bDiscriminatorMVA", &Jets_bDiscriminatorMVA, &b_Jets_bDiscriminatorMVA);
  fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
  fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
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
  fChain->SetBranchAddress("METPtUp", &METPtUp, &b_METPtUp);
  fChain->SetBranchAddress("METPtDown", &METPtDown, &b_METPtDown);
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
  fChain->SetBranchAddress("TauDecayCands", &TauDecayCands, &b_TauDecayCands);
  fChain->SetBranchAddress("TauDecayCands_pdgID", &TauDecayCands_pdgID, &b_TauDecayCands_pdgID);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
  fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
  fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
  fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
}

Bool_t ExpecMaker::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

#endif // #ifdef ExpecMaker_cxx
