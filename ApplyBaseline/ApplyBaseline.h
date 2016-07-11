//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 24 04:56:27 2016 by ROOT version 6.02/05
// from TTree PreSelection/PreSelection
// found on file: /eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV6/Spring15v2.TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_3_RA2AnalysisTree.root
//////////////////////////////////////////////////////////

#ifndef ApplyBaseline_h
#define ApplyBaseline_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TProofOutputFile.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TLorentzVector.h"

class ApplyBaseline : public TSelector {
public :
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // output tree
   TTree *tOut = 0;

   TProofOutputFile* ProofFile = 0;
   TFile *outPutFile = 0;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   ULong64_t       EvtNum;
   Bool_t          BadChargedCandidateFilter;
   Bool_t          BadPFMuonFilter;
   Int_t           BTags;
   Int_t           BTagsJECdown;
   Int_t           BTagsJECup;
   Int_t           BTagsJERdown;
   Int_t           BTagsJERup;
   Int_t           BTagsMVA;
   Int_t           BTagsMVAJECdown;
   Int_t           BTagsMVAJECup;
   Int_t           BTagsMVAJERdown;
   Int_t           BTagsMVAJERup;
   Double_t        CaloMET;
   Double_t        CaloMETPhi;
   Double_t        CrossSection;
   Int_t           CSCTightHaloFilter;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi1JECdown;
   Double_t        DeltaPhi1JECup;
   Double_t        DeltaPhi1JERdown;
   Double_t        DeltaPhi1JERup;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi2JECdown;
   Double_t        DeltaPhi2JECup;
   Double_t        DeltaPhi2JERdown;
   Double_t        DeltaPhi2JERup;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi3JECdown;
   Double_t        DeltaPhi3JECup;
   Double_t        DeltaPhi3JERdown;
   Double_t        DeltaPhi3JERup;
   Double_t        DeltaPhi4;
   Double_t        DeltaPhi4JECdown;
   Double_t        DeltaPhi4JECup;
   Double_t        DeltaPhi4JERdown;
   Double_t        DeltaPhi4JERup;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   vector<int>     *ElectronCharge = 0;
   vector<TLorentzVector> *Electrons = 0;
   vector<bool>    *GenElec_GenElecFromTau = 0;
   vector<double>  *GenElec_MT2Activity = 0;
   vector<double>  *GenElec_RecoTrkAct = 0;
   vector<double>  *GenElec_RecoTrkd3 = 0;
   vector<double>  *GenElec_RecoTrkIso = 0;
   vector<TLorentzVector> *GenEls = 0;
   Double_t        GenHT;
   vector<bool>    *GenHTJetsMask = 0;
   vector<TLorentzVector> *GenJets = 0;
   Double_t        GenMET;
   Double_t        GenMETPhi;
   Double_t        GenMHT;
   vector<bool>    *GenMHTJetsMask = 0;
   Double_t        GenMHTPhi;
   vector<bool>    *GenMu_GenMuFromTau = 0;
   vector<double>  *GenMu_MT2Activity = 0;
   vector<double>  *GenMu_RecoTrkAct = 0;
   vector<double>  *GenMu_RecoTrkd3 = 0;
   vector<double>  *GenMu_RecoTrkIso = 0;
   vector<TLorentzVector> *GenMus = 0;
   vector<TLorentzVector> *GenParticles = 0;
   vector<int>     *GenParticles_ParentId = 0;
   vector<int>     *GenParticles_ParentIdx = 0;
   vector<int>     *GenParticles_PdgId = 0;
   vector<int>     *GenParticles_Status = 0;
   vector<bool>    *GenTau_GenTauHad = 0;
   vector<double>  *GenTau_MT2Activity = 0;
   vector<double>  *GenTauLeadRecoTrkAct = 0;
   vector<double>  *GenTauLeadRecoTrkd3 = 0;
   vector<double>  *GenTauLeadRecoTrkIso = 0;
   vector<TLorentzVector> *GenTauLeadTrk = 0;
   vector<TLorentzVector> *GenTauNu = 0;
   vector<TLorentzVector> *GenTaus = 0;
   Int_t           globalTightHalo2016Filter;
   Int_t           HBHEIsoNoiseFilter;  
   Int_t           HBHENoiseFilter;    
   Double_t        HT;
   Double_t        HTJECdown;
   Double_t        HTJECup;
   Double_t        HTJERdown;
   Double_t        HTJERup;
   vector<bool>    *HTJetsMask = 0;
   vector<bool>    *HTJetsMaskJECdown = 0;
   vector<bool>    *HTJetsMaskJECup = 0;
   vector<bool>    *HTJetsMaskJERdown = 0;
   vector<bool>    *HTJetsMaskJERup = 0;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Bool_t          JetID;
   Bool_t          JetIDJECdown;
   Bool_t          JetIDJECup;
   Bool_t          JetIDJERdown;
   Bool_t          JetIDJERup;
   vector<TLorentzVector> *Jets = 0;
   vector<double>  *Jets_bDiscriminatorCSV = 0;
   vector<double>  *Jets_bDiscriminatorMVA = 0;
   vector<double>  *Jets_chargedEmEnergyFraction = 0;
   vector<double>  *Jets_chargedHadronEnergyFraction = 0;
   vector<int>     *Jets_chargedHadronMultiplicity = 0;
   vector<int>     *Jets_chargedMultiplicity = 0;
   vector<int>     *Jets_electronMultiplicity = 0;
   vector<int>     *Jets_hadronFlavor = 0;
   vector<bool>    *Jets_ID = 0;
   vector<double>  *Jets_jecFactor = 0;
   vector<double>  *Jets_jecUnc = 0;
   vector<double>  *Jets_muonEnergyFraction = 0;
   vector<int>     *Jets_muonMultiplicity = 0;
   vector<double>  *Jets_neutralEmEnergyFraction = 0;
   vector<double>  *Jets_neutralHadronEnergyFraction = 0;
   vector<int>     *Jets_neutralHadronMultiplicity = 0;
   vector<int>     *Jets_neutralMultiplicity = 0;
   vector<int>     *Jets_partonFlavor = 0;
   vector<double>  *Jets_photonEnergyFraction = 0;
   vector<int>     *Jets_photonMultiplicity = 0;
   vector<double>  *Jets_qgAxis2 = 0;
   vector<double>  *Jets_qgLikelihood = 0;
   vector<int>     *Jets_qgMult = 0;
   vector<double>  *Jets_qgPtD = 0;
   vector<TLorentzVector> *JetsJECdown = 0;
   vector<double>  *JetsJECdown_bDiscriminatorCSV = 0;
   vector<double>  *JetsJECdown_bDiscriminatorMVA = 0;
   vector<int>     *JetsJECdown_hadronFlavor = 0;
   vector<bool>    *JetsJECdown_ID = 0;
   vector<int>     *JetsJECdown_partonFlavor = 0;
   vector<TLorentzVector> *JetsJECup = 0;
   vector<double>  *JetsJECup_bDiscriminatorCSV = 0;
   vector<double>  *JetsJECup_bDiscriminatorMVA = 0;
   vector<int>     *JetsJECup_hadronFlavor = 0;
   vector<bool>    *JetsJECup_ID = 0;
   vector<int>     *JetsJECup_partonFlavor = 0;
   vector<TLorentzVector> *JetsJERdown = 0;
   vector<double>  *JetsJERdown_bDiscriminatorCSV = 0;
   vector<double>  *JetsJERdown_bDiscriminatorMVA = 0;
   vector<int>     *JetsJERdown_hadronFlavor = 0;
   vector<bool>    *JetsJERdown_ID = 0;
   vector<int>     *JetsJERdown_partonFlavor = 0;
   vector<TLorentzVector> *JetsJERup = 0;
   vector<double>  *JetsJERup_bDiscriminatorCSV = 0;
   vector<double>  *JetsJERup_bDiscriminatorMVA = 0;
   vector<int>     *JetsJERup_hadronFlavor = 0;
   vector<bool>    *JetsJERup_ID = 0;
   vector<int>     *JetsJERup_partonFlavor = 0;
   Double_t        madHT;
   Double_t        MET;
   vector<double>  *METDown = 0;
   Double_t        METPhi;
   vector<double>  *METPhiDown = 0;
   vector<double>  *METPhiUp = 0;
   vector<double>  *METUp = 0;
   Double_t        MHT;
   Double_t        MHTJECdown;
   Double_t        MHTJECup;
   Double_t        MHTJERdown;
   Double_t        MHTJERup;
   vector<bool>    *MHTJetsMask = 0;
   vector<bool>    *MHTJetsMaskJECdown = 0;
   vector<bool>    *MHTJetsMaskJECup = 0;
   vector<bool>    *MHTJetsMaskJERdown = 0;
   vector<bool>    *MHTJetsMaskJERup = 0;
   Double_t        MHTPhi;
   Double_t        MHTPhiJECdown;
   Double_t        MHTPhiJECup;
   Double_t        MHTPhiJERdown;
   Double_t        MHTPhiJERup;
   Double_t        MT2;
   vector<int>     *MuonCharge = 0;
   vector<TLorentzVector> *Muons = 0;
   Int_t           nAllVertices;
   Int_t           NJets;
   Int_t           NJetsJECdown;
   Int_t           NJetsJECup;
   Int_t           NJetsJERdown;
   Int_t           NJetsJERup;
   Double_t        NumEvents;
   Int_t           NumInteractions;
   Int_t           NVtx;
   vector<int>     *PDFids = 0;
   vector<double>  *PDFweights = 0;
   Double_t	   PFCaloMETRatio;
   Double_t        puSysDown;
   Double_t        puSysUp;
   Double_t        puWeight;
   vector<double>  *ScaleWeights = 0;
   vector<TLorentzVector> *selectedIDElectrons = 0;
   vector<double>  *selectedIDElectrons_MiniIso = 0;
   vector<double>  *selectedIDElectrons_MT2Activity = 0;
   vector<double>  *selectedIDElectrons_MTW = 0;
   vector<double>  *selectedIDIsoElectrons_MT2Activity = 0;
   vector<double>  *selectedIDIsoElectrons_MTW = 0;
   vector<double>  *selectedIDIsoElectrons_PTW = 0;
   vector<double>  *selectedIDIsoMuons_MT2Activity = 0;
   vector<double>  *selectedIDIsoMuons_MTW = 0;
   vector<double>  *selectedIDIsoMuons_PTW = 0;
   vector<TLorentzVector> *selectedIDMuons = 0;
   vector<double>  *selectedIDMuons_MiniIso = 0;
   vector<double>  *selectedIDMuons_MT2Activity = 0;
   vector<double>  *selectedIDMuons_MTW = 0;
   Double_t        SusyLSPMass;
   Double_t        SusyMotherMass;
   vector<TLorentzVector> *TAPElectronTracks = 0;
   vector<double>  *TAPElectronTracks_activity = 0;
   vector<int>     *TAPElectronTracks_chg = 0;
   vector<double>  *TAPElectronTracks_mT = 0;
   vector<double>  *TAPElectronTracks_trkiso = 0;
   vector<TLorentzVector> *TAPMuonTracks = 0;
   vector<double>  *TAPMuonTracks_activity = 0;
   vector<int>     *TAPMuonTracks_chg = 0;
   vector<double>  *TAPMuonTracks_mT = 0;
   vector<double>  *TAPMuonTracks_trkiso = 0;
   vector<TLorentzVector> *TAPPionTracks = 0;
   vector<double>  *TAPPionTracks_activity = 0;
   vector<int>     *TAPPionTracks_chg = 0;
   vector<double>  *TAPPionTracks_mT = 0;
   vector<double>  *TAPPionTracks_trkiso = 0;
   vector<string>  *TriggerNames = 0;
   vector<int>     *TriggerPass = 0;
   vector<int>     *TriggerPrescales = 0;
   Double_t        TrueNumInteractions;
   Double_t        Weight;


   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_BadChargedCandidateFilter;
   TBranch        *b_BadPFMuonFilter;
   TBranch        *b_BTags;   //!
   TBranch        *b_BTagsJECdown;   //!
   TBranch        *b_BTagsJECup;   //!
   TBranch        *b_BTagsJERdown;   //!
   TBranch        *b_BTagsJERup;   //!
   TBranch        *b_BTagsMVA;   //!
   TBranch        *b_BTagsMVAJECdown;   //!
   TBranch        *b_BTagsMVAJECup;   //!
   TBranch        *b_BTagsMVAJERdown;   //!
   TBranch        *b_BTagsMVAJERup;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CrossSection;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi1JECdown;   //!
   TBranch        *b_DeltaPhi1JECup;   //!
   TBranch        *b_DeltaPhi1JERdown;   //!
   TBranch        *b_DeltaPhi1JERup;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi2JECdown;   //!
   TBranch        *b_DeltaPhi2JECup;   //!
   TBranch        *b_DeltaPhi2JERdown;   //!
   TBranch        *b_DeltaPhi2JERup;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi3JECdown;   //!
   TBranch        *b_DeltaPhi3JECup;   //!
   TBranch        *b_DeltaPhi3JERdown;   //!
   TBranch        *b_DeltaPhi3JERup;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_DeltaPhi4JECdown;   //!
   TBranch        *b_DeltaPhi4JECup;   //!
   TBranch        *b_DeltaPhi4JERdown;   //!
   TBranch        *b_DeltaPhi4JERup;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_ElectronCharge;   //!
   TBranch        *b_Electrons;   //!
   TBranch        *b_GenElec_GenElecFromTau;   //!
   TBranch        *b_GenElec_MT2Activity;   //!
   TBranch        *b_GenElec_RecoTrkAct;   //!
   TBranch        *b_GenElec_RecoTrkd3;   //!
   TBranch        *b_GenElec_RecoTrkIso;   //!
   TBranch        *b_GenEls;   //!
   TBranch        *b_GenHT;   //!
   TBranch        *b_GenHTJetsMask;   //!
   TBranch        *b_GenJets;   //!
   TBranch        *b_GenMET;   //!
   TBranch        *b_GenMETPhi;   //!
   TBranch        *b_GenMHT;   //!
   TBranch        *b_GenMHTJetsMask;   //!
   TBranch        *b_GenMHTPhi;   //!
   TBranch        *b_GenMu_GenMuFromTau;   //!
   TBranch        *b_GenMu_MT2Activity;   //!
   TBranch        *b_GenMu_RecoTrkAct;   //!
   TBranch        *b_GenMu_RecoTrkd3;   //!
   TBranch        *b_GenMu_RecoTrkIso;   //!
   TBranch        *b_GenMus;   //!
   TBranch        *b_GenParticles;   //!
   TBranch        *b_GenParticles_ParentId;   //!
   TBranch        *b_GenParticles_ParentIdx;   //!
   TBranch        *b_GenParticles_PdgId;   //!
   TBranch        *b_GenParticles_Status;   //!
   TBranch        *b_GenTau_GenTauHad;   //!
   TBranch        *b_GenTau_MT2Activity;   //!
   TBranch        *b_GenTauLeadRecoTrkAct;   //!
   TBranch        *b_GenTauLeadRecoTrkd3;   //!
   TBranch        *b_GenTauLeadRecoTrkIso;   //!
   TBranch        *b_GenTauLeadTrk;   //!
   TBranch        *b_GenTauNu;   //!
   TBranch        *b_GenTaus;   //!
   TBranch        *b_globalTightHalo2016Filter;
   TBranch        *b_HBHEIsoNoiseFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_HTJECdown;   //!
   TBranch        *b_HTJECup;   //!
   TBranch        *b_HTJERdown;   //!
   TBranch        *b_HTJERup;   //!
   TBranch        *b_HTJetsMask;   //!
   TBranch        *b_HTJetsMaskJECdown;   //!
   TBranch        *b_HTJetsMaskJECup;   //!
   TBranch        *b_HTJetsMaskJERdown;   //!
   TBranch        *b_HTJetsMaskJERup;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_JetIDJECdown;   //!
   TBranch        *b_JetIDJECup;   //!
   TBranch        *b_JetIDJERdown;   //!
   TBranch        *b_JetIDJERup;   //!
   TBranch        *b_Jets;   //!
   TBranch        *b_Jets_bDiscriminatorCSV;   //!
   TBranch        *b_Jets_bDiscriminatorMVA;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_chargedMultiplicity;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_hadronFlavor;   //!
   TBranch        *b_Jets_ID;   //!
   TBranch        *b_Jets_jecFactor;   //!
   TBranch        *b_Jets_jecUnc;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_neutralMultiplicity;   //!
   TBranch        *b_Jets_partonFlavor;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_Jets_qgAxis2;   //!
   TBranch        *b_Jets_qgLikelihood;   //!
   TBranch        *b_Jets_qgMult;   //!
   TBranch        *b_Jets_qgPtD;   //!
   TBranch        *b_JetsJECdown;   //!
   TBranch        *b_JetsJECdown_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJECdown_bDiscriminatorMVA;   //!
   TBranch        *b_JetsJECdown_hadronFlavor;   //!
   TBranch        *b_JetsJECdown_ID;   //!
   TBranch        *b_JetsJECdown_partonFlavor;   //!
   TBranch        *b_JetsJECup;   //!
   TBranch        *b_JetsJECup_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJECup_bDiscriminatorMVA;   //!
   TBranch        *b_JetsJECup_hadronFlavor;   //!
   TBranch        *b_JetsJECup_ID;   //!
   TBranch        *b_JetsJECup_partonFlavor;   //!
   TBranch        *b_JetsJERdown;   //!
   TBranch        *b_JetsJERdown_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJERdown_bDiscriminatorMVA;   //!
   TBranch        *b_JetsJERdown_hadronFlavor;   //!
   TBranch        *b_JetsJERdown_ID;   //!
   TBranch        *b_JetsJERdown_partonFlavor;   //!
   TBranch        *b_JetsJERup;   //!
   TBranch        *b_JetsJERup_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJERup_bDiscriminatorMVA;   //!
   TBranch        *b_JetsJERup_hadronFlavor;   //!
   TBranch        *b_JetsJERup_ID;   //!
   TBranch        *b_JetsJERup_partonFlavor;   //!
   TBranch        *b_madHT;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METDown;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METPhiDown;   //!
   TBranch        *b_METPhiUp;   //!
   TBranch        *b_METUp;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHTJECdown;   //!
   TBranch        *b_MHTJECup;   //!
   TBranch        *b_MHTJERdown;   //!
   TBranch        *b_MHTJERup;   //!
   TBranch        *b_MHTJetsMask;   //!
   TBranch        *b_MHTJetsMaskJECdown;   //!
   TBranch        *b_MHTJetsMaskJECup;   //!
   TBranch        *b_MHTJetsMaskJERdown;   //!
   TBranch        *b_MHTJetsMaskJERup;   //!
   TBranch        *b_MHTPhi;   //!
   TBranch        *b_MHTPhiJECdown;   //!
   TBranch        *b_MHTPhiJECup;   //!
   TBranch        *b_MHTPhiJERdown;   //!
   TBranch        *b_MHTPhiJERup;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_MuonCharge;   //!
   TBranch        *b_Muons;   //!
   TBranch        *b_nAllVertices;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NJetsJECdown;   //!
   TBranch        *b_NJetsJECup;   //!
   TBranch        *b_NJetsJERdown;   //!
   TBranch        *b_NJetsJERup;   //!
   TBranch        *b_NumEvents;   //!
   TBranch        *b_NumInteractions;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_PDFids;   //!
   TBranch        *b_PDFweights;   //!
   TBranch        *b_PFCaloMETRatio;
   TBranch        *b_puSysDown;   //!
   TBranch        *b_puSysUp;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_selectedIDElectrons;   //!
   TBranch        *b_selectedIDElectrons_MiniIso;   //!
   TBranch        *b_selectedIDElectrons_MT2Activity;   //!
   TBranch        *b_selectedIDElectrons_MTW;   //!
   TBranch        *b_selectedIDIsoElectrons_MT2Activity;   //!
   TBranch        *b_selectedIDIsoElectrons_MTW;   //!
   TBranch        *b_selectedIDIsoElectrons_PTW;   //!
   TBranch        *b_selectedIDIsoMuons_MT2Activity;   //!
   TBranch        *b_selectedIDIsoMuons_MTW;   //!
   TBranch        *b_selectedIDIsoMuons_PTW;   //!
   TBranch        *b_selectedIDMuons;   //!
   TBranch        *b_selectedIDMuons_MiniIso;   //!
   TBranch        *b_selectedIDMuons_MT2Activity;   //!
   TBranch        *b_selectedIDMuons_MTW;   //!
   TBranch        *b_SusyLSPMass;   //!
   TBranch        *b_SusyMotherMass;   //!
   TBranch        *b_TAPElectronTracks;   //!
   TBranch        *b_TAPElectronTracks_activity;   //!
   TBranch        *b_TAPElectronTracks_chg;   //!
   TBranch        *b_TAPElectronTracks_mT;   //!
   TBranch        *b_TAPElectronTracks_trkiso;   //!
   TBranch        *b_TAPMuonTracks;   //!
   TBranch        *b_TAPMuonTracks_activity;   //!
   TBranch        *b_TAPMuonTracks_chg;   //!
   TBranch        *b_TAPMuonTracks_mT;   //!
   TBranch        *b_TAPMuonTracks_trkiso;   //!
   TBranch        *b_TAPPionTracks;   //!
   TBranch        *b_TAPPionTracks_activity;   //!
   TBranch        *b_TAPPionTracks_chg;   //!
   TBranch        *b_TAPPionTracks_mT;   //!
   TBranch        *b_TAPPionTracks_trkiso;   //!
   TBranch        *b_TriggerNames;   //!
   TBranch        *b_TriggerPass;   //!
   TBranch        *b_TriggerPrescales;   //!
   TBranch        *b_TrueNumInteractions;   //!
   TBranch        *b_Weight;   //!


