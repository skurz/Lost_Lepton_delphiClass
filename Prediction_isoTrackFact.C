#define Prediction_isoTrackFact_cxx

#include "Prediction_isoTrackFact.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>


void Prediction_isoTrackFact::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

}

void Prediction_isoTrackFact::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TFile *effInput = new TFile("Efficiencies.root","READ");
  TDirectory *EffInputFolder =   (TDirectory*)effInput->Get("Efficiencies");

  MuDiLepCRNJets_ = new TH1Eff("MuDiLepCRNJets1D", EffInputFolder);
  MuDiLepCRMHTNJets_ = new TH2Eff("MuDiLepCRMHTNJets", EffInputFolder);
  MuDiLepCRNJetsBTags_ = new TH2Eff("MuDiLepCRNJetsBTags", EffInputFolder);

  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT", EffInputFolder);
  MuRecoActivityPT_= new TH2Eff("MuRecoActivityPT", EffInputFolder);
  MuRecoPTEta_= new TH2Eff("MuRecoPTEta", EffInputFolder);
  MuPurityMHTNJets_ = new TH2Eff("MuonPurityMHTNJet", EffInputFolder); 
  MuPurityHTMHT_ = new TH2Eff("MuonPurityHTMHT", EffInputFolder); 

  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT", EffInputFolder);
  ElecRecoActivityPT_= new TH2Eff("ElecRecoActivityPT", EffInputFolder);
  ElecRecoPTEta_= new TH2Eff("ElecRecoPTEta", EffInputFolder);
  
  ElecPurityMHTNJets_ = new TH2Eff("ElecPurityMHTNJet", EffInputFolder);
  ElecPurityHTMHT_ = new TH2Eff("MuonPurityHTMHT", EffInputFolder); 

  ElecDiLepCRNJets_ = new TH1Eff("ElecDiLepCRNJets1D", EffInputFolder);
  ElecDiLepCRMHTNJets_ = new TH2Eff("ElecDiLepCRMHTNJets", EffInputFolder);
  ElecDiLepCRNJetsBTags_ = new TH2Eff("ElecDiLepCRNJetsBTags", EffInputFolder);

/*
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D", EffInputFolder);
  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets", EffInputFolder);
  MuMTWMHTNJets_ = new TH2Eff("MuMTWMHTNJets", EffInputFolder);
  MuMTWHTMHT_ = new TH2Eff("MuMTWHTMHT", EffInputFolder);
  MuMTWHTMHT_NJets24_ = new TH2Eff("MuMTWHTMHT_NJets24", EffInputFolder);
  MuMTWHTMHT_NJets56_ = new TH2Eff("MuMTWHTMHT_NJets56", EffInputFolder);
  MuMTWHTMHT_NJets7Inf_ = new TH2Eff("MuMTWHTMHT_NJets7Inf", EffInputFolder);
  MuMTWHTMHT_NJets2_ = new TH2Eff("MuMTWHTMHT_NJets2", EffInputFolder);
  MuMTWHTMHT_NJets3_ = new TH2Eff("MuMTWHTMHT_NJets3", EffInputFolder);
  MuMTWHTMHT_NJets4_ = new TH2Eff("MuMTWHTMHT_NJets4", EffInputFolder);
  MuMTWHTMHT_NJets5_ = new TH2Eff("MuMTWHTMHT_NJets5", EffInputFolder);
  MuMTWHTMHT_NJets6_ = new TH2Eff("MuMTWHTMHT_NJets6", EffInputFolder);
  MuMTWHTMHT_NJets78_ = new TH2Eff("MuMTWHTMHT_NJets78", EffInputFolder);
  MuMTWHTMHT_NJets9Inf_ = new TH2Eff("MuMTWHTMHT_NJets9Inf", EffInputFolder);

  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D", EffInputFolder);
  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets", EffInputFolder);
  ElecMTWMHTNJets_ = new TH2Eff("ElecMTWMHTNJets", EffInputFolder);
  ElecMTWHTMHT_ = new TH2Eff("ElecMTWHTMHT", EffInputFolder);
  ElecMTWHTMHT_NJets24_ = new TH2Eff("ElecMTWHTMHT_NJets24", EffInputFolder);
  ElecMTWHTMHT_NJets56_ = new TH2Eff("ElecMTWHTMHT_NJets56", EffInputFolder);
  ElecMTWHTMHT_NJets7Inf_ = new TH2Eff("ElecMTWHTMHT_NJets7Inf", EffInputFolder);
  ElecMTWHTMHT_NJets2_ = new TH2Eff("ElecMTWHTMHT_NJets2", EffInputFolder);
  ElecMTWHTMHT_NJets3_ = new TH2Eff("ElecMTWHTMHT_NJets3", EffInputFolder);
  ElecMTWHTMHT_NJets4_ = new TH2Eff("ElecMTWHTMHT_NJets4", EffInputFolder);
  ElecMTWHTMHT_NJets5_ = new TH2Eff("ElecMTWHTMHT_NJets5", EffInputFolder);
  ElecMTWHTMHT_NJets6_ = new TH2Eff("ElecMTWHTMHT_NJets6", EffInputFolder);
  ElecMTWHTMHT_NJets78_ = new TH2Eff("ElecMTWHTMHT_NJets78", EffInputFolder);
  ElecMTWHTMHT_NJets9Inf_ = new TH2Eff("ElecMTWHTMHT_NJets9Inf", EffInputFolder);
*/
  //NEW
  MuAccSearchBins_ = new TH1Eff("MuAccSearchBins", EffInputFolder);
  ElecAccSearchBins_ = new TH1Eff("ElecAccSearchBins", EffInputFolder);
  MuMTWSearchBins_ = new TH1Eff("MuMTWSearchBins", EffInputFolder);
  ElecMTWSearchBins_ = new TH1Eff("ElecMTWSearchBins", EffInputFolder);
  IsoTrackVetoSearchBins_ = new TH1Eff("IsoTrackVetoSearchBins", EffInputFolder);
  MuIsoTrackVetoSearchBins_ = new TH1Eff("MuIsoTrackVetoSearchBins", EffInputFolder);
  ElecIsoTrackVetoSearchBins_ = new TH1Eff("ElecIsoTrackVetoSearchBins", EffInputFolder);
  PionIsoTrackVetoSearchBins_ = new TH1Eff("PionIsoTrackVetoSearchBins", EffInputFolder);
  MuDiLepCRSearchBins_ = new TH1Eff("MuDiLepCRSearchBins", EffInputFolder);
  ElecDiLepCRSearchBins_ = new TH1Eff("ElecDiLepCRSearchBins", EffInputFolder);

  MuDiLepSRNJets_ = new TH1Eff("MuDiLepSRNJets1D", EffInputFolder);
  MuDiLepSRNJetsBTags_ = new TH2Eff("MuDiLepSRNJetsBTags", EffInputFolder);  
  ElecDiLepSRNJets_ = new TH1Eff("ElecDiLepSRNJets1D", EffInputFolder);
  ElecDiLepSRNJetsBTags_ = new TH2Eff("ElecDiLepSRNJetsBTags", EffInputFolder);

  MuDiLepSRwoVetoNJets_ = new TH1Eff("MuDiLepSRwoVetoNJets1D", EffInputFolder);
  MuDiLepSRwoVetoNJetsBTags_ = new TH2Eff("MuDiLepSRwoVetoNJetsBTags", EffInputFolder);  
  ElecDiLepSRwoVetoNJets_ = new TH1Eff("ElecDiLepSRwoVetoNJets1D", EffInputFolder);
  ElecDiLepSRwoVetoNJetsBTags_ = new TH2Eff("ElecDiLepSRwoVetoNJetsBTags", EffInputFolder);

  MuIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuAcc", EffInputFolder);
  ElecIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuAcc", EffInputFolder);
  PionIsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuAcc", EffInputFolder);
  IsoTrackVetoSearchBinsMuAcc_ = new TH1Eff("IsoTrackVetoSearchBinsMuAcc", EffInputFolder);

  MuIsoTrackVetoSearchBinsMuID_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuID", EffInputFolder);
  ElecIsoTrackVetoSearchBinsMuID_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuID", EffInputFolder);
  PionIsoTrackVetoSearchBinsMuID_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuID", EffInputFolder);
  IsoTrackVetoSearchBinsMuID_ = new TH1Eff("IsoTrackVetoSearchBinsMuID", EffInputFolder);

  MuIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsMuIso", EffInputFolder);
  ElecIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsMuIso", EffInputFolder);
  PionIsoTrackVetoSearchBinsMuIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsMuIso", EffInputFolder);
  IsoTrackVetoSearchBinsMuIso_ = new TH1Eff("IsoTrackVetoSearchBinsMuIso", EffInputFolder);

  MuIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecAcc", EffInputFolder);
  ElecIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecAcc", EffInputFolder);
  PionIsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecAcc", EffInputFolder);
  IsoTrackVetoSearchBinsElecAcc_ = new TH1Eff("IsoTrackVetoSearchBinsElecAcc", EffInputFolder);

  MuIsoTrackVetoSearchBinsElecID_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecID", EffInputFolder);
  ElecIsoTrackVetoSearchBinsElecID_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecID", EffInputFolder);
  PionIsoTrackVetoSearchBinsElecID_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecID", EffInputFolder);
  IsoTrackVetoSearchBinsElecID_ = new TH1Eff("IsoTrackVetoSearchBinsElecID", EffInputFolder);

  MuIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("MuIsoTrackVetoSearchBinsElecIso", EffInputFolder);
  ElecIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("ElecIsoTrackVetoSearchBinsElecIso", EffInputFolder);
  PionIsoTrackVetoSearchBinsElecIso_ = new TH1Eff("PionIsoTrackVetoSearchBinsElecIso", EffInputFolder);
  IsoTrackVetoSearchBinsElecIso_ = new TH1Eff("IsoTrackVetoSearchBinsElecIso", EffInputFolder);

