#define TagAndProbe_cxx
// The class definition in TagAndProbe.h has been generated automatically
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
// Root > T->Process("TagAndProbe.C")
// Root > T->Process("TagAndProbe.C","some options")
// Root > T->Process("TagAndProbe.C+")
//

#include "TagAndProbe.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include "TSystem.h"


void TagAndProbe::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
	 tTagAndProbeMuIso_=NULL;
	 tTagAndProbeMuReco_=NULL;
	 tTagAndProbeElecIso_=NULL;
	 tTagAndProbeElecReco_=NULL;

}

void TagAndProbe::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
	 // mu iso tree
	 tTagAndProbeMuIso_ = new TTree("TagAndProbeMuIso","a simple Tree with simple variables");
	 tTagAndProbeMuIso_->Branch("EvtNum",&EvtNum,"EvtNum/i");
	 tTagAndProbeMuIso_->Branch("HT",&HT,"HT/F");
	 tTagAndProbeMuIso_->Branch("MHT",&MHT,"MHT/F");
	 tTagAndProbeMuIso_->Branch("NJets",&NJets,"NJets/s");
	 tTagAndProbeMuIso_->Branch("BTags",&BTags,"BTags/s");
	 tTagAndProbeMuIso_->Branch("Leptons",&Leptons,"Leptons/s");
	 tTagAndProbeMuIso_->Branch("NVtx",&NVtx,"NVtx/s");
	 tTagAndProbeMuIso_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	 tTagAndProbeMuIso_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	 tTagAndProbeMuIso_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	 tTagAndProbeMuIso_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	 tTagAndProbeMuIso_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	 tTagAndProbeMuIso_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	 tTagAndProbeMuIso_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	 tTagAndProbeMuIso_->Branch("Weight", &Weight, "Weight/F");
	 
	 tTagAndProbeMuIso_->Branch("Pass", &Probe_PassingOrFail_, "Pass/I");
	 tTagAndProbeMuIso_->Branch("InvariantMass", &Probe_InvariantMass_, "InvariantMass/F");
	 tTagAndProbeMuIso_->Branch("Pt", &ProbePt_, "Pt/F");
	 tTagAndProbeMuIso_->Branch("Eta", &ProbeEta_, "Eta/F");
	 tTagAndProbeMuIso_->Branch("Phi", &ProbePhi_, "Phi/F");
	 tTagAndProbeMuIso_->Branch("Activity", &ProbeActivity_, "Activity/F");
	 GetOutputList()->Add(tTagAndProbeMuIso_);
	 
	 // mu reco tree
	 tTagAndProbeMuReco_ = new TTree("TagAndProbeMuReco","a simple Tree with simple variables");
	 tTagAndProbeMuReco_->Branch("EvtNum",&EvtNum,"EvtNum/i");
	 tTagAndProbeMuReco_->Branch("HT",&HT,"HT/F");
	 tTagAndProbeMuReco_->Branch("MHT",&MHT,"MHT/F");
	 tTagAndProbeMuReco_->Branch("NJets",&NJets,"NJets/s");
	 tTagAndProbeMuReco_->Branch("BTags",&BTags,"BTags/s");
	 tTagAndProbeMuReco_->Branch("Leptons",&Leptons,"Leptons/s");
	 tTagAndProbeMuReco_->Branch("NVtx",&NVtx,"NVtx/s");
	 tTagAndProbeMuReco_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	 tTagAndProbeMuReco_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	 tTagAndProbeMuReco_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	 tTagAndProbeMuReco_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	 tTagAndProbeMuReco_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	 tTagAndProbeMuReco_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	 tTagAndProbeMuReco_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	 tTagAndProbeMuReco_->Branch("Weight", &Weight, "Weight/F");
	 
	 tTagAndProbeMuReco_->Branch("Pass", &Probe_PassingOrFail_, "Pass/I");
	 tTagAndProbeMuReco_->Branch("InvariantMass", &Probe_InvariantMass_, "InvariantMass/F");
	 tTagAndProbeMuReco_->Branch("Pt", &ProbePt_, "Pt/F");
	 tTagAndProbeMuReco_->Branch("Eta", &ProbeEta_, "Eta/F");
	 tTagAndProbeMuReco_->Branch("Phi", &ProbePhi_, "Phi/F");
	 tTagAndProbeMuReco_->Branch("Activity", &ProbeActivity_, "Activity/F");
	 GetOutputList()->Add(tTagAndProbeMuReco_);
	 
	 // elec iso tree
	 tTagAndProbeElecIso_ = new TTree("TagAndProbeElecIso","a simple Tree with simple variables");
	 tTagAndProbeElecIso_->Branch("EvtNum",&EvtNum,"EvtNum/i");
	 tTagAndProbeElecIso_->Branch("HT",&HT,"HT/F");
	 tTagAndProbeElecIso_->Branch("MHT",&MHT,"MHT/F");
	 tTagAndProbeElecIso_->Branch("NJets",&NJets,"NJets/s");
	 tTagAndProbeElecIso_->Branch("BTags",&BTags,"BTags/s");
	 tTagAndProbeElecIso_->Branch("Leptons",&Leptons,"Leptons/s");
	 tTagAndProbeElecIso_->Branch("NVtx",&NVtx,"NVtx/s");
	 tTagAndProbeElecIso_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	 tTagAndProbeElecIso_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	 tTagAndProbeElecIso_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	 tTagAndProbeElecIso_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	 tTagAndProbeElecIso_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	 tTagAndProbeElecIso_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	 tTagAndProbeElecIso_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	 tTagAndProbeElecIso_->Branch("Weight", &Weight, "Weight/F");
	 
	 tTagAndProbeElecIso_->Branch("Pass", &Probe_PassingOrFail_, "Pass/I");
	 tTagAndProbeElecIso_->Branch("InvariantMass", &Probe_InvariantMass_, "InvariantMass/F");
	 tTagAndProbeElecIso_->Branch("Pt", &ProbePt_, "Pt/F");
	 tTagAndProbeElecIso_->Branch("Eta", &ProbeEta_, "Eta/F");
	 tTagAndProbeElecIso_->Branch("Phi", &ProbePhi_, "Phi/F");
	 tTagAndProbeElecIso_->Branch("Activity", &ProbeActivity_, "Activity/F");
	 GetOutputList()->Add(tTagAndProbeElecIso_);
	 
	 // elec reco tree
	 tTagAndProbeElecReco_ = new TTree("TagAndProbeElecReco","a simple Tree with simple variables");
	 tTagAndProbeElecReco_->Branch("EvtNum",&EvtNum,"EvtNum/i");
	 tTagAndProbeElecReco_->Branch("HT",&HT,"HT/F");
	 tTagAndProbeElecReco_->Branch("MHT",&MHT,"MHT/F");
	 tTagAndProbeElecReco_->Branch("NJets",&NJets,"NJets/s");
	 tTagAndProbeElecReco_->Branch("BTags",&BTags,"BTags/s");
	 tTagAndProbeElecReco_->Branch("Leptons",&Leptons,"Leptons/s");
	 tTagAndProbeElecReco_->Branch("NVtx",&NVtx,"NVtx/s");
	 tTagAndProbeElecReco_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	 tTagAndProbeElecReco_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	 tTagAndProbeElecReco_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	 tTagAndProbeElecReco_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	 tTagAndProbeElecReco_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	 tTagAndProbeElecReco_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	 tTagAndProbeElecReco_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	 tTagAndProbeElecReco_->Branch("Weight", &Weight, "Weight/F");
	 
	 tTagAndProbeElecReco_->Branch("Pass", &Probe_PassingOrFail_, "Pass/I");
	 tTagAndProbeElecReco_->Branch("InvariantMass", &Probe_InvariantMass_, "InvariantMass/F");
	 tTagAndProbeElecReco_->Branch("Pt", &ProbePt_, "Pt/F");
	 tTagAndProbeElecReco_->Branch("Eta", &ProbeEta_, "Eta/F");
	 tTagAndProbeElecReco_->Branch("Phi", &ProbePhi_, "Phi/F");
	 tTagAndProbeElecReco_->Branch("Activity", &ProbeActivity_, "Activity/F");
	 GetOutputList()->Add(tTagAndProbeElecReco_);
	 std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
	 

}

