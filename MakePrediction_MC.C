#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


void MakePrediction_MC()
{
  
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L Prediction.C+");
  
  TChain *Effchain[8];
  for(Int_t i=0; i<8; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }
  

  // Displayed are number of events equivalent to 3fb-1 of data. Note: Referred trees have baseline selection applied!!!
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //355644

  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //19823
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //69479
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //64605

  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //1406
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //2649
  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //9600
  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //9603

  Effchain[0]->Process("Prediction", "Prediction_MC/Prediction_0.root", 355644); // folder already has to exist for the time beeing...
  Effchain[1]->Process("Prediction", "Prediction_MC/Prediction_1.root", 19823); 
  Effchain[2]->Process("Prediction", "Prediction_MC/Prediction_2.root", 69479); 
  Effchain[3]->Process("Prediction", "Prediction_MC/Prediction_3.root", 64605); 
  Effchain[4]->Process("Prediction", "Prediction_MC/Prediction_4.root", 1406); 
  Effchain[5]->Process("Prediction", "Prediction_MC/Prediction_5.root", 2649); 
  Effchain[6]->Process("Prediction", "Prediction_MC/Prediction_6.root", 9600); 
  Effchain[7]->Process("Prediction", "Prediction_MC/Prediction_7.root", 9603); 

  // Merge output
  TChain ch("LostLeptonPrediction");
  for(Int_t i=0; i<8; i++) ch.Add(TString::Format("Prediction_MC/Prediction_%d.root",i));

  ch.Merge("Prediction_MC.root");
  
}
