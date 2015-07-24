#ifndef EffMaker_h
#define EffMaker_h

//#include <LLTools.h>
#include <THEff.h>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <TLegend.h>


// output control
const bool saveEffToPDF_=true;
const bool saveEffToPNG_=false;
// cuts

const double mtwCut_ = 100;
// binning of efficiencies
// gloabel 1D binning

const int oneDHT_=14;
double OneDHT_[oneDHT_] = {350,500,550,600,650,700,750,800,900,1000,1200,1500,2000,8000};
const int oneDMHT_=16;
double OneDMHT_[oneDMHT_] = {0,50,100,150,200,250,300,350,450,500,600,700,900,1200,1700,8000};
const int oneDNJets_=6;
double OneDNJets_[oneDNJets_] = {4,5,6,8,11,20};
const int oneDBJets_=6;
double OneDBJets_[oneDBJets_] = {0,1,2,3,5,10};
const int oneDDeltaR_=8;
double OneDDeltaR_[oneDDeltaR_]={0, 0.2 ,0.3, 0.5 ,0.7 ,1.0 , 1.8, 5.0 };
const int oneDPTRel_=7;
double OneDPTRel_[oneDPTRel_]={0, 0.2 ,0.4 ,0.6 ,0.8 ,1.0 , 10.0};

// used for closure
// const int oneDPT_=12;
// double OneDPT_[oneDPT_]={10,15,20,25,30,40,50,60,70,90,110,1900};
// const int oneDActivity_=9;
// double OneDActivity_[oneDActivity_]={0,5,10,20,40,60,80,100,1600};
// used to compare with tag and probe eff.
const int oneDPT_=7;
double OneDPT_[oneDPT_]={10,20,25,30,40,50,200};
const int oneDActivity_=6;
double OneDActivity_[oneDActivity_]={0,20,40,60,150,1600};

// purity
//mu
//1D

//2D
const int mupurityMHT_ = 5;
double muPurityMHT_[mupurityMHT_] ={200,800,900,1200,9600};
const int mupurityNJet_ = 3;
double muPurityNJet_[mupurityNJet_] ={4,5,20};

// elec

//1D


const int elecpurityMHT_ = 7;
double elecPurityMHT_[elecpurityMHT_] ={0,100,200,800,900,1200,9600};
const int elecpurityNJet_ = 3;
double elecPurityNJet_[elecpurityNJet_] ={4,5,20};
// mu acceptance
// 2D
const int muaccHT_ = 4;
double muAccHT_ [muaccHT_] = {500,800,1200,2500};
const int muaccMHT_ = 4;
double muAccMHT_ [muaccMHT_] = {200,500,750,1900};
const int muaccBTags_ = 5;
double muAccBTags_[muaccBTags_] = {0,1,2,3,10};
const int muaccNJets_ = 5;
double muAccNJets_ [muaccNJets_] = {4,5,6,9,20};

// elec acceptance
// 2D
const int elecaccHT_ = 4;
double elecAccHT_ [elecaccHT_] = {500,800,1200,2500};
const int elecaccMHT_ = 4;
double elecAccMHT_ [elecaccMHT_] = {200,500,750,1900};
const int elecaccBTags_ = 5;
double elecAccBTags_[elecaccBTags_] = {0,1,2,3,10};
const int elecaccNJets_ = 6;
double elecAccNJets_ [elecaccNJets_] = {4,5,6,8,11,20};

// mtw
// 2D
const int muMTWPT2D_=9;
double MuMTWPT2D_[muMTWPT2D_]={10,30,40,50,60,70,90,110,1900};
const int muMTWActivity2D_=9;
double MuMTWActivity2D_[muMTWActivity2D_]={0,5,10,20,40,60,80,100,1600};

const int elecMTWPT2D_=9;
double ElecMTWPT2D_[elecMTWPT2D_]={10,30,40,50,60,70,90,110,1900};
const int elecMTWActivity2D_=9;
double ElecMTWActivity2D_[elecMTWActivity2D_]={0,5,10,20,40,60,80,100,1600};

// isotrack reduction
// 1D
const int isotrackreductionHT_ = 4;
double isoTrackReductionHT_ [isotrackreductionHT_] = {500,800,1200,2500};
const int isotrackreductionMHT_ = 4;
double isoTrackReductionMHT_ [isotrackreductionMHT_] = {200,500,750,1900};
const int isotrackreductionBTags_ = 5;
double isoTrackReductionBTags_[isotrackreductionBTags_] = {0,1,2,3,10};
const int isotrackreductionNJets_ = 6;
double isoTrackReductionNJets_ [isotrackreductionNJets_] = {4,5,6,8,11,20};
const int isotrackreductionPT_ = 8;
double isoTrackReductionPT_ [isotrackreductionPT_] = {5,10,20,25,30,40,50,200};
const int isotrackreductionActivity_ = 6;
double isoTrackReductionActivity_ [isotrackreductionActivity_] = {0,20,40,60,150,1600};
// 2D
const int isotrackreductionBTags2D_ = 3;
double isoTrackReductionBTags2D_[isotrackreductionBTags2D_] = {0,1,10};
const int isotrackreductionNJets2D_ = 4;
double isoTrackReductionNJets2D_ [isotrackreductionNJets2D_] = {4,6,7,20};
const int isotrackreductionPT2D_ = 8;
double isoTrackReductionPT2D_[isotrackreductionPT2D_] = {5,10,20,25,30,40,50,200};
const int isotrackreductionActivity2D_ = 6;
double isoTrackReductionActivity2D_ [isotrackreductionActivity2D_] = {0,20,40,60,150,1600};



class EffMaker : public TSelector {
public :	
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	
	SearchBinEventCount *totalExpectation_;
	
	//efficiencies

	//purity

	//mu
	//1D
	TH1Eff *MuPurityBTag_;
	TH1Eff *MuPurityNJets_;
	TH1Eff *MuPurityHT_;
	TH1Eff *MuPurityMHT_;
	TH1Eff *MuPurityPT_;
	TH1Eff *MuPurityActivity_;
	//2D
	TH2Eff *MuonPurityMHTNJet_;
	
	//elec
	//1D
	TH1Eff *ElecPurityBTag_;
	TH1Eff *ElecPurityNJets_;
	TH1Eff *ElecPurityHT_;
	TH1Eff *ElecPurityMHT_;
	TH1Eff *ElecPurityPT_;
	TH1Eff *ElecPurityActivity_;
	//2D
	TH2Eff *ElecPurityMHTNJet_;
	
	// x-check of purity
	
	TH1Eff *MuPurityCheckBTag_;
	TH1Eff *MuPurityCheckNJets_;
	TH1Eff *MuPurityCheckHT_;
	TH1Eff *MuPurityCheckMHT_;
	TH1Eff *MuPurityCheckPT_;
	TH1Eff *MuPurityCheckActivity_;
	//2D
	TH2Eff *MuonPurityCheckMHTNJet_;
	