/*
  MuIsoTrackVetoActivityPtMuID_ = new TH2Eff("MuIsoTrackVetoPtEtaMuID", EffInputFolder);
  ElecIsoTrackVetoActivityPtMuID_ = new TH2Eff("ElecIsoTrackVetoPtEtaMuID", EffInputFolder);
  PionIsoTrackVetoActivityPtMuID_ = new TH2Eff("PionIsoTrackVetoPtEtaMuID", EffInputFolder);
  IsoTrackVetoActivityPtMuID_ = new TH2Eff("IsoTrackVetoPtEtaMuID", EffInputFolder);

  MuIsoTrackVetoActivityPtMuIso_ = new TH2Eff("MuIsoTrackVetoActivityPtMuIso", EffInputFolder);
  ElecIsoTrackVetoActivityPtMuIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtMuIso", EffInputFolder);
  PionIsoTrackVetoActivityPtMuIso_ = new TH2Eff("PionIsoTrackVetoActivityPtMuIso", EffInputFolder);
  IsoTrackVetoActivityPtMuIso_ = new TH2Eff("IsoTrackVetoActivityPtMuIso", EffInputFolder);

  MuIsoTrackVetoActivityPtElecID_ = new TH2Eff("MuIsoTrackVetoPtEtaElecID", EffInputFolder);
  ElecIsoTrackVetoActivityPtElecID_ = new TH2Eff("ElecIsoTrackVetoPtEtaElecID", EffInputFolder);
  PionIsoTrackVetoActivityPtElecID_ = new TH2Eff("PionIsoTrackVetoPtEtaElecID", EffInputFolder);
  IsoTrackVetoActivityPtElecID_ = new TH2Eff("IsoTrackVetoPtEtaElecID", EffInputFolder);

  MuIsoTrackVetoActivityPtElecIso_ = new TH2Eff("MuIsoTrackVetoActivityPtElecIso", EffInputFolder);
  ElecIsoTrackVetoActivityPtElecIso_ = new TH2Eff("ElecIsoTrackVetoActivityPtElecIso", EffInputFolder);
  PionIsoTrackVetoActivityPtElecIso_ = new TH2Eff("PionIsoTrackVetoActivityPtElecIso", EffInputFolder);
  IsoTrackVetoActivityPtElecIso_ = new TH2Eff("IsoTrackVetoActivityPtElecIso", EffInputFolder);
*/
 
  tPrediction_ = new TTree("LostLeptonPrediction","a simple Tree with simple variables");
  tPrediction_->Branch("HT",&HT);
  tPrediction_->Branch("MHT",&MHT);
  tPrediction_->Branch("NJets",&NJets);
  tPrediction_->Branch("BTags",&BTags);
  tPrediction_->Branch("NVtx",&NVtx);
  tPrediction_->Branch("Bin",&Bin_);
  tPrediction_->Branch("BinQCD",&BinQCD_);
  //tPrediction_->Branch("PTWBins", &ptw_bins);
  tPrediction_->Branch("isoTracksNum",&isoTracksNum);
  tPrediction_->Branch("DeltaPhi1",&DeltaPhi1);
  tPrediction_->Branch("DeltaPhi2",&DeltaPhi2);
  tPrediction_->Branch("DeltaPhi3",&DeltaPhi3);
  tPrediction_->Branch("DeltaPhi4",&DeltaPhi4);
  tPrediction_->Branch("Weight", &Weight);
  tPrediction_->Branch("MET",&MET);
  tPrediction_->Branch("METPhi",&METPhi);
  tPrediction_->Branch("MuonsNum",&MuonsNum_);
  tPrediction_->Branch("MuonsPt",&MuonsPt_);
  tPrediction_->Branch("MuonsEta",&MuonsEta_);
  tPrediction_->Branch("Muons", "std::vector<TLorentzVector>", &Muons, 32000, 0);
  tPrediction_->Branch("Muons_MT2Activity", &Muons_MT2Activity);
  //tPrediction_->Branch("MuonsPTW", &MuonsPTW);
  //  tPrediction_->Branch("MuonsCDTT", &MuonsCDTT);
  tPrediction_->Branch("ElectronsNum",&ElectronsNum_);
  tPrediction_->Branch("Electrons", "std::vector<TLorentzVector>", &Electrons, 32000, 0);
  tPrediction_->Branch("Electrons_MT2Activity", &Electrons_MT2Activity);
  //tPrediction_->Branch("ElectronsPTW", &ElectronsPTW);
  tPrediction_->Branch("ElectronsPt",&ElectronsPt_);
  tPrediction_->Branch("ElectronsEta",&ElectronsEta_);
  tPrediction_->Branch("Muons_tightID", &Muons_tightID);
  tPrediction_->Branch("Electrons_mediumID", &Electrons_mediumID);
  tPrediction_->Branch("Electrons_tightID", &Electrons_tightID);
  //  tPrediction_->Branch("ElectronsCDTT", &ElectronsCDTT);
  tPrediction_->Branch("MTW",&mtw);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined_);
  tPrediction_->Branch("totalWeight_BTags",&totalWeight_BTags_);
  tPrediction_->Branch("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack_);
  tPrediction_->Branch("muIsoWeight",&muIsoWeight_);
  tPrediction_->Branch("muRecoWeight",&muRecoWeight_);
  tPrediction_->Branch("muAccWeight",&muAccWeight_);
  tPrediction_->Branch("muTotalWeight",&muTotalWeight_);
  tPrediction_->Branch("totalMuons",&totalMuons_);
  tPrediction_->Branch("elecAccWeight",&elecAccWeight_);
  tPrediction_->Branch("elecRecoWeight",&elecRecoWeight_);
  tPrediction_->Branch("elecIsoWeight",&elecIsoWeight_);
  tPrediction_->Branch("elecTotalWeight",&elecTotalWeight_);
  tPrediction_->Branch("totalElectrons",&totalElectrons_);
  tPrediction_->Branch("diLepLostWeight", &diLepLostWeight_);
  tPrediction_->Branch("totalWeight",&totalWeight_);
  tPrediction_->Branch("totalWeightDiLep",&totalWeightDiLep_);
  //tPrediction_->Branch("Jets_HTMask", &Jets_HTMask);
  if(!runOnData){
    //tPrediction_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
    tPrediction_->Branch("bTagProb", &bTagProb);
    tPrediction_->Branch("madHT", &madHT);
    tPrediction_->Branch("w_pu", &w_pu);
    //tPrediction_->Branch("Weight_bTagCorr", &Weight_bTagCorr);
    tPrediction_->Branch("recoSF", &recoSF);
    tPrediction_->Branch("isoSF", &isoSF);
    tPrediction_->Branch("trackingSF", &trackingSF);
    tPrediction_->Branch("WeightCorr", &WeightCorr);
    tPrediction_->Branch("WeightTrackingCorr", &WeightTrackingCorr);
    if(topPTreweight){
      tPrediction_->Branch("GenMuons", "std::vector<TLorentzVector>", &GenMuons, 32000, 0);
      tPrediction_->Branch("GenElectrons", "std::vector<TLorentzVector>", &GenElectrons, 32000, 0);
      tPrediction_->Branch("topPtSF", &topPtSF);
      tPrediction_->Branch("topPt", &topPt);
    }
  }
  if(runOnSignalMC){
    tPrediction_->Branch("SusyLSPMass", &SusyLSPMass);
    tPrediction_->Branch("SusyMotherMass", &SusyMotherMass);
    tPrediction_->Branch("w_isr", &w_isr);
    tPrediction_->Branch("w_pu", &w_pu);
    tPrediction_->Branch("xsec", &xsec);
    tPrediction_->Branch("nEvtsTotal", &nEvtsTotal);
  }

  if(!fillEventSeperateBTags){
    tPrediction_->Branch("isoTrackMuAccStatUp", & isoTrackMuAccStatUp);
    tPrediction_->Branch("isoTrackMuAccStatDown", & isoTrackMuAccStatDown);
    tPrediction_->Branch("isoTrackMuIDStatUp", &isoTrackMuIDStatUp);
    tPrediction_->Branch("isoTrackMuIDStatDown", &isoTrackMuIDStatDown);
    tPrediction_->Branch("isoTrackMuIsoStatUp", &isoTrackMuIsoStatUp);
    tPrediction_->Branch("isoTrackMuIsoStatDown", &isoTrackMuIsoStatDown);
    tPrediction_->Branch("isoTrackElecAccStatUp", & isoTrackElecAccStatUp);
    tPrediction_->Branch("isoTrackElecAccStatDown", & isoTrackElecAccStatDown);
    tPrediction_->Branch("isoTrackElecIDStatUp", &isoTrackElecIDStatUp);
    tPrediction_->Branch("isoTrackElecIDStatDown", &isoTrackElecIDStatDown);
    tPrediction_->Branch("isoTrackElecIsoStatUp", &isoTrackElecIsoStatUp);
    tPrediction_->Branch("isoTrackElecIsoStatDown", &isoTrackElecIsoStatDown);
    tPrediction_->Branch("MTWStatUp", &MTWStatUp);
    tPrediction_->Branch("MTWStatDown", &MTWStatDown);
    tPrediction_->Branch("purityStatUp", &purityStatUp);
    tPrediction_->Branch("purityStatDown", &purityStatDown);
    tPrediction_->Branch("singleLepPurityStatUp", &singleLepPurityStatUp);
    tPrediction_->Branch("singleLepPurityStatDown", &singleLepPurityStatDown);
    tPrediction_->Branch("diLepSRStatUp", &diLepSRStatUp);
    tPrediction_->Branch("diLepSRStatDown", &diLepSRStatDown);
    tPrediction_->Branch("muIsoStatUp", &muIsoStatUp);
    tPrediction_->Branch("muIsoStatDown", &muIsoStatDown);
    tPrediction_->Branch("muRecoStatUp", &muRecoStatUp);
    tPrediction_->Branch("muRecoStatDown", &muRecoStatDown);
    tPrediction_->Branch("muAccStatUp", &muAccStatUp);
    tPrediction_->Branch("muAccStatDown", &muAccStatDown);
    tPrediction_->Branch("elecIsoStatUp", &elecIsoStatUp);
    tPrediction_->Branch("elecIsoStatDown", &elecIsoStatDown);
    tPrediction_->Branch("elecRecoStatUp", &elecRecoStatUp);
    tPrediction_->Branch("elecRecoStatDown", &elecRecoStatDown);
    tPrediction_->Branch("elecAccStatUp", &elecAccStatUp);
    tPrediction_->Branch("elecAccStatDown", &elecAccStatDown);
    
    tPrediction_->Branch("isoTrackMuAccSysUp", & isoTrackMuAccSysUp);
    tPrediction_->Branch("isoTrackMuAccSysDown", & isoTrackMuAccSysDown);
    tPrediction_->Branch("isoTrackMuIDSysUp", &isoTrackMuIDSysUp);
    tPrediction_->Branch("isoTrackMuIDSysDown", &isoTrackMuIDSysDown);
    tPrediction_->Branch("isoTrackMuIsoSysUp", &isoTrackMuIsoSysUp);
    tPrediction_->Branch("isoTrackMuIsoSysDown", &isoTrackMuIsoSysDown);
    tPrediction_->Branch("isoTrackElecAccSysUp", & isoTrackElecAccSysUp);
    tPrediction_->Branch("isoTrackElecAccSysDown", & isoTrackElecAccSysDown);
    tPrediction_->Branch("isoTrackElecIDSysUp", &isoTrackElecIDSysUp);
    tPrediction_->Branch("isoTrackElecIDSysDown", &isoTrackElecIDSysDown);
    tPrediction_->Branch("isoTrackElecIsoSysUp", &isoTrackElecIsoSysUp);
    tPrediction_->Branch("isoTrackElecIsoSysDown", &isoTrackElecIsoSysDown);
    tPrediction_->Branch("MTWSysUp", &MTWSysUp);
    tPrediction_->Branch("MTWSysDown", &MTWSysDown);
    tPrediction_->Branch("puritySysUp", &puritySysUp);
    tPrediction_->Branch("puritySysDown", &puritySysDown);
    tPrediction_->Branch("singleLepPuritySysUp", &singleLepPuritySysUp);
    tPrediction_->Branch("singleLepPuritySysDown", &singleLepPuritySysDown);
    tPrediction_->Branch("diLepSRSysUp", &diLepSRSysUp);
    tPrediction_->Branch("diLepSRSysDown", &diLepSRSysDown);
    tPrediction_->Branch("muIsoSysUp", &muIsoSysUp);
    tPrediction_->Branch("muIsoSysDown", &muIsoSysDown);
    tPrediction_->Branch("muRecoSysUp", &muRecoSysUp);
    tPrediction_->Branch("muRecoSysDown", &muRecoSysDown);
    tPrediction_->Branch("muAccSysUp", &muAccSysUp);
    tPrediction_->Branch("muAccSysDown", &muAccSysDown);
    tPrediction_->Branch("muAccQsquareSysUp", &muAccQsquareSysUp);
    tPrediction_->Branch("muAccQsquareSysDown", &muAccQsquareSysDown);
    tPrediction_->Branch("elecIsoSysUp", &elecIsoSysUp);
    tPrediction_->Branch("elecIsoSysDown", &elecIsoSysDown);
    tPrediction_->Branch("elecRecoSysUp", &elecRecoSysUp);
    tPrediction_->Branch("elecRecoSysDown", &elecRecoSysDown);
    tPrediction_->Branch("elecAccSysUp", &elecAccSysUp);
    tPrediction_->Branch("elecAccSysDown", &elecAccSysDown);
    tPrediction_->Branch("elecAccQsquareSysUp", &elecAccQsquareSysUp);
    tPrediction_->Branch("elecAccQsquareSysDown", &elecAccQsquareSysDown);
  }

  GetOutputList()->Add(tPrediction_);
  SearchBins_ = new SearchBins(false); // 72 searchbins
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  SearchBinsEff_ = new SearchBins(true); // 220 QCD binning

  std::cout<<"Run on Data: "<<runOnData<<std::endl;
  std::cout<<"Run on SM MC: "<<runOnStandardModelMC<<std::endl;
  std::cout<<"Run on Signal MC: "<<runOnSignalMC<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
}

