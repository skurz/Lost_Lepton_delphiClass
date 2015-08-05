#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"
void MakeExpectation()
{
	bool useTProof = false;

 	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");

//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/*.root");

////	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
////	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_spring15_3fb_bTags/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/*.root");				
	
	TProof *proof = NULL;

    if(useTProof){
    	proof = TProof::Open("workers=10");
    	Effchain->SetProof();     	
    }

	Effchain->Process("./../ExpecMaker.C++g");

    delete proof;
}
