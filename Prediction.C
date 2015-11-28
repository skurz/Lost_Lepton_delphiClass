#define Prediction_cxx

#include "Prediction.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>


void Prediction::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

}

void Prediction::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TFile *effInput = new TFile("Efficiencies.root","READ");
  TDirectory *EffInputFolder =   (TDirectory*)effInput->Get("Efficiencies");

  if(UseTagAndProbeEffIso_)
    {
      TDirectory *EffTagAndProbeInputFolder =   (TDirectory*)effInput->Get("TagAndProbe");
      MuIsoPTActivityTAPMC_ = (TH2D*)EffTagAndProbeInputFolder->Get("MuIsoTagAndProbeMC");    
      ElecIsoPTActivityTAPMC_ = (TH2D*)EffTagAndProbeInputFolder->Get("ElecIsoTagAndProbeMC");
    
    }
  if(UseTagAndProbeEffReco_)
    {
      TDirectory *EffTagAndProbeInputFolder =   (TDirectory*)effInput->Get("TagAndProbe");
      MuRecoPTActivityTAPMC_ = (TH2D*)EffTagAndProbeInputFolder->Get("MuRecoTagAndProbeMC");
      ElecRecoPTActivityTAPMC_ = (TH2D*)EffTagAndProbeInputFolder->Get("ElecRecoTagAndProbeMC");    
    }

  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity", EffInputFolder);
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D", EffInputFolder);
  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets", EffInputFolder);

  MuDiLepContributionMTWAppliedNJets_ = new TH1Eff("MuDiLepContributionMTWNJets1D", EffInputFolder);
  MuDiLepEffMTWAppliedNJets_ = new TH1Eff("MuDiLepMTWNJets1D", EffInputFolder);

  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT", EffInputFolder);
  MuIsoRelPTDeltaRJet_ = new TH2Eff("MuIsoRelPTDeltaRJet", EffInputFolder);
  MuRecoActivityPT_= new TH2Eff("MuRecoActivityPT", EffInputFolder);
  MuRecoPTEta_= new TH2Eff("MuRecoPTEta", EffInputFolder);
  MuPurityMHTNJets_ = new TH2Eff("MuonPurityMHTNJet", EffInputFolder); 

  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets", EffInputFolder);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets", EffInputFolder);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT", EffInputFolder);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets", EffInputFolder);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0", EffInputFolder);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf", EffInputFolder);
  MuAccHTMHT_NJetsLow_ = new TH2Eff("MuAccHTMHT_NJetsLow", EffInputFolder);
  MuAccHTMHT_NJets4_ = new TH2Eff("MuAccHTMHT_NJets4", EffInputFolder);
  MuAccHTMHT_NJets5_ = new TH2Eff("MuAccHTMHT_NJets5", EffInputFolder);
  MuAccHTMHT_NJets6_ = new TH2Eff("MuAccHTMHT_NJets6", EffInputFolder);
  MuAccHTMHT_NJets78_ = new TH2Eff("MuAccHTMHT_NJets78", EffInputFolder);
  MuAccHTMHT_NJets9Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf", EffInputFolder);
  MuAccHTMHT_NJetsHigh_ = new TH2Eff("MuAccHTMHT_NJetsHigh", EffInputFolder);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0", EffInputFolder);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf", EffInputFolder); 


  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT", EffInputFolder);
  ElecIsoRelPTDeltaRJet_ = new TH2Eff("ElecIsoRelPTDeltaRJet", EffInputFolder);
  ElecRecoActivityPT_= new TH2Eff("ElecRecoActivityPT", EffInputFolder);
  ElecRecoPTEta_= new TH2Eff("ElecRecoPTEta", EffInputFolder);
  
  ElecPurityMHTNJets_ = new TH2Eff("ElecPurityMHTNJet", EffInputFolder);
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D", EffInputFolder);
  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets", EffInputFolder);

  ElecDiLepContributionMTWAppliedNJets_ = new TH1Eff("ElecDiLepContributionMTWNJets1D", EffInputFolder);
  ElecDiLepEffMTWAppliedNJets_ = new TH1Eff("ElecDiLepMTWNJets1D", EffInputFolder);  

  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets", EffInputFolder);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets", EffInputFolder);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT", EffInputFolder);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets", EffInputFolder);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0", EffInputFolder);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf", EffInputFolder);
  ElecAccHTMHT_NJetsLow_ = new TH2Eff("ElecAccHTMHT_NJetsLow", EffInputFolder);
  ElecAccHTMHT_NJets4_ = new TH2Eff("ElecAccHTMHT_NJets4", EffInputFolder);
  ElecAccHTMHT_NJets5_ = new TH2Eff("ElecAccHTMHT_NJets5", EffInputFolder);
  ElecAccHTMHT_NJets6_ = new TH2Eff("ElecAccHTMHT_NJets6", EffInputFolder);
  ElecAccHTMHT_NJets78_ = new TH2Eff("ElecAccHTMHT_NJets78", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf", EffInputFolder);
  ElecAccHTMHT_NJetsHigh_ = new TH2Eff("ElecAccHTMHT_NJetsHigh", EffInputFolder);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0", EffInputFolder);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf", EffInputFolder);
  
  
  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff", EffInputFolder);
  ExpectationReductionIsoTrackBTagsNJetsEff_= new TH2Eff("IsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionIsoTrackHTNJetsEff_ = new TH2Eff("IsoTrackReductionHTNJets", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJetsLowEff_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJetsHighEff_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsHigh", EffInputFolder);
  ExpectationReductionIsoTrackMHTNJetsEff_ = new TH2Eff("IsoTrackReductionMHTNJets", EffInputFolder);
  ExpectationReductionMuIsoTrackBTagsNJetsEff_= new TH2Eff("MuIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionElecIsoTrackBTagsNJetsEff_= new TH2Eff("ElecIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionPionIsoTrackBTagsNJetsEff_= new TH2Eff("PionIsoTrackReductionBTagNJets", EffInputFolder);

  ExpectationReductionMuIsoTrackHTMHT_NJetsLowEff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsLow", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJetsLowEff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsLow", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJetsLowEff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsLow", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJetsHighEff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsHigh", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJetsHighEff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsHigh", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJetsHighEff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsHigh", EffInputFolder);


  // TProfiles
  MuMeanWeight_ = new TProfile("MuMeanWeight","MuMeanWeight",72,1.,73.);
  MuMeanWeight_->Sumw2();
  ElecMeanWeight_ = new TProfile("ElecMeanWeight","ElecMeanWeight",72,1.,73.);
  ElecMeanWeight_->Sumw2();
  CombinedMeanWeight_ = new TProfile("CombinedMeanWeight","CombinedMeanWeight",72,1.,73.);
  CombinedMeanWeight_->Sumw2();

  for(int b = 0; b <72; b++){
    MuWeightPerBin_[b] = new TH1D(TString("MuWeightPerBin_")+TString(to_string(b+1)),TString("MuWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    MuWeightPerBin_[b]->Sumw2();
    ElecWeightPerBin_[b] = new TH1D(TString("ElecWeightPerBin_")+TString(to_string(b+1)),TString("ElecWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    ElecWeightPerBin_[b]->Sumw2();
    CombinedWeightPerBin_[b] = new TH1D(TString("CombinedWeightPerBin_")+TString(to_string(b+1)),TString("CombinedWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    CombinedWeightPerBin_[b]->Sumw2();
  }  
    
  
  tPrediction_ = new TTree("LostLeptonPrediction","a simple Tree with simple variables");
  tPrediction_->Branch("HT",&HT);
  tPrediction_->Branch("MHT",&MHT);
  tPrediction_->Branch("NJets",&NJets);
  tPrediction_->Branch("BTags",&BTags);
  tPrediction_->Branch("NVtx",&NVtx);
  tPrediction_->Branch("Bin",&Bin_);
  tPrediction_->Branch("BinQCD",&BinQCD_);
  tPrediction_->Branch("isoTracks",&isoTracks);
  tPrediction_->Branch("Leptons",&Leptons);
  tPrediction_->Branch("DeltaPhi1",&DeltaPhi1);
  tPrediction_->Branch("DeltaPhi2",&DeltaPhi2);
  tPrediction_->Branch("DeltaPhi3",&DeltaPhi3);
  tPrediction_->Branch("DeltaPhi4",&DeltaPhi4);
  tPrediction_->Branch("Weight", &Weight);
  tPrediction_->Branch("MET",&METPt);
  tPrediction_->Branch("METPhi",&METPhi);
  tPrediction_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum_);
  tPrediction_->Branch("selectedIDIsoMuons", "std::vector<TLorentzVector>", &selectedIDIsoMuons, 32000, 0);
  tPrediction_->Branch("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW);
  tPrediction_->Branch("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity);
  tPrediction_->Branch("selectedIDIsoMuonsRelPTJet", &selectedIDIsoMuonsRelPTJet);
  tPrediction_->Branch("selectedIDIsoMuonsDeltaRJet", &selectedIDIsoMuonsDeltaRJet);
  tPrediction_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum_);
  tPrediction_->Branch("selectedIDIsoElectrons", "std::vector<TLorentzVector>", &selectedIDIsoElectrons, 32000, 0);
  tPrediction_->Branch("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW);
  tPrediction_->Branch("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity);
  tPrediction_->Branch("selectedIDIsoElectronsRelPTJet", &selectedIDIsoElectronsRelPTJet);
  tPrediction_->Branch("selectedIDIsoElectronsDeltaRJet", &selectedIDIsoElectronsDeltaRJet);
  tPrediction_->Branch("MTW",&mtw);
  tPrediction_->Branch("PTW",&ptw);
  //  tPrediction_->Branch("GenPTW",&genptw);
  muActivityMethod=muActivityMethod_;
  elecActivityMethod=elecActivityMethod_;
  isoTrackActivityMethod=isoTrackActivityMethod_;
  tPrediction_->Branch("muActivityMethod",&muActivityMethod);  
  tPrediction_->Branch("elecActivityMethod",&elecActivityMethod);  
  tPrediction_->Branch("isoTrackActivityMethod",&isoTrackActivityMethod);
  tPrediction_->Branch("muMTWEff",&muMTWEff_);
  tPrediction_->Branch("mtwCorrectedWeight",&mtwCorrectedWeight_);
  tPrediction_->Branch("muDiLepContributionMTWAppliedEff",&muDiLepContributionMTWAppliedEff_);
  tPrediction_->Branch("mtwDiLepCorrectedWeight",&mtwDiLepCorrectedWeight_);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoMuTrackReduced",&totalWeightDiLepIsoMuTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoElecTrackReduced",&totalWeightDiLepIsoElecTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoPionTrackReduced",&totalWeightDiLepIsoPionTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined_);
  tPrediction_->Branch("muIsoWeight",&muIsoWeight_);
  tPrediction_->Branch("muIsoOnlyWeight",&muIsoOnlyWeight_);
  tPrediction_->Branch("muIsoEff",&muIsoEff_);
  tPrediction_->Branch("muRecoWeight",&muRecoWeight_);
  tPrediction_->Branch("muRecoEff",&muRecoEff_);
  tPrediction_->Branch("muAccWeight",&muAccWeight_);
  tPrediction_->Branch("muAccEff",&muAccEff_);
  tPrediction_->Branch("muTotalWeight",&muTotalWeight_);
  tPrediction_->Branch("muTotalWeightDiLep",&muTotalWeightDiLep_);
  tPrediction_->Branch("muTotalWeightDiLepIsoTrackReduced",&muTotalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalMuons",&totalMuons_);
  tPrediction_->Branch("elecAccWeight",&elecAccWeight_);
  tPrediction_->Branch("elecAccEff",&elecAccEff_);
  tPrediction_->Branch("elecRecoWeight",&elecRecoWeight_);
  tPrediction_->Branch("elecRecoEff",&elecRecoEff_);
  tPrediction_->Branch("elecIsoWeight",&elecIsoWeight_);
  tPrediction_->Branch("elecIsoOnlyWeight",&elecIsoOnlyWeight_);
  tPrediction_->Branch("elecIsoEff",&elecIsoEff_);
  tPrediction_->Branch("elecTotalWeight",&elecTotalWeight_);
  tPrediction_->Branch("elecTotalWeightDiLep",&elecTotalWeightDiLep_);
  tPrediction_->Branch("elecTotalWeightDiLepIsoTrackReduced",&elecTotalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalElectrons",&totalElectrons_);
  tPrediction_->Branch("expectationReductionIsoTrackEff",&expectationReductionIsoTrackEff_);
  tPrediction_->Branch("expectationReductionMuIsoTrackEff",&expectationReductionMuIsoTrackEff_);
  tPrediction_->Branch("expectationReductionElecIsoTrackEff",&expectationReductionElecIsoTrackEff_);
  tPrediction_->Branch("expectationReductionPionIsoTrackEff",&expectationReductionPionIsoTrackEff_);
  tPrediction_->Branch("expectationReductionIsoTrackEffCombined",&expectationReductionIsoTrackEffCombined_);
  tPrediction_->Branch("totalWeight",&totalWeight_);
  tPrediction_->Branch("muDiLepEffMTWAppliedEff",&muDiLepEffMTWAppliedEff_);
  tPrediction_->Branch("elecDiLepEffMTWAppliedEff",&elecDiLepEffMTWAppliedEff_);
  tPrediction_->Branch("totalWeightDiLep",&totalWeightDiLep_);
  tPrediction_->Branch("isoMuonTracks",&isoMuonTracks);
  tPrediction_->Branch("IsolatedMuonTracksVeto", "std::vector<TLorentzVector>", &IsolatedMuonTracksVeto, 32000, 0);
  tPrediction_->Branch("IsolatedMuonTracksVetoActivity", &IsolatedMuonTracksVetoActivity);
  tPrediction_->Branch("IsolatedMuonTracksVetoMTW", &IsolatedMuonTracksVetoMTW);
  tPrediction_->Branch("isoElectronTracks",&isoElectronTracks);
  tPrediction_->Branch("IsolatedElectronTracksVeto", "std::vector<TLorentzVector>", &IsolatedElectronTracksVeto, 32000, 0);
  tPrediction_->Branch("IsolatedElectronTracksVetoActivity", &IsolatedElectronTracksVetoActivity);
  tPrediction_->Branch("IsolatedElectronTracksVetoMTW", &IsolatedElectronTracksVetoMTW);
  tPrediction_->Branch("isoPionTracks",&isoPionTracks);
  tPrediction_->Branch("IsolatedPionTracksVeto", "std::vector<TLorentzVector>", &IsolatedPionTracksVeto, 32000, 0);
  tPrediction_->Branch("IsolatedPionTracksVetoActivity", &IsolatedPionTracksVetoActivity);
  tPrediction_->Branch("IsolatedPionTracksVetoMTW", &IsolatedPionTracksVetoMTW);
  tPrediction_->Branch("HTJetsMask", &HTJetsMask);
  if(signalScan){
    tPrediction_->Branch("SusyLSPMass", &SusyLSPMass);
    tPrediction_->Branch("SusyMotherMass", &SusyMotherMass);
    tPrediction_->Branch("w_isr", &w_isr);
    tPrediction_->Branch("w_pu", &w_pu);
    tPrediction_->Branch("xsec", &xsec);
    tPrediction_->Branch("nEvtsTotal", &nEvtsTotal);
    tPrediction_->Branch("Jets_partonFlavor", &Jets_partonFlavor);
    tPrediction_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
    tPrediction_->Branch("bTagProb", &bTagProb);
  }

  tPrediction_->Branch("isoTrackStatUp", &isoTrackStatUp);
  tPrediction_->Branch("isoTrackStatDown", &isoTrackStatDown);
  tPrediction_->Branch("muIsoTrackStatUp", &muIsoTrackStatUp);
  tPrediction_->Branch("muIsoTrackStatDown", &muIsoTrackStatDown);
  tPrediction_->Branch("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  tPrediction_->Branch("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  tPrediction_->Branch("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  tPrediction_->Branch("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  tPrediction_->Branch("MTWStatUp", &MTWStatUp);
  tPrediction_->Branch("MTWStatDown", &MTWStatDown);
  tPrediction_->Branch("purityStatUp", &purityStatUp);
  tPrediction_->Branch("purityStatDown", &purityStatDown);
  tPrediction_->Branch("singleLepPurityStatUp", &singleLepPurityStatUp);
  tPrediction_->Branch("singleLepPurityStatDown", &singleLepPurityStatDown);
  tPrediction_->Branch("diLepFoundStatUp", &diLepFoundStatUp);
  tPrediction_->Branch("diLepFoundStatDown", &diLepFoundStatDown);
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
  
  tPrediction_->Branch("isoTrackSysUp", &isoTrackSysUp);
  tPrediction_->Branch("isoTrackSysDown", &isoTrackSysDown);
  tPrediction_->Branch("muIsoTrackSysUp", &muIsoTrackSysUp);
  tPrediction_->Branch("muIsoTrackSysDown", &muIsoTrackSysDown);
  tPrediction_->Branch("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  tPrediction_->Branch("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  tPrediction_->Branch("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  tPrediction_->Branch("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  tPrediction_->Branch("MTWSysUp", &MTWSysUp);
  tPrediction_->Branch("MTWSysDown", &MTWSysDown);
  tPrediction_->Branch("puritySysUp", &puritySysUp);
  tPrediction_->Branch("puritySysDown", &puritySysDown);
  tPrediction_->Branch("singleLepPuritySysUp", &singleLepPuritySysUp);
  tPrediction_->Branch("singleLepPuritySysDown", &singleLepPuritySysDown);
  tPrediction_->Branch("diLepFoundSysUp", &diLepFoundSysUp);
  tPrediction_->Branch("diLepFoundSysDown", &diLepFoundSysDown);
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

//  tPrediction_->Branch("diBosonUp", &diBosonUp);
//  tPrediction_->Branch("diBosonDown", &diBosonDown);
//  tPrediction_->Branch("nonClosureUp", &nonClosureUp);
//  tPrediction_->Branch("nonClosureDown", &nonClosureDown);

  tPrediction_->Branch("totalStatUp", &totalStatUp);
  tPrediction_->Branch("totalSysUp", &totalSysUp);
  tPrediction_->Branch("totalUncUp", &totalUncUp);

  tPrediction_->Branch("totalStatDown", &totalStatDown);
  tPrediction_->Branch("totalSysDown", &totalSysDown);
  tPrediction_->Branch("totalUncDown", &totalUncDown);

  GetOutputList()->Add(tPrediction_);
  SearchBins_ = new SearchBins(false); // 72 searchbins
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
  std::cout<<"Use MET filters: "<<useFilterData<<std::endl;
  std::cout<<"Apply Triggers: "<<useTrigger<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"UseAsymmErrors: "<<useAsymmErrors<<std::endl;
  std::cout<<"UseTagAndProbeEffIso: "<<UseTagAndProbeEffIso_<<std::endl;
  std::cout<<"UseTagAndProbeEffReco: "<<UseTagAndProbeEffReco_<<std::endl;
  
}

Bool_t Prediction::Process(Long64_t entry)
{
  resetValues();
  fChain->GetTree()->GetEntry(entry);

  if(restrictRunNum) if(RunNum > 257599) return kTRUE;

  if(HTgen_cut > 0.01) if(genHT > HTgen_cut) return kTRUE;
  
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  if(useFilterList){
    bool CSCTightHaloFilterUpdate = evtListFilter->CheckEvent(RunNum,LumiBlockNum,EvtNum);
    if(!CSCTightHaloFilterUpdate) return kTRUE;
  } 


  isoTracks= isoElectronTracks + isoMuonTracks + isoPionTracks;

  selectedIDMuonsNum_ = selectedIDMuons->size();
  selectedIDIsoMuonsNum_ = selectedIDIsoMuons->size();
  selectedIDElectronsNum_ = selectedIDElectrons->size();
  selectedIDIsoElectronsNum_ = selectedIDIsoElectrons->size();

  JetsNum_ = Jets->size();

  if((selectedIDIsoMuonsNum_+selectedIDIsoElectronsNum_) !=1) return kTRUE;

  /*
  bool passTrigger = false;
  for (std::vector<string>::iterator it = TriggerNames->begin() ; it != TriggerNames->end(); ++it){
    if(it->find("HLT_PFHT350_PFMET100_NoiseCleaned_v")!=std::string::npos){  // Run2015A,B
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
    if(it->find("HLT_PFHT350_PFMET100_JetIdCleaned_v")!=std::string::npos){  // Run2015C.D
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
    if(it->find("HLT_PFHT350_PFMET100_v")!=std::string::npos){  // Run2015C.D
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
  }
  if(useTrigger && !passTrigger) return kTRUE;
  */
  if(useTrigger) if(!TriggerPass->at(34) && !TriggerPass->at(35) && !TriggerPass->at(36)) return kTRUE;


  if(signalScan){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    if(currentTree != treeName){
      treeName = currentTree;   
         
      TH1F *nEventProc = (TH1F*)fChain->GetCurrentFile()->Get("nEventProc");
      TH1F *nEventNeg = (TH1F*)fChain->GetCurrentFile()->Get("nEventNeg");
      nEvtsTotal = nEventProc->GetBinContent(1) - 2*nEventNeg->GetBinContent(1);
/*
      // not recommended for Jamboree
      h_genpt = (TH1*)fChain->GetCurrentFile()->Get("GenPt");
      delete isrcorr;
      isrcorr = new ISRCorrector();
      isrcorr->SetWeights(h_isr,h_genpt);
      isrcorr->SetMother(1000021);
*/
      delete btagcorr;
      btagcorr = new BTagCorrector();
      btagcorr->SetEffs(fChain->GetCurrentFile());
      btagcorr->SetCalib("btag/CSVv2_mod.csv");
      btagcorr->SetFastSim(true);
      btagcorr->SetCalibFastSim("btag/CSV_13TEV_Combined_20_11_2015.csv");
    }

    xsec = 0;
    for (std::vector<std::pair<double, double>>::iterator it = xsecs.begin() ; it != xsecs.end(); ++it){
      if(std::abs(SusyMotherMass - it->first) < 0.1){
        xsec = it->second;
        break;
      }
    }

    Weight = xsec / nEvtsTotal;
    if(Weight < 0) Weight *= -1;

    //w_isr = isrcorr->GetCorrection(genParticles,genParticles_PDGid);
    // not recommended for Jamboree
    //Weight *= w_isr;

    bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,HTJetsMask);
  }

  if(useTriggerEffWeight){
    if(signalScan){
      Weight *= GetSignalTriggerEffWeight(MHT);
    }else{
      Weight *= GetTriggerEffWeight(MHT);
    }
  }

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

  if(runOnData) Weight = 1.;

  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);

  // get IsoTrack Effs
  //expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTNJetsEff_->GetEff(HT, NJets, useAsymmErrors);
  //expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackMHTNJetsEff_->GetEff(MHT, NJets, useAsymmErrors);
  //expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  if(NJets < 6.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJetsLowEff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJetsHighEff_->GetEff(HT, MHT, useAsymmErrors);

  //expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  //expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  //expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  if(NJets < 6.5) expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackHTMHT_NJetsLowEff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackHTMHT_NJetsHighEff_->GetEff(HT, MHT, useAsymmErrors);
  if(NJets < 6.5) expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackHTMHT_NJetsLowEff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackHTMHT_NJetsHighEff_->GetEff(HT, MHT, useAsymmErrors);
  if(NJets < 6.5) expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackHTMHT_NJetsLowEff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackHTMHT_NJetsHighEff_->GetEff(HT, MHT, useAsymmErrors);

  //for compatibility
  expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
  expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
  expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
  expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;


  if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0)
    {
      // cout << "Single muon event...";
      mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet);
      ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet);
      //selectedIDIsoMuonsActivity.push_back(MuActivity(selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons->at(0).Phi(),muActivityMethod_));
      //double elecActivity = ElecActivity(selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons->at(0).Phi(),elecActivityMethod_);

      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons->at(0).Phi());
      selectedIDIsoMuonsDeltaRJet.push_back(DeltaR_relPT.first);
      selectedIDIsoMuonsRelPTJet.push_back(DeltaR_relPT.second);

      // get Efficiencies
      muPurityCorrectionVec_ =  MuPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      muMTWEffVec_ = MuMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);      

      muIsoEffVec_ = MuIsoActivityPT_->GetEff(selectedIDIsoMuons_MT2Activity->at(0), selectedIDIsoMuons->at(0).Pt(), useAsymmErrors);
      //muRecoEffVec_ = MuRecoPTEta_->GetEff(selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), useAsymmErrors);
      muRecoEffVec_ = MuRecoActivityPT_->GetEff(selectedIDIsoMuons_MT2Activity->at(0), selectedIDIsoMuons->at(0).Pt(), useAsymmErrors);
      //muAccEffVec_ = MuAccHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      if(NJets<6.5){
        //muAccEffVec_ = MuAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      //elecAccEffVec_ = ElecAccHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      if(NJets<6.5){
         elecAccEffVec_ = ElecAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }

      //elecRecoEffVec_ = ElecRecoPTEta_->GetEff(selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), useAsymmErrors);
      elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(selectedIDIsoMuons_MT2Activity->at(0), selectedIDIsoMuons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(selectedIDIsoMuons_MT2Activity->at(0), selectedIDIsoMuons->at(0).Pt(), useAsymmErrors);
      /*
    	if(UseTagAndProbeEffIso_)muIsoEff_ = getEff(MuIsoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(),selectedIDIsoMuonsActivity[0]); 
    	if(UseTagAndProbeEffReco_)muRecoEff_ = getEff(MuRecoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(),selectedIDIsoMuonsActivity[0]); 
    	if(UseTagAndProbeEffReco_)elecRecoEff_ = getEff(ElecRecoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(),elecActivity); 
    	if(UseTagAndProbeEffIso_)elecIsoEff_ = getEff(ElecIsoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(),elecActivity); 
      */
      //for compatibility
      muPurityCorrection_ = muPurityCorrectionVec_.eff;
      muMTWEff_ = muMTWEffVec_.eff;
      muDiLepContributionMTWAppliedEff_ = muDiLepContributionMTWAppliedEffVec_.eff;
      muDiLepEffMTWAppliedEff_ = muDiLepEffMTWAppliedEffVec_.eff;
      muIsoEff_ = muIsoEffVec_.eff;
      muRecoEff_ = muRecoEffVec_.eff;
      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
      elecRecoEff_ = elecRecoEffVec_.eff;
      elecIsoEff_ = elecIsoEffVec_.eff;      

      // calculate Weights
      // muCS >99% purity
      //purityCorrectedWeight_ = Weight * muPurityCorrection_;
      purityCorrectedWeight_ = Weight;
      mtwCorrectedWeight_ = purityCorrectedWeight_ / muMTWEff_;  
      mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * muDiLepContributionMTWAppliedEff_;

      muIsoWeight_ = mtwDiLepCorrectedWeight_* (1 - muIsoEff_)/muIsoEff_; 
      muRecoWeight_ = mtwDiLepCorrectedWeight_* 1 / muIsoEff_ * (1-muRecoEff_)/muRecoEff_;    
      muAccWeight_ = mtwDiLepCorrectedWeight_* 1 / muIsoEff_ * 1 / muRecoEff_ * (1-muAccEff_)/muAccEff_;    
      muTotalWeight_ = muIsoWeight_ + muRecoWeight_ + muAccWeight_;
      totalMuons_ = mtwDiLepCorrectedWeight_ / ( muIsoEff_ * muRecoEff_ * muAccEff_);    

      elecAccWeight_ = totalMuons_ * (1 - elecAccEff_);
      elecRecoWeight_ = totalMuons_ * (elecAccEff_) * (1-elecRecoEff_);
      elecIsoWeight_ = totalMuons_ * (elecAccEff_) * (elecRecoEff_) * (1-elecIsoEff_);
      elecTotalWeight_ = elecIsoWeight_ + elecRecoWeight_ + elecAccWeight_;
      totalWeight_ = elecTotalWeight_ + muTotalWeight_;

      totalWeightDiLep_ = totalWeight_ + (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      totalWeightDiLepIsoTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);
      totalWeightDiLepIsoMuTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionMuIsoTrackEff_);
      totalWeightDiLepIsoElecTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionElecIsoTrackEff_);
      totalWeightDiLepIsoPionTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionPionIsoTrackEff_);
      totalWeightDiLepIsoTrackReducedCombined_ = totalWeightDiLep_ * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_));

      muTotalWeightDiLep_ = muTotalWeight_ + (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      muTotalWeightDiLepIsoTrackReduced_ = muTotalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);

      if(mtw<100){
        MuMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
        CombinedMeanWeight_->Fill(Bin_+0.01, 0.5*(totalWeightDiLepIsoTrackReduced_/Weight), Weight);

        if(Bin_<=72){
        	MuWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
        	CombinedWeightPerBin_[Bin_-1]->Fill(0.5*(totalWeightDiLepIsoTrackReduced_/Weight),Weight);
        }
      }

      // weights used for closure tests
      muIsoOnlyWeight_ = Weight * (1 - muIsoEff_) / muIsoEff_ * muPurityCorrection_ * muDiLepContributionMTWAppliedEff_;

      if(totalWeightDiLepIsoTrackReduced_/Weight<0.01){
        std::cout<<NJets<<"; "<<BTags<<"; "<<HT<<"; "<<MHT<<std::endl;
        std::cout<<muIsoWeight_/Weight<<"; "<<muRecoWeight_/Weight<<"; "<<muAccWeight_/Weight<<std::endl;
      }

      //std::cout << (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_ / Weight << std::endl;

      // Uncertainties
      // Total weight can be factorisated as 1*[2*(3a+3b)+4], where 1-4 are functions of
      // 1: eventweight, isotrack, MT cut, CS purity
      // 2: singleLep purity, 1/(iso(mu)*reco(mu)*acc(mu))
      // 3a: iso(mu),reco(mu),acc(mu)
      // 3a: iso(e),reco(e),acc(e)
      // 4: diLeptonic contribution: singleLep purity, diLep found

      Float_t w1 = Weight * (1 - expectationReductionIsoTrackEff_) * 1/muMTWEff_; // * muPurityCorrection_
      Float_t w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
      Float_t w3a = (1-muIsoEff_)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_);
      Float_t w3b = (1-elecIsoEff_)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_);
      Float_t w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReducedCombined_

      isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionMuIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionMuIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionElecIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionElecIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionPionIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionPionIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ + muMTWEffVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ - muMTWEffVec_.errDown) * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatUp = 0; // no purity correction for muCS (>99%)
      purityStatDown = 0; // no purity correction for muCS (>99%)

      singleLepPurityStatUp = w1 * ((muDiLepContributionMTWAppliedEff_ + muDiLepContributionMTWAppliedEffVec_.errUp) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_-muDiLepContributionMTWAppliedEffVec_.errUp) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      singleLepPurityStatDown = w1 * ((muDiLepContributionMTWAppliedEff_ - muDiLepContributionMTWAppliedEffVec_.errDown) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_+muDiLepContributionMTWAppliedEffVec_.errDown) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      diLepFoundStatDown = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errUp)/(muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
      diLepFoundStatUp =w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errDown)/(muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

      muIsoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_+muIsoEffVec_.errUp)*muRecoEff_*muAccEff_) * ((1-muIsoEff_-muIsoEffVec_.errUp)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      muIsoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_-muIsoEffVec_.errDown)*muRecoEff_*muAccEff_) * ((1-muIsoEff_+muIsoEffVec_.errDown)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      muRecoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_ + (1-muRecoEff_-muRecoEffVec_.errUp)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      muRecoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_ + (1-muRecoEff_+muRecoEffVec_.errDown)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      muAccStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_+muAccEffVec_.errUp)) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_+muAccEffVec_.errUp) + (1-muRecoEff_)*(muAccEff_+muAccEffVec_.errUp) + (1-muAccEff_-muAccEffVec_.errUp) +w3b) + w4) - wGes;
      muAccStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_-muAccEffVec_.errDown)) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_-muAccEffVec_.errDown) + (1-muRecoEff_)*(muAccEff_-muAccEffVec_.errDown) + (1-muAccEff_+muAccEffVec_.errDown) +w3b) + w4) - wGes;

      elecIsoStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_-elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      elecIsoStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_+elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      elecRecoStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecRecoEff_-elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      elecRecoStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecRecoEff_+elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      elecAccStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecRecoEff_)*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecAccEff_-elecAccEffVec_.errUp)) + w4) - wGes;
      elecAccStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecRecoEff_)*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecAccEff_+elecAccEffVec_.errDown)) + w4) - wGes;


      //cut of systematics so that efficiencies are <=1
      double isoTrackMax = expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_);
      if(isoTrackMax > 1) isoTrackMax = 1;
      isoTrackSysDown = Weight * (1 - isoTrackMax) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      double isoTrackMin = expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_);
      isoTrackSysUp  = Weight * (1 - isoTrackMin) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + 0.01 * muIsoTrackUncertaintyUp_);
      if(muIsoTrackMax > 1) muIsoTrackMax = 1;
      muIsoTrackSysDown = Weight * (1 - (muIsoTrackMax + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      double muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - 0.01 * muIsoTrackUncertaintyDown_);
      muIsoTrackSysUp  = Weight * (1 - (muIsoTrackMin + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + 0.01 * elecIsoTrackUncertaintyUp_);
      if(elecIsoTrackMax > 1) elecIsoTrackMax = 1;
      elecIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMax + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      double elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - 0.01 * elecIsoTrackUncertaintyDown_);
      elecIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMin + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + 0.01 * pionIsoTrackUncertaintyUp_);
      if(pionIsoTrackMax > 1) pionIsoTrackMax = 1;
      pionIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMax)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      double pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - 0.01 * pionIsoTrackUncertaintyDown_);
      pionIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMin)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double MTWMax = muMTWEff_ + (1-muMTWEff_) * 0.01 * MuMTWUncertaintyUp_;
      if(MTWMax > 1) MTWMax = 1;
      MTWSysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/MTWMax * (w2 * (w3a+w3b) + w4) - wGes;
      double MTWMin = muMTWEff_ - (1-muMTWEff_) * 0.01 * MuMTWUncertaintyDown_;
      MTWSysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/MTWMin * (w2 * (w3a+w3b) + w4) - wGes;

      puritySysUp = 0; // no purity correction for muCS (>99%)    
      puritySysDown = 0; // no purity correction for muCS (>99%)
      
      double singleLepPurityMax = muDiLepContributionMTWAppliedEff_ + (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityUp_;
      if(singleLepPurityMax > 1) singleLepPurityMax = 1;
      singleLepPuritySysUp = w1 * (singleLepPurityMax * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - singleLepPurityMax) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityMin = muDiLepContributionMTWAppliedEff_ - (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityDown_;
      singleLepPuritySysDown = w1 * (singleLepPurityMin * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - singleLepPurityMin) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;

      double diLepFoundMax = muDiLepEffMTWAppliedEff_ *(1 + 0.01 * MuDiLepFoundUp_);
      if(diLepFoundMax > 1) diLepFoundMax = 1;
      diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-diLepFoundMax)/diLepFoundMax) - wGes;
      double diLepFoundMin = muDiLepEffMTWAppliedEff_ *(1 - 0.01 * MuDiLepFoundDown_);
      diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-diLepFoundMin)/diLepFoundMin) - wGes;

      double muIsoMax = muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_);
      if(usePrelimSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * getMuonIsoSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons_MT2Activity->at(0)));
      if(useSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * GetSF(h_muIsoSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), true));
      if(muIsoMax > 1) muIsoMax = 1;
      muIsoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoMax*muRecoEff_*muAccEff_) * ((1-muIsoMax)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      double muIsoMin = muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_);
      if(usePrelimSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * getMuonIsoSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons_MT2Activity->at(0)));
      if(useSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * GetSF(h_muIsoSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), true));
      muIsoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoMin*muRecoEff_*muAccEff_) * ((1-muIsoMin)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;

      double muRecoMax = muRecoEff_ *(1 + 0.01 * MuRecoUncertaintyUp_);
      if(usePrelimSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * getMuonIDSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta()));
      if(useSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * GetSF(h_muIDSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), true));
      if(muRecoMax > 1) muRecoMax = 1;
      muRecoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoMax*muAccEff_) * ((1-muIsoEff_)*muRecoMax*muAccEff_ + (1-muRecoMax)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
      double muRecoMin = muRecoEff_ *(1 - 0.01 * MuRecoUncertaintyDown_);
      if(usePrelimSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * getMuonIDSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta()));
      if(useSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * GetSF(h_muIDSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), true));
      muRecoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoMin*muAccEff_) * ((1-muIsoEff_)*muRecoMin*muAccEff_ + (1-muRecoMin)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;

      double muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_LowMHT_);
      if(MHT>500) muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_HighMHT_);
      if(muAccMax > 1) muAccMax = 1;
      muAccSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccMax) * ((1-muIsoEff_)*muRecoEff_*muAccMax + (1-muRecoEff_)*muAccMax + (1-muAccMax) +w3b) + w4) - wGes;
      double muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_LowMHT_);
      if(MHT>500) muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_HighMHT_);
      muAccSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccMin) * ((1-muIsoEff_)*muRecoEff_*muAccMin + (1-muRecoEff_)*muAccMin + (1-muAccMin) +w3b) + w4) - wGes;

      double muAccQsquareMax = muAccEff_ *(1 + 0.01 * MuAccQsquareUncertaintyUp_);
      if(muAccQsquareMax > 1) muAccQsquareMax = 1;
      muAccQsquareSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccQsquareMax) * ((1-muIsoEff_)*muRecoEff_*muAccQsquareMax + (1-muRecoEff_)*muAccQsquareMax + (1-muAccQsquareMax) +w3b) + w4) - wGes;
      double muAccQsquareMin = muAccEff_ *(1 - 0.01 * MuAccQsquareUncertaintyDown_);
      muAccQsquareSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccQsquareMin) * ((1-muIsoEff_)*muRecoEff_*muAccQsquareMin + (1-muRecoEff_)*muAccQsquareMin + (1-muAccQsquareMin) +w3b) + w4) - wGes;
      
      double elecIsoMax = elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_);
      if(usePrelimSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * getElecIsoSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons_MT2Activity->at(0)));
      if(useSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * GetSF(h_elecIsoSF, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons_MT2Activity->at(0), false));
      if(elecIsoMax > 1) elecIsoMax = 1;
      elecIsoSysDown = w1 * (w2 * (w3a + (1-elecIsoMax)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      double elecIsoMin = elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_);
      if(usePrelimSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * getElecIsoSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta(), selectedIDIsoMuons_MT2Activity->at(0)));
      if(useSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * GetSF(h_elecIsoSF, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons_MT2Activity->at(0), false));
      elecIsoSysUp = w1 * (w2 * (w3a + (1-elecIsoMin)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;

      double elecRecoMax = elecRecoEff_*(1 + 0.01 * ElecRecoUncertaintyUp_);
      if(usePrelimSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * getElecIDSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta()));
      if(useSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * GetSF(h_elecIDSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), false));
      if(elecRecoMax > 1) elecRecoMax = 1;
      elecRecoSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoMax*elecAccEff_ + (1-elecRecoMax)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
      double elecRecoMin = elecRecoEff_*(1 - 0.01 * ElecRecoUncertaintyDown_);
      if(usePrelimSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * getElecIDSF(selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Eta()));
      if(useSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * GetSF(h_elecIDSF, selectedIDIsoMuons->at(0).Pt(), std::abs(selectedIDIsoMuons->at(0).Eta()), false));
      elecRecoSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoMin*elecAccEff_ + (1-elecRecoMin)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;

      double elecAccMax = elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_LowMHT_);
      if(MHT>500) elecAccMax = elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_HighMHT_);
      if(elecAccMax > 1) elecAccMax = 1;
      elecAccSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*elecAccMax + (1-elecRecoEff_)*elecAccMax + (1-elecAccMax)) + w4) - wGes;
      double elecAccMin = elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_LowMHT_);
      if(MHT>500) elecAccMin = elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_HighMHT_);
      elecAccSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*elecAccMin + (1-elecRecoEff_)*elecAccMin + (1-elecAccMin)) + w4) - wGes;

      double elecAccQsquareMax = elecAccEff_*(1 + 0.01 * ElecAccQsquareUncertaintyUp_);
      if(elecAccQsquareMax > 1) elecAccQsquareMax = 1;
      elecAccQsquareSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*elecAccQsquareMax + (1-elecRecoEff_)*elecAccQsquareMax + (1-elecAccQsquareMax)) + w4) - wGes;
      double elecAccQsquareMin = elecAccEff_*(1 - 0.01 * ElecAccQsquareUncertaintyDown_);
      elecAccQsquareSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*elecAccQsquareMin + (1-elecRecoEff_)*elecAccQsquareMin + (1-elecAccQsquareMin)) + w4) - wGes;


      totalStatUp = sqrt(muIsoTrackStatUp*muIsoTrackStatUp+elecIsoTrackStatUp*elecIsoTrackStatUp+pionIsoTrackStatUp*pionIsoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
      totalSysUp = sqrt(muIsoTrackSysUp*muIsoTrackSysUp+elecIsoTrackSysUp*elecIsoTrackSysUp+pionIsoTrackSysUp*pionIsoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp);
      totalUncUp = sqrt(totalStatUp*totalStatUp+totalSysUp*totalSysUp);

      totalStatDown = -sqrt(muIsoTrackStatDown*muIsoTrackStatDown+elecIsoTrackStatDown*elecIsoTrackStatDown+pionIsoTrackStatDown*pionIsoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);
      totalSysDown = -sqrt(muIsoTrackSysDown*muIsoTrackSysDown+elecIsoTrackSysDown*elecIsoTrackSysDown+pionIsoTrackSysDown*pionIsoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown);
      totalUncDown = -sqrt(totalStatDown*totalStatDown+totalSysDown*totalSysDown);
      // cout <<"DONE"<<endl;
    } 
  else if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1)
    {
      // cout << "Single electron event...";
      // cout << "get MTW...";
      mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet);
      ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet);
      //selectedIDIsoElectronsActivity.push_back(ElecActivity(selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons->at(0).Phi(),elecActivityMethod_));
      //double muActivity = MuActivity(selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons->at(0).Phi(),elecActivityMethod_);

      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons->at(0).Phi());
      selectedIDIsoElectronsDeltaRJet.push_back(DeltaR_relPT.first);
      selectedIDIsoElectronsRelPTJet.push_back(DeltaR_relPT.second);

      // get Efficiencies
      elecPurityCorrectionVec_ =  ElecPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      elecMTWEffVec_ = ElecMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);

      // cout << "get isolation efficiency...";
      //elecRecoEffVec_ = ElecRecoPTEta_->GetEff(selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), useAsymmErrors);
      elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(selectedIDIsoElectrons_MT2Activity->at(0), selectedIDIsoElectrons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(selectedIDIsoElectrons_MT2Activity->at(0), selectedIDIsoElectrons->at(0).Pt(), useAsymmErrors);

      //elecAccEffVec_ = ElecAccHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      if(NJets<6.5){
        // elecAccEffVec_ = ElecAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
      }

      // cout << "get acceptance efficiency...";
      //muAccEffVec_ = MuAccHTNJets_->GetEff(HT, NJets, useAsymmErrors);
      if(NJets<6.5){
        //muAccEffVec_ = MuAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
      }

      muIsoEffVec_ = MuIsoActivityPT_->GetEff(selectedIDIsoElectrons_MT2Activity->at(0), selectedIDIsoElectrons->at(0).Pt(), useAsymmErrors);
      //muRecoEffVec_ = MuRecoPTEta_->GetEff(selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), useAsymmErrors);
      muRecoEffVec_ = MuRecoActivityPT_->GetEff(selectedIDIsoElectrons_MT2Activity->at(0), selectedIDIsoElectrons->at(0).Pt(), useAsymmErrors);
      
      /*
    	if(UseTagAndProbeEffIso_) elecIsoEff_ = getEff(ElecIsoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoElectronsActivity[0]); 
    	if(UseTagAndProbeEffReco_)elecRecoEff_ = getEff(ElecRecoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoElectronsActivity[0]); 
    	if(UseTagAndProbeEffReco_) muRecoEff_ = getEff(MuRecoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(), muActivity); 
    	if(UseTagAndProbeEffIso_) muIsoEff_ = getEff(MuIsoPTActivityTAPMC_, selectedIDIsoMuons->at(0).Pt(), muActivity); 
      */    
      //for compatibility
      elecPurityCorrection_ = elecPurityCorrectionVec_.eff;
      elecMTWEff_ = elecMTWEffVec_.eff;
      elecDiLepContributionMTWAppliedEff_ = elecDiLepContributionMTWAppliedEffVec_.eff;
      elecDiLepEffMTWAppliedEff_ = elecDiLepEffMTWAppliedEffVec_.eff;
      elecIsoEff_ = elecIsoEffVec_.eff;
      elecRecoEff_ = elecRecoEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
      muAccEff_ = muAccEffVec_.eff;
      muRecoEff_ = muRecoEffVec_.eff;
      muIsoEff_ = muIsoEffVec_.eff;

      // calculate Weights
      // cout << "calculate weights...";
      purityCorrectedWeight_ = Weight * elecPurityCorrection_;
      mtwCorrectedWeight_ =  purityCorrectedWeight_ / elecMTWEff_;    
      mtwDiLepCorrectedWeight_ = mtwCorrectedWeight_ * elecDiLepContributionMTWAppliedEff_;

      elecIsoWeight_= mtwDiLepCorrectedWeight_ * (1 - elecIsoEff_)/elecIsoEff_;
      elecRecoWeight_ = mtwDiLepCorrectedWeight_* 1 / elecIsoEff_ * (1-elecRecoEff_)/elecRecoEff_;
      elecAccWeight_ = mtwDiLepCorrectedWeight_* 1 / elecIsoEff_ * 1 / elecRecoEff_ * (1-elecAccEff_)/elecAccEff_;
      elecTotalWeight_ = elecIsoWeight_ + elecRecoWeight_ + elecAccWeight_;
      totalElectrons_ = mtwDiLepCorrectedWeight_ / ( elecIsoEff_ * elecRecoEff_ * elecAccEff_);

      muAccWeight_ = totalElectrons_ * (1-muAccEff_);
      muRecoWeight_ = totalElectrons_ * (muAccEff_) * (1-muRecoEff_);
      muIsoWeight_ = totalElectrons_ * (muAccEff_) * (muRecoEff_) * (1-muIsoEff_);
      muTotalWeight_ = muIsoWeight_ + muRecoWeight_ + muAccWeight_;
      totalWeight_ = elecTotalWeight_ + muTotalWeight_;
    
      totalWeightDiLep_ = totalWeight_ + (1-elecDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      totalWeightDiLepIsoTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);
      totalWeightDiLepIsoMuTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionMuIsoTrackEff_);
      totalWeightDiLepIsoElecTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionElecIsoTrackEff_);
      totalWeightDiLepIsoPionTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionPionIsoTrackEff_);
      totalWeightDiLepIsoTrackReducedCombined_ = totalWeightDiLep_ * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_));

      elecTotalWeightDiLep_ = elecTotalWeight_ + (1-elecDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      elecTotalWeightDiLepIsoTrackReduced_ = elecTotalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);

      if(mtw<100){
        ElecMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
        CombinedMeanWeight_->Fill(Bin_+0.01, 0.5*(totalWeightDiLepIsoTrackReduced_/Weight), Weight);

        if(Bin_<=72){
        	ElecWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
        	CombinedWeightPerBin_[Bin_-1]->Fill(0.5*(totalWeightDiLepIsoTrackReduced_/Weight),Weight);
        }
      }

      // weights used for closure tests
      elecIsoOnlyWeight_ = Weight * (1 - elecIsoEff_) / elecIsoEff_ * elecPurityCorrection_ * elecDiLepContributionMTWAppliedEff_;  
      

      // Uncertainties
      // For explanation see muons
      Float_t w1 = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * elecPurityCorrection_;
      Float_t w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
      Float_t w3a = (1-elecIsoEff_)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_);
      Float_t w3b = (1-muIsoEff_)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_);
      Float_t w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReducedCombined_

      isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionMuIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionMuIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionElecIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionElecIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionPionIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionPionIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ + elecMTWEffVec_.errUp) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ - elecMTWEffVec_.errDown) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ + elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ - elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;

      singleLepPurityStatUp = w1 * ((elecDiLepContributionMTWAppliedEff_ + elecDiLepContributionMTWAppliedEffVec_.errUp) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_-elecDiLepContributionMTWAppliedEffVec_.errUp) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      singleLepPurityStatDown = w1 * ((elecDiLepContributionMTWAppliedEff_ - elecDiLepContributionMTWAppliedEffVec_.errDown) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_+elecDiLepContributionMTWAppliedEffVec_.errDown) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      diLepFoundStatDown = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errUp)/(elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
      diLepFoundStatUp =w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errDown)/(elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

      elecIsoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_+elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_-elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      elecIsoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_-elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_+elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      elecRecoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecRecoEff_-elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      elecRecoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecRecoEff_+elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      elecAccStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp)) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecRecoEff_)*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecAccEff_-elecAccEffVec_.errUp) +w3b) + w4) - wGes;
      elecAccStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown)) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecRecoEff_)*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecAccEff_+elecAccEffVec_.errDown) +w3b) + w4) - wGes;

      muIsoStatDown = w1 * (w2 * (w3a + (1-muIsoEff_-muIsoEffVec_.errUp)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      muIsoStatUp = w1 * (w2 * (w3a + (1-muIsoEff_+muIsoEffVec_.errDown)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      muRecoStatDown = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_ + (1-muRecoEff_-muRecoEffVec_.errUp)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      muRecoStatUp = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_ + (1-muRecoEff_+muRecoEffVec_.errDown)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      muAccStatDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_+muAccEffVec_.errUp) + (1-muRecoEff_)*(muAccEff_+muAccEffVec_.errUp) + (1-muAccEff_-muAccEffVec_.errUp)) + w4) - wGes;
      muAccStatUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_-muAccEffVec_.errDown) + (1-muRecoEff_)*(muAccEff_-muAccEffVec_.errDown) + (1-muAccEff_+muAccEffVec_.errDown)) + w4) - wGes;


      //cut of systematics so that efficiencies are <=1
      double isoTrackMax = expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_);
      if(isoTrackMax > 1) isoTrackMax = 1;
      isoTrackSysDown = Weight * (1 - isoTrackMax) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double isoTrackMin = expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_);
      isoTrackSysUp  = Weight * (1 - isoTrackMin) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + 0.01 * muIsoTrackUncertaintyUp_);
      if(muIsoTrackMax > 1) muIsoTrackMax = 1;
      muIsoTrackSysDown = Weight * (1 - (muIsoTrackMax + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - 0.01 * muIsoTrackUncertaintyDown_);
      muIsoTrackSysUp  = Weight * (1 - (muIsoTrackMin + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + 0.01 * elecIsoTrackUncertaintyUp_);
      if(elecIsoTrackMax > 1) elecIsoTrackMax = 1;
      elecIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMax + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - 0.01 * elecIsoTrackUncertaintyDown_);
      elecIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMin + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + 0.01 * pionIsoTrackUncertaintyUp_);
      if(pionIsoTrackMax > 1) pionIsoTrackMax = 1;
      pionIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMax)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - 0.01 * pionIsoTrackUncertaintyDown_);
      pionIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMin)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
 
      double MTWMax = elecMTWEff_ + (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyUp_;
      if(MTWMax > 1) MTWMax = 1;
      MTWSysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/MTWMax * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double MTWMin = elecMTWEff_ - (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyDown_;
      MTWSysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/MTWMin * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double purityMax = elecPurityCorrection_ + (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyUp_;
      if(purityMax > 1) purityMax = 1;
      puritySysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * purityMax * (w2 * (w3a+w3b) + w4) - wGes;
      double purityMin = elecPurityCorrection_ - (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyDown_;
      puritySysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * purityMin * (w2 * (w3a+w3b) + w4) - wGes;

      double singleLepPurityMax = elecDiLepContributionMTWAppliedEff_ + (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityUp_;
      if(singleLepPurityMax > 1) singleLepPurityMax = 1;
      singleLepPuritySysUp = w1 * (singleLepPurityMax * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - singleLepPurityMax) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityMin = elecDiLepContributionMTWAppliedEff_ - (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityDown_;
      singleLepPuritySysDown = w1 * (singleLepPurityMin * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - singleLepPurityMin) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;

      double diLepFoundMax = elecDiLepEffMTWAppliedEff_ *(1 + 0.01 * ElecDiLepFoundUp_);
      if(diLepFoundMax > 1) diLepFoundMax = 1;
      diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-diLepFoundMax)/diLepFoundMax) - wGes;
      double diLepFoundMin = elecDiLepEffMTWAppliedEff_ *(1 - 0.01 * ElecDiLepFoundDown_);
      diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-diLepFoundMin)/diLepFoundMin) - wGes;

      double elecIsoMax = elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_);
      if(usePrelimSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * getElecIsoSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons_MT2Activity->at(0)));
      if(useSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * GetSF(h_elecIsoSF, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons_MT2Activity->at(0), false));
      if(elecIsoMax > 1) elecIsoMax = 1;
      elecIsoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoMax*elecRecoEff_*elecAccEff_) * ((1-elecIsoMax)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      double elecIsoMin = elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_);
      if(usePrelimSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * getElecIsoSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons_MT2Activity->at(0)));
      if(useSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * GetSF(h_elecIsoSF, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons_MT2Activity->at(0), false));
      elecIsoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoMin*elecRecoEff_*elecAccEff_) * ((1-elecIsoMin)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;

      double elecRecoMax = elecRecoEff_ *(1 + 0.01 * ElecRecoUncertaintyUp_);
      if(usePrelimSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * getElecIDSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta()));
      if(useSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * GetSF(h_elecIDSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), false));
      if(elecRecoMax > 1) elecRecoMax = 1;
      elecRecoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoMax*elecAccEff_) * ((1-elecIsoEff_)*elecRecoMax*elecAccEff_ + (1-elecRecoMax)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
      double elecRecoMin = elecRecoEff_ *(1 - 0.01 * ElecRecoUncertaintyDown_);
      if(usePrelimSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * getElecIDSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta()));
      if(useSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * GetSF(h_elecIDSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), false));
      elecRecoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoMin*elecAccEff_) * ((1-elecIsoEff_)*elecRecoMin*elecAccEff_ + (1-elecRecoMin)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;

      double elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_LowMHT_);
      if(MHT>500) elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_HighMHT_);
      if(elecAccMax > 1) elecAccMax = 1;
      elecAccSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccMax) * ((1-elecIsoEff_)*elecRecoEff_*elecAccMax + (1-elecRecoEff_)*elecAccMax + (1-elecAccMax) +w3b) + w4) - wGes;
      double elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_LowMHT_);
      if(MHT>500) elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_HighMHT_);
      elecAccSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccMin) * ((1-elecIsoEff_)*elecRecoEff_*elecAccMin + (1-elecRecoEff_)*elecAccMin + (1-elecAccMin) +w3b) + w4) - wGes;
      
      double elecAccQsquareMax = elecAccEff_ *(1 + 0.01 * ElecAccQsquareUncertaintyUp_);
      if(elecAccQsquareMax > 1) elecAccQsquareMax = 1;
      elecAccQsquareSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccQsquareMax) * ((1-elecIsoEff_)*elecRecoEff_*elecAccQsquareMax + (1-elecRecoEff_)*elecAccQsquareMax + (1-elecAccQsquareMax) +w3b) + w4) - wGes;
      double elecAccQsquareMin = elecAccEff_ *(1 - 0.01 * ElecAccQsquareUncertaintyDown_);
      elecAccQsquareSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccQsquareMin) * ((1-elecIsoEff_)*elecRecoEff_*elecAccQsquareMin + (1-elecRecoEff_)*elecAccQsquareMin + (1-elecAccQsquareMin) +w3b) + w4) - wGes;
      
      double muIsoMax = muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_);
      if(usePrelimSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * getMuonIsoSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons_MT2Activity->at(0)));
      if(useSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * GetSF(h_muIsoSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), true));
      if(muIsoMax > 1) muIsoMax = 1;
      muIsoSysDown = w1 * (w2 * (w3a + (1-muIsoMax)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      double muIsoMin = muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_);
      if(usePrelimSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * getMuonIsoSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta(), selectedIDIsoElectrons_MT2Activity->at(0)));
      if(useSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * GetSF(h_muIsoSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), true));
      muIsoSysUp = w1 * (w2 * (w3a + (1-muIsoMin)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;

      double muRecoMax = muRecoEff_*(1 + 0.01 * MuRecoUncertaintyUp_);
      if(usePrelimSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * getMuonIDSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta()));
      if(useSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * GetSF(h_muIDSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), true));
      if(muRecoMax > 1) muRecoMax = 1;
      muRecoSysDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoMax*muAccEff_ + (1-muRecoMax)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
      double muRecoMin = muRecoEff_*(1 - 0.01 * MuRecoUncertaintyDown_);
      if(usePrelimSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * getMuonIDSF(selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Eta()));
      if(useSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * GetSF(h_muIDSF, selectedIDIsoElectrons->at(0).Pt(), std::abs(selectedIDIsoElectrons->at(0).Eta()), true));
      muRecoSysUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoMin*muAccEff_ + (1-muRecoMin)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;

      double muAccMax = muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_LowMHT_);
      if(MHT>500) muAccMax = muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_HighMHT_);
      if(muAccMax > 1) muAccMax = 1;
      muAccSysDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*muAccMax + (1-muRecoEff_)*muAccMax + (1-muAccMax)) + w4) - wGes;
      double muAccMin = muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_LowMHT_);
      if(MHT>500) muAccMin = muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_HighMHT_);
      muAccSysUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*muAccMin + (1-muRecoEff_)*muAccMin + (1-muAccMin)) + w4) - wGes;

      double muAccQsquareMax = muAccEff_*(1 + 0.01 * MuAccQsquareUncertaintyUp_);
      if(muAccQsquareMax > 1) muAccQsquareMax = 1;
      muAccQsquareSysDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*muAccQsquareMax + (1-muRecoEff_)*muAccQsquareMax + (1-muAccQsquareMax)) + w4) - wGes;
      double muAccQsquareMin = muAccEff_*(1 - 0.01 * MuAccQsquareUncertaintyDown_);
      muAccQsquareSysUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*muAccQsquareMin + (1-muRecoEff_)*muAccQsquareMin + (1-muAccQsquareMin)) + w4) - wGes;
      
      totalStatUp = sqrt(muIsoTrackStatUp*muIsoTrackStatUp+elecIsoTrackStatUp*elecIsoTrackStatUp+pionIsoTrackStatUp*pionIsoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
      totalSysUp = sqrt(muIsoTrackSysUp*muIsoTrackSysUp+elecIsoTrackSysUp*elecIsoTrackSysUp+pionIsoTrackSysUp*pionIsoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp);
      totalUncUp = sqrt(totalStatUp*totalStatUp+totalSysUp*totalSysUp);

      totalStatDown = -sqrt(muIsoTrackStatDown*muIsoTrackStatDown+elecIsoTrackStatDown*elecIsoTrackStatDown+pionIsoTrackStatDown*pionIsoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);
      totalSysDown = -sqrt(muIsoTrackSysDown*muIsoTrackSysDown+elecIsoTrackSysDown*elecIsoTrackSysDown+pionIsoTrackSysDown*pionIsoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown);
      totalUncDown = -sqrt(totalStatDown*totalStatDown+totalSysDown*totalSysDown);
      // cout << "DONE" << endl;
    }

  tPrediction_->Fill();
  return kTRUE;
}

