#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TSystem.h"
#include "TEnv.h"

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

void run_ApplyBaseline_script(std::string outName, std::string inFiles)
{
  gEnv->SetValue("ProofLite.Sandbox", "/nfs/dust/cms/user/kurzsimo/.proof/");

  TProof *proof = TProof::Open("lite://", "workers=5"); //"pod://"  "workers=10"
  //TProof *proof = TProof::Open("pod://"); //"pod://"  "workers=10"

  // Fast merging
  proof->SetParameter("PROOF_UseMergers", (Int_t)0);
 
  gSystem->Load("libPhysics.so");
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");

  Effchain->SetProof();

  Effchain->Add(TString("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12/")+TString(inFiles));
 
  Effchain->Process("ApplyBaseline.C++g", TString("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/")+TString(outName)+TString(".root"));

}
