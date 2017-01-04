#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction_isoTrackFact.h"

void MakePrediction_Scan()
{
	gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

    gROOT->ProcessLine(".L Prediction_isoTrackFact.C+");

	int nChains = 25;
	TChain *Effchain[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain[i] = new TChain("tree");
	}   

	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_1??_*.root");
	Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_1??_*.root");
	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_2??_*.root");
	Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_2??_*.root");
	Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_3??_*.root");
	Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_3??_*.root");
	Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_4??_*.root");
	Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_4??_*.root");
	Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_5??_*.root");
	Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_5??_*.root");

	Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_6??_*.root");
	Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_6??_*.root");
	Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_7??_*.root");
	Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_7??_*.root");
	Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_8??_*.root");
	Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_8??_*.root");
	Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_9??_*.root");
	Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_9??_*.root");
	Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_10??_*.root");
	Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_10??_*.root");

	Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_11??_*.root");
	Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_11??_*.root");
	Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_12??_*.root");
	Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_12??_*.root");
	Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_13??_*.root");
	Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_13??_*.root");
	Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_14??_*.root");
	Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_14??_*.root");
	Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_15??_*.root");
	Effchain[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_15??_*.root");

	Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_16??_*.root");
	Effchain[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_16??_*.root");
	Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_17??_*.root");
	Effchain[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_17??_*.root");
	Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_18??_*.root");
	Effchain[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_18??_*.root");
	Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_19??_*.root");
	Effchain[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_19??_*.root");
	Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_20??_*.root");
	Effchain[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_20??_*.root");
	Effchain[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_21??_*.root");
	Effchain[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_21??_*.root");
	Effchain[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_22??_*.root");
	Effchain[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_22??_*.root");
	Effchain[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_23??_*.root");
	Effchain[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_23??_*.root");
	Effchain[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_24??_*.root");
	Effchain[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_24??_*.root");
	Effchain[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLm/tree_T2tt_25??_*.root");
	Effchain[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v11/scan_genMHT/SLe/tree_T2tt_25??_*.root");


	for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T2tt_%d.root", (i+1)*100));
    }
}
