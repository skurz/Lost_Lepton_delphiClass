#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


void MakePrediction()
{
  bool useTProof = false;
  TProof *proof = NULL;

  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");
  Effchain->Add("/eos/uscms/store/user/jbradmil/lldev/13TeV_25ns20PU.TTJets_SingleLeptFromTbar*.root");

  if(useTProof){
    proof = TProof::Open("workers=10");
    Effchain->SetProof();     	
  }

  Effchain->Process("Prediction.C++g");

  delete proof;
}