Bool_t TagAndProbe::Process(Long64_t entry)
{
	resetValues();
	fChain->GetTree()->GetEntry(entry);
	if(applyFilters_ &&  !FiltersPass() ) return kTRUE;
 	if(HT < minHT_ && NJets<minNJets_) return kTRUE;
	if(ProbeIsoMuonNum>0 && MuIso_minDeltaPhiN>minDeltaPhiN_)
	{
		for (unsigned int i=0; i<1;i++)
		{
// 		  if(ProbeIsoMuonPt[0]<50) continue;
			ProbeActivity_=MuActivity(ProbeIsoMuonEta[i],ProbeIsoMuonPhi[i],muActivityMethod_);
			ProbePt_=ProbeIsoMuonPt[i];
			ProbeEta_=ProbeIsoMuonEta[i];
			ProbePhi_=ProbeIsoMuonPhi[i];
			Probe_PassingOrFail_=ProbeIsoMuon_PassingOrFail[i];
			if(Probe_PassingOrFail_==2)std::cout<<"This should not happen..."<<std::endl;
			Probe_InvariantMass_=ProbeIsoMuon_InvariantMass[i];
			tTagAndProbeMuIso_->Fill();
		}
	}
	resetValues();
	if(ProbeIDMuonNum>0 && MuID_minDeltaPhiN>minDeltaPhiN_)
	{
		for (unsigned int i=0; i<1;i++)
		{
// 		  if(ProbeIDMuonPt[0]<50) continue;
			ProbeActivity_=MuActivity(ProbeIDMuonEta[i],ProbeIDMuonPhi[i],muActivityMethod_);
			ProbePt_=ProbeIDMuonPt[i];
			ProbeEta_=ProbeIDMuonEta[i];
			ProbePhi_=ProbeIDMuonPhi[i];
			Probe_PassingOrFail_=ProbeIDMuon_PassingOrFail[i];
			Probe_InvariantMass_=ProbeIDMuon_InvariantMass[i];
			tTagAndProbeMuReco_->Fill();
		}
	}
	resetValues();
	if(ProbeIsoElectronNum>0 && ElecIso_minDeltaPhiN>minDeltaPhiN_)
	{
		for (unsigned int i=0; i<1;i++)
		{
// 		  if(ProbeIsoElectronPt[0]<50) continue;
			ProbeActivity_=MuActivity(ProbeIsoElectronEta[i],ProbeIsoElectronPhi[i],elecActivityMethod_);
			ProbePt_=ProbeIsoElectronPt[i];
			ProbeEta_=ProbeIsoElectronEta[i];
			ProbePhi_=ProbeIsoElectronPhi[i];
			Probe_PassingOrFail_=ProbeIsoElectron_PassingOrFail[i];
			Probe_InvariantMass_=ProbeIsoElectron_InvariantMass[i];
			tTagAndProbeElecIso_->Fill();
		}
	}
	resetValues();
	if(ProbeIDElectronNum>0 && ElecID_minDeltaPhiN>minDeltaPhiN_)
	{
		for (unsigned int i=0; i<1;i++)
		{
// 		  if(ProbeIDElectronPt[0]<50) continue;
		  
			ProbeActivity_=MuActivity(ProbeIDElectronEta[i],ProbeIDElectronPhi[i],elecActivityMethod_);
			ProbePt_=ProbeIDElectronPt[i];
			ProbeEta_=ProbeIDElectronEta[i];
			ProbePhi_=ProbeIDElectronPhi[i];
			Probe_PassingOrFail_=ProbeIDElectron_PassingOrFail[i];
			Probe_InvariantMass_=ProbeIDElectron_InvariantMass[i];
			tTagAndProbeElecReco_->Fill();
		}
	}


   return kTRUE;
}

