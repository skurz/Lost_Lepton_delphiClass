#define Prediction_cxx

#include "Prediction.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>


void Prediction::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

}

void Prediction::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TFile *effInput = new TFile("Efficiencies.root","READ");
  TDirectory *EffInputFolder =   (TDirectory*)effInput->Get("Efficiencies");

  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity", EffInputFolder);
  MuMTWNJets_ = new TH1Eff("MuMTWNJets1D", EffInputFolder);
  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets", EffInputFolder);
  MuMTWMHTNJets_ = new TH2Eff("MuMTWMHTNJets", EffInputFolder);
  MuMTWHTMHT_ = new TH2Eff("MuMTWHTMHT", EffInputFolder);
  MuMTWHTMHT_NJets24_ = new TH2Eff("MuMTWHTMHT_NJets24", EffInputFolder);
  MuMTWHTMHT_NJets56_ = new TH2Eff("MuMTWHTMHT_NJets56", EffInputFolder);
  MuMTWHTMHT_NJets7Inf_ = new TH2Eff("MuMTWHTMHT_NJets7Inf", EffInputFolder);
  MuMTWPT_ = new TH1Eff("MuMTWPT", EffInputFolder);
  MuMTWHTMHT_NJets2_ = new TH2Eff("MuMTWHTMHT_NJets2", EffInputFolder);
  MuMTWHTMHT_NJets3_ = new TH2Eff("MuMTWHTMHT_NJets3", EffInputFolder);
  MuMTWHTMHT_NJets4_ = new TH2Eff("MuMTWHTMHT_NJets4", EffInputFolder);
  MuMTWHTMHT_NJets5_ = new TH2Eff("MuMTWHTMHT_NJets5", EffInputFolder);
  MuMTWHTMHT_NJets6_ = new TH2Eff("MuMTWHTMHT_NJets6", EffInputFolder);
  MuMTWHTMHT_NJets78_ = new TH2Eff("MuMTWHTMHT_NJets78", EffInputFolder);
  MuMTWHTMHT_NJets9Inf_ = new TH2Eff("MuMTWHTMHT_NJets9Inf", EffInputFolder);

  MuDiLepContributionMTWAppliedNJets_ = new TH1Eff("MuDiLepContributionMTWNJets1D", EffInputFolder);
  MuDiLepContributionMTWAppliedMHTNJets_ = new TH2Eff("MuDiLepContributionMTWMHTNJets", EffInputFolder);
  MuDiLepContributionMTWAppliedNJetsBTags_ = new TH2Eff("MuDiLepContributionMTWNJetsBTags", EffInputFolder);
  MuDiLepEffMTWAppliedNJets_ = new TH1Eff("MuDiLepMTWNJets1D", EffInputFolder);
  MuDiLepEffMTWAppliedNJetsBTags_ = new TH2Eff("MuDiLepMTWNJetsBTags", EffInputFolder);

  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT", EffInputFolder);
  MuIsoRelPTDeltaRJet_ = new TH2Eff("MuIsoRelPTDeltaRJet", EffInputFolder);
  MuRecoActivityPT_= new TH2Eff("MuRecoActivityPT", EffInputFolder);
  MuRecoPTEta_= new TH2Eff("MuRecoPTEta", EffInputFolder);
  MuPurityMHTNJets_ = new TH2Eff("MuonPurityMHTNJet", EffInputFolder); 
  MuPurityHTMHT_ = new TH2Eff("MuonPurityHTMHT", EffInputFolder); 

  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets", EffInputFolder);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets", EffInputFolder);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT", EffInputFolder);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets", EffInputFolder);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0", EffInputFolder);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf", EffInputFolder);
  MuAccHTMHT_NJets26_ = new TH2Eff("MuAccHTMHT_NJets26", EffInputFolder);
  MuAccHTMHT_NJets2_ = new TH2Eff("MuAccHTMHT_NJets2", EffInputFolder);
  MuAccHTMHT_NJets3_ = new TH2Eff("MuAccHTMHT_NJets3", EffInputFolder);
  MuAccHTMHT_NJets4_ = new TH2Eff("MuAccHTMHT_NJets4", EffInputFolder);
  MuAccHTMHT_NJets5_ = new TH2Eff("MuAccHTMHT_NJets5", EffInputFolder);
  MuAccHTMHT_NJets6_ = new TH2Eff("MuAccHTMHT_NJets6", EffInputFolder);
  MuAccHTMHT_NJets78_ = new TH2Eff("MuAccHTMHT_NJets78", EffInputFolder);
  MuAccHTMHT_NJets9Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf", EffInputFolder);
  MuAccHTMHT_NJets7Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf", EffInputFolder);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0", EffInputFolder);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf", EffInputFolder); 

  MuAccHTMHT_NJets2_BTags0_ = new TH2Eff("MuAccHTMHT_NJets2_BTags0", EffInputFolder);
  MuAccHTMHT_NJets3_BTags0_ = new TH2Eff("MuAccHTMHT_NJets3_BTags0", EffInputFolder);
  MuAccHTMHT_NJets4_BTags0_ = new TH2Eff("MuAccHTMHT_NJets4_BTags0", EffInputFolder);
  MuAccHTMHT_NJets5_BTags0_ = new TH2Eff("MuAccHTMHT_NJets5_BTags0", EffInputFolder);
  MuAccHTMHT_NJets6_BTags0_ = new TH2Eff("MuAccHTMHT_NJets6_BTags0", EffInputFolder);
  MuAccHTMHT_NJets78_BTags0_ = new TH2Eff("MuAccHTMHT_NJets78_BTags0", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags0", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags0_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags0", EffInputFolder);
  MuAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags1Inf", EffInputFolder);
  MuAccHTMHT_NJets2_BTags1_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1", EffInputFolder);
  MuAccHTMHT_NJets3_BTags1_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1", EffInputFolder);
  MuAccHTMHT_NJets4_BTags1_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1", EffInputFolder);
  MuAccHTMHT_NJets5_BTags1_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1", EffInputFolder);
  MuAccHTMHT_NJets6_BTags1_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1", EffInputFolder);
  MuAccHTMHT_NJets78_BTags1_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags1_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags1", EffInputFolder);
  MuAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags2Inf", EffInputFolder);
  MuAccHTMHT_NJets3_BTags2_ = new TH2Eff("MuAccHTMHT_NJets3_BTags2", EffInputFolder);
  MuAccHTMHT_NJets4_BTags2_ = new TH2Eff("MuAccHTMHT_NJets4_BTags2", EffInputFolder);
  MuAccHTMHT_NJets5_BTags2_ = new TH2Eff("MuAccHTMHT_NJets5_BTags2", EffInputFolder);
  MuAccHTMHT_NJets6_BTags2_ = new TH2Eff("MuAccHTMHT_NJets6_BTags2", EffInputFolder);
  MuAccHTMHT_NJets78_BTags2_ = new TH2Eff("MuAccHTMHT_NJets78_BTags2", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags2_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags2", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags2_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags2", EffInputFolder);
  MuAccHTMHT_NJets3_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets4_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets5_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets6_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets78_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets9Inf_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags3Inf", EffInputFolder);
  MuAccHTMHT_NJets7Inf_BTags3Inf_ = new TH2Eff("MuAccHTMHT_NJets7Inf_BTags3Inf", EffInputFolder);

  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT", EffInputFolder);
  ElecIsoRelPTDeltaRJet_ = new TH2Eff("ElecIsoRelPTDeltaRJet", EffInputFolder);
  ElecRecoActivityPT_= new TH2Eff("ElecRecoActivityPT", EffInputFolder);
  ElecRecoPTEta_= new TH2Eff("ElecRecoPTEta", EffInputFolder);
  
  ElecMTWPTActivity_ = new TH2Eff("ElecMTWPTActivity", EffInputFolder);
  ElecPurityMHTNJets_ = new TH2Eff("ElecPurityMHTNJet", EffInputFolder);
  ElecPurityHTMHT_ = new TH2Eff("MuonPurityHTMHT", EffInputFolder); 
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D", EffInputFolder);
  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets", EffInputFolder);
  ElecMTWMHTNJets_ = new TH2Eff("ElecMTWMHTNJets", EffInputFolder);
  ElecMTWHTMHT_ = new TH2Eff("ElecMTWHTMHT", EffInputFolder);
  ElecMTWHTMHT_NJets24_ = new TH2Eff("ElecMTWHTMHT_NJets24", EffInputFolder);
  ElecMTWHTMHT_NJets56_ = new TH2Eff("ElecMTWHTMHT_NJets56", EffInputFolder);
  ElecMTWHTMHT_NJets7Inf_ = new TH2Eff("ElecMTWHTMHT_NJets7Inf", EffInputFolder);
  ElecMTWPT_ = new TH1Eff("ElecMTWPT", EffInputFolder);
  ElecMTWHTMHT_NJets2_ = new TH2Eff("ElecMTWHTMHT_NJets2", EffInputFolder);
  ElecMTWHTMHT_NJets3_ = new TH2Eff("ElecMTWHTMHT_NJets3", EffInputFolder);
  ElecMTWHTMHT_NJets4_ = new TH2Eff("ElecMTWHTMHT_NJets4", EffInputFolder);
  ElecMTWHTMHT_NJets5_ = new TH2Eff("ElecMTWHTMHT_NJets5", EffInputFolder);
  ElecMTWHTMHT_NJets6_ = new TH2Eff("ElecMTWHTMHT_NJets6", EffInputFolder);
  ElecMTWHTMHT_NJets78_ = new TH2Eff("ElecMTWHTMHT_NJets78", EffInputFolder);
  ElecMTWHTMHT_NJets9Inf_ = new TH2Eff("ElecMTWHTMHT_NJets9Inf", EffInputFolder);


  ElecDiLepContributionMTWAppliedNJets_ = new TH1Eff("ElecDiLepContributionMTWNJets1D", EffInputFolder);
  ElecDiLepContributionMTWAppliedMHTNJets_ = new TH2Eff("ElecDiLepContributionMTWMHTNJets", EffInputFolder);
  ElecDiLepContributionMTWAppliedNJetsBTags_ = new TH2Eff("ElecDiLepContributionMTWNJetsBTags", EffInputFolder);
  ElecDiLepEffMTWAppliedNJets_ = new TH1Eff("ElecDiLepMTWNJets1D", EffInputFolder);
  ElecDiLepEffMTWAppliedNJetsBTags_ = new TH2Eff("ElecDiLepMTWNJetsBTags", EffInputFolder);

  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets", EffInputFolder);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets", EffInputFolder);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT", EffInputFolder);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets", EffInputFolder);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0", EffInputFolder);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf", EffInputFolder);
  ElecAccHTMHT_NJets26_ = new TH2Eff("ElecAccHTMHT_NJets26", EffInputFolder);
  ElecAccHTMHT_NJets2_ = new TH2Eff("ElecAccHTMHT_NJets2", EffInputFolder);
  ElecAccHTMHT_NJets3_ = new TH2Eff("ElecAccHTMHT_NJets3", EffInputFolder);
  ElecAccHTMHT_NJets4_ = new TH2Eff("ElecAccHTMHT_NJets4", EffInputFolder);
  ElecAccHTMHT_NJets5_ = new TH2Eff("ElecAccHTMHT_NJets5", EffInputFolder);
  ElecAccHTMHT_NJets6_ = new TH2Eff("ElecAccHTMHT_NJets6", EffInputFolder);
  ElecAccHTMHT_NJets78_ = new TH2Eff("ElecAccHTMHT_NJets78", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf", EffInputFolder);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0", EffInputFolder);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf", EffInputFolder);

  ElecAccHTMHT_NJets2_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags0", EffInputFolder);
  ElecAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags1Inf", EffInputFolder);
  ElecAccHTMHT_NJets2_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags1", EffInputFolder);
  ElecAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags2Inf", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags2_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags2", EffInputFolder);
  ElecAccHTMHT_NJets3_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets4_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets5_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets6_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets78_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets9Inf_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags3Inf", EffInputFolder);
  ElecAccHTMHT_NJets7Inf_BTags3Inf_ = new TH2Eff("ElecAccHTMHT_NJets7Inf_BTags3Inf", EffInputFolder);

  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff", EffInputFolder);
  ExpectationReductionIsoTrackBTagsNJetsEff_= new TH2Eff("IsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionIsoTrackHTNJetsEff_ = new TH2Eff("IsoTrackReductionHTNJets", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets24Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets24", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets56Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets56", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets7InfEff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets7Inf", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets2Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets2", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets3Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets3", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets4Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets4", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets5Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets5", EffInputFolder);
  ExpectationReductionIsoTrackHTMHT_NJets6Eff_ = new TH2Eff("IsoTrackReductionHTMHT_NJets6", EffInputFolder);

  ExpectationReductionIsoTrackMHTNJetsEff_ = new TH2Eff("IsoTrackReductionMHTNJets", EffInputFolder);
  ExpectationReductionMuIsoTrackBTagsNJetsEff_= new TH2Eff("MuIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionElecIsoTrackBTagsNJetsEff_= new TH2Eff("ElecIsoTrackReductionBTagNJets", EffInputFolder);
  ExpectationReductionPionIsoTrackBTagsNJetsEff_= new TH2Eff("PionIsoTrackReductionBTagNJets", EffInputFolder);

  ExpectationReductionMuIsoTrackHTMHT_NJets24Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets24", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets24Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets24", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets24Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets24", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets56Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets56", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets56Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets56", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets56Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets56", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets7InfEff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets7Inf", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets7InfEff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets7Inf", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets7InfEff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets7Inf", EffInputFolder);

  ExpectationReductionMuIsoTrackHTMHT_NJets2Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets2", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets3Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets3", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets4Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets4", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets5Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets5", EffInputFolder);
  ExpectationReductionMuIsoTrackHTMHT_NJets6Eff_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJets6", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets2Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets2", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets3Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets3", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets4Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets4", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets5Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets5", EffInputFolder);
  ExpectationReductionElecIsoTrackHTMHT_NJets6Eff_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJets6", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets2Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets2", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets3Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets3", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets4Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets4", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets5Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets5", EffInputFolder);
  ExpectationReductionPionIsoTrackHTMHT_NJets6Eff_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJets6", EffInputFolder);

  //NEW
  MuAccSearchBins_ = new TH1Eff("MuAccSearchBins", EffInputFolder);
  ElecAccSearchBins_ = new TH1Eff("ElecAccSearchBins", EffInputFolder);
  MuMTWSearchBins_ = new TH1Eff("MuMTWSearchBins", EffInputFolder);
  ElecMTWSearchBins_ = new TH1Eff("ElecMTWSearchBins", EffInputFolder);
  IsoTrackVetoSearchBins_ = new TH1Eff("IsoTrackVetoSearchBins", EffInputFolder);
  MuIsoTrackVetoSearchBins_ = new TH1Eff("MuIsoTrackVetoSearchBins", EffInputFolder);
  ElecIsoTrackVetoSearchBins_ = new TH1Eff("ElecIsoTrackVetoSearchBins", EffInputFolder);
  PionIsoTrackVetoSearchBins_ = new TH1Eff("PionIsoTrackVetoSearchBins", EffInputFolder);
  MuDiLepContributionSearchBins_ = new TH1Eff("MuDiLepContributionSearchBins", EffInputFolder);
  ElecDiLepContributionSearchBins_ = new TH1Eff("ElecDiLepContributionSearchBins", EffInputFolder);


  // TProfiles
  MuMeanWeight_ = new TProfile("MuMeanWeight","MuMeanWeight",108,1.,109.);
  MuMeanWeight_->Sumw2();
  ElecMeanWeight_ = new TProfile("ElecMeanWeight","ElecMeanWeight",108,1.,109.);
  ElecMeanWeight_->Sumw2();
  CombinedMeanWeight_ = new TProfile("CombinedMeanWeight","CombinedMeanWeight",108,1.,109.);
  CombinedMeanWeight_->Sumw2();

  for(int b = 0; b <108; b++){
    MuWeightPerBin_[b] = new TH1D(TString("MuWeightPerBin_")+TString(to_string(b+1)),TString("MuWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    MuWeightPerBin_[b]->Sumw2();
    ElecWeightPerBin_[b] = new TH1D(TString("ElecWeightPerBin_")+TString(to_string(b+1)),TString("ElecWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    ElecWeightPerBin_[b]->Sumw2();
    CombinedWeightPerBin_[b] = new TH1D(TString("CombinedWeightPerBin_")+TString(to_string(b+1)),TString("CombinedWeightPerBin_")+TString(to_string(b+1)),60,0.,3.0);
    CombinedWeightPerBin_[b]->Sumw2();
  }  
    
  
  tPrediction_ = new TTree("LostLeptonPrediction","a simple Tree with simple variables");
  tPrediction_->Branch("HT",&HT);
  tPrediction_->Branch("MHT",&MHT);
  tPrediction_->Branch("NJets",&NJets);
  tPrediction_->Branch("BTags",&BTags);
  tPrediction_->Branch("NVtx",&NVtx);
  tPrediction_->Branch("Bin",&Bin_);
  tPrediction_->Branch("BinQCD",&BinQCD_);
  tPrediction_->Branch("PTWBins", &ptw_bins);
  tPrediction_->Branch("isoTracksNum",&isoTracksNum);
  tPrediction_->Branch("DeltaPhi1",&DeltaPhi1);
  tPrediction_->Branch("DeltaPhi2",&DeltaPhi2);
  tPrediction_->Branch("DeltaPhi3",&DeltaPhi3);
  tPrediction_->Branch("DeltaPhi4",&DeltaPhi4);
  tPrediction_->Branch("Weight", &Weight);
  tPrediction_->Branch("MET",&MET);
  tPrediction_->Branch("METPhi",&METPhi);
  tPrediction_->Branch("MuonsNum",&MuonsNum_);
  tPrediction_->Branch("MuonsPt",&MuonsPt_);
  tPrediction_->Branch("MuonsEta",&MuonsEta_);
  tPrediction_->Branch("Muons", "std::vector<TLorentzVector>", &Muons, 32000, 0);
  tPrediction_->Branch("Muons_MT2Activity", &Muons_MT2Activity);
  tPrediction_->Branch("MuonsPTW", &MuonsPTW);
  //  tPrediction_->Branch("MuonsCDTT", &MuonsCDTT);
//  tPrediction_->Branch("MuonsRelPTJet", &MuonsRelPTJet);
//  tPrediction_->Branch("MuonsDeltaRJet", &MuonsDeltaRJet);
  tPrediction_->Branch("ElectronsNum",&ElectronsNum_);
  tPrediction_->Branch("Electrons", "std::vector<TLorentzVector>", &Electrons, 32000, 0);
  tPrediction_->Branch("Electrons_MT2Activity", &Electrons_MT2Activity);
  tPrediction_->Branch("ElectronsPTW", &ElectronsPTW);
  tPrediction_->Branch("ElectronsPt",&ElectronsPt_);
  tPrediction_->Branch("ElectronsEta",&ElectronsEta_);
  tPrediction_->Branch("Muons_tightID", &Muons_tightID);
  tPrediction_->Branch("Electrons_mediumID", &Electrons_mediumID);
  tPrediction_->Branch("Electrons_tightID", &Electrons_tightID);
  //  tPrediction_->Branch("ElectronsCDTT", &ElectronsCDTT);
//  tPrediction_->Branch("ElectronsRelPTJet", &ElectronsRelPTJet);
//  tPrediction_->Branch("ElectronsDeltaRJet", &ElectronsDeltaRJet);
  tPrediction_->Branch("MTW",&mtw);
  tPrediction_->Branch("muMTWEff",&muMTWEff_);
  tPrediction_->Branch("mtwCorrectedWeight",&mtwCorrectedWeight_);
  tPrediction_->Branch("muDiLepContributionMTWAppliedEff",&muDiLepContributionMTWAppliedEff_);
  tPrediction_->Branch("mtwDiLepCorrectedWeight",&mtwDiLepCorrectedWeight_);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoMuTrackReduced",&totalWeightDiLepIsoMuTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoElecTrackReduced",&totalWeightDiLepIsoElecTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoPionTrackReduced",&totalWeightDiLepIsoPionTrackReduced_);
  tPrediction_->Branch("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined_);
  tPrediction_->Branch("totalWeight_BTags",&totalWeight_BTags_);
  tPrediction_->Branch("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack_);
  tPrediction_->Branch("muIsoWeight",&muIsoWeight_);
  tPrediction_->Branch("muIsoEff",&muIsoEff_);
  tPrediction_->Branch("muRecoWeight",&muRecoWeight_);
  tPrediction_->Branch("muRecoEff",&muRecoEff_);
  tPrediction_->Branch("muAccWeight",&muAccWeight_);
  tPrediction_->Branch("muAccEff",&muAccEff_);
  tPrediction_->Branch("muTotalWeight",&muTotalWeight_);
  tPrediction_->Branch("muTotalWeightDiLep",&muTotalWeightDiLep_);
  tPrediction_->Branch("muTotalWeightDiLepIsoTrackReduced",&muTotalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalMuons",&totalMuons_);
  tPrediction_->Branch("elecAccWeight",&elecAccWeight_);
  tPrediction_->Branch("elecAccEff",&elecAccEff_);
  tPrediction_->Branch("elecRecoWeight",&elecRecoWeight_);
  tPrediction_->Branch("elecRecoEff",&elecRecoEff_);
  tPrediction_->Branch("elecIsoWeight",&elecIsoWeight_);
  tPrediction_->Branch("elecIsoEff",&elecIsoEff_);
  tPrediction_->Branch("elecTotalWeight",&elecTotalWeight_);
  tPrediction_->Branch("elecTotalWeightDiLep",&elecTotalWeightDiLep_);
  tPrediction_->Branch("elecTotalWeightDiLepIsoTrackReduced",&elecTotalWeightDiLepIsoTrackReduced_);
  tPrediction_->Branch("totalElectrons",&totalElectrons_);
  tPrediction_->Branch("diLepLostWeight", &diLepLostWeight_);
  tPrediction_->Branch("expectationReductionIsoTrackEff",&expectationReductionIsoTrackEff_);
  tPrediction_->Branch("expectationReductionMuIsoTrackEff",&expectationReductionMuIsoTrackEff_);
  tPrediction_->Branch("expectationReductionElecIsoTrackEff",&expectationReductionElecIsoTrackEff_);
  tPrediction_->Branch("expectationReductionPionIsoTrackEff",&expectationReductionPionIsoTrackEff_);
  tPrediction_->Branch("expectationReductionIsoTrackEffCombined",&expectationReductionIsoTrackEffCombined_);
  tPrediction_->Branch("totalWeight",&totalWeight_);
  tPrediction_->Branch("muDiLepEffMTWAppliedEff",&muDiLepEffMTWAppliedEff_);
  tPrediction_->Branch("elecDiLepEffMTWAppliedEff",&elecDiLepEffMTWAppliedEff_);
  tPrediction_->Branch("totalWeightDiLep",&totalWeightDiLep_);
  //tPrediction_->Branch("Jets_HTMask", &Jets_HTMask);
  if(!runOnData){
    //tPrediction_->Branch("Jets_hadronFlavor", &Jets_hadronFlavor);
    tPrediction_->Branch("bTagProb", &bTagProb);
    tPrediction_->Branch("madHT", &madHT);
    tPrediction_->Branch("w_pu", &w_pu);
    //tPrediction_->Branch("Weight_bTagCorr", &Weight_bTagCorr);
    tPrediction_->Branch("recoSF", &recoSF);
    tPrediction_->Branch("isoSF", &isoSF);
    tPrediction_->Branch("trackingSF", &trackingSF);
    tPrediction_->Branch("WeightCorr", &WeightCorr);
    tPrediction_->Branch("WeightTrackingCorr", &WeightTrackingCorr);
    if(topPTreweight){
      tPrediction_->Branch("GenMuons", "std::vector<TLorentzVector>", &GenMuons, 32000, 0);
      tPrediction_->Branch("GenElectrons", "std::vector<TLorentzVector>", &GenElectrons, 32000, 0);
      tPrediction_->Branch("topPtSF", &topPtSF);
      tPrediction_->Branch("topPt", &topPt);
    }
  }
  if(runOnSignalMC){
    tPrediction_->Branch("SusyLSPMass", &SusyLSPMass);
    tPrediction_->Branch("SusyMotherMass", &SusyMotherMass);
    tPrediction_->Branch("w_isr", &w_isr);
    tPrediction_->Branch("w_pu", &w_pu);
    tPrediction_->Branch("xsec", &xsec);
    tPrediction_->Branch("nEvtsTotal", &nEvtsTotal);
  }

  if(!fillEventSeperateBTags){
    tPrediction_->Branch("isoTrackStatUp", &isoTrackStatUp);
    tPrediction_->Branch("isoTrackStatDown", &isoTrackStatDown);
    tPrediction_->Branch("muIsoTrackStatUp", &muIsoTrackStatUp);
    tPrediction_->Branch("muIsoTrackStatDown", &muIsoTrackStatDown);
    tPrediction_->Branch("elecIsoTrackStatUp", &elecIsoTrackStatUp);
    tPrediction_->Branch("elecIsoTrackStatDown", &elecIsoTrackStatDown);
    tPrediction_->Branch("pionIsoTrackStatUp", &pionIsoTrackStatUp);
    tPrediction_->Branch("pionIsoTrackStatDown", &pionIsoTrackStatDown);
    tPrediction_->Branch("MTWStatUp", &MTWStatUp);
    tPrediction_->Branch("MTWStatDown", &MTWStatDown);
    tPrediction_->Branch("purityStatUp", &purityStatUp);
    tPrediction_->Branch("purityStatDown", &purityStatDown);
    tPrediction_->Branch("singleLepPurityStatUp", &singleLepPurityStatUp);
    tPrediction_->Branch("singleLepPurityStatDown", &singleLepPurityStatDown);
    tPrediction_->Branch("diLepFoundStatUp", &diLepFoundStatUp);
    tPrediction_->Branch("diLepFoundStatDown", &diLepFoundStatDown);
    tPrediction_->Branch("muIsoStatUp", &muIsoStatUp);
    tPrediction_->Branch("muIsoStatDown", &muIsoStatDown);
    tPrediction_->Branch("muRecoStatUp", &muRecoStatUp);
    tPrediction_->Branch("muRecoStatDown", &muRecoStatDown);
    tPrediction_->Branch("muAccStatUp", &muAccStatUp);
    tPrediction_->Branch("muAccStatDown", &muAccStatDown);
    tPrediction_->Branch("elecIsoStatUp", &elecIsoStatUp);
    tPrediction_->Branch("elecIsoStatDown", &elecIsoStatDown);
    tPrediction_->Branch("elecRecoStatUp", &elecRecoStatUp);
    tPrediction_->Branch("elecRecoStatDown", &elecRecoStatDown);
    tPrediction_->Branch("elecAccStatUp", &elecAccStatUp);
    tPrediction_->Branch("elecAccStatDown", &elecAccStatDown);
    
    tPrediction_->Branch("isoTrackSysUp", &isoTrackSysUp);
    tPrediction_->Branch("isoTrackSysDown", &isoTrackSysDown);
    tPrediction_->Branch("muIsoTrackSysUp", &muIsoTrackSysUp);
    tPrediction_->Branch("muIsoTrackSysDown", &muIsoTrackSysDown);
    tPrediction_->Branch("elecIsoTrackSysUp", &elecIsoTrackSysUp);
    tPrediction_->Branch("elecIsoTrackSysDown", &elecIsoTrackSysDown);
    tPrediction_->Branch("pionIsoTrackSysUp", &pionIsoTrackSysUp);
    tPrediction_->Branch("pionIsoTrackSysDown", &pionIsoTrackSysDown);
    tPrediction_->Branch("MTWSysUp", &MTWSysUp);
    tPrediction_->Branch("MTWSysDown", &MTWSysDown);
    tPrediction_->Branch("puritySysUp", &puritySysUp);
    tPrediction_->Branch("puritySysDown", &puritySysDown);
    tPrediction_->Branch("singleLepPuritySysUp", &singleLepPuritySysUp);
    tPrediction_->Branch("singleLepPuritySysDown", &singleLepPuritySysDown);
    tPrediction_->Branch("diLepFoundSysUp", &diLepFoundSysUp);
    tPrediction_->Branch("diLepFoundSysDown", &diLepFoundSysDown);
    tPrediction_->Branch("muIsoSysUp", &muIsoSysUp);
    tPrediction_->Branch("muIsoSysDown", &muIsoSysDown);
    tPrediction_->Branch("muRecoSysUp", &muRecoSysUp);
    tPrediction_->Branch("muRecoSysDown", &muRecoSysDown);
    tPrediction_->Branch("muAccSysUp", &muAccSysUp);
    tPrediction_->Branch("muAccSysDown", &muAccSysDown);
    tPrediction_->Branch("muAccQsquareSysUp", &muAccQsquareSysUp);
    tPrediction_->Branch("muAccQsquareSysDown", &muAccQsquareSysDown);
    tPrediction_->Branch("elecIsoSysUp", &elecIsoSysUp);
    tPrediction_->Branch("elecIsoSysDown", &elecIsoSysDown);
    tPrediction_->Branch("elecRecoSysUp", &elecRecoSysUp);
    tPrediction_->Branch("elecRecoSysDown", &elecRecoSysDown);
    tPrediction_->Branch("elecAccSysUp", &elecAccSysUp);
    tPrediction_->Branch("elecAccSysDown", &elecAccSysDown);
    tPrediction_->Branch("elecAccQsquareSysUp", &elecAccQsquareSysUp);
    tPrediction_->Branch("elecAccQsquareSysDown", &elecAccQsquareSysDown);

    tPrediction_->Branch("totalStatUp", &totalStatUp);
    tPrediction_->Branch("totalSysUp", &totalSysUp);
    tPrediction_->Branch("totalUncUp", &totalUncUp);

    tPrediction_->Branch("totalStatDown", &totalStatDown);
    tPrediction_->Branch("totalSysDown", &totalSysDown);
    tPrediction_->Branch("totalUncDown", &totalUncDown);
  }

  GetOutputList()->Add(tPrediction_);
  SearchBins_ = new SearchBins(false); // 72 searchbins
  SearchBinsQCD_ = new SearchBins(true); // 220 QCD binning
  SearchBinsEff_ = new SearchBins(true); // 220 QCD binning

  std::cout<<"Run on Data: "<<runOnData<<std::endl;
  std::cout<<"Run on SM MC: "<<runOnStandardModelMC<<std::endl;
  std::cout<<"Run on Signal MC: "<<runOnSignalMC<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
}

Bool_t Prediction::Process(Long64_t entry)
{
  resetValues();
  fChain->GetTree()->GetEntry(entry);

//  if(entry % 3 != 0) return kTRUE;

  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;

// Not needed anymore. Special Skims used.
//  if(useGenHTMHT){
//    HT = GenHT;
//    MHT = GenMHT;
//  }
  
  if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  if(applyFilters_ &&  !FiltersPass() ) return kTRUE;

  isoTracksNum= isoElectronTracksNum + isoMuonTracksNum + isoPionTracksNum;

  //MuonsNoIsoNum_ = MuonsNoIso->size();
  MuonsNum_ = Muons->size();
  //ElectronsNoIsoNum_ = ElectronsNoIso->size();
  ElectronsNum_ = Electrons->size();

  if((MuonsNum_+ElectronsNum_) !=1) return kTRUE;


  // HTMHT Triggers
  //if(useTrigger) if(!TriggerPass->at(29) && !TriggerPass->at(30)) return kTRUE;

  // Signal triggers
  if(useTrigger) if(!TriggerPass->at(42) && !TriggerPass->at(43) &&!TriggerPass->at(44) && !TriggerPass->at(46) && !TriggerPass->at(47) && !TriggerPass->at(48)) return kTRUE;

  // Single lepton triggers (IsoVVVL)
  //if(useTrigger) if(!TriggerPass->at(5) && !TriggerPass->at(20)) return kTRUE;

  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
  BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTags);


  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;

  if(topPTreweight){
    if(GenParticles->size() != GenParticles_PdgId->size()){
      std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
    }else{
      for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
        if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
          topPt.push_back(GenParticles->at(iGen).Pt());
        }
      }
      
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#Example
      if(topPt.size() == 2){
        // dilept
        if(GenElectrons->size() + GenMuons->size() == 2){
          topPtSF = std::sqrt(std::exp(0.148-0.00129*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.148-0.00129*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
        // singlelept
        }else if(GenElectrons->size() + GenMuons->size() == 1){
          topPtSF = std::sqrt(std::exp(0.159-0.00141*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.159-0.00141*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
        //had
        }else{
          // Usually non-promt (in hadTau evts): use average SF
          topPtSF = std::sqrt(std::exp(0.156-0.00137*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.156-0.00137*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
          //std::cout << "Cannot do top-pT reweighting! No leptonic top found."<< std::endl; 
        }
      }else{
        topPtSF = -1;
        std::cout << "Cannot do top-pT reweighting! More/Less than 2 tops found."<< std::endl; 
      }

    }

    // Normalization tested on SingleLept and DiLept samples (varies from ~98.9x-99.0x)
        topPtSF /= 0.99;
  }

  if(!runOnData){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());

    if(currentTree != treeName){
      treeName = currentTree;

      if(doISRcorr){
        h_njetsisr = (TH1*) fChain->GetCurrentFile()->Get("NJetsISR");
        if(isrcorr!=0){
          delete isrcorr;
          isrcorr = 0;
        }
        isrcorr = new ISRCorrector();
        isrcorr->SetWeights(h_isr,h_njetsisr);
      }

      if(doBTagCorr){
        if(btagcorr!=0){
          delete btagcorr;
          btagcorr = 0;
        }
        btagcorr = new BTagCorrector();

        if(!runOnNtuples) btagcorr->SetEffs(fChain->GetCurrentFile());
        else{
          TObjArray *optionArray = currentTree.Tokenize("/");
          TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
          TFile *skimFile = TFile::Open(path_toSkims+currFileName, "READ");
          btagcorr->SetEffs(skimFile);
        }

        btagcorr->SetCalib(path_bTagCalib);        
        if(runOnSignalMC){
          btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
          btagcorr->SetFastSim(true);
        }
        else btagcorr->SetFastSim(false);
      }

      if(runOnSignalMC){
        if((std::string(currentTree.Data()).find(std::string("T1"))) != std::string::npos || (std::string(currentTree.Data()).find(std::string("T5"))) != std::string::npos){
          xsecs = &xsecsT1T5;
          //std::cout<<"Using xsecs for gluino pair production!"<<std::endl;
        }else if((std::string(currentTree.Data()).find(std::string("T2"))) != std::string::npos){
          xsecs = &xsecsT2;
          //std::cout<<"Using xsecs for stop pair production!"<<std::endl;
        }else{
          std::cout<<"No valid dictionary with xsecs found!"<<std::endl;
          return kTRUE;
        }
      }
    }

    if(runOnSignalMC){
      TH1F *nEventProc = (TH1F*)fChain->GetCurrentFile()->Get("nEventProc");
      TH1F *nEventNeg = (TH1F*)fChain->GetCurrentFile()->Get("nEventNeg");
      nEvtsTotal = nEventProc->GetBinContent(1) - 2*nEventNeg->GetBinContent(1);

      xsec = 0;
      for (std::vector<std::pair<double, double>>::iterator it = xsecs->begin() ; it != xsecs->end(); ++it){
        if(std::abs(SusyMotherMass - it->first) < 0.1){
          xsec = it->second;
          break;
        }
      }
      if(xsec < 1e-10){
        std::cout<<"No valid xsec found!"<<std::endl;
        return kTRUE;
      }

      Weight = xsec / nEvtsTotal;
      if(Weight < 0) Weight *= -1;
    }   

    if(doISRcorr){
      w_isr = isrcorr->GetCorrection(NJetsISR);
      Weight *= w_isr;
    }

    if(doBTagCorr) bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
    else bTagProb = {0, 0, 0, 0};
    // Simple bTag corrections don't work that way
    //if(!runOnData) bTagCorr_cut = btagcorr->GetSimpleCorrection(Jets,Jets_hadronFlavor,Jets_HTMask,Jets_bDiscriminatorCSV);
  }

  if(runOnData) Weight = 1.;

  if(runOnSignalMC){
    //Account for efficiency of JetID since we cannot apply it on fastSim
    Weight *= 0.99;
  }

  if(useTriggerEffWeight){
    if(runOnSignalMC){
      Weight *= GetSignalTriggerEffWeight(MHT);
    }else{
      Weight *= GetTriggerEffWeight(MHT);
    }
  }

  if(doPUreweighting){
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
  }

  //if(!runOnData){
  //  if(bTagCorr_cut < 0 || bTagCorr_cut > 10 || std::isnan(bTagCorr_cut)) Weight_bTagCorr = 1.; 
  //  else Weight_bTagCorr = Weight * bTagCorr_cut;
  //}
    // fill PTW values for extrapolation
  for (UShort_t ii=0; ii < MuonsNum_; ii++){
    MuonsPTW.push_back(PTWCalculator(MHT,MHTPhi, Muons->at(ii).Pt(), Muons->at(ii).Phi()));
    //    MuonsCDTT.push_back(GetCosDTT(MHT,MHTPhi, Muons->at(ii).Pt(), Muons->at(ii).Phi()));
  }
  for (UShort_t ii=0; ii < ElectronsNum_; ii++){
    ElectronsPTW.push_back(PTWCalculator(MHT,MHTPhi, Electrons->at(ii).Pt(), Electrons->at(ii).Phi()));
    //    ElectronsCDTT.push_back(GetCosDTT(MHT,MHTPhi, Electrons->at(ii).Pt(), Electrons->at(ii).Phi()));
  }


  double PTW(0.);
  if (MuonsNum_==1) PTW=MuonsPTW[0];
  else if (ElectronsNum_==1) PTW=ElectronsPTW[0];
  ptw_bins = GetPTWBin(Bin_, PTW, HT);

  // get IsoTrack Effs
  //if(NJets < 4.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets24Eff_->GetEff(HT, MHT, useAsymmErrors);
  //else if(NJets < 6.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets56Eff_->GetEff(HT, MHT, useAsymmErrors);
/*  if(NJets < 2.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets2Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 3.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets3Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 4.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets4Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 5.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets5Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 6.5) expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets6Eff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionIsoTrackEffVec_= ExpectationReductionIsoTrackHTMHT_NJets7InfEff_->GetEff(HT, MHT, useAsymmErrors);

  //if(NJets < 4.5) expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackHTMHT_NJets24Eff_->GetEff(HT, MHT, useAsymmErrors);
  //else if(NJets < 6.5) expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackHTMHT_NJets56Eff_->GetEff(HT, MHT, useAsymmErrors);
  if(NJets < 2.5) expectationReductionMuIsoTrackEffVec_= ExpectationReductionMuIsoTrackHTMHT_NJets2Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 3.5) expectationReductionMuIsoTrackEffVec_= ExpectationReductionMuIsoTrackHTMHT_NJets3Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 4.5) expectationReductionMuIsoTrackEffVec_= ExpectationReductionMuIsoTrackHTMHT_NJets4Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 5.5) expectationReductionMuIsoTrackEffVec_= ExpectationReductionMuIsoTrackHTMHT_NJets5Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 6.5) expectationReductionMuIsoTrackEffVec_= ExpectationReductionMuIsoTrackHTMHT_NJets6Eff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionMuIsoTrackEffVec_ = ExpectationReductionMuIsoTrackHTMHT_NJets7InfEff_->GetEff(HT, MHT, useAsymmErrors);

  //if(NJets < 4.5) expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackHTMHT_NJets24Eff_->GetEff(HT, MHT, useAsymmErrors);
  //else if(NJets < 6.5) expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackHTMHT_NJets56Eff_->GetEff(HT, MHT, useAsymmErrors);
  if(NJets < 2.5) expectationReductionElecIsoTrackEffVec_= ExpectationReductionElecIsoTrackHTMHT_NJets2Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 3.5) expectationReductionElecIsoTrackEffVec_= ExpectationReductionElecIsoTrackHTMHT_NJets3Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 4.5) expectationReductionElecIsoTrackEffVec_= ExpectationReductionElecIsoTrackHTMHT_NJets4Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 5.5) expectationReductionElecIsoTrackEffVec_= ExpectationReductionElecIsoTrackHTMHT_NJets5Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 6.5) expectationReductionElecIsoTrackEffVec_= ExpectationReductionElecIsoTrackHTMHT_NJets6Eff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionElecIsoTrackEffVec_ = ExpectationReductionElecIsoTrackHTMHT_NJets7InfEff_->GetEff(HT, MHT, useAsymmErrors);
  
  //if(NJets < 4.5) expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackHTMHT_NJets24Eff_->GetEff(HT, MHT, useAsymmErrors);
  //else if(NJets < 6.5) expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackHTMHT_NJets56Eff_->GetEff(HT, MHT, useAsymmErrors);
  if(NJets < 2.5) expectationReductionPionIsoTrackEffVec_= ExpectationReductionPionIsoTrackHTMHT_NJets2Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 3.5) expectationReductionPionIsoTrackEffVec_= ExpectationReductionPionIsoTrackHTMHT_NJets3Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 4.5) expectationReductionPionIsoTrackEffVec_= ExpectationReductionPionIsoTrackHTMHT_NJets4Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 5.5) expectationReductionPionIsoTrackEffVec_= ExpectationReductionPionIsoTrackHTMHT_NJets5Eff_->GetEff(HT, MHT, useAsymmErrors);
  else if(NJets < 6.5) expectationReductionPionIsoTrackEffVec_= ExpectationReductionPionIsoTrackHTMHT_NJets6Eff_->GetEff(HT, MHT, useAsymmErrors);
  else expectationReductionPionIsoTrackEffVec_ = ExpectationReductionPionIsoTrackHTMHT_NJets7InfEff_->GetEff(HT, MHT, useAsymmErrors);
*/
  expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);
  expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(BinQCD_, useAsymmErrors);

  //for compatibility
  expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
  expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
  expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
  expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;


  if(MuonsNum_==1 && ElectronsNum_==0)
    {
      // cout << "Single muon event...";
      mtw =  Muons_MTW->at(0);
      //mtw =  MTWCalculator(MET,METPhi, Muons->at(0).Pt(), Muons->at(0).Phi(), scaleMet);
      MuonsPt_ = Muons->at(0).Pt();
      MuonsEta_ = Muons->at(0).Eta();

    //  std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(Muons->at(0).Pt(), Muons->at(0).Eta(), Muons->at(0).Phi());
    //  MuonsDeltaRJet.push_back(DeltaR_relPT.first);
    //  MuonsRelPTJet.push_back(DeltaR_relPT.second);

      // get Efficiencies
      muPurityCorrectionVec_ =  MuPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      muMTWEffVec_ = MuMTWSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      //muMTWEffVec_ = MuMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
/*      if(NJets < 2.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets2_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 3.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets3_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 4.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets4_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 5.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets5_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 6.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets6_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 8.5){
        muMTWEffVec_ = MuMTWHTMHT_NJets78_->GetEff(HT, MHT, useAsymmErrors);
      }else{
        muMTWEffVec_ = MuMTWHTMHT_NJets9Inf_->GetEff(HT, MHT, useAsymmErrors);
      }
*/      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);      

      muIsoEffVec_ = MuIsoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);
      muRecoEffVec_ = MuRecoPTEta_->GetEff(Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), useAsymmErrors);
      //muRecoEffVec_ = MuRecoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);
      //muAccEffVec_ = MuAccHTNJets_->GetEff(HT, NJets, useAsymmErrors);

      muAccEffVec_ = MuAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);
/*
      if(BTags==0){
        if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }else if(BTags==1){
        if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }else if(BTags==2){
          if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }else{
          if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }
*/
      elecRecoEffVec_ = ElecRecoPTEta_->GetEff(Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), useAsymmErrors);
      //elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(Muons_MT2Activity->at(0), Muons->at(0).Pt(), useAsymmErrors);

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

      if(!runOnStandardModelMC && correctMuonIso) muIsoEff_ *= GetSF(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctMuonID) muRecoEff_ *= GetSF(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronID) elecRecoEff_ *= GetSF(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronIso) elecIsoEff_ *= GetSF(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));

      if(!runOnStandardModelMC && doTrackingCorrection){
        if(Muons->at(0).Pt() > 10) muRecoEff_ *= GetSF(h_muTrkHighPtSF, Muons->at(0).Eta());
        else muRecoEff_ *= GetSF(h_muTrkLowPtSF, Muons->at(0).Eta());
        elecRecoEff_ *= GetSF(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt());
      }

      if(runOnStandardModelMC){
        isoSF = GetSF(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
        recoSF = GetSF(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()));
        trackingSF = GetSF(h_muTrkHighPtSF, Muons->at(0).Eta());
      }

      if(muIsoEff_ > 1) muIsoEff_=1;
      if(muRecoEff_ > 1) muRecoEff_=1;
      if(elecRecoEff_ > 1) elecRecoEff_=1;
      if(elecIsoEff_ > 1) elecIsoEff_=1;

      // calculate Weights
      // muCS >99% purity
      //purityCorrectedWeight_ = Weight * muPurityCorrection_;
      purityCorrectedWeight_ = Weight;
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
      diLepLostWeight_ = Weight * 1/muMTWEff_ * (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;

      totalWeightDiLep_ = totalWeight_ + (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      totalWeightDiLepIsoTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);
      totalWeightDiLepIsoMuTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionMuIsoTrackEff_);
      totalWeightDiLepIsoElecTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionElecIsoTrackEff_);
      totalWeightDiLepIsoPionTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionPionIsoTrackEff_);
      totalWeightDiLepIsoTrackReducedCombined_ = totalWeightDiLep_ * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_));

      muTotalWeightDiLep_ = muTotalWeight_ + (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      muTotalWeightDiLepIsoTrackReduced_ = muTotalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);

      if(mtw<100){
        MuMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
        CombinedMeanWeight_->Fill(Bin_+0.01, 0.5*(totalWeightDiLepIsoTrackReduced_/Weight), Weight);

        if(Bin_<=72){
          MuWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
          CombinedWeightPerBin_[Bin_-1]->Fill(0.5*(totalWeightDiLepIsoTrackReduced_/Weight),Weight);
        }
      }

      if(totalWeightDiLepIsoTrackReduced_/Weight<0.01){
        std::cout<<"Something might have gone wrong! 0L/1L too small!"<<std::endl;
        std::cout<<NJets<<"; "<<BTags<<"; "<<HT<<"; "<<MHT<<std::endl;
        std::cout<<muIsoWeight_/Weight<<"; "<<muRecoWeight_/Weight<<"; "<<muAccWeight_/Weight<<std::endl;
      }

      //std::cout << (1-muDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_ / Weight << std::endl;

      // Uncertainties
      // Total weight can be factorisated as 1*[2*(3a+3b)+4], where 1-4 are functions of
      // 1: eventweight, isotrack, MT cut, CS purity
      // 2: singleLep purity, 1/(iso(mu)*reco(mu)*acc(mu))
      // 3a: iso(mu),reco(mu),acc(mu)
      // 3a: iso(e),reco(e),acc(e)
      // 4: diLeptonic contribution: singleLep purity, diLep found

      Float_t w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_; // * muPurityCorrection_
      Float_t w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
      Float_t w3a = 1-muIsoEff_*muRecoEff_*muAccEff_;
      Float_t w3b = 1-elecIsoEff_*elecRecoEff_*elecAccEff_ ;
      Float_t w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReducedCombined_

      isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionMuIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionMuIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionElecIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionElecIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionPionIsoTrackEffVec_.errUp) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionPionIsoTrackEffVec_.errDown) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/(muMTWEff_ + muMTWEffVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/(muMTWEff_ - muMTWEffVec_.errDown) * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatUp = 0; // no purity correction for muCS (>99%)
      purityStatDown = 0; // no purity correction for muCS (>99%)

      double singleLepPurityStat1 = w1 * ((muDiLepContributionMTWAppliedEff_ + muDiLepContributionMTWAppliedEffVec_.errUp) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_-muDiLepContributionMTWAppliedEffVec_.errUp) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityStat2 = w1 * ((muDiLepContributionMTWAppliedEff_ - muDiLepContributionMTWAppliedEffVec_.errDown) * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - muDiLepContributionMTWAppliedEff_+muDiLepContributionMTWAppliedEffVec_.errDown) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      if((singleLepPurityStat1 > 0 && singleLepPurityStat2 > 0) || (singleLepPurityStat1 < 0 && singleLepPurityStat2 < 0)){
        std::cout << "Error calculating singleLepPurityStat. Applying fix." << std::endl;
        singleLepPurityStatUp = 0;
        singleLepPurityStatDown = 0;
      }
      else if(singleLepPurityStat1 > 0){
        singleLepPurityStatUp = singleLepPurityStat1;
        singleLepPurityStatDown = singleLepPurityStat2;
      }else{
        singleLepPurityStatUp = singleLepPurityStat2;
        singleLepPurityStatDown = singleLepPurityStat1;
      }

      diLepFoundStatDown = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errUp)/(muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
      diLepFoundStatUp =w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_+muDiLepEffMTWAppliedEffVec_.errDown)/(muDiLepEffMTWAppliedEff_-muDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

      muIsoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_+muIsoEffVec_.errUp)*muRecoEff_*muAccEff_) * (1-(muIsoEff_+muIsoEffVec_.errUp)*muRecoEff_*muAccEff_ +w3b) + w4) - wGes;
      muIsoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/((muIsoEff_-muIsoEffVec_.errDown)*muRecoEff_*muAccEff_) * (1-(muIsoEff_-muIsoEffVec_.errDown)*muRecoEff_*muAccEff_ +w3b) + w4) - wGes;
      muRecoStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_) * (1-muIsoEff_*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_ +w3b) + w4) - wGes;
      muRecoStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_) * (1-muIsoEff_*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_ +w3b) + w4) - wGes;
      muAccStatDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_+muAccEffVec_.errUp)) * (1-muIsoEff_*muRecoEff_*(muAccEff_+muAccEffVec_.errUp) +w3b) + w4) - wGes;
      muAccStatUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*(muAccEff_-muAccEffVec_.errDown)) * (1-muIsoEff_*muRecoEff_*(muAccEff_-muAccEffVec_.errDown) +w3b) + w4) - wGes;

      elecIsoStatDown = w1 * (w2 * (w3a + 1-(elecIsoEff_+elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_) + w4) - wGes;
      elecIsoStatUp = w1 * (w2 * (w3a + 1-(elecIsoEff_-elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_)  + w4) - wGes;
      elecRecoStatDown = w1 * (w2 * (w3a + 1-elecIsoEff_*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_) + w4) - wGes;
      elecRecoStatUp = w1 * (w2 * (w3a + 1-elecIsoEff_*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_) + w4) - wGes;
      elecAccStatDown = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp)) + w4) - wGes;
      elecAccStatUp = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown)) + w4) - wGes;


      //cut of systematics so that efficiencies are <=1
      double isoTrackMax = expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_);
      if(isoTrackMax > 1) isoTrackMax = 1;
      isoTrackSysDown = Weight * (1 - isoTrackMax) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      double isoTrackMin = expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_);
      isoTrackSysUp  = Weight * (1 - isoTrackMin) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double muIsoTrackMax, muIsoTrackMin;
      if(useFlatIsoTrackUnc) muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + 0.01 * muIsoTrackUncertaintyUp_);
      else muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(NJets)));
      if(muIsoTrackMax > 1) muIsoTrackMax = 1;
      muIsoTrackSysDown = Weight * (1 - (muIsoTrackMax + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - 0.01 * muIsoTrackUncertaintyDown_);
      else muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(NJets)));
      muIsoTrackSysUp  = Weight * (1 - (muIsoTrackMin + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double elecIsoTrackMax, elecIsoTrackMin;
      if(useFlatIsoTrackUnc) elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + 0.01 * elecIsoTrackUncertaintyUp_);
      else elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(NJets)));
      if(elecIsoTrackMax > 1) elecIsoTrackMax = 1;
      elecIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMax + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - 0.01 * elecIsoTrackUncertaintyDown_);
      else elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(NJets)));
      elecIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMin + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double pionIsoTrackMax, pionIsoTrackMin;
      if(useFlatIsoTrackUnc) pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + 0.01 * pionIsoTrackUncertaintyUp_);
      else pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(NJets)));
      if(pionIsoTrackMax > 1) pionIsoTrackMax = 1;
      pionIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMax)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - 0.01 * pionIsoTrackUncertaintyDown_);
      else pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(NJets)));
      pionIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMin)) * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4) - wGes;

      double MTWMax, MTWMin; 
      if(useFlatMTWUnc) MTWMax = muMTWEff_ + (1-muMTWEff_) * 0.01 * MuMTWUncertaintyUp_;
      else MTWMax = muMTWEff_ + muMTWEff_ * GetAccSF(h_muMTW_up, NJets, HT, MHT);
      if(MTWMax > 1) MTWMax = 1;
      MTWSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/MTWMax * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatMTWUnc) MTWMin = muMTWEff_ - (1-muMTWEff_) * 0.01 * MuMTWUncertaintyDown_;
      else MTWMin = muMTWEff_ - muMTWEff_ * GetAccSF(h_muMTW_down, NJets, HT, MHT);
      MTWSysUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/MTWMin * (w2 * (w3a+w3b) + w4) - wGes;

      puritySysUp = 0; // no purity correction for muCS (>99%)    
      puritySysDown = 0; // no purity correction for muCS (>99%)
      
      double singleLepPurityMax = muDiLepContributionMTWAppliedEff_ + (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityUp_;
      if(singleLepPurityMax > 1) singleLepPurityMax = 1;
      double singleLepPuritySys1 = w1 * (singleLepPurityMax * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - singleLepPurityMax) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityMin = muDiLepContributionMTWAppliedEff_ - (1-muDiLepContributionMTWAppliedEff_) * 0.01 * MuSingleLepPurityDown_;
      double singleLepPuritySys2 = w1 * (singleLepPurityMin * 1/(muIsoEff_*muRecoEff_*muAccEff_) * (w3a+w3b) + (1 - singleLepPurityMin) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_) - wGes;
      if((singleLepPuritySys1 > 0 && singleLepPuritySys2 > 0) || (singleLepPuritySys1 < 0 && singleLepPuritySys2 < 0)){
        std::cout << "Error calculating singleLepPuritySys. Applying fix." << std::endl;
        singleLepPuritySysUp = 0;
        singleLepPuritySysDown = 0;
      }
      else if(singleLepPuritySys1 > 0){
        singleLepPuritySysUp = singleLepPuritySys1;
        singleLepPuritySysDown = singleLepPuritySys2;
      }else{
        singleLepPuritySysUp = singleLepPuritySys2;
        singleLepPuritySysDown = singleLepPuritySys1;
      }    

      double diLepFoundMax = muDiLepEffMTWAppliedEff_ *(1 + 0.01 * MuDiLepFoundUp_);
      if(diLepFoundMax > 1) diLepFoundMax = 1;
      diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-diLepFoundMax)/diLepFoundMax) - wGes;
      double diLepFoundMin = muDiLepEffMTWAppliedEff_ *(1 - 0.01 * MuDiLepFoundDown_);
      diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-muDiLepContributionMTWAppliedEff_) * (1-diLepFoundMin)/diLepFoundMin) - wGes;

      double muIsoMax = muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_);
      if(usePrelimSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * getMuonIsoSF(Muons->at(0).Pt(), Muons->at(0).Eta(), Muons_MT2Activity->at(0)));
      // add 1% systematic to uncertainty (set bool to true)
      if(useSFs) muIsoMax = muIsoEff_ *(1 + GetSFUnc(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014));
      if(muIsoMax > 1) muIsoMax = 1;
      muIsoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoMax*muRecoEff_*muAccEff_) * (1-muIsoMax*muRecoEff_*muAccEff_ +w3b) + w4) - wGes;
      double muIsoMin = muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_);
      if(usePrelimSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * getMuonIsoSF(Muons->at(0).Pt(), Muons->at(0).Eta(), Muons_MT2Activity->at(0)));
      // add 1% systematic to uncertainty (set bool to true)
      if(useSFs) muIsoMin = muIsoEff_ *(1 - GetSFUnc(h_muIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014));
      muIsoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoMin*muRecoEff_*muAccEff_) * (1-muIsoMin*muRecoEff_*muAccEff_ +w3b) + w4) - wGes;

      double muRecoMax = muRecoEff_ *(1 + 0.01 * MuRecoUncertaintyUp_);
      if(usePrelimSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * getMuonIDSF(Muons->at(0).Pt(), Muons->at(0).Eta()));
      // add 1% systematic to uncertainty (set bool to true)
      if(useSFs && !doTrackingCorrection) muRecoMax = muRecoEff_ *(1 + GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014));
      if(useSFs && doTrackingCorrection) muRecoMax = muRecoEff_ *(1 + GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014) + GetSFUnc(h_muTrkHighPtSF, Muons->at(0).Eta(), 0.01));
      if(muRecoMax > 1) muRecoMax = 1;
      muRecoSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoMax*muAccEff_) * (1-muIsoEff_*muRecoMax*muAccEff_ +w3b) + w4) - wGes;
      double muRecoMin = muRecoEff_ *(1 - 0.01 * MuRecoUncertaintyDown_);
      if(usePrelimSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * getMuonIDSF(Muons->at(0).Pt(), Muons->at(0).Eta()));
      // add 1% systematic to uncertainty (set bool to true)
      if(useSFs && !doTrackingCorrection) muRecoMin = muRecoEff_ *(1 - GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014));
      if(useSFs && doTrackingCorrection) muRecoMin = muRecoEff_ *(1 - GetSFUnc(h_muIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta()), 0.014) - GetSFUnc(h_muTrkHighPtSF, Muons->at(0).Eta(), 0.01));
      muRecoSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoMin*muAccEff_) * (1-muIsoEff_*muRecoMin*muAccEff_ +w3b) + w4) - wGes;

      double muAccMax, muAccMin;       
      if(useFlatAccUnc){
        if(MHT>500) muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_HighMHT_);
        else muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_LowMHT_);
      }else{
        muAccMax = muAccEff_ *(1 + GetAccSF(h_muAccPDF_up, NJets, HT, MHT));
      }
      if(muAccMax > 1) muAccMax = 1;
      muAccSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccMax) * (1-muIsoEff_*muRecoEff_*muAccMax +w3b) + w4) - wGes;
      if(useFlatAccUnc){
        if(MHT>500) muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_HighMHT_);
        else muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_LowMHT_);
      }else{
        muAccMin = muAccEff_ *(1 - GetAccSF(h_muAccPDF_down, NJets, HT, MHT));
      }
      muAccSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccMin) * (1-muIsoEff_*muRecoEff_*muAccMin +w3b) + w4) - wGes;
      
      double muAccQsquareMax, muAccQsquareMin;       
      if(useFlatAccUnc){
        muAccQsquareMax = muAccEff_ *(1 + 0.01 * MuAccQsquareUncertaintyUp_);
      }else{
        muAccQsquareMax = muAccEff_ *(1 + GetAccSF(h_muAccQ2_up, NJets, HT, MHT));
      }
      if(muAccQsquareMax > 1) muAccQsquareMax = 1;
      muAccQsquareSysDown = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccQsquareMax) * (1-muIsoEff_*muRecoEff_*muAccQsquareMax +w3b) + w4) - wGes;
      if(useFlatAccUnc){
        muAccQsquareMin = muAccEff_ *(1 - 0.01 * MuAccQsquareUncertaintyDown_);
      }else{
        muAccQsquareMin = muAccEff_ *(1 - GetAccSF(h_muAccQ2_down, NJets, HT, MHT));
      }
      muAccQsquareSysUp = w1 * (muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccQsquareMin) * (1-muIsoEff_*muRecoEff_*muAccQsquareMin +w3b) + w4) - wGes;
      
      double elecIsoMax = elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_);
      if(usePrelimSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * getElecIsoSF(Muons->at(0).Pt(), Muons->at(0).Eta(), Muons_MT2Activity->at(0)));
      if(useSFs) elecIsoMax = elecIsoEff_ *(1 + GetSFUnc(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())));
      if(elecIsoMax > 1) elecIsoMax = 1;
      elecIsoSysDown = w1 * (w2 * (w3a + 1-elecIsoMax*elecRecoEff_*elecAccEff_) + w4) - wGes;
      double elecIsoMin = elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_);
      if(usePrelimSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * getElecIsoSF(Muons->at(0).Pt(), Muons->at(0).Eta(), Muons_MT2Activity->at(0)));
      if(useSFs) elecIsoMin = elecIsoEff_ *(1 - GetSFUnc(h_elecIsoSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())));
      elecIsoSysUp = w1 * (w2 * (w3a + 1-elecIsoMin*elecRecoEff_*elecAccEff_) + w4) - wGes;

      double elecRecoMax = elecRecoEff_*(1 + 0.01 * ElecRecoUncertaintyUp_);
      if(usePrelimSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * getElecIDSF(Muons->at(0).Pt(), Muons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())));
      if(useSFs && doTrackingCorrection){
        if(Muons->at(0).Pt() > 20) elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt()));
        else elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt(), 0.03));
      }
      if(elecRecoMax > 1) elecRecoMax = 1;
      elecRecoSysDown = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoMax*elecAccEff_) + w4) - wGes;
      double elecRecoMin = elecRecoEff_*(1 - 0.01 * ElecRecoUncertaintyDown_);
      if(usePrelimSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * getElecIDSF(Muons->at(0).Pt(), Muons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())));
      if(useSFs && doTrackingCorrection){
        if(Muons->at(0).Pt() > 20) elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt()));
        else elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Muons->at(0).Pt(), std::abs(Muons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Muons->at(0).Eta(), Muons->at(0).Pt(), 0.03));
      }
      elecRecoSysUp = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoMin*elecAccEff_) + w4) - wGes;

      double elecAccMax, elecAccMin;       
      if(useFlatAccUnc){
        if(MHT>500) elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_HighMHT_);
        else elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_LowMHT_);
      }else{
        elecAccMax = elecAccEff_ *(1 + GetAccSF(h_elecAccPDF_up, NJets, HT, MHT));
      }
      if(elecAccMax > 1) elecAccMax = 1;
      elecAccSysDown = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*elecAccMax) + w4) - wGes;
      if(useFlatAccUnc){
        if(MHT>500) elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_HighMHT_);
        else elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_LowMHT_);
      }else{
        elecAccMin = elecAccEff_ *(1 - GetAccSF(h_elecAccPDF_down, NJets, HT, MHT));
      }
      elecAccSysUp = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*elecAccMin) + w4) - wGes;
      
      double elecAccQsquareMax, elecAccQsquareMin;       
      if(useFlatAccUnc){
        elecAccQsquareMax = elecAccEff_ *(1 + 0.01 * ElecAccQsquareUncertaintyUp_);
      }else{
        elecAccQsquareMax = elecAccEff_ *(1 + GetAccSF(h_elecAccQ2_up, NJets, HT, MHT));
      }
      if(elecAccQsquareMax > 1) elecAccQsquareMax = 1;
      elecAccQsquareSysDown =w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*elecAccQsquareMax) + w4) - wGes;
      if(useFlatAccUnc){
        elecAccQsquareMin = elecAccEff_ *(1 - 0.01 * ElecAccQsquareUncertaintyDown_);
      }else{
        elecAccQsquareMin = elecAccEff_ *(1 - GetAccSF(h_elecAccQ2_down, NJets, HT, MHT));
      }
      elecAccQsquareSysUp = w1 * (w2 * (w3a + 1-elecIsoEff_*elecRecoEff_*elecAccQsquareMin) + w4) - wGes;


      totalStatUp = sqrt(muIsoTrackStatUp*muIsoTrackStatUp+elecIsoTrackStatUp*elecIsoTrackStatUp+pionIsoTrackStatUp*pionIsoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
      totalSysUp = sqrt(muIsoTrackSysUp*muIsoTrackSysUp+elecIsoTrackSysUp*elecIsoTrackSysUp+pionIsoTrackSysUp*pionIsoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp);
      totalUncUp = sqrt(totalStatUp*totalStatUp+totalSysUp*totalSysUp);

      totalStatDown = -sqrt(muIsoTrackStatDown*muIsoTrackStatDown+elecIsoTrackStatDown*elecIsoTrackStatDown+pionIsoTrackStatDown*pionIsoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);
      totalSysDown = -sqrt(muIsoTrackSysDown*muIsoTrackSysDown+elecIsoTrackSysDown*elecIsoTrackSysDown+pionIsoTrackSysDown*pionIsoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown);
      totalUncDown = -sqrt(totalStatDown*totalStatDown+totalSysDown*totalSysDown);

/*
      // Calculate weights if they do depend on the number of BTags:
      // BTags == 0
      if(NJets<6.5){
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }

      if(NJets<6.5){
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);     
      muDiLepEffMTWAppliedEff_ = muDiLepEffMTWAppliedEffVec_.eff;
      muDiLepContributionMTWAppliedEff_ = muDiLepContributionMTWAppliedEffVec_.eff;
*/
      muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      muMTWEff_ = muMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_; 
      w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
      w3a = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w3b = 1-elecIsoEff_*elecRecoEff_*elecAccEff_ ;
      w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags == 1
      if(NJets<6.5){
        //if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        //if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);      
      muDiLepEffMTWAppliedEff_ = muDiLepEffMTWAppliedEffVec_.eff;
      muDiLepContributionMTWAppliedEff_ = muDiLepContributionMTWAppliedEffVec_.eff;
*/
      muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      muMTWEff_ = muMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_; 
      w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
      w3a = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w3b = 1-elecIsoEff_*elecRecoEff_*elecAccEff_ ;
      w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags == 2
      if(NJets<6.5){
        //if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        //if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);      
      muDiLepEffMTWAppliedEff_ = muDiLepEffMTWAppliedEffVec_.eff;
      muDiLepContributionMTWAppliedEff_ = muDiLepContributionMTWAppliedEffVec_.eff;
*/
      muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      muMTWEff_ = muMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_; 
      w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
      w3a = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w3b = 1-elecIsoEff_*elecRecoEff_*elecAccEff_ ;
      w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags >= 3
      if(NJets<6.5){
        //if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        //if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      if(NJets > 2){
	      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
	      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

	      muAccEff_ = muAccEffVec_.eff;
	      elecAccEff_ = elecAccEffVec_.eff;
/*
	      muDiLepContributionMTWAppliedEffVec_ = MuDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
	      muDiLepEffMTWAppliedEffVec_ = MuDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);      
      	muDiLepEffMTWAppliedEff_ = muDiLepEffMTWAppliedEffVec_.eff;
        muDiLepContributionMTWAppliedEff_ = muDiLepContributionMTWAppliedEffVec_.eff;
*/
        muMTWEffVec_ = MuMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        muMTWEff_ = muMTWEffVec_.eff;
     
        expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

        //for compatibility
        expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
        expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
        expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
        expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

        w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/muMTWEff_; 
	      w2 = muDiLepContributionMTWAppliedEff_ * 1/(muIsoEff_*muRecoEff_*muAccEff_);
	      w3a = 1-muIsoEff_*muRecoEff_*muAccEff_;
	      w3b = 1-elecIsoEff_*elecRecoEff_*elecAccEff_ ;
        w4 = (1-muDiLepContributionMTWAppliedEff_) * (1-muDiLepEffMTWAppliedEff_)/muDiLepEffMTWAppliedEff_;
	      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
	      totalWeight_BTags_noIsoTrack_.push_back(Weight * 1/muMTWEff_ * (w2 * (w3a+w3b) + w4));
  	  }

    } 
  else if(MuonsNum_==0 && ElectronsNum_==1)
    {
      // cout << "Single electron event...";
      // cout << "get MTW...";
      mtw =  Electrons_MTW->at(0);
      //mtw =  MTWCalculator(MET,METPhi, Electrons->at(0).Pt(), Electrons->at(0).Phi(), scaleMet);
      ElectronsPt_ = Electrons->at(0).Pt();
      ElectronsEta_ = Electrons->at(0).Eta();

    //  std::pair<double, double> DeltaR_relPT = minDeltaRLepJet(Electrons->at(0).Pt(), Electrons->at(0).Eta(), Electrons->at(0).Phi());
    //  ElectronsDeltaRJet.push_back(DeltaR_relPT.first);
    //  ElectronsRelPTJet.push_back(DeltaR_relPT.second);

      // get Efficiencies
      elecPurityCorrectionVec_ =  ElecPurityMHTNJets_->GetEff(MHT,NJets, useAsymmErrors);
      elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      //elecMTWEffVec_ = ElecMTWHTNJets_->GetEff(HT, NJets, useAsymmErrors);
/*      if(NJets < 2.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets2_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 3.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets3_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 4.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets4_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 5.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets5_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 6.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets6_->GetEff(HT, MHT, useAsymmErrors);
      }else if(NJets < 8.5){
        elecMTWEffVec_ = ElecMTWHTMHT_NJets78_->GetEff(HT, MHT, useAsymmErrors);
      }else{
        elecMTWEffVec_ = ElecMTWHTMHT_NJets9Inf_->GetEff(HT, MHT, useAsymmErrors);
      }
*/      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);
      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJets_->GetEff(NJets, useAsymmErrors);

      // cout << "get isolation efficiency...";
      elecRecoEffVec_ = ElecRecoPTEta_->GetEff(Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), useAsymmErrors);
      //elecRecoEffVec_ = ElecRecoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);
      elecIsoEffVec_ = ElecIsoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);

      muAccEffVec_ = MuAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(BinQCD_, useAsymmErrors);

    /*
      if(BTags==0){
        if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }else if(BTags==1){
          if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
      }else if(BTags==1){
          if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }    
      }else{
          if(NJets<6.5){
          if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }

        if(NJets<6.5){
          if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        }
        else{
          //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
          //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
          //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
          else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
        }    
      }
*/
      muIsoEffVec_ = MuIsoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);
      muRecoEffVec_ = MuRecoPTEta_->GetEff(Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), useAsymmErrors);
      //muRecoEffVec_ = MuRecoActivityPT_->GetEff(Electrons_MT2Activity->at(0), Electrons->at(0).Pt(), useAsymmErrors);
      
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

      if(!runOnStandardModelMC && correctMuonIso) muIsoEff_ *= GetSF(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctMuonID) muRecoEff_ *= GetSF(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronID) elecRecoEff_ *= GetSF(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
      if(!runOnStandardModelMC && correctElectronIso) elecIsoEff_ *= GetSF(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));

      if(!runOnStandardModelMC && doTrackingCorrection){
        if(Electrons->at(0).Pt() > 10) muRecoEff_ *= GetSF(h_muTrkHighPtSF, Electrons->at(0).Eta());
        else muRecoEff_ *= GetSF(h_muTrkLowPtSF, Electrons->at(0).Eta());
        elecRecoEff_ *= GetSF(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt());
      }

      if(runOnStandardModelMC){
        isoSF = GetSF(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
        recoSF = GetSF(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()));
        trackingSF = GetSF(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt());
      }

      if(muIsoEff_ > 1) muIsoEff_=1;
      if(muRecoEff_ > 1) muRecoEff_=1;
      if(elecRecoEff_ > 1) elecRecoEff_=1;
      if(elecIsoEff_ > 1) elecIsoEff_=1;

      // calculate Weights
      // cout << "calculate weights...";
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
      diLepLostWeight_ = Weight * elecPurityCorrection_ * 1/elecMTWEff_ * (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
    
      totalWeightDiLep_ = totalWeight_ + (1-elecDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      totalWeightDiLepIsoTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);
      totalWeightDiLepIsoMuTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionMuIsoTrackEff_);
      totalWeightDiLepIsoElecTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionElecIsoTrackEff_);
      totalWeightDiLepIsoPionTrackReduced_ = totalWeightDiLep_ * (1 - expectationReductionPionIsoTrackEff_);
      totalWeightDiLepIsoTrackReducedCombined_ = totalWeightDiLep_ * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_));

      elecTotalWeightDiLep_ = elecTotalWeight_ + (1-elecDiLepContributionMTWAppliedEff_) * mtwCorrectedWeight_ * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      elecTotalWeightDiLepIsoTrackReduced_ = elecTotalWeightDiLep_ * (1 - expectationReductionIsoTrackEff_);

      if(mtw<100){
        ElecMeanWeight_->Fill(Bin_+0.01, totalWeightDiLepIsoTrackReduced_/Weight, Weight);
        CombinedMeanWeight_->Fill(Bin_+0.01, 0.5*(totalWeightDiLepIsoTrackReduced_/Weight), Weight);

        if(Bin_<=72){
          ElecWeightPerBin_[Bin_-1]->Fill(totalWeightDiLepIsoTrackReduced_/Weight,Weight);
          CombinedWeightPerBin_[Bin_-1]->Fill(0.5*(totalWeightDiLepIsoTrackReduced_/Weight),Weight);
        }
      }

      if(totalWeightDiLepIsoTrackReduced_/Weight<0.01){
        std::cout<<"Something might have gone wrong! 0L/1L too small!"<<std::endl;
        std::cout<<NJets<<"; "<<BTags<<"; "<<HT<<"; "<<MHT<<std::endl;
        std::cout<<muIsoWeight_/Weight<<"; "<<muRecoWeight_/Weight<<"; "<<muAccWeight_/Weight<<std::endl;
      }

     
      // Uncertainties
      // For explanation see muons
      Float_t w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * elecPurityCorrection_ * 1/elecMTWEff_;
      Float_t w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
      Float_t w3a = 1-elecIsoEff_*elecRecoEff_*elecAccEff_;
      Float_t w3b = 1-muIsoEff_*muRecoEff_*muAccEff_;
      Float_t w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      Float_t wGes = w1 * (w2 * (w3a+w3b) + w4); // should be identical to totalWeightDiLepIsoTrackReducedCombined_

      isoTrackStatDown = Weight * (1 - expectationReductionIsoTrackEff_ - expectationReductionIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      isoTrackStatUp = Weight * (1 - expectationReductionIsoTrackEff_ + expectationReductionIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionMuIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      muIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionMuIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionElecIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      elecIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionElecIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) - expectationReductionPionIsoTrackEffVec_.errUp) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      pionIsoTrackStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_) + expectationReductionPionIsoTrackEffVec_.errDown) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/(elecMTWEff_ + elecMTWEffVec_.errUp) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      MTWStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/(elecMTWEff_ - elecMTWEffVec_.errDown) * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * (elecPurityCorrection_ + elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;
      purityStatDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * (elecPurityCorrection_ - elecPurityCorrectionVec_.errUp) * (w2 * (w3a+w3b) + w4) - wGes;

      double singleLepPurityStat1 = w1 * ((elecDiLepContributionMTWAppliedEff_ + elecDiLepContributionMTWAppliedEffVec_.errUp) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_-elecDiLepContributionMTWAppliedEffVec_.errUp) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityStat2 = w1 * ((elecDiLepContributionMTWAppliedEff_ - elecDiLepContributionMTWAppliedEffVec_.errDown) * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - elecDiLepContributionMTWAppliedEff_+elecDiLepContributionMTWAppliedEffVec_.errDown) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      if((singleLepPurityStat1 > 0 && singleLepPurityStat2 > 0) || (singleLepPurityStat1 < 0 && singleLepPurityStat2 < 0)){
        std::cout << "Error calculating singleLepPurityStat. Applying fix." << std::endl;
        singleLepPurityStatUp = 0;
        singleLepPurityStatDown = 0;
      }
      else if(singleLepPurityStat1 > 0){
        singleLepPurityStatUp = singleLepPurityStat1;
        singleLepPurityStatDown = singleLepPurityStat2;
      }else{
        singleLepPurityStatUp = singleLepPurityStat2;
        singleLepPurityStatDown = singleLepPurityStat1;
      }

      diLepFoundStatDown = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errUp)/(elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errUp)) - wGes;
      diLepFoundStatUp =w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_+elecDiLepEffMTWAppliedEffVec_.errDown)/(elecDiLepEffMTWAppliedEff_-elecDiLepEffMTWAppliedEffVec_.errDown)) - wGes;

      elecIsoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_+elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_) * (1-(elecIsoEff_+elecIsoEffVec_.errUp)*elecRecoEff_*elecAccEff_ +w3b) + w4) - wGes;
      elecIsoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/((elecIsoEff_-elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_) * (1-(elecIsoEff_-elecIsoEffVec_.errDown)*elecRecoEff_*elecAccEff_ +w3b) + w4) - wGes;
      elecRecoStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_) * (1-elecIsoEff_*(elecRecoEff_+elecRecoEffVec_.errUp)*elecAccEff_ +w3b) + w4) - wGes;
      elecRecoStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_) * (1-elecIsoEff_*(elecRecoEff_-elecRecoEffVec_.errDown)*elecAccEff_ +w3b) + w4) - wGes;
      elecAccStatDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp)) * (1-elecIsoEff_*elecRecoEff_*(elecAccEff_+elecAccEffVec_.errUp) +w3b) + w4) - wGes;
      elecAccStatUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown)) * (1-elecIsoEff_*elecRecoEff_*(elecAccEff_-elecAccEffVec_.errDown) +w3b) + w4) - wGes;

      muIsoStatDown = w1 * (w2 * (w3a + 1-(muIsoEff_+muIsoEffVec_.errUp)*muRecoEff_*muAccEff_) + w4) - wGes;
      muIsoStatUp = w1 * (w2 * (w3a + 1-(muIsoEff_-muIsoEffVec_.errDown)*muRecoEff_*muAccEff_) + w4) - wGes;
      muRecoStatDown = w1 * (w2 * (w3a + 1-muIsoEff_*(muRecoEff_+muRecoEffVec_.errUp)*muAccEff_) + w4) - wGes;
      muRecoStatUp = w1 * (w2 * (w3a + 1-muIsoEff_*(muRecoEff_-muRecoEffVec_.errDown)*muAccEff_) + w4) - wGes;
      muAccStatDown = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*(muAccEff_+muAccEffVec_.errUp)) + w4) - wGes;
      muAccStatUp = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*(muAccEff_-muAccEffVec_.errDown)) + w4) - wGes;


      //cut of systematics so that efficiencies are <=1
      double isoTrackMax = expectationReductionIsoTrackEff_ *(1 + 0.01 * isoTrackUncertaintyUp_);
      if(isoTrackMax > 1) isoTrackMax = 1;
      isoTrackSysDown = Weight * (1 - isoTrackMax) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      double isoTrackMin = expectationReductionIsoTrackEff_ *(1 - 0.01 * isoTrackUncertaintyDown_);
      isoTrackSysUp  = Weight * (1 - isoTrackMin) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double muIsoTrackMax, muIsoTrackMin;
      if(useFlatIsoTrackUnc) muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + 0.01 * muIsoTrackUncertaintyUp_);
      else muIsoTrackMax = expectationReductionMuIsoTrackEff_ *(1 + h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(NJets)));
      if(muIsoTrackMax > 1) muIsoTrackMax = 1;
      muIsoTrackSysDown = Weight * (1 - (muIsoTrackMax + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - 0.01 * muIsoTrackUncertaintyDown_);
      else muIsoTrackMin = expectationReductionMuIsoTrackEff_ *(1 - h_muIsoTrack_NJetsunc->GetBinContent(h_muIsoTrack_NJetsunc->FindBin(NJets)));
      muIsoTrackSysUp  = Weight * (1 - (muIsoTrackMin + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double elecIsoTrackMax, elecIsoTrackMin;
      if(useFlatIsoTrackUnc) elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + 0.01 * elecIsoTrackUncertaintyUp_);
      else elecIsoTrackMax = expectationReductionElecIsoTrackEff_ *(1 + h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(NJets)));
      if(elecIsoTrackMax > 1) elecIsoTrackMax = 1;
      elecIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMax + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - 0.01 * elecIsoTrackUncertaintyDown_);
      else elecIsoTrackMin = expectationReductionElecIsoTrackEff_ *(1 - h_elecIsoTrack_NJetsunc->GetBinContent(h_elecIsoTrack_NJetsunc->FindBin(NJets)));
      elecIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + elecIsoTrackMin + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double pionIsoTrackMax, pionIsoTrackMin;
      if(useFlatIsoTrackUnc) pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + 0.01 * pionIsoTrackUncertaintyUp_);
      else pionIsoTrackMax = expectationReductionPionIsoTrackEff_ *(1 + h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(NJets)));
      if(pionIsoTrackMax > 1) pionIsoTrackMax = 1;
      pionIsoTrackSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMax)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatIsoTrackUnc) pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - 0.01 * pionIsoTrackUncertaintyDown_);
      else pionIsoTrackMin = expectationReductionPionIsoTrackEff_ *(1 - h_pionIsoTrack_NJetsunc->GetBinContent(h_pionIsoTrack_NJetsunc->FindBin(NJets)));
      pionIsoTrackSysUp  = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + pionIsoTrackMin)) * 1/elecMTWEff_ * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double MTWMax, MTWMin; 
      if(useFlatMTWUnc) MTWMax = elecMTWEff_ + (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyUp_;
      else MTWMax = elecMTWEff_ + elecMTWEff_ * GetAccSF(h_elecMTW_up, NJets, HT, MHT);
      if(MTWMax > 1) MTWMax = 1;
      MTWSysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/MTWMax * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;
      if(useFlatMTWUnc) MTWMin = elecMTWEff_ - (1-elecMTWEff_) * 0.01 * ElecMTWUncertaintyDown_;
      else MTWMin = elecMTWEff_ - elecMTWEff_ * GetAccSF(h_elecMTW_down, NJets, HT, MHT);
      MTWSysUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/MTWMin * elecPurityCorrection_ * (w2 * (w3a+w3b) + w4) - wGes;

      double purityMax = elecPurityCorrection_ + (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyUp_;
      if(purityMax > 1) purityMax = 1;
      puritySysUp = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * purityMax * (w2 * (w3a+w3b) + w4) - wGes;
      double purityMin = elecPurityCorrection_ - (1-elecPurityCorrection_) * 0.01 * ElecPurityUncertaintyDown_;
      puritySysDown = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * 1/elecMTWEff_ * purityMin * (w2 * (w3a+w3b) + w4) - wGes;

      double singleLepPurityMax = elecDiLepContributionMTWAppliedEff_ + (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityUp_;
      if(singleLepPurityMax > 1) singleLepPurityMax = 1;
      double singleLepPuritySys1 = w1 * (singleLepPurityMax * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - singleLepPurityMax) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      double singleLepPurityMin = elecDiLepContributionMTWAppliedEff_ - (1-elecDiLepContributionMTWAppliedEff_) * 0.01 * ElecSingleLepPurityDown_;
      double singleLepPuritySys2 = w1 * (singleLepPurityMin * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_) * (w3a+w3b) + (1 - singleLepPurityMin) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_) - wGes;
      if((singleLepPuritySys1 > 0 && singleLepPuritySys2 > 0) || (singleLepPuritySys1 < 0 && singleLepPuritySys2 < 0)){
        std::cout << "Error calculating singleLepPuritySys. Applying fix." << std::endl;
        singleLepPuritySysUp = 0;
        singleLepPuritySysDown = 0;
      }
      else if(singleLepPuritySys1 > 0){
        singleLepPuritySysUp = singleLepPuritySys1;
        singleLepPuritySysDown = singleLepPuritySys2;
      }else{
        singleLepPuritySysUp = singleLepPuritySys2;
        singleLepPuritySysDown = singleLepPuritySys1;
      }      

      double diLepFoundMax = elecDiLepEffMTWAppliedEff_ *(1 + 0.01 * ElecDiLepFoundUp_);
      if(diLepFoundMax > 1) diLepFoundMax = 1;
      diLepFoundSysDown = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-diLepFoundMax)/diLepFoundMax) - wGes;
      double diLepFoundMin = elecDiLepEffMTWAppliedEff_ *(1 - 0.01 * ElecDiLepFoundDown_);
      diLepFoundSysUp = w1 * (w2 * (w3a+w3b) + (1-elecDiLepContributionMTWAppliedEff_) * (1-diLepFoundMin)/diLepFoundMin) - wGes;

      double elecIsoMax = elecIsoEff_ *(1 + 0.01 * ElecIsoUncertaintyUp_);
      if(usePrelimSFs) elecIsoMax = elecIsoEff_ *(1 + 0.01 * getElecIsoSF(Electrons->at(0).Pt(), Electrons->at(0).Eta(), Electrons_MT2Activity->at(0)));
      if(useSFs) elecIsoMax = elecIsoEff_ *(1 + GetSFUnc(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())));
      if(elecIsoMax > 1) elecIsoMax = 1;
      elecIsoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoMax*elecRecoEff_*elecAccEff_) * (1-elecIsoMax*elecRecoEff_*elecAccEff_ +w3b) + w4) - wGes;
      double elecIsoMin = elecIsoEff_ *(1 - 0.01 * ElecIsoUncertaintyDown_);
      if(usePrelimSFs) elecIsoMin = elecIsoEff_ *(1 - 0.01 * getElecIsoSF(Electrons->at(0).Pt(), Electrons->at(0).Eta(), Electrons_MT2Activity->at(0)));
      if(useSFs) elecIsoMin = elecIsoEff_ *(1 - GetSFUnc(h_elecIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())));
      elecIsoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoMin*elecRecoEff_*elecAccEff_) * (1-elecIsoMin*elecRecoEff_*elecAccEff_ +w3b) + w4) - wGes;

      double elecRecoMax = elecRecoEff_ *(1 + 0.01 * ElecRecoUncertaintyUp_);
      if(usePrelimSFs) elecRecoMax = elecRecoEff_ *(1 + 0.01 * getElecIDSF(Electrons->at(0).Pt(), Electrons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())));
      if(useSFs && doTrackingCorrection){
        if(Electrons->at(0).Pt() > 20) elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt()));
        else elecRecoMax = elecRecoEff_ *(1 + GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) + GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt(), 0.03));
      }
      if(elecRecoMax > 1) elecRecoMax = 1;
      elecRecoSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoMax*elecAccEff_) * (1-elecIsoEff_*elecRecoMax*elecAccEff_ +w3b) + w4) - wGes;
      double elecRecoMin = elecRecoEff_ *(1 - 0.01 * ElecRecoUncertaintyDown_);
      if(usePrelimSFs) elecRecoMin = elecRecoEff_ *(1 - 0.01 * getElecIDSF(Electrons->at(0).Pt(), Electrons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())));
      if(useSFs && doTrackingCorrection){
        if(Electrons->at(0).Pt() > 20) elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt()));
        else elecRecoMin = elecRecoEff_ *(1 - GetSFUnc(h_elecIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta())) - GetSFUnc(h_elecTrkSF, Electrons->at(0).Eta(), Electrons->at(0).Pt(), 0.03));
      }
      elecRecoSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoMin*elecAccEff_) * (1-elecIsoEff_*elecRecoMin*elecAccEff_ +w3b) + w4) - wGes;

      double elecAccMax, elecAccMin;       
      if(useFlatAccUnc){
        if(MHT>500) elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_HighMHT_);
        else elecAccMax = elecAccEff_ *(1 + 0.01 * ElecAccUncertaintyUp_LowMHT_);
      }else{
        elecAccMax = elecAccEff_ *(1 + GetAccSF(h_elecAccPDF_up, NJets, HT, MHT));
      }
      if(elecAccMax > 1) elecAccMax = 1;
      elecAccSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccMax) * (1-elecIsoEff_*elecRecoEff_*elecAccMax +w3b) + w4) - wGes;
      if(useFlatAccUnc){
        if(MHT>500) elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_HighMHT_);
        else elecAccMin = elecAccEff_ *(1 - 0.01 * ElecAccUncertaintyDown_LowMHT_);
      }else{
        elecAccMin = elecAccEff_ *(1 - GetAccSF(h_elecAccPDF_down, NJets, HT, MHT));
      }
      elecAccSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccMin) * (1-elecIsoEff_*elecRecoEff_*elecAccMin +w3b) + w4) - wGes;
      
      double elecAccQsquareMax, elecAccQsquareMin;       
      if(useFlatAccUnc){
        elecAccQsquareMax = elecAccEff_ *(1 + 0.01 * ElecAccQsquareUncertaintyUp_);
      }else{
        elecAccQsquareMax = elecAccEff_ *(1 + GetAccSF(h_elecAccQ2_up, NJets, HT, MHT));
      }
      if(elecAccQsquareMax > 1) elecAccQsquareMax = 1;
      elecAccQsquareSysDown = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccQsquareMax) * (1-elecIsoEff_*elecRecoEff_*elecAccQsquareMax +w3b) + w4) - wGes;
      if(useFlatAccUnc){
        elecAccQsquareMin = elecAccEff_ *(1 - 0.01 * ElecAccQsquareUncertaintyDown_);
      }else{
        elecAccQsquareMin = elecAccEff_ *(1 - GetAccSF(h_elecAccQ2_down, NJets, HT, MHT));
      }
      elecAccQsquareSysUp = w1 * (elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccQsquareMin) * (1-elecIsoEff_*elecRecoEff_*elecAccQsquareMin +w3b) + w4) - wGes;
      
      double muIsoMax = muIsoEff_ *(1 + 0.01 * MuIsoUncertaintyUp_);
      if(usePrelimSFs) muIsoMax = muIsoEff_ *(1 + 0.01 * getMuonIsoSF(Electrons->at(0).Pt(), Electrons->at(0).Eta(), Electrons_MT2Activity->at(0)));
      if(useSFs) muIsoMax = muIsoEff_ *(1 + GetSFUnc(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014));
      if(muIsoMax > 1) muIsoMax = 1;
      muIsoSysDown = w1 * (w2 * (w3a + 1-muIsoMax*muRecoEff_*muAccEff_) + w4) - wGes;
      double muIsoMin = muIsoEff_ *(1 - 0.01 * MuIsoUncertaintyDown_);
      if(usePrelimSFs) muIsoMin = muIsoEff_ *(1 - 0.01 * getMuonIsoSF(Electrons->at(0).Pt(), Electrons->at(0).Eta(), Electrons_MT2Activity->at(0)));
      if(useSFs) muIsoMin = muIsoEff_ *(1 - GetSFUnc(h_muIsoSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014));
      muIsoSysUp = w1 * (w2 * (w3a + 1-muIsoMin*muRecoEff_*muAccEff_) + w4) - wGes;

      double muRecoMax = muRecoEff_*(1 + 0.01 * MuRecoUncertaintyUp_);
      if(usePrelimSFs) muRecoMax = muRecoEff_ *(1 + 0.01 * getMuonIDSF(Electrons->at(0).Pt(), Electrons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) muRecoMax = muRecoEff_ *(1 + GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014));
      if(useSFs && doTrackingCorrection) muRecoMax = muRecoEff_ *(1 + GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014) + GetSFUnc(h_muTrkHighPtSF, Electrons->at(0).Eta(), 0.01));
      if(muRecoMax > 1) muRecoMax = 1;
      muRecoSysDown = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoMax*muAccEff_) + w4) - wGes;
      double muRecoMin = muRecoEff_*(1 - 0.01 * MuRecoUncertaintyDown_);
      if(usePrelimSFs) muRecoMin = muRecoEff_ *(1 - 0.01 * getMuonIDSF(Electrons->at(0).Pt(), Electrons->at(0).Eta()));
      if(useSFs && !doTrackingCorrection) muRecoMin = muRecoEff_ *(1 - GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014));
      if(useSFs && doTrackingCorrection) muRecoMin = muRecoEff_ *(1 - GetSFUnc(h_muIDSF, Electrons->at(0).Pt(), std::abs(Electrons->at(0).Eta()), 0.014) - GetSFUnc(h_muTrkHighPtSF, Electrons->at(0).Eta(), 0.01));
      muRecoSysUp = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoMin*muAccEff_) + w4) - wGes;

      double muAccMax, muAccMin;       
      if(useFlatAccUnc){
        if(MHT>500) muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_HighMHT_);
        else muAccMax = muAccEff_ *(1 + 0.01 * MuAccUncertaintyUp_LowMHT_);
      }else{
        muAccMax = muAccEff_ *(1 + GetAccSF(h_muAccPDF_up, NJets, HT, MHT));
      }
      if(muAccMax > 1) muAccMax = 1;
      muAccSysDown = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*muAccMax) + w4) - wGes;
      if(useFlatAccUnc){
        if(MHT>500) muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_HighMHT_);
        else muAccMin = muAccEff_ *(1 - 0.01 * MuAccUncertaintyDown_LowMHT_);
      }else{
        muAccMin = muAccEff_ *(1 - GetAccSF(h_muAccPDF_down, NJets, HT, MHT));
      }
      muAccSysUp = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*muAccMin) + w4) - wGes;
      
      double muAccQsquareMax, muAccQsquareMin;       
      if(useFlatAccUnc){
        muAccQsquareMax = muAccEff_ *(1 + 0.01 * MuAccQsquareUncertaintyUp_);
      }else{
        muAccQsquareMax = muAccEff_ *(1 + GetAccSF(h_muAccQ2_up, NJets, HT, MHT));
      }
      if(muAccQsquareMax > 1) muAccQsquareMax = 1;
      muAccQsquareSysDown =w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*muAccQsquareMax) + w4) - wGes;
      if(useFlatAccUnc){
        muAccQsquareMin = muAccEff_ *(1 - 0.01 * MuAccQsquareUncertaintyDown_);
      }else{
        muAccQsquareMin = muAccEff_ *(1 - GetAccSF(h_muAccQ2_down, NJets, HT, MHT));
      }
      muAccQsquareSysUp = w1 * (w2 * (w3a + 1-muIsoEff_*muRecoEff_*muAccQsquareMin) + w4) - wGes;
      
      totalStatUp = sqrt(muIsoTrackStatUp*muIsoTrackStatUp+elecIsoTrackStatUp*elecIsoTrackStatUp+pionIsoTrackStatUp*pionIsoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
      totalSysUp = sqrt(muIsoTrackSysUp*muIsoTrackSysUp+elecIsoTrackSysUp*elecIsoTrackSysUp+pionIsoTrackSysUp*pionIsoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp);
      totalUncUp = sqrt(totalStatUp*totalStatUp+totalSysUp*totalSysUp);

      totalStatDown = -sqrt(muIsoTrackStatDown*muIsoTrackStatDown+elecIsoTrackStatDown*elecIsoTrackStatDown+pionIsoTrackStatDown*pionIsoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);
      totalSysDown = -sqrt(muIsoTrackSysDown*muIsoTrackSysDown+elecIsoTrackSysDown*elecIsoTrackSysDown+pionIsoTrackSysDown*pionIsoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown);
      totalUncDown = -sqrt(totalStatDown*totalStatDown+totalSysDown*totalSysDown);

/*
      // Calculate weights if they do depend on the number of BTags:
      // BTags == 0
      if(NJets<6.5){
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }

      if(NJets<6.5){
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags0_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags0_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);
      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 0, useAsymmErrors);      
      elecDiLepEffMTWAppliedEff_ = elecDiLepEffMTWAppliedEffVec_.eff;
      elecDiLepContributionMTWAppliedEff_ = elecDiLepContributionMTWAppliedEffVec_.eff;
*/
      elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      elecMTWEff_ = elecMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,0), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * elecPurityCorrection_ * 1/elecMTWEff_;
      w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
      w3a = 1-elecIsoEff_*elecRecoEff_*elecAccEff_;
      w3b = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * elecPurityCorrection_ * 1/elecMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags == 1
      if(NJets<6.5){
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags1_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags1_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);
      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 1, useAsymmErrors);      
      elecDiLepEffMTWAppliedEff_ = elecDiLepEffMTWAppliedEffVec_.eff;
      elecDiLepContributionMTWAppliedEff_ = elecDiLepContributionMTWAppliedEffVec_.eff;
