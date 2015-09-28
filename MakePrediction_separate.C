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

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_v1/*.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_ext1-v1/*.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9-v2/*.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9_ext1-v1/*.root");

  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_DiLept_TuneCUETP8M1_V9-v2/*.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_DiLept_TuneCUETP8M1_V9_ext1-v1/*.root");

  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_HT-600to800_TuneCUETP8M1_13TeV/*.root");
  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_HT-800to1200_TuneCUETP8M1_13TeV/*.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV/*.root");
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV/*.root");

  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV/*.root");
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV/*.root"); 
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV/*.root"); 
  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV/*.root"); 
  Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV/*.root"); 
  Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV/*.root"); 

  Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); 
  Effchain[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_activity_2409/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/*.root"); 


  for(Int_t i=0; i<nChains; i++){
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i > 6)    Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root",i));
    else Effchain[i]->Process("Prediction", TString::Format("Prediction_separate/Prediction_%d.root, 600",i)); // folder already has to exist for the time beeing...
    
  }
}
