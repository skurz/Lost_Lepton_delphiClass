#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include <iostream>

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeExpectation_Signal()
{
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L ExpecMaker.C+");
  
  const int nChains = 2;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v12/T1tttt_2000_100.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v12/T2tt_850_100.root");

  Effchain[0]->Process("ExpecMaker", TString::Format("/nfs/dust/cms/user/kurzsimo/LostLeptonExpectation_bTagPlotting/Expectation_T1tttt_2000_100.root"));
  Effchain[1]->Process("ExpecMaker", TString::Format("/nfs/dust/cms/user/kurzsimo/LostLeptonExpectation_bTagPlotting/Expectation_T2tt_850_100.root"));



}
