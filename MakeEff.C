#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeEff()
{
  TChain *Effchain = new TChain("LostLeptonExpectation");
  Effchain->Add("Expectation.root");
  Effchain->Process("EffMaker.C+","Efficiencies.root"); //specify output path/file here // folder already has to exist for the time beeing...
}