*/
      elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      elecMTWEff_ = elecMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,1), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * elecPurityCorrection_ * 1/elecMTWEff_;
      w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
      w3a = 1-elecIsoEff_*elecRecoEff_*elecAccEff_;
      w3b = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * elecPurityCorrection_ * 1/elecMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags == 2
      if(NJets<6.5){
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags2_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags2_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

      muAccEff_ = muAccEffVec_.eff;
      elecAccEff_ = elecAccEffVec_.eff;
/*
      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);
      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 2, useAsymmErrors);      
      elecDiLepEffMTWAppliedEff_ = elecDiLepEffMTWAppliedEffVec_.eff;
      elecDiLepContributionMTWAppliedEff_ = elecDiLepContributionMTWAppliedEffVec_.eff;
*/
      elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      elecMTWEff_ = elecMTWEffVec_.eff;
     
      expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);
      expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,2), useAsymmErrors);

      //for compatibility
      expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
      expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
      expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
      expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

      w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * elecPurityCorrection_ * 1/elecMTWEff_;
      w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
      w3a = 1-elecIsoEff_*elecRecoEff_*elecAccEff_;
      w3b = 1-muIsoEff_*muRecoEff_*muAccEff_;
      w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
      totalWeight_BTags_noIsoTrack_.push_back(Weight * elecPurityCorrection_ * 1/elecMTWEff_ * (w2 * (w3a+w3b) + w4));
