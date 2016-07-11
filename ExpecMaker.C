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
  tExpectation_->Branch("isoTracksNum",&isoTracksNum);
  tExpectation_->Branch("Bin",&Bin_);
  tExpectation_->Branch("BinQCD",&BinQCD_);
  tExpectation_->Branch("madHT",&madHT);
  tExpectation_->Branch("NVtx",&NVtx);
  tExpectation_->Branch("DeltaPhi1",&DeltaPhi1);
  tExpectation_->Branch("DeltaPhi2",&DeltaPhi2);
  tExpectation_->Branch("DeltaPhi3",&DeltaPhi3);
  tExpectation_->Branch("DeltaPhi4",&DeltaPhi4);
  tExpectation_->Branch("Weight", &Weight);
  tExpectation_->Branch("MET",&MET);
  tExpectation_->Branch("METUp",&METUp);
  tExpectation_->Branch("METDown",&METDown);
  tExpectation_->Branch("METPhi",&METPhi);
  tExpectation_->Branch("MHTPhi",&MHTPhi);
  tExpectation_->Branch("GenHT",&GenHT);
  tExpectation_->Branch("GenMHT",&GenMHT);
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
  //tExpectation_->Branch("HTJetsMask", &HTJetsMask);
  //tExpectation_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
  tExpectation_->Branch("bTagProb", &bTagProb);
  tExpectation_->Branch("cosDTT", &cosDTT);
  tExpectation_->Branch("genCosDTT", &genCosDTT);
  tExpectation_->Branch("PDFweights", &PDFweights);
  tExpectation_->Branch("ScaleWeights", &ScaleWeights);
  tExpectation_->Branch("isoElectronTracks", "std::vector<TLorentzVector>", &isoElectronTracks, 32000, 0);
  //tExpectation_->Branch("isoElectronTracks_activity", &isoElectronTracks_activity);
  //tExpectation_->Branch("isoElectronTracks_chg", &isoElectronTracks_chg);
  //tExpectation_->Branch("isoElectronTracks_mT", &isoElectronTracks_mT);
  //tExpectation_->Branch("isoElectronTracks_trkiso", &isoElectronTracks_trkiso);
  tExpectation_->Branch("isoMuonTracks", "std::vector<TLorentzVector>", &isoMuonTracks, 32000, 0);
  //tExpectation_->Branch("isoMuonTracks_activity", &isoMuonTracks_activity);
  //tExpectation_->Branch("isoMuonTracks_chg", &isoMuonTracks_chg);
  //tExpectation_->Branch("isoMuonTracks_mT", &isoMuonTracks_mT);
  //tExpectation_->Branch("isoMuonTracks_trkiso", &isoMuonTracks_trkiso);
  tExpectation_->Branch("isoPionTracks", "std::vector<TLorentzVector>", &isoPionTracks, 32000, 0);
  //tExpectation_->Branch("isoPionTracks_activity", &isoPionTracks_activity);
  //tExpectation_->Branch("isoPionTracks_chg", &isoPionTracks_chg);
  //tExpectation_->Branch("isoPionTracks_mT", &isoPionTracks_mT);
  //tExpectation_->Branch("isoPionTracks_trkiso", &isoPionTracks_trkiso);
  
  tExpectation_->Branch("isoElectronTracksNum",&isoElectronTracksNum);   
  tExpectation_->Branch("isoMuonTracksNum",&isoMuonTracksNum);   
  tExpectation_->Branch("isoPionTracksNum",&isoPionTracksNum);
    
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

  SearchBins_ = new SearchBins();
  SearchBinsQCD_ = new SearchBins(true); // QCD binning
  
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
  
  GetOutputList()->Add(tExpectation_);
}