	//elec
	//1D
	TH1Eff *ElecPurityCheckBTag_;
	TH1Eff *ElecPurityCheckNJets_;
	TH1Eff *ElecPurityCheckHT_;
	TH1Eff *ElecPurityCheckMHT_;
	TH1Eff *ElecPurityCheckPT_;
	TH1Eff *ElecPurityCheckActivity_;
	//2D
	TH2Eff *ElecPurityCheckMHTNJet_;
	
	
	// Acceptance
	// mu 
	//1D
	TH1Eff *MuAccBTag_;
	TH1Eff *MuAccNJets_;
	TH1Eff *MuAccHT_;
	TH1Eff *MuAccMHT_;
	TH1Eff *MuAccPT_;
	TH1Eff *MuAccActivity_;
	// 2D
	TH2Eff *MuAccHTNJets_;
	TH2Eff *MuAccMHTNJets_;
	TH2Eff *MuAccHTMHT_;
	TH2Eff *MuAccBTagNJets_;
	TH2Eff *MuAccMHTNJetsB0_;
	TH2Eff *MuAccMHTNJetsB1_Inf_;
	TH2Eff *MuAccHTMHT_NJetsLow_;
	TH2Eff *MuAccHTMHT_NJetsHigh_;
	TH2Eff *MuAccHTMHTB0_;
	TH2Eff *MuAccHTMHTB1_Inf_;
	
	// elec
	//1D
	TH1Eff *ElecAccBTag_;
	TH1Eff *ElecAccNJets_;
	TH1Eff *ElecAccHT_;
	TH1Eff *ElecAccMHT_;
	TH1Eff *ElecAccPT_;
	TH1Eff *ElecAccActivity_;
	// 2D
	TH2Eff *ElecAccHTNJets_;
	TH2Eff *ElecAccMHTNJets_;
	TH2Eff *ElecAccHTMHT_;
	TH2Eff *ElecAccBTagNJets_;
	TH2Eff *ElecAccMHTNJetsB0_;
	TH2Eff *ElecAccMHTNJetsB1_Inf_;
	TH2Eff *ElecAccHTMHT_NJetsLow_;
	TH2Eff *ElecAccHTMHT_NJetsHigh_;
	TH2Eff *ElecAccHTMHTB0_;
	TH2Eff *ElecAccHTMHTB1_Inf_;
	

	// Reco 
	// mu 
	//1D
	TH1Eff *MuRecoBTag_;
	TH1Eff *MuRecoNJets_;
	TH1Eff *MuRecoHT_;
	TH1Eff *MuRecoMHT_;
	TH1Eff *MuRecoPT_;
	TH1Eff *MuRecoActivity_;
	TH1Eff *MuRecoRelPTJet_;
	TH1Eff *MuRecoDeltaRJet_;	
	//2D
	TH2Eff *MuRecoPTActivity_;
	TH2Eff *MuRecoRelPTDeltaRJet_;
	
	// elec
	//1D
	TH1Eff *ElecRecoBTag_;
	TH1Eff *ElecRecoNJets_;
	TH1Eff *ElecRecoHT_;
	TH1Eff *ElecRecoMHT_;
	TH1Eff *ElecRecoPT_;
	TH1Eff *ElecRecoActivity_;
	TH1Eff *ElecRecoRelPTJet_;
	TH1Eff *ElecRecoDeltaRJet_;
	//2D
	TH2Eff *ElecRecoPTActivity_;
	TH2Eff *ElecRecoRelPTDeltaRJet_;
	
	// Iso
	// mu 
	//1D
	TH1Eff *MuIsoBTag_;
	TH1Eff *MuIsoNJets_;
	TH1Eff *MuIsoHT_;
	TH1Eff *MuIsoMHT_;
	TH1Eff *MuIsoPT_;
	TH1Eff *MuIsoActivity_;
	TH1Eff *MuIsoRelPTJet_;
	TH1Eff *MuIsoDeltaRJet_;
	//2D
	TH2Eff *MuIsoPTActivity_;
	TH2Eff *MuIsoRelPTDeltaRJet_;
	
	// elec
	//1D
	TH1Eff *ElecIsoBTag_;
	TH1Eff *ElecIsoNJets_;
	TH1Eff *ElecIsoHT_;
	TH1Eff *ElecIsoMHT_;
	TH1Eff *ElecIsoPT_;
	TH1Eff *ElecIsoActivity_;
	TH1Eff *ElecIsoRelPTJet_;
	TH1Eff *ElecIsoDeltaRJet_;
	//2D
	TH2Eff *ElecIsoPTActivity_;
	TH2Eff *ElecIsoRelPTDeltaRJet_;	

	
	// MTW
	// mu 
	//1D
	TH1Eff *MuMTWBTag_;
	TH1Eff *MuMTWNJets_;
	TH1Eff *MuMTWHT_;
	TH1Eff *MuMTWMHT_;
	TH1Eff *MuMTWPT_;
	TH1Eff *MuMTWActivity_;
	// 2D
	TH2Eff *MuMTWPTActivity_;
	
	// elec
	//1D
	TH1Eff *ElecMTWBTag_;
	TH1Eff *ElecMTWNJets_;
	TH1Eff *ElecMTWHT_;
	TH1Eff *ElecMTWMHT_;
	TH1Eff *ElecMTWPT_;
	TH1Eff *ElecMTWActivity_;
	// 2D
	TH2Eff *ElecMTWPTActivity_;
	
	
	// Di lep control sample
	// mu 
	//1D
	TH1Eff *MuDiLepBTag_;
	TH1Eff *MuDiLepNJets_;
	TH1Eff *MuDiLepHT_;
	TH1Eff *MuDiLepMHT_;
	TH1Eff *MuDiLepPT_;
	TH1Eff *MuDiLepActivity_;
	
	
	// elec
	//1D
	TH1Eff *ElecDiLepBTag_;
	TH1Eff *ElecDiLepNJets_;
	TH1Eff *ElecDiLepHT_;
	TH1Eff *ElecDiLepMHT_;
	TH1Eff *ElecDiLepPT_;
	TH1Eff *ElecDiLepActivity_;
	
	// di lep mtw cut applied
	// mu 
	//1D
	TH1Eff *MuDiLepMTWBTag_;
	TH1Eff *MuDiLepMTWNJets_;
	TH1Eff *MuDiLepMTWHT_;
	TH1Eff *MuDiLepMTWMHT_;
	TH1Eff *MuDiLepMTWPT_;
	TH1Eff *MuDiLepMTWActivity_;
	
	// elec
	//1D
	TH1Eff *ElecDiLepMTWBTag_;
	TH1Eff *ElecDiLepMTWNJets_;
	TH1Eff *ElecDiLepMTWHT_;
	TH1Eff *ElecDiLepMTWMHT_;
	TH1Eff *ElecDiLepMTWPT_;
	TH1Eff *ElecDiLepMTWActivity_;	
	
	// mu 
	//1D
	TH1Eff *MuDiLepContributionBTag_;
	TH1Eff *MuDiLepContributionNJets_;
	TH1Eff *MuDiLepContributionHT_;
	TH1Eff *MuDiLepContributionMHT_;
	
	// elec
	//1D
	TH1Eff *ElecDiLepContributionBTag_;
	TH1Eff *ElecDiLepContributionNJets_;
	TH1Eff *ElecDiLepContributionHT_;
	TH1Eff *ElecDiLepContributionMHT_;
	
	// di lep mtw cut applied
	// mu 
	//1D
	TH1Eff *MuDiLepContributionMTWBTag_;
	TH1Eff *MuDiLepContributionMTWNJets_;
	TH1Eff *MuDiLepContributionMTWHT_;
	TH1Eff *MuDiLepContributionMTWMHT_;
	
