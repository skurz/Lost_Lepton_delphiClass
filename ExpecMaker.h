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
#include "btag/BTagCorrector.h"

TFile *outPutFile = 0;

using std::vector;
using std::cout;
using std::cerr;
using std::endl;

////////////////////////
//////// Options
///////////////////////

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;  //<-check------------------------

////////////////////////
//////// Usually don't have to be changed
///////////////////////

// useFilterData = true; unless you want to run without MET filters
const bool useFilterData = true;
// useTrigger = false; no simulated triggers in MC
const bool useTrigger = false;
// useTriggerEffWeight = true; correct for trigger inefficiency
const bool useTriggerEffWeight = false; //<-check------------------------ right now: disabled for 2016 data!

// Write some variables to tree for isotrack studies
const bool doIsoTrackStudies = false;
// Write some variables to tree for Jack's isotrack studies
const bool doTAPtrees = false;

// Correction for tracking inefficiency due to high luminosity
const bool doMuIsoTrackTrackingCorrection = false;

//////////////////////
//// IMPORTANT: running on signal not fully implemented yet (e.g. get x-sec/weight from txt file)
// If needed, look up at Prediction.C
// Do PU reweighting. true for signal scan
const bool doPUreweighting = false;
// False for FastSim (only!)
const bool applyJetID = true;
// NOTE: This corrections need the histograms contained in the Skims. Please adjust 'path_toSkims' below. Also, filenames of Skims and nTuples have to be the same at the moment.
const bool doBTagCorrFullSim = true;
const bool doBTagCorrFastSim = false;

// scaleMet = 0: keep things the way they are
// scaleMet = +-: scale MET up/down for MTW calculation (only!) by 30%
const int scaleMet = 0;
// propagate JEC only. +/-1 = up/down
//const int propagateJECtoMET = 1; // not used anymore

// apply filters
const bool applyFilters_=true;

// bTag corrections
const string path_toSkims("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/SLe/tree_");
const string path_bTagCalib("btag/CSVv2_ichep.csv");
const string path_bTagCalibFastSim("btag/CSV_13TEV_Combined_20_11_2015.csv");

// Muon tracking inefficiency
const TString path_muonTrk("SFs/general_tracks_and_early_general_tracks_corr_ratio.root");
const TString hist_muonTrkHighPt("mutrksfptg10");
const TString hist_muonTrkLowPt("mutrksfptl10");

////////////////////////
//////// Don't change anything below
///////////////////////

// cuts baseline
const double minHT_=300;
const double minMHT_=250;
const double minNJets_=1.5;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;

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
const double maxDeltaRGenMuToTrack_ = 0.2;
const double maxDiffPtGenMuToTrack_ = 0.5;
const double maxDeltaRRecoIsoMuToTrack_ = 0.2;
const double maxDiffPtRecoIsoMuToTrack_ = 0.5;

const double maxDeltaRGenElecToTrack_ = 0.3;
const double maxDiffPtGenElecToTrack_ = 0.5;
const double maxDeltaRRecoIsoElecToTrack_ = 0.3;
const double maxDiffPtRecoIsoElecToTrack_ = 0.5;

const double maxDeltaRGenTauToTrack_ = 0.3;
const double maxDiffPtGenTauToTrack_ = 0.5;

const double maxDeltaRGenToRecoIsoTrack_= 0.3;
const double maxDiffPtGenToRecoIsoTrack_=0.5;


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

  TH1D * h_muTrkLowPtSF = 0;
  TH1D * h_muTrkHighPtSF = 0;

  BTagCorrector *btagcorr = 0;
  std::vector<double> bTagProb;

  TString treeName = " ";


 // Storing stuff
  TTree *tExpectation_ = 0;

  //  template<> void TreeObject<TLorentzVector>::AddBranch() { tree->Branch(nameInTree.c_str(),nameInTree.c_str(),&value); }
  
  SearchBins *SearchBins_;
  SearchBins *SearchBinsQCD_;
