#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "ExpecMaker.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeExpectation()
{
  bool useTProof = false;

  TProof *proof = NULL;
  if(useTProof){
    proof = TProof::Open("lite://", "workers=2");
  }
  
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
  
  TChain *Effchain = new TChain("PreSelection");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_SingleLeptFromTbar.root");


  if(useTProof){
    Effchain->SetProof();
  }

  Effchain->Process("ExpecMaker.C++g", "Expectation.root"); //specify output path/file here // folder already has to exist for the time beeing...
  // No HT cut: Effchain->Process("ExpecMaker.C++g", "outputFile.root");
  // HT cut: Effchain->Process("ExpecMaker.C++g", "outputFile.root, genHTcut");
  // for Jacks Syntax (outputname based on input) use: Effchain->Process("ExpecMaker.C++g", "*, genHTcut");

  delete proof;

}