	// elec
	//1D
	TH1Eff *ElecDiLepContributionMTWBTag_;
	TH1Eff *ElecDiLepContributionMTWNJets_;
	TH1Eff *ElecDiLepContributionMTWHT_;
	TH1Eff *ElecDiLepContributionMTWMHT_;
	

	// single isolated track from mu or electron
	// muon
	TH1Eff *IsoTrackMuBTag_;
	TH1Eff *IsoTrackMuNJets_;
	TH1Eff *IsoTrackMuHT_;
	TH1Eff *IsoTrackMuMHT_;
	TH2Eff *IsoTrackMuPTActivity_;
	
	// elec
	TH1Eff *IsoTrackElecBTag_;
	TH1Eff *IsoTrackElecNJets_;
	TH1Eff *IsoTrackElecHT_;
	TH1Eff *IsoTrackElecMHT_;
	TH2Eff *IsoTrackElecPTActivity_;
	
	TH1Eff *ExpectationReductionIsoTrackBTagEff_;
	TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
	TH1Eff *ExpectationReductionIsoTrackHTEff_;
	TH1Eff *ExpectationReductionIsoTrackMHTEff_;
	TH1Eff *ExpectationReductionIsoTrackPTEff_;
	TH1Eff *ExpectationReductionIsoTrackActivityEff_;
	//2D
	// 2D
	TH2Eff *IsoTrackReductionHTNJets_; 
	TH2Eff *IsoTrackReductionMHTNJets_;
	TH2Eff *IsoTrackReductionBTagNJets_;
	TH2Eff *IsoTrackReductionPTActivity_;
	
	
	// mu iso tracks
	TH1Eff *ExpectationReductionMuIsoTrackBTagEff_;
	TH1Eff *ExpectationReductionMuIsoTrackNJetsEff_;
	TH1Eff *ExpectationReductionMuIsoTrackHTEff_;
	TH1Eff *ExpectationReductionMuIsoTrackMHTEff_;
	TH1Eff *ExpectationReductionMuIsoTrackPTEff_;
	TH1Eff *ExpectationReductionMuIsoTrackActivityEff_;
	//2D
	TH2Eff *MuIsoTrackReductionHTNJets_; 
	TH2Eff *MuIsoTrackReductionMHTNJets_;
	TH2Eff *MuIsoTrackReductionBTagNJets_;
	TH2Eff *MuIsoTrackReductionPTActivity_;
	
	//elec iso tracks
	TH1Eff *ExpectationReductionElecIsoTrackBTagEff_;
	TH1Eff *ExpectationReductionElecIsoTrackNJetsEff_;
	TH1Eff *ExpectationReductionElecIsoTrackHTEff_;
	TH1Eff *ExpectationReductionElecIsoTrackMHTEff_;
	TH1Eff *ExpectationReductionElecIsoTrackPTEff_;
	TH1Eff *ExpectationReductionElecIsoTrackActivityEff_;
	//2D
	TH2Eff *ElecIsoTrackReductionHTNJets_; 
	TH2Eff *ElecIsoTrackReductionMHTNJets_;
	TH2Eff *ElecIsoTrackReductionBTagNJets_;
	TH2Eff *ElecIsoTrackReductionPTActivity_;
	
