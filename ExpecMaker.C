#define ExpecMaker_cxx
// The class definition in ExpecMaker.h has been generated automatically
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
// Root > T->Process("ExpecMaker.C")
// Root > T->Process("ExpecMaker.C","some options")
// Root > T->Process("ExpecMaker.C+")
//

#include "ExpecMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include "TSystem.h"
void ExpecMaker::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).
	
	TString option = GetOption();
	tExpectation_=NULL;
}
void ExpecMaker::SlaveBegin(TTree * /*tree*/)
{
	TString option = GetOption();
	// tree
	tExpectation_ = new TTree("LostLeptonExpectation","a simple Tree with simple variables");

	tExpectation_->Branch("EvtNum",&EvtNum,"EvtNum/i");
	tExpectation_->Branch("HT",&HT,"HT/F");
	tExpectation_->Branch("MHT",&MHT,"MHT/F");
	tExpectation_->Branch("NJets",&NJets,"NJets/s");
	tExpectation_->Branch("BTags",&BTags,"BTags/s");
	tExpectation_->Branch("Leptons",&Leptons,"Leptons/s");
	tExpectation_->Branch("isoTracks",&isoTracks,"isoTracks/s");
	DY=DY_;
	tExpectation_->Branch("DY",&DY,"DY/b");
	tExpectation_->Branch("Bin",&Bin_,"Bin/s");
	tExpectation_->Branch("NVtx",&NVtx,"NVtx/s");
	tExpectation_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	tExpectation_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	tExpectation_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	tExpectation_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	tExpectation_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	tExpectation_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	tExpectation_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	tExpectation_->Branch("Weight", &Weight, "Weight/F");
	tExpectation_->Branch("MET",&METPt,"MET/F");
	tExpectation_->Branch("METPhi",&METPhi,"METPhi/F");
	tExpectation_->Branch("GenMuNum",&GenMuNum,"GenMuNum/s");
	tExpectation_->Branch("GenMuFromTau",GenMu_GenMuFromTau,"GenMuFromTau[GenMuNum]/s");
	tExpectation_->Branch("GenMuDeltaRJet",GenMuDeltaRJet_,"GenMuDeltaRJet[GenMuNum]/F");
	tExpectation_->Branch("GenMuRelPTJet",GenMuRelPTJet_,"GenMuRelPTJet[GenMuNum]/F");
	tExpectation_->Branch("GenMuPt", GenMuPt,"GenMuPt[GenMuNum]/F");
	tExpectation_->Branch("GenMuEta", GenMuEta,"GenMuEta[GenMuNum]/F");
	tExpectation_->Branch("GenMuPhi", GenMuPhi,"GenMuPhi[GenMuNum]/F");
	tExpectation_->Branch("GenMuonIsoTrackMatched", GenMuonIsoTrackMatched, "GenMuonIsoTrackMatched[GenMuNum]/s"); 
	tExpectation_->Branch("GenMuonActivity", GenMuonActivity,"GenMuonActivity[GenMuNum]/F");
	tExpectation_->Branch("GenElecNum",&GenElecNum,"GenElecNum/s");
	tExpectation_->Branch("GenElecFromTau",GenElec_GenElecFromTau,"GenElecFromTau[GenElecNum]/s");
	tExpectation_->Branch("GenElecDeltaRJet",GenElecDeltaRJet_,"GenElecDeltaRJet[GenElecNum]/F");
	tExpectation_->Branch("GenElecRelPTJet",GenElecRelPTJet_,"GenElecRelPTJet[GenElecNum]/F");
	tExpectation_->Branch("GenElecPt", GenElecPt,"GenElecPt[GenElecNum]/F");
	tExpectation_->Branch("GenElecEta", GenElecEta,"GenElecEta[GenElecNum]/F");
	tExpectation_->Branch("GenElecPhi", GenElecPhi,"GenElecPhi[GenElecNum]/F");
	tExpectation_->Branch("GenElecIsoTrackMatched", GenElecIsoTrackMatched, "GenElecIsoTrackMatched[GenElecNum]/s"); 
	tExpectation_->Branch("GenElecActivity", GenElecActivity,"GenElecActivity[GenElecNum]/F");
	tExpectation_->Branch("GenTauNum",&GenTauNum,"GenTauNum/s");
	tExpectation_->Branch("GenTauPt", GenTauPt,"GenTauPt[GenTauNum]/F");
	tExpectation_->Branch("GenTauEta", GenTauEta,"GenTauEta[GenTauNum]/F");
	tExpectation_->Branch("GenTauPhi", GenTauPhi,"GenTauPhi[GenTauNum]/F");
	tExpectation_->Branch("GenTauIsoTrackMatched", GenTauIsoTrackMatched, "GenTauIsoTrackMatched[GenTauNum]/s"); 
	tExpectation_->Branch("GenTauActivity", GenTauActivity,"GenTauActivity[GenTauNum]/F");
	tExpectation_->Branch("Expectation",&Expectation,"Expectation/s");  
	tExpectation_->Branch("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack,"ExpectationReductionIsoTrack/s");
	tExpectation_->Branch("muAcc",&muAcc,"muAcc/s");  
	tExpectation_->Branch("muReco",&muReco,"muReco/s");  
	tExpectation_->Branch("muIso",&muIso,"muIso/s");  
	tExpectation_->Branch("MTW",&mtw,"MTW/F");  
	tExpectation_->Branch("IsoTrackMTW",&isoTrackMTW_,"IsoTrackMTW/F"); 
	tExpectation_->Branch("elecAcc",&elecAcc,"elecAcc/s");  
	tExpectation_->Branch("elecReco",&elecReco,"elecReco/s");  
	tExpectation_->Branch("elecIso",&elecIso,"elecIso/s");  
	tExpectation_->Branch("muIsoTrack",&muIsoTrack,"muIsoTrack/s");  
	tExpectation_->Branch("MuPurity",&MuPurity_,"MuPurity/s"); 
	tExpectation_->Branch("ElecPurity",&ElecPurity_,"ElecPurity/s"); 
	muActivityMethod=muActivityMethod_;
	elecActivityMethod=elecActivityMethod_;
	muIsoTrackActivityMethod=muIsoTrackActivityMethod_;
	elecIsoTrackActivityMethod=elecIsoTrackActivityMethod_;
	pionIsoTrackActivityMethod=pionIsoTrackActivityMethod_;
	tExpectation_->Branch("muActivityMethod",&muActivityMethod,"muActivityMethod/s");  
	tExpectation_->Branch("elecActivityMethod",&elecActivityMethod,"elecActivityMethod/s");  
	tExpectation_->Branch("muIsoTrackActivityMethod",&muIsoTrackActivityMethod,"muIsoTrackActivityMethod/s");
	tExpectation_->Branch("elecIsoTrackActivityMethod",&elecIsoTrackActivityMethod,"elecIsoTrackActivityMethod/s");
	tExpectation_->Branch("pionIsoTrackActivityMethod",&pionIsoTrackActivityMethod,"pionIsoTrackActivityMethod/s");
	tExpectation_->Branch("FallsVetoLep",&FallsVetoLep,"FallsVetoLep/s");
	tExpectation_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum,"selectedIDIsoMuonsNum/s");
	tExpectation_->Branch("selectedIDIsoMuonsPt", selectedIDIsoMuonsPt, "selectedIDIsoMuonsPt[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("muIsoMatched", muIsoMatched, "muIsoMatched[selectedIDIsoMuonsNum]/s");
	tExpectation_->Branch("RecoIsoMuonPromtMatched", RecoIsoMuonPromtMatched, "RecoIsoMuonPromtMatched[selectedIDIsoMuonsNum]/s");
	tExpectation_->Branch("RecoIsoMuonPromtMatchedDeltaR", RecoIsoMuonPromtMatchedDeltaR, "RecoIsoMuonPromtMatchedDeltaR[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("RecoIsoMuonPromtMatchedRelPt", RecoIsoMuonPromtMatchedRelPt, "RecoIsoMuonPromtMatchedRelPt[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("selectedIDIsoMuonsEta", selectedIDIsoMuonsEta, "selectedIDIsoMuonsEta[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("selectedIDIsoMuonsPhi", selectedIDIsoMuonsPhi, "selectedIDIsoMuonsPhi[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("selectedIDIsoMuonsE", selectedIDIsoMuonsE, "selectedIDIsoMuonsE[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("selectedIDIsoMuons_MTW", selectedIDIsoMuons_MTW, "selectedIDIsoMuons_MTW[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("RecoIsoMuonActivity", RecoIsoMuonActivity, "RecoIsoMuonActivity[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("selectedIDMuonsNum",&selectedIDMuonsNum,"selectedIDMuonsNum/s");
	tExpectation_->Branch("selectedIDMuonsPt", selectedIDMuonsPt, "selectedIDMuonsPt[selectedIDMuonsNum]/F");
	tExpectation_->Branch("selectedIDMuonsMatched", muRecoMatched, "selectedIDMuonsMatched[selectedIDMuonsNum]/s");
	tExpectation_->Branch("selectedIDMuonsEta", selectedIDMuonsEta, "selectedIDMuonsEta[selectedIDMuonsNum]/F");
	tExpectation_->Branch("selectedIDMuonsPhi", selectedIDMuonsPhi, "selectedIDMuonsPhi[selectedIDMuonsNum]/F");
	tExpectation_->Branch("selectedIDMuonsE", selectedIDMuonsE, "selectedIDMuonsE[selectedIDMuonsNum]/F");
	tExpectation_->Branch("selectedIDMuons_MTW", selectedIDMuons_MTW, "selectedIDMuons_MTW[selectedIDIsoMuonsNum]/F");
	tExpectation_->Branch("RecoMuonActivity", RecoMuonActivity, "RecoMuonActivity[selectedIDMuonsNum]/F");
	tExpectation_->Branch("RecoIsoMuonIsoTrackMatched", RecoIsoMuonIsoTrackMatched, "RecoIsoMuonIsoTrackMatched[selectedIDIsoMuonsNum]/s");  
	tExpectation_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum,"selectedIDIsoElectronsNum/s");
	tExpectation_->Branch("selectedIDIsoElectronsPt", selectedIDIsoElectronsPt, "selectedIDIsoElectronsPt[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("elecIsoMatched", elecIsoMatched, "elecIsoMatched[selectedIDIsoElectronsNum]/s");
	tExpectation_->Branch("RecoIsoElecPromtMatched", RecoIsoElecPromtMatched, "RecoIsoElecPromtMatched[selectedIDIsoElectronsNum]/s");
	tExpectation_->Branch("RecoIsoElecPromtMatchedDeltaR", RecoIsoElecPromtMatchedDeltaR, "RecoIsoElecPromtMatchedDeltaR[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("RecoIsoElecPromtMatchedRelPt", RecoIsoElecPromtMatchedRelPt, "RecoIsoElecPromtMatchedRelPt[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("selectedIDIsoElectronsEta", selectedIDIsoElectronsEta, "selectedIDIsoElectronsEta[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("selectedIDIsoElectronsPhi", selectedIDIsoElectronsPhi, "selectedIDIsoElectronsPhi[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("selectedIDIsoElectronsE", selectedIDIsoElectronsE, "selectedIDIsoElectronsE[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("selectedIDIsoElectrons_MTW", selectedIDIsoElectrons_MTW, "selectedIDIsoElectrons_MTW[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("RecoIsoElectronActivity", RecoIsoElectronActivity, "RecoIsoElectronActivity[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("RecoIsoElecIsoTrackMatched", RecoIsoElecIsoTrackMatched, "RecoIsoElecIsoTrackMatched[selectedIDIsoElectronsNum]/s");
	tExpectation_->Branch("selectedIDElectronsNum",&selectedIDElectronsNum,"selectedIDElectronsNum/s");
	tExpectation_->Branch("selectedIDElectronsPt", selectedIDElectronsPt, "selectedIDElectronsPt[selectedIDElectronsNum]/F");
	tExpectation_->Branch("selectedIDElectronsMatched", elecRecoMatched, "selectedIDElectronsMatched[selectedIDElectronsNum]/s");
	tExpectation_->Branch("selectedIDElectronsEta", selectedIDElectronsEta, "selectedIDElectronsEta[selectedIDElectronsNum]/F");
	tExpectation_->Branch("selectedIDElectronsPhi", selectedIDElectronsPhi, "selectedIDElectronsPhi[selectedIDElectronsNum]/F");
	tExpectation_->Branch("selectedIDElectronsE", selectedIDElectronsE, "selectedIDElectronsE[selectedIDElectronsNum]/F");
	tExpectation_->Branch("selectedIDElectrons_MTW", selectedIDElectrons_MTW, "selectedIDElectrons_MTW[selectedIDIsoElectronsNum]/F");
	tExpectation_->Branch("RecoElectronActivity", RecoElectronActivity, "RecoElectronActivity[selectedIDElectronsNum]/F");
	
	if(!DY_)
	{
	tExpectation_->Branch("IsolatedElectronTracksVetoNum",&IsolatedElectronTracksVetoNum,"IsolatedElectronTracksVetoNum/s");
	tExpectation_->Branch("IsolatedElectronTracksVetoPt", IsolatedElectronTracksVetoPt, "IsolatedElectronTracksVetoPt[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedElectronTracksVetoEta", IsolatedElectronTracksVetoEta, "IsolatedElectronTracksVetoEta[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedElectronTracksVetoPhi", IsolatedElectronTracksVetoPhi, "IsolatedElectronTracksVetoPhi[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedElectronTracksVetoE", IsolatedElectronTracksVetoE, "IsolatedElectronTracksVetoE[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedElectronTracksVetoActivity", IsolatedElectronTracksVetoActivity, "IsolatedElectronTracksVetoActivity[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedElectronTracksVetoMTW", IsolatedElectronTracksVetoMTW, "IsolatedElectronTracksVetoMTW[IsolatedElectronTracksVetoNum]/F");
	tExpectation_->Branch("muIsoTrackMatchedToGenElec", muIsoTrackMatchedToGenElec, "muIsoTrackMatchedToGenElec[IsolatedElectronTracksVetoNum]/s");
	tExpectation_->Branch("elecIsoTrackMatchedToGenElec", elecIsoTrackMatchedToGenElec, "elecIsoTrackMatchedToGenElec[IsolatedElectronTracksVetoNum]/s");
	tExpectation_->Branch("pionIsoTrackMatchedToGenElec", pionIsoTrackMatchedToGenElec, "pionIsoTrackMatchedToGenElec[IsolatedElectronTracksVetoNum]/s");
	
	tExpectation_->Branch("IsolatedMuonTracksVetoNum",&IsolatedMuonTracksVetoNum,"IsolatedMuonTracksVetoNum/s");
	tExpectation_->Branch("IsolatedMuonTracksVetoPt", IsolatedMuonTracksVetoPt, "IsolatedMuonTracksVetoPt[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedMuonTracksVetoEta", IsolatedMuonTracksVetoEta, "IsolatedMuonTracksVetoEta[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedMuonTracksVetoPhi", IsolatedMuonTracksVetoPhi, "IsolatedMuonTracksVetoPhi[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedMuonTracksVetoE", IsolatedMuonTracksVetoE, "IsolatedMuonTracksVetoE[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedMuonTracksVetoActivity", IsolatedMuonTracksVetoActivity, "IsolatedMuonTracksVetoActivity[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedMuonTracksVetoMTW", IsolatedMuonTracksVetoMTW, "IsolatedMuonTracksVetoMTW[IsolatedMuonTracksVetoNum]/F");
	tExpectation_->Branch("muIsoTrackMatchedToGenMu", muIsoTrackMatchedToGenMu, "muIsoTrackMatchedToGenMu[IsolatedMuonTracksVetoNum]/s");
	tExpectation_->Branch("elecIsoTrackMatchedToGenMu", elecIsoTrackMatchedToGenMu, "elecIsoTrackMatchedToGenMu[IsolatedMuonTracksVetoNum]/s");
	tExpectation_->Branch("pionIsoTrackMatchedToGenMu", pionIsoTrackMatchedToGenMu, "pionIsoTrackMatchedToGenMu[IsolatedMuonTracksVetoNum]/s");
	tExpectation_->Branch("IsolatedPionTracksVetoNum",&IsolatedPionTracksVetoNum,"IsolatedPionTracksVetoNum/s");
	tExpectation_->Branch("IsolatedPionTracksVetoPt", IsolatedPionTracksVetoPt, "IsolatedPionTracksVetoPt[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedPionTracksVetoEta", IsolatedPionTracksVetoEta, "IsolatedPionTracksVetoEta[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedPionTracksVetoPhi", IsolatedPionTracksVetoPhi, "IsolatedPionTracksVetoPhi[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedPionTracksVetoE", IsolatedPionTracksVetoE, "IsolatedPionTracksVetoE[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedPionTracksVetoActivity", IsolatedPionTracksVetoActivity, "IsolatedPionTracksVetoActivity[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("IsolatedPionTracksVetoMTW", IsolatedPionTracksVetoMTW, "IsolatedPionTracksVetoMTW[IsolatedPionTracksVetoNum]/F");
	tExpectation_->Branch("muIsoTrackMatchedToGenSingleProngTau", muIsoTrackMatchedToGenSingleProngTau, "muIsoTrackMatchedToGenSingleProngTau[IsolatedPionTracksVetoNum]/s");
	tExpectation_->Branch("elecIsoTrackMatchedToGenSingleProngTau", elecIsoTrackMatchedToGenSingleProngTau, "elecIsoTrackMatchedToGenSingleProngTau[IsolatedPionTracksVetoNum]/s");
	tExpectation_->Branch("pionIsoTrackMatchedToGenSingleProngTau", pionIsoTrackMatchedToGenSingleProngTau, "pionIsoTrackMatchedToGenSingleProngTau[IsolatedPionTracksVetoNum]/s");
	
	
	tExpectation_->Branch("JetsNum",&JetsNum,"JetsNum/s");
	tExpectation_->Branch("JetsPt", JetsPt, "JetsPt[JetsNum]/F");
	tExpectation_->Branch("JetsEta", JetsEta, "JetsEta[JetsNum]/F");
	tExpectation_->Branch("JetsPhi", JetsPhi, "JetsPhi[JetsNum]/F");
	tExpectation_->Branch("JetsE", JetsE, "JetsE[JetsNum]/F");
	tExpectation_->Branch("Jets_bDiscriminator", Jets_bDiscriminator, "Jets_bDiscriminator[JetsNum]/F");
	tExpectation_->Branch("Jets_chargedEmEnergyFraction", Jets_chargedEmEnergyFraction, "Jets_chargedEmEnergyFraction[JetsNum]/F");
	tExpectation_->Branch("Jets_chargedHadronEnergyFraction", Jets_chargedHadronEnergyFraction, "Jets_chargedHadronEnergyFraction[JetsNum]/F");
	tExpectation_->Branch("Jets_chargedHadronMultiplicity", Jets_chargedHadronMultiplicity, "Jets_chargedHadronMultiplicity[JetsNum]/I");
	tExpectation_->Branch("Jets_electronMultiplicity", Jets_electronMultiplicity, "Jets_electronMultiplicity[JetsNum]/I");
	tExpectation_->Branch("Jets_jetArea", Jets_jetArea, "Jets_jetArea[JetsNum]/F");
	tExpectation_->Branch("Jets_muonEnergyFraction", Jets_muonEnergyFraction, "Jets_muonEnergyFraction[JetsNum]/F");
	tExpectation_->Branch("Jets_muonMultiplicity", Jets_muonMultiplicity, "Jets_muonMultiplicity[JetsNum]/I");
	tExpectation_->Branch("Jets_neutralEmEnergyFraction", Jets_neutralEmEnergyFraction, "Jets_neutralEmEnergyFraction[JetsNum]/F");
	tExpectation_->Branch("Jets_neutralHadronMultiplicity", Jets_neutralHadronMultiplicity, "Jets_neutralHadronMultiplicity[JetsNum]/I");
	tExpectation_->Branch("Jets_photonEnergyFraction", Jets_photonEnergyFraction, "Jets_photonEnergyFraction[JetsNum]/F");
	tExpectation_->Branch("Jets_photonMultiplicity", Jets_photonMultiplicity, "Jets_photonMultiplicity[JetsNum]/I");
	// di lep contribution
	tExpectation_->Branch("ExpectationDiLep",&ExpectationDiLep_,"ExpectationDiLep/s");
	tExpectation_->Branch("MuDiLepControlSample",&MuDiLepControlSample_,"MuDiLepControlSample/s");
	tExpectation_->Branch("ElecDiLepControlSample",&ElecDiLepControlSample_,"ElecDiLepControlSample/s");
	// stand alone isotrack prediction code  
	tExpectation_->Branch("StandAloneGenMuIsoTrackMatched",&StandAloneGenMuIsoTrackMatched_,"StandAloneGenMuIsoTrackMatched/s");
	tExpectation_->Branch("StandAloneIsoTrackToMuMatched",&StandAloneIsoTrackToMuMatched_,"StandAloneIsoTrackToMuMatched/s");
	tExpectation_->Branch("StandAloneGenElecIsoTrackMatched",&StandAloneGenElecIsoTrackMatched_,"StandAloneGenElecIsoTrackMatched/s");
	tExpectation_->Branch("StandAloneIsoTrackToElecMatched",&StandAloneIsoTrackToElecMatched_,"StandAloneIsoTrackToElecMatched/s");
	tExpectation_->Branch("StandAloneIsoTrackToRecoMuMatched",&StandAloneIsoTrackToRecoMuMatched_,"StandAloneIsoTrackToRecoMuMatched/s");
	tExpectation_->Branch("StandAloneIsoTrackToRecoElecMatched",&StandAloneIsoTrackToRecoElecMatched_,"StandAloneIsoTrackToRecoElecMatched/s");
	tExpectation_->Branch("IsoTrackDiLepControlSampleMu",&IsoTrackDiLepControlSampleMu_,"IsoTrackDiLepControlSampleMu/s");
	tExpectation_->Branch("IsoTrackDiLepControlSampleElec",&IsoTrackDiLepControlSampleElec_,"IsoTrackDiLepControlSampleElec/s"); 
	tExpectation_->Branch("IsoTrackDiLepMu",&IsoTrackDiLepMu_,"IsoTrackDiLepMu/s");
	tExpectation_->Branch("IsoTrackDiLepElec",&IsoTrackDiLepElec_,"IsoTrackDiLepElec/s");
	//   tExpectation_->Branch("maxDeltaRMuActivity",&maxDeltaRMuActivity_,"maxDeltaRMuActivity/F");
	//   tExpectation_->Branch("maxDeltaRElecActivity",&maxDeltaRElecActivity_,"maxDeltaRElecActivity/F");
	}
	// w pt spectrum extrapolation studies
	tExpectation_->Branch("GenMuWPt",&GenMuWPt_,"GenMuWPt/F");
	tExpectation_->Branch("GenMuWPhi",&GenMuWPhi_,"GenMuWPhi/F");
	tExpectation_->Branch("GenElecWPt",&GenElecWPt_,"GenElecWPt/F");
	tExpectation_->Branch("GenElecWPhi",&GenElecWPhi_,"GenElecWPhi/F");
	tExpectation_->Branch("GenBosonNum",&GenBosonNum,"GenBosonNum/s");
	tExpectation_->Branch("GenBosonPt", GenBosonPt, "GenBosonPt[GenBosonNum]/F");
	tExpectation_->Branch("GenBosonPhi", GenBosonPhi, "GenBosonPhi[GenBosonNum]/F");
	
	GetOutputList()->Add(tExpectation_);
	
	SearchBins_ = new SearchBins();
	std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
}
Bool_t ExpecMaker::Process(Long64_t entry)
{
	resetValues();
	fChain->GetTree()->GetEntry(entry);
	
	if(!DY_ && (HT<minHT_ || MHT< minMHT_ || NJets < minNJets_)) return kTRUE;
  	if(DY_ && ( HT<minHT_ || NJets < minNJets_) ) return kTRUE;	
 	if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ ) return kTRUE;
//	if(!DY_) if(minDeltaPhiN<minDeltaPhiN_) return kTRUE;

	if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

	Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
	isoTracks = IsolatedMuonTracksVetoNum + IsolatedPionTracksVetoNum + IsolatedElectronTracksVetoNum;
	
	// compute efficiencies 1 lepton
	if( (GenMuNum==1 && GenElecNum==0) || (DY_ && GenMuNum==2) )
	{
		// compute W pt from gen lepton and reco MET
		GenMuWPt_ = GenMuPt[0] + MHT * deltaR(0,METPhi,0,GenMuPhi[0]);
		
		if ( GenMuPt[0] < minMuPt_ || std::abs(GenMuEta[0]) > maxMuEta_)
		{
			muAcc=0;
			Expectation=1;
			// efficiency studies TH1 and so on
		}
		else
		{
			muAcc=2;
			bool RecoNotMatched=true;
			// efficiency studies TH1 and so on
			
			for (UShort_t i=0; i<selectedIDMuonsNum; i++)
			{
				//std::cout<<"selectedIDMuonsNum["<<i<<"] started"<<std::endl;
				if(deltaR(GenMuEta[0],GenMuPhi[0],selectedIDMuonsEta[i],selectedIDMuonsPhi[i])<maxDeltaRGenToRecoMu_ && std::abs(GenMuPt[0]-selectedIDMuonsPt[i])/GenMuPt[0] <maxDiffPtGenToRecoMu_)
				{
					// std::cout<<"selectedIDMuonsNum["<<i<<"] started"<<std::endl;
					RecoNotMatched=false;
					// efficiency studies TH1 and so on
					
					muReco =2;
					muRecoMatched[i]=1;
					bool IsoNotMatched=true;
					for (UShort_t ii=0; ii < selectedIDIsoMuonsNum; ii++)
					{
						if(deltaR(selectedIDIsoMuonsEta[ii],selectedIDIsoMuonsPhi[ii],selectedIDMuonsEta[i],selectedIDMuonsPhi[i])<maxDeltaRRecoToIsoMu_ && std::abs(selectedIDIsoMuonsPt[ii]-selectedIDMuonsPt[i])/selectedIDIsoMuonsPt[ii] <maxDiffPtRecoToIsoMu_)
						{
							IsoNotMatched=false;
							// efficiency studies TH1 and so on
							muIso=2;
							muIsoMatched[ii]=1;
							Expectation=2;
							if(!DY_)mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuonsPt[ii], selectedIDIsoMuonsPhi[ii]);
							MuDiLepControlSample_=2;
						}
						else 
						{
							muIsoMatched[ii]=0;
						}
					}
					if(IsoNotMatched)
					{
						muIso=0;
						Expectation=1;
						
					}
				}
				else 
				{
					muRecoMatched[i]=0;
				}
			}
			if(RecoNotMatched)
			{
				muReco=0;
				Expectation=1;
				
			}
		}
	} 
	// analyse gen electrons consider only single elec events
	if( (GenMuNum==0 && GenElecNum==1) || (DY_ && GenElecNum==2) )
	{
		// compute W pt from gen lepton and reco MET
		GenElecWPt_ = GenElecPt[0] + MHT * deltaR(0,METPhi,0,GenElecPhi[0]);
		if ( GenElecPt[0] < minElecPt_ || std::abs(GenElecEta[0]) > maxElecEta_)
		{
			elecAcc=0;
			Expectation=1;
		}
		else
		{
			elecAcc=2;
			bool RecoNotMatched=true;

			RecoNotMatched=true;
			// efficiency studies TH1 and so on
			for (UShort_t i=0; i<selectedIDElectronsNum; i++)
			{
				//std::cout<<"selectedIDElectronsNum["<<i<<"] started"<<std::endl;
				if(deltaR(GenElecEta[0],GenElecPhi[0],selectedIDElectronsEta[i],selectedIDElectronsPhi[i])<maxDeltaRGenToRecoElec_ && std::abs(GenElecPt[0]-selectedIDElectronsPt[i])/GenElecPt[0] <maxDiffPtGenToRecoElec_)
				{
					// std::cout<<"selectedIDElectronsNum["<<i<<"] started"<<std::endl;
					RecoNotMatched=false;
					elecReco =2;
					elecRecoMatched[i]=1;
					bool IsoNotMatched=true;
					for (UShort_t ii=0; ii < selectedIDIsoElectronsNum; ii++)
					{
						if(deltaR(selectedIDIsoElectronsEta[ii],selectedIDIsoElectronsPhi[ii],selectedIDElectronsEta[i],selectedIDElectronsPhi[i])<maxDeltaRRecoToIsoElec_ && std::abs(selectedIDIsoElectronsPt[ii]-selectedIDElectronsPt[i])/selectedIDIsoElectronsPt[ii] <maxDiffPtRecoToIsoElec_)
						{
							IsoNotMatched=false;
							elecIso=2;
							elecIsoMatched[ii]=1;
							Expectation=2;
							if(!DY_) mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectronsPt[ii], selectedIDIsoElectronsPhi[ii]);
							ElecDiLepControlSample_=2;
						}
						else 
						{
							elecIsoMatched[ii]=0;
						}
					}
					if(IsoNotMatched)
					{
						elecIso=0;
						Expectation=1;
						
					}
				}
				else 
				{
					elecRecoMatched[i]=0;
				}
			}
			if(RecoNotMatched)
			{
				elecReco=0;
				Expectation=1;
				
				// efficiency studies TH1 and so on
			}
		}
	} 
	// loop over all reco iso gen leptons and isotrack for specific variable calculations
	for(unsigned int i=0; i< GenMuNum;i++)
	{
		GenMuonActivity[i]=MuActivity(GenMuEta[i],GenMuPhi[i],muActivityMethod_);
		//std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMuPt[i],GenMuEta[i],GenMuPhi[i]);
		std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMuPt[i],GenMuEta[i],GenMuPhi[i]);
		GenMuDeltaRJet_[i]=DeltaR_relPT.first;
		GenMuRelPTJet_[i]=DeltaR_relPT.second;
	}
	for(unsigned int i=0; i< selectedIDMuonsNum;i++)
	{
		RecoMuonActivity[i]=MuActivity(selectedIDMuonsEta[i],selectedIDMuonsPhi[i],muActivityMethod_);
	}
	for(unsigned int i=0; i< selectedIDIsoMuonsNum;i++)
	{
		RecoIsoMuonActivity[i]=MuActivity(selectedIDIsoMuonsEta[i],selectedIDIsoMuonsPhi[i],muActivityMethod_);
	}
	for(unsigned int i=0; i< GenElecNum;i++)
	{
		GenElecActivity[i]=ElecActivity(GenElecEta[i],GenElecPhi[i],elecActivityMethod_);
		//std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenElecPt[i],GenElecEta[i],GenElecPhi[i]);
		std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenElecPt[i],GenElecEta[i],GenElecPhi[i]);
		GenElecDeltaRJet_[i]=DeltaR_relPT.first;
		GenElecRelPTJet_[i]=DeltaR_relPT.second;
	}
	for(unsigned int i=0; i< selectedIDElectronsNum;i++)
	{
		RecoElectronActivity[i]=ElecActivity(selectedIDElectronsEta[i],selectedIDElectronsPhi[i],elecActivityMethod_);
	}
	for(unsigned int i=0; i< selectedIDIsoElectronsNum;i++)
	{
		RecoIsoElectronActivity[i]=ElecActivity(selectedIDIsoElectronsEta[i],selectedIDIsoElectronsPhi[i],elecActivityMethod_);
	}
 	if(DY_)
 	{
 		tExpectation_->Fill();
 		return kTRUE;
 	}
// di leptonic events
	if( (GenMuNum+GenElecNum)==2)
	{
		if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==0)
		{
			Expectation=1;
			ExpectationDiLep_=1;
		}
		if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0)
		{
			mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuonsPt[0], selectedIDIsoMuonsPhi[0]);
			MuDiLepControlSample_=0;
		}
		if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
		{
			ElecDiLepControlSample_=0;
			mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectronsPt[0], selectedIDIsoElectronsPhi[0]);
		}
	}
	// isotrack
	if(GenMuNum==1 && GenElecNum==0)
	{
		
		for(unsigned int i=0; i< IsolatedMuonTracksVetoNum; i++)
		{
			if(deltaR(GenMuEta[0],GenMuPhi[0],IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i])<maxDeltaRGenMuToTack_ && std::abs(GenMuPt[0]-IsolatedMuonTracksVetoPt[i])/GenMuPt[0] <maxDiffPtGenMuToTack_)
			{
				muIsoTrackMatchedToGenMu[i]=1;
				IsolatedMuonTracksVetoActivity[i]=MuActivity(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],muIsoTrackActivityMethod_);
				IsolatedMuonTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedMuonTracksVetoPt[i], IsolatedMuonTracksVetoPhi[i]);
			}
		}
		for(unsigned int i=0; i< IsolatedElectronTracksVetoNum;i++)
		{
			if(deltaR(GenMuEta[0],GenMuPhi[0],IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i])<maxDeltaRGenMuToTack_ && std::abs(GenMuPt[0]-IsolatedElectronTracksVetoPt[i])/GenMuPt[0] <maxDiffPtGenMuToTack_)
			{
				elecIsoTrackMatchedToGenMu[i]=1;
				IsolatedElectronTracksVetoActivity[i]=ElecActivity(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],elecIsoTrackActivityMethod_);
				IsolatedElectronTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedElectronTracksVetoPt[i], IsolatedElectronTracksVetoPhi[i]);
			}
		}
		for(unsigned int i=0; i< IsolatedPionTracksVetoNum;i++)
		{
			if(deltaR(GenMuEta[0],GenMuPhi[0],IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i])<maxDeltaRGenMuToTack_ && std::abs(GenMuPt[0]-IsolatedPionTracksVetoPt[i])/GenMuPt[0] <maxDiffPtGenMuToTack_)
			{
				pionIsoTrackMatchedToGenMu[i]=1;
				IsolatedElectronTracksVetoActivity[i]=PionActivity(IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i],pionIsoTrackActivityMethod_);
				IsolatedPionTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedPionTracksVetoPt[i], IsolatedPionTracksVetoPhi[i]);
			}
		}
	}
	if(GenElecNum==1 && GenMuNum==0)
	{
		
		for(unsigned int i=0; i< IsolatedMuonTracksVetoNum; i++)
		{
			if(deltaR(GenElecEta[0],GenElecPhi[0],IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i])<maxDeltaRGenElecToTack_ && std::abs(GenElecPt[0]-IsolatedMuonTracksVetoPt[i])/GenElecPt[0] <maxDiffPtGenElecToTack_)
			{
				muIsoTrackMatchedToGenElec[i]=1;
				IsolatedMuonTracksVetoActivity[i]=MuActivity(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],muIsoTrackActivityMethod_);
				IsolatedMuonTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedMuonTracksVetoPt[i], IsolatedMuonTracksVetoPhi[i]);		
			}
		}
		for(unsigned int i=0; i< IsolatedElectronTracksVetoNum;i++)
		{
			if(deltaR(GenElecEta[0],GenElecPhi[0],IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i])<maxDeltaRGenElecToTack_ && std::abs(GenElecPt[0]-IsolatedElectronTracksVetoPt[i])/GenElecPt[0] <maxDiffPtGenElecToTack_)
			{
				elecIsoTrackMatchedToGenElec[i]=1;
				IsolatedElectronTracksVetoActivity[i]=ElecActivity(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],elecIsoTrackActivityMethod_);
				IsolatedElectronTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedElectronTracksVetoPt[i], IsolatedElectronTracksVetoPhi[i]);		
			}
		}
		for(unsigned int i=0; i< IsolatedPionTracksVetoNum;i++)
		{
			if(deltaR(GenElecEta[0],GenElecPhi[0],IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i])<maxDeltaRGenElecToTack_ && std::abs(GenElecPt[0]-IsolatedPionTracksVetoPt[i])/GenElecPt[0] <maxDiffPtGenElecToTack_)
			{
				pionIsoTrackMatchedToGenElec[i]=1;
				IsolatedElectronTracksVetoActivity[i]=PionActivity(IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i],pionIsoTrackActivityMethod_);
				IsolatedPionTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedPionTracksVetoPt[i], IsolatedPionTracksVetoPhi[i]);		
				
			}
		}
	}
	
	if(GenElecNum==0 && GenMuNum==0 && GenTauNum==1)
	{
		
		for(unsigned int i=0; i< IsolatedMuonTracksVetoNum; i++)
		{
			if(deltaR(GenTauEta[0],GenTauPhi[0],IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i])<maxDeltaRGenTauToTack_ && std::abs(GenTauPt[0]-IsolatedMuonTracksVetoPt[i])/GenTauPt[0] <maxDiffPtGenTauToTack_)
			{
				muIsoTrackMatchedToGenSingleProngTau[i]=1;
				IsolatedMuonTracksVetoActivity[i]=MuActivity(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],muIsoTrackActivityMethod_);
				IsolatedMuonTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedMuonTracksVetoPt[i], IsolatedMuonTracksVetoPhi[i]);
			}
		}
		for(unsigned int i=0; i< IsolatedElectronTracksVetoNum;i++)
		{
			if(deltaR(GenTauEta[0],GenTauPhi[0],IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i])<maxDeltaRGenTauToTack_ && std::abs(GenTauPt[0]-IsolatedElectronTracksVetoPt[i])/GenTauPt[0] <maxDiffPtGenTauToTack_)
			{
				elecIsoTrackMatchedToGenSingleProngTau[i]=1;
				IsolatedElectronTracksVetoActivity[i]=ElecActivity(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],elecIsoTrackActivityMethod_);
				IsolatedElectronTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedElectronTracksVetoPt[i], IsolatedElectronTracksVetoPhi[i]);
			}
		}
		for(unsigned int i=0; i< IsolatedPionTracksVetoNum;i++)
		{
			if(deltaR(GenTauEta[0],GenTauPhi[0],IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i])<maxDeltaRGenTauToTack_ && std::abs(GenTauPt[0]-IsolatedPionTracksVetoPt[i])/GenTauPt[0] <maxDiffPtGenTauToTack_)
			{
				pionIsoTrackMatchedToGenSingleProngTau[i]=1;
				IsolatedElectronTracksVetoActivity[i]=PionActivity(IsolatedPionTracksVetoEta[i],IsolatedPionTracksVetoPhi[i],pionIsoTrackActivityMethod_);
				IsolatedPionTracksVetoMTW[i]= MTWCalculator(METPt,METPhi, IsolatedPionTracksVetoPt[i], IsolatedPionTracksVetoPhi[i]);	
			}
		}
	}
	// ************************************************************************************************************* 22 June 2015 end****************************************************
	// purity studies:
	// new purity studies
	if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0 && (GenMuNum+ GenElecNum)<2)
	{
// 	  if(muIso!=2)
	    if(GenMuNum<1)
	  {
	    MuPurity_=0;
	  }
	  else MuPurity_=2;
	}
	if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1 && (GenMuNum+ GenElecNum)<2)
	{
// 	  if(elecIso!=2)
	    if(GenElecNum<1)
	  {
	    ElecPurity_=0;
	  }
	  else ElecPurity_=2;
	}
	//old purity calculations
	for (UShort_t i=0; i< selectedIDIsoMuonsNum;i++)
	{
		if(selectedIDIsoMuonsNum>1 || MTWCalculator(METPt,METPhi, selectedIDIsoMuonsPt[0], selectedIDIsoMuonsPhi[0])>mtwCut_) break;
		bool matched=false;
		for(UShort_t ii=0; ii<GenMuNum;ii++)
		{
			if(deltaR(selectedIDIsoMuonsEta[i],selectedIDIsoMuonsPhi[i],GenMuEta[ii],GenMuPhi[ii])<RecoIsoMuonPromtMatchedDeltaR[i])RecoIsoMuonPromtMatchedDeltaR[i]=deltaR(selectedIDIsoMuonsEta[i],selectedIDIsoMuonsPhi[i],GenMuEta[ii],GenMuPhi[ii]);
			if(std::abs(selectedIDIsoMuonsPt[i]-GenMuPt[ii])/selectedIDIsoMuonsPt[i] < std::abs(RecoIsoMuonPromtMatchedRelPt[i]) )RecoIsoMuonPromtMatchedRelPt[i]=(selectedIDIsoMuonsPt[i]-GenMuPt[ii])/selectedIDIsoMuonsPt[i];
			if(deltaR(selectedIDIsoMuonsEta[i],selectedIDIsoMuonsPhi[i],GenMuEta[ii],GenMuPhi[ii])<maxDeltaRIsoToGenMu_ && std::abs(selectedIDIsoMuonsPt[i]-GenMuPt[ii])/selectedIDIsoMuonsPt[i] <maxDiffPtIsoToGenMu_)
			{
				RecoIsoMuonPromtMatched[i]=1;
				matched=true;
			}
		}
		if(!matched)
		{
			RecoIsoMuonPromtMatched[i]=0;
		}
		if(GenMuNum==0)
		{
			RecoIsoMuonPromtMatchedDeltaR[i]=-1;
			RecoIsoMuonPromtMatchedRelPt[i]=-100;
		}
	}
	for (UShort_t i=0; i< selectedIDIsoElectronsNum;i++)
	{
		if(selectedIDIsoElectronsNum>1 || MTWCalculator(METPt,METPhi, selectedIDIsoElectronsPt[0], selectedIDIsoElectronsPhi[0])>mtwCut_) break;
		bool matched=false;
		for(UShort_t ii=0; ii<GenElecNum;ii++)
		{
			if(deltaR(selectedIDIsoElectronsEta[i],selectedIDIsoElectronsPhi[i],GenElecEta[ii],GenElecPhi[ii])<RecoIsoElecPromtMatchedDeltaR[i])RecoIsoElecPromtMatchedDeltaR[i]=deltaR(selectedIDIsoElectronsEta[i],selectedIDIsoElectronsPhi[i],GenElecEta[ii],GenElecPhi[ii]);
			if(std::abs(selectedIDIsoElectronsPt[i]-GenElecPt[ii])/selectedIDIsoElectronsPt[i] < std::abs(RecoIsoElecPromtMatchedRelPt[i]) )RecoIsoElecPromtMatchedRelPt[i]=(selectedIDIsoElectronsPt[i]-GenElecPt[ii])/selectedIDIsoElectronsPt[i];
			if(deltaR(selectedIDIsoElectronsEta[i],selectedIDIsoElectronsPhi[i],GenElecEta[ii],GenElecPhi[ii])<maxDeltaRIsoToGenElec_ && std::abs(selectedIDIsoElectronsPt[i]-GenElecPt[ii])/selectedIDIsoElectronsPt[i] <maxDiffPtIsoToGenElec_)
			{
				RecoIsoElecPromtMatched[i]=1;
				matched=true;
			}
		}
		if(!matched)
		{
			RecoIsoElecPromtMatched[i]=0;
		}
		if(GenElecNum==0)
		{
			RecoIsoElecPromtMatchedDeltaR[i]=-1;
			RecoIsoElecPromtMatchedRelPt[i]=-100;
		}
	}
	// check if false lepton veto will be applied
	int temp=0;
	for(unsigned int i=0; i< selectedIDIsoElectronsNum;i++)
	{
		if(RecoIsoElecPromtMatched[i]==0)temp=1;
	}
	for(unsigned int i=0; i< selectedIDIsoMuonsNum;i++)
	{
		if(RecoIsoMuonPromtMatched[i]==0)temp=1;
	}
	if(temp==1)FallsVetoLep=1;
	
	// new version for stand alone iso track
	// go for single lepton decay first
	if(GenMuNum==1 && GenElecNum==0)
	{
		bool IsoTrackNotMached=true;
		for (unsigned int i=0; i < IsolatedMuonTracksVetoNum; i++)
		{
			if( deltaR(GenMuEta[0],GenMuPhi[0],IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i])<maxDeltaRGenToRecoIsoTrack_ && std::abs(GenMuPt[0]-IsolatedMuonTracksVetoPt[i])/GenMuPt[0] <maxDiffPtGenToRecoIsoTrack_) 
			{
				IsoTrackNotMached=false;
				StandAloneGenMuIsoTrackMatched_++;
				bool IsoTrackIsoMuonNotMachted=true;
				for (unsigned int ii=0; ii < selectedIDIsoMuonsNum;ii++)
				{
					if(deltaR(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],selectedIDIsoMuonsEta[ii],selectedIDIsoMuonsPhi[ii])<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedMuonTracksVetoPt[i]-selectedIDIsoMuonsPt[ii])/IsolatedMuonTracksVetoPt[i] <maxDiffPtIsoTrackToMu_)
					{
						IsoTrackIsoMuonNotMachted=false;
						StandAloneIsoTrackToMuMatched_++;
						IsoTrackDiLepControlSampleMu_++;
					}
				}
				if(IsoTrackIsoMuonNotMachted)
				{
					StandAloneIsoTrackToMuMatched_=0;
				}
				bool IsoTrackRecoMuonNotMatched=true;
				bool IsoTrackRecoElecNotMatched=true;
				if(IsoTrackIsoMuonNotMachted)
				{
					for (unsigned int ii=0; ii< selectedIDMuonsNum;ii++)
					{
						if(deltaR(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],selectedIDMuonsEta[ii],selectedIDMuonsPhi[ii])<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedMuonTracksVetoPt[i]-selectedIDMuonsPt[ii])/IsolatedMuonTracksVetoPt[i] <maxDiffPtIsoTrackToMu_)
						{
							IsoTrackRecoMuonNotMatched=false;
							StandAloneIsoTrackToRecoMuMatched_++;
							IsoTrackDiLepControlSampleMu_++;
						}
					}
					for (unsigned int ii=0; ii< selectedIDElectronsNum;ii++)
					{
						if(deltaR(IsolatedMuonTracksVetoEta[i],IsolatedMuonTracksVetoPhi[i],selectedIDElectronsEta[ii],selectedIDElectronsPhi[ii])<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedMuonTracksVetoPt[i]-selectedIDElectronsPt[ii])/IsolatedMuonTracksVetoPt[i] <maxDiffPtIsoTrackToElec_)
						{
							IsoTrackRecoElecNotMatched=false;
							StandAloneIsoTrackToRecoElecMatched_++;
							IsoTrackDiLepControlSampleElec_++;
						}
					}
					if(IsoTrackRecoMuonNotMatched)
					{
						StandAloneIsoTrackToRecoMuMatched_=0;
					}
					if(IsoTrackRecoElecNotMatched)
					{
						StandAloneIsoTrackToRecoElecMatched_=0;
					}
				}
			}
		}
		if(IsoTrackNotMached)
		{
			StandAloneGenMuIsoTrackMatched_=0;
		}
	}
	// single gen electron
	if(GenMuNum==0 && GenElecNum==1)
	{
		bool IsoTrackNotMached=true;
		for (unsigned int i=0; i < IsolatedElectronTracksVetoNum; i++)
		{
			if(deltaR(GenElecEta[0],GenElecPhi[0],IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i])<maxDeltaRGenToRecoIsoTrack_ && std::abs(GenElecPt[0]-IsolatedElectronTracksVetoPt[i])/GenElecPt[0] <maxDiffPtGenToRecoIsoTrack_)
			{
				IsoTrackNotMached=false;
				StandAloneGenElecIsoTrackMatched_++;
				bool IsoTrackIsoEleconNotMachted=true;
				for (unsigned int ii=0; ii < selectedIDIsoElectronsNum;ii++)
				{
					if(deltaR(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],selectedIDIsoElectronsEta[ii],selectedIDIsoElectronsPhi[ii])<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedElectronTracksVetoPt[i]-selectedIDIsoElectronsPt[ii])/IsolatedElectronTracksVetoPt[i] <maxDiffPtIsoTrackToElec_)
					{
						IsoTrackIsoEleconNotMachted=false;
						StandAloneIsoTrackToElecMatched_++;
						IsoTrackDiLepControlSampleElec_++;
					}
				}
				if(IsoTrackIsoEleconNotMachted)
				{
					StandAloneIsoTrackToElecMatched_=0;
				}
				bool IsoTrackRecoMuonNotMatched=true;
				bool IsoTrackRecoElecNotMatched=true;
				if(IsoTrackIsoEleconNotMachted)
				{
					for (unsigned int ii=0; ii< selectedIDMuonsNum;ii++)
					{
						if(deltaR(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],selectedIDMuonsEta[ii],selectedIDMuonsPhi[ii])<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedElectronTracksVetoPt[i]-selectedIDMuonsPt[ii])/IsolatedElectronTracksVetoPt[i] <maxDiffPtIsoTrackToMu_)
						{
							IsoTrackRecoMuonNotMatched=false;
							StandAloneIsoTrackToRecoMuMatched_++;
							IsoTrackDiLepControlSampleElec_++;
						}
					}
					for (unsigned int ii=0; ii< selectedIDElectronsNum;ii++)
					{
						if(deltaR(IsolatedElectronTracksVetoEta[i],IsolatedElectronTracksVetoPhi[i],selectedIDElectronsEta[ii],selectedIDElectronsPhi[ii])<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedElectronTracksVetoPt[i]-selectedIDElectronsPt[ii])/IsolatedElectronTracksVetoPt[i] <maxDiffPtIsoTrackToElec_)
						{
							IsoTrackRecoElecNotMatched=false;
							StandAloneIsoTrackToRecoElecMatched_++;
							IsoTrackDiLepControlSampleElec_++;
						}
					}
					if(IsoTrackRecoMuonNotMatched)
					{
						StandAloneIsoTrackToRecoMuMatched_=0;
					}
					if(IsoTrackRecoElecNotMatched)
					{
						StandAloneIsoTrackToRecoElecMatched_=0;
					}
				}
			}
		}
		if(IsoTrackNotMached)
		{
			StandAloneGenElecIsoTrackMatched_=0;
		}
	}
	
	// check weather a background event according to plane lepton veto gets rejected by the isolated track veto with MT cut applied
	if(isoTracks>=1 && Expectation==1)
	{
		ExpectationReductionIsoTrack=1;
	}
	tExpectation_->Fill();
	return kTRUE;
}