Bool_t Prediction_isoTrackFact::Process(Long64_t entry)
{
  resetValues();
  fChain->GetTree()->GetEntry(entry);

//  if(entry % 3 != 0) return kTRUE;

  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;

// Not needed anymore. Special Skims used.
//  if(useGenHTMHT){
//    HT = GenHT;
//    MHT = GenMHT;
//  }
  
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  isoTracksNum= isoElectronTracksNum + isoMuonTracksNum + isoPionTracksNum;

  //MuonsNoIsoNum_ = MuonsNoIso->size();
  MuonsNum_ = Muons->size();
  //ElectronsNoIsoNum_ = ElectronsNoIso->size();
  ElectronsNum_ = Electrons->size();

  if((MuonsNum_+ElectronsNum_) !=1) return kTRUE;

  // Signal triggers
  if(useTrigger) if(!TriggerPass->at(42) && !TriggerPass->at(43) &&!TriggerPass->at(44) && !TriggerPass->at(46) && !TriggerPass->at(47) && !TriggerPass->at(48)) return kTRUE;

  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);


  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;

  if(topPTreweight){
    if(GenParticles->size() != GenParticles_PdgId->size()){
      std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
    }else{
      for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
        if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
          topPt.push_back(GenParticles->at(iGen).Pt());
        }
      }
      
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#Example
      if(topPt.size() == 2){
        // dilept
        if(GenElectrons->size() + GenMuons->size() == 2){
          topPtSF = std::sqrt(std::exp(0.148-0.00129*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.148-0.00129*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
        // singlelept
        }else if(GenElectrons->size() + GenMuons->size() == 1){
          topPtSF = std::sqrt(std::exp(0.159-0.00141*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.159-0.00141*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
        //had
        }else{
          // Usually non-promt (in hadTau evts): use average SF
          topPtSF = std::sqrt(std::exp(0.156-0.00137*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.156-0.00137*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
          //std::cout << "Cannot do top-pT reweighting! No leptonic top found."<< std::endl; 
        }
      }else{
        topPtSF = -1;
        std::cout << "Cannot do top-pT reweighting! More/Less than 2 tops found."<< std::endl; 
      }

    }

    // Normalization tested on SingleLept and DiLept samples (varies from ~98.9x-99.0x)
        topPtSF /= 0.99;
  }

  if(!runOnData){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());

    if(currentTree != treeName){
      treeName = currentTree;

      if(doISRcorr){
        h_njetsisr = (TH1*) fChain->GetCurrentFile()->Get("NJetsISR");
        if(isrcorr!=0){
          delete isrcorr;
          isrcorr = 0;
        }
        isrcorr = new ISRCorrector();
        isrcorr->SetWeights(h_isr,h_njetsisr);
      }

      if(doBTagCorr){
        if(btagcorr!=0){
          delete btagcorr;
          btagcorr = 0;
        }
        btagcorr = new BTagCorrector();

        if(!runOnNtuples) btagcorr->SetEffs(fChain->GetCurrentFile());
        else{
          TObjArray *optionArray = currentTree.Tokenize("/");
          TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
          TFile *skimFile = TFile::Open(path_toSkims+currFileName, "READ");
          btagcorr->SetEffs(skimFile);
        }

        btagcorr->SetCalib(path_bTagCalib);        
        if(runOnSignalMC){
          btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
          btagcorr->SetFastSim(true);
        }
        else btagcorr->SetFastSim(false);
      }

      if(runOnSignalMC){
        if((std::string(currentTree.Data()).find(std::string("T1"))) != std::string::npos || (std::string(currentTree.Data()).find(std::string("T5"))) != std::string::npos){
          xsecs = &xsecsT1T5;
          //std::cout<<"Using xsecs for gluino pair production!"<<std::endl;
        }else if((std::string(currentTree.Data()).find(std::string("T2"))) != std::string::npos){
          xsecs = &xsecsT2;
          //std::cout<<"Using xsecs for stop pair production!"<<std::endl;
        }else{
          std::cout<<"No valid dictionary with xsecs found!"<<std::endl;
          return kTRUE;
        }
      }
    }

    if(runOnSignalMC){
      TH1F *nEventProc = (TH1F*)fChain->GetCurrentFile()->Get("nEventProc");
      TH1F *nEventNeg = (TH1F*)fChain->GetCurrentFile()->Get("nEventNeg");
      nEvtsTotal = nEventProc->GetBinContent(1) - 2*nEventNeg->GetBinContent(1);

      xsec = 0;
      for (std::vector<std::pair<double, double>>::iterator it = xsecs->begin() ; it != xsecs->end(); ++it){
        if(std::abs(SusyMotherMass - it->first) < 0.1){
          xsec = it->second;
          break;
        }
      }
      if(xsec < 1e-10){
        std::cout<<"No valid xsec found!"<<std::endl;
        return kTRUE;
      }

      Weight = xsec / nEvtsTotal;
      if(Weight < 0) Weight *= -1;
    }   

    if(doISRcorr){
      w_isr = isrcorr->GetCorrection(NJetsISR);
      Weight *= w_isr;
    }

    if(doBTagCorr) bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
    else bTagProb = {0, 0, 0, 0};
    // Simple bTag corrections don't work that way
    //if(!runOnData) bTagCorr_cut = btagcorr->GetSimpleCorrection(Jets,Jets_hadronFlavor,Jets_HTMask,Jets_bDiscriminatorCSV);
  }

  if(runOnData) Weight = 1.;

  if(runOnSignalMC){
    //Account for efficiency of JetID since we cannot apply it on fastSim
    Weight *= 0.99;
  }

  if(useTriggerEffWeight){
    if(runOnSignalMC){
      Weight *= GetSignalTriggerEffWeight(MHT);
    }else{
      Weight *= GetTriggerEffWeight(MHT);
    }
  }

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

/*
  //if(!runOnData){
  //  if(bTagCorr_cut < 0 || bTagCorr_cut > 10 || std::isnan(bTagCorr_cut)) Weight_bTagCorr = 1.; 
  //  else Weight_bTagCorr = Weight * bTagCorr_cut;
  //}
    // fill PTW values for extrapolation
  for (UShort_t ii=0; ii < MuonsNum_; ii++){
    MuonsPTW.push_back(PTWCalculator(MHT,MHTPhi, Muons->at(ii).Pt(), Muons->at(ii).Phi()));
    //    MuonsCDTT.push_back(GetCosDTT(MHT,MHTPhi, Muons->at(ii).Pt(), Muons->at(ii).Phi()));
  }
  for (UShort_t ii=0; ii < ElectronsNum_; ii++){
    ElectronsPTW.push_back(PTWCalculator(MHT,MHTPhi, Electrons->at(ii).Pt(), Electrons->at(ii).Phi()));
    //    ElectronsCDTT.push_back(GetCosDTT(MHT,MHTPhi, Electrons->at(ii).Pt(), Electrons->at(ii).Phi()));
  }


  double PTW(0.);
  if (MuonsNum_==1) PTW=MuonsPTW[0];
  else if (ElectronsNum_==1) PTW=ElectronsPTW[0];
  ptw_bins = GetPTWBin(Bin_, PTW, HT);

*/

  // get IsoTrack Effs
/*  expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);

  //for compatibility
  expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
  expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
  expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
  expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;
*/
   muIsotrkMuAccEffVec_= MuIsoTrackVetoSearchBinsMuAcc_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkMuAccEffVec_= ElecIsoTrackVetoSearchBinsMuAcc_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkMuAccEffVec_= PionIsoTrackVetoSearchBinsMuAcc_->GetEff(BinQCD_, useAsymmErrors);
   isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(BinQCD_, useAsymmErrors);

   muIsotrkMuIDEffVec_= MuIsoTrackVetoSearchBinsMuID_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkMuIDEffVec_= ElecIsoTrackVetoSearchBinsMuID_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkMuIDEffVec_= PionIsoTrackVetoSearchBinsMuID_->GetEff(BinQCD_, useAsymmErrors);
   isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(BinQCD_, useAsymmErrors);

   muIsotrkMuIsoEffVec_= MuIsoTrackVetoSearchBinsMuIso_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkMuIsoEffVec_= ElecIsoTrackVetoSearchBinsMuIso_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkMuIsoEffVec_= PionIsoTrackVetoSearchBinsMuIso_->GetEff(BinQCD_, useAsymmErrors);
   isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(BinQCD_, useAsymmErrors);

   muIsotrkElecAccEffVec_= MuIsoTrackVetoSearchBinsElecAcc_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkElecAccEffVec_= ElecIsoTrackVetoSearchBinsElecAcc_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkElecAccEffVec_= PionIsoTrackVetoSearchBinsElecAcc_->GetEff(BinQCD_, useAsymmErrors);
   isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(BinQCD_, useAsymmErrors);

   muIsotrkElecIDEffVec_= MuIsoTrackVetoSearchBinsElecID_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkElecIDEffVec_= ElecIsoTrackVetoSearchBinsElecID_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkElecIDEffVec_= PionIsoTrackVetoSearchBinsElecID_->GetEff(BinQCD_, useAsymmErrors);
   isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(BinQCD_, useAsymmErrors);

   muIsotrkElecIsoEffVec_= MuIsoTrackVetoSearchBinsElecIso_->GetEff(BinQCD_, useAsymmErrors);
   elecIsotrkElecIsoEffVec_= ElecIsoTrackVetoSearchBinsElecIso_->GetEff(BinQCD_, useAsymmErrors);
   pionIsotrkElecIsoEffVec_= PionIsoTrackVetoSearchBinsElecIso_->GetEff(BinQCD_, useAsymmErrors);
   isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(BinQCD_, useAsymmErrors);

/*
   double lepEta = 0, lepPt = 0, lepAct = 0;
   if(MuonsNum_==1 && ElectronsNum_==0){
      lepEta = std::abs(Muons->at(0).Eta());
      lepPt = Muons->at(0).Pt();
      lepAct = Muons_MT2Activity->at(0);
   }else if(MuonsNum_==0 && ElectronsNum_==1){
      lepEta = std::abs(Electrons->at(0).Eta());
      lepPt = Electrons->at(0).Pt();
      lepAct = Electrons_MT2Activity->at(0);
   }

   muIsotrkMuIDEffVec_= MuIsoTrackVetoActivityPtMuID_->GetEff(lepPt, lepEta, false);
   elecIsotrkMuIDEffVec_= ElecIsoTrackVetoActivityPtMuID_->GetEff(lepPt, lepEta, false);
   pionIsotrkMuIDEffVec_= PionIsoTrackVetoActivityPtMuID_->GetEff(lepPt, lepEta, false);
   isotrkMuIDEffVec_= IsoTrackVetoActivityPtMuID_->GetEff(lepPt, lepEta, useAsymmErrors);

   muIsotrkMuIsoEffVec_= MuIsoTrackVetoActivityPtMuIso_->GetEff(lepAct, lepPt, false);
   elecIsotrkMuIsoEffVec_= ElecIsoTrackVetoActivityPtMuIso_->GetEff(lepAct, lepPt, false);
   pionIsotrkMuIsoEffVec_= PionIsoTrackVetoActivityPtMuIso_->GetEff(lepAct, lepPt, false);
   isotrkMuIsoEffVec_= IsoTrackVetoActivityPtMuIso_->GetEff(lepAct, lepPt, useAsymmErrors);

   muIsotrkElecIDEffVec_= MuIsoTrackVetoActivityPtElecID_->GetEff(lepPt, lepEta, false);
   elecIsotrkElecIDEffVec_= ElecIsoTrackVetoActivityPtElecID_->GetEff(lepPt, lepEta, false);
   pionIsotrkElecIDEffVec_= PionIsoTrackVetoActivityPtElecID_->GetEff(lepPt, lepEta, false);
   isotrkElecIDEffVec_= IsoTrackVetoActivityPtElecID_->GetEff(lepPt, lepEta, useAsymmErrors);

   muIsotrkElecIsoEffVec_= MuIsoTrackVetoActivityPtElecIso_->GetEff(lepAct, lepPt, false);
   elecIsotrkElecIsoEffVec_= ElecIsoTrackVetoActivityPtElecIso_->GetEff(lepAct, lepPt, false);
   pionIsotrkElecIsoEffVec_= PionIsoTrackVetoActivityPtElecIso_->GetEff(lepAct, lepPt, false);
   isotrkElecIsoEffVec_= IsoTrackVetoActivityPtElecIso_->GetEff(lepAct, lepPt, useAsymmErrors);
*/
  isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
  muIsotrkMuAccEff_ = muIsotrkMuAccEffVec_.eff;
  elecIsotrkMuAccEff_ = elecIsotrkMuAccEffVec_.eff;
  pionIsotrkMuAccEff_ = pionIsotrkMuAccEffVec_.eff;
  isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
  muIsotrkMuIDEff_ = muIsotrkMuIDEffVec_.eff;
  elecIsotrkMuIDEff_ = elecIsotrkMuIDEffVec_.eff;
  pionIsotrkMuIDEff_ = pionIsotrkMuIDEffVec_.eff;
  isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;
  muIsotrkMuIsoEff_ = muIsotrkMuIsoEffVec_.eff;
  elecIsotrkMuIsoEff_ = elecIsotrkMuIsoEffVec_.eff;
  pionIsotrkMuIsoEff_ = pionIsotrkMuIsoEffVec_.eff;

  isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
  muIsotrkElecAccEff_ = muIsotrkElecAccEffVec_.eff;
  elecIsotrkElecAccEff_ = elecIsotrkElecAccEffVec_.eff;
  pionIsotrkElecAccEff_ = pionIsotrkElecAccEffVec_.eff;
  isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
  muIsotrkElecIDEff_ = muIsotrkElecIDEffVec_.eff;
  elecIsotrkElecIDEff_ = elecIsotrkElecIDEffVec_.eff;
  pionIsotrkElecIDEff_ = pionIsotrkElecIDEffVec_.eff;
  isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;
  muIsotrkElecIsoEff_ = muIsotrkElecIsoEffVec_.eff;
  elecIsotrkElecIsoEff_ = elecIsotrkElecIsoEffVec_.eff;
  pionIsotrkElecIsoEff_ = pionIsotrkElecIsoEffVec_.eff;


  if(MuonsNum_==1 && ElectronsNum_==0)
    {
      mtw =  Muons_MTW->at(0);
      MuonsPt_ = Muons->at(0).Pt();
      MuonsEta_ = Muons->at(0).Eta();

      // get Efficiencies
      muPurityEffVec_ =  MuPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      muMTWEffVec_ = MuMTWSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      //muMTWEffVec_ = MuMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
/*      if(NJets < 2.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets2_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 3.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets3_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 4.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets4_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 5.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets5_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 6.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets6_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 8.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets78_->GetEff(HT, MHT, useAsymmErrors);
      }else{
        muMTWEffVec_ = MuMTWHTMHT_NJets9Inf_->GetEff(HT, MHT, useAsymmErrors);
      }
*/    
      muDiLepCREffVec_ = MuDiLepCRNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);
      muDiLepSREffVec_ = MuDiLepSRNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);      
      muDiLepSRwoVetoEffVec_ = MuDiLepSRwoVetoNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);      

      muIsoEffVec_ = MuIsoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);
      muRecoEffVec_ = MuRecoPTEta_->GetEff(Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), useAsymmErrors);
      //muRecoEffVec_ = MuRecoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);

      muAccEffVec_ = MuAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);

      elecRecoEffVec_ = ElecRecoPTEta_->GetEff(Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), useAsymmErrors);
      //elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);

      //for compatibility
      muPurityEff_ = muPurityEffVec_.eff;
      muMTWEff_ = muMTWEffVec_.eff;
      muDiLepCREff_ = muDiLepCREffVec_.eff;
      muDiLepSREff_ = muDiLepSREffVec_.eff;
      muDiLepSRwoVetoEff_ = muDiLepSRwoVetoEffVec_.eff;
      muIsoEff_ = muIsoEffVec_.eff;
      muRecoEff_ = muRecoEffVec_.eff;
      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
      elecRecoEff_ = elecRecoEffVec_.eff;
      elecIsoEff_ = elecIsoEffVec_.eff;

      if(!runOnStandardModelMC && correctMuonIso) muIsoEff_ *= GetSF(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctMuonID) muRecoEff_ *= GetSF(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronID) elecRecoEff_ *= GetSF(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronIso) elecIsoEff_ *= GetSF(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));

      if(!runOnStandardModelMC && doTrackingCorrection){
        if(Muons->at(0).Pt() > 10) muRecoEff_ *= GetSF(h_muTrkHighPtSF, Muons->at(0).Eta());
        else muRecoEff_ *= GetSF(h_muTrkLowPtSF, Muons->at(0).Eta());
        elecRecoEff_ *= GetSF(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt());
      }

      if(runOnStandardModelMC){
        isoSF = GetSF(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
        recoSF = GetSF(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
        trackingSF = GetSF(h_muTrkHighPtSF, Muons->at(0).Eta());
      }

      if(muIsoEff_ > 1) muIsoEff_=1;
      if(muRecoEff_ > 1) muRecoEff_=1;
      if(elecRecoEff_ > 1) elecRecoEff_=1;
      if(elecIsoEff_ > 1) elecIsoEff_=1;

      // calculate Weights
      // muCS >99% purity
      purityCorrectedWeight_ = Weight * muPurityEff_;
      //purityCorrectedWeight_ = Weight;
      mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
      mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepCREff_;

      double muIsoFrac = (1 - muIsoEff_)/muIsoEff_;
      double muRecoFrac = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
      double muAccFrac = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

      muIsoWeight_ = mtwDiLepCorrectedWeight_* muIsoFrac; 
      muRecoWeight_ = mtwDiLepCorrectedWeight_* muRecoFrac;    
      muAccWeight_ = mtwDiLepCorrectedWeight_* muAccFrac;    
      muTotalWeight_ = mtwDiLepCorrectedWeight_* (muIsoFrac + muRecoFrac + muAccFrac);

      double muTotalFrac = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);
      totalMuons_ = mtwDiLepCorrectedWeight_ * muTotalFrac;

      double elecAccFrac = muTotalFrac * (1 - elecAccEff_);
      double elecRecoFrac = muTotalFrac * (elecAccEff_ * (1-elecRecoEff_));
      double elecIsoFrac = muTotalFrac * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

      elecAccWeight_ = mtwDiLepCorrectedWeight_ * elecAccFrac;
      elecRecoWeight_ = mtwDiLepCorrectedWeight_ * elecRecoFrac;
      elecIsoWeight_ = mtwDiLepCorrectedWeight_ * elecIsoFrac;

      elecTotalWeight_ = mtwDiLepCorrectedWeight_* (elecIsoFrac + elecRecoFrac + elecAccFrac);
      totalWeight_ = mtwDiLepCorrectedWeight_ * (elecIsoFrac + elecRecoFrac + elecAccFrac + muIsoFrac + muRecoFrac + muAccFrac);

      diLepLostWeight_ = mtwDiLepCorrectedWeight_ * muDiLepSRwoVetoEff_;
      //totalWeightDiLep_ = muTotalWeight_ + elecTotalWeight_ + diLepLostWeight_;
      totalWeightDiLep_ = mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + muDiLepSRwoVetoEff_);

      diLepLostVetoWeight_ = mtwDiLepCorrectedWeight_ * muDiLepSREff_;
      totalWeightDiLepIsoTrackReduced_ = mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + muDiLepSREff_);
      totalWeightDiLepIsoTrackReducedCombined_ = mtwDiLepCorrectedWeight_ * ((1-muIsotrkMuIsoEff_-elecIsotrkMuIsoEff_-pionIsotrkMuIsoEff_)*muIsoFrac + (1-muIsotrkMuIDEff_-elecIsotrkMuIDEff_-pionIsotrkMuIDEff_)*muRecoFrac + (1-muIsotrkMuAccEff_-elecIsotrkMuAccEff_-pionIsotrkMuAccEff_)*muAccFrac + (1-muIsotrkElecIsoEff_-elecIsotrkElecIsoEff_-pionIsotrkElecIsoEff_)*elecIsoFrac + (1-muIsotrkElecIDEff_-elecIsotrkElecIDEff_-pionIsotrkElecIDEff_)*elecRecoFrac + (1-muIsotrkElecAccEff_-elecIsotrkElecAccEff_-pionIsotrkElecAccEff_)*elecAccFrac + muDiLepSREff_);

      if(totalWeightDiLepIsoTrackReduced_/Weight<0.01){
        std::cout<<"Something might have gone wrong! 0L/1L too small!"<<std::endl;
        std::cout<<NJets<<"; "<<BTags<<"; "<<HT<<"; "<<MHT<<std::endl;
        std::cout<<muIsoWeight_/Weight<<"; "<<muRecoWeight_/Weight<<"; "<<muAccWeight_/Weight<<std::endl;
      }


      // Uncertainties
      // Stat uncertainties on eff maps
      isoTrackMuAccStatUp = doMuUnc(1-isotrkMuAccEffVec_.errDown/isotrkMuAccEff_, "isoTrackMuAcc");
      isoTrackMuAccStatDown = doMuUnc(1+isotrkMuAccEffVec_.errUp/isotrkMuAccEff_, "isoTrackMuAcc");
      isoTrackMuIDStatUp = doMuUnc(1-isotrkMuIDEffVec_.errDown/isotrkMuIDEff_, "isoTrackMuID");
      isoTrackMuIDStatDown = doMuUnc(1+isotrkMuIDEffVec_.errUp/isotrkMuIDEff_, "isoTrackMuID");
      isoTrackMuIsoStatUp = doMuUnc(1-isotrkMuIsoEffVec_.errDown/isotrkMuIsoEff_, "isoTrackMuIso");
      isoTrackMuIsoStatDown = doMuUnc(1+isotrkMuIsoEffVec_.errUp/isotrkMuIsoEff_, "isoTrackMuIso");
      isoTrackElecAccStatUp = doMuUnc(1-isotrkElecAccEffVec_.errDown/isotrkElecAccEff_, "isoTrackElecAcc");
      isoTrackElecAccStatDown = doMuUnc(1+isotrkElecAccEffVec_.errUp/isotrkElecAccEff_, "isoTrackElecAcc");
      isoTrackElecIDStatUp = doMuUnc(1-isotrkElecIDEffVec_.errDown/isotrkElecIDEff_, "isoTrackElecID");
      isoTrackElecIDStatDown = doMuUnc(1+isotrkElecIDEffVec_.errUp/isotrkElecIDEff_, "isoTrackElecID");
      isoTrackElecIsoStatUp = doMuUnc(1-isotrkElecIsoEffVec_.errDown/isotrkElecIsoEff_, "isoTrackElecIso");
      isoTrackElecIsoStatDown = doMuUnc(1+isotrkElecIsoEffVec_.errUp/isotrkElecIsoEff_, "isoTrackElecIso");

      MTWStatUp = doMuUnc(1-muMTWEffVec_.errDown/muMTWEff_, "MTW");
      MTWStatDown = doMuUnc(1+muMTWEffVec_.errUp/muMTWEff_, "MTW");
      purityStatUp = doMuUnc(1+muPurityEffVec_.errUp/muPurityEff_, "purity");
      purityStatDown = doMuUnc(1-muPurityEffVec_.errDown/muPurityEff_, "purity");
      singleLepPurityStatUp = doMuUnc(1+muDiLepCREffVec_.errUp/muDiLepCREff_, "DiLepCR");
      singleLepPurityStatDown = doMuUnc(1-muDiLepCREffVec_.errDown/muDiLepCREff_, "DiLepCR");
      diLepSRStatUp = doMuUnc(1+muDiLepSREffVec_.errUp/muDiLepSREff_, "DiLepSR");
      diLepSRStatDown = doMuUnc(1-muDiLepSREffVec_.errDown/muDiLepSREff_, "DiLepSR");

      muIsoStatUp = doMuUnc(1-muIsoEffVec_.errDown/muIsoEff_, "muIso");
      muIsoStatDown = doMuUnc(1+muIsoEffVec_.errUp/muIsoEff_, "muIso");
      muRecoStatUp = doMuUnc(1-muRecoEffVec_.errDown/muRecoEff_, "muReco");
      muRecoStatDown = doMuUnc(1+muRecoEffVec_.errUp/muRecoEff_, "muReco");
      muAccStatUp = doMuUnc(1-muAccEffVec_.errDown/muAccEff_, "muAcc");
      muAccStatDown = doMuUnc(1+muAccEffVec_.errUp/muAccEff_, "muAcc");

      elecIsoStatUp = doMuUnc(1-elecIsoEffVec_.errDown/elecIsoEff_, "elecIso");
      elecIsoStatDown = doMuUnc(1+elecIsoEffVec_.errUp/elecIsoEff_, "elecIso");
      elecRecoStatUp = doMuUnc(1-elecRecoEffVec_.errDown/elecRecoEff_, "elecReco");
      elecRecoStatDown = doMuUnc(1+elecRecoEffVec_.errUp/elecRecoEff_, "elecReco");
      elecAccStatUp = doMuUnc(1-elecAccEffVec_.errDown/elecAccEff_, "elecAcc");
      elecAccStatDown = doMuUnc(1+elecAccEffVec_.errUp/elecAccEff_, "elecAcc");

      // Sys uncertainties on eff maps
      if(useFlatIsoTrackUnc){
        isoTrackMuAccSysUp = doMuUnc((muIsotrkMuAccEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuAccEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuAccEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuAccSysDown = doMuUnc((muIsotrkMuAccEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuAccEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuAccEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuIDSysUp = doMuUnc((muIsotrkMuIDEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuIDEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuIDEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIDSysDown = doMuUnc((muIsotrkMuIDEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuIDEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuIDEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIsoSysUp = doMuUnc((muIsotrkMuIsoEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuIsoEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuIsoEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackMuIsoSysDown = doMuUnc((muIsotrkMuIsoEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuIsoEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuIsoEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackElecAccSysUp = doMuUnc((muIsotrkElecAccEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecAccEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecAccEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecAccSysDown = doMuUnc((muIsotrkElecAccEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecAccEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecAccEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecIDSysUp = doMuUnc((muIsotrkElecIDEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecIDEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecIDEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIDSysDown = doMuUnc((muIsotrkElecIDEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecIDEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecIDEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIsoSysUp = doMuUnc((muIsotrkElecIsoEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecIsoEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecIsoEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecIsoEff_, "isoTrackElecIso");
        isoTrackElecIsoSysDown = doMuUnc((muIsotrkElecIsoEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecIsoEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecIsoEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecIsoEff_, "isoTrackElecIso");
      }else{
        double muIsoTrackSF = h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(min(double(NJets),h_muIsoTrack_NJetsunc->GetBinCenter(h_muIsoTrack_NJetsunc->GetNbinsX()))));
        double elecIsoTrackSF = h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(min(double(NJets),h_elecIsoTrack_NJetsunc->GetBinCenter(h_elecIsoTrack_NJetsunc->GetNbinsX()))));
        double pionIsoTrackSF = h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(min(double(NJets),h_pionIsoTrack_NJetsunc->GetBinCenter(h_pionIsoTrack_NJetsunc->GetNbinsX()))));
        isoTrackMuAccSysUp = doMuUnc((muIsotrkMuAccEff_*(1-muIsoTrackSF)+elecIsotrkMuAccEff_*(1-elecIsoTrackSF)+pionIsotrkMuAccEff_*(1-pionIsoTrackSF))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuAccSysDown = doMuUnc((muIsotrkMuAccEff_*(1+muIsoTrackSF)+elecIsotrkMuAccEff_*(1+elecIsoTrackSF)+pionIsotrkMuAccEff_*(1+pionIsoTrackSF))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuIDSysUp = doMuUnc((muIsotrkMuIDEff_*(1-muIsoTrackSF)+elecIsotrkMuIDEff_*(1-elecIsoTrackSF)+pionIsotrkMuIDEff_*(1-pionIsoTrackSF))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIDSysDown = doMuUnc((muIsotrkMuIDEff_*(1+muIsoTrackSF)+elecIsotrkMuIDEff_*(1+elecIsoTrackSF)+pionIsotrkMuIDEff_*(1+pionIsoTrackSF))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIsoSysUp = doMuUnc((muIsotrkMuIsoEff_*(1-muIsoTrackSF)+elecIsotrkMuIsoEff_*(1-elecIsoTrackSF)+pionIsotrkMuIsoEff_*(1-pionIsoTrackSF))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackMuIsoSysDown = doMuUnc((muIsotrkMuIsoEff_*(1+muIsoTrackSF)+elecIsotrkMuIsoEff_*(1+elecIsoTrackSF)+pionIsotrkMuIsoEff_*(1+pionIsoTrackSF))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackElecAccSysUp = doMuUnc((muIsotrkElecAccEff_*(1-muIsoTrackSF)+elecIsotrkElecAccEff_*(1-elecIsoTrackSF)+pionIsotrkElecAccEff_*(1-pionIsoTrackSF))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecAccSysDown = doMuUnc((muIsotrkElecAccEff_*(1+muIsoTrackSF)+elecIsotrkElecAccEff_*(1+elecIsoTrackSF)+pionIsotrkElecAccEff_*(1+pionIsoTrackSF))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecIDSysUp = doMuUnc((muIsotrkElecIDEff_*(1-muIsoTrackSF)+elecIsotrkElecIDEff_*(1-elecIsoTrackSF)+pionIsotrkElecIDEff_*(1-pionIsoTrackSF))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIDSysDown = doMuUnc((muIsotrkElecIDEff_*(1+muIsoTrackSF)+elecIsotrkElecIDEff_*(1+elecIsoTrackSF)+pionIsotrkElecIDEff_*(1+pionIsoTrackSF))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIsoSysUp = doMuUnc((muIsotrkElecIsoEff_*(1-muIsoTrackSF)+elecIsotrkElecIsoEff_*(1-elecIsoTrackSF)+pionIsotrkElecIsoEff_*(1-pionIsoTrackSF))/isotrkElecIsoEff_, "isoTrackElecIso");
        isoTrackElecIsoSysDown = doMuUnc((muIsotrkElecIsoEff_*(1+muIsoTrackSF)+elecIsotrkElecIsoEff_*(1+elecIsoTrackSF)+pionIsotrkElecIsoEff_*(1+pionIsoTrackSF))/isotrkElecIsoEff_, "isoTrackElecIso");
      }

      if(useFlatMTWUnc){
        MTWSysUp = doMuUnc((muMTWEff_-(1-muMTWEff_)*MuMTWUncertaintyDown_)/muMTWEff_, "MTW");
        MTWSysDown = doMuUnc((muMTWEff_+(1-muMTWEff_)*MuMTWUncertaintyUp_)/muMTWEff_, "MTW");
      }else{
        MTWSysUp = doMuUnc(1-GetAccSF(h_muMTW_down, NJets, HT, MHT), "MTW");
        MTWSysDown = doMuUnc(1+GetAccSF(h_muMTW_up, NJets, HT, MHT), "MTW");
      }

        puritySysUp = doMuUnc((muPurityEff_+(1-muPurityEff_)*MuPurityUncertaintyUp_)/muPurityEff_, "purity");
        puritySysDown = doMuUnc((muPurityEff_-(1-muPurityEff_)*MuPurityUncertaintyDown_)/muPurityEff_, "purity");
        singleLepPuritySysUp = doMuUnc((muDiLepCREff_+(1-muDiLepCREff_)*MuSingleLepPurityUp_)/muDiLepCREff_, "DiLepCR");
        singleLepPuritySysDown = doMuUnc((muDiLepCREff_-(1-muDiLepCREff_)*MuSingleLepPurityDown_)/muDiLepCREff_, "DiLepCR");
        diLepSRSysUp = doMuUnc(1+MuDiLepSRUp_, "DiLepSR");
        diLepSRSysDown = doMuUnc(1-MuDiLepSRDown_, "DiLepSR");

      if(!useSFs){
        muIsoSysUp = doMuUnc(1-MuIsoUncertaintyDown_, "muIso");
        muIsoSysDown = doMuUnc(1+MuIsoUncertaintyUp_, "muIso");
        muRecoSysUp = doMuUnc(1-MuRecoUncertaintyDown_, "muReco");
        muRecoSysDown = doMuUnc(1+MuRecoUncertaintyUp_, "muReco");
        if(MHT>500){
          muAccSysUp = doMuUnc(1-MuAccUncertaintyDown_HighMHT_, "muAcc");
          muAccSysDown = doMuUnc(1+MuAccUncertaintyUp_HighMHT_, "muAcc");
        }else{
          muAccSysUp = doMuUnc(1-MuAccUncertaintyDown_LowMHT_, "muAcc");
          muAccSysDown = doMuUnc(1+MuAccUncertaintyUp_LowMHT_, "muAcc");
        }
        muAccQsquareSysUp = doMuUnc(1-MuAccQsquareUncertaintyDown_, "muAcc");
        muAccQsquareSysDown = doMuUnc(1+MuAccQsquareUncertaintyUp_, "muAcc");

        elecIsoSysUp = doMuUnc(1-ElecIsoUncertaintyDown_, "elecIso");
        elecIsoSysDown = doMuUnc(1+ElecIsoUncertaintyUp_, "elecIso");
        elecRecoSysUp = doMuUnc(1-ElecRecoUncertaintyDown_, "elecReco");
        elecRecoSysDown = doMuUnc(1+ElecRecoUncertaintyUp_, "elecReco");
        if(MHT>500){
          elecAccSysUp = doMuUnc(1-ElecAccUncertaintyDown_HighMHT_, "elecAcc");
          elecAccSysDown = doMuUnc(1+ElecAccUncertaintyUp_HighMHT_, "elecAcc");
        }else{
          elecAccSysUp = doMuUnc(1-ElecAccUncertaintyDown_LowMHT_, "elecAcc");
          elecAccSysDown = doMuUnc(1+ElecAccUncertaintyUp_LowMHT_, "elecAcc");
        }
        elecAccQsquareSysUp = doMuUnc(1-ElecAccQsquareUncertaintyDown_, "elecAcc");
        elecAccQsquareSysDown = doMuUnc(1+ElecAccQsquareUncertaintyUp_, "elecAcc");
      }else{
        if(!doTrackingCorrection){
          muRecoSysUp = doMuUnc(1-GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014), "muReco");
          muRecoSysDown = doMuUnc(1+GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014), "muReco");          
          elecRecoSysUp = doMuUnc(1-GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())), "elecReco");
          elecRecoSysDown = doMuUnc(1+GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())), "elecReco");
        }else{
          muRecoSysUp = doMuUnc(1-GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014) - GetSFUnc(h_muTrkHighPtSF, Muons->at(0).Eta(), 0.01), "muReco");
          muRecoSysDown = doMuUnc(1+GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014) + GetSFUnc(h_muTrkHighPtSF, Muons->at(0).Eta(), 0.01), "muReco");
          if(Muons->at(0).Pt() > 20){
            elecRecoSysUp = doMuUnc(1-GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt()), "elecReco");
            elecRecoSysDown = doMuUnc(1+GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt()), "elecReco");
          }else{
            elecRecoSysUp = doMuUnc(1-GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt(), 0.03), "elecReco");
            elecRecoSysDown = doMuUnc(1+GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt(), 0.03), "elecReco");
          }
          
        }

        muIsoSysUp = doMuUnc(1-GetSFUnc(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014), "muIso");
        muIsoSysDown = doMuUnc(1+GetSFUnc(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014), "muIso");
        elecIsoSysUp = doMuUnc(1-GetSFUnc(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())), "elecIso");
        elecIsoSysDown = doMuUnc(1+GetSFUnc(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())), "elecIso");
        
        muAccSysUp = doMuUnc(1-GetAccSF(h_muAccPDF_down, NJets, HT, MHT), "muAcc");
        muAccSysDown = doMuUnc(1+GetAccSF(h_muAccPDF_up, NJets, HT, MHT), "muAcc");
        muAccQsquareSysUp = doMuUnc(1-GetAccSF(h_muAccQ2_down, NJets, HT, MHT), "muAcc");
        muAccQsquareSysDown = doMuUnc(1+GetAccSF(h_muAccQ2_up, NJets, HT, MHT), "muAcc");
        elecAccSysUp = doMuUnc(1-GetAccSF(h_elecAccPDF_down, NJets, HT, MHT), "elecAcc");
        elecAccSysDown = doMuUnc(1+GetAccSF(h_elecAccPDF_up, NJets, HT, MHT), "elecAcc");
        elecAccQsquareSysUp = doMuUnc(1-GetAccSF(h_elecAccQ2_down, NJets, HT, MHT), "elecAcc");
        elecAccQsquareSysDown = doMuUnc(1+GetAccSF(h_elecAccQ2_up, NJets, HT, MHT), "elecAcc");
      }


      // Calculate weights if they do depend on the number of BTags:
      if(!runOnData){
        // BTags == 0
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        muDiLepCREffVec_ = MuDiLepCRNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
        muDiLepCREff_ = muDiLepCREffVec_.eff;
        muDiLepSREffVec_ = MuDiLepSRNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);      
        muDiLepSRwoVetoEffVec_ = MuDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
        muDiLepSREff_ = muDiLepSREffVec_.eff;
        muDiLepSRwoVetoEff_ = muDiLepSRwoVetoEffVec_.eff;

        muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        muMTWEff_ = muMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ =  Weight * muPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepCREff_;

        muIsoFrac = (1 - muIsoEff_)/muIsoEff_;
        muRecoFrac = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
        muAccFrac = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

        muTotalFrac = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);

        elecAccFrac = muTotalFrac * (1 - elecAccEff_);
        elecRecoFrac = muTotalFrac * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoFrac = muTotalFrac * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + muDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + muDiLepSRwoVetoEff_));


        // BTags == 1
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        muDiLepCREffVec_ = MuDiLepCRNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
        muDiLepCREff_ = muDiLepCREffVec_.eff;
        muDiLepSREffVec_ = MuDiLepSRNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);      
        muDiLepSRwoVetoEffVec_ = MuDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
        muDiLepSREff_ = muDiLepSREffVec_.eff;
        muDiLepSRwoVetoEff_ = muDiLepSRwoVetoEffVec_.eff;

        muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        muMTWEff_ = muMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ =  Weight * muPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepCREff_;

        muIsoFrac = (1 - muIsoEff_)/muIsoEff_;
        muRecoFrac = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
        muAccFrac = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

        muTotalFrac = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);

        elecAccFrac = muTotalFrac * (1 - elecAccEff_);
        elecRecoFrac = muTotalFrac * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoFrac = muTotalFrac * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + muDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + muDiLepSRwoVetoEff_));


        // BTags == 2
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        muDiLepCREffVec_ = MuDiLepCRNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
        muDiLepCREff_ = muDiLepCREffVec_.eff;
        muDiLepSREffVec_ = MuDiLepSRNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);      
        muDiLepSRwoVetoEffVec_ = MuDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
        muDiLepSREff_ = muDiLepSREffVec_.eff;
        muDiLepSRwoVetoEff_ = muDiLepSRwoVetoEffVec_.eff;

        muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        muMTWEff_ = muMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ =  Weight * muPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepCREff_;

        muIsoFrac = (1 - muIsoEff_)/muIsoEff_;
        muRecoFrac = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
        muAccFrac = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

        muTotalFrac = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);

        elecAccFrac = muTotalFrac * (1 - elecAccEff_);
        elecRecoFrac = muTotalFrac * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoFrac = muTotalFrac * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + muDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + muDiLepSRwoVetoEff_));

        // BTags >= 3
        if(NJets > 2){
          muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

          muAccEff_ = muAccEffVec_.eff;
          elecAccEff_ = elecAccEffVec_.eff;

          muDiLepCREffVec_ = MuDiLepCRNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
          muDiLepCREff_ = muDiLepCREffVec_.eff;
          muDiLepSREffVec_ = MuDiLepSRNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);      
          muDiLepSRwoVetoEffVec_ = MuDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
          muDiLepSREff_ = muDiLepSREffVec_.eff;
          muDiLepSRwoVetoEff_ = muDiLepSRwoVetoEffVec_.eff;

          muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          muMTWEff_ = muMTWEffVec_.eff;

          isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
          isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
          isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

          isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
          isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
          isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

          purityCorrectedWeight_ =  Weight * muPurityEff_;
          mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
          mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepCREff_;

          muIsoFrac = (1 - muIsoEff_)/muIsoEff_;
          muRecoFrac = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
          muAccFrac = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

          muTotalFrac = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);

          elecAccFrac = muTotalFrac * (1 - elecAccEff_);
          elecRecoFrac = muTotalFrac * (elecAccEff_ * (1-elecRecoEff_));
          elecIsoFrac = muTotalFrac * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

          totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + muDiLepSREff_));
          totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + muDiLepSRwoVetoEff_));
        }
    }

  } 
  else if(MuonsNum_==0 && ElectronsNum_==1)
    {
      mtw =  Electrons_MTW->at(0);
      ElectronsPt_ = Electrons->at(0).Pt();
      ElectronsEta_ = Electrons->at(0).Eta();

      // get Efficiencies
      elecPurityEffVec_ =  ElecPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      //elecMTWEffVec_ = ElecMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
/*      if(NJets < 2.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets2_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 3.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets3_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 4.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets4_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 5.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets5_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 6.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets6_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 8.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets78_->GetEff(HT, MHT, useAsymmErrors);
      }else{
        elecMTWEffVec_ = ElecMTWHTMHT_NJets9Inf_->GetEff(HT, MHT, useAsymmErrors);
      }
*/  
      elecDiLepCREffVec_ = ElecDiLepCRNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);
      elecDiLepSREffVec_ = ElecDiLepSRNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);      
      elecDiLepSRwoVetoEffVec_ = ElecDiLepSRwoVetoNJetsBTags_->GetEff(NJets, BTags, useAsymmErrors);      

      muIsoEffVec_ = MuIsoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);
      muRecoEffVec_ = MuRecoPTEta_->GetEff(Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), useAsymmErrors);
      //muRecoEffVec_ = MuRecoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);

      muAccEffVec_ = MuAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);

      elecRecoEffVec_ = ElecRecoPTEta_->GetEff(Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), useAsymmErrors);
      //elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);

      //for compatibility
      elecPurityEff_ = elecPurityEffVec_.eff;
      elecMTWEff_ = elecMTWEffVec_.eff;
      elecDiLepCREff_ = elecDiLepCREffVec_.eff;
      elecDiLepSREff_ = elecDiLepSREffVec_.eff;
      elecDiLepSRwoVetoEff_ = elecDiLepSRwoVetoEffVec_.eff;
      muIsoEff_ = muIsoEffVec_.eff;
      muRecoEff_ = muRecoEffVec_.eff;
      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
      elecRecoEff_ = elecRecoEffVec_.eff;
      elecIsoEff_ = elecIsoEffVec_.eff;

      if(!runOnStandardModelMC && correctMuonIso) muIsoEff_ *= GetSF(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctMuonID) muRecoEff_ *= GetSF(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronID) elecRecoEff_ *= GetSF(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronIso) elecIsoEff_ *= GetSF(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));

      if(!runOnStandardModelMC && doTrackingCorrection){
        if(Electrons->at(0).Pt() > 10) muRecoEff_ *= GetSF(h_muTrkHighPtSF, Electrons->at(0).Eta());
        else muRecoEff_ *= GetSF(h_muTrkLowPtSF, Electrons->at(0).Eta());
        elecRecoEff_ *= GetSF(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt());
      }

      if(runOnStandardModelMC){
        isoSF = GetSF(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
        recoSF = GetSF(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
        trackingSF = GetSF(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt());
      }

      if(muIsoEff_ > 1) muIsoEff_=1;
      if(muRecoEff_ > 1) muRecoEff_=1;
      if(elecRecoEff_ > 1) elecRecoEff_=1;
      if(elecIsoEff_ > 1) elecIsoEff_=1;

      // calculate Weights
      purityCorrectedWeight_ = Weight * elecPurityEff_;
      mtwCorrectedWeight_ = purityCorrectedWeight_ / elecMTWEff_;  
      mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepCREff_;

      double elecIsoFrac = (1 - elecIsoEff_)/elecIsoEff_;
      double elecRecoFrac = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
      double elecAccFrac = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

      elecIsoWeight_ = mtwDiLepCorrectedWeight_* elecIsoFrac; 
      elecRecoWeight_ = mtwDiLepCorrectedWeight_* elecRecoFrac;    
      elecAccWeight_ = mtwDiLepCorrectedWeight_* elecAccFrac;    
      elecTotalWeight_ = mtwDiLepCorrectedWeight_* (elecIsoFrac + elecRecoFrac + elecAccFrac);

      double elecTotalFrac = 1. / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);
      totalMuons_ = mtwDiLepCorrectedWeight_ * elecTotalFrac;

      double muAccFrac = elecTotalFrac * (1 - muAccEff_);
      double muRecoFrac = elecTotalFrac * (muAccEff_ * (1-muRecoEff_));
      double muIsoFrac = elecTotalFrac * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

      muAccWeight_ = mtwDiLepCorrectedWeight_ * muAccFrac;
      muRecoWeight_ = mtwDiLepCorrectedWeight_ * muRecoFrac;
      muIsoWeight_ = mtwDiLepCorrectedWeight_ * muIsoFrac;

      muTotalWeight_ = mtwDiLepCorrectedWeight_* (muIsoFrac + muRecoFrac + muAccFrac);
      totalWeight_ = mtwDiLepCorrectedWeight_ * (elecIsoFrac + elecRecoFrac + elecAccFrac + muIsoFrac + muRecoFrac + muAccFrac);

      diLepLostWeight_ = mtwDiLepCorrectedWeight_ * elecDiLepSRwoVetoEff_;
      totalWeightDiLep_ = mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + elecDiLepSRwoVetoEff_);

      diLepLostVetoWeight_ = mtwDiLepCorrectedWeight_ * elecDiLepSREff_;
      totalWeightDiLepIsoTrackReduced_ = mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_);
      totalWeightDiLepIsoTrackReducedCombined_ = mtwDiLepCorrectedWeight_ * ((1-muIsotrkMuIsoEff_-elecIsotrkMuIsoEff_-pionIsotrkMuIsoEff_)*muIsoFrac + (1-muIsotrkMuIDEff_-elecIsotrkMuIDEff_-pionIsotrkMuIDEff_)*muRecoFrac + (1-muIsotrkMuAccEff_-elecIsotrkMuAccEff_-pionIsotrkMuAccEff_)*muAccFrac + (1-muIsotrkElecIsoEff_-elecIsotrkElecIsoEff_-pionIsotrkElecIsoEff_)*elecIsoFrac + (1-muIsotrkElecIDEff_-elecIsotrkElecIDEff_-pionIsotrkElecIDEff_)*elecRecoFrac + (1-muIsotrkElecAccEff_-elecIsotrkElecAccEff_-pionIsotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_);

      if(totalWeightDiLepIsoTrackReduced_/Weight<0.01){
        std::cout<<"Something might have gone wrong! 0L/1L too small!"<<std::endl;
        std::cout<<NJets<<"; "<<BTags<<"; "<<HT<<"; "<<MHT<<std::endl;
        std::cout<<elecIsoWeight_/Weight<<"; "<<elecRecoWeight_/Weight<<"; "<<elecAccWeight_/Weight<<std::endl;
      }


      // Uncertainties
      // Stat uncertainties on eff maps
      isoTrackElecAccStatUp = doElecUnc((isotrkElecAccEff_-isotrkElecAccEffVec_.errDown)/isotrkElecAccEff_, "isoTrackElecAcc");
      isoTrackElecAccStatDown = doElecUnc((isotrkElecAccEff_+isotrkElecAccEffVec_.errUp)/isotrkElecAccEff_, "isoTrackElecAcc");
      isoTrackElecIDStatUp = doElecUnc((isotrkElecIDEff_-isotrkElecIDEffVec_.errDown)/isotrkElecIDEff_, "isoTrackElecID");
      isoTrackElecIDStatDown = doElecUnc((isotrkElecIDEff_+isotrkElecIDEffVec_.errUp)/isotrkElecIDEff_, "isoTrackElecID");
      isoTrackElecIsoStatUp = doElecUnc((isotrkElecIsoEff_-isotrkElecIsoEffVec_.errDown)/isotrkElecIsoEff_, "isoTrackElecIso");
      isoTrackElecIsoStatDown = doElecUnc((isotrkElecIsoEff_+isotrkElecIsoEffVec_.errUp)/isotrkElecIsoEff_, "isoTrackElecIso");
      isoTrackMuAccStatUp = doElecUnc((isotrkMuAccEff_-isotrkMuAccEffVec_.errDown)/isotrkMuAccEff_, "isoTrackMuAcc");
      isoTrackMuAccStatDown = doElecUnc((isotrkMuAccEff_+isotrkMuAccEffVec_.errUp)/isotrkMuAccEff_, "isoTrackMuAcc");
      isoTrackMuIDStatUp = doElecUnc((isotrkMuIDEff_-isotrkMuIDEffVec_.errDown)/isotrkMuIDEff_, "isoTrackMuID");
      isoTrackMuIDStatDown = doElecUnc((isotrkMuIDEff_+isotrkMuIDEffVec_.errUp)/isotrkMuIDEff_, "isoTrackMuID");
      isoTrackMuIsoStatUp = doElecUnc((isotrkMuIsoEff_-isotrkMuIsoEffVec_.errDown)/isotrkMuIsoEff_, "isoTrackMuIso");
      isoTrackMuIsoStatDown = doElecUnc((isotrkMuIsoEff_+isotrkMuIsoEffVec_.errUp)/isotrkMuIsoEff_, "isoTrackMuIso");

      MTWStatUp = doElecUnc((elecMTWEff_-elecMTWEffVec_.errDown)/elecMTWEff_, "MTW");
      MTWStatDown = doElecUnc((elecMTWEff_+elecMTWEffVec_.errUp)/elecMTWEff_, "MTW");
      purityStatUp = doElecUnc((elecPurityEff_+elecPurityEffVec_.errUp)/elecPurityEff_, "purity");
      purityStatDown = doElecUnc((elecPurityEff_-elecPurityEffVec_.errDown)/elecPurityEff_, "purity");
      singleLepPurityStatUp = doElecUnc((elecDiLepCREff_+elecDiLepCREffVec_.errUp)/elecDiLepCREff_, "DiLepCR");
      singleLepPurityStatDown = doElecUnc((elecDiLepCREff_-elecDiLepCREffVec_.errDown)/elecDiLepCREff_, "DiLepCR");
      diLepSRStatUp = doElecUnc((elecDiLepSREff_+elecDiLepSREffVec_.errUp)/elecDiLepSREff_, "DiLepSR");
      diLepSRStatDown = doElecUnc((elecDiLepSREff_-elecDiLepSREffVec_.errDown)/elecDiLepSREff_, "DiLepSR");

      elecIsoStatUp = doElecUnc((elecIsoEff_-elecIsoEffVec_.errDown)/elecIsoEff_, "elecIso");
      elecIsoStatDown = doElecUnc((elecIsoEff_+elecIsoEffVec_.errUp)/elecIsoEff_, "elecIso");
      elecRecoStatUp = doElecUnc((elecRecoEff_-elecRecoEffVec_.errDown)/elecRecoEff_, "elecReco");
      elecRecoStatDown = doElecUnc((elecRecoEff_+elecRecoEffVec_.errUp)/elecRecoEff_, "elecReco");
      elecAccStatUp = doElecUnc((elecAccEff_-elecAccEffVec_.errDown)/elecAccEff_, "elecAcc");
      elecAccStatDown = doElecUnc((elecAccEff_+elecAccEffVec_.errUp)/elecAccEff_, "elecAcc");

      muIsoStatUp = doElecUnc((muIsoEff_-muIsoEffVec_.errDown)/muIsoEff_, "muIso");
      muIsoStatDown = doElecUnc((muIsoEff_+muIsoEffVec_.errUp)/muIsoEff_, "muIso");
      muRecoStatUp = doElecUnc((muRecoEff_-muRecoEffVec_.errDown)/muRecoEff_, "muReco");
      muRecoStatDown = doElecUnc((muRecoEff_+muRecoEffVec_.errUp)/muRecoEff_, "muReco");
      muAccStatUp = doElecUnc((muAccEff_-muAccEffVec_.errDown)/muAccEff_, "muAcc");
      muAccStatDown = doElecUnc((muAccEff_+muAccEffVec_.errUp)/muAccEff_, "muAcc");

      // Sys uncertainties on eff maps
      if(useFlatIsoTrackUnc){
        isoTrackMuAccSysUp = doElecUnc((muIsotrkMuAccEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuAccEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuAccEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuAccSysDown = doElecUnc((muIsotrkMuAccEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuAccEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuAccEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuIDSysUp = doElecUnc((muIsotrkMuIDEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuIDEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuIDEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIDSysDown = doElecUnc((muIsotrkMuIDEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuIDEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuIDEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIsoSysUp = doElecUnc((muIsotrkMuIsoEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkMuIsoEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkMuIsoEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackMuIsoSysDown = doElecUnc((muIsotrkMuIsoEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkMuIsoEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkMuIsoEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackElecAccSysUp = doElecUnc((muIsotrkElecAccEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecAccEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecAccEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecAccSysDown = doElecUnc((muIsotrkElecAccEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecAccEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecAccEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecIDSysUp = doElecUnc((muIsotrkElecIDEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecIDEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecIDEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIDSysDown = doElecUnc((muIsotrkElecIDEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecIDEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecIDEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIsoSysUp = doElecUnc((muIsotrkElecIsoEff_*(1-muIsoTrackUncertaintyDown_)+elecIsotrkElecIsoEff_*(1-elecIsoTrackUncertaintyDown_)+pionIsotrkElecIsoEff_*(1-pionIsoTrackUncertaintyDown_))/isotrkElecIsoEff_, "isoTrackElecIso");
        isoTrackElecIsoSysDown = doElecUnc((muIsotrkElecIsoEff_*(1+muIsoTrackUncertaintyUp_)+elecIsotrkElecIsoEff_*(1+elecIsoTrackUncertaintyUp_)+pionIsotrkElecIsoEff_*(1+pionIsoTrackUncertaintyUp_))/isotrkElecIsoEff_, "isoTrackElecIso");
      }else{
        double muIsoTrackSF = h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(min(double(NJets),h_muIsoTrack_NJetsunc->GetBinCenter(h_muIsoTrack_NJetsunc->GetNbinsX()))));
        double elecIsoTrackSF = h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(min(double(NJets),h_elecIsoTrack_NJetsunc->GetBinCenter(h_elecIsoTrack_NJetsunc->GetNbinsX()))));
        double pionIsoTrackSF = h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(min(double(NJets),h_pionIsoTrack_NJetsunc->GetBinCenter(h_pionIsoTrack_NJetsunc->GetNbinsX()))));
        isoTrackMuAccSysUp = doElecUnc((muIsotrkMuAccEff_*(1-muIsoTrackSF)+elecIsotrkMuAccEff_*(1-elecIsoTrackSF)+pionIsotrkMuAccEff_*(1-pionIsoTrackSF))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuAccSysDown = doElecUnc((muIsotrkMuAccEff_*(1+muIsoTrackSF)+elecIsotrkMuAccEff_*(1+elecIsoTrackSF)+pionIsotrkMuAccEff_*(1+pionIsoTrackSF))/isotrkMuAccEff_, "isoTrackMuAcc");
        isoTrackMuIDSysUp = doElecUnc((muIsotrkMuIDEff_*(1-muIsoTrackSF)+elecIsotrkMuIDEff_*(1-elecIsoTrackSF)+pionIsotrkMuIDEff_*(1-pionIsoTrackSF))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIDSysDown = doElecUnc((muIsotrkMuIDEff_*(1+muIsoTrackSF)+elecIsotrkMuIDEff_*(1+elecIsoTrackSF)+pionIsotrkMuIDEff_*(1+pionIsoTrackSF))/isotrkMuIDEff_, "isoTrackMuID");
        isoTrackMuIsoSysUp = doElecUnc((muIsotrkMuIsoEff_*(1-muIsoTrackSF)+elecIsotrkMuIsoEff_*(1-elecIsoTrackSF)+pionIsotrkMuIsoEff_*(1-pionIsoTrackSF))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackMuIsoSysDown = doElecUnc((muIsotrkMuIsoEff_*(1+muIsoTrackSF)+elecIsotrkMuIsoEff_*(1+elecIsoTrackSF)+pionIsotrkMuIsoEff_*(1+pionIsoTrackSF))/isotrkMuIsoEff_, "isoTrackMuIso");
        isoTrackElecAccSysUp = doElecUnc((muIsotrkElecAccEff_*(1-muIsoTrackSF)+elecIsotrkElecAccEff_*(1-elecIsoTrackSF)+pionIsotrkElecAccEff_*(1-pionIsoTrackSF))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecAccSysDown = doElecUnc((muIsotrkElecAccEff_*(1+muIsoTrackSF)+elecIsotrkElecAccEff_*(1+elecIsoTrackSF)+pionIsotrkElecAccEff_*(1+pionIsoTrackSF))/isotrkElecAccEff_, "isoTrackElecAcc");
        isoTrackElecIDSysUp = doElecUnc((muIsotrkElecIDEff_*(1-muIsoTrackSF)+elecIsotrkElecIDEff_*(1-elecIsoTrackSF)+pionIsotrkElecIDEff_*(1-pionIsoTrackSF))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIDSysDown = doElecUnc((muIsotrkElecIDEff_*(1+muIsoTrackSF)+elecIsotrkElecIDEff_*(1+elecIsoTrackSF)+pionIsotrkElecIDEff_*(1+pionIsoTrackSF))/isotrkElecIDEff_, "isoTrackElecID");
        isoTrackElecIsoSysUp = doElecUnc((muIsotrkElecIsoEff_*(1-muIsoTrackSF)+elecIsotrkElecIsoEff_*(1-elecIsoTrackSF)+pionIsotrkElecIsoEff_*(1-pionIsoTrackSF))/isotrkElecIsoEff_, "isoTrackElecIso");
        isoTrackElecIsoSysDown = doElecUnc((muIsotrkElecIsoEff_*(1+muIsoTrackSF)+elecIsotrkElecIsoEff_*(1+elecIsoTrackSF)+pionIsotrkElecIsoEff_*(1+pionIsoTrackSF))/isotrkElecIsoEff_, "isoTrackElecIso");
      }

      if(useFlatMTWUnc){
        MTWSysUp = doElecUnc((elecMTWEff_-(1-elecMTWEff_)*ElecMTWUncertaintyDown_)/elecMTWEff_, "MTW");
        MTWSysDown = doElecUnc((elecMTWEff_+(1-elecMTWEff_)*ElecMTWUncertaintyUp_)/elecMTWEff_, "MTW");
      }else{
        MTWSysUp = doElecUnc(1-GetAccSF(h_elecMTW_down, NJets, HT, MHT), "MTW");
        MTWSysDown = doElecUnc(1+GetAccSF(h_elecMTW_up, NJets, HT, MHT), "MTW");
      }

        puritySysUp = doElecUnc((elecPurityEff_+(1-elecPurityEff_)*ElecPurityUncertaintyUp_)/elecPurityEff_, "purity");
        puritySysDown = doElecUnc((elecPurityEff_-(1-elecPurityEff_)*ElecPurityUncertaintyDown_)/elecPurityEff_, "purity");
        singleLepPuritySysUp = doElecUnc((elecDiLepCREff_+(1-elecDiLepCREff_)*ElecSingleLepPurityUp_)/elecDiLepCREff_, "DiLepCR");
        singleLepPuritySysDown = doElecUnc((elecDiLepCREff_-(1-elecDiLepCREff_)*ElecSingleLepPurityDown_)/elecDiLepCREff_, "DiLepCR");
        diLepSRSysUp = doElecUnc(1+ElecDiLepSRUp_, "DiLepSR");
        diLepSRSysDown = doElecUnc(1-ElecDiLepSRDown_, "DiLepSR");

      if(!useSFs){
        muIsoSysUp = doElecUnc(1-MuIsoUncertaintyDown_, "muIso");
        muIsoSysDown = doElecUnc(1+MuIsoUncertaintyUp_, "muIso");
        muRecoSysUp = doElecUnc(1-MuRecoUncertaintyDown_, "muReco");
        muRecoSysDown = doElecUnc(1+MuRecoUncertaintyUp_, "muReco");
        if(MHT>500){
          muAccSysUp = doElecUnc(1-MuAccUncertaintyDown_HighMHT_, "muAcc");
          muAccSysDown = doElecUnc(1+MuAccUncertaintyUp_HighMHT_, "muAcc");
        }else{
          muAccSysUp = doElecUnc(1-MuAccUncertaintyDown_LowMHT_, "muAcc");
          muAccSysDown = doElecUnc(1+MuAccUncertaintyUp_LowMHT_, "muAcc");
        }
        muAccQsquareSysUp = doElecUnc(1-MuAccQsquareUncertaintyDown_, "muAcc");
        muAccQsquareSysDown = doElecUnc(1+MuAccQsquareUncertaintyUp_, "muAcc");

        elecIsoSysUp = doElecUnc(1-ElecIsoUncertaintyDown_, "elecIso");
        elecIsoSysDown = doElecUnc(1+ElecIsoUncertaintyUp_, "elecIso");
        elecRecoSysUp = doElecUnc(1-ElecRecoUncertaintyDown_, "elecReco");
        elecRecoSysDown = doElecUnc(1+ElecRecoUncertaintyUp_, "elecReco");
        if(MHT>500){
          elecAccSysUp = doElecUnc(1-ElecAccUncertaintyDown_HighMHT_, "elecAcc");
          elecAccSysDown = doElecUnc(1+ElecAccUncertaintyUp_HighMHT_, "elecAcc");
        }else{
          elecAccSysUp = doElecUnc(1-ElecAccUncertaintyDown_LowMHT_, "elecAcc");
          elecAccSysDown = doElecUnc(1+ElecAccUncertaintyUp_LowMHT_, "elecAcc");
        }
        elecAccQsquareSysUp = doElecUnc(1-ElecAccQsquareUncertaintyDown_, "elecAcc");
        elecAccQsquareSysDown = doElecUnc(1+ElecAccQsquareUncertaintyUp_, "elecAcc");
      }else{
        if(!doTrackingCorrection){
          muRecoSysUp = doElecUnc(1-GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014), "muReco");
          muRecoSysDown = doElecUnc(1+GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014), "muReco");          
          elecRecoSysUp = doElecUnc(1-GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())), "elecReco");
          elecRecoSysDown = doElecUnc(1+GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())), "elecReco");
        }else{
          muRecoSysUp = doElecUnc(1-GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014) - GetSFUnc(h_muTrkHighPtSF, Electrons->at(0).Eta(), 0.01), "muReco");
          muRecoSysDown = doElecUnc(1+GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014) + GetSFUnc(h_muTrkHighPtSF, Electrons->at(0).Eta(), 0.01), "muReco");
          if(Electrons->at(0).Pt() > 20){
            elecRecoSysUp = doElecUnc(1-GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt()), "elecReco");
            elecRecoSysDown = doElecUnc(1+GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt()), "elecReco");
          }else{
            elecRecoSysUp = doElecUnc(1-GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt(), 0.03), "elecReco");
            elecRecoSysDown = doElecUnc(1+GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt(), 0.03), "elecReco");
          }
          
        }

        muIsoSysUp = doElecUnc(1-GetSFUnc(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014), "muIso");
        muIsoSysDown = doElecUnc(1+GetSFUnc(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014), "muIso");
        elecIsoSysUp = doElecUnc(1-GetSFUnc(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())), "elecIso");
        elecIsoSysDown = doElecUnc(1+GetSFUnc(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())), "elecIso");
        
        muAccSysUp = doElecUnc(1-GetAccSF(h_muAccPDF_down, NJets, HT, MHT), "muAcc");
        muAccSysDown = doElecUnc(1+GetAccSF(h_muAccPDF_up, NJets, HT, MHT), "muAcc");
        muAccQsquareSysUp = doElecUnc(1-GetAccSF(h_muAccQ2_down, NJets, HT, MHT), "muAcc");
        muAccQsquareSysDown = doElecUnc(1+GetAccSF(h_muAccQ2_up, NJets, HT, MHT), "muAcc");
        elecAccSysUp = doElecUnc(1-GetAccSF(h_elecAccPDF_down, NJets, HT, MHT), "elecAcc");
        elecAccSysDown = doElecUnc(1+GetAccSF(h_elecAccPDF_up, NJets, HT, MHT), "elecAcc");
        elecAccQsquareSysUp = doElecUnc(1-GetAccSF(h_elecAccQ2_down, NJets, HT, MHT), "elecAcc");
        elecAccQsquareSysDown = doElecUnc(1+GetAccSF(h_elecAccQ2_up, NJets, HT, MHT), "elecAcc");
      }


      // Calculate weights if they do depend on the number of BTags:
      if(!runOnData){
        // BTags == 0
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        elecDiLepCREffVec_ = ElecDiLepCRNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
        elecDiLepCREff_ = elecDiLepCREffVec_.eff;
        elecDiLepSREffVec_ = ElecDiLepSRNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);      
        elecDiLepSRwoVetoEffVec_ = ElecDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
        elecDiLepSREff_ = elecDiLepSREffVec_.eff;
        elecDiLepSRwoVetoEff_ = elecDiLepSRwoVetoEffVec_.eff;

        elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        elecMTWEff_ = elecMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ = Weight * elecPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / elecMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepCREff_;

        elecIsoFrac = (1 - elecIsoEff_)/elecIsoEff_;
        elecRecoFrac = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
        elecAccFrac = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

        elecTotalFrac = 1. / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);

        muAccFrac = elecTotalFrac * (1 - muAccEff_);
        muRecoFrac = elecTotalFrac * (muAccEff_ * (1-muRecoEff_));
        muIsoFrac = elecTotalFrac * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + elecDiLepSRwoVetoEff_));


        // BTags == 1
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        elecDiLepCREffVec_ = ElecDiLepCRNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
        elecDiLepCREff_ = elecDiLepCREffVec_.eff;
        elecDiLepSREffVec_ = ElecDiLepSRNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);      
        elecDiLepSRwoVetoEffVec_ = ElecDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
        elecDiLepSREff_ = elecDiLepSREffVec_.eff;
        elecDiLepSRwoVetoEff_ = elecDiLepSRwoVetoEffVec_.eff;

        elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        elecMTWEff_ = elecMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ = Weight * elecPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / elecMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepCREff_;

        elecIsoFrac = (1 - elecIsoEff_)/elecIsoEff_;
        elecRecoFrac = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
        elecAccFrac = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

        elecTotalFrac = 1. / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);

        muAccFrac = elecTotalFrac * (1 - muAccEff_);
        muRecoFrac = elecTotalFrac * (muAccEff_ * (1-muRecoEff_));
        muIsoFrac = elecTotalFrac * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + elecDiLepSRwoVetoEff_));


        // BTags == 2
        muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

        muAccEff_ = muAccEffVec_.eff;
        elecAccEff_ = elecAccEffVec_.eff;

        elecDiLepCREffVec_ = ElecDiLepCRNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
        elecDiLepCREff_ = elecDiLepCREffVec_.eff;
        elecDiLepSREffVec_ = ElecDiLepSRNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);      
        elecDiLepSRwoVetoEffVec_ = ElecDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
        elecDiLepSREff_ = elecDiLepSREffVec_.eff;
        elecDiLepSRwoVetoEff_ = elecDiLepSRwoVetoEffVec_.eff;

        elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        elecMTWEff_ = elecMTWEffVec_.eff;

        isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
        isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
        isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

        isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
        isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
        isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
        isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

        purityCorrectedWeight_ = Weight * elecPurityEff_;
        mtwCorrectedWeight_ = purityCorrectedWeight_ / elecMTWEff_;  
        mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepCREff_;

        elecIsoFrac = (1 - elecIsoEff_)/elecIsoEff_;
        elecRecoFrac = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
        elecAccFrac = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

        elecTotalFrac = 1. / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);

        muAccFrac = elecTotalFrac * (1 - muAccEff_);
        muRecoFrac = elecTotalFrac * (muAccEff_ * (1-muRecoEff_));
        muIsoFrac = elecTotalFrac * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

        totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_));
        totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + elecDiLepSRwoVetoEff_));

        // BTags >= 3
        if(NJets > 2){
          muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

          muAccEff_ = muAccEffVec_.eff;
          elecAccEff_ = elecAccEffVec_.eff;

          elecDiLepCREffVec_ = ElecDiLepCRNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
          elecDiLepCREff_ = elecDiLepCREffVec_.eff;
          elecDiLepSREffVec_ = ElecDiLepSRNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);      
          elecDiLepSRwoVetoEffVec_ = ElecDiLepSRwoVetoNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
          elecDiLepSREff_ = elecDiLepSREffVec_.eff;
          elecDiLepSRwoVetoEff_ = elecDiLepSRwoVetoEffVec_.eff;

          elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          elecMTWEff_ = elecMTWEffVec_.eff;

          isotrkMuAccEffVec_ = IsoTrackVetoSearchBinsMuAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuIDEffVec_= IsoTrackVetoSearchBinsMuID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuIsoEffVec_= IsoTrackVetoSearchBinsMuIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkMuAccEff_ = isotrkMuAccEffVec_.eff;
          isotrkMuIDEff_ = isotrkMuIDEffVec_.eff;
          isotrkMuIsoEff_ = isotrkMuIsoEffVec_.eff;

          isotrkElecAccEffVec_= IsoTrackVetoSearchBinsElecAcc_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecIDEffVec_= IsoTrackVetoSearchBinsElecID_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecIsoEffVec_= IsoTrackVetoSearchBinsElecIso_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
          isotrkElecAccEff_ = isotrkElecAccEffVec_.eff;
          isotrkElecIDEff_ = isotrkElecIDEffVec_.eff;
          isotrkElecIsoEff_ = isotrkElecIsoEffVec_.eff;

          purityCorrectedWeight_ = Weight * elecPurityEff_;
          mtwCorrectedWeight_ = purityCorrectedWeight_ / elecMTWEff_;  
          mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepCREff_;

          elecIsoFrac = (1 - elecIsoEff_)/elecIsoEff_;
          elecRecoFrac = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
          elecAccFrac = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

          elecTotalFrac = 1. / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);

          muAccFrac = elecTotalFrac * (1 - muAccEff_);
          muRecoFrac = elecTotalFrac * (muAccEff_ * (1-muRecoEff_));
          muIsoFrac = elecTotalFrac * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

          totalWeight_BTags_.push_back(mtwDiLepCorrectedWeight_ * ((1-isotrkMuIsoEff_)*muIsoFrac + (1-isotrkMuIDEff_)*muRecoFrac + (1-isotrkMuAccEff_)*muAccFrac + (1-isotrkElecIsoEff_)*elecIsoFrac + (1-isotrkElecIDEff_)*elecRecoFrac + (1-isotrkElecAccEff_)*elecAccFrac + elecDiLepSREff_));
          totalWeight_BTags_noIsoTrack_.push_back(mtwDiLepCorrectedWeight_ * (muIsoFrac + muRecoFrac + muAccFrac + elecIsoFrac + elecRecoFrac + elecAccFrac + elecDiLepSRwoVetoEff_));
        }
    }

  }

    WeightTrackingCorr = Weight * isoSF * recoSF * trackingSF;

    if(fillEventSeperateBTags){
      for(int i = 0; i < (NJets == 2 ? 3 : 4); i++){
        Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,i);
        BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,i);
        BTags = i;

        double storeWeight = Weight;
        WeightCorr = Weight * bTagProb.at(i) * isoSF * recoSF * trackingSF;
        Weight *= bTagProb.at(i);
        if(topPTreweight && topPtSF > 0) WeightCorr *= topPtSF;

        tPrediction_->Fill();

        Weight = storeWeight;
      }
      return kTRUE;
    }

    // Simple bTag corrections don't work that way
    //WeightCorr = Weight_bTagCorr * isoSF * recoSF * trackingSF;
    WeightCorr = 0;
    if(topPTreweight && topPtSF > 0) WeightCorr *= topPtSF;

  tPrediction_->Fill();
  return kTRUE;
}

