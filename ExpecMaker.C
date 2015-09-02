#define ExpecMaker_cxx
#include "ExpecMaker.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

	
  tExpectation_ = new TTree("LostLeptonExpectation","a simple Tree with simple variables");

  tExpectation_->Branch("EvtNum",&EvtNum,"EvtNum/i");
  tExpectation_->Branch("HT",&HT);
  tExpectation_->Branch("MHT",&MHT);
  tExpectation_->Branch("NJets",&NJets);
  tExpectation_->Branch("BTags",&BTags);
  tExpectation_->Branch("Leptons",&Leptons);
  tExpectation_->Branch("isoTracks",&isoTracks);
  DY=DY_;
  tExpectation_->Branch("DY",&DY);
  tExpectation_->Branch("Bin",&Bin_);
  tExpectation_->Branch("BinQCD",&BinQCD_);
  tExpectation_->Branch("NVtx",&NVtx);
  tExpectation_->Branch("DeltaPhi1",&DeltaPhi1);
  tExpectation_->Branch("DeltaPhi2",&DeltaPhi2);
  tExpectation_->Branch("DeltaPhi3",&DeltaPhi3);
  tExpectation_->Branch("minDeltaPhiN",&minDeltaPhiN);
  tExpectation_->Branch("DeltaPhiN1",&DeltaPhiN1);
  tExpectation_->Branch("DeltaPhiN2",&DeltaPhiN2);
  tExpectation_->Branch("DeltaPhiN3",&DeltaPhiN3);
  tExpectation_->Branch("Weight", &Weight);
  tExpectation_->Branch("MET",&METPt);
  tExpectation_->Branch("METPhi",&METPhi);
  tExpectation_->Branch("PTW",&ptw);  
  tExpectation_->Branch("GenPTW",&gen_ptw);
  tExpectation_->Branch("GenMuNum",&GenMuNum_);
  tExpectation_->Branch("GenMus", "std::vector<TLorentzVector>", &GenMus,32000,0);
  tExpectation_->Branch("GenMuWPt",&GenMuWPt_);
  tExpectation_->Branch("GenMuFromTau", &GenMu_GenMuFromTau);
  tExpectation_->Branch("GenMuDeltaRJet",&GenMuDeltaRJet_);
  tExpectation_->Branch("GenMuRelPTJet",&GenMuRelPTJet_);
  tExpectation_->Branch("GenMuonIsoTrackMatched", &GenMuonIsoTrackMatched); 
  tExpectation_->Branch("GenMuonActivity", &GenMuonActivity);
  tExpectation_->Branch("GenElecNum",&GenElecNum_);
  tExpectation_->Branch("GenEls", "std::vector<TLorentzVector>", &GenEls, 32000, 0);
  tExpectation_->Branch("GenElecWPt",&GenElecWPt_);
  tExpectation_->Branch("GenElecFromTau", &GenElec_GenElecFromTau);
  tExpectation_->Branch("GenElecDeltaRJet", &GenElecDeltaRJet_);
  tExpectation_->Branch("GenElecRelPTJet", &GenElecRelPTJet_);
  tExpectation_->Branch("GenElecIsoTrackMatched", &GenElecIsoTrackMatched); 
  tExpectation_->Branch("GenElecActivity", &GenElecActivity);
  tExpectation_->Branch("GenTauNum",&GenTauNum_);
  tExpectation_->Branch("GenTaus", "std::vector<TLorentzVector>", &GenTaus, 32000, 0); 
  tExpectation_->Branch("GenTau_GenTauHad", &GenTau_GenTauHad); 
  tExpectation_->Branch("GenTauIsoTrackMatched", &GenTauIsoTrackMatched); 
  tExpectation_->Branch("GenTauActivity", &GenTauActivity);
  tExpectation_->Branch("GenTauNu", "std::vector<TLorentzVector>", &GenTauNu, 32000, 0); 
  tExpectation_->Branch("Expectation",&Expectation);  
  tExpectation_->Branch("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  tExpectation_->Branch("muAcc",&muAcc);  
  tExpectation_->Branch("muReco",&muReco);  
  tExpectation_->Branch("muIso",&muIso);  
  tExpectation_->Branch("MTW",&mtw);  
  tExpectation_->Branch("IsoTrackMTW",&isoTrackMTW_); 
  tExpectation_->Branch("elecAcc",&elecAcc);  
  tExpectation_->Branch("elecReco",&elecReco);  
  tExpectation_->Branch("elecIso",&elecIso);  
  tExpectation_->Branch("muIsoTrack",&muIsoTrack);  
  tExpectation_->Branch("MuPurity",&MuPurity_); 
  tExpectation_->Branch("ElecPurity",&ElecPurity_); 
  muActivityMethod=muActivityMethod_;
  elecActivityMethod=elecActivityMethod_;
  muIsoTrackActivityMethod=muIsoTrackActivityMethod_;
  elecIsoTrackActivityMethod=elecIsoTrackActivityMethod_;
  pionIsoTrackActivityMethod=pionIsoTrackActivityMethod_;
  tExpectation_->Branch("muActivityMethod",&muActivityMethod);  
  tExpectation_->Branch("elecActivityMethod",&elecActivityMethod);  
  tExpectation_->Branch("muIsoTrackActivityMethod",&muIsoTrackActivityMethod);
  tExpectation_->Branch("elecIsoTrackActivityMethod",&elecIsoTrackActivityMethod);
  tExpectation_->Branch("pionIsoTrackActivityMethod",&pionIsoTrackActivityMethod);
  tExpectation_->Branch("FallsVetoLep",&FallsVetoLep);
  tExpectation_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum_);
  tExpectation_->Branch("selectedIDIsoMuons", "std::vector<TLorentzVector>", &selectedIDIsoMuons, 32000, 0);
  tExpectation_->Branch("muIsoMatched", &muIsoMatched);
  tExpectation_->Branch("selectedIDIsoMuonsPromptMatched", &selectedIDIsoMuonsPromptMatched);
  tExpectation_->Branch("selectedIDIsoMuonsPromptMatchedDeltaR", &selectedIDIsoMuonsPromptMatchedDeltaR);
  tExpectation_->Branch("selectedIDIsoMuonsPromptMatchedRelPt", &selectedIDIsoMuonsPromptMatchedRelPt);
  tExpectation_->Branch("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW);
  tExpectation_->Branch("selectedIDIsoMuonsActivity", &selectedIDIsoMuonsActivity);
  tExpectation_->Branch("selectedIDMuonsNum",&selectedIDMuonsNum_);
  tExpectation_->Branch("selectedIDMuons", "std::vector<TLorentzVector>", &selectedIDMuons, 32000, 0);
  tExpectation_->Branch("selectedIDMuonsMatched", &muRecoMatched);
  tExpectation_->Branch("selectedIDMuons_MTW", &selectedIDMuons_MTW);
  tExpectation_->Branch("selectedIDMuonsActivity", &selectedIDMuonsActivity);
  tExpectation_->Branch("selectedIDIsoMuonsIsoTrackMatched", &selectedIDIsoMuonsIsoTrackMatched);  
  tExpectation_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum_);
  tExpectation_->Branch("selectedIDIsoElectrons", "std::vector<TLorentzVector>", &selectedIDIsoElectrons, 32000, 0);
  tExpectation_->Branch("elecIsoMatched", &elecIsoMatched);
  tExpectation_->Branch("selectedIDIsoElectronsPromptMatched", &selectedIDIsoElectronsPromptMatched);
  tExpectation_->Branch("selectedIDIsoElectronsPromptMatchedDeltaR", &selectedIDIsoElectronsPromptMatchedDeltaR);
  tExpectation_->Branch("selectedIDIsoElectronsPromptMatchedRelPt", &selectedIDIsoElectronsPromptMatchedRelPt);
  tExpectation_->Branch("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW);
  tExpectation_->Branch("selectedIDIsoElectronsActivity", &selectedIDIsoElectronsActivity);
  tExpectation_->Branch("selectedIDIsoElectronsIsoTrackMatched", &selectedIDIsoElectronsIsoTrackMatched);
  tExpectation_->Branch("selectedIDElectronsNum",&selectedIDElectronsNum_);
  tExpectation_->Branch("selectedIDElectrons", "std::vector<TLorentzVector>", &selectedIDElectrons, 32000, 0);
  tExpectation_->Branch("selectedIDElectronsMatched", &elecRecoMatched);
  tExpectation_->Branch("selectedIDElectrons_MTW", &selectedIDElectrons_MTW);
  tExpectation_->Branch("selectedIDElectronsActivity", &selectedIDElectronsActivity);
	
  if(!DY_)
    {
      tExpectation_->Branch("isoElectronTracks",&isoElectronTracks);
      tExpectation_->Branch("IsolatedElectronTracksVeto", "std::vector<TLorentzVector>", &IsolatedElectronTracksVeto, 32000, 0);
      tExpectation_->Branch("IsolatedElectronTracksVetoActivity", &IsolatedElectronTracksVetoActivity);
      tExpectation_->Branch("IsolatedElectronTracksVetoMTW", &IsolatedElectronTracksVetoMTW);
      tExpectation_->Branch("muIsoTrackMatchedToGenElec", &muIsoTrackMatchedToGenElec);
      tExpectation_->Branch("elecIsoTrackMatchedToGenElec", &elecIsoTrackMatchedToGenElec);
      tExpectation_->Branch("pionIsoTrackMatchedToGenElec", &pionIsoTrackMatchedToGenElec);
	
      tExpectation_->Branch("isoMuonTracks",&isoMuonTracks);
      tExpectation_->Branch("IsolatedMuonTracksVeto", "std::vector<TLorentzVector>", &IsolatedMuonTracksVeto, 32000, 0);
      tExpectation_->Branch("IsolatedMuonTracksVetoActivity", &IsolatedMuonTracksVetoActivity);
      tExpectation_->Branch("IsolatedMuonTracksVetoMTW", &IsolatedMuonTracksVetoMTW);
      tExpectation_->Branch("muIsoTrackMatchedToGenMu", &muIsoTrackMatchedToGenMu);
      tExpectation_->Branch("elecIsoTrackMatchedToGenMu", &elecIsoTrackMatchedToGenMu);
      tExpectation_->Branch("pionIsoTrackMatchedToGenMu", &pionIsoTrackMatchedToGenMu);
      tExpectation_->Branch("isoPionTracks",&isoPionTracks);
      tExpectation_->Branch("IsolatedPionTracksVeto", "std::vector<TLorentzVector>", &IsolatedPionTracksVeto, 32000, 0);
      tExpectation_->Branch("IsolatedPionTracksVetoActivity", &IsolatedPionTracksVetoActivity);
      tExpectation_->Branch("IsolatedPionTracksVetoMTW", &IsolatedPionTracksVetoMTW);
      tExpectation_->Branch("muIsoTrackMatchedToGenSingleProngTau", &muIsoTrackMatchedToGenSingleProngTau);
      tExpectation_->Branch("elecIsoTrackMatchedToGenSingleProngTau", &elecIsoTrackMatchedToGenSingleProngTau);
      tExpectation_->Branch("pionIsoTrackMatchedToGenSingleProngTau", &pionIsoTrackMatchedToGenSingleProngTau);
	
	
      tExpectation_->Branch("JetsNum",&JetsNum_);
      tExpectation_->Branch("Jets", "std::vector<TLorentzVector>", &Jets, 32000, 0);
      tExpectation_->Branch("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV);
      tExpectation_->Branch("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction);
      tExpectation_->Branch("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction);
      tExpectation_->Branch("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity);
      tExpectation_->Branch("Jets_electronMultiplicity", &Jets_electronMultiplicity);
      tExpectation_->Branch("Jets_jetArea", &Jets_jetArea);
      tExpectation_->Branch("Jets_muonEnergyFraction", &Jets_muonEnergyFraction);
      tExpectation_->Branch("Jets_muonMultiplicity", &Jets_muonMultiplicity);
      tExpectation_->Branch("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction);
      tExpectation_->Branch("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity);
      tExpectation_->Branch("Jets_photonEnergyFraction", &Jets_photonEnergyFraction);
      tExpectation_->Branch("Jets_photonMultiplicity", &Jets_photonMultiplicity);
      // di lep contribution
      tExpectation_->Branch("ExpectationDiLep",&ExpectationDiLep_);
      tExpectation_->Branch("MuDiLepControlSample",&MuDiLepControlSample_);
      tExpectation_->Branch("ElecDiLepControlSample",&ElecDiLepControlSample_);
      // stand alone isotrack prediction code  
      tExpectation_->Branch("StandAloneGenMuIsoTrackMatched",&StandAloneGenMuIsoTrackMatched_);
      tExpectation_->Branch("StandAloneIsoTrackToMuMatched",&StandAloneIsoTrackToMuMatched_);
      tExpectation_->Branch("StandAloneGenElecIsoTrackMatched",&StandAloneGenElecIsoTrackMatched_);
      tExpectation_->Branch("StandAloneIsoTrackToElecMatched",&StandAloneIsoTrackToElecMatched_);
      tExpectation_->Branch("StandAloneIsoTrackToRecoMuMatched",&StandAloneIsoTrackToRecoMuMatched_);
      tExpectation_->Branch("StandAloneIsoTrackToRecoElecMatched",&StandAloneIsoTrackToRecoElecMatched_);
      tExpectation_->Branch("IsoTrackDiLepControlSampleMu",&IsoTrackDiLepControlSampleMu_);
      tExpectation_->Branch("IsoTrackDiLepControlSampleElec",&IsoTrackDiLepControlSampleElec_); 
      tExpectation_->Branch("IsoTrackDiLepMu",&IsoTrackDiLepMu_);
      tExpectation_->Branch("IsoTrackDiLepElec",&IsoTrackDiLepElec_);
      //   tExpectation_->Branch("maxDeltaRMuActivity",&maxDeltaRMuActivity_,"maxDeltaRMuActivity/F");
      //   tExpectation_->Branch("maxDeltaRElecActivity",&maxDeltaRElecActivity_,"maxDeltaRElecActivity/F");
    }

  GetOutputList()->Add(tExpectation_);
  SearchBins_ = new SearchBins();
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
}

Bool_t ExpecMaker::Process(Long64_t entry)
{

  resetValues();
  fChain->GetTree()->GetEntry(entry);

  // std::cout << "Applying skim cuts..." << std::endl;
  if(!DY_ && (HT<minHT_ || MHT< minMHT_ || NJets < minNJets_)) return kTRUE;
  if(DY_ && ( HT<minHT_ || NJets < minNJets_) ) return kTRUE;	
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ ) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_)) return kTRUE;
  //	if(!DY_) if(minDeltaPhiN<minDeltaPhiN_) return kTRUE;

  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  bool passTrigger = false;	
  for (std::vector<string>::iterator it = TriggerNames->begin() ; it != TriggerNames->end(); ++it){
    if(*it=="HLT_PFHT350_PFMET100_NoiseCleaned_v1"){
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
    if(*it=="HLT_PFHT800_v1"){
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
    if(*it=="HLT_PFMET170_NoiseCleaned_v2"){
      if(TriggerPass->at(it - TriggerNames->begin())>0.5) passTrigger = true;
    }
  }
  if(useTrigger && !passTrigger) return kTRUE;

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

  //    printf("Gen e/mu/tau: %d/%d/%d\n", GenElecNum_, GenMuNum_, GenTauNum_);
  //    printf("Selected e/mu: %d/%d\n", selectedIDIsoElectronsNum_, selectedIDIsoMuonsNum_);
	
  // compute efficiencies 1 lepton
  if( (GenMuNum_==1 && GenElecNum_==0) || (DY_ && GenMuNum_==2) )
    {
      // compute W pt from gen lepton and reco MET
      GenMuWPt_ = GenMus->at(0).Pt() + MHT * deltaR(0,METPhi,0,GenMus->at(0).Phi());
      gen_ptw = GenMuWPt_;	
      if ( GenMus->at(0).Pt() < minMuPt_ || std::abs(GenMus->at(0).Eta()) > maxMuEta_)
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
			
	  for (UShort_t i=0; i<selectedIDMuonsNum_; i++)
	    {
	      //std::cout<<"selectedIDMuonsNum_["<<i<<"] started"<<std::endl;
	      if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),selectedIDMuons->at(i).Eta(),selectedIDMuons->at(i).Phi())<maxDeltaRGenToRecoMu_ && std::abs(GenMus->at(0).Pt()-selectedIDMuons->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenToRecoMu_)
		{
		  // std::cout<<"selectedIDMuonsNum_["<<i<<"] started"<<std::endl;
		  RecoNotMatched=false;
		  // efficiency studies TH1 and so on
					
		  muReco =2;
		  muRecoMatched.push_back(1);
		  bool IsoNotMatched=true;
		  for (UShort_t ii=0; ii < selectedIDIsoMuonsNum_; ii++)
		    {
		      if(deltaR(selectedIDIsoMuons->at(ii).Eta(),selectedIDIsoMuons->at(ii).Phi(),selectedIDMuons->at(i).Eta(),selectedIDMuons->at(i).Phi())<maxDeltaRRecoToIsoMu_ && std::abs(selectedIDIsoMuons->at(ii).Pt()-selectedIDMuons->at(i).Pt())/selectedIDIsoMuons->at(ii).Pt() <maxDiffPtRecoToIsoMu_)
			{
			  IsoNotMatched=false;
			  // efficiency studies TH1 and so on
			  muIso=2;
			  muIsoMatched.push_back(1);
			  Expectation=2;
			  if(!DY_) {
			    mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(ii).Pt(), selectedIDIsoMuons->at(ii).Phi());
			    ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoMuons->at(ii).Pt(), selectedIDIsoMuons->at(ii).Phi());
			  }
			  MuDiLepControlSample_=2;
			}
		      else 
			{
			  muIsoMatched.push_back(0);
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
		  muRecoMatched.push_back(0);
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
  //    cout << "analyse gen electrons consider only single elec events" << endl;
  if( (GenMuNum_==0 && GenElecNum_==1) || (DY_ && GenElecNum_==2) )
    {
      // compute W pt from gen lepton and reco MET
      GenElecWPt_ = GenEls->at(0).Pt() + MHT * deltaR(0,METPhi,0,GenEls->at(0).Phi());
      gen_ptw = GenElecWPt_;
      if ( GenEls->at(0).Pt() < minElecPt_ || std::abs(GenEls->at(0).Eta()) > maxElecEta_)
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
	  for (UShort_t i=0; i<selectedIDElectronsNum_; i++)
	    {
	      //		std::cout<<"selectedIDElectronsNum_["<<i<<"] started"<<std::endl;
	      if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),selectedIDElectrons->at(i).Eta(),selectedIDElectrons->at(i).Phi())<maxDeltaRGenToRecoElec_ && std::abs(GenEls->at(0).Pt()-selectedIDElectrons->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenToRecoElec_)
		{
		  //		    std::cout<<"Matched to gen electron"<<std::endl;
		  RecoNotMatched=false;
		  elecReco =2;
		  elecRecoMatched.push_back(1);
		  bool IsoNotMatched=true;
		  for (UShort_t ii=0; ii < selectedIDIsoElectronsNum_; ii++)
		    {
		      //			std::cout<<"selectedIDIsoElectronsNum_["<<ii<<"] started"<<std::endl;
		      if(deltaR(selectedIDIsoElectrons->at(ii).Eta(),selectedIDIsoElectrons->at(ii).Phi(),selectedIDElectrons->at(i).Eta(),selectedIDElectrons->at(i).Phi())<maxDeltaRRecoToIsoElec_ && std::abs(selectedIDIsoElectrons->at(ii).Pt()-selectedIDElectrons->at(i).Pt())/selectedIDIsoElectrons->at(ii).Pt() <maxDiffPtRecoToIsoElec_)
			{
			  IsoNotMatched=false;
			  elecIso=2;
			  elecIsoMatched.push_back(1);
			  Expectation=2;
			  if(!DY_) {
			    mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(ii).Pt(), selectedIDIsoElectrons->at(ii).Phi());
			    ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoElectrons->at(ii).Pt(), selectedIDIsoElectrons->at(ii).Phi());
			  }
			  ElecDiLepControlSample_=2;
			}
		      else 
			{
			  elecIsoMatched.push_back(0);
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
		  elecRecoMatched.push_back(0);
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
  //    cout << "loop over all reco iso gen leptons and isotrack for specific variable calculations" << endl;
  for(unsigned int i=0; i< GenMuNum_;i++)
    {
      GenMuonActivity.push_back(MuActivity(GenMus->at(i).Eta(),GenMus->at(i).Phi(),muActivityMethod_));
      //std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMus->at(i).Pt(),GenMus->at(i).Eta(),GenMus->at(i).Phi());
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenMus->at(i).Pt(),GenMus->at(i).Eta(),GenMus->at(i).Phi());
      GenMuDeltaRJet_.push_back(DeltaR_relPT.first);
      GenMuRelPTJet_.push_back(DeltaR_relPT.second);
    }
  for(unsigned int i=0; i< selectedIDMuonsNum_;i++)
    {
      selectedIDMuonsActivity.push_back(MuActivity(selectedIDMuons->at(i).Eta(),selectedIDMuons->at(i).Phi(),muActivityMethod_));
    }
  for(unsigned int i=0; i< selectedIDIsoMuonsNum_;i++)
    {
      selectedIDIsoMuonsActivity.push_back(MuActivity(selectedIDIsoMuons->at(i).Eta(),selectedIDIsoMuons->at(i).Phi(),muActivityMethod_));
    }
  for(unsigned int i=0; i< GenElecNum_;i++)
    {
      GenElecActivity.push_back(ElecActivity(GenEls->at(i).Eta(),GenEls->at(i).Phi(),elecActivityMethod_));
      //std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenEls->at(i).Pt(),GenEls->at(i).Eta(),GenEls->at(i).Phi());
      std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(GenEls->at(i).Pt(),GenEls->at(i).Eta(),GenEls->at(i).Phi());
      GenElecDeltaRJet_.push_back(DeltaR_relPT.first);
      GenElecRelPTJet_.push_back(DeltaR_relPT.second);
    }
  for(unsigned int i=0; i< selectedIDElectronsNum_;i++)
    {
      selectedIDElectronsActivity.push_back(ElecActivity(selectedIDElectrons->at(i).Eta(),selectedIDElectrons->at(i).Phi(),elecActivityMethod_));
    }
  for(unsigned int i=0; i< selectedIDIsoElectronsNum_;i++)
    {
      selectedIDIsoElectronsActivity.push_back(ElecActivity(selectedIDIsoElectrons->at(i).Eta(),selectedIDIsoElectrons->at(i).Phi(),elecActivityMethod_));
    }
  if(DY_)
    {
      tExpectation_->Fill();
      return kTRUE;
    }
  // di leptonic events
  //     cout << "Look for di leptonic events" << endl;
  if( (GenMuNum_+GenElecNum_)==2)
    {
      if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==0)
	{
	  Expectation=1;
	  ExpectationDiLep_=1;
	}
      if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0)
	{
	  mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi());
	  ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi());
	  MuDiLepControlSample_=0;
	}
      if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1)
	{
	  ElecDiLepControlSample_=0;
	  mtw =  MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi());
	  ptw =  PTWCalculator(MHT,MHT_Phi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi());
	}
    }
  // isotrack
  for(int i=0; i< isoMuonTracks; i++) {
    // JACK--can compute this at TreeMaker level
    IsolatedMuonTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedMuonTracksVeto->at(i).Pt(), IsolatedMuonTracksVeto->at(i).Phi()));
    IsolatedMuonTracksVetoActivity.push_back(MuActivity(IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi(),muIsoTrackActivityMethod_));
  }
  for(int i=0; i< isoElectronTracks; i++) {
    IsolatedElectronTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedElectronTracksVeto->at(i).Pt(), IsolatedElectronTracksVeto->at(i).Phi()));
    IsolatedElectronTracksVetoActivity.push_back(ElecActivity(IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi(),elecIsoTrackActivityMethod_));
  }
  for(int i=0; i< isoPionTracks; i++) {
    IsolatedPionTracksVetoMTW.push_back( MTWCalculator(METPt,METPhi, IsolatedPionTracksVeto->at(i).Pt(), IsolatedPionTracksVeto->at(i).Phi()));
    IsolatedPionTracksVetoActivity.push_back(PionActivity(IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi(),pionIsoTrackActivityMethod_));
  }
  if(GenMuNum_==1 && GenElecNum_==0)
    {
		
      for(int i=0; i< isoMuonTracks; i++)
	{

	  if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenMuToTack_ && std::abs(GenMus->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTack_)
	    {
	      muIsoTrackMatchedToGenMu.push_back(1);
	    }
	  else {
	    muIsoTrackMatchedToGenMu.push_back(0);
	  }
	}
      for(int i=0; i< isoElectronTracks;i++)
	{
	  if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenMuToTack_ && std::abs(GenMus->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTack_)
	    {
	      elecIsoTrackMatchedToGenMu.push_back(1);
	    }
	  else {
	    elecIsoTrackMatchedToGenMu.push_back(0);
	  }
	}
      for(int i=0; i< isoPionTracks;i++)
	{
	  if(deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenMuToTack_ && std::abs(GenMus->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenMuToTack_)
	    {
	      pionIsoTrackMatchedToGenMu.push_back(1);
	    }
	  else {
	    pionIsoTrackMatchedToGenMu.push_back(0);
	  }
	}
    }
  if(GenElecNum_==1 && GenMuNum_==0)
    {
		
      for(int i=0; i< isoMuonTracks; i++)
	{
	  if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenElecToTack_ && std::abs(GenEls->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTack_)
	    {
	      muIsoTrackMatchedToGenElec.push_back(1);
	    }
	  else muIsoTrackMatchedToGenElec.push_back(0);
	}
      for(int i=0; i< isoElectronTracks;i++)
	{
	  if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenElecToTack_ && std::abs(GenEls->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTack_)
	    {
	      elecIsoTrackMatchedToGenElec.push_back(1);
	    }
	  else elecIsoTrackMatchedToGenElec.push_back(0);
	}
      for(int i=0; i< isoPionTracks;i++)
	{
	  if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenElecToTack_ && std::abs(GenEls->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenElecToTack_)
	    {
	      pionIsoTrackMatchedToGenElec.push_back(1);				
	    }
	  else pionIsoTrackMatchedToGenElec.push_back(0);
	}
    }
	
  if(GenElecNum_==0 && GenMuNum_==0 && GenTauNum_==1)
    {
      for(int i=0; i< isoMuonTracks; i++)
	{
	  if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenTauToTack_ && std::abs(GenTaus->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTack_)
	    {
	      muIsoTrackMatchedToGenSingleProngTau.push_back(1);
	    }
	  else muIsoTrackMatchedToGenSingleProngTau.push_back(0);
	}
      for(int i=0; i< isoElectronTracks;i++)
	{
	  if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenTauToTack_ && std::abs(GenTaus->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTack_)
	    {
	      elecIsoTrackMatchedToGenSingleProngTau.push_back(1);
	    }
	  else elecIsoTrackMatchedToGenSingleProngTau.push_back(0);
	}
      for(int i=0; i< isoPionTracks;i++)
	{
	  if(deltaR(GenTaus->at(0).Eta(),GenTaus->at(0).Phi(),IsolatedPionTracksVeto->at(i).Eta(),IsolatedPionTracksVeto->at(i).Phi())<maxDeltaRGenTauToTack_ && std::abs(GenTaus->at(0).Pt()-IsolatedPionTracksVeto->at(i).Pt())/GenTaus->at(0).Pt() <maxDiffPtGenTauToTack_)
	    {
	      pionIsoTrackMatchedToGenSingleProngTau.push_back(1);
	    }
	  else pionIsoTrackMatchedToGenSingleProngTau.push_back(0);
	}
    }
  // ************************************************************************************************************* 22 June 2015 end****************************************************
  // purity studies:
  // new purity studies
  if(selectedIDIsoMuonsNum_==1 && selectedIDIsoElectronsNum_==0 && (GenMuNum_+ GenElecNum_)<2)
    {
      // 	  if(muIso!=2)
      if(GenMuNum_<1)
	{
	  MuPurity_=0;
	}
      else MuPurity_=2;
    }
  if(selectedIDIsoMuonsNum_==0 && selectedIDIsoElectronsNum_==1 && (GenMuNum_+ GenElecNum_)<2)
    {
      // 	  if(elecIso!=2)
      if(GenElecNum_<1)
	{
	  ElecPurity_=0;
	}
      else ElecPurity_=2;
    }
  //old purity calculations
  for (UShort_t i=0; i< selectedIDIsoMuonsNum_;i++)
    {
      if(selectedIDIsoMuonsNum_>1 || MTWCalculator(METPt,METPhi, selectedIDIsoMuons->at(0).Pt(), selectedIDIsoMuons->at(0).Phi())>mtwCut_) {
	selectedIDIsoMuonsPromptMatched.push_back(-1);
	selectedIDIsoMuonsPromptMatchedDeltaR.push_back(-999.);
	selectedIDIsoMuonsPromptMatchedRelPt.push_back(-999.);
	continue;
      }
      bool matched=false;
      //	int matchedPromptMuon_=-1;
      double best_score=999.;
      double selectedIDIsoMuonsPromptMatchedDeltaR_=999., selectedIDIsoMuonsPromptMatchedRelPt_=999.;
      TVector3 recoMu3(selectedIDIsoMuons->at(i).Px(), selectedIDIsoMuons->at(i).Py(), selectedIDIsoMuons->at(i).Pz());
      for(UShort_t ii=0; ii<GenMuNum_;ii++)
	{
	  TVector3 genMu3(GenMus->at(ii).Px(), GenMus->at(ii).Py(), GenMus->at(ii).Pz());
	  double this_score=(recoMu3-genMu3).Mag2();
	  selectedIDIsoMuonsPromptMatchedDeltaR_=deltaR(selectedIDIsoMuons->at(i).Eta(),selectedIDIsoMuons->at(i).Phi(),GenMus->at(ii).Eta(),GenMus->at(ii).Phi());
	  selectedIDIsoMuonsPromptMatchedRelPt_=(selectedIDIsoMuons->at(i).Pt()-GenMus->at(ii).Pt())/selectedIDIsoMuons->at(i).Pt();
	  if(this_score<best_score&&selectedIDIsoMuonsPromptMatchedDeltaR_<maxDeltaRIsoToGenMu_ && selectedIDIsoMuonsPromptMatchedRelPt_<maxDiffPtIsoToGenMu_)
	    {
	      //		matchedPromptMuon=ii;
	      matched=true;
	    }
	}
      if (matched) {
	selectedIDIsoMuonsPromptMatched.push_back(1);
      }
      else
	{
	  selectedIDIsoMuonsPromptMatched.push_back(0);
	}
      if (GenMuNum_>0) {
	selectedIDIsoMuonsPromptMatchedDeltaR.push_back(selectedIDIsoMuonsPromptMatchedDeltaR_);
	selectedIDIsoMuonsPromptMatchedRelPt.push_back(selectedIDIsoMuonsPromptMatchedRelPt_);
      }
      else 
	{
	  selectedIDIsoMuonsPromptMatchedDeltaR.push_back(-1);
	  selectedIDIsoMuonsPromptMatchedRelPt.push_back(-100);
	}
    }
  for (UShort_t i=0; i< selectedIDIsoElectronsNum_;i++)
    {
      if(selectedIDIsoElectronsNum_>1 || MTWCalculator(METPt,METPhi, selectedIDIsoElectrons->at(0).Pt(), selectedIDIsoElectrons->at(0).Phi())>mtwCut_) {
	selectedIDIsoElectronsPromptMatched.push_back(-1);
	selectedIDIsoElectronsPromptMatchedDeltaR.push_back(-999.);
	selectedIDIsoElectronsPromptMatchedRelPt.push_back(-999.);
	continue;
      }
      bool matched=false;
      //	int matchedPromptElec_=-1;
      double best_score=999.;
      double selectedIDIsoElectronsPromptMatchedDeltaR_=999., selectedIDIsoElectronsPromptMatchedRelPt_=999.;
      TVector3 recoEl3(selectedIDIsoElectrons->at(i).Px(), selectedIDIsoElectrons->at(i).Py(), selectedIDIsoElectrons->at(i).Pz());
      for(UShort_t ii=0; ii<GenElecNum_;ii++)
	{
	  TVector3 genEl3(GenEls->at(ii).Px(), GenEls->at(ii).Py(), GenEls->at(ii).Pz());
	  double this_score=(recoEl3-genEl3).Mag2();
	  selectedIDIsoElectronsPromptMatchedDeltaR_=deltaR(selectedIDIsoElectrons->at(i).Eta(),selectedIDIsoElectrons->at(i).Phi(),GenEls->at(ii).Eta(),GenEls->at(ii).Phi());
	  selectedIDIsoElectronsPromptMatchedRelPt_=(selectedIDIsoElectrons->at(i).Pt()-GenEls->at(ii).Pt())/selectedIDIsoElectrons->at(i).Pt();
	  if(this_score<best_score&&selectedIDIsoElectronsPromptMatchedDeltaR_<maxDeltaRIsoToGenElec_ && selectedIDIsoElectronsPromptMatchedRelPt_<maxDiffPtIsoToGenElec_)
	    {
	      //		matchedPromptElectron=ii;
	      matched=true;
	    }
	}
      if (matched) {
	selectedIDIsoElectronsPromptMatched.push_back(1);
      }
      else
	{
	  selectedIDIsoElectronsPromptMatched.push_back(0);
	}
      if (GenMuNum_>0) {
	selectedIDIsoElectronsPromptMatchedDeltaR.push_back(selectedIDIsoElectronsPromptMatchedDeltaR_);
	selectedIDIsoElectronsPromptMatchedRelPt.push_back(selectedIDIsoElectronsPromptMatchedRelPt_);
      }
      else 
	{
	  selectedIDIsoElectronsPromptMatchedDeltaR.push_back(-1);
	  selectedIDIsoElectronsPromptMatchedRelPt.push_back(-100);
	}
    }
  // check if false lepton veto will be applied
  int temp=0;
  for(unsigned int i=0; i< selectedIDIsoElectronsNum_;i++)
    {
      if(selectedIDIsoElectronsPromptMatched[i]==0)temp=1;
    }
  for(unsigned int i=0; i< selectedIDIsoMuonsNum_;i++)
    {
      if(selectedIDIsoMuonsPromptMatched[i]==0)temp=1;
    }
  if(temp==1)FallsVetoLep=1;
	
  // new version for stand alone iso track
  // go for single lepton decay first
  if(GenMuNum_==1 && GenElecNum_==0)
    {
      bool IsoTrackNotMached=true;
      for (int i=0; i < isoMuonTracks; i++)
	{
	  if( deltaR(GenMus->at(0).Eta(),GenMus->at(0).Phi(),IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi())<maxDeltaRGenToRecoIsoTrack_ && std::abs(GenMus->at(0).Pt()-IsolatedMuonTracksVeto->at(i).Pt())/GenMus->at(0).Pt() <maxDiffPtGenToRecoIsoTrack_) 
	    {
	      IsoTrackNotMached=false;
	      StandAloneGenMuIsoTrackMatched_++;
	      bool IsoTrackIsoMuonNotMachted=true;
	      for (unsigned int ii=0; ii < selectedIDIsoMuonsNum_;ii++)
		{
		  if(deltaR(IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi(),selectedIDIsoMuons->at(ii).Eta(),selectedIDIsoMuons->at(ii).Phi())<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedMuonTracksVeto->at(i).Pt()-selectedIDIsoMuons->at(ii).Pt())/IsolatedMuonTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToMu_)
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
		  for (unsigned int ii=0; ii< selectedIDMuonsNum_;ii++)
		    {
		      if(deltaR(IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi(),selectedIDMuons->at(ii).Eta(),selectedIDMuons->at(ii).Phi())<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedMuonTracksVeto->at(i).Pt()-selectedIDMuons->at(ii).Pt())/IsolatedMuonTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToMu_)
			{
			  IsoTrackRecoMuonNotMatched=false;
			  StandAloneIsoTrackToRecoMuMatched_++;
			  IsoTrackDiLepControlSampleMu_++;
			}
		    }
		  for (unsigned int ii=0; ii< selectedIDElectronsNum_;ii++)
		    {
		      if(deltaR(IsolatedMuonTracksVeto->at(i).Eta(),IsolatedMuonTracksVeto->at(i).Phi(),selectedIDElectrons->at(ii).Eta(),selectedIDElectrons->at(ii).Phi())<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedMuonTracksVeto->at(i).Pt()-selectedIDElectrons->at(ii).Pt())/IsolatedMuonTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToElec_)
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
  if(GenMuNum_==0 && GenElecNum_==1)
    {
      bool IsoTrackNotMached=true;
      for (int i=0; i < isoElectronTracks; i++)
	{
	  if(deltaR(GenEls->at(0).Eta(),GenEls->at(0).Phi(),IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi())<maxDeltaRGenToRecoIsoTrack_ && std::abs(GenEls->at(0).Pt()-IsolatedElectronTracksVeto->at(i).Pt())/GenEls->at(0).Pt() <maxDiffPtGenToRecoIsoTrack_)
	    {
	      IsoTrackNotMached=false;
	      StandAloneGenElecIsoTrackMatched_++;
	      bool IsoTrackIsoEleconNotMachted=true;
	      for (unsigned int ii=0; ii < selectedIDIsoElectronsNum_;ii++)
		{
		  if(deltaR(IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi(),selectedIDIsoElectrons->at(ii).Eta(),selectedIDIsoElectrons->at(ii).Phi())<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedElectronTracksVeto->at(i).Pt()-selectedIDIsoElectrons->at(ii).Pt())/IsolatedElectronTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToElec_)
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
		  for (unsigned int ii=0; ii< selectedIDMuonsNum_;ii++)
		    {
		      if(deltaR(IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi(),selectedIDMuons->at(ii).Eta(),selectedIDMuons->at(ii).Phi())<maxDeltaRIsoTrackToMu_ && std::abs(IsolatedElectronTracksVeto->at(i).Pt()-selectedIDMuons->at(ii).Pt())/IsolatedElectronTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToMu_)
			{
			  IsoTrackRecoMuonNotMatched=false;
			  StandAloneIsoTrackToRecoMuMatched_++;
			  IsoTrackDiLepControlSampleElec_++;
			}
		    }
		  for (unsigned int ii=0; ii< selectedIDElectronsNum_;ii++)
		    {
		      if(deltaR(IsolatedElectronTracksVeto->at(i).Eta(),IsolatedElectronTracksVeto->at(i).Phi(),selectedIDElectrons->at(ii).Eta(),selectedIDElectrons->at(ii).Phi())<maxDeltaRIsoTrackToElec_ && std::abs(IsolatedElectronTracksVeto->at(i).Pt()-selectedIDElectrons->at(ii).Pt())/IsolatedElectronTracksVeto->at(i).Pt() <maxDiffPtIsoTrackToElec_)
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
    
  //  } // end loop over events

  
}

void ExpecMaker::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
	
}

void ExpecMaker::Terminate()
{
  //  GetOutputList()->Print();
  // std::cout << "tExpectation_:" << tExpectation_ << '\n';
  tExpectation_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonExpectation"));
	
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
	
  // for(unsigned int i=0; i<40;i++)
  //   {
  muIsoMatched.clear();
  muRecoMatched.clear();
  elecIsoMatched.clear();
  elecRecoMatched.clear();
  selectedIDIsoMuonsPromptMatched.clear();
  selectedIDIsoMuonsPromptMatchedDeltaR.clear();
  selectedIDIsoMuonsPromptMatchedRelPt.clear();
  selectedIDIsoElectronsPromptMatched.clear();
  selectedIDIsoElectronsPromptMatchedDeltaR.clear();
  selectedIDIsoElectronsPromptMatchedRelPt.clear();
  GenMuonIsoTrackMatched.clear();
  selectedIDIsoMuonsIsoTrackMatched.clear();
  GenElecIsoTrackMatched.clear();
  selectedIDIsoElectronsIsoTrackMatched.clear();
  GenTauIsoTrackMatched.clear();
  SelectedIsoTracksMatchedToGenLepton.clear();
  SelectedIsoTracksMatchedToRecoIsoLepton.clear();
  SelectedIsoTracksMatchedToGenDeltaR.clear(); 
  SelectedIsoTracksMatchedToGenRelPT.clear();
  SelectedIsoTracksMatchedToRecoIsoDeltaR.clear();
  SelectedIsoTracksMatchedToRecoIsoRelPT.clear();
		
		
  GenMuonIsolatedTracksPT10Matched.clear();
  selectedIDIsoMuonsIsolatedTracksPT10Matched.clear();
  GenElecIsolatedTracksPT10Matched.clear();
  selectedIDIsoElectronsIsolatedTracksPT10Matched.clear();
  GenTauIsolatedTracksPT10Matched.clear();
  IsolatedTracksPT10MatchedToGenLepton.clear();
  IsolatedTracksPT10MatchedToRecoIsoLepton.clear();
  IsolatedTracksPT10MatchedToGenDeltaR.clear(); 
  IsolatedTracksPT10MatchedToGenRelPT.clear();
  IsolatedTracksPT10MatchedToRecoIsoDeltaR.clear();
  IsolatedTracksPT10MatchedToRecoIsoRelPT.clear();
		
  GenMuonIsolatedTracksPT10IsoCut08Matched.clear();
  selectedIDIsoMuonsIsolatedTracksPT10IsoCut08Matched.clear();
  GenElecIsolatedTracksPT10IsoCut08Matched.clear();
  selectedIDIsoElectronsIsolatedTracksPT10IsoCut08Matched.clear();
  GenTauIsolatedTracksPT10IsoCut08Matched.clear();
  IsolatedTracksPT10IsoCut08MatchedToGenLepton.clear();
  IsolatedTracksPT10IsoCut08MatchedToRecoIsoLepton.clear();
  IsolatedTracksPT10IsoCut08MatchedToGenDeltaR.clear(); 
  IsolatedTracksPT10IsoCut08MatchedToGenRelPT.clear();
  IsolatedTracksPT10IsoCut08MatchedToRecoIsoDeltaR.clear();
  IsolatedTracksPT10IsoCut08MatchedToRecoIsoRelPT.clear();
		
  GenMuonIsolatedTracksPT10IsoCut12Matched.clear();
  selectedIDIsoMuonsIsolatedTracksPT10IsoCut12Matched.clear();
  GenElecIsolatedTracksPT10IsoCut12Matched.clear();
  selectedIDIsoElectronsIsolatedTracksPT10IsoCut12Matched.clear();
  GenTauIsolatedTracksPT10IsoCut12Matched.clear();
  IsolatedTracksPT10IsoCut12MatchedToGenLepton.clear();
  IsolatedTracksPT10IsoCut12MatchedToRecoIsoLepton.clear();
  IsolatedTracksPT10IsoCut12MatchedToGenDeltaR.clear(); 
  IsolatedTracksPT10IsoCut12MatchedToGenRelPT.clear();
  IsolatedTracksPT10IsoCut12MatchedToRecoIsoDeltaR.clear();
  IsolatedTracksPT10IsoCut12MatchedToRecoIsoRelPT.clear();
		
  muIsoTrackMatchedToGenMu.clear();
  elecIsoTrackMatchedToGenMu.clear();
  pionIsoTrackMatchedToGenMu.clear();
  IsolatedMuonTracksVetoActivity.clear();
  IsolatedMuonTracksVetoMTW.clear();
		
  muIsoTrackMatchedToGenElec.clear();
  elecIsoTrackMatchedToGenElec.clear();
  pionIsoTrackMatchedToGenElec.clear();
  IsolatedElectronTracksVetoActivity.clear();
  IsolatedElectronTracksVetoMTW.clear();
		
  muIsoTrackMatchedToGenSingleProngTau.clear();
  elecIsoTrackMatchedToGenSingleProngTau.clear();
  pionIsoTrackMatchedToGenSingleProngTau.clear();
  IsolatedPionTracksVetoActivity.clear();
  IsolatedPionTracksVetoMTW.clear();
		
  selectedIDIsoMuonsActivity.clear(); 
  selectedIDMuonsActivity.clear(); 
  GenMuonActivity.clear();
  GenMuDeltaRJet_.clear();
  GenMuRelPTJet_.clear();
  GenElecDeltaRJet_.clear();
  GenElecRelPTJet_.clear();
  selectedIDIsoElectronsActivity.clear(); 
  selectedIDElectronsActivity.clear(); 
  GenElecActivity.clear();
		
  IsoTrackActivity.clear(); 
  GenTauActivity.clear();
		
  //  }
  // w pt spectrum extrapolation studies
  GenMuWPt_=-1.;
  GenMuWPhi_=-1.;
  GenElecWPt_=-1.;
  GenElecWPhi_=-1.;

  mtw=-1.;
  ptw=-1.;
}
bool ExpecMaker::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    if(CSCTightHaloFilter==0) result=false;
    if(NVtx==0) result=false;
    if(eeBadScFilter==0) result=false;
    if(HBHENoiseFilter==0) result=false;
  }
  if(!JetID) result=false;
  return result;
}

double ExpecMaker::MuActivity( double muEta, double muPhi, unsigned int method)
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
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(deltaR(muEta,muPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
  // if(method==3)
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(SelectedPFCandidates_Charge[i]!=0) continue;
  // 		if(deltaR(muEta,muPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
  return result;
	
}
double ExpecMaker::ElecActivity( double elecEta, double elecPhi, unsigned int method)
{
  double result =0;
  if(method==0)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(elecEta,elecPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_chargedHadronEnergyFraction->at(i));
	  //  			result+=Jets->at(i).Pt() * (Jets_chargedEmEnergyFraction->at(i) + Jets_chargedHadronEnergyFraction->at(i));
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
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
  // if(method==3)
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(SelectedPFCandidates_Charge[i]!=0) continue;
  // 		if(deltaR(elecEta,elecPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
  return result;
	
}
double ExpecMaker::PionActivity( double pionEta, double pionPhi, unsigned int method)
{
  double result =0;
  if(method==0)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(pionEta,pionPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_neutralEmEnergyFraction->at(i) + Jets_photonEnergyFraction->at(i));
	}
    }
  if(method==1)
    {
      for (unsigned int i=0; i < JetsNum_ ; i++)
	{
	  if(deltaR(pionEta,pionPhi,Jets->at(i).Eta(),Jets->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
	  result+=Jets->at(i).Pt() * (Jets_neutralEmEnergyFraction->at(i) + Jets_photonEnergyFraction->at(i))*(1/(deltaR(pionEta,pionPhi,Jets->at(i).Eta(),Jets->at(i).Phi())+0.5));
	}
    }
  // if(method==2)
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(deltaR(pionEta,pionPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
  // if(method==3)
  // {
  // 	for(unsigned int i=0; i< SelectedPFCandidatesNum; i++)
  // 	{
  // 		if(SelectedPFCandidates_Charge[i]!=0) continue;
  // 		if(deltaR(pionEta,pionPhi,SelectedPFCandidatesEta[i],SelectedPFCandidates->at(i).Phi())>maxDeltaRElecActivity_ ) continue;
  // 		result+=SelectedPFCandidatesPt[i];
  // 	}
  // }
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
	    if(lepPt < 1.2 * Jets->at(i).Pt())	continue;
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

