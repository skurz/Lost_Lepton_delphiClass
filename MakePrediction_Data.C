#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"
void MakePrediction_Data()
{
	bool useTProof = false;

	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/central_v4_data/*.root");

	TProof *proof = NULL;

    if(useTProof){
    	proof = TProof::Open("workers=10");
    	Effchain->SetProof();     	
    }

	Effchain->Process("Prediction.C++g", "Prediction_data.root");

    delete proof;
}
