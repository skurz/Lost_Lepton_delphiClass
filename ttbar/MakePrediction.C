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

  gROOT->ProcessLine(".L Prediction.C+");
  
  int nChains = 7;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_SingleLeptFromT.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_SingleLeptFromTbar.root");

  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_DiLept.root");

  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_HT-600to800.root");
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_HT-800to1200.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_HT-1200to2500.root");
  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_HT-2500toInf.root");


  for(Int_t i=0; i<nChains; i++){ //i<nChains i>2
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i > 2)    Effchain[i]->Process("Prediction", TString::Format("ttbar/Prediction_%d.root",i));
    else Effchain[i]->Process("Prediction", TString::Format("ttbar/Prediction_%d.root, 600",i)); // folder already has to exist for the time beeing...
    
  }
}
