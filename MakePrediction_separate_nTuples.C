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


void MakePrediction_separate_nTuples()
{
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L Prediction.C+");
  
  const int nChains = 19;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_SingleLeptFromT.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_SingleLeptFromTbar.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_DiLept.root");
  
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_HT-600to800.root");
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_HT-800to1200.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_HT-1200to2500.root");
  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/TTJets_HT-2500toInf.root");

  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-100to200.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-200to400.root");
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-400to600.root");
  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-600to800.root");
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-800to1200.root");
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-1200to2500.root");
  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/WJetsToLNu_HT-2500toInf.root");

  Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/ST_s-channel.root");
  Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/ST_t-channel_antitop.root");
  Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/ST_t-channel_top.root");
  Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/ST_tW_antitop.root");
  Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v7_baseline/ST_tW_top.root");


  for(Int_t i=0; i<nChains; i++){ //i<nChains i>2
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i>2)    Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root",i));
    else Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root, 600",i)); // folder already has to exist for the time beeing...
    
  }
}
