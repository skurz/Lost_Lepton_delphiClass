#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "ExpecMaker.h"
//#include "EffMaker.h"
using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeExpectation()
{

  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
  gROOT->ProcessLine(".L ExpecMaker.C+");
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");
  Effchain->Add("/eos/uscms/store/user/jbradmil/lldev/13TeV_25ns20PU.TTJets_SingleLeptFromTbar*ext*SIM_90*.root");
  
  ExpecMaker* expmkr = new ExpecMaker(Effchain);
  expmkr->Loop();

}