	//pion iso tracks
	TH1Eff *ExpectationReductionPionIsoTrackBTagEff_;
	TH1Eff *ExpectationReductionPionIsoTrackNJetsEff_;
	TH1Eff *ExpectationReductionPionIsoTrackHTEff_;
	TH1Eff *ExpectationReductionPionIsoTrackMHTEff_;
	TH1Eff *ExpectationReductionPionIsoTrackPTEff_;
	TH1Eff *ExpectationReductionPionIsoTrackActivityEff_;
	//2D
	TH2Eff *PionIsoTrackReductionHTNJets_; 
	TH2Eff *PionIsoTrackReductionMHTNJets_;
	TH2Eff *PionIsoTrackReductionBTagNJets_;
	TH2Eff *PionIsoTrackReductionPTActivity_;
	
	
   // Declaration of leaf types
	// Declaration of leaf types
	UInt_t          EvtNum;
	Float_t         HT;
	Float_t         MHT;
	UShort_t        NJets;
	UShort_t        BTags;
	UShort_t        Leptons;
	UShort_t        isoTracks;
	UChar_t         DY;
	UShort_t        Bin;
	UShort_t        NVtx;
	Float_t         DeltaPhi1;
	Float_t         DeltaPhi2;
	Float_t         DeltaPhi3;
	Float_t         minDeltaPhiN;
	Float_t         DeltaPhiN1;
	Float_t         DeltaPhiN2;
	Float_t         DeltaPhiN3;
	Float_t         Weight;
	Float_t         MET;
	Float_t         METPhi;
	UShort_t        GenMuNum;
	UShort_t        GenMuFromTau[2];   //[GenMuNum]
	Float_t         GenMuDeltaRJet[2];   //[GenMuNum]
	Float_t         GenMuRelPTJet[2];   //[GenMuNum]
	Float_t         GenMuPt[2];   //[GenMuNum]
	Float_t         GenMuEta[2];   //[GenMuNum]
	Float_t         GenMuPhi[2];   //[GenMuNum]
	UShort_t        GenMuonIsoTrackMatched[2];   //[GenMuNum]
	Float_t         GenMuonActivity[2];   //[GenMuNum]
	UShort_t        GenElecNum;
	UShort_t        GenElecFromTau[2];   //[GenElecNum]
	Float_t         GenElecDeltaRJet[2];   //[GenElecNum]
	Float_t         GenElecRelPTJet[2];   //[GenElecNum]
	Float_t         GenElecPt[2];   //[GenElecNum]
	Float_t         GenElecEta[2];   //[GenElecNum]
	Float_t         GenElecPhi[2];   //[GenElecNum]
	UShort_t        GenElecIsoTrackMatched[2];   //[GenElecNum]
	Float_t         GenElecActivity[2];   //[GenElecNum]
	UShort_t        GenTauNum;
	Float_t         GenTauPt[2];   //[GenTauNum]
	Float_t         GenTauEta[2];   //[GenTauNum]
	Float_t         GenTauPhi[2];   //[GenTauNum]
	UShort_t        GenTauIsoTrackMatched[2];   //[GenTauNum]
	Float_t         GenTauActivity[2];   //[GenTauNum]
	UShort_t        Expectation;
	UShort_t        ExpectationReductionIsoTrack;
	UShort_t        muAcc;
	UShort_t        muReco;
	UShort_t        muIso;
	Float_t         MTW;
	Float_t         IsoTrackMTW;
	UShort_t        elecAcc;
	UShort_t        elecReco;
	UShort_t        elecIso;
	UShort_t        muIsoTrack;
	UShort_t        MuPurity;
	UShort_t        ElecPurity;
	UShort_t        muActivityMethod;
	UShort_t        elecActivityMethod;
	UShort_t        muIsoTrackActivityMethod;
	UShort_t        elecIsoTrackActivityMethod;
	UShort_t        pionIsoTrackActivityMethod;
	UShort_t        FallsVetoLep;
	UShort_t        selectedIDIsoMuonsNum;
	Float_t         selectedIDIsoMuonsPt[3];   //[selectedIDIsoMuonsNum]
	UShort_t        muIsoMatched[3];   //[selectedIDIsoMuonsNum]
	UShort_t        RecoIsoMuonPromtMatched[3];   //[selectedIDIsoMuonsNum]
	Float_t         RecoIsoMuonPromtMatchedDeltaR[3];   //[selectedIDIsoMuonsNum]
	Float_t         RecoIsoMuonPromtMatchedRelPt[3];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsEta[3];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsPhi[3];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuonsE[3];   //[selectedIDIsoMuonsNum]
	Float_t         selectedIDIsoMuons_MTW[3];   //[selectedIDIsoMuonsNum]
	Float_t         RecoIsoMuonActivity[3];   //[selectedIDIsoMuonsNum]
	UShort_t        selectedIDMuonsNum;
	Float_t         selectedIDMuonsPt[5];   //[selectedIDMuonsNum]
	UShort_t        selectedIDMuonsMatched[5];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsEta[5];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsPhi[5];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuonsE[5];   //[selectedIDMuonsNum]
	Float_t         selectedIDMuons_MTW[3];   //[selectedIDIsoMuonsNum]
	Float_t         RecoMuonActivity[5];   //[selectedIDMuonsNum]
	UShort_t        RecoIsoMuonIsoTrackMatched[3];   //[selectedIDIsoMuonsNum]
	UShort_t        selectedIDIsoElectronsNum;
	Float_t         selectedIDIsoElectronsPt[3];   //[selectedIDIsoElectronsNum]
	UShort_t        elecIsoMatched[3];   //[selectedIDIsoElectronsNum]
	UShort_t        RecoIsoElecPromtMatched[3];   //[selectedIDIsoElectronsNum]
	Float_t         RecoIsoElecPromtMatchedDeltaR[3];   //[selectedIDIsoElectronsNum]
	Float_t         RecoIsoElecPromtMatchedRelPt[3];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsEta[3];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsPhi[3];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectronsE[3];   //[selectedIDIsoElectronsNum]
	Float_t         selectedIDIsoElectrons_MTW[3];   //[selectedIDIsoElectronsNum]
	Float_t         RecoIsoElectronActivity[3];   //[selectedIDIsoElectronsNum]
	UShort_t        RecoIsoElecIsoTrackMatched[3];   //[selectedIDIsoElectronsNum]
	UShort_t        selectedIDElectronsNum;
	Float_t         selectedIDElectronsPt[4];   //[selectedIDElectronsNum]
	UShort_t        selectedIDElectronsMatched[4];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsEta[4];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsPhi[4];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectronsE[4];   //[selectedIDElectronsNum]
	Float_t         selectedIDElectrons_MTW[3];   //[selectedIDIsoElectronsNum]
	Float_t         RecoElectronActivity[4];   //[selectedIDElectronsNum]
	UShort_t        IsolatedElectronTracksVetoNum;
	Float_t         IsolatedElectronTracksVetoPt[3];   //[IsolatedElectronTracksVetoNum]
	Float_t         IsolatedElectronTracksVetoEta[3];   //[IsolatedElectronTracksVetoNum]
	Float_t         IsolatedElectronTracksVetoPhi[3];   //[IsolatedElectronTracksVetoNum]
	Float_t         IsolatedElectronTracksVetoE[3];   //[IsolatedElectronTracksVetoNum]
	Float_t         IsolatedElectronTracksVetoActivity[3];   //[IsolatedElectronTracksVetoNum]
	Float_t         IsolatedElectronTracksVetoMTW[3];   //[IsolatedElectronTracksVetoNum]
	UShort_t        muIsoTrackMatchedToGenElec[3];   //[IsolatedElectronTracksVetoNum]
	UShort_t        elecIsoTrackMatchedToGenElec[3];   //[IsolatedElectronTracksVetoNum]
	UShort_t        pionIsoTrackMatchedToGenElec[3];   //[IsolatedElectronTracksVetoNum]
	UShort_t        IsolatedMuonTracksVetoNum;
	Float_t         IsolatedMuonTracksVetoPt[3];   //[IsolatedMuonTracksVetoNum]
	Float_t         IsolatedMuonTracksVetoEta[3];   //[IsolatedMuonTracksVetoNum]
	Float_t         IsolatedMuonTracksVetoPhi[3];   //[IsolatedMuonTracksVetoNum]
	Float_t         IsolatedMuonTracksVetoE[3];   //[IsolatedMuonTracksVetoNum]
	Float_t         IsolatedMuonTracksVetoActivity[3];   //[IsolatedMuonTracksVetoNum]
	Float_t         IsolatedMuonTracksVetoMTW[3];   //[IsolatedMuonTracksVetoNum]
	UShort_t        muIsoTrackMatchedToGenMu[3];   //[IsolatedMuonTracksVetoNum]
	UShort_t        elecIsoTrackMatchedToGenMu[3];   //[IsolatedMuonTracksVetoNum]
	UShort_t        pionIsoTrackMatchedToGenMu[3];   //[IsolatedMuonTracksVetoNum]
	UShort_t        IsolatedPionTracksVetoNum;
	Float_t         IsolatedPionTracksVetoPt[4];   //[IsolatedPionTracksVetoNum]
	Float_t         IsolatedPionTracksVetoEta[4];   //[IsolatedPionTracksVetoNum]
	Float_t         IsolatedPionTracksVetoPhi[4];   //[IsolatedPionTracksVetoNum]
	Float_t         IsolatedPionTracksVetoE[4];   //[IsolatedPionTracksVetoNum]
	Float_t         IsolatedPionTracksVetoActivity[4];   //[IsolatedPionTracksVetoNum]
	Float_t         IsolatedPionTracksVetoMTW[4];   //[IsolatedPionTracksVetoNum]
	UShort_t        muIsoTrackMatchedToGenSingleProngTau[4];   //[IsolatedPionTracksVetoNum]
	UShort_t        elecIsoTrackMatchedToGenSingleProngTau[4];   //[IsolatedPionTracksVetoNum]
	UShort_t        pionIsoTrackMatchedToGenSingleProngTau[4];   //[IsolatedPionTracksVetoNum]
	UShort_t        JetsNum;
	Float_t         JetsPt[15];   //[JetsNum]
	Float_t         JetsEta[15];   //[JetsNum]
	Float_t         JetsPhi[15];   //[JetsNum]
	Float_t         JetsE[15];   //[JetsNum]
	Float_t         Jets_bDiscriminator[15];   //[JetsNum]
	Float_t         Jets_chargedEmEnergyFraction[15];   //[JetsNum]
	Float_t         Jets_chargedHadronEnergyFraction[15];   //[JetsNum]
	Int_t           Jets_chargedHadronMultiplicity[15];   //[JetsNum]
	Int_t           Jets_electronMultiplicity[15];   //[JetsNum]
	Float_t         Jets_jetArea[15];   //[JetsNum]
	Float_t         Jets_muonEnergyFraction[15];   //[JetsNum]
	Int_t           Jets_muonMultiplicity[15];   //[JetsNum]
	Float_t         Jets_neutralEmEnergyFraction[15];   //[JetsNum]
	Int_t           Jets_neutralHadronMultiplicity[15];   //[JetsNum]
	Float_t         Jets_photonEnergyFraction[15];   //[JetsNum]
	Int_t           Jets_photonMultiplicity[15];   //[JetsNum]
	UShort_t        ExpectationDiLep;
	UShort_t        MuDiLepControlSample;
	UShort_t        ElecDiLepControlSample;
	UShort_t        StandAloneGenMuIsoTrackMatched;
	UShort_t        StandAloneIsoTrackToMuMatched;
	UShort_t        StandAloneGenElecIsoTrackMatched;
	UShort_t        StandAloneIsoTrackToElecMatched;
	UShort_t        StandAloneIsoTrackToRecoMuMatched;
	UShort_t        StandAloneIsoTrackToRecoElecMatched;
	UShort_t        IsoTrackDiLepControlSampleMu;
	UShort_t        IsoTrackDiLepControlSampleElec;
	UShort_t        IsoTrackDiLepMu;
	UShort_t        IsoTrackDiLepElec;
	Float_t         GenMuWPt;
	Float_t         GenMuWPhi;
	Float_t         GenElecWPt;
	Float_t         GenElecWPhi;
	UShort_t        GenBosonNum;
	Float_t         GenBosonPt[2];   //[GenBosonNum]
	Float_t         GenBosonPhi[2];   //[GenBosonNum]
	