void Prediction_isoTrackFact::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  //std::cout<<"--- QCD binning ---"<<std::endl;
  //SearchBinsQCD_->PrintUsed();

  std::cout<<"--- Search bins ---"<<std::endl;
  SearchBins_->PrintUsed();  
}

void Prediction_isoTrackFact::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.


  tPrediction_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonPrediction"));
  TFile *outPutFile = new TFile(fileName,"RECREATE"); ;
  outPutFile->cd();
  tPrediction_->Write();

  outPutFile->Close();

  cout << "Note: mT cut not yet applied " << endl;
  cout << "Saved output to " << fileName << endl;
  
}

double Prediction_isoTrackFact::doMuUnc(double relUnc, std::string type){
    double corrWeight = Weight * muPurityEff_ * muDiLepCREff_ / muMTWEff_;

    double muIsoF = (1 - muIsoEff_)/muIsoEff_;
    double muRecoF = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
    double muAccF = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;

    double muTotalF = 1. / (muIsoEff_ * muRecoEff_ * muAccEff_);
    double elecAccF = muTotalF * (1 - elecAccEff_);
    double elecRecoF = muTotalF * (elecAccEff_ * (1-elecRecoEff_));
    double elecIsoF = muTotalF * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));

    double effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;

    double wGes = corrWeight * effRatio;

    if(type == "purity"){
        double muPurityScale = muPurityEff_* relUnc;
        if(muPurityScale > 1) muPurityScale = 1;
        if(muPurityScale < 0.000001) muPurityScale = 0.000001;
        return Weight * muPurityScale * muDiLepCREff_ / muMTWEff_ * effRatio - wGes;
    }
    if(type == "DiLepCR"){
        double muDiLepCRScale = muDiLepCREff_* relUnc;
        if(muDiLepCRScale > 1) muDiLepCRScale = 1;
        if(muDiLepCRScale < 0.000001) muDiLepCRScale = 0.000001;
        return Weight * muPurityEff_ * muDiLepCRScale / muMTWEff_ * effRatio - wGes;
    }
    if(type == "MTW"){
        double muMTWScale = muMTWEff_* relUnc;
        if(muMTWScale > 1) muMTWScale = 1;
        if(muMTWScale < 0.000001) muMTWScale = 0.000001;
        return Weight * muPurityEff_ * muDiLepCREff_ / muMTWScale * effRatio - wGes;
    }
    if(type == "DiLepSR"){
        double muDiLepSRScale = muDiLepSREff_ * relUnc;
        if(muDiLepSRScale > 1) muDiLepSRScale = 1;
        if(muDiLepSRScale < 0.000001) muDiLepSRScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSRScale) - wGes;
    }
    if(type == "isoTrackMuAcc"){
        double isotrkMuAccScale = isotrkMuAccEff_* relUnc;
        if(isotrkMuAccScale > 1) isotrkMuAccScale = 1;
        if(isotrkMuAccScale < 0.000001) isotrkMuAccScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccScale)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_) - wGes;
    }
    if(type == "isoTrackMuID"){
        double isotrkMuIDScale = isotrkMuIDEff_* relUnc;
        if(isotrkMuIDScale > 1) isotrkMuIDScale = 1;
        if(isotrkMuIDScale < 0.000001) isotrkMuIDScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDScale)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_) - wGes;
    }
    if(type == "isoTrackMuIso"){
        double isotrkMuIsoScale = isotrkMuIsoEff_* relUnc;
        if(isotrkMuIsoScale > 1) isotrkMuIsoScale = 1;
        if(isotrkMuIsoScale < 0.000001) isotrkMuIsoScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoScale)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_) - wGes;
    }
    if(type == "isoTrackElecAcc"){
        double isotrkElecAccScale = isotrkElecAccEff_* relUnc;
        if(isotrkElecAccScale > 1) isotrkElecAccScale = 1;
        if(isotrkElecAccScale < 0.000001) isotrkElecAccScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccScale)*elecAccF + muDiLepSREff_) - wGes;
    }
    if(type == "isoTrackElecID"){
        double isotrkElecIDScale = isotrkElecIDEff_* relUnc;
        if(isotrkElecIDScale > 1) isotrkElecIDScale = 1;
        if(isotrkElecIDScale < 0.000001) isotrkElecIDScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDScale)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_) - wGes;
    }
    if(type == "isoTrackElecIso"){
        double isotrkElecIsoScale = isotrkElecIsoEff_* relUnc;
        if(isotrkElecIsoScale > 1) isotrkElecIsoScale = 1;
        if(isotrkElecIsoScale < 0.000001) isotrkElecIsoScale = 0.000001;
        return corrWeight * ((1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoScale)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_)- wGes;
    }
    if(type == "muIso"){
        double muIsoScale = muIsoEff_ * relUnc;
        if(muIsoScale > 1) muIsoScale = 1;
        if(muIsoScale < 0.000001) muIsoScale = 0.000001;
        muIsoF = (1 - muIsoScale)/muIsoScale;
        muRecoF = 1. / muIsoScale * (1-muRecoEff_)/muRecoEff_;
        muAccF = 1. / muIsoScale * 1. / muRecoEff_ * (1-muAccEff_)/muAccEff_;
        muTotalF = 1. / (muIsoScale * muRecoEff_ * muAccEff_);
        elecAccF = muTotalF * (1 - elecAccEff_);
        elecRecoF = muTotalF * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoF = muTotalF * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "muReco"){
        double muRecoScale = muRecoEff_ * relUnc;
        if(muRecoScale > 1) muRecoScale = 1;
        if(muRecoScale < 0.000001) muRecoScale = 0.000001;
        muIsoF = (1 - muIsoEff_)/muIsoEff_;
        muRecoF = 1. / muIsoEff_ * (1-muRecoScale)/muRecoScale;
        muAccF = 1. / muIsoEff_ * 1. / muRecoScale * (1-muAccEff_)/muAccEff_;
        muTotalF = 1. / (muIsoEff_ * muRecoScale * muAccEff_);
        elecAccF = muTotalF * (1 - elecAccEff_);
        elecRecoF = muTotalF * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoF = muTotalF * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "muAcc"){
        double muAccScale = muAccEff_ * relUnc;
        if(muAccScale > 1) muAccScale = 1;
        if(muAccScale < 0.000001) muAccScale = 0.000001;
        muIsoF = (1 - muIsoEff_)/muIsoEff_;
        muRecoF = 1. / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;
        muAccF = 1. / muIsoEff_ * 1. / muRecoEff_ * (1-muAccScale)/muAccScale;
        muTotalF = 1. / (muIsoEff_ * muRecoEff_ * muAccScale);
        elecAccF = muTotalF * (1 - elecAccEff_);
        elecRecoF = muTotalF * (elecAccEff_ * (1-elecRecoEff_));
        elecIsoF = muTotalF * (elecAccEff_ * elecRecoEff_ * (1-elecIsoEff_));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "elecAcc"){
        double elecAccScale = elecAccEff_ * relUnc;
        if(elecAccScale > 1) elecAccScale = 1;
        if(elecAccScale < 0.000001) elecAccScale = 0.000001;
        elecAccF = muTotalF * (1 - elecAccScale);
        elecRecoF = muTotalF * (elecAccScale * (1-elecRecoEff_));
        elecIsoF = muTotalF * (elecAccScale * elecRecoEff_ * (1-elecIsoEff_));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "elecReco"){
        double elecRecoScale = elecRecoEff_ * relUnc;
        if(elecRecoScale > 1) elecRecoScale = 1;
        if(elecRecoScale < 0.000001) elecRecoScale = 0.000001;
        elecRecoF = muTotalF * (elecAccEff_ * (1-elecRecoScale));
        elecIsoF = muTotalF * (elecAccEff_ * elecRecoScale * (1-elecIsoEff_));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "elecIso"){
        double elecIsoScale = elecIsoEff_ * relUnc;
        if(elecIsoScale > 1) elecIsoScale = 1;
        if(elecIsoScale < 0.000001) elecIsoScale = 0.000001;
        elecIsoF = muTotalF * (elecAccEff_ * elecRecoEff_ * (1-elecIsoScale));
        effRatio = (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + muDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }

    std::cout<<"No valid uncertainty found!"<<std::endl;
    return 0;
}

