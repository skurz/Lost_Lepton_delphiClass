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


void MakePrediction_separate()
{
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L Prediction.C+");
  
  int nChains = 21;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_SingleLeptFromT-v1/*.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_SingleLeptFromT_ext1-v1/*.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_SingleLeptFromTbar-v2/*.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_SingleLeptFromTbar_ext1-v1/*.root");

  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_DiLept-v2/*.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_DiLept_ext1-v1/*.root");

  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_HT-600to800/*.root");
  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_HT-800to1200/*.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_HT-1200to2500/*.root");
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/TTJets_HT-2500toInf/*.root");

  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-200To400/*.root");
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-400To600/*.root"); 
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-600To800/*.root"); 
  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-800To1200/*.root"); 
  Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-1200To2500/*.root"); 
  Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/WJetsToLNu_HT-2500ToInf/*.root"); 

  Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/ST_t-channel_antitop_4f_leptonDecays/*.root");
  Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/ST_t-channel_top_4f_leptonDecays/*.root");
  Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/ST_tW_antitop_5f_inclusiveDecays/*.root");
  Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/ST_tW_top_5f_inclusiveDecays/*.root"); 
  Effchain[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_V2/ST_s-channel_4f_leptonDecays/*.root");


  for(Int_t i=0; i<nChains; i++){
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i > 6)    Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root",i));
    else Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root, 600",i)); // folder already has to exist for the time beeing...
    
  }
}
