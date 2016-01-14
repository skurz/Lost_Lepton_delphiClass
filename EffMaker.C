#define EffMaker_cxx
#include "EffMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include "TSystem.h"
#include "TMath.h"

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
  
  // purity x-check

  // muon
  // 1D
  MuPurityCheckBTag_ = new TH1Eff("MuPurityCheckBTag1D","MuPurityCheckBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityCheckNJets_ = new TH1Eff("MuPurityCheckNJets1D","MuPurityCheckNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityCheckHT_ = new TH1Eff("MuPurityCheckHT1D","MuPurityCheckHT1D",oneDHT_-1,OneDHT_);
  MuPurityCheckMHT_ = new TH1Eff("MuPurityCheckMHT1D","MuPurityCheckMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityCheckMHTNJet_ = new TH2Eff("MuonPurityCheckMHTNJet","MuonPurityCheckMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  // electron
  //1D
  ElecPurityCheckBTag_ = new TH1Eff("ElecPurityCheckBTag1D","ElecPurityCheckBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityCheckNJets_ = new TH1Eff("ElecPurityCheckNJets1D","ElecPurityCheckNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityCheckHT_ = new TH1Eff("ElecPurityCheckHT1D","ElecPurityCheckHT1D",oneDHT_-1,OneDHT_);
  ElecPurityCheckMHT_ = new TH1Eff("ElecPurityCheckMHT1D","ElecPurityCheckMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityCheckMHTNJet_ = new TH2Eff("ElecPurityCheckMHTNJet","ElecPurityCheckMHTNJet",mupurityMHT_-1,muPurityMHT_,mupurityNJet_-1,muPurityNJet_);
  
  
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
  
  //electron
  //1D
  ElecDiLepContributionBTag_ = new TH1Eff("ElecDiLepContributionBTag1D","ElecDiLepContributionBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepContributionNJets_ = new TH1Eff("ElecDiLepContributionNJets1D","ElecDiLepContributionNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepContributionHT_ = new TH1Eff("ElecDiLepContributionHT1D","ElecDiLepContributionHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepContributionMHT_ = new TH1Eff("ElecDiLepContributionMHT1D","ElecDiLepContributionMHT1D",oneDMHT_-1,OneDMHT_);
  
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
  MuPurityPT_ = new TH1Eff("MuPurityPT","MuPurityPT",oneDPT_-1,OneDPT_);
  MuPurityActivity_ = new TH1Eff("MuPurityActivity","MuPurityActivity",oneDActivity_-1,OneDActivity_);
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
  ElecPurityPT_ = new TH1Eff("ElecPurityPT","ElecPurityPT",oneDPT_-1,OneDPT_);
  ElecPurityActivity_ = new TH1Eff("ElecPurityActivity","ElecPurityActivity",oneDActivity_-1,OneDActivity_);
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
  IsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow","IsoTrackReductionHTMHT_NJetsLow", isotrackreductionHT_-1,isoTrackReductionHT_, isotrackreductionMHT_-1,isoTrackReductionMHT_);
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
  
}

Bool_t EffMaker::Process(Long64_t entry)
{

  fChain->GetTree()->GetEntry(entry);

  if(Weight<0) return kTRUE;
  if(Bin > 900) return kTRUE;
  
  // purity
  // single muon control sample
  // x-check
  if(MuPurity==2){
      //1D
      MuPurityCheckBTag_->Fill(BTags,Weight,true);
      MuPurityCheckNJets_->Fill(NJets,Weight,true);
      MuPurityCheckHT_->Fill(HT,Weight,true);
      MuPurityCheckMHT_->Fill(MHT,Weight,true);
      //2D
      MuonPurityCheckMHTNJet_->Fill(MHT,NJets,Weight,true);
  }else if(MuPurity==0){
      //1D
      MuPurityCheckBTag_->Fill(BTags,Weight,false);
      MuPurityCheckNJets_->Fill(NJets,Weight,false);
      MuPurityCheckHT_->Fill(HT,Weight,false);
      MuPurityCheckMHT_->Fill(MHT,Weight,false);
      //2D
      MuonPurityCheckMHTNJet_->Fill(MHT,NJets,Weight,false);
  }

  if(ElecPurity==2){
      //1D
      ElecPurityCheckBTag_->Fill(BTags,Weight,true);
      ElecPurityCheckNJets_->Fill(NJets,Weight,true);
      ElecPurityCheckHT_->Fill(HT,Weight,true);
      ElecPurityCheckMHT_->Fill(MHT,Weight,true);
      //2D
      ElecPurityCheckMHTNJet_->Fill(MHT,NJets,Weight,true);
  }else if(ElecPurity==0){
      //1D
      ElecPurityCheckBTag_->Fill(BTags,Weight,false);
      ElecPurityCheckNJets_->Fill(NJets,Weight,false);
      ElecPurityCheckHT_->Fill(HT,Weight,false);
      ElecPurityCheckMHT_->Fill(MHT,Weight,false);
      //2D
      ElecPurityCheckMHTNJet_->Fill(MHT,NJets,Weight,false);
  }

  if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0){
      //cout << "muon event" << endl;
      if(selectedIDIsoMuonsPromptMatched->at(0)==1){
          // cout << "PromptMatched" << endl;
          //1D
          MuPurityBTag_->Fill(BTags,Weight,true);
          MuPurityNJets_->Fill(NJets,Weight,true);
          MuPurityHT_->Fill(HT,Weight,true);
          MuPurityMHT_->Fill(MHT,Weight,true);
          MuPurityPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,true);
          MuPurityActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,true);
          //2D
          MuonPurityMHTNJet_->Fill(MHT,NJets,Weight,true);
      }
      if(selectedIDIsoMuonsPromptMatched->at(0)==0){
          //1D
          MuPurityBTag_->Fill(BTags,Weight,false);
          MuPurityNJets_->Fill(NJets,Weight,false);
          MuPurityHT_->Fill(HT,Weight,false);
          MuPurityMHT_->Fill(MHT,Weight,false);
          MuPurityPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,false);
          MuPurityActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,false);
          //2D
          MuonPurityMHTNJet_->Fill(MHT,NJets,Weight,false);
      }
  }

  // single elec control sample
  if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1){
      if(selectedIDIsoElectronsPromptMatched->at(0)==1){
          //1D
          ElecPurityBTag_->Fill(BTags,Weight,true);
          ElecPurityNJets_->Fill(NJets,Weight,true);
          ElecPurityHT_->Fill(HT,Weight,true);
          ElecPurityMHT_->Fill(MHT,Weight,true);
          ElecPurityPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,true);
          ElecPurityActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,true);
          //2D
          ElecPurityMHTNJet_->Fill(MHT,NJets,Weight,true);
      }
      if(selectedIDIsoElectronsPromptMatched->at(0)==0){
          //1D
          ElecPurityBTag_->Fill(BTags,Weight,false);
          ElecPurityNJets_->Fill(NJets,Weight,false);
          ElecPurityHT_->Fill(HT,Weight,false);
          ElecPurityMHT_->Fill(MHT,Weight,false);
          ElecPurityPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,false);
          ElecPurityActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,false);
          //2D
          ElecPurityMHTNJet_->Fill(MHT,NJets,Weight,false);
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
      ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),Weight,true);
      //2D
      ElecRecoActivityPT_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,true);
      ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),Weight,true);
      ElecRecoPTEta_->Fill(GenEls->at(0).Pt(),std::abs(GenEls->at(0).Eta()),Weight,true);
  }

  if(elecReco==0){
      //1D
      ElecRecoBTag_->Fill(BTags,Weight,false);
      ElecRecoNJets_->Fill(NJets,Weight,false);
      ElecRecoHT_->Fill(HT,Weight,false);
      ElecRecoMHT_->Fill(MHT,Weight,false);
      ElecRecoPT_->Fill(GenEls->at(0).Pt(),Weight,false);
      ElecRecoActivity_->Fill(GenElec_MT2Activity->at(0),Weight,false);
      ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),Weight,false);
      ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),Weight,false);
      //2D
      ElecRecoActivityPT_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,false);
      ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),Weight,false);
      ElecRecoPTEta_->Fill(GenEls->at(0).Pt(),std::abs(GenEls->at(0).Eta()),Weight,false);
  }
  
  // isolation
  // single muon control sample
  if(muIso==2){
      //1D
      MuIsoBTag_->Fill(BTags,Weight,true);
      MuIsoNJets_->Fill(NJets,Weight,true);
      MuIsoHT_->Fill(HT,Weight,true);
      MuIsoMHT_->Fill(MHT,Weight,true);
      MuIsoPT_->Fill(GenMus->at(0).Pt(),Weight,true);
      MuIsoActivity_->Fill(GenMu_MT2Activity->at(0),Weight,true);
      MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),Weight,true);
      MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),Weight,true);
      //2D
      MuIsoActivityPT_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,true);
      MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),Weight,true);
  }

  if(muIso==0){
      //1D
      MuIsoBTag_->Fill(BTags,Weight,false);
      MuIsoNJets_->Fill(NJets,Weight,false);
      MuIsoHT_->Fill(HT,Weight,false);
      MuIsoMHT_->Fill(MHT,Weight,false);
      MuIsoPT_->Fill(GenMus->at(0).Pt(),Weight,false);
      MuIsoActivity_->Fill(GenMu_MT2Activity->at(0),Weight,false);
      MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),Weight,false);
      MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),Weight,false);
      //2D
      MuIsoActivityPT_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,false);
      MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),Weight,false);
  }
  
  // single elecon control sample
  if(elecIso==2){
      //1D
      ElecIsoBTag_->Fill(BTags,Weight,true);
      ElecIsoNJets_->Fill(NJets,Weight,true);
      ElecIsoHT_->Fill(HT,Weight,true);
      ElecIsoMHT_->Fill(MHT,Weight,true);
      ElecIsoPT_->Fill(GenEls->at(0).Pt(),Weight,true);
      ElecIsoActivity_->Fill(GenElec_MT2Activity->at(0),Weight,true);
      ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),Weight,true);
      ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),Weight,true);
      //2D
      ElecIsoActivityPT_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,true);
      ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),Weight,true);
  }

  if(elecIso==0){
      //1D
      ElecIsoBTag_->Fill(BTags,Weight,false);
      ElecIsoNJets_->Fill(NJets,Weight,false);
      ElecIsoHT_->Fill(HT,Weight,false);
      ElecIsoMHT_->Fill(MHT,Weight,false);
      ElecIsoPT_->Fill(GenEls->at(0).Pt(),Weight,false);
      ElecIsoActivity_->Fill(GenElec_MT2Activity->at(0),Weight,false);
      ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),Weight,false);
      ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),Weight,false);
      //2D
      ElecIsoActivityPT_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,false);
      ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),Weight,false);
  }

  // mtw
  // single muon control sample
  if(muIso==2 && MTW < mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,Weight,true);
      MuMTWNJets_->Fill(NJets,Weight,true);
      MuMTWHT_->Fill(HT,Weight,true);
      MuMTWMHT_->Fill(MHT,Weight,true);
      MuMTWPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,true);
      MuMTWActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,true);
      MuMTWPTActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),selectedIDIsoMuons->at(0).Pt(),Weight,true);
      MuMTWHTNJets_->Fill(HT, NJets, Weight, true);
  }

  if(muIso==2 && MTW > mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,Weight,false);
      MuMTWNJets_->Fill(NJets,Weight,false);
      MuMTWHT_->Fill(HT,Weight,false);
      MuMTWMHT_->Fill(MHT,Weight,false);
      MuMTWPT_->Fill(selectedIDIsoMuons->at(0).Pt(),Weight,false);
      MuMTWActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),Weight,false);
      MuMTWPTActivity_->Fill(selectedIDIsoMuons_MT2Activity->at(0),selectedIDIsoMuons->at(0).Pt(),Weight,false);
      MuMTWHTNJets_->Fill(HT, NJets, Weight, false);
  }
  
  // single elec control sample
  if(elecIso==2 && MTW < mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,Weight,true);
      ElecMTWNJets_->Fill(NJets,Weight,true);
      ElecMTWHT_->Fill(HT,Weight,true);
      ElecMTWMHT_->Fill(MHT,Weight,true);
      ElecMTWPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,true);
      ElecMTWActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,true);
      ElecMTWPTActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),selectedIDIsoElectrons->at(0).Pt(),Weight,true);
      ElecMTWHTNJets_->Fill(HT, NJets, Weight, true);
  }

  if(elecIso==2 && MTW > mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,Weight,false);
      ElecMTWNJets_->Fill(NJets,Weight,false);
      ElecMTWHT_->Fill(HT,Weight,false);
      ElecMTWMHT_->Fill(MHT,Weight,false);
      ElecMTWPT_->Fill(selectedIDIsoElectrons->at(0).Pt(),Weight,false);
      ElecMTWActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),Weight,false);
      ElecMTWPTActivity_->Fill(selectedIDIsoElectrons_MT2Activity->at(0),selectedIDIsoElectrons->at(0).Pt(),Weight,false);
      ElecMTWHTNJets_->Fill(HT, NJets, Weight, false);
  }

  // di lep contribution
  if(MuDiLepControlSample==2){
      // 1D
      MuDiLepBTag_->Fill(BTags,Weight,true);
      MuDiLepNJets_->Fill(NJets,Weight,true);
      MuDiLepHT_->Fill(HT,Weight,true);
      MuDiLepMHT_->Fill(MHT,Weight,true);

      // 1D
      MuDiLepContributionBTag_->Fill(BTags,Weight,true);
      MuDiLepContributionNJets_->Fill(NJets,Weight,true);
      MuDiLepContributionHT_->Fill(HT,Weight,true);
      MuDiLepContributionMHT_->Fill(MHT,Weight,true);

      if(MTW <mtwCut_){
          // 1D
          MuDiLepMTWBTag_->Fill(BTags,Weight,true);
          MuDiLepMTWNJets_->Fill(NJets,Weight,true);
          MuDiLepMTWHT_->Fill(HT,Weight,true);
          MuDiLepMTWMHT_->Fill(MHT,Weight,true);
      }

      if(MTW <mtwCut_){
          // 1D
          MuDiLepContributionMTWBTag_->Fill(BTags,Weight,true);
          MuDiLepContributionMTWNJets_->Fill(NJets,Weight,true);
          MuDiLepContributionMTWHT_->Fill(HT,Weight,true);
          MuDiLepContributionMTWMHT_->Fill(MHT,Weight,true);
      }
    
  }

  if(MuDiLepControlSample==0){
      // 1D
      MuDiLepContributionBTag_->Fill(BTags,Weight,false);
      MuDiLepContributionNJets_->Fill(NJets,Weight,false);
      MuDiLepContributionHT_->Fill(HT,Weight,false);
      MuDiLepContributionMHT_->Fill(MHT,Weight,false);

      // 1D
      MuDiLepBTag_->Fill(BTags,Weight,false);
      MuDiLepNJets_->Fill(NJets,Weight,false);
      MuDiLepHT_->Fill(HT,Weight,false);
      MuDiLepMHT_->Fill(MHT,Weight,false);
    
      // 1D
      MuDiLepMTWBTag_->Fill(BTags,Weight,false);
      MuDiLepMTWNJets_->Fill(NJets,Weight,false);
      MuDiLepMTWHT_->Fill(HT,Weight,false);
      MuDiLepMTWMHT_->Fill(MHT,Weight,false);

      if(MTW <mtwCut_){
          // 1D
          MuDiLepContributionMTWBTag_->Fill(BTags,Weight,false);
          MuDiLepContributionMTWNJets_->Fill(NJets,Weight,false);
          MuDiLepContributionMTWHT_->Fill(HT,Weight,false);
          MuDiLepContributionMTWMHT_->Fill(MHT,Weight,false);
      }
  }
  
  if(ElecDiLepControlSample==2){
      // 1D
      ElecDiLepBTag_->Fill(BTags,Weight,true);
      ElecDiLepNJets_->Fill(NJets,Weight,true);
      ElecDiLepHT_->Fill(HT,Weight,true);
      ElecDiLepMHT_->Fill(MHT,Weight,true);

      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,Weight,true);
      ElecDiLepContributionNJets_->Fill(NJets,Weight,true);
      ElecDiLepContributionHT_->Fill(HT,Weight,true);
      ElecDiLepContributionMHT_->Fill(MHT,Weight,true);

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepMTWBTag_->Fill(BTags,Weight,true);
          ElecDiLepMTWNJets_->Fill(NJets,Weight,true);
          ElecDiLepMTWHT_->Fill(HT,Weight,true);
          ElecDiLepMTWMHT_->Fill(MHT,Weight,true);
      }
      
      if(MTW <mtwCut_){
          // 1D
          ElecDiLepContributionMTWBTag_->Fill(BTags,Weight,true);
          ElecDiLepContributionMTWNJets_->Fill(NJets,Weight,true);
          ElecDiLepContributionMTWHT_->Fill(HT,Weight,true);
          ElecDiLepContributionMTWMHT_->Fill(MHT,Weight,true);
      }
    
  }

  if(ElecDiLepControlSample==0) {
    
      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,Weight,false);
      ElecDiLepContributionNJets_->Fill(NJets,Weight,false);
      ElecDiLepContributionHT_->Fill(HT,Weight,false);
      ElecDiLepContributionMHT_->Fill(MHT,Weight,false);

      // 1D
      ElecDiLepBTag_->Fill(BTags,Weight,false);
      ElecDiLepNJets_->Fill(NJets,Weight,false);
      ElecDiLepHT_->Fill(HT,Weight,false);
      ElecDiLepMHT_->Fill(MHT,Weight,false);
    
      // 1D
      ElecDiLepMTWBTag_->Fill(BTags,Weight,false);
      ElecDiLepMTWNJets_->Fill(NJets,Weight,false);
      ElecDiLepMTWHT_->Fill(HT,Weight,false);
      ElecDiLepMTWMHT_->Fill(MHT,Weight,false);

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepContributionMTWBTag_->Fill(BTags,Weight,false);
          ElecDiLepContributionMTWNJets_->Fill(NJets,Weight,false);
          ElecDiLepContributionMTWHT_->Fill(HT,Weight,false);
          ElecDiLepContributionMTWMHT_->Fill(MHT,Weight,false);
      }
  }  
    
  // ExpectationReductionIsoTrack
  if(Expectation==1 && ExpectationReductionIsoTrack==0){
      //  cout << "Event not rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,Weight,false);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,Weight,false);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,Weight,false);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,Weight,false);

      if(GenMuNum>0){
          //  cout << "Muon event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenMus->at(0).Pt(),Weight,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMu_MT2Activity->at(0),Weight,false);
      }else if(GenElecNum>0){
          // cout << "Electron event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenEls->at(0).Pt(),Weight,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElec_MT2Activity->at(0),Weight,false);
      }else if(GenTauNum>0){
          // cout << "Tau event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),Weight,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTau_MT2Activity->at(0),Weight,false);
      }else std::cout<<"No gen lepton found to fail..."<<std::endl;

      //2D
      IsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,false);
      IsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,false);
      IsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,false);
      if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
      else IsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
      if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,Weight,false);
      if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,Weight,false);
      if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,Weight,false);

      if(GenMuNum>0){
          IsoTrackReductionPTActivity_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,false);
      }else if(GenElecNum>0){
          IsoTrackReductionPTActivity_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,false);
      }else if(GenTauNum>0){
          IsoTrackReductionPTActivity_->Fill(GenTau_MT2Activity->at(0),GenTaus->at(0).Pt(),Weight,false);
      }
  }
  
  if(Expectation==1 && ExpectationReductionIsoTrack==1){
      // cout << "Event rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,Weight,true);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,Weight,true);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,Weight,true);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,Weight,true);

      if(isoMuonTracks>0 && GenMuNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenMus->at(0).Pt(),Weight,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMu_MT2Activity->at(0),Weight,true);
      }else if(isoElectronTracks>0 && GenElecNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenEls->at(0).Pt(),Weight,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElec_MT2Activity->at(0),Weight,true);
      }else if(isoPionTracks>0 && GenTauNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),Weight,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTau_MT2Activity->at(0),Weight,true);
    }

    //2D
    IsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,true);
    IsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,true);
    IsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,true);
    if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
    else IsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
    if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,Weight,true);
    if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,Weight,true);
    if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,Weight,true);

    if(isoMuonTracks>0 && GenMuNum>0){
        IsoTrackReductionPTActivity_->Fill(GenMu_MT2Activity->at(0),GenMus->at(0).Pt(),Weight,true);
    }else if(isoElectronTracks>0 && GenElecNum>0){
        IsoTrackReductionPTActivity_->Fill(GenElec_MT2Activity->at(0),GenEls->at(0).Pt(),Weight,true);
    }else if(isoPionTracks>0 && GenTauNum>0){
        IsoTrackReductionPTActivity_->Fill(GenTau_MT2Activity->at(0),GenTaus->at(0).Pt(),Weight,true);
    }
  }

    // In order to avoid double-counting events, only select track with highest pt
    if(Expectation==1){
        int isoTrack_highestPt = 0;

        if(isoMuonTracks>0){
            isoTrack_highestPt = 1;
            if(isoElectronTracks>0 && isoPionTracks>0){
                if(IsolatedElectronTracksVeto->at(0).Pt() > TMath::Max(IsolatedMuonTracksVeto->at(0).Pt(), IsolatedPionTracksVeto->at(0).Pt())) isoTrack_highestPt = 2;
                if(IsolatedPionTracksVeto->at(0).Pt() > TMath::Max(IsolatedMuonTracksVeto->at(0).Pt(), IsolatedElectronTracksVeto->at(0).Pt())) isoTrack_highestPt = 3;
            }else if(isoElectronTracks>0){
                if(IsolatedElectronTracksVeto->at(0).Pt() > IsolatedMuonTracksVeto->at(0).Pt()) isoTrack_highestPt = 2;
            }else if(isoPionTracks>0){
                if(IsolatedPionTracksVeto->at(0).Pt() > IsolatedMuonTracksVeto->at(0).Pt()) isoTrack_highestPt = 3;
            }
        }else if(isoElectronTracks>0){
            isoTrack_highestPt = 2;
            if(isoPionTracks>0) if(IsolatedPionTracksVeto->at(0).Pt() > IsolatedElectronTracksVeto->at(0).Pt()) isoTrack_highestPt = 3;
        }else if(isoPionTracks>0){
            isoTrack_highestPt = 3;
        }


        // muon iso tracks
        if(isoMuonTracks>0 && isoTrack_highestPt==1){
            // cout << "Muon tracks found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,Weight,true);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,Weight,true);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,Weight,true);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,Weight,true);
            ExpectationReductionMuIsoTrackPTEff_->Fill(IsolatedMuonTracksVeto->at(0).Pt(),Weight,true);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(IsolatedMuonTracksVetoActivity->at(0),Weight,true);
          
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,true);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,true);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,true);
            //  MuIsoTrackReductionPTActivity_->Fill(IsolatedMuonTracksVetoActivity->at(0),IsolatedMuonTracksVeto->at(0).Pt(),Weight,true);
            if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
            else MuIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
            // cout << "DONE" << endl;
        }else{
            // cout << "Muon tracks not found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,Weight,false);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,Weight,false);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,Weight,false);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,Weight,false);
            // JACK -- placeholders
            ExpectationReductionMuIsoTrackPTEff_->Fill(0,Weight,false);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(0,Weight,false);
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,false);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,false);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,false);
            //  MuIsoTrackReductionPTActivity_->Fill(0,0,Weight,false);
            if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
            else MuIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
            // cout << "DONE" << endl;
        }
      
      
        // elec iso tracks
        if(isoElectronTracks>0 && isoTrack_highestPt==2){
            // cout << "Electron tracks found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,Weight,true);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,Weight,true);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,Weight,true);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,Weight,true);
            ExpectationReductionElecIsoTrackPTEff_->Fill(IsolatedElectronTracksVeto->at(0).Pt(),Weight,true);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(IsolatedElectronTracksVetoActivity->at(0),Weight,true);
          
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,true);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,true);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,true);
            //  ElecIsoTrackReductionPTActivity_->Fill(IsolatedElectronTracksVetoActivity->at(0),IsolatedElectronTracksVeto->at(0).Pt(),Weight,true);
            if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
            else ElecIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
            // cout << "DONE" << endl;    
        }else{
            // cout << "Electron tracks not found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,Weight,false);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,Weight,false);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,Weight,false);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,Weight,false);
            ExpectationReductionElecIsoTrackPTEff_->Fill(0,Weight,false);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(0,Weight,false);
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,false);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,false);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,false);
            //  ElecIsoTrackReductionPTActivity_->Fill(0,0,Weight,false);
            if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
            else ElecIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
            // cout << "DONE" << endl;    
        }

        // pion iso tracks
        if(isoPionTracks>0 && isoTrack_highestPt==3){
            // cout << "Pion tracks found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,Weight,true);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,Weight,true);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,Weight,true);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,Weight,true);
            ExpectationReductionPionIsoTrackPTEff_->Fill(IsolatedPionTracksVeto->at(0).Pt(),Weight,true);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(IsolatedPionTracksVetoActivity->at(0),Weight,true);
          
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,true);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,true);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,true);
            //  PionIsoTrackReductionPTActivity_->Fill(IsolatedPionTracksVetoActivity->at(0),IsolatedPionTracksVeto->at(0).Pt(),Weight,true);
            if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,true);
            else PionIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,true);
            // cout << "DONE" << endl;    
        }else{
            // cout << "Pion tracks not found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,Weight,false);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,Weight,false);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,Weight,false);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,Weight,false);
            ExpectationReductionPionIsoTrackPTEff_->Fill(0,Weight,false);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(0,Weight,false);
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,Weight,false);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,Weight,false);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,Weight,false);
            //  PionIsoTrackReductionPTActivity_->Fill(0,0,Weight,false);
            if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,Weight,false);
            else PionIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,Weight,false);
            // cout << "DONE" << endl;    
        }
    }
  
  return kTRUE;
}

