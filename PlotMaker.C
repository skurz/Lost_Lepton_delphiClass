#include "PlotMaker.h"
#include "TSystem.h"

using std::string;

void initHistograms(Int_t nBins);
void saveHistograms(TFile* tf, bool combinedUnc = false, bool addCont = false);

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

	// Do some additional Plots for x-checks
	const bool doAdditionalPlots = true;

	// If you want to compare MC to MC set this to true. E.g. prediction with and without signal contamination
	const bool useMCForDataTree = false;	// NOT IMPLEMENTED

	// Scale all MC weights by this factor
	const Double_t scaleFactorWeight = 35862.351;  // 3998 2585 813  //in units of [pb] //<-check------------------------

	// Add some of the uncertainties in quadrature (if same correlation and similar shape)
	const bool doCombinedUnc = true;


	// Init
 	SearchBins_ = new SearchBins(doQCDbinning);
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
  	for (Long64_t ie=0; ie<nentries;ie++) {
  		LostLeptonExpectation->GetEntry(ie);

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

		    	if(muAcc == 0){
		    		totalAccMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalAccMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalAccMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalAccMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalAccMu_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormMu_NBTags_->Fill(i, std::abs(scaledWeight));
		    	}
				if(elecAcc == 0){
					totalAccElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalAccElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalAccElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalAccElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalAccElec_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormElec_NBTags_->Fill(i, std::abs(scaledWeight));
				}

				if(muReco == 0){
		    		totalRecoMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalRecoMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalRecoMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalRecoMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalRecoMu_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormMu_NBTags_->Fill(i, std::abs(scaledWeight));
		    	}
				if(elecReco == 0){
					totalRecoElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalRecoElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalRecoElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalRecoElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalRecoElec_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormElec_NBTags_->Fill(i, std::abs(scaledWeight));
				}

				if(muIso == 0){
		    		totalIsoMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalIsoMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalIsoMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalIsoMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalIsoMu_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormMu_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormMu_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormMu_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormMu_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormMu_NBTags_->Fill(i, std::abs(scaledWeight));
		    	}
				if(elecIso == 0){
					totalIsoElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalIsoElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalIsoElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalIsoElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalIsoElec_NBTags_->Fill(i, std::abs(scaledWeight));
					totalFractionNormElec_->Fill(Bin_bTags.at(i), std::abs(scaledWeight));
					totalFractionNormElec_HT_->Fill(HT, std::abs(scaledWeight));
					totalFractionNormElec_MHT_->Fill(MHT, std::abs(scaledWeight));
					totalFractionNormElec_NJets_->Fill(NJets, std::abs(scaledWeight));
					totalFractionNormElec_NBTags_->Fill(i, std::abs(scaledWeight));
				}
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
 	for (Long64_t ie=0; ie<nentries;ie++) {
 		LostLeptonPrediction->GetEntry(ie);

	    if(doQCDbinning) SearchBin = BinQCD;
	    else SearchBin = Bin;

	    if(SearchBin > 900) continue;
	    if(MTW>100)continue;
	    if(MuonsNum+ElectronsNum!=1)continue;

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
				totalPred_LL_MC_->Fill(Bin_bTags.at(i), totalWeightDiLepIsoTrackReduced*scaleFactorWeightBtagProb/2);
				totalPred_woIsoTrack_LL_MC_->Fill(Bin_bTags.at(i), totalWeightDiLep*scaleFactorWeightBtagProb/2);
				avgWeight_LL_MC_->Fill(Bin_bTags.at(i), abs(totalWeightDiLepIsoTrackReduced/Weight/2), Weight);

				if(MuonsNum==1){
					totalPred_LL_Mu_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
				}else{
					totalPred_LL_Elec_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
				}
			}else{
				totalPred_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPred_woIsoTrack_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags_noIsoTrack->at(i)*scaleFactorWeightBtagProb/2);
				avgWeight_LL_MC_->Fill(Bin_bTags.at(i), abs(totalWeight_BTags->at(i)/Weight/2), abs(Weight* bTagProb->at(i)));

				if(MuonsNum==1){
					totalPred_LL_Mu_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
					totalCS_LL_Mu_MC_->Fill(Bin_bTags.at(i), scaledWeight);
					totalCS_LL_HT_Mu_MC_->Fill(HT, scaledWeight);
					totalCS_LL_MHT_Mu_MC_->Fill(MHT, scaledWeight);
					totalCS_LL_MET_Mu_MC_->Fill(MET, scaledWeight);
					totalCS_LL_NJets_Mu_MC_->Fill(NJets, scaledWeight);
					totalCS_LL_NBTags_Mu_MC_->Fill(i, scaledWeight);
					totalCS_LL_LepPt_Mu_MC_->Fill(Muons->at(0).Pt(), scaledWeight);
				}else{
					totalPred_LL_Elec_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb);
					totalCS_LL_Elec_MC_->Fill(Bin_bTags.at(i),scaledWeight);
					totalCS_LL_HT_Elec_MC_->Fill(HT,scaledWeight);
					totalCS_LL_MHT_Elec_MC_->Fill(MHT,scaledWeight);
					totalCS_LL_MET_Elec_MC_->Fill(MET,scaledWeight);
					totalCS_LL_NJets_Elec_MC_->Fill(NJets,scaledWeight);
					totalCS_LL_NBTags_Elec_MC_->Fill(i,scaledWeight);
					totalCS_LL_LepPt_Elec_MC_->Fill(Electrons->at(0).Pt(),scaledWeight);
				}

				totalCSCombined_LL_MC_->Fill(Bin_bTags.at(i), scaledWeight);
				totalCSCombined_LL_HT_MC_->Fill(HT, scaledWeight);
				totalCSCombined_LL_MHT_MC_->Fill(MHT, scaledWeight);
				totalCSCombined_LL_MET_MC_->Fill(MET, scaledWeight);
				totalCSCombined_LL_NJets_MC_->Fill(NJets, scaledWeight);
				totalCSCombined_LL_NBTags_MC_->Fill(i, scaledWeight);

				totalPreCombined_LL_MC_->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPreCombined_LL_HT_MC_->Fill(HT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPreCombined_LL_MHT_MC_->Fill(MHT, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPreCombined_LL_MET_MC_->Fill(MET, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPreCombined_LL_NJets_MC_->Fill(NJets, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
				totalPreCombined_LL_NBTags_MC_->Fill(i, totalWeight_BTags->at(i)*scaleFactorWeightBtagProb/2);
			}

			totalCS_LL_MC_->Fill(Bin_bTags.at(i), scaledWeight);
        	nEvtsCS_LL_MC_->Fill(Bin_bTags.at(i));

		    totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoSysDown*scaleFactorWeightBtagProb/2);

			totalPredIsoTrackMuAccSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackMuAccSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackMuIDSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackMuIDSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackMuIsoSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackMuIsoSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecAccSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecAccSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecIDSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecIDSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDSysDown*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecIsoSysUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoSysUp*scaleFactorWeightBtagProb/2);
			totalPredIsoTrackElecIsoSysDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoSysDown*scaleFactorWeightBtagProb/2);

		    totalPredMTWSysUp_LL_MC_->Fill(Bin_bTags.at(i), MTWSysUp*scaleFactorWeightBtagProb/2);
		    totalPredMTWSysDown_LL_MC_->Fill(Bin_bTags.at(i), MTWSysDown*scaleFactorWeightBtagProb/2);
		    totalPredPuritySysUp_LL_MC_->Fill(Bin_bTags.at(i), puritySysUp*scaleFactorWeightBtagProb/2);
		    totalPredPuritySysDown_LL_MC_->Fill(Bin_bTags.at(i), puritySysDown*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPuritySysUp_LL_MC_->Fill(Bin_bTags.at(i), singleLepPuritySysUp*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPuritySysDown_LL_MC_->Fill(Bin_bTags.at(i), singleLepPuritySysDown*scaleFactorWeightBtagProb/2);
		    totalPredDiLepSRSysUp_LL_MC_->Fill(Bin_bTags.at(i), diLepSRSysUp*scaleFactorWeightBtagProb/2);
		    totalPredDiLepSRSysDown_LL_MC_->Fill(Bin_bTags.at(i), diLepSRSysDown*scaleFactorWeightBtagProb/2);
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

		    totalPredIsoTrackMuAccStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackMuAccStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuAccStatDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackMuIDStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackMuIDStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIDStatDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackMuIsoStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackMuIsoStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackMuIsoStatDown*scaleFactorWeightBtagProb/2);
		   	totalPredIsoTrackElecAccStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackElecAccStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecAccStatDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackElecIDStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackElecIDStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIDStatDown*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackElecIsoStatUp_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoStatUp*scaleFactorWeightBtagProb/2);
		    totalPredIsoTrackElecIsoStatDown_LL_MC_->Fill(Bin_bTags.at(i), isoTrackElecIsoStatDown*scaleFactorWeightBtagProb/2);
		    totalPredMTWStatUp_LL_MC_->Fill(Bin_bTags.at(i), MTWStatUp*scaleFactorWeightBtagProb/2);
		    totalPredMTWStatDown_LL_MC_->Fill(Bin_bTags.at(i), MTWStatDown*scaleFactorWeightBtagProb/2);
		    totalPredPurityStatUp_LL_MC_->Fill(Bin_bTags.at(i), purityStatUp*scaleFactorWeightBtagProb/2);
		    totalPredPurityStatDown_LL_MC_->Fill(Bin_bTags.at(i), purityStatDown*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPurityStatUp_LL_MC_->Fill(Bin_bTags.at(i), singleLepPurityStatUp*scaleFactorWeightBtagProb/2);
		    totalPredSingleLepPurityStatDown_LL_MC_->Fill(Bin_bTags.at(i), singleLepPurityStatDown*scaleFactorWeightBtagProb/2);
		    totalPredDiLepSRStatUp_LL_MC_->Fill(Bin_bTags.at(i), diLepSRStatUp*scaleFactorWeightBtagProb/2);
		    totalPredDiLepSRStatDown_LL_MC_->Fill(Bin_bTags.at(i), diLepSRStatDown*scaleFactorWeightBtagProb/2);
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
	  	for (Long64_t ie=0; ie<nentries;ie++) {
		    LostLeptonPredictionData->GetEntry(ie);

		    if(doQCDbinning) SearchBin = BinQCD;
		    else SearchBin = Bin;
		    
		    if(SearchBin > 900) continue;
		    if(MTW>100)continue;
		    if(MuonsNum+ElectronsNum!=1)continue;

		    double scaleFactorWeightData = 1.;
		    if(InputPath_Prediction_Data == InputPath_Prediction) scaleFactorWeightData = scaleFactorWeight;

		    scaledWeight = Weight * scaleFactorWeightData;
		    

		    totalPred_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
		    avgWeight_LL_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReduced/Weight/2), Weight);

			if(MuonsNum==1){
				totalPred_LL_Mu_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData);
				totalCS_LL_Mu_->Fill(SearchBin, scaledWeight*scaleFactorWeightData);
				totalCS_LL_HT_Mu_->Fill(HT, scaledWeight*scaleFactorWeightData);
				totalCS_LL_MHT_Mu_->Fill(MHT, scaledWeight*scaleFactorWeightData);
				totalCS_LL_MET_Mu_->Fill(MET, scaledWeight*scaleFactorWeightData);
				totalCS_LL_NJets_Mu_->Fill(NJets, scaledWeight*scaleFactorWeightData);
				totalCS_LL_NBTags_Mu_->Fill(BTags < 3 ? BTags : 3, scaledWeight*scaleFactorWeightData);
				totalCS_LL_LepPt_Mu_->Fill(Muons->at(0).Pt(), scaledWeight*scaleFactorWeightData);
			}else{
				totalPred_LL_Elec_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData);
				totalCS_LL_Elec_->Fill(SearchBin, scaledWeight*scaleFactorWeightData);
				totalCS_LL_HT_Elec_->Fill(HT, scaledWeight*scaleFactorWeightData);
				totalCS_LL_MHT_Elec_->Fill(MHT, scaledWeight*scaleFactorWeightData);
				totalCS_LL_MET_Elec_->Fill(MET, scaledWeight*scaleFactorWeightData);
				totalCS_LL_NJets_Elec_->Fill(NJets, scaledWeight*scaleFactorWeightData);
				totalCS_LL_NBTags_Elec_->Fill(BTags < 3 ? BTags : 3, scaledWeight*scaleFactorWeightData);
				totalCS_LL_LepPt_Elec_->Fill(Electrons->at(0).Pt(), scaledWeight*scaleFactorWeightData);
			}

			totalCSCombined_LL_->Fill(SearchBin, scaledWeight);
			totalCSCombined_LL_HT_->Fill(HT, scaledWeight);
			totalCSCombined_LL_MHT_->Fill(MHT, scaledWeight);
			totalCSCombined_LL_MET_->Fill(MET, scaledWeight);
			totalCSCombined_LL_NJets_->Fill(NJets, scaledWeight);
			totalCSCombined_LL_NBTags_->Fill(BTags < 3 ? BTags : 3, scaledWeight);

			totalPreCombined_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
			totalPreCombined_LL_HT_->Fill(HT, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
			totalPreCombined_LL_MHT_->Fill(MHT, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
			totalPreCombined_LL_MET_->Fill(MET, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
			totalPreCombined_LL_NJets_->Fill(NJets, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);
			totalPreCombined_LL_NBTags_->Fill(BTags < 3 ? BTags : 3, totalWeightDiLepIsoTrackReduced*scaleFactorWeightData/2);

		    totalCS_LL_->Fill(SearchBin, scaledWeight);
		    nEvtsCS_LL_->Fill(SearchBin);

		    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackMuAccSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackMuAccSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackMuIDSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackMuIDSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackMuIsoSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackMuIsoSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackElecAccSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackElecAccSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackElecIDSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackElecIDSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackElecIsoSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackElecIsoSysDown*scaleFactorWeightData/2);

			totalPredIsoTrackMuAccSysUp_LL_->Fill(SearchBin, isoTrackMuAccSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackMuAccSysDown_LL_->Fill(SearchBin, isoTrackMuAccSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackMuIDSysUp_LL_->Fill(SearchBin, isoTrackMuIDSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackMuIDSysDown_LL_->Fill(SearchBin, isoTrackMuIDSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackMuIsoSysUp_LL_->Fill(SearchBin, isoTrackMuIsoSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackMuIsoSysDown_LL_->Fill(SearchBin, isoTrackMuIsoSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackElecAccSysUp_LL_->Fill(SearchBin, isoTrackElecAccSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackElecAccSysDown_LL_->Fill(SearchBin, isoTrackElecAccSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackElecIDSysUp_LL_->Fill(SearchBin, isoTrackElecIDSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackElecIDSysDown_LL_->Fill(SearchBin, isoTrackElecIDSysDown*scaleFactorWeightData/2);
			totalPredIsoTrackElecIsoSysUp_LL_->Fill(SearchBin, isoTrackElecIsoSysUp*scaleFactorWeightData/2);
			totalPredIsoTrackElecIsoSysDown_LL_->Fill(SearchBin, isoTrackElecIsoSysDown*scaleFactorWeightData/2);

		    totalPredMTWSysUp_LL_->Fill(SearchBin, MTWSysUp*scaleFactorWeightData/2);
		    totalPredMTWSysDown_LL_->Fill(SearchBin, MTWSysDown*scaleFactorWeightData/2);
		    totalPredPuritySysUp_LL_->Fill(SearchBin, puritySysUp*scaleFactorWeightData/2);
		    totalPredPuritySysDown_LL_->Fill(SearchBin, puritySysDown*scaleFactorWeightData/2);
		    totalPredSingleLepPuritySysUp_LL_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeightData/2);
		    totalPredSingleLepPuritySysDown_LL_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeightData/2);
		    totalPredDiLepSRSysUp_LL_->Fill(SearchBin, diLepSRSysUp*scaleFactorWeightData/2);
		    totalPredDiLepSRSysDown_LL_->Fill(SearchBin, diLepSRSysDown*scaleFactorWeightData/2);
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

		    totalPredIsoTrackMuAccStatUp_LL_->Fill(SearchBin, isoTrackMuAccStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackMuAccStatDown_LL_->Fill(SearchBin, isoTrackMuAccStatDown*scaleFactorWeightData/2);
		    totalPredIsoTrackMuIDStatUp_LL_->Fill(SearchBin, isoTrackMuIDStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackMuIDStatDown_LL_->Fill(SearchBin, isoTrackMuIDStatDown*scaleFactorWeightData/2);
		    totalPredIsoTrackMuIsoStatUp_LL_->Fill(SearchBin, isoTrackMuIsoStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackMuIsoStatDown_LL_->Fill(SearchBin, isoTrackMuIsoStatDown*scaleFactorWeightData/2);
		   	totalPredIsoTrackElecAccStatUp_LL_->Fill(SearchBin, isoTrackElecAccStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackElecAccStatDown_LL_->Fill(SearchBin, isoTrackElecAccStatDown*scaleFactorWeightData/2);
		    totalPredIsoTrackElecIDStatUp_LL_->Fill(SearchBin, isoTrackElecIDStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackElecIDStatDown_LL_->Fill(SearchBin, isoTrackElecIDStatDown*scaleFactorWeightData/2);
		    totalPredIsoTrackElecIsoStatUp_LL_->Fill(SearchBin, isoTrackElecIsoStatUp*scaleFactorWeightData/2);
		    totalPredIsoTrackElecIsoStatDown_LL_->Fill(SearchBin, isoTrackElecIsoStatDown*scaleFactorWeightData/2);
		    totalPredMTWStatUp_LL_->Fill(SearchBin, MTWStatUp*scaleFactorWeightData/2);
		    totalPredMTWStatDown_LL_->Fill(SearchBin, MTWStatDown*scaleFactorWeightData/2);
		    totalPredPurityStatUp_LL_->Fill(SearchBin, purityStatUp*scaleFactorWeightData/2);
		    totalPredPurityStatDown_LL_->Fill(SearchBin, purityStatDown*scaleFactorWeightData/2);
		    totalPredSingleLepPurityStatUp_LL_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeightData/2);
		    totalPredSingleLepPurityStatDown_LL_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeightData/2);
		    totalPredDiLepSRStatUp_LL_->Fill(SearchBin, diLepSRStatUp*scaleFactorWeightData/2);
		    totalPredDiLepSRStatDown_LL_->Fill(SearchBin, diLepSRStatDown*scaleFactorWeightData/2);
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
		}

		fPre->Close();
	  	std::cout<<"Finished"<<std::endl;
	}


	TFile *LLoutputFile = new TFile(OutputPath_Prediction.c_str(),"RECREATE");
	saveHistograms(LLoutputFile, doCombinedUnc, doAdditionalPlots);
	LLoutputFile->Close();


}



void saveHistograms(TFile* tf, bool combinedUnc, bool addCont){
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

	for(int i = 0; i<=totalPredControlStat_LL_->GetNbinsX()+1; ++i){
		totalPredControlStat_LL_->SetBinContent(i, totalPred_LL_->GetBinError(i));
	}
	SaveFraction(totalPredControlStat_LL_, totalPred_LL_, dPreData, "llp_ControlStat");

	for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
		totalPredNonClosureUp_LL_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
		//std::cout<<i<<": "<<ClosureTest->GetBinContent(i)<<"-"<<ClosureTest->GetBinError(i)<<std::endl;
		totalPredNonClosureDown_LL_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	}
	SetBinLabel(totalPredNonClosureUp_LL_, "llp_nonClosure");
	totalPredNonClosureUp_LL_->Write();
	SetBinLabel(totalPredNonClosureDown_LL_, "llp_nonClosure");
	totalPredNonClosureDown_LL_->Write();

	SetBinLabel(totalCS_LL_);
	totalCS_LL_->Write();
	SetBinLabel(nEvtsCS_LL_);
	nEvtsCS_LL_->Write();

	std::vector<TH1D*> isoTrackStatUncUp_LL_;
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackMuAccStatUp_LL_);
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackMuIDStatUp_LL_);
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackMuIsoStatUp_LL_);
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackElecAccStatUp_LL_);
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackElecIDStatUp_LL_);
	isoTrackStatUncUp_LL_.push_back(totalPredIsoTrackElecIsoStatUp_LL_);
	addUncertainties(totalPredIsoTrackStatUp_LL_, isoTrackStatUncUp_LL_, true);

	std::vector<TH1D*> isoTrackStatUncDown_LL_;
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackMuAccStatDown_LL_);
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackMuIDStatDown_LL_);
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackMuIsoStatDown_LL_);
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackElecAccStatDown_LL_);
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackElecIDStatDown_LL_);
	isoTrackStatUncDown_LL_.push_back(totalPredIsoTrackElecIsoStatDown_LL_);
	addUncertainties(totalPredIsoTrackStatDown_LL_, isoTrackStatUncDown_LL_, false);
  
	std::vector<TH1D*> allUncUp_LL_;
	allUncUp_LL_.push_back(totalPredIsoTrackSysUp_LL_);
	allUncUp_LL_.push_back(totalPredMTWSysUp_LL_);
	allUncUp_LL_.push_back(totalPredPuritySysUp_LL_);
	allUncUp_LL_.push_back(totalPredSingleLepPuritySysUp_LL_);
	allUncUp_LL_.push_back(totalPredDiLepSRSysUp_LL_);
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
	allUncUp_LL_.push_back(totalPredDiLepSRStatUp_LL_);
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
	allUncDown_LL_.push_back(totalPredDiLepSRSysDown_LL_);
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
	allUncDown_LL_.push_back(totalPredDiLepSRStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuIsoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuRecoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredMuAccStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecIsoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecRecoStatDown_LL_);
	allUncDown_LL_.push_back(totalPredElecAccStatDown_LL_);
	addUncertainties(totalPropSysDown_LL_, allUncDown_LL_, false);
  
  	/*
	  SaveFraction(totalPredMuIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredMuIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackSysUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackSysDown_LL_, totalPred_LL_, dPreData);
	*/
	SaveFraction(totalPredIsoTrackSysUp_LL_, totalPred_LL_, dPreData, "llp_isoTrackSys", "all");
	SaveFraction(totalPredIsoTrackSysDown_LL_, totalPred_LL_, dPreData, "llp_isoTrackSys", "all");
	SaveFraction(totalPredMTWSysUp_LL_, totalPred_LL_, dPreData, "llp_mtwSys", "NJetsHTMHT");
	SaveFraction(totalPredMTWSysDown_LL_, totalPred_LL_, dPreData, "llp_mtwSys", "NJetsHTMHT");
	SaveFraction(totalPredPuritySysUp_LL_, totalPred_LL_, dPreData, "llp_puritySys", "MHTNJets");
	SaveFraction(totalPredPuritySysDown_LL_, totalPred_LL_, dPreData, "llp_puritySys", "MHTNJets");

	SaveFraction(totalPredMuIsoSysUp_LL_, totalPred_LL_, dPreData, "llp_muIsoSys", "ptAct");
	SaveFraction(totalPredMuIsoSysDown_LL_, totalPred_LL_, dPreData, "llp_muIsoSys", "ptAct");
	SaveFraction(totalPredMuRecoSysUp_LL_, totalPred_LL_, dPreData, "llp_muRecoSys", "ptAct");
	SaveFraction(totalPredMuRecoSysDown_LL_, totalPred_LL_, dPreData, "llp_muRecoSys", "ptAct");

	SaveFraction(totalPredElecIsoSysUp_LL_, totalPred_LL_, dPreData, "llp_elecIsoSys", "ptAct");
	SaveFraction(totalPredElecIsoSysDown_LL_, totalPred_LL_, dPreData, "llp_elecIsoSys", "ptAct");
	SaveFraction(totalPredElecRecoSysUp_LL_, totalPred_LL_, dPreData, "llp_elecRecoSys", "ptAct");
	SaveFraction(totalPredElecRecoSysDown_LL_, totalPred_LL_, dPreData, "llp_elecRecoSys", "ptAct");
	
	/*
	  SaveFraction(totalPredMuIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredMuIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredElecIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackStatUp_LL_, totalPred_LL_, dPreData);
	  SaveFraction(totalPredPionIsoTrackStatDown_LL_, totalPred_LL_, dPreData);
	*/
	SaveFraction(totalPredIsoTrackStatUp_LL_, totalPred_LL_, dPreData, "llp_isoTrackStat", "BinByBin");
	SaveFraction(totalPredIsoTrackStatDown_LL_, totalPred_LL_, dPreData, "llp_isoTrackStat", "BinByBin");
	SaveFraction(totalPredMTWStatUp_LL_, totalPred_LL_, dPreData, "llp_mtwStat", "BinByBin");
	SaveFraction(totalPredMTWStatDown_LL_, totalPred_LL_, dPreData, "llp_mtwStat", "BinByBin");
	SaveFraction(totalPredPurityStatUp_LL_, totalPred_LL_, dPreData, "llp_purityStat", "MHTNJets");
	SaveFraction(totalPredPurityStatDown_LL_, totalPred_LL_, dPreData, "llp_purityStat", "MHTNJets");

	if(!combinedUnc){
		SaveFraction(totalPredSingleLepPuritySysUp_LL_, totalPred_LL_, dPreData, "llp_singleLepPuritySys", "NJetsBTags");
		SaveFraction(totalPredSingleLepPuritySysDown_LL_, totalPred_LL_, dPreData, "llp_singleLepPuritySys", "NJetsBTags");
		SaveFraction(totalPredDiLepSRSysUp_LL_, totalPred_LL_, dPreData, "llp_diLepSRSys", "NJetsBTags");
		SaveFraction(totalPredDiLepSRSysDown_LL_, totalPred_LL_, dPreData, "llp_diLepSRSys", "NJetsBTags");

		SaveFraction(totalPredMuAccSysUp_LL_, totalPred_LL_, dPreData, "llp_muAccSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccSysDown_LL_, totalPred_LL_, dPreData, "llp_muAccSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccQsquareSysUp_LL_, totalPred_LL_, dPreData, "llp_muAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccQsquareSysDown_LL_, totalPred_LL_, dPreData, "llp_muAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccSysUp_LL_, totalPred_LL_, dPreData, "llp_elecAccSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccSysDown_LL_, totalPred_LL_, dPreData, "llp_elecAccSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccQsquareSysUp_LL_, totalPred_LL_, dPreData, "llp_elecAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccQsquareSysDown_LL_, totalPred_LL_, dPreData, "llp_elecAccQsquareSys", "NJetsHTMHT");

		SaveFraction(totalPredSingleLepPurityStatUp_LL_, totalPred_LL_, dPreData, "llp_singleLepPurityStat", "NJetsBTags");
		SaveFraction(totalPredSingleLepPurityStatDown_LL_, totalPred_LL_, dPreData, "llp_singleLepPurityStat", "NJetsBTags");
		SaveFraction(totalPredDiLepSRStatUp_LL_, totalPred_LL_, dPreData, "llp_diLepSRStat", "NJetsBTags");
		SaveFraction(totalPredDiLepSRStatDown_LL_, totalPred_LL_, dPreData, "llp_diLepSRStat", "NJetsBTags");

		SaveFraction(totalPredMuIsoStatUp_LL_, totalPred_LL_, dPreData, "llp_muIsoStat", "ptAct");
		SaveFraction(totalPredMuIsoStatDown_LL_, totalPred_LL_, dPreData, "llp_muIsoStat", "ptAct");
		SaveFraction(totalPredMuRecoStatUp_LL_, totalPred_LL_, dPreData, "llp_muRecoStat", "ptAct");
		SaveFraction(totalPredMuRecoStatDown_LL_, totalPred_LL_, dPreData, "llp_muRecoStat", "ptAct");
		SaveFraction(totalPredMuAccStatUp_LL_, totalPred_LL_, dPreData, "llp_muAccStat", "BinByBin");
		SaveFraction(totalPredMuAccStatDown_LL_, totalPred_LL_, dPreData, "llp_muAccStat", "BinByBin");
		SaveFraction(totalPredElecIsoStatUp_LL_, totalPred_LL_, dPreData, "llp_elecIsoStat", "ptAct");
		SaveFraction(totalPredElecIsoStatDown_LL_, totalPred_LL_, dPreData, "llp_elecIsoStat", "ptAct");
		SaveFraction(totalPredElecRecoStatUp_LL_, totalPred_LL_, dPreData, "llp_elecRecoStat", "ptAct");
		SaveFraction(totalPredElecRecoStatDown_LL_, totalPred_LL_, dPreData, "llp_elecRecoStat", "ptAct");
		SaveFraction(totalPredElecAccStatUp_LL_, totalPred_LL_, dPreData, "llp_elecAccStat", "BinByBin");
		SaveFraction(totalPredElecAccStatDown_LL_, totalPred_LL_, dPreData, "llp_elecAccStat", "BinByBin");
	}else{
		std::vector<TH1D*> diLepContributionSysUp_LL_;
		diLepContributionSysUp_LL_.push_back(totalPredSingleLepPuritySysUp_LL_);
		diLepContributionSysUp_LL_.push_back(totalPredDiLepSRSysUp_LL_);
		addUncertainties(totalPredDiLepContributionSysUp_LL_, diLepContributionSysUp_LL_, true);
		SaveFraction(totalPredDiLepContributionSysUp_LL_, totalPred_LL_, dPreData, "llp_diLepContribSys", "NJetsBTags");
		std::vector<TH1D*> diLepContributionSysDown_LL_;
		diLepContributionSysDown_LL_.push_back(totalPredSingleLepPuritySysDown_LL_);
		diLepContributionSysDown_LL_.push_back(totalPredDiLepSRSysDown_LL_);
		addUncertainties(totalPredDiLepContributionSysDown_LL_, diLepContributionSysDown_LL_, false);
		SaveFraction(totalPredDiLepContributionSysDown_LL_, totalPred_LL_, dPreData, "llp_diLepContribSys", "NJetsBTags");

		std::vector<TH1D*> lepAccSysUp_LL_;
		lepAccSysUp_LL_.push_back(totalPredMuAccSysUp_LL_);
		lepAccSysUp_LL_.push_back(totalPredElecAccSysUp_LL_);
		addUncertainties(totalPredLepAccSysUp_LL_, lepAccSysUp_LL_, true);
		SaveFraction(totalPredLepAccSysUp_LL_, totalPred_LL_, dPreData, "llp_lepAccSys", "NJetsHTMHT");
		std::vector<TH1D*> lepAccSysDown_LL_;
		lepAccSysDown_LL_.push_back(totalPredMuAccSysDown_LL_);
		lepAccSysDown_LL_.push_back(totalPredElecAccSysDown_LL_);
		addUncertainties(totalPredLepAccSysDown_LL_, lepAccSysDown_LL_, false);
		SaveFraction(totalPredLepAccSysDown_LL_, totalPred_LL_, dPreData, "llp_lepAccSys", "NJetsHTMHT");

		std::vector<TH1D*> lepAccQsquareSysUp_LL_;
		lepAccQsquareSysUp_LL_.push_back(totalPredMuAccQsquareSysUp_LL_);
		lepAccQsquareSysUp_LL_.push_back(totalPredElecAccQsquareSysUp_LL_);
		addUncertainties(totalPredLepAccQsquareSysUp_LL_, lepAccQsquareSysUp_LL_, true);
		SaveFraction(totalPredLepAccQsquareSysUp_LL_, totalPred_LL_, dPreData, "llp_lepAccQsquareSys", "NJetsHTMHT");
		std::vector<TH1D*> lepAccQsquareSysDown_LL_;
		lepAccQsquareSysDown_LL_.push_back(totalPredMuAccQsquareSysDown_LL_);
		lepAccQsquareSysDown_LL_.push_back(totalPredElecAccQsquareSysDown_LL_);
		addUncertainties(totalPredLepAccQsquareSysDown_LL_, lepAccQsquareSysDown_LL_, false);
		SaveFraction(totalPredLepAccQsquareSysDown_LL_, totalPred_LL_, dPreData, "llp_lepAccQsquareSys", "NJetsHTMHT");


		std::vector<TH1D*> diLepContributionStatUp_LL_;
		diLepContributionStatUp_LL_.push_back(totalPredSingleLepPurityStatUp_LL_);
		diLepContributionStatUp_LL_.push_back(totalPredDiLepSRStatUp_LL_);
		addUncertainties(totalPredDiLepContributionStatUp_LL_, diLepContributionStatUp_LL_, true);
		SaveFraction(totalPredDiLepContributionStatUp_LL_, totalPred_LL_, dPreData, "llp_diLepContribStat", "NJetsBTags");
		std::vector<TH1D*> diLepContributionStatDown_LL_;
		diLepContributionStatDown_LL_.push_back(totalPredSingleLepPurityStatDown_LL_);
		diLepContributionStatDown_LL_.push_back(totalPredDiLepSRStatDown_LL_);
		addUncertainties(totalPredDiLepContributionStatDown_LL_, diLepContributionStatDown_LL_, false);
		SaveFraction(totalPredDiLepContributionStatDown_LL_, totalPred_LL_, dPreData, "llp_diLepContribStat", "NJetsBTags");

		std::vector<TH1D*> lepRecoIsoStatUp_LL_;
		lepRecoIsoStatUp_LL_.push_back(totalPredMuIsoStatUp_LL_);
		lepRecoIsoStatUp_LL_.push_back(totalPredMuRecoStatUp_LL_);
		lepRecoIsoStatUp_LL_.push_back(totalPredElecIsoStatUp_LL_);
		lepRecoIsoStatUp_LL_.push_back(totalPredElecRecoStatUp_LL_);
		addUncertainties(totalPredLepRecoIsoStatUp_LL_, lepRecoIsoStatUp_LL_, true);
		SaveFraction(totalPredLepRecoIsoStatUp_LL_, totalPred_LL_, dPreData, "llp_lepRecoIsoStat", "ptAct");
		std::vector<TH1D*> lepRecoIsoStatDown_LL_;
		lepRecoIsoStatDown_LL_.push_back(totalPredMuIsoStatDown_LL_);
		lepRecoIsoStatDown_LL_.push_back(totalPredMuRecoStatDown_LL_);
		lepRecoIsoStatDown_LL_.push_back(totalPredElecIsoStatDown_LL_);
		lepRecoIsoStatDown_LL_.push_back(totalPredElecRecoStatDown_LL_);
		addUncertainties(totalPredLepRecoIsoStatDown_LL_, lepRecoIsoStatDown_LL_, false);
		SaveFraction(totalPredLepRecoIsoStatDown_LL_, totalPred_LL_, dPreData, "llp_lepRecoIsoStat", "ptAct");

		std::vector<TH1D*> lepAccStatUp_LL_;
		lepAccStatUp_LL_.push_back(totalPredMuAccStatUp_LL_);
		lepAccStatUp_LL_.push_back(totalPredElecAccStatUp_LL_);
		addUncertainties(totalPredLepAccStatUp_LL_, lepAccStatUp_LL_, true);
		SaveFraction(totalPredLepAccStatUp_LL_, totalPred_LL_, dPreData, "llp_lepAccStat", "BinByBin");
		std::vector<TH1D*> lepAccStatDown_LL_;
		lepAccStatDown_LL_.push_back(totalPredMuAccStatDown_LL_);
		lepAccStatDown_LL_.push_back(totalPredElecAccStatDown_LL_);
		addUncertainties(totalPredLepAccStatDown_LL_, lepAccStatDown_LL_, false);
		SaveFraction(totalPredLepAccStatDown_LL_, totalPred_LL_, dPreData, "llp_lepAccStat", "BinByBin");
	}


	tf->cd();
	tf->mkdir("Prediction_MC");
	TDirectory *dPreMC = (TDirectory*)tf->Get("Prediction_MC");
	dPreMC->cd();

	SetBinLabel(totalPred_LL_MC_);
	totalPred_LL_MC_->Write();

	for(int i = 0; i<=totalPredControlStat_LL_MC_->GetNbinsX()+1; ++i){
		totalPredControlStat_LL_MC_->SetBinContent(i, totalPred_LL_MC_->GetBinError(i));
	}
	SaveFraction(totalPredControlStat_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_ControlStat");

	SetBinLabel(totalPred_woIsoTrack_LL_MC_);
	totalPred_woIsoTrack_LL_MC_->Write();

	for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
	    totalPredNonClosureUp_LL_MC_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	    totalPredNonClosureDown_LL_MC_->SetBinContent(i, 1.-min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
	}
	SetBinLabel(totalPredNonClosureUp_LL_MC_, "llp_mc_nonClosure");
	totalPredNonClosureUp_LL_MC_->Write();
	SetBinLabel(totalPredNonClosureDown_LL_MC_, "llp_mc_nonClosure");
	totalPredNonClosureDown_LL_MC_->Write();

	SetBinLabel(totalCS_LL_MC_);
	totalCS_LL_MC_->Write();
	SetBinLabel(nEvtsCS_LL_MC_);
	nEvtsCS_LL_MC_->Write();


	tf->cd();
	tf->mkdir("AvgWeight_MC");
	TDirectory *dAvgWeight = (TDirectory*)tf->Get("AvgWeight_MC");
	dAvgWeight->cd();

	SetBinLabel(avgWeight_LL_);
	avgWeight_LL_->Write();

	TH1D* PredOverCS_LL_ = (TH1D*) totalPred_LL_->Clone("PredOverCS_LL");
	PredOverCS_LL_->Divide(totalCS_LL_);
	PredOverCS_LL_->SetTitle("Prediction / CS (=0L/1L)");
	//Fix for bins where negative sum of events
	for(int i = 1; i < PredOverCS_LL_->GetNbinsX(); i++){
		PredOverCS_LL_->SetBinContent(i, abs(PredOverCS_LL_->GetBinContent(i)));
	}
	SetBinLabel(PredOverCS_LL_);
	PredOverCS_LL_->Write();

	// Fill empty bins with avg. of remaining HTMHT bins
	SetBinLabel(avgWeight_LL_MC_);
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

	TH1D* PredOverCS_LL_MC_ = (TH1D*) totalPred_LL_MC_->Clone("PredOverCS_LL_MC");
	PredOverCS_LL_MC_->Divide(totalCS_LL_MC_);
	PredOverCS_LL_MC_->SetTitle("Prediction / CS (=0L/1L)");
	//Fix for bins where negative sum of events
	for(int i = 1; i < PredOverCS_LL_MC_->GetNbinsX(); i++){
		PredOverCS_LL_MC_->SetBinContent(i, abs(PredOverCS_LL_MC_->GetBinContent(i)));
	}
	SetBinLabel(PredOverCS_LL_MC_);
	PredOverCS_LL_MC_->Write();


	dPreData->cd();
	// Combine 0L/1L histograms for integration: use ratio from data and fill empty bins with ratio from MC
	TH1D* avgWeight_0L1L_ = (TH1D*) totalPred_LL_->Clone("avgWeight_0L1L");
	avgWeight_0L1L_->SetTitle("Prediction / CS (=0L/1L)");
	for(int i = 1; i < avgWeight_0L1L_->GetNbinsX()+1; i++){
		if(avgWeight_LL_->GetBinContent(i)!=0){
			avgWeight_0L1L_->SetBinContent(i, avgWeight_LL_->GetBinContent(i));
			avgWeight_0L1L_->SetBinError(i, avgWeight_LL_->GetBinError(i));
		}else{
			avgWeight_0L1L_->SetBinContent(i, avgWeight_LL_MC_->GetBinContent(i));
			avgWeight_0L1L_->SetBinError(i, avgWeight_LL_MC_->GetBinError(i));
		}
	}
	SetBinLabel(avgWeight_0L1L_);
	avgWeight_0L1L_->Write();


	std::vector<TH1D*> isoTrackStatUncUp_LL_MC_;
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackMuAccStatUp_LL_MC_);
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackMuIDStatUp_LL_MC_);
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackMuIsoStatUp_LL_MC_);
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackElecAccStatUp_LL_MC_);
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackElecIDStatUp_LL_MC_);
	isoTrackStatUncUp_LL_MC_.push_back(totalPredIsoTrackElecIsoStatUp_LL_MC_);
	addUncertainties(totalPredIsoTrackStatUp_LL_MC_, isoTrackStatUncUp_LL_MC_, true);

	std::vector<TH1D*> isoTrackStatUncDown_LL_MC_;
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackMuAccStatDown_LL_MC_);
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackMuIDStatDown_LL_MC_);
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackMuIsoStatDown_LL_MC_);
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackElecAccStatDown_LL_MC_);
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackElecIDStatDown_LL_MC_);
	isoTrackStatUncDown_LL_MC_.push_back(totalPredIsoTrackElecIsoStatDown_LL_MC_);
	addUncertainties(totalPredIsoTrackStatDown_LL_MC_, isoTrackStatUncDown_LL_MC_, false);

	std::vector<TH1D*> allUncUp_LL_MC_;
	allUncUp_LL_MC_.push_back(totalPredIsoTrackSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredMTWSysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredPuritySysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredSingleLepPuritySysUp_LL_MC_);
	allUncUp_LL_MC_.push_back(totalPredDiLepSRSysUp_LL_MC_);
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
	allUncUp_LL_MC_.push_back(totalPredDiLepSRStatUp_LL_MC_);
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
	allUncDown_LL_MC_.push_back(totalPredDiLepSRSysDown_LL_MC_);
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
	allUncDown_LL_MC_.push_back(totalPredDiLepSRStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuIsoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuRecoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredMuAccStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecIsoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecRecoStatDown_LL_MC_);
	allUncDown_LL_MC_.push_back(totalPredElecAccStatDown_LL_MC_);
	addUncertainties(totalPropSysDown_LL_MC_, allUncDown_LL_MC_, false);

	/*
	  SaveFraction(totalPredMuIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreDataMC);
	  SaveFraction(totalPredMuIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	*/
	SaveFraction(totalPredIsoTrackSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_isoTrackSys", "all");
	SaveFraction(totalPredIsoTrackSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_isoTrackSys", "all");
	SaveFraction(totalPredMTWSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_mtwSys", "NJetsHTMHT");
	SaveFraction(totalPredMTWSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_mtwSys", "NJetsHTMHT");
	SaveFraction(totalPredPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_puritySys", "MHTNJets");
	SaveFraction(totalPredPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_puritySys", "MHTNJets");

	SaveFraction(totalPredMuIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muIsoSys", "ptAct");
	SaveFraction(totalPredMuIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muIsoSys", "ptAct");
	SaveFraction(totalPredMuRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muRecoSys", "ptAct");
	SaveFraction(totalPredMuRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muRecoSys", "ptAct");

	SaveFraction(totalPredElecIsoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecIsoSys", "ptAct");
	SaveFraction(totalPredElecIsoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecIsoSys", "ptAct");
	SaveFraction(totalPredElecRecoSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecRecoSys", "ptAct");
	SaveFraction(totalPredElecRecoSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecRecoSys", "ptAct");
	
	/*
	  SaveFraction(totalPredMuIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredMuIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredElecIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC);
	  SaveFraction(totalPredPionIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC);
	*/
	SaveFraction(totalPredIsoTrackStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_isoTrackStat", "BinByBin");
	SaveFraction(totalPredIsoTrackStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_isoTrackStat", "BinByBin");
	SaveFraction(totalPredMTWStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_mtwStat", "BinByBin");
	SaveFraction(totalPredMTWStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_mtwStat", "BinByBin");
	SaveFraction(totalPredPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_purityStat", "MHTNJets");
	SaveFraction(totalPredPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_purityStat", "MHTNJets");

	if(!combinedUnc){
		SaveFraction(totalPredSingleLepPuritySysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_singleLepPuritySys", "NJetsBTags");
		SaveFraction(totalPredSingleLepPuritySysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_singleLepPuritySys", "NJetsBTags");
		SaveFraction(totalPredDiLepSRSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepSRSys", "NJetsBTags");
		SaveFraction(totalPredDiLepSRSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepSRSys", "NJetsBTags");

		SaveFraction(totalPredMuAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredMuAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccQsquareSys", "NJetsHTMHT");
		SaveFraction(totalPredElecAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccQsquareSys", "NJetsHTMHT");

		SaveFraction(totalPredSingleLepPurityStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_singleLepPurityStat", "NJetsBTags");
		SaveFraction(totalPredSingleLepPurityStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_singleLepPurityStat", "NJetsBTags");
		SaveFraction(totalPredDiLepSRStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepSRStat", "NJetsBTags");
		SaveFraction(totalPredDiLepSRStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepSRStat", "NJetsBTags");

		SaveFraction(totalPredMuIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muIsoStat", "ptAct");
		SaveFraction(totalPredMuIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muIsoStat", "ptAct");
		SaveFraction(totalPredMuRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muRecoStat", "ptAct");
		SaveFraction(totalPredMuRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muRecoStat", "ptAct");
		SaveFraction(totalPredMuAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccStat", "BinByBin");
		SaveFraction(totalPredMuAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_muAccStat", "BinByBin");
		SaveFraction(totalPredElecIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecIsoStat", "ptAct");
		SaveFraction(totalPredElecIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecIsoStat", "ptAct");
		SaveFraction(totalPredElecRecoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecRecoStat", "ptAct");
		SaveFraction(totalPredElecRecoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecRecoStat", "ptAct");
		SaveFraction(totalPredElecAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccStat", "BinByBin");
		SaveFraction(totalPredElecAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_elecAccStat", "BinByBin");
	}else{
		std::vector<TH1D*> diLepContributionSysUp_LL_MC_;
		diLepContributionSysUp_LL_MC_.push_back(totalPredSingleLepPuritySysUp_LL_MC_);
		diLepContributionSysUp_LL_MC_.push_back(totalPredDiLepSRSysUp_LL_MC_);
		addUncertainties(totalPredDiLepContributionSysUp_LL_MC_, diLepContributionSysUp_LL_MC_, true);
		SaveFraction(totalPredDiLepContributionSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepContribSys", "NJetsBTags");
		std::vector<TH1D*> diLepContributionSysDown_LL_MC_;
		diLepContributionSysDown_LL_MC_.push_back(totalPredSingleLepPuritySysDown_LL_MC_);
		diLepContributionSysDown_LL_MC_.push_back(totalPredDiLepSRSysDown_LL_MC_);
		addUncertainties(totalPredDiLepContributionSysDown_LL_MC_, diLepContributionSysDown_LL_MC_, false);
		SaveFraction(totalPredDiLepContributionSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepContribSys", "NJetsBTags");

		std::vector<TH1D*> lepAccSysUp_LL_MC_;
		lepAccSysUp_LL_MC_.push_back(totalPredMuAccSysUp_LL_MC_);
		lepAccSysUp_LL_MC_.push_back(totalPredElecAccSysUp_LL_MC_);
		addUncertainties(totalPredLepAccSysUp_LL_MC_, lepAccSysUp_LL_MC_, true);
		SaveFraction(totalPredLepAccSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccSys", "NJetsHTMHT");
		std::vector<TH1D*> lepAccSysDown_LL_MC_;
		lepAccSysDown_LL_MC_.push_back(totalPredMuAccSysDown_LL_MC_);
		lepAccSysDown_LL_MC_.push_back(totalPredElecAccSysDown_LL_MC_);
		addUncertainties(totalPredLepAccSysDown_LL_MC_, lepAccSysDown_LL_MC_, false);
		SaveFraction(totalPredLepAccSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccSys", "NJetsHTMHT");

		std::vector<TH1D*> lepAccQsquareSysUp_LL_MC_;
		lepAccQsquareSysUp_LL_MC_.push_back(totalPredMuAccQsquareSysUp_LL_MC_);
		lepAccQsquareSysUp_LL_MC_.push_back(totalPredElecAccQsquareSysUp_LL_MC_);
		addUncertainties(totalPredLepAccQsquareSysUp_LL_MC_, lepAccQsquareSysUp_LL_MC_, true);
		SaveFraction(totalPredLepAccQsquareSysUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccQsquareSys", "NJetsHTMHT");
		std::vector<TH1D*> lepAccQsquareSysDown_LL_MC_;
		lepAccQsquareSysDown_LL_MC_.push_back(totalPredMuAccQsquareSysDown_LL_MC_);
		lepAccQsquareSysDown_LL_MC_.push_back(totalPredElecAccQsquareSysDown_LL_MC_);
		addUncertainties(totalPredLepAccQsquareSysDown_LL_MC_, lepAccQsquareSysDown_LL_MC_, false);
		SaveFraction(totalPredLepAccQsquareSysDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccQsquareSys", "NJetsHTMHT");


		std::vector<TH1D*> diLepContributionStatUp_LL_MC_;
		diLepContributionStatUp_LL_MC_.push_back(totalPredSingleLepPurityStatUp_LL_MC_);
		diLepContributionStatUp_LL_MC_.push_back(totalPredDiLepSRStatUp_LL_MC_);
		addUncertainties(totalPredDiLepContributionStatUp_LL_MC_, diLepContributionStatUp_LL_MC_, true);
		SaveFraction(totalPredDiLepContributionStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepContribStat", "NJetsBTags");
		std::vector<TH1D*> diLepContributionStatDown_LL_MC_;
		diLepContributionStatDown_LL_MC_.push_back(totalPredSingleLepPurityStatDown_LL_MC_);
		diLepContributionStatDown_LL_MC_.push_back(totalPredDiLepSRStatDown_LL_MC_);
		addUncertainties(totalPredDiLepContributionStatDown_LL_MC_, diLepContributionStatDown_LL_MC_, false);
		SaveFraction(totalPredDiLepContributionStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_diLepContribStat", "NJetsBTags");

		std::vector<TH1D*> lepRecoIsoStatUp_LL_MC_;
		lepRecoIsoStatUp_LL_MC_.push_back(totalPredMuIsoStatUp_LL_MC_);
		lepRecoIsoStatUp_LL_MC_.push_back(totalPredMuRecoStatUp_LL_MC_);
		lepRecoIsoStatUp_LL_MC_.push_back(totalPredElecIsoStatUp_LL_MC_);
		lepRecoIsoStatUp_LL_MC_.push_back(totalPredElecRecoStatUp_LL_MC_);
		addUncertainties(totalPredLepRecoIsoStatUp_LL_MC_, lepRecoIsoStatUp_LL_MC_, true);
		SaveFraction(totalPredLepRecoIsoStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepRecoIsoStat", "ptAct");
		std::vector<TH1D*> lepRecoIsoStatDown_LL_MC_;
		lepRecoIsoStatDown_LL_MC_.push_back(totalPredMuIsoStatDown_LL_MC_);
		lepRecoIsoStatDown_LL_MC_.push_back(totalPredMuRecoStatDown_LL_MC_);
		lepRecoIsoStatDown_LL_MC_.push_back(totalPredElecIsoStatDown_LL_MC_);
		lepRecoIsoStatDown_LL_MC_.push_back(totalPredElecRecoStatDown_LL_MC_);
		addUncertainties(totalPredLepRecoIsoStatDown_LL_MC_, lepRecoIsoStatDown_LL_MC_, false);
		SaveFraction(totalPredLepRecoIsoStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepRecoIsoStat", "ptAct");

		std::vector<TH1D*> lepAccStatUp_LL_MC_;
		lepAccStatUp_LL_MC_.push_back(totalPredMuAccStatUp_LL_MC_);
		lepAccStatUp_LL_MC_.push_back(totalPredElecAccStatUp_LL_MC_);
		addUncertainties(totalPredLepAccStatUp_LL_MC_, lepAccStatUp_LL_MC_, true);
		SaveFraction(totalPredLepAccStatUp_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccStat", "BinByBin");
		std::vector<TH1D*> lepAccStatDown_LL_MC_;
		lepAccStatDown_LL_MC_.push_back(totalPredMuAccStatDown_LL_MC_);
		lepAccStatDown_LL_MC_.push_back(totalPredElecAccStatDown_LL_MC_);
		addUncertainties(totalPredLepAccStatDown_LL_MC_, lepAccStatDown_LL_MC_, false);
		SaveFraction(totalPredLepAccStatDown_LL_MC_, totalPred_LL_MC_, dPreMC, "llp_mc_lepAccStat", "BinByBin");
	}


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

	if(addCont){
		tf->cd();
		tf->mkdir("Plotting");
		TDirectory *dPlotting = (TDirectory*)tf->Get("Plotting");
		dPlotting->cd();

		//SetBinLabel(totalCSCombined_LL_MC_);
		totalCSCombined_LL_MC_->Write();
		totalCSCombined_LL_HT_MC_->Write();
		totalCSCombined_LL_MHT_MC_->Write();
		totalCSCombined_LL_MET_MC_->Write();
		totalCSCombined_LL_NJets_MC_->Write();
		totalCSCombined_LL_NBTags_MC_->Write();
		
		//SetBinLabel(totalExpCombined_LL_MC_);
		totalExpCombined_LL_MC_->Write();
		totalExpCombined_LL_HT_MC_->Write();
		totalExpCombined_LL_MHT_MC_->Write();
		totalExpCombined_LL_MET_MC_->Write();
		totalExpCombined_LL_NJets_MC_->Write();
		totalExpCombined_LL_NBTags_MC_->Write();

		//SetBinLabel(totalPreCombined_LL_MC_);
		totalPreCombined_LL_MC_->Write();
		totalPreCombined_LL_HT_MC_->Write();
		totalPreCombined_LL_MHT_MC_->Write();
		totalPreCombined_LL_MET_MC_->Write();
		totalPreCombined_LL_NJets_MC_->Write();
		totalPreCombined_LL_NBTags_MC_->Write();


		tf->cd();
		tf->mkdir("AdditionalPlots");
		TDirectory *dAddPlots = (TDirectory*)tf->Get("AdditionalPlots");
		dAddPlots->cd();

		SetBinLabel(totalCS_LL_Mu_MC_);
		totalCS_LL_Mu_MC_->Write();
		totalCS_LL_HT_Mu_MC_->Write();
		totalCS_LL_MHT_Mu_MC_->Write();
		totalCS_LL_MET_Mu_MC_->Write();
		totalCS_LL_NJets_Mu_MC_->Write();
		totalCS_LL_NBTags_Mu_MC_->Write();
		totalCS_LL_LepPt_Mu_MC_->Write();
		
		SetBinLabel(totalCS_LL_Elec_MC_);
		totalCS_LL_Elec_MC_->Write();
		totalCS_LL_HT_Elec_MC_->Write();
		totalCS_LL_MHT_Elec_MC_->Write();
		totalCS_LL_MET_Elec_MC_->Write();
		totalCS_LL_NJets_Elec_MC_->Write();
		totalCS_LL_NBTags_Elec_MC_->Write();
		totalCS_LL_LepPt_Elec_MC_->Write();

		SetBinLabel(totalCS_LL_Mu_);
		totalCS_LL_Mu_->Write();
		totalCS_LL_HT_Mu_->Write();
		totalCS_LL_MHT_Mu_->Write();
		totalCS_LL_MET_Mu_->Write();
		totalCS_LL_NJets_Mu_->Write();
		totalCS_LL_NBTags_Mu_->Write();
		totalCS_LL_LepPt_Mu_->Write();
		
		SetBinLabel(totalCS_LL_Elec_);
		totalCS_LL_Elec_->Write();
		totalCS_LL_HT_Elec_->Write();
		totalCS_LL_MHT_Elec_->Write();
		totalCS_LL_MET_Elec_->Write();
		totalCS_LL_NJets_Elec_->Write();
		totalCS_LL_NBTags_Elec_->Write();
		totalCS_LL_LepPt_Elec_->Write();

		tf->cd();
		tf->mkdir("PlotsThesis");
		TDirectory *dPlotsThesis = (TDirectory*)tf->Get("PlotsThesis");
		dPlotsThesis->cd();

		dPlotsThesis->mkdir("Source");
		TDirectory *dPlotsThesisSource = (TDirectory*)dPlotsThesis->Get("Source");
		dPlotsThesisSource->cd();

		setTDRStyle();
		gStyle->SetPalette(1);

		//SetBinLabel(totalAccMu_);
		totalAccMu_->Divide(totalFractionNormMu_);
		totalAccMu_HT_->Divide(totalFractionNormMu_HT_);
		totalAccMu_MHT_->Divide(totalFractionNormMu_MHT_);
		totalAccMu_NJets_->Divide(totalFractionNormMu_NJets_);
		totalAccMu_NBTags_->Divide(totalFractionNormMu_NBTags_);
		totalAccMu_->Write();
		totalAccMu_HT_->Write();
		totalAccMu_MHT_->Write();
		totalAccMu_NJets_->Write();
		totalAccMu_NBTags_->Write();

		//SetBinLabel(totalRecoMu_);
		totalRecoMu_->Divide(totalFractionNormMu_);
		totalRecoMu_HT_->Divide(totalFractionNormMu_HT_);
		totalRecoMu_MHT_->Divide(totalFractionNormMu_MHT_);
		totalRecoMu_NJets_->Divide(totalFractionNormMu_NJets_);
		totalRecoMu_NBTags_->Divide(totalFractionNormMu_NBTags_);
		totalRecoMu_->Write();
		totalRecoMu_HT_->Write();
		totalRecoMu_MHT_->Write();
		totalRecoMu_NJets_->Write();
		totalRecoMu_NBTags_->Write();

		//SetBinLabel(totalIsoMu_);
		totalIsoMu_->Divide(totalFractionNormMu_);
		totalIsoMu_HT_->Divide(totalFractionNormMu_HT_);
		totalIsoMu_MHT_->Divide(totalFractionNormMu_MHT_);
		totalIsoMu_NJets_->Divide(totalFractionNormMu_NJets_);
		totalIsoMu_NBTags_->Divide(totalFractionNormMu_NBTags_);
		totalIsoMu_->Write();
		totalIsoMu_HT_->Write();
		totalIsoMu_MHT_->Write();
		totalIsoMu_NJets_->Write();
		totalIsoMu_NBTags_->Write();

		//SetBinLabel(totalAccElec_);
		totalAccElec_->Divide(totalFractionNormElec_);
		totalAccElec_HT_->Divide(totalFractionNormElec_HT_);
		totalAccElec_MHT_->Divide(totalFractionNormElec_MHT_);
		totalAccElec_NJets_->Divide(totalFractionNormElec_NJets_);
		totalAccElec_NBTags_->Divide(totalFractionNormElec_NBTags_);
		totalAccElec_->Write();
		totalAccElec_HT_->Write();
		totalAccElec_MHT_->Write();
		totalAccElec_NJets_->Write();
		totalAccElec_NBTags_->Write();

		//SetBinLabel(totalRecoElec_);
		totalRecoElec_->Divide(totalFractionNormElec_);
		totalRecoElec_HT_->Divide(totalFractionNormElec_HT_);
		totalRecoElec_MHT_->Divide(totalFractionNormElec_MHT_);
		totalRecoElec_NJets_->Divide(totalFractionNormElec_NJets_);
		totalRecoElec_NBTags_->Divide(totalFractionNormElec_NBTags_);
		totalRecoElec_->Write();
		totalRecoElec_HT_->Write();
		totalRecoElec_MHT_->Write();
		totalRecoElec_NJets_->Write();
		totalRecoElec_NBTags_->Write();

		//SetBinLabel(totalIsoElec_);
		totalIsoElec_->Divide(totalFractionNormElec_);
		totalIsoElec_HT_->Divide(totalFractionNormElec_HT_);
		totalIsoElec_MHT_->Divide(totalFractionNormElec_MHT_);
		totalIsoElec_NJets_->Divide(totalFractionNormElec_NJets_);
		totalIsoElec_NBTags_->Divide(totalFractionNormElec_NBTags_);
		totalIsoElec_->Write();
		totalIsoElec_HT_->Write();
		totalIsoElec_MHT_->Write();
		totalIsoElec_NJets_->Write();
		totalIsoElec_NBTags_->Write();

		dPlotsThesis->cd();

		totalAccMu_->SetLineColor(kBlack);
		totalAccMu_HT_->SetLineColor(kBlack);
		totalAccMu_MHT_->SetLineColor(kBlack);
		totalAccMu_NJets_->SetLineColor(kBlack);
		totalAccMu_NBTags_->SetLineColor(kBlack);
		totalRecoMu_->SetLineColor(kBlack);
		totalRecoMu_HT_->SetLineColor(kBlack);
		totalRecoMu_MHT_->SetLineColor(kBlack);
		totalRecoMu_NJets_->SetLineColor(kBlack);
		totalRecoMu_NBTags_->SetLineColor(kBlack);
		totalIsoMu_->SetLineColor(kBlack);
		totalIsoMu_HT_->SetLineColor(kBlack);
		totalIsoMu_MHT_->SetLineColor(kBlack);
		totalIsoMu_NJets_->SetLineColor(kBlack);
		totalIsoMu_NBTags_->SetLineColor(kBlack);
		totalAccElec_->SetLineColor(kBlack);
		totalAccElec_HT_->SetLineColor(kBlack);
		totalAccElec_MHT_->SetLineColor(kBlack);
		totalAccElec_NJets_->SetLineColor(kBlack);
		totalAccElec_NBTags_->SetLineColor(kBlack);
		totalRecoElec_->SetLineColor(kBlack);
		totalRecoElec_HT_->SetLineColor(kBlack);
		totalRecoElec_MHT_->SetLineColor(kBlack);
		totalRecoElec_NJets_->SetLineColor(kBlack);
		totalRecoElec_NBTags_->SetLineColor(kBlack);
		totalIsoElec_->SetLineColor(kBlack);
		totalIsoElec_HT_->SetLineColor(kBlack);
		totalIsoElec_MHT_->SetLineColor(kBlack);
		totalIsoElec_NJets_->SetLineColor(kBlack);
		totalIsoElec_NBTags_->SetLineColor(kBlack);

		totalAccMu_->SetFillColor(kRed);
		totalFractionMu_->Add(totalAccMu_);
		totalAccMu_HT_->SetFillColor(kRed);
		totalFractionMu_HT_->Add(totalAccMu_HT_);
		totalAccMu_MHT_->SetFillColor(kRed);
		totalFractionMu_MHT_->Add(totalAccMu_MHT_);
		totalAccMu_NJets_->SetFillColor(kRed);
		totalFractionMu_NJets_->Add(totalAccMu_NJets_);
		totalAccMu_NBTags_->SetFillColor(kRed);
		totalFractionMu_NBTags_->Add(totalAccMu_NBTags_);

		totalRecoMu_->SetFillColor(kBlue);
		totalFractionMu_->Add(totalRecoMu_);
		totalRecoMu_HT_->SetFillColor(kBlue);
		totalFractionMu_HT_->Add(totalRecoMu_HT_);
		totalRecoMu_MHT_->SetFillColor(kBlue);
		totalFractionMu_MHT_->Add(totalRecoMu_MHT_);
		totalRecoMu_NJets_->SetFillColor(kBlue);
		totalFractionMu_NJets_->Add(totalRecoMu_NJets_);
		totalRecoMu_NBTags_->SetFillColor(kBlue);
		totalFractionMu_NBTags_->Add(totalRecoMu_NBTags_);

		totalIsoMu_->SetFillColor(kGreen);
		totalFractionMu_->Add(totalIsoMu_);
		totalIsoMu_HT_->SetFillColor(kGreen);
		totalFractionMu_HT_->Add(totalIsoMu_HT_);
		totalIsoMu_MHT_->SetFillColor(kGreen);
		totalFractionMu_MHT_->Add(totalIsoMu_MHT_);
		totalIsoMu_NJets_->SetFillColor(kGreen);
		totalFractionMu_NJets_->Add(totalIsoMu_NJets_);
		totalIsoMu_NBTags_->SetFillColor(kGreen);
		totalFractionMu_NBTags_->Add(totalIsoMu_NBTags_);

		totalAccElec_->SetFillColor(kRed);
		totalFractionElec_->Add(totalAccElec_);
		totalAccElec_HT_->SetFillColor(kRed);
		totalFractionElec_HT_->Add(totalAccElec_HT_);
		totalAccElec_MHT_->SetFillColor(kRed);
		totalFractionElec_MHT_->Add(totalAccElec_MHT_);
		totalAccElec_NJets_->SetFillColor(kRed);
		totalFractionElec_NJets_->Add(totalAccElec_NJets_);
		totalAccElec_NBTags_->SetFillColor(kRed);
		totalFractionElec_NBTags_->Add(totalAccElec_NBTags_);

		totalRecoElec_->SetFillColor(kBlue);
		totalFractionElec_->Add(totalRecoElec_);
		totalRecoElec_HT_->SetFillColor(kBlue);
		totalFractionElec_HT_->Add(totalRecoElec_HT_);
		totalRecoElec_MHT_->SetFillColor(kBlue);
		totalFractionElec_MHT_->Add(totalRecoElec_MHT_);
		totalRecoElec_NJets_->SetFillColor(kBlue);
		totalFractionElec_NJets_->Add(totalRecoElec_NJets_);
		totalRecoElec_NBTags_->SetFillColor(kBlue);
		totalFractionElec_NBTags_->Add(totalRecoElec_NBTags_);

		totalIsoElec_->SetFillColor(kGreen);
		totalFractionElec_->Add(totalIsoElec_);
		totalIsoElec_HT_->SetFillColor(kGreen);
		totalFractionElec_HT_->Add(totalIsoElec_HT_);
		totalIsoElec_MHT_->SetFillColor(kGreen);
		totalFractionElec_MHT_->Add(totalIsoElec_MHT_);
		totalIsoElec_NJets_->SetFillColor(kGreen);
		totalFractionElec_NJets_->Add(totalIsoElec_NJets_);
		totalIsoElec_NBTags_->SetFillColor(kGreen);
		totalFractionElec_NBTags_->Add(totalIsoElec_NBTags_);

		totalFractionMu_HT_->Write();
		totalFractionElec_HT_->Write();
		totalFractionMu_MHT_->Write();
		totalFractionElec_MHT_->Write();
		totalFractionMu_NJets_->Write();
		totalFractionElec_NJets_->Write();
		totalFractionMu_NBTags_->Write();
		totalFractionElec_NBTags_->Write();
		totalFractionMu_->Write();
		totalFractionElec_->Write();

		char xtitlename[200];
  		char ytitlename[200];
  		sprintf(ytitlename,"Fraction of Events");
  		sprintf(xtitlename,"H_{T} [GeV]");
		PlotFraction("", totalFractionMu_HT_, true, xtitlename, ytitlename);
		PlotFraction("", totalFractionElec_HT_, false, xtitlename, ytitlename);
		sprintf(xtitlename,"H_{T}^{miss} [GeV]");
		PlotFraction("", totalFractionMu_MHT_, true, xtitlename, ytitlename);
		PlotFraction("", totalFractionElec_MHT_, false, xtitlename, ytitlename);
		sprintf(xtitlename,"N_{jet}");
		PlotFraction("", totalFractionMu_NJets_, true, xtitlename, ytitlename);
		PlotFraction("", totalFractionElec_NJets_, false, xtitlename, ytitlename);
		sprintf(xtitlename,"N_{b-jet}");
		PlotFraction("", totalFractionMu_NBTags_, true, xtitlename, ytitlename);
		PlotFraction("", totalFractionElec_NBTags_, false, xtitlename, ytitlename);
		sprintf(xtitlename,"Search region bin number");
		PlotFraction("", totalFractionMu_, true, xtitlename, ytitlename);
		PlotFraction("", totalFractionElec_, false, xtitlename, ytitlename);

		dAddPlots->mkdir("DoubleRatio");
		TDirectory *dAddPlots2 = (TDirectory*)dAddPlots->Get("DoubleRatio");
		dAddPlots2->cd();

		TH1D* totalCS_DR_SB = new TH1D("totalCS_DR_SB", "totalCS_DR_SB", totalCS_LL_Mu_MC_->GetNbinsX(), 0.5, totalCS_LL_Mu_MC_->GetNbinsX()+0.5);
		TH1D* totalCS_DR_HT = new TH1D("totalCS_DR_HT", "totalCS_DR_HT", 22, 250, 3000);
		TH1D* totalCS_DR_MHT = new TH1D("totalCS_DR_MHT", "totalCS_DR_MHT", 20, 250, 1500);
		TH1D* totalCS_DR_MET = new TH1D("totalCS_DR_MET", "totalCS_DR_MET", 22, 125, 1500);
		TH1D* totalCS_DR_NJets = new TH1D("totalCS_DR_NJets", "totalCS_DR_NJets", 9, 1.5, 10.5);
		TH1D* totalCS_DR_NBTags = new TH1D("totalCS_DR_NBTags", "totalCS_DR_NBTags", 4, -0.5, 3.5);
		TH1D* totalCS_DR_LepPt = new TH1D("totalCS_DR_LepPt", "totalCS_DR_LepPt", 25, 0, 500);

		totalCS_LL_Mu_->Divide(totalCS_LL_Mu_MC_);
		totalCS_LL_Elec_->Divide(totalCS_LL_Elec_MC_);
		totalCS_DR_SB->Divide(totalCS_LL_Mu_, totalCS_LL_Elec_);
		SetBinLabel(totalCS_DR_SB);
		totalCS_DR_SB->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_SB->Write();

		totalCS_LL_HT_Mu_->Divide(totalCS_LL_HT_Mu_MC_);
		totalCS_LL_HT_Elec_->Divide(totalCS_LL_HT_Elec_MC_);
		totalCS_DR_HT->Divide(totalCS_LL_HT_Mu_, totalCS_LL_HT_Elec_);
		totalCS_DR_HT->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_HT->Write();

		totalCS_LL_MHT_Mu_->Divide(totalCS_LL_MHT_Mu_MC_);
		totalCS_LL_MHT_Elec_->Divide(totalCS_LL_MHT_Elec_MC_);
		totalCS_DR_MHT->Divide(totalCS_LL_MHT_Mu_, totalCS_LL_MHT_Elec_);
		totalCS_DR_MHT->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_MHT->Write();

		totalCS_LL_MET_Mu_->Divide(totalCS_LL_MET_Mu_MC_);
		totalCS_LL_MET_Elec_->Divide(totalCS_LL_MET_Elec_MC_);
		totalCS_DR_MET->Divide(totalCS_LL_MET_Mu_, totalCS_LL_MET_Elec_);
		totalCS_DR_MET->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_MET->Write();

		totalCS_LL_NJets_Mu_->Divide(totalCS_LL_NJets_Mu_MC_);
		totalCS_LL_NJets_Elec_->Divide(totalCS_LL_NJets_Elec_MC_);
		totalCS_DR_NJets->Divide(totalCS_LL_NJets_Mu_, totalCS_LL_NJets_Elec_);
		totalCS_DR_NJets->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_NJets->Write();

		totalCS_LL_NBTags_Mu_->Divide(totalCS_LL_NBTags_Mu_MC_);
		totalCS_LL_NBTags_Elec_->Divide(totalCS_LL_NBTags_Elec_MC_);
		totalCS_DR_NBTags->Divide(totalCS_LL_NBTags_Mu_, totalCS_LL_NBTags_Elec_);
		totalCS_DR_NBTags->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_NBTags->Write();

		totalCS_LL_LepPt_Mu_->Divide(totalCS_LL_LepPt_Mu_MC_);
		totalCS_LL_LepPt_Elec_->Divide(totalCS_LL_LepPt_Elec_MC_);
		totalCS_DR_LepPt->Divide(totalCS_LL_LepPt_Mu_, totalCS_LL_LepPt_Elec_);
		totalCS_DR_LepPt->GetYaxis()->SetRangeUser(0., 2.);
		totalCS_DR_LepPt->Write();
	}
}

void initHistograms(Int_t nBins){
	TH1::SetDefaultSumw2();

	totalExp_LL_ = new TH1D("totalExp_LL","totalExp_LL", nBins, 0.5, nBins+0.5);
	totalExp_woIsoTrack_LL_ = new TH1D("totalExp_woIsoTrack_LL","totalExp_woIsoTrack_LL", nBins, 0.5, nBins+0.5);
  	nEvtsExp_LL_ = new TH1D("nEvtsExp_LL","nEvtsExp_LL", nBins, 0.5, nBins+0.5);

 	totalPred_LL_ = new TH1D("totalPred_LL","totalPred_LL", nBins, 0.5, nBins+0.5);
 	totalPred_LL_Mu_ = new TH1D("totalPred_LL_Mu","totalPred_LL_Mu", nBins, 0.5, nBins+0.5);
 	totalPred_LL_Elec_ = new TH1D("totalPred_LL_Elec","totalPred_LL_Elec", nBins, 0.5, nBins+0.5);
 	totalPredControlStat_LL_ = new TH1D("totalPredControlStat_LL","totalPredControlStat_LL", nBins, 0.5, nBins+0.5);
 	totalCS_LL_ = new TH1D("totalCS_LL","totalCS_LL", nBins, 0.5, nBins+0.5);
	nEvtsCS_LL_ = new TH1D("nEvtsCS_LL","nEvtsCS_LL", nBins, 0.5, nBins+0.5);
	avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", nBins, 0.5, nBins+0.5);

	totalPred_LL_MC_ = new TH1D("totalPred_LL_MC","totalPred_LL_MC", nBins, 0.5, nBins+0.5);
	totalPred_LL_Mu_MC_ = new TH1D("totalPred_LL_Mu_MC","totalPred_LL_Mu_MC", nBins, 0.5, nBins+0.5);
	totalPred_LL_Elec_MC_ = new TH1D("totalPred_LL_Elec_MC","totalPred_LL_Elec_MC", nBins, 0.5, nBins+0.5);
	totalPredControlStat_LL_MC_ = new TH1D("totalPredControlStat_LL_MC","totalPredControlStat_LL_MC", nBins, 0.5, nBins+0.5);
	totalPred_woIsoTrack_LL_MC_ = new TH1D("totalPred_woIsoTrack_LL_MC","totalPred_woIsoTrack_LL_MC", nBins, 0.5, nBins+0.5);
 	totalCS_LL_MC_ = new TH1D("totalCS_LL_MC","totalCS_LL_MC", nBins, 0.5, nBins+0.5);
	nEvtsCS_LL_MC_ = new TH1D("nEvtsCS_LL_MC","nEvtsCS_LL_MC", nBins, 0.5, nBins+0.5);
	avgWeight_LL_MC_ = new TProfile("avgWeight_LL_MC","avgWeight_LL_MC", nBins, 0.5, nBins+0.5);

 	totalPredIsoTrackSysUp_LL_ = new TH1D("totalPredIsoTrackSysUp_LL","totalPredIsoTrackSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackSysDown_LL_ = new TH1D("totalPredIsoTrackSysDown_LL","totalPredIsoTrackSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccSysUp_LL_ = new TH1D("totalPredIsoTrackMuAccSysUp_LL","totalPredIsoTrackMuAccSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccSysDown_LL_ = new TH1D("totalPredIsoTrackMuAccSysDown_LL","totalPredIsoTrackMuAccSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDSysUp_LL_ = new TH1D("totalPredIsoTrackMuIDSysUp_LL","totalPredIsoTrackMuIDSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDSysDown_LL_ = new TH1D("totalPredIsoTrackMuIDSysDown_LL","totalPredIsoTrackMuIDSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoSysUp_LL_ = new TH1D("totalPredIsoTrackMuIsoSysUp_LL","totalPredIsoTrackMuIsoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoSysDown_LL_ = new TH1D("totalPredIsoTrackMuIsoSysDown_LL","totalPredIsoTrackMuIsoSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccSysUp_LL_ = new TH1D("totalPredIsoTrackElecAccSysUp_LL","totalPredIsoTrackElecAccSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccSysDown_LL_ = new TH1D("totalPredIsoTrackElecAccSysDown_LL","totalPredIsoTrackElecAccSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDSysUp_LL_ = new TH1D("totalPredIsoTrackElecIDSysUp_LL","totalPredIsoTrackElecIDSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDSysDown_LL_ = new TH1D("totalPredIsoTrackElecIDSysDown_LL","totalPredIsoTrackElecIDSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoSysUp_LL_ = new TH1D("totalPredIsoTrackElecIsoSysUp_LL","totalPredIsoTrackElecIsoSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoSysDown_LL_ = new TH1D("totalPredIsoTrackElecIsoSysDown_LL","totalPredIsoTrackElecIsoSysDown_LL", nBins, 0.5, nBins+0.5);	
	totalPredMTWSysUp_LL_ = new TH1D("totalPredMTWSysUp_LL","totalPredMTWSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWSysDown_LL_ = new TH1D("totalPredMTWSysDown_LL","totalPredMTWSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPuritySysUp_LL_ = new TH1D("totalPredPuritySysUp_LL","totalPredPuritySysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPuritySysDown_LL_ = new TH1D("totalPredPuritySysDown_LL","totalPredPuritySysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysUp_LL_ = new TH1D("totalPredSingleLepPuritySysUp_LL","totalPredSingleLepPuritySysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysDown_LL_ = new TH1D("totalPredSingleLepPuritySysDown_LL","totalPredSingleLepPuritySysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRSysUp_LL_ = new TH1D("totalPredDiLepSRSysUp_LL","totalPredDiLepSRSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRSysDown_LL_ = new TH1D("totalPredDiLepSRSysDown_LL","totalPredDiLepSRSysDown_LL", nBins, 0.5, nBins+0.5);
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
	totalPredIsoTrackMuAccStatUp_LL_ = new TH1D("totalPredIsoTrackMuAccStatUp_LL","totalPredIsoTrackMuAccStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccStatDown_LL_ = new TH1D("totalPredIsoTrackMuAccStatDown_LL","totalPredIsoTrackMuAccStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDStatUp_LL_ = new TH1D("totalPredIsoTrackMuIDStatUp_LL","totalPredIsoTrackMuIDStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDStatDown_LL_ = new TH1D("totalPredIsoTrackMuIDStatDown_LL","totalPredIsoTrackMuIDStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoStatUp_LL_ = new TH1D("totalPredIsoTrackMuIsoStatUp_LL","totalPredIsoTrackMuIsoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoStatDown_LL_ = new TH1D("totalPredIsoTrackMuIsoStatDown_LL","totalPredIsoTrackMuIsoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccStatUp_LL_ = new TH1D("totalPredIsoTrackElecAccStatUp_LL","totalPredIsoTrackElecAccStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccStatDown_LL_ = new TH1D("totalPredIsoTrackElecAccStatDown_LL","totalPredIsoTrackElecAccStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDStatUp_LL_ = new TH1D("totalPredIsoTrackElecIDStatUp_LL","totalPredIsoTrackElecIDStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDStatDown_LL_ = new TH1D("totalPredIsoTrackElecIDStatDown_LL","totalPredIsoTrackElecIDStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoStatUp_LL_ = new TH1D("totalPredIsoTrackElecIsoStatUp_LL","totalPredIsoTrackElecIsoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoStatDown_LL_ = new TH1D("totalPredIsoTrackElecIsoStatDown_LL","totalPredIsoTrackElecIsoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWStatUp_LL_ = new TH1D("totalPredMTWStatUp_LL","totalPredMTWStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredMTWStatDown_LL_ = new TH1D("totalPredMTWStatDown_LL","totalPredMTWStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredPurityStatUp_LL_ = new TH1D("totalPredPurityStatUp_LL","totalPredPurityStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredPurityStatDown_LL_ = new TH1D("totalPredPurityStatDown_LL","totalPredPurityStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatUp_LL_ = new TH1D("totalPredSingleLepPurityStatUp_LL","totalPredSingleLepPurityStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatDown_LL_ = new TH1D("totalPredSingleLepPurityStatDown_LL","totalPredSingleLepPurityStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRStatUp_LL_ = new TH1D("totalPredDiLepSRStatUp_LL","totalPredDiLepSRStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRStatDown_LL_ = new TH1D("totalPredDiLepSRStatDown_LL","totalPredDiLepSRStatDown_LL", nBins, 0.5, nBins+0.5);
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

	totalPredDiLepContributionStatUp_LL_ = new TH1D("totalPredDiLepContributionStatUp_LL", "totalPredDiLepContributionStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionStatDown_LL_ = new TH1D("totalPredDiLepContributionStatDown_LL", "totalPredDiLepContributionStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionSysUp_LL_ = new TH1D("totalPredDiLepContributionSysUp_LL", "totalPredDiLepContributionSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionSysDown_LL_ = new TH1D("totalPredDiLepContributionSysDown_LL", "totalPredDiLepContributionSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredLepRecoIsoStatUp_LL_ = new TH1D("totalPredLepRecoIsoStatUp_LL", "totalPredLepRecoIsoStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredLepRecoIsoStatDown_LL_ = new TH1D("totalPredLepRecoIsoStatDown_LL", "totalPredLepRecoIsoStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccStatUp_LL_ = new TH1D("totalPredLepAccStatUp_LL", "totalPredLepAccStatUp_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccStatDown_LL_ = new TH1D("totalPredLepAccStatDown_LL", "totalPredLepAccStatDown_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccSysUp_LL_ = new TH1D("totalPredLepAccSysUp_LL", "totalPredLepAccSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccSysDown_LL_ = new TH1D("totalPredLepAccSysDown_LL", "totalPredLepAccSysDown_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccQsquareSysUp_LL_ = new TH1D("totalPredLepAccQsquareSysUp_LL", "totalPredLepAccQsquareSysUp_LL", nBins, 0.5, nBins+0.5);
	totalPredLepAccQsquareSysDown_LL_ = new TH1D("totalPredLepAccQsquareSysDown_LL", "totalPredLepAccQsquareSysDown_LL", nBins, 0.5, nBins+0.5);

	totalPredIsoTrackSysUp_LL_MC_ = new TH1D("totalPredIsoTrackSysUp_LL_MC","totalPredIsoTrackSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackSysDown_LL_MC_ = new TH1D("totalPredIsoTrackSysDown_LL_MC","totalPredIsoTrackSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccSysUp_LL_MC_ = new TH1D("totalPredIsoTrackMuAccSysUp_LL_MC","totalPredIsoTrackMuAccSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccSysDown_LL_MC_ = new TH1D("totalPredIsoTrackMuAccSysDown_LL_MC","totalPredIsoTrackMuAccSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDSysUp_LL_MC_ = new TH1D("totalPredIsoTrackMuIDSysUp_LL_MC","totalPredIsoTrackMuIDSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDSysDown_LL_MC_ = new TH1D("totalPredIsoTrackMuIDSysDown_LL_MC","totalPredIsoTrackMuIDSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoSysUp_LL_MC_ = new TH1D("totalPredIsoTrackMuIsoSysUp_LL_MC","totalPredIsoTrackMuIsoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoSysDown_LL_MC_ = new TH1D("totalPredIsoTrackMuIsoSysDown_LL_MC","totalPredIsoTrackMuIsoSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccSysUp_LL_MC_ = new TH1D("totalPredIsoTrackElecAccSysUp_LL_MC","totalPredIsoTrackElecAccSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccSysDown_LL_MC_ = new TH1D("totalPredIsoTrackElecAccSysDown_LL_MC","totalPredIsoTrackElecAccSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDSysUp_LL_MC_ = new TH1D("totalPredIsoTrackElecIDSysUp_LL_MC","totalPredIsoTrackElecIDSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDSysDown_LL_MC_ = new TH1D("totalPredIsoTrackElecIDSysDown_LL_MC","totalPredIsoTrackElecIDSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoSysUp_LL_MC_ = new TH1D("totalPredIsoTrackElecIsoSysUp_LL_MC","totalPredIsoTrackElecIsoSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoSysDown_LL_MC_ = new TH1D("totalPredIsoTrackElecIsoSysDown_LL_MC","totalPredIsoTrackElecIsoSysDown_LL_MC", nBins, 0.5, nBins+0.5);	
	totalPredMTWSysUp_LL_MC_ = new TH1D("totalPredMTWSysUp_LL_MC","totalPredMTWSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWSysDown_LL_MC_ = new TH1D("totalPredMTWSysDown_LL_MC","totalPredMTWSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPuritySysUp_LL_MC_ = new TH1D("totalPredPuritySysUp_LL_MC","totalPredPuritySysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPuritySysDown_LL_MC_ = new TH1D("totalPredPuritySysDown_LL_MC","totalPredPuritySysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysUp_LL_MC_ = new TH1D("totalPredSingleLepPuritySysUp_LL_MC","totalPredSingleLepPuritySysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPuritySysDown_LL_MC_ = new TH1D("totalPredSingleLepPuritySysDown_LL_MC","totalPredSingleLepPuritySysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRSysUp_LL_MC_ = new TH1D("totalPredDiLepSRSysUp_LL_MC","totalPredDiLepSRSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRSysDown_LL_MC_ = new TH1D("totalPredDiLepSRSysDown_LL_MC","totalPredDiLepSRSysDown_LL_MC", nBins, 0.5, nBins+0.5);
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
	totalPredIsoTrackMuAccStatUp_LL_MC_ = new TH1D("totalPredIsoTrackMuAccStatUp_LL_MC","totalPredIsoTrackMuAccStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuAccStatDown_LL_MC_ = new TH1D("totalPredIsoTrackMuAccStatDown_LL_MC","totalPredIsoTrackMuAccStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDStatUp_LL_MC_ = new TH1D("totalPredIsoTrackMuIDStatUp_LL_MC","totalPredIsoTrackMuIDStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIDStatDown_LL_MC_ = new TH1D("totalPredIsoTrackMuIDStatDown_LL_MC","totalPredIsoTrackMuIDStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoStatUp_LL_MC_ = new TH1D("totalPredIsoTrackMuIsoStatUp_LL_MC","totalPredIsoTrackMuIsoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackMuIsoStatDown_LL_MC_ = new TH1D("totalPredIsoTrackMuIsoStatDown_LL_MC","totalPredIsoTrackMuIsoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccStatUp_LL_MC_ = new TH1D("totalPredIsoTrackElecAccStatUp_LL_MC","totalPredIsoTrackElecAccStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecAccStatDown_LL_MC_ = new TH1D("totalPredIsoTrackElecAccStatDown_LL_MC","totalPredIsoTrackElecAccStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDStatUp_LL_MC_ = new TH1D("totalPredIsoTrackElecIDStatUp_LL_MC","totalPredIsoTrackElecIDStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIDStatDown_LL_MC_ = new TH1D("totalPredIsoTrackElecIDStatDown_LL_MC","totalPredIsoTrackElecIDStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoStatUp_LL_MC_ = new TH1D("totalPredIsoTrackElecIsoStatUp_LL_MC","totalPredIsoTrackElecIsoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredIsoTrackElecIsoStatDown_LL_MC_ = new TH1D("totalPredIsoTrackElecIsoStatDown_LL_MC","totalPredIsoTrackElecIsoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWStatUp_LL_MC_ = new TH1D("totalPredMTWStatUp_LL_MC","totalPredMTWStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredMTWStatDown_LL_MC_ = new TH1D("totalPredMTWStatDown_LL_MC","totalPredMTWStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPurityStatUp_LL_MC_ = new TH1D("totalPredPurityStatUp_LL_MC","totalPredPurityStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredPurityStatDown_LL_MC_ = new TH1D("totalPredPurityStatDown_LL_MC","totalPredPurityStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatUp_LL_MC_ = new TH1D("totalPredSingleLepPurityStatUp_LL_MC","totalPredSingleLepPurityStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredSingleLepPurityStatDown_LL_MC_ = new TH1D("totalPredSingleLepPurityStatDown_LL_MC","totalPredSingleLepPurityStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRStatUp_LL_MC_ = new TH1D("totalPredDiLepSRStatUp_LL_MC","totalPredDiLepSRStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepSRStatDown_LL_MC_ = new TH1D("totalPredDiLepSRStatDown_LL_MC","totalPredDiLepSRStatDown_LL_MC", nBins, 0.5, nBins+0.5);
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

	totalPredDiLepContributionStatUp_LL_MC_ = new TH1D("totalPredDiLepContributionStatUp_LL_MC", "totalPredDiLepContributionStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionStatDown_LL_MC_ = new TH1D("totalPredDiLepContributionStatDown_LL_MC", "totalPredDiLepContributionStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionSysUp_LL_MC_ = new TH1D("totalPredDiLepContributionSysUp_LL_MC", "totalPredDiLepContributionSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredDiLepContributionSysDown_LL_MC_ = new TH1D("totalPredDiLepContributionSysDown_LL_MC", "totalPredDiLepContributionSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepRecoIsoStatUp_LL_MC_ = new TH1D("totalPredLepRecoIsoStatUp_LL_MC", "totalPredLepRecoIsoStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepRecoIsoStatDown_LL_MC_ = new TH1D("totalPredLepRecoIsoStatDown_LL_MC", "totalPredLepRecoIsoStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccStatUp_LL_MC_ = new TH1D("totalPredLepAccStatUp_LL_MC", "totalPredLepAccStatUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccStatDown_LL_MC_ = new TH1D("totalPredLepAccStatDown_LL_MC", "totalPredLepAccStatDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccSysUp_LL_MC_ = new TH1D("totalPredLepAccSysUp_LL_MC", "totalPredLepAccSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccSysDown_LL_MC_ = new TH1D("totalPredLepAccSysDown_LL_MC", "totalPredLepAccSysDown_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccQsquareSysUp_LL_MC_ = new TH1D("totalPredLepAccQsquareSysUp_LL_MC", "totalPredLepAccQsquareSysUp_LL_MC", nBins, 0.5, nBins+0.5);
	totalPredLepAccQsquareSysDown_LL_MC_ = new TH1D("totalPredLepAccQsquareSysDown_LL_MC", "totalPredLepAccQsquareSysDown_LL_MC", nBins, 0.5, nBins+0.5);

	totalCS_LL_Mu_ = new TH1D("totalCS_LL_Mu","totalCS_LL_Mu", nBins, 0.5, nBins+0.5);
	totalCS_LL_Elec_ = new TH1D("totalCS_LL_Elec","totalCS_LL_Elec", nBins, 0.5, nBins+0.5);
	totalCS_LL_Mu_MC_ = new TH1D("totalCS_LL_Mu_MC","totalCS_LL_Mu_MC", nBins, 0.5, nBins+0.5);
	totalCS_LL_Elec_MC_ = new TH1D("totalCS_LL_Elec_MC","totalCS_LL_Elec_MC", nBins, 0.5, nBins+0.5);

	totalCS_LL_HT_Mu_ = new TH1D("totalCS_LL_HT_Mu","totalCS_LL_HT_Mu", 22, 250, 3000);
	totalCS_LL_HT_Elec_ = new TH1D("totalCS_LL_HT_Elec","totalCS_LL_HT_Elec", 22, 250, 3000);
	totalCS_LL_HT_Mu_MC_ = new TH1D("totalCS_LL_HT_Mu_MC","totalCS_LL_HT_Mu_MC", 22, 250, 3000);
	totalCS_LL_HT_Elec_MC_ = new TH1D("totalCS_LL_HT_Elec_MC","totalCS_LL_HT_Elec_MC", 22, 250, 3000);

	totalCS_LL_MHT_Mu_ = new TH1D("totalCS_LL_MHT_Mu","totalCS_LL_MHT_Mu", 20, 250, 1500);
	totalCS_LL_MHT_Elec_ = new TH1D("totalCS_LL_MHT_Elec","totalCS_LL_MHT_Elec", 20, 250, 1500);
	totalCS_LL_MHT_Mu_MC_ = new TH1D("totalCS_LL_MHT_Mu_MC","totalCS_LL_MHT_Mu_MC", 20, 250, 1500);
	totalCS_LL_MHT_Elec_MC_ = new TH1D("totalCS_LL_MHT_Elec_MC","totalCS_LL_MHT_Elec_MC", 20, 250, 1500);

	totalCS_LL_MET_Mu_ = new TH1D("totalCS_LL_MET_Mu","totalCS_LL_MET_Mu", 22, 125, 1500);
	totalCS_LL_MET_Elec_ = new TH1D("totalCS_LL_MET_Elec","totalCS_LL_MET_Elec", 22, 125, 1500);
	totalCS_LL_MET_Mu_MC_ = new TH1D("totalCS_LL_MET_Mu_MC","totalCS_LL_MET_Mu_MC", 22, 125, 1500);
	totalCS_LL_MET_Elec_MC_ = new TH1D("totalCS_LL_MET_Elec_MC","totalCS_LL_MET_Elec_MC", 22, 125, 1500);

	totalCS_LL_NJets_Mu_ = new TH1D("totalCS_LL_NJets_Mu","totalCS_LL_NJets_Mu", 9, 1.5, 10.5);
	totalCS_LL_NJets_Elec_ = new TH1D("totalCS_LL_NJets_Elec","totalCS_LL_NJets_Elec", 9, 1.5, 10.5);
	totalCS_LL_NJets_Mu_MC_ = new TH1D("totalCS_LL_NJets_Mu_MC","totalCS_LL_NJets_Mu_MC", 9, 1.5, 10.5);
	totalCS_LL_NJets_Elec_MC_ = new TH1D("totalCS_LL_NJets_Elec_MC","totalCS_LL_NJets_Elec_MC", 9, 1.5, 10.5);

	totalCS_LL_NBTags_Mu_ = new TH1D("totalCS_LL_NBTags_Mu","totalCS_LL_NBTags_Mu", 4, -0.5, 3.5);
	totalCS_LL_NBTags_Elec_ = new TH1D("totalCS_LL_NBTags_Elec","totalCS_LL_NBTags_Elec", 4, -0.5, 3.5);
	totalCS_LL_NBTags_Mu_MC_ = new TH1D("totalCS_LL_NBTags_Mu_MC","totalCS_LL_NBTags_Mu_MC", 4, -0.5, 3.5);
	totalCS_LL_NBTags_Elec_MC_ = new TH1D("totalCS_LL_NBTags_Elec_MC","totalCS_LL_NBTags_Elec_MC", 4, -0.5, 3.5);

	totalCS_LL_LepPt_Mu_ = new TH1D("totalCS_LL_LepPt_Mu","totalCS_LL_LepPt_Mu", 25, 0, 500);
	totalCS_LL_LepPt_Elec_ = new TH1D("totalCS_LL_LepPt_Elec","totalCS_LL_LepPt_Elec", 25, 0, 500);
	totalCS_LL_LepPt_Mu_MC_ = new TH1D("totalCS_LL_LepPt_Mu_MC","totalCS_LL_LepPt_Mu_MC", 25, 0, 500);
	totalCS_LL_LepPt_Elec_MC_ = new TH1D("totalCS_LL_LepPt_Elec_MC","totalCS_LL_LepPt_Elec_MC", 25, 0, 500);

	totalFractionMu_HT_ = new THStack("totalFractionMu_HT", "totalFractionMu_HT");
	totalFractionElec_HT_ = new THStack("totalFractionElec_HT", "totalFractionElec_HT");
	totalFractionMu_MHT_ = new THStack("totalFractionMu_MHT", "totalFractionMu_MHT");
	totalFractionElec_MHT_ = new THStack("totalFractionElec_MHT", "totalFractionElec_MHT");
	totalFractionMu_NJets_ = new THStack("totalFractionMu_NJets", "totalFractionMu_NJets");
	totalFractionElec_NJets_ = new THStack("totalFractionElec_NJets", "totalFractionElec_NJets");
	totalFractionMu_NBTags_ = new THStack("totalFractionMu_NBTags", "totalFractionMu_NBTags");
	totalFractionElec_NBTags_ = new THStack("totalFractionElec_NBTags", "totalFractionElec_NBTags");
	totalFractionMu_ = new THStack("totalFractionMu", "totalFractionMu");
	totalFractionElec_ = new THStack("totalFractionElec", "totalFractionElec");

	totalFractionNormMu_ = new TH1D("totalFractionNormMu","totalFractionNormMu", nBins, 0.5, nBins+0.5);
	totalFractionNormElec_ = new TH1D("totalFractionNormElec","totalFractionNormElec", nBins, 0.5, nBins+0.5);
	totalFractionNormMu_HT_ = new TH1D("totalFractionNorm_HT_Mu","totalFractionNorm_HT_Mu", 16, 250, 2250);
	totalFractionNormElec_HT_ = new TH1D("totalFractionNorm_HT_Elec","totalFractionNorm_HT_Elec", 16, 250, 2250);
	totalFractionNormMu_MHT_ = new TH1D("totalFractionNorm_MHT_Mu","totalFractionNorm_MHT_Mu", 12, 250, 1000);
	totalFractionNormElec_MHT_ = new TH1D("totalFractionNorm_MHT_Elec","totalFractionNorm_MHT_Elec", 12, 250, 1000);
	totalFractionNormMu_NJets_ = new TH1D("totalFractionNorm_NJets_Mu","totalFractionNorm_NJets_Mu", 9, 1.5, 10.5);
	totalFractionNormElec_NJets_ = new TH1D("totalFractionNorm_NJets_Elec","totalFractionNorm_NJets_Elec", 9, 1.5, 10.5);
	totalFractionNormMu_NBTags_ = new TH1D("totalFractionNorm_NBTags_Mu","totalFractionNorm_NBTags_Mu", 4, -0.5, 3.5);
	totalFractionNormElec_NBTags_ = new TH1D("totalFractionNorm_NBTags_Elec","totalFractionNorm_NBTags_Elec", 4, -0.5, 3.5);

	totalAccMu_ = new TH1D("totalAccMu","totalAccMu", nBins, 0.5, nBins+0.5);
	totalAccElec_ = new TH1D("totalAccElec","totalAccElec", nBins, 0.5, nBins+0.5);
	totalAccMu_HT_ = new TH1D("totalAcc_HT_Mu","totalAcc_HT_Mu", 16, 250, 2250);
	totalAccElec_HT_ = new TH1D("totalAcc_HT_Elec","totalAcc_HT_Elec", 16, 250, 2250);
	totalAccMu_MHT_ = new TH1D("totalAcc_MHT_Mu","totalAcc_MHT_Mu", 12, 250, 1000);
	totalAccElec_MHT_ = new TH1D("totalAcc_MHT_Elec","totalAcc_MHT_Elec", 12, 250, 1000);
	totalAccMu_NJets_ = new TH1D("totalAcc_NJets_Mu","totalAcc_NJets_Mu", 9, 1.5, 10.5);
	totalAccElec_NJets_ = new TH1D("totalAcc_NJets_Elec","totalAcc_NJets_Elec", 9, 1.5, 10.5);
	totalAccMu_NBTags_ = new TH1D("totalAcc_NBTags_Mu","totalAcc_NBTags_Mu", 4, -0.5, 3.5);
	totalAccElec_NBTags_ = new TH1D("totalAcc_NBTags_Elec","totalAcc_NBTags_Elec", 4, -0.5, 3.5);

	totalRecoMu_ = new TH1D("totalRecoMu","totalRecoMu", nBins, 0.5, nBins+0.5);
	totalRecoElec_ = new TH1D("totalRecoElec","totalRecoElec", nBins, 0.5, nBins+0.5);
	totalRecoMu_HT_ = new TH1D("totalReco_HT_Mu","totalReco_HT_Mu", 16, 250, 2250);
	totalRecoElec_HT_ = new TH1D("totalReco_HT_Elec","totalReco_HT_Elec", 16, 250, 2250);
	totalRecoMu_MHT_ = new TH1D("totalReco_MHT_Mu","totalReco_MHT_Mu", 12, 250, 1000);
	totalRecoElec_MHT_ = new TH1D("totalReco_MHT_Elec","totalReco_MHT_Elec", 12, 250, 1000);
	totalRecoMu_NJets_ = new TH1D("totalReco_NJets_Mu","totalReco_NJets_Mu", 9, 1.5, 10.5);
	totalRecoElec_NJets_ = new TH1D("totalReco_NJets_Elec","totalReco_NJets_Elec", 9, 1.5, 10.5);
	totalRecoMu_NBTags_ = new TH1D("totalReco_NBTags_Mu","totalReco_NBTags_Mu", 4, -0.5, 3.5);
	totalRecoElec_NBTags_ = new TH1D("totalReco_NBTags_Elec","totalReco_NBTags_Elec", 4, -0.5, 3.5);

	totalIsoMu_ = new TH1D("totalIsoMu","totalIsoMu", nBins, 0.5, nBins+0.5);
	totalIsoElec_ = new TH1D("totalIsoElec","totalIsoElec", nBins, 0.5, nBins+0.5);
	totalIsoMu_HT_ = new TH1D("totalIso_HT_Mu","totalIso_HT_Mu", 16, 250, 2250);
	totalIsoElec_HT_ = new TH1D("totalIso_HT_Elec","totalIso_HT_Elec", 16, 250, 2250);
	totalIsoMu_MHT_ = new TH1D("totalIso_MHT_Mu","totalIso_MHT_Mu", 12, 250, 1000);
	totalIsoElec_MHT_ = new TH1D("totalIso_MHT_Elec","totalIso_MHT_Elec", 12, 250, 1000);
	totalIsoMu_NJets_ = new TH1D("totalIso_NJets_Mu","totalIso_NJets_Mu", 9, 1.5, 10.5);
	totalIsoElec_NJets_ = new TH1D("totalIso_NJets_Elec","totalIso_NJets_Elec", 9, 1.5, 10.5);
	totalIsoMu_NBTags_ = new TH1D("totalIso_NBTags_Mu","totalIso_NBTags_Mu", 4, -0.5, 3.5);
	totalIsoElec_NBTags_ = new TH1D("totalIso_NBTags_Elec","totalIso_NBTags_Elec", 4, -0.5, 3.5);

	totalCSCombined_LL_ = new TH1D("totalCSCombined_LL","totalCSCombined_LL", nBins, 0.5, nBins+0.5);
	totalCSCombined_LL_MC_ = new TH1D("totalCSCombined_LL_MC","totalCSCombined_LL_MC", nBins, 0.5, nBins+0.5);
	totalCSCombined_LL_HT_ = new TH1D("totalCSCombined_LL_HT","totalCSCombined_LL_HT", 11, 250, 3000);
	totalCSCombined_LL_HT_MC_ = new TH1D("totalCSCombined_LL_HT_MC","totalCSCombined_LL_HT_MC", 11, 250, 3000);
	totalCSCombined_LL_MHT_ = new TH1D("totalCSCombined_LL_MHT","totalCSCombined_LL_MHT", 10, 250, 1500);
	totalCSCombined_LL_MHT_MC_ = new TH1D("totalCSCombined_LL_MHT_MC","totalCSCombined_LL_MHT_MC", 10, 250, 1500);
	totalCSCombined_LL_MET_ = new TH1D("totalCSCombined_LL_MET","totalCSCombined_LL_MET", 11, 125, 1500);
	totalCSCombined_LL_MET_MC_ = new TH1D("totalCSCombined_LL_MET_MC","totalCSCombined_LL_MET_MC", 11, 125, 1500);
	totalCSCombined_LL_NJets_ = new TH1D("totalCSCombined_LL_NJets","totalCSCombined_LL_NJets", 11, 1.5, 12.5);
	totalCSCombined_LL_NJets_MC_ = new TH1D("totalCSCombined_LL_NJets_MC","totalCSCombined_LL_NJets_MC", 11, 1.5, 12.5);
	totalCSCombined_LL_NBTags_ = new TH1D("totalCSCombined_LL_NBTags","totalCSCombined_LL_NBTags", 4, -0.5, 3.5);
	totalCSCombined_LL_NBTags_MC_ = new TH1D("totalCSCombined_LL_NBTags_MC","totalCSCombined_LL_NBTags_MC", 4, -0.5, 3.5);

	totalExpCombined_LL_ = new TH1D("totalExpCombined_LL","totalExpCombined_LL", nBins, 0.5, nBins+0.5);
	totalExpCombined_LL_MC_ = new TH1D("totalExpCombined_LL_MC","totalExpCombined_LL_MC", nBins, 0.5, nBins+0.5);
	totalExpCombined_LL_HT_ = new TH1D("totalExpCombined_LL_HT","totalExpCombined_LL_HT", 11, 250, 3000);
	totalExpCombined_LL_HT_MC_ = new TH1D("totalExpCombined_LL_HT_MC","totalExpCombined_LL_HT_MC", 11, 250, 3000);
	totalExpCombined_LL_MHT_ = new TH1D("totalExpCombined_LL_MHT","totalExpCombined_LL_MHT", 10, 250, 1500);
	totalExpCombined_LL_MHT_MC_ = new TH1D("totalExpCombined_LL_MHT_MC","totalExpCombined_LL_MHT_MC", 10, 250, 1500);
	totalExpCombined_LL_MET_ = new TH1D("totalExpCombined_LL_MET","totalExpCombined_LL_MET", 11, 125, 1500);
	totalExpCombined_LL_MET_MC_ = new TH1D("totalExpCombined_LL_MET_MC","totalExpCombined_LL_MET_MC", 11, 125, 1500);
	totalExpCombined_LL_NJets_ = new TH1D("totalExpCombined_LL_NJets","totalExpCombined_LL_NJets", 11, 1.5, 12.5);
	totalExpCombined_LL_NJets_MC_ = new TH1D("totalExpCombined_LL_NJets_MC","totalExpCombined_LL_NJets_MC", 11, 1.5, 12.5);
	totalExpCombined_LL_NBTags_ = new TH1D("totalExpCombined_LL_NBTags","totalExpCombined_LL_NBTags", 4, -0.5, 3.5);
	totalExpCombined_LL_NBTags_MC_ = new TH1D("totalExpCombined_LL_NBTags_MC","totalExpCombined_LL_NBTags_MC", 4, -0.5, 3.5);

	totalPreCombined_LL_ = new TH1D("totalPreCombined_LL","totalPreCombined_LL", nBins, 0.5, nBins+0.5);
	totalPreCombined_LL_MC_ = new TH1D("totalPreCombined_LL_MC","totalPreCombined_LL_MC", nBins, 0.5, nBins+0.5);
	totalPreCombined_LL_HT_ = new TH1D("totalPreCombined_LL_HT","totalPreCombined_LL_HT", 11, 250, 3000);
	totalPreCombined_LL_HT_MC_ = new TH1D("totalPreCombined_LL_HT_MC","totalPreCombined_LL_HT_MC", 11, 250, 3000);
	totalPreCombined_LL_MHT_ = new TH1D("totalPreCombined_LL_MHT","totalPreCombined_LL_MHT", 10, 250, 1500);
	totalPreCombined_LL_MHT_MC_ = new TH1D("totalPreCombined_LL_MHT_MC","totalPreCombined_LL_MHT_MC", 10, 250, 1500);
	totalPreCombined_LL_MET_ = new TH1D("totalPreCombined_LL_MET","totalPreCombined_LL_MET", 11, 125, 1500);
	totalPreCombined_LL_MET_MC_ = new TH1D("totalPreCombined_LL_MET_MC","totalPreCombined_LL_MET_MC", 11, 125, 1500);
	totalPreCombined_LL_NJets_ = new TH1D("totalPreCombined_LL_NJets","totalPreCombined_LL_NJets", 11, 1.5, 12.5);
	totalPreCombined_LL_NJets_MC_ = new TH1D("totalPreCombined_LL_NJets_MC","totalPreCombined_LL_NJets_MC", 11, 1.5, 12.5);
	totalPreCombined_LL_NBTags_ = new TH1D("totalPreCombined_LL_NBTags","totalPreCombined_LL_NBTags", 4, -0.5, 3.5);
	totalPreCombined_LL_NBTags_MC_ = new TH1D("totalPreCombined_LL_NBTags_MC","totalPreCombined_LL_NBTags_MC", 4, -0.5, 3.5);
}