void ExpecMaker::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
	
}
void ExpecMaker::Terminate()
{
	GetOutputList()->Print();
	std::cout << "tExpectation_:" << tExpectation_ << '\n';
	tExpectation_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonExpectation"));
	std::cout << "tExpectation_:" << tExpectation_ << '\n';
	
	TFile *outPutFile = new TFile("Expectation.root","RECREATE"); 
	outPutFile->cd();
	tExpectation_->Write();
	
	outPutFile->Close();
	
}
void ExpecMaker::resetValues()
{
	isoTrackMTW_=-5;
	Expectation=0;
	ExpectationReductionIsoTrack=0;
	muIso =1;
	muIsoTrack=1;
	muIsoTrackMTW=1;
	muReco =1;
	muAcc =1;
	muMTW =1;
	muTotal=1;
	elecIso =1;
	elecReco =1;
	elecAcc =1;
	elecTotal=1;
	elecMTW=1;
	FallsVetoLep=0;
	FallsVetoIsoTrack=0;
	FallsVetoIsoTrackPT10=0;
	FallsVetoIsoTrackPT10IsoCut08=0;
	FallsVetoIsoTrackPT10IsoCut12=0;
	// di lep
	ExpectationDiLep_=0;
	MuDiLepControlSample_=1;
	ElecDiLepControlSample_=1;
	// new purity
	MuPurity_=1;
	ElecPurity_=1;
	
	//stand alone isolatedtrack studies
	StandAloneGenMuIsoTrackMatched_=1;
	StandAloneIsoTrackToMuMatched_=1;
	StandAloneGenElecIsoTrackMatched_=1;
	StandAloneIsoTrackToElecMatched_=1;
	StandAloneIsoTrackToRecoMuMatched_=1;
	StandAloneIsoTrackToRecoElecMatched_=1;
	IsoTrackDiLepControlSampleMu_=1;
	IsoTrackDiLepControlSampleElec_=1;
	IsoTrackDiLepMu_=1;
	IsoTrackDiLepElec_=1;
	
	for(unsigned int i=0; i<40;i++)
	{
		muIsoMatched[i]=0;
		muRecoMatched[i]=0;
		elecIsoMatched[i]=0;
		elecRecoMatched[i]=0;
		RecoIsoMuonPromtMatched[i]=999;
		RecoIsoMuonPromtMatchedDeltaR[i]=999.;
		RecoIsoMuonPromtMatchedRelPt[i]=999.;
		RecoIsoElecPromtMatched[i]=999;
		RecoIsoElecPromtMatchedDeltaR[i]=999.;
		RecoIsoElecPromtMatchedRelPt[i]=999.;
		GenMuonIsoTrackMatched[i]=0;
		RecoIsoMuonIsoTrackMatched[i]=0;
		GenElecIsoTrackMatched[i]=0;
		RecoIsoElecIsoTrackMatched[i]=0;
		GenTauIsoTrackMatched[i]=0;
		SelectedIsoTracksMatchedToGenLepton[i]=0;
		SelectedIsoTracksMatchedToRecoIsoLepton[i]=0;
		SelectedIsoTracksMatchedToGenDeltaR[i]=-1; 
		SelectedIsoTracksMatchedToGenRelPT[i]=-1;
		SelectedIsoTracksMatchedToRecoIsoDeltaR[i]=-1;
		SelectedIsoTracksMatchedToRecoIsoRelPT[i]=-1;
		
		
		GenMuonIsolatedTracksPT10Matched[i]=0;
		RecoIsoMuonIsolatedTracksPT10Matched[i]=0;
		GenElecIsolatedTracksPT10Matched[i]=0;
		RecoIsoElecIsolatedTracksPT10Matched[i]=0;
		GenTauIsolatedTracksPT10Matched[i]=0;
		IsolatedTracksPT10MatchedToGenLepton[i]=0;
		IsolatedTracksPT10MatchedToRecoIsoLepton[i]=0;
		IsolatedTracksPT10MatchedToGenDeltaR[i]=-1; 
		IsolatedTracksPT10MatchedToGenRelPT[i]=-1;
		IsolatedTracksPT10MatchedToRecoIsoDeltaR[i]=-1;
		IsolatedTracksPT10MatchedToRecoIsoRelPT[i]=-1;
		
		GenMuonIsolatedTracksPT10IsoCut08Matched[i]=0;
		RecoIsoMuonIsolatedTracksPT10IsoCut08Matched[i]=0;
		GenElecIsolatedTracksPT10IsoCut08Matched[i]=0;
		RecoIsoElecIsolatedTracksPT10IsoCut08Matched[i]=0;
		GenTauIsolatedTracksPT10IsoCut08Matched[i]=0;
		IsolatedTracksPT10IsoCut08MatchedToGenLepton[i]=0;
		IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton[i]=0;
		IsolatedTracksPT10IsoCut08MatchedToGenDeltaR[i]=-1; 
		IsolatedTracksPT10IsoCut08MatchedToGenRelPT[i]=-1;
		IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR[i]=-1;
		IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT[i]=-1;
		
		GenMuonIsolatedTracksPT10IsoCut12Matched[i]=0;
		RecoIsoMuonIsolatedTracksPT10IsoCut12Matched[i]=0;
		GenElecIsolatedTracksPT10IsoCut12Matched[i]=0;
		RecoIsoElecIsolatedTracksPT10IsoCut12Matched[i]=0;
		GenTauIsolatedTracksPT10IsoCut12Matched[i]=0;
		IsolatedTracksPT10IsoCut12MatchedToGenLepton[i]=0;
		IsolatedTracksPT10IsoCut12MatchedToRecoIsoLepton[i]=0;
		IsolatedTracksPT10IsoCut12MatchedToGenDeltaR[i]=-1; 
		IsolatedTracksPT10IsoCut12MatchedToGenRelPT[i]=-1;
		IsolatedTracksPT10IsoCut12MatchedToRecoIsoDeltaR[i]=-1;
		IsolatedTracksPT10IsoCut12MatchedToRecoIsoRelPT[i]=-1;
		
		muIsoTrackMatchedToGenMu[i]=0;
		elecIsoTrackMatchedToGenMu[i]=0;
		pionIsoTrackMatchedToGenMu[i]=0;
		IsolatedMuonTracksVetoActivity[i]=0.;
		IsolatedMuonTracksVetoMTW[i]=0.;
		
		muIsoTrackMatchedToGenElec[i]=0;
		elecIsoTrackMatchedToGenElec[i]=0;
		pionIsoTrackMatchedToGenElec[i]=0;
		IsolatedElectronTracksVetoActivity[i]=0.;
		IsolatedElectronTracksVetoMTW[i]=0.;
		
		muIsoTrackMatchedToGenSingleProngTau[i]=0;
		elecIsoTrackMatchedToGenSingleProngTau[i]=0;
		pionIsoTrackMatchedToGenSingleProngTau[i]=0;
		IsolatedPionTracksVetoActivity[i]=0.;
		IsolatedPionTracksVetoMTW[i]=0.;
		
		RecoIsoMuonActivity[i]=0; 
		RecoMuonActivity[i]=0; 
		GenMuonActivity[i]=0;
		GenMuDeltaRJet_[i]=0;
		GenMuRelPTJet_[i]=0;
		GenElecDeltaRJet_[i]=0;
		GenElecRelPTJet_[i]=0;
		RecoIsoElectronActivity[i]=0; 
		RecoElectronActivity[i]=0; 
		GenElecActivity[i]=0;
		
		IsoTrackActivity[i]=0; 
		GenTauActivity[i]=0;
		
	}
	// w pt spectrum extrapolation studies
	GenMuWPt_=-1.;
	GenMuWPhi_=-1.;
	GenElecWPt_=-1.;
	GenElecWPhi_=-1.;
}
bool ExpecMaker::FiltersPass()
{
	bool result=true;
	// if(Filter_HBHENoiseFilterRA2==0) result=false;
	if(!JetID) result=false;
	return result;
}

