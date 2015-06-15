#ifndef ExpecMaker_h
#define ExpecMaker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"

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

// actity around lepton
const double maxDeltaRMuActivity_=1.0;
const double maxDeltaRElecActivity_=1.0;
const double maxDeltaRIsoTrackActivity_=1.0;
const unsigned int elecActivityMethod_=0;               // ###############
const unsigned int muActivityMethod_=0;                 // ###############
const unsigned int isoTrackActivityMethod_=0;

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
// search bins
class Bin
{
public:
  Bin(){}
  Bin(double HTmin, double HTmax, double MHTmin, double MHTmax, int NJetsmin, int NJetsmax, int BTagsmin, int BTagsmax)
  {
    HTmin_=HTmin;
    HTmax_=HTmax;
    MHTmin_=MHTmin;
    MHTmax_=MHTmax;
    NJetsmin_=NJetsmin;
    NJetsmax_=NJetsmax;
    BTagsmin_=BTagsmin;
    BTagsmax_=BTagsmax;
  }
  double HTmin_, HTmax_, MHTmin_, MHTmax_;
  int NJetsmin_, NJetsmax_, BTagsmin_, BTagsmax_;
  ~Bin(){}
private:
};
class SearchBins
{
public:
  SearchBins();
  unsigned int GetBinNumber(double HT, double MHT, int NJets, int BTags);
  void PrintUsed();
  
  
  ~SearchBins(){}
protected:
  std::vector<Bin> bins_;
  std::vector<int> usedBin_;
};
class ExpecMaker : public TSelector {
public :
	void resetValues();
	bool FiltersPass();
	double deltaR(double eta1, double phi1, double eta2, double phi2);
	double MTWCalculator(double metPt,double  metPhi,double  lepPt,double  lepPhi);
	double MuActivity(double muEta, double muPhi, unsigned int method);
	double ElecActivity( double elecEta, double elecPhi, unsigned int method);
	double IsoTrackActivityCalc( double isoTrackEta, double isoTrackPhi, unsigned int method);
	
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
	UShort_t muIsoMatched[40], muRecoMatched[40];
	UShort_t elecIso, elecReco, elecAcc, elecMTW, elecTotal;
	UShort_t elecIsoMatched[40], elecRecoMatched[40];
	UShort_t muIsoTrack, muIsoTrackMTW;
	UShort_t muIsoTrackMatched[40], elecIsoTrackMatched[40];
	UShort_t elecIsoTrack, elecIsoTrackMTW;
	UShort_t         RecoIsoMuonPromtMatched[40];
	Float_t         RecoIsoMuonPromtMatchedDeltaR[40];
	Float_t         RecoIsoMuonPromtMatchedRelPt[40];
	UShort_t         RecoIsoElecPromtMatched[40];
	Float_t         RecoIsoElecPromtMatchedDeltaR[40];
	Float_t         RecoIsoElecPromtMatchedRelPt[40];
	// isolated track studies
	UShort_t GenMuonIsoTrackMatched[40], RecoIsoMuonIsoTrackMatched[40];
	UShort_t GenElecIsoTrackMatched[40], RecoIsoElecIsoTrackMatched[40];
	UShort_t GenTauIsoTrackMatched[40];
	UShort_t SelectedIsoTracksMatchedToGenLepton[40], SelectedIsoTracksMatchedToRecoIsoLepton[40];
	Float_t SelectedIsoTracksMatchedToGenDeltaR[40], SelectedIsoTracksMatchedToGenRelPT[40];
	Float_t SelectedIsoTracksMatchedToRecoIsoDeltaR[40], SelectedIsoTracksMatchedToRecoIsoRelPT[40];
	
	UShort_t GenMuonIsolatedTracksPT10Matched[40], RecoIsoMuonIsolatedTracksPT10Matched[40];
	UShort_t GenElecIsolatedTracksPT10Matched[40], RecoIsoElecIsolatedTracksPT10Matched[40];
	UShort_t GenTauIsolatedTracksPT10Matched[40];
	UShort_t IsolatedTracksPT10MatchedToGenLepton[40], IsolatedTracksPT10MatchedToRecoIsoLepton[40];
	Float_t IsolatedTracksPT10MatchedToGenDeltaR[40], IsolatedTracksPT10MatchedToGenRelPT[40];
	Float_t IsolatedTracksPT10MatchedToRecoIsoDeltaR[40], IsolatedTracksPT10MatchedToRecoIsoRelPT[40];
	