void Prediction::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  std::cout<<"--- QCD binning ---"<<std::endl;
  SearchBinsQCD_->PrintUsed();
  std::cout<<"--- Search bins ---"<<std::endl;
  SearchBins_->PrintUsed();
  
}

void Prediction::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.


  tPrediction_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonPrediction"));
  TFile *outPutFile = new TFile(fileName,"RECREATE"); ;
  outPutFile->cd();
  tPrediction_->Write();

  outPutFile->cd();
  outPutFile->mkdir("MeanWeight");
  TDirectory *dEfficiencies = (TDirectory*)outPutFile->Get("MeanWeight");
  dEfficiencies->cd();
  MuMeanWeight_->Write();
  ElecMeanWeight_->Write();
  CombinedMeanWeight_->Write();

  outPutFile->cd();
  outPutFile->mkdir("WeightPerBin");
  TDirectory *dEfficienciesPerBin = (TDirectory*)outPutFile->Get("WeightPerBin");
  dEfficienciesPerBin->cd();
  for(int b = 0; b <72; b++){
    MuWeightPerBin_[b]->Write();
    ElecWeightPerBin_[b]->Write();
    CombinedWeightPerBin_[b]->Write();
  }

  outPutFile->Close();

  cout << "Saved output to " << fileName << endl;
  
}
void Prediction::resetValues()
{
  mtw=0.;
  muMTWEff_=0.;
  mtwCorrectedWeight_=0.;
  muDiLepContributionMTWAppliedEff_=0.;
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
  muDiLepEffMTWAppliedEff_=0.;
  elecDiLepEffMTWAppliedEff_=0.;
  totalWeightDiLep_=0.;
  totalWeightDiLepIsoTrackReduced_=0.;
  muIsoOnlyWeight_=0.;
  elecIsoOnlyWeight_=0.;
  // isolated track prediction
  IsolatedTracksMuMatched_=false;
  IsolatedTracksElecMatched_=false;
  //selectedIDIsoMuonsActivity.clear(); 
  //selectedIDIsoElectronsActivity.clear(); 
  selectedIDIsoMuonsDeltaRJet.clear();
  selectedIDIsoMuonsRelPTJet.clear(); 
  selectedIDIsoElectronsDeltaRJet.clear();
  selectedIDIsoElectronsRelPTJet.clear();
  IsolatedMuonTracksVetoActivity.clear();
  IsolatedMuonTracksVetoMTW.clear();
  IsolatedElectronTracksVetoActivity.clear();
  IsolatedElectronTracksVetoMTW.clear();
  IsolatedPionTracksVetoActivity.clear();
  IsolatedPionTracksVetoMTW.clear();
}

