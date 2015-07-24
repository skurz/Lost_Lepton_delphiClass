#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"
void MakeEff()
{
	TChain *Effchain = new TChain("LostLeptonExpectation");
	Effchain->Add("Expectation.root");
	Effchain->Process("EffMaker.C+");
}
