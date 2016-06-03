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
#include <TH2D.h>
#include <TH1D.h>
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

const int oneDHT_=16;
double OneDHT_[oneDHT_] = {250,300,350,500,550,600,650,700,750,800,900,1000,1200,1500,2000,10000};
const int oneDMHT_=16;
double OneDMHT_[oneDMHT_] = {0,50,100,150,200,250,300,350,450,500,600,750,900,1200,1700,10000};
const int oneDNJets_=8;
double OneDNJets_[oneDNJets_] = {2,3,4,5,6,7,9,21};
const int oneDBJets_=5;
double OneDBJets_[oneDBJets_] = {0,1,2,3,10};
const int oneDDeltaR_=8;
double OneDDeltaR_[oneDDeltaR_]={0, 0.2 ,0.3, 0.5 ,0.7 ,1.0 , 1.8, 5.0};
const int oneDPTRel_=7;
double OneDPTRel_[oneDPTRel_]={0, 0.2 ,0.4 ,0.6 ,0.8 ,1.0 , 10.0};
const int oneDPT_=12;
double OneDPT_[oneDPT_]={10,12,15,20,30,40,50,60,70,90,100,10000};
const int oneDActivity_=11;
double OneDActivity_[oneDActivity_]={0, 0.01, 0.02, 0.03, 0.05, 0.1, 0.2, 0.4, 0.6, 1., 100.};
const int oneDEta_=7;
double OneDEta_[oneDEta_]={0., 0.5, 1., 1.442, 1.566, 2., 2.52};
const int oneDDTT_ = 11;
double OneDDTT_ [oneDDTT_] = {0.0,0.6,0.8,0.9,0.92,0.94,0.96,0.97,0.98,0.99,1.0};

const int twoDHT_=7;
double TwoDHT_[twoDHT_] = {250,350,500,750,1000,1500,10000};
const int twoDMHT_=5;
double TwoDMHT_[twoDMHT_] = {250,350,500,750,10000};
const int twoDNJets_=8;
double TwoDNJets_[twoDNJets_] = {2,3,4,5,6,7,9,21};
const int twoDBJets_=5;
double TwoDBJets_[twoDBJets_] = {0,1,2,3,10};
const int twoDDeltaR_=8;
double TwoDDeltaR_[twoDDeltaR_]={0, 0.2 ,0.3, 0.5 ,0.7 ,1.0 , 1.8, 5.0};
const int twoDPTRel_=7;
double TwoDPTRel_[twoDPTRel_]={0, 0.2 ,0.4 ,0.6 ,0.8 ,1.0 , 10.0};
const int twoDPT_=12;
double TwoDPT_[twoDPT_]={10,12,15,20,30,40,50,60,70,90,100,10000};
const int twoDActivity_=11;
double TwoDActivity_[twoDActivity_]={0, 0.01, 0.02, 0.03, 0.05, 0.1, 0.2, 0.4, 0.6, 1., 100.};
const int twoDEta_=7;
double TwoDEta_[twoDEta_]={0., 0.5, 1., 1.442, 1.566, 2., 2.52};

const int threeDHT_=6;
double ThreeDHT_[threeDHT_] = {250,350,500,750,1000,10000};
const int threeDMHT_=4;
double ThreeDMHT_[threeDMHT_] = {250,350,500,10000};


class EffMaker : public TSelector {
 public :
  
  TTree          *fChain;

  TString fileName;

  
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
  
  TH1Eff *MuPurityOldBTag_;
  TH1Eff *MuPurityOldNJets_;
  TH1Eff *MuPurityOldHT_;
  TH1Eff *MuPurityOldMHT_;
  TH1Eff *MuPurityOldPT_;
  TH1Eff *MuPurityOldActivity_;
  //2D
  TH2Eff *MuonPurityOldMHTNJet_;
  