bool Prediction::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    if(!CSCTightHaloFilter) result=false;
    if(eeBadScFilter!=1) result=false;
    if(!eeBadSc4Filter) result=false;
    if(!HBHENoiseFilter) result=false;
    if(!HBHEIsoNoiseFilter) result=false;
  }
  if(NVtx<=0) result=false;
  if(JetID!=1) result=false;
  return result;
}

double Prediction::getEff(TH2F* effTH2F, double xValue, double yValue)
{
  double result = 0;
  if(xValue < effTH2F->GetXaxis()->GetXmin() )
    {
      //              std::cout<<"Warning xValue: "<<xValue<<" is smaller than minimum of histo: "<<effTH2F->GetName()<<std::endl;
      xValue= effTH2F->GetXaxis()->GetXmin()+0.01;
    }
  else if(xValue > effTH2F->GetXaxis()->GetXmax() )
    {
      //        std::cout<<"Warning xValue: "<<xValue<<" is bigger than maximum of histo: "<<effTH2F->GetName()<<" which is: "<<effTH2F->GetXaxis()->GetXmax();
      xValue= effTH2F->GetXaxis()->GetXmax()-0.01;
      //              std::cout<<" Setting xValue to: "<<xValue<<std::endl;
      if(xValue > effTH2F->GetXaxis()->GetXmax() )std::cout<<"Problem persists!!!!!!!!!"<<std::endl;
    }
  
  if(yValue < effTH2F->GetYaxis()->GetXmin() )
    {
      //              std::cout<<"Warning yValue: "<<yValue<<" is smaller than minimum of histo: "<<effTH2F->GetName()<<std::endl;
      yValue= effTH2F->GetYaxis()->GetXmin()+0.01;
    }
  else if(yValue > effTH2F->GetYaxis()->GetXmax() )
    {
      //              std::cout<<"Warning yValue: "<<yValue<<" is bigger than maximum of histo: "<<effTH2F->GetName()<<std::endl;
      yValue= effTH2F->GetYaxis()->GetXmax()-0.01;
    }
  result = effTH2F->GetBinContent(effTH2F->GetXaxis()->FindBin(xValue),effTH2F->GetYaxis()->FindBin(yValue));
  if(result<0.01)
    {
      std::cout<<"Warning efficiency is: "<<result<<" is smaller than 0.01 for histo: "<<effTH2F->GetName()<<std::endl;
      result =0.01;
    }
  if(result>1)
    {
      std::cout<<"Warning efficiency is: "<<result<<" is bigger than 1 for histo: "<<effTH2F->GetName()<<std::endl;
      result =0.99;
    }
  return result;
}
double Prediction::getEff(TH1F* effTH1F, double xValue)
{
  double result = 0;
  if(xValue < effTH1F->GetXaxis()->GetXmin() )
    {
      std::cout<<"Warning xValue: "<<xValue<<" is smaller than minimum of histo: "<<effTH1F->GetName()<<std::endl;
      xValue= effTH1F->GetXaxis()->GetXmin()+0.01;
    }
  else if(xValue > effTH1F->GetXaxis()->GetXmax() )
    {
      std::cout<<"Warning xValue: "<<xValue<<" is bigger than maximum of histo: "<<effTH1F->GetName()<<" which is: "<<effTH1F->GetXaxis()->GetXmax();
      xValue= effTH1F->GetXaxis()->GetXmax()-0.01;
      std::cout<<" Setting xValue to: "<<xValue<<std::endl;
      if(xValue > effTH1F->GetXaxis()->GetXmax() )std::cout<<"Problem persists!!!!!!!!!"<<std::endl;
    }
  
  
  result = effTH1F->GetBinContent(effTH1F->GetXaxis()->FindBin(xValue));
  if(result<0.01)
    {
      std::cout<<"Warning efficiency is: "<<result<<" is smaller than 1% for histo: "<<effTH1F->GetName()<<std::endl;
      result =0.01;
    }
  if(result>1)
    {
      std::cout<<"Warning efficiency is: "<<result<<" is bigger than 1 for histo: "<<effTH1F->GetName()<<std::endl;
      result =0.99;
    }
  return result;
}

