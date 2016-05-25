#define ExpecMaker_cxx
#include "ExpecMaker.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TSystem.h"

void ExpecMaker::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

}

void ExpecMaker::SlaveBegin(TTree * /*tree*/)
{	
  tExpectation_ = new TTree("LostLeptonExpectation","a simple Tree with simple variables");

  tExpectation_->Branch("EvtNum",&EvtNum,"EvtNum/i");
  tExpectation_->Branch("HT",&HT);
  tExpectation_->Branch("MHT",&MHT);
  tExpectation_->Branch("NJets",&NJets);
  tExpectation_->Branch("BTags",&BTags);
  tExpectation_->Branch("isoTracks",&isoTracks);
  tExpectation_->Branch("Bin",&Bin_);
  tExpectation_->Branch("BinQCD",&BinQCD_);
  tExpectation_->Branch("genHT",&genHT);
  tExpectation_->Branch("NVtx",&NVtx);
  tExpectation_->Branch("DeltaPhi1",&DeltaPhi1);
  tExpectation_->Branch("DeltaPhi2",&DeltaPhi2);
  tExpectation_->Branch("DeltaPhi3",&DeltaPhi3);
  tExpectation_->Branch("DeltaPhi4",&DeltaPhi4);
  tExpectation_->Branch("Weight", &Weight);
  tExpectation_->Branch("MET",&METPt);
  tExpectation_->Branch("METPtUp",&METPtUp);
  tExpectation_->Branch("METPtDown",&METPtDown);
  tExpectation_->Branch("METPhi",&METPhi);
  tExpectation_->Branch("MHT_Phi",&MHT_Phi);
  tExpectation_->Branch("GenMuNum",&GenMuNum_);
  tExpectation_->Branch("GenMus", "std::vector<TLorentzVector>", &GenMus,32000,0);
  tExpectation_->Branch("GenMuDeltaRJet",&GenMuDeltaRJet_);
  tExpectation_->Branch("GenMuRelPTJet",&GenMuRelPTJet_);
  tExpectation_->Branch("GenMu_MT2Activity", &GenMu_MT2Activity);
  tExpectation_->Branch("GenElecNum",&GenElecNum_);
  tExpectation_->Branch("GenEls", "std::vector<TLorentzVector>", &GenEls, 32000, 0);
  tExpectation_->Branch("GenElecDeltaRJet", &GenElecDeltaRJet_);
  tExpectation_->Branch("GenElecRelPTJet", &GenElecRelPTJet_);
  tExpectation_->Branch("GenElec_MT2Activity", &GenElec_MT2Activity);
  tExpectation_->Branch("GenTauNum",&GenTauNum_);
  tExpectation_->Branch("GenTaus", "std::vector<TLorentzVector>", &GenTaus, 32000, 0); 
  tExpectation_->Branch("GenTau_MT2Activity", &GenTau_MT2Activity);
  tExpectation_->Branch("Expectation",&Expectation);  
  tExpectation_->Branch("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  tExpectation_->Branch("muAcc",&muAcc);  
  tExpectation_->Branch("muReco",&muReco);  
  tExpectation_->Branch("muIso",&muIso);  
  tExpectation_->Branch("MTW",&mtw);  
  tExpectation_->Branch("elecAcc",&elecAcc);  
  tExpectation_->Branch("elecReco",&elecReco);  
  tExpectation_->Branch("elecIso",&elecIso);   
  tExpectation_->Branch("MuPurity",&MuPurity_); 
  tExpectation_->Branch("ElecPurity",&ElecPurity_); 
  tExpectation_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum_);
  tExpectation_->Branch("selectedIDIsoMuons", "std::vector<TLorentzVector>", &selectedIDIsoMuons, 32000, 0);
  tExpectation_->Branch("selectedIDIsoMuonsPromptMatched", &selectedIDIsoMuonsPromptMatched);
  tExpectation_->Branch("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity);
  tExpectation_->Branch("selectedIDMuonsNum",&selectedIDMuonsNum_);
  tExpectation_->Branch("selectedIDMuons", "std::vector<TLorentzVector>", &selectedIDMuons, 32000, 0);
  tExpectation_->Branch("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity); 
  tExpectation_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum_);
  tExpectation_->Branch("selectedIDIsoElectrons", "std::vector<TLorentzVector>", &selectedIDIsoElectrons, 32000, 0);
  tExpectation_->Branch("selectedIDIsoElectronsPromptMatched", &selectedIDIsoElectronsPromptMatched);
  tExpectation_->Branch("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity);
  tExpectation_->Branch("selectedIDElectronsNum",&selectedIDElectronsNum_);
  tExpectation_->Branch("selectedIDElectrons", "std::vector<TLorentzVector>", &selectedIDElectrons, 32000, 0);
  tExpectation_->Branch("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity);
  tExpectation_->Branch("HTJetsMask", &HTJetsMask);
  tExpectation_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
  tExpectation_->Branch("bTagProb", &bTagProb);
  tExpectation_->Branch("cosDTT", &cosDTT);
  tExpectation_->Branch("genCosDTT", &genCosDTT);
  
  if(!DY_){
    tExpectation_->Branch("isoElectronTracks",&isoElectronTracks);
    tExpectation_->Branch("IsolatedElectronTracksVeto", "std::vector<TLorentzVector>", &IsolatedElectronTracksVeto, 32000, 0);
    tExpectation_->Branch("IsolatedElectronTracksVetoMTW", &IsolatedElectronTracksVetoMTW);    
    tExpectation_->Branch("isoMuonTracks",&isoMuonTracks);
    tExpectation_->Branch("IsolatedMuonTracksVeto", "std::vector<TLorentzVector>", &IsolatedMuonTracksVeto, 32000, 0);
    tExpectation_->Branch("IsolatedMuonTracksVetoMTW", &IsolatedMuonTracksVetoMTW);    
    tExpectation_->Branch("isoPionTracks",&isoPionTracks);
    tExpectation_->Branch("IsolatedPionTracksVeto", "std::vector<TLorentzVector>", &IsolatedPionTracksVeto, 32000, 0);
    tExpectation_->Branch("IsolatedPionTracksVetoMTW", &IsolatedPionTracksVetoMTW);
    
    tExpectation_->Branch("ExpectationDiLep",&ExpectationDiLep_);
    tExpectation_->Branch("MuDiLepControlSample",&MuDiLepControlSample_);
    tExpectation_->Branch("ElecDiLepControlSample",&ElecDiLepControlSample_);

    if(doIsoTrackStudies){
      tExpectation_->Branch("muIsoTrackMatchedToGenElec", &muIsoTrackMatchedToGenElec);
      tExpectation_->Branch("elecIsoTrackMatchedToGenElec", &elecIsoTrackMatchedToGenElec);
      tExpectation_->Branch("pionIsoTrackMatchedToGenElec", &pionIsoTrackMatchedToGenElec);
      tExpectation_->Branch("muIsoTrackMatchedToGenMu", &muIsoTrackMatchedToGenMu);
      tExpectation_->Branch("elecIsoTrackMatchedToGenMu", &elecIsoTrackMatchedToGenMu);
      tExpectation_->Branch("pionIsoTrackMatchedToGenMu", &pionIsoTrackMatchedToGenMu);
      tExpectation_->Branch("muIsoTrackMatchedToGenSingleProngTau", &muIsoTrackMatchedToGenSingleProngTau);
      tExpectation_->Branch("elecIsoTrackMatchedToGenSingleProngTau", &elecIsoTrackMatchedToGenSingleProngTau);
      tExpectation_->Branch("pionIsoTrackMatchedToGenSingleProngTau", &pionIsoTrackMatchedToGenSingleProngTau);
    }
  }

  SearchBins_ = new SearchBins();
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
  
  GetOutputList()->Add(tExpectation_);
}

Bool_t ExpecMaker::Process(Long64_t entry)
{

  resetValues();
  fChain->GetTree()->GetEntry(entry);

  // genLevel HTcut
  if(HTgen_cut > 0.01) if(genHT > HTgen_cut) return kTRUE;

  // std::cout << "Applying skim cuts..." << std::endl;
  if(!DY_ && (HT<minHT_ || MHT< minMHT_ || NJets < minNJets_)) return kTRUE;
  if(DY_ && ( HT<minHT_ || NJets < minNJets_) ) return kTRUE;	
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_ ) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  //	if(!DY_) if(minDeltaPhiN<minDeltaPhiN_) return kTRUE;

  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  if(useTrigger) if(!TriggerPass->at(34) && !TriggerPass->at(35) && !TriggerPass->at(36)) return kTRUE;


  if(useTriggerEffWeight) Weight = Weight * GetTriggerEffWeight(MHT);

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

  if(doBTagCorrFullSim || doBTagCorrFastSim){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    if(currentTree != treeName){
      treeName = currentTree;

      delete btagcorr;
      btagcorr = new BTagCorrector();

      TObjArray *optionArray = currentTree.Tokenize("/");
      TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();

      TFile *skimFile = TFile::Open(path_toSkims+currFileName, "READ");

      btagcorr->SetEffs(skimFile);
      btagcorr->SetCalib(path_bTagCalib);
      btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
      if(doBTagCorrFastSim) btagcorr->SetFastSim(true);
      else btagcorr->SetFastSim(false);
    }
    bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,HTJetsMask);
  }
  else bTagProb = {0, 0, 0, 0};

  //Account for efficiency of JetID since we cannot apply it on fastSim
  if(!applyJetID) Weight *= 0.99;
  
  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);
  //    std::cout << "Event falls in bin " << Bin_ << std::endl;
  isoTracks = isoMuonTracks + isoPionTracks + isoElectronTracks;

  GenMuNum_ = GenMus->size();
  GenElecNum_ = GenEls->size();
  GenTauNum_ = GenTaus->size();

  selectedIDMuonsNum_ = selectedIDMuons->size();
  selectedIDIsoMuonsNum_ = selectedIDIsoMuons->size();
  selectedIDElectronsNum_ = selectedIDElectrons->size();
  selectedIDIsoElectronsNum_ = selectedIDIsoElectrons->size();

  JetsNum_ = Jets->size();

  if(propagateJECtoMET == +1) METPt = METPtUp->at(1);
  if(propagateJECtoMET == -1) METPt = METPtDown->at(1);

	
  // Muons
  if( (GenMuNum_==1 && GenElecNum_==0) || (DY_ && GenMuNum_==2) ){ 
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHT_Phi, GenMus->at(0).Pt(), GenMus->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHT_Phi, GenMus->at(0).Pt(), GenMus->at(0).Phi()));
    if ( GenMus->at(0).Pt() < minMuPt_ || std::abs(GenMus->at(0).Eta()) > maxMuEta_){
      muAcc=0;
      Expectation=1;
    }else{
      muAcc=2;
      bool RecoNotMatched=true; 

      for (UShort_t i=0; i<selectedIDMuonsNum_; i++){
        if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),selectedIDMuons->at(i).Eta(),selectedIDMuons->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMus->at(0).Pt()-selectedIDMuons->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenToRecoMu_){
          RecoNotMatched=false;          
          muReco =2;
          bool IsoNotMatched=true;

          for (UShort_t ii=0; ii < selectedIDIsoMuonsNum_; ii++){
            if(deltaR(selectedIDIsoMuons->at(ii).Eta(),selectedIDIsoMuons->at(ii).Phi(),selectedIDMuons->at(i).Eta(),selectedIDMuons->at(i).Phi())<maxDeltaRRecoToIsoMu_ && std::abs(selectedIDIsoMuons->at(ii).Pt()-selectedIDMuons->at(i).Pt())/selectedIDIsoMuons->at(ii).Pt() <maxDiffPtRecoToIsoMu_){
              IsoNotMatched=false;
              muIso=2;
              Expectation=2;
              if(!DY_){
                mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(ii).Pt(), selectedIDIsoMuons->at(ii).Phi(), scaleMet);
              }
              MuDiLepControlSample_=2;
            }
          }
          if(IsoNotMatched){
            muIso=0;
            Expectation=1;
          }
        }
      }
      if(RecoNotMatched){
        muReco=0;
        Expectation=1;
      }
    }
  }

  // Electrons
  if( (GenMuNum_==0 && GenElecNum_==1) || (DY_ && GenElecNum_==2) ){
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHT_Phi, GenEls->at(0).Pt(), GenEls->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHT_Phi, GenEls->at(0).Pt(), GenEls->at(0).Phi()));
    if( GenEls->at(0).Pt() < minElecPt_ || std::abs(GenEls->at(0).Eta()) > maxElecEta_){
    elecAcc=0;
    Expectation=1;
    }else{
      elecAcc=2;
      bool RecoNotMatched=true;

      for (UShort_t i=0; i<selectedIDElectronsNum_; i++){
        if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),selectedIDElectrons->at(i).Eta(),selectedIDElectrons->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenEls->at(0).Pt()-selectedIDElectrons->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenToRecoElec_){
          RecoNotMatched=false;
          elecReco =2;
          bool IsoNotMatched=true;

          for (UShort_t ii=0; ii < selectedIDIsoElectronsNum_; ii++){
            if(deltaR(selectedIDIsoElectrons->at(ii).Eta(),selectedIDIsoElectrons->at(ii).Phi(),selectedIDElectrons->at(i).Eta(),selectedIDElectrons->at(i).Phi())<maxDeltaRRecoToIsoElec_ && std::abs(selectedIDIsoElectrons->at(ii).Pt()-selectedIDElectrons->at(i).Pt())/selectedIDIsoElectrons->at(ii).Pt() <maxDiffPtRecoToIsoElec_){
              IsoNotMatched=false;
              elecIso=2;
              Expectation=2;
              if(!DY_) {
                mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(ii).Pt(), selectedIDIsoElectrons->at(ii).Phi(), scaleMet);
              }
              ElecDiLepControlSample_=2;
            }
          }
          if(IsoNotMatched){
            elecIso=0;
            Expectation=1; 
          }
        }
      }
      if(RecoNotMatched)
      {
        elecReco=0;
        Expectation=1;
      }
    }
  } 

  // Useful values
  for(unsigned int i=0; i< GenMuNum_;i++){
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMus->at(i).Pt(),GenMus->at(i).Eta(),GenMus->at(i).Phi());
      GenMuDeltaRJet_.push_back(DeltaR_relPT.first);
      GenMuRelPTJet_.push_back(DeltaR_relPT.second);
  }
  for(unsigned int i=0; i< GenElecNum_;i++){
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenEls->at(i).Pt(),GenEls->at(i).Eta(),GenEls->at(i).Phi());
      GenElecDeltaRJet_.push_back(DeltaR_relPT.first);
      GenElecRelPTJet_.push_back(DeltaR_relPT.second);
  }

  if(DY_){
    tExpectation_->Fill();
    return kTRUE;
  }

  // di leptonic events
  if((GenMuNum_+GenElecNum_)==2){
    if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==0){
      Expectation=1;
      ExpectationDiLep_=1;
    }
    if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0){
      mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet);
      MuDiLepControlSample_=0;
    }
    if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1){
      mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet);
      ElecDiLepControlSample_=0;
    }
  }

  // new purity studies
  if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0 && (GenMuNum_ + GenElecNum_)<2){
    if(GenMuNum_<1){
      MuPurity_=0;
    }
    else{
      MuPurity_=2;
    }
  }
  if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1 && (GenMuNum_+ GenElecNum_)<2){
    if(GenElecNum_<1){
      ElecPurity_=0;
    }else{
      ElecPurity_=2;
    }
  }

  //old purity calculations
  for (UShort_t i=0; i< selectedIDIsoMuonsNum_;i++){
    if(selectedIDIsoMuonsNum_>1 || MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet)>mtwCut_){
      selectedIDIsoMuonsPromptMatched.push_back(-1);
      continue;
    }

    bool matched=false;
    double best_score=999.;
    double selectedIDIsoMuonsPromptMatchedDeltaR_=999., selectedIDIsoMuonsPromptMatchedRelPt_=999.;
    TVector3 recoMu3(selectedIDIsoMuons->at(i).Px(), selectedIDIsoMuons->at(i).Py(), selectedIDIsoMuons->at(i).Pz());

    for(UShort_t ii=0; ii<GenMuNum_;ii++){
      TVector3 genMu3(GenMus->at(ii).Px(), GenMus->at(ii).Py(), GenMus->at(ii).Pz());
      double this_score=(recoMu3-genMu3).Mag2();
      selectedIDIsoMuonsPromptMatchedDeltaR_=deltaR(selectedIDIsoMuons->at(i).Eta(),selectedIDIsoMuons->at(i).Phi(),GenMus->at(ii).Eta(),GenMus->at(ii).Phi());
      selectedIDIsoMuonsPromptMatchedRelPt_=(selectedIDIsoMuons->at(i).Pt()-GenMus->at(ii).Pt())/selectedIDIsoMuons->at(i).Pt();
      if(this_score<best_score&&selectedIDIsoMuonsPromptMatchedDeltaR_<maxDeltaRIsoToGenMu_ && selectedIDIsoMuonsPromptMatchedRelPt_<maxDiffPtIsoToGenMu_){
        matched=true;
      }
    }
    if(matched){
      selectedIDIsoMuonsPromptMatched.push_back(1);
    }else{
      selectedIDIsoMuonsPromptMatched.push_back(0);
    }
  }

  for (UShort_t i=0; i< selectedIDIsoElectronsNum_;i++){
    if(selectedIDIsoElectronsNum_>1 || MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet)>mtwCut_){
      selectedIDIsoElectronsPromptMatched.push_back(-1);
      continue;
    }

    bool matched=false;
    double best_score=999.;
    double selectedIDIsoElectronsPromptMatchedDeltaR_=999., selectedIDIsoElectronsPromptMatchedRelPt_=999.;
    TVector3 recoEl3(selectedIDIsoElectrons->at(i).Px(), selectedIDIsoElectrons->at(i).Py(), selectedIDIsoElectrons->at(i).Pz());
    for(UShort_t ii=0; ii<GenElecNum_;ii++){
      TVector3 genEl3(GenEls->at(ii).Px(), GenEls->at(ii).Py(), GenEls->at(ii).Pz());
      double this_score=(recoEl3-genEl3).Mag2();
      selectedIDIsoElectronsPromptMatchedDeltaR_=deltaR(selectedIDIsoElectrons->at(i).Eta(),selectedIDIsoElectrons->at(i).Phi(),GenEls->at(ii).Eta(),GenEls->at(ii).Phi());
      selectedIDIsoElectronsPromptMatchedRelPt_=(selectedIDIsoElectrons->at(i).Pt()-GenEls->at(ii).Pt())/selectedIDIsoElectrons->at(i).Pt();

      if(this_score<best_score&&selectedIDIsoElectronsPromptMatchedDeltaR_<maxDeltaRIsoToGenElec_ && selectedIDIsoElectronsPromptMatchedRelPt_<maxDiffPtIsoToGenElec_){
        matched=true;
      }
    }
    if(matched){
      selectedIDIsoElectronsPromptMatched.push_back(1);
    }else{
      selectedIDIsoElectronsPromptMatched.push_back(0);
    }
  }
  
  // check weather a background event according to plane lepton veto gets rejected by the isolated track veto with MT cut applied
  if(isoTracks>=1 && Expectation==1){
    ExpectationReductionIsoTrack=1;
  }

  if(!doIsoTrackStudies){
    tExpectation_->Fill();
    return kTRUE;
  }

  // isotrack studies
  for(int i=0; i< isoMuonTracks; i++) {
    IsolatedMuonTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedMuonTracksVeto->at(i).Pt(), IsolatedMuonTracksVeto->at(i).Phi()));
  }
  for(int i=0; i< isoElectronTracks; i++) {
    IsolatedElectronTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedElectronTracksVeto->at(i).Pt(), IsolatedElectronTracksVeto->at(i).Phi()));
  }
  for(int i=0; i< isoPionTracks; i++) {
    IsolatedPionTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedPionTracksVeto->at(i).Pt(), IsolatedPionTracksVeto->at(i).Phi()));
  }

  if(GenMuNum_==1 && GenElecNum_==0){
    for(int i=0; i< isoMuonTracks; i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        muIsoTrackMatchedToGenMu.push_back(1);
      }else{
        muIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoElectronTracks;i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        elecIsoTrackMatchedToGenMu.push_back(1);
      }else{
        elecIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoPionTracks;i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        pionIsoTrackMatchedToGenMu.push_back(1);
      }else{
        pionIsoTrackMatchedToGenMu.push_back(0);
      }
    }
  }

  if(GenElecNum_==1 && GenMuNum_==0){
    for(int i=0; i< isoMuonTracks; i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        muIsoTrackMatchedToGenElec.push_back(1);
      }else{
        muIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  
    for(int i=0; i< isoElectronTracks;i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        elecIsoTrackMatchedToGenElec.push_back(1);
      }else{
        elecIsoTrackMatchedToGenElec.push_back(0);
      }
    }
      
    for(int i=0; i< isoPionTracks;i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        pionIsoTrackMatchedToGenElec.push_back(1);        
      }else{
        pionIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  }
  
  if(GenElecNum_==0 && GenMuNum_==0 && GenTauNum_==1){
    for(int i=0; i< isoMuonTracks; i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
        muIsoTrackMatchedToGenSingleProngTau.push_back(1);
      }else{
        muIsoTrackMatchedToGenSingleProngTau.push_back(0);
      }
    }

    for(int i=0; i< isoElectronTracks;i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
        elecIsoTrackMatchedToGenSingleProngTau.push_back(1);
      }else{
        elecIsoTrackMatchedToGenSingleProngTau.push_back(0);
      }
    }

    for(int i=0; i< isoPionTracks;i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
        pionIsoTrackMatchedToGenSingleProngTau.push_back(1);
      }else{
        pionIsoTrackMatchedToGenSingleProngTau.push_back(0);
      }
    }
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
  //std::cout << "tExpectation_:" << tExpectation_ << '\n';
  tExpectation_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonExpectation"));
  //std::cout << "tExpectation_:" << tExpectation_ << '\n';

  if(!tExpectation_) Error("Terminate", "TTree object missing in output list");
  else{
    TFile *outPutFile = new TFile(fileName, "RECREATE"); 
    outPutFile->cd();
    tExpectation_->Write();
    outPutFile->Close();
  }

  cout << "Saved output to " << fileName << endl;
	
}

