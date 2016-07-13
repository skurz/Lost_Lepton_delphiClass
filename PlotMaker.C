#include "PlotMaker.h"
#include "TSystem.h"

using std::string;

void initHistograms(Int_t nBins);
void saveHistograms(TFile* tf);

void PlotMaker(string InputPath_Expectation="Expectation.root",
	string InputPath_Efficiencies="Efficiencies.root",
	string InputPath_Prediction="Prediction.root",
	string InputPath_Prediction_Data="Prediction_data.root", // Use same path as above if pure MC prediction wanted
	string OutputPath_Prediction="LLPrediction.root"){
	
	gSystem->Load("libPhysics.so");
	gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");


	 // Present output in QCD binning
	const bool doQCDbinning = false;  //<-check------------------------

	// Weight MC events with bTag probabilities
	const bool doBtagProbabilities = true;

	// Fill MC histograms only (saves time)
	const bool doMConly = false;

	// Prepare Code for Extrapolation Method
	const bool doExtrapolation = false;		// NOT IMPLEMENTED

	// If you want to compare MC to MC set this to true. E.g. prediction with and without signal contamination
	const bool useMCForDataTree = false;	// NOT IMPLEMENTED

	// Scale all MC weights by this factor
	const Double_t scaleFactorWeight = 7632;  // 3998 2585 813  //in units of [pb] //<-check------------------------


	// Init
 	SearchBins * const SearchBins_ = new SearchBins(doQCDbinning);
	const int nSearchBinsTotal = SearchBins_->GetNbins();

	initHistograms(nSearchBinsTotal);

	
	// Begin of Code
	//gROOT->Reset();
	TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation.c_str());
	if (!fExp) {
	  fExp = new TFile(InputPath_Expectation.c_str());
	}
  
	TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");
	setBranchesExpectation(LostLeptonExpectation);


	std::cout<<"Loop on Expectation"<<std::endl;

  	Long64_t nentries = LostLeptonExpectation->GetEntries();
  	for (Long64_t i=0; i<nentries;i++) {
  		LostLeptonExpectation->GetEntry(i);

	    if(doQCDbinning) SearchBin = BinQCD;
	    else SearchBin = Bin;

	    if(SearchBin > 900) continue;


	    // Fill events 4 times if using bTag probabilities
	    int nLoops = 4;
	    if(!doBtagProbabilities){
	      nLoops = 1;
	    }else if(NJets < 3){
	      nLoops = 3;
	    }

	    for(int i = 0; i < nLoops; i++){
	      if(doBtagProbabilities){
	        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
	      }else{
	        Bin_bTags.at(i)=SearchBin;
	      }
	    }

		for(int i = 0; i < nLoops; i++){
		    if(doBtagProbabilities) scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
		    else scaledWeight = Weight * scaleFactorWeight;

		    if(Expectation==1){
		    	totalExp_woIsoTrack_LL_->Fill(Bin_bTags.at(i), scaledWeight);
		    }

		    if(Expectation==1 && ExpectationReductionIsoTrack==0){
		    	totalExp_LL_->Fill(Bin_bTags.at(i), scaledWeight);
		    	nEvtsExp_LL_->Fill(Bin_bTags.at(i));
			}
		}
	}

	fExp->Close();
	std::cout<<"Finished"<<std::endl;


	//gROOT->Reset();
	TFile *fPreMC = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction.c_str());
	if (!fPreMC) {
	fPreMC = new TFile(InputPath_Prediction.c_str());
	}
	TTree* LostLeptonPrediction = (TTree*) fPreMC->Get("LostLeptonPrediction");
	setBranchesPrediction(LostLeptonPrediction, false);


	std::cout<<"Loop on Prediction (MC)"<<std::endl;

	nentries = LostLeptonPrediction->GetEntries();
 	for (Long64_t i=0; i<nentries;i++) {
 		LostLeptonPrediction->GetEntry(i);

	    if(doQCDbinning) SearchBin = BinQCD;
	    else SearchBin = Bin;

	    if(SearchBin > 900) continue;
	    if(MTW>100)continue;
	    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

	    int nLoops = 4;
	    if(!doBtagProbabilities){
	      nLoops = 1;
	    }else if(NJets < 3){
	      nLoops = 3;
	    }

	    for(int i = 0; i < nLoops; i++){
	      if(doBtagProbabilities){
	        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
	      }else{
	        Bin_bTags.at(i)=SearchBin;
	      }
	    }

		//fill event 4 times weighting with the btag probability
		for(int i = 0; i < nLoops; i++){
			double scaleFactorWeightBtagProb;
	        if(doBtagProbabilities){
	          scaleFactorWeightBtagProb = scaleFactorWeight * bTagProb->at(i);
	          scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
	        }else{
	          scaleFactorWeightBtagProb = scaleFactorWeight;
	          scaledWeight = Weight * scaleFactorWeight;
	        }

	        if(nLoops==1){
				totalPred_LL_MC_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightBtagProb/2);
				totalPred_woIsoTrack_LL_MC_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
				avgWeight_LL_MC_->Fill(Bin_bTags.at(i), abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
			}else{
				totalPred_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPred_woIsoTrack_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2);
				avgWeight_LL_MC_->Fill(Bin_bTags.at(i), abs(totalWeight_BTags->at(i)/Weight/2), abs(Weight));
			}

			totalCS_LL_MC_->Fill(Bin_bTags.at(i), scaledWeight);
        	nEvtsCS_LL_MC_->Fill(Bin_bTags.at(i));


        	totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackSysDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackSysDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackSysDown*scaleFactorWeightBtagProb/2);

		    totalPredMuIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackSysDown*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackSysDown*scaleFactorWeightBtagProb/2);
		    totalPredPionIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackSysUp*scaleFactorWeightBtagProb/2);
		    totalPredPionIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackSysDown*scaleFactorWeightBtagProb/2);
		    totalPredMTWSysUp_LL_MC_->Fill(Bin_bTags.at(i), MTWSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMTWSysDown_LL_MC_->Fill(Bin_bTags.at(i), MTWSysDown*scaleFactorWeightBtagProb/2);
		    totalPredPuritySysUp_LL_MC_->Fill(Bin_bTags.at(i), puritySysUp*scaleFactorWeightBtagProb/2);
		    totalPredPuritySysDown_LL_MC_->Fill(Bin_bTags.at(i), puritySysDown*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPuritySysUp_LL_MC_->Fill(Bin_bTags.at(i), singleLepPuritySysUp*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPuritySysDown_LL_MC_->Fill(Bin_bTags.at(i), singleLepPuritySysDown*scaleFactorWeightBtagProb/2);
		    totalPredDiLepFoundSysUp_LL_MC_->Fill(Bin_bTags.at(i), diLepFoundSysUp*scaleFactorWeightBtagProb/2);
		    totalPredDiLepFoundSysDown_LL_MC_->Fill(Bin_bTags.at(i), diLepFoundSysDown*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoSysUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoSysDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoSysDown*scaleFactorWeightBtagProb/2);
		    totalPredMuRecoSysUp_LL_MC_->Fill(Bin_bTags.at(i), muRecoSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMuRecoSysDown_LL_MC_->Fill(Bin_bTags.at(i), muRecoSysDown*scaleFactorWeightBtagProb/2);
		    totalPredMuAccSysUp_LL_MC_->Fill(Bin_bTags.at(i), muAccSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMuAccSysDown_LL_MC_->Fill(Bin_bTags.at(i), muAccSysDown*scaleFactorWeightBtagProb/2);
		    totalPredMuAccQsquareSysUp_LL_MC_->Fill(Bin_bTags.at(i), muAccQsquareSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMuAccQsquareSysDown_LL_MC_->Fill(Bin_bTags.at(i), muAccQsquareSysDown*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoSysUp*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoSysDown*scaleFactorWeightBtagProb/2);
		    totalPredElecRecoSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecRecoSysUp*scaleFactorWeightBtagProb/2);
		    totalPredElecRecoSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecRecoSysDown*scaleFactorWeightBtagProb/2);
		    totalPredElecAccSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecAccSysUp*scaleFactorWeightBtagProb/2);
		    totalPredElecAccSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecAccSysDown*scaleFactorWeightBtagProb/2);
		    totalPredElecAccQsquareSysUp_LL_MC_->Fill(Bin_bTags.at(i), elecAccQsquareSysUp*scaleFactorWeightBtagProb/2);
		    totalPredElecAccQsquareSysDown_LL_MC_->Fill(Bin_bTags.at(i), elecAccQsquareSysDown*scaleFactorWeightBtagProb/2);

		    totalPredIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackStatDown*scaleFactorWeightBtagProb/2);
		    /*    totalPredIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackStatUp*scaleFactorWeightBtagProb/2);
			  totalPredIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackStatDown*scaleFactorWeightBtagProb/2);
			  totalPredIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackStatUp*scaleFactorWeightBtagProb/2);
			  totalPredIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackStatDown*scaleFactorWeightBtagProb/2);
			  totalPredIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackStatUp*scaleFactorWeightBtagProb/2);
			  totalPredIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackStatDown*scaleFactorWeightBtagProb/2);
		    */
		    totalPredMuIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoTrackStatDown*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackStatUp*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoTrackStatDown*scaleFactorWeightBtagProb/2);
		    totalPredPionIsoTrackStatUp_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackStatUp*scaleFactorWeightBtagProb/2);
		    totalPredPionIsoTrackStatDown_LL_MC_->Fill(Bin_bTags.at(i), pionIsoTrackStatDown*scaleFactorWeightBtagProb/2);
		    totalPredMTWStatUp_LL_MC_->Fill(Bin_bTags.at(i), MTWStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMTWStatDown_LL_MC_->Fill(Bin_bTags.at(i), MTWStatDown*scaleFactorWeightBtagProb/2);
		    totalPredPurityStatUp_LL_MC_->Fill(Bin_bTags.at(i), purityStatUp*scaleFactorWeightBtagProb/2);
		    totalPredPurityStatDown_LL_MC_->Fill(Bin_bTags.at(i), purityStatDown*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPurityStatUp_LL_MC_->Fill(Bin_bTags.at(i), singleLepPurityStatUp*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPurityStatDown_LL_MC_->Fill(Bin_bTags.at(i), singleLepPurityStatDown*scaleFactorWeightBtagProb/2);
		    totalPredDiLepFoundStatUp_LL_MC_->Fill(Bin_bTags.at(i), diLepFoundStatUp*scaleFactorWeightBtagProb/2);
		    totalPredDiLepFoundStatDown_LL_MC_->Fill(Bin_bTags.at(i), diLepFoundStatDown*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoStatUp_LL_MC_->Fill(Bin_bTags.at(i), muIsoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMuIsoStatDown_LL_MC_->Fill(Bin_bTags.at(i), muIsoStatDown*scaleFactorWeightBtagProb/2);
		    totalPredMuRecoStatUp_LL_MC_->Fill(Bin_bTags.at(i), muRecoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMuRecoStatDown_LL_MC_->Fill(Bin_bTags.at(i), muRecoStatDown*scaleFactorWeightBtagProb/2);
		    totalPredMuAccStatUp_LL_MC_->Fill(Bin_bTags.at(i), muAccStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMuAccStatDown_LL_MC_->Fill(Bin_bTags.at(i), muAccStatDown*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoStatUp_LL_MC_->Fill(Bin_bTags.at(i), elecIsoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredElecIsoStatDown_LL_MC_->Fill(Bin_bTags.at(i), elecIsoStatDown*scaleFactorWeightBtagProb/2);
		    totalPredElecRecoStatUp_LL_MC_->Fill(Bin_bTags.at(i), elecRecoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredElecRecoStatDown_LL_MC_->Fill(Bin_bTags.at(i), elecRecoStatDown*scaleFactorWeightBtagProb/2);
		    totalPredElecAccStatUp_LL_MC_->Fill(Bin_bTags.at(i), elecAccStatUp*scaleFactorWeightBtagProb/2);
		    totalPredElecAccStatDown_LL_MC_->Fill(Bin_bTags.at(i), elecAccStatDown*scaleFactorWeightBtagProb/2);

		    //totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
		    //totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

		    //totalPropSysUp_LL_MC_->Fill(Bin_bTags.at(i), totalPropSysUp*scaleFactorWeightBtagProb/2);
		    //totalPropSysDown_LL_MC_->Fill(Bin_bTags.at(i), totalPropSysDown*scaleFactorWeightBtagProb/2)
	   	}
	}

	fPreMC->Close();    
	std::cout<<"Finished"<<std::endl;


	if(!doMConly){
		//Prediction Data Tree
		//gROOT->Reset();
		TFile *fPre = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction_Data.c_str());
		if (!fPre) {
		fPre = new TFile(InputPath_Prediction_Data.c_str());
		}
		TTree* LostLeptonPredictionData = (TTree*) fPre->Get("LostLeptonPrediction");
		setBranchesPrediction(LostLeptonPredictionData, true);

		 
		std::cout<<"Loop on Prediction (Data)"<<std::endl;
		
		nentries = LostLeptonPredictionData->GetEntries();
	  	for (Long64_t i=0; i<nentries;i++) {
		    LostLeptonPredictionData->GetEntry(i);

		    if(doQCDbinning) SearchBin = BinQCD;
		    else SearchBin = Bin;
		    
		    if(SearchBin > 900) continue;
		    if(MTW>100)continue;
		    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

		    double scaleFactorWeightData = 1.;
		    if(InputPath_Prediction_Data == InputPath_Prediction) scaleFactorWeightData = scaleFactorWeight;

		    scaledWeight = Weight * scaleFactorWeightData;
		    

		    totalPred_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeightData/2);
		    avgWeight_LL_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);

		    totalCS_LL_->Fill(SearchBin, scaledWeight);
		    nEvtsCS_LL_->Fill(SearchBin);

		    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeightData/2);
		    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeightData/2);
		    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeightData/2);

		    totalPredMuIsoTrackSysUp_LL_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredMuIsoTrackSysDown_LL_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeightData/2);
		    totalPredElecIsoTrackSysUp_LL_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredElecIsoTrackSysDown_LL_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeightData/2);
		    totalPredPionIsoTrackSysUp_LL_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeightData/2);
		    totalPredPionIsoTrackSysDown_LL_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeightData/2);
		    totalPredMTWSysUp_LL_->Fill(SearchBin, MTWSysUp*scaleFactorWeightData/2);
		    totalPredMTWSysDown_LL_->Fill(SearchBin, MTWSysDown*scaleFactorWeightData/2);
		    totalPredPuritySysUp_LL_->Fill(SearchBin, puritySysUp*scaleFactorWeightData/2);
		    totalPredPuritySysDown_LL_->Fill(SearchBin, puritySysDown*scaleFactorWeightData/2);
		    totalPredSingleLepPuritySysUp_LL_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeightData/2);
		    totalPredSingleLepPuritySysDown_LL_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeightData/2);
		    totalPredDiLepFoundSysUp_LL_->Fill(SearchBin, diLepFoundSysUp*scaleFactorWeightData/2);
		    totalPredDiLepFoundSysDown_LL_->Fill(SearchBin, diLepFoundSysDown*scaleFactorWeightData/2);
		    totalPredMuIsoSysUp_LL_->Fill(SearchBin, muIsoSysUp*scaleFactorWeightData/2);
		    totalPredMuIsoSysDown_LL_->Fill(SearchBin, muIsoSysDown*scaleFactorWeightData/2);
		    totalPredMuRecoSysUp_LL_->Fill(SearchBin, muRecoSysUp*scaleFactorWeightData/2);
		    totalPredMuRecoSysDown_LL_->Fill(SearchBin, muRecoSysDown*scaleFactorWeightData/2);
		    totalPredMuAccSysUp_LL_->Fill(SearchBin, muAccSysUp*scaleFactorWeightData/2);
		    totalPredMuAccSysDown_LL_->Fill(SearchBin, muAccSysDown*scaleFactorWeightData/2);
		    totalPredMuAccQsquareSysUp_LL_->Fill(SearchBin, muAccQsquareSysUp*scaleFactorWeightData/2);
		    totalPredMuAccQsquareSysDown_LL_->Fill(SearchBin, muAccQsquareSysDown*scaleFactorWeightData/2);
		    totalPredElecIsoSysUp_LL_->Fill(SearchBin, elecIsoSysUp*scaleFactorWeightData/2);
		    totalPredElecIsoSysDown_LL_->Fill(SearchBin, elecIsoSysDown*scaleFactorWeightData/2);
		    totalPredElecRecoSysUp_LL_->Fill(SearchBin, elecRecoSysUp*scaleFactorWeightData/2);
		    totalPredElecRecoSysDown_LL_->Fill(SearchBin, elecRecoSysDown*scaleFactorWeightData/2);
		    totalPredElecAccSysUp_LL_->Fill(SearchBin, elecAccSysUp*scaleFactorWeightData/2);
		    totalPredElecAccSysDown_LL_->Fill(SearchBin, elecAccSysDown*scaleFactorWeightData/2);
		    totalPredElecAccQsquareSysUp_LL_->Fill(SearchBin, elecAccQsquareSysUp*scaleFactorWeightData/2);
		    totalPredElecAccQsquareSysDown_LL_->Fill(SearchBin, elecAccQsquareSysDown*scaleFactorWeightData/2);

		    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, isoTrackStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, isoTrackStatDown*scaleFactorWeightData/2);
		    /*    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeightData/2);
			  totalPredIsoTrackStatDown_LL_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeightData/2);
			  totalPredIsoTrackStatUp_LL_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeightData/2);
			  totalPredIsoTrackStatDown_LL_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeightData/2);
			  totalPredIsoTrackStatUp_LL_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeightData/2);
			  totalPredIsoTrackStatDown_LL_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeightData/2);
		    */
		    totalPredMuIsoTrackStatUp_LL_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeightData/2);
		    totalPredMuIsoTrackStatDown_LL_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeightData/2);
		    totalPredElecIsoTrackStatUp_LL_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeightData/2);
		    totalPredElecIsoTrackStatDown_LL_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeightData/2);
		    totalPredPionIsoTrackStatUp_LL_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeightData/2);
		    totalPredPionIsoTrackStatDown_LL_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeightData/2);
		    totalPredMTWStatUp_LL_->Fill(SearchBin, MTWStatUp*scaleFactorWeightData/2);
		    totalPredMTWStatDown_LL_->Fill(SearchBin, MTWStatDown*scaleFactorWeightData/2);
		    totalPredPurityStatUp_LL_->Fill(SearchBin, purityStatUp*scaleFactorWeightData/2);
		    totalPredPurityStatDown_LL_->Fill(SearchBin, purityStatDown*scaleFactorWeightData/2);
		    totalPredSingleLepPurityStatUp_LL_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeightData/2);
		    totalPredSingleLepPurityStatDown_LL_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeightData/2);
		    totalPredDiLepFoundStatUp_LL_->Fill(SearchBin, diLepFoundStatUp*scaleFactorWeightData/2);
		    totalPredDiLepFoundStatDown_LL_->Fill(SearchBin, diLepFoundStatDown*scaleFactorWeightData/2);
		    totalPredMuIsoStatUp_LL_->Fill(SearchBin, muIsoStatUp*scaleFactorWeightData/2);
		    totalPredMuIsoStatDown_LL_->Fill(SearchBin, muIsoStatDown*scaleFactorWeightData/2);
		    totalPredMuRecoStatUp_LL_->Fill(SearchBin, muRecoStatUp*scaleFactorWeightData/2);
		    totalPredMuRecoStatDown_LL_->Fill(SearchBin, muRecoStatDown*scaleFactorWeightData/2);
		    totalPredMuAccStatUp_LL_->Fill(SearchBin, muAccStatUp*scaleFactorWeightData/2);
		    totalPredMuAccStatDown_LL_->Fill(SearchBin, muAccStatDown*scaleFactorWeightData/2);
		    totalPredElecIsoStatUp_LL_->Fill(SearchBin, elecIsoStatUp*scaleFactorWeightData/2);
		    totalPredElecIsoStatDown_LL_->Fill(SearchBin, elecIsoStatDown*scaleFactorWeightData/2);
		    totalPredElecRecoStatUp_LL_->Fill(SearchBin, elecRecoStatUp*scaleFactorWeightData/2);
		    totalPredElecRecoStatDown_LL_->Fill(SearchBin, elecRecoStatDown*scaleFactorWeightData/2);
		    totalPredElecAccStatUp_LL_->Fill(SearchBin, elecAccStatUp*scaleFactorWeightData/2);
		    totalPredElecAccStatDown_LL_->Fill(SearchBin, elecAccStatDown*scaleFactorWeightData/2);

		    //totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
		    //totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

		    //totalPropSysUp_LL_->Fill(SearchBin, totalPropSysUp*scaleFactorWeightData/2);
		    //totalPropSysDown_LL_->Fill(SearchBin, totalPropSysDown*scaleFactorWeightData/2;
		}

		fPre->Close();
	  	std::cout<<"Finished"<<std::endl;
	}


	TFile *LLoutputFile = new TFile(OutputPath_Prediction.c_str(),"RECREATE");
	saveHistograms(LLoutputFile);
	LLoutputFile->Close();


}



