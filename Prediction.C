#define Prediction_cxx
// The class definition in Prediction.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("Prediction.C")
// Root > T->Process("Prediction.C","some options")
// Root > T->Process("Prediction.C+")
//

#include "Prediction.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>


void Prediction::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
  
  
}

void Prediction::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TFile *effInput = new TFile("Efficiencies.root","UPDATE");
  TDirectory *EffInputFolder =   (TDirectory*)effInput->Get("Efficiencies");

  if(UseTagAndProbeEffIso_)
  {
    TDirectory *EffTagAndProbeInputFolder =   (TDirectory*)effInput->Get("TagAndProbe");
    MuIsoPTActivityTAPMC_ = (TH2F*)EffTagAndProbeInputFolder->Get("MuIsoTagAndProbeMC");    
    ElecIsoPTActivityTAPMC_ = (TH2F*)EffTagAndProbeInputFolder->Get("ElecIsoTagAndProbeMC");
    
  }
  if(UseTagAndProbeEffReco_)
  {
    TDirectory *EffTagAndProbeInputFolder =   (TDirectory*)effInput->Get("TagAndProbe");
    MuRecoPTActivityTAPMC_ = (TH2F*)EffTagAndProbeInputFolder->Get("MuRecoTagAndProbeMC");
    ElecRecoPTActivityTAPMC_ = (TH2F*)EffTagAndProbeInputFolder->Get("ElecRecoTagAndProbeMC");    
  }

  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity", EffInputFolder);
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D", EffInputFolder);
  MuDiLepContributionMTWAppliedNJets_ = new TH1Eff("MuDiLepContributionMTWNJets1D", EffInputFolder);
  MuDiLepEffMTWAppliedNJets_ = new TH1Eff("MuDiLepMTWNJets1D", EffInputFolder);

  MuIsoPTActivity_ = new TH2Eff("MuIsoPTActivity", EffInputFolder);
  MuIsoRelPTDeltaRJet_ = new TH2Eff("MuIsoRelPTDeltaRJet", EffInputFolder);
  MuRecoPTActivity_= new TH2Eff("MuRecoPTActivity", EffInputFolder);
  MuPurityMHTNJets_ = new TH2Eff("MuonPurityMHTNJet", EffInputFolder); 

  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets", EffInputFolder);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets", EffInputFolder);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT", EffInputFolder);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets", EffInputFolder);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0", EffInputFolder);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf", EffInputFolder);
  MuAccHTMHT_NJetsLow_ = new TH2Eff("MuAccHTMHT_NJetsLow", EffInputFolder);
  MuAccHTMHT_NJetsHigh_ = new TH2Eff("MuAccHTMHT_NJetsHigh", EffInputFolder);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0", EffInputFolder);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf", EffInputFolder); 


  ElecIsoPTActivity_ = new TH2Eff("ElecIsoPTActivity", EffInputFolder);
  ElecIsoRelPTDeltaRJet_ = new TH2Eff("ElecIsoRelPTDeltaRJet", EffInputFolder);
  ElecRecoPTActivity_= new TH2Eff("ElecRecoPTActivity", EffInputFolder);
  
  ElecPurityMHTNJets_ = new TH2Eff("ElecPurityMHTNJet", EffInputFolder);
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D", EffInputFolder);
  ElecDiLepContributionMTWAppliedNJets_ = new TH1Eff("ElecDiLepContributionMTWNJets1D", EffInputFolder);
  ElecDiLepEffMTWAppliedNJets_ = new TH1Eff("ElecDiLepMTWNJets1D", EffInputFolder);  

  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets", EffInputFolder);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets", EffInputFolder);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT", EffInputFolder);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets", EffInputFolder);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0", EffInputFolder);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf", EffInputFolder);
  ElecAccHTMHT_NJetsLow_ = new TH2Eff("ElecAccHTMHT_NJetsLow", EffInputFolder);
  ElecAccHTMHT_NJetsHigh_ = new TH2Eff("ElecAccHTMHT_NJetsHigh", EffInputFolder);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0", EffInputFolder);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf", EffInputFolder);
  
  
  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff", EffInputFolder);
  ExpectationReductionIsoTrackBTagsNJetsEff_= new TH2Eff("IsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionMuIsoTrackBTagsNJetsEff_= new TH2Eff("MuIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionElecIsoTrackBTagsNJetsEff_= new TH2Eff("ElecIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionPionIsoTrackBTagsNJetsEff_= new TH2Eff("PionIsoTrackReductionBTagNJets", EffInputFolder);


  // TProfiles
  MuMeanWeight_ = new TProfile("MuMeanWeight","MuMeanWeight",300,0.,300.);
  MuMeanWeight_->Sumw2();
  ElecMeanWeight_ = new TProfile("ElecMeanWeight","ElecMeanWeight",300,0.,300.);
  ElecMeanWeight_->Sumw2();
  CombinedMeanWeight_ = new TProfile("CombinedMeanWeight","CombinedMeanWeight",300,0.,300.);
  CombinedMeanWeight_->Sumw2();

  for(int b = 0; b <300; b++){
    MuWeightPerBin_[b] = new TH1D(TString("MuWeightPerBin_")+TString(to_string(b+1)),TString("MuWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    MuWeightPerBin_[b]->Sumw2();
    ElecWeightPerBin_[b] = new TH1D(TString("ElecWeightPerBin_")+TString(to_string(b+1)),TString("ElecWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    ElecWeightPerBin_[b]->Sumw2();
    CombinedWeightPerBin_[b] = new TH1D(TString("CombinedWeightPerBin_")+TString(to_string(b+1)),TString("CombinedWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    CombinedWeightPerBin_[b]->Sumw2();
  }  
    
  
  TString option = GetOption();
  tPrediction_ = new TTree("LostLeptonPrediction","a simple Tree with simple variables");
  tPrediction_->Branch("HT",&HT,"HT/F");
  tPrediction_->Branch("MHT",&MHT,"MHT/F");
  tPrediction_->Branch("NJets",&NJets,"NJets/s");
  tPrediction_->Branch("BTags",&BTags,"BTags/s");
  tPrediction_->Branch("NVtx",&NVtx,"NVtx/s");
  tPrediction_->Branch("Bin",&Bin_,"Bin/s");
  tPrediction_->Branch("BinQCD",&BinQCD_,"BinQCD/s");
  tPrediction_->Branch("isoTracks",&isoTracks,"isoTracks/s");
  tPrediction_->Branch("Leptons",&Leptons,"Leptons/s");
  tPrediction_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
  tPrediction_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
  tPrediction_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
  tPrediction_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
  tPrediction_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
  tPrediction_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
  tPrediction_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
  tPrediction_->Branch("Weight", &Weight, "Weight/F");
  tPrediction_->Branch("MET",&METPt,"MET/F");
  tPrediction_->Branch("METPhi",&METPhi,"METPhi/F");
  tPrediction_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum,"selectedIDIsoMuonsNum/s");
  tPrediction_->Branch("selectedIDIsoMuonsPt", selectedIDIsoMuonsPt, "selectedIDIsoMuonsPt[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoMuonsEta", selectedIDIsoMuonsEta, "selectedIDIsoMuonsEta[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoMuonsPhi", selectedIDIsoMuonsPhi, "selectedIDIsoMuonsPhi[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoMuonsActivity", selectedIDIsoMuonsActivity, "selectedIDIsoMuonsActivity[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoMuonsRelPTJet", selectedIDIsoMuonsRelPTJet, "selectedIDIsoMuonsRelPTJet[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoMuonsDeltaRJet", selectedIDIsoMuonsDeltaRJet, "selectedIDIsoMuonsDeltaRJet[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("RecoIsoMuonE", selectedIDIsoMuonsE, "RecoIsoMuonE[selectedIDIsoMuonsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum,"selectedIDIsoElectronsNum/s");
  tPrediction_->Branch("selectedIDIsoElectronsPt", selectedIDIsoElectronsPt, "RecoIsoElecPt[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsEta", selectedIDIsoElectronsEta, "RecoIsoElecEta[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsPhi", selectedIDIsoElectronsPhi, "RecoIsoElecPhi[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("RecoIsoElecE", selectedIDIsoElectronsE, "RecoIsoElecE[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsActivity", selectedIDIsoElectronsActivity, "selectedIDIsoElectronsActivity[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsRelPTJet", selectedIDIsoElectronsRelPTJet, "selectedIDIsoElectronsRelPTJet[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("selectedIDIsoElectronsDeltaRJet", selectedIDIsoElectronsDeltaRJet, "selectedIDIsoElectronsDeltaRJet[selectedIDIsoElectronsNum]/F");
  tPrediction_->Branch("MTW",&mtw,"MTW/F");
  muActivityMethod=muActivityMethod_;
  elecActivityMethod=elecActivityMethod_;
  isoTrackActivityMethod=isoTrackActivityMethod_;
  tPrediction_->Branch("muActivityMethod",&muActivityMethod,"muActivityMethod/s");  
  tPrediction_->Branch("elecActivityMethod",&elecActivityMethod,"elecActivityMethod/s");  
  tPrediction_->Branch("isoTrackActivityMethod",&isoTrackActivityMethod,"isoTrackActivityMethod/s");
  tPrediction_->Branch("muMTWEff",&muMTWEff_,"muMTWEff/F");
  tPrediction_->Branch("mtwCorrectedWeight",&mtwCorrectedWeight_,"mtwCorrectedWeight/F");
  tPrediction_->Branch("muDiLepContributionMTWAppliedEff",&muDiLepContributionMTWAppliedEff_,"muDiLepContributionMTWAppliedEff/F");
  tPrediction_->Branch("mtwDiLepCorrectedWeight",&mtwDiLepCorrectedWeight_,"mtwDiLepCorrectedWeight/F");
  tPrediction_->Branch("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced_,"totalWeightDiLepIsoTrackReduced/F");
  tPrediction_->Branch("totalWeightDiLepIsoMuTrackReduced",&totalWeightDiLepIsoMuTrackReduced_,"totalWeightDiLepIsoMuTrackReduced/F");
  tPrediction_->Branch("totalWeightDiLepIsoElecTrackReduced",&totalWeightDiLepIsoElecTrackReduced_,"totalWeightDiLepIsoElecTrackReduced/F");
  tPrediction_->Branch("totalWeightDiLepIsoPionTrackReduced",&totalWeightDiLepIsoPionTrackReduced_,"totalWeightDiLepIsoPionTrackReduced/F");
  tPrediction_->Branch("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined_,"totalWeightDiLepIsoTrackReducedCombined/F");
  tPrediction_->Branch("muIsoWeight",&muIsoWeight_,"muIsoWeight/F");
  tPrediction_->Branch("muIsoOnlyWeight",&muIsoOnlyWeight_,"muIsoOnlyWeight/F");
  tPrediction_->Branch("muIsoEff",&muIsoEff_,"muIsoEff/F");
  tPrediction_->Branch("muRecoWeight",&muRecoWeight_,"muRecoWeight/F");
  tPrediction_->Branch("muRecoEff",&muRecoEff_,"muRecoEff/F");
  tPrediction_->Branch("muAccWeight",&muAccWeight_,"muAccWeight/F");
  tPrediction_->Branch("muAccEff",&muAccEff_,"muAccEff/F");
  tPrediction_->Branch("muTotalWeight",&muTotalWeight_,"muTotalWeight/F");
  tPrediction_->Branch("totalMuons",&totalMuons_,"totalMuons/F");
  tPrediction_->Branch("elecAccWeight",&elecAccWeight_,"elecAccWeight/F");
  tPrediction_->Branch("elecAccEff",&elecAccEff_,"elecAccEff/F");
  tPrediction_->Branch("elecRecoWeight",&elecRecoWeight_,"elecRecoWeight/F");
  tPrediction_->Branch("elecRecoEff",&elecRecoEff_,"elecRecoEff/F");
  tPrediction_->Branch("elecIsoWeight",&elecIsoWeight_,"elecIsoWeight/F");
  tPrediction_->Branch("elecIsoOnlyWeight",&elecIsoOnlyWeight_,"elecIsoOnlyWeight/F");
  tPrediction_->Branch("elecIsoEff",&elecIsoEff_,"elecIsoEff/F");
  tPrediction_->Branch("elecTotalWeight",&elecTotalWeight_,"elecTotalWeight/F");
  tPrediction_->Branch("totalElectrons",&totalElectrons_,"totalElectrons/F");
  tPrediction_->Branch("expectationReductionIsoTrackEff",&expectationReductionIsoTrackEff_,"expectationReductionIsoTrackEff/F");
  tPrediction_->Branch("expectationReductionMuIsoTrackEff",&expectationReductionMuIsoTrackEff_,"expectationReductionMuIsoTrackEff/F");
  tPrediction_->Branch("expectationReductionElecIsoTrackEff",&expectationReductionElecIsoTrackEff_,"expectationReductionElecIsoTrackEff/F");
  tPrediction_->Branch("expectationReductionPionIsoTrackEff",&expectationReductionPionIsoTrackEff_,"expectationReductionPionIsoTrackEff/F");
  tPrediction_->Branch("expectationReductionIsoTrackEffCombined",&expectationReductionIsoTrackEffCombined_,"expectationReductionIsoTrackEffCombined/F");
  tPrediction_->Branch("totalWeight",&totalWeight_,"totalWeight/F");
  tPrediction_->Branch("muDiLepEffMTWAppliedEff",&muDiLepEffMTWAppliedEff_,"muDiLepEffMTWAppliedEff/F");
  tPrediction_->Branch("elecDiLepEffMTWAppliedEff",&elecDiLepEffMTWAppliedEff_,"elecDiLepEffMTWAppliedEff/F");
  tPrediction_->Branch("totalWeightDiLep",&totalWeightDiLep_,"totalWeightDiLep/F");
  tPrediction_->Branch("IsolatedMuonTracksVetoNum",&IsolatedMuonTracksVetoNum,"IsolatedMuonTracksVetoNum/s");
  tPrediction_->Branch("IsolatedMuonTracksVetoPt", IsolatedMuonTracksVetoPt, "IsolatedMuonTracksVetoPt[IsolatedMuonTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedMuonTracksVetoEta", IsolatedMuonTracksVetoEta, "IsolatedMuonTracksVetoEta[IsolatedMuonTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedMuonTracksVetoPhi", IsolatedMuonTracksVetoPhi, "IsolatedMuonTracksVetoPhi[IsolatedMuonTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedMuonTracksVetoE", IsolatedMuonTracksVetoE, "IsolatedMuonTracksVetoE[IsolatedMuonTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedMuonTracksVeto_MT", IsolatedMuonTracksVeto_MT, "IsolatedMuonTracksVeto_MT[IsolatedMuonTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedElectronTracksVetoNum",&IsolatedElectronTracksVetoNum,"IsolatedElectronTracksVetoNum/s");
  tPrediction_->Branch("IsolatedElectronTracksVetoPt", IsolatedElectronTracksVetoPt, "IsolatedElectronTracksVetoPt[IsolatedElectronTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedElectronTracksVetoEta", IsolatedElectronTracksVetoEta, "IsolatedElectronTracksVetoEta[IsolatedElectronTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedElectronTracksVetoPhi", IsolatedElectronTracksVetoPhi, "IsolatedElectronTracksVetoPhi[IsolatedElectronTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedElectronTracksVetoE", IsolatedElectronTracksVetoE, "IsolatedElectronTracksVetoE[IsolatedElectronTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedElectronTracksVeto_MT", IsolatedElectronTracksVeto_MT, "IsolatedElectronTracksVeto_MT[IsolatedElectronTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedPionTracksVetoNum",&IsolatedPionTracksVetoNum,"IsolatedPionTracksVetoNum/s");
  tPrediction_->Branch("IsolatedPionTracksVetoPt", IsolatedPionTracksVetoPt, "IsolatedPionTracksVetoPt[IsolatedPionTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedPionTracksVetoEta", IsolatedPionTracksVetoEta, "IsolatedPionTracksVetoEta[IsolatedPionTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedPionTracksVetoPhi", IsolatedPionTracksVetoPhi, "IsolatedPionTracksVetoPhi[IsolatedPionTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedPionTracksVetoE", IsolatedPionTracksVetoE, "IsolatedPionTracksVetoE[IsolatedPionTracksVetoNum]/F");
  tPrediction_->Branch("IsolatedPionTracksVeto_MT", IsolatedPionTracksVeto_MT, "IsolatedPionTracksVeto_MT[IsolatedPionTracksVetoNum]/F");

  tPrediction_->Branch("isoTrackStatUp", &isoTrackStatUp, "isoTrackStatUp/F");
  tPrediction_->Branch("isoTrackStatDown", &isoTrackStatDown, "isoTrackStatDown/F");
  tPrediction_->Branch("MTWStatUp", &MTWStatUp, "MTWStatUp/F");
  tPrediction_->Branch("MTWStatDown", &MTWStatDown, "MTWStatDown/F");
  tPrediction_->Branch("purityStatUp", &purityStatUp, "purityStatUp/F");
  tPrediction_->Branch("purityStatDown", &purityStatDown, "purityStatDown/F");
  tPrediction_->Branch("singleLepPurityStatUp", &singleLepPurityStatUp, "singleLepPurityStatUp/F");
  tPrediction_->Branch("singleLepPurityStatDown", &singleLepPurityStatDown, "singleLepPurityStatDown/F");
  tPrediction_->Branch("diLepFoundStatUp", &diLepFoundStatUp, "diLepFoundStatUp/F");
  tPrediction_->Branch("diLepFoundStatDown", &diLepFoundStatDown, "diLepFoundStatDown/F");
  tPrediction_->Branch("muIsoStatUp", &muIsoStatUp, "muIsoStatUp/F");
  tPrediction_->Branch("muIsoStatDown", &muIsoStatDown, "muIsoStatDown/F");
  tPrediction_->Branch("muRecoStatUp", &muRecoStatUp, "muRecoStatUp/F");
  tPrediction_->Branch("muRecoStatDown", &muRecoStatDown, "muRecoStatDown/F");
  tPrediction_->Branch("muAccStatUp", &muAccStatUp, "muAccStatUp/F");
  tPrediction_->Branch("muAccStatDown", &muAccStatDown, "muAccStatDown/F");
  tPrediction_->Branch("elecIsoStatUp", &elecIsoStatUp, "elecIsoStatUp/F");
  tPrediction_->Branch("elecIsoStatDown", &elecIsoStatDown, "elecIsoStatDown/F");
  tPrediction_->Branch("elecRecoStatUp", &elecRecoStatUp, "elecRecoStatUp/F");
  tPrediction_->Branch("elecRecoStatDown", &elecRecoStatDown, "elecRecoStatDown/F");
  tPrediction_->Branch("elecAccStatUp", &elecAccStatUp, "elecAccStatUp/F");
  tPrediction_->Branch("elecAccStatDown", &elecAccStatDown, "elecAccStatDown/F");

  tPrediction_->Branch("isoTrackSysUp", &isoTrackSysUp, "isoTrackSysUp/F");
  tPrediction_->Branch("isoTrackSysDown", &isoTrackSysDown, "isoTrackSysDown/F");
  tPrediction_->Branch("MTWSysUp", &MTWSysUp, "MTWSysUp/F");
  tPrediction_->Branch("MTWSysDown", &MTWSysDown, "MTWSysDown/F");
  tPrediction_->Branch("puritySysUp", &puritySysUp, "puritySysUp/F");
  tPrediction_->Branch("puritySysDown", &puritySysDown, "puritySysDown/F");
  tPrediction_->Branch("singleLepPuritySysUp", &singleLepPuritySysUp, "singleLepPuritySysUp/F");
  tPrediction_->Branch("singleLepPuritySysDown", &singleLepPuritySysDown, "singleLepPuritySysDown/F");
  tPrediction_->Branch("diLepFoundSysUp", &diLepFoundSysUp, "diLepFoundSysUp/F");
  tPrediction_->Branch("diLepFoundSysDown", &diLepFoundSysDown, "diLepFoundSysDown/F");
  tPrediction_->Branch("muIsoSysUp", &muIsoSysUp, "muIsoSysUp/F");
  tPrediction_->Branch("muIsoSysDown", &muIsoSysDown, "muIsoSysDown/F");
  tPrediction_->Branch("muRecoSysUp", &muRecoSysUp, "muRecoSysUp/F");
  tPrediction_->Branch("muRecoSysDown", &muRecoSysDown, "muRecoSysDown/F");
  tPrediction_->Branch("muAccSysUp", &muAccSysUp, "muAccSysUp/F");
  tPrediction_->Branch("muAccSysDown", &muAccSysDown, "muAccSysDown/F");
  tPrediction_->Branch("elecIsoSysUp", &elecIsoSysUp, "elecIsoSysUp/F");
  tPrediction_->Branch("elecIsoSysDown", &elecIsoSysDown, "elecIsoSysDown/F");
  tPrediction_->Branch("elecRecoSysUp", &elecRecoSysUp, "elecRecoSysUp/F");
  tPrediction_->Branch("elecRecoSysDown", &elecRecoSysDown, "elecRecoSysDown/F");
  tPrediction_->Branch("elecAccSysUp", &elecAccSysUp, "elecAccSysUp/F");
  tPrediction_->Branch("elecAccSysDown", &elecAccSysDown, "elecAccSysDown/F");

  tPrediction_->Branch("diBosonUp", &diBosonUp, "diBosonUp/F");
  tPrediction_->Branch("diBosonDown", &diBosonDown, "diBosonDown/F");
  tPrediction_->Branch("nonClosureUp", &nonClosureUp, "nonClosureUp/F");
  tPrediction_->Branch("nonClosureDown", &nonClosureDown, "nonClosureDown/F");

  tPrediction_->Branch("totalStat", &totalStat, "totalStat/F");
  tPrediction_->Branch("totalSys", &totalSys, "totalSys/F");
  tPrediction_->Branch("totalUnc", &totalUnc, "totalUnc/F");

  GetOutputList()->Add(tPrediction_);
  SearchBins_ = new SearchBins(false); // 72 searchbins
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
  std::cout<<"Use MET filters: "<<useFilterData<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"UseAsymmErrors: "<<useAsymmErrors<<std::endl;
  std::cout<<"UseTagAndProbeEffIso: "<<UseTagAndProbeEffIso_<<std::endl;
  std::cout<<"UseTagAndProbeEffReco: "<<UseTagAndProbeEffReco_<<std::endl;
  
}

Bool_t Prediction::Process(Long64_t entry)
{
  resetValues();
  fChain->GetTree()->GetEntry(entry);
  
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ ) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_)) return kTRUE;
  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  if((selectedIDIsoMuonsNum+selectedIDIsoElectronsNum) !=1) return kTRUE;

  bool passTrigger = false;  
    for (std::vector<string>::iterator it = TriggerNames->begin() ; it != TriggerNames->end(); ++it){
      if(*it=="HLT_PFHT350_PFMET100_NoiseCleaned_v1"){
        if(PassTrigger->at(it - TriggerNames->begin())>0.5) passTrigger = true;
      }
      if(*it=="HLT_PFHT800_v1"){
        if(PassTrigger->at(it - TriggerNames->begin())>0.5) passTrigger = true;
      }
      if(*it=="HLT_PFMET170_NoiseCleaned_v2"){
        if(PassTrigger->at(it - TriggerNames->begin())>0.5) passTrigger = true;
      }
    }
    if(useTrigger && !passTrigger) return kTRUE;

  isoTracks= isoElectronTracks + isoMuonTracks + isoPionTracks;
  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);

  // get IsoTrack Effs
  //      expectationReductionIsoTrackEff_= ExpectationReductionIsoTrackNJetsEff_->GetEff(NJets, useAsymmErrors);
  expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);
  expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackBTagsNJetsEff_->GetEff(BTags,NJets, useAsymmErrors);

  //for compatibility
  expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
  expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
  expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
  expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

  if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0)
  {
    mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuonsPt[0], selectedIDIsoMuonsPhi[0]);
    selectedIDIsoMuonsActivity[0]=MuActivity(selectedIDIsoMuonsEta[0], selectedIDIsoMuonsPhi[0],muActivityMethod_);
    double elecActivity = ElecActivity(selectedIDIsoMuonsEta[0], selectedIDIsoMuonsPhi[0],elecActivityMethod_);

    std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(selectedIDIsoMuonsPt[0], selectedIDIsoMuonsEta[0], selectedIDIsoMuonsPhi[0]);
    selectedIDIsoMuonsDeltaRJet[0]=DeltaR_relPT.first;
    selectedIDIsoMuonsRelPTJet[0]=DeltaR_relPT.second;

    // get Efficiencies
    muPurityCorrectionVec_ =  MuPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    muMTWEffVec_ = MuMTWNJets_->GetEff(NJets, useAsymmErrors);
    muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
    muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);

    muIsoEffVec_ = MuIsoPTActivity_->GetEff( selectedIDIsoMuonsPt[0],selectedIDIsoMuonsActivity[0], useAsymmErrors);
  //  muIsoEffVec_ = MuIsoRelPTDeltaRJet_->GetEff(selectedIDIsoMuonsRelPTJet[0], selectedIDIsoMuonsDeltaRJet[0], useAsymmErrors);
    muRecoEffVec_ = MuRecoPTActivity_->GetEff(selectedIDIsoMuonsPt[0],selectedIDIsoMuonsActivity[0], useAsymmErrors);
  //muAccEffVec_ = MuAccMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    if(NJets<6.5) muAccEffVec_ = MuAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
    else muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);

    //elecAccEffVec_ = ElecAccMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    if(NJets<6.5) elecAccEffVec_ = ElecAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
    else elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
    elecRecoEffVec_ = ElecRecoPTActivity_->GetEff(selectedIDIsoMuonsPt[0],elecActivity, useAsymmErrors);
    elecIsoEffVec_ = ElecIsoPTActivity_->GetEff(selectedIDIsoMuonsPt[0],elecActivity, useAsymmErrors);
    //elecIsoEffVec_ = ElecIsoRelPTDeltaRJet_->GetEff(selectedIDIsoMuonsRelPTJet[0], selectedIDIsoMuonsDeltaRJet[0], useAsymmErrors);
/*
    if(UseTagAndProbeEffIso_)muIsoEff_ = getEff(MuIsoPTActivityTAPMC_, selectedIDIsoMuonsPt[0],selectedIDIsoMuonsActivity[0]); 
    if(UseTagAndProbeEffReco_)muRecoEff_ = getEff(MuRecoPTActivityTAPMC_, selectedIDIsoMuonsPt[0],selectedIDIsoMuonsActivity[0]); 
    if(UseTagAndProbeEffReco_)elecRecoEff_ = getEff(ElecRecoPTActivityTAPMC_, selectedIDIsoMuonsPt[0],elecActivity); 
    if(UseTagAndProbeEffIso_)elecIsoEff_ = getEff(ElecIsoPTActivityTAPMC_, selectedIDIsoMuonsPt[0],elecActivity); 
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

    MuMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
    CombinedMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);

    if(Bin_<300){
      MuWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
      CombinedWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
    }

    // weights used for closure tests
    muIsoOnlyWeight_ = Weight * (1 - muIsoEff_) / muIsoEff_ * muPurityCorrection_ * muDiLepContributionMTWAppliedEff_;

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
    Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReduced_

    isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
    isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ + muMTWEffVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
    MTWStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ - muMTWEffVec_.errDown) * (w2 * (w3a+w3b) + w4) - wGes;
    purityStatUp = 0.; // no purity correction for muCS (>99%)
    purityStatDown = 0.; // no purity correction for muCS (>99%)

    singleLepPurityStatUp = w1 * ((muDiLepContributionMTWAppliedEff_ + muDiLepContributionMTWAppliedEffVec_.errUp) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_-muDiLepContributionMTWAppliedEffVec_.errUp) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
    singleLepPurityStatDown = w1 * ((muDiLepContributionMTWAppliedEff_ - muDiLepContributionMTWAppliedEffVec_.errDown) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_+muDiLepContributionMTWAppliedEffVec_.errDown) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
    diLepFoundStatUp = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errUp)/(muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
    diLepFoundStatDown =w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errDown)/(muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

    muIsoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_+muIsoEffVec_.errUp)*muRecoEff_*muAccEff_) * ((1-muIsoEff_-muIsoEffVec_.errUp)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muIsoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_-muIsoEffVec_.errDown)*muRecoEff_*muAccEff_) * ((1-muIsoEff_+muIsoEffVec_.errDown)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muRecoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_ + (1-muRecoEff_-muRecoEffVec_.errUp)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muRecoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_ + (1-muRecoEff_+muRecoEffVec_.errDown)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muAccStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_+muAccEffVec_.errUp)) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_+muAccEffVec_.errUp) + (1-muRecoEff_)*(muAccEff_+muAccEffVec_.errUp) + (1-muAccEff_-muAccEffVec_.errUp) +w3b) + w4) - wGes;
    muAccStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_-muAccEffVec_.errDown)) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_-muAccEffVec_.errDown) + (1-muRecoEff_)*(muAccEff_-muAccEffVec_.errDown) + (1-muAccEff_+muAccEffVec_.errDown) +w3b) + w4) - wGes;

    elecIsoStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_-elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecIsoStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_+elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecRecoStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecRecoEff_-elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecRecoStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecRecoEff_+elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecAccStatUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecRecoEff_)*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecAccEff_-elecAccEffVec_.errUp)) + w4) - wGes;
    elecAccStatDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecRecoEff_)*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecAccEff_+elecAccEffVec_.errDown)) + w4) - wGes;


    isoTrackSysUp = Weight * (1 - expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
    isoTrackSysDown  = Weight * (1 - expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWSysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ + (1-muMTWEff_) * 0.01 * MuMTWUncertaintyUp_) * (w2 * (w3a+w3b) + w4) - wGes;
    MTWSysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(muMTWEff_ - (1-muMTWEff_) * 0.01 * MuMTWUncertaintyDown_) * (w2 * (w3a+w3b) + w4) - wGes;
    puritySysUp = 0.; // no purity correction for muCS (>99%)
    puritySysDown = 0.; // no purity correction for muCS (>99%)
    singleLepPuritySysUp = w1 * ((muDiLepContributionMTWAppliedEff_ + (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityUp_) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_ + (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityUp_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
    singleLepPuritySysDown = w1 * ((muDiLepContributionMTWAppliedEff_ - (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityDown_) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_ - (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityDown_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
    diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_ *(1 + 0.01 * MuDiLepFoundUp_))/(muDiLepEffMTWAppliedEff_ *(1 + 0.01 * MuDiLepFoundUp_))) - wGes;
    diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_ *(1 - 0.01 * MuDiLepFoundDown_))/(muDiLepEffMTWAppliedEff_ *(1 - 0.01 * MuDiLepFoundDown_))) - wGes;
    
    muIsoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_))*muRecoEff_*muAccEff_) * ((1-muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_))*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muIsoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_))*muRecoEff_*muAccEff_) * ((1-muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_))*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muRecoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_ *(1 + 0.01 * MuRecoUncertaintyUp_))*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_  *(1 + 0.01 * MuRecoUncertaintyUp_))*muAccEff_ + (1-muRecoEff_ *(1 + 0.01 * MuRecoUncertaintyUp_))*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muRecoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_ *(1 - 0.01 * MuRecoUncertaintyDown_))*muAccEff_) * ((1-muIsoEff_)*(muRecoEff_  *(1 - 0.01 * MuRecoUncertaintyDown_))*muAccEff_ + (1-muRecoEff_ *(1 - 0.01 * MuRecoUncertaintyDown_))*muAccEff_ + (1-muAccEff_) +w3b) + w4) - wGes;
    muAccSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_))) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_)) + (1-muRecoEff_)*(muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_)) + (1-muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_)) +w3b) + w4) - wGes;
    muAccSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_))) * ((1-muIsoEff_)*muRecoEff_*(muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_)) + (1-muRecoEff_)*(muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_)) + (1-muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_)) +w3b) + w4) - wGes;

    elecIsoSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_))*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecIsoSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_))*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecRecoSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_*(1 + 0.01 * ElecRecoUncertaintyUp_))*elecAccEff_ + (1-elecRecoEff_*(1 + 0.01 * ElecRecoUncertaintyUp_))*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecRecoSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*(elecRecoEff_*(1 - 0.01 * ElecRecoUncertaintyDown_))*elecAccEff_ + (1-elecRecoEff_*(1 - 0.01 * ElecRecoUncertaintyDown_))*elecAccEff_ + (1-elecAccEff_)) + w4) - wGes;
    elecAccSysUp = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_)) + (1-elecRecoEff_)*(elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_)) + (1-elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_))) + w4) - wGes;
    elecAccSysDown = w1 * (w2 * (w3a + (1-elecIsoEff_)*elecRecoEff_*(elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_)) + (1-elecRecoEff_)*(elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_)) + (1-elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_))) + w4) - wGes;
  
    diBosonUp = wGes * 0.01 * diBosonContributionUp_;
    diBosonDown = wGes * 0.01 * diBosonContributionDown_;

    if(NJets < 6.5){
      nonClosureUp = wGes * 0.01 * nonClosureLowNJets_;
      nonClosureDown = - wGes * 0.01 * nonClosureLowNJets_;
    }else{
      nonClosureUp = wGes * 0.01 * nonClosureHighNJets_;
      nonClosureDown = - wGes * 0.01 * nonClosureHighNJets_;
    }

    totalStat = sqrt(isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    totalSys = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+diBosonUp*diBosonUp+nonClosureUp*nonClosureUp);
    totalUnc = sqrt(totalStat*totalStat+totalSys*totalSys);

  }       
  else if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
  {
    mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectronsPt[0], selectedIDIsoElectronsPhi[0]);
    selectedIDIsoElectronsActivity[0]=ElecActivity(selectedIDIsoElectronsEta[0], selectedIDIsoElectronsPhi[0],elecActivityMethod_);
    double muActivity = MuActivity(selectedIDIsoMuonsEta[0], selectedIDIsoMuonsPhi[0],elecActivityMethod_);

    std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(selectedIDIsoElectronsPt[0], selectedIDIsoElectronsEta[0], selectedIDIsoElectronsPhi[0]);
    selectedIDIsoElectronsDeltaRJet[0]=DeltaR_relPT.first;
    selectedIDIsoElectronsRelPTJet[0]=DeltaR_relPT.second;

    // get Efficiencies
    elecPurityCorrectionVec_ =  ElecPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    elecMTWEffVec_ = ElecMTWNJets_->GetEff(NJets, useAsymmErrors);
    elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
    elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);

    elecIsoEffVec_ =  ElecIsoPTActivity_->GetEff(selectedIDIsoElectronsPt[0],selectedIDIsoElectronsActivity[0], useAsymmErrors);
  //  elecIsoEffVec_ = ElecIsoRelPTDeltaRJet_->GetEff(selectedIDIsoElectronsRelPTJet[0], selectedIDIsoElectronsDeltaRJet[0], useAsymmErrors);
    elecRecoEffVec_ = ElecRecoPTActivity_->GetEff(selectedIDIsoElectronsPt[0],selectedIDIsoElectronsActivity[0], useAsymmErrors);
    //elecAccEffVec_ = ElecAccMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    if(NJets<6.5) elecAccEffVec_ = ElecAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
    else elecAccEffVec_ = ElecAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);

    //muAccEffVec_ = MuAccMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
    if(NJets<6.5) muAccEffVec_ = MuAccHTMHT_NJetsLow_->GetEff(HT,MHT, useAsymmErrors);
    else muAccEffVec_ = MuAccHTMHT_NJetsHigh_->GetEff(HT,MHT, useAsymmErrors);
    muRecoEffVec_ = MuRecoPTActivity_->GetEff( selectedIDIsoElectronsPt[0], muActivity, useAsymmErrors);
    muIsoEffVec_ = MuIsoPTActivity_->GetEff( selectedIDIsoElectronsPt[0], muActivity, useAsymmErrors);
  //  muIsoEffVec_ = MuIsoRelPTDeltaRJet_->GetEff(selectedIDIsoElectronsRelPTJet[0], selectedIDIsoElectronsDeltaRJet[0], useAsymmErrors);
/*
    if(UseTagAndProbeEffIso_) elecIsoEff_ = getEff(ElecIsoPTActivityTAPMC_, selectedIDIsoMuonsPt[0], selectedIDIsoElectronsActivity[0]); 
    if(UseTagAndProbeEffReco_)elecRecoEff_ = getEff(ElecRecoPTActivityTAPMC_, selectedIDIsoMuonsPt[0], selectedIDIsoElectronsActivity[0]); 
    if(UseTagAndProbeEffReco_) muRecoEff_ = getEff(MuRecoPTActivityTAPMC_, selectedIDIsoMuonsPt[0], muActivity); 
    if(UseTagAndProbeEffIso_) muIsoEff_ = getEff(MuIsoPTActivityTAPMC_, selectedIDIsoMuonsPt[0], muActivity); 
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

    ElecMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
    CombinedMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);

    if(Bin_<300){
      ElecWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
      CombinedWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
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
    Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReduced_

    isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ + elecMTWEffVec_.errUp) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ - elecMTWEffVec_.errDown) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    purityStatUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ + elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
    purityStatDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ - elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;

    singleLepPurityStatUp = w1 * ((elecDiLepContributionMTWAppliedEff_ + elecDiLepContributionMTWAppliedEffVec_.errUp) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_-elecDiLepContributionMTWAppliedEffVec_.errUp) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
    singleLepPurityStatDown = w1 * ((elecDiLepContributionMTWAppliedEff_ - elecDiLepContributionMTWAppliedEffVec_.errDown) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_+elecDiLepContributionMTWAppliedEffVec_.errDown) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
    diLepFoundStatUp = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errUp)/(elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
    diLepFoundStatDown =w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errDown)/(elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

    elecIsoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_+elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_-elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecIsoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_-elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_+elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecRecoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecRecoEff_-elecRecoEffVec_.errUp)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecRecoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecRecoEff_+elecRecoEffVec_.errDown)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecAccStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp)) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecRecoEff_)*(elecAccEff_+elecAccEffVec_.errUp) + (1-elecAccEff_-elecAccEffVec_.errUp) +w3b) + w4) - wGes;
    elecAccStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown)) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecRecoEff_)*(elecAccEff_-elecAccEffVec_.errDown) + (1-elecAccEff_+elecAccEffVec_.errDown) +w3b) + w4) - wGes;

    muIsoStatUp = w1 * (w2 * (w3a + (1-muIsoEff_-muIsoEffVec_.errUp)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muIsoStatDown = w1 * (w2 * (w3a + (1-muIsoEff_+muIsoEffVec_.errDown)*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muRecoStatUp = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_ + (1-muRecoEff_-muRecoEffVec_.errUp)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muRecoStatDown = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_ + (1-muRecoEff_+muRecoEffVec_.errDown)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muAccStatUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_+muAccEffVec_.errUp) + (1-muRecoEff_)*(muAccEff_+muAccEffVec_.errUp) + (1-muAccEff_-muAccEffVec_.errUp)) + w4) - wGes;
    muAccStatDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_-muAccEffVec_.errDown) + (1-muRecoEff_)*(muAccEff_-muAccEffVec_.errDown) + (1-muAccEff_+muAccEffVec_.errDown)) + w4) - wGes;


    isoTrackSysUp = Weight * (1 - expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    isoTrackSysDown  = Weight * (1 - expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWSysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ + (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyUp_) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    MTWSysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/(elecMTWEff_ - (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyDown_) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
    puritySysUp = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ + (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyUp_) * (w2 * (w3a+w3b) + w4) - wGes; 
    puritySysDown = Weight * (1 - expectationReductionIsoTrackEff_) * 1/elecMTWEff_ * (elecPurityCorrection_ - (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyDown_) * (w2 * (w3a+w3b) + w4) - wGes;
    singleLepPuritySysUp = w1 * ((elecDiLepContributionMTWAppliedEff_ + (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityUp_) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_ + (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityUp_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
    singleLepPuritySysDown = w1 * ((elecDiLepContributionMTWAppliedEff_ - (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityDown_) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_ - (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityDown_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
    diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_ *(1 + 0.01 * ElecDiLepFoundUp_))/(elecDiLepEffMTWAppliedEff_ *(1 + 0.01 * ElecDiLepFoundUp_))) - wGes;
    diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_ *(1 - 0.01 * ElecDiLepFoundDown_))/(elecDiLepEffMTWAppliedEff_ *(1 - 0.01 * ElecDiLepFoundDown_))) - wGes;
    
    elecIsoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_))*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_))*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecIsoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_))*elecRecoEff_*elecAccEff_) * ((1-elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_))*elecRecoEff_*elecAccEff_ + (1-elecRecoEff_)*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecRecoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_ *(1 + 0.01 * ElecRecoUncertaintyUp_))*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_  *(1 + 0.01 * ElecRecoUncertaintyUp_))*elecAccEff_ + (1-elecRecoEff_ *(1 + 0.01 * ElecRecoUncertaintyUp_))*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecRecoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_ *(1 - 0.01 * ElecRecoUncertaintyDown_))*elecAccEff_) * ((1-elecIsoEff_)*(elecRecoEff_  *(1 - 0.01 * ElecRecoUncertaintyDown_))*elecAccEff_ + (1-elecRecoEff_ *(1 - 0.01 * ElecRecoUncertaintyDown_))*elecAccEff_ + (1-elecAccEff_) +w3b) + w4) - wGes;
    elecAccSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_))) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_)) + (1-elecRecoEff_)*(elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_)) + (1-elecAccEff_*(1 + 0.01 * ElecAccUncertaintyUp_)) +w3b) + w4) - wGes;
    elecAccSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_))) * ((1-elecIsoEff_)*elecRecoEff_*(elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_)) + (1-elecRecoEff_)*(elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_)) + (1-elecAccEff_*(1 - 0.01 * ElecAccUncertaintyDown_)) +w3b) + w4) - wGes;

    muIsoSysUp = w1 * (w2 * (w3a + (1-muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_))*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muIsoSysDown = w1 * (w2 * (w3a + (1-muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_))*muRecoEff_*muAccEff_ + (1-muRecoEff_)*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muRecoSysUp = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_*(1 + 0.01 * MuRecoUncertaintyUp_))*muAccEff_ + (1-muRecoEff_*(1 + 0.01 * MuRecoUncertaintyUp_))*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muRecoSysDown = w1 * (w2 * (w3a + (1-muIsoEff_)*(muRecoEff_*(1 - 0.01 * MuRecoUncertaintyDown_))*muAccEff_ + (1-muRecoEff_*(1 - 0.01 * MuRecoUncertaintyDown_))*muAccEff_ + (1-muAccEff_)) + w4) - wGes;
    muAccSysUp = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_)) + (1-muRecoEff_)*(muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_)) + (1-muAccEff_*(1 + 0.01 * MuAccUncertaintyUp_))) + w4) - wGes;
    muAccSysDown = w1 * (w2 * (w3a + (1-muIsoEff_)*muRecoEff_*(muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_)) + (1-muRecoEff_)*(muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_)) + (1-muAccEff_*(1 - 0.01 * MuAccUncertaintyDown_))) + w4) - wGes;
  
    diBosonUp = wGes * 0.01 * diBosonContributionUp_;
    diBosonDown = wGes * 0.01 * diBosonContributionDown_;

    if(NJets < 6.5){
      nonClosureUp = wGes * 0.01 * nonClosureLowNJets_;
      nonClosureDown = - wGes * 0.01 * nonClosureLowNJets_;
    }else{
      nonClosureUp = wGes * 0.01 * nonClosureHighNJets_;
      nonClosureDown = - wGes * 0.01 * nonClosureHighNJets_;
    }

    totalStat = sqrt(isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    totalSys = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+diBosonUp*diBosonUp+nonClosureUp*nonClosureUp);
    totalUnc = sqrt(totalStat*totalStat+totalSys*totalSys);

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
  TFile *outPutFile = new TFile("Prediction.root","RECREATE"); ;
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
  outPutFile->mkdir("MeanWeightPerBin");
  TDirectory *dEfficienciesPerBin = (TDirectory*)outPutFile->Get("MeanWeightPerBin");
  dEfficienciesPerBin->cd();
  for(int b = 0; b <300; b++){
    MuWeightPerBin_[b]->Write();
    ElecWeightPerBin_[b]->Write();
    CombinedWeightPerBin_[b]->Write();
  }

  outPutFile->Close();
  
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
  
}
bool Prediction::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    if(CSCTightHaloFilter==0) result=false;;
    if(GoodVtx==0) result=false;;
    if(eeBadScFilter==0) result=false;;
    //if(HBHENoiseFilter==0) result=false;
  }
  if(!JetID) result=false;
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
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(muEta,muPhi,JetsEta[i],JetsPhi[i])>maxDeltaRMuActivity_ ) continue;
      result+=JetsPt[i] * (Jets_chargedEmEnergyFraction[i] + Jets_chargedHadronEnergyFraction[i]);
    }
  }
  if(method==1)
  {
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(muEta,muPhi,JetsEta[i],JetsPhi[i])>maxDeltaRMuActivity_ ) continue;
      result+=JetsPt[i] * (Jets_chargedEmEnergyFraction[i] + Jets_chargedHadronEnergyFraction[i])*(1/(deltaR(muEta,muPhi,JetsEta[i],JetsPhi[i])+0.5));
    }
  }
  if(method==2)
  {
    for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
    {
      if(deltaR(muEta,muPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=SelectedPFCandidatesPt[i];
    }
  }
  if(method==3)
  {
    for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
    {
      if(SelectedPFCandidates_Charge[i]!=0) continue;
      if(deltaR(muEta,muPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=SelectedPFCandidatesPt[i];
    }
  }
  return result;
  
}
double Prediction::ElecActivity( double elecEta, double elecPhi, unsigned int method)
{
  double result =0;
  if(method==0)
  {
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(elecEta,elecPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=JetsPt[i] * (Jets_chargedHadronEnergyFraction[i]);
      //                      result+=JetsPt[i] * (Jets_chargedEmEnergyFraction[i] + Jets_chargedHadronEnergyFraction[i]);
    }
  }
  if(method==1)
  {
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(elecEta,elecPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=JetsPt[i] * (Jets_chargedHadronEnergyFraction[i])*(1/(deltaR(elecEta,elecPhi,JetsEta[i],JetsPhi[i])+0.5));
    }
  }
  if(method==2)
  {
    for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
    {
      if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=SelectedPFCandidatesPt[i];
    }
  }
  if(method==3)
  {
    for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
    {
      if(SelectedPFCandidates_Charge[i]!=0) continue;
      if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=SelectedPFCandidatesPt[i];
    }
  }
  return result;
  
}
double Prediction::IsoTrackActivityCalc( double isoTrackEta, double isoTrackPhi, unsigned int method)
{
  double result =0;
  if(method==0)
  {
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(isoTrackEta,isoTrackPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=JetsPt[i] * (Jets_neutralEmEnergyFraction[i] + Jets_photonEnergyFraction[i]);
    }
  }
  if(method==1)
  {
    for (unsigned int i=0; i < JetsNum ; i++)
    {
      if(deltaR(isoTrackEta,isoTrackPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=JetsPt[i] * (Jets_neutralEmEnergyFraction[i] + Jets_photonEnergyFraction[i])*(1/(deltaR(isoTrackEta,isoTrackPhi,JetsEta[i],JetsPhi[i])+0.5));
    }
  }
  if(method==2)
  {
    for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
    {
      if(deltaR(isoTrackEta,isoTrackPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
      result+=SelectedPFCandidatesPt[i];
    }
  }
  return result;
  
}

std::pair <double,double> Prediction::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
  double relPt = 9999;
  double deltaRmin = 9999;

  for (unsigned int i=0; i < JetsNum ; i++)
  {
    if(deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]) > deltaRmin) continue;

    if(deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]) < jetCone_)
    {
      if(lepPt > JetsPt[i]){
        if(lepPt < 1.2 * JetsPt[i]) continue;
        else{
          relPt = lepPt / JetsPt[i];
          deltaRmin = deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]);
          continue;
        }
      }
      if((JetsPt[i] - lepPt) < jetMinPt_) continue;
      else{
        relPt = lepPt / (JetsPt[i] - lepPt);
        deltaRmin = deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]);
        continue;
      }      
    }

    relPt = lepPt / JetsPt[i];
    deltaRmin = deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]);
  }

  return std::make_pair(deltaRmin, relPt);
}