  //elec
  //1D
  TH1Eff *ElecPurityOldBTag_;
  TH1Eff *ElecPurityOldNJets_;
  TH1Eff *ElecPurityOldHT_;
  TH1Eff *ElecPurityOldMHT_;
  TH1Eff *ElecPurityOldPT_;
  TH1Eff *ElecPurityOldActivity_;
  //2D
  TH2Eff *ElecPurityOldMHTNJet_;
  
  
  // Acceptance
  // mu 
  //1D
  TH1Eff *MuAccBTag_;
  TH1Eff *MuAccNJets_;
  TH1Eff *MuAccHT_;
  TH1Eff *MuAccMHT_;
  TH1Eff *MuAccPT_;
  TH1Eff *MuAccDTT_;
  TH1Eff *MuAccActivity_;
  // 2D
  TH2Eff *MuAccHTNJets_;
  TH2Eff *MuAccMHTNJets_;
  TH2Eff *MuAccHTMHT_;
  TH2Eff *MuAccBTagNJets_;
  TH2Eff *MuAccMHTNJetsB0_;
  TH2Eff *MuAccMHTNJetsB1_Inf_;
  TH2Eff *MuAccHTMHT_NJetsLow_;
  TH2Eff *MuAccHTMHT_NJets2_;
  TH2Eff *MuAccHTMHT_NJets3_;
  TH2Eff *MuAccHTMHT_NJets4_;
  TH2Eff *MuAccHTMHT_NJets5_;
  TH2Eff *MuAccHTMHT_NJets6_;
  TH2Eff *MuAccHTMHT_NJets78_;
  TH2Eff *MuAccHTMHT_NJets9Inf_;
  TH2Eff *MuAccHTMHT_NJetsHigh_;
  TH2Eff *MuAccHTMHTB0_;
  TH2Eff *MuAccHTMHTB1_Inf_;
  TH2Eff *MuAccHTDTT_NJets2_;
  TH2Eff *MuAccHTDTT_NJets3_;
  TH2Eff *MuAccHTDTT_NJets4_;
  TH2Eff *MuAccHTDTT_NJets5_;
  TH2Eff *MuAccHTDTT_NJets6_;
  TH2Eff *MuAccHTDTT_NJets78_;
  TH2Eff *MuAccHTDTT_NJets9Inf_;
  
  // elec
  //1D
  TH1Eff *ElecAccBTag_;
  TH1Eff *ElecAccNJets_;
  TH1Eff *ElecAccHT_;
  TH1Eff *ElecAccMHT_;
  TH1Eff *ElecAccPT_;
  TH1Eff *ElecAccDTT_;
  TH1Eff *ElecAccActivity_;
  // 2D
  TH2Eff *ElecAccHTNJets_;
  TH2Eff *ElecAccMHTNJets_;
  TH2Eff *ElecAccHTMHT_;
  TH2Eff *ElecAccBTagNJets_;
  TH2Eff *ElecAccMHTNJetsB0_;
  TH2Eff *ElecAccMHTNJetsB1_Inf_;
  TH2Eff *ElecAccHTMHT_NJetsLow_;
  TH2Eff *ElecAccHTMHT_NJets2_;
  TH2Eff *ElecAccHTMHT_NJets3_;
  TH2Eff *ElecAccHTMHT_NJets4_;
  TH2Eff *ElecAccHTMHT_NJets5_;
  TH2Eff *ElecAccHTMHT_NJets6_;
  TH2Eff *ElecAccHTMHT_NJets78_;
  TH2Eff *ElecAccHTMHT_NJets9Inf_;
  TH2Eff *ElecAccHTMHT_NJetsHigh_;
  TH2Eff *ElecAccHTMHTB0_;
  TH2Eff *ElecAccHTMHTB1_Inf_;
  TH2Eff *ElecAccHTDTT_NJets2_;
  TH2Eff *ElecAccHTDTT_NJets3_;
  TH2Eff *ElecAccHTDTT_NJets4_;
  TH2Eff *ElecAccHTDTT_NJets5_;
  TH2Eff *ElecAccHTDTT_NJets6_;
  TH2Eff *ElecAccHTDTT_NJets78_;
  TH2Eff *ElecAccHTDTT_NJets9Inf_;
  

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
  TH2Eff *MuRecoActivityPT_;
  TH2Eff *MuRecoRelPTDeltaRJet_;
  TH2Eff *MuRecoPTEta_;

  
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
  TH2Eff *ElecRecoActivityPT_;
  TH2Eff *ElecRecoRelPTDeltaRJet_;
  TH2Eff *ElecRecoPTEta_;

  
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
  TH2Eff *MuIsoActivityPT_;
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
  TH2Eff *ElecIsoActivityPT_;
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
  TH2Eff *MuMTWHTNJets_;
  TH2Eff *MuMTWMHTNJets_;
  TH2Eff *MuMTWHTMHT_;

  
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
  TH2Eff *ElecMTWHTNJets_;
  TH2Eff *ElecMTWMHTNJets_;
  TH2Eff *ElecMTWHTMHT_;

  
  
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