void saveHistograms(TFile* tf){
	tf->cd();
	tf->mkdir("Closure");
	TDirectory *dClosure = (TDirectory*)tf->Get("Closure");
	dClosure->cd();

	TH1D *ClosureTest = (TH1D*) totalExp_LL_->Clone("ClosureTest");
	ClosureTest->Divide(totalPred_LL_MC_);
	ClosureTest->SetTitle("Expectation / Prediction");
	SetBinLabel(ClosureTest);
	ClosureTest->Write();

	TH1D *ClosureTest_woIsoTrack = (TH1D*) totalExp_woIsoTrack_LL_->Clone("ClosureTest_woIsoTrack");
	ClosureTest_woIsoTrack->Divide(totalPred_woIsoTrack_LL_MC_);
	ClosureTest_woIsoTrack->SetTitle("Expectation / Prediction");
	SetBinLabel(ClosureTest_woIsoTrack);
	ClosureTest_woIsoTrack->Write();


	tf->cd();
	tf->mkdir("Expectation");
	TDirectory *dExp = (TDirectory*)tf->Get("Expectation");
	dExp->cd();

	SetBinLabel(totalExp_LL_);
	totalExp_LL_->Write();
	SetBinLabel(totalExp_woIsoTrack_LL_);
	totalExp_woIsoTrack_LL_->Write();	
	SetBinLabel(nEvtsExp_LL_);
	nEvtsExp_LL_->Write();


	tf->cd();
	tf->mkdir("Prediction_data");
	TDirectory *dPreData = (TDirectory*)tf->Get("Prediction_data");
	dPreData->cd();

	SetBinLabel(totalPred_LL_);
	totalPred_LL_->Write();

	for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
		totalPredNonClosureUp_LL_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
		//std::cout<<i<<": "<<ClosureTest->GetBinContent(i)<<"-"<<ClosureTest->GetBinError(i)<<std::endl;
		totalPredNonClosureDown_LL_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	}
	SetBinLabel(totalPredNonClosureUp_LL_);
	totalPredNonClosureUp_LL_->Write();
	SetBinLabel(totalPredNonClosureDown_LL_);
	totalPredNonClosureDown_LL_->Write();

	SetBinLabel(totalCS_LL_);
	totalCS_LL_->Write();
	SetBinLabel(nEvtsCS_LL_);
	nEvtsCS_LL_->Write();

	SetBinLabel(avgWeight_LL_);
	avgWeight_LL_->Write();

	TH1D* PredOverCS_LL_ = (TH1D*) totalPred_LL_->Clone("PredOverCS_LL");
	PredOverCS_LL_->Divide(totalCS_LL_);
	PredOverCS_LL_->SetTitle("Prediction / CS (=0L/1L)");
	PredOverCS_LL_->Write();

  
	std::vector<TH1D*> allUncUp_LL_;
	allUncUp_LL_.push_back(totalPredIsoTrackSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMTWSysUp_LL_);
	allUncUp_LL_.push_back(totalPredPuritySysUp_LL_);
	allUncUp_LL_.push_back(totalPredSingleLepPuritySysUp_LL_);
	allUncUp_LL_.push_back(totalPredDiLepFoundSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMuIsoSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMuRecoSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMuAccSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMuAccQsquareSysUp_LL_);
	allUncUp_LL_.push_back(totalPredElecIsoSysUp_LL_);
	allUncUp_LL_.push_back(totalPredElecRecoSysUp_LL_);
	allUncUp_LL_.push_back(totalPredElecAccSysUp_LL_);
	allUncUp_LL_.push_back(totalPredElecAccQsquareSysUp_LL_);
	allUncUp_LL_.push_back(totalPredIsoTrackStatUp_LL_);
	allUncUp_LL_.push_back(totalPredMTWStatUp_LL_);
	allUncUp_LL_.push_back(totalPredPurityStatUp_LL_);
	allUncUp_LL_.push_back(totalPredSingleLepPurityStatUp_LL_);
	allUncUp_LL_.push_back(totalPredDiLepFoundStatUp_LL_);
	allUncUp_LL_.push_back(totalPredMuIsoStatUp_LL_);
	allUncUp_LL_.push_back(totalPredMuRecoStatUp_LL_);
	allUncUp_LL_.push_back(totalPredMuAccStatUp_LL_);
	allUncUp_LL_.push_back(totalPredElecIsoStatUp_LL_);
	allUncUp_LL_.push_back(totalPredElecRecoStatUp_LL_);
	allUncUp_LL_.push_back(totalPredElecAccStatUp_LL_);

	addUncertainties(totalPropSysUp_LL_, allUncUp_LL_, true);

	std::vector<TH1D*> allUncDown_LL_;
	allUncDown_LL_.push_back(totalPredIsoTrackSysDown_LL_);
	allUncDown_LL_.push_back(totalPredMTWSysDown_LL_);
	allUncDown_LL_.push_back(totalPredPuritySysDown_LL_);
	allUncDown_LL_.push_back(totalPredSingleLepPuritySysDown_LL_);
	allUncDown_LL_.push_back(totalPredDiLepFoundSysDown_LL_);
	allUncDown_LL_.push_back(totalPredMuIsoSysDown_LL_);
	allUncDown_LL_.push_back(totalPredMuRecoSysDown_LL_);
	allUncDown_LL_.push_back(totalPredMuAccSysDown_LL_);
	allUncDown_LL_.push_back(totalPredMuAccQsquareSysDown_LL_);
	allUncDown_LL_.push_back(totalPredElecIsoSysDown_LL_);
	allUncDown_LL_.push_back(totalPredElecRecoSysDown_LL_);
	allUncDown_LL_.push_back(totalPredElecAccSysDown_LL_);
	allUncDown_LL_.push_back(totalPredElecAccQsquareSysDown_LL_);
	allUncDown_LL_.push_back(totalPredIsoTrackStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMTWStatDown_LL_);
	allUncDown_LL_.push_back(totalPredPurityStatDown_LL_);
	allUncDown_LL_.push_back(totalPredSingleLepPurityStatDown_LL_);
	allUncDown_LL_.push_back(totalPredDiLepFoundStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuIsoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuRecoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuAccStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecIsoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecRecoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecAccStatDown_LL_);

	addUncertainties(totalPropSysDown_LL_, allUncDown_LL_, false);
  
	SaveFraction(totalPredIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	/*  SaveFraction(totalPredMuIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredMuIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	*/  SaveFraction(totalPredMTWSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMTWSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredPuritySysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredPuritySysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredSingleLepPuritySysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredSingleLepPuritySysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredDiLepFoundSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredDiLepFoundSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuIsoSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuIsoSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuRecoSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuRecoSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccQsquareSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccQsquareSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecIsoSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecIsoSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecRecoSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecRecoSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccSysDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccQsquareSysUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccQsquareSysDown_LL_, totalPred_LL_, dPreData);

	SaveFraction(totalPredIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	/*  SaveFraction(totalPredMuIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredMuIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	*/  SaveFraction(totalPredMTWStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMTWStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredPurityStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredPurityStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredSingleLepPurityStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredSingleLepPurityStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredDiLepFoundStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredDiLepFoundStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuIsoStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuIsoStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuRecoStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuRecoStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredMuAccStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecIsoStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecIsoStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecRecoStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecRecoStatDown_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccStatUp_LL_, totalPred_LL_, dPreData);
	SaveFraction(totalPredElecAccStatDown_LL_, totalPred_LL_, dPreData);


	tf->cd();
	tf->mkdir("Prediction_MC");
	TDirectory *dPreMC = (TDirectory*)tf->Get("Prediction_MC");
	dPreMC->cd();

	SetBinLabel(totalPred_LL_MC_);
	totalPred_LL_MC_->Write();
	SetBinLabel(totalPred_woIsoTrack_LL_MC_);
	totalPred_woIsoTrack_LL_MC_->Write();

	for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
	    totalPredNonClosureUp_LL_MC_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	    totalPredNonClosureDown_LL_MC_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	}
	SetBinLabel(totalPredNonClosureUp_LL_MC_);
	totalPredNonClosureUp_LL_MC_->Write();
	SetBinLabel(totalPredNonClosureDown_LL_MC_);
	totalPredNonClosureDown_LL_MC_->Write();

	SetBinLabel(totalCS_LL_MC_);
	totalCS_LL_MC_->Write();
	SetBinLabel(nEvtsCS_LL_MC_);
	nEvtsCS_LL_MC_->Write();

	SetBinLabel(avgWeight_LL_MC_);
	// Fill empty bins with avg. of remaining HTMHT bins
	for(int i = 1; i < avgWeight_LL_MC_->GetNbinsX(); i++){
		if(avgWeight_LL_MC_->GetBinContent(i) <= 0.01){
			for(int j = 0; j < avgWeight_LL_MC_->GetNbinsX(); j++){
				if(i == j) continue;
				if(avgWeight_LL_MC_->GetBinContent(j) <= 0.01) continue;
				if(std::string(avgWeight_LL_MC_->GetXaxis()->GetBinLabel(j), 0, 13) == std::string(avgWeight_LL_MC_->GetXaxis()->GetBinLabel(i), 0, 13)){
					avgWeight_LL_MC_->Fill(i, avgWeight_LL_MC_->GetBinContent(j), 1.);
				}
			}
		}
	}
	avgWeight_LL_MC_->Write();

	tf->cd();
	tf->mkdir("AvgWeight_MC");
	TDirectory *dAvgWeight = (TDirectory*)tf->Get("AvgWeight_MC");
	dAvgWeight->cd();

	TH1D* PredOverCS_LL_MC_ = (TH1D*) totalPred_LL_MC_->Clone("PredOverCS_LL_MC");
	PredOverCS_LL_MC_->Divide(totalCS_LL_MC_);
	PredOverCS_LL_MC_->SetTitle("Prediction / CS (=0L/1L)");
	//Fix for bins where negative sum of events
	for(int i = 1; i < PredOverCS_LL_MC_->GetNbinsX(); i++){
		PredOverCS_LL_MC_->SetBinContent(i, abs(PredOverCS_LL_MC_->GetBinContent(i)));
	}
	SetBinLabel(PredOverCS_LL_MC_);
	PredOverCS_LL_MC_->Write();


	std::vector<TH1D*> allUncUp_LL_MC_;
	allUncUp_LL_MC_.push_back(totalPredIsoTrackSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMTWSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredPuritySysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredSingleLepPuritySysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredDiLepFoundSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuIsoSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuRecoSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuAccSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuAccQsquareSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecIsoSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecRecoSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecAccSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecAccQsquareSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredIsoTrackStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMTWStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredPurityStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredSingleLepPurityStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredDiLepFoundStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuIsoStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuRecoStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMuAccStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecIsoStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecRecoStatUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredElecAccStatUp_LL_MC_);

	addUncertainties(totalPropSysUp_LL_MC_, allUncUp_LL_MC_, true);

	std::vector<TH1D*> allUncDown_LL_MC_;
	allUncDown_LL_MC_.push_back(totalPredIsoTrackSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMTWSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredPuritySysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredSingleLepPuritySysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredDiLepFoundSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuIsoSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuRecoSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuAccSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuAccQsquareSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecIsoSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecRecoSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecAccSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecAccQsquareSysDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredIsoTrackStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMTWStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredPurityStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredSingleLepPurityStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredDiLepFoundStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuIsoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuRecoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuAccStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecIsoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecRecoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecAccStatDown_LL_MC_);

	addUncertainties(totalPropSysDown_LL_MC_, allUncDown_LL_MC_, false);


	SaveFraction(totalPredIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	/*  SaveFraction(totalPredMuIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredMuIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	*/  SaveFraction(totalPredMTWSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMTWSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredSingleLepPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredSingleLepPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredDiLepFoundSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredDiLepFoundSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);

	SaveFraction(totalPredIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	/*  SaveFraction(totalPredMuIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredMuIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	*/  SaveFraction(totalPredMTWStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMTWStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredSingleLepPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredSingleLepPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredDiLepFoundStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredDiLepFoundStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredMuAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	SaveFraction(totalPredElecAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);


	tf->cd();
	tf->mkdir("Prediction_Data_MC");
	TDirectory *dDataMC = (TDirectory*)tf->Get("Prediction_Data_MC");
	dDataMC->cd();

	TH1D *Prediction_Data_MC = (TH1D*) totalPred_LL_->Clone("Prediction_Data_MC");
	Prediction_Data_MC->Divide(totalPred_LL_MC_);
	Prediction_Data_MC->SetTitle("Prediction Data / Prediction MC");
	SetBinLabel(Prediction_Data_MC);
	Prediction_Data_MC->Write();


	tf->cd();
	tf->mkdir("AdditionalContent");
	TDirectory *dAdd = (TDirectory*)tf->Get("AdditionalContent");
	dAdd->cd();

	SaveFraction(totalPropSysUp_LL_MC_, totalPred_LL_MC_, dAdd);
	SaveFraction(totalPropSysDown_LL_MC_, totalPred_LL_MC_, dAdd);
	SaveFraction(totalPropSysUp_LL_, totalPred_LL_, dAdd);
	SaveFraction(totalPropSysDown_LL_, totalPred_LL_, dAdd);
}

void initHistograms(Int_t nBins){
	TH1::SetDefaultSumw2();

	totalExp_LL_ = new TH1D("totalExp_LL","totalExp_LL", nBins, 0.5, nBins+0.5);
	totalExp_woIsoTrack_LL_ = new TH1D("totalExp_woIsoTrack_LL","totalExp_woIsoTrack_LL", nBins, 0.5, nBins+0.5);
  	nEvtsExp_LL_ = new TH1D("nEvtsExp_LL","nEvtsExp_LL", nBins, 0.5, nBins+0.5);

 	totalPred_LL_ = new TH1D("totalPred_LL","totalPred_LL", nBins, 0.5, nBins+0.5);
 	totalCS_LL_ = new TH1D("totalCS_LL","totalCS_LL", nBins, 0.5, nBins+0.5);
	nEvtsCS_LL_ = new TH1D("nEvtsCS_LL","nEvtsCS_LL", nBins, 0.5, nBins+0.5);
	avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", nBins, 0.5, nBins+0.5);

	totalPred_LL_MC_ = new TH1D("totalPred_LL_MC","totalPred_LL_MC", nBins, 0.5, nBins+0.5);
	totalPred_woIsoTrack_LL_MC_ = new TH1D("totalPred_woIsoTrack_LL_MC","totalPred_woIsoTrack_LL_MC", nBins, 0.5, nBins+0.5);
 	totalCS_LL_MC_ = new TH1D("totalCS_LL_MC","totalCS_LL_MC", nBins, 0.5, nBins+0.5);
	nEvtsCS_LL_MC_ = new TH1D("nEvtsCS_LL_MC","nEvtsCS_LL_MC", nBins, 0.5, nBins+0.5);
	avgWeight_LL_MC_ = new TProfile("avgWeight_LL_MC","avgWeight_LL_MC", nBins, 0.5, nBins+0.5);

 	totalPredIsoTrackSysUp_LL_ = new TH1D("totalPredIsoTrackSysUp_LL","totalPredIsoTrackSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackSysDown_LL_ = new TH1D("totalPredIsoTrackSysDown_LL","totalPredIsoTrackSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackSysUp_LL_ = new TH1D("totalPredMuIsoTrackSysUp_LL","totalPredMuIsoTrackSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackSysDown_LL_ = new TH1D("totalPredMuIsoTrackSysDown_LL","totalPredMuIsoTrackSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackSysUp_LL_ = new TH1D("totalPredElecIsoTrackSysUp_LL","totalPredElecIsoTrackSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackSysDown_LL_ = new TH1D("totalPredElecIsoTrackSysDown_LL","totalPredElecIsoTrackSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackSysUp_LL_ = new TH1D("totalPredPionIsoTrackSysUp_LL","totalPredPionIsoTrackSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackSysDown_LL_ = new TH1D("totalPredPionIsoTrackSysDown_LL","totalPredPionIsoTrackSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWSysUp_LL_ = new TH1D("totalPredMTWSysUp_LL","totalPredMTWSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWSysDown_LL_ = new TH1D("totalPredMTWSysDown_LL","totalPredMTWSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPuritySysUp_LL_ = new TH1D("totalPredPuritySysUp_LL","totalPredPuritySysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPuritySysDown_LL_ = new TH1D("totalPredPuritySysDown_LL","totalPredPuritySysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysUp_LL_ = new TH1D("totalPredSingleLepPuritySysUp_LL","totalPredSingleLepPuritySysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysDown_LL_ = new TH1D("totalPredSingleLepPuritySysDown_LL","totalPredSingleLepPuritySysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundSysUp_LL_ = new TH1D("totalPredDiLepFoundSysUp_LL","totalPredDiLepFoundSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundSysDown_LL_ = new TH1D("totalPredDiLepFoundSysDown_LL","totalPredDiLepFoundSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoSysUp_LL_ = new TH1D("totalPredMuIsoSysUp_LL","totalPredMuIsoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoSysDown_LL_ = new TH1D("totalPredMuIsoSysDown_LL","totalPredMuIsoSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuRecoSysUp_LL_ = new TH1D("totalPredMuRecoSysUp_LL","totalPredMuRecoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuRecoSysDown_LL_ = new TH1D("totalPredMuRecoSysDown_LL","totalPredMuRecoSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccSysUp_LL_ = new TH1D("totalPredMuAccSysUp_LL","totalPredMuAccSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccSysDown_LL_ = new TH1D("totalPredMuAccSysDown_LL","totalPredMuAccSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccQsquareSysUp_LL_ = new TH1D("totalPredMuAccQsquareSysUp_LL","totalPredMuAccQsquareSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccQsquareSysDown_LL_ = new TH1D("totalPredMuAccQsquareSysDown_LL","totalPredMuAccQsquareSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoSysUp_LL_ = new TH1D("totalPredElecIsoSysUp_LL","totalPredElecIsoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoSysDown_LL_ = new TH1D("totalPredElecIsoSysDown_LL","totalPredElecIsoSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecRecoSysUp_LL_ = new TH1D("totalPredElecRecoSysUp_LL","totalPredElecRecoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecRecoSysDown_LL_ = new TH1D("totalPredElecRecoSysDown_LL","totalPredElecRecoSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccSysUp_LL_ = new TH1D("totalPredElecAccSysUp_LL","totalPredElecAccSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccSysDown_LL_ = new TH1D("totalPredElecAccSysDown_LL","totalPredElecAccSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccQsquareSysUp_LL_ = new TH1D("totalPredElecAccQsquareSysUp_LL","totalPredElecAccQsquareSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccQsquareSysDown_LL_ = new TH1D("totalPredElecAccQsquareSysDown_LL","totalPredElecAccQsquareSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredNonClosureUp_LL_ = new TH1D("totalPredNonClosureUp_LL","totalPredNonClosureUp_LL", nBins, 0.5, nBins+0.5);
	totalPredNonClosureDown_LL_ = new TH1D("totalPredNonClosureDown_LL","totalPredNonClosureDown_LL", nBins, 0.5, nBins+0.5);

	totalPredIsoTrackStatUp_LL_ = new TH1D("totalPredIsoTrackStatUp_LL","totalPredIsoTrackStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackStatDown_LL_ = new TH1D("totalPredIsoTrackStatDown_LL","totalPredIsoTrackStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackStatUp_LL_ = new TH1D("totalPredMuIsoTrackStatUp_LL","totalPredMuIsoTrackStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackStatDown_LL_ = new TH1D("totalPredMuIsoTrackStatDown_LL","totalPredMuIsoTrackStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackStatUp_LL_ = new TH1D("totalPredElecIsoTrackStatUp_LL","totalPredElecIsoTrackStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackStatDown_LL_ = new TH1D("totalPredElecIsoTrackStatDown_LL","totalPredElecIsoTrackStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackStatUp_LL_ = new TH1D("totalPredPionIsoTrackStatUp_LL","totalPredPionIsoTrackStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackStatDown_LL_ = new TH1D("totalPredPionIsoTrackStatDown_LL","totalPredPionIsoTrackStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWStatUp_LL_ = new TH1D("totalPredMTWStatUp_LL","totalPredMTWStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWStatDown_LL_ = new TH1D("totalPredMTWStatDown_LL","totalPredMTWStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPurityStatUp_LL_ = new TH1D("totalPredPurityStatUp_LL","totalPredPurityStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPurityStatDown_LL_ = new TH1D("totalPredPurityStatDown_LL","totalPredPurityStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatUp_LL_ = new TH1D("totalPredSingleLepPurityStatUp_LL","totalPredSingleLepPurityStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatDown_LL_ = new TH1D("totalPredSingleLepPurityStatDown_LL","totalPredSingleLepPurityStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundStatUp_LL_ = new TH1D("totalPredDiLepFoundStatUp_LL","totalPredDiLepFoundStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundStatDown_LL_ = new TH1D("totalPredDiLepFoundStatDown_LL","totalPredDiLepFoundStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoStatUp_LL_ = new TH1D("totalPredMuIsoStatUp_LL","totalPredMuIsoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuIsoStatDown_LL_ = new TH1D("totalPredMuIsoStatDown_LL","totalPredMuIsoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuRecoStatUp_LL_ = new TH1D("totalPredMuRecoStatUp_LL","totalPredMuRecoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuRecoStatDown_LL_ = new TH1D("totalPredMuRecoStatDown_LL","totalPredMuRecoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccStatUp_LL_ = new TH1D("totalPredMuAccStatUp_LL","totalPredMuAccStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMuAccStatDown_LL_ = new TH1D("totalPredMuAccStatDown_LL","totalPredMuAccStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoStatUp_LL_ = new TH1D("totalPredElecIsoStatUp_LL","totalPredElecIsoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecIsoStatDown_LL_ = new TH1D("totalPredElecIsoStatDown_LL","totalPredElecIsoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecRecoStatUp_LL_ = new TH1D("totalPredElecRecoStatUp_LL","totalPredElecRecoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecRecoStatDown_LL_ = new TH1D("totalPredElecRecoStatDown_LL","totalPredElecRecoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccStatUp_LL_ = new TH1D("totalPredElecAccStatUp_LL","totalPredElecAccStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredElecAccStatDown_LL_ = new TH1D("totalPredElecAccStatDown_LL","totalPredElecAccStatDown_LL", nBins, 0.5, nBins+0.5);

	totalPropSysUp_LL_ = new TH1D("totalPropSysUp_LL","totalPropSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPropSysDown_LL_ = new TH1D("totalPropSysDown_LL","totalPropSysDown_LL", nBins, 0.5, nBins+0.5);

	totalPredIsoTrackSysUp_LL_MC_ = new TH1D("totalPredIsoTrackSysUp_LL_MC","totalPredIsoTrackSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackSysDown_LL_MC_ = new TH1D("totalPredIsoTrackSysDown_LL_MC","totalPredIsoTrackSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackSysUp_LL_MC_ = new TH1D("totalPredMuIsoTrackSysUp_LL_MC","totalPredMuIsoTrackSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackSysDown_LL_MC_ = new TH1D("totalPredMuIsoTrackSysDown_LL_MC","totalPredMuIsoTrackSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackSysUp_LL_MC_ = new TH1D("totalPredElecIsoTrackSysUp_LL_MC","totalPredElecIsoTrackSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackSysDown_LL_MC_ = new TH1D("totalPredElecIsoTrackSysDown_LL_MC","totalPredElecIsoTrackSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackSysUp_LL_MC_ = new TH1D("totalPredPionIsoTrackSysUp_LL_MC","totalPredPionIsoTrackSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackSysDown_LL_MC_ = new TH1D("totalPredPionIsoTrackSysDown_LL_MC","totalPredPionIsoTrackSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWSysUp_LL_MC_ = new TH1D("totalPredMTWSysUp_LL_MC","totalPredMTWSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWSysDown_LL_MC_ = new TH1D("totalPredMTWSysDown_LL_MC","totalPredMTWSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPuritySysUp_LL_MC_ = new TH1D("totalPredPuritySysUp_LL_MC","totalPredPuritySysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPuritySysDown_LL_MC_ = new TH1D("totalPredPuritySysDown_LL_MC","totalPredPuritySysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysUp_LL_MC_ = new TH1D("totalPredSingleLepPuritySysUp_LL_MC","totalPredSingleLepPuritySysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysDown_LL_MC_ = new TH1D("totalPredSingleLepPuritySysDown_LL_MC","totalPredSingleLepPuritySysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundSysUp_LL_MC_ = new TH1D("totalPredDiLepFoundSysUp_LL_MC","totalPredDiLepFoundSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundSysDown_LL_MC_ = new TH1D("totalPredDiLepFoundSysDown_LL_MC","totalPredDiLepFoundSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoSysUp_LL_MC_ = new TH1D("totalPredMuIsoSysUp_LL_MC","totalPredMuIsoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoSysDown_LL_MC_ = new TH1D("totalPredMuIsoSysDown_LL_MC","totalPredMuIsoSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuRecoSysUp_LL_MC_ = new TH1D("totalPredMuRecoSysUp_LL_MC","totalPredMuRecoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuRecoSysDown_LL_MC_ = new TH1D("totalPredMuRecoSysDown_LL_MC","totalPredMuRecoSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccSysUp_LL_MC_ = new TH1D("totalPredMuAccSysUp_LL_MC","totalPredMuAccSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccSysDown_LL_MC_ = new TH1D("totalPredMuAccSysDown_LL_MC","totalPredMuAccSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccQsquareSysUp_LL_MC_ = new TH1D("totalPredMuAccQsquareSysUp_LL_MC","totalPredMuAccQsquareSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccQsquareSysDown_LL_MC_ = new TH1D("totalPredMuAccQsquareSysDown_LL_MC","totalPredMuAccQsquareSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoSysUp_LL_MC_ = new TH1D("totalPredElecIsoSysUp_LL_MC","totalPredElecIsoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoSysDown_LL_MC_ = new TH1D("totalPredElecIsoSysDown_LL_MC","totalPredElecIsoSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecRecoSysUp_LL_MC_ = new TH1D("totalPredElecRecoSysUp_LL_MC","totalPredElecRecoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecRecoSysDown_LL_MC_ = new TH1D("totalPredElecRecoSysDown_LL_MC","totalPredElecRecoSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccSysUp_LL_MC_ = new TH1D("totalPredElecAccSysUp_LL_MC","totalPredElecAccSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccSysDown_LL_MC_ = new TH1D("totalPredElecAccSysDown_LL_MC","totalPredElecAccSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccQsquareSysUp_LL_MC_ = new TH1D("totalPredElecAccQsquareSysUp_LL_MC","totalPredElecAccQsquareSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccQsquareSysDown_LL_MC_ = new TH1D("totalPredElecAccQsquareSysDown_LL_MC","totalPredElecAccQsquareSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredNonClosureUp_LL_MC_ = new TH1D("totalPredNonClosureUp_LL_MC","totalPredNonClosureUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredNonClosureDown_LL_MC_ = new TH1D("totalPredNonClosureDown_LL_MC","totalPredNonClosureDown_LL_MC", nBins, 0.5, nBins+0.5);

	totalPredIsoTrackStatUp_LL_MC_ = new TH1D("totalPredIsoTrackStatUp_LL_MC","totalPredIsoTrackStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackStatDown_LL_MC_ = new TH1D("totalPredIsoTrackStatDown_LL_MC","totalPredIsoTrackStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackStatUp_LL_MC_ = new TH1D("totalPredMuIsoTrackStatUp_LL_MC","totalPredMuIsoTrackStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoTrackStatDown_LL_MC_ = new TH1D("totalPredMuIsoTrackStatDown_LL_MC","totalPredMuIsoTrackStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackStatUp_LL_MC_ = new TH1D("totalPredElecIsoTrackStatUp_LL_MC","totalPredElecIsoTrackStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoTrackStatDown_LL_MC_ = new TH1D("totalPredElecIsoTrackStatDown_LL_MC","totalPredElecIsoTrackStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackStatUp_LL_MC_ = new TH1D("totalPredPionIsoTrackStatUp_LL_MC","totalPredPionIsoTrackStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPionIsoTrackStatDown_LL_MC_ = new TH1D("totalPredPionIsoTrackStatDown_LL_MC","totalPredPionIsoTrackStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWStatUp_LL_MC_ = new TH1D("totalPredMTWStatUp_LL_MC","totalPredMTWStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWStatDown_LL_MC_ = new TH1D("totalPredMTWStatDown_LL_MC","totalPredMTWStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPurityStatUp_LL_MC_ = new TH1D("totalPredPurityStatUp_LL_MC","totalPredPurityStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPurityStatDown_LL_MC_ = new TH1D("totalPredPurityStatDown_LL_MC","totalPredPurityStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatUp_LL_MC_ = new TH1D("totalPredSingleLepPurityStatUp_LL_MC","totalPredSingleLepPurityStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatDown_LL_MC_ = new TH1D("totalPredSingleLepPurityStatDown_LL_MC","totalPredSingleLepPurityStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundStatUp_LL_MC_ = new TH1D("totalPredDiLepFoundStatUp_LL_MC","totalPredDiLepFoundStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepFoundStatDown_LL_MC_ = new TH1D("totalPredDiLepFoundStatDown_LL_MC","totalPredDiLepFoundStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoStatUp_LL_MC_ = new TH1D("totalPredMuIsoStatUp_LL_MC","totalPredMuIsoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuIsoStatDown_LL_MC_ = new TH1D("totalPredMuIsoStatDown_LL_MC","totalPredMuIsoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuRecoStatUp_LL_MC_ = new TH1D("totalPredMuRecoStatUp_LL_MC","totalPredMuRecoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuRecoStatDown_LL_MC_ = new TH1D("totalPredMuRecoStatDown_LL_MC","totalPredMuRecoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccStatUp_LL_MC_ = new TH1D("totalPredMuAccStatUp_LL_MC","totalPredMuAccStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMuAccStatDown_LL_MC_ = new TH1D("totalPredMuAccStatDown_LL_MC","totalPredMuAccStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoStatUp_LL_MC_ = new TH1D("totalPredElecIsoStatUp_LL_MC","totalPredElecIsoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecIsoStatDown_LL_MC_ = new TH1D("totalPredElecIsoStatDown_LL_MC","totalPredElecIsoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecRecoStatUp_LL_MC_ = new TH1D("totalPredElecRecoStatUp_LL_MC","totalPredElecRecoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecRecoStatDown_LL_MC_ = new TH1D("totalPredElecRecoStatDown_LL_MC","totalPredElecRecoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccStatUp_LL_MC_ = new TH1D("totalPredElecAccStatUp_LL_MC","totalPredElecAccStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredElecAccStatDown_LL_MC_ = new TH1D("totalPredElecAccStatDown_LL_MC","totalPredElecAccStatDown_LL_MC", nBins, 0.5, nBins+0.5);

	totalPropSysUp_LL_MC_ = new TH1D("totalPropSysUp_LL_MC","totalPropSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPropSysDown_LL_MC_ = new TH1D("totalPropSysDown_LL_MC","totalPropSysDown_LL_MC", nBins, 0.5, nBins+0.5);
}