   ApplyBaseline(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~ApplyBaseline() { }
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

   ClassDef(ApplyBaseline,0);
};

#endif

#ifdef ApplyBaseline_cxx
void ApplyBaseline::Init(TTree *tree)
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

   fChain->SetBranchStatus("*", 0);

   fChain->SetBranchStatus("RunNum", 1);
   fChain->SetBranchStatus("LumiBlockNum", 1);
   fChain->SetBranchStatus("EvtNum", 1);
   fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
   fChain->SetBranchStatus("BadPFMuonFilter", 1);
   fChain->SetBranchStatus("BTags", 1);
   fChain->SetBranchStatus("BTagsJECdown", 1);
   fChain->SetBranchStatus("BTagsJECup", 1);
   fChain->SetBranchStatus("BTagsJERdown", 1);
   fChain->SetBranchStatus("BTagsJERup", 1);
   fChain->SetBranchStatus("BTagsMVA", 1);
   fChain->SetBranchStatus("BTagsMVAJECdown", 1);
   fChain->SetBranchStatus("BTagsMVAJECup", 1);
   fChain->SetBranchStatus("BTagsMVAJERdown", 1);
   fChain->SetBranchStatus("BTagsMVAJERup", 1);
   fChain->SetBranchStatus("CaloMET", 1);
   fChain->SetBranchStatus("CaloMETPhi", 1);
   fChain->SetBranchStatus("CrossSection", 1);
   fChain->SetBranchStatus("CSCTightHaloFilter", 1);
   fChain->SetBranchStatus("DeltaPhi1", 1);
   fChain->SetBranchStatus("DeltaPhi1JECdown", 1);
   fChain->SetBranchStatus("DeltaPhi1JECup", 1);
   fChain->SetBranchStatus("DeltaPhi1JERdown", 1);
   fChain->SetBranchStatus("DeltaPhi1JERup", 1);
   fChain->SetBranchStatus("DeltaPhi2", 1);
   fChain->SetBranchStatus("DeltaPhi2JECdown", 1);
   fChain->SetBranchStatus("DeltaPhi2JECup", 1);
   fChain->SetBranchStatus("DeltaPhi2JERdown", 1);
   fChain->SetBranchStatus("DeltaPhi2JERup", 1);
   fChain->SetBranchStatus("DeltaPhi3", 1);
   fChain->SetBranchStatus("DeltaPhi3JECdown", 1);
   fChain->SetBranchStatus("DeltaPhi3JECup", 1);
   fChain->SetBranchStatus("DeltaPhi3JERdown", 1);
   fChain->SetBranchStatus("DeltaPhi3JERup", 1);
   fChain->SetBranchStatus("DeltaPhi4", 1);
   fChain->SetBranchStatus("DeltaPhi4JECdown", 1);
   fChain->SetBranchStatus("DeltaPhi4JECup", 1);
   fChain->SetBranchStatus("DeltaPhi4JERdown", 1);
   fChain->SetBranchStatus("DeltaPhi4JERup", 1);
   fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
   fChain->SetBranchStatus("eeBadScFilter", 1);
   fChain->SetBranchStatus("ElectronCharge", 1);
   fChain->SetBranchStatus("Electrons", 1);
   fChain->SetBranchStatus("GenElec_GenElecFromTau", 1);
   fChain->SetBranchStatus("GenElec_MT2Activity", 1);
   fChain->SetBranchStatus("GenElec_RecoTrkAct", 1);
   fChain->SetBranchStatus("GenElec_RecoTrkd3", 1);
   fChain->SetBranchStatus("GenElec_RecoTrkIso", 1);
   fChain->SetBranchStatus("GenEls", 1);
   fChain->SetBranchStatus("GenHT", 1);
   fChain->SetBranchStatus("GenHTJetsMask", 1);
   fChain->SetBranchStatus("GenJets", 1);
   fChain->SetBranchStatus("GenMET", 1);
   fChain->SetBranchStatus("GenMETPhi", 1);
   fChain->SetBranchStatus("GenMHT", 1);
   fChain->SetBranchStatus("GenMHTJetsMask", 1);
   fChain->SetBranchStatus("GenMHTPhi", 1);
   fChain->SetBranchStatus("GenMu_GenMuFromTau", 1);
   fChain->SetBranchStatus("GenMu_MT2Activity", 1);
   fChain->SetBranchStatus("GenMu_RecoTrkAct", 1);
   fChain->SetBranchStatus("GenMu_RecoTrkd3", 1);
   fChain->SetBranchStatus("GenMu_RecoTrkIso", 1);
   fChain->SetBranchStatus("GenMus", 1);
   fChain->SetBranchStatus("GenParticles", 1);
   fChain->SetBranchStatus("GenParticles_ParentId", 1);
   fChain->SetBranchStatus("GenParticles_ParentIdx", 1);
   fChain->SetBranchStatus("GenParticles_PdgId", 1);
   fChain->SetBranchStatus("GenParticles_Status", 1);
   fChain->SetBranchStatus("GenTau_GenTauHad", 1);
   fChain->SetBranchStatus("GenTau_MT2Activity", 1);
   fChain->SetBranchStatus("GenTauLeadRecoTrkAct", 1);
   fChain->SetBranchStatus("GenTauLeadRecoTrkd3", 1);
   fChain->SetBranchStatus("GenTauLeadRecoTrkIso", 1);
   fChain->SetBranchStatus("GenTauLeadTrk", 1);
   fChain->SetBranchStatus("GenTauNu", 1);
   fChain->SetBranchStatus("GenTaus", 1);
   fChain->SetBranchStatus("globalTightHalo2016Filter", 1);
   fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
   fChain->SetBranchStatus("HBHENoiseFilter", 1);
   fChain->SetBranchStatus("HT", 1);
   fChain->SetBranchStatus("HTJECdown", 1);
   fChain->SetBranchStatus("HTJECup", 1);
   fChain->SetBranchStatus("HTJERdown", 1);
   fChain->SetBranchStatus("HTJERup", 1);
   fChain->SetBranchStatus("HTJetsMask", 1);
   fChain->SetBranchStatus("HTJetsMaskJECdown", 1);
   fChain->SetBranchStatus("HTJetsMaskJECup", 1);
   fChain->SetBranchStatus("HTJetsMaskJERdown", 1);
   fChain->SetBranchStatus("HTJetsMaskJERup", 1);
   fChain->SetBranchStatus("isoElectronTracks", 1);
   fChain->SetBranchStatus("isoMuonTracks", 1);
   fChain->SetBranchStatus("isoPionTracks", 1);
   fChain->SetBranchStatus("JetID", 1);
   fChain->SetBranchStatus("JetIDJECdown", 1);
   fChain->SetBranchStatus("JetIDJECup", 1);
   fChain->SetBranchStatus("JetIDJERdown", 1);
   fChain->SetBranchStatus("JetIDJERup", 1);
   fChain->SetBranchStatus("Jets", 1);
   fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("Jets_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("Jets_chargedEmEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_chargedHadronMultiplicity", 1);
   fChain->SetBranchStatus("Jets_chargedMultiplicity", 1);
   fChain->SetBranchStatus("Jets_electronMultiplicity", 1);
   fChain->SetBranchStatus("Jets_hadronFlavor", 1);
   fChain->SetBranchStatus("Jets_ID", 1);
   fChain->SetBranchStatus("Jets_jecFactor", 1);
   fChain->SetBranchStatus("Jets_jecUnc", 1);
   fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_muonMultiplicity", 1);
   fChain->SetBranchStatus("Jets_neutralEmEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_neutralHadronEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_neutralHadronMultiplicity", 1);
   fChain->SetBranchStatus("Jets_neutralMultiplicity", 1);
   fChain->SetBranchStatus("Jets_partonFlavor", 1);
   fChain->SetBranchStatus("Jets_photonEnergyFraction", 1);
   fChain->SetBranchStatus("Jets_photonMultiplicity", 1);
   fChain->SetBranchStatus("Jets_qgAxis2", 1);
   fChain->SetBranchStatus("Jets_qgLikelihood", 1);
   fChain->SetBranchStatus("Jets_qgMult", 1);
   fChain->SetBranchStatus("Jets_qgPtD", 1);
   fChain->SetBranchStatus("JetsJECdown", 1);
   fChain->SetBranchStatus("JetsJECdown_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJECdown_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJECdown_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJECdown_ID", 1);
   fChain->SetBranchStatus("JetsJECdown_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJECup", 1);
   fChain->SetBranchStatus("JetsJECup_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJECup_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJECup_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJECup_ID", 1);
   fChain->SetBranchStatus("JetsJECup_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJERdown", 1);
   fChain->SetBranchStatus("JetsJERdown_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJERdown_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJERdown_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJERdown_ID", 1);
   fChain->SetBranchStatus("JetsJERdown_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJERup", 1);
   fChain->SetBranchStatus("JetsJERup_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJERup_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJERup_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJERup_ID", 1);
   fChain->SetBranchStatus("JetsJERup_partonFlavor", 1);
   fChain->SetBranchStatus("madHT", 1);
   fChain->SetBranchStatus("MET", 1);
   fChain->SetBranchStatus("METDown", 1);
   fChain->SetBranchStatus("METPhi", 1);
   fChain->SetBranchStatus("METPhiDown", 1);
   fChain->SetBranchStatus("METPhiUp", 1);
   fChain->SetBranchStatus("METUp", 1);
   fChain->SetBranchStatus("MHT", 1);
   fChain->SetBranchStatus("MHTJECdown", 1);
   fChain->SetBranchStatus("MHTJECup", 1);
   fChain->SetBranchStatus("MHTJERdown", 1);
   fChain->SetBranchStatus("MHTJERup", 1);
   fChain->SetBranchStatus("MHTJetsMask", 1);
   fChain->SetBranchStatus("MHTJetsMaskJECdown", 1);
   fChain->SetBranchStatus("MHTJetsMaskJECup", 1);
   fChain->SetBranchStatus("MHTJetsMaskJERdown", 1);
   fChain->SetBranchStatus("MHTJetsMaskJERup", 1);
   fChain->SetBranchStatus("MHTPhi", 1);
   fChain->SetBranchStatus("MHTPhiJECdown", 1);
   fChain->SetBranchStatus("MHTPhiJECup", 1);
   fChain->SetBranchStatus("MHTPhiJERdown", 1);
   fChain->SetBranchStatus("MHTPhiJERup", 1);
   fChain->SetBranchStatus("MT2", 1);
   fChain->SetBranchStatus("MuonCharge", 1);
   fChain->SetBranchStatus("Muons", 1);
   fChain->SetBranchStatus("nAllVertices", 1);
   fChain->SetBranchStatus("NJets", 1);
   fChain->SetBranchStatus("NJetsJECdown", 1);
   fChain->SetBranchStatus("NJetsJECup", 1);
   fChain->SetBranchStatus("NJetsJERdown", 1);
   fChain->SetBranchStatus("NJetsJERup", 1);
   fChain->SetBranchStatus("NumEvents", 1);
   fChain->SetBranchStatus("NumInteractions", 1);
   fChain->SetBranchStatus("NVtx", 1);
   fChain->SetBranchStatus("PDFids", 1);
   fChain->SetBranchStatus("PDFweights", 1);
   fChain->SetBranchStatus("PFCaloMETRatio", 1);
   fChain->SetBranchStatus("puSysDown", 1);
   fChain->SetBranchStatus("puSysUp", 1);
   fChain->SetBranchStatus("puWeight", 1);
   fChain->SetBranchStatus("ScaleWeights", 1);
   fChain->SetBranchStatus("selectedIDElectrons", 1);
   fChain->SetBranchStatus("selectedIDElectrons_MiniIso", 1);
   fChain->SetBranchStatus("selectedIDElectrons_MT2Activity", 1);
   fChain->SetBranchStatus("selectedIDElectrons_MTW", 1);
   fChain->SetBranchStatus("selectedIDIsoElectrons_MT2Activity", 1);
   fChain->SetBranchStatus("selectedIDIsoElectrons_MTW", 1);
   fChain->SetBranchStatus("selectedIDIsoElectrons_PTW", 1);
   fChain->SetBranchStatus("selectedIDIsoMuons_MT2Activity", 1);
   fChain->SetBranchStatus("selectedIDIsoMuons_MTW", 1);
   fChain->SetBranchStatus("selectedIDIsoMuons_PTW", 1);
   fChain->SetBranchStatus("selectedIDMuons", 1);
   fChain->SetBranchStatus("selectedIDMuons_MiniIso", 1);
   fChain->SetBranchStatus("selectedIDMuons_MT2Activity", 1);
   fChain->SetBranchStatus("selectedIDMuons_MTW", 1);
   fChain->SetBranchStatus("SusyLSPMass", 1);
   fChain->SetBranchStatus("SusyMotherMass", 1);
   fChain->SetBranchStatus("TAPElectronTracks", 1);
   fChain->SetBranchStatus("TAPElectronTracks_activity", 1);
   fChain->SetBranchStatus("TAPElectronTracks_chg", 1);
   fChain->SetBranchStatus("TAPElectronTracks_mT", 1);
   fChain->SetBranchStatus("TAPElectronTracks_trkiso", 1);
   fChain->SetBranchStatus("TAPMuonTracks", 1);
   fChain->SetBranchStatus("TAPMuonTracks_activity", 1);
   fChain->SetBranchStatus("TAPMuonTracks_chg", 1);
   fChain->SetBranchStatus("TAPMuonTracks_mT", 1);
   fChain->SetBranchStatus("TAPMuonTracks_trkiso", 1);
   fChain->SetBranchStatus("TAPPionTracks", 1);
   fChain->SetBranchStatus("TAPPionTracks_activity", 1);
   fChain->SetBranchStatus("TAPPionTracks_chg", 1);
   fChain->SetBranchStatus("TAPPionTracks_mT", 1);
   fChain->SetBranchStatus("TAPPionTracks_trkiso", 1);
   fChain->SetBranchStatus("TriggerNames", 1);
   fChain->SetBranchStatus("TriggerPass", 1);
   fChain->SetBranchStatus("TriggerPrescales", 1);
   fChain->SetBranchStatus("TrueNumInteractions", 1);
   fChain->SetBranchStatus("Weight", 1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("BTagsJECdown", &BTagsJECdown, &b_BTagsJECdown);
   fChain->SetBranchAddress("BTagsJECup", &BTagsJECup, &b_BTagsJECup);
   fChain->SetBranchAddress("BTagsJERdown", &BTagsJERdown, &b_BTagsJERdown);
   fChain->SetBranchAddress("BTagsJERup", &BTagsJERup, &b_BTagsJERup);
   fChain->SetBranchAddress("BTagsMVA", &BTagsMVA, &b_BTagsMVA);
   fChain->SetBranchAddress("BTagsMVAJECdown", &BTagsMVAJECdown, &b_BTagsMVAJECdown);
   fChain->SetBranchAddress("BTagsMVAJECup", &BTagsMVAJECup, &b_BTagsMVAJECup);
   fChain->SetBranchAddress("BTagsMVAJERdown", &BTagsMVAJERdown, &b_BTagsMVAJERdown);
   fChain->SetBranchAddress("BTagsMVAJERup", &BTagsMVAJERup, &b_BTagsMVAJERup);
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi1JECdown", &DeltaPhi1JECdown, &b_DeltaPhi1JECdown);
   fChain->SetBranchAddress("DeltaPhi1JECup", &DeltaPhi1JECup, &b_DeltaPhi1JECup);
   fChain->SetBranchAddress("DeltaPhi1JERdown", &DeltaPhi1JERdown, &b_DeltaPhi1JERdown);
   fChain->SetBranchAddress("DeltaPhi1JERup", &DeltaPhi1JERup, &b_DeltaPhi1JERup);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi2JECdown", &DeltaPhi2JECdown, &b_DeltaPhi2JECdown);
   fChain->SetBranchAddress("DeltaPhi2JECup", &DeltaPhi2JECup, &b_DeltaPhi2JECup);
   fChain->SetBranchAddress("DeltaPhi2JERdown", &DeltaPhi2JERdown, &b_DeltaPhi2JERdown);
   fChain->SetBranchAddress("DeltaPhi2JERup", &DeltaPhi2JERup, &b_DeltaPhi2JERup);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi3JECdown", &DeltaPhi3JECdown, &b_DeltaPhi3JECdown);
   fChain->SetBranchAddress("DeltaPhi3JECup", &DeltaPhi3JECup, &b_DeltaPhi3JECup);
   fChain->SetBranchAddress("DeltaPhi3JERdown", &DeltaPhi3JERdown, &b_DeltaPhi3JERdown);
   fChain->SetBranchAddress("DeltaPhi3JERup", &DeltaPhi3JERup, &b_DeltaPhi3JERup);
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("DeltaPhi4JECdown", &DeltaPhi4JECdown, &b_DeltaPhi4JECdown);
   fChain->SetBranchAddress("DeltaPhi4JECup", &DeltaPhi4JECup, &b_DeltaPhi4JECup);
   fChain->SetBranchAddress("DeltaPhi4JERdown", &DeltaPhi4JERdown, &b_DeltaPhi4JERdown);
   fChain->SetBranchAddress("DeltaPhi4JERup", &DeltaPhi4JERup, &b_DeltaPhi4JERup);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("ElectronCharge", &ElectronCharge, &b_ElectronCharge);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("GenElec_GenElecFromTau", &GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
   fChain->SetBranchAddress("GenElec_MT2Activity", &GenElec_MT2Activity, &b_GenElec_MT2Activity);
   fChain->SetBranchAddress("GenElec_RecoTrkAct", &GenElec_RecoTrkAct, &b_GenElec_RecoTrkAct);
   fChain->SetBranchAddress("GenElec_RecoTrkd3", &GenElec_RecoTrkd3, &b_GenElec_RecoTrkd3);
   fChain->SetBranchAddress("GenElec_RecoTrkIso", &GenElec_RecoTrkIso, &b_GenElec_RecoTrkIso);
   fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
   fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
   fChain->SetBranchAddress("GenHTJetsMask", &GenHTJetsMask, &b_GenHTJetsMask);
   fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
   fChain->SetBranchAddress("GenMET", &GenMET, &b_GenMET);
   fChain->SetBranchAddress("GenMETPhi", &GenMETPhi, &b_GenMETPhi);
   fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
   fChain->SetBranchAddress("GenMHTJetsMask", &GenMHTJetsMask, &b_GenMHTJetsMask);
   fChain->SetBranchAddress("GenMHTPhi", &GenMHTPhi, &b_GenMHTPhi);
   fChain->SetBranchAddress("GenMu_GenMuFromTau", &GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
   fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity, &b_GenMu_MT2Activity);
   fChain->SetBranchAddress("GenMu_RecoTrkAct", &GenMu_RecoTrkAct, &b_GenMu_RecoTrkAct);
   fChain->SetBranchAddress("GenMu_RecoTrkd3", &GenMu_RecoTrkd3, &b_GenMu_RecoTrkd3);
   fChain->SetBranchAddress("GenMu_RecoTrkIso", &GenMu_RecoTrkIso, &b_GenMu_RecoTrkIso);
   fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
   fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
   fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
   fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
   fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
   fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
   fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad, &b_GenTau_GenTauHad);
   fChain->SetBranchAddress("GenTau_MT2Activity", &GenTau_MT2Activity, &b_GenTau_MT2Activity);
   fChain->SetBranchAddress("GenTauLeadRecoTrkAct", &GenTauLeadRecoTrkAct, &b_GenTauLeadRecoTrkAct);
   fChain->SetBranchAddress("GenTauLeadRecoTrkd3", &GenTauLeadRecoTrkd3, &b_GenTauLeadRecoTrkd3);
   fChain->SetBranchAddress("GenTauLeadRecoTrkIso", &GenTauLeadRecoTrkIso, &b_GenTauLeadRecoTrkIso);
   fChain->SetBranchAddress("GenTauLeadTrk", &GenTauLeadTrk, &b_GenTauLeadTrk);
   fChain->SetBranchAddress("GenTauNu", &GenTauNu, &b_GenTauNu);
   fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
   fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HTJECdown", &HTJECdown, &b_HTJECdown);
   fChain->SetBranchAddress("HTJECup", &HTJECup, &b_HTJECup);
   fChain->SetBranchAddress("HTJERdown", &HTJERdown, &b_HTJERdown);
   fChain->SetBranchAddress("HTJERup", &HTJERup, &b_HTJERup);
   fChain->SetBranchAddress("HTJetsMask", &HTJetsMask, &b_HTJetsMask);
   fChain->SetBranchAddress("HTJetsMaskJECdown", &HTJetsMaskJECdown, &b_HTJetsMaskJECdown);
   fChain->SetBranchAddress("HTJetsMaskJECup", &HTJetsMaskJECup, &b_HTJetsMaskJECup);
   fChain->SetBranchAddress("HTJetsMaskJERdown", &HTJetsMaskJERdown, &b_HTJetsMaskJERdown);
   fChain->SetBranchAddress("HTJetsMaskJERup", &HTJetsMaskJERup, &b_HTJetsMaskJERup);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDJECdown", &JetIDJECdown, &b_JetIDJECdown);
   fChain->SetBranchAddress("JetIDJECup", &JetIDJECup, &b_JetIDJECup);
   fChain->SetBranchAddress("JetIDJERdown", &JetIDJERdown, &b_JetIDJERdown);
   fChain->SetBranchAddress("JetIDJERup", &JetIDJERup, &b_JetIDJERup);
   fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
   fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jets_bDiscriminatorMVA", &Jets_bDiscriminatorMVA, &b_Jets_bDiscriminatorMVA);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
   fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
   fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);
   fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
   fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
   fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor, &b_Jets_partonFlavor);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("Jets_qgAxis2", &Jets_qgAxis2, &b_Jets_qgAxis2);
   fChain->SetBranchAddress("Jets_qgLikelihood", &Jets_qgLikelihood, &b_Jets_qgLikelihood);
   fChain->SetBranchAddress("Jets_qgMult", &Jets_qgMult, &b_Jets_qgMult);
   fChain->SetBranchAddress("Jets_qgPtD", &Jets_qgPtD, &b_Jets_qgPtD);
   fChain->SetBranchAddress("JetsJECdown", &JetsJECdown, &b_JetsJECdown);
   fChain->SetBranchAddress("JetsJECdown_bDiscriminatorCSV", &JetsJECdown_bDiscriminatorCSV, &b_JetsJECdown_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJECdown_bDiscriminatorMVA", &JetsJECdown_bDiscriminatorMVA, &b_JetsJECdown_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJECdown_hadronFlavor", &JetsJECdown_hadronFlavor, &b_JetsJECdown_hadronFlavor);
   fChain->SetBranchAddress("JetsJECdown_ID", &JetsJECdown_ID, &b_JetsJECdown_ID);
   fChain->SetBranchAddress("JetsJECdown_partonFlavor", &JetsJECdown_partonFlavor, &b_JetsJECdown_partonFlavor);
   fChain->SetBranchAddress("JetsJECup", &JetsJECup, &b_JetsJECup);
   fChain->SetBranchAddress("JetsJECup_bDiscriminatorCSV", &JetsJECup_bDiscriminatorCSV, &b_JetsJECup_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJECup_bDiscriminatorMVA", &JetsJECup_bDiscriminatorMVA, &b_JetsJECup_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJECup_hadronFlavor", &JetsJECup_hadronFlavor, &b_JetsJECup_hadronFlavor);
   fChain->SetBranchAddress("JetsJECup_ID", &JetsJECup_ID, &b_JetsJECup_ID);
   fChain->SetBranchAddress("JetsJECup_partonFlavor", &JetsJECup_partonFlavor, &b_JetsJECup_partonFlavor);
   fChain->SetBranchAddress("JetsJERdown", &JetsJERdown, &b_JetsJERdown);
   fChain->SetBranchAddress("JetsJERdown_bDiscriminatorCSV", &JetsJERdown_bDiscriminatorCSV, &b_JetsJERdown_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJERdown_bDiscriminatorMVA", &JetsJERdown_bDiscriminatorMVA, &b_JetsJERdown_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJERdown_hadronFlavor", &JetsJERdown_hadronFlavor, &b_JetsJERdown_hadronFlavor);
   fChain->SetBranchAddress("JetsJERdown_ID", &JetsJERdown_ID, &b_JetsJERdown_ID);
   fChain->SetBranchAddress("JetsJERdown_partonFlavor", &JetsJERdown_partonFlavor, &b_JetsJERdown_partonFlavor);
   fChain->SetBranchAddress("JetsJERup", &JetsJERup, &b_JetsJERup);
   fChain->SetBranchAddress("JetsJERup_bDiscriminatorCSV", &JetsJERup_bDiscriminatorCSV, &b_JetsJERup_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJERup_bDiscriminatorMVA", &JetsJERup_bDiscriminatorMVA, &b_JetsJERup_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJERup_hadronFlavor", &JetsJERup_hadronFlavor, &b_JetsJERup_hadronFlavor);
   fChain->SetBranchAddress("JetsJERup_ID", &JetsJERup_ID, &b_JetsJERup_ID);
   fChain->SetBranchAddress("JetsJERup_partonFlavor", &JetsJERup_partonFlavor, &b_JetsJERup_partonFlavor);
   fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METDown", &METDown, &b_METDown);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
   fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
   fChain->SetBranchAddress("METUp", &METUp, &b_METUp);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHTJECdown", &MHTJECdown, &b_MHTJECdown);
   fChain->SetBranchAddress("MHTJECup", &MHTJECup, &b_MHTJECup);
   fChain->SetBranchAddress("MHTJERdown", &MHTJERdown, &b_MHTJERdown);
   fChain->SetBranchAddress("MHTJERup", &MHTJERup, &b_MHTJERup);
   fChain->SetBranchAddress("MHTJetsMask", &MHTJetsMask, &b_MHTJetsMask);
   fChain->SetBranchAddress("MHTJetsMaskJECdown", &MHTJetsMaskJECdown, &b_MHTJetsMaskJECdown);
   fChain->SetBranchAddress("MHTJetsMaskJECup", &MHTJetsMaskJECup, &b_MHTJetsMaskJECup);
   fChain->SetBranchAddress("MHTJetsMaskJERdown", &MHTJetsMaskJERdown, &b_MHTJetsMaskJERdown);
   fChain->SetBranchAddress("MHTJetsMaskJERup", &MHTJetsMaskJERup, &b_MHTJetsMaskJERup);
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
   fChain->SetBranchAddress("MHTPhiJECdown", &MHTPhiJECdown, &b_MHTPhiJECdown);
   fChain->SetBranchAddress("MHTPhiJECup", &MHTPhiJECup, &b_MHTPhiJECup);
   fChain->SetBranchAddress("MHTPhiJERdown", &MHTPhiJERdown, &b_MHTPhiJERdown);
   fChain->SetBranchAddress("MHTPhiJERup", &MHTPhiJERup, &b_MHTPhiJERup);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsJECdown", &NJetsJECdown, &b_NJetsJECdown);
   fChain->SetBranchAddress("NJetsJECup", &NJetsJECup, &b_NJetsJECup);
   fChain->SetBranchAddress("NJetsJERdown", &NJetsJERdown, &b_NJetsJERdown);
   fChain->SetBranchAddress("NJetsJERup", &NJetsJERup, &b_NJetsJERup);
   fChain->SetBranchAddress("NumEvents", &NumEvents, &b_NumEvents);
   fChain->SetBranchAddress("NumInteractions", &NumInteractions, &b_NumInteractions);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("PDFids", &PDFids, &b_PDFids);
   fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
   fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
   fChain->SetBranchAddress("puSysDown", &puSysDown, &b_puSysDown);
   fChain->SetBranchAddress("puSysUp", &puSysUp, &b_puSysUp);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
   fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
   fChain->SetBranchAddress("selectedIDElectrons_MiniIso", &selectedIDElectrons_MiniIso, &b_selectedIDElectrons_MiniIso);
   fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
   fChain->SetBranchAddress("selectedIDElectrons_MTW", &selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
   fChain->SetBranchAddress("selectedIDIsoElectrons_PTW", &selectedIDIsoElectrons_PTW, &b_selectedIDIsoElectrons_PTW);
   fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
   fChain->SetBranchAddress("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
   fChain->SetBranchAddress("selectedIDIsoMuons_PTW", &selectedIDIsoMuons_PTW, &b_selectedIDIsoMuons_PTW);
   fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
   fChain->SetBranchAddress("selectedIDMuons_MiniIso", &selectedIDMuons_MiniIso, &b_selectedIDMuons_MiniIso);
   fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
   fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
   fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
   fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
   fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
   fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
   fChain->SetBranchAddress("TAPElectronTracks_chg", &TAPElectronTracks_chg, &b_TAPElectronTracks_chg);
   fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
   fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
   fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
   fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
   fChain->SetBranchAddress("TAPMuonTracks_chg", &TAPMuonTracks_chg, &b_TAPMuonTracks_chg);
   fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
   fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
   fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
   fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
   fChain->SetBranchAddress("TAPPionTracks_chg", &TAPPionTracks_chg, &b_TAPPionTracks_chg);
   fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
   fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
   fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
   fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
}

Bool_t ApplyBaseline::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef ApplyBaseline_cxx
