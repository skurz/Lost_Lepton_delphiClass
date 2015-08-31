//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 31 11:24:01 2015 by ROOT version 6.02/05
// from TChain TreeMaker2/PreSelection/
//////////////////////////////////////////////////////////

#ifndef ExpecMaker_h
#define ExpecMaker_h

#include "SearchBins.h"
#include "LLTools.h"

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

using std::vector;
using std::cout;
using std::cerr;
using std::endl;
const bool useFilterData = true;
const bool useTrigger = false;


// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;

// cuts baseline
const double minHT_=500;
const double minMHT_=200;
const double minNJets_=3.4;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
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


class ExpecMaker {
 public :

  void resetValues();
  bool FiltersPass();
  double MuActivity(double muEta, double muPhi, unsigned int method);
  double ElecActivity( double elecEta, double elecPhi, unsigned int method);
  double PionActivity( double pionEta, double pionPhi, unsigned int method);
  std::pair <double,double> minDeltaRLepJet(double lepPT, double lepEta, double lepPhi);
  
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain


 // Storing stuff
  TTree	*tExpectation_;

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
  std::vector<UShort_t>         RecoIsoMuonPromptMatched;
  std::vector<Float_t>         RecoIsoMuonPromptMatchedDeltaR;
  std::vector<Float_t>         RecoIsoMuonPromptMatchedRelPt;
  std::vector<UShort_t>         RecoIsoElecPromptMatched;
  std::vector<Float_t>         RecoIsoElecPromptMatchedDeltaR;
  std::vector<Float_t>         RecoIsoElecPromptMatchedRelPt;
  // isolated track studies
  std::vector<UShort_t> GenMuonIsoTrackMatched, RecoIsoMuonIsoTrackMatched;
  std::vector<UShort_t> GenElecIsoTrackMatched, RecoIsoElecIsoTrackMatched;
  std::vector<Float_t> GenMuDeltaRJet_, GenMuRelPTJet_;
  std::vector<Float_t> GenElecDeltaRJet_, GenElecRelPTJet_;
  std::vector<UShort_t> GenTauIsoTrackMatched;
  std::vector<UShort_t> SelectedIsoTracksMatchedToGenLepton, SelectedIsoTracksMatchedToRecoIsoLepton;
  std::vector<Float_t> SelectedIsoTracksMatchedToGenDeltaR, SelectedIsoTracksMatchedToGenRelPT;
  std::vector<Float_t> SelectedIsoTracksMatchedToRecoIsoDeltaR, SelectedIsoTracksMatchedToRecoIsoRelPT;
	
  std::vector<UShort_t> GenMuonIsolatedTracksPT10Matched, RecoIsoMuonIsolatedTracksPT10Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10Matched, RecoIsoElecIsolatedTracksPT10Matched;
  std::vector<UShort_t> GenTauIsolatedTracksPT10Matched;
  std::vector<UShort_t> IsolatedTracksPT10MatchedToGenLepton, IsolatedTracksPT10MatchedToRecoIsoLepton;
  std::vector<Float_t> IsolatedTracksPT10MatchedToGenDeltaR, IsolatedTracksPT10MatchedToGenRelPT;
  std::vector<Float_t> IsolatedTracksPT10MatchedToRecoIsoDeltaR, IsolatedTracksPT10MatchedToRecoIsoRelPT;
	
  std::vector<UShort_t> GenMuonIsolatedTracksPT10IsoCut08Matched, RecoIsoMuonIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10IsoCut08Matched, RecoIsoElecIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> GenTauIsolatedTracksPT10IsoCut08Matched;
  std::vector<UShort_t> IsolatedTracksPT10IsoCut08MatchedToGenLepton, IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton;
  std::vector<Float_t> IsolatedTracksPT10IsoCut08MatchedToGenDeltaR, IsolatedTracksPT10IsoCut08MatchedToGenRelPT;
  std::vector<Float_t> IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR, IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT;
	
	
  std::vector<UShort_t> GenMuonIsolatedTracksPT10IsoCut12Matched, RecoIsoMuonIsolatedTracksPT10IsoCut12Matched;
  std::vector<UShort_t> GenElecIsolatedTracksPT10IsoCut12Matched, RecoIsoElecIsolatedTracksPT10IsoCut12Matched;
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
	