	UShort_t GenMuonIsolatedTracksPT10IsoCut08Matched[40], RecoIsoMuonIsolatedTracksPT10IsoCut08Matched[40];
	UShort_t GenElecIsolatedTracksPT10IsoCut08Matched[40], RecoIsoElecIsolatedTracksPT10IsoCut08Matched[40];
	UShort_t GenTauIsolatedTracksPT10IsoCut08Matched[40];
	UShort_t IsolatedTracksPT10IsoCut08MatchedToGenLepton[40], IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton[40];
	Float_t IsolatedTracksPT10IsoCut08MatchedToGenDeltaR[40], IsolatedTracksPT10IsoCut08MatchedToGenRelPT[40];
	Float_t IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR[40], IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT[40];
	
	
	UShort_t GenMuonIsolatedTracksPT10IsoCut12Matched[40], RecoIsoMuonIsolatedTracksPT10IsoCut12Matched[40];
	UShort_t GenElecIsolatedTracksPT10IsoCut12Matched[40], RecoIsoElecIsolatedTracksPT10IsoCut12Matched[40];
	UShort_t GenTauIsolatedTracksPT10IsoCut12Matched[40];
	UShort_t IsolatedTracksPT10IsoCut12MatchedToGenLepton[40], IsolatedTracksPT10IsoCut12MatchedToRecoIsoLepton[40];
	Float_t IsolatedTracksPT10IsoCut12MatchedToGenDeltaR[40], IsolatedTracksPT10IsoCut12MatchedToGenRelPT[40];
	Float_t IsolatedTracksPT10IsoCut12MatchedToRecoIsoDeltaR[40], IsolatedTracksPT10IsoCut12MatchedToRecoIsoRelPT[40];
	// di lep
	UShort_t ExpectationDiLep_, MuDiLepControlSample_, ElecDiLepControlSample_;
	// stand alone isolated track prediction
	UShort_t StandAloneGenMuIsoTrackMatched_, StandAloneIsoTrackToMuMatched_;
	UShort_t StandAloneGenElecIsoTrackMatched_, StandAloneIsoTrackToElecMatched_;
	UShort_t StandAloneIsoTrackToRecoMuMatched_, StandAloneIsoTrackToRecoElecMatched_;
	UShort_t IsoTrackDiLepControlSampleElec_, IsoTrackDiLepControlSampleMu_, IsoTrackDiLepElec_, IsoTrackDiLepMu_;
	
	// activity resetValues
	Float_t         RecoIsoMuonActivity[40], RecoMuonActivity[40], GenMuonActivity[40];
	Float_t         RecoIsoElectronActivity[40], RecoElectronActivity[40], GenElecActivity[40];
	
	Float_t IsoTrackActivity[40], GenTauActivity[40];
	UShort_t elecActivityMethod, muActivityMethod, isoTrackActivityMethod;
	bool DY;
	
	UShort_t Bin_;
	
	
	UShort_t MuPurity_, ElecPurity_;
	
	
	Float_t mtw, isoTrackMTW_;
	