void TagAndProbe::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void TagAndProbe::Terminate()
{
	GetOutputList()->Print();
	tTagAndProbeMuIso_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("TagAndProbeMuIso"));
 	TFile *outPutFile = new TFile("TagAndProbe_HT400_NJets3_4_MinDeltaPhi-9999_activity0DR1_Only1ProbeEachEvent.root","RECREATE"); 
	outPutFile->cd();
	outPutFile->mkdir("MuIso");
	TDirectory *dMuIso = (TDirectory*)outPutFile->Get("MuIso");
	dMuIso->cd();
	tTagAndProbeMuIso_->Write();
	outPutFile->mkdir("MuReco");
	TDirectory *dMuReco = (TDirectory*)outPutFile->Get("MuReco");
	dMuReco->cd();
	tTagAndProbeMuReco_->Write();
	outPutFile->mkdir("ElecIso");
	TDirectory *dElecIso = (TDirectory*)outPutFile->Get("ElecIso");
	dElecIso->cd();
	tTagAndProbeElecIso_->Write();
	outPutFile->mkdir("ElecReco");
	TDirectory *dElecReco = (TDirectory*)outPutFile->Get("ElecReco");
	dElecReco->cd();
	tTagAndProbeElecReco_->Write();
	outPutFile->Close();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void TagAndProbe::resetValues()
{
	Probe_PassingOrFail_=-1;
	Probe_InvariantMass_=-100;
	ProbePt_=-100;
	ProbeEta_=-100;
	ProbePhi_=-100;
	ProbeActivity_=-100;
}
bool TagAndProbe::FiltersPass()
{
	bool result=true;
  if(!JetID) result=false;
	return result;
}
double TagAndProbe::deltaR(double eta1, double phi1, double eta2, double phi2)
{
	double deta = eta1-eta2;
	double dphi = TVector2::Phi_mpi_pi(phi1-phi2);
	return sqrt(deta * deta + dphi *dphi); 
}
double TagAndProbe::MuActivity( double muEta, double muPhi, unsigned int method)
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
double TagAndProbe::ElecActivity( double elecEta, double elecPhi, unsigned int method)
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