  // activity resetValues
  std::vector<Float_t>         RecoIsoMuonActivity, RecoMuonActivity, GenMuonActivity;
  std::vector<Float_t>         RecoIsoElectronActivity, RecoElectronActivity, GenElecActivity;
	
  std::vector<Float_t> IsoTrackActivity, GenTauActivity;
  UShort_t elecActivityMethod, muActivityMethod, muIsoTrackActivityMethod, elecIsoTrackActivityMethod, pionIsoTrackActivityMethod;
  bool DY;
	
  UShort_t Bin_, BinQCD_;	
	
  UShort_t MuPurity_, ElecPurity_;
	
	
  Float_t mtw, isoTrackMTW_;
	
  // w pt spectrum extrapolation studies
  Float_t GenMuWPt_, GenElecWPt_;
  Float_t GenMuWPhi_, GenElecWPhi_;

  UShort_t selectedIDMuonsNum_, selectedIDIsoMuonsNum_;
  UShort_t selectedIDElectronsNum_, selectedIDIsoElectronsNum_;

  
  Int_t		isoTracks;
  UInt_t JetsNum_;
	
  // MTW studies TH1F s
  TH1F *RecoMuonMTWPrompt_;
  TH1F *RecoMuonMTWNonPrompt_;
  TH1F *IsoMuonMTWPrompt_;
  TH1F *IsoMuonMTWNonPrompt_;
	
  TH1F *RecoElectronMTWPrompt_;
  TH1F *RecoElectronMTWNonPrompt_;
  TH1F *IsoElectronMTWPrompt_;
  TH1F *IsoElectronMTWNonPrompt_;
  
  // Declaration of leaf types
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  UInt_t          EvtNum;
  std::vector<TLorentzVector> *bestPhoton;
  Int_t           BTags;
  Int_t           CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhiN1;
  Double_t        DeltaPhiN2;
  Double_t        DeltaPhiN3;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  std::vector<int>     *ElectronCharge;
  std::vector<TLorentzVector> *Electrons;
  std::vector<int>     *GenElec_GenElecFromTau;
  std::vector<TLorentzVector> *GenEls;
  std::vector<int>     *GenMu_GenMuFromTau;
  std::vector<TLorentzVector> *GenMus;
  std::vector<int>     *GenTau_GenTauHad;
  std::vector<TLorentzVector> *GenTauNu;
  std::vector<TLorentzVector> *GenTaus;
  Bool_t          HBHENoiseFilter;
  Double_t        HT;
  Int_t           isoElectronTracks;
  std::vector<TLorentzVector> *IsolatedElectronTracksVeto;
  std::vector<double>  *IsolatedElectronTracksVeto_MTW;
  std::vector<TLorentzVector> *IsolatedMuonTracksVeto;
  std::vector<double>  *IsolatedMuonTracksVeto_MTW;
  std::vector<TLorentzVector> *IsolatedPionTracksVeto;
  std::vector<double>  *IsolatedPionTracksVeto_MTW;
  Int_t           isoMuonTracks;
  Int_t           isoPionTracks;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets;
  std::vector<double>  *Jets_bDiscriminatorCSV;
  std::vector<double>  *Jets_bDiscriminatorMVA;
  std::vector<double>  *Jets_chargedEmEnergyFraction;
  std::vector<double>  *Jets_chargedHadronEnergyFraction;
  std::vector<int>     *Jets_chargedHadronMultiplicity;
  std::vector<int>     *Jets_electronMultiplicity;
  std::vector<int>     *Jets_flavor;
  std::vector<double>  *Jets_jetArea;
  std::vector<double>  *Jets_muonEnergyFraction;
  std::vector<int>     *Jets_muonMultiplicity;
  std::vector<double>  *Jets_neutralEmEnergyFraction;
  std::vector<int>     *Jets_neutralHadronMultiplicity;
  std::vector<double>  *Jets_photonEnergyFraction;
  std::vector<int>     *Jets_photonMultiplicity;
  Int_t           Leptons;
  Int_t           METFilters;
  Double_t        METPhi;
  Double_t        METPt;
  Double_t        MHT;
  Double_t        MHT_Phi;
  Double_t        minDeltaPhiN;
  std::vector<int>     *MuonCharge;
  std::vector<TLorentzVector> *Muons;
  Int_t           nAllVertices;
  Int_t           NJets;
  Int_t           NumPhotons;
  Int_t           NVtx;
  std::vector<TLorentzVector> *selectedIDElectrons;
  std::vector<double>  *selectedIDElectrons_MTW;
  std::vector<TLorentzVector> *selectedIDIsoElectrons;
  std::vector<double>  *selectedIDIsoElectrons_MTW;
  std::vector<TLorentzVector> *selectedIDIsoMuons;
  std::vector<double>  *selectedIDIsoMuons_MTW;
  std::vector<TLorentzVector> *selectedIDMuons;
  std::vector<double>  *selectedIDMuons_MTW;
  Int_t           TagLeptonHighPT;
  std::vector<TLorentzVector> *TauDecayCands;
  std::vector<int>     *TauDecayCands_pdgID;
  std::vector<string>  *TriggerNames;
  std::vector<bool>    *TriggerPass;
  std::vector<int>     *TriggerPrescales;
  Double_t        Weight;