  TH1Eff *MuDiLepFractionBTag_;
  TH1Eff *MuDiLepFractionNJets_;
  TH1Eff *MuDiLepFractionHT_;
  TH1Eff *MuDiLepFractionMHT_;
  
  // elec
  //1D
  TH1Eff *ElecDiLepContributionBTag_;
  TH1Eff *ElecDiLepContributionNJets_;
  TH1Eff *ElecDiLepContributionHT_;
  TH1Eff *ElecDiLepContributionMHT_;

  TH1Eff *ElecDiLepFractionBTag_;
  TH1Eff *ElecDiLepFractionNJets_;
  TH1Eff *ElecDiLepFractionHT_;
  TH1Eff *ElecDiLepFractionMHT_;
  
  // di lep mtw cut applied
  // mu 
  //1D
  TH1Eff *MuDiLepContributionMTWBTag_;
  TH1Eff *MuDiLepContributionMTWNJets_;
  TH1Eff *MuDiLepContributionMTWHT_;
  TH1Eff *MuDiLepContributionMTWMHT_;
  TH2Eff *MuDiLepContributionMTWMHTNJets_;
  
  // elec
  //1D
  TH1Eff *ElecDiLepContributionMTWBTag_;
  TH1Eff *ElecDiLepContributionMTWNJets_;
  TH1Eff *ElecDiLepContributionMTWHT_;
  TH1Eff *ElecDiLepContributionMTWMHT_;
  TH2Eff *ElecDiLepContributionMTWMHTNJets_;
  

  // single isolated track from mu or electron
  TH1Eff *ExpectationReductionIsoTrackBTagEff_;
  TH1Eff *ExpectationReductionIsoTrackNJetsEff_;
  TH1Eff *ExpectationReductionIsoTrackHTEff_;
  TH1Eff *ExpectationReductionIsoTrackMHTEff_;
  TH1Eff *ExpectationReductionIsoTrackPTEff_;
  TH1Eff *ExpectationReductionIsoTrackActivityEff_;

  // 2D
  TH2Eff *IsoTrackReductionHTNJets_; 
  TH2Eff *IsoTrackReductionMHTNJets_;
  TH2Eff *IsoTrackReductionHTMHT_NJetsVeryLow_;
  TH2Eff *IsoTrackReductionHTMHT_NJetsLow_;
  TH2Eff *IsoTrackReductionHTMHT_NJets2_;
  TH2Eff *IsoTrackReductionHTMHT_NJets3_;
  TH2Eff *IsoTrackReductionHTMHT_NJets4_;
  TH2Eff *IsoTrackReductionHTMHT_NJets5_;
  TH2Eff *IsoTrackReductionHTMHT_NJets6_;
  TH2Eff *IsoTrackReductionHTMHT_NJetsHigh_;
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
  TH2Eff *MuIsoTrackReductionHTMHT_NJetsVeryLow_;
  TH2Eff *MuIsoTrackReductionHTMHT_NJetsLow_;
  TH2Eff *MuIsoTrackReductionHTMHT_NJetsHigh_;
  
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
  TH2Eff *ElecIsoTrackReductionHTMHT_NJetsVeryLow_;
  TH2Eff *ElecIsoTrackReductionHTMHT_NJetsLow_;
  TH2Eff *ElecIsoTrackReductionHTMHT_NJetsHigh_;
  
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
  TH2Eff *PionIsoTrackReductionHTMHT_NJetsVeryLow_;
  TH2Eff *PionIsoTrackReductionHTMHT_NJetsLow_;
  TH2Eff *PionIsoTrackReductionHTMHT_NJetsHigh_;

