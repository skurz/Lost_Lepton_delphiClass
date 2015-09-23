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

void MakeExpectation_separate()
{
  
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L ExpecMaker.C+");
  
  TChain *Effchain[13];
  for(Int_t i=0; i<13; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_v1/*.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_ext1-v1/*.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9-v2/*.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9_ext1-v1/*.root");

  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_DiLept_TuneCUETP8M1_V9-v2/*.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_DiLept_TuneCUETP8M1_V9_ext1-v1/*.root");

  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); 
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); 

  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); 

  for(Int_t i=0; i<13; i++){
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i != 1 && i != 3 && i != 5)    Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d.root",i)); // folder already has to exist for the time beeing...
    else{
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_1.root",i), 4000000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_2.root",i), TChain::kBigNumber, 4000001);
    }
  }
/*
  // Merge output
  TChain ch("LostLeptonExpectation");
  std::cout<<"Merging output"<<std::endl;
  for(Int_t i=0; i<11; i++){
    if(i != 1 && i != 3) ch.Add(TString::Format("/nfs/dust/cms/user/kurzsimo/LostLepton/Expectations_0309_highStat/Expectation_separate/Expectation_%d.root",i));
    else{
      ch.Add(TString::Format("/nfs/dust/cms/user/kurzsimo/LostLepton/Expectations_0309_highStat/Expectation_separate/Expectation_%d_1.root",i));
      ch.Add(TString::Format("/nfs/dust/cms/user/kurzsimo/LostLepton/Expectations_0309_highStat/Expectation_separate/Expectation_%d_2.root",i));
    }
  }
  ch.Merge("Expectation.root");
*/
}