	// Declaration of leaf types
	UInt_t          RunNum;
	UInt_t          LumiBlockNum;
	UInt_t          EvtNum;
	Int_t           NVtx;
	Int_t           isoTracks;
	Int_t           Leptons;
	Int_t           LeptonsNoMiniIsolation;
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
	Float_t         MuonsPt[100];   //[MuonsNum]
	Float_t         MuonsEta[100];   //[MuonsNum]
	Float_t         MuonsPhi[100];   //[MuonsNum]
	Float_t         MuonsE[100];   //[MuonsNum]
	UShort_t        ElectronsNum;
	Float_t         ElectronsPt[100];   //[ElectronsNum]
	Float_t         ElectronsEta[100];   //[ElectronsNum]
	Float_t         ElectronsPhi[100];   //[ElectronsNum]
	Float_t         ElectronsE[100];   //[ElectronsNum]
	UShort_t        IsolatedTracksNum;
	Float_t         IsolatedTracksPt[100];   //[IsolatedTracksNum]
	Float_t         IsolatedTracksEta[100];   //[IsolatedTracksNum]
	Float_t         IsolatedTracksPhi[100];   //[IsolatedTracksNum]
	Float_t         IsolatedTracksE[100];   //[IsolatedTracksNum]
	UShort_t        selectedIDIsoMuonsNum;
	Float_t         selectedIDIsoMuonsPt[100];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsEta[100];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsPhi[100];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsE[100];   //[selectedIDIsoMuonsNum]
	UShort_t        selectedIDMuonsNum;
	Float_t         selectedIDMuonsPt[100];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsEta[100];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsPhi[100];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsE[100];   //[selectedIDMuonsNum]
	UShort_t        selectedIDIsoElectronsNum;
	Float_t         selectedIDIsoElectronsPt[100];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsEta[100];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsPhi[100];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsE[100];   //[selectedIDIsoElectronsNum]
	UShort_t        selectedIDElectronsNum;
	Float_t         selectedIDElectronsPt[100];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsEta[100];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsPhi[100];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsE[100];   //[selectedIDElectronsNum]
	UShort_t        SelectedPFCandidatesNum;
	Float_t         SelectedPFCandidatesPt[1000];   //[SelectedPFCandidatesNum]
	Float_t         SelectedPFCandidatesEta[1000];   //[SelectedPFCandidatesNum]
	Float_t         SelectedPFCandidatesPhi[1000];   //[SelectedPFCandidatesNum]
	Float_t         SelectedPFCandidatesE[1000];   //[SelectedPFCandidatesNum]
	Int_t           SelectedPFCandidates_Charge[1000];   //[SelectedPFCandidatesNum]
	Int_t           SelectedPFCandidates_Typ[1000];   //[SelectedPFCandidatesNum]
	UShort_t        GenBosonNum;
	Float_t         GenBosonPt[100];   //[GenBosonNum]
	Float_t         GenBosonEta[100];   //[GenBosonNum]
	Float_t         GenBosonPhi[100];   //[GenBosonNum]
	Float_t         GenBosonE[100];   //[GenBosonNum]
	Int_t           GenBoson_GenBosonPDGId[100];   //[GenBosonNum]
	UShort_t        GenMuNum;
	Float_t         GenMuPt[100];   //[GenMuNum]
	Float_t         GenMuEta[100];   //[GenMuNum]
	Float_t         GenMuPhi[100];   //[GenMuNum]
	Float_t         GenMuE[100];   //[GenMuNum]
	Int_t           GenMu_GenMuFromTau[100];   //[GenMuNum]
	UShort_t        GenElecNum;
	Float_t         GenElecPt[100];   //[GenElecNum]
	Float_t         GenElecEta[100];   //[GenElecNum]
	Float_t         GenElecPhi[100];   //[GenElecNum]
	Float_t         GenElecE[100];   //[GenElecNum]
	Int_t           GenElec_GenElecFromTau[100];   //[GenElecNum]
	UShort_t        GenTauNum;
	Float_t         GenTauPt[100];   //[GenTauNum]
	Float_t         GenTauEta[100];   //[GenTauNum]
	Float_t         GenTauPhi[100];   //[GenTauNum]
	Float_t         GenTauE[100];   //[GenTauNum]
	Int_t           GenTau_GenTauHad[100];   //[GenTauNum]
	UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
	Float_t         selectedIDIsoMuonsNoMiniIsoPt[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
	Float_t         selectedIDIsoMuonsNoMiniIsoEta[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
	Float_t         selectedIDIsoMuonsNoMiniIsoPhi[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
	Float_t         selectedIDIsoMuonsNoMiniIsoE[3];   //[selectedIDIsoMuonsNoMiniIsoNum]
	UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
	Float_t         selectedIDIsoElectronsNoMiniIsoPt[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
	Float_t         selectedIDIsoElectronsNoMiniIsoEta[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
	Float_t         selectedIDIsoElectronsNoMiniIsoPhi[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
	Float_t         selectedIDIsoElectronsNoMiniIsoE[100];   //[selectedIDIsoElectronsNoMiniIsoNum]
	UShort_t        JetsNum;
	Float_t         JetsPt[1000];   //[JetsNum]
	Float_t         JetsEta[1000];   //[JetsNum]
	Float_t         JetsPhi[1000];   //[JetsNum]
	Float_t         JetsE[1000];   //[JetsNum]
	Float_t         Jets_bDiscriminator[1000];   //[JetsNum]
	Float_t         Jets_chargedEmEnergyFraction[1000];   //[JetsNum]
	Float_t         Jets_chargedHadronEnergyFraction[1000];   //[JetsNum]
	Int_t           Jets_chargedHadronMultiplicity[1000];   //[JetsNum]
	Int_t           Jets_electronMultiplicity[1000];   //[JetsNum]
	Float_t         Jets_jetArea[1000];   //[JetsNum]
	Float_t         Jets_muonEnergyFraction[1000];   //[JetsNum]
	Int_t           Jets_muonMultiplicity[1000];   //[JetsNum]
	Float_t         Jets_neutralEmEnergyFraction[1000];   //[JetsNum]
	Int_t           Jets_neutralHadronMultiplicity[1000];   //[JetsNum]
	Float_t         Jets_photonEnergyFraction[1000];   //[JetsNum]
	Int_t           Jets_photonMultiplicity[1000];   //[JetsNum]
	UShort_t        slimmedElectronsNum;
	Float_t         slimmedElectronsPt[1000];   //[slimmedElectronsNum]
	Float_t         slimmedElectronsEta[1000];   //[slimmedElectronsNum]
	Float_t         slimmedElectronsPhi[1000];   //[slimmedElectronsNum]
	Float_t         slimmedElectronsE[1000];   //[slimmedElectronsNum]
	UShort_t        slimmedMuonsNum;
	Float_t         slimmedMuonsPt[1000];   //[slimmedMuonsNum]
	Float_t         slimmedMuonsEta[1000];   //[slimmedMuonsNum]
	Float_t         slimmedMuonsPhi[1000];   //[slimmedMuonsNum]
	Float_t         slimmedMuonsE[1000];   //[slimmedMuonsNum]
	
	// List of branches
	TBranch        *b_RunNum;   //!
	TBranch        *b_LumiBlockNum;   //!
	TBranch        *b_EvtNum;   //!
	TBranch        *b_NVtx;   //!
	TBranch        *b_isoTracks;   //!
	TBranch        *b_Leptons;   //!
	TBranch        *b_LeptonsNoMiniIsolation;   //!
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
	TBranch        *b_IsolatedTracksNum;   //!
	TBranch        *b_IsolatedTracksPt;   //!
	TBranch        *b_IsolatedTracksEta;   //!
	TBranch        *b_IsolatedTracksPhi;   //!
	TBranch        *b_IsolatedTracksE;   //!
	TBranch        *b_selectedIDIsoMuonsNum;   //!
	TBranch        *b_selectedIDIsoMuonsPt;   //!
	TBranch        *b_selectedIDIsoMuonsEta;   //!
	TBranch        *b_selectedIDIsoMuonsPhi;   //!
	TBranch        *b_selectedIDIsoMuonsE;   //!
	TBranch        *b_selectedIDMuonsNum;   //!
	TBranch        *b_selectedIDMuonsPt;   //!
	TBranch        *b_selectedIDMuonsEta;   //!
	TBranch        *b_selectedIDMuonsPhi;   //!
	TBranch        *b_selectedIDMuonsE;   //!
	TBranch        *b_selectedIDIsoElectronsNum;   //!
	TBranch        *b_selectedIDIsoElectronsPt;   //!
	TBranch        *b_selectedIDIsoElectronsEta;   //!
	TBranch        *b_selectedIDIsoElectronsPhi;   //!
	TBranch        *b_selectedIDIsoElectronsE;   //!
	TBranch        *b_selectedIDElectronsNum;   //!
	TBranch        *b_selectedIDElectronsPt;   //!
	TBranch        *b_selectedIDElectronsEta;   //!
	TBranch        *b_selectedIDElectronsPhi;   //!
	TBranch        *b_selectedIDElectronsE;   //!
	TBranch        *b_SelectedPFCandidatesNum;   //!
	TBranch        *b_SelectedPFCandidatesPt;   //!
	TBranch        *b_SelectedPFCandidatesEta;   //!
	TBranch        *b_SelectedPFCandidatesPhi;   //!
	TBranch        *b_SelectedPFCandidatesE;   //!
	TBranch        *b_SelectedPFCandidates_Charge;   //!
	TBranch        *b_SelectedPFCandidates_Typ;   //!
	TBranch        *b_GenBosonNum;   //!
	TBranch        *b_GenBosonPt;   //!
	TBranch        *b_GenBosonEta;   //!
	TBranch        *b_GenBosonPhi;   //!
	TBranch        *b_GenBosonE;   //!
	TBranch        *b_GenBoson_GenBosonPDGId;   //!
	TBranch        *b_GenMuNum;   //!
	TBranch        *b_GenMuPt;   //!
	TBranch        *b_GenMuEta;   //!
	TBranch        *b_GenMuPhi;   //!
	TBranch        *b_GenMuE;   //!
	TBranch        *b_GenMu_GenMuFromTau;   //!
	TBranch        *b_GenElecNum;   //!
	TBranch        *b_GenElecPt;   //!
	TBranch        *b_GenElecEta;   //!
	TBranch        *b_GenElecPhi;   //!
	TBranch        *b_GenElecE;   //!
	TBranch        *b_GenElec_GenElecFromTau;   //!
	TBranch        *b_GenTauNum;   //!
	TBranch        *b_GenTauPt;   //!
	TBranch        *b_GenTauEta;   //!
	TBranch        *b_GenTauPhi;   //!
	TBranch        *b_GenTauE;   //!
	TBranch        *b_GenTau_GenTauHad;   //!
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
  fChain->SetBranchAddress("isoTracks", &isoTracks, &b_isoTracks);
  fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
  fChain->SetBranchAddress("LeptonsNoMiniIsolation", &LeptonsNoMiniIsolation, &b_LeptonsNoMiniIsolation);
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
  fChain->SetBranchAddress("IsolatedTracksNum", &IsolatedTracksNum, &b_IsolatedTracksNum);
  fChain->SetBranchAddress("IsolatedTracksPt", IsolatedTracksPt, &b_IsolatedTracksPt);
  fChain->SetBranchAddress("IsolatedTracksEta", IsolatedTracksEta, &b_IsolatedTracksEta);
  fChain->SetBranchAddress("IsolatedTracksPhi", IsolatedTracksPhi, &b_IsolatedTracksPhi);
  fChain->SetBranchAddress("IsolatedTracksE", IsolatedTracksE, &b_IsolatedTracksE);
  fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
  fChain->SetBranchAddress("selectedIDIsoMuonsPt", selectedIDIsoMuonsPt, &b_selectedIDIsoMuonsPt);
  fChain->SetBranchAddress("selectedIDIsoMuonsEta", selectedIDIsoMuonsEta, &b_selectedIDIsoMuonsEta);
  fChain->SetBranchAddress("selectedIDIsoMuonsPhi", selectedIDIsoMuonsPhi, &b_selectedIDIsoMuonsPhi);
  fChain->SetBranchAddress("selectedIDIsoMuonsE", selectedIDIsoMuonsE, &b_selectedIDIsoMuonsE);
  fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
  fChain->SetBranchAddress("selectedIDMuonsPt", selectedIDMuonsPt, &b_selectedIDMuonsPt);
  fChain->SetBranchAddress("selectedIDMuonsEta", selectedIDMuonsEta, &b_selectedIDMuonsEta);
  fChain->SetBranchAddress("selectedIDMuonsPhi", selectedIDMuonsPhi, &b_selectedIDMuonsPhi);
  fChain->SetBranchAddress("selectedIDMuonsE", selectedIDMuonsE, &b_selectedIDMuonsE);
  fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
  fChain->SetBranchAddress("selectedIDIsoElectronsPt", selectedIDIsoElectronsPt, &b_selectedIDIsoElectronsPt);
  fChain->SetBranchAddress("selectedIDIsoElectronsEta", selectedIDIsoElectronsEta, &b_selectedIDIsoElectronsEta);
  fChain->SetBranchAddress("selectedIDIsoElectronsPhi", selectedIDIsoElectronsPhi, &b_selectedIDIsoElectronsPhi);
  fChain->SetBranchAddress("selectedIDIsoElectronsE", selectedIDIsoElectronsE, &b_selectedIDIsoElectronsE);
  fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
  fChain->SetBranchAddress("selectedIDElectronsPt", selectedIDElectronsPt, &b_selectedIDElectronsPt);
  fChain->SetBranchAddress("selectedIDElectronsEta", selectedIDElectronsEta, &b_selectedIDElectronsEta);
  fChain->SetBranchAddress("selectedIDElectronsPhi", selectedIDElectronsPhi, &b_selectedIDElectronsPhi);
  fChain->SetBranchAddress("selectedIDElectronsE", selectedIDElectronsE, &b_selectedIDElectronsE);
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

