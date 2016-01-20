#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakePrediction_Scan()
{
	gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

    gROOT->ProcessLine(".L Prediction.C+");

	int nChains = 15;
	TChain *Effchain[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain[i] = new TChain("tree");
	}   

	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_6*_*.root");
	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_6*_*.root");
	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_7*_*.root");
	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_7*_*.root");
	Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_8*_*.root");
	Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_8*_*.root");
	Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_9*_*.root");
	Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_9*_*.root");
	Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_10*_*.root");
	Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_10*_*.root");

	Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_11*_*.root");
	Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_11*_*.root");
	Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_12*_*.root");
	Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_12*_*.root");
	Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_13*_*.root");
	Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_13*_*.root");
	Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_14*_*.root");
	Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_14*_*.root");
	Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_15*_*.root");
	Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_15*_*.root");

	Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_16*_*.root");
	Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_16*_*.root");
	Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_17*_*.root");
	Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_17*_*.root");
	Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_18*_*.root");
	Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_18*_*.root");
	Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_19*_*.root");
	Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_19*_*.root");
	Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLm/tree_T5qqqqVV_20*_*.root");
	Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/scan_v5/SLe/tree_T5qqqqVV_20*_*.root");


	for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain[i]->Process("Prediction", TString::Format("Prediction_Scan/Prediction_Scan_T5qqqqVV_%d.root", (i+6)*100));
    }
}
