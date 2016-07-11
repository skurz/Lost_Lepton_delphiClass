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
  
  const int nChains = 33;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("PreSelection");
  }   

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_SingleLeptFromT.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_SingleLeptFromTbar.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_DiLept.root");
  
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_HT-600to800.root");
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_HT-800to1200.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_HT-1200to2500.root");
  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTJets_HT-2500toInf.root");

  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-100to200.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-200to400.root");
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-400to600.root");
  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-600to800.root");
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-800to1200.root");
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-1200to2500.root");
  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WJetsToLNu_HT-2500toInf.root");

  Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ST_s-channel.root");
  Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ST_t-channel_antitop.root");
  Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ST_t-channel_top.root");
  Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ST_tW_antitop.root");
  Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ST_tW_top.root");

  Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTGJets.root");
  Effchain[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTTT.root");
  Effchain[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTWJetsToLNu.root");
  Effchain[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTWJetsToQQ.root");
  Effchain[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTZToLLNuNu.root");
  Effchain[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/TTZToQQ.root");
  Effchain[25]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WWTo1L1Nu2Q.root");
  Effchain[26]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WWTo2L2Nu.root");
  Effchain[27]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WWZ.root");
  Effchain[28]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WZTo1L1Nu2Q.root");
  Effchain[29]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WZTo1L3Nu.root");
  Effchain[30]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/WZZ.root");
  Effchain[31]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ZZTo2L2Q.root");
  Effchain[32]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v9_baseline/ZZZ.root");
  //Effchain[33]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v8_baseline/ZZTo2Q2Nu.root");


  for(Int_t i=0; i<nChains; i++){ // i<nChains
    std::cout<<"Processing Tree: "<<i<<std::endl;
    if(i>2){ //2
      //Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d.root",i)); // folder already has to exist for the time beeing...
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_1.root",i), 2000000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_2.root",i), TChain::kBigNumber, 2000001);
    }else{
      //Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d.root, 600",i));
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_1.root, 600",i), 2000000, 0);
      Effchain[i]->Process("ExpecMaker", TString::Format("Expectation_separate/Expectation_%d_2.root, 600",i), TChain::kBigNumber, 2000001);
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