Bool_t ExpecMaker::Process(Long64_t entry)
{

  resetValues();
  fChain->GetTree()->GetEntry(entry);

  // genLevel HTcut
  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;

  // std::cout << "Applying skim cuts..." << std::endl;
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_ ) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;

  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  //if(useTrigger) if(!TriggerPass->at(34) && !TriggerPass->at(35) && !TriggerPass->at(36)) return kTRUE;

  if(doBTagCorrFullSim || doBTagCorrFastSim){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());

    // Fix for v8 production
      //TObjArray *optionArrayFix = currentTree.Tokenize("/");
      //TString currFileNameFix = ((TObjString *)(optionArrayFix->At(optionArrayFix->GetEntries()-1)))->String();
      //std::string wrongWeights = "TTJets_SingleLeptFromT.root";
      //std::size_t found = std::string(currFileNameFix.Data()).find(wrongWeights);
      //if(found!=std::string::npos){
      //  Weight = 3.52337e-6;
      //}

    if(currentTree != treeName){
      treeName = currentTree;

      //if(found!=std::string::npos){
      //  std::cout<<"Correcting Weight!"<<std::endl;
      //}

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

  if(useTriggerEffWeight) Weight = Weight * GetTriggerEffWeight(MHT);

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

  //Account for efficiency of JetID since we cannot apply it on fastSim
  if(!applyJetID) Weight *= 0.99;
  
  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);
  //    std::cout << "Event falls in bin " << Bin_ << std::endl;
  isoTracksNum = isoMuonTracksNum + isoPionTracksNum + isoElectronTracksNum;

  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;

  GenMuNum_ = GenMus->size();
  GenElecNum_ = GenEls->size();
  GenTauNum_ = GenTaus->size();

  selectedIDMuonsNum_ = selectedIDMuons->size();
  selectedIDIsoMuonsNum_ = selectedIDIsoMuons->size();
  selectedIDElectronsNum_ = selectedIDElectrons->size();
  selectedIDIsoElectronsNum_ = selectedIDIsoElectrons->size();

  if(propagateJECtoMET == +1) MET = METUp->at(1);
  if(propagateJECtoMET == -1) MET = METDown->at(1);
	
  // Muons
  if(GenMuNum_==1 && GenElecNum_==0){ 
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHTPhi, GenMus->at(0).Pt(), GenMus->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHTPhi, GenMus->at(0).Pt(), GenMus->at(0).Phi()));
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
              mtw =  MTWCalculator(MET,METPhi, selectedIDIsoMuons->at(ii).Pt(), selectedIDIsoMuons->at(ii).Phi(), scaleMet);
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
  if(GenMuNum_==0 && GenElecNum_==1){
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHTPhi, GenEls->at(0).Pt(), GenEls->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHTPhi, GenEls->at(0).Pt(), GenEls->at(0).Phi()));
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
              mtw =  MTWCalculator(MET,METPhi, selectedIDIsoElectrons->at(ii).Pt(), selectedIDIsoElectrons->at(ii).Phi(), scaleMet);
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

  // di leptonic events
  if((GenMuNum_+GenElecNum_)==2){
    if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==0){
      Expectation=1;
      ExpectationDiLep_=1;
    }
    if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0){
      mtw =  MTWCalculator(MET,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet);
      MuDiLepControlSample_=0;
    }
    if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1){
      mtw =  MTWCalculator(MET,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet);
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
    if(selectedIDIsoMuonsNum_>1 || MTWCalculator(MET,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi(), scaleMet)>mtwCut_){
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
    if(selectedIDIsoElectronsNum_>1 || MTWCalculator(MET,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi(), scaleMet)>mtwCut_){
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
  if(isoTracksNum>=1 && Expectation==1){
    ExpectationReductionIsoTrack=1;
  }

  // get isoTrack collection from full TAP collection
  for(unsigned i=0; i< TAPElectronTracks->size(); i++){
    if(TAPElectronTracks_trkiso->at(i) < 0.2 && TAPElectronTracks_mT->at(i) < 100){
      isoElectronTracks.push_back(TAPElectronTracks->at(i));
      isoElectronTracks_activity.push_back(TAPElectronTracks_activity->at(i));
      isoElectronTracks_chg.push_back(TAPElectronTracks_chg->at(i));
      isoElectronTracks_mT.push_back(TAPElectronTracks_mT->at(i));
      isoElectronTracks_trkiso.push_back(TAPElectronTracks_trkiso->at(i));
    }
  }
  if(isoElectronTracks.size() != (unsigned) isoElectronTracksNum){
    std::cout << "WARNING! Number of isoElectronTracks is not correct! Skipping event." << std::endl;
    return kTRUE;
  }

  for(unsigned i=0; i< TAPMuonTracks->size(); i++){
    if(TAPMuonTracks_trkiso->at(i) < 0.2 && TAPMuonTracks_mT->at(i) < 100){
      isoMuonTracks.push_back(TAPMuonTracks->at(i));
      isoMuonTracks_activity.push_back(TAPMuonTracks_activity->at(i));
      isoMuonTracks_chg.push_back(TAPMuonTracks_chg->at(i));
      isoMuonTracks_mT.push_back(TAPMuonTracks_mT->at(i));
      isoMuonTracks_trkiso.push_back(TAPMuonTracks_trkiso->at(i));
    }      
  }
  if(isoMuonTracks.size() != (unsigned) isoMuonTracksNum){
    std::cout << "WARNING! Number of isoMuonTracks is not correct! Skipping event." << std::endl;
    return kTRUE;
  }

  for(unsigned i=0; i< TAPPionTracks->size(); i++){
    if(TAPPionTracks_trkiso->at(i) < 0.1 && TAPPionTracks_mT->at(i) < 100){
      isoPionTracks.push_back(TAPPionTracks->at(i));
      isoPionTracks_activity.push_back(TAPPionTracks_activity->at(i));
      isoPionTracks_chg.push_back(TAPPionTracks_chg->at(i));
      isoPionTracks_mT.push_back(TAPPionTracks_mT->at(i));
      isoPionTracks_trkiso.push_back(TAPPionTracks_trkiso->at(i));
    }      
  }
  if(isoPionTracks.size() != (unsigned) isoPionTracksNum){
    std::cout << "WARNING! Number of isoPionTracks is not correct! Skipping event." << std::endl;
    return kTRUE;
  }

  if(!doIsoTrackStudies){
    tExpectation_->Fill();
    return kTRUE;
  }

  // isotrack studies
  if(GenMuNum_==1 && GenElecNum_==0){
    for(int i=0; i< isoMuonTracksNum; i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),isoMuonTracks.at(i).Eta(),isoMuonTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-isoMuonTracks.at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        muIsoTrackMatchedToGenMu.push_back(1);
      }else{
        muIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoElectronTracksNum;i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),isoElectronTracks.at(i).Eta(),isoElectronTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-isoElectronTracks.at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        elecIsoTrackMatchedToGenMu.push_back(1);
      }else{
        elecIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoPionTracksNum;i++){
      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),isoPionTracks.at(i).Eta(),isoPionTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMus->at(0).Pt()-isoPionTracks.at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTrack_){
        pionIsoTrackMatchedToGenMu.push_back(1);
      }else{
        pionIsoTrackMatchedToGenMu.push_back(0);
      }
    }
  }

  if(GenElecNum_==1 && GenMuNum_==0){
    for(int i=0; i< isoMuonTracksNum; i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),isoMuonTracks.at(i).Eta(),isoMuonTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-isoMuonTracks.at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        muIsoTrackMatchedToGenElec.push_back(1);
      }else{
        muIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  
    for(int i=0; i< isoElectronTracksNum;i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),isoElectronTracks.at(i).Eta(),isoElectronTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-isoElectronTracks.at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        elecIsoTrackMatchedToGenElec.push_back(1);
      }else{
        elecIsoTrackMatchedToGenElec.push_back(0);
      }
    }
      
    for(int i=0; i< isoPionTracksNum;i++){
      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),isoPionTracks.at(i).Eta(),isoPionTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenEls->at(0).Pt()-isoPionTracks.at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTrack_){
        pionIsoTrackMatchedToGenElec.push_back(1);        
      }else{
        pionIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  }
  
  if(GenElecNum_==0 && GenMuNum_==0 && GenTauNum_==1){
    for(int i=0; i< isoMuonTracksNum; i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),isoMuonTracks.at(i).Eta(),isoMuonTracks.at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-isoMuonTracks.at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
        muIsoTrackMatchedToGenSingleProngTau.push_back(1);
      }else{
        muIsoTrackMatchedToGenSingleProngTau.push_back(0);
      }
    }

    for(int i=0; i< isoElectronTracksNum;i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),isoElectronTracks.at(i).Eta(),isoElectronTracks.at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-isoElectronTracks.at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
        elecIsoTrackMatchedToGenSingleProngTau.push_back(1);
      }else{
        elecIsoTrackMatchedToGenSingleProngTau.push_back(0);
      }
    }

    for(int i=0; i< isoPionTracksNum;i++){
      if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),isoPionTracks.at(i).Eta(),isoPionTracks.at(i).Phi())<maxDeltaRGenTauToTrack_ && std::abs(GenTaus->at(0).Pt()-isoPionTracks.at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTrack_){
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

  std::cout<<"--- Search bins ---"<<std::endl;
  SearchBins_->PrintUsed();

}

