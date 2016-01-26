#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction.h"


using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


void MakePrediction()
{
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L Prediction.C++g");
  
  int nChains = 6;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-200To400.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-400To600.root"); 
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-600To800.root"); 
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-800To1200.root"); 
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-1200To2500.root"); 
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-2500ToInf.root"); 


  for(Int_t i=0; i<nChains; i++){ //i<nChains i>2
    std::cout<<"Processing Tree: "<<i<<std::endl;
    Effchain[i]->Process("Prediction", TString::Format("wpj/Prediction_%d.root",i));
    
  }
}
