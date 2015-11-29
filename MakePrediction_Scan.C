#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction.h"

void MakePrediction_Scan()
{
	gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

    gROOT->ProcessLine(".L Prediction.C+");

	int nChains = 1;
	TChain *Effchain[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain[i] = new TChain("tree");
	}   

	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T1tttt_*.root");
	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T1tttt_*.root");

	//Effchain[0]->Process("Prediction", "Prediction_Scan/Prediction_Scan_T1tttt_1.root", 1000000, 0);
	//Effchain[0]->Process("Prediction", "Prediction_Scan/Prediction_Scan_T1tttt_2.root", TChain::kBigNumber, 1000001);

	Effchain[0]->Process("Prediction", TString::Format("Prediction_Scan/Prediction_Scan_T1tttt_%d.root", 0), 200000, 0);
	for(int i = 1; i < 50; ++i){
		Effchain[0]->Process("Prediction", TString::Format("Prediction_Scan/Prediction_Scan_T1tttt_%d.root", i), 200000*(i+1), 200000*i+1);
	}
}