void ExpecMaker::Terminate()
{
  //GetOutputList()->Print();
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

  isoElectronTracks.clear();
  isoElectronTracks_activity.clear();
  isoElectronTracks_chg.clear();
  isoElectronTracks_mT.clear();
  isoElectronTracks_trkiso.clear();
  isoMuonTracks.clear();
  isoMuonTracks_activity.clear();
  isoMuonTracks_chg.clear();
  isoMuonTracks_mT.clear();
  isoMuonTracks_trkiso.clear();
  isoPionTracks.clear();
  isoPionTracks_activity.clear();
  isoPionTracks_chg.clear();
  isoPionTracks_mT.clear();
  isoPionTracks_trkiso.clear();

  if(doIsoTrackStudies){    
    muIsoTrackMatchedToGenMu.clear();
    elecIsoTrackMatchedToGenMu.clear();
    pionIsoTrackMatchedToGenMu.clear();
      
    muIsoTrackMatchedToGenElec.clear();
    elecIsoTrackMatchedToGenElec.clear();
    pionIsoTrackMatchedToGenElec.clear();
      
    muIsoTrackMatchedToGenSingleProngTau.clear();
    elecIsoTrackMatchedToGenSingleProngTau.clear();
    pionIsoTrackMatchedToGenSingleProngTau.clear();
  }
}

bool ExpecMaker::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    // 2015 only if(CSCTightHaloFilter!=1) result=false;
    // 2015 only if(!eeBadSc4Filter) result=false;
    if(!BadChargedCandidateFilter) result=false;
    if(!BadPFMuonFilter) result=false;
    if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
    if(eeBadScFilter!=1) result=false;
    if(std::abs(globalTightHalo2016Filter)!=1) result=false;
    if(HBHENoiseFilter!=1) result=false;
    if(HBHEIsoNoiseFilter!=1) result=false;
    // Preliminary filters
    if(PFCaloMETRatio>5) result=false;
    for(unsigned j = 0; j < Jets->size(); j++){
    	if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
    		//std::cout<<"found bad muon jet"<<std::endl;
    		result=false;
    	}
    }
  }
  if(NVtx<=0) result=false;
  if(applyJetID) if(!JetID) result=false;
  return result;
}

std::pair <double,double> ExpecMaker::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
  double relPt = 9999;
  double deltaRmin = 9999;

  for (int i=0; i < NJets ; i++)
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

