#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include <iostream>

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakePrediction_Signal()
{
	gSystem->Load("libPhysics.so");
	gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

	gROOT->ProcessLine(".L Prediction_isoTrackFact.C+");

	const int nChains = 2;
	TChain *Effchain[nChains];
	for(Int_t i=0; i<nChains; i++){
//		Effchain[i] = new TChain("tree");
		Effchain[i] = new TChain("TreeMaker2/PreSelection");
	}  

//	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/SLe/tree_T1tttt_2000_100.root");
//	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/SLm/tree_T1tttt_2000_100.root");
//	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/SLe/tree_T2tt_850_100.root");
//	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/SLm/tree_T2tt_850_100.root");

	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v12/T1tttt_2000_100.root");
 	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v12/T2tt_850_100.root");

	Effchain[0]->Process("Prediction_isoTrackFact", "/nfs/dust/cms/user/kurzsimo/LostLeptonExpectation_bTagPlotting/Prediction_nTuple_T1tttt_2000_100.root");
	Effchain[1]->Process("Prediction_isoTrackFact", "/nfs/dust/cms/user/kurzsimo/LostLeptonExpectation_bTagPlotting/Prediction_nTuple_T2tt_850_100.root");

}
