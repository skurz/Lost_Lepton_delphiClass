#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
#include <iostream>

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeEff(std::string ExpFile="Expectation.root", std::string EffFile="Efficiencies.root")
{
  TChain *Effchain = new TChain("LostLeptonExpectation");
  Effchain->Add(ExpFile.c_str());
  Effchain->Process("EffMaker.C+", EffFile.c_str());
}