double Prediction::MuActivity( double muEta, double muPhi, unsigned int method)
{
  double result =0;
  if(method==0)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(muEta,muPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRMuActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_chargedEmEnergyFraction->at(i) + Jets_chargedHadronEnergyFraction->at(i));
	}
    }
  if(method==1)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(muEta,muPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRMuActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_chargedEmEnergyFraction->at(i) + Jets_chargedHadronEnergyFraction->at(i))*(1/(deltaR(muEta,muPhi,Jets->at(i).Eta(),Jets->at(i).Phi())+0.5));
	}
    }
  // if(method==2)
  //   {
  //     for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 	  if(deltaR(muEta,muPhi,SelectedPFCandidatesEta->at(i),SelectedPFCandidatesPhi->at(i))>maxDeltaRElecActivity_ ) continue;
  // 	  result+=SelectedPFCandidatesPt->at(i);
  // 	}
  //   }
  // if(method==3)
  //   {
  //     for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 	  if(SelectedPFCandidates_Charge->at(i)!=0) continue;
  // 	  if(deltaR(muEta,muPhi,SelectedPFCandidatesEta->at(i),SelectedPFCandidatesPhi->at(i))>maxDeltaRElecActivity_ ) continue;
  // 	  result+=SelectedPFCandidatesPt->at(i);
  // 	}
  //   }
  return result;
  
}
double Prediction::ElecActivity( double elecEta, double elecPhi, unsigned int method)
{
  double result =0;
  if(method==0)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(elecEta,elecPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_chargedHadronEnergyFraction->at(i));
	  //                      result+=Jets->at(i).Pt() * (Jets_chargedEmEnergyFraction->at(i) + Jets_chargedHadronEnergyFraction->at(i));
	}
    }
  if(method==1)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(elecEta,elecPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_chargedHadronEnergyFraction->at(i))*(1/(deltaR(elecEta,elecPhi,Jets->at(i).Eta(),Jets->at(i).Phi())+0.5));
	}
    }
  // if(method==2)
  //   {
  //     for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 	  if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta->at(i),SelectedPFCandidatesPhi->at(i))>maxDeltaRElecActivity_ ) continue;
  // 	  result+=SelectedPFCandidatesPt->at(i);
  // 	}
  //   }
  // if(method==3)
  //   {
  //     for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 	  if(SelectedPFCandidates_Charge->at(i)!=0) continue;
  // 	  if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta->at(i),SelectedPFCandidatesPhi->at(i))>maxDeltaRElecActivity_ ) continue;
  // 	  result+=SelectedPFCandidatesPt->at(i);
  // 	}
  //   }
  return result;
  
}
double Prediction::IsoTrackActivityCalc( double isoTrackEta, double isoTrackPhi, unsigned int method)
{
  double result =0;
  if(method==0)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(isoTrackEta,isoTrackPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_neutralEmEnergyFraction->at(i) + Jets_photonEnergyFraction->at(i));
	}
    }
  if(method==1)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(isoTrackEta,isoTrackPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_neutralEmEnergyFraction->at(i) + Jets_photonEnergyFraction->at(i))*(1/(deltaR(isoTrackEta,isoTrackPhi,Jets->at(i).Eta(),Jets->at(i).Phi())+0.5));
	}
    }
  // if(method==2)
  //   {
  //     for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 	  if(deltaR(isoTrackEta,isoTrackPhi,SelectedPFCandidatesEta->at(i),SelectedPFCandidatesPhi->at(i))>maxDeltaRElecActivity_ ) continue;
  // 	  result+=SelectedPFCandidatesPt->at(i);
  // 	}
  //   }
  return result;
  
}

std::pair <double,double> Prediction::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
  double relPt = 9999;
  double deltaRmin = 9999;

  for (unsigned int i=0; i < JetsNum_ ; i++)
    {
      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) > deltaRmin) continue;

      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) < jetCone_)
	{
	  if(lepPt > Jets->at(i).Pt()){
	    if(lepPt < 1.2 * Jets->at(i).Pt()) continue;
	    else{
	      relPt = lepPt / Jets->at(i).Pt();
	      deltaRmin = deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi());
	      continue;
	    }
	  }
	  if((Jets->at(i).Pt() - lepPt) < jetMinPt_) continue;
	  else{
	    relPt = lepPt / (Jets->at(i).Pt() - lepPt);
	    deltaRmin = deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi());
	    continue;
	  }      
	}

      relPt = lepPt / Jets->at(i).Pt();
      deltaRmin = deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi());
    }

  return std::make_pair(deltaRmin, relPt);
}
