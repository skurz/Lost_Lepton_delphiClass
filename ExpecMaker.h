#ifndef ExpecMaker_h
#define ExpecMaker_h

#include "SearchBins.h"
#include "LLTools.h"

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


class ExpecMaker : public TSelector {
public :
	void resetValues();
	bool FiltersPass();
	double MuActivity(double muEta, double muPhi, unsigned int method);
	double ElecActivity( double elecEta, double elecPhi, unsigned int method);
	double PionActivity( double pionEta, double pionPhi, unsigned int method);
	std::pair <double,double> minDeltaRLepJet(double lepPT, double lepEta, double lepPhi);
	
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	// Storing stuff
	TTree	*tExpectation_;
	
	SearchBins *SearchBins_;
	// eff variables fot the tree
	UShort_t Expectation;
	UShort_t ExpectationReductionIsoTrack;
	UShort_t FallsVetoLep, FallsVetoIsoTrack;
	UShort_t FallsVetoIsoTrackPT10, FallsVetoIsoTrackPT10IsoCut08, FallsVetoIsoTrackPT10IsoCut12;
	UShort_t muIso, muReco, muAcc, muMTW, muTotal;
	UShort_t muIsoMatched[400], muRecoMatched[400];
	UShort_t elecIso, elecReco, elecAcc, elecMTW, elecTotal;
	UShort_t elecIsoMatched[400], elecRecoMatched[400];
	UShort_t muIsoTrack, muIsoTrackMTW;
	UShort_t muIsoTrackMatchedToGenMu[400], elecIsoTrackMatchedToGenMu[400], pionIsoTrackMatchedToGenMu[400];
	UShort_t muIsoTrackMatchedToGenElec[400], elecIsoTrackMatchedToGenElec[400], pionIsoTrackMatchedToGenElec[400];
	UShort_t muIsoTrackMatchedToGenSingleProngTau[400], elecIsoTrackMatchedToGenSingleProngTau[400], pionIsoTrackMatchedToGenSingleProngTau[400];
	Float_t IsolatedMuonTracksVetoActivity[400],IsolatedElectronTracksVetoActivity[400],IsolatedPionTracksVetoActivity[400];
	Float_t IsolatedMuonTracksVetoMTW[400],IsolatedElectronTracksVetoMTW[400],IsolatedPionTracksVetoMTW[400];
	UShort_t         RecoIsoMuonPromtMatched[400];
	Float_t         RecoIsoMuonPromtMatchedDeltaR[400];
	Float_t         RecoIsoMuonPromtMatchedRelPt[400];
	UShort_t         RecoIsoElecPromtMatched[400];
	Float_t         RecoIsoElecPromtMatchedDeltaR[400];
	Float_t         RecoIsoElecPromtMatchedRelPt[400];
	// isolated track studies
	UShort_t GenMuonIsoTrackMatched[400], RecoIsoMuonIsoTrackMatched[400];
	UShort_t GenElecIsoTrackMatched[400], RecoIsoElecIsoTrackMatched[400];
	Float_t GenMuDeltaRJet_[400], GenMuRelPTJet_[400];
	Float_t GenElecDeltaRJet_[400], GenElecRelPTJet_[400];
	UShort_t GenTauIsoTrackMatched[400];
	UShort_t SelectedIsoTracksMatchedToGenLepton[400], SelectedIsoTracksMatchedToRecoIsoLepton[400];
	Float_t SelectedIsoTracksMatchedToGenDeltaR[400], SelectedIsoTracksMatchedToGenRelPT[400];
	Float_t SelectedIsoTracksMatchedToRecoIsoDeltaR[400], SelectedIsoTracksMatchedToRecoIsoRelPT[400];
	
	UShort_t GenMuonIsolatedTracksPT10Matched[400], RecoIsoMuonIsolatedTracksPT10Matched[400];
	UShort_t GenElecIsolatedTracksPT10Matched[400], RecoIsoElecIsolatedTracksPT10Matched[400];
	UShort_t GenTauIsolatedTracksPT10Matched[400];
	UShort_t IsolatedTracksPT10MatchedToGenLepton[400], IsolatedTracksPT10MatchedToRecoIsoLepton[400];
	Float_t IsolatedTracksPT10MatchedToGenDeltaR[400], IsolatedTracksPT10MatchedToGenRelPT[400];
	Float_t IsolatedTracksPT10MatchedToRecoIsoDeltaR[400], IsolatedTracksPT10MatchedToRecoIsoRelPT[400];
	