  // MHT/PTW PDFs
  // NJ X NB, merged HT bins
  TH1D* LostMuRATIO_HT12[9]; 
  TH1D* LostElecRATIO_HT12[9];
  TH1D* LostLepRATIO_HT12[9];
  TH1D* LostMuRATIO_HT3[9]; 
  TH1D* LostElecRATIO_HT3[9];
  TH1D* LostLepRATIO_HT3[9];
  TH1D* LostMuRATIO_HT23[9]; 
  TH1D* LostElecRATIO_HT23[9];
  TH1D* LostLepRATIO_HT23[9];
  
  // Declaration of leaf types
  // Declaration of leaf types
  UInt_t          EvtNum;
  Double_t        HT;
  Double_t        MHT;
  Double_t        MHTPhi;
  Int_t           NJets;
  Int_t           BTags;
  Int_t           isoTracksNum;
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
  std::vector<double>  *GenElec_MT2Activity=0;
  std::vector<double>  *GenMu_MT2Activity=0;
  // std::vector<float>  *GenElecCDTT=0; 
  // std::vector<float>  *GenMuCDTT=0; 
  std::vector<double>  *GenTau_MT2Activity=0;
  std::vector<double>  *selectedIDElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoElectrons_MT2Activity=0;
  std::vector<double>  *selectedIDMuons_MT2Activity=0;
  std::vector<double>  *selectedIDIsoMuons_MT2Activity=0;
  //  std::vector<float>  *selectedIDIsoMuonsCDTT=0;
  std::vector<TLorentzVector> *GenMus=0;
  std::vector<float>   *GenMuDeltaRJet=0;
  std::vector<float>   *GenMuRelPTJet=0;
  UShort_t        GenElecNum;
  std::vector<TLorentzVector> *GenEls=0;
  std::vector<float>   *GenElecDeltaRJet=0;
  std::vector<float>   *GenElecRelPTJet=0;
  //  std::vector<float>  *selectedIDIsoElectronsCDTT=0;
  UShort_t        GenTauNum;
  std::vector<TLorentzVector> *GenTaus=0;
  UShort_t        Expectation;
  UShort_t        ExpectationReductionIsoTrack;
  UShort_t        muAcc;
  UShort_t        muReco;
  UShort_t        muIso;
  Float_t         MTW;
  UShort_t        elecAcc;
  UShort_t        elecReco;
  UShort_t        elecIso;
  UShort_t        MuPurity;
  UShort_t        ElecPurity;
  UShort_t        selectedIDIsoMuonsNum;
  std::vector<TLorentzVector> *selectedIDIsoMuons=0;
  std::vector<unsigned short> *selectedIDIsoMuonsPromptMatched=0;
  UShort_t        selectedIDMuonsNum;
  std::vector<TLorentzVector> *selectedIDMuons=0;
  UShort_t        selectedIDIsoElectronsNum;
  std::vector<TLorentzVector> *selectedIDIsoElectrons=0;
  std::vector<unsigned short> *selectedIDIsoElectronsPromptMatched=0;
  UShort_t        selectedIDElectronsNum;
  std::vector<TLorentzVector> *selectedIDElectrons=0;
  Int_t           isoElectronTracksNum;
  std::vector<TLorentzVector> *isoElectronTracks=0;
  Int_t           isoMuonTracksNum;
  std::vector<TLorentzVector> *isoMuonTracks=0;
  Int_t           isoPionTracksNum;
  std::vector<TLorentzVector> *isoPionTracks=0;
  UShort_t        ExpectationDiLep;
  UShort_t        MuDiLepControlSample;
  UShort_t        ElecDiLepControlSample;
  Double_t        cosDTT;

