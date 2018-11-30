#define EffMaker_cxx
#include "EffMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include "TSystem.h"
#include "TMath.h"

const int nEXTRAPBins(13);

void EffMaker::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();

  TH1::SetDefaultSumw2();

  gSystem->mkdir("Efficiencies");

  if(nicePublication){
    OneDHT_[(sizeof(OneDHT_)/sizeof(OneDHT_[0]))-1] = 5000.;
    OneDMHT_[(sizeof(OneDMHT_)/sizeof(OneDMHT_[0]))-1] = 5000.;
    OneDPT_[(sizeof(OneDPT_)/sizeof(OneDPT_[0]))-1] = 1000.;
    OneDPTtrk_[(sizeof(OneDPTtrk_)/sizeof(OneDPTtrk_[0]))-1] = 1000.;
    OneDActivity_[(sizeof(OneDActivity_)/sizeof(OneDActivity_[0]))-1] = 10.;
    OneDNJets_[(sizeof(OneDNJets_)/sizeof(OneDNJets_[0]))-1] = 15.5;
    OneDPT_[0] = 9.99;
    OneDPTtrk_[0] = 4.99;
  }

  if(nicePublication){
    TwoDHT_[(sizeof(TwoDHT_)/sizeof(TwoDHT_[0]))-1] = 5000.;
    TwoDMHT_[(sizeof(TwoDMHT_)/sizeof(TwoDMHT_[0]))-1] = 5000.;
    TwoDPT_[(sizeof(TwoDPT_)/sizeof(TwoDPT_[0]))-1] = 200.;
    TwoDPTlow_[(sizeof(TwoDPTlow_)/sizeof(TwoDPTlow_[0]))-1] = 200.;
    TwoDActivity_[(sizeof(TwoDActivity_)/sizeof(TwoDActivity_[0]))-1] = 10.;
    TwoDNJets_[(sizeof(TwoDNJets_)/sizeof(TwoDNJets_[0]))-1] = 15.5;
    TwoDPT_[0] = 9.99;
    TwoDPTlow_[0] = 4.99;
  }

  if(nicePublication){
    ThreeDHT_[(sizeof(ThreeDHT_)/sizeof(ThreeDHT_[0]))-1] = 5000.;
    ThreeDHT_fine_[(sizeof(ThreeDHT_fine_)/sizeof(ThreeDHT_fine_[0]))-1] = 5000.;
    ThreeDHT_coarse_[(sizeof(ThreeDHT_coarse_)/sizeof(ThreeDHT_coarse_[0]))-1] = 5000.;
    ThreeDHT_bin_[(sizeof(ThreeDHT_bin_)/sizeof(ThreeDHT_bin_[0]))-1] = 5000.;
    ThreeDMHT_[(sizeof(ThreeDMHT_)/sizeof(ThreeDMHT_[0]))-1] = 5000.;
    ThreeDMHT_fine_[(sizeof(ThreeDMHT_fine_)/sizeof(ThreeDMHT_fine_[0]))-1] = 5000.;
    ThreeDMHT_coarse_[(sizeof(ThreeDMHT_coarse_)/sizeof(ThreeDMHT_coarse_[0]))-1] = 5000.;
    ThreeDMHT_bin_[(sizeof(ThreeDMHT_bin_)/sizeof(ThreeDMHT_bin_[0]))-1] = 5000.;
  } 

}

