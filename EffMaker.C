#define EffMaker_cxx
#include "EffMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include "TSystem.h"
#include "TMath.h"

const int nEXTRAPBins(13);

void EffMaker::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();

  TH1::SetDefaultSumw2();

  gSystem->mkdir("Efficiencies");

}

void EffMaker::SlaveBegin(TTree * /*tree*/)
{
  TString option = GetOption();
  TH1::SetDefaultSumw2();

  gSystem->mkdir("Efficiencies"); 


  // purity

  // muon
  //1D
  MuPurityOldBTag_ = new TH1Eff("MuPurityOldBTag1D","MuPurityOldBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityOldNJets_ = new TH1Eff("MuPurityOldNJets1D","MuPurityOldNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityOldHT_ = new TH1Eff("MuPurityOldHT1D","MuPurityOldHT1D",oneDHT_-1,OneDHT_);
  MuPurityOldMHT_ = new TH1Eff("MuPurityOldMHT1D","MuPurityOldMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityOldMHTNJet_ = new TH2Eff("MuonPurityOldMHTNJet","MuonPurityOldMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  // electron
  //1D
  ElecPurityOldBTag_ = new TH1Eff("ElecPurityOldBTag1D","ElecPurityOldBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityOldNJets_ = new TH1Eff("ElecPurityOldNJets1D","ElecPurityOldNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityOldHT_ = new TH1Eff("ElecPurityOldHT1D","ElecPurityOldHT1D",oneDHT_-1,OneDHT_);
  ElecPurityOldMHT_ = new TH1Eff("ElecPurityOldMHT1D","ElecPurityOldMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityOldMHTNJet_ = new TH2Eff("ElecPurityOldMHTNJet","ElecPurityOldMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  // purity x-check

  // muon
  // 1D
  MuPurityBTag_ = new TH1Eff("MuPurityBTag1D","MuPurityBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityNJets_ = new TH1Eff("MuPurityNJets1D","MuPurityNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityHT_ = new TH1Eff("MuPurityHT1D","MuPurityHT1D",oneDHT_-1,OneDHT_);
  MuPurityMHT_ = new TH1Eff("MuPurityMHT1D","MuPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityMHTNJet_ = new TH2Eff("MuonPurityMHTNJet","MuonPurityMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  // electron
  //1D
  ElecPurityBTag_ = new TH1Eff("ElecPurityBTag1D","ElecPurityBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityNJets_ = new TH1Eff("ElecPurityNJets1D","ElecPurityNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityHT_ = new TH1Eff("ElecPurityHT1D","ElecPurityHT1D",oneDHT_-1,OneDHT_);
  ElecPurityMHT_ = new TH1Eff("ElecPurityMHT1D","ElecPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityMHTNJet_ = new TH2Eff("ElecPurityMHTNJet","ElecPurityMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  
  // acceptance
  //muon
  //1D
  MuAccBTag_ = new TH1Eff("MuAccBTag1D","MuAccBTag1D",oneDBJets_-1,OneDBJets_);
  MuAccNJets_ = new TH1Eff("MuAccNJets1D","MuAccNJets1D",oneDNJets_-1,OneDNJets_);
  MuAccHT_ = new TH1Eff("MuAccHT1D","MuAccHT1D",oneDHT_-1,OneDHT_);
  MuAccMHT_ = new TH1Eff("MuAccMHT1D","MuAccMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets","MuAccHTNJets",muaccHT_-1,muAccHT_, muaccNJets_-1, muAccNJets_);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets","MuAccMHTNJets",muaccMHT_-1,muAccMHT_, muaccNJets_-1, muAccNJets_);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT","MuAccHTMHT",muaccHT_-1,muAccHT_, muaccMHT_-1,muAccMHT_);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets","MuAccBTagNJets",muaccBTags_-1,muAccBTags_, muaccNJets_-1, muAccNJets_);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0","MuAccMHTNJetsB0",muaccMHT_-1,muAccMHT_, muaccNJets_-1, muAccNJets_);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf","MuAccMHTNJetsB1_Inf",muaccMHT_-1,muAccMHT_, muaccNJets_-1, muAccNJets_);
  MuAccHTMHT_NJetsLow_ = new TH2Eff("MuAccHTMHT_NJetsLow","MuAccHTMHT_NJetsLow",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets2_ = new TH2Eff("MuAccHTMHT_NJets2","MuAccHTMHT_NJets2",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets3_ = new TH2Eff("MuAccHTMHT_NJets3","MuAccHTMHT_NJets3",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets4_ = new TH2Eff("MuAccHTMHT_NJets4","MuAccHTMHT_NJets4",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets5_ = new TH2Eff("MuAccHTMHT_NJets5","MuAccHTMHT_NJets5",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets6_ = new TH2Eff("MuAccHTMHT_NJets6","MuAccHTMHT_NJets6",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets78_ = new TH2Eff("MuAccHTMHT_NJets78","MuAccHTMHT_NJets78",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJets9Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf","MuAccHTMHT_NJets9Inf",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHT_NJetsHigh_ = new TH2Eff("MuAccHTMHT_NJetsHigh"," MuAccHTMHT_NJetsHigh",muaccHT_-1,muAccHT_, muaccMHT2D_-1,muAccMHT2D_);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0","MuAccHTMHTB0",muaccHT_-1,muAccHT_, muaccMHT_-1,muAccMHT_);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf","MuAccHTMHTB1_Inf",muaccHT_-1,muAccHT_, muaccMHT_-1,muAccMHT_);
  
  //elec
  //1D
  ElecAccBTag_ = new TH1Eff("ElecAccBTag1D","ElecAccBTag1D",oneDBJets_-1,OneDBJets_);
  ElecAccNJets_ = new TH1Eff("ElecAccNJets1D","ElecAccNJets1D",oneDNJets_-1,OneDNJets_);
  ElecAccHT_ = new TH1Eff("ElecAccHT1D","ElecAccHT1D",oneDHT_-1,OneDHT_);
  ElecAccMHT_ = new TH1Eff("ElecAccMHT1D","ElecAccMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets","ElecAccHTNJets",elecaccHT_-1,elecAccHT_, elecaccNJets_-1, elecAccNJets_);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets","ElecAccMHTNJets",elecaccMHT_-1,elecAccMHT_, elecaccNJets_-1, elecAccNJets_);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT","ElecAccHTMHT",elecaccHT_-1,elecAccHT_, elecaccMHT_-1,elecAccMHT_);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets","ElecAccBTagNJets",elecaccBTags_-1,elecAccBTags_, elecaccNJets_-1, elecAccNJets_);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0","ElecAccMHTNJetsB0",elecaccMHT_-1,elecAccMHT_, elecaccNJets_-1, elecAccNJets_);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf","ElecAccMHTNJetsB1_Inf",elecaccMHT_-1,elecAccMHT_, elecaccNJets_-1, elecAccNJets_);
  ElecAccHTMHT_NJetsLow_ = new TH2Eff("ElecAccHTMHT_NJetsLow","ElecAccHTMHT_NJetsLow",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets2_ = new TH2Eff("ElecAccHTMHT_NJets2","ElecAccHTMHT_NJets2",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets3_ = new TH2Eff("ElecAccHTMHT_NJets3","ElecAccHTMHT_NJets3",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets4_ = new TH2Eff("ElecAccHTMHT_NJets4","ElecAccHTMHT_NJets4",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets5_ = new TH2Eff("ElecAccHTMHT_NJets5","ElecAccHTMHT_NJets5",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets6_ = new TH2Eff("ElecAccHTMHT_NJets6","ElecAccHTMHT_NJets6",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets78_ = new TH2Eff("ElecAccHTMHT_NJets78","ElecAccHTMHT_NJets78",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJets9Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf","ElecAccHTMHT_NJets9Inf",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHT_NJetsHigh_ = new TH2Eff("ElecAccHTMHT_NJetsHigh"," ElecAccHTMHT_NJetsHigh",elecaccHT_-1,elecAccHT_, elecaccMHT2D_-1,elecAccMHT2D_);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0","ElecAccHTMHTB0",elecaccHT_-1,elecAccHT_, elecaccMHT_-1,elecAccMHT_);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf","ElecAccHTMHTB1_Inf",elecaccHT_-1,elecAccHT_, elecaccMHT_-1,elecAccMHT_);

  
  // reconstruction
  //muon
  //1D
  MuRecoBTag_ = new TH1Eff("MuRecoBTag1D","MuRecoBTag1D",oneDBJets_-1,OneDBJets_);
  MuRecoNJets_ = new TH1Eff("MuRecoNJets1D","MuRecoNJets1D",oneDNJets_-1,OneDNJets_);
  MuRecoHT_ = new TH1Eff("MuRecoHT1D","MuRecoHT1D",oneDHT_-1,OneDHT_);
  MuRecoMHT_ = new TH1Eff("MuRecoMHT1D","MuRecoMHT1D",oneDMHT_-1,OneDMHT_);
 
  //elec
  //1D
  ElecRecoBTag_ = new TH1Eff("ElecRecoBTag1D","ElecRecoBTag1D",oneDBJets_-1,OneDBJets_);
  ElecRecoNJets_ = new TH1Eff("ElecRecoNJets1D","ElecRecoNJets1D",oneDNJets_-1,OneDNJets_);
  ElecRecoHT_ = new TH1Eff("ElecRecoHT1D","ElecRecoHT1D",oneDHT_-1,OneDHT_);
  ElecRecoMHT_ = new TH1Eff("ElecRecoMHT1D","ElecRecoMHT1D",oneDMHT_-1,OneDMHT_);

  
  // isolation
  //muon
  //1D
  MuIsoBTag_ = new TH1Eff("MuIsoBTag1D","MuIsoBTag1D",oneDBJets_-1,OneDBJets_);
  MuIsoNJets_ = new TH1Eff("MuIsoNJets1D","MuIsoNJets1D",oneDNJets_-1,OneDNJets_);
  MuIsoHT_ = new TH1Eff("MuIsoHT1D","MuIsoHT1D",oneDHT_-1,OneDHT_);
  MuIsoMHT_ = new TH1Eff("MuIsoMHT1D","MuIsoMHT1D",oneDMHT_-1,OneDMHT_);
  
  //elec
  //1D
  ElecIsoBTag_ = new TH1Eff("ElecIsoBTag1D","ElecIsoBTag1D",oneDBJets_-1,OneDBJets_);
  ElecIsoNJets_ = new TH1Eff("ElecIsoNJets1D","ElecIsoNJets1D",oneDNJets_-1,OneDNJets_);
  ElecIsoHT_ = new TH1Eff("ElecIsoHT1D","ElecIsoHT1D",oneDHT_-1,OneDHT_);
  ElecIsoMHT_ = new TH1Eff("ElecIsoMHT1D","ElecIsoMHT1D",oneDMHT_-1,OneDMHT_);

  
  // mtw
  //muon
  //1D
  MuMTWBTag_ = new TH1Eff("MuMTWBTag1D","MuMTWBTag1D",oneDBJets_-1,OneDBJets_);
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D","MuMTWNJets1D",oneDNJets_-1,OneDNJets_);
  MuMTWHT_ = new TH1Eff("MuMTWHT1D","MuMTWHT1D",oneDHT_-1,OneDHT_);
  MuMTWMHT_ = new TH1Eff("MuMTWMHT1D","MuMTWMHT1D",oneDMHT_-1,OneDMHT_);

  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets","MuMTWHTNJets",muaccHT_-1,muAccHT_, muaccNJets_-1, muAccNJets_);
  
  //electron
  //1D
  ElecMTWBTag_ = new TH1Eff("ElecMTWBTag1D","ElecMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D","ElecMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecMTWHT_ = new TH1Eff("ElecMTWHT1D","ElecMTWHT1D",oneDHT_-1,OneDHT_);
  ElecMTWMHT_ = new TH1Eff("ElecMTWMHT1D","ElecMTWMHT1D",oneDMHT_-1,OneDMHT_);

  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets","ElecMTWHTNJets",elecaccHT_-1,elecAccHT_, elecaccNJets_-1, elecAccNJets_);

 
  // di lep  
  //muon
  //1D
  MuDiLepBTag_ = new TH1Eff("MuDiLepBTag1D","MuDiLepBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepNJets_ = new TH1Eff("MuDiLepNJets1D","MuDiLepNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepHT_ = new TH1Eff("MuDiLepHT1D","MuDiLepHT1D",oneDHT_-1,OneDHT_);
  MuDiLepMHT_ = new TH1Eff("MuDiLepMHT1D","MuDiLepMHT1D",oneDMHT_-1,OneDMHT_);
 
  //electron
  //1D
  ElecDiLepBTag_ = new TH1Eff("ElecDiLepBTag1D","ElecDiLepBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepNJets_ = new TH1Eff("ElecDiLepNJets1D","ElecDiLepNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepHT_ = new TH1Eff("ElecDiLepHT1D","ElecDiLepHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepMHT_ = new TH1Eff("ElecDiLepMHT1D","ElecDiLepMHT1D",oneDMHT_-1,OneDMHT_);
  
  // mtw
  //muon
  //1D
  MuDiLepMTWBTag_ = new TH1Eff("MuDiLepMTWBTag1D","MuDiLepMTWBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepMTWNJets_ = new TH1Eff("MuDiLepMTWNJets1D","MuDiLepMTWNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepMTWHT_ = new TH1Eff("MuDiLepMTWHT1D","MuDiLepMTWHT1D",oneDHT_-1,OneDHT_);
  MuDiLepMTWMHT_ = new TH1Eff("MuDiLepMTWMHT1D","MuDiLepMTWMHT1D",oneDMHT_-1,OneDMHT_);
  
  //electron
  //1D
  ElecDiLepMTWBTag_ = new TH1Eff("ElecDiLepMTWBTag1D","ElecDiLepMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepMTWNJets_ = new TH1Eff("ElecDiLepMTWNJets1D","ElecDiLepMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepMTWHT_ = new TH1Eff("ElecDiLepMTWHT1D","ElecDiLepMTWHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepMTWMHT_ = new TH1Eff("ElecDiLepMTWMHT1D","ElecDiLepMTWMHT1D",oneDMHT_-1,OneDMHT_);
  
  
  // di lep 
  //muon
  //1D
  MuDiLepContributionBTag_ = new TH1Eff("MuDiLepContributionBTag1D","MuDiLepContributionBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepContributionNJets_ = new TH1Eff("MuDiLepContributionNJets1D","MuDiLepContributionNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepContributionHT_ = new TH1Eff("MuDiLepContributionHT1D","MuDiLepContributionHT1D",oneDHT_-1,OneDHT_);
  MuDiLepContributionMHT_ = new TH1Eff("MuDiLepContributionMHT1D","MuDiLepContributionMHT1D",oneDMHT_-1,OneDMHT_);

  MuDiLepFractionBTag_ = new TH1Eff("MuDiLepFractionBTag1D","MuDiLepFractionBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepFractionNJets_ = new TH1Eff("MuDiLepFractionNJets1D","MuDiLepFractionNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepFractionHT_ = new TH1Eff("MuDiLepFractionHT1D","MuDiLepFractionHT1D",oneDHT_-1,OneDHT_);
  MuDiLepFractionMHT_ = new TH1Eff("MuDiLepFractionMHT1D","MuDiLepFractionMHT1D",oneDMHT_-1,OneDMHT_);
  
  //electron
  //1D
  ElecDiLepContributionBTag_ = new TH1Eff("ElecDiLepContributionBTag1D","ElecDiLepContributionBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepContributionNJets_ = new TH1Eff("ElecDiLepContributionNJets1D","ElecDiLepContributionNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepContributionHT_ = new TH1Eff("ElecDiLepContributionHT1D","ElecDiLepContributionHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepContributionMHT_ = new TH1Eff("ElecDiLepContributionMHT1D","ElecDiLepContributionMHT1D",oneDMHT_-1,OneDMHT_);

  ElecDiLepFractionBTag_ = new TH1Eff("ElecDiLepFractionBTag1D","ElecDiLepFractionBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepFractionNJets_ = new TH1Eff("ElecDiLepFractionNJets1D","ElecDiLepFractionNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepFractionHT_ = new TH1Eff("ElecDiLepFractionHT1D","ElecDiLepFractionHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepFractionMHT_ = new TH1Eff("ElecDiLepFractionMHT1D","ElecDiLepFractionMHT1D",oneDMHT_-1,OneDMHT_);
  
  //muon
  //1D
  MuDiLepContributionMTWBTag_ = new TH1Eff("MuDiLepContributionMTWBTag1D","MuDiLepContributionMTWBTag1D",oneDBJets_-1,OneDBJets_);
  MuDiLepContributionMTWNJets_ = new TH1Eff("MuDiLepContributionMTWNJets1D","MuDiLepContributionMTWNJets1D",oneDNJets_-1,OneDNJets_);
  MuDiLepContributionMTWHT_ = new TH1Eff("MuDiLepContributionMTWHT1D","MuDiLepContributionMTWHT1D",oneDHT_-1,OneDHT_);
  MuDiLepContributionMTWMHT_ = new TH1Eff("MuDiLepContributionMTWMHT1D","MuDiLepContributionMTWMHT1D",oneDMHT_-1,OneDMHT_);

  
  //electron
  //1D
  ElecDiLepContributionMTWBTag_ = new TH1Eff("ElecDiLepContributionMTWBTag1D","ElecDiLepContributionMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepContributionMTWNJets_ = new TH1Eff("ElecDiLepContributionMTWNJets1D","ElecDiLepContributionMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepContributionMTWHT_ = new TH1Eff("ElecDiLepContributionMTWHT1D","ElecDiLepContributionMTWHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepContributionMTWMHT_ = new TH1Eff("ElecDiLepContributionMTWMHT1D","ElecDiLepContributionMTWMHT1D",oneDMHT_-1,OneDMHT_);
  
  // acitivity and pt
  // mu 
  MuPurityOldPT_ = new TH1Eff("MuPurityOldPT","MuPurityOldPT",oneDPT_-1,OneDPT_);
  MuPurityOldActivity_ = new TH1Eff("MuPurityOldActivity","MuPurityOldActivity",oneDActivity_-1,OneDActivity_);
  MuAccPT_ = new TH1Eff("MuAccPT","MuAccPT",oneDPT_-1,OneDPT_);
  MuAccActivity_ = new TH1Eff("MuAccActivity","MuAccActivity",oneDActivity_-1,OneDActivity_);
  MuRecoPT_ = new TH1Eff("MuRecoPT","MuRecoPT",oneDPT_-1,OneDPT_);
  MuRecoActivity_ = new TH1Eff("MuRecoActivity","MuRecoActivity",oneDActivity_-1,OneDActivity_);
  MuIsoPT_ = new TH1Eff("MuIsoPT","MuIsoPT",oneDPT_-1,OneDPT_);
  MuIsoActivity_ = new TH1Eff("MuIsoActivity","MuIsoActivity",oneDActivity_-1,OneDActivity_);
  MuMTWPT_ = new TH1Eff("MuMTWPT","MuMTWPT",oneDPT_-1,OneDPT_);
  MuMTWActivity_ = new TH1Eff("MuMTWActivity","MuMTWActivity",oneDActivity_-1,OneDActivity_);
  MuDiLepPT_ = new TH1Eff("MuDiLepPT","MuDiLepPT",oneDPT_-1,OneDPT_);
  MuDiLepActivity_ = new TH1Eff("MuDiLepActivity","MuDiLepActivity",oneDActivity_-1,OneDActivity_);
  MuDiLepMTWPT_ = new TH1Eff("MuDiLepMTWPT","MuDiLepMTWPT",oneDPT_-1,OneDPT_);
  MuDiLepMTWActivity_ = new TH1Eff("MuDiLepMTWActivity","MuDiLepMTWActivity",oneDActivity_-1,OneDActivity_);
  
  // elec  
  ElecPurityOldPT_ = new TH1Eff("ElecPurityOldPT","ElecPurityOldPT",oneDPT_-1,OneDPT_);
  ElecPurityOldActivity_ = new TH1Eff("ElecPurityOldActivity","ElecPurityOldActivity",oneDActivity_-1,OneDActivity_);
  ElecAccPT_ = new TH1Eff("ElecAccPT","ElecAccPT",oneDPT_-1,OneDPT_);
  ElecAccActivity_ = new TH1Eff("ElecAccActivity","ElecAccActivity",oneDActivity_-1,OneDActivity_);
  ElecRecoPT_ = new TH1Eff("ElecRecoPT","ElecRecoPT",oneDPT_-1,OneDPT_);
  ElecRecoActivity_ = new TH1Eff("ElecRecoActivity","ElecRecoActivity",oneDActivity_-1,OneDActivity_);
  ElecIsoPT_ = new TH1Eff("ElecIsoPT","ElecIsoPT",oneDPT_-1,OneDPT_);
  ElecIsoActivity_ = new TH1Eff("ElecIsoActivity","ElecIsoActivity",oneDActivity_-1,OneDActivity_);
  ElecMTWPT_ = new TH1Eff("ElecMTWPT","ElecMTWPT",oneDPT_-1,OneDPT_);
  ElecMTWActivity_ = new TH1Eff("ElecMTWActivity","ElecMTWActivity",oneDActivity_-1,OneDActivity_);
  ElecDiLepPT_ = new TH1Eff("ElecDiLepPT","ElecDiLepPT",oneDPT_-1,OneDPT_);
  ElecDiLepActivity_ = new TH1Eff("ElecDiLepActivity","ElecDiLepActivity",oneDActivity_-1,OneDActivity_);
  ElecDiLepMTWPT_ = new TH1Eff("ElecDiLepMTWPT","ElecDiLepMTWPT",oneDPT_-1,OneDPT_);
  ElecDiLepMTWActivity_ = new TH1Eff("ElecDiLepMTWActivity","ElecDiLepMTWActivity",oneDActivity_-1,OneDActivity_);
  
  // 2D
  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT","MuIsoActivityPT", oneDActivity_-1,OneDActivity_,oneDPT_-1,OneDPT_);
  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT","ElecIsoActivityPT", oneDActivity_-1,OneDActivity_,oneDPT_-1,OneDPT_);
  MuRecoActivityPT_ = new TH2Eff("MuRecoActivityPT","MuRecoActivityPT", oneDActivity_-1,OneDActivity_,oneDPT_-1,OneDPT_);
  ElecRecoActivityPT_ = new TH2Eff("ElecRecoActivityPT","ElecRecoActivityPT", oneDActivity_-1,OneDActivity_,oneDPT_-1,OneDPT_);
  MuRecoPTEta_ = new TH2Eff("MuRecoPTEta","MuRecoPTEta", oneDPT_-1,OneDPT_, oneDEta_-1,OneDEta_);
  ElecRecoPTEta_ = new TH2Eff("ElecRecoPTEta","ElecRecoPTEta", oneDPT_-1,OneDPT_, oneDEta_-1,OneDEta_);
  
  // mtw 2d
  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity","MuMTWPTActivity",muMTWActivity2D_-1,MuMTWActivity2D_,muMTWPT2D_-1,MuMTWPT2D_);
  ElecMTWPTActivity_ = new TH2Eff("ElecMTWPTActivity","ElecMTWPTActivity",elecMTWActivity2D_-1,ElecMTWActivity2D_,elecMTWPT2D_-1,ElecMTWPT2D_);
    
  //1D
  ExpectationReductionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionIsoTrackBTagEff","ExpectationReductionIsoTrackBTagEff",isotrackreductionBTags_-1,isoTrackReductionBTags_);
  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff","ExpectationReductionIsoTrackNJetsEff",isotrackreductionNJets_-1,isoTrackReductionNJets_);
  ExpectationReductionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionIsoTrackHTEff","ExpectationReductionIsoTrackHTEff",isotrackreductionHT_-1,isoTrackReductionHT_);
  ExpectationReductionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionIsoTrackMHTEff","ExpectationReductionIsoTrackMHTEff",isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ExpectationReductionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionIsoTrackPTEff","ExpectationReductionIsoTrackPTEff",isotrackreductionPT_-1,isoTrackReductionPT_);
  ExpectationReductionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionIsoTrackActivityEff","ExpectationReductionIsoTrackActivityEff",isotrackreductionActivity_-1,isoTrackReductionActivity_);
  //2D
  IsoTrackReductionHTNJets_ = new TH2Eff("IsoTrackReductionHTNJets","IsoTrackReductionHTNJets",isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  IsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsVeryLow","IsoTrackReductionHTMHT_NJetsVeryLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow","IsoTrackReductionHTMHT_NJetsLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJets2_ = new TH2Eff("IsoTrackReductionHTMHT_NJets2","IsoTrackReductionHTMHT_NJets2", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJets3_ = new TH2Eff("IsoTrackReductionHTMHT_NJets3","IsoTrackReductionHTMHT_NJets3", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJets4_ = new TH2Eff("IsoTrackReductionHTMHT_NJets4","IsoTrackReductionHTMHT_NJets4", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJets5_ = new TH2Eff("IsoTrackReductionHTMHT_NJets5","IsoTrackReductionHTMHT_NJets5", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJets6_ = new TH2Eff("IsoTrackReductionHTMHT_NJets6","IsoTrackReductionHTMHT_NJets6", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsHigh","IsoTrackReductionHTMHT_NJetsHigh", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  IsoTrackReductionMHTNJets_ = new TH2Eff("IsoTrackReductionMHTNJets","IsoTrackReductionMHTNJets",isotrackreductionMHT_-1,isoTrackReductionMHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  IsoTrackReductionBTagNJets_ = new TH2Eff("IsoTrackReductionBTagNJets","IsoTrackReductionBTagNJets",isotrackreductionBTags2D_-1,isoTrackReductionBTags2D_, isotrackreductionNJets2D_-1, isoTrackReductionNJets2D_);
  IsoTrackReductionPTActivity_ = new TH2Eff("IsoTrackReductionPTActivity","IsoTrackReductionPTActivity", isotrackreductionActivity2D_-1, isoTrackReductionActivity2D_,isotrackreductionPT2D_-1,isoTrackReductionPT2D_);
  
  // muon iso track
  //1D
  ExpectationReductionMuIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionMuIsoTrackBTagEff","ExpectationReductionMuIsoTrackBTagEff",isotrackreductionBTags_-1,isoTrackReductionBTags_);
  ExpectationReductionMuIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionMuIsoTrackNJetsEff","ExpectationReductionMuIsoTrackNJetsEff",isotrackreductionNJets_-1,isoTrackReductionNJets_);
  ExpectationReductionMuIsoTrackHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackHTEff","ExpectationReductionMuIsoTrackHTEff",isotrackreductionHT_-1,isoTrackReductionHT_);
  ExpectationReductionMuIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackMHTEff","ExpectationReductionMuIsoTrackMHTEff",isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ExpectationReductionMuIsoTrackPTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackPTEff","ExpectationReductionMuIsoTrackPTEff",isotrackreductionPT_-1,isoTrackReductionPT_);
  ExpectationReductionMuIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionMuIsoTrackActivityEff","ExpectationReductionMuIsoTrackActivityEff",isotrackreductionActivity_-1,isoTrackReductionActivity_);
  //2D
  MuIsoTrackReductionHTNJets_ = new TH2Eff("MuIsoTrackReductionHTNJets","MuIsoTrackReductionHTNJets",isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  MuIsoTrackReductionMHTNJets_ = new TH2Eff("MuIsoTrackReductionMHTNJets","MuIsoTrackReductionMHTNJets",isotrackreductionMHT_-1,isoTrackReductionMHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  MuIsoTrackReductionBTagNJets_ = new TH2Eff("MuIsoTrackReductionBTagNJets","MuIsoTrackReductionBTagNJets",isotrackreductionBTags2D_-1,isoTrackReductionBTags2D_, isotrackreductionNJets2D_-1, isoTrackReductionNJets2D_);
  MuIsoTrackReductionPTActivity_ = new TH2Eff("MuIsoTrackReductionPTActivity","MuIsoTrackReductionPTActivity", isotrackreductionActivity2D_-1, isoTrackReductionActivity2D_,isotrackreductionPT2D_-1,isoTrackReductionPT2D_);
  MuIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsVeryLow","MuIsoTrackReductionHTMHT_NJetsVeryLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  MuIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsLow","MuIsoTrackReductionHTMHT_NJetsLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  MuIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsHigh","MuIsoTrackReductionHTMHT_NJetsHigh", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);

  // elec iso track
  //1D
  ExpectationReductionElecIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionElecIsoTrackBTagEff","ExpectationReductionElecIsoTrackBTagEff",isotrackreductionBTags_-1,isoTrackReductionBTags_);
  ExpectationReductionElecIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionElecIsoTrackNJetsEff","ExpectationReductionElecIsoTrackNJetsEff",isotrackreductionNJets_-1,isoTrackReductionNJets_);
  ExpectationReductionElecIsoTrackHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackHTEff","ExpectationReductionElecIsoTrackHTEff",isotrackreductionHT_-1,isoTrackReductionHT_);
  ExpectationReductionElecIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackMHTEff","ExpectationReductionElecIsoTrackMHTEff",isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ExpectationReductionElecIsoTrackPTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackPTEff","ExpectationReductionElecIsoTrackPTEff",isotrackreductionPT_-1,isoTrackReductionPT_);
  ExpectationReductionElecIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionElecIsoTrackActivityEff","ExpectationReductionElecIsoTrackActivityEff",isotrackreductionActivity_-1,isoTrackReductionActivity_);
  //2D
  ElecIsoTrackReductionHTNJets_ = new TH2Eff("ElecIsoTrackReductionHTNJets","ElecIsoTrackReductionHTNJets",isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  ElecIsoTrackReductionMHTNJets_ = new TH2Eff("ElecIsoTrackReductionMHTNJets","ElecIsoTrackReductionMHTNJets",isotrackreductionMHT_-1,isoTrackReductionMHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  ElecIsoTrackReductionBTagNJets_ = new TH2Eff("ElecIsoTrackReductionBTagNJets","ElecIsoTrackReductionBTagNJets",isotrackreductionBTags2D_-1,isoTrackReductionBTags2D_, isotrackreductionNJets2D_-1, isoTrackReductionNJets2D_);
  ElecIsoTrackReductionPTActivity_ = new TH2Eff("ElecIsoTrackReductionPTActivity","ElecIsoTrackReductionPTActivity", isotrackreductionActivity2D_-1, isoTrackReductionActivity2D_,isotrackreductionPT2D_-1,isoTrackReductionPT2D_);
  ElecIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsVeryLow","ElecIsoTrackReductionHTMHT_NJetsVeryLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ElecIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsLow","ElecIsoTrackReductionHTMHT_NJetsLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ElecIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsHigh","ElecIsoTrackReductionHTMHT_NJetsHigh", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);

  // pion iso track
  //1D
  ExpectationReductionPionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionPionIsoTrackBTagEff","ExpectationReductionPionIsoTrackBTagEff",isotrackreductionBTags_-1,isoTrackReductionBTags_);
  ExpectationReductionPionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionPionIsoTrackNJetsEff","ExpectationReductionPionIsoTrackNJetsEff",isotrackreductionNJets_-1,isoTrackReductionNJets_);
  ExpectationReductionPionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackHTEff","ExpectationReductionPionIsoTrackHTEff",isotrackreductionHT_-1,isoTrackReductionHT_);
  ExpectationReductionPionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackMHTEff","ExpectationReductionPionIsoTrackMHTEff",isotrackreductionMHT_-1,isoTrackReductionMHT_);
  ExpectationReductionPionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackPTEff","ExpectationReductionPionIsoTrackPTEff",isotrackreductionPT_-1,isoTrackReductionPT_);
  ExpectationReductionPionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionPionIsoTrackActivityEff","ExpectationReductionPionIsoTrackActivityEff",isotrackreductionActivity_-1,isoTrackReductionActivity_);
  //2D
  PionIsoTrackReductionHTNJets_ = new TH2Eff("PionIsoTrackReductionHTNJets","PionIsoTrackReductionHTNJets",isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  PionIsoTrackReductionMHTNJets_ = new TH2Eff("PionIsoTrackReductionMHTNJets","PionIsoTrackReductionMHTNJets",isotrackreductionMHT_-1,isoTrackReductionMHT_, isotrackreductionNJets_-1, isoTrackReductionNJets_);
  PionIsoTrackReductionBTagNJets_ = new TH2Eff("PionIsoTrackReductionBTagNJets","PionIsoTrackReductionBTagNJets",isotrackreductionBTags2D_-1,isoTrackReductionBTags2D_, isotrackreductionNJets2D_-1, isoTrackReductionNJets2D_);
  PionIsoTrackReductionPTActivity_ = new TH2Eff("PionIsoTrackReductionPTActivity","PionIsoTrackReductionPTActivity", isotrackreductionActivity2D_-1, isoTrackReductionActivity2D_,isotrackreductionPT2D_-1,isoTrackReductionPT2D_);
  PionIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsVeryLow","PionIsoTrackReductionHTMHT_NJetsVeryLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  PionIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsLow","PionIsoTrackReductionHTMHT_NJetsLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
  PionIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsHigh","PionIsoTrackReductionHTMHT_NJetsHigh", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);

  // delta R jet and pT jet 
  MuIsoRelPTJet_ = new TH1Eff("MuIsoRelPTJet","MuIsoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  MuIsoDeltaRJet_ = new TH1Eff("MuIsoDeltaRJet","MuIsoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  MuIsoRelPTDeltaRJet_ = new TH2Eff("MuIsoRelPTDeltaRJet","MuIsoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  MuRecoRelPTJet_ = new TH1Eff("MuRecoRelPTJet","MuRecoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  MuRecoDeltaRJet_ = new TH1Eff("MuRecoDeltaRJet","MuRecoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  MuRecoRelPTDeltaRJet_ = new TH2Eff("MuRecoRelPTDeltaRJet","MuRecoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  ElecIsoRelPTJet_ = new TH1Eff("ElecIsoRelPTJet","ElecIsoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  ElecIsoDeltaRJet_ = new TH1Eff("ElecIsoDeltaRJet","ElecIsoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  ElecIsoRelPTDeltaRJet_ = new TH2Eff("ElecIsoRelPTDeltaRJet","ElecIsoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);
  ElecRecoRelPTJet_ = new TH1Eff("ElecRecoRelPTJet","ElecRecoRelPTJet",oneDPTRel_-1,OneDPTRel_);
  ElecRecoDeltaRJet_ = new TH1Eff("ElecRecoDeltaRJet","ElecRecoDeltaRJet",oneDDeltaR_-1,OneDDeltaR_);
  ElecRecoRelPTDeltaRJet_ = new TH2Eff("ElecRecoRelPTDeltaRJet","ElecRecoRelPTDeltaRJet",oneDPTRel_-1,OneDPTRel_,oneDDeltaR_-1,OneDDeltaR_);

  // MHT?PTW histograms
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<3; inb++) {
      LostMuRATIO_HT12[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT12[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT12[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT12_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostMuRATIO_HT3[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT3[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT3[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT3_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostMuRATIO_HT23[inj*3+inb] = new TH1D(Form("LostMuRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostElecRATIO_HT23[inj*3+inb] = new TH1D(Form("LostElecRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
      LostLepRATIO_HT23[inj*3+inb] = new TH1D(Form("LostLepRATIO_HT23_NJ%d_NB%d", inj+1, inb), ";H_{T}^{miss}/p_{T}^{W};Fraction of Events", nEXTRAPBins, 0., 1.3);
    }
  }

}

Bool_t EffMaker::Process(Long64_t entry)
{

//  if (entry%10000==0) cout << "fChain->GetTree()->GetEntry(" << entry << ");" << endl;
  fChain->GetTree()->GetEntry(entry);

  if(Weight<0) return kTRUE;
  if(Bin > 900) return kTRUE;
  
  // purity
  // single muon control sample
  // x-check
  if(MuPurity==2){
      //1D
      MuPurityBTag_->Fill(BTags,Weight,true);
      MuPurityNJets_->Fill(NJets,Weight,true);
      MuPurityHT_->Fill(HT,Weight,true);
      MuPurityMHT_->Fill(MHT,Weight,true);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,Weight,true);
  }else if(MuPurity==0){
      //1D
      MuPurityBTag_->Fill(BTags,Weight,false);
      MuPurityNJets_->Fill(NJets,Weight,false);
      MuPurityHT_->Fill(HT,Weight,false);
      MuPurityMHT_->Fill(MHT,Weight,false);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,Weight,false);
  }

  if(ElecPurity==2){
      //1D
      ElecPurityBTag_->Fill(BTags,Weight,true);
      ElecPurityNJets_->Fill(NJets,Weight,true);
      ElecPurityHT_->Fill(HT,Weight,true);
      ElecPurityMHT_->Fill(MHT,Weight,true);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,Weight,true);
  }else if(ElecPurity==0){
      //1D
      ElecPurityBTag_->Fill(BTags,Weight,false);
      ElecPurityNJets_->Fill(NJets,Weight,false);
      ElecPurityHT_->Fill(HT,Weight,false);
      ElecPurityMHT_->Fill(MHT,Weight,false);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,Weight,false);
  }

  if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0){
      //cout << "muon event" << endl;
      if(selectedIDIsoMuonsPromptMatched->at(0)==1){
          // cout << "PromptMatched" << endl;
          //1D
          MuPurityOldBTag_->Fill(BTags,Weight,true);
          MuPurityOldNJets_->Fill(NJets,Weight,true);
          MuPurityOldHT_->Fill(HT,Weight,true);
          MuPurityOldMHT_->Fill(MHT,Weight,true);
          MuPurityOldPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,true);
          MuPurityOldActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,true);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,Weight,true);
      }
      if(selectedIDIsoMuonsPromptMatched->at(0)==0){
          //1D
          MuPurityOldBTag_->Fill(BTags,Weight,false);
          MuPurityOldNJets_->Fill(NJets,Weight,false);
          MuPurityOldHT_->Fill(HT,Weight,false);
          MuPurityOldMHT_->Fill(MHT,Weight,false);
          MuPurityOldPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,false);
          MuPurityOldActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,false);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,Weight,false);
      }
  }

  // single elec control sample
  if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1){
      if(selectedIDIsoElectronsPromptMatched->at(0)==1){
          //1D
          ElecPurityOldBTag_->Fill(BTags,Weight,true);
          ElecPurityOldNJets_->Fill(NJets,Weight,true);
          ElecPurityOldHT_->Fill(HT,Weight,true);
          ElecPurityOldMHT_->Fill(MHT,Weight,true);
          ElecPurityOldPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,true);
          ElecPurityOldActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,true);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,Weight,true);
      }
      if(selectedIDIsoElectronsPromptMatched->at(0)==0){
          //1D
          ElecPurityOldBTag_->Fill(BTags,Weight,false);
          ElecPurityOldNJets_->Fill(NJets,Weight,false);
          ElecPurityOldHT_->Fill(HT,Weight,false);
          ElecPurityOldMHT_->Fill(MHT,Weight,false);
          ElecPurityOldPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,false);
          ElecPurityOldActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,false);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,Weight,false);
      }
  }

  // acceptance
  // single muon control sample
  if(muAcc==2){
      //1D
      MuAccBTag_->Fill(BTags,Weight,true);
      MuAccNJets_->Fill(NJets,Weight,true);
      MuAccHT_->Fill(HT,Weight,true);
      MuAccMHT_->Fill(MHT,Weight,true);
      MuAccPT_->Fill(GenMus->at(0).Pt(),Weight,true);
      MuAccActivity_->Fill(GenMu_MT2Activity->at(0),Weight,true);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,Weight,true);
      MuAccMHTNJets_->Fill(MHT,NJets,Weight,true);
      MuAccHTMHT_->Fill(HT,MHT,Weight,true);
      MuAccBTagNJets_->Fill(BTags,NJets,Weight,true);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,Weight,true);
          MuAccHTMHTB0_->Fill(HT,MHT,Weight,true);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,Weight,true);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,Weight,true);
      }
      
      if(NJets<6.5){
          MuAccHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
      }else{
          MuAccHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,Weight,true);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,Weight,true);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,Weight,true);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,Weight,true);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,Weight,true);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,Weight,true);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,Weight,true);
  }

  if(muAcc==0){
      //1D
      MuAccBTag_->Fill(BTags,Weight,false);
      MuAccNJets_->Fill(NJets,Weight,false);
      MuAccHT_->Fill(HT,Weight,false);
      MuAccMHT_->Fill(MHT,Weight,false);
      MuAccPT_->Fill(GenMus->at(0).Pt(),Weight,false);
      MuAccActivity_->Fill(GenMu_MT2Activity->at(0),Weight,false);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,Weight,false);
      MuAccMHTNJets_->Fill(MHT,NJets,Weight,false);
      MuAccHTMHT_->Fill(HT,MHT,Weight,false);
      MuAccBTagNJets_->Fill(BTags,NJets,Weight,false);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,Weight,false);
          MuAccHTMHTB0_->Fill(HT,MHT,Weight,false);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,Weight,false);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,Weight,false);
      }

      if(NJets<6.5){
          MuAccHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
      }else{
          MuAccHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,Weight,false);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,Weight,false);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,Weight,false);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,Weight,false);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,Weight,false);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,Weight,false);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,Weight,false);
  }
  
  // single elecon control sample
  if(elecAcc==2){
      //1D
      ElecAccBTag_->Fill(BTags,Weight,true);
      ElecAccNJets_->Fill(NJets,Weight,true);
      ElecAccHT_->Fill(HT,Weight,true);
      ElecAccMHT_->Fill(MHT,Weight,true);
      ElecAccPT_->Fill(GenEls->at(0).Pt(),Weight,true);
      ElecAccActivity_->Fill(GenElec_MT2Activity->at(0),Weight,true);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,Weight,true);
      ElecAccMHTNJets_->Fill(MHT,NJets,Weight,true);
      ElecAccHTMHT_->Fill(HT,MHT,Weight,true);
      ElecAccBTagNJets_->Fill(BTags,NJets,Weight,true);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,Weight,true);
          ElecAccHTMHTB0_->Fill(HT,MHT,Weight,true);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,Weight,true);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,Weight,true);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
      }else{
          ElecAccHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
      }

        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,Weight,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,Weight,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,Weight,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,Weight,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,Weight,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,Weight,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,Weight,true);
  }

  if(elecAcc==0){
      //1D
      ElecAccBTag_->Fill(BTags,Weight,false);
      ElecAccNJets_->Fill(NJets,Weight,false);
      ElecAccHT_->Fill(HT,Weight,false);
      ElecAccMHT_->Fill(MHT,Weight,false);
      ElecAccPT_->Fill(GenEls->at(0).Pt(),Weight,false);
      ElecAccActivity_->Fill(GenElec_MT2Activity->at(0),Weight,false);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,Weight,false);
      ElecAccMHTNJets_->Fill(MHT,NJets,Weight,false);
      ElecAccHTMHT_->Fill(HT,MHT,Weight,false);
      ElecAccBTagNJets_->Fill(BTags,NJets,Weight,false);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,Weight,false);
          ElecAccHTMHTB0_->Fill(HT,MHT,Weight,false);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,Weight,false);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,Weight,false);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
      }else{
          ElecAccHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
      }

      if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,Weight,false);
      if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,Weight,false);
      if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,Weight,false);
      if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,Weight,false);
      if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,Weight,false);
      if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,Weight,false);
      if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,Weight,false);
  }
  
  // reconstruction
  // single muon control sample
  if(muReco==2){
      //1D
      MuRecoBTag_->Fill(BTags,Weight,true);
      MuRecoNJets_->Fill(NJets,Weight,true);
      MuRecoHT_->Fill(HT,Weight,true);
      MuRecoMHT_->Fill(MHT,Weight,true);
      MuRecoPT_->Fill(GenMus->at(0).Pt(),Weight,true);
      MuRecoActivity_->Fill(GenMu_MT2Activity->at(0),Weight,true);
      MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),Weight,true);
      MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),Weight,true);
      //2D
      MuRecoActivityPT_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,true);
      MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),Weight,true);
      MuRecoPTEta_->Fill(GenMus->at(0).Pt(),std::abs(GenMus->at(0).Eta()),Weight,true);
  }

  if(muReco==0){
      //1D
      MuRecoBTag_->Fill(BTags,Weight,false);
      MuRecoNJets_->Fill(NJets,Weight,false);
      MuRecoHT_->Fill(HT,Weight,false);
      MuRecoMHT_->Fill(MHT,Weight,false);
      MuRecoPT_->Fill(GenMus->at(0).Pt(),Weight,false);
      MuRecoActivity_->Fill(GenMu_MT2Activity->at(0),Weight,false);
      MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),Weight,false);
      MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),Weight,false);
      //2D
      MuRecoActivityPT_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,false);
      MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),Weight,false);
      MuRecoPTEta_->Fill(GenMus->at(0).Pt(),std::abs(GenMus->at(0).Eta()),Weight,false);
  }
  
  // single elecon control sample
  if(elecReco==2){
      //1D
      ElecRecoBTag_->Fill(BTags,Weight,true);
      ElecRecoNJets_->Fill(NJets,Weight,true);
      ElecRecoHT_->Fill(HT,Weight,true);
      ElecRecoMHT_->Fill(MHT,Weight,true);
      ElecRecoPT_->Fill(GenEls->at(0).Pt(),Weight,true);
      ElecRecoActivity_->Fill(GenElec_MT2Activity->at(0),Weight,true);
      ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),Weight,true);
      ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at