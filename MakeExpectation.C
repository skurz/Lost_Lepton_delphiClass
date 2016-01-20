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
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v5/TTJets_SingleLeptFromT.root");

  //Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_v1/*.root");
  //Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromT_TuneCUETP8M1_V9_ext1-v1/*.root");
  //Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9-v2/*.root");
  //Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_SingleLeptFromTbar_TuneCUETP8M1_V9_ext1-v1/*.root");

//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");

////  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
////  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");

  if(useTProof){
    Effchain->SetProof();
  }

  Effchain->Process("ExpecMaker.C++g", "Expectation_test.root"); //specify output path/file here // folder already has to exist for the time beeing...
  // No HT cut: Effchain->Process("ExpecMaker.C++g", "outputFile.root");
  // HT cut: Effchain->Process("ExpecMaker.C++g", "outputFile.root, genHTcut");
  // for Jacks Syntax (outputname based on input) use: Effchain->Process("ExpecMaker.C++g", "*, genHTcut");

  delete proof;

}
