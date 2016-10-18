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
  MuonPurityOldMHTNJet_ = new TH2Eff("MuonPurityOldMHTNJet","MuonPurityOldMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  
  // electron
  //1D
  ElecPurityOldBTag_ = new TH1Eff("ElecPurityOldBTag1D","ElecPurityOldBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityOldNJets_ = new TH1Eff("ElecPurityOldNJets1D","ElecPurityOldNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityOldHT_ = new TH1Eff("ElecPurityOldHT1D","ElecPurityOldHT1D",oneDHT_-1,OneDHT_);
  ElecPurityOldMHT_ = new TH1Eff("ElecPurityOldMHT1D","ElecPurityOldMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityOldMHTNJet_ = new TH2Eff("ElecPurityOldMHTNJet","ElecPurityOldMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  
  // purity x-check

  // muon
  // 1D
  MuPurityBTag_ = new TH1Eff("MuPurityBTag1D","MuPurityBTag1D",oneDBJets_-1,OneDBJets_);
  MuPurityNJets_ = new TH1Eff("MuPurityNJets1D","MuPurityNJets1D",oneDNJets_-1,OneDNJets_);
  MuPurityHT_ = new TH1Eff("MuPurityHT1D","MuPurityHT1D",oneDHT_-1,OneDHT_);
  MuPurityMHT_ = new TH1Eff("MuPurityMHT1D","MuPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  MuonPurityMHTNJet_ = new TH2Eff("MuonPurityMHTNJet","MuonPurityMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  
  // electron
  //1D
  ElecPurityBTag_ = new TH1Eff("ElecPurityBTag1D","ElecPurityBTag1D",oneDBJets_-1,OneDBJets_);
  ElecPurityNJets_ = new TH1Eff("ElecPurityNJets1D","ElecPurityNJets1D",oneDNJets_-1,OneDNJets_);
  ElecPurityHT_ = new TH1Eff("ElecPurityHT1D","ElecPurityHT1D",oneDHT_-1,OneDHT_);
  ElecPurityMHT_ = new TH1Eff("ElecPurityMHT1D","ElecPurityMHT1D",oneDMHT_-1,OneDMHT_);
  //2D
  ElecPurityMHTNJet_ = new TH2Eff("ElecPurityMHTNJet","ElecPurityMHTNJet",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);
  
  
  // acceptance
  //muon
  //1D
  MuAccBTag_ = new TH1Eff("MuAccBTag1D","MuAccBTag1D",oneDBJets_-1,OneDBJets_);
  MuAccNJets_ = new TH1Eff("MuAccNJets1D","MuAccNJets1D",oneDNJets_-1,OneDNJets_);
  MuAccHT_ = new TH1Eff("MuAccHT1D","MuAccHT1D",oneDHT_-1,OneDHT_);
  MuAccMHT_ = new TH1Eff("MuAccMHT1D","MuAccMHT1D",oneDMHT_-1,OneDMHT_);
  MuAccDTT_ = new TH1Eff("MuAccDTT1D","MuAccDTT1D",oneDDTT_-1,OneDDTT_);
  //2D
  MuAccHTNJets_ = new TH2Eff("MuAccHTNJets","MuAccHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJets_ = new TH2Eff("MuAccMHTNJets","MuAccMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccHTMHT_ = new TH2Eff("MuAccHTMHT","MuAccHTMHT",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccBTagNJets_ = new TH2Eff("MuAccBTagNJets","MuAccBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJetsB0_ = new TH2Eff("MuAccMHTNJetsB0","MuAccMHTNJetsB0",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccMHTNJetsB1_Inf_ = new TH2Eff("MuAccMHTNJetsB1_Inf","MuAccMHTNJetsB1_Inf",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuAccHTMHT_NJetsLow_ = new TH2Eff("MuAccHTMHT_NJetsLow","MuAccHTMHT_NJetsLow",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccHTMHT_NJets2_ = new TH2Eff("MuAccHTMHT_NJets2","MuAccHTMHT_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets3_ = new TH2Eff("MuAccHTMHT_NJets3","MuAccHTMHT_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_ = new TH2Eff("MuAccHTMHT_NJets4","MuAccHTMHT_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_ = new TH2Eff("MuAccHTMHT_NJets5","MuAccHTMHT_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_ = new TH2Eff("MuAccHTMHT_NJets6","MuAccHTMHT_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_ = new TH2Eff("MuAccHTMHT_NJets78","MuAccHTMHT_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets9Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf","MuAccHTMHT_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJetsHigh_ = new TH2Eff("MuAccHTMHT_NJetsHigh"," MuAccHTMHT_NJetsHigh",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccHTMHTB0_ = new TH2Eff("MuAccHTMHTB0","MuAccHTMHTB0",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  MuAccHTMHTB1_Inf_ = new TH2Eff("MuAccHTMHTB1_Inf","MuAccHTMHTB1_Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);

  MuAccHTMHT_NJets2_BTags0_ = new TH2Eff("MuAccHTMHT_NJets2_BTags0","MuAccHTMHT_NJets2_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets3_BTags0_ = new TH2Eff("MuAccHTMHT_NJets3_BTags0","MuAccHTMHT_NJets3_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_BTags0_ = new TH2Eff("MuAccHTMHT_NJets4_BTags0","MuAccHTMHT_NJets4_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_BTags0_ = new TH2Eff("MuAccHTMHT_NJets5_BTags0","MuAccHTMHT_NJets5_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_BTags0_ = new TH2Eff("MuAccHTMHT_NJets6_BTags0","MuAccHTMHT_NJets6_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_BTags0_ = new TH2Eff("MuAccHTMHT_NJets78_BTags0","MuAccHTMHT_NJets78_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags0","MuAccHTMHT_NJets9Inf_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJetsHigh_BTags0_ = new TH2Eff("MuAccHTMHT_NJetsHigh_BTags0","MuAccHTMHT_NJetsHigh_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  MuAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1Inf","MuAccHTMHT_NJets2_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1Inf","MuAccHTMHT_NJets3_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1Inf","MuAccHTMHT_NJets4_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1Inf","MuAccHTMHT_NJets5_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1Inf","MuAccHTMHT_NJets6_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1Inf","MuAccHTMHT_NJets78_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1Inf","MuAccHTMHT_NJets9Inf_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("MuAccHTMHT_NJetsHigh_BTags1Inf","MuAccHTMHT_NJetsHigh_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  MuAccHTMHT_NJets2_BTags1_ = new TH2Eff("MuAccHTMHT_NJets2_BTags1","MuAccHTMHT_NJets2_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets3_BTags1_ = new TH2Eff("MuAccHTMHT_NJets3_BTags1","MuAccHTMHT_NJets3_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_BTags1_ = new TH2Eff("MuAccHTMHT_NJets4_BTags1","MuAccHTMHT_NJets4_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_BTags1_ = new TH2Eff("MuAccHTMHT_NJets5_BTags1","MuAccHTMHT_NJets5_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_BTags1_ = new TH2Eff("MuAccHTMHT_NJets6_BTags1","MuAccHTMHT_NJets6_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_BTags1_ = new TH2Eff("MuAccHTMHT_NJets78_BTags1","MuAccHTMHT_NJets78_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags1","MuAccHTMHT_NJets9Inf_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJetsHigh_BTags1_ = new TH2Eff("MuAccHTMHT_NJetsHigh_BTags1","MuAccHTMHT_NJetsHigh_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  MuAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets2_BTags2Inf","MuAccHTMHT_NJets2_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets3_BTags2Inf","MuAccHTMHT_NJets3_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets4_BTags2Inf","MuAccHTMHT_NJets4_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets5_BTags2Inf","MuAccHTMHT_NJets5_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets6_BTags2Inf","MuAccHTMHT_NJets6_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  MuAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets78_BTags2Inf","MuAccHTMHT_NJets78_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJets9Inf_BTags2Inf","MuAccHTMHT_NJets9Inf_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuAccHTMHT_NJetsHigh_BTags2Inf_ = new TH2Eff("MuAccHTMHT_NJetsHigh_BTags2Inf","MuAccHTMHT_NJetsHigh_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  
  //elec
  //1D
  ElecAccBTag_ = new TH1Eff("ElecAccBTag1D","ElecAccBTag1D",oneDBJets_-1,OneDBJets_);
  ElecAccNJets_ = new TH1Eff("ElecAccNJets1D","ElecAccNJets1D",oneDNJets_-1,OneDNJets_);
  ElecAccHT_ = new TH1Eff("ElecAccHT1D","ElecAccHT1D",oneDHT_-1,OneDHT_);
  ElecAccMHT_ = new TH1Eff("ElecAccMHT1D","ElecAccMHT1D",oneDMHT_-1,OneDMHT_);
  ElecAccDTT_ = new TH1Eff("ElecAccDTT1D","ElecAccDTT1D",oneDDTT_-1,OneDDTT_);
  //2D
  ElecAccHTNJets_ = new TH2Eff("ElecAccHTNJets","ElecAccHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJets_ = new TH2Eff("ElecAccMHTNJets","ElecAccMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccHTMHT_ = new TH2Eff("ElecAccHTMHT","ElecAccHTMHT",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccBTagNJets_ = new TH2Eff("ElecAccBTagNJets","ElecAccBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJetsB0_ = new TH2Eff("ElecAccMHTNJetsB0","ElecAccMHTNJetsB0",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccMHTNJetsB1_Inf_ = new TH2Eff("ElecAccMHTNJetsB1_Inf","ElecAccMHTNJetsB1_Inf",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecAccHTMHT_NJetsLow_ = new TH2Eff("ElecAccHTMHT_NJetsLow","ElecAccHTMHT_NJetsLow",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccHTMHT_NJets2_ = new TH2Eff("ElecAccHTMHT_NJets2","ElecAccHTMHT_NJets2",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets3_ = new TH2Eff("ElecAccHTMHT_NJets3","ElecAccHTMHT_NJets3",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets4_ = new TH2Eff("ElecAccHTMHT_NJets4","ElecAccHTMHT_NJets4",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets5_ = new TH2Eff("ElecAccHTMHT_NJets5","ElecAccHTMHT_NJets5",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets6_ = new TH2Eff("ElecAccHTMHT_NJets6","ElecAccHTMHT_NJets6",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets78_ = new TH2Eff("ElecAccHTMHT_NJets78","ElecAccHTMHT_NJets78",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets9Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf","ElecAccHTMHT_NJets9Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJetsHigh_ = new TH2Eff("ElecAccHTMHT_NJetsHigh"," ElecAccHTMHT_NJetsHigh",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccHTMHTB0_ = new TH2Eff("ElecAccHTMHTB0","ElecAccHTMHTB0",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);
  ElecAccHTMHTB1_Inf_ = new TH2Eff("ElecAccHTMHTB1_Inf","ElecAccHTMHTB1_Inf",twoDHT_-1,TwoDHT_, twoDMHT_-1,TwoDMHT_);

  ElecAccHTMHT_NJets2_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags0","ElecAccHTMHT_NJets2_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets3_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags0","ElecAccHTMHT_NJets3_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets4_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags0","ElecAccHTMHT_NJets4_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets5_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags0","ElecAccHTMHT_NJets5_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets6_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags0","ElecAccHTMHT_NJets6_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets78_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags0","ElecAccHTMHT_NJets78_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets9Inf_BTags0_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags0","ElecAccHTMHT_NJets9Inf_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJetsHigh_BTags0_ = new TH2Eff("ElecAccHTMHT_NJetsHigh_BTags0","ElecAccHTMHT_NJetsHigh_BTags0",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  ElecAccHTMHT_NJets2_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1Inf","ElecAccHTMHT_NJets2_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets3_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1Inf","ElecAccHTMHT_NJets3_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets4_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1Inf","ElecAccHTMHT_NJets4_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets5_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1Inf","ElecAccHTMHT_NJets5_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets6_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1Inf","ElecAccHTMHT_NJets6_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets78_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1Inf","ElecAccHTMHT_NJets78_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets9Inf_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1Inf","ElecAccHTMHT_NJets9Inf_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("ElecAccHTMHT_NJetsHigh_BTags1Inf","ElecAccHTMHT_NJetsHigh_BTags1Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  ElecAccHTMHT_NJets2_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags1","ElecAccHTMHT_NJets2_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets3_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags1","ElecAccHTMHT_NJets3_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets4_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags1","ElecAccHTMHT_NJets4_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets5_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags1","ElecAccHTMHT_NJets5_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets6_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags1","ElecAccHTMHT_NJets6_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets78_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags1","ElecAccHTMHT_NJets78_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets9Inf_BTags1_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags1","ElecAccHTMHT_NJets9Inf_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJetsHigh_BTags1_ = new TH2Eff("ElecAccHTMHT_NJetsHigh_BTags1","ElecAccHTMHT_NJetsHigh_BTags1",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  ElecAccHTMHT_NJets2_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets2_BTags2Inf","ElecAccHTMHT_NJets2_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets3_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets3_BTags2Inf","ElecAccHTMHT_NJets3_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets4_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets4_BTags2Inf","ElecAccHTMHT_NJets4_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets5_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets5_BTags2Inf","ElecAccHTMHT_NJets5_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets6_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets6_BTags2Inf","ElecAccHTMHT_NJets6_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_fine_-1,ThreeDMHT_fine_);
  ElecAccHTMHT_NJets78_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets78_BTags2Inf","ElecAccHTMHT_NJets78_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJets9Inf_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJets9Inf_BTags2Inf","ElecAccHTMHT_NJets9Inf_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecAccHTMHT_NJetsHigh_BTags2Inf_ = new TH2Eff("ElecAccHTMHT_NJetsHigh_BTags2Inf","ElecAccHTMHT_NJetsHigh_BTags2Inf",threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

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

  MuMTWHTNJets_ = new TH2Eff("MuMTWHTNJets","MuMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  MuMTWMHTNJets_ = new TH2Eff("MuMTWMHTNJets","MuMTWMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  MuMTWHTMHT_ = new TH2Eff("MuMTWHTMHT","MuMTWHTMHT",twoDHT_-1,TwoDHT_,twoDMHT_-1,TwoDMHT_);
  
  //electron
  //1D
  ElecMTWBTag_ = new TH1Eff("ElecMTWBTag1D","ElecMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecMTWNJets_ = new TH1Eff("ElecMTWNJets1D","ElecMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecMTWHT_ = new TH1Eff("ElecMTWHT1D","ElecMTWHT1D",oneDHT_-1,OneDHT_);
  ElecMTWMHT_ = new TH1Eff("ElecMTWMHT1D","ElecMTWMHT1D",oneDMHT_-1,OneDMHT_);

  ElecMTWHTNJets_ = new TH2Eff("ElecMTWHTNJets","ElecMTWHTNJets",twoDHT_-1,TwoDHT_, twoDNJets_-1, TwoDNJets_);
  ElecMTWMHTNJets_ = new TH2Eff("ElecMTWMHTNJets","ElecMTWMHTNJets",twoDMHT_-1,TwoDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecMTWHTMHT_ = new TH2Eff("ElecMTWHTMHT","ElecMTWHTMHT",twoDHT_-1,TwoDHT_,twoDMHT_-1,TwoDMHT_);

 
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
  MuDiLepContributionMTWMHTNJets_ = new TH2Eff("MuDiLepContributionMTWMHTNJets","MuDiLepContributionMTWMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);

  
  //electron
  //1D
  ElecDiLepContributionMTWBTag_ = new TH1Eff("ElecDiLepContributionMTWBTag1D","ElecDiLepContributionMTWBTag1D",oneDBJets_-1,OneDBJets_);
  ElecDiLepContributionMTWNJets_ = new TH1Eff("ElecDiLepContributionMTWNJets1D","ElecDiLepContributionMTWNJets1D",oneDNJets_-1,OneDNJets_);
  ElecDiLepContributionMTWHT_ = new TH1Eff("ElecDiLepContributionMTWHT1D","ElecDiLepContributionMTWHT1D",oneDHT_-1,OneDHT_);
  ElecDiLepContributionMTWMHT_ = new TH1Eff("ElecDiLepContributionMTWMHT1D","ElecDiLepContributionMTWMHT1D",oneDMHT_-1,OneDMHT_);
  ElecDiLepContributionMTWMHTNJets_ = new TH2Eff("ElecDiLepContributionMTWMHTNJets","ElecDiLepContributionMTWMHTNJets",twoDMHT_-1,TwoDMHT_,twoDNJets_-1,TwoDNJets_);

  
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
  MuIsoActivityPT_ = new TH2Eff("MuIsoActivityPT","MuIsoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoActivityPT_ = new TH2Eff("ElecIsoActivityPT","ElecIsoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuRecoActivityPT_ = new TH2Eff("MuRecoActivityPT","MuRecoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecRecoActivityPT_ = new TH2Eff("ElecRecoActivityPT","ElecRecoActivityPT", twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuRecoPTEta_ = new TH2Eff("MuRecoPTEta","MuRecoPTEta", twoDPT_-1,TwoDPT_, twoDEta_-1,TwoDEta_);
  ElecRecoPTEta_ = new TH2Eff("ElecRecoPTEta","ElecRecoPTEta", twoDPT_-1,TwoDPT_, twoDEta_-1,TwoDEta_);
  
  // mtw 2d
  MuMTWPTActivity_ = new TH2Eff("MuMTWPTActivity","MuMTWPTActivity",twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecMTWPTActivity_ = new TH2Eff("ElecMTWPTActivity","ElecMTWPTActivity",twoDActivity_-1,TwoDActivity_,twoDPT_-1,TwoDPT_);
    
  //1D
  ExpectationReductionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionIsoTrackBTagEff","ExpectationReductionIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionIsoTrackNJetsEff","ExpectationReductionIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionIsoTrackHTEff","ExpectationReductionIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionIsoTrackMHTEff","ExpectationReductionIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionIsoTrackPTEff","ExpectationReductionIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionIsoTrackActivityEff","ExpectationReductionIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  IsoTrackReductionHTNJets_ = new TH2Eff("IsoTrackReductionHTNJets","IsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsVeryLow","IsoTrackReductionHTMHT_NJetsVeryLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow","IsoTrackReductionHTMHT_NJetsLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets2_ = new TH2Eff("IsoTrackReductionHTMHT_NJets2","IsoTrackReductionHTMHT_NJets2", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets3_ = new TH2Eff("IsoTrackReductionHTMHT_NJets3","IsoTrackReductionHTMHT_NJets3", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets4_ = new TH2Eff("IsoTrackReductionHTMHT_NJets4","IsoTrackReductionHTMHT_NJets4", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets5_ = new TH2Eff("IsoTrackReductionHTMHT_NJets5","IsoTrackReductionHTMHT_NJets5", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJets6_ = new TH2Eff("IsoTrackReductionHTMHT_NJets6","IsoTrackReductionHTMHT_NJets6", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsHigh","IsoTrackReductionHTMHT_NJetsHigh", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionMHTNJets_ = new TH2Eff("IsoTrackReductionMHTNJets","IsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionBTagNJets_ = new TH2Eff("IsoTrackReductionBTagNJets","IsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  IsoTrackReductionPTActivity_ = new TH2Eff("IsoTrackReductionPTActivity","IsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPT_-1,TwoDPT_);

  IsoTrackReductionHTMHT_NJetsVeryLow_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsVeryLow_BTags0","IsoTrackReductionHTMHT_NJetsVeryLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsLow_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow_BTags0","IsoTrackReductionHTMHT_NJetsLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsHigh_BTags0_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsHigh_BTags0","IsoTrackReductionHTMHT_NJetsHigh_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf","IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsLow_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsLow_BTags1Inf","IsoTrackReductionHTMHT_NJetsLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf","IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  
  // muon iso track
  //1D
  ExpectationReductionMuIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionMuIsoTrackBTagEff","ExpectationReductionMuIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionMuIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionMuIsoTrackNJetsEff","ExpectationReductionMuIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionMuIsoTrackHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackHTEff","ExpectationReductionMuIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionMuIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackMHTEff","ExpectationReductionMuIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionMuIsoTrackPTEff_ = new TH1Eff("ExpectationReductionMuIsoTrackPTEff","ExpectationReductionMuIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionMuIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionMuIsoTrackActivityEff","ExpectationReductionMuIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  MuIsoTrackReductionHTNJets_ = new TH2Eff("MuIsoTrackReductionHTNJets","MuIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionMHTNJets_ = new TH2Eff("MuIsoTrackReductionMHTNJets","MuIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionBTagNJets_ = new TH2Eff("MuIsoTrackReductionBTagNJets","MuIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  MuIsoTrackReductionPTActivity_ = new TH2Eff("MuIsoTrackReductionPTActivity","MuIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPT_-1,TwoDPT_);
  MuIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsVeryLow","MuIsoTrackReductionHTMHT_NJetsVeryLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsLow","MuIsoTrackReductionHTMHT_NJetsLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsHigh","MuIsoTrackReductionHTMHT_NJetsHigh", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0","MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsLow_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsLow_BTags0","MuIsoTrackReductionHTMHT_NJetsLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsHigh_BTags0_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsHigh_BTags0","MuIsoTrackReductionHTMHT_NJetsHigh_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf","MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf","MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf","MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  // elec iso track
  //1D
  ExpectationReductionElecIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionElecIsoTrackBTagEff","ExpectationReductionElecIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionElecIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionElecIsoTrackNJetsEff","ExpectationReductionElecIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionElecIsoTrackHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackHTEff","ExpectationReductionElecIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionElecIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackMHTEff","ExpectationReductionElecIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionElecIsoTrackPTEff_ = new TH1Eff("ExpectationReductionElecIsoTrackPTEff","ExpectationReductionElecIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionElecIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionElecIsoTrackActivityEff","ExpectationReductionElecIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  ElecIsoTrackReductionHTNJets_ = new TH2Eff("ElecIsoTrackReductionHTNJets","ElecIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionMHTNJets_ = new TH2Eff("ElecIsoTrackReductionMHTNJets","ElecIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionBTagNJets_ = new TH2Eff("ElecIsoTrackReductionBTagNJets","ElecIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  ElecIsoTrackReductionPTActivity_ = new TH2Eff("ElecIsoTrackReductionPTActivity","ElecIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPT_-1,TwoDPT_);
  ElecIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsVeryLow","ElecIsoTrackReductionHTMHT_NJetsVeryLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsLow","ElecIsoTrackReductionHTMHT_NJetsLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsHigh","ElecIsoTrackReductionHTMHT_NJetsHigh", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0","ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsLow_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsLow_BTags0","ElecIsoTrackReductionHTMHT_NJetsLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0","ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf","ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf","ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf","ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  // pion iso track
  //1D
  ExpectationReductionPionIsoTrackBTagEff_ = new TH1Eff("ExpectationReductionPionIsoTrackBTagEff","ExpectationReductionPionIsoTrackBTagEff",oneDBJets_-1,OneDBJets_);
  ExpectationReductionPionIsoTrackNJetsEff_ = new TH1Eff("ExpectationReductionPionIsoTrackNJetsEff","ExpectationReductionPionIsoTrackNJetsEff",oneDNJets_-1,OneDNJets_);
  ExpectationReductionPionIsoTrackHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackHTEff","ExpectationReductionPionIsoTrackHTEff",oneDHT_-1,OneDHT_);
  ExpectationReductionPionIsoTrackMHTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackMHTEff","ExpectationReductionPionIsoTrackMHTEff",oneDMHT_-1,OneDMHT_);
  ExpectationReductionPionIsoTrackPTEff_ = new TH1Eff("ExpectationReductionPionIsoTrackPTEff","ExpectationReductionPionIsoTrackPTEff",oneDPT_-1,OneDPT_);
  ExpectationReductionPionIsoTrackActivityEff_ = new TH1Eff("ExpectationReductionPionIsoTrackActivityEff","ExpectationReductionPionIsoTrackActivityEff",oneDActivity_-1,OneDActivity_);
  //2D
  PionIsoTrackReductionHTNJets_ = new TH2Eff("PionIsoTrackReductionHTNJets","PionIsoTrackReductionHTNJets",threeDHT_-1,ThreeDHT_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionMHTNJets_ = new TH2Eff("PionIsoTrackReductionMHTNJets","PionIsoTrackReductionMHTNJets",threeDMHT_-1,ThreeDMHT_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionBTagNJets_ = new TH2Eff("PionIsoTrackReductionBTagNJets","PionIsoTrackReductionBTagNJets",twoDBJets_-1,TwoDBJets_, twoDNJets_-1, TwoDNJets_);
  PionIsoTrackReductionPTActivity_ = new TH2Eff("PionIsoTrackReductionPTActivity","PionIsoTrackReductionPTActivity", twoDActivity_-1, TwoDActivity_,twoDPT_-1,TwoDPT_);
  PionIsoTrackReductionHTMHT_NJetsVeryLow_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsVeryLow","PionIsoTrackReductionHTMHT_NJetsVeryLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsLow_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsLow","PionIsoTrackReductionHTMHT_NJetsLow", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsHigh_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsHigh","PionIsoTrackReductionHTMHT_NJetsHigh", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

  PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0","PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsLow_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsLow_BTags0","PionIsoTrackReductionHTMHT_NJetsLow_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsHigh_BTags0_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsHigh_BTags0","PionIsoTrackReductionHTMHT_NJetsHigh_BTags0", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf","PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf","PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);
  PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_ = new TH2Eff("PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf","PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf", threeDHT_-1,ThreeDHT_, threeDMHT_-1,ThreeDMHT_);

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

  if(Bin > 900 && BinQCD > 900) return kTRUE;

  if(Weight<0) Weight*=-1;

  // Fill events 4 times if using bTag probabilities
  int nLoops = 4;
  if(!doBtagProbabilities){
    nLoops = 1;
  }else if(NJets < 3){
    nLoops = 3;
  }

  for(int i = 0; i < nLoops; i++){
      double WeightBTagProb;

        if(doBtagProbabilities){
          WeightBTagProb = Weight * bTagProb->at(i);
        }else{
          WeightBTagProb = Weight;
        }

  // purity
  // single muon control sample
  // x-check
  if(MuPurity==2){
      //1D
      MuPurityBTag_->Fill(BTags,WeightBTagProb,true);
      MuPurityNJets_->Fill(NJets,WeightBTagProb,true);
      MuPurityHT_->Fill(HT,WeightBTagProb,true);
      MuPurityMHT_->Fill(MHT,WeightBTagProb,true);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
  }else if(MuPurity==0){
      //1D
      MuPurityBTag_->Fill(BTags,WeightBTagProb,false);
      MuPurityNJets_->Fill(NJets,WeightBTagProb,false);
      MuPurityHT_->Fill(HT,WeightBTagProb,false);
      MuPurityMHT_->Fill(MHT,WeightBTagProb,false);
      //2D
      MuonPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
  }

  if(ElecPurity==2){
      //1D
      ElecPurityBTag_->Fill(BTags,WeightBTagProb,true);
      ElecPurityNJets_->Fill(NJets,WeightBTagProb,true);
      ElecPurityHT_->Fill(HT,WeightBTagProb,true);
      ElecPurityMHT_->Fill(MHT,WeightBTagProb,true);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
  }else if(ElecPurity==0){
      //1D
      ElecPurityBTag_->Fill(BTags,WeightBTagProb,false);
      ElecPurityNJets_->Fill(NJets,WeightBTagProb,false);
      ElecPurityHT_->Fill(HT,WeightBTagProb,false);
      ElecPurityMHT_->Fill(MHT,WeightBTagProb,false);
      //2D
      ElecPurityMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
  }

  if(MuonsNum==1 && ElectronsNum==0){
      //cout << "muon event" << endl;
      if(MuonsPromptMatched->at(0)==1){
          // cout << "PromptMatched" << endl;
          //1D
          MuPurityOldBTag_->Fill(BTags,WeightBTagProb,true);
          MuPurityOldNJets_->Fill(NJets,WeightBTagProb,true);
          MuPurityOldHT_->Fill(HT,WeightBTagProb,true);
          MuPurityOldMHT_->Fill(MHT,WeightBTagProb,true);
          MuPurityOldPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,true);
          MuPurityOldActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,true);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
      }
      if(MuonsPromptMatched->at(0)==0){
          //1D
          MuPurityOldBTag_->Fill(BTags,WeightBTagProb,false);
          MuPurityOldNJets_->Fill(NJets,WeightBTagProb,false);
          MuPurityOldHT_->Fill(HT,WeightBTagProb,false);
          MuPurityOldMHT_->Fill(MHT,WeightBTagProb,false);
          MuPurityOldPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,false);
          MuPurityOldActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,false);
          //2D
          MuonPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
      }
  }

  // single elec control sample
  if(MuonsNum==0 && ElectronsNum==1){
      if(ElectronsPromptMatched->at(0)==1){
          //1D
          ElecPurityOldBTag_->Fill(BTags,WeightBTagProb,true);
          ElecPurityOldNJets_->Fill(NJets,WeightBTagProb,true);
          ElecPurityOldHT_->Fill(HT,WeightBTagProb,true);
          ElecPurityOldMHT_->Fill(MHT,WeightBTagProb,true);
          ElecPurityOldPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,true);
          ElecPurityOldActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,true);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,true);
      }
      if(ElectronsPromptMatched->at(0)==0){
          //1D
          ElecPurityOldBTag_->Fill(BTags,WeightBTagProb,false);
          ElecPurityOldNJets_->Fill(NJets,WeightBTagProb,false);
          ElecPurityOldHT_->Fill(HT,WeightBTagProb,false);
          ElecPurityOldMHT_->Fill(MHT,WeightBTagProb,false);
          ElecPurityOldPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,false);
          ElecPurityOldActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,false);
          //2D
          ElecPurityOldMHTNJet_->Fill(MHT,NJets,WeightBTagProb,false);
      }
  }

  // acceptance
  // single muon control sample
  if(muAcc==2){
      //1D
      MuAccBTag_->Fill(BTags,WeightBTagProb,true);
      MuAccNJets_->Fill(NJets,WeightBTagProb,true);
      MuAccHT_->Fill(HT,WeightBTagProb,true);
      MuAccMHT_->Fill(MHT,WeightBTagProb,true);
      MuAccDTT_->Fill(cosDTT,WeightBTagProb,true);
      MuAccPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuAccActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
      MuAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      MuAccHTMHT_->Fill(HT,MHT,WeightBTagProb,true);
      MuAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,true);
          MuAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,true);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }
      
      if(NJets<6.5){
          MuAccHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          MuAccHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
        }
      }
  }

  if(muAcc==0){
      //1D
      MuAccBTag_->Fill(BTags,WeightBTagProb,false);
      MuAccNJets_->Fill(NJets,WeightBTagProb,false);
      MuAccHT_->Fill(HT,WeightBTagProb,false);
      MuAccMHT_->Fill(MHT,WeightBTagProb,false);
      MuAccDTT_->Fill(cosDTT,WeightBTagProb,false);
      MuAccPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuAccActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //2D
      MuAccHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      MuAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      MuAccHTMHT_->Fill(HT,MHT,WeightBTagProb,false);
      MuAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);

      if(BTags==0){
          MuAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,false);
          MuAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          MuAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,false);
          MuAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets<6.5){
          MuAccHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          MuAccHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 8.5) MuAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
        if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets > 1.5 && NJets < 2.5) MuAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) MuAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) MuAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) MuAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) MuAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) MuAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) MuAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) MuAccHTMHT_NJetsHigh_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
        }
      }
  }
  
  // single elecon control sample
  if(elecAcc==2){
      //1D
      ElecAccBTag_->Fill(BTags,WeightBTagProb,true);
      ElecAccNJets_->Fill(NJets,WeightBTagProb,true);
      ElecAccHT_->Fill(HT,WeightBTagProb,true);
      ElecAccMHT_->Fill(MHT,WeightBTagProb,true);
      ElecAccDTT_->Fill(cosDTT,WeightBTagProb,true);
      ElecAccPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecAccActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
      ElecAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      ElecAccHTMHT_->Fill(HT,MHT,WeightBTagProb,true);
      ElecAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,true);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,true);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
          ElecAccHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);
      }

        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,true);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
      }else{
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags1_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
          if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,true);
        }
      }
  }

  if(elecAcc==0){
      //1D
      ElecAccBTag_->Fill(BTags,WeightBTagProb,false);
      ElecAccNJets_->Fill(NJets,WeightBTagProb,false);
      ElecAccHT_->Fill(HT,WeightBTagProb,false);
      ElecAccMHT_->Fill(MHT,WeightBTagProb,false);
      ElecAccDTT_->Fill(cosDTT,WeightBTagProb,false);
      ElecAccPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecAccActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //2D
      ElecAccHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      ElecAccMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      ElecAccHTMHT_->Fill(HT,MHT,WeightBTagProb,false);
      ElecAccBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);

      if(BTags==0){
          ElecAccMHTNJetsB0_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecAccHTMHTB0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          ElecAccMHTNJetsB1_Inf_->Fill(MHT,NJets,WeightBTagProb,false);
          ElecAccHTMHTB1_Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets<6.5){
          ElecAccHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
          ElecAccHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags < 0.5){
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
        if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);

        if(BTags < 1.5){
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags1_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets > 1.5 && NJets < 2.5) ElecAccHTMHT_NJets2_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 2.5 && NJets < 3.5) ElecAccHTMHT_NJets3_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 3.5 && NJets < 4.5) ElecAccHTMHT_NJets4_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 4.5 && NJets < 5.5) ElecAccHTMHT_NJets5_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 5.5 && NJets < 6.5) ElecAccHTMHT_NJets6_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5 && NJets < 8.5) ElecAccHTMHT_NJets78_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 8.5) ElecAccHTMHT_NJets9Inf_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
          if(NJets > 6.5) ElecAccHTMHT_NJetsHigh_BTags2Inf_->Fill(HT,MHT,WeightBTagProb,false);
        }
      }
  }
  
  // reconstruction
  // single muon control sample
  if(muReco==2){
      //1D
      MuRecoBTag_->Fill(BTags,WeightBTagProb,true);
      MuRecoNJets_->Fill(NJets,WeightBTagProb,true);
      MuRecoHT_->Fill(HT,WeightBTagProb,true);
      MuRecoMHT_->Fill(MHT,WeightBTagProb,true);
      MuRecoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuRecoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,true);
      //MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      MuRecoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      //MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,true);
      MuRecoPTEta_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,true);
  }

  if(muReco==0){
      //1D
      MuRecoBTag_->Fill(BTags,WeightBTagProb,false);
      MuRecoNJets_->Fill(NJets,WeightBTagProb,false);
      MuRecoHT_->Fill(HT,WeightBTagProb,false);
      MuRecoMHT_->Fill(MHT,WeightBTagProb,false);
      MuRecoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuRecoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //MuRecoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,false);
      //MuRecoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      MuRecoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      //MuRecoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,false);
      MuRecoPTEta_->Fill(GenMuons->at(0).Pt(),std::abs(GenMuons->at(0).Eta()),WeightBTagProb,false);
  }
  
  // single elecon control sample
  if(elecReco==2){
      //1D
      ElecRecoBTag_->Fill(BTags,WeightBTagProb,true);
      ElecRecoNJets_->Fill(NJets,WeightBTagProb,true);
      ElecRecoHT_->Fill(HT,WeightBTagProb,true);
      ElecRecoMHT_->Fill(MHT,WeightBTagProb,true);
      ElecRecoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecRecoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,true);
      //ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      ElecRecoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      //ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,true);
      ElecRecoPTEta_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,true);
  }

  if(elecReco==0){
      //1D
      ElecRecoBTag_->Fill(BTags,WeightBTagProb,false);
      ElecRecoNJets_->Fill(NJets,WeightBTagProb,false);
      ElecRecoHT_->Fill(HT,WeightBTagProb,false);
      ElecRecoMHT_->Fill(MHT,WeightBTagProb,false);
      ElecRecoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecRecoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //ElecRecoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,false);
      //ElecRecoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      ElecRecoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      //ElecRecoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,false);
      ElecRecoPTEta_->Fill(GenElectrons->at(0).Pt(),std::abs(GenElectrons->at(0).Eta()),WeightBTagProb,false);
  }
  
  // isolation
  // single muon control sample
  if(muIso==2){
      //1D
      MuIsoBTag_->Fill(BTags,WeightBTagProb,true);
      MuIsoNJets_->Fill(NJets,WeightBTagProb,true);
      MuIsoHT_->Fill(HT,WeightBTagProb,true);
      MuIsoMHT_->Fill(MHT,WeightBTagProb,true);
      MuIsoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
      MuIsoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      //MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,true);
      //MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      MuIsoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
      //MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,true);
  }

  if(muIso==0){
      //1D
      MuIsoBTag_->Fill(BTags,WeightBTagProb,false);
      MuIsoNJets_->Fill(NJets,WeightBTagProb,false);
      MuIsoHT_->Fill(HT,WeightBTagProb,false);
      MuIsoMHT_->Fill(MHT,WeightBTagProb,false);
      MuIsoPT_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
      MuIsoActivity_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      //MuIsoRelPTJet_->Fill(GenMuRelPTJet->at(0),WeightBTagProb,false);
      //MuIsoDeltaRJet_->Fill(GenMuDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      MuIsoActivityPT_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      //MuIsoRelPTDeltaRJet_->Fill(GenMuRelPTJet->at(0),GenMuDeltaRJet->at(0),WeightBTagProb,false);
  }
  
  // single elecon control sample
  if(elecIso==2){
      //1D
      ElecIsoBTag_->Fill(BTags,WeightBTagProb,true);
      ElecIsoNJets_->Fill(NJets,WeightBTagProb,true);
      ElecIsoHT_->Fill(HT,WeightBTagProb,true);
      ElecIsoMHT_->Fill(MHT,WeightBTagProb,true);
      ElecIsoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
      ElecIsoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      //ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,true);
      //ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,true);
      //2D
      ElecIsoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
      //ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,true);
  }

  if(elecIso==0){
      //1D
      ElecIsoBTag_->Fill(BTags,WeightBTagProb,false);
      ElecIsoNJets_->Fill(NJets,WeightBTagProb,false);
      ElecIsoHT_->Fill(HT,WeightBTagProb,false);
      ElecIsoMHT_->Fill(MHT,WeightBTagProb,false);
      ElecIsoPT_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
      ElecIsoActivity_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      //ElecIsoRelPTJet_->Fill(GenElecRelPTJet->at(0),WeightBTagProb,false);
      //ElecIsoDeltaRJet_->Fill(GenElecDeltaRJet->at(0),WeightBTagProb,false);
      //2D
      ElecIsoActivityPT_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      //ElecIsoRelPTDeltaRJet_->Fill(GenElecRelPTJet->at(0),GenElecDeltaRJet->at(0),WeightBTagProb,false);
  }

  // mtw
  // single muon control sample
  if(muIso==2 && MTW < mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,WeightBTagProb,true);
      MuMTWNJets_->Fill(NJets,WeightBTagProb,true);
      MuMTWHT_->Fill(HT,WeightBTagProb,true);
      MuMTWMHT_->Fill(MHT,WeightBTagProb,true);
      MuMTWPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,true);
      MuMTWActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,true);
      MuMTWPTActivity_->Fill(Muons_MT2Activity->at(0),Muons->at(0).Pt(),WeightBTagProb,true);
      MuMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, true);
      MuMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, true);
      MuMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, true);
  }

  if(muIso==2 && MTW > mtwCut_){
      // 1D
      MuMTWBTag_->Fill(BTags,WeightBTagProb,false);
      MuMTWNJets_->Fill(NJets,WeightBTagProb,false);
      MuMTWHT_->Fill(HT,WeightBTagProb,false);
      MuMTWMHT_->Fill(MHT,WeightBTagProb,false);
      MuMTWPT_->Fill(Muons->at(0).Pt(),WeightBTagProb,false);
      MuMTWActivity_->Fill(Muons_MT2Activity->at(0),WeightBTagProb,false);
      MuMTWPTActivity_->Fill(Muons_MT2Activity->at(0),Muons->at(0).Pt(),WeightBTagProb,false);
      MuMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, false);
      MuMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, false);
      MuMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, false);
  }
  
  // single elec control sample
  if(elecIso==2 && MTW < mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,WeightBTagProb,true);
      ElecMTWNJets_->Fill(NJets,WeightBTagProb,true);
      ElecMTWHT_->Fill(HT,WeightBTagProb,true);
      ElecMTWMHT_->Fill(MHT,WeightBTagProb,true);
      ElecMTWPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,true);
      ElecMTWActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,true);
      ElecMTWPTActivity_->Fill(Electrons_MT2Activity->at(0),Electrons->at(0).Pt(),WeightBTagProb,true);
      ElecMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, true);
      ElecMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, true);
      ElecMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, true);
  }

  if(elecIso==2 && MTW > mtwCut_){
      // 1D
      ElecMTWBTag_->Fill(BTags,WeightBTagProb,false);
      ElecMTWNJets_->Fill(NJets,WeightBTagProb,false);
      ElecMTWHT_->Fill(HT,WeightBTagProb,false);
      ElecMTWMHT_->Fill(MHT,WeightBTagProb,false);
      ElecMTWPT_->Fill(Electrons->at(0).Pt(),WeightBTagProb,false);
      ElecMTWActivity_->Fill(Electrons_MT2Activity->at(0),WeightBTagProb,false);
      ElecMTWPTActivity_->Fill(Electrons_MT2Activity->at(0),Electrons->at(0).Pt(),WeightBTagProb,false);
      ElecMTWHTNJets_->Fill(HT, NJets, WeightBTagProb, false);
      ElecMTWMHTNJets_->Fill(MHT, NJets, WeightBTagProb, false);
      ElecMTWHTMHT_->Fill(HT, MHT, WeightBTagProb, false);
  }

  // di lep contribution
  if(MuDiLepControlSample==2){
      // 1D
      MuDiLepBTag_->Fill(BTags,WeightBTagProb,true);
      MuDiLepNJets_->Fill(NJets,WeightBTagProb,true);
      MuDiLepHT_->Fill(HT,WeightBTagProb,true);
      MuDiLepMHT_->Fill(MHT,WeightBTagProb,true);

      // 1D
      MuDiLepContributionBTag_->Fill(BTags,WeightBTagProb,true);
      MuDiLepContributionNJets_->Fill(NJets,WeightBTagProb,true);
      MuDiLepContributionHT_->Fill(HT,WeightBTagProb,true);
      MuDiLepContributionMHT_->Fill(MHT,WeightBTagProb,true);

      if(MTW <mtwCut_){
          // 1D
          MuDiLepFractionBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepFractionNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepFractionHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepFractionMHT_->Fill(MHT,WeightBTagProb,true);
      }


      if(MTW <mtwCut_){
          // 1D
          MuDiLepContributionMTWBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepContributionMTWNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepContributionMTWHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepContributionMTWMHT_->Fill(MHT,WeightBTagProb,true);
          MuDiLepContributionMTWMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      }
    
  }

  if(MuDiLepControlSample==0){
      // 1D
      MuDiLepContributionBTag_->Fill(BTags,WeightBTagProb,false);
      MuDiLepContributionNJets_->Fill(NJets,WeightBTagProb,false);
      MuDiLepContributionHT_->Fill(HT,WeightBTagProb,false);
      MuDiLepContributionMHT_->Fill(MHT,WeightBTagProb,false);

      // 1D
      MuDiLepBTag_->Fill(BTags,WeightBTagProb,false);
      MuDiLepNJets_->Fill(NJets,WeightBTagProb,false);
      MuDiLepHT_->Fill(HT,WeightBTagProb,false);
      MuDiLepMHT_->Fill(MHT,WeightBTagProb,false);
    
      if(MTW <mtwCut_){
          // 1D
          MuDiLepMTWBTag_->Fill(BTags,WeightBTagProb,true);
          MuDiLepMTWNJets_->Fill(NJets,WeightBTagProb,true);
          MuDiLepMTWHT_->Fill(HT,WeightBTagProb,true);
          MuDiLepMTWMHT_->Fill(MHT,WeightBTagProb,true);
      }

      if(MTW <mtwCut_){
          // 1D
          MuDiLepContributionMTWBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepContributionMTWNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepContributionMTWHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepContributionMTWMHT_->Fill(MHT,WeightBTagProb,false);
          MuDiLepContributionMTWMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      }
  }

  if(ExpectationDiLep==1){
          MuDiLepFractionBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepFractionNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepFractionHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepFractionMHT_->Fill(MHT,WeightBTagProb,false);

          MuDiLepMTWBTag_->Fill(BTags,WeightBTagProb,false);
          MuDiLepMTWNJets_->Fill(NJets,WeightBTagProb,false);
          MuDiLepMTWHT_->Fill(HT,WeightBTagProb,false);
          MuDiLepMTWMHT_->Fill(MHT,WeightBTagProb,false);
  }
  
  if(ElecDiLepControlSample==2){
      // 1D
      ElecDiLepBTag_->Fill(BTags,WeightBTagProb,true);
      ElecDiLepNJets_->Fill(NJets,WeightBTagProb,true);
      ElecDiLepHT_->Fill(HT,WeightBTagProb,true);
      ElecDiLepMHT_->Fill(MHT,WeightBTagProb,true);

      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,WeightBTagProb,true);
      ElecDiLepContributionNJets_->Fill(NJets,WeightBTagProb,true);
      ElecDiLepContributionHT_->Fill(HT,WeightBTagProb,true);
      ElecDiLepContributionMHT_->Fill(MHT,WeightBTagProb,true);

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepFractionBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepFractionNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepFractionHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepFractionMHT_->Fill(MHT,WeightBTagProb,true);
      }
      
      if(MTW <mtwCut_){
          // 1D
          ElecDiLepContributionMTWBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepContributionMTWNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepContributionMTWHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepContributionMTWMHT_->Fill(MHT,WeightBTagProb,true);
          ElecDiLepContributionMTWMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
      }
    
  }

  if(ElecDiLepControlSample==0) {
    
      // 1D
      ElecDiLepContributionBTag_->Fill(BTags,WeightBTagProb,false);
      ElecDiLepContributionNJets_->Fill(NJets,WeightBTagProb,false);
      ElecDiLepContributionHT_->Fill(HT,WeightBTagProb,false);
      ElecDiLepContributionMHT_->Fill(MHT,WeightBTagProb,false);

      // 1D
      ElecDiLepBTag_->Fill(BTags,WeightBTagProb,false);
      ElecDiLepNJets_->Fill(NJets,WeightBTagProb,false);
      ElecDiLepHT_->Fill(HT,WeightBTagProb,false);
      ElecDiLepMHT_->Fill(MHT,WeightBTagProb,false);
    
      if(MTW <mtwCut_){
          // 1D
          ElecDiLepMTWBTag_->Fill(BTags,WeightBTagProb,true);
          ElecDiLepMTWNJets_->Fill(NJets,WeightBTagProb,true);
          ElecDiLepMTWHT_->Fill(HT,WeightBTagProb,true);
          ElecDiLepMTWMHT_->Fill(MHT,WeightBTagProb,true);
      }

      if(MTW <mtwCut_){
          // 1D
          ElecDiLepContributionMTWBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepContributionMTWNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepContributionMTWHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepContributionMTWMHT_->Fill(MHT,WeightBTagProb,false);
          ElecDiLepContributionMTWMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      }
  } 

    if(ExpectationDiLep==1){
          ElecDiLepFractionBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepFractionNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepFractionHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepFractionMHT_->Fill(MHT,WeightBTagProb,false);

          ElecDiLepMTWBTag_->Fill(BTags,WeightBTagProb,false);
          ElecDiLepMTWNJets_->Fill(NJets,WeightBTagProb,false);
          ElecDiLepMTWHT_->Fill(HT,WeightBTagProb,false);
          ElecDiLepMTWMHT_->Fill(MHT,WeightBTagProb,false);
  }
    
  // ExpectationReductionIsoTrack
  if(Expectation==1 && ExpectationReductionIsoTrack==0){
      //  cout << "Event not rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);

      if(GenMuonsNum>0){
          //  cout << "Muon event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,false);
      }else if(GenElectronsNum>0){
          // cout << "Electron event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,false);
      }else if(GenTausNum>0){
          // cout << "Tau event" << endl;
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),WeightBTagProb,false);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTaus_MT2Activity->at(0),WeightBTagProb,false);
      }else std::cout<<"No gen lepton found to fail..."<<std::endl;

      //2D
      IsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
      IsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
      IsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);      
      if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,false);
      else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
      else IsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 1.5 && NJets < 2.5) IsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 2.5 && NJets < 3.5) IsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,false);
      if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,false);

      if(BTags<0.5){
        if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        else IsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
      }else{
      if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
      }

      if(GenMuonsNum>0){
          IsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,false);
      }else if(GenElectronsNum>0){
          IsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,false);
      }else if(GenTausNum>0){
          IsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,false);
      }
  }
  
  if(Expectation==1 && ExpectationReductionIsoTrack==1){
      // cout << "Event rejected by iso track veto" << endl;
      ExpectationReductionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
      ExpectationReductionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
      ExpectationReductionIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
      ExpectationReductionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);

      if(isoMuonTracksNum>0 && GenMuonsNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenMuons->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenMuons_MT2Activity->at(0),WeightBTagProb,true);
      }else if(isoElectronTracksNum>0 && GenElectronsNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenElectrons->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenElectrons_MT2Activity->at(0),WeightBTagProb,true);
      }else if(isoPionTracksNum>0 && GenTausNum>0){
          ExpectationReductionIsoTrackPTEff_->Fill(GenTaus->at(0).Pt(),WeightBTagProb,true);
          ExpectationReductionIsoTrackActivityEff_->Fill(GenTaus_MT2Activity->at(0),WeightBTagProb,true);
    }

    //2D
    IsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
    IsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
    IsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
    if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,true);
    else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 1.5 && NJets < 2.5) IsoTrackReductionHTMHT_NJets2_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 2.5 && NJets < 3.5) IsoTrackReductionHTMHT_NJets3_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 3.5 && NJets < 4.5) IsoTrackReductionHTMHT_NJets4_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 4.5 && NJets < 5.5) IsoTrackReductionHTMHT_NJets5_->Fill(HT,MHT,WeightBTagProb,true);
    if(NJets > 5.5 && NJets < 6.5) IsoTrackReductionHTMHT_NJets6_->Fill(HT,MHT,WeightBTagProb,true);

  if(BTags<0.5){
    if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
    else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
  }else{
  if(NJets < 4.5) IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
      else if(NJets < 6.5) IsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
    else IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
  }

    if(isoMuonTracksNum>0 && GenMuonsNum>0){
        IsoTrackReductionPTActivity_->Fill(GenMuons_MT2Activity->at(0),GenMuons->at(0).Pt(),WeightBTagProb,true);
    }else if(isoElectronTracksNum>0 && GenElectronsNum>0){
        IsoTrackReductionPTActivity_->Fill(GenElectrons_MT2Activity->at(0),GenElectrons->at(0).Pt(),WeightBTagProb,true);
    }else if(isoPionTracksNum>0 && GenTausNum>0){
        IsoTrackReductionPTActivity_->Fill(GenTaus_MT2Activity->at(0),GenTaus->at(0).Pt(),WeightBTagProb,true);
    }
  }

    // In order to avoid double-counting events, only select track with highest pt
    if(Expectation==1){
        int isoTrack_highestPt = 0;

        if(isoMuonTracksNum>0){
            isoTrack_highestPt = 1;
            if(isoElectronTracksNum>0 && isoPionTracksNum>0){
                if(isoElectronTracks->at(0).Pt() > TMath::Max(isoMuonTracks->at(0).Pt(), isoPionTracks->at(0).Pt())) isoTrack_highestPt = 2;
                if(isoPionTracks->at(0).Pt() > TMath::Max(isoMuonTracks->at(0).Pt(), isoElectronTracks->at(0).Pt())) isoTrack_highestPt = 3;
            }else if(isoElectronTracksNum>0){
                if(isoElectronTracks->at(0).Pt() > isoMuonTracks->at(0).Pt()) isoTrack_highestPt = 2;
            }else if(isoPionTracksNum>0){
                if(isoPionTracks->at(0).Pt() > isoMuonTracks->at(0).Pt()) isoTrack_highestPt = 3;
            }
        }else if(isoElectronTracksNum>0){
            isoTrack_highestPt = 2;
            if(isoPionTracksNum>0) if(isoPionTracks->at(0).Pt() > isoElectronTracks->at(0).Pt()) isoTrack_highestPt = 3;
        }else if(isoPionTracksNum>0){
            isoTrack_highestPt = 3;
        }


        // muon iso tracks
        if(isoMuonTracksNum>0 && isoTrack_highestPt==1){
            // cout << "Muon tracks found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionMuIsoTrackPTEff_->Fill(isoMuonTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(isoMuonTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  MuIsoTrackReductionPTActivity_->Fill(isoMuonTracksNumActivity->at(0),isoMuonTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
            else MuIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
          if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else MuIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
          else MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        }
            // cout << "DONE" << endl;
        }else{
            // cout << "Muon tracks not found...";
            ExpectationReductionMuIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionMuIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            // JACK -- placeholders
            ExpectationReductionMuIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionMuIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            MuIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            MuIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            MuIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  MuIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
            else MuIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
          if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else MuIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets < 4.5) MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
          else MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        }
            // cout << "DONE" << endl;
        }
      
      
        // elec iso tracks
        if(isoElectronTracksNum>0 && isoTrack_highestPt==2){
            // cout << "Electron tracks found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionElecIsoTrackPTEff_->Fill(isoElectronTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(isoElectronTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  ElecIsoTrackReductionPTActivity_->Fill(isoElectronTracksNumActivity->at(0),isoElectronTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
            else ElecIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
          if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
          if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
          else ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        }
            // cout << "DONE" << endl;    
        }else{
            // cout << "Electron tracks not found...";
            ExpectationReductionElecIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            ExpectationReductionElecIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionElecIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            ElecIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            ElecIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            ElecIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  ElecIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
            else ElecIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
          if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets < 4.5) ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
          else ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        }
            // cout << "DONE" << endl;    
        }

        // pion iso tracks
        if(isoPionTracksNum>0 && isoTrack_highestPt==3){
            // cout << "Pion tracks found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,true);
            ExpectationReductionPionIsoTrackPTEff_->Fill(isoPionTracks->at(0).Pt(),WeightBTagProb,true);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(isoPionTracksNumActivity->at(0),WeightBTagProb,true);
          
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,true);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,true);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,true);
            //  PionIsoTrackReductionPTActivity_->Fill(isoPionTracksNumActivity->at(0),isoPionTracks->at(0).Pt(),WeightBTagProb,true);
            if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,true);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,true);
            else PionIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,true);

            if(BTags<0.5){
          if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
          else PionIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,true);
        }else{
        if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
          else PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,true);
        }
            // cout << "DONE" << endl;    
        }else{
            // cout << "Pion tracks not found...";
            ExpectationReductionPionIsoTrackBTagEff_->Fill(BTags,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackNJetsEff_->Fill(NJets,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackHTEff_->Fill(HT,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackMHTEff_->Fill(MHT,WeightBTagProb,false);
            ExpectationReductionPionIsoTrackPTEff_->Fill(0,WeightBTagProb,false);
            //  ExpectationReductionPionIsoTrackActivityEff_->Fill(0,WeightBTagProb,false);
            //2D
            PionIsoTrackReductionHTNJets_->Fill(HT,NJets,WeightBTagProb,false);
            PionIsoTrackReductionMHTNJets_->Fill(MHT,NJets,WeightBTagProb,false);
            PionIsoTrackReductionBTagNJets_->Fill(BTags,NJets,WeightBTagProb,false);
            //  PionIsoTrackReductionPTActivity_->Fill(0,0,WeightBTagProb,false);
            if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_->Fill(HT,MHT,WeightBTagProb,false);
            else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_->Fill(HT,MHT,WeightBTagProb,false);
            else PionIsoTrackReductionHTMHT_NJetsHigh_->Fill(HT,MHT,WeightBTagProb,false);

            if(BTags<0.5){
          if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
          else PionIsoTrackReductionHTMHT_NJetsHigh_BTags0_->Fill(HT,MHT,WeightBTagProb,false);
        }else{
          if(NJets < 4.5) PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        else if(NJets < 6.5) PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
          else PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->Fill(HT,MHT,WeightBTagProb,false);
        }
            // cout << "DONE" << endl;    
        }

  // MHT/PTW histograms
  int INJ(-1);
  if (NJets>=4&&NJets<=6) INJ=0;
  else if (NJets>=7&&NJets<=8) INJ=1;
  else if (NJets>=9) INJ=2;
  int INB(BTags);
  if (INB>2) INB=2;
  int IHT(-1);
  if (HT>500&&HT<800) IHT=0;
  else if (HT>800&&HT<1200) IHT=1;
  else if (HT>1200) IHT=2;
  if (HT<800&&MHT>750) IHT=-1;

  //  printf("INJ/INB/IHT = %d/%d/%d\n", INJ, INB, IHT);
  if (INJ>=0&&INB>=0&&IHT>=0) {
    if (Expectation==1) {
      if (GenMuonsNum==1&&GenElectronsNum==0) {          
        if (ExpectationReductionIsoTrack==0) {
    double PTW = sqrt( (GenMuons->at(0).Px()+MHT*cos(MHTPhi))*(GenMuons->at(0).Px()+MHT*cos(MHTPhi)) +  (GenMuons->at(0).Py()+MHT*sin(MHTPhi))*(GenMuons->at(0).Py()+MHT*sin(MHTPhi)) );
    if (HT>500&&HT<1200) LostMuRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>1200) LostMuRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>800) LostMuRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
        }
      }
      else if (GenMuonsNum==0&&GenElectronsNum==1) {
        if (ExpectationReductionIsoTrack==0) {        
    double PTW = sqrt( (GenElectrons->at(0).Px()+MHT*cos(MHTPhi))*(GenElectrons->at(0).Px()+MHT*cos(MHTPhi)) +  (GenElectrons->at(0).Py()+MHT*sin(MHTPhi))*(GenElectrons->at(0).Py()+MHT*sin(MHTPhi)) );
    if (HT>500&&HT<1200) LostElecRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>1200) LostElecRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>800) LostElecRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
    if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
        }
      } // 1-electron events
      // what do we want to do with di/multi-lepton events?
      // commented out below: take sum of all leptons and MHT
      // else if (GenMuonsNum+GenElectronsNum>1) { 
      //   std::vector<TLorentzVector> GenLeps;
      //   for (unsigned int imu(0); imu<GenMuonsNum; imu++) {
      //  GenLeps.push_back(GenMuons->at(imu));
      //   }
      //   for (unsigned int iel(0); iel<GenElectronsNum; iel++) {
      //  GenLeps.push_back(GenElectrons->at(iel));
      //   }
      //   double PXW(MHT*cos(MHTPhi)), PYW(MHT*sin(MHTPhi));
      //   for (unsigned int ilep(0); ilep<GenLeps.size(); ilep++) {
      //  PXW+=GenLeps[ilep].Px();
      //  PYW+=GenLeps[ilep].Py();
      //   }
      //   double PTW = sqrt(PXW*PXW+PYW*PYW);
      //   if (HT>500&&HT<1200) LostLepRATIO_HT12[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      //   if (HT>1200) LostLepRATIO_HT3[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      //   if (HT>800) LostLepRATIO_HT23[INJ*3+INB]->Fill(MHT/PTW, WeightBTagProb);
      // } // di/multi-lepton events
    }
  }
  
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

  
  TFile *outPutFile = new TFile(fileName,"RECREATE"); 
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
  MuPurityOldBTag_->SaveEff("#mu purity; B_{Tags}", dEfficiencies);
  MuPurityOldNJets_->SaveEff("#mu purity; N_{Jets}", dEfficiencies);   
  MuPurityOldHT_->SaveEff("#mu purity; H_{T} [GeV]", dEfficiencies);   
  MuPurityOldMHT_->SaveEff("#mu purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuonPurityOldMHTNJet_->SaveEff("#mu purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  //1D
  ElecPurityOldBTag_->SaveEff("e purity; B_{Tags}", dEfficiencies);
  ElecPurityOldNJets_->SaveEff("e purity; N_{Jets}", dEfficiencies);   
  ElecPurityOldHT_->SaveEff("e purity; H_{T} [GeV]", dEfficiencies);   
  ElecPurityOldMHT_->SaveEff("e purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecPurityOldMHTNJet_->SaveEff("e purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuPurityBTag_->SaveEff("#mu purity; B_{Tags}", dEfficiencies);   
  MuPurityNJets_->SaveEff("#mu purity; N_{Jets}", dEfficiencies);   
  MuPurityHT_->SaveEff("#mu purity; H_{T} [GeV]", dEfficiencies);   
  MuPurityMHT_->SaveEff("#mu purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuonPurityMHTNJet_->SaveEff("#mu purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  //elec
  //1D
  ElecPurityBTag_->SaveEff("e purity; B_{Tags}", dEfficiencies);   
  ElecPurityNJets_->SaveEff("e purity; N_{Jets}", dEfficiencies);   
  ElecPurityHT_->SaveEff("e purity; H_{T} [GeV]", dEfficiencies);   
  ElecPurityMHT_->SaveEff("e purity; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecPurityMHTNJet_->SaveEff("e purity; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   

  // acc
  //muon
  //1D
  MuAccBTag_->SaveEff("#mu acc; B_{Tags}", dEfficiencies);   
  MuAccNJets_->SaveEff("#mu acc; N_{Jets}", dEfficiencies);   
  MuAccHT_->SaveEff("#mu acc; H_{T} [GeV]", dEfficiencies);   
  MuAccMHT_->SaveEff("#mu acc; #slash{H}_{T} [GeV]", dEfficiencies); 
  MuAccDTT_->SaveEff("#mu acc; 0.5*(1-cosDTT)", dEfficiencies);  
  // 2D 
  MuAccHTNJets_->SaveEff("#mu acc; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccHTMHT_->SaveEff("#mu acc; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccMHTNJets_->SaveEff("#mu acc; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccBTagNJets_->SaveEff("#mu acc; B_{Tags}; N_{Jets}", dEfficiencies);   
  MuAccMHTNJetsB0_->SaveEff("#mu acc B_{Tags}=0; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  MuAccMHTNJetsB1_Inf_->SaveEff("#mu acc B_{Tags}#geq1; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);    
  MuAccHTMHT_NJetsLow_->SaveEff("#mu acc N_{Jets}=2-6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets2_->SaveEff("#mu acc N_{Jets}=2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets3_->SaveEff("#mu acc N_{Jets}=3;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_->SaveEff("#mu acc N_{Jets}=4;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_->SaveEff("#mu acc N_{Jets}=5;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_->SaveEff("#mu acc N_{Jets}=6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_->SaveEff("#mu acc N_{Jets}=7-8;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_->SaveEff("#mu acc N_{Jets}=9+;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJetsHigh_->SaveEff("#mu acc N_{Jets}#geq7;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHTB0_->SaveEff("#mu acc B_{Tags}=0;H_{T} [GeV] ; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHTB1_Inf_->SaveEff("#mu acc B_{Tags}#geq1; H_{T} [GeV]; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);

  MuAccHTMHT_NJets2_BTags0_->SaveEff("#mu acc N_{Jets}=2, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags0_->SaveEff("#mu acc N_{Jets}=3, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags0_->SaveEff("#mu acc N_{Jets}=4, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags0_->SaveEff("#mu acc N_{Jets}=5, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags0_->SaveEff("#mu acc N_{Jets}=6, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags0_->SaveEff("#mu acc N_{Jets}=7-8, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags0_->SaveEff("#mu acc N_{Jets}=9+, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuAccHTMHT_NJetsHigh_BTags0_->SaveEff("#mu acc N_{Jets}=7+, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuAccHTMHT_NJets2_BTags1Inf_->SaveEff("#mu acc N_{Jets}=2, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags1Inf_->SaveEff("#mu acc N_{Jets}=3, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags1Inf_->SaveEff("#mu acc N_{Jets}=4, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags1Inf_->SaveEff("#mu acc N_{Jets}=5, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags1Inf_->SaveEff("#mu acc N_{Jets}=6, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags1Inf_->SaveEff("#mu acc N_{Jets}=7-8, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags1Inf_->SaveEff("#mu acc N_{Jets}=9+, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 
  MuAccHTMHT_NJetsHigh_BTags1Inf_->SaveEff("#mu acc N_{Jets}=7+, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuAccHTMHT_NJets2_BTags1_->SaveEff("#mu acc N_{Jets}=2, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags1_->SaveEff("#mu acc N_{Jets}=3, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags1_->SaveEff("#mu acc N_{Jets}=4, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags1_->SaveEff("#mu acc N_{Jets}=5, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags1_->SaveEff("#mu acc N_{Jets}=6, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags1_->SaveEff("#mu acc N_{Jets}=7-8, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags1_->SaveEff("#mu acc N_{Jets}=9+, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 
  MuAccHTMHT_NJetsHigh_BTags1_->SaveEff("#mu acc N_{Jets}=7+, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuAccHTMHT_NJets2_BTags2Inf_->SaveEff("#mu acc N_{Jets}=2, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets3_BTags2Inf_->SaveEff("#mu acc N_{Jets}=3, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets4_BTags2Inf_->SaveEff("#mu acc N_{Jets}=4, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets5_BTags2Inf_->SaveEff("#mu acc N_{Jets}=5, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets6_BTags2Inf_->SaveEff("#mu acc N_{Jets}=6, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets78_BTags2Inf_->SaveEff("#mu acc N_{Jets}=7-8, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  MuAccHTMHT_NJets9Inf_BTags2Inf_->SaveEff("#mu acc N_{Jets}=9+, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 
  MuAccHTMHT_NJetsHigh_BTags2Inf_->SaveEff("#mu acc N_{Jets}=7+, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 

  //elec
  //1D
  ElecAccBTag_->SaveEff("e acc; B_{Tags}", dEfficiencies);   
  ElecAccNJets_->SaveEff("e acc; N_{Jets}", dEfficiencies);   
  ElecAccHT_->SaveEff("e acc; H_{T} [GeV]", dEfficiencies);   
  ElecAccMHT_->SaveEff("e acc; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecAccDTT_->SaveEff("e acc; 0.5*(1-cosDTT)", dEfficiencies);
  // 2D 
  ElecAccHTNJets_->SaveEff("e acc; H_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccHTMHT_->SaveEff("e acc; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccMHTNJets_->SaveEff("e acc; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccBTagNJets_->SaveEff("e acc; B_{Tags}; N_{Jets}", dEfficiencies);   
  ElecAccMHTNJetsB0_->SaveEff("e acc B_{Tags}=0; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccMHTNJetsB1_Inf_->SaveEff("e acc B_{Tags}#geq1; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  ElecAccHTMHT_NJetsLow_->SaveEff("e acc N_{Jets}=2-6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets2_->SaveEff("e acc N_{Jets}=2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets3_->SaveEff("e acc N_{Jets}=3;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_->SaveEff("e acc N_{Jets}=4;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_->SaveEff("e acc N_{Jets}=5;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_->SaveEff("e acc N_{Jets}=6;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_->SaveEff("e acc N_{Jets}=7-8;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_->SaveEff("e acc N_{Jets}=9+;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJetsHigh_->SaveEff("e acc N_{Jets}#geq7;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHTB0_->SaveEff("e acc B_{Tags}=0;H_{T} [GeV] ; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHTB1_Inf_->SaveEff("e acc B_{Tags}#geq1; H_{T} [GeV]; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies); 

  ElecAccHTMHT_NJets2_BTags0_->SaveEff("e acc N_{Jets}=2, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags0_->SaveEff("e acc N_{Jets}=3, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags0_->SaveEff("e acc N_{Jets}=4, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags0_->SaveEff("e acc N_{Jets}=5, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags0_->SaveEff("e acc N_{Jets}=6, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags0_->SaveEff("e acc N_{Jets}=7-8, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags0_->SaveEff("e acc N_{Jets}=9+, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecAccHTMHT_NJetsHigh_BTags0_->SaveEff("e acc N_{Jets}=7+, B_{Tags}=0;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags1Inf_->SaveEff("e acc N_{Jets}=2, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags1Inf_->SaveEff("e acc N_{Jets}=3, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags1Inf_->SaveEff("e acc N_{Jets}=4, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags1Inf_->SaveEff("e acc N_{Jets}=5, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags1Inf_->SaveEff("e acc N_{Jets}=6, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags1Inf_->SaveEff("e acc N_{Jets}=7-8, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags1Inf_->SaveEff("e acc N_{Jets}=9+, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);  
  ElecAccHTMHT_NJetsHigh_BTags1Inf_->SaveEff("e acc N_{Jets}=7+, B_{Tags}#geq1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags1_->SaveEff("e acc N_{Jets}=2, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags1_->SaveEff("e acc N_{Jets}=3, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags1_->SaveEff("e acc N_{Jets}=4, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags1_->SaveEff("e acc N_{Jets}=5, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags1_->SaveEff("e acc N_{Jets}=6, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags1_->SaveEff("e acc N_{Jets}=7-8, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags1_->SaveEff("e acc N_{Jets}=9+, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 
  ElecAccHTMHT_NJetsHigh_BTags1_->SaveEff("e acc N_{Jets}=7+, B_{Tags}=1;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecAccHTMHT_NJets2_BTags2Inf_->SaveEff("e acc N_{Jets}=2, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets3_BTags2Inf_->SaveEff("e acc N_{Jets}=3, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets4_BTags2Inf_->SaveEff("e acc N_{Jets}=4, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets5_BTags2Inf_->SaveEff("e acc N_{Jets}=5, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets6_BTags2Inf_->SaveEff("e acc N_{Jets}=6, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets78_BTags2Inf_->SaveEff("e acc N_{Jets}=7-8, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);   
  ElecAccHTMHT_NJets9Inf_BTags2Inf_->SaveEff("e acc N_{Jets}=9+, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 
  ElecAccHTMHT_NJetsHigh_BTags2Inf_->SaveEff("e acc N_{Jets}=7+, B_{Tags}#geq2;H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 

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
  MuMTWMHTNJets_->SaveEff("#mu m_{T}(w); #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);
  MuMTWHTMHT_->SaveEff("#mu m_{T}(w); H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);


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
  MuDiLepFractionBTag_->SaveEff("#mu di lep contri; B_{Tags}", dEfficiencies);   
  MuDiLepFractionNJets_->SaveEff("#mu di lep contri; N_{Jets}", dEfficiencies);   
  MuDiLepFractionHT_->SaveEff("#mu di lep contri; H_{T} [GeV]", dEfficiencies);   
  MuDiLepFractionMHT_->SaveEff("#mu di lep contri; #slash{H}_{T} [GeV]", dEfficiencies); 
  MuDiLepContributionMTWBTag_->SaveEff("#mu di lep contri; B_{Tags}", dEfficiencies);   
  MuDiLepContributionMTWNJets_->SaveEff("#mu di lep contri; N_{Jets}", dEfficiencies);   
  MuDiLepContributionMTWHT_->SaveEff("#mu di lep contri; H_{T} [GeV]", dEfficiencies);   
  MuDiLepContributionMTWMHT_->SaveEff("#mu di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);
  MuDiLepContributionMTWMHTNJets_->SaveEff("#mu di lep contri; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);

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
  ElecMTWMHTNJets_->SaveEff("e m_{T}(w); #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);
  ElecMTWHTMHT_->SaveEff("e m_{T}(w); H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);


  //elec
  //1D
  ElecDiLepContributionBTag_->SaveEff("e di lep contri; B_{Tags}", dEfficiencies);   
  ElecDiLepContributionNJets_->SaveEff("e di lep contri; N_{Jets}", dEfficiencies);   
  ElecDiLepContributionHT_->SaveEff("e di lep contri; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepContributionMHT_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecDiLepFractionBTag_->SaveEff("e di lep contri; B_{Tags}", dEfficiencies);   
  ElecDiLepFractionNJets_->SaveEff("e di lep contri; N_{Jets}", dEfficiencies);   
  ElecDiLepFractionHT_->SaveEff("e di lep contri; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepFractionMHT_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);  
  ElecDiLepContributionMTWBTag_->SaveEff("e di lep contri; B_{Tags}", dEfficiencies);   
  ElecDiLepContributionMTWNJets_->SaveEff("e di lep contri; N_{Jets}", dEfficiencies);   
  ElecDiLepContributionMTWHT_->SaveEff("e di lep contri; H_{T} [GeV]", dEfficiencies);   
  ElecDiLepContributionMTWMHT_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecDiLepContributionMTWMHTNJets_->SaveEff("e di lep contri; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);

  
  // pt and activity  
  //muon
  MuPurityOldPT_->SaveEff("#mu purity; p_{T}(#mu) [GeV]", dEfficiencies);   
  MuPurityOldActivity_->SaveEff("#mu purity; Activity", dEfficiencies, true);   
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
  ElecPurityOldPT_->SaveEff("e purity; p_{T}(e) [GeV]", dEfficiencies);   
  ElecPurityOldActivity_->SaveEff("e purity; Activity", dEfficiencies, true);   
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
  IsoTrackReductionHTMHT_NJetsVeryLow_->SaveEff("iso track expec. reduction N_{Jets}=3-4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsLow_->SaveEff("iso track expec. reduction N_{Jets}=5-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets2_->SaveEff("iso track expec. reduction N_{Jets}=2; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets3_->SaveEff("iso track expec. reduction N_{Jets}=3; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets4_->SaveEff("iso track expec. reduction N_{Jets}=4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets5_->SaveEff("iso track expec. reduction N_{Jets}=5; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJets6_->SaveEff("iso track expec. reduction N_{Jets}=6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsHigh_->SaveEff("iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionMHTNJets_->SaveEff("iso track expec. reduction; #slash{H}_{T} [GeV]; N_{Jets}", dEfficiencies);   
  IsoTrackReductionBTagNJets_->SaveEff("iso track expec. reduction; B_{Tags}; N_{Jets}", dEfficiencies);   
  IsoTrackReductionPTActivity_->SaveEff("iso track expec. reduction; Activity; p_{T} [GeV]", dEfficiencies, true);   

  IsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->SaveEff("iso track expec. reduction N_{Jets}=3-4, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsLow_BTags0_->SaveEff("iso track expec. reduction N_{Jets}=5-6, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsHigh_BTags0_->SaveEff("iso track expec. reduction N_{Jets}#geq7, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->SaveEff("iso track expec. reduction N_{Jets}=3-4, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->SaveEff("iso track expec. reduction N_{Jets}=5-6, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  IsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->SaveEff("iso track expec. reduction N_{Jets}#geq7, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);

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
  MuIsoTrackReductionHTMHT_NJetsVeryLow_->SaveEff("#mu iso track expec. reduction N_{Jets}=2-4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsLow_->SaveEff("#mu iso track expec. reduction N_{Jets}=5-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("#mu iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies); 

  MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->SaveEff("#mu iso track expec. reduction N_{Jets}=2-4, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsLow_BTags0_->SaveEff("#mu iso track expec. reduction N_{Jets}=5-6, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsHigh_BTags0_->SaveEff("#mu iso track expec. reduction N_{Jets}#geq7, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{Jets}=2-4, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{Jets}=5-6, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  MuIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->SaveEff("#mu iso track expec. reduction N_{Jets}#geq7, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);

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
  ElecIsoTrackReductionHTMHT_NJetsVeryLow_->SaveEff("e iso track expec. reduction N_{Jets}=2-4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsLow_->SaveEff("e iso track expec. reduction N_{Jets}=5-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("e iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);

  ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->SaveEff("e iso track expec. reduction N_{Jets}=2-4, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsLow_BTags0_->SaveEff("e iso track expec. reduction N_{Jets}=5-6, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsHigh_BTags0_->SaveEff("e iso track expec. reduction N_{Jets}#geq7, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->SaveEff("e iso track expec. reduction N_{Jets}=2-4, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->SaveEff("e iso track expec. reduction N_{Jets}=5-6, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  ElecIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->SaveEff("e iso track expec. reduction N_{Jets}#geq7, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  
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
  PionIsoTrackReductionHTMHT_NJetsVeryLow_->SaveEff("#pi iso track expec. reduction N_{Jets}=2-4; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsLow_->SaveEff("#pi iso track expec. reduction N_{Jets}=5-6; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsHigh_->SaveEff("#pi iso track expec. reduction N_{Jets}#geq7; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);

  PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags0_->SaveEff("#pi iso track expec. reduction N_{Jets}=2-4, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsLow_BTags0_->SaveEff("#pi iso track expec. reduction N_{Jets}=5-6, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsHigh_BTags0_->SaveEff("#pi iso track expec. reduction N_{Jets}#geq7, B_{Tags}=0; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsVeryLow_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{Jets}=2-4, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsLow_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{Jets}=5-6, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);
  PionIsoTrackReductionHTMHT_NJetsHigh_BTags1Inf_->SaveEff("#pi iso track expec. reduction N_{Jets}#geq7, B_{Tags}=1+; H_{T} [GeV]; #slash{H}_{T} [GeV]", dEfficiencies);

  outPutFile->cd();
  outPutFile->mkdir("ExtrapPDFs");
  TDirectory *dExtrapPDFs = (TDirectory*)outPutFile->Get("ExtrapPDFs");
  dExtrapPDFs->cd();
  for (unsigned int inj(0); inj<3; inj++) {
    for (unsigned int inb(0); inb<3; inb++) {
      // fix overflow bins
      // lump remiaining tail into 1.2 < MHT/PTW < 1.3 -- does this make sense?
      Double_t erro(0.);
      LostMuRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostMuRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostMuRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostMuRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostMuRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostMuRATIO_HT12[inj*3+inb]->Integral()>0) LostMuRATIO_HT12[inj*3+inb]->Scale(1/LostMuRATIO_HT12[inj*3+inb]->Integral());
      if (LostMuRATIO_HT3[inj*3+inb]->Integral()>0) LostMuRATIO_HT3[inj*3+inb]->Scale(1/LostMuRATIO_HT3[inj*3+inb]->Integral());
      if (LostMuRATIO_HT23[inj*3+inb]->Integral()>0) LostMuRATIO_HT23[inj*3+inb]->Scale(1/LostMuRATIO_HT23[inj*3+inb]->Integral());
      LostMuRATIO_HT12[inj*3+inb]->Write();
      LostMuRATIO_HT3[inj*3+inb]->Write();
      LostMuRATIO_HT23[inj*3+inb]->Write();
      LostElecRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostElecRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostElecRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostElecRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostElecRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostElecRATIO_HT12[inj*3+inb]->Integral()>0) LostElecRATIO_HT12[inj*3+inb]->Scale(1/LostElecRATIO_HT12[inj*3+inb]->Integral());
      if (LostElecRATIO_HT3[inj*3+inb]->Integral()>0) LostElecRATIO_HT3[inj*3+inb]->Scale(1/LostElecRATIO_HT3[inj*3+inb]->Integral());
      if (LostElecRATIO_HT23[inj*3+inb]->Integral()>0) LostElecRATIO_HT23[inj*3+inb]->Scale(1/LostElecRATIO_HT23[inj*3+inb]->Integral());
      LostElecRATIO_HT12[inj*3+inb]->Write();
      LostElecRATIO_HT3[inj*3+inb]->Write();
      LostElecRATIO_HT23[inj*3+inb]->Write();
      LostLepRATIO_HT12[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT12[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT12[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostLepRATIO_HT3[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT3[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT3[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      LostLepRATIO_HT23[inj*3+inb]->SetBinContent(nEXTRAPBins, LostLepRATIO_HT23[inj*3+inb]->IntegralAndError(nEXTRAPBins,nEXTRAPBins+1,erro));
      LostLepRATIO_HT23[inj*3+inb]->SetBinError(nEXTRAPBins, erro);
      if (LostLepRATIO_HT12[inj*3+inb]->Integral()>0) LostLepRATIO_HT12[inj*3+inb]->Scale(1/LostLepRATIO_HT12[inj*3+inb]->Integral());
      if (LostLepRATIO_HT3[inj*3+inb]->Integral()>0) LostLepRATIO_HT3[inj*3+inb]->Scale(1/LostLepRATIO_HT3[inj*3+inb]->Integral());
      if (LostLepRATIO_HT23[inj*3+inb]->Integral()>0) LostLepRATIO_HT23[inj*3+inb]->Scale(1/LostLepRATIO_HT23[inj*3+inb]->Integral());
      LostLepRATIO_HT12[inj*3+inb]->Write();
      LostLepRATIO_HT3[inj*3+inb]->Write();
      LostLepRATIO_HT23[inj*3+inb]->Write();   
    }
  }
  outPutFile->cd();
  outPutFile->Close();
}
