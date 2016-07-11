#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include "TROOT.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


// module load pod
// set-up master: pod-server start
// run workers: pod-submit -n 2 -r ge       // -q default.q
// check status: pod-info -n
// -> run code
// pod-server stop

void run_ApplyBaseline()
{
  TProof *proof = TProof::Open("lite://", "workers=20"); //"pod://"  "workers=10"
//  TProof *proof = TProof::Open("pod://"); //"pod://"  "workers=10"

  proof->SetParameter("PROOF_UseMergers", 0);

  gSystem->Load("libPhysics.so");
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");

  Effchain->SetProof();
 
  TString fileNamesT_i[3] = {"TTJets_SingleLeptFromT", "TTJets_SingleLeptFromTbar", "TTJets_DiLept"};
  TString fileNamesT_HT[4] = {"TTJets_HT-600to800", "TTJets_HT-800to1200", "TTJets_HT-1200to2500", "TTJets_HT-2500toInf"};
  TString fileNamesW[7] = {"WJetsToLNu_HT-100to200", "WJetsToLNu_HT-200to400", "WJetsToLNu_HT-400to600", "WJetsToLNu_HT-600to800", "WJetsToLNu_HT-800to1200", "WJetsToLNu_HT-1200to2500", "WJetsToLNu_HT-2500toInf"};
  TString fileNamesST[5] = {"ST_s-channel", "ST_t-channel_antitop", "ST_t-channel_top", "ST_tW_antitop", "ST_tW_top"};
  TString fileNamesExo[3] = {"TTGJets", "TTZToLLNuNu", "TTZToQQ"};

//!!!! Apply madHT cut here!!!!
//  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.TTJets_SingleLeptFromT_*-pythia8_?_RA2AnalysisTree.root");
//  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.TTJets_SingleLeptFromT_*-pythia8_??_RA2AnalysisTree.root");
//  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.TTJets_SingleLeptFromT_*-pythia8_???_RA2AnalysisTree.root");
  //Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.TTJets_SingleLeptFromT_*ext1_*.root");

//  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.TTJets_SingleLeptFromT_*.root");
//    Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_SingleLeptFromTbar_*.root");
//    Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_DiLept*.root");

  //!!!! Remove madHT cut here!!!!  
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_HT-600to800*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_HT-800to1200*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_HT-1200to2500*.root");
//    Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTJets_HT-2500toInf*.root");

  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-100To200*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-200To400*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-400To600*.root");
//    Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring15v2.WJetsToLNu_HT-600To800*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-800To1200*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-1200To2500*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.WJetsToLNu_HT-2500ToInf*.root");

  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.ST_s-channel*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.ST_t-channel_antitop*.root");
    Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV8/Spring15v2.ST_t-channel_top*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.ST_tW_antitop*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.ST_tW_top*.root");

  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTGJets*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTZToLLNuNu*.root");
  //  Effchain->Add("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV7/Spring16.TTZToQQ*.root");
  
  Effchain->Process("ApplyBaseline.C++g", TString("/eos/uscms/store/user/skurz/central_v8_baseline/")+fileNamesST[2]+TString(".root"));

}
