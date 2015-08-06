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
  
    
  
  TString option = GetOption();
  tPrediction_ = new TTree("LostLeptonPrediction","a simple Tree with simple variables");
  tPrediction_->Branch("HT",&HT,"HT/F");
  tPrediction_->Branch("MHT",&MHT,"MHT/F");
  tPrediction_->Branch("NJets",&NJets,"NJets/s");
  tPrediction_->Branch("BTags",&BTags,"BTags/s");
  tPrediction_->Branch("NVtx",&NVtx,"NVtx/s");
  tPrediction_->Branch("Bin",&Bin_,"Bin/s");
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
  GetOutputList()->Add(tPrediction_);
  SearchBins_ = new SearchBins();
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
  if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ )return kTRUE;
  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  if((selectedIDIsoMuonsNum+selectedIDIsoElectronsNum) !=1) return kTRUE;

  if(useTrigger){
    for (std::vector<string>::iterator it = TriggerNames->begin() ; it != TriggerNames->end(); ++it){
      if(*it=="HLT_PFHT350_PFMET100_NoiseCleaned_v1"){
        if(PassTrigger->at(it - TriggerNames->begin())<0.5) return kTRUE;
     }
    }
  }

  isoTracks= isoElectronTracks + isoMuonTracks + isoPionTracks;
  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);

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
    purityCorrectedWeight_ = Weight * muPurityCorrection_;
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

    // weights used for closure tests
    muIsoOnlyWeight_ = Weight * (1 - muIsoEff_) / muIsoEff_ * muPurityCorrection_ * muDiLepContributionMTWAppliedEff_;

    //std::cout << (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_ / Weight << std::endl;
    
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

    // weights used for closure tests
    elecIsoOnlyWeight_ = Weight * (1 - elecIsoEff_) / elecIsoEff_ * elecPurityCorrection_ * elecDiLepContributionMTWAppliedEff_;  
    }

  tPrediction_->Fill();
  return kTRUE;
}

void Prediction::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
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
    if(METFilters==1) result=false;;
    if(CSCTightHaloFilter==0) result=false;;
    if(HBHENoiseFilter==1) result=false;;
    if(EcalDeadCellTriggerPrimitiveFilter==0) result=false;
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
