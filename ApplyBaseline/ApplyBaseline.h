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
   Bool_t          BadGlobalMuon;
   Double_t        BadGlobalMuonLeadPt;
   Bool_t          BadPFMuonFilter;
   Bool_t          BadTrkGlobalMuon;
   Double_t        BadTrkGlobalMuonLeadPt;
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
   Bool_t          DupGlobalMuon;
   Double_t        DupGlobalMuonLeadPt;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   vector<TLorentzVector> *Electrons = 0;
   vector<int>     *Electrons_charge = 0;
   vector<bool>    *Electrons_mediumID = 0;
   vector<double>  *Electrons_MT2Activity = 0;
   vector<double>  *Electrons_MTW = 0;
   vector<double>  *Electrons_PTW = 0;
   vector<bool>    *Electrons_tightID = 0;
   vector<TLorentzVector> *ElectronsNoIso = 0;
   vector<bool>    *ElectronsNoIso_mediumID = 0;
   vector<double>  *ElectronsNoIso_MiniIso = 0;
   vector<double>  *ElectronsNoIso_MT2Activity = 0;
   vector<double>  *ElectronsNoIso_MTW = 0;
   vector<bool>    *ElectronsNoIso_tightID = 0;
   vector<TLorentzVector> *GenElectrons = 0;
   vector<bool>    *GenElectrons_fromTau = 0;
   vector<double>  *GenElectrons_MT2Activity = 0;
   vector<double>  *GenElectrons_RecoTrkAct = 0;
   vector<double>  *GenElectrons_RecoTrkd3 = 0;
   vector<double>  *GenElectrons_RecoTrkIso = 0;
   Double_t        GenHT;
   vector<TLorentzVector> *GenJets = 0;
   vector<bool>    *GenJets_HTMask = 0;
   vector<bool>    *GenJets_MHTMask = 0;
   Double_t        GenMET;
   Double_t        GenMETPhi;
   Double_t        GenMHT;
   Double_t        GenMHTPhi;
   vector<TLorentzVector> *GenMuons = 0;
   vector<bool>    *GenMuons_fromTau = 0;
   vector<double>  *GenMuons_MT2Activity = 0;
   vector<double>  *GenMuons_RecoTrkAct = 0;
   vector<double>  *GenMuons_RecoTrkd3 = 0;
   vector<double>  *GenMuons_RecoTrkIso = 0;
   vector<TLorentzVector> *GenParticles = 0;
   vector<int>     *GenParticles_ParentId = 0;
   vector<int>     *GenParticles_ParentIdx = 0;
   vector<int>     *GenParticles_PdgId = 0;
   vector<int>     *GenParticles_Status = 0;
   vector<TLorentzVector> *GenTaus = 0;
   vector<bool>    *GenTaus_had = 0;
   vector<double>  *GenTaus_LeadRecoTrkAct = 0;
   vector<double>  *GenTaus_LeadRecoTrkd3 = 0;
   vector<double>  *GenTaus_LeadRecoTrkIso = 0;
   vector<TLorentzVector> *GenTaus_LeadTrk = 0;
   vector<double>  *GenTaus_MT2Activity = 0;
   vector<int>     *GenTaus_NNeutralHadrons = 0;
   vector<int>     *GenTaus_NProngs = 0;
   vector<TLorentzVector> *GenTaus_Nu = 0;
   vector<TLorentzVector> *GenTops = 0;
   Double_t        GenTopWeight;
   Int_t           globalTightHalo2016Filter;
   Int_t           HBHEIsoNoiseFilter;
   Int_t           HBHENoiseFilter;
   Double_t        HT;
   Double_t        HTJECdown;
   Double_t        HTJECup;
   Double_t        HTJERdown;
   Double_t        HTJERup;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Bool_t          JetID;
   Bool_t          JetIDAK8;
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
   vector<bool>    *Jets_HTMask = 0;
   vector<bool>    *Jets_ID = 0;
   vector<bool>    *Jets_ISRMask = 0;
   vector<double>  *Jets_jecFactor = 0;
   vector<double>  *Jets_jecUnc = 0;
   vector<double>  *Jets_jerFactor = 0;
   vector<double>  *Jets_jerFactorDown = 0;
   vector<double>  *Jets_jerFactorUp = 0;
   vector<bool>    *Jets_LeptonMask = 0;
   vector<bool>    *Jets_MHTMask = 0;
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
   vector<bool>    *JetsJECdown_HTMask = 0;
   vector<bool>    *JetsJECdown_ID = 0;
   vector<bool>    *JetsJECdown_ISRMask = 0;
   vector<bool>    *JetsJECdown_LeptonMask = 0;
   vector<bool>    *JetsJECdown_MHTMask = 0;
   vector<double>  *JetsJECdown_muonEnergyFraction = 0;
   vector<int>     *JetsJECdown_partonFlavor = 0;
   vector<TLorentzVector> *JetsJECup = 0;
   vector<double>  *JetsJECup_bDiscriminatorCSV = 0;
   vector<double>  *JetsJECup_bDiscriminatorMVA = 0;
   vector<int>     *JetsJECup_hadronFlavor = 0;
   vector<bool>    *JetsJECup_HTMask = 0;
   vector<bool>    *JetsJECup_ID = 0;
   vector<bool>    *JetsJECup_ISRMask = 0;
   vector<bool>    *JetsJECup_LeptonMask = 0;
   vector<bool>    *JetsJECup_MHTMask = 0;
   vector<double>  *JetsJECup_muonEnergyFraction = 0;
   vector<int>     *JetsJECup_partonFlavor = 0;
   vector<TLorentzVector> *JetsJERdown = 0;
   vector<double>  *JetsJERdown_bDiscriminatorCSV = 0;
   vector<double>  *JetsJERdown_bDiscriminatorMVA = 0;
   vector<int>     *JetsJERdown_hadronFlavor = 0;
   vector<bool>    *JetsJERdown_HTMask = 0;
   vector<bool>    *JetsJERdown_ID = 0;
   vector<bool>    *JetsJERdown_ISRMask = 0;
   vector<bool>    *JetsJERdown_LeptonMask = 0;
   vector<bool>    *JetsJERdown_MHTMask = 0;
   vector<double>  *JetsJERdown_muonEnergyFraction = 0;
   vector<int>     *JetsJERdown_partonFlavor = 0;
   vector<TLorentzVector> *JetsJERup = 0;
   vector<double>  *JetsJERup_bDiscriminatorCSV = 0;
   vector<double>  *JetsJERup_bDiscriminatorMVA = 0;
   vector<int>     *JetsJERup_hadronFlavor = 0;
   vector<bool>    *JetsJERup_HTMask = 0;
   vector<bool>    *JetsJERup_ID = 0;
   vector<bool>    *JetsJERup_ISRMask = 0;
   vector<bool>    *JetsJERup_LeptonMask = 0;
   vector<bool>    *JetsJERup_MHTMask = 0;
   vector<double>  *JetsJERup_muonEnergyFraction = 0;
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
   Double_t        MHTPhi;
   Double_t        MHTPhiJECdown;
   Double_t        MHTPhiJECup;
   Double_t        MHTPhiJERdown;
   Double_t        MHTPhiJERup;
   Double_t        MT2;
   vector<TLorentzVector> *Muons = 0;
   vector<int>     *Muons_charge = 0;
   vector<double>  *Muons_MT2Activity = 0;
   vector<double>  *Muons_MTW = 0;
   vector<double>  *Muons_PTW = 0;
   vector<bool>    *Muons_tightID = 0;
   vector<TLorentzVector> *MuonsNoIso = 0;
   vector<double>  *MuonsNoIso_MiniIso = 0;
   vector<double>  *MuonsNoIso_MT2Activity = 0;
   vector<double>  *MuonsNoIso_MTW = 0;
   vector<bool>    *MuonsNoIso_tightID = 0;
   Int_t           nAllVertices;
   Int_t           NJets;
   Int_t           NJetsISR;
   Int_t           NJetsISRJECdown;
   Int_t           NJetsISRJECup;
   Int_t           NJetsISRJERdown;
   Int_t           NJetsISRJERup;
   Int_t           NJetsJECdown;
   Int_t           NJetsJECup;
   Int_t           NJetsJERdown;
   Int_t           NJetsJERup;
   Double_t        NumEvents;
   Int_t           NumInteractions;
   Int_t           NVtx;
   vector<int>     *PDFids = 0;
   vector<double>  *PDFweights = 0;
   Double_t        PFCaloMETRatio;
   Double_t        PmssmId;
   Double_t        puSysDown;
   Double_t        puSysUp;
   Double_t        puWeight;
   vector<double>  *ScaleWeights = 0;
   Double_t        SusyLSPMass;
   Double_t        SusyMotherMass;
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
   vector<string>  *TriggerNames = 0;
   vector<int>     *TriggerPass = 0;
   vector<int>     *TriggerPrescales = 0;
   Double_t        TrueNumInteractions;
   Double_t        Weight;

   // List of branches
   TBranch        *b_RunNum = 0;   //!
   TBranch        *b_LumiBlockNum = 0;   //!
   TBranch        *b_EvtNum = 0;   //!
   TBranch        *b_BadChargedCandidateFilter = 0;   //!
   TBranch        *b_BadGlobalMuon = 0;   //!
   TBranch        *b_BadGlobalMuonLeadPt = 0;   //!
   TBranch        *b_BadPFMuonFilter = 0;   //!
   TBranch        *b_BadTrkGlobalMuon = 0;   //!
   TBranch        *b_BadTrkGlobalMuonLeadPt = 0;   //!
   TBranch        *b_BTags = 0;   //!
   TBranch        *b_BTagsJECdown = 0;   //!
   TBranch        *b_BTagsJECup = 0;   //!
   TBranch        *b_BTagsJERdown = 0;   //!
   TBranch        *b_BTagsJERup = 0;   //!
   TBranch        *b_BTagsMVA = 0;   //!
   TBranch        *b_BTagsMVAJECdown = 0;   //!
   TBranch        *b_BTagsMVAJECup = 0;   //!
   TBranch        *b_BTagsMVAJERdown = 0;   //!
   TBranch        *b_BTagsMVAJERup = 0;   //!
   TBranch        *b_CaloMET = 0;   //!
   TBranch        *b_CaloMETPhi = 0;   //!
   TBranch        *b_CrossSection = 0;   //!
   TBranch        *b_CSCTightHaloFilter = 0;   //!
   TBranch        *b_DeltaPhi1 = 0;   //!
   TBranch        *b_DeltaPhi1JECdown = 0;   //!
   TBranch        *b_DeltaPhi1JECup = 0;   //!
   TBranch        *b_DeltaPhi1JERdown = 0;   //!
   TBranch        *b_DeltaPhi1JERup = 0;   //!
   TBranch        *b_DeltaPhi2 = 0;   //!
   TBranch        *b_DeltaPhi2JECdown = 0;   //!
   TBranch        *b_DeltaPhi2JECup = 0;   //!
   TBranch        *b_DeltaPhi2JERdown = 0;   //!
   TBranch        *b_DeltaPhi2JERup = 0;   //!
   TBranch        *b_DeltaPhi3 = 0;   //!
   TBranch        *b_DeltaPhi3JECdown = 0;   //!
   TBranch        *b_DeltaPhi3JECup = 0;   //!
   TBranch        *b_DeltaPhi3JERdown = 0;   //!
   TBranch        *b_DeltaPhi3JERup = 0;   //!
   TBranch        *b_DeltaPhi4 = 0;   //!
   TBranch        *b_DeltaPhi4JECdown = 0;   //!
   TBranch        *b_DeltaPhi4JECup = 0;   //!
   TBranch        *b_DeltaPhi4JERdown = 0;   //!
   TBranch        *b_DeltaPhi4JERup = 0;   //!
   TBranch        *b_DupGlobalMuon = 0;   //!
   TBranch        *b_DupGlobalMuonLeadPt = 0;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter = 0;   //!
   TBranch        *b_eeBadScFilter = 0;   //!
   TBranch        *b_Electrons = 0;   //!
   TBranch        *b_Electrons_charge = 0;   //!
   TBranch        *b_Electrons_mediumID = 0;   //!
   TBranch        *b_Electrons_MT2Activity = 0;   //!
   TBranch        *b_Electrons_MTW = 0;   //!
   TBranch        *b_Electrons_PTW = 0;   //!
   TBranch        *b_Electrons_tightID = 0;   //!
   TBranch        *b_ElectronsNoIso = 0;   //!
   TBranch        *b_ElectronsNoIso_mediumID = 0;   //!
   TBranch        *b_ElectronsNoIso_MiniIso = 0;   //!
   TBranch        *b_ElectronsNoIso_MT2Activity = 0;   //!
   TBranch        *b_ElectronsNoIso_MTW = 0;   //!
   TBranch        *b_ElectronsNoIso_tightID = 0;   //!
   TBranch        *b_GenElectrons = 0;   //!
   TBranch        *b_GenElectrons_fromTau = 0;   //!
   TBranch        *b_GenElectrons_MT2Activity = 0;   //!
   TBranch        *b_GenElectrons_RecoTrkAct = 0;   //!
   TBranch        *b_GenElectrons_RecoTrkd3 = 0;   //!
   TBranch        *b_GenElectrons_RecoTrkIso = 0;   //!
   TBranch        *b_GenHT = 0;   //!
   TBranch        *b_GenJets = 0;   //!
   TBranch        *b_GenJets_HTMask = 0;   //!
   TBranch        *b_GenJets_MHTMask = 0;   //!
   TBranch        *b_GenMET = 0;   //!
   TBranch        *b_GenMETPhi = 0;   //!
   TBranch        *b_GenMHT = 0;   //!
   TBranch        *b_GenMHTPhi = 0;   //!
   TBranch        *b_GenMuons = 0;   //!
   TBranch        *b_GenMuons_fromTau = 0;   //!
   TBranch        *b_GenMuons_MT2Activity = 0;   //!
   TBranch        *b_GenMuons_RecoTrkAct = 0;   //!
   TBranch        *b_GenMuons_RecoTrkd3 = 0;   //!
   TBranch        *b_GenMuons_RecoTrkIso = 0;   //!
   TBranch        *b_GenParticles = 0;   //!
   TBranch        *b_GenParticles_ParentId = 0;   //!
   TBranch        *b_GenParticles_ParentIdx = 0;   //!
   TBranch        *b_GenParticles_PdgId = 0;   //!
   TBranch        *b_GenParticles_Status = 0;   //!
   TBranch        *b_GenTaus = 0;   //!
   TBranch        *b_GenTaus_had = 0;   //!
   TBranch        *b_GenTaus_LeadRecoTrkAct = 0;   //!
   TBranch        *b_GenTaus_LeadRecoTrkd3 = 0;   //!
   TBranch        *b_GenTaus_LeadRecoTrkIso = 0;   //!
   TBranch        *b_GenTaus_LeadTrk = 0;   //!
   TBranch        *b_GenTaus_MT2Activity = 0;   //!
   TBranch        *b_GenTaus_NNeutralHadrons = 0;   //!
   TBranch        *b_GenTaus_NProngs = 0;   //!
   TBranch        *b_GenTaus_Nu = 0;   //!
   TBranch        *b_GenTops = 0;   //!
   TBranch        *b_GenTopWeight = 0;   //!
   TBranch        *b_globalTightHalo2016Filter = 0;   //!
   TBranch        *b_HBHEIsoNoiseFilter = 0;   //!
   TBranch        *b_HBHENoiseFilter = 0;   //!
   TBranch        *b_HT = 0;   //!
   TBranch        *b_HTJECdown = 0;   //!
   TBranch        *b_HTJECup = 0;   //!
   TBranch        *b_HTJERdown = 0;   //!
   TBranch        *b_HTJERup = 0;   //!
   TBranch        *b_isoElectronTracks = 0;   //!
   TBranch        *b_isoMuonTracks = 0;   //!
   TBranch        *b_isoPionTracks = 0;   //!
   TBranch        *b_JetID = 0;   //!
   TBranch        *b_JetIDAK8 = 0;   //!
   TBranch        *b_JetIDJECdown = 0;   //!
   TBranch        *b_JetIDJECup = 0;   //!
   TBranch        *b_JetIDJERdown = 0;   //!
   TBranch        *b_JetIDJERup = 0;   //!
   TBranch        *b_Jets = 0;   //!
   TBranch        *b_Jets_bDiscriminatorCSV = 0;   //!
   TBranch        *b_Jets_bDiscriminatorMVA = 0;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction = 0;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction = 0;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity = 0;   //!
   TBranch        *b_Jets_chargedMultiplicity = 0;   //!
   TBranch        *b_Jets_electronMultiplicity = 0;   //!
   TBranch        *b_Jets_hadronFlavor = 0;   //!
   TBranch        *b_Jets_HTMask = 0;   //!
   TBranch        *b_Jets_ID = 0;   //!
   TBranch        *b_Jets_ISRMask = 0;   //!
   TBranch        *b_Jets_jecFactor = 0;   //!
   TBranch        *b_Jets_jecUnc = 0;   //!
   TBranch        *b_Jets_jerFactor = 0;   //!
   TBranch        *b_Jets_jerFactorDown = 0;   //!
   TBranch        *b_Jets_jerFactorUp = 0;   //!
   TBranch        *b_Jets_LeptonMask = 0;   //!
   TBranch        *b_Jets_MHTMask = 0;   //!
   TBranch        *b_Jets_muonEnergyFraction = 0;   //!
   TBranch        *b_Jets_muonMultiplicity = 0;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction = 0;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction = 0;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity = 0;   //!
   TBranch        *b_Jets_neutralMultiplicity = 0;   //!
   TBranch        *b_Jets_partonFlavor = 0;   //!
   TBranch        *b_Jets_photonEnergyFraction = 0;   //!
   TBranch        *b_Jets_photonMultiplicity = 0;   //!
   TBranch        *b_Jets_qgAxis2 = 0;   //!
   TBranch        *b_Jets_qgLikelihood = 0;   //!
   TBranch        *b_Jets_qgMult = 0;   //!
   TBranch        *b_Jets_qgPtD = 0;   //!
   TBranch        *b_JetsJECdown = 0;   //!
   TBranch        *b_JetsJECdown_bDiscriminatorCSV = 0;   //!
   TBranch        *b_JetsJECdown_bDiscriminatorMVA = 0;   //!
   TBranch        *b_JetsJECdown_hadronFlavor = 0;   //!
   TBranch        *b_JetsJECdown_HTMask = 0;   //!
   TBranch        *b_JetsJECdown_ID = 0;   //!
   TBranch        *b_JetsJECdown_ISRMask = 0;   //!
   TBranch        *b_JetsJECdown_LeptonMask = 0;   //!
   TBranch        *b_JetsJECdown_MHTMask = 0;   //!
   TBranch        *b_JetsJECdown_muonEnergyFraction = 0;   //!
   TBranch        *b_JetsJECdown_partonFlavor = 0;   //!
   TBranch        *b_JetsJECup = 0;   //!
   TBranch        *b_JetsJECup_bDiscriminatorCSV = 0;   //!
   TBranch        *b_JetsJECup_bDiscriminatorMVA = 0;   //!
   TBranch        *b_JetsJECup_hadronFlavor = 0;   //!
   TBranch        *b_JetsJECup_HTMask = 0;   //!
   TBranch        *b_JetsJECup_ID = 0;   //!
   TBranch        *b_JetsJECup_ISRMask = 0;   //!
   TBranch        *b_JetsJECup_LeptonMask = 0;   //!
   TBranch        *b_JetsJECup_MHTMask = 0;   //!
   TBranch        *b_JetsJECup_muonEnergyFraction = 0;   //!
   TBranch        *b_JetsJECup_partonFlavor = 0;   //!
   TBranch        *b_JetsJERdown = 0;   //!
   TBranch        *b_JetsJERdown_bDiscriminatorCSV = 0;   //!
   TBranch        *b_JetsJERdown_bDiscriminatorMVA = 0;   //!
   TBranch        *b_JetsJERdown_hadronFlavor = 0;   //!
   TBranch        *b_JetsJERdown_HTMask = 0;   //!
   TBranch        *b_JetsJERdown_ID = 0;   //!
   TBranch        *b_JetsJERdown_ISRMask = 0;   //!
   TBranch        *b_JetsJERdown_LeptonMask = 0;   //!
   TBranch        *b_JetsJERdown_MHTMask = 0;   //!
   TBranch        *b_JetsJERdown_muonEnergyFraction = 0;   //!
   TBranch        *b_JetsJERdown_partonFlavor = 0;   //!
   TBranch        *b_JetsJERup = 0;   //!
   TBranch        *b_JetsJERup_bDiscriminatorCSV = 0;   //!
   TBranch        *b_JetsJERup_bDiscriminatorMVA = 0;   //!
   TBranch        *b_JetsJERup_hadronFlavor = 0;   //!
   TBranch        *b_JetsJERup_HTMask = 0;   //!
   TBranch        *b_JetsJERup_ID = 0;   //!
   TBranch        *b_JetsJERup_ISRMask = 0;   //!
   TBranch        *b_JetsJERup_LeptonMask = 0;   //!
   TBranch        *b_JetsJERup_MHTMask = 0;   //!
   TBranch        *b_JetsJERup_muonEnergyFraction = 0;   //!
   TBranch        *b_JetsJERup_partonFlavor = 0;   //!
   TBranch        *b_madHT = 0;   //!
   TBranch        *b_MET = 0;   //!
   TBranch        *b_METDown = 0;   //!
   TBranch        *b_METPhi = 0;   //!
   TBranch        *b_METPhiDown = 0;   //!
   TBranch        *b_METPhiUp = 0;   //!
   TBranch        *b_METUp = 0;   //!
   TBranch        *b_MHT = 0;   //!
   TBranch        *b_MHTJECdown = 0;   //!
   TBranch        *b_MHTJECup = 0;   //!
   TBranch        *b_MHTJERdown = 0;   //!
   TBranch        *b_MHTJERup = 0;   //!
   TBranch        *b_MHTPhi = 0;   //!
   TBranch        *b_MHTPhiJECdown = 0;   //!
   TBranch        *b_MHTPhiJECup = 0;   //!
   TBranch        *b_MHTPhiJERdown = 0;   //!
   TBranch        *b_MHTPhiJERup = 0;   //!
   TBranch        *b_MT2 = 0;   //!
   TBranch        *b_Muons = 0;   //!
   TBranch        *b_Muons_charge = 0;   //!
   TBranch        *b_Muons_MT2Activity = 0;   //!
   TBranch        *b_Muons_MTW = 0;   //!
   TBranch        *b_Muons_PTW = 0;   //!
   TBranch        *b_Muons_tightID = 0;   //!
   TBranch        *b_MuonsNoIso = 0;   //!
   TBranch        *b_MuonsNoIso_MiniIso = 0;   //!
   TBranch        *b_MuonsNoIso_MT2Activity = 0;   //!
   TBranch        *b_MuonsNoIso_MTW = 0;   //!
   TBranch        *b_MuonsNoIso_tightID = 0;   //!
   TBranch        *b_nAllVertices = 0;   //!
   TBranch        *b_NJets = 0;   //!
   TBranch        *b_NJetsISR = 0;   //!
   TBranch        *b_NJetsISRJECdown = 0;   //!
   TBranch        *b_NJetsISRJECup = 0;   //!
   TBranch        *b_NJetsISRJERdown = 0;   //!
   TBranch        *b_NJetsISRJERup = 0;   //!
   TBranch        *b_NJetsJECdown = 0;   //!
   TBranch        *b_NJetsJECup = 0;   //!
   TBranch        *b_NJetsJERdown = 0;   //!
   TBranch        *b_NJetsJERup = 0;   //!
   TBranch        *b_NumEvents = 0;   //!
   TBranch        *b_NumInteractions = 0;   //!
   TBranch        *b_NVtx = 0;   //!
   TBranch        *b_PDFids = 0;   //!
   TBranch        *b_PDFweights = 0;   //!
   TBranch        *b_PFCaloMETRatio = 0;   //!
   TBranch        *b_PmssmId = 0;   //!
   TBranch        *b_puSysDown = 0;   //!
   TBranch        *b_puSysUp = 0;   //!
   TBranch        *b_puWeight = 0;   //!
   TBranch        *b_ScaleWeights = 0;   //!
   TBranch        *b_SusyLSPMass = 0;   //!
   TBranch        *b_SusyMotherMass = 0;   //!
   TBranch        *b_TAPElectronTracks = 0;   //!
   TBranch        *b_TAPElectronTracks_activity = 0;   //!
   TBranch        *b_TAPElectronTracks_charge = 0;   //!
   TBranch        *b_TAPElectronTracks_mT = 0;   //!
   TBranch        *b_TAPElectronTracks_trkiso = 0;   //!
   TBranch        *b_TAPMuonTracks = 0;   //!
   TBranch        *b_TAPMuonTracks_activity = 0;   //!
   TBranch        *b_TAPMuonTracks_charge = 0;   //!
   TBranch        *b_TAPMuonTracks_mT = 0;   //!
   TBranch        *b_TAPMuonTracks_trkiso = 0;   //!
   TBranch        *b_TAPPionTracks = 0;   //!
   TBranch        *b_TAPPionTracks_activity = 0;   //!
   TBranch        *b_TAPPionTracks_charge = 0;   //!
   TBranch        *b_TAPPionTracks_mT = 0;   //!
   TBranch        *b_TAPPionTracks_trkiso = 0;   //!
   TBranch        *b_TriggerNames = 0;   //!
   TBranch        *b_TriggerPass = 0;   //!
   TBranch        *b_TriggerPrescales = 0;   //!
   TBranch        *b_TrueNumInteractions = 0;   //!
   TBranch        *b_Weight = 0;   //!


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
   fChain->SetBranchStatus("BadGlobalMuon", 1);
   fChain->SetBranchStatus("BadGlobalMuonLeadPt", 1);
   fChain->SetBranchStatus("BadPFMuonFilter", 1);
   fChain->SetBranchStatus("BadTrkGlobalMuon", 1);
   fChain->SetBranchStatus("BadTrkGlobalMuonLeadPt", 1);
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
   fChain->SetBranchStatus("DupGlobalMuon", 1);
   fChain->SetBranchStatus("DupGlobalMuonLeadPt", 1);
   fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
   fChain->SetBranchStatus("eeBadScFilter", 1);
   fChain->SetBranchStatus("Electrons", 1);
   fChain->SetBranchStatus("Electrons_charge", 1);
   fChain->SetBranchStatus("Electrons_mediumID", 1);
   fChain->SetBranchStatus("Electrons_MT2Activity", 1);
   fChain->SetBranchStatus("Electrons_MTW", 1);
   fChain->SetBranchStatus("Electrons_PTW", 1);
   fChain->SetBranchStatus("Electrons_tightID", 1);
   fChain->SetBranchStatus("ElectronsNoIso", 1);
   fChain->SetBranchStatus("ElectronsNoIso_mediumID", 1);
   fChain->SetBranchStatus("ElectronsNoIso_MiniIso", 1);
   fChain->SetBranchStatus("ElectronsNoIso_MT2Activity", 1);
   fChain->SetBranchStatus("ElectronsNoIso_MTW", 1);
   fChain->SetBranchStatus("ElectronsNoIso_tightID", 1);
   fChain->SetBranchStatus("GenElectrons", 1);
   fChain->SetBranchStatus("GenElectrons_fromTau", 1);
   fChain->SetBranchStatus("GenElectrons_MT2Activity", 1);
   fChain->SetBranchStatus("GenElectrons_RecoTrkAct", 1);
   fChain->SetBranchStatus("GenElectrons_RecoTrkd3", 1);
   fChain->SetBranchStatus("GenElectrons_RecoTrkIso", 1);
   fChain->SetBranchStatus("GenHT", 1);
   fChain->SetBranchStatus("GenJets", 1);
   fChain->SetBranchStatus("GenJets_HTMask", 1);
   fChain->SetBranchStatus("GenJets_MHTMask", 1);
   fChain->SetBranchStatus("GenMET", 1);
   fChain->SetBranchStatus("GenMETPhi", 1);
   fChain->SetBranchStatus("GenMHT", 1);
   fChain->SetBranchStatus("GenMHTPhi", 1);
   fChain->SetBranchStatus("GenMuons", 1);
   fChain->SetBranchStatus("GenMuons_fromTau", 1);
   fChain->SetBranchStatus("GenMuons_MT2Activity", 1);
   fChain->SetBranchStatus("GenMuons_RecoTrkAct", 1);
   fChain->SetBranchStatus("GenMuons_RecoTrkd3", 1);
   fChain->SetBranchStatus("GenMuons_RecoTrkIso", 1);
   fChain->SetBranchStatus("GenParticles", 1);
   fChain->SetBranchStatus("GenParticles_ParentId", 1);
   fChain->SetBranchStatus("GenParticles_ParentIdx", 1);
   fChain->SetBranchStatus("GenParticles_PdgId", 1);
   fChain->SetBranchStatus("GenParticles_Status", 1);
   fChain->SetBranchStatus("GenTaus", 1);
   fChain->SetBranchStatus("GenTaus_had", 1);
   fChain->SetBranchStatus("GenTaus_LeadRecoTrkAct", 1);
   fChain->SetBranchStatus("GenTaus_LeadRecoTrkd3", 1);
   fChain->SetBranchStatus("GenTaus_LeadRecoTrkIso", 1);
   fChain->SetBranchStatus("GenTaus_LeadTrk", 1);
   fChain->SetBranchStatus("GenTaus_MT2Activity", 1);
   fChain->SetBranchStatus("GenTaus_NNeutralHadrons", 1);
   fChain->SetBranchStatus("GenTaus_NProngs", 1);
   fChain->SetBranchStatus("GenTaus_Nu", 1);
   fChain->SetBranchStatus("GenTops", 1);
   fChain->SetBranchStatus("GenTopWeight", 1);
   fChain->SetBranchStatus("globalTightHalo2016Filter", 1);
   fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
   fChain->SetBranchStatus("HBHENoiseFilter", 1);
   fChain->SetBranchStatus("HT", 1);
   fChain->SetBranchStatus("HTJECdown", 1);
   fChain->SetBranchStatus("HTJECup", 1);
   fChain->SetBranchStatus("HTJERdown", 1);
   fChain->SetBranchStatus("HTJERup", 1);
   fChain->SetBranchStatus("isoElectronTracks", 1);
   fChain->SetBranchStatus("isoMuonTracks", 1);
   fChain->SetBranchStatus("isoPionTracks", 1);
   fChain->SetBranchStatus("JetID", 1);
   fChain->SetBranchStatus("JetIDAK8", 1);
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
   fChain->SetBranchStatus("Jets_HTMask", 1);
   fChain->SetBranchStatus("Jets_ID", 1);
   fChain->SetBranchStatus("Jets_ISRMask", 1);
   fChain->SetBranchStatus("Jets_jecFactor", 1);
   fChain->SetBranchStatus("Jets_jecUnc", 1);
   fChain->SetBranchStatus("Jets_jerFactor", 1);
   fChain->SetBranchStatus("Jets_jerFactorDown", 1);
   fChain->SetBranchStatus("Jets_jerFactorUp", 1);
   fChain->SetBranchStatus("Jets_LeptonMask", 1);
   fChain->SetBranchStatus("Jets_MHTMask", 1);
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
   fChain->SetBranchStatus("JetsJECdown_HTMask", 1);
   fChain->SetBranchStatus("JetsJECdown_ID", 1);
   fChain->SetBranchStatus("JetsJECdown_ISRMask", 1);
   fChain->SetBranchStatus("JetsJECdown_LeptonMask", 1);
   fChain->SetBranchStatus("JetsJECdown_MHTMask", 1);
   fChain->SetBranchStatus("JetsJECdown_muonEnergyFraction", 1);
   fChain->SetBranchStatus("JetsJECdown_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJECup", 1);
   fChain->SetBranchStatus("JetsJECup_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJECup_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJECup_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJECup_HTMask", 1);
   fChain->SetBranchStatus("JetsJECup_ID", 1);
   fChain->SetBranchStatus("JetsJECup_ISRMask", 1);
   fChain->SetBranchStatus("JetsJECup_LeptonMask", 1);
   fChain->SetBranchStatus("JetsJECup_MHTMask", 1);
   fChain->SetBranchStatus("JetsJECup_muonEnergyFraction", 1);
   fChain->SetBranchStatus("JetsJECup_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJERdown", 1);
   fChain->SetBranchStatus("JetsJERdown_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJERdown_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJERdown_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJERdown_HTMask", 1);
   fChain->SetBranchStatus("JetsJERdown_ID", 1);
   fChain->SetBranchStatus("JetsJERdown_ISRMask", 1);
   fChain->SetBranchStatus("JetsJERdown_LeptonMask", 1);
   fChain->SetBranchStatus("JetsJERdown_MHTMask", 1);
   fChain->SetBranchStatus("JetsJERdown_muonEnergyFraction", 1);
   fChain->SetBranchStatus("JetsJERdown_partonFlavor", 1);
   fChain->SetBranchStatus("JetsJERup", 1);
   fChain->SetBranchStatus("JetsJERup_bDiscriminatorCSV", 1);
   fChain->SetBranchStatus("JetsJERup_bDiscriminatorMVA", 1);
   fChain->SetBranchStatus("JetsJERup_hadronFlavor", 1);
   fChain->SetBranchStatus("JetsJERup_HTMask", 1);
   fChain->SetBranchStatus("JetsJERup_ID", 1);
   fChain->SetBranchStatus("JetsJERup_ISRMask", 1);
   fChain->SetBranchStatus("JetsJERup_LeptonMask", 1);
   fChain->SetBranchStatus("JetsJERup_MHTMask", 1);
   fChain->SetBranchStatus("JetsJERup_muonEnergyFraction", 1);
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
   fChain->SetBranchStatus("MHTPhi", 1);
   fChain->SetBranchStatus("MHTPhiJECdown", 1);
   fChain->SetBranchStatus("MHTPhiJECup", 1);
   fChain->SetBranchStatus("MHTPhiJERdown", 1);
   fChain->SetBranchStatus("MHTPhiJERup", 1);
   fChain->SetBranchStatus("MT2", 1);
   fChain->SetBranchStatus("Muons", 1);
   fChain->SetBranchStatus("Muons_charge", 1);
   fChain->SetBranchStatus("Muons_MT2Activity", 1);
   fChain->SetBranchStatus("Muons_MTW", 1);
   fChain->SetBranchStatus("Muons_PTW", 1);
   fChain->SetBranchStatus("Muons_tightID", 1);
   fChain->SetBranchStatus("MuonsNoIso", 1);
   fChain->SetBranchStatus("MuonsNoIso_MiniIso", 1);
   fChain->SetBranchStatus("MuonsNoIso_MT2Activity", 1);
   fChain->SetBranchStatus("MuonsNoIso_MTW", 1);
   fChain->SetBranchStatus("MuonsNoIso_tightID", 1);
   fChain->SetBranchStatus("nAllVertices", 1);
   fChain->SetBranchStatus("NJets", 1);
   fChain->SetBranchStatus("NJetsISR", 1);
   fChain->SetBranchStatus("NJetsISRJECdown", 1);
   fChain->SetBranchStatus("NJetsISRJECup", 1);
   fChain->SetBranchStatus("NJetsISRJERdown", 1);
   fChain->SetBranchStatus("NJetsISRJERup", 1);
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
   fChain->SetBranchStatus("PmssmId", 1);
   fChain->SetBranchStatus("puSysDown", 1);
   fChain->SetBranchStatus("puSysUp", 1);
   fChain->SetBranchStatus("puWeight", 1);
   fChain->SetBranchStatus("ScaleWeights", 1);
   fChain->SetBranchStatus("SusyLSPMass", 1);
   fChain->SetBranchStatus("SusyMotherMass", 1);
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
   fChain->SetBranchStatus("TriggerNames", 1);
   fChain->SetBranchStatus("TriggerPass", 1);
   fChain->SetBranchStatus("TriggerPrescales", 1);
   fChain->SetBranchStatus("TrueNumInteractions", 1);
   fChain->SetBranchStatus("Weight", 1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   fChain->SetBranchAddress("BadGlobalMuon", &BadGlobalMuon, &b_BadGlobalMuon);
   fChain->SetBranchAddress("BadGlobalMuonLeadPt", &BadGlobalMuonLeadPt, &b_BadGlobalMuonLeadPt);
   fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("BadTrkGlobalMuon", &BadTrkGlobalMuon, &b_BadTrkGlobalMuon);
   fChain->SetBranchAddress("BadTrkGlobalMuonLeadPt", &BadTrkGlobalMuonLeadPt, &b_BadTrkGlobalMuonLeadPt);
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
   fChain->SetBranchAddress("DupGlobalMuon", &DupGlobalMuon, &b_DupGlobalMuon);
   fChain->SetBranchAddress("DupGlobalMuonLeadPt", &DupGlobalMuonLeadPt, &b_DupGlobalMuonLeadPt);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("Electrons_charge", &Electrons_charge, &b_Electrons_charge);
   fChain->SetBranchAddress("Electrons_mediumID", &Electrons_mediumID, &b_Electrons_mediumID);
   fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
   fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
   fChain->SetBranchAddress("Electrons_PTW", &Electrons_PTW, &b_Electrons_PTW);
   fChain->SetBranchAddress("Electrons_tightID", &Electrons_tightID, &b_Electrons_tightID);
   fChain->SetBranchAddress("ElectronsNoIso", &ElectronsNoIso, &b_ElectronsNoIso);
   fChain->SetBranchAddress("ElectronsNoIso_mediumID", &ElectronsNoIso_mediumID, &b_ElectronsNoIso_mediumID);
   fChain->SetBranchAddress("ElectronsNoIso_MiniIso", &ElectronsNoIso_MiniIso, &b_ElectronsNoIso_MiniIso);
   fChain->SetBranchAddress("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity, &b_ElectronsNoIso_MT2Activity);
   fChain->SetBranchAddress("ElectronsNoIso_MTW", &ElectronsNoIso_MTW, &b_ElectronsNoIso_MTW);
   fChain->SetBranchAddress("ElectronsNoIso_tightID", &ElectronsNoIso_tightID, &b_ElectronsNoIso_tightID);
   fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
   fChain->SetBranchAddress("GenElectrons_fromTau", &GenElectrons_fromTau, &b_GenElectrons_fromTau);
   fChain->SetBranchAddress("GenElectrons_MT2Activity", &GenElectrons_MT2Activity, &b_GenElectrons_MT2Activity);
   fChain->SetBranchAddress("GenElectrons_RecoTrkAct", &GenElectrons_RecoTrkAct, &b_GenElectrons_RecoTrkAct);
   fChain->SetBranchAddress("GenElectrons_RecoTrkd3", &GenElectrons_RecoTrkd3, &b_GenElectrons_RecoTrkd3);
   fChain->SetBranchAddress("GenElectrons_RecoTrkIso", &GenElectrons_RecoTrkIso, &b_GenElectrons_RecoTrkIso);
   fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
   fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
   fChain->SetBranchAddress("GenJets_HTMask", &GenJets_HTMask, &b_GenJets_HTMask);
   fChain->SetBranchAddress("GenJets_MHTMask", &GenJets_MHTMask, &b_GenJets_MHTMask);
   fChain->SetBranchAddress("GenMET", &GenMET, &b_GenMET);
   fChain->SetBranchAddress("GenMETPhi", &GenMETPhi, &b_GenMETPhi);
   fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
   fChain->SetBranchAddress("GenMHTPhi", &GenMHTPhi, &b_GenMHTPhi);
   fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
   fChain->SetBranchAddress("GenMuons_fromTau", &GenMuons_fromTau, &b_GenMuons_fromTau);
   fChain->SetBranchAddress("GenMuons_MT2Activity", &GenMuons_MT2Activity, &b_GenMuons_MT2Activity);
   fChain->SetBranchAddress("GenMuons_RecoTrkAct", &GenMuons_RecoTrkAct, &b_GenMuons_RecoTrkAct);
   fChain->SetBranchAddress("GenMuons_RecoTrkd3", &GenMuons_RecoTrkd3, &b_GenMuons_RecoTrkd3);
   fChain->SetBranchAddress("GenMuons_RecoTrkIso", &GenMuons_RecoTrkIso, &b_GenMuons_RecoTrkIso);
   fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
   fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
   fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
   fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
   fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
   fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
   fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);
   fChain->SetBranchAddress("GenTaus_LeadRecoTrkAct", &GenTaus_LeadRecoTrkAct, &b_GenTaus_LeadRecoTrkAct);
   fChain->SetBranchAddress("GenTaus_LeadRecoTrkd3", &GenTaus_LeadRecoTrkd3, &b_GenTaus_LeadRecoTrkd3);
   fChain->SetBranchAddress("GenTaus_LeadRecoTrkIso", &GenTaus_LeadRecoTrkIso, &b_GenTaus_LeadRecoTrkIso);
   fChain->SetBranchAddress("GenTaus_LeadTrk", &GenTaus_LeadTrk, &b_GenTaus_LeadTrk);
   fChain->SetBranchAddress("GenTaus_MT2Activity", &GenTaus_MT2Activity, &b_GenTaus_MT2Activity);
   fChain->SetBranchAddress("GenTaus_NNeutralHadrons", &GenTaus_NNeutralHadrons, &b_GenTaus_NNeutralHadrons);
   fChain->SetBranchAddress("GenTaus_NProngs", &GenTaus_NProngs, &b_GenTaus_NProngs);
   fChain->SetBranchAddress("GenTaus_Nu", &GenTaus_Nu, &b_GenTaus_Nu);
   fChain->SetBranchAddress("GenTops", &GenTops, &b_GenTops);
   fChain->SetBranchAddress("GenTopWeight", &GenTopWeight, &b_GenTopWeight);
   fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HTJECdown", &HTJECdown, &b_HTJECdown);
   fChain->SetBranchAddress("HTJECup", &HTJECup, &b_HTJECup);
   fChain->SetBranchAddress("HTJERdown", &HTJERdown, &b_HTJERdown);
   fChain->SetBranchAddress("HTJERup", &HTJERup, &b_HTJERup);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDAK8", &JetIDAK8, &b_JetIDAK8);
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
   fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
   fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);
   fChain->SetBranchAddress("Jets_ISRMask", &Jets_ISRMask, &b_Jets_ISRMask);
   fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
   fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
   fChain->SetBranchAddress("Jets_jerFactor", &Jets_jerFactor, &b_Jets_jerFactor);
   fChain->SetBranchAddress("Jets_jerFactorDown", &Jets_jerFactorDown, &b_Jets_jerFactorDown);
   fChain->SetBranchAddress("Jets_jerFactorUp", &Jets_jerFactorUp, &b_Jets_jerFactorUp);
   fChain->SetBranchAddress("Jets_LeptonMask", &Jets_LeptonMask, &b_Jets_LeptonMask);
   fChain->SetBranchAddress("Jets_MHTMask", &Jets_MHTMask, &b_Jets_MHTMask);
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
   fChain->SetBranchAddress("JetsJECdown_HTMask", &JetsJECdown_HTMask, &b_JetsJECdown_HTMask);
   fChain->SetBranchAddress("JetsJECdown_ID", &JetsJECdown_ID, &b_JetsJECdown_ID);
   fChain->SetBranchAddress("JetsJECdown_ISRMask", &JetsJECdown_ISRMask, &b_JetsJECdown_ISRMask);
   fChain->SetBranchAddress("JetsJECdown_LeptonMask", &JetsJECdown_LeptonMask, &b_JetsJECdown_LeptonMask);
   fChain->SetBranchAddress("JetsJECdown_MHTMask", &JetsJECdown_MHTMask, &b_JetsJECdown_MHTMask);
   fChain->SetBranchAddress("JetsJECdown_muonEnergyFraction", &JetsJECdown_muonEnergyFraction, &b_JetsJECdown_muonEnergyFraction);
   fChain->SetBranchAddress("JetsJECdown_partonFlavor", &JetsJECdown_partonFlavor, &b_JetsJECdown_partonFlavor);
   fChain->SetBranchAddress("JetsJECup", &JetsJECup, &b_JetsJECup);
   fChain->SetBranchAddress("JetsJECup_bDiscriminatorCSV", &JetsJECup_bDiscriminatorCSV, &b_JetsJECup_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJECup_bDiscriminatorMVA", &JetsJECup_bDiscriminatorMVA, &b_JetsJECup_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJECup_hadronFlavor", &JetsJECup_hadronFlavor, &b_JetsJECup_hadronFlavor);
   fChain->SetBranchAddress("JetsJECup_HTMask", &JetsJECup_HTMask, &b_JetsJECup_HTMask);
   fChain->SetBranchAddress("JetsJECup_ID", &JetsJECup_ID, &b_JetsJECup_ID);
   fChain->SetBranchAddress("JetsJECup_ISRMask", &JetsJECup_ISRMask, &b_JetsJECup_ISRMask);
   fChain->SetBranchAddress("JetsJECup_LeptonMask", &JetsJECup_LeptonMask, &b_JetsJECup_LeptonMask);
   fChain->SetBranchAddress("JetsJECup_MHTMask", &JetsJECup_MHTMask, &b_JetsJECup_MHTMask);
   fChain->SetBranchAddress("JetsJECup_muonEnergyFraction", &JetsJECup_muonEnergyFraction, &b_JetsJECup_muonEnergyFraction);
   fChain->SetBranchAddress("JetsJECup_partonFlavor", &JetsJECup_partonFlavor, &b_JetsJECup_partonFlavor);
   fChain->SetBranchAddress("JetsJERdown", &JetsJERdown, &b_JetsJERdown);
   fChain->SetBranchAddress("JetsJERdown_bDiscriminatorCSV", &JetsJERdown_bDiscriminatorCSV, &b_JetsJERdown_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJERdown_bDiscriminatorMVA", &JetsJERdown_bDiscriminatorMVA, &b_JetsJERdown_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJERdown_hadronFlavor", &JetsJERdown_hadronFlavor, &b_JetsJERdown_hadronFlavor);
   fChain->SetBranchAddress("JetsJERdown_HTMask", &JetsJERdown_HTMask, &b_JetsJERdown_HTMask);
   fChain->SetBranchAddress("JetsJERdown_ID", &JetsJERdown_ID, &b_JetsJERdown_ID);
   fChain->SetBranchAddress("JetsJERdown_ISRMask", &JetsJERdown_ISRMask, &b_JetsJERdown_ISRMask);
   fChain->SetBranchAddress("JetsJERdown_LeptonMask", &JetsJERdown_LeptonMask, &b_JetsJERdown_LeptonMask);
   fChain->SetBranchAddress("JetsJERdown_MHTMask", &JetsJERdown_MHTMask, &b_JetsJERdown_MHTMask);
   fChain->SetBranchAddress("JetsJERdown_muonEnergyFraction", &JetsJERdown_muonEnergyFraction, &b_JetsJERdown_muonEnergyFraction);
   fChain->SetBranchAddress("JetsJERdown_partonFlavor", &JetsJERdown_partonFlavor, &b_JetsJERdown_partonFlavor);
   fChain->SetBranchAddress("JetsJERup", &JetsJERup, &b_JetsJERup);
   fChain->SetBranchAddress("JetsJERup_bDiscriminatorCSV", &JetsJERup_bDiscriminatorCSV, &b_JetsJERup_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJERup_bDiscriminatorMVA", &JetsJERup_bDiscriminatorMVA, &b_JetsJERup_bDiscriminatorMVA);
   fChain->SetBranchAddress("JetsJERup_hadronFlavor", &JetsJERup_hadronFlavor, &b_JetsJERup_hadronFlavor);
   fChain->SetBranchAddress("JetsJERup_HTMask", &JetsJERup_HTMask, &b_JetsJERup_HTMask);
   fChain->SetBranchAddress("JetsJERup_ID", &JetsJERup_ID, &b_JetsJERup_ID);
   fChain->SetBranchAddress("JetsJERup_ISRMask", &JetsJERup_ISRMask, &b_JetsJERup_ISRMask);
   fChain->SetBranchAddress("JetsJERup_LeptonMask", &JetsJERup_LeptonMask, &b_JetsJERup_LeptonMask);
   fChain->SetBranchAddress("JetsJERup_MHTMask", &JetsJERup_MHTMask, &b_JetsJERup_MHTMask);
   fChain->SetBranchAddress("JetsJERup_muonEnergyFraction", &JetsJERup_muonEnergyFraction, &b_JetsJERup_muonEnergyFraction);
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
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
   fChain->SetBranchAddress("MHTPhiJECdown", &MHTPhiJECdown, &b_MHTPhiJECdown);
   fChain->SetBranchAddress("MHTPhiJECup", &MHTPhiJECup, &b_MHTPhiJECup);
   fChain->SetBranchAddress("MHTPhiJERdown", &MHTPhiJERdown, &b_MHTPhiJERdown);
   fChain->SetBranchAddress("MHTPhiJERup", &MHTPhiJERup, &b_MHTPhiJERup);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("Muons_charge", &Muons_charge, &b_Muons_charge);
   fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
   fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
   fChain->SetBranchAddress("Muons_PTW", &Muons_PTW, &b_Muons_PTW);
   fChain->SetBranchAddress("Muons_tightID", &Muons_tightID, &b_Muons_tightID);
   fChain->SetBranchAddress("MuonsNoIso", &MuonsNoIso, &b_MuonsNoIso);
   fChain->SetBranchAddress("MuonsNoIso_MiniIso", &MuonsNoIso_MiniIso, &b_MuonsNoIso_MiniIso);
   fChain->SetBranchAddress("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity, &b_MuonsNoIso_MT2Activity);
   fChain->SetBranchAddress("MuonsNoIso_MTW", &MuonsNoIso_MTW, &b_MuonsNoIso_MTW);
   fChain->SetBranchAddress("MuonsNoIso_tightID", &MuonsNoIso_tightID, &b_MuonsNoIso_tightID);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
   fChain->SetBranchAddress("NJetsISRJECdown", &NJetsISRJECdown, &b_NJetsISRJECdown);
   fChain->SetBranchAddress("NJetsISRJECup", &NJetsISRJECup, &b_NJetsISRJECup);
   fChain->SetBranchAddress("NJetsISRJERdown", &NJetsISRJERdown, &b_NJetsISRJERdown);
   fChain->SetBranchAddress("NJetsISRJERup", &NJetsISRJERup, &b_NJetsISRJERup);
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
   fChain->SetBranchAddress("PmssmId", &PmssmId, &b_PmssmId);
   fChain->SetBranchAddress("puSysDown", &puSysDown, &b_puSysDown);
   fChain->SetBranchAddress("puSysUp", &puSysUp, &b_puSysUp);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
   fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
   fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
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