/*
      // BTags >= 3
      if(NJets<6.5){
        if(NJets<2.5) muAccEffVec_ = MuAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) muAccEffVec_ = MuAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) muAccEffVec_ = MuAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) muAccEffVec_ = MuAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //muAccEffVec_ = MuAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else muAccEffVec_ = MuAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) muAccEffVec_ = MuAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else muAccEffVec_ = MuAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      } 

      if(NJets<6.5){
        if(NJets<2.5) elecAccEffVec_ = ElecAccHTMHT_NJets2_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<3.5) elecAccEffVec_ = ElecAccHTMHT_NJets3_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if(NJets<4.5) elecAccEffVec_ = ElecAccHTMHT_NJets4_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else if (NJets < 5.5) elecAccEffVec_ = ElecAccHTMHT_NJets5_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets6_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
      else{
        //elecAccEffVec_ = ElecAccHTMHT_NJets7Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_BTags3Inf_->GetEff(HT,MHT, useAsymmErrors);
        //else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_BTags1Inf_->GetEff(HT,MHT, useAsymmErrors);
        //if(NJets<8.5) elecAccEffVec_ = ElecAccHTMHT_NJets78_->GetEff(HT,MHT, useAsymmErrors);
        else elecAccEffVec_ = ElecAccHTMHT_NJets9Inf_->GetEff(HT,MHT, useAsymmErrors);
      }
*/
      if(NJets > 2){
	      muAccEffVec_ = MuAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
	      elecAccEffVec_ = ElecAccSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

	      muAccEff_ = muAccEffVec_.eff;
	      elecAccEff_ = elecAccEffVec_.eff;
/*
	      elecDiLepContributionMTWAppliedEffVec_ = ElecDiLepContributionMTWAppliedNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);
	      elecDiLepEffMTWAppliedEffVec_ = ElecDiLepEffMTWAppliedNJetsBTags_->GetEff(NJets, 3, useAsymmErrors);      
      	elecDiLepEffMTWAppliedEff_ = elecDiLepEffMTWAppliedEffVec_.eff;
        elecDiLepContributionMTWAppliedEff_ = elecDiLepContributionMTWAppliedEffVec_.eff;
*/
        elecMTWEffVec_ = ElecMTWSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        elecMTWEff_ = elecMTWEffVec_.eff;
     
        expectationReductionIsoTrackEffVec_ = IsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionMuIsoTrackEffVec_ = MuIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionElecIsoTrackEffVec_ = ElecIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);
        expectationReductionPionIsoTrackEffVec_ = PionIsoTrackVetoSearchBins_->GetEff(SearchBinsEff_->GetBinNumber(HT,MHT,NJets,3), useAsymmErrors);

        //for compatibility
        expectationReductionIsoTrackEff_ = expectationReductionIsoTrackEffVec_.eff;
        expectationReductionMuIsoTrackEff_ = expectationReductionMuIsoTrackEffVec_.eff;
        expectationReductionElecIsoTrackEff_ = expectationReductionElecIsoTrackEffVec_.eff;
        expectationReductionPionIsoTrackEff_ = expectationReductionPionIsoTrackEffVec_.eff;

        w1 = Weight * (1 - (expectationReductionMuIsoTrackEff_ + expectationReductionElecIsoTrackEff_ + expectationReductionPionIsoTrackEff_)) * elecPurityCorrection_ * 1/elecMTWEff_;
	      w2 = elecDiLepContributionMTWAppliedEff_ * 1/(elecIsoEff_*elecRecoEff_*elecAccEff_);
	      w3a = 1-elecIsoEff_*elecRecoEff_*elecAccEff_;
	      w3b = 1-muIsoEff_*muRecoEff_*muAccEff_;
        w4 = (1-elecDiLepContributionMTWAppliedEff_) * (1-elecDiLepEffMTWAppliedEff_)/elecDiLepEffMTWAppliedEff_;
	      totalWeight_BTags_.push_back(w1 * (w2 * (w3a+w3b) + w4));
	      totalWeight_BTags_noIsoTrack_.push_back(Weight * elecPurityCorrection_ * 1/elecMTWEff_ * (w2 * (w3a+w3b) + w4));
  	  }

    }

    WeightTrackingCorr = Weight * isoSF * recoSF * trackingSF;

    if(fillEventSeperateBTags){
      for(int i = 0; i < (NJets == 2 ? 3 : 4); i++){
        Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,i);
        BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,i);
        BTags = i;

        double storeWeight = Weight;
        WeightCorr = Weight * bTagProb.at(i) * isoSF * recoSF * trackingSF;
        Weight *= bTagProb.at(i);
        if(topPTreweight && topPtSF > 0) WeightCorr *= topPtSF;

        tPrediction_->Fill();

        Weight = storeWeight;
      }
      return kTRUE;
    }

    // Simple bTag corrections don't work that way
    //WeightCorr = Weight_bTagCorr * isoSF * recoSF * trackingSF;
    WeightCorr = 0;
    if(topPTreweight && topPtSF > 0) WeightCorr *= topPtSF;

  tPrediction_->Fill();
  return kTRUE;
}

