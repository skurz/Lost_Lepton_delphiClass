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
	TChain *Effchain1[nChains];
	TChain *Effchain2[nChains];
	TChain *Effchain3[nChains];
	for(Int_t i=0; i<nChains; i++){
	  Effchain1[i] = new TChain("tree");
	  Effchain2[i] = new TChain("tree");
	  Effchain3[i] = new TChain("tree");
	}   

	// T2tt
	Effchain1[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_1??_*.root");
	Effchain1[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_1??_*.root");
	Effchain1[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_2??_*.root");
	Effchain1[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_2??_*.root");
	Effchain1[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_3??_*.root");
	Effchain1[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_3??_*.root");
	Effchain1[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_4??_*.root");
	Effchain1[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_4??_*.root");
	Effchain1[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_5??_*.root");
	Effchain1[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_5??_*.root");

	Effchain1[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_6??_*.root");
	Effchain1[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_6??_*.root");
	Effchain1[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_7??_*.root");
	Effchain1[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_7??_*.root");
	Effchain1[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_8??_*.root");
	Effchain1[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_8??_*.root");
	Effchain1[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_9??_*.root");
	Effchain1[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_9??_*.root");
	Effchain1[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_10??_*.root");
	Effchain1[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_10??_*.root");

	Effchain1[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_11??_*.root");
	Effchain1[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_11??_*.root");
	Effchain1[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_12??_*.root");
	Effchain1[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_12??_*.root");
	Effchain1[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_13??_*.root");
	Effchain1[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_13??_*.root");
	Effchain1[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_14??_*.root");
	Effchain1[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_14??_*.root");
	Effchain1[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_15??_*.root");
	Effchain1[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_15??_*.root");

	Effchain1[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_16??_*.root");
	Effchain1[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_16??_*.root");
	Effchain1[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_17??_*.root");
	Effchain1[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_17??_*.root");
	Effchain1[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_18??_*.root");
	Effchain1[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_18??_*.root");
	Effchain1[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_19??_*.root");
	Effchain1[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_19??_*.root");
	Effchain1[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_20??_*.root");
	Effchain1[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_20??_*.root");
	Effchain1[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_21??_*.root");
	Effchain1[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_21??_*.root");
	Effchain1[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_22??_*.root");
	Effchain1[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_22??_*.root");
	Effchain1[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_23??_*.root");
	Effchain1[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_23??_*.root");
	Effchain1[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_24??_*.root");
	Effchain1[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_24??_*.root");
	Effchain1[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T2tt_25??_*.root");
	Effchain1[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T2tt_25??_*.root");

	// T1tttt
	Effchain2[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_1??_*.root");
	Effchain2[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_1??_*.root");
	Effchain2[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_2??_*.root");
	Effchain2[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_2??_*.root");
	Effchain2[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_3??_*.root");
	Effchain2[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_3??_*.root");
	Effchain2[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_4??_*.root");
	Effchain2[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_4??_*.root");
	Effchain2[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_5??_*.root");
	Effchain2[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_5??_*.root");

	Effchain2[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_6??_*.root");
	Effchain2[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_6??_*.root");
	Effchain2[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_7??_*.root");
	Effchain2[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_7??_*.root");
	Effchain2[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_8??_*.root");
	Effchain2[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_8??_*.root");
	Effchain2[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_9??_*.root");
	Effchain2[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_9??_*.root");
	Effchain2[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_10??_*.root");
	Effchain2[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_10??_*.root");

	Effchain2[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_11??_*.root");
	Effchain2[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_11??_*.root");
	Effchain2[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_12??_*.root");
	Effchain2[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_12??_*.root");
	Effchain2[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_13??_*.root");
	Effchain2[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_13??_*.root");
	Effchain2[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_14??_*.root");
	Effchain2[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_14??_*.root");
	Effchain2[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_15??_*.root");
	Effchain2[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_15??_*.root");

	Effchain2[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_16??_*.root");
	Effchain2[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_16??_*.root");
	Effchain2[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_17??_*.root");
	Effchain2[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_17??_*.root");
	Effchain2[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_18??_*.root");
	Effchain2[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_18??_*.root");
	Effchain2[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_19??_*.root");
	Effchain2[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_19??_*.root");
	Effchain2[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_20??_*.root");
	Effchain2[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_20??_*.root");
	Effchain2[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_21??_*.root");
	Effchain2[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_21??_*.root");
	Effchain2[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_22??_*.root");
	Effchain2[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_22??_*.root");
	Effchain2[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_23??_*.root");
	Effchain2[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_23??_*.root");
	Effchain2[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_24??_*.root");
	Effchain2[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_24??_*.root");
	Effchain2[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T1tttt_25??_*.root");
	Effchain2[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T1tttt_25??_*.root");

	// T5qqqqVV
	Effchain3[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_1??_*.root");
	Effchain3[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_1??_*.root");
	Effchain3[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_2??_*.root");
	Effchain3[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_2??_*.root");
	Effchain3[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_3??_*.root");
	Effchain3[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_3??_*.root");
	Effchain3[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_4??_*.root");
	Effchain3[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_4??_*.root");
	Effchain3[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_5??_*.root");
	Effchain3[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_5??_*.root");

	Effchain3[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_6??_*.root");
	Effchain3[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_6??_*.root");
	Effchain3[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_7??_*.root");
	Effchain3[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_7??_*.root");
	Effchain3[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_8??_*.root");
	Effchain3[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_8??_*.root");
	Effchain3[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_9??_*.root");
	Effchain3[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_9??_*.root");
	Effchain3[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_10??_*.root");
	Effchain3[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_10??_*.root");

	Effchain3[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_11??_*.root");
	Effchain3[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_11??_*.root");
	Effchain3[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_12??_*.root");
	Effchain3[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_12??_*.root");
	Effchain3[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_13??_*.root");
	Effchain3[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_13??_*.root");
	Effchain3[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_14??_*.root");
	Effchain3[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_14??_*.root");
	Effchain3[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_15??_*.root");
	Effchain3[14]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_15??_*.root");

	Effchain3[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_16??_*.root");
	Effchain3[15]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_16??_*.root");
	Effchain3[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_17??_*.root");
	Effchain3[16]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_17??_*.root");
	Effchain3[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_18??_*.root");
	Effchain3[17]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_18??_*.root");
	Effchain3[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_19??_*.root");
	Effchain3[18]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_19??_*.root");
	Effchain3[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_20??_*.root");
	Effchain3[19]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_20??_*.root");
	Effchain3[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_21??_*.root");
	Effchain3[20]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_21??_*.root");
	Effchain3[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_22??_*.root");
	Effchain3[21]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_22??_*.root");
	Effchain3[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_23??_*.root");
	Effchain3[22]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_23??_*.root");
	Effchain3[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_24??_*.root");
	Effchain3[23]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_24??_*.root");
	Effchain3[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLm/tree_T5qqqqVV_25??_*.root");
	Effchain3[24]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/scan/SLe/tree_T5qqqqVV_25??_*.root");

	// T2tt
	for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain1[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T2tt_%d.root", (i+1)*100));
    }

    // T1tttt
    for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain2[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T1tttt_%d.root", (i+1)*100));
    }

    // T5qqqqVV
    for(Int_t i=0; i<nChains; i++){ // i<nChains
    	std::cout<<"Processing Tree: "<<i<<std::endl;
    	Effchain3[i]->Process("Prediction_isoTrackFact", TString::Format("Prediction_Scan/Prediction_Scan_T5qqqqVV_%d.root", (i+1)*100));
    }
}