void EffMaker::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

void EffMaker::Terminate()
{

  
  TFile *outPutFile = new TFile("Efficiencies.root","RECREATE"); 
  outPutFile->cd();
  outPutFile->mkdir("Efficiencies");
  TDirectory *dEfficiencies = (TDirectory*)outPutFile->Get("Efficiencies");
  dEfficiencies->cd();
  gStyle->SetPaintTextFormat("5.2f");
  gStyle->SetStatW(0.1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatY(202);
  gStyle->SetTitleYOffset(1.3);

  gStyle->SetPalette(56);
  gStyle->SetMarkerSize(1.3);
  
  // purity
  //muon
  //1D
  MuPurityBTag_->SaveEff("#mu purity; B_{Tags}", dEfficiencies);
  MuPurityNJets_->SaveEff("#mu purity; N_{Jets}", dEfficiencies);   
  MuPurityHT_->SaveEff("#mu purity; H_{T} [GeV]", dEfficiencies);   
  MuPurityMHT_->SaveEff("#mu purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuonPurityMHTNJet_->SaveEff("#mu purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  //1D
  ElecPurityBTag_->SaveEff("e purity; B_{Tags}", dEfficiencies);
  ElecPurityNJets_->SaveEff("e purity; N_{Jets}", dEfficiencies);   
  ElecPurityHT_->SaveEff("e purity; H_{T} [GeV]", dEfficiencies);   
  ElecPurityMHT_->SaveEff("e purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecPurityMHTNJet_->SaveEff("e purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuPurityCheckBTag_->SaveEff("#mu purity; B_{Tags}", dEfficiencies);   
  MuPurityCheckNJets_->SaveEff("#mu purity; N_{Jets}", dEfficiencies);   
  MuPurityCheckHT_->SaveEff("#mu purity; H_{T} [GeV]", dEfficiencies);   
  MuPurityCheckMHT_->SaveEff("#mu purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuonPurityCheckMHTNJet_->SaveEff("#mu purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  //elec
  //1D
  ElecPurityCheckBTag_->SaveEff("e purity; B_{Tags}", dEfficiencies);   
  ElecPurityCheckNJets_->SaveEff("e purity; N_{Jets}", dEfficiencies);   
  ElecPurityCheckHT_->SaveEff("e purity; H_{T} [GeV]", dEfficiencies);   
  ElecPurityCheckMHT_->SaveEff("e purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecPurityCheckMHTNJet_->SaveEff("e purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   

  // acc
  //muon
  //1D
  MuAccBTag_->SaveEff("#mu acc; B_{Tags}", dEfficiencies);   
  MuAccNJets_->SaveEff("#mu acc; N_{Jets}", dEfficiencies);   
  MuAccHT_->SaveEff("#mu acc; H_{T} [GeV]", dEfficiencies);   
  MuAccMHT_->SaveEff("#mu acc; #slash{H}_{T} [GeV]", dEfficiencies);   
  // 2D 
  MuAccHTNJets_->SaveEff("#mu acc; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccHTMHT_->SaveEff("#mu acc; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccMHTNJets_->SaveEff("#mu acc; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccBTagNJets_->SaveEff("#mu acc; B_{Tags}; N_{Jets}", dEfficiencies);   
  MuAccMHTNJetsB0_->SaveEff("#mu acc B_{Tags}=0; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccMHTNJetsB1_Inf_->SaveEff("#mu acc B_{Tags}#geq1; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccHTMHT_NJetsLow_->SaveEff("#mu acc N_{Jets}=4-6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_->SaveEff("#mu acc N_{Jets}=4;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_->SaveEff("#mu acc N_{Jets}=5;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_->SaveEff("#mu acc N_{Jets}=6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_->SaveEff("#mu acc N_{Jets}=7-8;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_->SaveEff("#mu acc N_{Jets}=9+;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJetsHigh_->SaveEff("#mu acc N_{Jets}#geq7;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHTB0_->SaveEff("#mu acc B_{Tags}=0;H_{T} [GeV] ; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHTB1_Inf_->SaveEff("#mu acc B_{Tags}#geq1; H_{T} [GeV]; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   

  //elec
  //1D
  ElecAccBTag_->SaveEff("e acc; B_{Tags}", dEfficiencies);   
  ElecAccNJets_->SaveEff("e acc; N_{Jets}", dEfficiencies);   
  ElecAccHT_->SaveEff("e acc; H_{T} [GeV]", dEfficiencies);   
  ElecAccMHT_->SaveEff("e acc; #slash{H}_{T} [GeV]", dEfficiencies);   
  // 2D 
  ElecAccHTNJets_->SaveEff("e acc; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccHTMHT_->SaveEff("e acc; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccMHTNJets_->SaveEff("e acc; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccBTagNJets_->SaveEff("e acc; B_{Tags}; N_{Jets}", dEfficiencies);   
  ElecAccMHTNJetsB0_->SaveEff("e acc B_{Tags}=0; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccMHTNJetsB1_Inf_->SaveEff("e acc B_{Tags}#geq1; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccHTMHT_NJetsLow_->SaveEff("e acc N_{Jets}=4-6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_->SaveEff("e acc N_{Jets}=4;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_->SaveEff("e acc N_{Jets}=5;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_->SaveEff("e acc N_{Jets}=6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_->SaveEff("e acc N_{Jets}=7-8;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_->SaveEff("e acc N_{Jets}=9+;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJetsHigh_->SaveEff("e acc N_{Jets}#geq7;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHTB0_->SaveEff("e acc B_{Tags}=0;H_{T} [GeV] ; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHTB1_Inf_->SaveEff("e acc B_{Tags}#geq1; H_{T} [GeV]; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   

  // reco
  //muon
  //1D
  MuRecoBTag_->SaveEff("#mu reco; B_{Tags}", dEfficiencies);   
  MuRecoNJets_->SaveEff("#mu reco; N_{Jets}", dEfficiencies);   
  MuRecoHT_->SaveEff("#mu reco; H_{T} [GeV]", dEfficiencies);   
  MuRecoMHT_->SaveEff("#mu reco; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuRecoRelPTJet_->SaveEff("#mu reco; p_{T}(#mu)/Jet p_{T}", dEfficiencies);   
  MuRecoDeltaRJet_->SaveEff("#mu reco; #DeltaR", dEfficiencies);   
  MuRecoRelPTDeltaRJet_->SaveEff("#mu reco; p_{T}(#mu)/Jet p_{T}; #DeltaR", dEfficiencies);   

  //elec
  //1D
  ElecRecoBTag_->SaveEff("e reco; B_{Tags}", dEfficiencies);   
  ElecRecoNJets_->SaveEff("e reco; N_{Jets}", dEfficiencies);   
  ElecRecoHT_->SaveEff("e reco; H_{T} [GeV]", dEfficiencies);   
  ElecRecoMHT_->SaveEff("e reco; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecRecoRelPTJet_->SaveEff("e reco; p_{T}(e)/Jet p_{T}", dEfficiencies);   
  ElecRecoDeltaRJet_->SaveEff("e reco; #DeltaR", dEfficiencies);   
  ElecRecoRelPTDeltaRJet_->SaveEff("e reco; p_{T}(e)/Jet p_{T}; #DeltaR", dEfficiencies);   

  // iso
  //muon
  //1D
  MuIsoBTag_->SaveEff("#mu iso; B_{Tags}", dEfficiencies);   
  MuIsoNJets_->SaveEff("#mu iso; N_{Jets}", dEfficiencies);   
  MuIsoHT_->SaveEff("#mu iso; H_{T} [GeV]", dEfficiencies);   
  MuIsoMHT_->SaveEff("#mu iso; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuIsoRelPTJet_->SaveEff("#mu iso; p_{T}(#mu)/Jet p_{T}", dEfficiencies);   
  MuIsoDeltaRJet_->SaveEff("#mu iso; #DeltaR", dEfficiencies);   
  MuIsoRelPTDeltaRJet_->SaveEff("#mu iso; p_{T}(#mu)/Jet p_{T}; #DeltaR", dEfficiencies);   

  //elec
  //1D
  ElecIsoBTag_->SaveEff("e iso; B_{Tags}", dEfficiencies);   
  ElecIsoNJets_->SaveEff("e iso; N_{Jets}", dEfficiencies);   
  ElecIsoHT_->SaveEff("e iso; H_{T} [GeV]", dEfficiencies);   
  ElecIsoMHT_->SaveEff("e iso; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecIsoRelPTJet_->SaveEff("e iso; p_{T}(e)/Jet p_{T}", dEfficiencies);   
  ElecIsoDeltaRJet_->SaveEff("e iso; #DeltaR", dEfficiencies);   
  ElecIsoRelPTDeltaRJet_->SaveEff("e iso; p_{T}(e)/Jet p_{T}; #DeltaR", dEfficiencies);   

  // m_{T}^{W}
  //muon
  //1D
  MuMTWBTag_->SaveEff("#mu m_{T}^{W}; B_{Tags}", dEfficiencies);   
  MuMTWNJets_->SaveEff("#mu m_{T}^{W}; N_{Jets}", dEfficiencies);   
  MuMTWHT_->SaveEff("#mu m_{T}^{W}; H_{T} [GeV]", dEfficiencies);   
  MuMTWMHT_->SaveEff("#mu m_{T}^{W}; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuMTWPTActivity_->SaveEff("#mu m_{T}^{W};  Activity; p_{T}(#mu) [GeV]", dEfficiencies, true);
  MuMTWHTNJets_->SaveEff("#mu m_{T}(w); H_{T} [GeV]; N_{Jets}", dEfficiencies);


  //muon
  //1D
  MuDiLepBTag_->SaveEff("#mu di lep; B_{Tags}", dEfficiencies);   
  MuDiLepNJets_->SaveEff("#mu di lep; N_{Jets}", dEfficiencies);   
  MuDiLepHT_->SaveEff("#mu di lep; H_{T} [GeV]", dEfficiencies);   
  MuDiLepMHT_->SaveEff("#mu di lep; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuDiLepMTWBTag_->SaveEff("#mu di lep; B_{Tags}", dEfficiencies);   
  MuDiLepMTWNJets_->SaveEff("#mu di lep; N_{Jets}", dEfficiencies);   
  MuDiLepMTWHT_->SaveEff("#mu di lep; H_{T} [GeV]", dEfficiencies);   
  MuDiLepMTWMHT_->SaveEff("#mu di lep; #slash{H}_{T} [GeV]", dEfficiencies);   
  //muon
  //1D
  MuDiLepContributionBTag_->SaveEff("#mu di lep contri; B_{Tags}", dEfficiencies);   
  MuDiLepContributionNJets_->SaveEff("#mu di lep contri; N_{Jets}", dEfficiencies);   
  MuDiLepContributionHT_->SaveEff("#mu di lep contri; H_{T} [GeV]", dEfficiencies);   
  MuDiLepContributionMHT_->SaveEff("#mu di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuDiLepContributionMTWBTag_->SaveEff("#mu di lep contri; B_{Tags}", dEfficiencies);   
  MuDiLepContributionMTWNJets_->SaveEff("#mu di lep contri; N_{Jets}", dEfficiencies);   
  MuDiLepContributionMTWHT_->SaveEff("#mu di lep contri; H_{T} [GeV]", dEfficiencies);   
  MuDiLepContributionMTWMHT_->SaveEff("#mu di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);   

  //elec
  //1D
  ElecMTWBTag_->SaveEff("e m_{T}^{W}; B_{Tags}", dEfficiencies);   
  ElecMTWNJets_->SaveEff("e m_{T}^{W}; N_{Jets}", dEfficiencies);   
  ElecMTWHT_->SaveEff("e m_{T}^{W}; H_{T} [GeV]", dEfficiencies);   
  ElecMTWMHT_->SaveEff("e m_{T}^{W}; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecDiLepBTag_->SaveEff("e di lep; B_{Tags}", dEfficiencies);   
  ElecDiLepNJets_->SaveEff("e di lep; N_{Jets}", dEfficiencies);   
  ElecDiLepHT_->SaveEff("e di lep; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepMHT_->SaveEff("e di lep; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecDiLepMTWBTag_->SaveEff("e di lep; B_{Tags}", dEfficiencies);   
  ElecDiLepMTWNJets_->SaveEff("e di lep; N_{Jets}", dEfficiencies);   
  ElecDiLepMTWHT_->SaveEff("e di lep; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepMTWMHT_->SaveEff("e di lep; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecMTWPTActivity_->SaveEff("e m_{T}^{W}; Activity; p_{T}(e) [GeV]", dEfficiencies, true);
  ElecMTWHTNJets_->SaveEff("e m_{T}(w); H_{T} [GeV]; N_{Jets}", dEfficiencies);

  //elec
  //1D
  ElecDiLepContributionBTag_->SaveEff("e di lep contri; B_{Tags}", dEfficiencies);   
  ElecDiLepContributionNJets_->SaveEff("e di lep contri; N_{Jets}", dEfficiencies);   
  ElecDiLepContributionHT_->SaveEff("e di lep contri; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepContributionMHT_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecDiLepContributionMTWBTag_->SaveEff("e di lep contri; B_{Tags}", dEfficiencies);   
  ElecDiLepContributionMTWNJets_->SaveEff("e di lep contri; N_{Jets}", dEfficiencies);   
  ElecDiLepContributionMTWHT_->SaveEff("e di lep contri; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepContributionMTWMHT_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);   
  
  // pt and activity  
  //muon
  MuPurityPT_->SaveEff("#mu purity; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuPurityActivity_->SaveEff("#mu purity; Activity", dEfficiencies, true);   
  MuAccPT_->SaveEff("#mu acc; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuAccActivity_->SaveEff("#mu acc; Activity", dEfficiencies, true);   
  MuRecoPT_->SaveEff("#mu reco; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuRecoActivity_->SaveEff("#mu reco; Activity", dEfficiencies, true);   
  MuRecoActivityPT_->SaveEff("#mu reco; Activity; p_{T}(#mu) [GeV]", dEfficiencies, true);   
  MuIsoPT_->SaveEff("#mu iso; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuIsoActivity_->SaveEff("#mu iso; Activity", dEfficiencies, true);   
  MuMTWPT_->SaveEff("#mu m_{T}^{W}; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuMTWActivity_->SaveEff("#mu m_{T}^{W}; Activity", dEfficiencies, true);   
  MuIsoActivityPT_->SaveEff("#mu Iso; Activity; p_{T}(#mu) [GeV]", dEfficiencies, true);   
  MuRecoPTEta_->SaveEff("#mu reco; p_{T}(#mu) [GeV]; #eta(#mu)", dEfficiencies, true);   

  //elec
  ElecPurityPT_->SaveEff("e purity; p_{T}(e) [GeV]", dEfficiencies);   
  ElecPurityActivity_->SaveEff("e purity; Activity", dEfficiencies, true);   
  ElecAccPT_->SaveEff("e acc; p_{T}(e) [GeV]", dEfficiencies);   
  ElecAccActivity_->SaveEff("e acc; Activity", dEfficiencies, true);   
  ElecRecoPT_->SaveEff("e reco; p_{T}(e) [GeV]", dEfficiencies);   
  ElecRecoActivity_->SaveEff("e reco; Activity", dEfficiencies, true);   
  ElecRecoActivityPT_->SaveEff("e reco; Activity; p_{T}(e) [GeV]", dEfficiencies, true);   
  ElecIsoPT_->SaveEff("e iso; p_{T}(e) [GeV]", dEfficiencies);   
  ElecIsoActivity_->SaveEff("e iso; Activity", dEfficiencies, true);   
  ElecMTWPT_->SaveEff("e m_{T}^{W}; p_{T}(e) [GeV]", dEfficiencies);   
  ElecMTWActivity_->SaveEff("e m_{T}^{W}; Activity", dEfficiencies, true);   
  ElecIsoActivityPT_->SaveEff("e Iso; Activity; p_{T}(e) [GeV]", dEfficiencies, true);   
  ElecRecoPTEta_->SaveEff("e reco; p_{T}(e) [GeV]; #eta(e)", dEfficiencies, true);   


  //Isotracks
  //1D
  ExpectationReductionIsoTrackBTagEff_->SaveEff("iso track expec. reduction; B_{Tags}", dEfficiencies);   
  ExpectationReductionIsoTrackNJetsEff_->SaveEff("iso track expec. reduction; N_{Jets}", dEfficiencies);   
  ExpectationReductionIsoTrackHTEff_->SaveEff("iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionIsoTrackMHTEff_->SaveEff("iso track expec. reduction; #slash{H}_{T} [GeV]", dEfficiencies);   
  ExpectationReductionIsoTrackPTEff_->SaveEff("iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionIsoTrackActivityEff_->SaveEff("iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  IsoTrackReductionHTNJets_->SaveEff("iso track expec. reduction; H_{T} [GeV]; N_{Jets}", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsLow_->SaveEff("iso track expec. reduction N_{Jets}=4-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets4_->SaveEff("iso track expec. reduction N_{Jets}=4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets5_->SaveEff("iso track expec. reduction N_{Jets}=5; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets6_->SaveEff("iso track expec. reduction N_{Jets}=6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsHigh_->SaveEff("iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionMHTNJets_->SaveEff("iso track expec. reduction; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  IsoTrackReductionBTagNJets_->SaveEff("iso track expec. reduction; B_{Tags}; N_{Jets}", dEfficiencies);   
  IsoTrackReductionPTActivity_->SaveEff("iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true);   

  // mu iso tracks
  //1D
  ExpectationReductionMuIsoTrackBTagEff_->SaveEff("#mu iso track expec. reduction; B_{Tags}", dEfficiencies);   
  ExpectationReductionMuIsoTrackNJetsEff_->SaveEff("#mu iso track expec. reduction; N_{Jets}", dEfficiencies);   
  ExpectationReductionMuIsoTrackHTEff_->SaveEff("#mu iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionMuIsoTrackMHTEff_->SaveEff("#mu iso track expec. reduction; #slash{H}_{T} [GeV]", dEfficiencies);   
  ExpectationReductionMuIsoTrackPTEff_->SaveEff("#mu iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionMuIsoTrackActivityEff_->SaveEff("#mu iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  MuIsoTrackReductionHTNJets_->SaveEff("#mu iso track expec. reduction; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuIsoTrackReductionMHTNJets_->SaveEff("#mu iso track expec. reduction; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuIsoTrackReductionBTagNJets_->SaveEff("#mu iso track expec. reduction; B_{Tags}; N_{Jets}", dEfficiencies);   
  MuIsoTrackReductionPTActivity_->SaveEff("#mu iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true); 
  MuIsoTrackReductionHTMHT_NJetsLow_->SaveEff("#mu iso track expec. reduction N_{Jets}=4-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("#mu iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 

  // elec iso tracks
  //1D
  ExpectationReductionElecIsoTrackBTagEff_->SaveEff("e iso track expec. reduction; B_{Tags}", dEfficiencies);   
  ExpectationReductionElecIsoTrackNJetsEff_->SaveEff("e iso track expec. reduction; N_{Jets}", dEfficiencies);   
  ExpectationReductionElecIsoTrackHTEff_->SaveEff("e iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionElecIsoTrackMHTEff_->SaveEff("e iso track expec. reduction; #slash{H}_{T} [GeV]", dEfficiencies);   
  ExpectationReductionElecIsoTrackPTEff_->SaveEff("e iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionElecIsoTrackActivityEff_->SaveEff("e iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  ElecIsoTrackReductionHTNJets_->SaveEff("e iso track expec. reduction; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecIsoTrackReductionMHTNJets_->SaveEff("e iso track expec. reduction; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecIsoTrackReductionBTagNJets_->SaveEff("e iso track expec. reduction; B_{Tags}; N_{Jets}", dEfficiencies);   
  ElecIsoTrackReductionPTActivity_->SaveEff("e iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true); 
  ElecIsoTrackReductionHTMHT_NJetsLow_->SaveEff("e iso track expec. reduction N_{Jets}=4-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("e iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  
  // pion iso tracks
  //1D
  ExpectationReductionPionIsoTrackBTagEff_->SaveEff("#pi iso track expec. reduction; B_{Tags}", dEfficiencies);   
  ExpectationReductionPionIsoTrackNJetsEff_->SaveEff("#pi iso track expec. reduction; N_{Jets}", dEfficiencies);   
  ExpectationReductionPionIsoTrackHTEff_->SaveEff("#pi iso track expec. reduction; H_{T}", dEfficiencies);   
  ExpectationReductionPionIsoTrackMHTEff_->SaveEff("#pi iso track expec. reduction; #slash{H}_{T} [GeV]", dEfficiencies);   
  ExpectationReductionPionIsoTrackPTEff_->SaveEff("#pi iso track expec. reduction; p_{T} [GeV]", dEfficiencies);   
  ExpectationReductionPionIsoTrackActivityEff_->SaveEff("#pi iso track expec. reduction; Activity", dEfficiencies, true);   
  //2D
  PionIsoTrackReductionHTNJets_->SaveEff("#pi iso track expec. reduction; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  PionIsoTrackReductionMHTNJets_->SaveEff("#pi iso track expec. reduction; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  PionIsoTrackReductionBTagNJets_->SaveEff("#pi iso track expec. reduction; B_{Tags}; N_{Jets}", dEfficiencies);   
  PionIsoTrackReductionPTActivity_->SaveEff("#pi iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true);
  PionIsoTrackReductionHTMHT_NJetsLow_->SaveEff("#pi iso track expec. reduction N_{Jets}=4-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("#pi iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 

  outPutFile->Close();
}