void ExpecMaker::resetValues()
{
  Expectation=0;
  ExpectationReductionIsoTrack=0;
  muIso =1;
  muReco =1;
  muAcc =1;
  elecIso =1;
  elecReco =1;
  elecAcc =1;

  mtw=-1.;
  genCosDTT=-1;
  cosDTT=-1;

  ExpectationDiLep_=0;
  MuDiLepControlSample_=1;
  ElecDiLepControlSample_=1;

  MuPurity_=1;
  ElecPurity_=1;
  
  selectedIDIsoMuonsPromptMatched.clear();
  selectedIDIsoElectronsPromptMatched.clear();

  GenMuDeltaRJet_.clear();
  GenMuRelPTJet_.clear();
  GenElecDeltaRJet_.clear();
  GenElecRelPTJet_.clear();

  if(doIsoTrackStudies){    
    muIsoTrackMatchedToGenMu.clear();
    elecIsoTrackMatchedToGenMu.clear();
    pionIsoTrackMatchedToGenMu.clear();
    IsolatedMuonTracksVetoMTW.clear();
      
    muIsoTrackMatchedToGenElec.clear();
    elecIsoTrackMatchedToGenElec.clear();
    pionIsoTrackMatchedToGenElec.clear();
    IsolatedElectronTracksVetoMTW.clear();
      
    muIsoTrackMatchedToGenSingleProngTau.clear();
    elecIsoTrackMatchedToGenSingleProngTau.clear();
    pionIsoTrackMatchedToGenSingleProngTau.clear();
    IsolatedPionTracksVetoMTW.clear();
  }
}

bool ExpecMaker::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    //Applied via List on Data
    //if(!CSCTightHaloFilter) result=false;
    if(eeBadScFilter!=1) result=false;
    if(!eeBadSc4Filter) result=false;
    if(!HBHENoiseFilter) result=false;
    if(!HBHEIsoNoiseFilter) result=false;
  }
  if(NVtx<=0) result=false;
  if(applyJetID) if(JetID!=1) result=false;
  return result;
}

std::pair <double,double> ExpecMaker::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
  double relPt = 9999;
  double deltaRmin = 9999;

  for (unsigned int i=0; i < JetsNum_ ; i++)
    {
      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) > deltaRmin) continue;

      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) < jetCone_)
  {
    if(lepPt > Jets->at(i).Pt()){
      if(lepPt < 1.2 * Jets->at(i).Pt())  continue;
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

