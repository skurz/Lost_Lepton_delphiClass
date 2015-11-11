#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction.h"

void MakePrediction_Signal()
{
	gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

    gROOT->ProcessLine(".L Prediction.C+");

	int nChains = 6;
	TChain *Effchain[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain[i] = new TChain("TreeMaker2/PreSelection");
	}   

	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1tttt_mGluino-1200_mLSP-800*.root");
	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1tttt_mGluino-1500_mLSP-100*.root");
	Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1bbbb_mGluino-1000_mLSP-900*.root");
	Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1bbbb_mGluino-1500_mLSP-100*.root");
	Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1qqqq_mGluino-1000_mLSP-800*.root");
	Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/signal_v3/*SMS-T1qqqq_mGluino-1400_mLSP-100*.root");

	Effchain[0]->Process("Prediction", "Prediction_signal_T1tttt_1200_800.root");
	Effchain[1]->Process("Prediction", "Prediction_signal_T1tttt_1500_100.root");
	Effchain[2]->Process("Prediction", "Prediction_signal_T1bbbb_1000_900.root");
	Effchain[3]->Process("Prediction", "Prediction_signal_T1bbbb_1500_100.root");
	Effchain[4]->Process("Prediction", "Prediction_signal_T1qqqq_1000_800.root");
	Effchain[5]->Process("Prediction", "Prediction_signal_T1qqqq_1400_100.root");

}