double Prediction_isoTrackFact::doElecUnc(double relUnc, std::string type){
    double corrWeight = Weight * elecPurityEff_ * elecDiLepCREff_ / elecMTWEff_;

    double elecIsoF = (1 - elecIsoEff_)/elecIsoEff_;
    double elecRecoF = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
    double elecAccF = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;

    double elecTotalF = 1. / (elecIsoEff_ * elecRecoEff_ * elecAccEff_);
    double muAccF = elecTotalF * (1 - muAccEff_);
    double muRecoF = elecTotalF * (muAccEff_ * (1-muRecoEff_));
    double muIsoF = elecTotalF * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));

    double effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;

    double wGes = corrWeight * effRatio;

    if(type == "purity"){
        double elecPurityScale = elecPurityEff_* relUnc;
        if(elecPurityScale > 1) elecPurityScale = 1;
        if(elecPurityScale < 0.000001) elecPurityScale = 0.000001;
        return Weight * elecPurityScale * elecDiLepCREff_ / elecMTWEff_ * effRatio - wGes;
    }
    if(type == "DiLepCR"){
        double elecDiLepCRScale = elecDiLepCREff_* relUnc;
        if(elecDiLepCRScale > 1) elecDiLepCRScale = 1;
        if(elecDiLepCRScale < 0.000001) elecDiLepCRScale = 0.000001;
        return Weight * elecPurityEff_ * elecDiLepCRScale / elecMTWEff_ * effRatio - wGes;
    }
    if(type == "MTW"){
        double elecMTWScale = elecMTWEff_* relUnc;
        if(elecMTWScale > 1) elecMTWScale = 1;
        if(elecMTWScale < 0.000001) elecMTWScale = 0.000001;
        return Weight * elecPurityEff_ * elecDiLepCREff_ / elecMTWScale * effRatio - wGes;
    }
    if(type == "DiLepSR"){
        double elecDiLepSRScale = elecDiLepSREff_ * relUnc;
        if(elecDiLepSRScale > 1) elecDiLepSRScale = 1;
        if(elecDiLepSRScale < 0.000001) elecDiLepSRScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSRScale) - wGes;
    }
    if(type == "isoTrackElecAcc"){
        double isotrkElecAccScale = isotrkElecAccEff_* relUnc;
        if(isotrkElecAccScale > 1) isotrkElecAccScale = 1;
        if(isotrkElecAccScale < 0.000001) isotrkElecAccScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccScale)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_) - wGes;
    }
    if(type == "isoTrackElecID"){
        double isotrkElecIDScale = isotrkElecIDEff_* relUnc;
        if(isotrkElecIDScale > 1) isotrkElecIDScale = 1;
        if(isotrkElecIDScale < 0.000001) isotrkElecIDScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDScale)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_) - wGes;
    }
    if(type == "isoTrackElecIso"){
        double isotrkElecIsoScale = isotrkElecIsoEff_* relUnc;
        if(isotrkElecIsoScale > 1) isotrkElecIsoScale = 1;
        if(isotrkElecIsoScale < 0.000001) isotrkElecIsoScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoScale)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_) - wGes;
    }
    if(type == "isoTrackMuAcc"){
        double isotrkMuAccScale = isotrkMuAccEff_* relUnc;
        if(isotrkMuAccScale > 1) isotrkMuAccScale = 1;
        if(isotrkMuAccScale < 0.000001) isotrkMuAccScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccScale)*muAccF + elecDiLepSREff_) - wGes;
    }
    if(type == "isoTrackMuID"){
        double isotrkMuIDScale = isotrkMuIDEff_* relUnc;
        if(isotrkMuIDScale > 1) isotrkMuIDScale = 1;
        if(isotrkMuIDScale < 0.000001) isotrkMuIDScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDScale)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_) - wGes;
    }
    if(type == "isoTrackMuIso"){
        double isotrkMuIsoScale = isotrkMuIsoEff_* relUnc;
        if(isotrkMuIsoScale > 1) isotrkMuIsoScale = 1;
        if(isotrkMuIsoScale < 0.000001) isotrkMuIsoScale = 0.000001;
        return corrWeight * ((1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoScale)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_)- wGes;
    }
    if(type == "elecIso"){
        double elecIsoScale = elecIsoEff_ * relUnc;
        if(elecIsoScale > 1) elecIsoScale = 1;
        if(elecIsoScale < 0.000001) elecIsoScale = 0.000001;
        elecIsoF = (1 - elecIsoScale)/elecIsoScale;
        elecRecoF = 1. / elecIsoScale * (1-elecRecoEff_)/elecRecoEff_;
        elecAccF = 1. / elecIsoScale * 1. / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;
        elecTotalF = 1. / (elecIsoScale * elecRecoEff_ * elecAccEff_);
        muAccF = elecTotalF * (1 - muAccEff_);
        muRecoF = elecTotalF * (muAccEff_ * (1-muRecoEff_));
        muIsoF = elecTotalF * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "elecReco"){
        double elecRecoScale = elecRecoEff_ * relUnc;
        if(elecRecoScale > 1) elecRecoScale = 1;
        if(elecRecoScale < 0.000001) elecRecoScale = 0.000001;
        elecIsoF = (1 - elecIsoEff_)/elecIsoEff_;
        elecRecoF = 1. / elecIsoEff_ * (1-elecRecoScale)/elecRecoScale;
        elecAccF = 1. / elecIsoEff_ * 1. / elecRecoScale * (1-elecAccEff_)/elecAccEff_;
        elecTotalF = 1. / (elecIsoEff_ * elecRecoScale * elecAccEff_);
        muAccF = elecTotalF * (1 - muAccEff_);
        muRecoF = elecTotalF * (muAccEff_ * (1-muRecoEff_));
        muIsoF = elecTotalF * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "elecAcc"){
        double elecAccScale = elecAccEff_ * relUnc;
        if(elecAccScale > 1) elecAccScale = 1;
        if(elecAccScale < 0.000001) elecAccScale = 0.000001;
        elecIsoF = (1 - elecIsoEff_)/elecIsoEff_;
        elecRecoF = 1. / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
        elecAccF = 1. / elecIsoEff_ * 1. / elecRecoEff_ * (1-elecAccScale)/elecAccScale;
        elecTotalF = 1. / (elecIsoEff_ * elecRecoEff_ * elecAccScale);
        muAccF = elecTotalF * (1 - muAccEff_);
        muRecoF = elecTotalF * (muAccEff_ * (1-muRecoEff_));
        muIsoF = elecTotalF * (muAccEff_ * muRecoEff_ * (1-muIsoEff_));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "muAcc"){
        double muAccScale = muAccEff_ * relUnc;
        if(muAccScale > 1) muAccScale = 1;
        if(muAccScale < 0.000001) muAccScale = 0.000001;
        muAccF = elecTotalF * (1 - muAccScale);
        muRecoF = elecTotalF * (muAccScale * (1-muRecoEff_));
        muIsoF = elecTotalF * (muAccScale * muRecoEff_ * (1-muIsoEff_));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "muReco"){
        double muRecoScale = muRecoEff_ * relUnc;
        if(muRecoScale > 1) muRecoScale = 1;
        if(muRecoScale < 0.000001) muRecoScale = 0.000001;
        muRecoF = elecTotalF * (muAccEff_ * (1-muRecoScale));
        muIsoF = elecTotalF * (muAccEff_ * muRecoScale * (1-muIsoEff_));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }
    if(type == "muIso"){
        double muIsoScale = muIsoEff_ * relUnc;
        if(muIsoScale > 1) muIsoScale = 1;
        if(muIsoScale < 0.000001) muIsoScale = 0.000001;
        muIsoF = elecTotalF * (muAccEff_ * muRecoEff_ * (1-muIsoScale));
        effRatio = (1-isotrkElecIsoEff_)*elecIsoF + (1-isotrkElecIDEff_)*elecRecoF + (1-isotrkElecAccEff_)*elecAccF + (1-isotrkMuIsoEff_)*muIsoF + (1-isotrkMuIDEff_)*muRecoF + (1-isotrkMuAccEff_)*muAccF + elecDiLepSREff_;
        return corrWeight * effRatio - wGes;
    }

    std::cout<<"No valid uncertainty found!"<<std::endl;
    return 0;
}