void Prediction::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  //std::cout<<"--- QCD binning ---"<<std::endl;
  //SearchBinsQCD_->PrintUsed();

  std::cout<<"--- Search bins ---"<<std::endl;
  SearchBins_->PrintUsed();  
}

void Prediction::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.


  tPrediction_ = dynamic_cast<TTree*>(GetOutputList()->FindObject("LostLeptonPrediction"));
  TFile *outPutFile = new TFile(fileName,"RECREATE"); ;
  outPutFile->cd();
  tPrediction_->Write();

  outPutFile->cd();
  outPutFile->mkdir("MeanWeight");
  TDirectory *dEfficiencies = (TDirectory*)outPutFile->Get("MeanWeight");
  dEfficiencies->cd();
  MuMeanWeight_->Write();
  ElecMeanWeight_->Write();
  CombinedMeanWeight_->Write();

  outPutFile->cd();
  outPutFile->mkdir("WeightPerBin");
  TDirectory *dEfficienciesPerBin = (TDirectory*)outPutFile->Get("WeightPerBin");
  dEfficienciesPerBin->cd();
  for(int b = 0; b <108; b++){
    MuWeightPerBin_[b]->Write();
    ElecWeightPerBin_[b]->Write();
    CombinedWeightPerBin_[b]->Write();
  }

  outPutFile->Close();

  cout << "Note: mT cut not yet applied " << endl;
  cout << "Saved output to " << fileName << endl;
  
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

  // DeltaR/RelPt
  MuonsDeltaRJet.clear();
  MuonsRelPTJet.clear(); 
  ElectronsDeltaRJet.clear();
  ElectronsRelPTJet.clear();

  MuonsPTW.clear();
  MuonsPt_=0.;
  MuonsEta_=0.;
  //  MuonsCDTT.clear();
  ElectronsPTW.clear();
  ElectronsPt_=0.;
  ElectronsEta_=0.;
  //  ElectronsCDTT.clear();

  ptw_bins.clear();

  totalWeight_BTags_.clear();
  totalWeight_BTags_noIsoTrack_.clear();
  topPt.clear();
}

