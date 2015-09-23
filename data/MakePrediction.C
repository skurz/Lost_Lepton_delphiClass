#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"
void MakePrediction()
{
	bool useTProof = false;

	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
	//Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_commissioning_JECv4/Run2015B-17Jul2015-v1_50ns_251162-251562/*.root");
	//Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_commissioning_JECv4/Run2015B-PromptReco-v1_50ns_251563-251883/*.root");

//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //355644

//    Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //19823
//    Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //69479
//    Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root"); //64605

//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //1406
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //2649
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //9600
	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_0309/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root"); //9603



	TProof *proof = NULL;

    if(useTProof){
    	proof = TProof::Open("workers=10");
    	Effchain->SetProof();     	
    }

	Effchain->Process("./../Prediction.C++g", "", 9603);

    delete proof;
}
