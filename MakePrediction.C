#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


void MakePrediction()
{
  bool useTProof = false;
  TProof *proof = NULL;

  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
  
  TChain *Effchain = new TChain("tree");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-600to800.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-600to800.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-800to1200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-800to1200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-1200to2500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-1200to2500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZJetsToNuNu_HT-2500toInf.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZJetsToNuNu_HT-2500toInf.root");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_DYJetsToLL_M-50_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_DYJetsToLL_M-50_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_DYJetsToLL_M-50_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_DYJetsToLL_M-50_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_DYJetsToLL_M-50_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_DYJetsToLL_M-50_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_DYJetsToLL_M-50_HT-600toInf.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_DYJetsToLL_M-50_HT-600toInf.root");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_GJets_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_GJets_HT-100to200.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_GJets_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_GJets_HT-200to400.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_GJets_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_GJets_HT-400to600.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_GJets_HT-600toInf.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_GJets_HT-600toInf.root");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-200to300.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-200to300.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-300to500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-300to500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-500to700.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-500to700.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-700to1000.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-700to1000.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-1000to1500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-1000to1500.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-1500to2000.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-1500to2000.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_QCD_HT-2000toInf.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_QCD_HT-2000toInf.root");
/*
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WWTo1L1Nu2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WWTo1L1Nu2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WWTo2L2Nu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WWTo2L2Nu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WZTo1L1Nu2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WZTo1L1Nu2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WZTo1L3Nu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WZTo1L3Nu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZZTo2L2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZZTo2L2Q.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZZTo2Q2Nu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZZTo2Q2Nu.root");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WWZ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WWZ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_WZZ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_WZZ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_ZZZ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_ZZZ.root");

  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTTT.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTTT.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTGJets.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTGJets.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTWJetsToLNu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTWJetsToLNu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTWJetsToQQ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTWJetsToQQ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTZToLLNuNu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTZToLLNuNu.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLe/tree_TTZToQQ.root");
  Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v7/SLm/tree_TTZToQQ.root");
*/

  if(useTProof){
    proof = TProof::Open("workers=2");
    Effchain->SetProof();     	
  }

  Effchain->Process("Prediction.C++g", "Prediction_other.root"); //specify output path/file here
  // No HT cut: Effchain->Process("Prediction.C++g", "outputFile.root");
  // HT cut: Effchain->Process("Prediction.C++g", "outputFile.root, genHTcut");
  // for Jacks Syntax (outputname based on input) use: Effchain->Process("Prediction.C++g", "*, genHTcut");

  delete proof;
}