double ExpecMaker::MuActivity( double muEta, double muPhi, unsigned int method)
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
double ExpecMaker::ElecActivity( double elecEta, double elecPhi, unsigned int method)
{
	double result =0;
	if(method==0)
	{
		for (unsigned int i=0; i < JetsNum ; i++)
		{
			if(deltaR(elecEta,elecPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
  			result+=JetsPt[i] * (Jets_chargedHadronEnergyFraction[i]);
//  			result+=JetsPt[i] * (Jets_chargedEmEnergyFraction[i] + Jets_chargedHadronEnergyFraction[i]);
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
double ExpecMaker::PionActivity( double pionEta, double pionPhi, unsigned int method)
{
	double result =0;
	if(method==0)
	{
		for (unsigned int i=0; i < JetsNum ; i++)
		{
			if(deltaR(pionEta,pionPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
			result+=JetsPt[i] * (Jets_neutralEmEnergyFraction[i] + Jets_photonEnergyFraction[i]);
		}
	}
	if(method==1)
	{
		for (unsigned int i=0; i < JetsNum ; i++)
		{
			if(deltaR(pionEta,pionPhi,JetsEta[i],JetsPhi[i])>maxDeltaRElecActivity_ ) continue;
			result+=JetsPt[i] * (Jets_neutralEmEnergyFraction[i] + Jets_photonEnergyFraction[i])*(1/(deltaR(pionEta,pionPhi,JetsEta[i],JetsPhi[i])+0.5));
		}
	}
	if(method==2)
	{
		for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
		{
			if(deltaR(pionEta,pionPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
			result+=SelectedPFCandidatesPt[i];
		}
	}
	if(method==3)
	{
		for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
		{
			if(SelectedPFCandidates_Charge[i]!=0) continue;
			if(deltaR(pionEta,pionPhi,SelectedPFCandidatesEta[i],SelectedPFCandidatesPhi[i])>maxDeltaRElecActivity_ ) continue;
			result+=SelectedPFCandidatesPt[i];
		}
	}
	return result;
	
}


std::pair <double,double> ExpecMaker::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
	double relPt = 9999;
	double deltaRmin = 9999;

	for (unsigned int i=0; i < JetsNum ; i++)
	{
		if(deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]) > deltaRmin) continue;

		if(deltaR(lepEta,lepPhi,JetsEta[i],JetsPhi[i]) < jetCone_)
		{
			if(lepPt > JetsPt[i]){
				if(lepPt < 1.2 * JetsPt[i])	continue;
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