void Prediction_isoTrackFact::resetValues()
{
  mtw=0.;
  muMTWEff_=0.;
  mtwCorrectedWeight_=0.;
  muDiLepCREff_=0.;
  mtwDiLepCorrectedWeight_=0.;
  muIsoEff_=0;
  muIsoWeight_=0;
  muRecoEff_=0;
  muRecoWeight_=0;
  muAccEff_=0;
  muAccWeight_=0;
  muTotalWeight_=0.;
  totalMuons_=0;
  elecIsoEff_=0;
  elecIsoWeight_=0;
  elecRecoEff_=0;
  elecRecoWeight_=0;
  elecAccEff_=0;
  elecAccWeight_=0;
  elecTotalWeight_=0;
  totalElectrons_=0.;
  totalWeight_=0.;
  muDiLepSREff_=0.;
  elecDiLepSREff_=0.;
  muDiLepSRwoVetoEff_=0.;
  elecDiLepSRwoVetoEff_=0.;
  totalWeightDiLep_=0.;
  totalWeightDiLepIsoTrackReduced_=0.;

  MuonsPTW.clear();
  MuonsPt_=0.;
  MuonsEta_=0.;
  //  MuonsCDTT.clear();
  ElectronsPTW.clear();
  ElectronsPt_=0.;
  ElectronsEta_=0.;
  //  ElectronsCDTT.clear();

  ptw_bins.clear();

  totalWeight_BTags_.clear();
  totalWeight_BTags_noIsoTrack_.clear();
  topPt.clear();
}

