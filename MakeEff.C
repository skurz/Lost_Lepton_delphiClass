#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeEff()
{
    gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
    gROOT->ProcessLine(".L EffMaker.C+");
    TChain *Effchain = new TChain("LostLeptonExpectation");
    Effchain->Add("Expectation.root");

    EffMaker* effmkr = new EffMaker(Effchain);
    effmkr->Loop();
}