void EffMaker::SlaveBegin(TTree * /*tree*/)
{
  TString option = GetOption();
  TH1::SetDefaultSumw2();

  gSystem->mkdir("Efficiencies"); 

  if(nicePublication){
    std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    std::cout<<"!Option for nice plotting enabled! You cannot use Efficiencies.root, as bins might be cut off etc!"<<std::endl;
    std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
  }

  SearchBins_ = new SearchBins(!nicePublication);

  // additional stuff for thesis
  IsoTrackFractionPTActivity_ = new TH2Eff("IsoTrackFractionPTActivity","IsoTrackFractionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  MuIsoTrackFractionPTActivity_ = new TH2Eff("MuIsoTrackFractionPTActivity","MuIsoTrackFractionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  ElecIsoTrackFractionPTActivity_ = new TH2Eff("ElecIsoTrackFractionPTActivity","ElecIsoTrackFractionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  PionIsoTrackFractionPTActivity_ = new TH2Eff("PionIsoTrackFractionPTActivity","PionIsoTrackFractionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);


  // Sam
  recoLepOverAccMu = new TH2Eff("recoLepOverAccMu", "recoLepOverAccMu", twoDPTlow_-1,TwoDPTlow_, twoDEtaMu_-1,TwoDEtaMu_);
  recoTrackOverAccMu = new TH2Eff("recoTrackOverAccMu", "recoTrackOverAccMu", twoDPTlow_-1,TwoDPTlow_, twoDEtaMu_-1,TwoDEtaMu_);
  recoOverAccMu = new TH2Eff("recoOverAccMu", "recoOverAccMu", twoDPTlow_-1,TwoDPTlow_, twoDEtaMu_-1,TwoDEtaMu_);
  recoLepOverAccEl = new TH2Eff("recoLepOverAccEl", "recoLepOverAccEl", twoDPTlow_-1,TwoDPTlow_, twoDEtaElec_-1,TwoDEtaElec_);
  recoTrackOverAccEl = new TH2Eff("recoTrackOverAccEl", "recoTrackOverAccEl", twoDPTlow_-1,TwoDPTlow_, twoDEtaElec_-1,TwoDEtaElec_);
  recoOverAccEl = new TH2Eff("recoOverAccEl", "recoOverAccEl", twoDPTlow_-1,TwoDPTlow_, twoDEtaElec_-1,TwoDEtaElec_);

  // NEW
  MuAccSearchBins_ = new TH1Eff("MuAccSearchBins","MuAccSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecAccSearchBins_ = new TH1Eff("ElecAccSearchBins","ElecAccSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuRecoSearchBins_ = new TH1Eff("MuRecoSearchBins","MuRecoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoSearchBins_ = new TH1Eff("MuIsoSearchBins","MuIsoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecRecoSearchBins_ = new TH1Eff("ElecRecoSearchBins","ElecRecoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoSearchBins_ = new TH1Eff("ElecIsoSearchBins","ElecIsoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuIsoTrackVetoSearchBins_ = new TH1Eff("MuIsoTrackVetoSearchBins","MuIsoTrackVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBins_ = new TH1Eff("ElecIsoTrackVetoSearchBins","ElecIsoTrackVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBins_ = new TH1Eff("PionIsoTrackVetoSearchBins","PionIsoTrackVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  IsoTrackVetoSearchBins_ = new TH1Eff("IsoTrackVetoSearchBins","IsoTrackVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuIsoTrackVetoSearchBinsSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsSF","MuIsoTrackVetoSearchBinsSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsSF","ElecIsoTrackVetoSearchBinsSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsSF","PionIsoTrackVetoSearchBinsSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  IsoTrackVetoSearchBinsSF_ = new TH1Eff("IsoTrackVetoSearchBinsSF","IsoTrackVetoSearchBinsSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuMTWSearchBins_ = new TH1Eff("MuMTWSearchBins","MuMTWSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecMTWSearchBins_ = new TH1Eff("ElecMTWSearchBins","ElecMTWSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuPuritySearchBins_ = new TH1Eff("MuPuritySearchBins","MuPuritySearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecPuritySearchBins_ = new TH1Eff("ElecPuritySearchBins","ElecPuritySearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuDiLepCRSearchBins_ = new TH1Eff("MuDiLepCRSearchBins","MuDiLepCRSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecDiLepCRSearchBins_ = new TH1Eff("ElecDiLepCRSearchBins","ElecDiLepCRSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuDiLepSRSearchBins_ = new TH1Eff("MuDiLepSRSearchBins","MuDiLepSRSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecDiLepSRSearchBins_ = new TH1Eff("ElecDiLepSRSearchBins","ElecDiLepSRSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuDiLepSRwoVetoSearchBins_ = new TH1Eff("MuDiLepSRwoVetoSearchBins","MuDiLepSRwoVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecDiLepSRwoVetoSearchBins_ = new TH1Eff("ElecDiLepSRwoVetoSearchBins","ElecDiLepSRwoVetoSearchBins", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuDiLepSRSearchBinsEff_ = new TH1Eff("MuDiLepSRSearchBinsEff","MuDiLepSRSearchBinsEff", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecDiLepSRSearchBinsEff_ = new TH1Eff("ElecDiLepSRSearchBinsEff","ElecDiLepSRSearchBinsEff", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuDiLepSRwoVetoSearchBinsEff_ = new TH1Eff("MuDiLepSRwoVetoSearchBinsEff","MuDiLepSRwoVetoSearchBinsEff", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecDiLepSRwoVetoSearchBinsEff_ = new TH1Eff("ElecDiLepSRwoVetoSearchBinsEff","ElecDiLepSRwoVetoSearchBinsEff", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuIsoTrackVetoSearchBinsLowPt_ = new TH1Eff("MuIsoTrackVetoSearchBinsLowPt","MuIsoTrackVetoSearchBinsLowPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsLowPt_ = new TH1Eff("ElecIsoTrackVetoSearchBinsLowPt","ElecIsoTrackVetoSearchBinsLowPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsLowPt_ = new TH1Eff("PionIsoTrackVetoSearchBinsLowPt","PionIsoTrackVetoSearchBinsLowPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  IsoTrackVetoSearchBinsLowPt_ = new TH1Eff("IsoTrackVetoSearchBinsLowPt","IsoTrackVetoSearchBinsLowPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  MuIsoTrackVetoSearchBinsHighPt_ = new TH1Eff("MuIsoTrackVetoSearchBinsHighPt","MuIsoTrackVetoSearchBinsHighPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsHighPt_ = new TH1Eff("ElecIsoTrackVetoSearchBinsHighPt","ElecIsoTrackVetoSearchBinsHighPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);      
  PionIsoTrackVetoSearchBinsHighPt_ = new TH1Eff("PionIsoTrackVetoSearchBinsHighPt","PionIsoTrackVetoSearchBinsHighPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  IsoTrackVetoSearchBinsHighPt_ = new TH1Eff("IsoTrackVetoSearchBinsHighPt","IsoTrackVetoSearchBinsHighPt", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsAcc_ = new TH1Eff("IsoTrackVetoSearchBinsAcc","IsoTrackVetoSearchBinsAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsAcc_ = new TH1Eff("MuIsoTrackVetoSearchBinsAcc","MuIsoTrackVetoSearchBinsAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsAcc_ = new TH1Eff("ElecIsoTrackVetoSearchBinsAcc","ElecIsoTrackVetoSearchBinsAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsAcc_ = new TH1Eff("PionIsoTrackVetoSearchBinsAcc","PionIsoTrackVetoSearchBinsAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsIDIso_ = new TH1Eff("IsoTrackVetoSearchBinsIDIso","IsoTrackVetoSearchBinsIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsIDIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsIDIso","MuIsoTrackVetoSearchBinsIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsIDIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsIDIso","ElecIsoTrackVetoSearchBinsIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsIDIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsIDIso","PionIsoTrackVetoSearchBinsIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsID_ = new TH1Eff("IsoTrackVetoSearchBinsID","IsoTrackVetoSearchBinsID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsID_ = new TH1Eff("MuIsoTrackVetoSearchBinsID","MuIsoTrackVetoSearchBinsID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsID_ = new TH1Eff("ElecIsoTrackVetoSearchBinsID","ElecIsoTrackVetoSearchBinsID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsID_ = new TH1Eff("PionIsoTrackVetoSearchBinsID","PionIsoTrackVetoSearchBinsID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsIso_ = new TH1Eff("IsoTrackVetoSearchBinsIso","IsoTrackVetoSearchBinsIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsIso","MuIsoTrackVetoSearchBinsIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsIso","ElecIsoTrackVetoSearchBinsIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsIso","PionIsoTrackVetoSearchBinsIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("IsoTrackVetoSearchBinsMuAcc","IsoTrackVetoSearchBinsMuAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuAcc","MuIsoTrackVetoSearchBinsMuAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuAcc","ElecIsoTrackVetoSearchBinsMuAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuAcc","PionIsoTrackVetoSearchBinsMuAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuIDIso_ = new TH1Eff("IsoTrackVetoSearchBinsMuIDIso","IsoTrackVetoSearchBinsMuIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuIDIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuIDIso","MuIsoTrackVetoSearchBinsMuIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuIDIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuIDIso","ElecIsoTrackVetoSearchBinsMuIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuIDIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuIDIso","PionIsoTrackVetoSearchBinsMuIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuID_ = new TH1Eff("IsoTrackVetoSearchBinsMuID","IsoTrackVetoSearchBinsMuID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuID_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuID","MuIsoTrackVetoSearchBinsMuID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuID_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuID","ElecIsoTrackVetoSearchBinsMuID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuID_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuID","PionIsoTrackVetoSearchBinsMuID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuIso_ = new TH1Eff("IsoTrackVetoSearchBinsMuIso","IsoTrackVetoSearchBinsMuIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuIso","MuIsoTrackVetoSearchBinsMuIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuIso","ElecIsoTrackVetoSearchBinsMuIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuIso","PionIsoTrackVetoSearchBinsMuIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("IsoTrackVetoSearchBinsElecAcc","IsoTrackVetoSearchBinsElecAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecAcc","MuIsoTrackVetoSearchBinsElecAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecAcc","ElecIsoTrackVetoSearchBinsElecAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecAcc","PionIsoTrackVetoSearchBinsElecAcc", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecIDIso_ = new TH1Eff("IsoTrackVetoSearchBinsElecIDIso","IsoTrackVetoSearchBinsElecIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecIDIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecIDIso","MuIsoTrackVetoSearchBinsElecIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecIDIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecIDIso","ElecIsoTrackVetoSearchBinsElecIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecIDIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecIDIso","PionIsoTrackVetoSearchBinsElecIDIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecID_ = new TH1Eff("IsoTrackVetoSearchBinsElecID","IsoTrackVetoSearchBinsElecID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecID_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecID","MuIsoTrackVetoSearchBinsElecID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecID_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecID","ElecIsoTrackVetoSearchBinsElecID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecID_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecID","PionIsoTrackVetoSearchBinsElecID", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecIso_ = new TH1Eff("IsoTrackVetoSearchBinsElecIso","IsoTrackVetoSearchBinsElecIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecIso","MuIsoTrackVetoSearchBinsElecIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecIso","ElecIsoTrackVetoSearchBinsElecIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecIso","PionIsoTrackVetoSearchBinsElecIso", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuAccSF_ = new TH1Eff("IsoTrackVetoSearchBinsMuAccSF","IsoTrackVetoSearchBinsMuAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuAccSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuAccSF","MuIsoTrackVetoSearchBinsMuAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuAccSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuAccSF","ElecIsoTrackVetoSearchBinsMuAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuAccSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuAccSF","PionIsoTrackVetoSearchBinsMuAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuIDSF_ = new TH1Eff("IsoTrackVetoSearchBinsMuIDSF","IsoTrackVetoSearchBinsMuIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuIDSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuIDSF","MuIsoTrackVetoSearchBinsMuIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuIDSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuIDSF","ElecIsoTrackVetoSearchBinsMuIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuIDSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuIDSF","PionIsoTrackVetoSearchBinsMuIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsMuIsoSF_ = new TH1Eff("IsoTrackVetoSearchBinsMuIsoSF","IsoTrackVetoSearchBinsMuIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsMuIsoSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuIsoSF","MuIsoTrackVetoSearchBinsMuIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsMuIsoSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuIsoSF","ElecIsoTrackVetoSearchBinsMuIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsMuIsoSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuIsoSF","PionIsoTrackVetoSearchBinsMuIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecAccSF_ = new TH1Eff("IsoTrackVetoSearchBinsElecAccSF","IsoTrackVetoSearchBinsElecAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecAccSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecAccSF","MuIsoTrackVetoSearchBinsElecAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecAccSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecAccSF","ElecIsoTrackVetoSearchBinsElecAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecAccSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecAccSF","PionIsoTrackVetoSearchBinsElecAccSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecIDSF_ = new TH1Eff("IsoTrackVetoSearchBinsElecIDSF","IsoTrackVetoSearchBinsElecIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecIDSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecIDSF","MuIsoTrackVetoSearchBinsElecIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecIDSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecIDSF","ElecIsoTrackVetoSearchBinsElecIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecIDSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecIDSF","PionIsoTrackVetoSearchBinsElecIDSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoSearchBinsElecIsoSF_ = new TH1Eff("IsoTrackVetoSearchBinsElecIsoSF","IsoTrackVetoSearchBinsElecIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  MuIsoTrackVetoSearchBinsElecIsoSF_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecIsoSF","MuIsoTrackVetoSearchBinsElecIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  ElecIsoTrackVetoSearchBinsElecIsoSF_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecIsoSF","ElecIsoTrackVetoSearchBinsElecIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);
  PionIsoTrackVetoSearchBinsElecIsoSF_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecIsoSF","PionIsoTrackVetoSearchBinsElecIsoSF", SearchBins_->GetNbins(), 0.5, SearchBins_->GetNbins()+0.5);

  IsoTrackVetoActivityPtMuIDIso_ = new TH2Eff("IsoTrackVetoActivityPtMuIDIso","IsoTrackVetoActivityPtMuIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtMuIDIso_ = new TH2Eff("MuIsoTrackVetoActivityPtMuIDIso","MuIsoTrackVetoActivityPtMuIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtMuIDIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtMuIDIso","ElecIsoTrackVetoActivityPtMuIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtMuIDIso_ = new TH2Eff("PionIsoTrackVetoActivityPtMuIDIso","PionIsoTrackVetoActivityPtMuIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoActivityPtMuID_ = new TH2Eff("IsoTrackVetoActivityPtMuID","IsoTrackVetoActivityPtMuID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtMuID_ = new TH2Eff("MuIsoTrackVetoActivityPtMuID","MuIsoTrackVetoActivityPtMuID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtMuID_ = new TH2Eff("ElecIsoTrackVetoActivityPtMuID","ElecIsoTrackVetoActivityPtMuID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtMuID_ = new TH2Eff("PionIsoTrackVetoActivityPtMuID","PionIsoTrackVetoActivityPtMuID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoActivityPtMuIso_ = new TH2Eff("IsoTrackVetoActivityPtMuIso","IsoTrackVetoActivityPtMuIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtMuIso_ = new TH2Eff("MuIsoTrackVetoActivityPtMuIso","MuIsoTrackVetoActivityPtMuIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtMuIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtMuIso","ElecIsoTrackVetoActivityPtMuIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtMuIso_ = new TH2Eff("PionIsoTrackVetoActivityPtMuIso","PionIsoTrackVetoActivityPtMuIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoActivityPtElecIDIso_ = new TH2Eff("IsoTrackVetoActivityPtElecIDIso","IsoTrackVetoActivityPtElecIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtElecIDIso_ = new TH2Eff("MuIsoTrackVetoActivityPtElecIDIso","MuIsoTrackVetoActivityPtElecIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtElecIDIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtElecIDIso","ElecIsoTrackVetoActivityPtElecIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtElecIDIso_ = new TH2Eff("PionIsoTrackVetoActivityPtElecIDIso","PionIsoTrackVetoActivityPtElecIDIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoActivityPtElecID_ = new TH2Eff("IsoTrackVetoActivityPtElecID","IsoTrackVetoActivityPtElecID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtElecID_ = new TH2Eff("MuIsoTrackVetoActivityPtElecID","MuIsoTrackVetoActivityPtElecID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtElecID_ = new TH2Eff("ElecIsoTrackVetoActivityPtElecID","ElecIsoTrackVetoActivityPtElecID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtElecID_ = new TH2Eff("PionIsoTrackVetoActivityPtElecID","PionIsoTrackVetoActivityPtElecID", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoActivityPtElecIso_ = new TH2Eff("IsoTrackVetoActivityPtElecIso","IsoTrackVetoActivityPtElecIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  MuIsoTrackVetoActivityPtElecIso_ = new TH2Eff("MuIsoTrackVetoActivityPtElecIso","MuIsoTrackVetoActivityPtElecIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  ElecIsoTrackVetoActivityPtElecIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtElecIso","ElecIsoTrackVetoActivityPtElecIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);
  PionIsoTrackVetoActivityPtElecIso_ = new TH2Eff("PionIsoTrackVetoActivityPtElecIso","PionIsoTrackVetoActivityPtElecIso", twoDActivity_-1, TwoDActivity_, twoDPT_-1, TwoDPT_);

  IsoTrackVetoPtEtaMuIDIso_ = new TH2Eff("IsoTrackVetoPtEtaMuIDIso","IsoTrackVetoPtEtaMuIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaMuIDIso_ = new TH2Eff("MuIsoTrackVetoPtEtaMuIDIso","MuIsoTrackVetoPtEtaMuIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaMuIDIso_ = new TH2Eff("ElecIsoTrackVetoPtEtaMuIDIso","ElecIsoTrackVetoPtEtaMuIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaMuIDIso_ = new TH2Eff("PionIsoTrackVetoPtEtaMuIDIso","PionIsoTrackVetoPtEtaMuIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);

  IsoTrackVetoPtEtaMuID_ = new TH2Eff("IsoTrackVetoPtEtaMuID","IsoTrackVetoPtEtaMuID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaMuID_ = new TH2Eff("MuIsoTrackVetoPtEtaMuID","MuIsoTrackVetoPtEtaMuID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaMuID_ = new TH2Eff("ElecIsoTrackVetoPtEtaMuID","ElecIsoTrackVetoPtEtaMuID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaMuID_ = new TH2Eff("PionIsoTrackVetoPtEtaMuID","PionIsoTrackVetoPtEtaMuID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);

  IsoTrackVetoPtEtaMuIso_ = new TH2Eff("IsoTrackVetoPtEtaMuIso","IsoTrackVetoPtEtaMuIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaMuIso_ = new TH2Eff("MuIsoTrackVetoPtEtaMuIso","MuIsoTrackVetoPtEtaMuIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaMuIso_ = new TH2Eff("ElecIsoTrackVetoPtEtaMuIso","ElecIsoTrackVetoPtEtaMuIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaMuIso_ = new TH2Eff("PionIsoTrackVetoPtEtaMuIso","PionIsoTrackVetoPtEtaMuIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);

  IsoTrackVetoPtEtaElecIDIso_ = new TH2Eff("IsoTrackVetoPtEtaElecIDIso","IsoTrackVetoPtEtaElecIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaElecIDIso_ = new TH2Eff("MuIsoTrackVetoPtEtaElecIDIso","MuIsoTrackVetoPtEtaElecIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaElecIDIso_ = new TH2Eff("ElecIsoTrackVetoPtEtaElecIDIso","ElecIsoTrackVetoPtEtaElecIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaElecIDIso_ = new TH2Eff("PionIsoTrackVetoPtEtaElecIDIso","PionIsoTrackVetoPtEtaElecIDIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);

  IsoTrackVetoPtEtaElecID_ = new TH2Eff("IsoTrackVetoPtEtaElecID","IsoTrackVetoPtEtaElecID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaElecID_ = new TH2Eff("MuIsoTrackVetoPtEtaElecID","MuIsoTrackVetoPtEtaElecID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaElecID_ = new TH2Eff("ElecIsoTrackVetoPtEtaElecID","ElecIsoTrackVetoPtEtaElecID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaElecID_ = new TH2Eff("PionIsoTrackVetoPtEtaElecID","PionIsoTrackVetoPtEtaElecID", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);

  IsoTrackVetoPtEtaElecIso_ = new TH2Eff("IsoTrackVetoPtEtaElecIso","IsoTrackVetoPtEtaElecIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  MuIsoTrackVetoPtEtaElecIso_ = new TH2Eff("MuIsoTrackVetoPtEtaElecIso","MuIsoTrackVetoPtEtaElecIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  ElecIsoTrackVetoPtEtaElecIso_ = new TH2Eff("ElecIsoTrackVetoPtEtaElecIso","ElecIsoTrackVetoPtEtaElecIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);
  PionIsoTrackVetoPtEtaElecIso_ = new TH2Eff("PionIsoTrackVetoPtEtaElecIso","PionIsoTrackVetoPtEtaElecIso", twoDPT_-1, TwoDPT_, twoDEtaElec_-1, TwoDEtaElec_);


  // purity
  // muon
  //1D
  MuPurityOldBTag_ = new TH1Eff("MuPurityOldBTag1D","MuPurityOldBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityOldNJets_ = new TH1Eff("MuPurityOldNJets1D","MuPurityOldNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityOldHT_ = new TH1Eff("MuPurityOldHT1D","MuPurityOldHT1D",oneDHT_-1,OneDHT_);
  MuPurityOldMHT_ = new TH1Eff("MuPurityOldMHT1D","MuPurityOldMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityOldMHTNJet_ = new TH2Eff("MuonPurityOldMHTNJet","MuonPurityOldMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuonPurityOldNJetsBTags_ = new TH2Eff("MuonPurityOldNJetsBTags","MuonPurityOldNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  
  // electron
  //1D
  ElecPurityOldBTag_ = new TH1Eff("ElecPurityOldBTag1D","ElecPurityOldBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityOldNJets_ = new TH1Eff("ElecPurityOldNJets1D","ElecPurityOldNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityOldHT_ = new TH1Eff("ElecPurityOldHT1D","ElecPurityOldHT1D",oneDHT_-1,OneDHT_);
  ElecPurityOldMHT_ = new TH1Eff("ElecPurityOldMHT1D","ElecPurityOldMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityOldMHTNJet_ = new TH2Eff("ElecPurityOldMHTNJet","ElecPurityOldMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecPurityOldNJetsBTags_ = new TH2Eff("ElecPurityOldNJetsBTags","ElecPurityOldNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  
  // purity x-check

  // muon
  // 1D
  MuPurityBTag_ = new TH1Eff("MuPurityBTag1D","MuPurityBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityNJets_ = new TH1Eff("MuPurityNJets1D","MuPurityNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityHT_ = new TH1Eff("MuPurityHT1D","MuPurityHT1D",oneDHT_-1,OneDHT_);
  MuPurityMHT_ = new TH1Eff("MuPurityMHT1D","MuPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityMHTNJet_ = new TH2Eff("MuonPurityMHTNJet","MuonPurityMHTNJet",twoDMHT_fine_-1,TwoDMHT_fine_,twoDNJets_-1,TwoDNJets_);
  MuonPurityNJetsBTags_ = new TH2Eff("MuonPurityNJetsBTags","MuonPurityNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  MuonPurityMHTBTags_ = new TH2Eff("MuonPurityMHTBTags","MuonPurityMHTBTags",twoDMHT_-1,TwoDMHT_,twoDBJets_-1,TwoDBJets_);
  MuonPurityHTMHT_ = new TH2Eff("MuonPurityHTMHT","MuonPurityHTMHT",twoDHT_bin_-1,TwoDHT_bin_,twoDMHT_bin_-1,TwoDMHT_bin_);

  
  // electron
  //1D
  ElecPurityBTag_ = new TH1Eff("ElecPurityBTag1D","ElecPurityBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityNJets_ = new TH1Eff("ElecPurityNJets1D","ElecPurityNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityHT_ = new TH1Eff("ElecPurityHT1D","ElecPurityHT1D",oneDHT_-1,OneDHT_);
  ElecPurityMHT_ = new TH1Eff("ElecPurityMHT1D","ElecPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityMHTNJet_ = new TH2Eff("ElecPurityMHTNJet","ElecPurityMHTNJet",twoDMHT_fine_-1,TwoDMHT_fine_,twoDNJets_-1,TwoDNJets_);
  ElecPurityNJetsBTags_ = new TH2Eff("ElecPurityNJetsBTags","ElecPurityNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  ElecPurityMHTBTags_ = new TH2Eff("ElecPurityMHTBTags","ElecPurityMHTBTags",twoDMHT_-1,TwoDMHT_,twoDBJets_-1,TwoDBJets_);
  ElecPurityHTMHT_ = new TH2Eff("ElecPurityHTMHT","ElecPurityHTMHT",twoDHT_bin_-1,TwoDHT_bin_,twoDMHT_bin_-1,TwoDMHT_bin_);

  
  
  // acceptance
  //muon
  //1D
  MuAccBTag_ = new TH1Eff("MuAccBTag1D","MuAccBTag1D",oneDBJets_-1,OneDBJets_);
  MuAccNJets_ = new TH1Eff("MuAccNJets1D","MuAccNJets1D",oneDNJets_-1,OneDNJets_);
  MuAccHT_ = new TH1Eff("MuAccHT1D","MuAccHT1D",oneDHT_-1,OneDHT_);
  MuAccMHT_ = new TH1Eff("MuAccMHT1D","MuAccMHT1D",oneDMHT_-1,OneDMHT_);
  MuAccDTT_ = new TH1Eff("MuAccDTT1D","MuAccDTT1D",oneDDTT_-1,OneDDTT_);
  //2D
  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets","MuAccHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets","MuAccMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT","MuAccHTMHT",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets","MuAccBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0","MuAccMHTNJetsB0",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf","MuAccMHTNJetsB1_Inf",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccHTMHT_NJets26_ = new TH2Eff("MuAccHTMHT_NJets26","MuAccHTMHT_NJets26",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  
  MuAccHTMHT_NJets2_ = new TH2Eff("MuAccHTMHT_NJets2","MuAccHTMHT_NJets2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets3_ = new TH2Eff("MuAccHTMHT_NJets3","MuAccHTMHT_NJets3",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_ = new TH2Eff("MuAccHTMHT_NJets4","MuAccHTMHT_NJets4",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_ = new TH2Eff("MuAccHTMHT_NJets5","MuAccHTMHT_NJets5",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_ = new TH2Eff("MuAccHTMHT_NJets6","MuAccHTMHT_NJets6",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_ = new TH2Eff("MuAccHTMHT_NJets78","MuAccHTMHT_NJets78",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets9Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf","MuAccHTMHT_NJets9Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  
  MuAccHTMHT_NJets7Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf","MuAccHTMHT_NJets7Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0","MuAccHTMHTB0",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf","MuAccHTMHTB1_Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);

  MuAccHTMHT_NJets2_BTags0_ = new TH2Eff("MuAccHTMHT_NJets2_BTags0","MuAccHTMHT_NJets2_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets3_BTags0_ = new TH2Eff("MuAccHTMHT_NJets3_BTags0","MuAccHTMHT_NJets3_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags0_ = new TH2Eff("MuAccHTMHT_NJets4_BTags0","MuAccHTMHT_NJets4_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags0_ = new TH2Eff("MuAccHTMHT_NJets5_BTags0","MuAccHTMHT_NJets5_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags0_ = new TH2Eff("MuAccHTMHT_NJets6_BTags0","MuAccHTMHT_NJets6_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags0_ = new TH2Eff("MuAccHTMHT_NJets78_BTags0","MuAccHTMHT_NJets78_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags0","MuAccHTMHT_NJets9Inf_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags0_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags0","MuAccHTMHT_NJets7Inf_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  MuAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1Inf","MuAccHTMHT_NJets2_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1Inf","MuAccHTMHT_NJets3_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1Inf","MuAccHTMHT_NJets4_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1Inf","MuAccHTMHT_NJets5_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1Inf","MuAccHTMHT_NJets6_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1Inf","MuAccHTMHT_NJets78_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1Inf","MuAccHTMHT_NJets9Inf_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags1Inf","MuAccHTMHT_NJets7Inf_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  MuAccHTMHT_NJets2_BTags1_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1","MuAccHTMHT_NJets2_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets3_BTags1_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1","MuAccHTMHT_NJets3_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags1_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1","MuAccHTMHT_NJets4_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags1_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1","MuAccHTMHT_NJets5_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags1_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1","MuAccHTMHT_NJets6_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags1_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1","MuAccHTMHT_NJets78_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1","MuAccHTMHT_NJets9Inf_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags1_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags1","MuAccHTMHT_NJets7Inf_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  MuAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags2Inf","MuAccHTMHT_NJets2_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags2Inf","MuAccHTMHT_NJets3_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags2Inf","MuAccHTMHT_NJets4_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags2Inf","MuAccHTMHT_NJets5_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags2Inf","MuAccHTMHT_NJets6_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags2Inf","MuAccHTMHT_NJets78_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags2Inf","MuAccHTMHT_NJets9Inf_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags2Inf","MuAccHTMHT_NJets7Inf_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  MuAccHTMHT_NJets3_BTags2_ = new TH2Eff("MuAccHTMHT_NJets3_BTags2","MuAccHTMHT_NJets3_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags2_ = new TH2Eff("MuAccHTMHT_NJets4_BTags2","MuAccHTMHT_NJets4_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags2_ = new TH2Eff("MuAccHTMHT_NJets5_BTags2","MuAccHTMHT_NJets5_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags2_ = new TH2Eff("MuAccHTMHT_NJets6_BTags2","MuAccHTMHT_NJets6_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags2_ = new TH2Eff("MuAccHTMHT_NJets78_BTags2","MuAccHTMHT_NJets78_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags2_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags2","MuAccHTMHT_NJets9Inf_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags2_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags2","MuAccHTMHT_NJets7Inf_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  MuAccHTMHT_NJets3_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags3Inf","MuAccHTMHT_NJets3_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets4_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags3Inf","MuAccHTMHT_NJets4_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets5_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags3Inf","MuAccHTMHT_NJets5_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets6_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags3Inf","MuAccHTMHT_NJets6_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets78_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags3Inf","MuAccHTMHT_NJets78_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets9Inf_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags3Inf","MuAccHTMHT_NJets9Inf_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  MuAccHTMHT_NJets7Inf_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags3Inf","MuAccHTMHT_NJets7Inf_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  
  //elec
  //1D
  ElecAccBTag_ = new TH1Eff("ElecAccBTag1D","ElecAccBTag1D",oneDBJets_-1,OneDBJets_);
  ElecAccNJets_ = new TH1Eff("ElecAccNJets1D","ElecAccNJets1D",oneDNJets_-1,OneDNJets_);
  ElecAccHT_ = new TH1Eff("ElecAccHT1D","ElecAccHT1D",oneDHT_-1,OneDHT_);
  ElecAccMHT_ = new TH1Eff("ElecAccMHT1D","ElecAccMHT1D",oneDMHT_-1,OneDMHT_);
  ElecAccDTT_ = new TH1Eff("ElecAccDTT1D","ElecAccDTT1D",oneDDTT_-1,OneDDTT_);
  //2D
  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets","ElecAccHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets","ElecAccMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT","ElecAccHTMHT",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets","ElecAccBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0","ElecAccMHTNJetsB0",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf","ElecAccMHTNJetsB1_Inf",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccHTMHT_NJets26_ = new TH2Eff("ElecAccHTMHT_NJets26","ElecAccHTMHT_NJets26",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  
  ElecAccHTMHT_NJets2_ = new TH2Eff("ElecAccHTMHT_NJets2","ElecAccHTMHT_NJets2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets3_ = new TH2Eff("ElecAccHTMHT_NJets3","ElecAccHTMHT_NJets3",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_ = new TH2Eff("ElecAccHTMHT_NJets4","ElecAccHTMHT_NJets4",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_ = new TH2Eff("ElecAccHTMHT_NJets5","ElecAccHTMHT_NJets5",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_ = new TH2Eff("ElecAccHTMHT_NJets6","ElecAccHTMHT_NJets6",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_ = new TH2Eff("ElecAccHTMHT_NJets78","ElecAccHTMHT_NJets78",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf","ElecAccHTMHT_NJets9Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  
  ElecAccHTMHT_NJets7Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf","ElecAccHTMHT_NJets7Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0","ElecAccHTMHTB0",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf","ElecAccHTMHTB1_Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);

  ElecAccHTMHT_NJets2_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags0","ElecAccHTMHT_NJets2_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets3_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags0","ElecAccHTMHT_NJets3_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags0","ElecAccHTMHT_NJets4_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags0","ElecAccHTMHT_NJets5_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags0","ElecAccHTMHT_NJets6_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags0","ElecAccHTMHT_NJets78_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags0","ElecAccHTMHT_NJets9Inf_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags0","ElecAccHTMHT_NJets7Inf_BTags0",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  ElecAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1Inf","ElecAccHTMHT_NJets2_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1Inf","ElecAccHTMHT_NJets3_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1Inf","ElecAccHTMHT_NJets4_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1Inf","ElecAccHTMHT_NJets5_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1Inf","ElecAccHTMHT_NJets6_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1Inf","ElecAccHTMHT_NJets78_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1Inf","ElecAccHTMHT_NJets9Inf_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags1Inf","ElecAccHTMHT_NJets7Inf_BTags1Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  ElecAccHTMHT_NJets2_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1","ElecAccHTMHT_NJets2_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets3_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1","ElecAccHTMHT_NJets3_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1","ElecAccHTMHT_NJets4_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1","ElecAccHTMHT_NJets5_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1","ElecAccHTMHT_NJets6_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1","ElecAccHTMHT_NJets78_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1","ElecAccHTMHT_NJets9Inf_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags1","ElecAccHTMHT_NJets7Inf_BTags1",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  ElecAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags2Inf","ElecAccHTMHT_NJets2_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags2Inf","ElecAccHTMHT_NJets3_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags2Inf","ElecAccHTMHT_NJets4_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags2Inf","ElecAccHTMHT_NJets5_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags2Inf","ElecAccHTMHT_NJets6_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags2Inf","ElecAccHTMHT_NJets78_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags2Inf","ElecAccHTMHT_NJets9Inf_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags2Inf","ElecAccHTMHT_NJets7Inf_BTags2Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  ElecAccHTMHT_NJets3_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags2","ElecAccHTMHT_NJets3_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags2","ElecAccHTMHT_NJets4_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags2","ElecAccHTMHT_NJets5_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags2","ElecAccHTMHT_NJets6_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags2","ElecAccHTMHT_NJets78_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags2","ElecAccHTMHT_NJets9Inf_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags2","ElecAccHTMHT_NJets7Inf_BTags2",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  ElecAccHTMHT_NJets3_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags3Inf","ElecAccHTMHT_NJets3_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets4_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags3Inf","ElecAccHTMHT_NJets4_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets5_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags3Inf","ElecAccHTMHT_NJets5_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets6_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags3Inf","ElecAccHTMHT_NJets6_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets78_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags3Inf","ElecAccHTMHT_NJets78_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets9Inf_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags3Inf","ElecAccHTMHT_NJets9Inf_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);
  ElecAccHTMHT_NJets7Inf_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags3Inf","ElecAccHTMHT_NJets7Inf_BTags3Inf",threeDHT_fine_-1,ThreeDHT_fine_, threeDMHT_coarse_-1,ThreeDMHT_coarse_);

  // reconstruction
  //muon
  //1D
  MuRecoBTag_ = new TH1Eff("MuRecoBTag1D","MuRecoBTag1D",oneDBJets_-1,OneDBJets_);
  MuRecoNJets_ = new TH1Eff("MuRecoNJets1D","MuRecoNJets1D",oneDNJets_-1,OneDNJets_);
  MuRecoHT_ = new TH1Eff("MuRecoHT1D","MuRecoHT1D",oneDHT_-1,OneDHT_);
  MuRecoMHT_ = new TH1Eff("MuRecoMHT1D","MuRecoMHT1D",oneDMHT_-1,OneDMHT_);
 
  //elec
  //1D
  ElecRecoBTag_ = new TH1Eff("ElecRecoBTag1D","ElecRecoBTag1D",oneDBJets_-1,OneDBJets_);
  ElecRecoNJets_ = new TH1Eff("ElecRecoNJets1D","ElecRecoNJets1D",oneDNJets_-1,OneDNJets_);
  ElecRecoHT_ = new TH1Eff("ElecRecoHT1D","ElecRecoHT1D",oneDHT_-1,OneDHT_);
  ElecRecoMHT_ = new TH1Eff("ElecRecoMHT1D","ElecRecoMHT1D",oneDMHT_-1,OneDMHT_);

  
  // isolation
  //muon
  //1D
  MuIsoBTag_ = new TH1Eff("MuIsoBTag1D","MuIsoBTag1D",oneDBJets_-1,OneDBJets_);
  MuIsoNJets_ = new TH1Eff("MuIsoNJets1D","MuIsoNJets1D",oneDNJets_-1,OneDNJets_);
  MuIsoHT_ = new TH1Eff("MuIsoHT1D","MuIsoHT1D",oneDHT_-1,OneDHT_);
  MuIsoMHT_ = new TH1Eff("MuIsoMHT1D","MuIsoMHT1D",oneDMHT_-1,OneDMHT_);
  
  //elec
  //1D
  ElecIsoBTag_ = new TH1Eff("ElecIsoBTag1D","ElecIsoBTag1D",oneDBJets_-1,OneDBJets_);
  ElecIsoNJets_ = new TH1Eff("ElecIsoNJets1D","ElecIsoNJets1D",oneDNJets_-1,OneDNJets_);
  ElecIsoHT_ = new TH1Eff("ElecIsoHT1D","ElecIsoHT1D",oneDHT_-1,OneDHT_);
  ElecIsoMHT_ = new TH1Eff("ElecIsoMHT1D","ElecIsoMHT1D",oneDMHT_-1,OneDMHT_);
  
  // mtw
  //muon
  //1D
  MuMTWBTag_ = new TH1Eff("MuMTWBTag1D","MuMTWBTag1D",oneDBJets_-1,OneDBJets_);
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D","MuMTWNJets1D",oneDNJets_-1,OneDNJets_);
  MuMTWHT_ = new TH1Eff("MuMTWHT1D","MuMTWHT1D",oneDHT_-1,OneDHT_);
  MuMTWMHT_ = new TH1Eff("MuMTWMHT1D","MuMTWMHT1D",oneDMHT_-1,OneDMHT_);

  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets","MuMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  MuMTWMHTNJets_ = new TH2Eff("MuMTWMHTNJets","MuMTWMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuMTWHTMHT_ = new TH2Eff("MuMTWHTMHT","MuMTWHTMHT",twoDHT_-1,TwoDHT_,twoDMHT_-1,TwoDMHT_);
  MuMTWHTMHT_NJets24_ = new TH2Eff("MuMTWHTMHT_NJets24","MuMTWHTMHT_NJets24",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets56_ = new TH2Eff("MuMTWHTMHT_NJets56","MuMTWHTMHT_NJets56",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets7Inf_ = new TH2Eff("MuMTWHTMHT_NJets7Inf","MuMTWHTMHT_NJets7Inf",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);

  MuMTWHTMHT_NJets2_ = new TH2Eff("MuMTWHTMHT_NJets2","MuMTWHTMHT_NJets2",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets3_ = new TH2Eff("MuMTWHTMHT_NJets3","MuMTWHTMHT_NJets3",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets4_ = new TH2Eff("MuMTWHTMHT_NJets4","MuMTWHTMHT_NJets4",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets5_ = new TH2Eff("MuMTWHTMHT_NJets5","MuMTWHTMHT_NJets5",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets6_ = new TH2Eff("MuMTWHTMHT_NJets6","MuMTWHTMHT_NJets6",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets78_ = new TH2Eff("MuMTWHTMHT_NJets78","MuMTWHTMHT_NJets78",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuMTWHTMHT_NJets9Inf_ = new TH2Eff("MuMTWHTMHT_NJets9Inf","MuMTWHTMHT_NJets9Inf",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  
  //electron
  //1D
  ElecMTWBTag_ = new TH1Eff("ElecMTWBTag1D","ElecMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D","ElecMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecMTWHT_ = new TH1Eff("ElecMTWHT1D","ElecMTWHT1D",oneDHT_-1,OneDHT_);
  ElecMTWMHT_ = new TH1Eff("ElecMTWMHT1D","ElecMTWMHT1D",oneDMHT_-1,OneDMHT_);

  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets","ElecMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  ElecMTWMHTNJets_ = new TH2Eff("ElecMTWMHTNJets","ElecMTWMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecMTWHTMHT_ = new TH2Eff("ElecMTWHTMHT","ElecMTWHTMHT",twoDHT_-1,TwoDHT_,twoDMHT_-1,TwoDMHT_);
  ElecMTWHTMHT_NJets24_ = new TH2Eff("ElecMTWHTMHT_NJets24","ElecMTWHTMHT_NJets24",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets56_ = new TH2Eff("ElecMTWHTMHT_NJets56","ElecMTWHTMHT_NJets56",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets7Inf_ = new TH2Eff("ElecMTWHTMHT_NJets7Inf","ElecMTWHTMHT_NJets7Inf",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);

  ElecMTWHTMHT_NJets2_ = new TH2Eff("ElecMTWHTMHT_NJets2","ElecMTWHTMHT_NJets2",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets3_ = new TH2Eff("ElecMTWHTMHT_NJets3","ElecMTWHTMHT_NJets3",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets4_ = new TH2Eff("ElecMTWHTMHT_NJets4","ElecMTWHTMHT_NJets4",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets5_ = new TH2Eff("ElecMTWHTMHT_NJets5","ElecMTWHTMHT_NJets5",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets6_ = new TH2Eff("ElecMTWHTMHT_NJets6","ElecMTWHTMHT_NJets6",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets78_ = new TH2Eff("ElecMTWHTMHT_NJets78","ElecMTWHTMHT_NJets78",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecMTWHTMHT_NJets9Inf_ = new TH2Eff("ElecMTWHTMHT_NJets9Inf","ElecMTWHTMHT_NJets9Inf",threeDHT_bin_-1,ThreeDHT_bin_,threeDMHT_bin_-1,ThreeDMHT_bin_);

 
  // di lep  
  //muon
  //1D
  MuDiLepBTag_ = new TH1Eff("MuDiLepBTag1D","MuDiLepBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepNJets_ = new TH1Eff("MuDiLepNJets1D","MuDiLepNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepHT_ = new TH1Eff("MuDiLepHT1D","MuDiLepHT1D",oneDHT_-1,OneDHT_);
  MuDiLepMHT_ = new TH1Eff("MuDiLepMHT1D","MuDiLepMHT1D",oneDMHT_-1,OneDMHT_);
 
  //electron
  //1D
  ElecDiLepBTag_ = new TH1Eff("ElecDiLepBTag1D","ElecDiLepBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepNJets_ = new TH1Eff("ElecDiLepNJets1D","ElecDiLepNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepHT_ = new TH1Eff("ElecDiLepHT1D","ElecDiLepHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepMHT_ = new TH1Eff("ElecDiLepMHT1D","ElecDiLepMHT1D",oneDMHT_-1,OneDMHT_);
  
  // mtw
  //muon
  //1D
  MuDiLepEffBTag_ = new TH1Eff("MuDiLepEffBTag1D","MuDiLepEffBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepEffNJets_ = new TH1Eff("MuDiLepEffNJets1D","MuDiLepEffNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepEffHT_ = new TH1Eff("MuDiLepEffHT1D","MuDiLepEffHT1D",oneDHT_-1,OneDHT_);
  MuDiLepEffMHT_ = new TH1Eff("MuDiLepEffMHT1D","MuDiLepEffMHT1D",oneDMHT_-1,OneDMHT_);
  MuDiLepEffNJetsBTags_ = new TH2Eff("MuDiLepEffNJetsBTags","MuDiLepEffNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  
  //electron
  //1D
  ElecDiLepEffBTag_ = new TH1Eff("ElecDiLepEffBTag1D","ElecDiLepEffBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepEffNJets_ = new TH1Eff("ElecDiLepEffNJets1D","ElecDiLepEffNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepEffHT_ = new TH1Eff("ElecDiLepEffHT1D","ElecDiLepEffHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepEffMHT_ = new TH1Eff("ElecDiLepEffMHT1D","ElecDiLepEffMHT1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepEffNJetsBTags_ = new TH2Eff("ElecDiLepEffNJetsBTags","ElecDiLepEffNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);
  
  
  // di lep 
  //muon
  //1D
  MuDiLepContributionBTag_ = new TH1Eff("MuDiLepContributionBTag1D","MuDiLepContributionBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepContributionNJets_ = new TH1Eff("MuDiLepContributionNJets1D","MuDiLepContributionNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepContributionHT_ = new TH1Eff("MuDiLepContributionHT1D","MuDiLepContributionHT1D",oneDHT_-1,OneDHT_);
  MuDiLepContributionMHT_ = new TH1Eff("MuDiLepContributionMHT1D","MuDiLepContributionMHT1D",oneDMHT_-1,OneDMHT_);

  MuDiLepFractionBTag_ = new TH1Eff("MuDiLepFractionBTag1D","MuDiLepFractionBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepFractionNJets_ = new TH1Eff("MuDiLepFractionNJets1D","MuDiLepFractionNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepFractionHT_ = new TH1Eff("MuDiLepFractionHT1D","MuDiLepFractionHT1D",oneDHT_-1,OneDHT_);
  MuDiLepFractionMHT_ = new TH1Eff("MuDiLepFractionMHT1D","MuDiLepFractionMHT1D",oneDMHT_-1,OneDMHT_);
  
  //electron
  //1D
  ElecDiLepContributionBTag_ = new TH1Eff("ElecDiLepContributionBTag1D","ElecDiLepContributionBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepContributionNJets_ = new TH1Eff("ElecDiLepContributionNJets1D","ElecDiLepContributionNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepContributionHT_ = new TH1Eff("ElecDiLepContributionHT1D","ElecDiLepContributionHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepContributionMHT_ = new TH1Eff("ElecDiLepContributionMHT1D","ElecDiLepContributionMHT1D",oneDMHT_-1,OneDMHT_);

  ElecDiLepFractionBTag_ = new TH1Eff("ElecDiLepFractionBTag1D","ElecDiLepFractionBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepFractionNJets_ = new TH1Eff("ElecDiLepFractionNJets1D","ElecDiLepFractionNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepFractionHT_ = new TH1Eff("ElecDiLepFractionHT1D","ElecDiLepFractionHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepFractionMHT_ = new TH1Eff("ElecDiLepFractionMHT1D","ElecDiLepFractionMHT1D",oneDMHT_-1,OneDMHT_);
  
  //muon
  //1D
  MuDiLepCRBTag_ = new TH1Eff("MuDiLepCRBTag1D","MuDiLepCRBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepCRNJets_ = new TH1Eff("MuDiLepCRNJets1D","MuDiLepCRNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepCRHT_ = new TH1Eff("MuDiLepCRHT1D","MuDiLepCRHT1D",oneDHT_-1,OneDHT_);
  MuDiLepCRMHT_ = new TH1Eff("MuDiLepCRMHT1D","MuDiLepCRMHT1D",oneDMHT_-1,OneDMHT_);
  MuDiLepCRMHTNJets_ = new TH2Eff("MuDiLepCRMHTNJets","MuDiLepCRMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuDiLepCRNJetsBTags_ = new TH2Eff("MuDiLepCRNJetsBTags","MuDiLepCRNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  //electron
  //1D
  ElecDiLepCRBTag_ = new TH1Eff("ElecDiLepCRBTag1D","ElecDiLepCRBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepCRNJets_ = new TH1Eff("ElecDiLepCRNJets1D","ElecDiLepCRNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepCRHT_ = new TH1Eff("ElecDiLepCRHT1D","ElecDiLepCRHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepCRMHT_ = new TH1Eff("ElecDiLepCRMHT1D","ElecDiLepCRMHT1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepCRMHTNJets_ = new TH2Eff("ElecDiLepCRMHTNJets","ElecDiLepCRMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecDiLepCRNJetsBTags_ = new TH2Eff("ElecDiLepCRNJetsBTags","ElecDiLepCRNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);


  //muon
  //1D
  MuDiLepSRBTag_ = new TH1Eff("MuDiLepSRBTag1D","MuDiLepSRBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepSRNJets_ = new TH1Eff("MuDiLepSRNJets1D","MuDiLepSRNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepSRHT_ = new TH1Eff("MuDiLepSRHT1D","MuDiLepSRHT1D",oneDHT_-1,OneDHT_);
  MuDiLepSRMHT_ = new TH1Eff("MuDiLepSRMHT1D","MuDiLepSRMHT1D",oneDMHT_-1,OneDMHT_);
  MuDiLepSRMHTNJets_ = new TH2Eff("MuDiLepSRMHTNJets","MuDiLepSRMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuDiLepSRNJetsBTags_ = new TH2Eff("MuDiLepSRNJetsBTags","MuDiLepSRNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  //electron
  //1D
  ElecDiLepSRBTag_ = new TH1Eff("ElecDiLepSRBTag1D","ElecDiLepSRBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepSRNJets_ = new TH1Eff("ElecDiLepSRNJets1D","ElecDiLepSRNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepSRHT_ = new TH1Eff("ElecDiLepSRHT1D","ElecDiLepSRHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepSRMHT_ = new TH1Eff("ElecDiLepSRMHT1D","ElecDiLepSRMHT1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepSRMHTNJets_ = new TH2Eff("ElecDiLepSRMHTNJets","ElecDiLepSRMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecDiLepSRNJetsBTags_ = new TH2Eff("ElecDiLepSRNJetsBTags","ElecDiLepSRNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  //muon
  //1D
  MuDiLepSRBTagEff_ = new TH1Eff("MuDiLepSRBTagEff1D","MuDiLepSRBTagEff1D",oneDBJets_-1,OneDBJets_);
  MuDiLepSRNJetsEff_ = new TH1Eff("MuDiLepSRNJetsEff1D","MuDiLepSRNJetsEff1D",oneDNJets_-1,OneDNJets_);
  MuDiLepSRHTEff_ = new TH1Eff("MuDiLepSRHTEff1D","MuDiLepSRHTEff1D",oneDHT_-1,OneDHT_);
  MuDiLepSRMHTEff_ = new TH1Eff("MuDiLepSRMHTEff1D","MuDiLepSRMHTEff1D",oneDMHT_-1,OneDMHT_);
  MuDiLepSRMHTNJetsEff_ = new TH2Eff("MuDiLepSRMHTNJetsEff","MuDiLepSRMHTNJetsEff",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuDiLepSRNJetsBTagsEff_ = new TH2Eff("MuDiLepSRNJetsBTagsEff","MuDiLepSRNJetsBTagsEff",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  //electron
  //1D
  ElecDiLepSRBTagEff_ = new TH1Eff("ElecDiLepSRBTagEff1D","ElecDiLepSRBTagEff1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepSRNJetsEff_ = new TH1Eff("ElecDiLepSRNJetsEff1D","ElecDiLepSRNJetsEff1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepSRHTEff_ = new TH1Eff("ElecDiLepSRHTEff1D","ElecDiLepSRHTEff1D",oneDHT_-1,OneDHT_);
  ElecDiLepSRMHTEff_ = new TH1Eff("ElecDiLepSRMHTEff1D","ElecDiLepSRMHTEff1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepSRMHTNJetsEff_ = new TH2Eff("ElecDiLepSRMHTNJetsEff","ElecDiLepSRMHTNJetsEff",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecDiLepSRNJetsBTagsEff_ = new TH2Eff("ElecDiLepSRNJetsBTagsEff","ElecDiLepSRNJetsBTagsEff",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);



  //muon
  //1D
  MuDiLepSRwoVetoBTag_ = new TH1Eff("MuDiLepSRwoVetoBTag1D","MuDiLepSRwoVetoBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepSRwoVetoNJets_ = new TH1Eff("MuDiLepSRwoVetoNJets1D","MuDiLepSRwoVetoNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepSRwoVetoHT_ = new TH1Eff("MuDiLepSRwoVetoHT1D","MuDiLepSRwoVetoHT1D",oneDHT_-1,OneDHT_);
  MuDiLepSRwoVetoMHT_ = new TH1Eff("MuDiLepSRwoVetoMHT1D","MuDiLepSRwoVetoMHT1D",oneDMHT_-1,OneDMHT_);
  MuDiLepSRwoVetoMHTNJets_ = new TH2Eff("MuDiLepSRwoVetoMHTNJets","MuDiLepSRwoVetoMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuDiLepSRwoVetoNJetsBTags_ = new TH2Eff("MuDiLepSRwoVetoNJetsBTags","MuDiLepSRwoVetoNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  //electron
  //1D
  ElecDiLepSRwoVetoBTag_ = new TH1Eff("ElecDiLepSRwoVetoBTag1D","ElecDiLepSRwoVetoBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepSRwoVetoNJets_ = new TH1Eff("ElecDiLepSRwoVetoNJets1D","ElecDiLepSRwoVetoNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepSRwoVetoHT_ = new TH1Eff("ElecDiLepSRwoVetoHT1D","ElecDiLepSRwoVetoHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepSRwoVetoMHT_ = new TH1Eff("ElecDiLepSRwoVetoMHT1D","ElecDiLepSRwoVetoMHT1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepSRwoVetoMHTNJets_ = new TH2Eff("ElecDiLepSRwoVetoMHTNJets","ElecDiLepSRwoVetoMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecDiLepSRwoVetoNJetsBTags_ = new TH2Eff("ElecDiLepSRwoVetoNJetsBTags","ElecDiLepSRwoVetoNJetsBTags",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  //muon
  //1D
  MuDiLepSRwoVetoBTagEff_ = new TH1Eff("MuDiLepSRwoVetoBTagEff1D","MuDiLepSRwoVetoBTagEff1D",oneDBJets_-1,OneDBJets_);
  MuDiLepSRwoVetoNJetsEff_ = new TH1Eff("MuDiLepSRwoVetoNJetsEff1D","MuDiLepSRwoVetoNJetsEff1D",oneDNJets_-1,OneDNJets_);
  MuDiLepSRwoVetoHTEff_ = new TH1Eff("MuDiLepSRwoVetoHTEff1D","MuDiLepSRwoVetoHTEff1D",oneDHT_-1,OneDHT_);
  MuDiLepSRwoVetoMHTEff_ = new TH1Eff("MuDiLepSRwoVetoMHTEff1D","MuDiLepSRwoVetoMHTEff1D",oneDMHT_-1,OneDMHT_);
  MuDiLepSRwoVetoMHTNJetsEff_ = new TH2Eff("MuDiLepSRwoVetoMHTNJetsEff","MuDiLepSRwoVetoMHTNJetsEff",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  MuDiLepSRwoVetoNJetsBTagsEff_ = new TH2Eff("MuDiLepSRwoVetoNJetsBTagsEff","MuDiLepSRwoVetoNJetsBTagsEff",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  //electron
  //Eff1D
  ElecDiLepSRwoVetoBTagEff_ = new TH1Eff("ElecDiLepSRwoVetoBTagEff1D","ElecDiLepSRwoVetoBTagEff1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepSRwoVetoNJetsEff_ = new TH1Eff("ElecDiLepSRwoVetoNJetsEff1D","ElecDiLepSRwoVetoNJetsEff1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepSRwoVetoHTEff_ = new TH1Eff("ElecDiLepSRwoVetoHTEff1D","ElecDiLepSRwoVetoHTEff1D",oneDHT_-1,OneDHT_);
  ElecDiLepSRwoVetoMHTEff_ = new TH1Eff("ElecDiLepSRwoVetoMHTEff1D","ElecDiLepSRwoVetoMHTEff1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepSRwoVetoMHTNJetsEff_ = new TH2Eff("ElecDiLepSRwoVetoMHTNJetsEff","ElecDiLepSRwoVetoMHTNJetsEff",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  ElecDiLepSRwoVetoNJetsBTagsEff_ = new TH2Eff("ElecDiLepSRwoVetoNJetsBTagsEff","ElecDiLepSRwoVetoNJetsBTagsEff",twoDNJets_-1,TwoDNJets_,twoDBJets_-1,TwoDBJets_);

  
  // acitivity and pt
  // mu 
  MuPurityOldPT_ = new TH1Eff("MuPurityOldPT","MuPurityOldPT",oneDPT_-1,OneDPT_);
  MuPurityOldActivity_ = new TH1Eff("MuPurityOldActivity","MuPurityOldActivity",oneDActivity_-1,OneDActivity_);
  MuAccPT_ = new TH1Eff("MuAccPT","MuAccPT",oneDPT_-1,OneDPT_);
  MuAccActivity_ = new TH1Eff("MuAccActivity","MuAccActivity",oneDActivity_-1,OneDActivity_);
  MuRecoPT_ = new TH1Eff("MuRecoPT","MuRecoPT",oneDPT_-1,OneDPT_);
  MuRecoActivity_ = new TH1Eff("MuRecoActivity","MuRecoActivity",oneDActivity_-1,OneDActivity_);
  MuIsoPT_ = new TH1Eff("MuIsoPT","MuIsoPT",oneDPT_-1,OneDPT_);
  MuIsoActivity_ = new TH1Eff("MuIsoActivity","MuIsoActivity",oneDActivity_-1,OneDActivity_);
  MuMTWPT_ = new TH1Eff("MuMTWPT","MuMTWPT",oneDPT_-1,OneDPT_);
  MuMTWActivity_ = new TH1Eff("MuMTWActivity","MuMTWActivity",oneDActivity_-1,OneDActivity_);
  MuDiLepPT_ = new TH1Eff("MuDiLepPT","MuDiLepPT",oneDPT_-1,OneDPT_);
  MuDiLepActivity_ = new TH1Eff("MuDiLepActivity","MuDiLepActivity",oneDActivity_-1,OneDActivity_);
  MuDiLepEffPT_ = new TH1Eff("MuDiLepEffPT","MuDiLepEffPT",oneDPT_-1,OneDPT_);
  MuDiLepEffActivity_ = new TH1Eff("MuDiLepEffActivity","MuDiLepEffActivity",oneDActivity_-1,OneDActivity_);
  
  // elec  
  ElecPurityOldPT_ = new TH1Eff("ElecPurityOldPT","ElecPurityOldPT",oneDPT_-1,OneDPT_);
  ElecPurityOldActivity_ = new TH1Eff("ElecPurityOldActivity","ElecPurityOldActivity",oneDActivity_-1,OneDActivity_);
  ElecAccPT_ = new TH1Eff("ElecAccPT","ElecAccPT",oneDPT_-1,OneDPT_);
  ElecAccActivity_ = new TH1Eff("ElecAccActivity","ElecAccActivity",oneDActivity_-1,OneDActivity_);
  ElecRecoPT_ = new TH1Eff("ElecRecoPT","ElecRecoPT",oneDPT_-1,OneDPT_);
  ElecRecoActivity_ = new TH1Eff("ElecRecoActivity","ElecRecoActivity",oneDActivity_-1,OneDActivity_);
  ElecIsoPT_ = new TH1Eff("ElecIsoPT","ElecIsoPT",oneDPT_-1,OneDPT_);
  ElecIsoActivity_ = new TH1Eff("ElecIsoActivity","ElecIsoActivity",oneDActivity_-1,OneDActivity_);
  ElecMTWPT_ = new TH1Eff("ElecMTWPT","ElecMTWPT",oneDPT_-1,OneDPT_);
  ElecMTWActivity_ = new TH1Eff("ElecMTWActivity","ElecMTWActivity",oneDActivity_-1,OneDActivity_);
  ElecDiLepPT_ = new TH1Eff("ElecDiLepPT","ElecDiLepPT",oneDPT_-1,OneDPT_);
  ElecDiLepActivity_ = new TH1Eff("ElecDiLepActivity","ElecDiLepActivity",oneDActivity_-1,OneDActivity_);
  ElecDiLepEffPT_ = new TH1Eff("ElecDiLepEffPT","ElecDiLepEffPT",oneDPT_-1,OneDPT_);
  ElecDiLepEffActivity_ = new TH1Eff("ElecDiLepEffActivity","ElecDiLepEffActivity",oneDActivity_-1,OneDActivity_);
  
  // 2D
  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT","MuIsoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT","ElecIsoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuRecoActivityPT_ = new TH2Eff("MuRecoActivityPT","MuRecoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecRecoActivityPT_ = new TH2Eff("ElecRecoActivityPT","ElecRecoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuRecoPTEta_ = new TH2Eff("MuRecoPTEta","MuRecoPTEta", twoDPT_-1,TwoDPT_, twoDEtaMu_-1,TwoDEtaMu_);
  ElecRecoPTEta_ = new TH2Eff("ElecRecoPTEta","ElecRecoPTEta", twoDPT_-1,TwoDPT_, twoDEtaElec_-1,TwoDEtaElec_);
  MuIsoPTEta_ = new TH2Eff("MuIsoPTEta","MuIsoPTEta", twoDPT_-1,TwoDPT_, twoDEtaMu_-1,TwoDEtaMu_);
  ElecIsoPTEta_ = new TH2Eff("ElecIsoPTEta","ElecIsoPTEta", twoDPT_-1,TwoDPT_, twoDEtaElec_-1,TwoDEtaElec_);

  MuRecoPTEtaBTags0_ = new TH2Eff("MuRecoPTEtaBTags0","MuRecoPTEtaBTags0", twoDPT_-1,TwoDPT_, twoDEtaMu_-1,TwoDEtaMu_);
  ElecRecoPTEtaBTags0_ = new TH2Eff("ElecRecoPTEtaBTags0","ElecRecoPTEtaBTags0", twoDPT_-1,TwoDPT_, twoDEtaElec_-1,TwoDEtaElec_);
  MuRecoPTEtaBTags1Inf_ = new TH2Eff("MuRecoPTEtaBTags1Inf","MuRecoPTEtaBTags1Inf", twoDPT_-1,TwoDPT_, twoDEtaMu_-1,TwoDEtaMu_);
  ElecRecoPTEtaBTags1Inf_ = new TH2Eff("ElecRecoPTEtaBTags1Inf","ElecRecoPTEtaBTags1Inf", twoDPT_-1,TwoDPT_, twoDEtaElec_-1,TwoDEtaElec_);
  MuIsoActivityPTBTags0_ = new TH2Eff("MuIsoActivityPTBTags0","MuIsoActivityPTBTags0", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPTBTags0_ = new TH2Eff("ElecIsoActivityPTBTags0","ElecIsoActivityPTBTags0", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuIsoActivityPTBTags1Inf_ = new TH2Eff("MuIsoActivityPTBTags1Inf","MuIsoActivityPTBTags1Inf", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPTBTags1Inf_ = new TH2Eff("ElecIsoActivityPTBTags1Inf","ElecIsoActivityPTBTags1Inf", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);

  // NEW
  MuRecoActivityPTBarrel_ = new TH2Eff("MuRecoActivityPTBarrel","MuRecoActivityPTBarrel", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuIsoActivityPTBarrel_ = new TH2Eff("MuIsoActivityPTBarrel","MuIsoActivityPTBarrel", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecRecoActivityPTBarrel_ = new TH2Eff("ElecRecoActivityPTBarrel","ElecRecoActivityPTBarrel", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPTBarrel_ = new TH2Eff("ElecIsoActivityPTBarrel","ElecIsoActivityPTBarrel", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);

  MuRecoActivityPTDisk_ = new TH2Eff("MuRecoActivityPTDisk","MuRecoActivityPTDisk", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuIsoActivityPTDisk_ = new TH2Eff("MuIsoActivityPTDisk","MuIsoActivityPTDisk", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecRecoActivityPTDisk_ = new TH2Eff("ElecRecoActivityPTDisk","ElecRecoActivityPTDisk", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPTDisk_ = new TH2Eff("ElecIsoActivityPTDisk","ElecIsoActivityPTDisk", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  
  // mtw 2d
  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity","MuMTWPTActivity",twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecMTWPTActivity_ = new TH2Eff("ElecMTWPTActivity","ElecMTWPTActivity",twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
    
  //1D
  ExpectationReductionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionIsoTrackBTagEff","ExpectationReductionIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff","ExpectationReductionIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionIsoTrackHTEff","ExpectationReductionIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionIsoTrackMHTEff","ExpectationReductionIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionIsoTrackPTEff","ExpectationReductionIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionIsoTrackActivityEff","ExpectationReductionIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  IsoTrackReductionHTNJets_ = new TH2Eff("IsoTrackReductionHTNJets","IsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionHTMHT_NJets24_ = new TH2Eff("IsoTrackReductionHTMHT_NJets24","IsoTrackReductionHTMHT_NJets24", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets56_ = new TH2Eff("IsoTrackReductionHTMHT_NJets56","IsoTrackReductionHTMHT_NJets56", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets7Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJets7Inf","IsoTrackReductionHTMHT_NJets7Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets2_ = new TH2Eff("IsoTrackReductionHTMHT_NJets2","IsoTrackReductionHTMHT_NJets2", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets3_ = new TH2Eff("IsoTrackReductionHTMHT_NJets3","IsoTrackReductionHTMHT_NJets3", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets4_ = new TH2Eff("IsoTrackReductionHTMHT_NJets4","IsoTrackReductionHTMHT_NJets4", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets5_ = new TH2Eff("IsoTrackReductionHTMHT_NJets5","IsoTrackReductionHTMHT_NJets5", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets6_ = new TH2Eff("IsoTrackReductionHTMHT_NJets6","IsoTrackReductionHTMHT_NJets6", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets78_ = new TH2Eff("IsoTrackReductionHTMHT_NJets78","IsoTrackReductionHTMHT_NJets78", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionHTMHT_NJets9Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJets9Inf","IsoTrackReductionHTMHT_NJets9Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  IsoTrackReductionMHTNJets_ = new TH2Eff("IsoTrackReductionMHTNJets","IsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionBTagNJets_ = new TH2Eff("IsoTrackReductionBTagNJets","IsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionPTActivity_ = new TH2Eff("IsoTrackReductionPTActivity","IsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);

  IsoTrackReductionHTMHT_NJets24_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJets24_BTags0","IsoTrackReductionHTMHT_NJets24_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets56_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJets56_BTags0","IsoTrackReductionHTMHT_NJets56_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets7Inf_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJets7Inf_BTags0","IsoTrackReductionHTMHT_NJets7Inf_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets24_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJets24_BTags1Inf","IsoTrackReductionHTMHT_NJets24_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets56_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJets56_BTags1Inf","IsoTrackReductionHTMHT_NJets56_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf","IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  
  // muon iso track
  //1D
  ExpectationReductionMuIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionMuIsoTrackBTagEff","ExpectationReductionMuIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionMuIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionMuIsoTrackNJetsEff","ExpectationReductionMuIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionMuIsoTrackHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackHTEff","ExpectationReductionMuIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionMuIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackMHTEff","ExpectationReductionMuIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionMuIsoTrackPTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackPTEff","ExpectationReductionMuIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionMuIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionMuIsoTrackActivityEff","ExpectationReductionMuIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  MuIsoTrackReductionHTNJets_ = new TH2Eff("MuIsoTrackReductionHTNJets","MuIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionMHTNJets_ = new TH2Eff("MuIsoTrackReductionMHTNJets","MuIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionBTagNJets_ = new TH2Eff("MuIsoTrackReductionBTagNJets","MuIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionPTActivity_ = new TH2Eff("MuIsoTrackReductionPTActivity","MuIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  
  MuIsoTrackReductionHTMHT_NJets24_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets24","MuIsoTrackReductionHTMHT_NJets24", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets56_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets56","MuIsoTrackReductionHTMHT_NJets56", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets7Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets7Inf","MuIsoTrackReductionHTMHT_NJets7Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets2_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets2","MuIsoTrackReductionHTMHT_NJets2", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets3_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets3","MuIsoTrackReductionHTMHT_NJets3", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets4_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets4","MuIsoTrackReductionHTMHT_NJets4", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets5_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets5","MuIsoTrackReductionHTMHT_NJets5", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets6_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets6","MuIsoTrackReductionHTMHT_NJets6", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets78_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets78","MuIsoTrackReductionHTMHT_NJets78", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  MuIsoTrackReductionHTMHT_NJets9Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets9Inf","MuIsoTrackReductionHTMHT_NJets9Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);

  MuIsoTrackReductionHTMHT_NJets24_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets24_BTags0","MuIsoTrackReductionHTMHT_NJets24_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJets56_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets56_BTags0","MuIsoTrackReductionHTMHT_NJets56_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJets7Inf_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets7Inf_BTags0","MuIsoTrackReductionHTMHT_NJets7Inf_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJets24_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets24_BTags1Inf","MuIsoTrackReductionHTMHT_NJets24_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJets56_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets56_BTags1Inf","MuIsoTrackReductionHTMHT_NJets56_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf","MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  // elec iso track
  //1D
  ExpectationReductionElecIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionElecIsoTrackBTagEff","ExpectationReductionElecIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionElecIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionElecIsoTrackNJetsEff","ExpectationReductionElecIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionElecIsoTrackHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackHTEff","ExpectationReductionElecIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionElecIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackMHTEff","ExpectationReductionElecIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionElecIsoTrackPTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackPTEff","ExpectationReductionElecIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionElecIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionElecIsoTrackActivityEff","ExpectationReductionElecIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  ElecIsoTrackReductionHTNJets_ = new TH2Eff("ElecIsoTrackReductionHTNJets","ElecIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionMHTNJets_ = new TH2Eff("ElecIsoTrackReductionMHTNJets","ElecIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionBTagNJets_ = new TH2Eff("ElecIsoTrackReductionBTagNJets","ElecIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionPTActivity_ = new TH2Eff("ElecIsoTrackReductionPTActivity","ElecIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  
  ElecIsoTrackReductionHTMHT_NJets24_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets24","ElecIsoTrackReductionHTMHT_NJets24", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets56_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets56","ElecIsoTrackReductionHTMHT_NJets56", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets7Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets7Inf","ElecIsoTrackReductionHTMHT_NJets7Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets2_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets2","ElecIsoTrackReductionHTMHT_NJets2", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets3_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets3","ElecIsoTrackReductionHTMHT_NJets3", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets4_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets4","ElecIsoTrackReductionHTMHT_NJets4", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets5_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets5","ElecIsoTrackReductionHTMHT_NJets5", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets6_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets6","ElecIsoTrackReductionHTMHT_NJets6", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets78_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets78","ElecIsoTrackReductionHTMHT_NJets78", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  ElecIsoTrackReductionHTMHT_NJets9Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets9Inf","ElecIsoTrackReductionHTMHT_NJets9Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);

  ElecIsoTrackReductionHTMHT_NJets24_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets24_BTags0","ElecIsoTrackReductionHTMHT_NJets24_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJets56_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets56_BTags0","ElecIsoTrackReductionHTMHT_NJets56_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0","ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf","ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf","ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf","ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  // pion iso track
  //1D
  ExpectationReductionPionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionPionIsoTrackBTagEff","ExpectationReductionPionIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionPionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionPionIsoTrackNJetsEff","ExpectationReductionPionIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionPionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackHTEff","ExpectationReductionPionIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionPionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackMHTEff","ExpectationReductionPionIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionPionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackPTEff","ExpectationReductionPionIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionPionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionPionIsoTrackActivityEff","ExpectationReductionPionIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  PionIsoTrackReductionHTNJets_ = new TH2Eff("PionIsoTrackReductionHTNJets","PionIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionMHTNJets_ = new TH2Eff("PionIsoTrackReductionMHTNJets","PionIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionBTagNJets_ = new TH2Eff("PionIsoTrackReductionBTagNJets","PionIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionPTActivity_ = new TH2Eff("PionIsoTrackReductionPTActivity","PionIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  
  PionIsoTrackReductionHTMHT_NJets24_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets24","PionIsoTrackReductionHTMHT_NJets24", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets56_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets56","PionIsoTrackReductionHTMHT_NJets56", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets7Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets7Inf","PionIsoTrackReductionHTMHT_NJets7Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets2_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets2","PionIsoTrackReductionHTMHT_NJets2", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets3_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets3","PionIsoTrackReductionHTMHT_NJets3", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets4_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets4","PionIsoTrackReductionHTMHT_NJets4", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets5_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets5","PionIsoTrackReductionHTMHT_NJets5", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets6_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets6","PionIsoTrackReductionHTMHT_NJets6", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets78_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets78","PionIsoTrackReductionHTMHT_NJets78", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);
  PionIsoTrackReductionHTMHT_NJets9Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets9Inf","PionIsoTrackReductionHTMHT_NJets9Inf", threeDHT_bin_-1,ThreeDHT_bin_, threeDMHT_bin_-1,ThreeDMHT_bin_);

  PionIsoTrackReductionHTMHT_NJets24_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets24_BTags0","PionIsoTrackReductionHTMHT_NJets24_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJets56_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets56_BTags0","PionIsoTrackReductionHTMHT_NJets56_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJets7Inf_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets7Inf_BTags0","PionIsoTrackReductionHTMHT_NJets7Inf_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJets24_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets24_BTags1Inf","PionIsoTrackReductionHTMHT_NJets24_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJets56_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets56_BTags1Inf","PionIsoTrackReductionHTMHT_NJets56_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf","PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  // delta R jet and pT jet 
  MuIsoRelPTJet_ = new TH1Eff("MuIsoRelPTJet","MuIsoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  MuIsoDeltaRJet_ = new TH1Eff("MuIsoDeltaRJet","MuIsoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  MuIsoRelPTDeltaRJet_ = new TH2Eff("MuIsoRelPTDeltaRJet","MuIsoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  MuRecoRelPTJet_ = new TH1Eff("MuRecoRelPTJet","MuRecoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  MuRecoDeltaRJet_ = new TH1Eff("MuRecoDeltaRJet","MuRecoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  MuRecoRelPTDeltaRJet_ = new TH2Eff("MuRecoRelPTDeltaRJet","MuRecoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  ElecIsoRelPTJet_ = new TH1Eff("ElecIsoRelPTJet","ElecIsoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  ElecIsoDeltaRJet_ = new TH1Eff("ElecIsoDeltaRJet","ElecIsoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  ElecIsoRelPTDeltaRJet_ = new TH2Eff("ElecIsoRelPTDeltaRJet","ElecIsoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  ElecRecoRelPTJet_ = new TH1Eff("ElecRecoRelPTJet","ElecRecoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  ElecRecoDeltaRJet_ = new TH1Eff("ElecRecoDeltaRJet","ElecRecoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  ElecRecoRelPTDeltaRJet_ = new TH2Eff("ElecRecoRelPTDeltaRJet","ElecRecoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);

  // Additional Plots
  IsoTrackVetoPt_ = new TH1D("IsoTrackVetoPt","IsoTrackVetoPt", 80., 0., 200.);
  MuIsoTrackVetoPt_ = new TH1D("MuIsoTrackVetoPt","MuIsoTrackVetoPt", 80., 0., 200.);
  ElecIsoTrackVetoPt_ = new TH1D("ElecIsoTrackVetoPt","ElecIsoTrackVetoPt", 80., 0., 200.);
  PionIsoTrackVetoPt_ = new TH1D("PionIsoTrackVetoPt","PionIsoTrackVetoPt", 80., 0., 200.);

  IsoTrackVetoPtAcc_ = new TH1D("IsoTrackVetoPtAcc","IsoTrackVetoPtAcc", 80., 0., 200.);
  MuIsoTrackVetoPtAcc_ = new TH1D("MuIsoTrackVetoPtAcc","MuIsoTrackVetoPtAcc", 80., 0., 200.);
  ElecIsoTrackVetoPtAcc_ = new TH1D("ElecIsoTrackVetoPtAcc","ElecIsoTrackVetoPtAcc", 80., 0., 200.);
  PionIsoTrackVetoPtAcc_ = new TH1D("PionIsoTrackVetoPtAcc","PionIsoTrackVetoPtAcc", 80., 0., 200.);

  IsoTrackVetoPtIDIso_ = new TH1D("IsoTrackVetoPtIDIso","IsoTrackVetoPtIDIso", 80., 0., 200.);
  MuIsoTrackVetoPtIDIso_ = new TH1D("MuIsoTrackVetoPtIDIso","MuIsoTrackVetoPtIDIso", 80., 0., 200.);
  ElecIsoTrackVetoPtIDIso_ = new TH1D("ElecIsoTrackVetoPtIDIso","ElecIsoTrackVetoPtIDIso", 80., 0., 200.);
  PionIsoTrackVetoPtIDIso_ = new TH1D("PionIsoTrackVetoPtIDIso","PionIsoTrackVetoPtIDIso", 80., 0., 200.);

  IsoTrackVetoPtID_ = new TH1D("IsoTrackVetoPtID","IsoTrackVetoPtID", 80., 0., 200.);
  MuIsoTrackVetoPtID_ = new TH1D("MuIsoTrackVetoPtID","MuIsoTrackVetoPtID", 80., 0., 200.);
  ElecIsoTrackVetoPtID_ = new TH1D("ElecIsoTrackVetoPtID","ElecIsoTrackVetoPtID", 80., 0., 200.);
  PionIsoTrackVetoPtID_ = new TH1D("PionIsoTrackVetoPtID","PionIsoTrackVetoPtID", 80., 0., 200.);

  IsoTrackVetoPtIso_ = new TH1D("IsoTrackVetoPtIso","IsoTrackVetoPtIso", 80., 0., 200.);
  MuIsoTrackVetoPtIso_ = new TH1D("MuIsoTrackVetoPtIso","MuIsoTrackVetoPtIso", 80., 0., 200.);
  ElecIsoTrackVetoPtIso_ = new TH1D("ElecIsoTrackVetoPtIso","ElecIsoTrackVetoPtIso", 80., 0., 200.);
  PionIsoTrackVetoPtIso_ = new TH1D("PionIsoTrackVetoPtIso","PionIsoTrackVetoPtIso", 80., 0., 200.);

  IsoTrackVetoPtMuAcc_ = new TH1D("IsoTrackVetoPtMuAcc","IsoTrackVetoPtMuAcc", 80., 0., 200.);
  MuIsoTrackVetoPtMuAcc_ = new TH1D("MuIsoTrackVetoPtMuAcc","MuIsoTrackVetoPtMuAcc", 80., 0., 200.);
  ElecIsoTrackVetoPtMuAcc_ = new TH1D("ElecIsoTrackVetoPtMuAcc","ElecIsoTrackVetoPtMuAcc", 80., 0., 200.);
  PionIsoTrackVetoPtMuAcc_ = new TH1D("PionIsoTrackVetoPtMuAcc","PionIsoTrackVetoPtMuAcc", 80., 0., 200.);

  IsoTrackVetoPtMuIDIso_ = new TH1D("IsoTrackVetoPtMuIDIso","IsoTrackVetoPtMuIDIso", 80., 0., 200.);
  MuIsoTrackVetoPtMuIDIso_ = new TH1D("MuIsoTrackVetoPtMuIDIso","MuIsoTrackVetoPtMuIDIso", 80., 0., 200.);
  ElecIsoTrackVetoPtMuIDIso_ = new TH1D("ElecIsoTrackVetoPtMuIDIso","ElecIsoTrackVetoPtMuIDIso", 80., 0., 200.);
  PionIsoTrackVetoPtMuIDIso_ = new TH1D("PionIsoTrackVetoPtMuIDIso","PionIsoTrackVetoPtMuIDIso", 80., 0., 200.);

  IsoTrackVetoPtMuID_ = new TH1D("IsoTrackVetoPtMuID","IsoTrackVetoPtMuID", 80., 0., 200.);
  MuIsoTrackVetoPtMuID_ = new TH1D("MuIsoTrackVetoPtMuID","MuIsoTrackVetoPtMuID", 80., 0., 200.);
  ElecIsoTrackVetoPtMuID_ = new TH1D("ElecIsoTrackVetoPtMuID","ElecIsoTrackVetoPtMuID", 80., 0., 200.);
  PionIsoTrackVetoPtMuID_ = new TH1D("PionIsoTrackVetoPtMuID","PionIsoTrackVetoPtMuID", 80., 0., 200.);

  IsoTrackVetoPtMuIso_ = new TH1D("IsoTrackVetoPtMuIso","IsoTrackVetoPtMuIso", 80., 0., 200.);
  MuIsoTrackVetoPtMuIso_ = new TH1D("MuIsoTrackVetoPtMuIso","MuIsoTrackVetoPtMuIso", 80., 0., 200.);
  ElecIsoTrackVetoPtMuIso_ = new TH1D("ElecIsoTrackVetoPtMuIso","ElecIsoTrackVetoPtMuIso", 80., 0., 200.);
  PionIsoTrackVetoPtMuIso_ = new TH1D("PionIsoTrackVetoPtMuIso","PionIsoTrackVetoPtMuIso", 80., 0., 200.);

  IsoTrackVetoPtElecAcc_ = new TH1D("IsoTrackVetoPtElecAcc","IsoTrackVetoPtElecAcc", 80., 0., 200.);
  MuIsoTrackVetoPtElecAcc_ = new TH1D("MuIsoTrackVetoPtElecAcc","MuIsoTrackVetoPtElecAcc", 80., 0., 200.);
  ElecIsoTrackVetoPtElecAcc_ = new TH1D("ElecIsoTrackVetoPtElecAcc","ElecIsoTrackVetoPtElecAcc", 80., 0., 200.);
  PionIsoTrackVetoPtElecAcc_ = new TH1D("PionIsoTrackVetoPtElecAcc","PionIsoTrackVetoPtElecAcc", 80., 0., 200.);

  IsoTrackVetoPtElecIDIso_ = new TH1D("IsoTrackVetoPtElecIDIso","IsoTrackVetoPtElecIDIso", 80., 0., 200.);
  MuIsoTrackVetoPtElecIDIso_ = new TH1D("MuIsoTrackVetoPtElecIDIso","MuIsoTrackVetoPtElecIDIso", 80., 0., 200.);
  ElecIsoTrackVetoPtElecIDIso_ = new TH1D("ElecIsoTrackVetoPtElecIDIso","ElecIsoTrackVetoPtElecIDIso", 80., 0., 200.);
  PionIsoTrackVetoPtElecIDIso_ = new TH1D("PionIsoTrackVetoPtElecIDIso","PionIsoTrackVetoPtElecIDIso", 80., 0., 200.);

  IsoTrackVetoPtElecID_ = new TH1D("IsoTrackVetoPtElecID","IsoTrackVetoPtElecID", 80., 0., 200.);
  MuIsoTrackVetoPtElecID_ = new TH1D("MuIsoTrackVetoPtElecID","MuIsoTrackVetoPtElecID", 80., 0., 200.);
  ElecIsoTrackVetoPtElecID_ = new TH1D("ElecIsoTrackVetoPtElecID","ElecIsoTrackVetoPtElecID", 80., 0., 200.);
  PionIsoTrackVetoPtElecID_ = new TH1D("PionIsoTrackVetoPtElecID","PionIsoTrackVetoPtElecID", 80., 0., 200.);

  IsoTrackVetoPtElecIso_ = new TH1D("IsoTrackVetoPtElecIso","IsoTrackVetoPtElecIso", 80., 0., 200.);
  MuIsoTrackVetoPtElecIso_ = new TH1D("MuIsoTrackVetoPtElecIso","MuIsoTrackVetoPtElecIso", 80., 0., 200.);
  ElecIsoTrackVetoPtElecIso_ = new TH1D("ElecIsoTrackVetoPtElecIso","ElecIsoTrackVetoPtElecIso", 80., 0., 200.);
  PionIsoTrackVetoPtElecIso_ = new TH1D("PionIsoTrackVetoPtElecIso","PionIsoTrackVetoPtElecIso", 80., 0., 200.);

  MuAccFracHT_ = new TH1D("MuAccFracHT", "MuAccFracHT", 22, 250., 3000.);
  MuRecoFracHT_ = new TH1D("MuRecoFracHT", "MuRecoFracHT", 22, 250., 3000.);
  MuIsoFracHT_ = new TH1D("MuIsoFracHT", "MuIsoFracHT", 22, 250., 3000.);
  MuAccWoVetoFracHT_ = new TH1D("MuAccWoVetoFracHT", "MuAccWoVetoFracHT", 22, 250., 3000.);
  MuRecoWoVetoFracHT_ = new TH1D("MuRecoWoVetoFracHT", "MuRecoWoVetoFracHT", 22, 250., 3000.);
  MuIsoWoVetoFracHT_ = new TH1D("MuIsoWoVetoFracHT", "MuIsoWoVetoFracHT", 22, 250., 3000.);
  ElecAccFracHT_ = new TH1D("ElecAccFracHT", "ElecAccFracHT", 22, 250., 3000.);
  ElecRecoFracHT_ = new TH1D("ElecRecoFracHT", "ElecRecoFracHT", 22, 250., 3000.);
  ElecIsoFracHT_ = new TH1D("ElecIsoFracHT", "ElecIsoFracHT", 22, 250., 3000.);
  ElecAccWoVetoFracHT_ = new TH1D("ElecAccWoVetoFracHT", "ElecAccWoVetoFracHT", 22, 250., 3000.);
  ElecRecoWoVetoFracHT_ = new TH1D("ElecRecoWoVetoFracHT", "ElecRecoWoVetoFracHT", 22, 250., 3000.);
  ElecIsoWoVetoFracHT_ = new TH1D("ElecIsoWoVetoFracHT", "ElecIsoWoVetoFracHT", 22, 250., 3000.);

  MuAccFracMHT_ = new TH1D("MuAccFracMHT", "MuAccFracMHT", 20, 250., 1500.);
  MuRecoFracMHT_ = new TH1D("MuRecoFracMHT", "MuRecoFracMHT", 20, 250., 1500.);
  MuIsoFracMHT_ = new TH1D("MuIsoFracMHT", "MuIsoFracMHT", 20, 250., 1500.);
  MuAccWoVetoFracMHT_ = new TH1D("MuAccWoVetoFracMHT", "MuAccWoVetoFracMHT", 20, 250., 1500.);
  MuRecoWoVetoFracMHT_ = new TH1D("MuRecoWoVetoFracMHT", "MuRecoWoVetoFracMHT", 20, 250., 1500.);
  MuIsoWoVetoFracMHT_ = new TH1D("MuIsoWoVetoFracMHT", "MuIsoWoVetoFracMHT", 20, 250., 1500.);
  ElecAccFracMHT_ = new TH1D("ElecAccFracMHT", "ElecAccFracMHT", 20, 250., 1500.);
  ElecRecoFracMHT_ = new TH1D("ElecRecoFracMHT", "ElecRecoFracMHT", 20, 250., 1500.);
  ElecIsoFracMHT_ = new TH1D("ElecIsoFracMHT", "ElecIsoFracMHT", 20, 250., 1500.);
  ElecAccWoVetoFracMHT_ = new TH1D("ElecAccWoVetoFracMHT", "ElecAccWoVetoFracMHT", 20, 250., 1500.);
  ElecRecoWoVetoFracMHT_ = new TH1D("ElecRecoWoVetoFracMHT", "ElecRecoWoVetoFracMHT", 20, 250., 1500.);
  ElecIsoWoVetoFracMHT_ = new TH1D("ElecIsoWoVetoFracMHT", "ElecIsoWoVetoFracMHT", 20, 250., 1500.);

  MuAccFracNJets_ = new TH1D("MuAccFracNJets", "MuAccFracNJets", 9, 1.5, 10.5);
  MuRecoFracNJets_ = new TH1D("MuRecoFracNJets", "MuRecoFracNJets", 9, 1.5, 10.5);
  MuIsoFracNJets_ = new TH1D("MuIsoFracNJets", "MuIsoFracNJets", 9, 1.5, 10.5);
  MuAccWoVetoFracNJets_ = new TH1D("MuAccWoVetoFracNJets", "MuAccWoVetoFracNJets", 9, 1.5, 10.5);
  MuRecoWoVetoFracNJets_ = new TH1D("MuRecoWoVetoFracNJets", "MuRecoWoVetoFracNJets", 9, 1.5, 10.5);
  MuIsoWoVetoFracNJets_ = new TH1D("MuIsoWoVetoFracNJets", "MuIsoWoVetoFracNJets", 9, 1.5, 10.5);
  ElecAccFracNJets_ = new TH1D("ElecAccFracNJets", "ElecAccFracNJets", 9, 1.5, 10.5);
  ElecRecoFracNJets_ = new TH1D("ElecRecoFracNJets", "ElecRecoFracNJets", 9, 1.5, 10.5);
  ElecIsoFracNJets_ = new TH1D("ElecIsoFracNJets", "ElecIsoFracNJets", 9, 1.5, 10.5);
  ElecAccWoVetoFracNJets_ = new TH1D("ElecAccWoVetoFracNJets", "ElecAccWoVetoFracNJets", 9, 1.5, 10.5);
  ElecRecoWoVetoFracNJets_ = new TH1D("ElecRecoWoVetoFracNJets", "ElecRecoWoVetoFracNJets", 9, 1.5, 10.5);
  ElecIsoWoVetoFracNJets_ = new TH1D("ElecIsoWoVetoFracNJets", "ElecIsoWoVetoFracNJets", 9, 1.5, 10.5);

  MuAccFracBTags_ = new TH1D("MuAccFracBTags", "MuAccFracBTags", 6, -0.5, 5.5);
  MuRecoFracBTags_ = new TH1D("MuRecoFracBTags", "MuRecoFracBTags", 6, -0.5, 5.5);
  MuIsoFracBTags_ = new TH1D("MuIsoFracBTags", "MuIsoFracBTags", 6, -0.5, 5.5);
  MuAccWoVetoFracBTags_ = new TH1D("MuAccWoVetoFracBTags", "MuAccWoVetoFracBTags", 6, -0.5, 5.5);
  MuRecoWoVetoFracBTags_ = new TH1D("MuRecoWoVetoFracBTags", "MuRecoWoVetoFracBTags", 6, -0.5, 5.5);
  MuIsoWoVetoFracBTags_ = new TH1D("MuIsoWoVetoFracBTags", "MuIsoWoVetoFracBTags", 6, -0.5, 5.5);
  ElecAccFracBTags_ = new TH1D("ElecAccFracBTags", "ElecAccFracBTags", 6, -0.5, 5.5);
  ElecRecoFracBTags_ = new TH1D("ElecRecoFracBTags", "ElecRecoFracBTags", 6, -0.5, 5.5);
  ElecIsoFracBTags_ = new TH1D("ElecIsoFracBTags", "ElecIsoFracBTags", 6, -0.5, 5.5);
  ElecAccWoVetoFracBTags_ = new TH1D("ElecAccWoVetoFracBTags", "ElecAccWoVetoFracBTags", 6, -0.5, 5.5);
  ElecRecoWoVetoFracBTags_ = new TH1D("ElecRecoWoVetoFracBTags", "ElecRecoWoVetoFracBTags", 6, -0.5, 5.5);
  ElecIsoWoVetoFracBTags_ = new TH1D("ElecIsoWoVetoFracBTags", "ElecIsoWoVetoFracBTags", 6, -0.5, 5.5);

  // TAP studies
  TrackIsolationPTActivity_ = new TH2Eff("TrackIsolationPTActivity","TrackIsolationPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  MuTrackIsolationPTActivity_ = new TH2Eff("MuTrackIsolationPTActivity","MuTrackIsolationPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  ElecTrackIsolationPTActivity_ = new TH2Eff("ElecTrackIsolationPTActivity","ElecTrackIsolationPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);
  PionTrackIsolationPTActivity_ = new TH2Eff("PionTrackIsolationPTActivity","PionTrackIsolationPTActivity", twoDActivity_-1, TwoDActivity_,twoDPTlow_-1,TwoDPTlow_);

  // MHT?PTW histograms
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<3; inb++) {
      LostMuRATIO_HT12[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT12[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT12[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostMuRATIO_HT3[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT3[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT3[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostMuRATIO_HT23[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT23[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT23[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
    }
  }

}

Bool_t EffMaker::Process(Long64_t entry)
{

//  if (entry%10000==0) cout << "fChain->GetTree()->GetEntry(" << entry << ");" << endl;
  fChain->GetTree()->GetEntry(entry);

  if(Bin > 900 && BinQCD > 900) return kTRUE;

  //if(Weight<0) Weight*=-1;
  if(Weight<0) return kTRUE;

  // Fill events 4 times if using bTag probabilities
  int nLoops = 4;
  if(!doBtagProbabilities){
    nLoops = 1;
  }else if(NJets < 3){
    nLoops = 3;
  }

  for(int i = 0; i < nLoops; i++){
      double WeightBTagProb;

        if(doBtagProbabilities){
          BTags = i;
          BinQCD = SearchBins_->GetBinNumber(HT,MHT,NJets,i);
          WeightBTagProb = Weight * bTagProb->at(i);
        }else{
          WeightBTagProb = Weight;
        }

  // purity
  // single muon control sample
  // x-check
  if(MuPurity==2 && MTW < mtwCut_){
      //1D
      MuPurityBTag_->Fill(BTags,WeightBTagProb,true);
      MuPurityNJets_->Fill(NJets,WeightBTagProb,true);
      MuPurityHT_->Fill(HT,WeightBTagProb,true);
      MuPurityMHT_->Fill(MHT,WeightBTagProb,true);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
      MuonPurityNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      MuonPurityMHTBTags_->Fill(MHT,BTags,WeightBTagProb,true);
      MuonPurityHTMHT_->Fill(HT,MHT,WeightBTagProb,true);

      //NEW
      MuPuritySearchBins_->Fill(BinQCD, WeightBTagProb, true);
  }else if(MuPurity==0 && MTW < mtwCut_){
      //1D
      MuPurityBTag_->Fill(BTags,WeightBTagProb,false);
      MuPurityNJets_->Fill(NJets,WeightBTagProb,false);
      MuPurityHT_->Fill(HT,WeightBTagProb,false);
      MuPurityMHT_->Fill(MHT,WeightBTagProb,false);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
      MuonPurityNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
      MuonPurityMHTBTags_->Fill(MHT,BTags,WeightBTagProb,false);
      MuonPurityHTMHT_->Fill(HT,MHT,WeightBTagProb,false);

      //NEW
      MuPuritySearchBins_->Fill(BinQCD, WeightBTagProb, false);
  }

  if(ElecPurity==2 && MTW < mtwCut_){
      //1D
      ElecPurityBTag_->Fill(BTags,WeightBTagProb,true);
      ElecPurityNJets_->Fill(NJets,WeightBTagProb,true);
      ElecPurityHT_->Fill(HT,WeightBTagProb,true);
      ElecPurityMHT_->Fill(MHT,WeightBTagProb,true);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
      ElecPurityNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      ElecPurityMHTBTags_->Fill(MHT,BTags,WeightBTagProb,true);
      ElecPurityHTMHT_->Fill(HT,MHT,WeightBTagProb,true);

      //NEW
      ElecPuritySearchBins_->Fill(BinQCD, WeightBTagProb, true);
  }else if(ElecPurity==0 && MTW < mtwCut_){
      //1D
      ElecPurityBTag_->Fill(BTags,WeightBTagProb,false);
      ElecPurityNJets_->Fill(NJets,WeightBTagProb,false);
      ElecPurityHT_->Fill(HT,WeightBTagProb,false);
      ElecPurityMHT_->Fill(MHT,WeightBTagProb,false);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
      ElecPurityNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
      ElecPurityMHTBTags_->Fill(MHT,BTags,WeightBTagProb,false);
      ElecPurityHTMHT_->Fill(HT,MHT,WeightBTagProb,false);

      //NEW
      ElecPuritySearchBins_->Fill(BinQCD, WeightBTagProb, false);
  }

  if(MuonsNum==1 && ElectronsNum==0 && MTW < mtwCut_){
      //cout << "muon event" << endl;
      if(MuonsPromptMatched->at(0)==1){
          // cout << "PromptMatched" << endl;
          //1D
          MuPurityOldBTag_->Fill(BTags,WeightBTagProb,true);
          MuPurityOldNJets_->Fill(NJets,WeightBTagProb,true);
          MuPurityOldHT_->Fill(HT,WeightBTagProb,true);
          MuPurityOldMHT_->Fill(MHT,WeightBTagProb,true);
          MuPurityOldPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,true);
          MuPurityOldActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,true);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
          MuonPurityOldNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      }
      if(MuonsPromptMatched->at(0)==0){
          //1D
          MuPurityOldBTag_->Fill(BTags,WeightBTagProb,false);
          MuPurityOldNJets_->Fill(NJets,WeightBTagProb,false);
          MuPurityOldHT_->Fill(HT,WeightBTagProb,false);
          MuPurityOldMHT_->Fill(MHT,WeightBTagProb,false);
          MuPurityOldPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,false);
          MuPurityOldActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,false);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
          MuonPurityOldNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
      }
  }

  // single elec control sample
  if(MuonsNum==0 && ElectronsNum==1 && MTW < mtwCut_){
      if(ElectronsPromptMatched->at(0)==1){
          //1D
          ElecPurityOldBTag_->Fill(BTags,WeightBTagProb,true);
          ElecPurityOldNJets_->Fill(NJets,WeightBTagProb,true);
          ElecPurityOldHT_->Fill(HT,WeightBTagProb,true);
          ElecPurityOldMHT_->Fill(MHT,WeightBTagProb,true);
          ElecPurityOldPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,true);
          ElecPurityOldActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,true);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecPurityOldNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      }
      if(ElectronsPromptMatched->at(0)==0){
          //1D
          ElecPurityOldBTag_->Fill(BTags,WeightBTagProb,false);
          ElecPurityOldNJets_->Fill(NJets,WeightBTagProb,false);
          ElecPurityOldHT_->Fill(HT,WeightBTagProb,false);
          ElecPurityOldMHT_->Fill(MHT,WeightBTagProb,false);
          ElecPurityOldPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,false);
          ElecPurityOldActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,false);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecPurityOldNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
      }
  }

  // acceptance
  // single muon control sample
  if(muAcc==2){
      //1D
      MuAccBTag_->Fill(BTags,WeightBTagProb,true);
      MuAccNJets_->Fill(NJets,WeightBTagProb,true);
      MuAccHT_->Fill(HT,WeightBTagProb,true);
      MuAccMHT_->Fill(MHT,WeightBTagProb,true);
      MuAccDTT_->Fill(cosDTT,WeightBTagProb,true);
      MuAccPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuAccActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
      MuAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      MuAccHTMHT_->Fill(HT,MHT,WeightBTagProb,true);
      MuAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
      MuAccSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,true);
          MuAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,true);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }
      
      if(NJets<6.5){
          MuAccHTMHT_NJets26_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          MuAccHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);

          if(BTags < 2.5){
            if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
          }else{
            if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
          }
        }
      }
  }

  if(muAcc==0){
      //1D
      MuAccBTag_->Fill(BTags,WeightBTagProb,false);
      MuAccNJets_->Fill(NJets,WeightBTagProb,false);
      MuAccHT_->Fill(HT,WeightBTagProb,false);
      MuAccMHT_->Fill(MHT,WeightBTagProb,false);
      MuAccDTT_->Fill(cosDTT,WeightBTagProb,false);
      MuAccPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuAccActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      MuAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      MuAccHTMHT_->Fill(HT,MHT,WeightBTagProb,false);
      MuAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
      MuAccSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,false);
          MuAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,false);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets<6.5){
          MuAccHTMHT_NJets26_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          MuAccHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);

          if(BTags < 2.5){
            if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
          }else{
            if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5) MuAccHTMHT_NJets7Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
          }
        }
      }
  }
  
  // single elecon control sample
  if(elecAcc==2){
      //1D
      ElecAccBTag_->Fill(BTags,WeightBTagProb,true);
      ElecAccNJets_->Fill(NJets,WeightBTagProb,true);
      ElecAccHT_->Fill(HT,WeightBTagProb,true);
      ElecAccMHT_->Fill(MHT,WeightBTagProb,true);
      ElecAccDTT_->Fill(cosDTT,WeightBTagProb,true);
      ElecAccPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecAccActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
      ElecAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      ElecAccHTMHT_->Fill(HT,MHT,WeightBTagProb,true);
      ElecAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
      ElecAccSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJets26_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          ElecAccHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }

        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);

          if(BTags < 2.5){
            if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,true);
          }else{
            if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,true);
          }
        }
      }
  }

  if(elecAcc==0){
      //1D
      ElecAccBTag_->Fill(BTags,WeightBTagProb,false);
      ElecAccNJets_->Fill(NJets,WeightBTagProb,false);
      ElecAccHT_->Fill(HT,WeightBTagProb,false);
      ElecAccMHT_->Fill(MHT,WeightBTagProb,false);
      ElecAccDTT_->Fill(cosDTT,WeightBTagProb,false);
      ElecAccPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecAccActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      ElecAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      ElecAccHTMHT_->Fill(HT,MHT,WeightBTagProb,false);
      ElecAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
      ElecAccSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJets26_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          ElecAccHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);

          if(BTags < 2.5){
            if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags2_->Fill(HT,MHT,WeightBTagProb,false);
          }else{
            if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5) ElecAccHTMHT_NJets7Inf_BTags3Inf_->Fill(HT,MHT,WeightBTagProb,false);
          }
        }
      }
  }

  //Sam
  if(doPlotsForSam){
    if(GenMuons->size() == 1 && GenMuons->at(0).Pt() > 5. && std::abs(GenMuons->at(0).Eta()) < 2.4){
      if(muReco==2){
        recoLepOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);
        recoOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);

        recoTrackOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);
      }else{
        recoLepOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);

        bool matchedIsoTrack = false;
        for (UShort_t i=0; i<TAPMuonTracks->size(); i++){
          if(TAPMuonTracks->at(i).Pt() > 5 && deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),TAPMuonTracks->at(i).Eta(),TAPMuonTracks->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMuons->at(0).Pt()-TAPMuonTracks->at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenToRecoMu_){
            matchedIsoTrack = true;
            break;
          }
        }

        if(!matchedIsoTrack){
          for (UShort_t i=0; i<TAPPionTracks->size(); i++){
            if(TAPPionTracks->at(i).Pt() > 10 && deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),TAPPionTracks->at(i).Eta(),TAPPionTracks->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMuons->at(0).Pt()-TAPPionTracks->at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenToRecoMu_){
              matchedIsoTrack = true;
              break;
            }
          }
        }

        if(matchedIsoTrack){
          recoOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);
          recoTrackOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);
        }else{
          recoOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);
          recoTrackOverAccMu->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);
        }
      }
    }
    if(GenElectrons->size() == 1 && GenElectrons->at(0).Pt() > 5. && std::abs(GenElectrons->at(0).Eta()) < 2.5){
      if(elecReco==2){
        recoLepOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);
        recoOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);

        recoTrackOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);
      }else{
        recoLepOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);

        bool matchedIsoTrack = false;
        for (UShort_t i=0; i<TAPElectronTracks->size(); i++){
          if(TAPElectronTracks->at(i).Pt() > 5 && deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),TAPElectronTracks->at(i).Eta(),TAPElectronTracks->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenElectrons->at(0).Pt()-TAPElectronTracks->at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenToRecoElec_){
            matchedIsoTrack = true;
            break;
          }
        }

        if(!matchedIsoTrack){
          for (UShort_t i=0; i<TAPPionTracks->size(); i++){
            if(TAPPionTracks->at(i).Pt() > 10 && deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),TAPPionTracks->at(i).Eta(),TAPPionTracks->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenElectrons->at(0).Pt()-TAPPionTracks->at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenToRecoElec_){
              matchedIsoTrack = true;
              break;
            }
          }
        }

        if(matchedIsoTrack){
          recoOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);
          recoTrackOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);
        }else{
          recoOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);
          recoTrackOverAccEl->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);
        }
      }
    }
  }
  
  // reconstruction
  // single muon control sample
  if(muReco==2){
      //1D
      MuRecoBTag_->Fill(BTags,WeightBTagProb,true);
      MuRecoNJets_->Fill(NJets,WeightBTagProb,true);
      MuRecoHT_->Fill(HT,WeightBTagProb,true);
      MuRecoMHT_->Fill(MHT,WeightBTagProb,true);
      MuRecoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuRecoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,true);
      //MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      MuRecoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      //MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,true);
      MuRecoPTEta_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);

      MuRecoSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(std::abs(GenMuons->at(0).Eta()) < 1.1){
      	MuRecoActivityPTBarrel_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }else{
      	MuRecoActivityPTDisk_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }

      if(BTags == 0){
      	MuRecoPTEtaBTags0_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);
      }else{
      	MuRecoPTEtaBTags1Inf_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);
      }
  }

  if(muReco==0){
      //1D
      MuRecoBTag_->Fill(BTags,WeightBTagProb,false);
      MuRecoNJets_->Fill(NJets,WeightBTagProb,false);
      MuRecoHT_->Fill(HT,WeightBTagProb,false);
      MuRecoMHT_->Fill(MHT,WeightBTagProb,false);
      MuRecoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuRecoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,false);
      //MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      MuRecoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      //MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,false);
      MuRecoPTEta_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);

      MuRecoSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(std::abs(GenMuons->at(0).Eta()) < 1.1){
      	MuRecoActivityPTBarrel_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }else{
      	MuRecoActivityPTDisk_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }

      if(BTags == 0){
      	MuRecoPTEtaBTags0_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);
      }else{
      	MuRecoPTEtaBTags1Inf_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);
      }
  }
  
  // single elecon control sample
  if(elecReco==2){
      //1D
      ElecRecoBTag_->Fill(BTags,WeightBTagProb,true);
      ElecRecoNJets_->Fill(NJets,WeightBTagProb,true);
      ElecRecoHT_->Fill(HT,WeightBTagProb,true);
      ElecRecoMHT_->Fill(MHT,WeightBTagProb,true);
      ElecRecoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecRecoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,true);
      //ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      ElecRecoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      //ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,true);
      ElecRecoPTEta_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);

      ElecRecoSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(std::abs(GenElectrons->at(0).Eta()) < 1.442){
      	ElecRecoActivityPTBarrel_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }else if(std::abs(GenElectrons->at(0).Eta()) > 1.566){
      	ElecRecoActivityPTDisk_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }

      if(BTags == 0){
      	ElecRecoPTEtaBTags0_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);
      }else{
      	ElecRecoPTEtaBTags1Inf_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);
      }
  }

  if(elecReco==0){
      //1D
      ElecRecoBTag_->Fill(BTags,WeightBTagProb,false);
      ElecRecoNJets_->Fill(NJets,WeightBTagProb,false);
      ElecRecoHT_->Fill(HT,WeightBTagProb,false);
      ElecRecoMHT_->Fill(MHT,WeightBTagProb,false);
      ElecRecoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecRecoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,false);
      //ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      ElecRecoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      //ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,false);
      ElecRecoPTEta_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);

      ElecRecoSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(std::abs(GenElectrons->at(0).Eta()) < 1.442){
      	ElecRecoActivityPTBarrel_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }else if(std::abs(GenElectrons->at(0).Eta()) > 1.566){
      	ElecRecoActivityPTDisk_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }

      if(BTags == 0){
      	ElecRecoPTEtaBTags0_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);
      }else{
      	ElecRecoPTEtaBTags1Inf_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);
      }
  }
  
  // isolation
  // single muon control sample
  if(muIso==2){
      //1D
      MuIsoBTag_->Fill(BTags,WeightBTagProb,true);
      MuIsoNJets_->Fill(NJets,WeightBTagProb,true);
      MuIsoHT_->Fill(HT,WeightBTagProb,true);
      MuIsoMHT_->Fill(MHT,WeightBTagProb,true);
      MuIsoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuIsoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,true);
      //MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      MuIsoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      //MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,true);

      MuIsoPTEta_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,true);

      MuIsoSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(std::abs(GenMuons->at(0).Eta()) < 1.1){
      	MuIsoActivityPTBarrel_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }else{
      	MuIsoActivityPTDisk_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }

      if(BTags == 0){
      	MuIsoActivityPTBTags0_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }else{
      	MuIsoActivityPTBTags1Inf_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      }
  }

  if(muIso==0){
      //1D
      MuIsoBTag_->Fill(BTags,WeightBTagProb,false);
      MuIsoNJets_->Fill(NJets,WeightBTagProb,false);
      MuIsoHT_->Fill(HT,WeightBTagProb,false);
      MuIsoMHT_->Fill(MHT,WeightBTagProb,false);
      MuIsoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuIsoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,false);
      //MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      MuIsoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      //MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,false);

      MuIsoPTEta_->Fill(GenMuons->at(0).Pt(),GenMuons->at(0).Eta(),WeightBTagProb,false);

      MuIsoSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(std::abs(GenMuons->at(0).Eta()) < 1.1){
      	MuIsoActivityPTBarrel_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }else{
      	MuIsoActivityPTDisk_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }

      if(BTags == 0){
      	MuIsoActivityPTBTags0_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }else{
      	MuIsoActivityPTBTags1Inf_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }
  }
  
  // single elecon control sample
  if(elecIso==2){
      //1D
      ElecIsoBTag_->Fill(BTags,WeightBTagProb,true);
      ElecIsoNJets_->Fill(NJets,WeightBTagProb,true);
      ElecIsoHT_->Fill(HT,WeightBTagProb,true);
      ElecIsoMHT_->Fill(MHT,WeightBTagProb,true);
      ElecIsoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecIsoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,true);
      //ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      ElecIsoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      //ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,true);

      ElecIsoPTEta_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,true);

      ElecIsoSearchBins_->Fill(BinQCD, WeightBTagProb, true);

      if(std::abs(GenElectrons->at(0).Eta()) < 1.442){
      	ElecIsoActivityPTBarrel_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }else if(std::abs(GenElectrons->at(0).Eta()) > 1.566){
      	ElecIsoActivityPTDisk_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }

      if(BTags == 0){
      	ElecIsoActivityPTBTags0_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }else{
      	ElecIsoActivityPTBTags1Inf_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      }
  }

  if(elecIso==0){
      //1D
      ElecIsoBTag_->Fill(BTags,WeightBTagProb,false);
      ElecIsoNJets_->Fill(NJets,WeightBTagProb,false);
      ElecIsoHT_->Fill(HT,WeightBTagProb,false);
      ElecIsoMHT_->Fill(MHT,WeightBTagProb,false);
      ElecIsoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecIsoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,false);
      //ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      ElecIsoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      //ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,false);

      ElecIsoPTEta_->Fill(GenElectrons->at(0).Pt(),GenElectrons->at(0).Eta(),WeightBTagProb,false);

      ElecIsoSearchBins_->Fill(BinQCD, WeightBTagProb, false);

      if(std::abs(GenElectrons->at(0).Eta()) < 1.442){
      	ElecIsoActivityPTBarrel_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }else if(std::abs(GenElectrons->at(0).Eta()) > 1.566){
      	ElecIsoActivityPTDisk_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }

      if(BTags == 0){
      	ElecIsoActivityPTBTags0_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }else{
      	ElecIsoActivityPTBTags1Inf_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }
  }

  // mtw
  // single muon control sample
  if(muIso==2 && MTW < mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,WeightBTagProb,true);
      MuMTWNJets_->Fill(NJets,WeightBTagProb,true);
      MuMTWHT_->Fill(HT,WeightBTagProb,true);
      MuMTWMHT_->Fill(MHT,WeightBTagProb,true);
      MuMTWPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,true);
      MuMTWActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,true);
      MuMTWPTActivity_->Fill(Muons_MT2Activity->at(0),Muons->at(0).Pt(),WeightBTagProb,true);
      MuMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, true);
      MuMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, true);
      MuMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, true);
      if(NJets < 4.5) MuMTWHTMHT_NJets24_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 6.5) MuMTWHTMHT_NJets56_->Fill(HT, MHT, WeightBTagProb, true);
      else MuMTWHTMHT_NJets7Inf_->Fill(HT, MHT, WeightBTagProb, true);

      if(NJets < 2.5) MuMTWHTMHT_NJets2_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 3.5) MuMTWHTMHT_NJets3_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 4.5) MuMTWHTMHT_NJets4_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 5.5) MuMTWHTMHT_NJets5_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 6.5) MuMTWHTMHT_NJets6_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 8.5) MuMTWHTMHT_NJets78_->Fill(HT, MHT, WeightBTagProb, true);
      else MuMTWHTMHT_NJets9Inf_->Fill(HT, MHT, WeightBTagProb, true);

      //NEW
      MuMTWSearchBins_->Fill(BinQCD, WeightBTagProb, true);
  }

  if(muIso==2 && MTW > mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,WeightBTagProb,false);
      MuMTWNJets_->Fill(NJets,WeightBTagProb,false);
      MuMTWHT_->Fill(HT,WeightBTagProb,false);
      MuMTWMHT_->Fill(MHT,WeightBTagProb,false);
      MuMTWPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,false);
      MuMTWActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,false);
      MuMTWPTActivity_->Fill(Muons_MT2Activity->at(0),Muons->at(0).Pt(),WeightBTagProb,false);
      MuMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, false);
      MuMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, false);
      MuMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, false);
      if(NJets < 4.5) MuMTWHTMHT_NJets24_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 6.5) MuMTWHTMHT_NJets56_->Fill(HT, MHT, WeightBTagProb, false);
      else MuMTWHTMHT_NJets7Inf_->Fill(HT, MHT, WeightBTagProb, false);

      if(NJets < 2.5) MuMTWHTMHT_NJets2_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 3.5) MuMTWHTMHT_NJets3_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 4.5) MuMTWHTMHT_NJets4_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 5.5) MuMTWHTMHT_NJets5_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 6.5) MuMTWHTMHT_NJets6_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 8.5) MuMTWHTMHT_NJets78_->Fill(HT, MHT, WeightBTagProb, false);
      else MuMTWHTMHT_NJets9Inf_->Fill(HT, MHT, WeightBTagProb, false);

      //NEW
      MuMTWSearchBins_->Fill(BinQCD, WeightBTagProb, false);
  }
  
  // single elec control sample
  if(elecIso==2 && MTW < mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,WeightBTagProb,true);
      ElecMTWNJets_->Fill(NJets,WeightBTagProb,true);
      ElecMTWHT_->Fill(HT,WeightBTagProb,true);
      ElecMTWMHT_->Fill(MHT,WeightBTagProb,true);
      ElecMTWPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,true);
      ElecMTWActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,true);
      ElecMTWPTActivity_->Fill(Electrons_MT2Activity->at(0),Electrons->at(0).Pt(),WeightBTagProb,true);
      ElecMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, true);
      ElecMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, true);
      ElecMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, true);
      if(NJets < 4.5) ElecMTWHTMHT_NJets24_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 6.5) ElecMTWHTMHT_NJets56_->Fill(HT, MHT, WeightBTagProb, true);
      else ElecMTWHTMHT_NJets7Inf_->Fill(HT, MHT, WeightBTagProb, true);

      if(NJets < 2.5) ElecMTWHTMHT_NJets2_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 3.5) ElecMTWHTMHT_NJets3_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 4.5) ElecMTWHTMHT_NJets4_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 5.5) ElecMTWHTMHT_NJets5_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 6.5) ElecMTWHTMHT_NJets6_->Fill(HT, MHT, WeightBTagProb, true);
      else if(NJets < 8.5) ElecMTWHTMHT_NJets78_->Fill(HT, MHT, WeightBTagProb, true);
      else ElecMTWHTMHT_NJets9Inf_->Fill(HT, MHT, WeightBTagProb, true);

      //NEW
      ElecMTWSearchBins_->Fill(BinQCD, WeightBTagProb, true);
  }

  if(elecIso==2 && MTW > mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,WeightBTagProb,false);
      ElecMTWNJets_->Fill(NJets,WeightBTagProb,false);
      ElecMTWHT_->Fill(HT,WeightBTagProb,false);
      ElecMTWMHT_->Fill(MHT,WeightBTagProb,false);
      ElecMTWPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,false);
      ElecMTWActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,false);
      ElecMTWPTActivity_->Fill(Electrons_MT2Activity->at(0),Electrons->at(0).Pt(),WeightBTagProb,false);
      ElecMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, false);
      ElecMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, false);
      ElecMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, false);
      if(NJets < 4.5) ElecMTWHTMHT_NJets24_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 6.5) ElecMTWHTMHT_NJets56_->Fill(HT, MHT, WeightBTagProb, false);
      else ElecMTWHTMHT_NJets7Inf_->Fill(HT, MHT, WeightBTagProb, false);

      if(NJets < 2.5) ElecMTWHTMHT_NJets2_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 3.5) ElecMTWHTMHT_NJets3_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 4.5) ElecMTWHTMHT_NJets4_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 5.5) ElecMTWHTMHT_NJets5_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 6.5) ElecMTWHTMHT_NJets6_->Fill(HT, MHT, WeightBTagProb, false);
      else if(NJets < 8.5) ElecMTWHTMHT_NJets78_->Fill(HT, MHT, WeightBTagProb, false);
      else ElecMTWHTMHT_NJets9Inf_->Fill(HT, MHT, WeightBTagProb, false);

      //NEW
      ElecMTWSearchBins_->Fill(BinQCD, WeightBTagProb, false);
  }

  // di lep contribution
  if(MuDiLepControlSample==2){
      // 1D
      MuDiLepBTag_->Fill(BTags,WeightBTagProb,true);
      MuDiLepNJets_->Fill(NJets,WeightBTagProb,true);
      MuDiLepHT_->Fill(HT,WeightBTagProb,true);
      MuDiLepMHT_->Fill(MHT,WeightBTagProb,true);

      // 1D
      MuDiLepContributionBTag_->Fill(BTags,WeightBTagProb,true);
      MuDiLepContributionNJets_->Fill(NJets,WeightBTagProb,true);
      MuDiLepContributionHT_->Fill(HT,WeightBTagProb,true);
      MuDiLepContributionMHT_->Fill(MHT,WeightBTagProb,true);

      if(MTW <mtwCut_){
          // 1D
          MuDiLepFractionBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepFractionNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepFractionHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepFractionMHT_->Fill(MHT,WeightBTagProb,true);
      }


      if(MTW <mtwCut_){
          // 1D
          MuDiLepCRBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepCRNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepCRHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepCRMHT_->Fill(MHT,WeightBTagProb,true);
          MuDiLepCRMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
          MuDiLepCRNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
          MuDiLepCRSearchBins_->Fill(BinQCD,WeightBTagProb,true);
      }
    
  }

  if(MuDiLepControlSample==0){
      // 1D
      MuDiLepContributionBTag_->Fill(BTags,WeightBTagProb,false);
      MuDiLepContributionNJets_->Fill(NJets,WeightBTagProb,false);
      MuDiLepContributionHT_->Fill(HT,WeightBTagProb,false);
      MuDiLepContributionMHT_->Fill(MHT,WeightBTagProb,false);

      // 1D
      MuDiLepBTag_->Fill(BTags,WeightBTagProb,false);
      MuDiLepNJets_->Fill(NJets,WeightBTagProb,false);
      MuDiLepHT_->Fill(HT,WeightBTagProb,false);
      MuDiLepMHT_->Fill(MHT,WeightBTagProb,false);
    
      if(MTW <mtwCut_){
          // 1D
          MuDiLepEffBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepEffNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepEffHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepEffMHT_->Fill(MHT,WeightBTagProb,true);
          MuDiLepEffNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      }

      if(MTW <mtwCut_){
          // 1D
          MuDiLepCRBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepCRNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepCRHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepCRMHT_->Fill(MHT,WeightBTagProb,false);
          MuDiLepCRMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
          MuDiLepCRNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
          MuDiLepCRSearchBins_->Fill(BinQCD,WeightBTagProb,false);
      }
  }

  if(ExpectationDiLep==1){
          MuDiLepFractionBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepFractionNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepFractionHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepFractionMHT_->Fill(MHT,WeightBTagProb,false);

          MuDiLepEffBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepEffNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepEffHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepEffMHT_->Fill(MHT,WeightBTagProb,false);
          MuDiLepEffNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
  }
  
  if(ElecDiLepControlSample==2){
      // 1D
      ElecDiLepBTag_->Fill(BTags,WeightBTagProb,true);
      ElecDiLepNJets_->Fill(NJets,WeightBTagProb,true);
      ElecDiLepHT_->Fill(HT,WeightBTagProb,true);
      ElecDiLepMHT_->Fill(MHT,WeightBTagProb,true);

      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,WeightBTagProb,true);
      ElecDiLepContributionNJets_->Fill(NJets,WeightBTagProb,true);
      ElecDiLepContributionHT_->Fill(HT,WeightBTagProb,true);
      ElecDiLepContributionMHT_->Fill(MHT,WeightBTagProb,true);

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepFractionBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepFractionNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepFractionHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepFractionMHT_->Fill(MHT,WeightBTagProb,true);
      }
      
      if(MTW <mtwCut_){
          // 1D
          ElecDiLepCRBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepCRNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepCRHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepCRMHT_->Fill(MHT,WeightBTagProb,true);
          ElecDiLepCRMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecDiLepCRNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
          ElecDiLepCRSearchBins_->Fill(BinQCD,WeightBTagProb,true);
      }
    
  }

  if(ElecDiLepControlSample==0) {    
      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,WeightBTagProb,false);
      ElecDiLepContributionNJets_->Fill(NJets,WeightBTagProb,false);
      ElecDiLepContributionHT_->Fill(HT,WeightBTagProb,false);
      ElecDiLepContributionMHT_->Fill(MHT,WeightBTagProb,false);

      // 1D
      ElecDiLepBTag_->Fill(BTags,WeightBTagProb,false);
      ElecDiLepNJets_->Fill(NJets,WeightBTagProb,false);
      ElecDiLepHT_->Fill(HT,WeightBTagProb,false);
      ElecDiLepMHT_->Fill(MHT,WeightBTagProb,false);
    
      if(MTW <mtwCut_){
          // 1D
          ElecDiLepEffBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepEffNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepEffHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepEffMHT_->Fill(MHT,WeightBTagProb,true);
          ElecDiLepEffNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,true);
      }

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepCRBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepCRNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepCRHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepCRMHT_->Fill(MHT,WeightBTagProb,false);
          ElecDiLepCRMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecDiLepCRNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
          ElecDiLepCRSearchBins_->Fill(BinQCD,WeightBTagProb,false);
      }
  } 

    if(ExpectationDiLep==1){
          ElecDiLepFractionBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepFractionNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepFractionHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepFractionMHT_->Fill(MHT,WeightBTagProb,false);

          ElecDiLepEffBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepEffNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepEffHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepEffMHT_->Fill(MHT,WeightBTagProb,false);
          ElecDiLepEffNJetsBTags_->Fill(NJets,BTags,WeightBTagProb,false);
  }

  if(Expectation==2){
    // CS event
    if(MuDiLepControlSample==2){
      MuDiLepSRBTag_->FillFrac(BTags,WeightBTagProb,false);
      MuDiLepSRNJets_->FillFrac(NJets,WeightBTagProb,false);
      MuDiLepSRHT_->FillFrac(HT,WeightBTagProb,false);
      MuDiLepSRMHT_->FillFrac(MHT,WeightBTagProb,false);
      MuDiLepSRMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,false);
      MuDiLepSRNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,false);
      MuDiLepSRSearchBins_->FillFrac(BinQCD,WeightBTagProb,false);

      MuDiLepSRwoVetoBTag_->FillFrac(BTags,WeightBTagProb,false);
      MuDiLepSRwoVetoNJets_->FillFrac(NJets,WeightBTagProb,false);
      MuDiLepSRwoVetoHT_->FillFrac(HT,WeightBTagProb,false);
      MuDiLepSRwoVetoMHT_->FillFrac(MHT,WeightBTagProb,false);
      MuDiLepSRwoVetoMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,false);
      MuDiLepSRwoVetoNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,false);
      MuDiLepSRwoVetoSearchBins_->FillFrac(BinQCD,WeightBTagProb,false);
    }

    if(ElecDiLepControlSample==2){
      ElecDiLepSRBTag_->FillFrac(BTags,WeightBTagProb,false);
      ElecDiLepSRNJets_->FillFrac(NJets,WeightBTagProb,false);
      ElecDiLepSRHT_->FillFrac(HT,WeightBTagProb,false);
      ElecDiLepSRMHT_->FillFrac(MHT,WeightBTagProb,false);
      ElecDiLepSRMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,false);
      ElecDiLepSRNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,false);
      ElecDiLepSRSearchBins_->FillFrac(BinQCD,WeightBTagProb,false);

      ElecDiLepSRwoVetoBTag_->FillFrac(BTags,WeightBTagProb,false);
      ElecDiLepSRwoVetoNJets_->FillFrac(NJets,WeightBTagProb,false);
      ElecDiLepSRwoVetoHT_->FillFrac(HT,WeightBTagProb,false);
      ElecDiLepSRwoVetoMHT_->FillFrac(MHT,WeightBTagProb,false);
      ElecDiLepSRwoVetoMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,false);
      ElecDiLepSRwoVetoNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,false);
      ElecDiLepSRwoVetoSearchBins_->FillFrac(BinQCD,WeightBTagProb,false);   
    }
  }

    if(MuDiLepControlSample==0){
      MuDiLepSRBTagEff_->FillFrac(BTags,WeightBTagProb,false);
      MuDiLepSRNJetsEff_->FillFrac(NJets,WeightBTagProb,false);
      MuDiLepSRHTEff_->FillFrac(HT,WeightBTagProb,false);
      MuDiLepSRMHTEff_->FillFrac(MHT,WeightBTagProb,false);
      MuDiLepSRMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,false);
      MuDiLepSRNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,false);
      MuDiLepSRSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,false);

      MuDiLepSRwoVetoBTagEff_->FillFrac(BTags,WeightBTagProb,false);
      MuDiLepSRwoVetoNJetsEff_->FillFrac(NJets,WeightBTagProb,false);
      MuDiLepSRwoVetoHTEff_->FillFrac(HT,WeightBTagProb,false);
      MuDiLepSRwoVetoMHTEff_->FillFrac(MHT,WeightBTagProb,false);
      MuDiLepSRwoVetoMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,false);
      MuDiLepSRwoVetoNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,false);
      MuDiLepSRwoVetoSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,false);
    }

    if(ElecDiLepControlSample==0){
      ElecDiLepSRBTagEff_->FillFrac(BTags,WeightBTagProb,false);
      ElecDiLepSRNJetsEff_->FillFrac(NJets,WeightBTagProb,false);
      ElecDiLepSRHTEff_->FillFrac(HT,WeightBTagProb,false);
      ElecDiLepSRMHTEff_->FillFrac(MHT,WeightBTagProb,false);
      ElecDiLepSRMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,false);
      ElecDiLepSRNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,false);
      ElecDiLepSRSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,false);

      ElecDiLepSRwoVetoBTagEff_->FillFrac(BTags,WeightBTagProb,false);
      ElecDiLepSRwoVetoNJetsEff_->FillFrac(NJets,WeightBTagProb,false);
      ElecDiLepSRwoVetoHTEff_->FillFrac(HT,WeightBTagProb,false);
      ElecDiLepSRwoVetoMHTEff_->FillFrac(MHT,WeightBTagProb,false);
      ElecDiLepSRwoVetoMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,false);
      ElecDiLepSRwoVetoNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,false);
      ElecDiLepSRwoVetoSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,false);   
    }

  if(Expectation==1 && ExpectationDiLep==1){

    if(ExpectationReductionIsoTrack==0){
      // Dilep evt in SR (passed isotrack veto)
      MuDiLepSRBTag_->FillFrac(BTags,WeightBTagProb,true);
      MuDiLepSRNJets_->FillFrac(NJets,WeightBTagProb,true);
      MuDiLepSRHT_->FillFrac(HT,WeightBTagProb,true);
      MuDiLepSRMHT_->FillFrac(MHT,WeightBTagProb,true);
      MuDiLepSRMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,true);
      MuDiLepSRNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,true);
      MuDiLepSRSearchBins_->FillFrac(BinQCD,WeightBTagProb,true);

      ElecDiLepSRBTag_->FillFrac(BTags,WeightBTagProb,true);
      ElecDiLepSRNJets_->FillFrac(NJets,WeightBTagProb,true);
      ElecDiLepSRHT_->FillFrac(HT,WeightBTagProb,true);
      ElecDiLepSRMHT_->FillFrac(MHT,WeightBTagProb,true);
      ElecDiLepSRMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,true);
      ElecDiLepSRNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,true);
      ElecDiLepSRSearchBins_->FillFrac(BinQCD,WeightBTagProb,true);
    }

      // Dilep evt in SR (ignores isotrack veto)
      MuDiLepSRwoVetoBTag_->FillFrac(BTags,WeightBTagProb,true);
      MuDiLepSRwoVetoNJets_->FillFrac(NJets,WeightBTagProb,true);
      MuDiLepSRwoVetoHT_->FillFrac(HT,WeightBTagProb,true);
      MuDiLepSRwoVetoMHT_->FillFrac(MHT,WeightBTagProb,true);
      MuDiLepSRwoVetoMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,true);
      MuDiLepSRwoVetoNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,true);
      MuDiLepSRwoVetoSearchBins_->FillFrac(BinQCD,WeightBTagProb,true);

      ElecDiLepSRwoVetoBTag_->FillFrac(BTags,WeightBTagProb,true);
      ElecDiLepSRwoVetoNJets_->FillFrac(NJets,WeightBTagProb,true);
      ElecDiLepSRwoVetoHT_->FillFrac(HT,WeightBTagProb,true);
      ElecDiLepSRwoVetoMHT_->FillFrac(MHT,WeightBTagProb,true);
      ElecDiLepSRwoVetoMHTNJets_->FillFrac(MHT,NJets,WeightBTagProb,true);
      ElecDiLepSRwoVetoNJetsBTags_->FillFrac(NJets,BTags,WeightBTagProb,true);
      ElecDiLepSRwoVetoSearchBins_->FillFrac(BinQCD,WeightBTagProb,true);

    if(ExpectationReductionIsoTrack==0){
      // Dilep evt in SR (passed isotrack veto)
      MuDiLepSRBTagEff_->FillFrac(BTags,WeightBTagProb,true);
      MuDiLepSRNJetsEff_->FillFrac(NJets,WeightBTagProb,true);
      MuDiLepSRHTEff_->FillFrac(HT,WeightBTagProb,true);
      MuDiLepSRMHTEff_->FillFrac(MHT,WeightBTagProb,true);
      MuDiLepSRMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,true);
      MuDiLepSRNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,true);
      MuDiLepSRSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,true);

      ElecDiLepSRBTagEff_->FillFrac(BTags,WeightBTagProb,true);
      ElecDiLepSRNJetsEff_->FillFrac(NJets,WeightBTagProb,true);
      ElecDiLepSRHTEff_->FillFrac(HT,WeightBTagProb,true);
      ElecDiLepSRMHTEff_->FillFrac(MHT,WeightBTagProb,true);
      ElecDiLepSRMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,true);
      ElecDiLepSRNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,true);
      ElecDiLepSRSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,true);
    }

      // Dilep evt in SR (ignores isotrack veto)
      MuDiLepSRwoVetoBTagEff_->FillFrac(BTags,WeightBTagProb,true);
      MuDiLepSRwoVetoNJetsEff_->FillFrac(NJets,WeightBTagProb,true);
      MuDiLepSRwoVetoHTEff_->FillFrac(HT,WeightBTagProb,true);
      MuDiLepSRwoVetoMHTEff_->FillFrac(MHT,WeightBTagProb,true);
      MuDiLepSRwoVetoMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,true);
      MuDiLepSRwoVetoNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,true);
      MuDiLepSRwoVetoSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,true);

      ElecDiLepSRwoVetoBTagEff_->FillFrac(BTags,WeightBTagProb,true);
      ElecDiLepSRwoVetoNJetsEff_->FillFrac(NJets,WeightBTagProb,true);
      ElecDiLepSRwoVetoHTEff_->FillFrac(HT,WeightBTagProb,true);
      ElecDiLepSRwoVetoMHTEff_->FillFrac(MHT,WeightBTagProb,true);
      ElecDiLepSRwoVetoMHTNJetsEff_->FillFrac(MHT,NJets,WeightBTagProb,true);
      ElecDiLepSRwoVetoNJetsBTagsEff_->FillFrac(NJets,BTags,WeightBTagProb,true);
      ElecDiLepSRwoVetoSearchBinsEff_->FillFrac(BinQCD,WeightBTagProb,true);    
  }
    
  // ExpectationReductionIsoTrack
  if(Expectation==1 && ExpectationReductionIsoTrack==0){
      //  cout << "Event not rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);

      if(GenMuonsNum>0){
          //  cout << "Muon event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      }else if(GenElectronsNum>0){
          // cout << "Electron event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      }else if(GenTausNum>0){
          // cout << "Tau event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTaus_MT2Activity->at(0),WeightBTagProb,false);
      }else std::cout<<"No gen lepton found to fail..."<<std::endl;

      //2D
      IsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      IsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      IsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);      
      if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,false);
      else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,false);
      else IsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 1.5 && NJets < 2.5) IsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) IsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 6.5 && NJets < 8.5) IsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 8.5) IsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags<0.5){
        if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        else IsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
      if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(GenMuonsNum>0){
          IsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
          MuIsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }else if(GenElectronsNum>0){
          IsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
          ElecIsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }else if(GenTausNum>0){
          IsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,false);
          if(GenTaus->at(0).Pt() > 10.) PionIsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,false);
      }

      //NEW
      IsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, false);
  }
  
  if(Expectation==1 && ExpectationReductionIsoTrack==1){
      // cout << "Event rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);

      if(isoMuonTracksNum>0 && GenMuonsNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      }else if(isoElectronTracksNum>0 && GenElectronsNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      }else if(isoPionTracksNum>0 && GenTausNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTaus_MT2Activity->at(0),WeightBTagProb,true);
    }

    //2D
    IsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
    IsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
    IsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
    if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,true);
    else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 1.5 && NJets < 2.5) IsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 2.5 && NJets < 3.5) IsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 6.5 && NJets < 8.5) IsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 8.5) IsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

  if(BTags<0.5){
    if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
    else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
  }else{
  if(NJets < 4.5) IsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
      else if(NJets < 6.5) IsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
  }

    if(isoMuonTracksNum>0 && GenMuonsNum>0){
        IsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
        MuIsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);

        IsoTrackFractionPTActivity_->FillFrac(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
        MuIsoTrackFractionPTActivity_->FillFrac(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
        //easy norm
        int isotrackActBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenMuons_MT2Activity->at(0));
        int isotrackPtBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenMuons->at(0).Pt());
        int muIsotrackActBin = MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenMuons_MT2Activity->at(0));
        int muIsotrackPtBin = MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenMuons->at(0).Pt());
        if(isotrackActBin > 0 && isotrackActBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && isotrackPtBin > 0 && isotrackPtBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){
          for(int xBin = 0; xBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              IsoTrackFractionPTActivity_->FillFrac(IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
        if(muIsotrackActBin > 0 && muIsotrackActBin < MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && muIsotrackPtBin > 0 && muIsotrackPtBin < MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){    
          for(int xBin = 0; xBin <= MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              MuIsoTrackFractionPTActivity_->FillFrac(MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),MuIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
    }else if(isoElectronTracksNum>0 && GenElectronsNum>0){
        IsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
        ElecIsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);

        IsoTrackFractionPTActivity_->FillFrac(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
        ElecIsoTrackFractionPTActivity_->FillFrac(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
        //easy norm
        int isotrackActBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenElectrons_MT2Activity->at(0));
        int isotrackPtBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenElectrons->at(0).Pt());
        int elecIsotrackActBin = ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenElectrons_MT2Activity->at(0));
        int elecIsotrackPtBin = ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenElectrons->at(0).Pt());
        if(isotrackActBin > 0 && isotrackActBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && isotrackPtBin > 0 && isotrackPtBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){
          for(int xBin = 0; xBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              IsoTrackFractionPTActivity_->FillFrac(IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
        if(elecIsotrackActBin > 0 && elecIsotrackActBin < ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && elecIsotrackPtBin > 0 && elecIsotrackPtBin < ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){ 
          for(int xBin = 0; xBin <= ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              ElecIsoTrackFractionPTActivity_->FillFrac(ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),ElecIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
    }else if(isoPionTracksNum>0 && GenTausNum>0){
        IsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,true);
        if(GenTaus->at(0).Pt() > 10.) PionIsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,true);

        IsoTrackFractionPTActivity_->FillFrac(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,true);
        if(GenTaus->at(0).Pt()>10.) PionIsoTrackFractionPTActivity_->FillFrac(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,true);
        //easy norm
        int isotrackActBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenTaus_MT2Activity->at(0));
        int isotrackPtBin = IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenTaus->at(0).Pt());
        int pionIsotrackActBin = PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->FindBin(GenTaus_MT2Activity->at(0));
        int pionIsotrackPtBin = PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->FindBin(GenTaus->at(0).Pt());
        if(isotrackActBin > 0 && isotrackActBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && isotrackPtBin > 0 && isotrackPtBin < IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){
          for(int xBin = 0; xBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              if(GenTaus->at(0).Pt()>10.) IsoTrackFractionPTActivity_->FillFrac(IsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),IsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
        if(pionIsotrackActBin > 0 && pionIsotrackActBin < PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1
          && pionIsotrackPtBin > 0 && pionIsotrackPtBin < PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1){
          for(int xBin = 0; xBin <= PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetNbins()+1; xBin++){
            for(int yBin = 0; yBin <= PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetNbins()+1; yBin++){
              if(GenTaus->at(0).Pt()>10.) PionIsoTrackFractionPTActivity_->FillFrac(PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetXaxis()->GetBinCenter(xBin),PionIsoTrackFractionPTActivity_->GetTotalTH2()->GetYaxis()->GetBinCenter(yBin),WeightBTagProb,false);
            }
          }
        }
    }

    //NEW
    IsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, true);
  }

    // In order to avoid double-counting events, only select track with highest pt
    if(Expectation==1){
        int isoTrack_highestPt = 0;

        if(isoMuonTracksNum>0){
            isoTrack_highestPt = 1;
            if(isoElectronTracksNum>0 && isoPionTracksNum>0){
                if(isoElectronTracks->at(0).Pt() > TMath::Max(isoMuonTracks->at(0).Pt(), isoPionTracks->at(0).Pt())) isoTrack_highestPt = 2;
                if(isoPionTracks->at(0).Pt() > TMath::Max(isoMuonTracks->at(0).Pt(), isoElectronTracks->at(0).Pt())) isoTrack_highestPt = 3;
            }else if(isoElectronTracksNum>0){
                if(isoElectronTracks->at(0).Pt() > isoMuonTracks->at(0).Pt()) isoTrack_highestPt = 2;
            }else if(isoPionTracksNum>0){
                if(isoPionTracks->at(0).Pt() > isoMuonTracks->at(0).Pt()) isoTrack_highestPt = 3;
            }
        }else if(isoElectronTracksNum>0){
            isoTrack_highestPt = 2;
            if(isoPionTracksNum>0) if(isoPionTracks->at(0).Pt() > isoElectronTracks->at(0).Pt()) isoTrack_highestPt = 3;
        }else if(isoPionTracksNum>0){
            isoTrack_highestPt = 3;
        }

        if(isoMuonTracksNum+isoElectronTracksNum+isoPionTracksNum==0){
            IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
        }

        MuIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb, false);
        ElecIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb, false);
        PionIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb, false);
        IsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb, false);


        // muon iso tracks
        if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
            // cout << "Muon tracks found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackPTEff_->Fill(isoMuonTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(isoMuonTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  MuIsoTrackReductionPTActivity_->Fill(isoMuonTracksNumActivity->at(0),isoMuonTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,true);
            else MuIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 1.5 && NJets < 2.5) MuIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 2.5 && NJets < 3.5) MuIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) MuIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) MuIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) MuIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) MuIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) MuIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
              if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else MuIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
            }else{
              if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
              else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
              else MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
            }

            //NEW
            MuIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, true);
            if(isoMuonTracks->at(0).Pt() < 10){
              MuIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              MuIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              MuIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              MuIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            if(isoMuonTracks->at(0).Pt() < 10){
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }

            double trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
            if(isoMuonTracks->at(0).Pt() < 10) trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
            MuIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            IsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            // cout << "DONE" << endl;
        }else{
            // cout << "Muon tracks not found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            // JACK -- placeholders
            ExpectationReductionMuIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  MuIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,false);
            else MuIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 1.5 && NJets < 2.5) MuIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 2.5 && NJets < 3.5) MuIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) MuIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) MuIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) MuIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) MuIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) MuIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
              if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else MuIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
            }else{
              if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
              else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
              else MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
            }

            //NEW
            MuIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, false);
            MuIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            MuIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            // cout << "DONE" << endl;
        }
      
      
        // elec iso tracks
        if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
            // cout << "Electron tracks found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackPTEff_->Fill(isoElectronTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(isoElectronTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  ElecIsoTrackReductionPTActivity_->Fill(isoElectronTracksNumActivity->at(0),isoElectronTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,true);
            else ElecIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 1.5 && NJets < 2.5) ElecIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 2.5 && NJets < 3.5) ElecIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) ElecIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) ElecIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) ElecIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
              if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
            }else{
              if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
              else ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
            }

            //NEW
            ElecIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, true);
            if(isoElectronTracks->at(0).Pt() < 10){
              ElecIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              ElecIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              ElecIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              ElecIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            if(isoElectronTracks->at(0).Pt() < 10){
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }

            double trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
            ElecIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            IsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            // cout << "DONE" << endl;    
        }else{
            // cout << "Electron tracks not found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  ElecIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,false);
            else ElecIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 1.5 && NJets < 2.5) ElecIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 2.5 && NJets < 3.5) ElecIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) ElecIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) ElecIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) ElecIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
              if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
            }else{
              if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
              else ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
            }

            //NEW
            ElecIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, false);
            ElecIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            ElecIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            // cout << "DONE" << endl;    
        }

        // pion iso tracks
        if(isoPionTracksNum>0 && isoTrack_highestPt==3){
            // cout << "Pion tracks found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackPTEff_->Fill(isoPionTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(isoPionTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  PionIsoTrackReductionPTActivity_->Fill(isoPionTracksNumActivity->at(0),isoPionTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,true);
            else PionIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 1.5 && NJets < 2.5) PionIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 2.5 && NJets < 3.5) PionIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 3.5 && NJets < 4.5) PionIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 4.5 && NJets < 5.5) PionIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 5.5 && NJets < 6.5) PionIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 6.5 && NJets < 8.5) PionIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
            if(NJets > 8.5) PionIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
              if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
              else PionIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
            }else{
            if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
              else PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
            }

            //NEW
            PionIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, true);
            if(isoPionTracks->at(0).Pt() < 10){
              PionIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              PionIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              PionIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              PionIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            if(isoPionTracks->at(0).Pt() < 10){
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
            }
            else{
              IsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, true);
              IsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            }

            double trackingSF = 1;
            PionIsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            IsoTrackVetoSearchBinsSF_->FillFrac(BinQCD, WeightBTagProb*trackingSF, true);
            // cout << "DONE" << endl;    
        }else{
            // cout << "Pion tracks not found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  PionIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_->Fill(HT,MHT,WeightBTagProb,false);
            else PionIsoTrackReductionHTMHT_NJets7Inf_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 1.5 && NJets < 2.5) PionIsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 2.5 && NJets < 3.5) PionIsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 3.5 && NJets < 4.5) PionIsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 4.5 && NJets < 5.5) PionIsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 5.5 && NJets < 6.5) PionIsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 6.5 && NJets < 8.5) PionIsoTrackReductionHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
            if(NJets > 8.5) PionIsoTrackReductionHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
              if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
              else PionIsoTrackReductionHTMHT_NJets7Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
            }else{
              if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJets24_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJets56_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
              else PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
            }

            //NEW
            PionIsoTrackVetoSearchBins_->Fill(BinQCD, WeightBTagProb, false);
            PionIsoTrackVetoSearchBinsLowPt_->Fill(BinQCD, WeightBTagProb, false);
            PionIsoTrackVetoSearchBinsHighPt_->Fill(BinQCD, WeightBTagProb, false);
                // cout << "DONE" << endl;    
        }

        if(muAcc==0 || elecAcc==0){
          if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,true);
          else IsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,false);

          if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,true);
          else MuIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,false);

          if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,true);
          else ElecIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,false);

          if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,true);
          else PionIsoTrackVetoSearchBinsAcc_->Fill(BinQCD,WeightBTagProb,false);

          if(muAcc == 0){
            double trackingSF = 1;
            IsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            MuIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            ElecIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            PionIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
              MuIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,true);
              if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
              else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
              MuIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else MuIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
              ElecIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,true);
              trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
              ElecIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else ElecIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3){
              PionIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,true);
              trackingSF = 1;
              PionIsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsMuAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else PionIsoTrackVetoSearchBinsMuAcc_->Fill(BinQCD,WeightBTagProb,false);
          }

          if(elecAcc == 0){
            double trackingSF = 1;
            IsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            MuIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            ElecIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb,false);
            PionIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
              MuIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,true);
              if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
              else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
              MuIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else MuIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
              ElecIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,true);
              trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
              ElecIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else ElecIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3){
              PionIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,true);
              trackingSF = 1;
              PionIsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              IsoTrackVetoSearchBinsElecAccSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
            }else PionIsoTrackVetoSearchBinsElecAcc_->Fill(BinQCD,WeightBTagProb,false);
          }
        }

        if((muAcc==2 && (muReco==0 || (muReco==2 && muIso==0))) || (elecAcc==2 && (elecReco==0 || (elecReco==2 && elecIso==0)))){
          if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,true);
          else IsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,false);

          if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,true);
          else MuIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,false);

          if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,true);
          else ElecIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,false);

          if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,true);
          else PionIsoTrackVetoSearchBinsIDIso_->Fill(BinQCD,WeightBTagProb,false);

          if(muReco==0 || (muReco==2 && muIso==0)){
            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else MuIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else ElecIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else PionIsoTrackVetoSearchBinsMuIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
            else IsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
            else MuIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
            else ElecIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
            else PionIsoTrackVetoActivityPtMuIDIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
            else IsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
            else MuIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
            else ElecIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
            else PionIsoTrackVetoPtEtaMuIDIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);
          }

          if(elecReco==0 || (elecReco==2 && elecIso==0)){
            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else MuIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else ElecIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,true);
            else PionIsoTrackVetoSearchBinsElecIDIso_->Fill(BinQCD,WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
            else IsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
            else MuIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
            else ElecIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
            else PionIsoTrackVetoActivityPtElecIDIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

            if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
            else IsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
            else MuIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
            else ElecIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
            else PionIsoTrackVetoPtEtaElecIDIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);
          }

          if(muReco==0 || elecReco==0){
            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,true);
            else MuIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,true);
            else ElecIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,true);
            else PionIsoTrackVetoSearchBinsID_->Fill(BinQCD,WeightBTagProb,false);

            if(muReco==0){
              double trackingSF = 1;
              IsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              MuIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              ElecIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              PionIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,true);
              else IsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,true);
                if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
                else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
                MuIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else MuIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
                ElecIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else ElecIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = 1;
                PionIsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else PionIsoTrackVetoSearchBinsMuID_->Fill(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else IsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else MuIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else ElecIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else PionIsoTrackVetoActivityPtMuID_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else IsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else MuIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else ElecIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else PionIsoTrackVetoPtEtaMuID_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);
            }

            if(elecReco==0){
              double trackingSF = 1;
              IsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              MuIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              ElecIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb,false);
              PionIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,true);
              else IsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,true);
                if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
                else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
                MuIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else MuIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
                ElecIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else ElecIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = 1;
                PionIsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIDSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else PionIsoTrackVetoSearchBinsElecID_->Fill(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else IsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else MuIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else ElecIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else PionIsoTrackVetoActivityPtElecID_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else IsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else MuIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else ElecIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else PionIsoTrackVetoPtEtaElecID_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);
            }
          }

          if(muIso==0 || elecIso==0){
            if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,true);
            else IsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,true);
            else MuIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,true);
            else ElecIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,false);

            if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,true);
            else PionIsoTrackVetoSearchBinsIso_->Fill(BinQCD,WeightBTagProb,false);

            if(muIso==0){
              double trackingSF = 1;
              IsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              MuIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              ElecIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              PionIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1){
                IsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,true);
              }else IsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,true);
                if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
                else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
                MuIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else MuIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
                ElecIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else ElecIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = 1;
                PionIsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsMuIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else PionIsoTrackVetoSearchBinsMuIso_->Fill(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else IsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else MuIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else ElecIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
              else PionIsoTrackVetoActivityPtMuIso_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else IsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else MuIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else ElecIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
              else PionIsoTrackVetoPtEtaMuIso_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);
            }

            if(elecIso==0){
              double trackingSF = 1;
              IsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              MuIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              ElecIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);
              PionIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,true);
              else IsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,true);
                if(isoMuonTracks->at(0).Pt() > 10) trackingSF = GetSF(h_muTrkHighPtSF, isoMuonTracks->at(0).Eta());
                else trackingSF = GetSF(h_muTrkLowPtSF, isoMuonTracks->at(0).Eta());
                MuIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else MuIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = GetSF(h_elecTrkSF, isoElectronTracks->at(0).Eta(), isoElectronTracks->at(0).Pt());
                ElecIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else ElecIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,true);
                trackingSF = 1;
                PionIsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
                IsoTrackVetoSearchBinsElecIsoSF_->FillFrac(BinQCD,WeightBTagProb*trackingSF,true);
              }else PionIsoTrackVetoSearchBinsElecIso_->Fill(BinQCD,WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else IsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else MuIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else ElecIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
              else PionIsoTrackVetoActivityPtElecIso_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);

              if(ExpectationReductionIsoTrack==1) IsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else IsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoMuonTracksNum>0 && isoTrack_highestPt==1) MuIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else MuIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoElectronTracksNum>0 && isoTrack_highestPt==2) ElecIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else ElecIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);

              if(isoPionTracksNum>0 && isoTrack_highestPt==3) PionIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
              else PionIsoTrackVetoPtEtaElecIso_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);
            }
          }
        }

        if(doTAPplots){
          if(muAcc==0 || elecAcc==0 || muReco==0 || elecReco==0 || muIso==0 || elecIso==0){
            for(unsigned i=0; i< TAPMuonTracks->size(); i++){
              if(GenMuonsNum > 0){
                for(unsigned j=0; j< GenMuons->size(); j++){
                  if(TAPMuonTracks_mT->at(i) < 100. && deltaR(GenMuons->at(j).Eta(),GenMuons->at(j).Phi(),TAPMuonTracks->at(i).Eta(),TAPMuonTracks->at(i).Phi())<maxDeltaRGenToRecoMu_){
                    if(TAPMuonTracks_trkiso->at(i) < 0.2){
                      TrackIsolationPTActivity_->Fill(TAPMuonTracks_activity->at(i), TAPMuonTracks->at(i).Pt(),WeightBTagProb,true);
                      MuTrackIsolationPTActivity_->Fill(TAPMuonTracks_activity->at(i), TAPMuonTracks->at(i).Pt(),WeightBTagProb,true);
                    }else{
                      TrackIsolationPTActivity_->Fill(TAPMuonTracks_activity->at(i), TAPMuonTracks->at(i).Pt(),WeightBTagProb,false);
                      MuTrackIsolationPTActivity_->Fill(TAPMuonTracks_activity->at(i), TAPMuonTracks->at(i).Pt(),WeightBTagProb,false);
                    }
                  }
                }
              }
            }

            for(unsigned i=0; i< TAPElectronTracks->size(); i++){
              if(GenElectronsNum > 0){
                for(unsigned j=0; j< GenElectrons->size(); j++){
                  if(TAPElectronTracks_mT->at(i) < 100. && deltaR(GenElectrons->at(j).Eta(),GenElectrons->at(j).Phi(),TAPElectronTracks->at(i).Eta(),TAPElectronTracks->at(i).Phi())<maxDeltaRGenToRecoMu_){
                    if(TAPElectronTracks_trkiso->at(i) < 0.2){
                      TrackIsolationPTActivity_->Fill(TAPElectronTracks_activity->at(i), TAPElectronTracks->at(i).Pt(),WeightBTagProb,true);
                      ElecTrackIsolationPTActivity_->Fill(TAPElectronTracks_activity->at(i), TAPElectronTracks->at(i).Pt(),WeightBTagProb,true);
                    }else{
                      TrackIsolationPTActivity_->Fill(TAPElectronTracks_activity->at(i), TAPElectronTracks->at(i).Pt(),WeightBTagProb,false);
                      ElecTrackIsolationPTActivity_->Fill(TAPElectronTracks_activity->at(i), TAPElectronTracks->at(i).Pt(),WeightBTagProb,false);
                    }
                  }
                }
              }
            }
          }

          // end of if(muAcc==0 || elecAcc==0 || muReco==0 || elecReco==0 || muIso==0 || elecIso==0)
          for(unsigned i=0; i< TAPPionTracks->size(); i++){
            if(GenTausNum > 0){
              for(unsigned j=0; j< GenTaus->size(); j++){
                if(TAPPionTracks_mT->at(i) < 100. && TAPPionTracks->at(i).Pt() > 10.  && deltaR(GenTaus->at(j).Eta(),GenTaus->at(j).Phi(),TAPPionTracks->at(i).Eta(),TAPPionTracks->at(i).Phi())<maxDeltaRGenToRecoMu_){
                  // actually pion track isolation is < 0.1
                  if(TAPPionTracks_trkiso->at(i) < 0.2){
                    TrackIsolationPTActivity_->Fill(TAPPionTracks_activity->at(i), TAPPionTracks->at(i).Pt(),WeightBTagProb,true);
                    PionTrackIsolationPTActivity_->Fill(TAPPionTracks_activity->at(i), TAPPionTracks->at(i).Pt(),WeightBTagProb,true);
                  }else{
                    TrackIsolationPTActivity_->Fill(TAPPionTracks_activity->at(i), TAPPionTracks->at(i).Pt(),WeightBTagProb,false);
                    PionTrackIsolationPTActivity_->Fill(TAPPionTracks_activity->at(i), TAPPionTracks->at(i).Pt(),WeightBTagProb,false);
                  }
                }
              }
            }
          }
        }

        if(doAdditionalPlots){
          if(muAcc==0 || elecAcc==0 || muReco==0 || elecReco==0 || muIso==0 || elecIso==0){
            if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
              MuIsoTrackVetoPt_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPt_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
              ElecIsoTrackVetoPt_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPt_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoPionTracksNum>0 && isoTrack_highestPt==3){
              PionIsoTrackVetoPt_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPt_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
            }
          }

          if(muAcc==0 || elecAcc==0){
            if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
              MuIsoTrackVetoPtAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
              ElecIsoTrackVetoPtAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoPionTracksNum>0 && isoTrack_highestPt==3){
              PionIsoTrackVetoPtAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
            }

            if(muAcc==0){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtMuAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtMuAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtMuAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }

              MuAccWoVetoFracHT_->Fill(HT, WeightBTagProb);
              MuAccWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
              MuAccWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
              MuAccWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

              if(ExpectationReductionIsoTrack==0){
                MuAccFracHT_->Fill(HT, WeightBTagProb);
                MuAccFracMHT_->Fill(MHT, WeightBTagProb);
                MuAccFracNJets_->Fill(NJets, WeightBTagProb);
                MuAccFracBTags_->Fill(BTags, WeightBTagProb);
              }
            }

            if(elecAcc==0){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtElecAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecAcc_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtElecAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecAcc_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtElecAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecAcc_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }

              ElecAccWoVetoFracHT_->Fill(HT, WeightBTagProb);
              ElecAccWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
              ElecAccWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
              ElecAccWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

              if(ExpectationReductionIsoTrack==0){
                ElecAccFracHT_->Fill(HT, WeightBTagProb);
                ElecAccFracMHT_->Fill(MHT, WeightBTagProb);
                ElecAccFracNJets_->Fill(NJets, WeightBTagProb);
                ElecAccFracBTags_->Fill(BTags, WeightBTagProb);
            }
            }
          }

          if((muAcc==2 && (muReco==0 || (muReco==2 && muIso==0))) || (elecAcc==2 && (elecReco==0 || (elecReco==2 && elecIso==0)))){
            if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
              MuIsoTrackVetoPtIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
              ElecIsoTrackVetoPtIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
            }
            if(isoPionTracksNum>0 && isoTrack_highestPt==3){
              PionIsoTrackVetoPtIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              IsoTrackVetoPtIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
            }

            if(muReco==0 || (muReco==2 && muIso==0)){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtMuIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtMuIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtMuIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtMuIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }
            }

            if(elecReco==0 || (elecReco==2 && elecIso==0)){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtElecIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecIDIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtElecIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecIDIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtElecIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtElecIDIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }
            }

            if(muReco==0 || elecReco==0){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }

              if(muReco==0){
                if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                  MuIsoTrackVetoPtMuID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                  ElecIsoTrackVetoPtMuID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                  PionIsoTrackVetoPtMuID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                }

                  MuRecoWoVetoFracHT_->Fill(HT, WeightBTagProb);
                MuRecoWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
                MuRecoWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
                MuRecoWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

                if(ExpectationReductionIsoTrack==0){
                  MuRecoFracHT_->Fill(HT, WeightBTagProb);
                  MuRecoFracMHT_->Fill(MHT, WeightBTagProb);
                  MuRecoFracNJets_->Fill(NJets, WeightBTagProb);
                  MuRecoFracBTags_->Fill(BTags, WeightBTagProb);
                }
              }

              if(elecReco==0){
                if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                  MuIsoTrackVetoPtElecID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecID_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                  ElecIsoTrackVetoPtElecID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecID_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                  PionIsoTrackVetoPtElecID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecID_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                }

                    ElecRecoWoVetoFracHT_->Fill(HT, WeightBTagProb);
                ElecRecoWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
                ElecRecoWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
                ElecRecoWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

                if(ExpectationReductionIsoTrack==0){
                  ElecRecoFracHT_->Fill(HT, WeightBTagProb);
                  ElecRecoFracMHT_->Fill(MHT, WeightBTagProb);
                  ElecRecoFracNJets_->Fill(NJets, WeightBTagProb);
                  ElecRecoFracBTags_->Fill(BTags, WeightBTagProb);
                }
              }
            }

            if(muIso==0 || elecIso==0){
              if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                MuIsoTrackVetoPtIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                ElecIsoTrackVetoPtIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
              }
              if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                PionIsoTrackVetoPtIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                IsoTrackVetoPtIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
              }

              if(muIso==0){
                if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                  MuIsoTrackVetoPtMuIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                  ElecIsoTrackVetoPtMuIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                  PionIsoTrackVetoPtMuIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtMuIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                }

                    MuIsoWoVetoFracHT_->Fill(HT, WeightBTagProb);
                MuIsoWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
                MuIsoWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
                MuIsoWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

                if(ExpectationReductionIsoTrack==0){
                  MuIsoFracHT_->Fill(HT, WeightBTagProb);
                  MuIsoFracMHT_->Fill(MHT, WeightBTagProb);
                  MuIsoFracNJets_->Fill(NJets, WeightBTagProb);
                  MuIsoFracBTags_->Fill(BTags, WeightBTagProb);
                }
              }

              if(elecIso==0){
                if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
                  MuIsoTrackVetoPtElecIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecIso_->Fill(isoMuonTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
                  ElecIsoTrackVetoPtElecIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecIso_->Fill(isoElectronTracks->at(0).Pt(), WeightBTagProb*36300);
                }
                if(isoPionTracksNum>0 && isoTrack_highestPt==3){
                  PionIsoTrackVetoPtElecIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                  IsoTrackVetoPtElecIso_->Fill(isoPionTracks->at(0).Pt(), WeightBTagProb*36300);
                }

                  ElecIsoWoVetoFracHT_->Fill(HT, WeightBTagProb);
                ElecIsoWoVetoFracMHT_->Fill(MHT, WeightBTagProb);
                ElecIsoWoVetoFracNJets_->Fill(NJets, WeightBTagProb);
                ElecIsoWoVetoFracBTags_->Fill(BTags, WeightBTagProb);

                if(ExpectationReductionIsoTrack==0){
                  ElecIsoFracHT_->Fill(HT, WeightBTagProb);
                  ElecIsoFracMHT_->Fill(MHT, WeightBTagProb);
                  ElecIsoFracNJets_->Fill(NJets, WeightBTagProb);
                  ElecIsoFracBTags_->Fill(BTags, WeightBTagProb);
                }
              }
            }
          }
      }


  // MHT/PTW histograms
  int INJ(-1);
  if (NJets>=4&&NJets<=6) INJ=0;
  else if (NJets>=7&&NJets<=8) INJ=1;
  else if (NJets>=9) INJ=2;
  int INB(BTags);
  if (INB>2) INB=2;
  int IHT(-1);
  if (HT>500&&HT<800) IHT=0;
  else if (HT>800&&HT<1200) IHT=1;
  else if (HT>1200) IHT=2;
  if (HT<800&&MHT>750) IHT=-1;

  //  printf("INJ/INB/IHT = %d/%d/%d\n", INJ, INB, IHT);
    if (INJ>=0&&INB>=0&&IHT>=0) {
      if (Expectation==1) {
        if (GenMuonsNum==1&&GenElectronsNum==0) {          
          if (ExpectationReductionIsoTrack==0) {
      double PTW = sqrt( (GenMuons->at(0).Px()+MHT*cos(MHTPhi))*(GenMuons->at(0).Px()+MHT*cos(MHTPhi)) +  (GenMuons->at(0).Py()+MHT*sin(MHTPhi))*(GenMuons->at(0).Py()+MHT*sin(MHTPhi)) );
      if (HT>500&&HT<1200) LostMuRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>1200) LostMuRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>800) LostMuRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
          }
        }
        else if (GenMuonsNum==0&&GenElectronsNum==1) {
          if (ExpectationReductionIsoTrack==0) {        
      double PTW = sqrt( (GenElectrons->at(0).Px()+MHT*cos(MHTPhi))*(GenElectrons->at(0).Px()+MHT*cos(MHTPhi)) +  (GenElectrons->at(0).Py()+MHT*sin(MHTPhi))*(GenElectrons->at(0).Py()+MHT*sin(MHTPhi)) );
      if (HT>500&&HT<1200) LostElecRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>1200) LostElecRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>800) LostElecRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
          }
        } // 1-electron events
        // what do we want to do with di/multi-lepton events?
        // commented out below: take sum of all leptons and MHT
        // else if (GenMuonsNum+GenElectronsNum>1) { 
        //   std::vector<TLorentzVector> GenLeps;
        //   for (unsigned int imu(0); imu<GenMuonsNum; imu++) {
        //  GenLeps.push_back(GenMuons->at(imu));
        //   }
        //   for (unsigned int iel(0); iel<GenElectronsNum; iel++) {
        //  GenLeps.push_back(GenElectrons->at(iel));
        //   }
        //   double PXW(MHT*cos(MHTPhi)), PYW(MHT*sin(MHTPhi));
        //   for (unsigned int ilep(0); ilep<GenLeps.size(); ilep++) {
        //  PXW+=GenLeps[ilep].Px();
        //  PYW+=GenLeps[ilep].Py();
        //   }
        //   double PTW = sqrt(PXW*PXW+PYW*PYW);
        //   if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
        //   if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
        //   if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
        // } // di/multi-lepton events
      }
    }
  
    }

  }
  
  return kTRUE;
}