bool Prediction_isoTrackFact::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    if(HBHENoiseFilter!=1) result=false;
    if(HBHEIsoNoiseFilter!=1) result=false;
    if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
    if(eeBadScFilter!=1) result=false;

    if(runOnData){
      if(!BadChargedCandidateFilter) result=false;
      if(!BadPFMuonFilter) result=false;
      if(globalTightHalo2016Filter!=1) result=false;
    }    
  }
  if(NVtx<=0) result=false;

  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;

  for(unsigned j = 0; j < Jets->size(); j++){
    if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
    if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
      //std::cout<<"found bad muon jet"<<std::endl;
      result=false;
    }
  }

  // Do not apply on fastSim samples!
  if(!runOnSignalMC) if(!JetID) result=false;
  return result;
}

std::vector<int> Prediction_isoTrackFact::GetPTWBin(int Bin, double ptw, double ht) {

  std::vector<int> ptw_bins;
  if (Bin%6>0&&Bin%6<4) ptw_bins.push_back(Bin);
  if (ptw > 500 && ptw < 750) {
    if (ht>500&&ht<1200) ptw_bins.push_back(6*((Bin-1)/6)+4);
    else if (ht>1200) ptw_bins.push_back(6*((Bin-1)/6)+5);
  } else if (ptw > 750) {
    if (ht>800) ptw_bins.push_back(6*((Bin-1)/6)+6);
    if (ht>500&&ht<1200) ptw_bins.push_back(6*((Bin-1)/6)+4);
    else if (ht>1200) ptw_bins.push_back(6*((Bin-1)/6)+5);
  }

  return ptw_bins;
  
}