bool Prediction::FiltersPass()
{
  bool result=true;
  if(useFilterData){
    //if(useFilterList){
    //  bool CSCTightHaloFilterUpdate = evtListFilter->CheckEvent(RunNum,LumiBlockNum,EvtNum);
    //  if(!CSCTightHaloFilterUpdate) result=false;
    //} 
    // 2015 only if(CSCTightHaloFilter!=1) result=false;
    // 2015 only if(!eeBadSc4Filter) result=false;
    if(HBHENoiseFilter!=1) result=false;
    if(HBHEIsoNoiseFilter!=1) result=false;
    if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
    if(eeBadScFilter!=1) result=false;

    if(runOnData){
      if(!BadChargedCandidateFilter) result=false;
      if(!BadPFMuonFilter) result=false;
      if(globalTightHalo2016Filter!=1) result=false;
    }    
  }
  if(NVtx<=0) result=false;

  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;

  for(unsigned j = 0; j < Jets->size(); j++){
    if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
    if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
      //std::cout<<"found bad muon jet"<<std::endl;
      result=false;
    }
  }

  // Do not apply on fastSim samples!
  if(!runOnSignalMC) if(!JetID) result=false;
  return result;
}


std::pair <double,double> Prediction::minDeltaRLepJet(double lepPt, double lepEta, double lepPhi)
{
  double relPt = 9999;
  double deltaRmin = 9999;

  for (int i=0; i < NJets ; i++)
    {
      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) > deltaRmin) continue;

      if(deltaR(lepEta,lepPhi,Jets->at(i).Eta(),Jets->at(i).Phi()) < jetCone_)
  {
    if(lepPt > Jets->at(i).Pt()){
      if(lepPt < 1.2 * Jets->at(i).Pt()) continue;
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

std::vector<int> Prediction::GetPTWBin(int Bin, double ptw, double ht) {

  std::vector<int> ptw_bins;
  if (Bin%6>0&&Bin%6<4) ptw_bins.push_back(Bin);
  if (ptw > 500 && ptw < 750) {
    if (ht>500&&ht<1200) ptw_bins.push_back(6*((Bin-1)/6)+4);
    else if (ht>1200) ptw_bins.push_back(6*((Bin-1)/6)+5);
  } else if (ptw > 750) {
    if (ht>800) ptw_bins.push_back(6*((Bin-1)/6)+6);
    if (ht>500&&ht<1200) ptw_bins.push_back(6*((Bin-1)/6)+4);
    else if (ht>1200) ptw_bins.push_back(6*((Bin-1)/6)+5);
  }

  return ptw_bins;
  
}