void EffMaker::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

void EffMaker::Terminate()
{

  
  TFile *outPutFile = new TFile(fileName,"RECREATE"); 
  outPutFile->cd();
  outPutFile->mkdir("Efficiencies");
  TDirectory *dEfficiencies = (TDirectory*)outPutFile->Get("Efficiencies");
  dEfficiencies->cd();
  gStyle->SetPaintTextFormat("5.2f");
  gStyle->SetStatW(0.1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatY(202);

  //Double_t stops[9] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};
  //Double_t stops[8] = { 0.0000, 0.1429, 0.2857, 0.4286, 0.5714, 0.7143, 0.8571, 1.0000};
  Double_t stops[7] = { 0.0000, 0.1667, 0.3333, 0.5000, 0.6667, 0.8333, 1.0000};

  // kBird, noBlue
  //Double_t red[8]   = { 0.0592, 0.0780, 0.0232, 0.1802, 0.5301, 0.8186, 0.9956, 0.9764};
  //Double_t green[8] = { 0.3599, 0.5041, 0.6419, 0.7178, 0.7492, 0.7328, 0.7862, 0.9832};
  //Double_t blue[8]  = { 0.8684, 0.8385, 0.7914, 0.6425, 0.4662, 0.3499, 0.1968, 0.0539};

  // kBird, test
  //Double_t red[8]   = { 46./255., 49./255., 11./255., 71./255., 165./255., 220./255., 254./255., 249./255.};
  //Double_t green[8] = { 118./255., 155./255., 200./255., 209./255., 207./255., 203./255., 213./255., 252./255.};
  //Double_t blue[8]  = { 241./255., 236./255., 248./255., 190./255., 154./255., 129./255., 101./255., 64./255.};

  // kBird, test2
  //Double_t red[8]   = { 46./255., 49./255., 11./255., 0.1802, 0.5301, 0.8186, 0.9956, 0.9764};
  //Double_t green[8] = { 118./255., 155./255., 200./255., 0.7178, 0.7492, 0.7328, 0.7862, 0.9832};
  //Double_t blue[8]  = { 241./255., 236./255., 248./255., 0.6425, 0.4662, 0.3499, 0.1968, 0.0539};

  // kBlackBody, noRed
  //Double_t red[8]   = { 243./255., 240./255., 240./255., 241./255., 239./255., 186./255., 151./255., 129./255.};
  //Double_t green[8] = { 46./255.,  99./255., 149./255., 194./255., 220./255., 183./255., 166./255., 147./255.};
  //Double_t blue[8]  = { 8./255., 36./255., 91./255., 169./255., 235./255., 246./255., 240./255., 233./255.};
  //TColor::InvertPalette();

  // kBlackBody, noRed x2
  //Double_t red[7]   = { 240./255., 240./255., 241./255., 239./255., 186./255., 151./255., 129./255.};
  //Double_t green[7] = { 99./255., 149./255., 194./255., 220./255., 183./255., 166./255., 147./255.};
  //Double_t blue[7]  = { 36./255., 91./255., 169./255., 235./255., 246./255., 240./255., 233./255.};
  //TColor::InvertPalette();

  // kLightTemperature, noRed, noBlue
  Double_t red[7]   = {   71./255., 123./255., 160./255., 210./255., 222./255., 214./255., 199./255.};
  Double_t green[7] = {  117./255., 171./255., 211./255., 231./255., 220./255., 190./255., 132./255.};
  Double_t blue[7]  = {  214./255., 228./255., 222./255., 210./255., 160./255., 105./255., 60./255. };

  TColor::CreateGradientColorTable(7, stops, red, green, blue, 255);

//  gStyle->SetPalette(57, 0);
  gStyle->SetMarkerSize(1.0);
  gStyle->SetNumberContours(255);

  gStyle->SetTextFont(42);
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetStatFont(42);

  
  // NEW
  MuAccSearchBins_->SaveEff("#mu acc; Search region bin number; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  ElecAccSearchBins_->SaveEff("e acc; Search region bin number; #varepsilon_{Acc}^{e}", dEfficiencies);

  MuRecoSearchBins_->SaveEff("#mu reco; Search region bin number; #varepsilon_{Id}^{#mu}", dEfficiencies);
  MuIsoSearchBins_->SaveEff("#mu iso; Search region bin number; #varepsilon_{Iso}^{#mu}", dEfficiencies);
  ElecRecoSearchBins_->SaveEff("e reco; Search region bin number; #varepsilon_{Id}^{e}", dEfficiencies);
  ElecIsoSearchBins_->SaveEff("e iso; Search region bin number; #varepsilon_{Iso}^{e}", dEfficiencies);

  MuIsoTrackVetoSearchBins_->SaveEff("#mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}", dEfficiencies);
  ElecIsoTrackVetoSearchBins_->SaveEff("e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}", dEfficiencies);
  PionIsoTrackVetoSearchBins_->SaveEff("#pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}", dEfficiencies);
  IsoTrackVetoSearchBins_->SaveEff("iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}", dEfficiencies);

  MuIsoTrackVetoSearchBinsSF_->SaveEff("#mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsSF_->SaveEff("e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsSF_->SaveEff("#pi iso track expec. reduction; Search region bin number", dEfficiencies);
  IsoTrackVetoSearchBinsSF_->SaveEff("iso track expec. reduction; Search region bin number", dEfficiencies);

  MuIsoTrackVetoSearchBinsLowPt_->SaveEff("#mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsLowPt_->SaveEff("e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsLowPt_->SaveEff("#pi iso track expec. reduction; Search region bin number", dEfficiencies);
  IsoTrackVetoSearchBinsLowPt_->SaveEff("iso track expec. reduction; Search region bin number", dEfficiencies);

  MuIsoTrackVetoSearchBinsHighPt_->SaveEff("#mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsHighPt_->SaveEff("e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsHighPt_->SaveEff("#pi iso track expec. reduction; Search region bin number", dEfficiencies);
  IsoTrackVetoSearchBinsHighPt_->SaveEff("iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsAcc_->SaveEff("!acc iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Acc}}", dEfficiencies);
  MuIsoTrackVetoSearchBinsAcc_->SaveEff("!acc #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Acc}}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsAcc_->SaveEff("!acc e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Acc}}", dEfficiencies);
  PionIsoTrackVetoSearchBinsAcc_->SaveEff("!acc #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Acc}}", dEfficiencies);

  IsoTrackVetoSearchBinsIDIso_->SaveEff("!id/!iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id}/#slash{Iso}}", dEfficiencies);
  MuIsoTrackVetoSearchBinsIDIso_->SaveEff("!id/!iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id}/#slash{Iso}}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsIDIso_->SaveEff("!id/!iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id}/#slash{Iso}}", dEfficiencies);
  PionIsoTrackVetoSearchBinsIDIso_->SaveEff("!id/!iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id}/#slash{Iso}}", dEfficiencies);

  IsoTrackVetoSearchBinsID_->SaveEff("!id iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id}}", dEfficiencies);
  MuIsoTrackVetoSearchBinsID_->SaveEff("!id #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id}}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsID_->SaveEff("!id e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id}}", dEfficiencies);
  PionIsoTrackVetoSearchBinsID_->SaveEff("!id #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id}}", dEfficiencies);

  IsoTrackVetoSearchBinsIso_->SaveEff("!iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id}}", dEfficiencies);
  MuIsoTrackVetoSearchBinsIso_->SaveEff("!iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id}}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsIso_->SaveEff("!iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id}}", dEfficiencies);
  PionIsoTrackVetoSearchBinsIso_->SaveEff("!iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id}}", dEfficiencies);

  IsoTrackVetoSearchBinsMuAcc_->SaveEff("mu !acc iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Acc},#mu}", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuAcc_->SaveEff("mu !acc #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Acc},#mu}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuAcc_->SaveEff("mu !acc e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Acc},#mu}", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuAcc_->SaveEff("mu !acc #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Acc},#mu}", dEfficiencies);

  IsoTrackVetoSearchBinsMuIDIso_->SaveEff("mu !id/!iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id}/#slash{Iso},#mu}", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuIDIso_->SaveEff("mu !id/!iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id}/#slash{Iso},#mu}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuIDIso_->SaveEff("mu !id/!iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id}/#slash{Iso},#mu}", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuIDIso_->SaveEff("mu !id/!iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id}/#slash{Iso},#mu}", dEfficiencies);

  IsoTrackVetoSearchBinsMuID_->SaveEff("mu !id iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id},#mu}", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuID_->SaveEff("mu !id #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id},#mu}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuID_->SaveEff("mu !id e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id},#mu}", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuID_->SaveEff("mu !id #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id},#mu}", dEfficiencies);

  IsoTrackVetoSearchBinsMuIso_->SaveEff("mu !iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Iso},#mu}", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuIso_->SaveEff("mu !iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Iso},#mu}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuIso_->SaveEff("mu !iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Iso},#mu}", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuIso_->SaveEff("mu !iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Iso},#mu}", dEfficiencies);

  IsoTrackVetoSearchBinsElecAcc_->SaveEff("e !acc iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Acc},e}", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecAcc_->SaveEff("e !acc #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Acc},e}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecAcc_->SaveEff("e !acc e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Acc},e}", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecAcc_->SaveEff("e !acc #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Acc},e}", dEfficiencies);

  IsoTrackVetoSearchBinsElecIDIso_->SaveEff("e !id/!iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id}/#slash{Iso},e}", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecIDIso_->SaveEff("e !id/!iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id}/#slash{Iso},e}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecIDIso_->SaveEff("e !id/!iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id}/#slash{Iso},e}", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecIDIso_->SaveEff("e !id/!iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id}/#slash{Iso},e}", dEfficiencies);

  IsoTrackVetoSearchBinsElecID_->SaveEff("e !id iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Id},e}", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecID_->SaveEff("e !id #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Id},e}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecID_->SaveEff("e !id e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Id},e}", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecID_->SaveEff("e !id #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Id},e}", dEfficiencies);

  IsoTrackVetoSearchBinsElecIso_->SaveEff("e !iso iso track expec. reduction; Search region bin number; #varepsilon_{isotrk}^{#slash{Iso},e}", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecIso_->SaveEff("e !iso #mu iso track expec. reduction; Search region bin number; #varepsilon_{#mu isotrk}^{#slash{Iso},e}", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecIso_->SaveEff("e !iso e iso track expec. reduction; Search region bin number; #varepsilon_{e isotrk}^{#slash{Iso},e}", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecIso_->SaveEff("e !iso #pi iso track expec. reduction; Search region bin number; #varepsilon_{#pi isotrk}^{#slash{Iso},e}", dEfficiencies);

  IsoTrackVetoSearchBinsMuAccSF_->SaveEff("mu !acc iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuAccSF_->SaveEff("mu !acc #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuAccSF_->SaveEff("mu !acc e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuAccSF_->SaveEff("mu !acc #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsMuIDSF_->SaveEff("mu !id iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuIDSF_->SaveEff("mu !id #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuIDSF_->SaveEff("mu !id e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuIDSF_->SaveEff("mu !id #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsMuIsoSF_->SaveEff("mu !iso iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsMuIsoSF_->SaveEff("mu !iso #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsMuIsoSF_->SaveEff("mu !iso e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsMuIsoSF_->SaveEff("mu !iso #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsElecAccSF_->SaveEff("e !acc iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecAccSF_->SaveEff("e !acc #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecAccSF_->SaveEff("e !acc e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecAccSF_->SaveEff("e !acc #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsElecIDSF_->SaveEff("e !id iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecIDSF_->SaveEff("e !id #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecIDSF_->SaveEff("e !id e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecIDSF_->SaveEff("e !id #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoSearchBinsElecIsoSF_->SaveEff("e !iso iso track expec. reduction; Search region bin number", dEfficiencies);
  MuIsoTrackVetoSearchBinsElecIsoSF_->SaveEff("e !iso #mu iso track expec. reduction; Search region bin number", dEfficiencies);
  ElecIsoTrackVetoSearchBinsElecIsoSF_->SaveEff("e !iso e iso track expec. reduction; Search region bin number", dEfficiencies);
  PionIsoTrackVetoSearchBinsElecIsoSF_->SaveEff("e !iso #pi iso track expec. reduction; Search region bin number", dEfficiencies);

  IsoTrackVetoActivityPtMuIDIso_->SaveEff("mu !id/!iso iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtMuIDIso_->SaveEff("mu !id/!iso #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtMuIDIso_->SaveEff("mu !id/!iso e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtMuIDIso_->SaveEff("mu !id/!iso #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoActivityPtMuID_->SaveEff("mu !id iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtMuID_->SaveEff("mu !id #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtMuID_->SaveEff("mu !id e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtMuID_->SaveEff("mu !id #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoActivityPtMuIso_->SaveEff("mu !iso iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtMuIso_->SaveEff("mu !iso #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtMuIso_->SaveEff("mu !iso e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtMuIso_->SaveEff("mu !iso #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoActivityPtElecIDIso_->SaveEff("e !id/!iso iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtElecIDIso_->SaveEff("e !id/!iso #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtElecIDIso_->SaveEff("e !id/!iso e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtElecIDIso_->SaveEff("e !id/!iso #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoActivityPtElecID_->SaveEff("e !id iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtElecID_->SaveEff("e !id #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtElecID_->SaveEff("e !id e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtElecID_->SaveEff("e !id #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoActivityPtElecIso_->SaveEff("e !iso iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  MuIsoTrackVetoActivityPtElecIso_->SaveEff("e !iso #mu iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  ElecIsoTrackVetoActivityPtElecIso_->SaveEff("e !iso e iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);
  PionIsoTrackVetoActivityPtElecIso_->SaveEff("e !iso #pi iso track expec. reduction; Activity; p_{T}", dEfficiencies, true);

  IsoTrackVetoPtEtaMuIDIso_->SaveEff("mu !id/!iso iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaMuIDIso_->SaveEff("mu !id/!iso #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaMuIDIso_->SaveEff("mu !id/!iso e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaMuIDIso_->SaveEff("mu !id/!iso #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);

  IsoTrackVetoPtEtaMuID_->SaveEff("mu !id iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaMuID_->SaveEff("mu !id #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaMuID_->SaveEff("mu !id e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaMuID_->SaveEff("mu !id #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);

  IsoTrackVetoPtEtaMuIso_->SaveEff("mu !iso iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaMuIso_->SaveEff("mu !iso #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaMuIso_->SaveEff("mu !iso e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaMuIso_->SaveEff("mu !iso #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);

  IsoTrackVetoPtEtaElecIDIso_->SaveEff("e !id/!iso iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaElecIDIso_->SaveEff("e !id/!iso #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaElecIDIso_->SaveEff("e !id/!iso e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaElecIDIso_->SaveEff("e !id/!iso #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);

  IsoTrackVetoPtEtaElecID_->SaveEff("e !id iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaElecID_->SaveEff("e !id #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaElecID_->SaveEff("e !id e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaElecID_->SaveEff("e !id #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);

  IsoTrackVetoPtEtaElecIso_->SaveEff("e !iso iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  MuIsoTrackVetoPtEtaElecIso_->SaveEff("e !iso #mu iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  ElecIsoTrackVetoPtEtaElecIso_->SaveEff("e !iso e iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);
  PionIsoTrackVetoPtEtaElecIso_->SaveEff("e !iso #pi iso track expec. reduction; p_{T}; #eta", dEfficiencies, true);


  MuMTWSearchBins_->SaveEff("#mu m_{T}^{W}; Search region bin number; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);  
  ElecMTWSearchBins_->SaveEff("e m_{T}^{W}; Search region bin number; #varepsilon_{m_{T}}^{e}", dEfficiencies);  

  MuPuritySearchBins_->SaveEff("#mu purity; Search region bin number; #beta^{#mu}", dEfficiencies);  
  ElecPuritySearchBins_->SaveEff("e purity; Search region bin number; #beta^{e}", dEfficiencies);

  MuDiLepCRSearchBins_->SaveEff("#mu dilep purity; Search region bin number; #beta_{1l}^{#mu}", dEfficiencies);   
  ElecDiLepCRSearchBins_->SaveEff("e dilep purity; Search region bin number; #beta_{1l}^{e}", dEfficiencies);   

  // old purity
  //1D
  MuPurityOldBTag_->SaveEff("#mu purity; N_{b-jet}; #beta^{#mu}_{old}", dEfficiencies);
  MuPurityOldNJets_->SaveEff("#mu purity; N_{jet}; #beta^{#mu}_{old}", dEfficiencies);   
  MuPurityOldHT_->SaveEff("#mu purity; H_{T} [GeV]; #beta^{#mu}_{old}", dEfficiencies);   
  MuPurityOldMHT_->SaveEff("#mu purity; H_{T}^{miss} [GeV]; #beta^{#mu}_{old}", dEfficiencies);   
  MuonPurityOldMHTNJet_->SaveEff("#mu purity; H_{T}^{miss} [GeV]; N_{jet}; #beta^{#mu}_{old}", dEfficiencies);   
  MuonPurityOldNJetsBTags_->SaveEff("#mu purity; N_{jet}; N_{b-jet}; #beta^{#mu}_{old}", dEfficiencies);
  //1D
  ElecPurityOldBTag_->SaveEff("e purity; N_{b-jet}; #beta^{e}_{old}", dEfficiencies);
  ElecPurityOldNJets_->SaveEff("e purity; N_{jet}; #beta^{e}_{old}", dEfficiencies);   
  ElecPurityOldHT_->SaveEff("e purity; H_{T} [GeV]; #beta^{e}_{old}", dEfficiencies);   
  ElecPurityOldMHT_->SaveEff("e purity; H_{T}^{miss} [GeV]; #beta^{e}_{old}", dEfficiencies);   
  ElecPurityOldMHTNJet_->SaveEff("e purity; H_{T}^{miss} [GeV]; N_{jet}; #beta^{e}_{old}", dEfficiencies);   
  ElecPurityOldNJetsBTags_->SaveEff("e purity; N_{jet}; N_{b-jet}; #beta^{e}_{old}", dEfficiencies);

  // new purity
  //muon
  MuPurityBTag_->SaveEff("#mu purity; N_{b-jet}; #beta^{#mu}", dEfficiencies);   
  MuPurityNJets_->SaveEff("#mu purity; N_{jet}; #beta^{#mu}", dEfficiencies);   
  MuPurityHT_->SaveEff("#mu purity; H_{T} [GeV]; #beta^{#mu}", dEfficiencies);   
  MuPurityMHT_->SaveEff("#mu purity; H_{T}^{miss} [GeV]; #beta^{#mu}", dEfficiencies);   
  MuonPurityMHTNJet_->SaveEff("#mu purity; H_{T}^{miss} [GeV]; N_{jet}; #beta^{#mu}", dEfficiencies);
  MuonPurityNJetsBTags_->SaveEff("#mu purity; N_{jet}; N_{b-jet}; #beta^{#mu}", dEfficiencies);
  MuonPurityMHTBTags_->SaveEff("#mu purity; H_{T}^{miss} [GeV]; N_{b-jet}; #beta^{#mu}", dEfficiencies);
  MuonPurityHTMHT_->SaveEff("#mu purity; H_{T} [GeV]; H_{T}^{miss} [GeV]; #beta^{#mu}", dEfficiencies);

  //elec
  //1D
  ElecPurityBTag_->SaveEff("e purity; N_{b-jet}; #beta^{e}", dEfficiencies);   
  ElecPurityNJets_->SaveEff("e purity; N_{jet}; #beta^{e}", dEfficiencies);   
  ElecPurityHT_->SaveEff("e purity; H_{T} [GeV]; #beta^{e}", dEfficiencies);   
  ElecPurityMHT_->SaveEff("e purity; H_{T}^{miss} [GeV]; #beta^{e}", dEfficiencies);   
  ElecPurityMHTNJet_->SaveEff("e purity; H_{T}^{miss} [GeV]; N_{jet}; #beta^{e}", dEfficiencies);
  ElecPurityNJetsBTags_->SaveEff("e purity; N_{jet}; N_{b-jet}; #beta^{e}", dEfficiencies);
  ElecPurityMHTBTags_->SaveEff("e purity; H_{T}^{miss} [GeV]; N_{b-jet}; #beta^{e}", dEfficiencies);
  ElecPurityHTMHT_->SaveEff("e purity; H_{T} [GeV]; H_{T}^{miss} [GeV]; #beta^{e}", dEfficiencies);


  // acc
  //muon
  //1D
  MuAccBTag_->SaveEff("#mu acc; N_{b-jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccNJets_->SaveEff("#mu acc; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHT_->SaveEff("#mu acc; H_{T} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccMHT_->SaveEff("#mu acc; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccDTT_->SaveEff("#mu acc; 0.5*(1-cosDTT); #varepsilon_{Acc}^{#mu}", dEfficiencies);
  // 2D 
  MuAccHTNJets_->SaveEff("#mu acc; H_{T} [GeV]; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_->SaveEff("#mu acc; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccMHTNJets_->SaveEff("#mu acc; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccBTagNJets_->SaveEff("#mu acc; N_{b-jet}; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccMHTNJetsB0_->SaveEff("#mu acc N_{b-jet}=0; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccMHTNJetsB1_Inf_->SaveEff("#mu acc N_{b-jet}#geq1; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);    
  MuAccHTMHT_NJets26_->SaveEff("#mu acc N_{jet}=2-6;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets2_->SaveEff("#mu acc N_{jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets3_->SaveEff("#mu acc N_{jet}=3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_->SaveEff("#mu acc N_{jet}=4;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_->SaveEff("#mu acc N_{jet}=5;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_->SaveEff("#mu acc N_{jet}=6;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_->SaveEff("#mu acc N_{jet}=7-8;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_->SaveEff("#mu acc N_{jet}=9+;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets7Inf_->SaveEff("#mu acc N_{jet}#geq7;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHTB0_->SaveEff("#mu acc N_{b-jet}=0;H_{T} [GeV] ; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHTB1_Inf_->SaveEff("#mu acc N_{b-jet}#geq1; H_{T} [GeV]; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{#mu}", dEfficiencies);

  MuAccHTMHT_NJets2_BTags0_->SaveEff("#mu acc N_{jet}=2, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags0_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags0_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags0_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags0_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags0_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags0_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  MuAccHTMHT_NJets7Inf_BTags0_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  MuAccHTMHT_NJets2_BTags1Inf_->SaveEff("#mu acc N_{jet}=2, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags1Inf_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags1Inf_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags1Inf_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags1Inf_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags1Inf_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags1Inf_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets7Inf_BTags1Inf_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  MuAccHTMHT_NJets2_BTags1_->SaveEff("#mu acc N_{jet}=2, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags1_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags1_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags1_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags1_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags1_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags1_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets7Inf_BTags1_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  MuAccHTMHT_NJets2_BTags2Inf_->SaveEff("#mu acc N_{jet}=2, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags2Inf_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags2Inf_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags2Inf_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags2Inf_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags2Inf_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags2Inf_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets7Inf_BTags2Inf_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);
  MuAccHTMHT_NJets3_BTags2_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags2_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags2_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags2_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags2_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags2_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets7Inf_BTags2_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets3_BTags3Inf_->SaveEff("#mu acc N_{jet}=3, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags3Inf_->SaveEff("#mu acc N_{jet}=4, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags3Inf_->SaveEff("#mu acc N_{jet}=5, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags3Inf_->SaveEff("#mu acc N_{jet}=6, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags3Inf_->SaveEff("#mu acc N_{jet}=7-8, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags3Inf_->SaveEff("#mu acc N_{jet}=9+, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 
  MuAccHTMHT_NJets7Inf_BTags3Inf_->SaveEff("#mu acc N_{jet}=7+, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies); 

  //elec
  //1D
  ElecAccBTag_->SaveEff("e acc; N_{b-jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccNJets_->SaveEff("e acc; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHT_->SaveEff("e acc; H_{T} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccMHT_->SaveEff("e acc; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccDTT_->SaveEff("e acc; 0.5*(1-cosDTT); #varepsilon_{Acc}^{e}", dEfficiencies);

  // 2D 
  ElecAccHTNJets_->SaveEff("e acc; H_{T} [GeV]; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_->SaveEff("e acc; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccMHTNJets_->SaveEff("e acc; H_{T}^{miss} [GeV]; N_{jet}", dEfficiencies);   
  ElecAccBTagNJets_->SaveEff("e acc; N_{b-jet}; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccMHTNJetsB0_->SaveEff("e acc N_{b-jet}=0; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccMHTNJetsB1_Inf_->SaveEff("e acc N_{b-jet}#geq1; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets26_->SaveEff("e acc N_{jet}=2-6;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets2_->SaveEff("e acc N_{jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets3_->SaveEff("e acc N_{jet}=3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_->SaveEff("e acc N_{jet}=4;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_->SaveEff("e acc N_{jet}=5;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_->SaveEff("e acc N_{jet}=6;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_->SaveEff("e acc N_{jet}=7-8;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_->SaveEff("e acc N_{jet}=9+;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets7Inf_->SaveEff("e acc N_{jet}#geq7;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHTB0_->SaveEff("e acc N_{b-jet}=0;H_{T} [GeV] ; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHTB1_Inf_->SaveEff("e acc N_{b-jet}#geq1; H_{T} [GeV]; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{Acc}^{e}", dEfficiencies); 

  ElecAccHTMHT_NJets2_BTags0_->SaveEff("e acc N_{jet}=2, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags0_->SaveEff("e acc N_{jet}=3, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags0_->SaveEff("e acc N_{jet}=4, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags0_->SaveEff("e acc N_{jet}=5, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags0_->SaveEff("e acc N_{jet}=6, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags0_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags0_->SaveEff("e acc N_{jet}=9+, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccHTMHT_NJets7Inf_BTags0_->SaveEff("e acc N_{jet}=7+, N_{b-jet}=0;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags1Inf_->SaveEff("e acc N_{jet}=2, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags1Inf_->SaveEff("e acc N_{jet}=3, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags1Inf_->SaveEff("e acc N_{jet}=4, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags1Inf_->SaveEff("e acc N_{jet}=5, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags1Inf_->SaveEff("e acc N_{jet}=6, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags1Inf_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags1Inf_->SaveEff("e acc N_{jet}=9+, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);  
  ElecAccHTMHT_NJets7Inf_BTags1Inf_->SaveEff("e acc N_{jet}=7+, N_{b-jet}#geq1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags1_->SaveEff("e acc N_{jet}=2, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags1_->SaveEff("e acc N_{jet}=3, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags1_->SaveEff("e acc N_{jet}=4, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags1_->SaveEff("e acc N_{jet}=5, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags1_->SaveEff("e acc N_{jet}=6, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags1_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags1_->SaveEff("e acc N_{jet}=9+, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 
  ElecAccHTMHT_NJets7Inf_BTags1_->SaveEff("e acc N_{jet}=7+, N_{b-jet}=1;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags2Inf_->SaveEff("e acc N_{jet}=2, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags2Inf_->SaveEff("e acc N_{jet}=3, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags2Inf_->SaveEff("e acc N_{jet}=4, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags2Inf_->SaveEff("e acc N_{jet}=5, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags2Inf_->SaveEff("e acc N_{jet}=6, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags2Inf_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags2Inf_->SaveEff("e acc N_{jet}=9+, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 
  ElecAccHTMHT_NJets7Inf_BTags2Inf_->SaveEff("e acc N_{jet}=7+, N_{b-jet}#geq2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);
  ElecAccHTMHT_NJets3_BTags2_->SaveEff("e acc N_{jet}=3, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags2_->SaveEff("e acc N_{jet}=4, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags2_->SaveEff("e acc N_{jet}=5, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags2_->SaveEff("e acc N_{jet}=6, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags2_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags2_->SaveEff("e acc N_{jet}=9+, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 
  ElecAccHTMHT_NJets7Inf_BTags2_->SaveEff("e acc N_{jet}=7+, N_{b-jet}=2;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 
  ElecAccHTMHT_NJets3_BTags3Inf_->SaveEff("e acc N_{jet}=3, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags3Inf_->SaveEff("e acc N_{jet}=4, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags3Inf_->SaveEff("e acc N_{jet}=5, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags3Inf_->SaveEff("e acc N_{jet}=6, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags3Inf_->SaveEff("e acc N_{jet}=7-8, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags3Inf_->SaveEff("e acc N_{jet}=9+, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 
  ElecAccHTMHT_NJets7Inf_BTags3Inf_->SaveEff("e acc N_{jet}=7+, N_{b-jet}#geq3;H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies); 

  // reco
  //muon
  //1D
  MuRecoBTag_->SaveEff("#mu reco; N_{b-jet}; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoNJets_->SaveEff("#mu reco; N_{jet}; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoHT_->SaveEff("#mu reco; H_{T} [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoMHT_->SaveEff("#mu reco; H_{T}^{miss} [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoRelPTJet_->SaveEff("#mu reco; p_{T}(#mu)/Jet p_{T}; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoDeltaRJet_->SaveEff("#mu reco; #DeltaR; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoRelPTDeltaRJet_->SaveEff("#mu reco; p_{T}(#mu)/Jet p_{T}; #DeltaR; #varepsilon_{Id}^{#mu}", dEfficiencies);   

  //elec
  //1D
  ElecRecoBTag_->SaveEff("e reco; N_{b-jet}; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoNJets_->SaveEff("e reco; N_{jet}; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoHT_->SaveEff("e reco; H_{T} [GeV]; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoMHT_->SaveEff("e reco; H_{T}^{miss} [GeV]; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoRelPTJet_->SaveEff("e reco; p_{T}(e)/Jet p_{T}; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoDeltaRJet_->SaveEff("e reco; #DeltaR; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoRelPTDeltaRJet_->SaveEff("e reco; p_{T}(e)/Jet p_{T}; #DeltaR; #varepsilon_{Id}^{e}", dEfficiencies);   

  // iso
  //muon
  //1D
  MuIsoBTag_->SaveEff("#mu iso; N_{b-jet}; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoNJets_->SaveEff("#mu iso; N_{jet}; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoHT_->SaveEff("#mu iso; H_{T} [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoMHT_->SaveEff("#mu iso; H_{T}^{miss} [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoRelPTJet_->SaveEff("#mu iso; p_{T}(#mu)/Jet p_{T}; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoDeltaRJet_->SaveEff("#mu iso; #DeltaR; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoRelPTDeltaRJet_->SaveEff("#mu iso; p_{T}(#mu)/Jet p_{T}; #DeltaR; #varepsilon_{Iso}^{#mu}", dEfficiencies);   

  //elec
  //1D
  ElecIsoBTag_->SaveEff("e iso; N_{b-jet}; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoNJets_->SaveEff("e iso; N_{jet}; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoHT_->SaveEff("e iso; H_{T} [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoMHT_->SaveEff("e iso; H_{T}^{miss} [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoRelPTJet_->SaveEff("e iso; p_{T}(e)/Jet p_{T}; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoDeltaRJet_->SaveEff("e iso; #DeltaR; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoRelPTDeltaRJet_->SaveEff("e iso; p_{T}(e)/Jet p_{T}; #DeltaR; #varepsilon_{Iso}^{e}", dEfficiencies);   

  // m_{T}^{W}
  //muon
  //1D
  MuMTWBTag_->SaveEff("#mu m_{T}^{W}; N_{b-jet}; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);   
  MuMTWNJets_->SaveEff("#mu m_{T}^{W}; N_{jet}; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);   
  MuMTWHT_->SaveEff("#mu m_{T}^{W}; H_{T} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);   
  MuMTWMHT_->SaveEff("#mu m_{T}^{W}; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);   
  MuMTWPTActivity_->SaveEff("#mu m_{T}^{W};  Activity; p_{T}(#mu) [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies, true);
  MuMTWHTNJets_->SaveEff("#mu m_{T}(w); H_{T} [GeV]; N_{jet}; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWMHTNJets_->SaveEff("#mu m_{T}(w); H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_->SaveEff("#mu m_{T}(w); H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets24_->SaveEff("#mu m_{T}(w) N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets56_->SaveEff("#mu m_{T}(w) N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets7Inf_->SaveEff("#mu m_{T}(w) N_{jet}=7+; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);

  MuMTWHTMHT_NJets2_->SaveEff("#mu m_{T}(w) N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets3_->SaveEff("#mu m_{T}(w) N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets4_->SaveEff("#mu m_{T}(w) N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets5_->SaveEff("#mu m_{T}(w) N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets6_->SaveEff("#mu m_{T}(w) N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets78_->SaveEff("#mu m_{T}(w) N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);
  MuMTWHTMHT_NJets9Inf_->SaveEff("#mu m_{T}(w) N_{jet}=9+; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);


  //muon
  //1D
  MuDiLepBTag_->SaveEff("#mu di lep; N_{b-jet}; #beta_{1l}^{#mu}", dEfficiencies);   
  MuDiLepNJets_->SaveEff("#mu di lep; N_{jet}; #beta_{1l}^{#mu}", dEfficiencies);   
  MuDiLepHT_->SaveEff("#mu di lep; H_{T} [GeV]; #beta_{1l}^{#mu}", dEfficiencies);   
  MuDiLepMHT_->SaveEff("#mu di lep; H_{T}^{miss} [GeV]; #beta_{1l}^{#mu}", dEfficiencies);  

  MuDiLepEffBTag_->SaveEff("#mu dilep eff; N_{b-jet}; #varepsilon_{2l,SR,old}^{#mu}", dEfficiencies);   
  MuDiLepEffNJets_->SaveEff("#mu dilep eff; N_{jet}; #varepsilon_{2l,SR,old}^{#mu}", dEfficiencies);   
  MuDiLepEffHT_->SaveEff("#mu dilep eff; H_{T} [GeV]; #varepsilon_{2l,SR,old}^{#mu}", dEfficiencies);   
  MuDiLepEffMHT_->SaveEff("#mu dilep eff; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,old}^{#mu}", dEfficiencies);
  MuDiLepEffNJetsBTags_->SaveEff("#mu dilep eff; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR,old}^{#mu}", dEfficiencies);
  //muon
  //1D
  MuDiLepContributionBTag_->SaveEff("#mu di lep contri; N_{b-jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepContributionNJets_->SaveEff("#mu di lep contri; N_{jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepContributionHT_->SaveEff("#mu di lep contri; H_{T} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepContributionMHT_->SaveEff("#mu di lep contri; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepFractionBTag_->SaveEff("#mu di lep contri; N_{b-jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepFractionNJets_->SaveEff("#mu di lep contri; N_{jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepFractionHT_->SaveEff("#mu di lep contri; H_{T} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepFractionMHT_->SaveEff("#mu di lep contri; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies); 

  //elec
  //1D
  
  ElecDiLepBTag_->SaveEff("e di lep; N_{b-jet}; #beta_{1l}^{#mu}", dEfficiencies);   
  ElecDiLepNJets_->SaveEff("e di lep; N_{jet}; #beta_{1l}^{#mu}", dEfficiencies);   
  ElecDiLepHT_->SaveEff("e di lep; H_{T} [GeV]; #beta_{1l}^{#mu}", dEfficiencies);   
  ElecDiLepMHT_->SaveEff("e di lep; H_{T}^{miss} [GeV]; #beta_{1l}^{#mu}", dEfficiencies);  

  ElecDiLepEffBTag_->SaveEff("e dilep eff; N_{b-jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepEffNJets_->SaveEff("e dilep eff; N_{jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepEffHT_->SaveEff("e dilep eff; H_{T} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepEffMHT_->SaveEff("e dilep eff; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);
  ElecDiLepEffNJetsBTags_->SaveEff("e dilep eff; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);
  
  ElecMTWBTag_->SaveEff("e m_{T}^{W}; N_{b-jet}; #varepsilon_{m_{T}}^{e}", dEfficiencies);   
  ElecMTWNJets_->SaveEff("e m_{T}^{W}; N_{jet}; #varepsilon_{m_{T}}^{e}", dEfficiencies);   
  ElecMTWHT_->SaveEff("e m_{T}^{W}; H_{T} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);   
  ElecMTWMHT_->SaveEff("e m_{T}^{W}; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);   
  ElecMTWPTActivity_->SaveEff("e m_{T}^{W}; Activity; p_{T}(e) [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies, true);
  ElecMTWHTNJets_->SaveEff("e m_{T}(w); H_{T} [GeV]; N_{jet}; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWMHTNJets_->SaveEff("e m_{T}(w); H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_->SaveEff("e m_{T}(w); H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets24_->SaveEff("e m_{T}(w) N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets56_->SaveEff("e m_{T}(w) N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets7Inf_->SaveEff("e m_{T}(w) N_{jet}=7+; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);

  ElecMTWHTMHT_NJets2_->SaveEff("e m_{T}(w) N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets3_->SaveEff("e m_{T}(w) N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets4_->SaveEff("e m_{T}(w) N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets5_->SaveEff("e m_{T}(w) N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets6_->SaveEff("e m_{T}(w) N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets78_->SaveEff("e m_{T}(w) N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);
  ElecMTWHTMHT_NJets9Inf_->SaveEff("e m_{T}(w) N_{jet}=9+; H_{T} [GeV]; H_{T}^{miss} [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);

  //elec
  //1D
  ElecDiLepContributionBTag_->SaveEff("e di lep contri; N_{b-jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepContributionNJets_->SaveEff("e di lep contri; N_{jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepContributionHT_->SaveEff("e di lep contri; H_{T} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepContributionMHT_->SaveEff("e di lep contri; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);
  ElecDiLepFractionBTag_->SaveEff("e di lep contri; N_{b-jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepFractionNJets_->SaveEff("e di lep contri; N_{jet}; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepFractionHT_->SaveEff("e di lep contri; H_{T} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);   
  ElecDiLepFractionMHT_->SaveEff("e di lep contri; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,old}^{e}", dEfficiencies);  

  MuDiLepCRBTag_->SaveEff("#mu dilep contrib CR; N_{b-jet}; #beta_{1l,cr}^{#mu}", dEfficiencies);   
  MuDiLepCRNJets_->SaveEff("#mu dilep contrib CR; N_{jet}; #beta_{1l,cr}^{#mu}", dEfficiencies);   
  MuDiLepCRHT_->SaveEff("#mu dilep contrib CR; H_{T} [GeV]; #beta_{1l,cr}^{#mu}", dEfficiencies);   
  MuDiLepCRMHT_->SaveEff("#mu dilep contrib CR; H_{T}^{miss} [GeV]; #beta_{1l,cr}^{#mu}", dEfficiencies);
  MuDiLepCRMHTNJets_->SaveEff("#mu dilep contrib CR; H_{T}^{miss} [GeV]; N_{jet}; #beta_{1l,cr}^{#mu}", dEfficiencies);
  MuDiLepCRNJetsBTags_->SaveEff("#mu dilep contrib CR; N_{jet}; N_{b-jet}; #beta_{1l,cr}^{#mu}", dEfficiencies);

  ElecDiLepCRBTag_->SaveEff("e dilep contrib CR; N_{b-jet}; #beta_{1l,cr}^{e}", dEfficiencies);   
  ElecDiLepCRNJets_->SaveEff("e dilep contrib CR; N_{jet}; #beta_{1l,cr}^{e}", dEfficiencies);   
  ElecDiLepCRHT_->SaveEff("e dilep contrib CR; H_{T} [GeV]; #beta_{1l,cr}^{e}", dEfficiencies);   
  ElecDiLepCRMHT_->SaveEff("e dilep contrib CR; H_{T}^{miss} [GeV]; #beta_{1l,cr}^{e}", dEfficiencies);
  ElecDiLepCRMHTNJets_->SaveEff("e dilep contrib CR; H_{T}^{miss} [GeV]; N_{jet}; #beta_{1l,cr}^{e}", dEfficiencies);
  ElecDiLepCRNJetsBTags_->SaveEff("e dilep contrib CR; N_{jet}; N_{b-jet}; #beta_{1l,cr}^{e}", dEfficiencies);

  MuDiLepSRBTag_->SaveEff("#mu dilep contrib SR; N_{b-jet}; f_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRNJets_->SaveEff("#mu dilep contrib SR; N_{jet}; f_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRHT_->SaveEff("#mu dilep contrib SR; H_{T} [GeV]; f_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRMHT_->SaveEff("#mu dilep contrib SR; H_{T}^{miss} [GeV]; f_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRMHTNJets_->SaveEff("#mu dilep contrib SR; H_{T}^{miss} [GeV]; N_{jet}; f_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRNJetsBTags_->SaveEff("#mu dilep contrib SR; N_{jet}; N_{b-jet}; f_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRSearchBins_->SaveEff("#mu dilep contrib SR; N_{jet}; Search region bin number; f_{2l,SR}^{#mu}", dEfficiencies);

  ElecDiLepSRBTag_->SaveEff("e dilep contrib SR; N_{b-jet}; f_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRNJets_->SaveEff("e dilep contrib SR; N_{jet}; f_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRHT_->SaveEff("e dilep contrib SR; H_{T} [GeV]; f_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRMHT_->SaveEff("e dilep contrib SR; H_{T}^{miss} [GeV]; f_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRMHTNJets_->SaveEff("e dilep contrib SR; H_{T}^{miss} [GeV]; N_{jet}; f_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRNJetsBTags_->SaveEff("e dilep contrib SR; N_{jet}; N_{b-jet}; f_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRSearchBins_->SaveEff("e dilep contrib SR; N_{jet}; Search region bin number; f_{2l,SR}^{e}", dEfficiencies);

  MuDiLepSRwoVetoBTag_->SaveEff("#mu dilep contrib SRwoVeto; N_{b-jet}; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoNJets_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoHT_->SaveEff("#mu dilep contrib SRwoVeto; H_{T} [GeV]; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoMHT_->SaveEff("#mu dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoMHTNJets_->SaveEff("#mu dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; N_{jet}; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoNJetsBTags_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; N_{b-jet}; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoSearchBins_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; Search region bin number; f_{2l,SR,woVeto}^{#mu}", dEfficiencies);

  ElecDiLepSRwoVetoBTag_->SaveEff("e dilep contrib SRwoVeto; N_{b-jet}; f_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoNJets_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; f_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoHT_->SaveEff("e dilep contrib SRwoVeto; H_{T} [GeV]; f_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoMHT_->SaveEff("e dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; f_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoMHTNJets_->SaveEff("e dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; N_{jet}; f_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoNJetsBTags_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; N_{b-jet}; f_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoSearchBins_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; Search region bin number; f_{2l,SR,woVeto}^{e}", dEfficiencies);

  MuDiLepSRBTagEff_->SaveEff("#mu dilep contrib SR; N_{b-jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRNJetsEff_->SaveEff("#mu dilep contrib SR; N_{jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRHTEff_->SaveEff("#mu dilep contrib SR; H_{T} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);   
  MuDiLepSRMHTEff_->SaveEff("#mu dilep contrib SR; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRMHTNJetsEff_->SaveEff("#mu dilep contrib SR; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRNJetsBTagsEff_->SaveEff("#mu dilep contrib SR; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);
  MuDiLepSRSearchBinsEff_->SaveEff("#mu dilep contrib SR; N_{jet}; Search region bin number; #varepsilon_{2l,SR}^{#mu}", dEfficiencies);

  ElecDiLepSRBTagEff_->SaveEff("e dilep contrib SR; N_{b-jet}; #varepsilon_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRNJetsEff_->SaveEff("e dilep contrib SR; N_{jet}; #varepsilon_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRHTEff_->SaveEff("e dilep contrib SR; H_{T} [GeV]; #varepsilon_{2l,SR}^{e}", dEfficiencies);   
  ElecDiLepSRMHTEff_->SaveEff("e dilep contrib SR; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRMHTNJetsEff_->SaveEff("e dilep contrib SR; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRNJetsBTagsEff_->SaveEff("e dilep contrib SR; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR}^{e}", dEfficiencies);
  ElecDiLepSRSearchBinsEff_->SaveEff("e dilep contrib SR; N_{jet}; Search region bin number; #varepsilon_{2l,SR}^{e}", dEfficiencies);

  MuDiLepSRwoVetoBTagEff_->SaveEff("#mu dilep contrib SRwoVeto; N_{b-jet}; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoNJetsEff_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoHTEff_->SaveEff("#mu dilep contrib SRwoVeto; H_{T} [GeV]; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);   
  MuDiLepSRwoVetoMHTEff_->SaveEff("#mu dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoMHTNJetsEff_->SaveEff("#mu dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoNJetsBTagsEff_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);
  MuDiLepSRwoVetoSearchBinsEff_->SaveEff("#mu dilep contrib SRwoVeto; N_{jet}; Search region bin number; #varepsilon_{2l,SR,woVeto}^{#mu}", dEfficiencies);

  ElecDiLepSRwoVetoBTagEff_->SaveEff("e dilep contrib SRwoVeto; N_{b-jet}; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoNJetsEff_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoHTEff_->SaveEff("e dilep contrib SRwoVeto; H_{T} [GeV]; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);   
  ElecDiLepSRwoVetoMHTEff_->SaveEff("e dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoMHTNJetsEff_->SaveEff("e dilep contrib SRwoVeto; H_{T}^{miss} [GeV]; N_{jet}; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoNJetsBTagsEff_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; N_{b-jet}; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);
  ElecDiLepSRwoVetoSearchBinsEff_->SaveEff("e dilep contrib SRwoVeto; N_{jet}; Search region bin number; #varepsilon_{2l,SR,woVeto}^{e}", dEfficiencies);

  
  // pt and activity  
  //muon
  MuPurityOldPT_->SaveEff("#mu purity; p_{T}(#mu) [GeV]; #beta_{old}^{#mu}", dEfficiencies);   
  MuPurityOldActivity_->SaveEff("#mu purity; Activity; #beta_{old}^{#mu}", dEfficiencies, true);   
  MuAccPT_->SaveEff("#mu acc; p_{T}(#mu) [GeV]; #varepsilon_{Acc}^{#mu}", dEfficiencies);   
  MuAccActivity_->SaveEff("#mu acc; Activity; #varepsilon_{Acc}^{#mu}", dEfficiencies, true);   
  MuRecoPT_->SaveEff("#mu reco; p_{T}(#mu) [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies);   
  MuRecoActivity_->SaveEff("#mu reco; Activity; #varepsilon_{Id}^{#mu}", dEfficiencies, true);   
  MuRecoActivityPT_->SaveEff("#mu reco; Activity; p_{T}(#mu) [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies, true);   
  MuIsoPT_->SaveEff("#mu iso; p_{T}(#mu) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies);   
  MuIsoActivity_->SaveEff("#mu iso; Activity; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);   
  MuMTWPT_->SaveEff("#mu m_{T}^{W}; p_{T}(#mu) [GeV]; #varepsilon_{m_{T}}^{#mu}", dEfficiencies);   
  MuMTWActivity_->SaveEff("#mu m_{T}^{W}; Activity; #varepsilon_{m_{T}}^{#mu}", dEfficiencies, true);   
  MuIsoActivityPT_->SaveEff("#mu Iso; Activity; p_{T}(#mu) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);   
  MuRecoPTEta_->SaveEff("#mu reco; p_{T}(#mu) [GeV]; #eta(#mu); #varepsilon_{Id}^{#mu}", dEfficiencies, true);   
  MuIsoPTEta_->SaveEff("#mu iso; p_{T}(#mu) [GeV]; #eta(#mu); #varepsilon_{Id}^{#mu}", dEfficiencies, true);   

  MuIsoActivityPTBTags0_->SaveEff("#mu Iso; Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);   
  MuRecoPTEtaBTags0_->SaveEff("#mu reco; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Id}^{#mu}", dEfficiencies, true);   
  MuIsoActivityPTBTags1Inf_->SaveEff("#mu Iso; Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);   
  MuRecoPTEtaBTags1Inf_->SaveEff("#mu reco; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Id}^{#mu}", dEfficiencies, true);   

  //elec
  ElecPurityOldPT_->SaveEff("e purity; p_{T}(e) [GeV]; #beta_{old}^{e}", dEfficiencies);   
  ElecPurityOldActivity_->SaveEff("e purity; Activity; #beta_{old}^{e}", dEfficiencies, true);   
  ElecAccPT_->SaveEff("e acc; p_{T}(e) [GeV]; #varepsilon_{Acc}^{e}", dEfficiencies);   
  ElecAccActivity_->SaveEff("e acc; Activity; #varepsilon_{Acc}^{e}", dEfficiencies, true);   
  ElecRecoPT_->SaveEff("e reco; p_{T}(e) [GeV]; #varepsilon_{Id}^{e}", dEfficiencies);   
  ElecRecoActivity_->SaveEff("e reco; Activity; #varepsilon_{Id}^{e}", dEfficiencies, true);   
  ElecRecoActivityPT_->SaveEff("e reco; Activity; p_{T}(e) [GeV]; #varepsilon_{Id}^{e}", dEfficiencies, true);   
  ElecIsoPT_->SaveEff("e iso; p_{T}(e) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies);   
  ElecIsoActivity_->SaveEff("e iso; Activity; #varepsilon_{Iso}^{e}", dEfficiencies, true);   
  ElecMTWPT_->SaveEff("e m_{T}^{W}; p_{T}(e) [GeV]; #varepsilon_{m_{T}}^{e}", dEfficiencies);   
  ElecMTWActivity_->SaveEff("e m_{T}^{W}; Activity; #varepsilon_{m_{T}}^{e}", dEfficiencies, true);   
  ElecIsoActivityPT_->SaveEff("e Iso; Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies, true);   
  ElecRecoPTEta_->SaveEff("e reco; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Id}^{e}", dEfficiencies, true);  
  ElecIsoPTEta_->SaveEff("e iso; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Iso}^{e}", dEfficiencies, true); 

  ElecIsoActivityPTBTags0_->SaveEff("e Iso; Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies, true);   
  ElecRecoPTEtaBTags0_->SaveEff("e reco; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Id}^{e}", dEfficiencies, true);   
  ElecIsoActivityPTBTags1Inf_->SaveEff("e Iso; Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies, true);   
  ElecRecoPTEtaBTags1Inf_->SaveEff("e reco; p_{T}(e) [GeV]; #eta(e); #varepsilon_{Id}^{e}", dEfficiencies, true);   

  // NEW
  MuRecoActivityPTBarrel_->SaveEff("#mu Reco (barrel); Activity; p_{T}(#mu) [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies, true);
  MuIsoActivityPTBarrel_->SaveEff("#mu Iso (barrel); Activity; p_{T}(#mu) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);
  ElecRecoActivityPTBarrel_->SaveEff("e Reco (barrel); Activity; p_{T}(e) [GeV]; #varepsilon_{Id}^{#mu}", dEfficiencies, true);
  ElecIsoActivityPTBarrel_->SaveEff("e Iso (barrel); Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{#mu}", dEfficiencies, true);

  MuRecoActivityPTDisk_->SaveEff("#mu Reco (disk); Activity; p_{T}(#mu) [GeV]; #varepsilon_{Id}^{e}", dEfficiencies, true);
  MuIsoActivityPTDisk_->SaveEff("#mu Iso (disk); Activity; p_{T}(#mu) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies, true);
  ElecRecoActivityPTDisk_->SaveEff("e Reco (disk); Activity; p_{T}(e) [GeV]; #varepsilon_{Id}^{e}", dEfficiencies, true);
  ElecIsoActivityPTDisk_->SaveEff("e Iso (disk); Activity; p_{T}(e) [GeV]; #varepsilon_{Iso}^{e}", dEfficiencies, true);


  //Isotracks
  //1D
  ExpectationReductionIsoTrackBTagEff_->SaveEff("iso track expec. reduction; N_{b-jet}", dEfficiencies);   
  ExpectationReductionIsoTrackNJetsEff_->SaveEff("iso track expec. reduction; N_{jet}", dEfficiencies);   
  ExpectationReductionIsoTrackHTEff_->SaveEff("iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionIsoTrackMHTEff_->SaveEff("iso track expec. reduction; H_{T}^{miss} [GeV]", dEfficiencies);   
  ExpectationReductionIsoTrackPTEff_->SaveEff("iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionIsoTrackActivityEff_->SaveEff("iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  IsoTrackReductionHTNJets_->SaveEff("iso track expec. reduction; H_{T} [GeV]; N_{jet}", dEfficiencies);
  IsoTrackReductionHTMHT_NJets24_->SaveEff("iso track expec. reduction N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets56_->SaveEff("iso track expec. reduction N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets7Inf_->SaveEff("iso track expec. reduction N_{jet}#geq7; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets2_->SaveEff("iso track expec. reduction N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets3_->SaveEff("iso track expec. reduction N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets4_->SaveEff("iso track expec. reduction N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets5_->SaveEff("iso track expec. reduction N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets6_->SaveEff("iso track expec. reduction N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets78_->SaveEff("iso track expec. reduction N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets9Inf_->SaveEff("iso track expec. reduction N_{jet}#geq9; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionMHTNJets_->SaveEff("iso track expec. reduction; H_{T}^{miss} [GeV]; N_{jet}", dEfficiencies);   
  IsoTrackReductionBTagNJets_->SaveEff("iso track expec. reduction; N_{b-jet}; N_{jet}", dEfficiencies);   
  IsoTrackReductionPTActivity_->SaveEff("iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true);   

  IsoTrackReductionHTMHT_NJets24_BTags0_->SaveEff("iso track expec. reduction N_{jet}=2-4, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets56_BTags0_->SaveEff("iso track expec. reduction N_{jet}=5-6, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets7Inf_BTags0_->SaveEff("iso track expec. reduction N_{jet}#geq7, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets24_BTags1Inf_->SaveEff("iso track expec. reduction N_{jet}=3-4, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets56_BTags1Inf_->SaveEff("iso track expec. reduction N_{jet}=5-6, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->SaveEff("iso track expec. reduction N_{jet}#geq7, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  // mu iso tracks
  //1D
  ExpectationReductionMuIsoTrackBTagEff_->SaveEff("#mu iso track expec. reduction; N_{b-jet}", dEfficiencies);   
  ExpectationReductionMuIsoTrackNJetsEff_->SaveEff("#mu iso track expec. reduction; N_{jet}", dEfficiencies);   
  ExpectationReductionMuIsoTrackHTEff_->SaveEff("#mu iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionMuIsoTrackMHTEff_->SaveEff("#mu iso track expec. reduction; H_{T}^{miss} [GeV]", dEfficiencies);   
  ExpectationReductionMuIsoTrackPTEff_->SaveEff("#mu iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionMuIsoTrackActivityEff_->SaveEff("#mu iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  MuIsoTrackReductionHTNJets_->SaveEff("#mu iso track expec. reduction; H_{T} [GeV]; N_{jet}", dEfficiencies);   
  MuIsoTrackReductionMHTNJets_->SaveEff("#mu iso track expec. reduction; H_{T}^{miss} [GeV]; N_{jet}", dEfficiencies);   
  MuIsoTrackReductionBTagNJets_->SaveEff("#mu iso track expec. reduction; N_{b-jet}; N_{jet}", dEfficiencies);   
  MuIsoTrackReductionPTActivity_->SaveEff("#mu iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true); 
  
  MuIsoTrackReductionHTMHT_NJets24_->SaveEff("#mu iso track expec. reduction N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets56_->SaveEff("#mu iso track expec. reduction N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets7Inf_->SaveEff("#mu iso track expec. reduction N_{jet}#geq7; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets2_->SaveEff("#mu iso track expec. reduction N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets3_->SaveEff("#mu iso track expec. reduction N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets4_->SaveEff("#mu iso track expec. reduction N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets5_->SaveEff("#mu iso track expec. reduction N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets6_->SaveEff("#mu iso track expec. reduction N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets78_->SaveEff("#mu iso track expec. reduction N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets9Inf_->SaveEff("#mu iso track expec. reduction N_{jet}#geq9; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  MuIsoTrackReductionHTMHT_NJets24_BTags0_->SaveEff("#mu iso track expec. reduction N_{jet}=2-4, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets56_BTags0_->SaveEff("#mu iso track expec. reduction N_{jet}=5-6, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets7Inf_BTags0_->SaveEff("#mu iso track expec. reduction N_{jet}#geq7, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets24_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{jet}=2-4, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets56_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{jet}=5-6, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{jet}#geq7, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  // elec iso tracks
  //1D
  ExpectationReductionElecIsoTrackBTagEff_->SaveEff("e iso track expec. reduction; N_{b-jet}", dEfficiencies);   
  ExpectationReductionElecIsoTrackNJetsEff_->SaveEff("e iso track expec. reduction; N_{jet}", dEfficiencies);   
  ExpectationReductionElecIsoTrackHTEff_->SaveEff("e iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionElecIsoTrackMHTEff_->SaveEff("e iso track expec. reduction; H_{T}^{miss} [GeV]", dEfficiencies);   
  ExpectationReductionElecIsoTrackPTEff_->SaveEff("e iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionElecIsoTrackActivityEff_->SaveEff("e iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  ElecIsoTrackReductionHTNJets_->SaveEff("e iso track expec. reduction; H_{T} [GeV]; N_{jet}", dEfficiencies);   
  ElecIsoTrackReductionMHTNJets_->SaveEff("e iso track expec. reduction; H_{T}^{miss} [GeV]; N_{jet}", dEfficiencies);   
  ElecIsoTrackReductionBTagNJets_->SaveEff("e iso track expec. reduction; N_{b-jet}; N_{jet}", dEfficiencies);   
  ElecIsoTrackReductionPTActivity_->SaveEff("e iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true); 
  
  ElecIsoTrackReductionHTMHT_NJets24_->SaveEff("e iso track expec. reduction N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets56_->SaveEff("e iso track expec. reduction N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets7Inf_->SaveEff("e iso track expec. reduction N_{jet}#geq7; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets2_->SaveEff("e iso track expec. reduction N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets3_->SaveEff("e iso track expec. reduction N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets4_->SaveEff("e iso track expec. reduction N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets5_->SaveEff("e iso track expec. reduction N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets6_->SaveEff("e iso track expec. reduction N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets78_->SaveEff("e iso track expec. reduction N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets9Inf_->SaveEff("e iso track expec. reduction N_{jet}#geq9; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  ElecIsoTrackReductionHTMHT_NJets24_BTags0_->SaveEff("e iso track expec. reduction N_{jet}=2-4, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets56_BTags0_->SaveEff("e iso track expec. reduction N_{jet}=5-6, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets7Inf_BTags0_->SaveEff("e iso track expec. reduction N_{jet}#geq7, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets24_BTags1Inf_->SaveEff("e iso track expec. reduction N_{jet}=2-4, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets56_BTags1Inf_->SaveEff("e iso track expec. reduction N_{jet}=5-6, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->SaveEff("e iso track expec. reduction N_{jet}#geq7, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  
  // pion iso tracks
  //1D
  ExpectationReductionPionIsoTrackBTagEff_->SaveEff("#pi iso track expec. reduction; N_{b-jet}", dEfficiencies);   
  ExpectationReductionPionIsoTrackNJetsEff_->SaveEff("#pi iso track expec. reduction; N_{jet}", dEfficiencies);   
  ExpectationReductionPionIsoTrackHTEff_->SaveEff("#pi iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionPionIsoTrackMHTEff_->SaveEff("#pi iso track expec. reduction; H_{T}^{miss} [GeV]", dEfficiencies);   
  ExpectationReductionPionIsoTrackPTEff_->SaveEff("#pi iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionPionIsoTrackActivityEff_->SaveEff("#pi iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  PionIsoTrackReductionHTNJets_->SaveEff("#pi iso track expec. reduction; H_{T} [GeV]; N_{jet}", dEfficiencies);   
  PionIsoTrackReductionMHTNJets_->SaveEff("#pi iso track expec. reduction; H_{T}^{miss} [GeV]; N_{jet}", dEfficiencies);   
  PionIsoTrackReductionBTagNJets_->SaveEff("#pi iso track expec. reduction; N_{b-jet}; N_{jet}", dEfficiencies);   
  PionIsoTrackReductionPTActivity_->SaveEff("#pi iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true);
  
  PionIsoTrackReductionHTMHT_NJets24_->SaveEff("#pi iso track expec. reduction N_{jet}=2-4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets56_->SaveEff("#pi iso track expec. reduction N_{jet}=5-6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets7Inf_->SaveEff("#pi iso track expec. reduction N_{jet}#geq7; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets2_->SaveEff("#pi iso track expec. reduction N_{jet}=2; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets3_->SaveEff("#pi iso track expec. reduction N_{jet}=3; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets4_->SaveEff("#pi iso track expec. reduction N_{jet}=4; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets5_->SaveEff("#pi iso track expec. reduction N_{jet}=5; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets6_->SaveEff("#pi iso track expec. reduction N_{jet}=6; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets78_->SaveEff("#pi iso track expec. reduction N_{jet}=7-8; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets9Inf_->SaveEff("#pi iso track expec. reduction N_{jet}#geq9; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  PionIsoTrackReductionHTMHT_NJets24_BTags0_->SaveEff("#pi iso track expec. reduction N_{jet}=2-4, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets56_BTags0_->SaveEff("#pi iso track expec. reduction N_{jet}=5-6, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets7Inf_BTags0_->SaveEff("#pi iso track expec. reduction N_{jet}#geq7, N_{b-jet}=0; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets24_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{jet}=2-4, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets56_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{jet}=5-6, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJets7Inf_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{jet}#geq7, N_{b-jet}=1+; H_{T} [GeV]; H_{T}^{miss} [GeV]", dEfficiencies);

  if(doAdditionalPlots){
    outPutFile->cd();
    outPutFile->mkdir("FractionsIsoTrack");
    TDirectory *dFractionsIsoTrack = (TDirectory*)outPutFile->Get("FractionsIsoTrack");
    dFractionsIsoTrack->cd();
    IsoTrackFractionPTActivity_->SaveEff("iso track fraction; Activity; p_{T} [GeV]; fraction of events [%]", dFractionsIsoTrack, true, true, true);
    MuIsoTrackFractionPTActivity_->SaveEff("mu iso track fraction; Activity; p_{T} [GeV]; fraction of events [%]", dFractionsIsoTrack, true, true, true);
    ElecIsoTrackFractionPTActivity_->SaveEff("elec iso track fraction; Activity; p_{T} [GeV]; fraction of events [%]", dFractionsIsoTrack, true, true, true);
    PionIsoTrackFractionPTActivity_->SaveEff("pion iso track fraction; Activity; p_{T} [GeV]; fraction of events [%]", dFractionsIsoTrack, true, true, true);

    if(doTAPplots){
      TrackIsolationPTActivity_->SaveEff("track isolation; Activity; p_{T} [GeV]; #varepsilon_{trk}^{iso}", dEfficiencies, true, true);
      MuTrackIsolationPTActivity_->SaveEff("mu track isolation; Activity; p_{T} [GeV]; #varepsilon_{#mu trk}^{iso}", dEfficiencies, true, true);
      ElecTrackIsolationPTActivity_->SaveEff("elec track isolation; Activity; p_{T} [GeV]; #varepsilon_{e trk}^{iso}", dEfficiencies, true, true);
      PionTrackIsolationPTActivity_->SaveEff("pion track isolation; Activity; p_{T} [GeV]; #varepsilon_{#pi trk}^{iso}", dEfficiencies, true, true);
    }

    TH1D *MuWoVetoFracHT_ = (TH1D*) MuAccWoVetoFracHT_->Clone("MuWoVetoFracHT");
    MuWoVetoFracHT_->Add(MuRecoWoVetoFracHT_);
    MuWoVetoFracHT_->Add(MuIsoWoVetoFracHT_);
    TH1D *MuWoVetoFracMHT_ = (TH1D*) MuAccWoVetoFracMHT_->Clone("MuWoVetoFracMHT");
    MuWoVetoFracMHT_->Add(MuRecoWoVetoFracMHT_);
    MuWoVetoFracMHT_->Add(MuIsoWoVetoFracMHT_);
    TH1D *MuWoVetoFracNJets_ = (TH1D*) MuAccWoVetoFracNJets_->Clone("MuWoVetoFracNJets");
    MuWoVetoFracNJets_->Add(MuRecoWoVetoFracNJets_);
    MuWoVetoFracNJets_->Add(MuIsoWoVetoFracNJets_);
    TH1D *MuWoVetoFracBTags_ = (TH1D*) MuAccWoVetoFracBTags_->Clone("MuWoVetoFracBTags");
    MuWoVetoFracBTags_->Add(MuRecoWoVetoFracBTags_);
    MuWoVetoFracBTags_->Add(MuIsoWoVetoFracBTags_);

    TH1D *ElecWoVetoFracHT_ = (TH1D*) ElecAccWoVetoFracHT_->Clone("ElecWoVetoFracHT");
    ElecWoVetoFracHT_->Add(ElecRecoWoVetoFracHT_);
    ElecWoVetoFracHT_->Add(ElecIsoWoVetoFracHT_);
    TH1D *ElecWoVetoFracMHT_ = (TH1D*) ElecAccWoVetoFracMHT_->Clone("ElecWoVetoFracMHT");
    ElecWoVetoFracMHT_->Add(ElecRecoWoVetoFracMHT_);
    ElecWoVetoFracMHT_->Add(ElecIsoWoVetoFracMHT_);
    TH1D *ElecWoVetoFracNJets_ = (TH1D*) ElecAccWoVetoFracNJets_->Clone("ElecWoVetoFracNJets");
    ElecWoVetoFracNJets_->Add(ElecRecoWoVetoFracNJets_);
    ElecWoVetoFracNJets_->Add(ElecIsoWoVetoFracNJets_);
    TH1D *ElecWoVetoFracBTags_ = (TH1D*) ElecAccWoVetoFracBTags_->Clone("ElecWoVetoFracBTags");
    ElecWoVetoFracBTags_->Add(ElecRecoWoVetoFracBTags_);
    ElecWoVetoFracBTags_->Add(ElecIsoWoVetoFracBTags_);

    TH1D *MuFracHT_ = (TH1D*) MuAccFracHT_->Clone("MuFracHT");
    MuFracHT_->Add(MuRecoFracHT_);
    MuFracHT_->Add(MuIsoFracHT_);
    TH1D *MuFracMHT_ = (TH1D*) MuAccFracMHT_->Clone("MuFracMHT");
    MuFracMHT_->Add(MuRecoFracMHT_);
    MuFracMHT_->Add(MuIsoFracMHT_);
    TH1D *MuFracNJets_ = (TH1D*) MuAccFracNJets_->Clone("MuFracNJets");
    MuFracNJets_->Add(MuRecoFracNJets_);
    MuFracNJets_->Add(MuIsoFracNJets_);
    TH1D *MuFracBTags_ = (TH1D*) MuAccFracBTags_->Clone("MuFracBTags");
    MuFracBTags_->Add(MuRecoFracBTags_);
    MuFracBTags_->Add(MuIsoFracBTags_);

    TH1D *ElecFracHT_ = (TH1D*) ElecAccFracHT_->Clone("ElecFracHT");
    ElecFracHT_->Add(ElecRecoFracHT_);
    ElecFracHT_->Add(ElecIsoFracHT_);
    TH1D *ElecFracMHT_ = (TH1D*) ElecAccFracMHT_->Clone("ElecFracMHT");
    ElecFracMHT_->Add(ElecRecoFracMHT_);
    ElecFracMHT_->Add(ElecIsoFracMHT_);
    TH1D *ElecFracNJets_ = (TH1D*) ElecAccFracNJets_->Clone("ElecFracNJets");
    ElecFracNJets_->Add(ElecRecoFracNJets_);
    ElecFracNJets_->Add(ElecIsoFracNJets_);
    TH1D *ElecFracBTags_ = (TH1D*) ElecAccFracBTags_->Clone("ElecFracBTags");
    ElecFracBTags_->Add(ElecRecoFracBTags_);
    ElecFracBTags_->Add(ElecIsoFracBTags_);


  MuAccWoVetoFracHT_->Divide(MuWoVetoFracHT_);    
  MuAccWoVetoFracMHT_->Divide(MuWoVetoFracMHT_);    
  MuAccWoVetoFracNJets_->Divide(MuWoVetoFracNJets_);    
  MuAccWoVetoFracBTags_->Divide(MuWoVetoFracBTags_);

  MuRecoWoVetoFracHT_->Divide(MuWoVetoFracHT_);   
  MuRecoWoVetoFracMHT_->Divide(MuWoVetoFracMHT_);   
  MuRecoWoVetoFracNJets_->Divide(MuWoVetoFracNJets_);   
  MuRecoWoVetoFracBTags_->Divide(MuWoVetoFracBTags_);

  MuIsoWoVetoFracHT_->Divide(MuWoVetoFracHT_);    
  MuIsoWoVetoFracMHT_->Divide(MuWoVetoFracMHT_);    
  MuIsoWoVetoFracNJets_->Divide(MuWoVetoFracNJets_);    
  MuIsoWoVetoFracBTags_->Divide(MuWoVetoFracBTags_);

  ElecAccWoVetoFracHT_->Divide(ElecWoVetoFracHT_);    
  ElecAccWoVetoFracMHT_->Divide(ElecWoVetoFracMHT_);    
  ElecAccWoVetoFracNJets_->Divide(ElecWoVetoFracNJets_);    
  ElecAccWoVetoFracBTags_->Divide(ElecWoVetoFracBTags_);

  ElecRecoWoVetoFracHT_->Divide(ElecWoVetoFracHT_);   
  ElecRecoWoVetoFracMHT_->Divide(ElecWoVetoFracMHT_);   
  ElecRecoWoVetoFracNJets_->Divide(ElecWoVetoFracNJets_);   
  ElecRecoWoVetoFracBTags_->Divide(ElecWoVetoFracBTags_);

  ElecIsoWoVetoFracHT_->Divide(ElecWoVetoFracHT_);    
  ElecIsoWoVetoFracMHT_->Divide(ElecWoVetoFracMHT_);    
  ElecIsoWoVetoFracNJets_->Divide(ElecWoVetoFracNJets_);    
  ElecIsoWoVetoFracBTags_->Divide(ElecWoVetoFracBTags_);

  MuAccFracHT_->Divide(MuFracHT_);    
  MuAccFracMHT_->Divide(MuFracMHT_);    
  MuAccFracNJets_->Divide(MuFracNJets_);    
  MuAccFracBTags_->Divide(MuFracBTags_);

  MuRecoFracHT_->Divide(MuFracHT_);   
  MuRecoFracMHT_->Divide(MuFracMHT_);   
  MuRecoFracNJets_->Divide(MuFracNJets_);   
  MuRecoFracBTags_->Divide(MuFracBTags_);

  MuIsoFracHT_->Divide(MuFracHT_);    
  MuIsoFracMHT_->Divide(MuFracMHT_);    
  MuIsoFracNJets_->Divide(MuFracNJets_);    
  MuIsoFracBTags_->Divide(MuFracBTags_);

  ElecAccFracHT_->Divide(ElecFracHT_);    
  ElecAccFracMHT_->Divide(ElecFracMHT_);    
  ElecAccFracNJets_->Divide(ElecFracNJets_);    
  ElecAccFracBTags_->Divide(ElecFracBTags_);

  ElecRecoFracHT_->Divide(ElecFracHT_);   
  ElecRecoFracMHT_->Divide(ElecFracMHT_);   
  ElecRecoFracNJets_->Divide(ElecFracNJets_);   
  ElecRecoFracBTags_->Divide(ElecFracBTags_);

  ElecIsoFracHT_->Divide(ElecFracHT_);    
  ElecIsoFracMHT_->Divide(ElecFracMHT_);    
  ElecIsoFracNJets_->Divide(ElecFracNJets_);    
  ElecIsoFracBTags_->Divide(ElecFracBTags_);


  savePlot(MuAccWoVetoFracHT_);
  savePlot(MuAccWoVetoFracMHT_);
  savePlot(MuAccWoVetoFracNJets_);
  savePlot(MuAccWoVetoFracBTags_);

  savePlot(MuRecoWoVetoFracHT_);
  savePlot(MuRecoWoVetoFracMHT_);
  savePlot(MuRecoWoVetoFracNJets_);
  savePlot(MuRecoWoVetoFracBTags_);

  savePlot(MuIsoWoVetoFracHT_);
  savePlot(MuIsoWoVetoFracMHT_);
  savePlot(MuIsoWoVetoFracNJets_);
  savePlot(MuIsoWoVetoFracBTags_);

  savePlot(ElecAccWoVetoFracHT_);
  savePlot(ElecAccWoVetoFracMHT_);
  savePlot(ElecAccWoVetoFracNJets_);
  savePlot(ElecAccWoVetoFracBTags_);

  savePlot(ElecRecoWoVetoFracHT_);
  savePlot(ElecRecoWoVetoFracMHT_);
  savePlot(ElecRecoWoVetoFracNJets_);
  savePlot(ElecRecoWoVetoFracBTags_);

  savePlot(ElecIsoWoVetoFracHT_);
  savePlot(ElecIsoWoVetoFracMHT_);
  savePlot(ElecIsoWoVetoFracNJets_);
  savePlot(ElecIsoWoVetoFracBTags_);

  savePlot(MuAccFracHT_);
  savePlot(MuAccFracMHT_);
  savePlot(MuAccFracNJets_);
  savePlot(MuAccFracBTags_);

  savePlot(MuRecoFracHT_);
  savePlot(MuRecoFracMHT_);
  savePlot(MuRecoFracNJets_);
  savePlot(MuRecoFracBTags_);

  savePlot(MuIsoFracHT_);
  savePlot(MuIsoFracMHT_);
  savePlot(MuIsoFracNJets_);
  savePlot(MuIsoFracBTags_);

  savePlot(ElecAccFracHT_);
  savePlot(ElecAccFracMHT_);
  savePlot(ElecAccFracNJets_);
  savePlot(ElecAccFracBTags_);

  savePlot(ElecRecoFracHT_);
  savePlot(ElecRecoFracMHT_);
  savePlot(ElecRecoFracNJets_);
  savePlot(ElecRecoFracBTags_);

  savePlot(ElecIsoFracHT_);
  savePlot(ElecIsoFracMHT_);
  savePlot(ElecIsoFracNJets_);
  savePlot(ElecIsoFracBTags_);

  MuIsoTrackVetoPt_->Scale(1./MuIsoTrackVetoPt_->Integral());
  ElecIsoTrackVetoPt_->Scale(1./ElecIsoTrackVetoPt_->Integral());
  PionIsoTrackVetoPt_->Scale(1./PionIsoTrackVetoPt_->Integral());
  IsoTrackVetoPt_->Scale(1./IsoTrackVetoPt_->Integral());

  MuIsoTrackVetoPtAcc_->Scale(1./MuIsoTrackVetoPtAcc_->Integral());
  ElecIsoTrackVetoPtAcc_->Scale(1./ElecIsoTrackVetoPtAcc_->Integral());
  PionIsoTrackVetoPtAcc_->Scale(1./PionIsoTrackVetoPtAcc_->Integral());
  IsoTrackVetoPtAcc_->Scale(1./IsoTrackVetoPtAcc_->Integral());

  MuIsoTrackVetoPtIDIso_->Scale(1./MuIsoTrackVetoPtIDIso_->Integral());
  ElecIsoTrackVetoPtIDIso_->Scale(1./ElecIsoTrackVetoPtIDIso_->Integral());
  PionIsoTrackVetoPtIDIso_->Scale(1./PionIsoTrackVetoPtIDIso_->Integral());
  IsoTrackVetoPtIDIso_->Scale(1./IsoTrackVetoPtIDIso_->Integral());

  MuIsoTrackVetoPtID_->Scale(1./MuIsoTrackVetoPtID_->Integral());
  ElecIsoTrackVetoPtID_->Scale(1./ElecIsoTrackVetoPtID_->Integral());
  PionIsoTrackVetoPtID_->Scale(1./PionIsoTrackVetoPtID_->Integral());
  IsoTrackVetoPtID_->Scale(1./IsoTrackVetoPtID_->Integral());

  MuIsoTrackVetoPtIso_->Scale(1./MuIsoTrackVetoPtIso_->Integral());
  ElecIsoTrackVetoPtIso_->Scale(1./ElecIsoTrackVetoPtIso_->Integral());
  PionIsoTrackVetoPtIso_->Scale(1./PionIsoTrackVetoPtIso_->Integral());
  IsoTrackVetoPtIso_->Scale(1./IsoTrackVetoPtIso_->Integral());

  MuIsoTrackVetoPtMuAcc_->Scale(1./MuIsoTrackVetoPtMuAcc_->Integral());
  ElecIsoTrackVetoPtMuAcc_->Scale(1./ElecIsoTrackVetoPtMuAcc_->Integral());
  PionIsoTrackVetoPtMuAcc_->Scale(1./PionIsoTrackVetoPtMuAcc_->Integral());
  IsoTrackVetoPtMuAcc_->Scale(1./IsoTrackVetoPtMuAcc_->Integral());

  MuIsoTrackVetoPtMuIDIso_->Scale(1./MuIsoTrackVetoPtMuIDIso_->Integral());
  ElecIsoTrackVetoPtMuIDIso_->Scale(1./ElecIsoTrackVetoPtMuIDIso_->Integral());
  PionIsoTrackVetoPtMuIDIso_->Scale(1./PionIsoTrackVetoPtMuIDIso_->Integral());
  IsoTrackVetoPtMuIDIso_->Scale(1./IsoTrackVetoPtMuIDIso_->Integral());

  MuIsoTrackVetoPtMuID_->Scale(1./MuIsoTrackVetoPtMuID_->Integral());
  ElecIsoTrackVetoPtMuID_->Scale(1./ElecIsoTrackVetoPtMuID_->Integral());
  PionIsoTrackVetoPtMuID_->Scale(1./PionIsoTrackVetoPtMuID_->Integral());
  IsoTrackVetoPtMuID_->Scale(1./IsoTrackVetoPtMuID_->Integral());

  MuIsoTrackVetoPtMuIso_->Scale(1./MuIsoTrackVetoPtMuIso_->Integral());
  ElecIsoTrackVetoPtMuIso_->Scale(1./ElecIsoTrackVetoPtMuIso_->Integral());
  PionIsoTrackVetoPtMuIso_->Scale(1./PionIsoTrackVetoPtMuIso_->Integral());
  IsoTrackVetoPtMuIso_->Scale(1./IsoTrackVetoPtMuIso_->Integral());

  MuIsoTrackVetoPtElecAcc_->Scale(1./MuIsoTrackVetoPtElecAcc_->Integral());
  ElecIsoTrackVetoPtElecAcc_->Scale(1./ElecIsoTrackVetoPtElecAcc_->Integral());
  PionIsoTrackVetoPtElecAcc_->Scale(1./PionIsoTrackVetoPtElecAcc_->Integral());
  IsoTrackVetoPtElecAcc_->Scale(1./IsoTrackVetoPtElecAcc_->Integral());

  MuIsoTrackVetoPtElecIDIso_->Scale(1./MuIsoTrackVetoPtElecIDIso_->Integral());
  ElecIsoTrackVetoPtElecIDIso_->Scale(1./ElecIsoTrackVetoPtElecIDIso_->Integral());
  PionIsoTrackVetoPtElecIDIso_->Scale(1./PionIsoTrackVetoPtElecIDIso_->Integral());
  IsoTrackVetoPtElecIDIso_->Scale(1./IsoTrackVetoPtElecIDIso_->Integral());

  MuIsoTrackVetoPtElecID_->Scale(1./MuIsoTrackVetoPtElecID_->Integral());
  ElecIsoTrackVetoPtElecID_->Scale(1./ElecIsoTrackVetoPtElecID_->Integral());
  PionIsoTrackVetoPtElecID_->Scale(1./PionIsoTrackVetoPtElecID_->Integral());
  IsoTrackVetoPtElecID_->Scale(1./IsoTrackVetoPtElecID_->Integral());

  MuIsoTrackVetoPtElecIso_->Scale(1./MuIsoTrackVetoPtElecIso_->Integral());
  ElecIsoTrackVetoPtElecIso_->Scale(1./ElecIsoTrackVetoPtElecIso_->Integral());
  PionIsoTrackVetoPtElecIso_->Scale(1./PionIsoTrackVetoPtElecIso_->Integral());
  IsoTrackVetoPtElecIso_->Scale(1./IsoTrackVetoPtElecIso_->Integral());


  savePlot(MuIsoTrackVetoPt_);
  savePlot(ElecIsoTrackVetoPt_);
  savePlot(PionIsoTrackVetoPt_);
  savePlot(IsoTrackVetoPt_);

  savePlot(MuIsoTrackVetoPtAcc_);
  savePlot(ElecIsoTrackVetoPtAcc_);
  savePlot(PionIsoTrackVetoPtAcc_);
  savePlot(IsoTrackVetoPtAcc_);

  savePlot(MuIsoTrackVetoPtIDIso_);
  savePlot(ElecIsoTrackVetoPtIDIso_);
  savePlot(PionIsoTrackVetoPtIDIso_);
  savePlot(IsoTrackVetoPtIDIso_);

  savePlot(MuIsoTrackVetoPtID_);
  savePlot(ElecIsoTrackVetoPtID_);
  savePlot(PionIsoTrackVetoPtID_);
  savePlot(IsoTrackVetoPtID_);

  savePlot(MuIsoTrackVetoPtIso_);
  savePlot(ElecIsoTrackVetoPtIso_);
  savePlot(PionIsoTrackVetoPtIso_);
  savePlot(IsoTrackVetoPtIso_);

  savePlot(MuIsoTrackVetoPtMuAcc_);
  savePlot(ElecIsoTrackVetoPtMuAcc_);
  savePlot(PionIsoTrackVetoPtMuAcc_);
  savePlot(IsoTrackVetoPtMuAcc_);

  savePlot(MuIsoTrackVetoPtMuIDIso_);
  savePlot(ElecIsoTrackVetoPtMuIDIso_);
  savePlot(PionIsoTrackVetoPtMuIDIso_);
  savePlot(IsoTrackVetoPtMuIDIso_);

  savePlot(MuIsoTrackVetoPtMuID_);
  savePlot(ElecIsoTrackVetoPtMuID_);
  savePlot(PionIsoTrackVetoPtMuID_);
  savePlot(IsoTrackVetoPtMuID_);

  savePlot(MuIsoTrackVetoPtMuIso_);
  savePlot(ElecIsoTrackVetoPtMuIso_);
  savePlot(PionIsoTrackVetoPtMuIso_);
  savePlot(IsoTrackVetoPtMuIso_);

  savePlot(MuIsoTrackVetoPtElecAcc_);
  savePlot(ElecIsoTrackVetoPtElecAcc_);
  savePlot(PionIsoTrackVetoPtElecAcc_);
  savePlot(IsoTrackVetoPtElecAcc_);

  savePlot(MuIsoTrackVetoPtElecIDIso_);
  savePlot(ElecIsoTrackVetoPtElecIDIso_);
  savePlot(PionIsoTrackVetoPtElecIDIso_);
  savePlot(IsoTrackVetoPtElecIDIso_);

  savePlot(MuIsoTrackVetoPtElecID_);
  savePlot(ElecIsoTrackVetoPtElecID_);
  savePlot(PionIsoTrackVetoPtElecID_);
  savePlot(IsoTrackVetoPtElecID_);

  savePlot(MuIsoTrackVetoPtElecIso_);
  savePlot(ElecIsoTrackVetoPtElecIso_);
  savePlot(PionIsoTrackVetoPtElecIso_);
  savePlot(IsoTrackVetoPtElecIso_);
 }

  outPutFile->cd();
  outPutFile->mkdir("ExtrapPDFs");
  TDirectory *dExtrapPDFs = (TDirectory*)outPutFile->Get("ExtrapPDFs");
  dExtrapPDFs->cd();
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<3; inb++) {
      // fix overflow bins
      // lump remiaining tail into 1.2 < MHT/PTW < 1.3 -- does this make sense?
      Double_t erro(0.);
      LostMuRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostMuRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostMuRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostMuRATIO_HT12[inj*3+inb]->Integral()>0) LostMuRATIO_HT12[inj*3+inb]->Scale(1/LostMuRATIO_HT12[inj*3+inb]->Integral());
      if (LostMuRATIO_HT3[inj*3+inb]->Integral()>0) LostMuRATIO_HT3[inj*3+inb]->Scale(1/LostMuRATIO_HT3[inj*3+inb]->Integral());
      if (LostMuRATIO_HT23[inj*3+inb]->Integral()>0) LostMuRATIO_HT23[inj*3+inb]->Scale(1/LostMuRATIO_HT23[inj*3+inb]->Integral());
      LostMuRATIO_HT12[inj*3+inb]->Write();
      LostMuRATIO_HT3[inj*3+inb]->Write();
      LostMuRATIO_HT23[inj*3+inb]->Write();
      LostElecRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostElecRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostElecRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostElecRATIO_HT12[inj*3+inb]->Integral()>0) LostElecRATIO_HT12[inj*3+inb]->Scale(1/LostElecRATIO_HT12[inj*3+inb]->Integral());
      if (LostElecRATIO_HT3[inj*3+inb]->Integral()>0) LostElecRATIO_HT3[inj*3+inb]->Scale(1/LostElecRATIO_HT3[inj*3+inb]->Integral());
      if (LostElecRATIO_HT23[inj*3+inb]->Integral()>0) LostElecRATIO_HT23[inj*3+inb]->Scale(1/LostElecRATIO_HT23[inj*3+inb]->Integral());
      LostElecRATIO_HT12[inj*3+inb]->Write();
      LostElecRATIO_HT3[inj*3+inb]->Write();
      LostElecRATIO_HT23[inj*3+inb]->Write();
      LostLepRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostLepRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostLepRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostLepRATIO_HT12[inj*3+inb]->Integral()>0) LostLepRATIO_HT12[inj*3+inb]->Scale(1/LostLepRATIO_HT12[inj*3+inb]->Integral());
      if (LostLepRATIO_HT3[inj*3+inb]->Integral()>0) LostLepRATIO_HT3[inj*3+inb]->Scale(1/LostLepRATIO_HT3[inj*3+inb]->Integral());
      if (LostLepRATIO_HT23[inj*3+inb]->Integral()>0) LostLepRATIO_HT23[inj*3+inb]->Scale(1/LostLepRATIO_HT23[inj*3+inb]->Integral());
      LostLepRATIO_HT12[inj*3+inb]->Write();
      LostLepRATIO_HT3[inj*3+inb]->Write();
      LostLepRATIO_HT23[inj*3+inb]->Write();   
    }
  }
  outPutFile->cd();
  outPutFile->Close();
  
  TFile *outPutFileSam = new TFile("Efficiencies_reco_LepTrack.root","RECREATE"); 
  outPutFileSam->cd();

  recoLepOverAccMu->SaveEff("recoLepOverAccMu; p_{T}(mu) [GeV]; #eta(mu)", outPutFileSam, true);
  recoTrackOverAccMu->SaveEff("recoTrackOverAccMu; p_{T}(mu) [GeV]; #eta(mu)", outPutFileSam, true);
  recoOverAccMu->SaveEff("recoOverAccMu; p_{T}(mu) [GeV]; #eta(mu)", outPutFileSam, true);
  recoLepOverAccEl->SaveEff("recoLepOverAccEl; p_{T}(e) [GeV]; #eta(e)", outPutFileSam, true);
  recoTrackOverAccEl->SaveEff("recoTrackOverAccEl; p_{T}(e) [GeV]; #eta(e)", outPutFileSam, true);
  recoOverAccEl->SaveEff("recoOverAccEl; p_{T}(e) [GeV]; #eta(e)", outPutFileSam, true);

  outPutFileSam->cd();
  outPutFileSam->Close();
}
