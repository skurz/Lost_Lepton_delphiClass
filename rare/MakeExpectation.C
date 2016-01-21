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
  
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L ExpecMaker.C+");
  
  int nChains = 6;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTTT.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTV.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTH.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VV.root");
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VVV.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VH.root");

  

  for(Int_t i=0; i<nChains; i++){ // i<nChains
      std::cout<<"Processing Tree: "<<i<<std::endl;
      Effchain[i]->Process("ExpecMaker", TString::Format("rare/Expectation_%d_1.root",i), 300000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("rare/Expectation_%d_2.root",i), TChain::kBigNumber, 300001);
  }
}
