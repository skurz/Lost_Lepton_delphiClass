#define ExpecMaker_cxx
#include "ExpecMaker.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TSystem.h"
#include <math.h>

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
  //tExpectation_->Branch("madHT",&madHT);
  tExpectation_->Branch("NVtx",&NVtx);
  tExpectation_->Branch("MTW",&mtw);  
  tExpectation_->Branch("DeltaPhi1",&DeltaPhi1);
  tExpectation_->Branch("DeltaPhi2",&DeltaPhi2);
  tExpectation_->Branch("DeltaPhi3",&DeltaPhi3);
  tExpectation_->Branch("DeltaPhi4",&DeltaPhi4);
  tExpectation_->Branch("Weight", &Weight);
  tExpectation_->Branch("MET",&MET);
  tExpectation_->Branch("GenMuonsNum",&GenMuonsNum_);
  tExpectation_->Branch("GenMuonsPt",&GenMuonsPt);
  tExpectation_->Branch("GenMuonsEta",&GenMuonsEta);
  tExpectation_->Branch("GenElectronsNum",&GenElectronsNum_);
  tExpectation_->Branch("GenElectronsPt",&GenElectronsPt);
  tExpectation_->Branch("GenElectronsEta",&GenElectronsEta);
  tExpectation_->Branch("MuonsNum",&MuonsNum_);
  tExpectation_->Branch("ElectronsNum",&ElectronsNum_);
  tExpectation_->Branch("Expectation",&Expectation);  
  tExpectation_->Branch("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  tExpectation_->Branch("isoElectronTracksNum",&isoElectronTracksNum);   
  tExpectation_->Branch("isoMuonTracksNum",&isoMuonTracksNum);   
  tExpectation_->Branch("isoPionTracksNum",&isoPionTracksNum);

  if(!fillEventSeperateBTags){
    tExpectation_->Branch("METUp",&METUp);
    tExpectation_->Branch("METDown",&METDown);
    tExpectation_->Branch("METPhi",&METPhi);
    tExpectation_->Branch("MHTPhi",&MHTPhi);
    tExpectation_->Branch("GenHT",&GenHT);
    tExpectation_->Branch("GenMHT",&GenMHT);
    tExpectation_->Branch("GenMuons", "std::vector<TLorentzVector>", &GenMuons,32000,0);
    tExpectation_->Branch("GenMuons_MT2Activity", &GenMuons_MT2Activity);  
    tExpectation_->Branch("GenElectrons", "std::vector<TLorentzVector>", &GenElectrons, 32000, 0);
    tExpectation_->Branch("GenElectrons_MT2Activity", &GenElectrons_MT2Activity);
    //tExpectation_->Branch("GenMuDeltaRJet",&GenMuDeltaRJet_);
    //tExpectation_->Branch("GenMuRelPTJet",&GenMuRelPTJet_);
    //tExpectation_->Branch("GenElecDeltaRJet", &GenElecDeltaRJet_);
    //tExpectation_->Branch("GenElecRelPTJet", &GenElecRelPTJet_);
    tExpectation_->Branch("GenTausNum",&GenTausNum_);
    tExpectation_->Branch("GenTaus", "std::vector<TLorentzVector>", &GenTaus, 32000, 0); 
    tExpectation_->Branch("GenTaus_MT2Activity", &GenTaus_MT2Activity);
    tExpectation_->Branch("muAcc",&muAcc);  
    tExpectation_->Branch("muReco",&muReco);  
    tExpectation_->Branch("muIso",&muIso);  
    tExpectation_->Branch("MTW_METup",&mtw_METup);  
    tExpectation_->Branch("MTW_METdown",&mtw_METdown);  
    tExpectation_->Branch("elecAcc",&elecAcc);  
    tExpectation_->Branch("elecReco",&elecReco);  
    tExpectation_->Branch("elecIso",&elecIso);   
    tExpectation_->Branch("MuPurity",&MuPurity_); 
    tExpectation_->Branch("ElecPurity",&ElecPurity_); 
    tExpectation_->Branch("Muons", "std::vector<TLorentzVector>", &Muons, 32000, 0);
    tExpectation_->Branch("MuonsPromptMatched", &MuonsPromptMatched);
    tExpectation_->Branch("Muons_MT2Activity", &Muons_MT2Activity);
    //tExpectation_->Branch("MuonsNoIsoNum",&MuonsNoIsoNum_);
    //tExpectation_->Branch("MuonsNoIso", "std::vector<TLorentzVector>", &MuonsNoIso, 32000, 0);
    //tExpectation_->Branch("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity); 
    tExpectation_->Branch("Electrons", "std::vector<TLorentzVector>", &Electrons, 32000, 0);
    tExpectation_->Branch("ElectronsPromptMatched", &ElectronsPromptMatched);
    tExpectation_->Branch("Electrons_MT2Activity", &Electrons_MT2Activity);
    //tExpectation_->Branch("ElectronsNoIsoNum",&ElectronsNoIsoNum_);
    //tExpectation_->Branch("ElectronsNoIso", "std::vector<TLorentzVector>", &ElectronsNoIso, 32000, 0);
    //tExpectation_->Branch("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity);
    tExpectation_->Branch("isoElectronTracks", "std::vector<TLorentzVector>", &isoElectronTracks, 32000, 0);
    tExpectation_->Branch("isoMuonTracks", "std::vector<TLorentzVector>", &isoMuonTracks, 32000, 0);  
    tExpectation_->Branch("isoPionTracks", "std::vector<TLorentzVector>", &isoPionTracks, 32000, 0);

    //tExpectation_->Branch("Jets_HTMask", &Jets_HTMask);
    //tExpectation_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
    tExpectation_->Branch("bTagProb", &bTagProb);
    tExpectation_->Branch("cosDTT", &cosDTT);
    tExpectation_->Branch("genCosDTT", &genCosDTT);
    tExpectation_->Branch("PDFweights", &PDFweights);
    tExpectation_->Branch("ScaleWeights", &ScaleWeights);
    tExpectation_->Branch("ExpectationDiLep",&ExpectationDiLep_);
    tExpectation_->Branch("MuDiLepControlSample",&MuDiLepControlSample_);
    tExpectation_->Branch("ElecDiLepControlSample",&ElecDiLepControlSample_);
  }

  if(doTAPtrees){
    tExpectation_->Branch("isoElectronTracks_activity", &isoElectronTracks_activity);
    tExpectation_->Branch("isoElectronTracks_charge", &isoElectronTracks_charge);
    tExpectation_->Branch("isoElectronTracks_mT", &isoElectronTracks_mT);
    tExpectation_->Branch("isoElectronTracks_trkiso", &isoElectronTracks_trkiso);
    tExpectation_->Branch("isoMuonTracks_activity", &isoMuonTracks_activity);
    tExpectation_->Branch("isoMuonTracks_charge", &isoMuonTracks_charge);
    tExpectation_->Branch("isoMuonTracks_mT", &isoMuonTracks_mT);
    tExpectation_->Branch("isoMuonTracks_trkiso", &isoMuonTracks_trkiso);
    tExpectation_->Branch("isoPionTracks_activity", &isoPionTracks_activity);
    tExpectation_->Branch("isoPionTracks_charge", &isoPionTracks_charge);
    tExpectation_->Branch("isoPionTracks_mT", &isoPionTracks_mT);
    tExpectation_->Branch("isoPionTracks_trkiso", &isoPionTracks_trkiso);
    tExpectation_->Branch("TAPElectronTracks", "std::vector<TLorentzVector>", &TAPElectronTracks, 32000, 0);
    tExpectation_->Branch("TAPElectronTracks_activity", &TAPElectronTracks_activity);
    tExpectation_->Branch("TAPElectronTracks_charge", &TAPElectronTracks_charge);
    tExpectation_->Branch("TAPElectronTracks_mT", &TAPElectronTracks_mT);
    tExpectation_->Branch("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso);
    tExpectation_->Branch("TAPMuonTracks", "std::vector<TLorentzVector>", &TAPMuonTracks, 32000, 0);
    tExpectation_->Branch("TAPMuonTracks_activity", &TAPMuonTracks_activity);
    tExpectation_->Branch("TAPMuonTracks_charge", &TAPMuonTracks_charge);
    tExpectation_->Branch("TAPMuonTracks_mT", &TAPMuonTracks_mT);
    tExpectation_->Branch("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso);
    tExpectation_->Branch("TAPPionTracks", "std::vector<TLorentzVector>", &TAPPionTracks, 32000, 0);
    tExpectation_->Branch("TAPPionTracks_activity", &TAPPionTracks_activity);
    tExpectation_->Branch("TAPPionTracks_charge", &TAPPionTracks_charge);
    tExpectation_->Branch("TAPPionTracks_mT", &TAPPionTracks_mT);
    tExpectation_->Branch("TAPPionTracks_trkiso", &TAPPionTracks_trkiso);
    tExpectation_->Branch("GenElectrons_fromTau", &GenElectrons_fromTau);
    tExpectation_->Branch("GenElectrons_RecoTrkAct", &GenElectrons_RecoTrkAct);
    tExpectation_->Branch("GenElectrons_RecoTrkd3", &GenElectrons_RecoTrkd3);
    tExpectation_->Branch("GenElectrons_RecoTrkIso", &GenElectrons_RecoTrkIso);
    tExpectation_->Branch("GenMuons_fromTau", &GenMuons_fromTau);
    tExpectation_->Branch("GenMuons_RecoTrkAct", &GenMuons_RecoTrkAct);
    tExpectation_->Branch("GenMuons_RecoTrkd3", &GenMuons_RecoTrkd3);
    tExpectation_->Branch("GenMuons_RecoTrkIso", &GenMuons_RecoTrkIso);
    tExpectation_->Branch("GenTaus_had", &GenTaus_had);
    tExpectation_->Branch("GenTaus_LeadRecoTrkAct", &GenTaus_LeadRecoTrkAct);
    tExpectation_->Branch("GenTaus_LeadRecoTrkd3", &GenTaus_LeadRecoTrkd3);
    tExpectation_->Branch("GenTaus_LeadRecoTrkIso", &GenTaus_LeadRecoTrkIso);
    tExpectation_->Branch("GenTaus_LeadTrk", "std::vector<TLorentzVector>", &GenTaus_LeadTrk, 32000, 0);
    tExpectation_->Branch("GenTaus_NProngs", &GenTaus_NProngs);
    tExpectation_->Branch("GenTaus_Nu", "std::vector<TLorentzVector>", &GenTaus_Nu, 32000, 0);
  }

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

  SearchBins_ = new SearchBins(false);
  SearchBinsQCD_ = new SearchBins(true); // QCD binning
  
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
  
  GetOutputList()->Add(tExpectation_);

  fudgeFactors = {0.931355, 0.913146, 0.866418, 0.799251, 0.706555, 0.567275, 0.422828};
}

Bool_t ExpecMaker::Process(Long64_t entry)
{

  resetValues();
  fChain->GetTree()->GetEntry(entry);

//  if(entry % 3 != 0) return kTRUE;

  GenMuonsNum_ = GenMuons->size();
  GenElectronsNum_ = GenElectrons->size();
  GenTausNum_ = GenTaus->size();

  MuonsNoIsoNum_ = MuonsNoIso->size();
  MuonsNum_ = Muons->size();
  ElectronsNoIsoNum_ = ElectronsNoIso->size();
  ElectronsNum_ = Electrons->size();

  if(GenElectronsNum_>0){
    GenElectronsPt = GenElectrons->at(0).Pt();
    GenElectronsEta = GenElectrons->at(0).Eta();
  }
  if(GenMuonsNum_>0){
    GenMuonsPt = GenMuons->at(0).Pt();
    GenMuonsEta = GenMuons->at(0).Eta();
  }
/*
  if(GenElectronsNum_>0){
  	if(GenElectronsPt > 300){
  		if(std::abs(GenElectronsEta) < 1.4442) GenElectronsPt = GenElectronsPt * 0.8;
      else GenElectronsPt = GenElectronsPt * 1.00;
      double scaledPt = GenElectrons->at(0).Pt() - GenElectronsPt;
  		double phiE = GenElectrons->at(0).Phi();
  		HT = HT - scaledPt;
  		MHT = sqrt((MHT*cos(MHTPhi)-scaledPt*cos(phiE))*(MHT*cos(MHTPhi)-scaledPt*cos(phiE))+(MHT*sin(MHTPhi)-scaledPt*sin(phiE))*(MHT*sin(MHTPhi)-scaledPt*sin(phiE)));
  	}
  }
*/
  // genLevel HTcut
  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;

  // std::cout << "Applying skim cuts..." << std::endl;
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_ ) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;

  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);
  //    std::cout << "Event falls in bin " << Bin_ << std::endl;
  isoTracksNum = isoMuonTracksNum + isoPionTracksNum + isoElectronTracksNum;

  if(!doTAPtrees) if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;

  //if(useTrigger) if(!TriggerPass->at(34) && !TriggerPass->at(35) && !TriggerPass->at(36)) return kTRUE;

  if(doBTagCorrFullSim || doBTagCorrFastSim){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());

    if(currentTree != treeName){
      treeName = currentTree;
/*
      fudgeFactorWeight = 1;
      
      if((std::string(treeName.Data()).find(std::string("WJetsToLNu"))) != std::string::npos){
        if((std::string(treeName.Data()).find(std::string("100to200"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(0);
        }else if((std::string(treeName.Data()).find(std::string("200to400"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(1);
        }else if((std::string(treeName.Data()).find(std::string("400to600"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(2);
        }else if((std::string(treeName.Data()).find(std::string("600to800"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(3);
        }else if((std::string(treeName.Data()).find(std::string("800to1200"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(4);
        }else if((std::string(treeName.Data()).find(std::string("1200to2500"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(5);
        }else if((std::string(treeName.Data()).find(std::string("2500toInf"))) != std::string::npos){
          fudgeFactorWeight = fudgeFactors.at(6);
        }else{
          std::cout<<"FudgeFactor not found"<<std::endl;
        }
      }
      std::cout<<"FudgeFactor: "<<fudgeFactorWeight<<std::endl;
*/
      if(btagcorr!=0){
        delete btagcorr;
        btagcorr = 0;
      }
      btagcorr = new BTagCorrector();

      TObjArray *optionArray = currentTree.Tokenize("/");
      TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();

      TFile *skimFile = TFile::Open(path_toSkims+currFileName, "READ");

      btagcorr->SetEffs(skimFile);
      btagcorr->SetCalib(path_bTagCalib);      
      if(doBTagCorrFastSim){
        btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
        btagcorr->SetFastSim(true);
      }
      else btagcorr->SetFastSim(false);
    }
    bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
  }
  else bTagProb = {0, 0, 0, 0};

  if(useTriggerEffWeight) Weight = Weight * GetTriggerEffWeight(MHT);

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

  //Account for efficiency of JetID since we cannot apply it on fastSim
  if(!applyJetID) Weight *= 0.99;

  //Weight *= fudgeFactorWeight;

  if(MuonsNum_==1 && ElectronsNum_==0){
  mtw =  Muons_MTW->at(0);
  //mtw =  MTWCalculator(MET,METPhi, Muons->at(0).Pt(), Muons->at(0).Phi(), scaleMet);
  mtw_METup = MTWCalculator(METUp->at(1),METPhiUp->at(1), Muons->at(0).Pt(), Muons->at(0).Phi(), scaleMet);
  mtw_METdown = MTWCalculator(METDown->at(1),METPhiDown->at(1), Muons->at(0).Pt(), Muons->at(0).Phi(), scaleMet);
  }
  if(MuonsNum_==0 && ElectronsNum_==1){
    mtw =  Electrons_MTW->at(0);
 	//mtw =  MTWCalculator(MET,METPhi, Electrons->at(0).Pt(), Electrons->at(0).Phi(), scaleMet);
 	mtw_METup = MTWCalculator(METUp->at(1),METPhiUp->at(1), Electrons->at(0).Pt(), Electrons->at(0).Phi(), scaleMet);
 	mtw_METdown = MTWCalculator(METDown->at(1),METPhiDown->at(1), Electrons->at(0).Pt(), Electrons->at(0).Phi(), scaleMet);
  }

  // Muons
  if(GenMuonsNum_==1 && GenElectronsNum_==0){ 
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHTPhi, GenMuons->at(0).Pt(), GenMuons->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHTPhi, GenMuons->at(0).Pt(), GenMuons->at(0).Phi()));
    
    bool outAcc = false;
    if(GenMuons->at(0).Pt() < minMuPt_ || std::abs(GenMuons->at(0).Eta()) > maxMuEta_){
      outAcc = true;
    }
    /*
    if(outAcc){
      for (UShort_t i=0; i<MuonsNoIsoNum_; i++){
        if(deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),MuonsNoIso->at(i).Eta(),MuonsNoIso->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMuons->at(0).Pt()-MuonsNoIso->at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenToRecoMu_){
          outAcc = false;
          break;
        }
      }
    }
    */  

    if(outAcc){
      muAcc=0;
      Expectation=1;
    }else{
      muAcc=2;
      bool RecoNotMatched=true; 

      for (UShort_t i=0; i<MuonsNoIsoNum_; i++){
        if(deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),MuonsNoIso->at(i).Eta(),MuonsNoIso->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMuons->at(0).Pt()-MuonsNoIso->at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenToRecoMu_){
          RecoNotMatched=false;          
          muReco =2;
          bool IsoNotMatched=true;

          for (UShort_t ii=0; ii < MuonsNum_; ii++){
            if(deltaR(Muons->at(ii).Eta(),Muons->at(ii).Phi(),MuonsNoIso->at(i).Eta(),MuonsNoIso->at(i).Phi())<maxDeltaRRecoToIsoMu_ && std::abs(Muons->at(ii).Pt()-MuonsNoIso->at(i).Pt())/Muons->at(ii).Pt() <maxDiffPtRecoToIsoMu_){
              IsoNotMatched=false;
              muIso=2;
              Expectation=2;
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
  if(GenMuonsNum_==0 && GenElectronsNum_==1){
    genCosDTT = 0.5 * (1. - GetCosDTT(GenMHT, GenMHTPhi, GenElectrons->at(0).Pt(), GenElectrons->at(0).Phi()));
    cosDTT = 0.5 * (1. - GetCosDTT(MHT, MHTPhi, GenElectrons->at(0).Pt(), GenElectrons->at(0).Phi()));

    bool outAcc = false;
    if(GenElectrons->at(0).Pt() < minElecPt_ || std::abs(GenElectrons->at(0).Eta()) > maxElecEta_){
      outAcc = true;
    }
    /*
    if(outAcc){
      for (UShort_t i=0; i<ElectronsNoIsoNum_; i++){
        if(deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),ElectronsNoIso->at(i).Eta(),ElectronsNoIso->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenElectrons->at(0).Pt()-ElectronsNoIso->at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenToRecoElec_){
          outAcc = false;
          break;
        }
      }
    }
    */

    if(outAcc){
      elecAcc=0;
      Expectation=1;
    }else{
      elecAcc=2;
      bool RecoNotMatched=true;

      for (UShort_t i=0; i<ElectronsNoIsoNum_; i++){
        if(deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),ElectronsNoIso->at(i).Eta(),ElectronsNoIso->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenElectrons->at(0).Pt()-ElectronsNoIso->at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenToRecoElec_){
          RecoNotMatched=false;
          elecReco =2;
          bool IsoNotMatched=true;

          for (UShort_t ii=0; ii < ElectronsNum_; ii++){
            if(deltaR(Electrons->at(ii).Eta(),Electrons->at(ii).Phi(),ElectronsNoIso->at(i).Eta(),ElectronsNoIso->at(i).Phi())<maxDeltaRRecoToIsoElec_ && std::abs(Electrons->at(ii).Pt()-ElectronsNoIso->at(i).Pt())/Electrons->at(ii).Pt() <maxDiffPtRecoToIsoElec_){
              IsoNotMatched=false;
              elecIso=2;
              Expectation=2;
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
/*  for(unsigned int i=0; i< GenMuonsNum_;i++){
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMuons->at(i).Pt(),GenMuons->at(i).Eta(),GenMuons->at(i).Phi());
      GenMuDeltaRJet_.push_back(DeltaR_relPT.first);
      GenMuRelPTJet_.push_back(DeltaR_relPT.second);
  }
  for(unsigned int i=0; i< GenElectronsNum_;i++){
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenElectrons->at(i).Pt(),GenElectrons->at(i).Eta(),GenElectrons->at(i).Phi());
      GenElecDeltaRJet_.push_back(DeltaR_relPT.first);
      GenElecRelPTJet_.push_back(DeltaR_relPT.second);
  }
*/
  // di leptonic events
  if((GenMuonsNum_+GenElectronsNum_)==2){
    if(MuonsNum_==0 && ElectronsNum_==0){
      Expectation=1;
      ExpectationDiLep_=1;
    }
    if(MuonsNum_==1 && ElectronsNum_==0){
      MuDiLepControlSample_=0;
    }
    if(MuonsNum_==0 && ElectronsNum_==1){
      ElecDiLepControlSample_=0;
    }
  }

  // new purity studies
  if(MuonsNum_==1 && ElectronsNum_==0 && (GenMuonsNum_ + GenElectronsNum_)<2){
    if(GenMuonsNum_<1){
      MuPurity_=0;
    }
    else{
      MuPurity_=2;
    }
  }
  if(MuonsNum_==0 && ElectronsNum_==1 && (GenMuonsNum_+ GenElectronsNum_)<2){
    if(GenElectronsNum_<1){
      ElecPurity_=0;
    }else{
      ElecPurity_=2;
    }
  }

  //old purity calculations
  for (UShort_t i=0; i< MuonsNum_;i++){
    if(MuonsNum_>1 || Muons_MTW->at(0)>mtwCut_){
      MuonsPromptMatched.push_back(-1);
      continue;
    }

    bool matched=false;
    double best_score=999.;
    double MuonsPromptMatchedDeltaR_=999., MuonsPromptMatchedRelPt_=999.;
    TVector3 recoMu3(Muons->at(i).Px(), Muons->at(i).Py(), Muons->at(i).Pz());

    for(UShort_t ii=0; ii<GenMuonsNum_;ii++){
      TVector3 genMu3(GenMuons->at(ii).Px(), GenMuons->at(ii).Py(), GenMuons->at(ii).Pz());
      double this_score=(recoMu3-genMu3).Mag2();
      MuonsPromptMatchedDeltaR_=deltaR(Muons->at(i).Eta(),Muons->at(i).Phi(),GenMuons->at(ii).Eta(),GenMuons->at(ii).Phi());
      MuonsPromptMatchedRelPt_=(Muons->at(i).Pt()-GenMuons->at(ii).Pt())/Muons->at(i).Pt();
      if(this_score<best_score&&MuonsPromptMatchedDeltaR_<maxDeltaRIsoToGenMu_ && MuonsPromptMatchedRelPt_<maxDiffPtIsoToGenMu_){
        matched=true;
      }
    }
    if(matched){
      MuonsPromptMatched.push_back(1);
    }else{
      MuonsPromptMatched.push_back(0);
    }
  }

  for (UShort_t i=0; i< ElectronsNum_;i++){
    if(ElectronsNum_>1 || Electrons_MTW->at(0)>mtwCut_){
      ElectronsPromptMatched.push_back(-1);
      continue;
    }

    bool matched=false;
    double best_score=999.;
    double ElectronsPromptMatchedDeltaR_=999., ElectronsPromptMatchedRelPt_=999.;
    TVector3 recoEl3(Electrons->at(i).Px(), Electrons->at(i).Py(), Electrons->at(i).Pz());
    for(UShort_t ii=0; ii<GenElectronsNum_;ii++){
      TVector3 genEl3(GenElectrons->at(ii).Px(), GenElectrons->at(ii).Py(), GenElectrons->at(ii).Pz());
      double this_score=(recoEl3-genEl3).Mag2();
      ElectronsPromptMatchedDeltaR_=deltaR(Electrons->at(i).Eta(),Electrons->at(i).Phi(),GenElectrons->at(ii).Eta(),GenElectrons->at(ii).Phi());
      ElectronsPromptMatchedRelPt_=(Electrons->at(i).Pt()-GenElectrons->at(ii).Pt())/Electrons->at(i).Pt();

      if(this_score<best_score&&ElectronsPromptMatchedDeltaR_<maxDeltaRIsoToGenElec_ && ElectronsPromptMatchedRelPt_<maxDiffPtIsoToGenElec_){
        matched=true;
      }
    }
    if(matched){
      ElectronsPromptMatched.push_back(1);
    }else{
      ElectronsPromptMatched.push_back(0);
    }
  }
  
  // check weather a background event according to plane lepton veto gets rejected by the isolated track veto with MT cut applied
  if(isoTracksNum>=1 && Expectation==1){
    ExpectationReductionIsoTrack=1;
  }

  if(fillEventSeperateBTags){
    for(int i = 0; i < (NJets == 2 ? 3 : 4); i++){
      Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,i);
      BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,i);
      BTags = i;

      double storeWeight = Weight;
      Weight *= bTagProb.at(i);

      tExpectation_->Fill();

      Weight = storeWeight;
    }
    return kTRUE;
  }

  // get isoTrack collection from full TAP collection
  for(unsigned i=0; i< TAPElectronTracks->size(); i++){
    if(TAPElectronTracks_trkiso->at(i) < 0.2 && TAPElectronTracks_mT->at(i) < 100){
      isoElectronTracks.push_back(TAPElectronTracks->at(i));
      isoElectronTracks_activity.push_back(TAPElectronTracks_activity->at(i));
      isoElectronTracks_charge.push_back(TAPElectronTracks_charge->at(i));
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
      isoMuonTracks_charge.push_back(TAPMuonTracks_charge->at(i));
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
      isoPionTracks_charge.push_back(TAPPionTracks_charge->at(i));
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
  if(GenMuonsNum_==1 && GenElectronsNum_==0){
    for(int i=0; i< isoMuonTracksNum; i++){
      if(deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),isoMuonTracks.at(i).Eta(),isoMuonTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMuons->at(0).Pt()-isoMuonTracks.at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenMuToTrack_){
        muIsoTrackMatchedToGenMu.push_back(1);
      }else{
        muIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoElectronTracksNum;i++){
      if(deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),isoElectronTracks.at(i).Eta(),isoElectronTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMuons->at(0).Pt()-isoElectronTracks.at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenMuToTrack_){
        elecIsoTrackMatchedToGenMu.push_back(1);
      }else{
        elecIsoTrackMatchedToGenMu.push_back(0);
      }
    }

    for(int i=0; i< isoPionTracksNum;i++){
      if(deltaR(GenMuons->at(0).Eta(),GenMuons->at(0).Phi(),isoPionTracks.at(i).Eta(),isoPionTracks.at(i).Phi())<maxDeltaRGenMuToTrack_ && std::abs(GenMuons->at(0).Pt()-isoPionTracks.at(i).Pt())/GenMuons->at(0).Pt() <maxDiffPtGenMuToTrack_){
        pionIsoTrackMatchedToGenMu.push_back(1);
      }else{
        pionIsoTrackMatchedToGenMu.push_back(0);
      }
    }
  }

  if(GenElectronsNum_==1 && GenMuonsNum_==0){
    for(int i=0; i< isoMuonTracksNum; i++){
      if(deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),isoMuonTracks.at(i).Eta(),isoMuonTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenElectrons->at(0).Pt()-isoMuonTracks.at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenElecToTrack_){
        muIsoTrackMatchedToGenElec.push_back(1);
      }else{
        muIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  
    for(int i=0; i< isoElectronTracksNum;i++){
      if(deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),isoElectronTracks.at(i).Eta(),isoElectronTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenElectrons->at(0).Pt()-isoElectronTracks.at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenElecToTrack_){
        elecIsoTrackMatchedToGenElec.push_back(1);
      }else{
        elecIsoTrackMatchedToGenElec.push_back(0);
      }
    }
      
    for(int i=0; i< isoPionTracksNum;i++){
      if(deltaR(GenElectrons->at(0).Eta(),GenElectrons->at(0).Phi(),isoPionTracks.at(i).Eta(),isoPionTracks.at(i).Phi())<maxDeltaRGenElecToTrack_ && std::abs(GenElectrons->at(0).Pt()-isoPionTracks.at(i).Pt())/GenElectrons->at(0).Pt() <maxDiffPtGenElecToTrack_){
        pionIsoTrackMatchedToGenElec.push_back(1);        
      }else{
        pionIsoTrackMatchedToGenElec.push_back(0);
      }
    }
  }
  
  if(GenElectronsNum_==0 && GenMuonsNum_==0 && GenTausNum_==1){
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

  outPutFile->Close();

  cout << "Saved output to " << fileName << endl;
	
}

void ExpecMaker::resetValues()
{
  GenMuonsPt=0;
  GenMuonsEta=0;
  GenElectronsPt=0;
  GenElectronsEta=0;

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
  
  MuonsPromptMatched.clear();
  ElectronsPromptMatched.clear();

  GenMuDeltaRJet_.clear();
  GenMuRelPTJet_.clear();
  GenElecDeltaRJet_.clear();
  GenElecRelPTJet_.clear();

  isoElectronTracks.clear();
  isoElectronTracks_activity.clear();
  isoElectronTracks_charge.clear();
  isoElectronTracks_mT.clear();
  isoElectronTracks_trkiso.clear();
  isoMuonTracks.clear();
  isoMuonTracks_activity.clear();
  isoMuonTracks_charge.clear();
  isoMuonTracks_mT.clear();
  isoMuonTracks_trkiso.clear();
  isoPionTracks.clear();
  isoPionTracks_activity.clear();
  isoPionTracks_charge.clear();
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
    if(HBHENoiseFilter!=1) result=false;
    if(HBHEIsoNoiseFilter!=1) result=false;
    if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
    if(eeBadScFilter!=1) result=false;
    // Data only
    //if(!BadChargedCandidateFilter) result=false;
    //if(!BadPFMuonFilter) result=false;
    //if(globalTightHalo2016Filter!=1) result=false;
  }
  if(NVtx<=0) result=false;
  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;

  // Do not apply on fastSim samples!
  if(!JetID) result=false;

  if(result)
  for(unsigned j = 0; j < Jets->size(); j++){
    if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
    else if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
      //std::cout<<"found bad muon jet"<<std::endl;
      result=false;
    }
  }

  
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

