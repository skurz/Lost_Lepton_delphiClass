#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Prediction_isoTrackFact.h"

void MakePrediction_Scan_mixed()
{
	gSystem->Load("libPhysics.so");
    gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

    gROOT->ProcessLine(".L Prediction_isoTrackFact.C+");

	int nChains = 25;
	TChain *Effchain1[nChains];
	TChain *Effchain2[nChains];
	TChain *Effchain3[nChains];
	TChain *Effchain4[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain1[i] = new TChain("tree");
	  Effchain2[i] = new TChain("tree");
	  Effchain3[i] = new TChain("tree");
	  Effchain4[i] = new TChain("tree");
	}   

	// T1tbtt
	Effchain1[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_1??_*.root");
	Effchain1[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_1??_*.root");
	Effchain1[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_2??_*.root");
	Effchain1[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_2??_*.root");
	Effchain1[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_3??_*.root");
	Effchain1[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_3??_*.root");
	Effchain1[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_4??_*.root");
	Effchain1[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_4??_*.root");
	Effchain1[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_5??_*.root");
	Effchain1[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_5??_*.root");

	Effchain1[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_6??_*.root");
	Effchain1[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_6??_*.root");
	Effchain1[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_7??_*.root");
	Effchain1[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_7??_*.root");
	Effchain1[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_8??_*.root");
	Effchain1[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_8??_*.root");
	Effchain1[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_9??_*.root");
	Effchain1[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_9??_*.root");
	Effchain1[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_10??_*.root");
	Effchain1[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_10??_*.root");

	Effchain1[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_11??_*.root");
	Effchain1[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_11??_*.root");
	Effchain1[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_12??_*.root");
	Effchain1[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_12??_*.root");
	Effchain1[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_13??_*.root");
	Effchain1[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_13??_*.root");
	Effchain1[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_14??_*.root");
	Effchain1[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_14??_*.root");
	Effchain1[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_15??_*.root");
	Effchain1[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_15??_*.root");

	Effchain1[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_16??_*.root");
	Effchain1[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_16??_*.root");
	Effchain1[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_17??_*.root");
	Effchain1[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_17??_*.root");
	Effchain1[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_18??_*.root");
	Effchain1[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_18??_*.root");
	Effchain1[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_19??_*.root");
	Effchain1[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_19??_*.root");
	Effchain1[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_20??_*.root");
	Effchain1[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_20??_*.root");
	Effchain1[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_21??_*.root");
	Effchain1[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_21??_*.root");
	Effchain1[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_22??_*.root");
	Effchain1[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_22??_*.root");
	Effchain1[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_23??_*.root");
	Effchain1[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_23??_*.root");
	Effchain1[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_24??_*.root");
	Effchain1[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_24??_*.root");
	Effchain1[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtt_25??_*.root");
	Effchain1[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtt_25??_*.root");

	// T1tbtb
	Effchain2[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_1??_*.root");
	Effchain2[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_1??_*.root");
	Effchain2[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_2??_*.root");
	Effchain2[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_2??_*.root");
	Effchain2[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_3??_*.root");
	Effchain2[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_3??_*.root");
	Effchain2[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_4??_*.root");
	Effchain2[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_4??_*.root");
	Effchain2[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_5??_*.root");
	Effchain2[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_5??_*.root");

	Effchain2[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_6??_*.root");
	Effchain2[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_6??_*.root");
	Effchain2[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_7??_*.root");
	Effchain2[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_7??_*.root");
	Effchain2[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_8??_*.root");
	Effchain2[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_8??_*.root");
	Effchain2[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_9??_*.root");
	Effchain2[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_9??_*.root");
	Effchain2[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_10??_*.root");
	Effchain2[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_10??_*.root");

	Effchain2[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_11??_*.root");
	Effchain2[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_11??_*.root");
	Effchain2[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_12??_*.root");
	Effchain2[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_12??_*.root");
	Effchain2[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_13??_*.root");
	Effchain2[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_13??_*.root");
	Effchain2[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_14??_*.root");
	Effchain2[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_14??_*.root");
	Effchain2[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_15??_*.root");
	Effchain2[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_15??_*.root");

	Effchain2[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_16??_*.root");
	Effchain2[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_16??_*.root");
	Effchain2[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_17??_*.root");
	Effchain2[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_17??_*.root");
	Effchain2[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_18??_*.root");
	Effchain2[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_18??_*.root");
	Effchain2[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_19??_*.root");
	Effchain2[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_19??_*.root");
	Effchain2[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_20??_*.root");
	Effchain2[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_20??_*.root");
	Effchain2[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_21??_*.root");
	Effchain2[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_21??_*.root");
	Effchain2[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_22??_*.root");
	Effchain2[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_22??_*.root");
	Effchain2[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_23??_*.root");
	Effchain2[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_23??_*.root");
	Effchain2[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_24??_*.root");
	Effchain2[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_24??_*.root");
	Effchain2[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbtb_25??_*.root");
	Effchain2[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbtb_25??_*.root");

	// T1tbbb
	Effchain3[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_1??_*.root");
	Effchain3[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_1??_*.root");
	Effchain3[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_2??_*.root");
	Effchain3[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_2??_*.root");
	Effchain3[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_3??_*.root");
	Effchain3[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_3??_*.root");
	Effchain3[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_4??_*.root");
	Effchain3[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_4??_*.root");
	Effchain3[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_5??_*.root");
	Effchain3[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_5??_*.root");

	Effchain3[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_6??_*.root");
	Effchain3[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_6??_*.root");
	Effchain3[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_7??_*.root");
	Effchain3[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_7??_*.root");
	Effchain3[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_8??_*.root");
	Effchain3[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_8??_*.root");
	Effchain3[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_9??_*.root");
	Effchain3[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_9??_*.root");
	Effchain3[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_10??_*.root");
	Effchain3[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_10??_*.root");

	Effchain3[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_11??_*.root");
	Effchain3[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_11??_*.root");
	Effchain3[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_12??_*.root");
	Effchain3[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_12??_*.root");
	Effchain3[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_13??_*.root");
	Effchain3[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_13??_*.root");
	Effchain3[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_14??_*.root");
	Effchain3[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_14??_*.root");
	Effchain3[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_15??_*.root");
	Effchain3[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_15??_*.root");

	Effchain3[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_16??_*.root");
	Effchain3[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_16??_*.root");
	Effchain3[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_17??_*.root");
	Effchain3[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_17??_*.root");
	Effchain3[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_18??_*.root");
	Effchain3[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_18??_*.root");
	Effchain3[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_19??_*.root");
	Effchain3[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_19??_*.root");
	Effchain3[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_20??_*.root");
	Effchain3[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_20??_*.root");
	Effchain3[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_21??_*.root");
	Effchain3[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_21??_*.root");
	Effchain3[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_22??_*.root");
	Effchain3[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_22??_*.root");
	Effchain3[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_23??_*.root");
	Effchain3[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_23??_*.root");
	Effchain3[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_24??_*.root");
	Effchain3[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_24??_*.root");
	Effchain3[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tbbb_25??_*.root");
	Effchain3[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tbbb_25??_*.root");

	// T1bbtt
	Effchain4[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_1??_*.root");
	Effchain4[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_1??_*.root");
	Effchain4[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_2??_*.root");
	Effchain4[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_2??_*.root");
	Effchain4[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_3??_*.root");
	Effchain4[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_3??_*.root");
	Effchain4[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_4??_*.root");
	Effchain4[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_4??_*.root");
	Effchain4[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_5??_*.root");
	Effchain4[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_5??_*.root");

	Effchain4[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_6??_*.root");
	Effchain4[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_6??_*.root");
	Effchain4[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_7??_*.root");
	Effchain4[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_7??_*.root");
	Effchain4[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_8??_*.root");
	Effchain4[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_8??_*.root");
	Effchain4[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_9??_*.root");
	Effchain4[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_9??_*.root");
	Effchain4[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_10??_*.root");
	Effchain4[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_10??_*.root");

	Effchain4[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_11??_*.root");
	Effchain4[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_11??_*.root");
	Effchain4[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_12??_*.root");
	Effchain4[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_12??_*.root");
	Effchain4[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_13??_*.root");
	Effchain4[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_13??_*.root");
	Effchain4[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_14??_*.root");
	Effchain4[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_14??_*.root");
	Effchain4[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_15??_*.root");
	Effchain4[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_15??_*.root");

	Effchain4[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_16??_*.root");
	Effchain4[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_16??_*.root");
	Effchain4[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_17??_*.root");
	Effchain4[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_17??_*.root");
	Effchain4[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_18??_*.root");
	Effchain4[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_18??_*.root");
	Effchain4[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_19??_*.root");
	Effchain4[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_19??_*.root");
	Effchain4[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_20??_*.root");
	Effchain4[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_20??_*.root");
	Effchain4[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_21??_*.root");
	Effchain4[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_21??_*.root");
	Effchain4[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_22??_*.root");
	Effchain4[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_22??_*.root");
	Effchain4[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_23??_*.root");
	Effchain4[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_23??_*.root");
	Effchain4[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_24??_*.root");
	Effchain4[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_24??_*.root");
	Effchain4[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1bbtt_25??_*.root");
	Effchain4[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1bbtt_25??_*.root");

	// T1tbtt
	for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain1[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T1tbtt_%d.root", (i+1)*100));
    }

    // T1tbtb
    for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain2[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T1tbtb_%d.root", (i+1)*100));
    }

    // T1tbbb
    for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain3[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T1tbbb_%d.root", (i+1)*100));
    }


    // T1bbtt
    for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain4[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T1bbtt_%d.root", (i+1)*100));
    }
}