	UShort_t GenMuonIsolatedTracksPT10IsoCut08Matched[400], RecoIsoMuonIsolatedTracksPT10IsoCut08Matched[400];
	UShort_t GenElecIsolatedTracksPT10IsoCut08Matched[400], RecoIsoElecIsolatedTracksPT10IsoCut08Matched[400];
	UShort_t GenTauIsolatedTracksPT10IsoCut08Matched[400];
	UShort_t IsolatedTracksPT10IsoCut08MatchedToGenLepton[400], IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton[400];
	Float_t IsolatedTracksPT10IsoCut08MatchedToGenDeltaR[400], IsolatedTracksPT10IsoCut08MatchedToGenRelPT[400];
	Float_t IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR[400], IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT[400];
	
	
	UShort_t GenMuonIsolatedTracksPT10IsoCut12Matched[400], RecoIsoMuonIsolatedTracksPT10IsoCut12Matched[400];
	UShort_t GenElecIsolatedTracksPT10IsoCut12Matched[400], RecoIsoElecIsolatedTracksPT10IsoCut12Matched[400];
	UShort_t GenTauIsolatedTracksPT10IsoCut12Matched[400];
	UShort_t IsolatedTracksPT10IsoCut12MatchedToGenLepton[400], IsolatedTracksPT10IsoCut12MatchedToRecoIsoLepton[400];
	Float_t IsolatedTracksPT10IsoCut12MatchedToGenDeltaR[400], IsolatedTracksPT10IsoCut12MatchedToGenRelPT[400];
	Float_t IsolatedTracksPT10IsoCut12MatchedToRecoIsoDeltaR[400], IsolatedTracksPT10IsoCut12MatchedToRecoIsoRelPT[400];
	// di lep
	UShort_t ExpectationDiLep_, MuDiLepControlSample_, ElecDiLepControlSample_;
	// stand alone isolated track prediction
	UShort_t StandAloneGenMuIsoTrackMatched_, StandAloneIsoTrackToMuMatched_;
	UShort_t StandAloneGenElecIsoTrackMatched_, StandAloneIsoTrackToElecMatched_;
	UShort_t StandAloneIsoTrackToRecoMuMatched_, StandAloneIsoTrackToRecoElecMatched_;
	UShort_t IsoTrackDiLepControlSampleElec_, IsoTrackDiLepControlSampleMu_, IsoTrackDiLepElec_, IsoTrackDiLepMu_;
	
	// activity resetValues
	Float_t         RecoIsoMuonActivity[400], RecoMuonActivity[400], GenMuonActivity[400];
	Float_t         RecoIsoElectronActivity[400], RecoElectronActivity[400], GenElecActivity[400];
	
	Float_t IsoTrackActivity[400], GenTauActivity[400];
	UShort_t elecActivityMethod, muActivityMethod, muIsoTrackActivityMethod, elecIsoTrackActivityMethod, pionIsoTrackActivityMethod;
	bool DY;
	
	UShort_t Bin_;
	
	
	UShort_t MuPurity_, ElecPurity_;
	
	
	Float_t mtw, isoTrackMTW_;
	
	// w pt spectrum extrapolation studies
	Float_t GenMuWPt_, GenElecWPt_;
	Float_t GenMuWPhi_, GenElecWPhi_;
	