  // List of branches
  TBranch        *b_RunNum;   //!
  TBranch        *b_LumiBlockNum;   //!
  TBranch        *b_EvtNum;   //!
  TBranch        *b_bestPhoton;   //!
  TBranch        *b_BTags;   //!
  TBranch        *b_CSCTightHaloFilter;   //!
  TBranch        *b_DeltaPhi1;   //!
  TBranch        *b_DeltaPhi2;   //!
  TBranch        *b_DeltaPhi3;   //!
  TBranch        *b_DeltaPhiN1;   //!
  TBranch        *b_DeltaPhiN2;   //!
  TBranch        *b_DeltaPhiN3;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
  TBranch        *b_eeBadScFilter;   //!
  TBranch        *b_ElectronCharge;   //!
  TBranch        *b_Electrons;   //!
  TBranch        *b_GenElec_GenElecFromTau;   //!
  TBranch        *b_GenEls;   //!
  TBranch        *b_GenMu_GenMuFromTau;   //!
  TBranch        *b_GenMus;   //!
  TBranch        *b_GenTau_GenTauHad;   //!
  TBranch        *b_GenTauNu;   //!
  TBranch        *b_GenTaus;   //!
  TBranch        *b_HBHENoiseFilter;   //!
  TBranch        *b_HT;   //!
  TBranch        *b_isoElectronTracks;   //!
  TBranch        *b_IsolatedElectronTracksVeto;   //!
  TBranch        *b_IsolatedElectronTracksVeto_MTW;   //!
  TBranch        *b_IsolatedMuonTracksVeto;   //!
  TBranch        *b_IsolatedMuonTracksVeto_MTW;   //!
  TBranch        *b_IsolatedPionTracksVeto;   //!
  TBranch        *b_IsolatedPionTracksVeto_MTW;   //!
  TBranch        *b_isoMuonTracks;   //!
  TBranch        *b_isoPionTracks;   //!
  TBranch        *b_JetID;   //!
  TBranch        *b_Jets;   //!
  TBranch        *b_Jets_bDiscriminatorCSV;   //!
  TBranch        *b_Jets_bDiscriminatorMVA;   //!
  TBranch        *b_Jets_chargedEmEnergyFraction;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
  TBranch        *b_Jets_chargedHadronMultiplicity;   //!
  TBranch        *b_Jets_electronMultiplicity;   //!
  TBranch        *b_Jets_flavor;   //!
  TBranch        *b_Jets_jetArea;   //!
  TBranch        *b_Jets_muonEnergyFraction;   //!
  TBranch        *b_Jets_muonMultiplicity;   //!
  TBranch        *b_Jets_neutralEmEnergyFraction;   //!
  TBranch        *b_Jets_neutralHadronMultiplicity;   //!
  TBranch        *b_Jets_photonEnergyFraction;   //!
  TBranch        *b_Jets_photonMultiplicity;   //!
  TBranch        *b_Leptons;   //!
  TBranch        *b_METFilters;   //!
  TBranch        *b_METPhi;   //!
  TBranch        *b_METPt;   //!
  TBranch        *b_MHT;   //!
  TBranch        *b_MHT_Phi;   //!
  TBranch        *b_minDeltaPhiN;   //!
  TBranch        *b_MuonCharge;   //!
  TBranch        *b_Muons;   //!
  TBranch        *b_nAllVertices;   //!
  TBranch        *b_NJets;   //!
  TBranch        *b_NumPhotons;   //!
  TBranch        *b_NVtx;   //!
  TBranch        *b_selectedIDElectrons;   //!
  TBranch        *b_selectedIDElectrons_MTW;   //!
  TBranch        *b_selectedIDIsoElectrons;   //!
  TBranch        *b_selectedIDIsoElectrons_MTW;   //!
  TBranch        *b_selectedIDIsoMuons;   //!
  TBranch        *b_selectedIDIsoMuons_MTW;   //!
  TBranch        *b_selectedIDMuons;   //!
  TBranch        *b_selectedIDMuons_MTW;   //!
  TBranch        *b_TagLeptonHighPT;   //!
  TBranch        *b_TauDecayCands;   //!
  TBranch        *b_TauDecayCands_pdgID;   //!
  TBranch        *b_TriggerNames;   //!
  TBranch        *b_TriggerPass;   //!
  TBranch        *b_TriggerPrescales;   //!
  TBranch        *b_Weight;   //!

