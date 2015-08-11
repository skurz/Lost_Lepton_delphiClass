#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"
void MakePrediction()
{
	bool useTProof = false;

	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_45pb/Run2015B-PromptReco-v1/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_golden40pb/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/36pb.root");
	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_commissioning/Run2015B-17Jul2015-v1_50ns_251162-251562_commissioning/*.root");
	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_commissioning/Run2015B-PromptReco-v1_50ns_251563-251883_commissioning/*.root");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_commissioning.root");



	TProof *proof = NULL;

    if(useTProof){
    	proof = TProof::Open("workers=10");
    	Effchain->SetProof();     	
    }

	Effchain->Process("./../Prediction.C++g");

    delete proof;
}