	// List of branches
	TBranch        *b_EvtNum;   //!
	TBranch        *b_HT;   //!
	TBranch        *b_MHT;   //!
	TBranch        *b_NJets;   //!
	TBranch        *b_BTags;   //!
	TBranch        *b_Leptons;   //!
	TBranch        *b_isoTracks;   //!
	TBranch        *b_DY;   //!
	TBranch        *b_Bin;   //!
	TBranch        *b_NVtx;   //!
	TBranch        *b_DeltaPhi1;   //!
	TBranch        *b_DeltaPhi2;   //!
	TBranch        *b_DeltaPhi3;   //!
	TBranch        *b_minDeltaPhiN;   //!
	TBranch        *b_DeltaPhiN1;   //!
	TBranch        *b_DeltaPhiN2;   //!
	TBranch        *b_DeltaPhiN3;   //!
	TBranch        *b_Weight;   //!
	TBranch        *b_MET;   //!
	TBranch        *b_METPhi;   //!
	TBranch        *b_GenMuNum;   //!
	TBranch        *b_GenMuFromTau;   //!
	TBranch        *b_GenMuDeltaRJet;   //!
	TBranch        *b_GenMuRelPTJet;   //!
	TBranch        *b_GenMuPt;   //!
	TBranch        *b_GenMuEta;   //!
	TBranch        *b_GenMuPhi;   //!
	TBranch        *b_GenMuonIsoTrackMatched;   //!
	TBranch        *b_GenMuonActivity;   //!
	TBranch        *b_GenElecNum;   //!
	TBranch        *b_GenElecFromTau;   //!
	TBranch        *b_GenElecDeltaRJet;   //!
	TBranch        *b_GenElecRelPTJet;   //!
	TBranch        *b_GenElecPt;   //!
	TBranch        *b_GenElecEta;   //!
	TBranch        *b_GenElecPhi;   //!
	TBranch        *b_GenElecIsoTrackMatched;   //!
	TBranch        *b_GenElecActivity;   //!
	TBranch        *b_GenTauNum;   //!
	TBranch        *b_GenTauPt;   //!
	TBranch        *b_GenTauEta;   //!
	TBranch        *b_GenTauPhi;   //!
	TBranch        *b_GenTauIsoTrackMatched;   //!
	TBranch        *b_GenTauActivity;   //!
	TBranch        *b_Expectation;   //!
	TBranch        *b_ExpectationReductionIsoTrack;   //!
	TBranch        *b_muAcc;   //!
	TBranch        *b_muReco;   //!
	TBranch        *b_muIso;   //!
	TBranch        *b_MTW;   //!
	TBranch        *b_IsoTrackMTW;   //!
	TBranch        *b_elecAcc;   //!
	TBranch        *b_elecReco;   //!
	TBranch        *b_elecIso;   //!
	TBranch        *b_muIsoTrack;   //!
	TBranch        *b_MuPurity;   //!
	TBranch        *b_ElecPurity;   //!
	TBranch        *b_muActivityMethod;   //!
	TBranch        *b_elecActivityMethod;   //!
	TBranch        *b_muIsoTrackActivityMethod;   //!
	TBranch        *b_elecIsoTrackActivityMethod;   //!
	TBranch        *b_pionIsoTrackActivityMethod;   //!
	TBranch        *b_FallsVetoLep;   //!
	TBranch        *b_selectedIDIsoMuonsNum;   //!
	TBranch        *b_selectedIDIsoMuonsPt;   //!
	TBranch        *b_muIsoMatched;   //!
	TBranch        *b_RecoIsoMuonPromtMatched;   //!
	TBranch        *b_RecoIsoMuonPromtMatchedDeltaR;   //!
	TBranch        *b_RecoIsoMuonPromtMatchedRelPt;   //!
	TBranch        *b_selectedIDIsoMuonsEta;   //!
	TBranch        *b_selectedIDIsoMuonsPhi;   //!
	TBranch        *b_selectedIDIsoMuonsE;   //!
	TBranch        *b_selectedIDIsoMuons_MTW;   //!
	TBranch        *b_RecoIsoMuonActivity;   //!
	TBranch        *b_selectedIDMuonsNum;   //!
	TBranch        *b_selectedIDMuonsPt;   //!
	TBranch        *b_selectedIDMuonsMatched;   //!
	TBranch        *b_selectedIDMuonsEta;   //!
	TBranch        *b_selectedIDMuonsPhi;   //!
	TBranch        *b_selectedIDMuonsE;   //!
	TBranch        *b_selectedIDMuons_MTW;   //!
	TBranch        *b_RecoMuonActivity;   //!
	TBranch        *b_RecoIsoMuonIsoTrackMatched;   //!
	TBranch        *b_selectedIDIsoElectronsNum;   //!
	TBranch        *b_selectedIDIsoElectronsPt;   //!
	TBranch        *b_elecIsoMatched;   //!
	TBranch        *b_RecoIsoElecPromtMatched;   //!
	TBranch        *b_RecoIsoElecPromtMatchedDeltaR;   //!
	TBranch        *b_RecoIsoElecPromtMatchedRelPt;   //!
	TBranch        *b_selectedIDIsoElectronsEta;   //!
	TBranch        *b_selectedIDIsoElectronsPhi;   //!
	TBranch        *b_selectedIDIsoElectronsE;   //!
	TBranch        *b_selectedIDIsoElectrons_MTW;   //!
	TBranch        *b_RecoIsoElectronActivity;   //!
	TBranch        *b_RecoIsoElecIsoTrackMatched;   //!
	TBranch        *b_selectedIDElectronsNum;   //!
	TBranch        *b_selectedIDElectronsPt;   //!
	TBranch        *b_selectedIDElectronsMatched;   //!
	TBranch        *b_selectedIDElectronsEta;   //!
	TBranch        *b_selectedIDElectronsPhi;   //!
	TBranch        *b_selectedIDElectronsE;   //!
	TBranch        *b_selectedIDElectrons_MTW;   //!
	TBranch        *b_RecoElectronActivity;   //!
	TBranch        *b_IsolatedElectronTracksVetoNum;   //!
	TBranch        *b_IsolatedElectronTracksVetoPt;   //!
	TBranch        *b_IsolatedElectronTracksVetoEta;   //!
	TBranch        *b_IsolatedElectronTracksVetoPhi;   //!
	TBranch        *b_IsolatedElectronTracksVetoE;   //!
	TBranch        *b_IsolatedElectronTracksVetoActivity;   //!
	TBranch        *b_IsolatedElectronTracksVetoMTW;   //!
	TBranch        *b_muIsoTrackMatchedToGenElec;   //!
	TBranch        *b_elecIsoTrackMatchedToGenElec;   //!
	TBranch        *b_pionIsoTrackMatchedToGenElec;   //!
	TBranch        *b_IsolatedMuonTracksVetoNum;   //!
	TBranch        *b_IsolatedMuonTracksVetoPt;   //!
	TBranch        *b_IsolatedMuonTracksVetoEta;   //!
	TBranch        *b_IsolatedMuonTracksVetoPhi;   //!
	TBranch        *b_IsolatedMuonTracksVetoE;   //!
	TBranch        *b_IsolatedMuonTracksVetoActivity;   //!
	TBranch        *b_IsolatedMuonTracksVetoMTW;   //!
	TBranch        *b_muIsoTrackMatchedToGenMu;   //!
	TBranch        *b_elecIsoTrackMatchedToGenMu;   //!
	TBranch        *b_pionIsoTrackMatchedToGenMu;   //!
	TBranch        *b_IsolatedPionTracksVetoNum;   //!
	TBranch        *b_IsolatedPionTracksVetoPt;   //!
	TBranch        *b_IsolatedPionTracksVetoEta;   //!
	TBranch        *b_IsolatedPionTracksVetoPhi;   //!
	TBranch        *b_IsolatedPionTracksVetoE;   //!
	TBranch        *b_IsolatedPionTracksVetoActivity;   //!
	TBranch        *b_IsolatedPionTracksVetoMTW;   //!
	TBranch        *b_muIsoTrackMatchedToGenSingleProngTau;   //!
	TBranch        *b_elecIsoTrackMatchedToGenSingleProngTau;   //!
	TBranch        *b_pionIsoTrackMatchedToGenSingleProngTau;   //!
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
	TBranch        *b_ExpectationDiLep;   //!
	TBranch        *b_MuDiLepControlSample;   //!
	TBranch        *b_ElecDiLepControlSample;   //!
	TBranch        *b_StandAloneGenMuIsoTrackMatched;   //!
	TBranch        *b_StandAloneIsoTrackToMuMatched;   //!
	TBranch        *b_StandAloneGenElecIsoTrackMatched;   //!
	TBranch        *b_StandAloneIsoTrackToElecMatched;   //!
	TBranch        *b_StandAloneIsoTrackToRecoMuMatched;   //!
	TBranch        *b_StandAloneIsoTrackToRecoElecMatched;   //!
	TBranch        *b_IsoTrackDiLepControlSampleMu;   //!
	TBranch        *b_IsoTrackDiLepControlSampleElec;   //!
	TBranch        *b_IsoTrackDiLepMu;   //!
	TBranch        *b_IsoTrackDiLepElec;   //!
	TBranch        *b_GenMuWPt;   //!
	TBranch        *b_GenMuWPhi;   //!
	TBranch        *b_GenElecWPt;   //!
	TBranch        *b_GenElecWPhi;   //!
	TBranch        *b_GenBosonNum;   //!
	TBranch        *b_GenBosonPt;   //!
	TBranch        *b_GenBosonPhi;   //!
	