  // List of branches
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_Leptons=0;   //!
  TBranch        *b_isoTracksNum=0;   //!
  TBranch        *b_Bin=0;   //!
  TBranch        *b_BinQCD=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
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
  //  TBranch        *b_GenMuCDTT=0;   //!
  TBranch        *b_GenElec_MT2Activity=0;   //!
  //  TBranch        *b_GenElecCDTT=0;   //!
  TBranch        *b_GenMu_MT2Activity=0;   //!
  TBranch        *b_GenTau_MT2Activity=0;   //!
  TBranch        *b_selectedIDIsoElectrons_MT2Activity=0;   //!
  TBranch        *b_selectedIDElectrons_MT2Activity=0;   //!
  //  TBranch        *b_selectedIDIsoElectronsCDTT=0;
  TBranch        *b_selectedIDIsoMuons_MT2Activity=0;   //!
  TBranch        *b_selectedIDMuons_MT2Activity=0;   //!
  //  TBranch        *b_selectedIDIsoMuonsCDTT=0;
  TBranch        *b_GenElecNum=0;   //!
  TBranch        *b_GenEls=0;   //!
  TBranch        *b_GenElecDeltaRJet=0;   //!
  TBranch        *b_GenElecRelPTJet=0;   //!!
  TBranch        *b_GenTauNum=0;   //!
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_Expectation=0;   //!
  TBranch        *b_ExpectationReductionIsoTrack=0;   //!
  TBranch        *b_muAcc=0;   //!
  TBranch        *b_muReco=0;   //!
  TBranch        *b_muIso=0;   //!
  TBranch        *b_MTW=0;   //!
  TBranch        *b_elecAcc=0;   //!
  TBranch        *b_elecReco=0;   //!
  TBranch        *b_elecIso=0;   //!
  TBranch        *b_MuPurity=0;   //!
  TBranch        *b_ElecPurity=0;   //!
  TBranch        *b_selectedIDIsoMuonsNum=0;   //!
  TBranch        *b_selectedIDIsoMuons=0;   //!!
  TBranch        *b_selectedIDIsoMuonsPromptMatched=0;   //!
  TBranch        *b_selectedIDMuonsNum=0;   //!
  TBranch        *b_selectedIDMuons=0;   //!
  TBranch        *b_selectedIDIsoElectronsNum=0;   //!
  TBranch        *b_selectedIDIsoElectrons=0;   //!
  TBranch        *b_selectedIDIsoElectronsPromptMatched=0;   //!
  TBranch        *b_selectedIDElectronsNum=0;   //!
  TBranch        *b_selectedIDElectrons=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoElectronTracks=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoMuonTracks=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_isoPionTracks=0;   //!
  TBranch        *b_ExpectationDiLep=0;   //!
  TBranch        *b_MuDiLepControlSample=0;   //!
  TBranch        *b_ElecDiLepControlSample=0;   //!
  TBranch        *b_cosDTT=0;   //!
  

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


  TString option = GetOption();
  TObjArray *optionArray = option.Tokenize(",");
  TString fileNameString = "";

  if(!optionArray->IsEmpty()){
    fileNameString = ((TObjString *)(optionArray->At(0)))->String();
  }

  fileNameString = fileNameString.Strip(TString::kBoth, ' ').String();