  ExpecMaker(TTree *tree=0);
  virtual ~ExpecMaker();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ExpecMaker_cxx
ExpecMaker::ExpecMaker(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {

#ifdef SINGLE_TREE
    // The following code should be used if you want this class to access
    // a single tree instead of a chain
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
    if (!f || !f->IsOpen()) {
      f = new TFile("Memory Directory");
    }
    f->GetObject("TreeMaker2/PreSelection",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
    TChain * chain = new TChain("TreeMaker2/PreSelection","");
    chain->Add("/eos/uscms/store/user/jbradmil/lldev/13TeV_25ns20PU.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM_1193.root/TreeMaker2/PreSelection");
    tree = chain;
#endif // SINGLE_TREE

  }
  Init(tree);
}

ExpecMaker::~ExpecMaker()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ExpecMaker::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ExpecMaker::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ExpecMaker::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  bestPhoton = 0;
  ElectronCharge = 0;
  Electrons = 0;
  GenElec_GenElecFromTau = 0;
  GenEls = 0;
  GenMu_GenMuFromTau = 0;
  GenMus = 0;
  GenTau_GenTauHad = 0;
  GenTauNu = 0;
  GenTaus = 0;
  IsolatedElectronTracksVeto = 0;
  IsolatedElectronTracksVeto_MTW = 0;
  IsolatedMuonTracksVeto = 0;
  IsolatedMuonTracksVeto_MTW = 0;
  IsolatedPionTracksVeto = 0;
  IsolatedPionTracksVeto_MTW = 0;
  Jets = 0;
  Jets_bDiscriminatorCSV = 0;
  Jets_bDiscriminatorMVA = 0;
  Jets_chargedEmEnergyFraction = 0;
  Jets_chargedHadronEnergyFraction = 0;
  Jets_chargedHadronMultiplicity = 0;
  Jets_electronMultiplicity = 0;
  Jets_flavor = 0;
  Jets_jetArea = 0;
  Jets_muonEnergyFraction = 0;
  Jets_muonMultiplicity = 0;
  Jets_neutralEmEnergyFraction = 0;
  Jets_neutralHadronMultiplicity = 0;
  Jets_photonEnergyFraction = 0;
  Jets_photonMultiplicity = 0;
  MuonCharge = 0;
  Muons = 0;
  selectedIDElectrons = 0;
  selectedIDElectrons_MTW = 0;
  selectedIDIsoElectrons = 0;
  selectedIDIsoElectrons_MTW = 0;
  selectedIDIsoMuons = 0;
  selectedIDIsoMuons_MTW = 0;
  selectedIDMuons = 0;
  selectedIDMuons_MTW = 0;
  TauDecayCands = 0;
  TauDecayCands_pdgID = 0;
  TriggerNames = 0;
  TriggerPass = 0;
  TriggerPrescales = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("bestPhoton", &bestPhoton, &b_bestPhoton);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
  fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
  fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
  fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
  fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
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
  fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
  fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
  fChain->SetBranchAddress("selectedIDElectrons_MTW", &selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
  fChain->SetBranchAddress("selectedIDIsoElectrons", &selectedIDIsoElectrons, &b_selectedIDIsoElectrons);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
  fChain->SetBranchAddress("selectedIDIsoMuons", &selectedIDIsoMuons, &b_selectedIDIsoMuons);
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
  Notify();
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

void ExpecMaker::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t ExpecMaker::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef ExpecMaker_cxx