// eff variables fot the tree
  UShort_t Expectation;
  UShort_t ExpectationReductionIsoTrack;
  UShort_t GenMuonsNum_, GenElectronsNum_, GenTausNum_;
  UShort_t muIso, muReco, muAcc, muMTW, muTotal;
  UShort_t elecIso, elecReco, elecAcc;
  std::vector<UShort_t> muIsoTrackMatchedToGenMu, elecIsoTrackMatchedToGenMu, pionIsoTrackMatchedToGenMu;
  std::vector<UShort_t> muIsoTrackMatchedToGenElec, elecIsoTrackMatchedToGenElec, pionIsoTrackMatchedToGenElec;
  std::vector<UShort_t> muIsoTrackMatchedToGenSingleProngTau, elecIsoTrackMatchedToGenSingleProngTau, pionIsoTrackMatchedToGenSingleProngTau;
  std::vector<UShort_t>         MuonsPromptMatched;
  std::vector<UShort_t>         ElectronsPromptMatched;

  std::vector<Float_t> GenMuDeltaRJet_, GenMuRelPTJet_;
  std::vector<Float_t> GenElecDeltaRJet_, GenElecRelPTJet_;

  // di lep
  UShort_t ExpectationDiLep_, MuDiLepControlSample_, ElecDiLepControlSample_;
  
  UShort_t Bin_, BinQCD_; 
  
  UShort_t MuPurity_, ElecPurity_;
  
  
  Float_t mtw;
  Float_t mtw_METup;
  Float_t mtw_METdown;

  UShort_t MuonsNoIsoNum_, MuonsNum_;
  UShort_t ElectronsNoIsoNum_, ElectronsNum_;

  
  Int_t   isoTracksNum;
  vector<TLorentzVector> isoElectronTracks;
  vector<double>  isoElectronTracks_activity;
  vector<int>     isoElectronTracks_charge;
  vector<double>  isoElectronTracks_mT;
  vector<double>  isoElectronTracks_trkiso;
  vector<TLorentzVector> isoMuonTracks;
  vector<double>  isoMuonTracks_activity;
  vector<int>     isoMuonTracks_charge;
  vector<double>  isoMuonTracks_mT;
  vector<double>  isoMuonTracks_trkiso;
  vector<TLorentzVector> isoPionTracks;
  vector<double>  isoPionTracks_activity;
  vector<int>     isoPionTracks_charge;
  vector<double>  isoPionTracks_mT;
  vector<double>  isoPionTracks_trkiso;
  
  // Declaration of leaf types
  Double_t        madHT;
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  Bool_t          BadChargedCandidateFilter;
  Bool_t          BadPFMuonFilter;
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
  //Bool_t           eeBadSc4Filter;
  std::vector<TLorentzVector> *GenElectrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<TLorentzVector> *GenTaus=0;
  Int_t           globalTightHalo2016Filter;
  Int_t           HBHENoiseFilter;
  Int_t           HBHEIsoNoiseFilter;
  Double_t        HT;
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;
  std::vector<TLorentzVector> *Jets=0;
  Double_t        METPhi;
  Double_t        MET;
  Double_t        PFCaloMETRatio;
  std::vector<double>   *METUp=0;
  std::vector<double>   *METDown=0;
  std::vector<double>   *METPhiUp=0;
  std::vector<double>   *METPhiDown=0;
  Double_t        MHT;
  Double_t        MHTPhi;
  Double_t        GenHT;
  Double_t        GenMHT;
  Double_t        GenMHTPhi;
  Int_t           NJets;
  Int_t           NVtx;
  std::vector<TLorentzVector> *ElectronsNoIso=0;
  std::vector<double>  *ElectronsNoIso_MTW=0;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<double>  *Electrons_MTW=0;
  std::vector<TLorentzVector> *Muons=0;
  std::vector<double>  *Muons_MTW=0;
  std::vector<TLorentzVector> *MuonsNoIso=0;
  std::vector<double>  *MuonsNoIso_MTW=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  Double_t        Weight;
  Double_t        puWeight;
  Double_t        TrueNumInteractions;
  std::vector<double>  *GenElectrons_MT2Activity=0;
  std::vector<double>  *GenMuons_MT2Activity=0;
  std::vector<double>  *GenTaus_MT2Activity=0;
  std::vector<double>  *ElectronsNoIso_MT2Activity=0;
  std::vector<double>  *Electrons_MT2Activity=0;
  std::vector<double>  *MuonsNoIso_MT2Activity=0;
  std::vector<double>  *Muons_MT2Activity=0;
  std::vector<double>  *PDFweights=0;
  std::vector<double>  *ScaleWeights=0;
  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<double>     *Jets_muonEnergyFraction=0;
  std::vector<bool>    *Jets_HTMask=0;
  Double_t        cosDTT=0;
  Double_t        genCosDTT=0;
  vector<TLorentzVector> *TAPElectronTracks = 0;
  vector<double>  *TAPElectronTracks_activity = 0;
  vector<int>     *TAPElectronTracks_charge = 0;
  vector<double>  *TAPElectronTracks_mT = 0;
  vector<double>  *TAPElectronTracks_trkiso = 0;
  vector<TLorentzVector> *TAPMuonTracks = 0;
  vector<double>  *TAPMuonTracks_activity = 0;
  vector<int>     *TAPMuonTracks_charge = 0;
  vector<double>  *TAPMuonTracks_mT = 0;
  vector<double>  *TAPMuonTracks_trkiso = 0;
  vector<TLorentzVector> *TAPPionTracks = 0;
  vector<double>  *TAPPionTracks_activity = 0;
  vector<int>     *TAPPionTracks_charge = 0;
  vector<double>  *TAPPionTracks_mT = 0;
  vector<double>  *TAPPionTracks_trkiso = 0;
  vector<bool>    *GenElectrons_fromTau=0;
  vector<double>  *GenElectrons_RecoTrkAct=0;
  vector<double>  *GenElectrons_RecoTrkd3=0;
  vector<double>  *GenElectrons_RecoTrkIso=0;
  vector<bool>    *GenMuons_fromTau=0;
  vector<double>  *GenMuons_RecoTrkAct=0;
  vector<double>  *GenMuons_RecoTrkd3=0;
  vector<double>  *GenMuons_RecoTrkIso=0;
  vector<bool>    *GenTaus_had=0;
  vector<double>  *GenTaus_LeadRecoTrkAct=0;
  vector<double>  *GenTaus_LeadRecoTrkd3=0;
  vector<double>  *GenTaus_LeadRecoTrkIso=0;
  vector<TLorentzVector> *GenTaus_LeadTrk=0;
  vector<int>     *GenTaus_NProngs=0;
  vector<TLorentzVector> *GenTaus_Nu=0;



  // List of branches
  TBranch        *b_madHT=0;
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BadChargedCandidateFilter=0;
  TBranch        *b_BadPFMuonFilter=0;
  TBranch        *b_BTags=0;   //!
  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  //TBranch        *b_eeBadSc4Filter=0;   //!
  TBranch        *b_GenElectrons=0;   //!
  TBranch        *b_GenMuons=0;   //!
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_globalTightHalo2016Filter=0;   //!
  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch        *b_PFCaloMETRatio=0;   //!
  TBranch        *b_METUp=0;   //!
  TBranch        *b_METDown=0;   //!
  TBranch        *b_METPhiUp=0;   //!
  TBranch        *b_METPhiDown=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_GenHT=0;
  TBranch        *b_GenMHT=0;   //!
  TBranch        *b_GenMHTPhi=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_NumPhotons=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_ElectronsNoIso=0;   //!
  TBranch        *b_ElectronsNoIso_MTW=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_Electrons_MTW=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_Muons_MTW=0;   //!
  TBranch        *b_MuonsNoIso=0;   //!
  TBranch        *b_MuonsNoIso_MTW=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_puWeight=0;   //!
  TBranch        *b_PDFweights=0;   //!
  TBranch        *b_ScaleWeights=0;   //!
  TBranch        *b_TrueNumInteractions=0;   //!
  TBranch        *b_GenElectrons_MT2Activity=0;   //!
  TBranch        *b_GenMuons_MT2Activity=0;   //!
  TBranch        *b_GenTaus_MT2Activity=0;   //!
  TBranch        *b_ElectronsNoIso_MT2Activity=0;   //!
  TBranch        *b_Electrons_MT2Activity=0;   //!
  TBranch        *b_Muons_MT2Activity=0;   //!
  TBranch        *b_MuonsNoIso_MT2Activity=0;   //!
  TBranch        *b_Jets_hadronFlavor=0;   //!
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_HTMask=0;   //!
  TBranch        *b_TAPElectronTracks=0;   //!
  TBranch        *b_TAPElectronTracks_activity=0;   //!
  TBranch        *b_TAPElectronTracks_charge=0;   //!
  TBranch        *b_TAPElectronTracks_mT=0;   //!
  TBranch        *b_TAPElectronTracks_trkiso=0;   //!
  TBranch        *b_TAPMuonTracks=0;   //!
  TBranch        *b_TAPMuonTracks_activity=0;   //!
  TBranch        *b_TAPMuonTracks_charge=0;   //!
  TBranch        *b_TAPMuonTracks_mT=0;   //!
  TBranch        *b_TAPMuonTracks_trkiso=0;   //!
  TBranch        *b_TAPPionTracks=0;   //!
  TBranch        *b_TAPPionTracks_activity=0;   //!
  TBranch        *b_TAPPionTracks_charge=0;   //!
  TBranch        *b_TAPPionTracks_mT=0;   //!
  TBranch        *b_TAPPionTracks_trkiso=0;   //!
  TBranch        *b_GenElectrons_fromTau=0;
  TBranch        *b_GenElectrons_RecoTrkAct=0;
  TBranch        *b_GenElectrons_RecoTrkd3=0;
  TBranch        *b_GenElectrons_RecoTrkIso=0;
  TBranch        *b_GenMuons_fromTau=0;
  TBranch        *b_GenMuons_RecoTrkAct=0;
  TBranch        *b_GenMuons_RecoTrkd3=0;
  TBranch        *b_GenMuons_RecoTrkIso=0;
  TBranch        *b_GenTaus_had=0;
  TBranch        *b_GenTaus_LeadRecoTrkAct=0;
  TBranch        *b_GenTaus_LeadRecoTrkd3=0;
  TBranch        *b_GenTaus_LeadRecoTrkIso=0;
  TBranch        *b_GenTaus_LeadTrk=0;
  TBranch        *b_GenTaus_NProngs;   //!
  TBranch        *b_GenTaus_Nu=0;


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

  std::cout << "madHT cut: " << HTgen_cut << std::endl;

  std::cout << "Saving file to: " << fileName << std::endl;

  if(doPUreweighting){
    pufile = TFile::Open("PU/PileupHistograms_1117.root","READ");
    puhist = (TH1*)pufile->Get("pu_weights_central");
  }

  // Open histograms for SFs
  TFile *muTrkSF_histFile = TFile::Open(path_muonTrk, "READ");
  h_muTrkLowPtSF = (TH1D*) muTrkSF_histFile->Get(hist_muonTrkLowPt)->Clone();
  h_muTrkHighPtSF = (TH1D*) muTrkSF_histFile->Get(hist_muonTrkHighPt)->Clone();

  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("RunNum", 1);
  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchStatus("BTags", 1);
  //fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
  //fChain->SetBranchStatus("BadPFMuonFilter", 1);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
  fChain->SetBranchStatus("eeBadScFilter", 1);
  //fChain->SetBranchStatus("eeBadSc4Filter", 1);
  //fChain->SetBranchStatus("CSCTightHaloFilter", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("GenElectrons", 1);
  fChain->SetBranchStatus("GenMuons", 1);
  fChain->SetBranchStatus("GenTaus", 1);
  //fChain->SetBranchStatus("globalTightHalo2016Filter", 1);
  fChain->SetBranchStatus("HBHENoiseFilter", 1);
  fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("METPhi", 1);
  fChain->SetBranchStatus("MET", 1);
  fChain->SetBranchStatus("PFCaloMETRatio", 1);
  fChain->SetBranchStatus("METUp", 1);
  fChain->SetBranchStatus("METDown", 1);
  fChain->SetBranchStatus("METPhiUp", 1);
  fChain->SetBranchStatus("METPhiDown", 1);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchStatus("MHTPhi", 1);
  fChain->SetBranchStatus("GenMHT", 1);
  fChain->SetBranchStatus("GenMHTPhi", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("ElectronsNoIso", 1);
  fChain->SetBranchStatus("ElectronsNoIso_MTW", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Electrons_MTW", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("Muons_MTW", 1);
  fChain->SetBranchStatus("MuonsNoIso", 1);
  fChain->SetBranchStatus("MuonsNoIso_MTW", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Weight", 1);
  fChain->SetBranchStatus("puWeight", 1);
  fChain->SetBranchStatus("PDFweights", 1);
  fChain->SetBranchStatus("ScaleWeights", 1);
  fChain->SetBranchStatus("ElectronsNoIso", 1);
  fChain->SetBranchStatus("GenHT", 1);
  fChain->SetBranchStatus("madHT", 1);
  fChain->SetBranchStatus("TrueNumInteractions", 1);
  fChain->SetBranchStatus("GenElectrons_MT2Activity",1);
  fChain->SetBranchStatus("GenMuons_MT2Activity", 1);
  fChain->SetBranchStatus("GenTaus_MT2Activity",1);
  fChain->SetBranchStatus("ElectronsNoIso_MT2Activity",1);
  fChain->SetBranchStatus("Electrons_MT2Activity", 1);
  fChain->SetBranchStatus("Muons_MT2Activity",1);
  fChain->SetBranchStatus("MuonsNoIso_MT2Activity", 1);
  fChain->SetBranchStatus("Jets_hadronFlavor", 1);
  fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_HTMask", 1);
  fChain->SetBranchStatus("TAPElectronTracks", 1);
  fChain->SetBranchStatus("TAPElectronTracks_activity", 1);
  fChain->SetBranchStatus("TAPElectronTracks_charge", 1);
  fChain->SetBranchStatus("TAPElectronTracks_mT", 1);
  fChain->SetBranchStatus("TAPElectronTracks_trkiso", 1);
  fChain->SetBranchStatus("TAPMuonTracks", 1);
  fChain->SetBranchStatus("TAPMuonTracks_activity", 1);
  fChain->SetBranchStatus("TAPMuonTracks_charge", 1);
  fChain->SetBranchStatus("TAPMuonTracks_mT", 1);
  fChain->SetBranchStatus("TAPMuonTracks_trkiso", 1);
  fChain->SetBranchStatus("TAPPionTracks", 1);
  fChain->SetBranchStatus("TAPPionTracks_activity", 1);
  fChain->SetBranchStatus("TAPPionTracks_charge", 1);
  fChain->SetBranchStatus("TAPPionTracks_mT", 1);
  fChain->SetBranchStatus("TAPPionTracks_trkiso", 1);
  if(doTAPtrees){
    fChain->SetBranchStatus("GenElectrons_fromTau", 1);
    fChain->SetBranchStatus("GenElectrons_RecoTrkAct", 1);
    fChain->SetBranchStatus("GenElectrons_RecoTrkd3", 1);
    fChain->SetBranchStatus("GenElectrons_RecoTrkIso", 1);
    fChain->SetBranchStatus("GenMuons_fromTau", 1);
    fChain->SetBranchStatus("GenMuons_RecoTrkAct", 1);
    fChain->SetBranchStatus("GenMuons_RecoTrkd3", 1);
    fChain->SetBranchStatus("GenMuons_RecoTrkIso", 1);
    fChain->SetBranchStatus("GenTaus_had", 1);
    fChain->SetBranchStatus("GenTaus_LeadRecoTrkAct", 1);
    fChain->SetBranchStatus("GenTaus_LeadRecoTrkd3", 1);
    fChain->SetBranchStatus("GenTaus_LeadRecoTrkIso", 1);
    fChain->SetBranchStatus("GenTaus_LeadTrk", 1);
    fChain->SetBranchStatus("GenTaus_NProngs", 1);
    fChain->SetBranchStatus("GenTaus_Nu", 1);
  }

  fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
  fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  //fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
  //fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
  fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
  fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
  //fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
  fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  //fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
  fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
  fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
  fChain->SetBranchAddress("METUp", &METUp, &b_METUp);
  fChain->SetBranchAddress("METDown", &METDown, &b_METDown);
  fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
  fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
  fChain->SetBranchAddress("GenMHTPhi", &GenMHTPhi, &b_GenMHTPhi);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("ElectronsNoIso", &ElectronsNoIso, &b_ElectronsNoIso);
  fChain->SetBranchAddress("ElectronsNoIso_MTW", &ElectronsNoIso_MTW, &b_ElectronsNoIso_MTW);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
  fChain->SetBranchAddress("MuonsNoIso", &MuonsNoIso, &b_MuonsNoIso);
  fChain->SetBranchAddress("MuonsNoIso_MTW", &MuonsNoIso_MTW, &b_MuonsNoIso_MTW);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
  fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
  fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
  fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
  fChain->SetBranchAddress("GenElectrons_MT2Activity", &GenElectrons_MT2Activity, &b_GenElectrons_MT2Activity);
  fChain->SetBranchAddress("GenMuons_MT2Activity", &GenMuons_MT2Activity, &b_GenMuons_MT2Activity);
  fChain->SetBranchAddress("GenTaus_MT2Activity", &GenTaus_MT2Activity, &b_GenTaus_MT2Activity);
  fChain->SetBranchAddress("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity, &b_ElectronsNoIso_MT2Activity);
  fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
  fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
  fChain->SetBranchAddress("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity, &b_MuonsNoIso_MT2Activity);
  fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
  fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
  fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
  fChain->SetBranchAddress("TAPElectronTracks_charge", &TAPElectronTracks_charge, &b_TAPElectronTracks_charge);
  fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
  fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
  fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
  fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
  fChain->SetBranchAddress("TAPMuonTracks_charge", &TAPMuonTracks_charge, &b_TAPMuonTracks_charge);
  fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
  fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
  fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
  fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
  fChain->SetBranchAddress("TAPPionTracks_charge", &TAPPionTracks_charge, &b_TAPPionTracks_charge);
  fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
  fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
  if(doTAPtrees){
    fChain->SetBranchAddress("GenElectrons_fromTau", &GenElectrons_fromTau, &b_GenElectrons_fromTau);
    fChain->SetBranchAddress("GenElectrons_RecoTrkAct", &GenElectrons_RecoTrkAct, &b_GenElectrons_RecoTrkAct);
    fChain->SetBranchAddress("GenElectrons_RecoTrkd3", &GenElectrons_RecoTrkd3, &b_GenElectrons_RecoTrkd3);
    fChain->SetBranchAddress("GenElectrons_RecoTrkIso", &GenElectrons_RecoTrkIso, &b_GenElectrons_RecoTrkIso);
    fChain->SetBranchAddress("GenMuons_fromTau", &GenMuons_fromTau, &b_GenMuons_fromTau);
    fChain->SetBranchAddress("GenMuons_RecoTrkAct", &GenMuons_RecoTrkAct, &b_GenMuons_RecoTrkAct);
    fChain->SetBranchAddress("GenMuons_RecoTrkd3", &GenMuons_RecoTrkd3, &b_GenMuons_RecoTrkd3);
    fChain->SetBranchAddress("GenMuons_RecoTrkIso", &GenMuons_RecoTrkIso, &b_GenMuons_RecoTrkIso);
    fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);
    fChain->SetBranchAddress("GenTaus_LeadRecoTrkAct", &GenTaus_LeadRecoTrkAct, &b_GenTaus_LeadRecoTrkAct);
    fChain->SetBranchAddress("GenTaus_LeadRecoTrkd3", &GenTaus_LeadRecoTrkd3, &b_GenTaus_LeadRecoTrkd3);
    fChain->SetBranchAddress("GenTaus_LeadRecoTrkIso", &GenTaus_LeadRecoTrkIso, &b_GenTaus_LeadRecoTrkIso);
    fChain->SetBranchAddress("GenTaus_LeadTrk", &GenTaus_LeadTrk, &b_GenTaus_LeadTrk);
    fChain->SetBranchAddress("GenTaus_NProngs", &GenTaus_NProngs, &b_GenTaus_NProngs);
    fChain->SetBranchAddress("GenTaus_Nu", &GenTaus_Nu, &b_GenTaus_Nu);
  }

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