  if(fileNameString!="*" && fileNameString!="") fileName = fileNameString;

  
  
  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchStatus("MHTPhi", 1);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchStatus("isoTracksNum", 1);
  fChain->SetBranchAddress("isoTracksNum", &isoTracksNum, &b_isoTracksNum);
  fChain->SetBranchStatus("Bin", 1);
  fChain->SetBranchAddress("Bin", &Bin, &b_Bin);
  fChain->SetBranchStatus("BinQCD", 1);
  fChain->SetBranchAddress("BinQCD", &BinQCD, &b_BinQCD);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchStatus("Weight", 1);
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchStatus("MET", 1);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchStatus("GenMuNum", 1);
  fChain->SetBranchAddress("GenMuNum", &GenMuNum, &b_GenMuNum);
  fChain->SetBranchStatus("GenMus", 1);
  fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
  fChain->SetBranchStatus("GenMuDeltaRJet", 1);
  fChain->SetBranchAddress("GenMuDeltaRJet", &GenMuDeltaRJet, &b_GenMuDeltaRJet);
  fChain->SetBranchStatus("GenMuRelPTJet", 1);
  fChain->SetBranchAddress("GenMuRelPTJet", &GenMuRelPTJet, &b_GenMuRelPTJet);
  //  fChain->SetBranchStatus("GenMuCDTT", 1);
  //  fChain->SetBranchAddress("GenMuCDTT", &GenMuCDTT, &b_GenMuCDTT);
  fChain->SetBranchStatus("GenElecNum", 1);
  fChain->SetBranchAddress("GenElecNum", &GenElecNum, &b_GenElecNum);
  fChain->SetBranchStatus("GenEls", 1);
  fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
  fChain->SetBranchStatus("GenElecDeltaRJet", 1);
  fChain->SetBranchAddress("GenElecDeltaRJet", &GenElecDeltaRJet, &b_GenElecDeltaRJet);
  fChain->SetBranchStatus("GenElecRelPTJet", 1);
  fChain->SetBranchAddress("GenElecRelPTJet", &GenElecRelPTJet, &b_GenElecRelPTJet);
  //  fChain->SetBranchStatus("GenElecCDTT", 1);
  //  fChain->SetBranchAddress("GenElecCDTT", &GenElecCDTT, &b_GenElecCDTT);
  fChain->SetBranchStatus("GenTauNum", 1);
  fChain->SetBranchAddress("GenTauNum", &GenTauNum, &b_GenTauNum);
  fChain->SetBranchStatus("GenTaus", 1);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  fChain->SetBranchStatus("Expectation", 1);
  fChain->SetBranchAddress("Expectation", &Expectation, &b_Expectation);
  fChain->SetBranchStatus("ExpectationReductionIsoTrack", 1);
  fChain->SetBranchAddress("ExpectationReductionIsoTrack", &ExpectationReductionIsoTrack, &b_ExpectationReductionIsoTrack);
  fChain->SetBranchStatus("muAcc", 1);
  fChain->SetBranchAddress("muAcc", &muAcc, &b_muAcc);
  fChain->SetBranchStatus("muReco", 1);
  fChain->SetBranchAddress("muReco", &muReco, &b_muReco);
  fChain->SetBranchStatus("muIso", 1);
  fChain->SetBranchAddress("muIso", &muIso, &b_muIso);
  fChain->SetBranchStatus("MTW", 1);
  fChain->SetBranchAddress("MTW", &MTW, &b_MTW);
  fChain->SetBranchStatus("elecAcc", 1);
  fChain->SetBranchAddress("elecAcc", &elecAcc, &b_elecAcc);
  fChain->SetBranchStatus("elecReco", 1);
  fChain->SetBranchAddress("elecReco", &elecReco, &b_elecReco);
  fChain->SetBranchStatus("elecIso", 1);
  fChain->SetBranchAddress("elecIso", &elecIso, &b_elecIso);
  fChain->SetBranchStatus("MuPurity", 1);
  fChain->SetBranchAddress("MuPurity", &MuPurity, &b_MuPurity);
  fChain->SetBranchStatus("ElecPurity", 1);
  fChain->SetBranchAddress("ElecPurity", &ElecPurity, &b_ElecPurity);
  fChain->SetBranchStatus("selectedIDIsoMuonsNum", 1);
  fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
  fChain->SetBranchStatus("selectedIDIsoMuons", 1);
  fChain->SetBranchAddress("selectedIDIsoMuons", &selectedIDIsoMuons, &b_selectedIDIsoMuons);
  fChain->SetBranchStatus("selectedIDIsoMuonsPromptMatched", 1);
  fChain->SetBranchAddress("selectedIDIsoMuonsPromptMatched", &selectedIDIsoMuonsPromptMatched, &b_selectedIDIsoMuonsPromptMatched);
  fChain->SetBranchStatus("selectedIDMuonsNum", 1);
  fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
  fChain->SetBranchStatus("selectedIDMuons", 1);
  fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
  //  fChain->SetBranchStatus("selectedIDIsoMuonsCDTT", 1);
  //  fChain->SetBranchAddress("selectedIDIsoMuonsCDTT", &selectedIDIsoMuonsCDTT, &b_selectedIDIsoMuonsCDTT);
  fChain->SetBranchStatus("selectedIDIsoElectronsNum", 1);
  fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
  fChain->SetBranchStatus("selectedIDIsoElectrons", 1);
  fChain->SetBranchAddress("selectedIDIsoElectrons", &selectedIDIsoElectrons, &b_selectedIDIsoElectrons);
  fChain->SetBranchStatus("selectedIDIsoElectronsPromptMatched", 1);
  fChain->SetBranchAddress("selectedIDIsoElectronsPromptMatched", &selectedIDIsoElectronsPromptMatched, &b_selectedIDIsoElectronsPromptMatched);
  fChain->SetBranchStatus("selectedIDElectronsNum", 1);
  fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
  fChain->SetBranchStatus("selectedIDElectrons", 1);
  fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
  //  fChain->SetBranchStatus("selectedIDIsoElectronsCDTT", 1);
  //  fChain->SetBranchAddress("selectedIDIsoElectronsCDTT", &selectedIDIsoElectronsCDTT, &b_selectedIDIsoElectronsCDTT);
  fChain->SetBranchStatus("isoElectronTracksNum", 1);
  fChain->SetBranchAddress("isoElectronTracksNum", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
  fChain->SetBranchStatus("isoMuonTracksNum", 1);
  fChain->SetBranchAddress("isoMuonTracksNum", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
  fChain->SetBranchStatus("isoPionTracksNum", 1);
  fChain->SetBranchAddress("isoPionTracksNum", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
  fChain->SetBranchStatus("ExpectationDiLep", 1);
  fChain->SetBranchAddress("ExpectationDiLep", &ExpectationDiLep, &b_ExpectationDiLep);
  fChain->SetBranchStatus("MuDiLepControlSample", 1);
  fChain->SetBranchAddress("MuDiLepControlSample", &MuDiLepControlSample, &b_MuDiLepControlSample);
  fChain->SetBranchStatus("ElecDiLepControlSample", 1);
  fChain->SetBranchAddress("ElecDiLepControlSample", &ElecDiLepControlSample, &b_ElecDiLepControlSample);
  fChain->SetBranchStatus("GenElec_MT2Activity",1);
  fChain->SetBranchAddress("GenElec_MT2Activity", &GenElec_MT2Activity, &b_GenElec_MT2Activity);
  fChain->SetBranchStatus("GenMu_MT2Activity", 1);
  fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity, &b_GenMu_MT2Activity);
  fChain->SetBranchStatus("GenTau_MT2Activity",1);
  fChain->SetBranchAddress("GenTau_MT2Activity", &GenTau_MT2Activity, &b_GenTau_MT2Activity);
  fChain->SetBranchStatus("selectedIDElectrons_MT2Activity",1);
  fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
  fChain->SetBranchStatus("selectedIDIsoElectrons_MT2Activity", 1);
  fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
  fChain->SetBranchStatus("selectedIDIsoMuons_MT2Activity",1);
  fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
  fChain->SetBranchStatus("selectedIDMuons_MT2Activity", 1);
  fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
  fChain->SetBranchStatus("cosDTT", 1);
  fChain->SetBranchAddress("cosDTT", &cosDTT, &b_cosDTT);
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