	EffMaker(TTree * /*tree*/ =0) : fChain(0) { }
	virtual ~EffMaker() { }
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
	
	ClassDef(EffMaker,0);
};

#endif

#ifdef EffMaker_cxx
void EffMaker::Init(TTree *tree)
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
	
	fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
	fChain->SetBranchAddress("HT", &HT, &b_HT);
	fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
	fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
	fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
	fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
	fChain->SetBranchAddress("isoTracks", &isoTracks, &b_isoTracks);
	fChain->SetBranchAddress("DY", &DY, &b_DY);
	fChain->SetBranchAddress("Bin", &Bin, &b_Bin);
	fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
	fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
	fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
	fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
	fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
	fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
	fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
	fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
	fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
	fChain->SetBranchAddress("MET", &MET, &b_MET);
	fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
	fChain->SetBranchAddress("GenMuNum", &GenMuNum, &b_GenMuNum);
	fChain->SetBranchAddress("GenMuFromTau", GenMuFromTau, &b_GenMuFromTau);
	fChain->SetBranchAddress("GenMuDeltaRJet", GenMuDeltaRJet, &b_GenMuDeltaRJet);
	fChain->SetBranchAddress("GenMuRelPTJet", GenMuRelPTJet, &b_GenMuRelPTJet);
	fChain->SetBranchAddress("GenMuPt", GenMuPt, &b_GenMuPt);
	fChain->SetBranchAddress("GenMuEta", GenMuEta, &b_GenMuEta);
	fChain->SetBranchAddress("GenMuPhi", GenMuPhi, &b_GenMuPhi);
	fChain->SetBranchAddress("GenMuonIsoTrackMatched", GenMuonIsoTrackMatched, &b_GenMuonIsoTrackMatched);
	fChain->SetBranchAddress("GenMuonActivity", GenMuonActivity, &b_GenMuonActivity);
	fChain->SetBranchAddress("GenElecNum", &GenElecNum, &b_GenElecNum);
	fChain->SetBranchAddress("GenElecFromTau", GenElecFromTau, &b_GenElecFromTau);
	fChain->SetBranchAddress("GenElecDeltaRJet", GenElecDeltaRJet, &b_GenElecDeltaRJet);
	fChain->SetBranchAddress("GenElecRelPTJet", GenElecRelPTJet, &b_GenElecRelPTJet);
	fChain->SetBranchAddress("GenElecPt", GenElecPt, &b_GenElecPt);
	fChain->SetBranchAddress("GenElecEta", GenElecEta, &b_GenElecEta);
	fChain->SetBranchAddress("GenElecPhi", GenElecPhi, &b_GenElecPhi);
	fChain->SetBranchAddress("GenElecIsoTrackMatched", GenElecIsoTrackMatched, &b_GenElecIsoTrackMatched);
	fChain->SetBranchAddress("GenElecActivity", GenElecActivity, &b_GenElecActivity);
	fChain->SetBranchAddress("GenTauNum", &GenTauNum, &b_GenTauNum);
	fChain->SetBranchAddress("GenTauPt", GenTauPt, &b_GenTauPt);
	fChain->SetBranchAddress("GenTauEta", GenTauEta, &b_GenTauEta);
	fChain->SetBranchAddress("GenTauPhi", GenTauPhi, &b_GenTauPhi);
	fChain->SetBranchAddress("GenTauIsoTrackMatched", GenTauIsoTrackMatched, &b_GenTauIsoTrackMatched);
	fChain->SetBranchAddress("GenTauActivity", GenTauActivity, &b_GenTauActivity);
	fChain->SetBranchAddress("Expectation", &Expectation, &b_Expectation);
	fChain->SetBranchAddress("ExpectationReductionIsoTrack", &ExpectationReductionIsoTrack, &b_ExpectationReductionIsoTrack);
	fChain->SetBranchAddress("muAcc", &muAcc, &b_muAcc);
	fChain->SetBranchAddress("muReco", &muReco, &b_muReco);
	fChain->SetBranchAddress("muIso", &muIso, &b_muIso);
	fChain->SetBranchAddress("MTW", &MTW, &b_MTW);
	fChain->SetBranchAddress("IsoTrackMTW", &IsoTrackMTW, &b_IsoTrackMTW);
	fChain->SetBranchAddress("elecAcc", &elecAcc, &b_elecAcc);
	fChain->SetBranchAddress("elecReco", &elecReco, &b_elecReco);
	fChain->SetBranchAddress("elecIso", &elecIso, &b_elecIso);
	fChain->SetBranchAddress("muIsoTrack", &muIsoTrack, &b_muIsoTrack);
	fChain->SetBranchAddress("MuPurity", &MuPurity, &b_MuPurity);
	fChain->SetBranchAddress("ElecPurity", &ElecPurity, &b_ElecPurity);
	fChain->SetBranchAddress("muActivityMethod", &muActivityMethod, &b_muActivityMethod);
	fChain->SetBranchAddress("elecActivityMethod", &elecActivityMethod, &b_elecActivityMethod);
	fChain->SetBranchAddress("muIsoTrackActivityMethod", &muIsoTrackActivityMethod, &b_muIsoTrackActivityMethod);
	fChain->SetBranchAddress("elecIsoTrackActivityMethod", &elecIsoTrackActivityMethod, &b_elecIsoTrackActivityMethod);
	fChain->SetBranchAddress("pionIsoTrackActivityMethod", &pionIsoTrackActivityMethod, &b_pionIsoTrackActivityMethod);
	fChain->SetBranchAddress("FallsVetoLep", &FallsVetoLep, &b_FallsVetoLep);
	fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
	fChain->SetBranchAddress("selectedIDIsoMuonsPt", selectedIDIsoMuonsPt, &b_selectedIDIsoMuonsPt);
	fChain->SetBranchAddress("muIsoMatched", muIsoMatched, &b_muIsoMatched);
	fChain->SetBranchAddress("RecoIsoMuonPromtMatched", RecoIsoMuonPromtMatched, &b_RecoIsoMuonPromtMatched);
	fChain->SetBranchAddress("RecoIsoMuonPromtMatchedDeltaR", RecoIsoMuonPromtMatchedDeltaR, &b_RecoIsoMuonPromtMatchedDeltaR);
	fChain->SetBranchAddress("RecoIsoMuonPromtMatchedRelPt", RecoIsoMuonPromtMatchedRelPt, &b_RecoIsoMuonPromtMatchedRelPt);
	fChain->SetBranchAddress("selectedIDIsoMuonsEta", selectedIDIsoMuonsEta, &b_selectedIDIsoMuonsEta);
	fChain->SetBranchAddress("selectedIDIsoMuonsPhi", selectedIDIsoMuonsPhi, &b_selectedIDIsoMuonsPhi);
	fChain->SetBranchAddress("selectedIDIsoMuonsE", selectedIDIsoMuonsE, &b_selectedIDIsoMuonsE);
	fChain->SetBranchAddress("selectedIDIsoMuons_MTW", selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
	fChain->SetBranchAddress("RecoIsoMuonActivity", RecoIsoMuonActivity, &b_RecoIsoMuonActivity);
	fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
	fChain->SetBranchAddress("selectedIDMuonsPt", selectedIDMuonsPt, &b_selectedIDMuonsPt);
	fChain->SetBranchAddress("selectedIDMuonsMatched", selectedIDMuonsMatched, &b_selectedIDMuonsMatched);
	fChain->SetBranchAddress("selectedIDMuonsEta", selectedIDMuonsEta, &b_selectedIDMuonsEta);
	fChain->SetBranchAddress("selectedIDMuonsPhi", selectedIDMuonsPhi, &b_selectedIDMuonsPhi);
	fChain->SetBranchAddress("selectedIDMuonsE", selectedIDMuonsE, &b_selectedIDMuonsE);
	fChain->SetBranchAddress("selectedIDMuons_MTW", selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
	fChain->SetBranchAddress("RecoMuonActivity", RecoMuonActivity, &b_RecoMuonActivity);
	fChain->SetBranchAddress("RecoIsoMuonIsoTrackMatched", RecoIsoMuonIsoTrackMatched, &b_RecoIsoMuonIsoTrackMatched);
	fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
	fChain->SetBranchAddress("selectedIDIsoElectronsPt", selectedIDIsoElectronsPt, &b_selectedIDIsoElectronsPt);
	fChain->SetBranchAddress("elecIsoMatched", elecIsoMatched, &b_elecIsoMatched);
	fChain->SetBranchAddress("RecoIsoElecPromtMatched", RecoIsoElecPromtMatched, &b_RecoIsoElecPromtMatched);
	fChain->SetBranchAddress("RecoIsoElecPromtMatchedDeltaR", RecoIsoElecPromtMatchedDeltaR, &b_RecoIsoElecPromtMatchedDeltaR);
	fChain->SetBranchAddress("RecoIsoElecPromtMatchedRelPt", RecoIsoElecPromtMatchedRelPt, &b_RecoIsoElecPromtMatchedRelPt);
	fChain->SetBranchAddress("selectedIDIsoElectronsEta", selectedIDIsoElectronsEta, &b_selectedIDIsoElectronsEta);
	fChain->SetBranchAddress("selectedIDIsoElectronsPhi", selectedIDIsoElectronsPhi, &b_selectedIDIsoElectronsPhi);
	fChain->SetBranchAddress("selectedIDIsoElectronsE", selectedIDIsoElectronsE, &b_selectedIDIsoElectronsE);
	fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
	fChain->SetBranchAddress("RecoIsoElectronActivity", RecoIsoElectronActivity, &b_RecoIsoElectronActivity);
	fChain->SetBranchAddress("RecoIsoElecIsoTrackMatched", RecoIsoElecIsoTrackMatched, &b_RecoIsoElecIsoTrackMatched);
	fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
	fChain->SetBranchAddress("selectedIDElectronsPt", selectedIDElectronsPt, &b_selectedIDElectronsPt);
	fChain->SetBranchAddress("selectedIDElectronsMatched", selectedIDElectronsMatched, &b_selectedIDElectronsMatched);
	fChain->SetBranchAddress("selectedIDElectronsEta", selectedIDElectronsEta, &b_selectedIDElectronsEta);
	fChain->SetBranchAddress("selectedIDElectronsPhi", selectedIDElectronsPhi, &b_selectedIDElectronsPhi);
	fChain->SetBranchAddress("selectedIDElectronsE", selectedIDElectronsE, &b_selectedIDElectronsE);
	fChain->SetBranchAddress("selectedIDElectrons_MTW", selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
	fChain->SetBranchAddress("RecoElectronActivity", RecoElectronActivity, &b_RecoElectronActivity);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoNum", &IsolatedElectronTracksVetoNum, &b_IsolatedElectronTracksVetoNum);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoPt", IsolatedElectronTracksVetoPt, &b_IsolatedElectronTracksVetoPt);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoEta", IsolatedElectronTracksVetoEta, &b_IsolatedElectronTracksVetoEta);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoPhi", IsolatedElectronTracksVetoPhi, &b_IsolatedElectronTracksVetoPhi);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoE", IsolatedElectronTracksVetoE, &b_IsolatedElectronTracksVetoE);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoActivity", IsolatedElectronTracksVetoActivity, &b_IsolatedElectronTracksVetoActivity);
	fChain->SetBranchAddress("IsolatedElectronTracksVetoMTW", IsolatedElectronTracksVetoMTW, &b_IsolatedElectronTracksVetoMTW);
	fChain->SetBranchAddress("muIsoTrackMatchedToGenElec", muIsoTrackMatchedToGenElec, &b_muIsoTrackMatchedToGenElec);
	fChain->SetBranchAddress("elecIsoTrackMatchedToGenElec", elecIsoTrackMatchedToGenElec, &b_elecIsoTrackMatchedToGenElec);
	fChain->SetBranchAddress("pionIsoTrackMatchedToGenElec", pionIsoTrackMatchedToGenElec, &b_pionIsoTrackMatchedToGenElec);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoNum", &IsolatedMuonTracksVetoNum, &b_IsolatedMuonTracksVetoNum);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoPt", IsolatedMuonTracksVetoPt, &b_IsolatedMuonTracksVetoPt);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoEta", IsolatedMuonTracksVetoEta, &b_IsolatedMuonTracksVetoEta);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoPhi", IsolatedMuonTracksVetoPhi, &b_IsolatedMuonTracksVetoPhi);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoE", IsolatedMuonTracksVetoE, &b_IsolatedMuonTracksVetoE);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoActivity", IsolatedMuonTracksVetoActivity, &b_IsolatedMuonTracksVetoActivity);
	fChain->SetBranchAddress("IsolatedMuonTracksVetoMTW", IsolatedMuonTracksVetoMTW, &b_IsolatedMuonTracksVetoMTW);
	fChain->SetBranchAddress("muIsoTrackMatchedToGenMu", muIsoTrackMatchedToGenMu, &b_muIsoTrackMatchedToGenMu);
	fChain->SetBranchAddress("elecIsoTrackMatchedToGenMu", elecIsoTrackMatchedToGenMu, &b_elecIsoTrackMatchedToGenMu);
	fChain->SetBranchAddress("pionIsoTrackMatchedToGenMu", pionIsoTrackMatchedToGenMu, &b_pionIsoTrackMatchedToGenMu);
	fChain->SetBranchAddress("IsolatedPionTracksVetoNum", &IsolatedPionTracksVetoNum, &b_IsolatedPionTracksVetoNum);
	fChain->SetBranchAddress("IsolatedPionTracksVetoPt", IsolatedPionTracksVetoPt, &b_IsolatedPionTracksVetoPt);
	fChain->SetBranchAddress("IsolatedPionTracksVetoEta", IsolatedPionTracksVetoEta, &b_IsolatedPionTracksVetoEta);
	fChain->SetBranchAddress("IsolatedPionTracksVetoPhi", IsolatedPionTracksVetoPhi, &b_IsolatedPionTracksVetoPhi);
	fChain->SetBranchAddress("IsolatedPionTracksVetoE", IsolatedPionTracksVetoE, &b_IsolatedPionTracksVetoE);
	fChain->SetBranchAddress("IsolatedPionTracksVetoActivity", IsolatedPionTracksVetoActivity, &b_IsolatedPionTracksVetoActivity);
	fChain->SetBranchAddress("IsolatedPionTracksVetoMTW", IsolatedPionTracksVetoMTW, &b_IsolatedPionTracksVetoMTW);
	fChain->SetBranchAddress("muIsoTrackMatchedToGenSingleProngTau", muIsoTrackMatchedToGenSingleProngTau, &b_muIsoTrackMatchedToGenSingleProngTau);
	fChain->SetBranchAddress("elecIsoTrackMatchedToGenSingleProngTau", elecIsoTrackMatchedToGenSingleProngTau, &b_elecIsoTrackMatchedToGenSingleProngTau);
	fChain->SetBranchAddress("pionIsoTrackMatchedToGenSingleProngTau", pionIsoTrackMatchedToGenSingleProngTau, &b_pionIsoTrackMatchedToGenSingleProngTau);
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
	fChain->SetBranchAddress("ExpectationDiLep", &ExpectationDiLep, &b_ExpectationDiLep);
	fChain->SetBranchAddress("MuDiLepControlSample", &MuDiLepControlSample, &b_MuDiLepControlSample);
	fChain->SetBranchAddress("ElecDiLepControlSample", &ElecDiLepControlSample, &b_ElecDiLepControlSample);
	fChain->SetBranchAddress("StandAloneGenMuIsoTrackMatched", &StandAloneGenMuIsoTrackMatched, &b_StandAloneGenMuIsoTrackMatched);
	fChain->SetBranchAddress("StandAloneIsoTrackToMuMatched", &StandAloneIsoTrackToMuMatched, &b_StandAloneIsoTrackToMuMatched);
	fChain->SetBranchAddress("StandAloneGenElecIsoTrackMatched", &StandAloneGenElecIsoTrackMatched, &b_StandAloneGenElecIsoTrackMatched);
	fChain->SetBranchAddress("StandAloneIsoTrackToElecMatched", &StandAloneIsoTrackToElecMatched, &b_StandAloneIsoTrackToElecMatched);
	fChain->SetBranchAddress("StandAloneIsoTrackToRecoMuMatched", &StandAloneIsoTrackToRecoMuMatched, &b_StandAloneIsoTrackToRecoMuMatched);
	fChain->SetBranchAddress("StandAloneIsoTrackToRecoElecMatched", &StandAloneIsoTrackToRecoElecMatched, &b_StandAloneIsoTrackToRecoElecMatched);
	fChain->SetBranchAddress("IsoTrackDiLepControlSampleMu", &IsoTrackDiLepControlSampleMu, &b_IsoTrackDiLepControlSampleMu);
	fChain->SetBranchAddress("IsoTrackDiLepControlSampleElec", &IsoTrackDiLepControlSampleElec, &b_IsoTrackDiLepControlSampleElec);
	fChain->SetBranchAddress("IsoTrackDiLepMu", &IsoTrackDiLepMu, &b_IsoTrackDiLepMu);
	fChain->SetBranchAddress("IsoTrackDiLepElec", &IsoTrackDiLepElec, &b_IsoTrackDiLepElec);
	fChain->SetBranchAddress("GenMuWPt", &GenMuWPt, &b_GenMuWPt);
	fChain->SetBranchAddress("GenMuWPhi", &GenMuWPhi, &b_GenMuWPhi);
	fChain->SetBranchAddress("GenElecWPt", &GenElecWPt, &b_GenElecWPt);
	fChain->SetBranchAddress("GenElecWPhi", &GenElecWPhi, &b_GenElecWPhi);
	fChain->SetBranchAddress("GenBosonNum", &GenBosonNum, &b_GenBosonNum);
	fChain->SetBranchAddress("GenBosonPt", GenBosonPt, &b_GenBosonPt);
	fChain->SetBranchAddress("GenBosonPhi", GenBosonPhi, &b_GenBosonPhi);
}

Bool_t EffMaker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EffMaker_cxx
