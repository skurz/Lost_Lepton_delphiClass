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
  
  int nChains = 20;
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

  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-200To400.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-400To600.root"); 
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-600To800.root"); 
  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-800To1200.root"); 
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-1200To2500.root"); 
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/WJetsToLNu_HT-2500ToInf.root"); 

  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/ST_all.root");

  Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTTT.root");
  Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTV.root");
  Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTH.root");
  Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VV.root");
  Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VVV.root");
  Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/VH.root");

  

  for(Int_t i=0; i<nChains; i++){ // i<nChains
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i > 2){ //2
      //Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d.root",i)); // folder already has to exist for the time beeing...
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_1.root",i), 300000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_2.root",i), TChain::kBigNumber, 300001);
    }else{
      //Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d.root, 600",i));
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_1.root, 600",i), 300000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_2.root, 600",i), TChain::kBigNumber, 300001);
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