	Int_t		isoTracks;
	
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
   UShort_t        GenBosonNum;
   Float_t         GenBosonPt[200];   //[GenBosonNum]
   Float_t         GenBosonEta[200];   //[GenBosonNum]
   Float_t         GenBosonPhi[200];   //[GenBosonNum]
   Float_t         GenBosonE[200];   //[GenBosonNum]
   Int_t           GenBoson_GenBosonPDGId[200];   //[GenBosonNum]
   UShort_t        GenMuNum;
   Float_t         GenMuPt[200];   //[GenMuNum]
   Float_t         GenMuEta[200];   //[GenMuNum]
   Float_t         GenMuPhi[200];   //[GenMuNum]
   Float_t         GenMuE[200];   //[GenMuNum]
   Int_t           GenMu_GenMuFromTau[200];   //[GenMuNum]
   UShort_t        GenElecNum;
   Float_t         GenElecPt[200];   //[GenElecNum]
   Float_t         GenElecEta[200];   //[GenElecNum]
   Float_t         GenElecPhi[200];   //[GenElecNum]
   Float_t         GenElecE[200];   //[GenElecNum]
   Int_t           GenElec_GenElecFromTau[200];   //[GenElecNum]
   UShort_t        GenTauNum;
   Float_t         GenTauPt[200];   //[GenTauNum]
   Float_t         GenTauEta[200];   //[GenTauNum]
   Float_t         GenTauPhi[200];   //[GenTauNum]
   Float_t         GenTauE[200];   //[GenTauNum]
   Int_t           GenTau_GenTauHad[200];   //[GenTauNum]
   UShort_t        TauDecayCandsNum;
   Float_t         TauDecayCandsPt[200];   //[TauDecayCandsNum]
   Float_t         TauDecayCandsEta[200];   //[TauDecayCandsNum]
   Float_t         TauDecayCandsPhi[200];   //[TauDecayCandsNum]
   Float_t         TauDecayCandsE[200];   //[TauDecayCandsNum]
   Int_t           TauDecayCands_pdgID[200];   //[TauDecayCandsNum]
   UShort_t        GenTauNuNum;
   Float_t         GenTauNuPt[200];   //[GenTauNuNum]
   Float_t         GenTauNuEta[200];   //[GenTauNuNum]
   Float_t         GenTauNuPhi[200];   //[GenTauNuNum]
   Float_t         GenTauNuE[200];   //[GenTauNuNum]
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
   vector<int>     *genParticles_PDGid = 0;
   vector<int>     *PassTrigger = 0;
   vector<string>  *TriggerNames = 0;
   vector<TLorentzVector> *genParticles = 0;
   vector<TLorentzVector> *bestPhoton = 0;

	
	// List of branches
   TBranch        *b_RunNum = 0;   //!
   TBranch        *b_LumiBlockNum = 0;   //!
   TBranch        *b_EvtNum = 0;   //!
   TBranch        *b_NVtx = 0;   //!
   TBranch        *b_isoElectronTracks = 0;   //!
   TBranch        *b_isoMuonTracks = 0;   //!
   TBranch        *b_isoPionTracks = 0;   //!
   TBranch        *b_Leptons = 0;   //!
   TBranch        *b_TagLeptonHighPT = 0;   //!
   TBranch        *b_NumPhotons = 0;   //!
   TBranch        *b_METFilters = 0;   //!
   TBranch        *b_CSCTightHaloFilter = 0;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter = 0;   //!
   TBranch        *b_eeBadScFilter = 0;   //!
   TBranch        *b_NJets = 0;   //!
   TBranch        *b_BTags = 0;   //!
   TBranch        *b_Weight = 0;   //!
   TBranch        *b_HT = 0;   //!
   TBranch        *b_MHT = 0;   //!
   TBranch        *b_MHT_Phi = 0;   //!
   TBranch        *b_DeltaPhi1 = 0;   //!
   TBranch        *b_DeltaPhi2 = 0;   //!
   TBranch        *b_DeltaPhi3 = 0;   //!
   TBranch        *b_minDeltaPhiN = 0;   //!
   TBranch        *b_DeltaPhiN1 = 0;   //!
   TBranch        *b_DeltaPhiN2 = 0;   //!
   TBranch        *b_DeltaPhiN3 = 0;   //!
   TBranch        *b_METPt = 0;   //!
   TBranch        *b_METPhi = 0;   //!
   TBranch        *b_GoodVtx = 0;   //!
   TBranch        *b_JetID = 0;   //!
   TBranch        *b_PassHFVeto = 0;   //!
   TBranch        *b_HBHENoiseFilter = 0;   //!
   TBranch        *b_MuonsNum = 0;   //!
   TBranch        *b_MuonsPt = 0;   //!
   TBranch        *b_MuonsEta = 0;   //!
   TBranch        *b_MuonsPhi = 0;   //!
   TBranch        *b_MuonsE = 0;   //!
   TBranch        *b_ElectronsNum = 0;   //!
   TBranch        *b_ElectronsPt = 0;   //!
   TBranch        *b_ElectronsEta = 0;   //!
   TBranch        *b_ElectronsPhi = 0;   //!
   TBranch        *b_ElectronsE = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoNum = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoPt = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoEta = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoPhi = 0;   //!
   TBranch        *b_IsolatedElectronTracksVetoE = 0;   //!
   TBranch        *b_IsolatedElectronTracksVeto_MT = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoNum = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoPt = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoEta = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoPhi = 0;   //!
   TBranch        *b_IsolatedMuonTracksVetoE = 0;   //!
   TBranch        *b_IsolatedMuonTracksVeto_MT = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoNum = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoPt = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoEta = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoPhi = 0;   //!
   TBranch        *b_IsolatedPionTracksVetoE = 0;   //!
   TBranch        *b_IsolatedPionTracksVeto_MT = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNum = 0;   //!
   TBranch        *b_selectedIDIsoMuonsPt = 0;   //!
   TBranch        *b_selectedIDIsoMuonsEta = 0;   //!
   TBranch        *b_selectedIDIsoMuonsPhi = 0;   //!
   TBranch        *b_selectedIDIsoMuonsE = 0;   //!
   TBranch        *b_selectedIDIsoMuons_MTW = 0;   //!
   TBranch        *b_selectedIDMuonsNum = 0;   //!
   TBranch        *b_selectedIDMuonsPt = 0;   //!
   TBranch        *b_selectedIDMuonsEta = 0;   //!
   TBranch        *b_selectedIDMuonsPhi = 0;   //!
   TBranch        *b_selectedIDMuonsE = 0;   //!
   TBranch        *b_selectedIDMuons_MTW = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNum = 0;   //!
   TBranch        *b_selectedIDIsoElectronsPt = 0;   //!
   TBranch        *b_selectedIDIsoElectronsEta = 0;   //!
   TBranch        *b_selectedIDIsoElectronsPhi = 0;   //!
   TBranch        *b_selectedIDIsoElectronsE = 0;   //!
   TBranch        *b_selectedIDIsoElectrons_MTW = 0;   //!
   TBranch        *b_selectedIDElectronsNum = 0;   //!
   TBranch        *b_selectedIDElectronsPt = 0;   //!
   TBranch        *b_selectedIDElectronsEta = 0;   //!
   TBranch        *b_selectedIDElectronsPhi = 0;   //!
   TBranch        *b_selectedIDElectronsE = 0;   //!
   TBranch        *b_selectedIDElectrons_MTW = 0;   //!
   TBranch        *b_SelectedPFCandidatesNum = 0;   //!
   TBranch        *b_SelectedPFCandidatesPt = 0;   //!
   TBranch        *b_SelectedPFCandidatesEta = 0;   //!
   TBranch        *b_SelectedPFCandidatesPhi = 0;   //!
   TBranch        *b_SelectedPFCandidatesE = 0;   //!
   TBranch        *b_SelectedPFCandidates_Charge = 0;   //!
   TBranch        *b_SelectedPFCandidates_Typ = 0;   //!
   TBranch        *b_GenBosonNum = 0;   //!
   TBranch        *b_GenBosonPt = 0;   //!
   TBranch        *b_GenBosonEta = 0;   //!
   TBranch        *b_GenBosonPhi = 0;   //!
   TBranch        *b_GenBosonE = 0;   //!
   TBranch        *b_GenBoson_GenBosonPDGId = 0;   //!
   TBranch        *b_GenMuNum = 0;   //!
   TBranch        *b_GenMuPt = 0;   //!
   TBranch        *b_GenMuEta = 0;   //!
   TBranch        *b_GenMuPhi = 0;   //!
   TBranch        *b_GenMuE = 0;   //!
   TBranch        *b_GenMu_GenMuFromTau = 0;   //!
   TBranch        *b_GenElecNum = 0;   //!
   TBranch        *b_GenElecPt = 0;   //!
   TBranch        *b_GenElecEta = 0;   //!
   TBranch        *b_GenElecPhi = 0;   //!
   TBranch        *b_GenElecE = 0;   //!
   TBranch        *b_GenElec_GenElecFromTau = 0;   //!
   TBranch        *b_GenTauNum = 0;   //!
   TBranch        *b_GenTauPt = 0;   //!
   TBranch        *b_GenTauEta = 0;   //!
   TBranch        *b_GenTauPhi = 0;   //!
   TBranch        *b_GenTauE = 0;   //!
   TBranch        *b_GenTau_GenTauHad = 0;   //!
   TBranch        *b_TauDecayCandsNum = 0;   //!
   TBranch        *b_TauDecayCandsPt = 0;   //!
   TBranch        *b_TauDecayCandsEta = 0;   //!
   TBranch        *b_TauDecayCandsPhi = 0;   //!
   TBranch        *b_TauDecayCandsE = 0;   //!
   TBranch        *b_TauDecayCands_pdgID = 0;   //!
   TBranch        *b_GenTauNuNum = 0;   //!
   TBranch        *b_GenTauNuPt = 0;   //!
   TBranch        *b_GenTauNuEta = 0;   //!
   TBranch        *b_GenTauNuPhi = 0;   //!
   TBranch        *b_GenTauNuE = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoNum = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPt = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoEta = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPhi = 0;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoE = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoNum = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPt = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoEta = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPhi = 0;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoE = 0;   //!
   TBranch        *b_JetsNum = 0;   //!
   TBranch        *b_JetsPt = 0;   //!
   TBranch        *b_JetsEta = 0;   //!
   TBranch        *b_JetsPhi = 0;   //!
   TBranch        *b_JetsE = 0;   //!
   TBranch        *b_Jets_bDiscriminator = 0;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction = 0;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction = 0;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity = 0;   //!
   TBranch        *b_Jets_electronMultiplicity = 0;   //!
   TBranch        *b_Jets_jetArea = 0;   //!
   TBranch        *b_Jets_muonEnergyFraction = 0;   //!
   TBranch        *b_Jets_muonMultiplicity = 0;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction = 0;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity = 0;   //!
   TBranch        *b_Jets_photonEnergyFraction = 0;   //!
   TBranch        *b_Jets_photonMultiplicity = 0;   //!
   TBranch        *b_slimmedElectronsNum = 0;   //!
   TBranch        *b_slimmedElectronsPt = 0;   //!
   TBranch        *b_slimmedElectronsEta = 0;   //!
   TBranch        *b_slimmedElectronsPhi = 0;   //!
   TBranch        *b_slimmedElectronsE = 0;   //!
   TBranch        *b_slimmedMuonsNum = 0;   //!
   TBranch        *b_slimmedMuonsPt = 0;   //!
   TBranch        *b_slimmedMuonsEta = 0;   //!
   TBranch        *b_slimmedMuonsPhi = 0;   //!
   TBranch        *b_slimmedMuonsE = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesNum = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesPt = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesEta = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesPhi = 0;   //!
   TBranch        *b_SelectedPFElecCandidatesE = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesNum = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesPt = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesEta = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesPhi = 0;   //!
   TBranch        *b_SelectedPFMuCandidatesE = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesNum = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesPt = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesEta = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesPhi = 0;   //!
   TBranch        *b_SelectedPFPionCandidatesE = 0;   //!
   TBranch        *b_genParticles_PDGid = 0;   //!
   TBranch        *b_PassTrigger = 0;   //!
   TBranch        *b_TriggerNames = 0;   //!
   TBranch        *b_genParticles = 0;   //!
   TBranch        *b_bestPhoton = 0;   //!
	
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
   fChain->SetBranchAddress("GenBosonNum", &GenBosonNum, &b_GenBosonNum);
   fChain->SetBranchAddress("GenBosonPt", GenBosonPt, &b_GenBosonPt);
   fChain->SetBranchAddress("GenBosonEta", GenBosonEta, &b_GenBosonEta);
   fChain->SetBranchAddress("GenBosonPhi", GenBosonPhi, &b_GenBosonPhi);
   fChain->SetBranchAddress("GenBosonE", GenBosonE, &b_GenBosonE);
   fChain->SetBranchAddress("GenBoson_GenBosonPDGId", GenBoson_GenBosonPDGId, &b_GenBoson_GenBosonPDGId);
   fChain->SetBranchAddress("GenMuNum", &GenMuNum, &b_GenMuNum);
   fChain->SetBranchAddress("GenMuPt", GenMuPt, &b_GenMuPt);
   fChain->SetBranchAddress("GenMuEta", GenMuEta, &b_GenMuEta);
   fChain->SetBranchAddress("GenMuPhi", GenMuPhi, &b_GenMuPhi);
   fChain->SetBranchAddress("GenMuE", GenMuE, &b_GenMuE);
   fChain->SetBranchAddress("GenMu_GenMuFromTau", GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
   fChain->SetBranchAddress("GenElecNum", &GenElecNum, &b_GenElecNum);
   fChain->SetBranchAddress("GenElecPt", GenElecPt, &b_GenElecPt);
   fChain->SetBranchAddress("GenElecEta", GenElecEta, &b_GenElecEta);
   fChain->SetBranchAddress("GenElecPhi", GenElecPhi, &b_GenElecPhi);
   fChain->SetBranchAddress("GenElecE", GenElecE, &b_GenElecE);
   fChain->SetBranchAddress("GenElec_GenElecFromTau", GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
   fChain->SetBranchAddress("GenTauNum", &GenTauNum, &b_GenTauNum);
   fChain->SetBranchAddress("GenTauPt", GenTauPt, &b_GenTauPt);
   fChain->SetBranchAddress("GenTauEta", GenTauEta, &b_GenTauEta);
   fChain->SetBranchAddress("GenTauPhi", GenTauPhi, &b_GenTauPhi);
   fChain->SetBranchAddress("GenTauE", GenTauE, &b_GenTauE);
   fChain->SetBranchAddress("GenTau_GenTauHad", GenTau_GenTauHad, &b_GenTau_GenTauHad);
   fChain->SetBranchAddress("TauDecayCandsNum", &TauDecayCandsNum, &b_TauDecayCandsNum);
   fChain->SetBranchAddress("TauDecayCandsPt", TauDecayCandsPt, &b_TauDecayCandsPt);
   fChain->SetBranchAddress("TauDecayCandsEta", TauDecayCandsEta, &b_TauDecayCandsEta);
   fChain->SetBranchAddress("TauDecayCandsPhi", TauDecayCandsPhi, &b_TauDecayCandsPhi);
   fChain->SetBranchAddress("TauDecayCandsE", TauDecayCandsE, &b_TauDecayCandsE);
   fChain->SetBranchAddress("TauDecayCands_pdgID", TauDecayCands_pdgID, &b_TauDecayCands_pdgID);
   fChain->SetBranchAddress("GenTauNuNum", &GenTauNuNum, &b_GenTauNuNum);
   fChain->SetBranchAddress("GenTauNuPt", GenTauNuPt, &b_GenTauNuPt);
   fChain->SetBranchAddress("GenTauNuEta", GenTauNuEta, &b_GenTauNuEta);
   fChain->SetBranchAddress("GenTauNuPhi", GenTauNuPhi, &b_GenTauNuPhi);
   fChain->SetBranchAddress("GenTauNuE", GenTauNuE, &b_GenTauNuE);
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
   fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid, &b_genParticles_PDGid);
   fChain->SetBranchAddress("PassTrigger", &PassTrigger, &b_PassTrigger);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("genParticles", &genParticles, &b_genParticles);
   fChain->SetBranchAddress("bestPhoton", &bestPhoton, &b_bestPhoton);
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

