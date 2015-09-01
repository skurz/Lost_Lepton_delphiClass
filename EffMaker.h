#ifndef EffMaker_h
#define EffMaker_h

//#include <LLTools.h>
#include <THEff.h>


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
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include <TLegend.h>


using std::vector;
using std::cout;
using std::cerr;
using std::endl;
const bool useFilterData = true;
const bool useTrigger = false;


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
  Double_t        HT;
  Double_t        MHT;
  Int_t           NJets;
  Int_t           BTags;
  Int_t           Leptons;
  Int_t           isoTracks;
  Bool_t          DY;
  UShort_t        Bin;
  UShort_t        BinQCD;
  Int_t           NVtx;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        minDeltaPhiN;
  Double_t        DeltaPhiN1;
  Double_t        DeltaPhiN2;
  Double_t        DeltaPhiN3;
  Double_t        Weight;
  Double_t        MET;
  Double_t        METPhi;
  UShort_t        GenMuNum;
  std::vector<TLorentzVector> *GenMus=0;
  std::vector<int>     *GenMuFromTau=0;
  std::vector<float>   *GenMuDeltaRJet=0;
  std::vector<float>   *GenMuRelPTJet=0;
  std::vector<unsigned short> *GenMuonIsoTrackMatched=0;
  std::vector<float>   *GenMuonActivity=0;
  UShort_t        GenElecNum;
  std::vector<TLorentzVector> *GenEls=0;
  std::vector<int>     *GenElecFromTau=0;
  std::vector<float>   *GenElecDeltaRJet=0;
  std::vector<float>   *GenElecRelPTJet=0;
  std::vector<unsigned short> *GenElecIsoTrackMatched=0;
  std::vector<float>   *GenElecActivity=0;
  UShort_t        GenTauNum;
  std::vector<TLorentzVector> *GenTaus=0;
  std::vector<int>     *GenTau_GenTauHad=0;
  std::vector<unsigned short> *GenTauIsoTrackMatched=0;
  std::vector<float>   *GenTauActivity=0;
  std::vector<TLorentzVector> *GenTauNu=0;
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
  std::vector<TLorentzVector> *selectedIDIsoMuons=0;
  std::vector<unsigned short> *muIsoMatched=0;
  std::vector<unsigned short> *RecoIsoMuonPromptMatched=0;
  std::vector<float>   *RecoIsoMuonPromptMatchedDeltaR=0;
  std::vector<float>   *RecoIsoMuonPromptMatchedRelPt=0;
  std::vector<double>  *selectedIDIsoMuons_MTW=0;
  std::vector<float>   *RecoIsoMuonActivity=0;
  UShort_t        selectedIDMuonsNum;
  std::vector<TLorentzVector> *selectedIDMuons=0;
  std::vector<unsigned short> *selectedIDMuonsMatched=0;
  std::vector<double>  *selectedIDMuons_MTW=0;
  std::vector<float>   *RecoMuonActivity=0;
  std::vector<unsigned short> *RecoIsoMuonIsoTrackMatched=0;
  UShort_t        selectedIDIsoElectronsNum;
  std::vector<TLorentzVector> *selectedIDIsoElectrons=0;
  std::vector<unsigned short> *elecIsoMatched=0;
  std::vector<unsigned short> *RecoIsoElecPromptMatched=0;
  std::vector<float>   *RecoIsoElecPromptMatchedDeltaR=0;
  std::vector<float>   *RecoIsoElecPromptMatchedRelPt=0;
  std::vector<double>  *selectedIDIsoElectrons_MTW=0;
  std::vector<float>   *RecoIsoElectronActivity=0;
  std::vector<unsigned short> *RecoIsoElecIsoTrackMatched=0;
  UShort_t        selectedIDElectronsNum;
  std::vector<TLorentzVector> *selectedIDElectrons=0;
  std::vector<unsigned short> *selectedIDElectronsMatched=0;
  std::vector<double>  *selectedIDElectrons_MTW=0;
  std::vector<float>   *RecoElectronActivity=0;
  Int_t           isoElectronTracks;
  std::vector<TLorentzVector> *IsolatedElectronTracksVeto=0;
  std::vector<float>   *IsolatedElectronTracksVetoActivity=0;
  std::vector<float>   *IsolatedElectronTracksVetoMTW=0;
  std::vector<unsigned short> *muIsoTrackMatchedToGenElec=0;
  std::vector<unsigned short> *elecIsoTrackMatchedToGenElec=0;
  std::vector<unsigned short> *pionIsoTrackMatchedToGenElec=0;
  Int_t           isoMuonTracks;
  std::vector<TLorentzVector> *IsolatedMuonTracksVeto=0;
  std::vector<float>   *IsolatedMuonTracksVetoActivity=0;
  std::vector<float>   *IsolatedMuonTracksVetoMTW=0;
  std::vector<unsigned short> *muIsoTrackMatchedToGenMu=0;
  std::vector<unsigned short> *elecIsoTrackMatchedToGenMu=0;
  std::vector<unsigned short> *pionIsoTrackMatchedToGenMu=0;
  Int_t           isoPionTracks;
  std::vector<TLorentzVector> *IsolatedPionTracksVeto=0;
  std::vector<float>   *IsolatedPionTracksVetoActivity=0;
  std::vector<float>   *IsolatedPionTracksVetoMTW=0;
  std::vector<unsigned short> *muIsoTrackMatchedToGenSingleProngTau=0;
  std::vector<unsigned short> *elecIsoTrackMatchedToGenSingleProngTau=0;
  std::vector<unsigned short> *pionIsoTrackMatchedToGenSingleProngTau=0;
  UInt_t          JetsNum;
  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>  *Jets_bDiscriminatorCSV=0;
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

  // List of branches
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_Leptons=0;   //!
  TBranch        *b_isoTracks=0;   //!
  TBranch        *b_DY=0;   //!
  TBranch        *b_Bin=0;   //!
  TBranch        *b_BinQCD=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_minDeltaPhiN=0;   //!
  TBranch        *b_DeltaPhiN1=0;   //!
  TBranch        *b_DeltaPhiN2=0;   //!
  TBranch        *b_DeltaPhiN3=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_GenMuNum=0;   //!
  TBranch        *b_GenMus=0;   //!
  TBranch        *b_GenMuFromTau=0;   //!
  TBranch        *b_GenMuDeltaRJet=0;   //!
  TBranch        *b_GenMuRelPTJet=0;   //!
  TBranch        *b_GenMuonIsoTrackMatched=0;   //!
  TBranch        *b_GenMuonActivity=0;   //!
  TBranch        *b_GenElecNum=0;   //!
  TBranch        *b_GenEls=0;   //!
  TBranch        *b_GenElecFromTau=0;   //!
  TBranch        *b_GenElecDeltaRJet=0;   //!
  TBranch        *b_GenElecRelPTJet=0;   //!
  TBranch        *b_GenElecIsoTrackMatched=0;   //!
  TBranch        *b_GenElecActivity=0;   //!
  TBranch        *b_GenTauNum=0;   //!
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_GenTau_GenTauHad=0;   //!
  TBranch        *b_GenTauIsoTrackMatched=0;   //!
  TBranch        *b_GenTauActivity=0;   //!
  TBranch        *b_GenTauNu=0;   //!
  TBranch        *b_Expectation=0;   //!
  TBranch        *b_ExpectationReductionIsoTrack=0;   //!
  TBranch        *b_muAcc=0;   //!
  TBranch        *b_muReco=0;   //!
  TBranch        *b_muIso=0;   //!
  TBranch        *b_MTW=0;   //!
  TBranch        *b_IsoTrackMTW=0;   //!
  TBranch        *b_elecAcc=0;   //!
  TBranch        *b_elecReco=0;   //!
  TBranch        *b_elecIso=0;   //!
  TBranch        *b_muIsoTrack=0;   //!
  TBranch        *b_MuPurity=0;   //!
  TBranch        *b_ElecPurity=0;   //!
  TBranch        *b_muActivityMethod=0;   //!
  TBranch        *b_elecActivityMethod=0;   //!
  TBranch        *b_muIsoTrackActivityMethod=0;   //!
  TBranch        *b_elecIsoTrackActivityMethod=0;   //!
  TBranch        *b_pionIsoTrackActivityMethod=0;   //!
  TBranch        *b_FallsVetoLep=0;   //!
  TBranch        *b_selectedIDIsoMuonsNum=0;   //!
  TBranch        *b_selectedIDIsoMuons=0;   //!
  TBranch        *b_muIsoMatched=0;   //!
  TBranch        *b_RecoIsoMuonPromptMatched=0;   //!
  TBranch        *b_RecoIsoMuonPromptMatchedDeltaR=0;   //!
  TBranch        *b_RecoIsoMuonPromptMatchedRelPt=0;   //!
  TBranch        *b_selectedIDIsoMuons_MTW=0;   //!
  TBranch        *b_RecoIsoMuonActivity=0;   //!
  TBranch        *b_selectedIDMuonsNum=0;   //!
  TBranch        *b_selectedIDMuons=0;   //!
  TBranch        *b_selectedIDMuonsMatched=0;   //!
  TBranch        *b_selectedIDMuons_MTW=0;   //!
  TBranch        *b_RecoMuonActivity=0;   //!
  TBranch        *b_RecoIsoMuonIsoTrackMatched=0;   //!
  TBranch        *b_selectedIDIsoElectronsNum=0;   //!
  TBranch        *b_selectedIDIsoElectrons=0;   //!
  TBranch        *b_elecIsoMatched=0;   //!
  TBranch        *b_RecoIsoElecPromptMatched=0;   //!
  TBranch        *b_RecoIsoElecPromptMatchedDeltaR=0;   //!
  TBranch        *b_RecoIsoElecPromptMatchedRelPt=0;   //!
  TBranch        *b_selectedIDIsoElectrons_MTW=0;   //!
  TBranch        *b_RecoIsoElectronActivity=0;   //!
  TBranch        *b_RecoIsoElecIsoTrackMatched=0;   //!
  TBranch        *b_selectedIDElectronsNum=0;   //!
  TBranch        *b_selectedIDElectrons=0;   //!
  TBranch        *b_selectedIDElectronsMatched=0;   //!
  TBranch        *b_selectedIDElectrons_MTW=0;   //!
  TBranch        *b_RecoElectronActivity=0;   //!
  TBranch        *b_isoElectronTracks=0;   //!
  TBranch        *b_IsolatedElectronTracksVeto=0;   //!
  TBranch        *b_IsolatedElectronTracksVetoActivity=0;   //!
  TBranch        *b_IsolatedElectronTracksVetoMTW=0;   //!
  TBranch        *b_muIsoTrackMatchedToGenElec=0;   //!
  TBranch        *b_elecIsoTrackMatchedToGenElec=0;   //!
  TBranch        *b_pionIsoTrackMatchedToGenElec=0;   //!
  TBranch        *b_isoMuonTracks=0;   //!
  TBranch        *b_IsolatedMuonTracksVeto=0;   //!
  TBranch        *b_IsolatedMuonTracksVetoActivity=0;   //!
  TBranch        *b_IsolatedMuonTracksVetoMTW=0;   //!
  TBranch        *b_muIsoTrackMatchedToGenMu=0;   //!
  TBranch        *b_elecIsoTrackMatchedToGenMu=0;   //!
  TBranch        *b_pionIsoTrackMatchedToGenMu=0;   //!
  TBranch        *b_isoPionTracks=0;   //!
  TBranch        *b_IsolatedPionTracksVeto=0;   //!
  TBranch        *b_IsolatedPionTracksVetoActivity=0;   //!
  TBranch        *b_IsolatedPionTracksVetoMTW=0;   //!
  TBranch        *b_muIsoTrackMatchedToGenSingleProngTau=0;   //!
  TBranch        *b_elecIsoTrackMatchedToGenSingleProngTau=0;   //!
  TBranch        *b_pionIsoTrackMatchedToGenSingleProngTau=0;   //!
  TBranch        *b_JetsNum=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
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
  TBranch        *b_ExpectationDiLep=0;   //!
  TBranch        *b_MuDiLepControlSample=0;   //!
  TBranch        *b_ElecDiLepControlSample=0;   //!
  TBranch        *b_StandAloneGenMuIsoTrackMatched=0;   //!
  TBranch        *b_StandAloneIsoTrackToMuMatched=0;   //!
  TBranch        *b_StandAloneGenElecIsoTrackMatched=0;   //!
  TBranch        *b_StandAloneIsoTrackToElecMatched=0;   //!
  TBranch        *b_StandAloneIsoTrackToRecoMuMatched=0;   //!
  TBranch        *b_StandAloneIsoTrackToRecoElecMatched=0;   //!
  TBranch        *b_IsoTrackDiLepControlSampleMu=0;   //!
  TBranch        *b_IsoTrackDiLepControlSampleElec=0;   //!
  TBranch        *b_IsoTrackDiLepMu=0;   //!
  TBranch        *b_IsoTrackDiLepElec=0;   //!
	

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
  fChain->SetBranchAddress("BinQCD", &BinQCD, &b_BinQCD);
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
  fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
  fChain->SetBranchAddress("GenMuFromTau", &GenMuFromTau, &b_GenMuFromTau);
  fChain->SetBranchAddress("GenMuDeltaRJet", &GenMuDeltaRJet, &b_GenMuDeltaRJet);
  fChain->SetBranchAddress("GenMuRelPTJet", &GenMuRelPTJet, &b_GenMuRelPTJet);
  fChain->SetBranchAddress("GenMuonIsoTrackMatched", &GenMuonIsoTrackMatched, &b_GenMuonIsoTrackMatched);
  fChain->SetBranchAddress("GenMuonActivity", &GenMuonActivity, &b_GenMuonActivity);
  fChain->SetBranchAddress("GenElecNum", &GenElecNum, &b_GenElecNum);
  fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
  fChain->SetBranchAddress("GenElecFromTau", &GenElecFromTau, &b_GenElecFromTau);
  fChain->SetBranchAddress("GenElecDeltaRJet", &GenElecDeltaRJet, &b_GenElecDeltaRJet);
  fChain->SetBranchAddress("GenElecRelPTJet", &GenElecRelPTJet, &b_GenElecRelPTJet);
  fChain->SetBranchAddress("GenElecIsoTrackMatched", &GenElecIsoTrackMatched, &b_GenElecIsoTrackMatched);
  fChain->SetBranchAddress("GenElecActivity", &GenElecActivity, &b_GenElecActivity);
  fChain->SetBranchAddress("GenTauNum", &GenTauNum, &b_GenTauNum);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad, &b_GenTau_GenTauHad);
  fChain->SetBranchAddress("GenTauIsoTrackMatched", &GenTauIsoTrackMatched, &b_GenTauIsoTrackMatched);
  fChain->SetBranchAddress("GenTauActivity", &GenTauActivity, &b_GenTauActivity);
  fChain->SetBranchAddress("GenTauNu", &GenTauNu, &b_GenTauNu);
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
  fChain->SetBranchAddress("selectedIDIsoMuons", &selectedIDIsoMuons, &b_selectedIDIsoMuons);
  fChain->SetBranchAddress("muIsoMatched", &muIsoMatched, &b_muIsoMatched);
  fChain->SetBranchAddress("RecoIsoMuonPromptMatched", &RecoIsoMuonPromptMatched, &b_RecoIsoMuonPromptMatched);
  fChain->SetBranchAddress("RecoIsoMuonPromptMatchedDeltaR", &RecoIsoMuonPromptMatchedDeltaR, &b_RecoIsoMuonPromptMatchedDeltaR);
  fChain->SetBranchAddress("RecoIsoMuonPromptMatchedRelPt", &RecoIsoMuonPromptMatchedRelPt, &b_RecoIsoMuonPromptMatchedRelPt);
  fChain->SetBranchAddress("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
  fChain->SetBranchAddress("RecoIsoMuonActivity", &RecoIsoMuonActivity, &b_RecoIsoMuonActivity);
  fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
  fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
  fChain->SetBranchAddress("selectedIDMuonsMatched", &selectedIDMuonsMatched, &b_selectedIDMuonsMatched);
  fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
  fChain->SetBranchAddress("RecoMuonActivity", &RecoMuonActivity, &b_RecoMuonActivity);
  fChain->SetBranchAddress("RecoIsoMuonIsoTrackMatched", &RecoIsoMuonIsoTrackMatched, &b_RecoIsoMuonIsoTrackMatched);
  fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
  fChain->SetBranchAddress("selectedIDIsoElectrons", &selectedIDIsoElectrons, &b_selectedIDIsoElectrons);
  fChain->SetBranchAddress("elecIsoMatched", &elecIsoMatched, &b_elecIsoMatched);
  fChain->SetBranchAddress("RecoIsoElecPromptMatched", &RecoIsoElecPromptMatched, &b_RecoIsoElecPromptMatched);
  fChain->SetBranchAddress("RecoIsoElecPromptMatchedDeltaR", &RecoIsoElecPromptMatchedDeltaR, &b_RecoIsoElecPromptMatchedDeltaR);
  fChain->SetBranchAddress("RecoIsoElecPromptMatchedRelPt", &RecoIsoElecPromptMatchedRelPt, &b_RecoIsoElecPromptMatchedRelPt);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
  fChain->SetBranchAddress("RecoIsoElectronActivity", &RecoIsoElectronActivity, &b_RecoIsoElectronActivity);
  fChain->SetBranchAddress("RecoIsoElecIsoTrackMatched", &RecoIsoElecIsoTrackMatched, &b_RecoIsoElecIsoTrackMatched);
  fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
  fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
  fChain->SetBranchAddress("selectedIDElectronsMatched", &selectedIDElectronsMatched, &b_selectedIDElectronsMatched);
  fChain->SetBranchAddress("selectedIDElectrons_MTW", &selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
  fChain->SetBranchAddress("RecoElectronActivity", &RecoElectronActivity, &b_RecoElectronActivity);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
  fChain->SetBranchAddress("IsolatedElectronTracksVeto", &IsolatedElectronTracksVeto, &b_IsolatedElectronTracksVeto);
  fChain->SetBranchAddress("IsolatedElectronTracksVetoActivity", &IsolatedElectronTracksVetoActivity, &b_IsolatedElectronTracksVetoActivity);
  fChain->SetBranchAddress("IsolatedElectronTracksVetoMTW", &IsolatedElectronTracksVetoMTW, &b_IsolatedElectronTracksVetoMTW);
  fChain->SetBranchAddress("muIsoTrackMatchedToGenElec", &muIsoTrackMatchedToGenElec, &b_muIsoTrackMatchedToGenElec);
  fChain->SetBranchAddress("elecIsoTrackMatchedToGenElec", &elecIsoTrackMatchedToGenElec, &b_elecIsoTrackMatchedToGenElec);
  fChain->SetBranchAddress("pionIsoTrackMatchedToGenElec", &pionIsoTrackMatchedToGenElec, &b_pionIsoTrackMatchedToGenElec);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
  fChain->SetBranchAddress("IsolatedMuonTracksVeto", &IsolatedMuonTracksVeto, &b_IsolatedMuonTracksVeto);
  fChain->SetBranchAddress("IsolatedMuonTracksVetoActivity", &IsolatedMuonTracksVetoActivity, &b_IsolatedMuonTracksVetoActivity);
  fChain->SetBranchAddress("IsolatedMuonTracksVetoMTW", &IsolatedMuonTracksVetoMTW, &b_IsolatedMuonTracksVetoMTW);
  fChain->SetBranchAddress("muIsoTrackMatchedToGenMu", &muIsoTrackMatchedToGenMu, &b_muIsoTrackMatchedToGenMu);
  fChain->SetBranchAddress("elecIsoTrackMatchedToGenMu", &elecIsoTrackMatchedToGenMu, &b_elecIsoTrackMatchedToGenMu);
  fChain->SetBranchAddress("pionIsoTrackMatchedToGenMu", &pionIsoTrackMatchedToGenMu, &b_pionIsoTrackMatchedToGenMu);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
  fChain->SetBranchAddress("IsolatedPionTracksVeto", &IsolatedPionTracksVeto, &b_IsolatedPionTracksVeto);
  fChain->SetBranchAddress("IsolatedPionTracksVetoActivity", &IsolatedPionTracksVetoActivity, &b_IsolatedPionTracksVetoActivity);
  fChain->SetBranchAddress("IsolatedPionTracksVetoMTW", &IsolatedPionTracksVetoMTW, &b_IsolatedPionTracksVetoMTW);
  fChain->SetBranchAddress("muIsoTrackMatchedToGenSingleProngTau", &muIsoTrackMatchedToGenSingleProngTau, &b_muIsoTrackMatchedToGenSingleProngTau);
  fChain->SetBranchAddress("elecIsoTrackMatchedToGenSingleProngTau", &elecIsoTrackMatchedToGenSingleProngTau, &b_elecIsoTrackMatchedToGenSingleProngTau);
  fChain->SetBranchAddress("pionIsoTrackMatchedToGenSingleProngTau", &pionIsoTrackMatchedToGenSingleProngTau, &b_pionIsoTrackMatchedToGenSingleProngTau);
  fChain->SetBranchAddress("JetsNum", &JetsNum, &b_JetsNum);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
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
