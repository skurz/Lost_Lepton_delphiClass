#define ApplyBaseline_cxx

#include "ApplyBaseline.h"
#include <TH2.h>
#include <TStyle.h>
#include <TSystem.h>

void ApplyBaseline::Begin(TTree * /*tree*/)
{

   TString option = GetOption();

}

void ApplyBaseline::SlaveBegin(TTree * /*tree*/)
{
   
   gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

   TString option = GetOption();

   ProofFile = new TProofOutputFile(option, TProofOutputFile::kMerge);
   ProofFile->SetOutputFileName(option);

   outPutFile = ProofFile->OpenFile("RECREATE");


   tOut = new TTree("PreSelection","a simple Tree with simple variables");

   tOut->AutoSave();

   tOut->Branch("RunNum", &RunNum);
   tOut->Branch("LumiBlockNum", &LumiBlockNum);
   tOut->Branch("EvtNum", &EvtNum);
   tOut->Branch("BadChargedCandidateFilter", &BadChargedCandidateFilter);
   tOut->Branch("BadPFMuonFilter", &BadPFMuonFilter);
   tOut->Branch("BTags", &BTags);
   tOut->Branch("BTagsJECdown", &BTagsJECdown);
   tOut->Branch("BTagsJECup", &BTagsJECup);
   tOut->Branch("BTagsJERdown", &BTagsJERdown);
   tOut->Branch("BTagsJERup", &BTagsJERup);
   tOut->Branch("BTagsMVA", &BTagsMVA);
   tOut->Branch("BTagsMVAJECdown", &BTagsMVAJECdown);
   tOut->Branch("BTagsMVAJECup", &BTagsMVAJECup);
   tOut->Branch("BTagsMVAJERdown", &BTagsMVAJERdown);
   tOut->Branch("BTagsMVAJERup", &BTagsMVAJERup);
   tOut->Branch("CaloMET", &CaloMET);
   tOut->Branch("CaloMETPhi", &CaloMETPhi);
   tOut->Branch("CrossSection", &CrossSection);
   tOut->Branch("CSCTightHaloFilter", &CSCTightHaloFilter);
   tOut->Branch("DeltaPhi1", &DeltaPhi1);
   tOut->Branch("DeltaPhi1JECdown", &DeltaPhi1JECdown);
   tOut->Branch("DeltaPhi1JECup", &DeltaPhi1JECup);
   tOut->Branch("DeltaPhi1JERdown", &DeltaPhi1JERdown);
   tOut->Branch("DeltaPhi1JERup", &DeltaPhi1JERup);
   tOut->Branch("DeltaPhi2", &DeltaPhi2);
   tOut->Branch("DeltaPhi2JECdown", &DeltaPhi2JECdown);
   tOut->Branch("DeltaPhi2JECup", &DeltaPhi2JECup);
   tOut->Branch("DeltaPhi2JERdown", &DeltaPhi2JERdown);
   tOut->Branch("DeltaPhi2JERup", &DeltaPhi2JERup);
   tOut->Branch("DeltaPhi3", &DeltaPhi3);
   tOut->Branch("DeltaPhi3JECdown", &DeltaPhi3JECdown);
   tOut->Branch("DeltaPhi3JECup", &DeltaPhi3JECup);
   tOut->Branch("DeltaPhi3JERdown", &DeltaPhi3JERdown);
   tOut->Branch("DeltaPhi3JERup", &DeltaPhi3JERup);
   tOut->Branch("DeltaPhi4", &DeltaPhi4);
   tOut->Branch("DeltaPhi4JECdown", &DeltaPhi4JECdown);
   tOut->Branch("DeltaPhi4JECup", &DeltaPhi4JECup);
   tOut->Branch("DeltaPhi4JERdown", &DeltaPhi4JERdown);
   tOut->Branch("DeltaPhi4JERup", &DeltaPhi4JERup);
   tOut->Branch("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
   tOut->Branch("eeBadScFilter", &eeBadScFilter);
   tOut->Branch("Electrons", &Electrons);
   tOut->Branch("Electrons_charge", &Electrons_charge);
   tOut->Branch("Electrons_mediumID", &Electrons_mediumID);
   tOut->Branch("Electrons_MT2Activity", &Electrons_MT2Activity);
   tOut->Branch("Electrons_MTW", &Electrons_MTW);
   tOut->Branch("Electrons_PTW", &Electrons_PTW);
   tOut->Branch("Electrons_tightID", &Electrons_tightID);
   tOut->Branch("ElectronsNoIso", &ElectronsNoIso);
   tOut->Branch("ElectronsNoIso_mediumID", &ElectronsNoIso_mediumID);
   tOut->Branch("ElectronsNoIso_MiniIso", &ElectronsNoIso_MiniIso);
   tOut->Branch("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity);
   tOut->Branch("ElectronsNoIso_MTW", &ElectronsNoIso_MTW);
   tOut->Branch("ElectronsNoIso_tightID", &ElectronsNoIso_tightID);
   tOut->Branch("GenElectrons", &GenElectrons);
   tOut->Branch("GenElectrons_fromTau", &GenElectrons_fromTau);
   tOut->Branch("GenElectrons_MT2Activity", &GenElectrons_MT2Activity);
   tOut->Branch("GenElectrons_RecoTrkAct", &GenElectrons_RecoTrkAct);
   tOut->Branch("GenElectrons_RecoTrkd3", &GenElectrons_RecoTrkd3);
   tOut->Branch("GenElectrons_RecoTrkIso", &GenElectrons_RecoTrkIso);
   tOut->Branch("GenHT", &GenHT);
   tOut->Branch("GenJets", &GenJets);
   tOut->Branch("GenJets_HTMask", &GenJets_HTMask);
   tOut->Branch("GenJets_MHTMask", &GenJets_MHTMask);
   tOut->Branch("GenMET", &GenMET);
   tOut->Branch("GenMETPhi", &GenMETPhi);
   tOut->Branch("GenMHT", &GenMHT);
   tOut->Branch("GenMHTPhi", &GenMHTPhi);
   tOut->Branch("GenMuons", &GenMuons);
   tOut->Branch("GenMuons_fromTau", &GenMuons_fromTau);
   tOut->Branch("GenMuons_MT2Activity", &GenMuons_MT2Activity);
   tOut->Branch("GenMuons_RecoTrkAct", &GenMuons_RecoTrkAct);
   tOut->Branch("GenMuons_RecoTrkd3", &GenMuons_RecoTrkd3);
   tOut->Branch("GenMuons_RecoTrkIso", &GenMuons_RecoTrkIso);
   tOut->Branch("GenParticles", &GenParticles);
   tOut->Branch("GenParticles_ParentId", &GenParticles_ParentId);
   tOut->Branch("GenParticles_ParentIdx", &GenParticles_ParentIdx);
   tOut->Branch("GenParticles_PdgId", &GenParticles_PdgId);
   tOut->Branch("GenParticles_Status", &GenParticles_Status);
   tOut->Branch("GenTaus", &GenTaus);
   tOut->Branch("GenTaus_had", &GenTaus_had);
   tOut->Branch("GenTaus_LeadRecoTrkAct", &GenTaus_LeadRecoTrkAct);
   tOut->Branch("GenTaus_LeadRecoTrkd3", &GenTaus_LeadRecoTrkd3);
   tOut->Branch("GenTaus_LeadRecoTrkIso", &GenTaus_LeadRecoTrkIso);
   tOut->Branch("GenTaus_LeadTrk", &GenTaus_LeadTrk);
   tOut->Branch("GenTaus_MT2Activity", &GenTaus_MT2Activity);
   tOut->Branch("GenTaus_Nu", &GenTaus_Nu);
   tOut->Branch("globalTightHalo2016Filter", &globalTightHalo2016Filter);
   tOut->Branch("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter);
   tOut->Branch("HBHENoiseFilter", &HBHENoiseFilter);
   tOut->Branch("HT", &HT);
   tOut->Branch("HTJECdown", &HTJECdown);
   tOut->Branch("HTJECup", &HTJECup);
   tOut->Branch("HTJERdown", &HTJERdown);
   tOut->Branch("HTJERup", &HTJERup);
   tOut->Branch("isoElectronTracks", &isoElectronTracks);
   tOut->Branch("isoMuonTracks", &isoMuonTracks);
   tOut->Branch("isoPionTracks", &isoPionTracks);
   tOut->Branch("JetID", &JetID);
   tOut->Branch("JetIDAK8", &JetIDAK8);
   tOut->Branch("JetIDJECdown", &JetIDJECdown);
   tOut->Branch("JetIDJECup", &JetIDJECup);
   tOut->Branch("JetIDJERdown", &JetIDJERdown);
   tOut->Branch("JetIDJERup", &JetIDJERup);
   tOut->Branch("Jets", &Jets);
   tOut->Branch("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV);
   tOut->Branch("Jets_bDiscriminatorMVA", &Jets_bDiscriminatorMVA);
   tOut->Branch("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction);
   tOut->Branch("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction);
   tOut->Branch("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity);
   tOut->Branch("Jets_chargedMultiplicity", &Jets_chargedMultiplicity);
   tOut->Branch("Jets_electronMultiplicity", &Jets_electronMultiplicity);
   tOut->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
   tOut->Branch("Jets_HTMask", &Jets_HTMask);
   tOut->Branch("Jets_ID", &Jets_ID);
   tOut->Branch("Jets_ISRMask", &Jets_ISRMask);
   tOut->Branch("Jets_jecFactor", &Jets_jecFactor);
   tOut->Branch("Jets_jecUnc", &Jets_jecUnc);
   tOut->Branch("Jets_LeptonMask", &Jets_LeptonMask);
   tOut->Branch("Jets_MHTMask", &Jets_MHTMask);
   tOut->Branch("Jets_muonEnergyFraction", &Jets_muonEnergyFraction);
   tOut->Branch("Jets_muonMultiplicity", &Jets_muonMultiplicity);
   tOut->Branch("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction);
   tOut->Branch("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction);
   tOut->Branch("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity);
   tOut->Branch("Jets_neutralMultiplicity", &Jets_neutralMultiplicity);
   tOut->Branch("Jets_partonFlavor", &Jets_partonFlavor);
   tOut->Branch("Jets_photonEnergyFraction", &Jets_photonEnergyFraction);
   tOut->Branch("Jets_photonMultiplicity", &Jets_photonMultiplicity);
   tOut->Branch("Jets_qgAxis2", &Jets_qgAxis2);
   tOut->Branch("Jets_qgLikelihood", &Jets_qgLikelihood);
   tOut->Branch("Jets_qgMult", &Jets_qgMult);
   tOut->Branch("Jets_qgPtD", &Jets_qgPtD);
   tOut->Branch("JetsJECdown", &JetsJECdown);
   tOut->Branch("JetsJECdown_bDiscriminatorCSV", &JetsJECdown_bDiscriminatorCSV);
   tOut->Branch("JetsJECdown_bDiscriminatorMVA", &JetsJECdown_bDiscriminatorMVA);
   tOut->Branch("JetsJECdown_hadronFlavor", &JetsJECdown_hadronFlavor);
   tOut->Branch("JetsJECdown_HTMask", &JetsJECdown_HTMask);
   tOut->Branch("JetsJECdown_ID", &JetsJECdown_ID);
   tOut->Branch("JetsJECdown_ISRMask", &JetsJECdown_ISRMask);
   tOut->Branch("JetsJECdown_LeptonMask", &JetsJECdown_LeptonMask);
   tOut->Branch("JetsJECdown_MHTMask", &JetsJECdown_MHTMask);
   tOut->Branch("JetsJECdown_muonEnergyFraction", &JetsJECdown_muonEnergyFraction);
   tOut->Branch("JetsJECdown_partonFlavor", &JetsJECdown_partonFlavor);
   tOut->Branch("JetsJECup", &JetsJECup);
   tOut->Branch("JetsJECup_bDiscriminatorCSV", &JetsJECup_bDiscriminatorCSV);
   tOut->Branch("JetsJECup_bDiscriminatorMVA", &JetsJECup_bDiscriminatorMVA);
   tOut->Branch("JetsJECup_hadronFlavor", &JetsJECup_hadronFlavor);
   tOut->Branch("JetsJECup_HTMask", &JetsJECup_HTMask);
   tOut->Branch("JetsJECup_ID", &JetsJECup_ID);
   tOut->Branch("JetsJECup_ISRMask", &JetsJECup_ISRMask);
   tOut->Branch("JetsJECup_LeptonMask", &JetsJECup_LeptonMask);
   tOut->Branch("JetsJECup_MHTMask", &JetsJECup_MHTMask);
   tOut->Branch("JetsJECup_muonEnergyFraction", &JetsJECup_muonEnergyFraction);
   tOut->Branch("JetsJECup_partonFlavor", &JetsJECup_partonFlavor);
   tOut->Branch("JetsJERdown", &JetsJERdown);
   tOut->Branch("JetsJERdown_bDiscriminatorCSV", &JetsJERdown_bDiscriminatorCSV);
   tOut->Branch("JetsJERdown_bDiscriminatorMVA", &JetsJERdown_bDiscriminatorMVA);
   tOut->Branch("JetsJERdown_hadronFlavor", &JetsJERdown_hadronFlavor);
   tOut->Branch("JetsJERdown_HTMask", &JetsJERdown_HTMask);
   tOut->Branch("JetsJERdown_ID", &JetsJERdown_ID);
   tOut->Branch("JetsJERdown_ISRMask", &JetsJERdown_ISRMask);
   tOut->Branch("JetsJERdown_LeptonMask", &JetsJERdown_LeptonMask);
   tOut->Branch("JetsJERdown_MHTMask", &JetsJERdown_MHTMask);
   tOut->Branch("JetsJERdown_muonEnergyFraction", &JetsJERdown_muonEnergyFraction);
   tOut->Branch("JetsJERdown_partonFlavor", &JetsJERdown_partonFlavor);
   tOut->Branch("JetsJERup", &JetsJERup);
   tOut->Branch("JetsJERup_bDiscriminatorCSV", &JetsJERup_bDiscriminatorCSV);
   tOut->Branch("JetsJERup_bDiscriminatorMVA", &JetsJERup_bDiscriminatorMVA);
   tOut->Branch("JetsJERup_hadronFlavor", &JetsJERup_hadronFlavor);
   tOut->Branch("JetsJERup_HTMask", &JetsJERup_HTMask);
   tOut->Branch("JetsJERup_ID", &JetsJERup_ID);
   tOut->Branch("JetsJERup_ISRMask", &JetsJERup_ISRMask);
   tOut->Branch("JetsJERup_LeptonMask", &JetsJERup_LeptonMask);
   tOut->Branch("JetsJERup_MHTMask", &JetsJERup_MHTMask);
   tOut->Branch("JetsJERup_muonEnergyFraction", &JetsJERup_muonEnergyFraction);
   tOut->Branch("JetsJERup_partonFlavor", &JetsJERup_partonFlavor);
   tOut->Branch("madHT", &madHT);
   tOut->Branch("MET", &MET);
   tOut->Branch("METDown", &METDown);
   tOut->Branch("METPhi", &METPhi);
   tOut->Branch("METPhiDown", &METPhiDown);
   tOut->Branch("METPhiUp", &METPhiUp);
   tOut->Branch("METUp", &METUp);
   tOut->Branch("MHT", &MHT);
   tOut->Branch("MHTJECdown", &MHTJECdown);
   tOut->Branch("MHTJECup", &MHTJECup);
   tOut->Branch("MHTJERdown", &MHTJERdown);
   tOut->Branch("MHTJERup", &MHTJERup);
   tOut->Branch("MHTPhi", &MHTPhi);
   tOut->Branch("MHTPhiJECdown", &MHTPhiJECdown);
   tOut->Branch("MHTPhiJECup", &MHTPhiJECup);
   tOut->Branch("MHTPhiJERdown", &MHTPhiJERdown);
   tOut->Branch("MHTPhiJERup", &MHTPhiJERup);
   tOut->Branch("MT2", &MT2);
   tOut->Branch("Muons", &Muons);
   tOut->Branch("Muons_charge", &Muons_charge);
   tOut->Branch("Muons_MT2Activity", &Muons_MT2Activity);
   tOut->Branch("Muons_MTW", &Muons_MTW);
   tOut->Branch("Muons_PTW", &Muons_PTW);
   tOut->Branch("Muons_tightID", &Muons_tightID);
   tOut->Branch("MuonsNoIso", &MuonsNoIso);
   tOut->Branch("MuonsNoIso_MiniIso", &MuonsNoIso_MiniIso);
   tOut->Branch("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity);
   tOut->Branch("MuonsNoIso_MTW", &MuonsNoIso_MTW);
   tOut->Branch("MuonsNoIso_tightID", &MuonsNoIso_tightID);
   tOut->Branch("nAllVertices", &nAllVertices);
   tOut->Branch("NJets", &NJets);
   tOut->Branch("NJetsISR", &NJetsISR);
   tOut->Branch("NJetsISRJECdown", &NJetsISRJECdown);
   tOut->Branch("NJetsISRJECup", &NJetsISRJECup);
   tOut->Branch("NJetsISRJERdown", &NJetsISRJERdown);
   tOut->Branch("NJetsISRJERup", &NJetsISRJERup);
   tOut->Branch("NJetsJECdown", &NJetsJECdown);
   tOut->Branch("NJetsJECup", &NJetsJECup);
   tOut->Branch("NJetsJERdown", &NJetsJERdown);
   tOut->Branch("NJetsJERup", &NJetsJERup);
   tOut->Branch("NumEvents", &NumEvents);
   tOut->Branch("NumInteractions", &NumInteractions);
   tOut->Branch("NVtx", &NVtx);
   tOut->Branch("PDFids", &PDFids);
   tOut->Branch("PDFweights", &PDFweights);
   tOut->Branch("PFCaloMETRatio", &PFCaloMETRatio);
   tOut->Branch("puSysDown", &puSysDown);
   tOut->Branch("puSysUp", &puSysUp);
   tOut->Branch("puWeight", &puWeight);
   tOut->Branch("ScaleWeights", &ScaleWeights);
   tOut->Branch("SusyLSPMass", &SusyLSPMass);
   tOut->Branch("SusyMotherMass", &SusyMotherMass);
   tOut->Branch("TAPElectronTracks", &TAPElectronTracks);
   tOut->Branch("TAPElectronTracks_activity", &TAPElectronTracks_activity);
   tOut->Branch("TAPElectronTracks_charge", &TAPElectronTracks_charge);
   tOut->Branch("TAPElectronTracks_mT", &TAPElectronTracks_mT);
   tOut->Branch("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso);
   tOut->Branch("TAPMuonTracks", &TAPMuonTracks);
   tOut->Branch("TAPMuonTracks_activity", &TAPMuonTracks_activity);
   tOut->Branch("TAPMuonTracks_charge", &TAPMuonTracks_charge);
   tOut->Branch("TAPMuonTracks_mT", &TAPMuonTracks_mT);
   tOut->Branch("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso);
   tOut->Branch("TAPPionTracks", &TAPPionTracks);
   tOut->Branch("TAPPionTracks_activity", &TAPPionTracks_activity);
   tOut->Branch("TAPPionTracks_charge", &TAPPionTracks_charge);
   tOut->Branch("TAPPionTracks_mT", &TAPPionTracks_mT);
   tOut->Branch("TAPPionTracks_trkiso", &TAPPionTracks_trkiso);
   tOut->Branch("TriggerNames", &TriggerNames);
   tOut->Branch("TriggerPass", &TriggerPass);
   tOut->Branch("TriggerPrescales", &TriggerPrescales);
   tOut->Branch("TrueNumInteractions", &TrueNumInteractions);
   tOut->Branch("Weight", &Weight);
}

Bool_t ApplyBaseline::Process(Long64_t entry)
{
   fChain->GetTree()->GetEntry(entry);

   if(HT < 250)  return kTRUE;
   if(MHT < 200)  return kTRUE;
   if(NJets < 2)  return kTRUE;

   // if(DeltaPhi1 < 0.5 || DeltaPhi2 < 0.5 || DeltaPhi3 < 0.3 || DeltaPhi4 < 0.3)  return kTRUE;

   //if(madHT > 600) return kTRUE;   

   //if(Muons->size() + Electrons->size() != 1)  return kTRUE;

   tOut->Fill();
   return kTRUE;
}

void ApplyBaseline::SlaveTerminate()
{
   outPutFile->cd();
   tOut->Write();
   ProofFile->Print();
   fOutput->Add(ProofFile);
   tOut->SetDirectory(0);
   outPutFile->Close();
}

void ApplyBaseline::Terminate()
{
   



}
