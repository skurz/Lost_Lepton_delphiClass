#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <vector>
#include "LLTools.h"
#include "THEff.h"

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder) // prediction durch expectation
{
  TH1D* Closure = (TH1D*) prediction->Clone();
  Closure->Divide(prediction,expectation,1,1,"B");
  TString title = prediction->GetTitle();
  title +="_closure";
  // 	title = "#mu & e Control-Sample Ratio in Search Bins; Search bins; #mu / e CS";
  Closure->SetTitle(title);
  title = prediction->GetName();
  title+="_closure";
  Closure->SetName(title);
  Folder->cd();
  Closure->Write();
}

UShort_t getMergedBinQCD(UShort_t BinQCD, Int_t NJets){
  if(BinQCD > 900) return 900;
  if(NJets < 4) return 900;

  UShort_t bin = 0;

  switch(NJets){
    case 4:
      bin = BinQCD % 11;
      if(bin == 0) bin = 11;
      break;
    case 5:
      bin = BinQCD % 11 + 11;
      if(bin == 11) bin = 22;
      break;
    case 6:
      bin = BinQCD % 11 + 22;
      if(bin == 22) bin = 33;
      break;
    case 7:
    case 8:
      bin = BinQCD % 11 + 33;
      if(bin == 33) bin = 44;
      break;
    default:
      bin = BinQCD % 11 + 44;
      if(bin == 44) bin = 55;
      break;
  }

  return bin;
}

UShort_t getHTMHTBox(Double_t HT, Double_t MHT){
  if(MHT < 200 || HT < 500) return -1;
  if(MHT >= 750 && HT < 800) return -1;

  if(MHT < 500){
    if(HT < 800) return 1;
    if(HT < 1200) return 2;
    else return 3;
  }else if(MHT < 750){
    if(HT < 1200) return 4;
    else return 5;
  }else{
    return 6;
  }

  return -1; // Should not be reached
}

void SetBinLabel(TH1D* hist){
  if(hist->GetNbinsX()==72)
  for(int nji = 0; nji<3; ++nji){
    for(int nbi = 0; nbi<4; ++nbi){
        for(int hti = 0; hti<6; ++hti){
          int mhti =0;
          if(hti >=0 && hti <=2) mhti = 0;
          else if(hti >=3 && hti <=4) mhti = 1;
          else mhti = 2;
          char binlabel[100];
          int bi = nji * 24 + nbi * 6 + hti + 1;
          //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
          sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
          hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
        }
    }
  }

  if(hist->GetNbinsX()==220)
  for(int nji = 0; nji<5; ++nji){
    for(int nbi = 0; nbi<4; ++nbi){
        for(int mhti = 0; mhti<4; ++mhti){
          int htiMin = 0;
          if(mhti==3) htiMin = 1;
          for(int hti = htiMin; hti<3; ++hti){
            char binlabel[100];
            int bi = nji * 44 + nbi * 11 + mhti * 3 + hti + 1;
            if(htiMin==1) bi = nji * 44 + nbi * 11 + mhti * 3 + hti;
            //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
            sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
            hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
          }
        }
    }
  }
  
  hist -> GetXaxis() -> LabelsOption("v");
}

void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir){
  for(int i = 1; i<Bottom->GetNbinsX()+1; ++i){
      if(Bottom->GetBinContent(i)>0) Top->SetBinContent(i, 1.+Top->GetBinContent(i)/Bottom->GetBinContent(i));
      else Top->SetBinContent(i, -999);
      Top->SetBinError(i, 0);
  } 

  SetBinLabel(Top);

  dir->cd();
  Top->Write();
}

void ResultPlot()
{

  // General Settings
  TString InputPath_Expectation("Expectation_woExo.root");
  TString InputPath_Prediction("Prediction_woExo.root");
  TString InputPath_Prediction_Data("Prediction_data.root"); // Use same path as above if pure MC prediction wanted
  TString OutputPath_Closure("Closure.root");
  TString OutputPath_Prediction("LLPrediction.root");

  // If you want to compare MC to MC set this to true. E.g. prediction with and without signal contamination
  bool useMCForDataTree = false;

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 1280; //1280 //150

  // Do approximation of statistical uncertainties if full MC statistics are used (stat. unc. then refers to a given luminosity of data)
  // Leave at 'false' if doing a closure test so stat. uncertainty is the one using full MC statistics
  bool approxStatUncertainty = false;

  // Prepare Code for Extrapolation Method
  bool doExtrapolation = false; // not fully implemented yet

  // Present output in QCD binning
  bool doQCDbinning = false;
  //Merge QCDbins (bTags) = 55 bins // only works if doQCDbinning = true;
  //BUT: Output table does not work! However, histograms are filled properly
  bool mergeQCDbins = false; 

  // Histograms for Readiness Talk
  bool doMergedHistograms = true;



  // Begin of Code
  int nSearchBinsTotal = 72;
  if(doQCDbinning){
    nSearchBinsTotal = 220;
    if(mergeQCDbins) nSearchBinsTotal = 55;
  }
  UShort_t         SearchBin=0;


  //Declaration of leaves types for both trees (Expectation/Prediction)
  UShort_t         Bin;
  UShort_t         BinQCD;
  Double_t         Weight;
  Double_t         scaledWeight;
  Double_t         HT;
  Double_t         MHT;
  Int_t            NJets;
  Int_t            BTags;
  
  UShort_t        Expectation;
  UShort_t        muAcc;
  UShort_t        muReco;
  UShort_t        muIso;
  UShort_t        elecAcc;
  UShort_t        elecReco;
  UShort_t        elecIso;
  Int_t           isoTracks;
  UShort_t        ExpectationDiLep;
  UShort_t        ExpectationReductionIsoTrack;

  Float_t         MTW;
  UShort_t        selectedIDIsoMuonsNum;
  UShort_t        selectedIDIsoElectronsNum;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReduced;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;
  
  Float_t         muIsoWeight;
  Float_t         muRecoWeight;
  Float_t         muAccWeight;

  Float_t         elecAccWeight;
  Float_t         elecRecoWeight;
  Float_t         elecIsoWeight;

  Float_t         totalStatUp;
  Float_t         totalStatDown;
  Float_t         totalSysUp;
  Float_t         totalSysDown;
  Float_t         nonClosureUp;
  Float_t         nonClosureDown;
  Float_t         diBosonUp;
  Float_t         diBosonDown;
  Float_t         totalUncUp;
  Float_t         totalUncDown;

  // Uncertainties
  Float_t isoTrackStatUp;
  Float_t isoTrackStatDown;
  Float_t muIsoTrackStatUp;
  Float_t muIsoTrackStatDown;
  Float_t elecIsoTrackStatUp;
  Float_t elecIsoTrackStatDown;
  Float_t pionIsoTrackStatUp;
  Float_t pionIsoTrackStatDown;
  Float_t MTWStatUp;
  Float_t MTWStatDown;
  Float_t purityStatUp;
  Float_t purityStatDown;
  Float_t singleLepPurityStatUp;
  Float_t singleLepPurityStatDown;
  Float_t diLepFoundStatUp;
  Float_t diLepFoundStatDown;
  Float_t muIsoStatUp;
  Float_t muIsoStatDown;
  Float_t muRecoStatUp;
  Float_t muRecoStatDown;
  Float_t muAccStatUp;
  Float_t muAccStatDown;
  Float_t elecIsoStatUp;
  Float_t elecIsoStatDown;
  Float_t elecRecoStatUp;
  Float_t elecRecoStatDown;
  Float_t elecAccStatUp;
  Float_t elecAccStatDown;

  Float_t isoTrackSysUp;
  Float_t isoTrackSysDown;
  Float_t muIsoTrackSysUp;
  Float_t muIsoTrackSysDown;
  Float_t elecIsoTrackSysUp;
  Float_t elecIsoTrackSysDown;
  Float_t pionIsoTrackSysUp;
  Float_t pionIsoTrackSysDown;
  Float_t MTWSysUp;
  Float_t MTWSysDown;
  Float_t puritySysUp;
  Float_t puritySysDown;
  Float_t singleLepPuritySysUp;
  Float_t singleLepPuritySysDown;
  Float_t diLepFoundSysUp;
  Float_t diLepFoundSysDown;
  Float_t muIsoSysUp;
  Float_t muIsoSysDown;
  Float_t muRecoSysUp;
  Float_t muRecoSysDown;
  Float_t muAccSysUp;
  Float_t muAccSysDown;
  Float_t muAccQsquareSysUp;
  Float_t muAccQsquareSysDown;
  Float_t elecIsoSysUp;
  Float_t elecIsoSysDown;
  Float_t elecRecoSysUp;
  Float_t elecRecoSysDown;
  Float_t elecAccSysUp;
  Float_t elecAccSysDown;
  Float_t elecAccQsquareSysUp;
  Float_t elecAccQsquareSysDown;

  Float_t totalPropSysUp;
  Float_t totalPropSysDown;

  //closure test
  TFile *outPutFile = new TFile(OutputPath_Closure,"RECREATE"); 
  outPutFile->cd();

  double totalExp=0, totalPre=0;
  double totalExpError=0, totalPreError=0;
  double totalPreMu=0, totalPreMuError=0;
  double totalPreElec=0, totalPreElecError=0;
  double totalExpIsoTrack=0, totalExpIsoTrackError=0;

  double totalPreIsoTrack=0, totalPreIsoTrackError=0;
  double totalPreIsoTrackMu=0, totalPreIsoTrackMuError=0;
  double totalPreIsoTrackElec=0, totalPreIsoTrackElecError=0;
  
  double totalExpMuAcc=0, totalExpMuReco=0, totalExpMuIso=0;
  
  double totalPreMuAcc=0, totalPreMuReco=0, totalPreMuIso=0;
  double totalPreMuMuAcc=0, totalPreMuMuReco=0, totalPreMuMuIso=0;
  double totalPreMuElecAcc=0, totalPreMuElecReco=0, totalPreMuElecIso=0;
  
  
  double totalExpElecAcc=0, totalExpElecReco=0, totalExpElecIso=0;
  
  double totalPreElecAcc=0, totalPreElecReco=0, totalPreElecIso=0;
  double totalPreElecMuAcc=0, totalPreElecMuReco=0, totalPreElecMuIso=0;
  double totalPreElecElecAcc=0, totalPreElecElecReco=0, totalPreElecElecIso=0;
	
  TH1D* ControlSampleMu_ = new TH1D("ControlSampleMu", "ControlSampleMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* ControlSampleElec_ = new TH1D("ControlSampleElec", "ControlSampleElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectation_ = new TH1D("TotalLostLeptonExpecation", "TotalLostLeptonExpecation", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPrediction_ = new TH1D("TotalLostLeptonPrediction", "TotalLostLeptonPrediction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMu_ = new TH1D("TotalLostLeptonPredictionMu", "TotalLostLeptonPredictionMu", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElec_ = new TH1D("TotalLostLeptonPredictionElec", "TotalLostLeptonPredictionElec", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectationIsoTrackReduction_ = new TH1D("TotalLostLeptonExpecationIsoTrackReduction", "TotalLostLeptonExpecationIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionIsoTrackReduction", "TotalLostLeptonPredictionIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionMuIsoTrackReduction", "TotalLostLeptonPredictionMuIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecIsoTrackReduction_ = new TH1D("TotalLostLeptonPredictionElecIsoTrackReduction", "TotalLostLeptonPredictionElecIsoTrackReduction", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  // separted closure
  TH1D* totalExpectationMuAcc_ = new TH1D("TotalLostLeptonExpecationMuAcc", "TotalLostLeptonExpecationMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuAcc_ = new TH1D("TotalLostLeptonPredictionMuCSMuAcc", "TotalLostLeptonPredictionMuCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuAcc_ = new TH1D("TotalLostLeptonPredictionElecCSMuAcc", "TotalLostLeptonPredictionElecCSMuAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectationMuReco_ = new TH1D("TotalLostLeptonExpecationMuReco", "TotalLostLeptonExpecationMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuReco_ = new TH1D("TotalLostLeptonPredictionMuCSMuReco", "TotalLostLeptonPredictionMuCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuReco_ = new TH1D("TotalLostLeptonPredictionElecCSMuReco", "TotalLostLeptonPredictionElecCSMuReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectationMuIso_ = new TH1D("TotalLostLeptonExpecationMuIso", "TotalLostLeptonExpecationMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSMuIso_ = new TH1D("TotalLostLeptonPredictionMuCSMuIso", "TotalLostLeptonPredictionMuCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSMuIso_ = new TH1D("TotalLostLeptonPredictionElecCSMuIso", "TotalLostLeptonPredictionElecCSMuIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);	
	
  TH1D* totalExpectationElecAcc_ = new TH1D("TotalLostLeptonExpecationElecAcc", "TotalLostLeptonExpecationElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecAcc_ = new TH1D("TotalLostLeptonPredictionMuCSElecAcc", "TotalLostLeptonPredictionMuCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecAcc_ = new TH1D("TotalLostLeptonPredictionElecCSElecAcc", "TotalLostLeptonPredictionElecCSElecAcc", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectationElecReco_ = new TH1D("TotalLostLeptonExpecationElecReco", "TotalLostLeptonExpecationElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecReco_ = new TH1D("TotalLostLeptonPredictionMuCSElecReco", "TotalLostLeptonPredictionMuCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecReco_ = new TH1D("TotalLostLeptonPredictionElecCSElecReco", "TotalLostLeptonPredictionElecCSElecReco", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
	
  TH1D* totalExpectationElecIso_ = new TH1D("TotalLostLeptonExpecationElecIso", "TotalLostLeptonExpecationElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionMuCSElecIso_ = new TH1D("TotalLostLeptonPredictionMuCSElecIso", "TotalLostLeptonPredictionMuCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredictionElecCSElecIso_ = new TH1D("TotalLostLeptonPredictionElecCSElecIso", "TotalLostLeptonPredictionElecCSElecIso", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);


  // Define histrograms to do totalPrediction per SearchBin
  TH1D* totalExp_LL_ = new TH1D("totalExp_LL","totalExp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsExp_LL_ = new TH1D("nEvtsExp_LL","nEvtsExp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPred_LL_ = new TH1D("totalPred_LL","totalPred_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysUp_LL_ = new TH1D("totalPredIsoTrackSysUp_LL","totalPredIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysDown_LL_ = new TH1D("totalPredIsoTrackSysDown_LL","totalPredIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysUp_LL_ = new TH1D("totalPredMuIsoTrackSysUp_LL","totalPredMuIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysDown_LL_ = new TH1D("totalPredMuIsoTrackSysDown_LL","totalPredMuIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysUp_LL_ = new TH1D("totalPredElecIsoTrackSysUp_LL","totalPredElecIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysDown_LL_ = new TH1D("totalPredElecIsoTrackSysDown_LL","totalPredElecIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysUp_LL_ = new TH1D("totalPredPionIsoTrackSysUp_LL","totalPredPionIsoTrackSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysDown_LL_ = new TH1D("totalPredPionIsoTrackSysDown_LL","totalPredPionIsoTrackSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysUp_LL_ = new TH1D("totalPredMTWSysUp_LL","totalPredMTWSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysDown_LL_ = new TH1D("totalPredMTWSysDown_LL","totalPredMTWSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysUp_LL_ = new TH1D("totalPredPuritySysUp_LL","totalPredPuritySysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysDown_LL_ = new TH1D("totalPredPuritySysDown_LL","totalPredPuritySysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysUp_LL_ = new TH1D("totalPredSingleLepPuritySysUp_LL","totalPredSingleLepPuritySysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysDown_LL_ = new TH1D("totalPredSingleLepPuritySysDown_LL","totalPredSingleLepPuritySysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysUp_LL_ = new TH1D("totalPredDiLepFoundSysUp_LL","totalPredDiLepFoundSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysDown_LL_ = new TH1D("totalPredDiLepFoundSysDown_LL","totalPredDiLepFoundSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysUp_LL_ = new TH1D("totalPredMuIsoSysUp_LL","totalPredMuIsoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysDown_LL_ = new TH1D("totalPredMuIsoSysDown_LL","totalPredMuIsoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysUp_LL_ = new TH1D("totalPredMuRecoSysUp_LL","totalPredMuRecoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysDown_LL_ = new TH1D("totalPredMuRecoSysDown_LL","totalPredMuRecoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysUp_LL_ = new TH1D("totalPredMuAccSysUp_LL","totalPredMuAccSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysDown_LL_ = new TH1D("totalPredMuAccSysDown_LL","totalPredMuAccSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysUp_LL_ = new TH1D("totalPredMuAccQsquareSysUp_LL","totalPredMuAccQsquareSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysDown_LL_ = new TH1D("totalPredMuAccQsquareSysDown_LL","totalPredMuAccQsquareSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysUp_LL_ = new TH1D("totalPredElecIsoSysUp_LL","totalPredElecIsoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysDown_LL_ = new TH1D("totalPredElecIsoSysDown_LL","totalPredElecIsoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysUp_LL_ = new TH1D("totalPredElecRecoSysUp_LL","totalPredElecRecoSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysDown_LL_ = new TH1D("totalPredElecRecoSysDown_LL","totalPredElecRecoSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysUp_LL_ = new TH1D("totalPredElecAccSysUp_LL","totalPredElecAccSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysDown_LL_ = new TH1D("totalPredElecAccSysDown_LL","totalPredElecAccSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysUp_LL_ = new TH1D("totalPredElecAccQsquareSysUp_LL","totalPredElecAccQsquareSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysDown_LL_ = new TH1D("totalPredElecAccQsquareSysDown_LL","totalPredElecAccQsquareSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureUp_LL_ = new TH1D("totalPredNonClosureUp_LL","totalPredNonClosureUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureDown_LL_ = new TH1D("totalPredNonClosureDown_LL","totalPredNonClosureDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredIsoTrackStatUp_LL_ = new TH1D("totalPredIsoTrackStatUp_LL","totalPredIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackStatDown_LL_ = new TH1D("totalPredIsoTrackStatDown_LL","totalPredIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatUp_LL_ = new TH1D("totalPredMuIsoTrackStatUp_LL","totalPredMuIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatDown_LL_ = new TH1D("totalPredMuIsoTrackStatDown_LL","totalPredMuIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatUp_LL_ = new TH1D("totalPredElecIsoTrackStatUp_LL","totalPredElecIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatDown_LL_ = new TH1D("totalPredElecIsoTrackStatDown_LL","totalPredElecIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatUp_LL_ = new TH1D("totalPredPionIsoTrackStatUp_LL","totalPredPionIsoTrackStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatDown_LL_ = new TH1D("totalPredPionIsoTrackStatDown_LL","totalPredPionIsoTrackStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatUp_LL_ = new TH1D("totalPredMTWStatUp_LL","totalPredMTWStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatDown_LL_ = new TH1D("totalPredMTWStatDown_LL","totalPredMTWStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatUp_LL_ = new TH1D("totalPredPurityStatUp_LL","totalPredPurityStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatDown_LL_ = new TH1D("totalPredPurityStatDown_LL","totalPredPurityStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatUp_LL_ = new TH1D("totalPredSingleLepPurityStatUp_LL","totalPredSingleLepPurityStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatDown_LL_ = new TH1D("totalPredSingleLepPurityStatDown_LL","totalPredSingleLepPurityStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatUp_LL_ = new TH1D("totalPredDiLepFoundStatUp_LL","totalPredDiLepFoundStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatDown_LL_ = new TH1D("totalPredDiLepFoundStatDown_LL","totalPredDiLepFoundStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatUp_LL_ = new TH1D("totalPredMuIsoStatUp_LL","totalPredMuIsoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatDown_LL_ = new TH1D("totalPredMuIsoStatDown_LL","totalPredMuIsoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatUp_LL_ = new TH1D("totalPredMuRecoStatUp_LL","totalPredMuRecoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatDown_LL_ = new TH1D("totalPredMuRecoStatDown_LL","totalPredMuRecoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatUp_LL_ = new TH1D("totalPredMuAccStatUp_LL","totalPredMuAccStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatDown_LL_ = new TH1D("totalPredMuAccStatDown_LL","totalPredMuAccStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatUp_LL_ = new TH1D("totalPredElecIsoStatUp_LL","totalPredElecIsoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatDown_LL_ = new TH1D("totalPredElecIsoStatDown_LL","totalPredElecIsoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatUp_LL_ = new TH1D("totalPredElecRecoStatUp_LL","totalPredElecRecoStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatDown_LL_ = new TH1D("totalPredElecRecoStatDown_LL","totalPredElecRecoStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatUp_LL_ = new TH1D("totalPredElecAccStatUp_LL","totalPredElecAccStatUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatDown_LL_ = new TH1D("totalPredElecAccStatDown_LL","totalPredElecAccStatDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPropSysUp_LL_ = new TH1D("totalPropSysUp_LL","totalPropSysUp_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPropSysDown_LL_ = new TH1D("totalPropSysDown_LL","totalPropSysDown_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_LL_ = new TH1D("totalCS_LL","totalCS_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsCS_LL_ = new TH1D("nEvtsCS_LL","nEvtsCS_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TProfile* avgWeight_LL_ = new TProfile("avgWeight_LL","avgWeight_LL", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  totalPred_LL_->Sumw2();
  totalPredIsoTrackSysUp_LL_->Sumw2();
  totalPredIsoTrackSysDown_LL_->Sumw2();
  totalPredMuIsoTrackSysUp_LL_->Sumw2();
  totalPredMuIsoTrackSysDown_LL_->Sumw2();
  totalPredElecIsoTrackSysUp_LL_->Sumw2();
  totalPredElecIsoTrackSysDown_LL_->Sumw2();
  totalPredPionIsoTrackSysUp_LL_->Sumw2();
  totalPredPionIsoTrackSysDown_LL_->Sumw2();
  totalPredMTWSysUp_LL_->Sumw2();
  totalPredMTWSysDown_LL_->Sumw2();
  totalPredPuritySysUp_LL_->Sumw2();
  totalPredPuritySysDown_LL_->Sumw2();
  totalPredSingleLepPuritySysUp_LL_->Sumw2();
  totalPredSingleLepPuritySysDown_LL_->Sumw2();
  totalPredDiLepFoundSysUp_LL_->Sumw2();
  totalPredDiLepFoundSysDown_LL_->Sumw2();
  totalPredMuIsoSysUp_LL_->Sumw2();
  totalPredMuIsoSysDown_LL_->Sumw2();
  totalPredMuRecoSysUp_LL_->Sumw2();
  totalPredMuRecoSysDown_LL_->Sumw2();
  totalPredMuAccSysUp_LL_->Sumw2();
  totalPredMuAccSysDown_LL_->Sumw2();
  totalPredMuAccQsquareSysUp_LL_->Sumw2();
  totalPredMuAccQsquareSysDown_LL_->Sumw2();
  totalPredElecIsoSysUp_LL_->Sumw2();
  totalPredElecIsoSysDown_LL_->Sumw2();
  totalPredElecRecoSysUp_LL_->Sumw2();
  totalPredElecRecoSysDown_LL_->Sumw2();
  totalPredElecAccSysUp_LL_->Sumw2();
  totalPredElecAccSysDown_LL_->Sumw2();
  totalPredElecAccQsquareSysUp_LL_->Sumw2();
  totalPredElecAccQsquareSysDown_LL_->Sumw2();
  totalPredNonClosureUp_LL_->Sumw2();
  totalPredNonClosureDown_LL_->Sumw2();

  totalPredIsoTrackStatUp_LL_->Sumw2();
  totalPredIsoTrackStatDown_LL_->Sumw2();
  totalPredMuIsoTrackStatUp_LL_->Sumw2();
  totalPredMuIsoTrackStatDown_LL_->Sumw2();
  totalPredElecIsoTrackStatUp_LL_->Sumw2();
  totalPredElecIsoTrackStatDown_LL_->Sumw2();
  totalPredPionIsoTrackStatUp_LL_->Sumw2();
  totalPredPionIsoTrackStatDown_LL_->Sumw2();
  totalPredMTWStatUp_LL_->Sumw2();
  totalPredMTWStatDown_LL_->Sumw2();
  totalPredPurityStatUp_LL_->Sumw2();
  totalPredPurityStatDown_LL_->Sumw2();
  totalPredSingleLepPurityStatUp_LL_->Sumw2();
  totalPredSingleLepPurityStatDown_LL_->Sumw2();
  totalPredDiLepFoundStatUp_LL_->Sumw2();
  totalPredDiLepFoundStatDown_LL_->Sumw2();
  totalPredMuIsoStatUp_LL_->Sumw2();
  totalPredMuIsoStatDown_LL_->Sumw2();
  totalPredMuRecoStatUp_LL_->Sumw2();
  totalPredMuRecoStatDown_LL_->Sumw2();
  totalPredMuAccStatUp_LL_->Sumw2();
  totalPredMuAccStatDown_LL_->Sumw2();
  totalPredElecIsoStatUp_LL_->Sumw2();
  totalPredElecIsoStatDown_LL_->Sumw2();
  totalPredElecRecoStatUp_LL_->Sumw2();
  totalPredElecRecoStatDown_LL_->Sumw2();
  totalPredElecAccStatUp_LL_->Sumw2();
  totalPredElecAccStatDown_LL_->Sumw2();

  totalPropSysUp_LL_->Sumw2();
  totalPropSysDown_LL_->Sumw2();

  totalCS_LL_->Sumw2();

  avgWeight_LL_->Sumw2();


  // Define histrograms to do totalPrediction per SearchBin (MC)
  TH1D* totalPred_LL_MC_ = new TH1D("totalPred_LL_MC","totalPred_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysUp_LL_MC_ = new TH1D("totalPredIsoTrackSysUp_LL_MC","totalPredIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackSysDown_LL_MC_ = new TH1D("totalPredIsoTrackSysDown_LL_MC","totalPredIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysUp_LL_MC_ = new TH1D("totalPredMuIsoTrackSysUp_LL_MC","totalPredMuIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackSysDown_LL_MC_ = new TH1D("totalPredMuIsoTrackSysDown_LL_MC","totalPredMuIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysUp_LL_MC_ = new TH1D("totalPredElecIsoTrackSysUp_LL_MC","totalPredElecIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackSysDown_LL_MC_ = new TH1D("totalPredElecIsoTrackSysDown_LL_MC","totalPredElecIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysUp_LL_MC_ = new TH1D("totalPredPionIsoTrackSysUp_LL_MC","totalPredPionIsoTrackSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackSysDown_LL_MC_ = new TH1D("totalPredPionIsoTrackSysDown_LL_MC","totalPredPionIsoTrackSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysUp_LL_MC_ = new TH1D("totalPredMTWSysUp_LL_MC","totalPredMTWSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWSysDown_LL_MC_ = new TH1D("totalPredMTWSysDown_LL_MC","totalPredMTWSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysUp_LL_MC_ = new TH1D("totalPredPuritySysUp_LL_MC","totalPredPuritySysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPuritySysDown_LL_MC_ = new TH1D("totalPredPuritySysDown_LL_MC","totalPredPuritySysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysUp_LL_MC_ = new TH1D("totalPredSingleLepPuritySysUp_LL_MC","totalPredSingleLepPuritySysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPuritySysDown_LL_MC_ = new TH1D("totalPredSingleLepPuritySysDown_LL_MC","totalPredSingleLepPuritySysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysUp_LL_MC_ = new TH1D("totalPredDiLepFoundSysUp_LL_MC","totalPredDiLepFoundSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundSysDown_LL_MC_ = new TH1D("totalPredDiLepFoundSysDown_LL_MC","totalPredDiLepFoundSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysUp_LL_MC_ = new TH1D("totalPredMuIsoSysUp_LL_MC","totalPredMuIsoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoSysDown_LL_MC_ = new TH1D("totalPredMuIsoSysDown_LL_MC","totalPredMuIsoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysUp_LL_MC_ = new TH1D("totalPredMuRecoSysUp_LL_MC","totalPredMuRecoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoSysDown_LL_MC_ = new TH1D("totalPredMuRecoSysDown_LL_MC","totalPredMuRecoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysUp_LL_MC_ = new TH1D("totalPredMuAccSysUp_LL_MC","totalPredMuAccSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccSysDown_LL_MC_ = new TH1D("totalPredMuAccSysDown_LL_MC","totalPredMuAccSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysUp_LL_MC_ = new TH1D("totalPredMuAccQsquareSysUp_LL_MC","totalPredMuAccQsquareSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccQsquareSysDown_LL_MC_ = new TH1D("totalPredMuAccQsquareSysDown_LL_MC","totalPredMuAccQsquareSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysUp_LL_MC_ = new TH1D("totalPredElecIsoSysUp_LL_MC","totalPredElecIsoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoSysDown_LL_MC_ = new TH1D("totalPredElecIsoSysDown_LL_MC","totalPredElecIsoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysUp_LL_MC_ = new TH1D("totalPredElecRecoSysUp_LL_MC","totalPredElecRecoSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoSysDown_LL_MC_ = new TH1D("totalPredElecRecoSysDown_LL_MC","totalPredElecRecoSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysUp_LL_MC_ = new TH1D("totalPredElecAccSysUp_LL_MC","totalPredElecAccSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccSysDown_LL_MC_ = new TH1D("totalPredElecAccSysDown_LL_MC","totalPredElecAccSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysUp_LL_MC_ = new TH1D("totalPredElecAccQsquareSysUp_LL_MC","totalPredElecAccQsquareSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccQsquareSysDown_LL_MC_ = new TH1D("totalPredElecAccQsquareSysDown_LL_MC","totalPredElecAccQsquareSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureUp_LL_MC_ = new TH1D("totalPredNonClosureUp_LL_MC","totalPredNonClosureUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredNonClosureDown_LL_MC_ = new TH1D("totalPredNonClosureDown_LL_MC","totalPredNonClosureDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPredIsoTrackStatUp_LL_MC_ = new TH1D("totalPredIsoTrackStatUp_LL_MC","totalPredIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredIsoTrackStatDown_LL_MC_ = new TH1D("totalPredIsoTrackStatDown_LL_MC","totalPredIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatUp_LL_MC_ = new TH1D("totalPredMuIsoTrackStatUp_LL_MC","totalPredMuIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoTrackStatDown_LL_MC_ = new TH1D("totalPredMuIsoTrackStatDown_LL_MC","totalPredMuIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatUp_LL_MC_ = new TH1D("totalPredElecIsoTrackStatUp_LL_MC","totalPredElecIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoTrackStatDown_LL_MC_ = new TH1D("totalPredElecIsoTrackStatDown_LL_MC","totalPredElecIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatUp_LL_MC_ = new TH1D("totalPredPionIsoTrackStatUp_LL_MC","totalPredPionIsoTrackStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPionIsoTrackStatDown_LL_MC_ = new TH1D("totalPredPionIsoTrackStatDown_LL_MC","totalPredPionIsoTrackStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatUp_LL_MC_ = new TH1D("totalPredMTWStatUp_LL_MC","totalPredMTWStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMTWStatDown_LL_MC_ = new TH1D("totalPredMTWStatDown_LL_MC","totalPredMTWStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatUp_LL_MC_ = new TH1D("totalPredPurityStatUp_LL_MC","totalPredPurityStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredPurityStatDown_LL_MC_ = new TH1D("totalPredPurityStatDown_LL_MC","totalPredPurityStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatUp_LL_MC_ = new TH1D("totalPredSingleLepPurityStatUp_LL_MC","totalPredSingleLepPurityStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredSingleLepPurityStatDown_LL_MC_ = new TH1D("totalPredSingleLepPurityStatDown_LL_MC","totalPredSingleLepPurityStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatUp_LL_MC_ = new TH1D("totalPredDiLepFoundStatUp_LL_MC","totalPredDiLepFoundStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredDiLepFoundStatDown_LL_MC_ = new TH1D("totalPredDiLepFoundStatDown_LL_MC","totalPredDiLepFoundStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatUp_LL_MC_ = new TH1D("totalPredMuIsoStatUp_LL_MC","totalPredMuIsoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuIsoStatDown_LL_MC_ = new TH1D("totalPredMuIsoStatDown_LL_MC","totalPredMuIsoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatUp_LL_MC_ = new TH1D("totalPredMuRecoStatUp_LL_MC","totalPredMuRecoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuRecoStatDown_LL_MC_ = new TH1D("totalPredMuRecoStatDown_LL_MC","totalPredMuRecoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatUp_LL_MC_ = new TH1D("totalPredMuAccStatUp_LL_MC","totalPredMuAccStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredMuAccStatDown_LL_MC_ = new TH1D("totalPredMuAccStatDown_LL_MC","totalPredMuAccStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatUp_LL_MC_ = new TH1D("totalPredElecIsoStatUp_LL_MC","totalPredElecIsoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecIsoStatDown_LL_MC_ = new TH1D("totalPredElecIsoStatDown_LL_MC","totalPredElecIsoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatUp_LL_MC_ = new TH1D("totalPredElecRecoStatUp_LL_MC","totalPredElecRecoStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecRecoStatDown_LL_MC_ = new TH1D("totalPredElecRecoStatDown_LL_MC","totalPredElecRecoStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatUp_LL_MC_ = new TH1D("totalPredElecAccStatUp_LL_MC","totalPredElecAccStatUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPredElecAccStatDown_LL_MC_ = new TH1D("totalPredElecAccStatDown_LL_MC","totalPredElecAccStatDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalPropSysUp_LL_MC_ = new TH1D("totalPropSysUp_LL_MC","totalPropSysUp_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* totalPropSysDown_LL_MC_ = new TH1D("totalPropSysDown_LL_MC","totalPropSysDown_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TH1D* totalCS_LL_MC_ = new TH1D("totalCS_LL_MC","totalCS_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);
  TH1D* nEvtsCS_LL_MC_ = new TH1D("nEvtsCS_LL_MC","nEvtsCS_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  TProfile* avgWeight_LL_MC_ = new TProfile("avgWeight_LL_MC","avgWeight_LL_MC", nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5);

  totalPred_LL_MC_->Sumw2();
  totalPredIsoTrackSysUp_LL_MC_->Sumw2();
  totalPredIsoTrackSysDown_LL_MC_->Sumw2();
  totalPredMuIsoTrackSysUp_LL_MC_->Sumw2();
  totalPredMuIsoTrackSysDown_LL_MC_->Sumw2();
  totalPredElecIsoTrackSysUp_LL_MC_->Sumw2();
  totalPredElecIsoTrackSysDown_LL_MC_->Sumw2();
  totalPredPionIsoTrackSysUp_LL_MC_->Sumw2();
  totalPredPionIsoTrackSysDown_LL_MC_->Sumw2();
  totalPredMTWSysUp_LL_MC_->Sumw2();
  totalPredMTWSysDown_LL_MC_->Sumw2();
  totalPredPuritySysUp_LL_MC_->Sumw2();
  totalPredPuritySysDown_LL_MC_->Sumw2();
  totalPredSingleLepPuritySysUp_LL_MC_->Sumw2();
  totalPredSingleLepPuritySysDown_LL_MC_->Sumw2();
  totalPredDiLepFoundSysUp_LL_MC_->Sumw2();
  totalPredDiLepFoundSysDown_LL_MC_->Sumw2();
  totalPredMuIsoSysUp_LL_MC_->Sumw2();
  totalPredMuIsoSysDown_LL_MC_->Sumw2();
  totalPredMuRecoSysUp_LL_MC_->Sumw2();
  totalPredMuRecoSysDown_LL_MC_->Sumw2();
  totalPredMuAccSysUp_LL_MC_->Sumw2();
  totalPredMuAccSysDown_LL_MC_->Sumw2();
  totalPredMuAccQsquareSysUp_LL_MC_->Sumw2();
  totalPredMuAccQsquareSysDown_LL_MC_->Sumw2();
  totalPredElecIsoSysUp_LL_MC_->Sumw2();
  totalPredElecIsoSysDown_LL_MC_->Sumw2();
  totalPredElecRecoSysUp_LL_MC_->Sumw2();
  totalPredElecRecoSysDown_LL_MC_->Sumw2();
  totalPredElecAccSysUp_LL_MC_->Sumw2();
  totalPredElecAccSysDown_LL_MC_->Sumw2();
  totalPredElecAccQsquareSysUp_LL_MC_->Sumw2();
  totalPredElecAccQsquareSysDown_LL_MC_->Sumw2();
  totalPredNonClosureUp_LL_MC_->Sumw2();
  totalPredNonClosureDown_LL_MC_->Sumw2();

  totalPredIsoTrackStatUp_LL_MC_->Sumw2();
  totalPredIsoTrackStatDown_LL_MC_->Sumw2();
  totalPredMuIsoTrackStatUp_LL_MC_->Sumw2();
  totalPredMuIsoTrackStatDown_LL_MC_->Sumw2();
  totalPredElecIsoTrackStatUp_LL_MC_->Sumw2();
  totalPredElecIsoTrackStatDown_LL_MC_->Sumw2();
  totalPredPionIsoTrackStatUp_LL_MC_->Sumw2();
  totalPredPionIsoTrackStatDown_LL_MC_->Sumw2();
  totalPredMTWStatUp_LL_MC_->Sumw2();
  totalPredMTWStatDown_LL_MC_->Sumw2();
  totalPredPurityStatUp_LL_MC_->Sumw2();
  totalPredPurityStatDown_LL_MC_->Sumw2();
  totalPredSingleLepPurityStatUp_LL_MC_->Sumw2();
  totalPredSingleLepPurityStatDown_LL_MC_->Sumw2();
  totalPredDiLepFoundStatUp_LL_MC_->Sumw2();
  totalPredDiLepFoundStatDown_LL_MC_->Sumw2();
  totalPredMuIsoStatUp_LL_MC_->Sumw2();
  totalPredMuIsoStatDown_LL_MC_->Sumw2();
  totalPredMuRecoStatUp_LL_MC_->Sumw2();
  totalPredMuRecoStatDown_LL_MC_->Sumw2();
  totalPredMuAccStatUp_LL_MC_->Sumw2();
  totalPredMuAccStatDown_LL_MC_->Sumw2();
  totalPredElecIsoStatUp_LL_MC_->Sumw2();
  totalPredElecIsoStatDown_LL_MC_->Sumw2();
  totalPredElecRecoStatUp_LL_MC_->Sumw2();
  totalPredElecRecoStatDown_LL_MC_->Sumw2();
  totalPredElecAccStatUp_LL_MC_->Sumw2();
  totalPredElecAccStatDown_LL_MC_->Sumw2();

  totalPropSysUp_LL_MC_->Sumw2();
  totalPropSysDown_LL_MC_->Sumw2();

  totalCS_LL_MC_->Sumw2();

  avgWeight_LL_MC_->Sumw2();


  // Histograms for Readiness Talk
  TH1D* hPredAllBins = new TH1D("hPredAllBins", ";Bin;Events / Bin", 72, 0.5, 72.5);
  TH1D* hExpAllBins = new TH1D("hExpAllBins", ";Bin;Events / Bin", 72, 0.5, 72.5);
  TProfile* hAvgWeightAllBins = new TProfile("hAvgWeightAllBins", ";Bin;avgWeight / Bin", 72, 0.5, 72.5);

  TH1D* hPredHTMHT0b = new TH1D("hPredHTMHT0b", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hPredHTMHTwb = new TH1D("hPredHTMHTwb", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hExpHTMHT0b = new TH1D("hExpHTMHT0b", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hExpHTMHTwb = new TH1D("hExpHTMHTwb", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TProfile* hAvgWeightHTMHT0b = new TProfile("hAvgWeightHTMHT0b", ";HTMHT Box;avgWeight / Bin", 6, 0.5, 6.5);
  TProfile* hAvgWeightHTMHTwb = new TProfile("hAvgWeightHTMHTwb", ";HTMHT Box;avgWeight / Bin", 6, 0.5, 6.5);

  Double_t njetbins[4] = {3.5, 6.5, 8.5, 11.5};
  TH1D* hPredNJetBins = new TH1D("hPredNJetBins", ";N_{jets} (p_{T} > 30 GeV);Events / Bin", 3, njetbins);
  TH1D* hExpNJetBins = new TH1D("hExpNJetBins", ";N_{jets} (p_{T} > 30 GeV);Events / Bin", 3, njetbins);
  TProfile* hAvgWeightNJetBins = new TProfile("hAvgWeightNJetBins", ";N_{jets} (p_{T} > 30 GeV);avgWeight / Bin", 3, njetbins);

  TH1D* hPredNbBins = new TH1D("hPredNbBins", ";N_{b-jets} (p_{T} > 30 GeV);Events / Bin", 4, -0.5, 3.5);
  TH1D* hExpNbBins = new TH1D("hExpNbBins", ";N_{b-jets} (p_{T} > 30 GeV);Events / Bin", 4, -0.5, 3.5);
  TProfile* hAvgWeightNbBins = new TProfile("hAvgWeightNbBins", ";N_{b-jets} (p_{T} > 30 GeV);avgWeight / Bin", 4, -0.5, 3.5);

  hPredAllBins->Sumw2();
  hExpAllBins->Sumw2();
  hAvgWeightAllBins->Sumw2();
  hPredHTMHT0b->Sumw2();
  hPredHTMHTwb->Sumw2();
  hExpHTMHT0b->Sumw2();
  hExpHTMHTwb->Sumw2();
  hAvgWeightHTMHT0b->Sumw2();
  hAvgWeightHTMHTwb->Sumw2();
  hPredNJetBins->Sumw2();
  hExpNJetBins->Sumw2();
  hAvgWeightNJetBins->Sumw2();
  hPredNbBins->Sumw2();
  hExpNbBins->Sumw2();
  hAvgWeightNbBins->Sumw2();


	
  //Expectation Tree
  gROOT->Reset();
  TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation);
  if (!fExp) {
    fExp = new TFile(InputPath_Expectation);
  }
  
  TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");

	
  // Set branch addresses.
  LostLeptonExpectation->SetBranchStatus("*",0);
  LostLeptonExpectation->SetBranchStatus("HT",1);
  LostLeptonExpectation->SetBranchStatus("MHT",1);
  LostLeptonExpectation->SetBranchStatus("NJets",1);
  LostLeptonExpectation->SetBranchStatus("BTags",1);
  LostLeptonExpectation->SetBranchStatus("Weight",1);
  LostLeptonExpectation->SetBranchStatus("Bin",1);
  LostLeptonExpectation->SetBranchStatus("BinQCD",1);
  LostLeptonExpectation->SetBranchStatus("Expectation",1);
  LostLeptonExpectation->SetBranchStatus("ExpectationReductionIsoTrack",1);
  LostLeptonExpectation->SetBranchStatus("muAcc",1);
  LostLeptonExpectation->SetBranchStatus("muReco",1);
  LostLeptonExpectation->SetBranchStatus("muIso",1);
  LostLeptonExpectation->SetBranchStatus("elecAcc",1);
  LostLeptonExpectation->SetBranchStatus("elecReco",1);
  LostLeptonExpectation->SetBranchStatus("elecIso",1);
  LostLeptonExpectation->SetBranchStatus("isoTracks",1);
  LostLeptonExpectation->SetBranchStatus("ExpectationDiLep",1);


  LostLeptonExpectation->SetBranchAddress("HT",&HT);
  LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
  LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
  LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
  LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
  LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
  LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
	
  LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
  LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);

  LostLeptonExpectation->SetBranchAddress("muAcc",&muAcc);
  LostLeptonExpectation->SetBranchAddress("muReco",&muReco);
  LostLeptonExpectation->SetBranchAddress("muIso",&muIso);
	
  LostLeptonExpectation->SetBranchAddress("elecAcc",&elecAcc);
  LostLeptonExpectation->SetBranchAddress("elecReco",&elecReco);
  LostLeptonExpectation->SetBranchAddress("elecIso",&elecIso);
	
  LostLeptonExpectation->SetBranchAddress("isoTracks",&isoTracks);
  LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);
	

	std::cout<<"Loop on Expectation"<<std::endl;
  Long64_t nentries = LostLeptonExpectation->GetEntries();  

  Long64_t nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonExpectation->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
    }
    else SearchBin = Bin;

    // total expectation
    if(doExtrapolation || SearchBin > 900) continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(Expectation==1 && NJets>3.1)
    {
    	totalExpectation_->Fill(SearchBin, scaledWeight);
    	totalExp+=scaledWeight;
    	totalExpError+= scaledWeight*scaledWeight;
    }
    if(Expectation==1 && ExpectationReductionIsoTrack==0 && NJets>3.1)
    {
    	totalExpectationIsoTrackReduction_->Fill(SearchBin, scaledWeight);
    	totalExpIsoTrack+=scaledWeight;
    	totalExpIsoTrackError+= scaledWeight*scaledWeight;
      totalExp_LL_->Fill(SearchBin, scaledWeight);

      nEvtsExp_LL_->Fill(SearchBin);

      hExpAllBins->Fill(SearchBin, scaledWeight);
      if(BTags==0) hExpHTMHT0b->Fill(getHTMHTBox(HT, MHT), scaledWeight);
      else hExpHTMHTwb->Fill(getHTMHTBox(HT, MHT), scaledWeight);
      hExpNJetBins->Fill(NJets, scaledWeight);
      hExpNbBins->Fill(BTags, scaledWeight);
    }
    if(muAcc==0)
    {
    	totalExpectationMuAcc_->Fill(SearchBin, scaledWeight);
    	totalExpMuAcc+=scaledWeight;
    }
    if(muReco==0)
    {
    	totalExpectationMuReco_->Fill(SearchBin, scaledWeight);
    	totalExpMuReco+=scaledWeight;
    }
    if(muIso==0)
    {
    	totalExpectationMuIso_->Fill(SearchBin, scaledWeight);
    	totalExpMuIso+=scaledWeight;
    }
					
    if(elecAcc==0)
    {
    	totalExpectationElecAcc_->Fill(SearchBin, scaledWeight);
    	totalExpElecAcc+=scaledWeight;
    }
    if(elecReco==0)
    {
    	totalExpectationElecReco_->Fill(SearchBin, scaledWeight);
    	totalExpElecReco+=scaledWeight;
    }
    if(elecIso==0)
    {
    	totalExpectationElecIso_->Fill(SearchBin, scaledWeight);
    	totalExpElecIso+=scaledWeight;
    }
  }
	
  std::cout<<"Finished"<<std::endl;

  //Prediction MC Tree
  gROOT->Reset();
  TFile *fPreMC = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction);
  if (!fPreMC) {
    fPreMC = new TFile(InputPath_Prediction);
  }
  TTree* LostLeptonPrediction = (TTree*) fPreMC->Get("LostLeptonPrediction");

  LostLeptonPrediction->SetBranchStatus("*",0);
  LostLeptonPrediction->SetBranchStatus("HT",1);
  LostLeptonPrediction->SetBranchStatus("MHT",1);
  LostLeptonPrediction->SetBranchStatus("NJets",1);
  LostLeptonPrediction->SetBranchStatus("BTags",1);
  LostLeptonPrediction->SetBranchStatus("Weight",1);
  LostLeptonPrediction->SetBranchStatus("Bin",1);
  LostLeptonPrediction->SetBranchStatus("BinQCD",1);
  LostLeptonPrediction->SetBranchStatus("MTW",1);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPrediction->SetBranchStatus("muIsoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("muAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecAccWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPrediction->SetBranchStatus("elecIsoWeight",1);

  LostLeptonPrediction->SetBranchStatus("isoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("isoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("MTWSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("MTWSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("puritySysUp", 1);
  LostLeptonPrediction->SetBranchStatus("puritySysDown", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPuritySysUp", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPuritySysDown", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccQsquareSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccQsquareSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccSysDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccQsquareSysUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccQsquareSysDown", 1);

  LostLeptonPrediction->SetBranchStatus("isoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("isoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("pionIsoTrackStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("MTWStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("MTWStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("purityStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("purityStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPurityStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("singleLepPurityStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("diLepFoundStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muIsoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muRecoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("muAccStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("muAccStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecIsoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecRecoStatDown", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccStatUp", 1);
  LostLeptonPrediction->SetBranchStatus("elecAccStatDown", 1);
  
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
  LostLeptonPrediction->SetBranchAddress("BinQCD",&BinQCD);
  
  LostLeptonPrediction->SetBranchAddress("MTW",&MTW);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
  
  LostLeptonPrediction->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPrediction->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPrediction->SetBranchAddress("muAccWeight",&muAccWeight);
  
  LostLeptonPrediction->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPrediction->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPrediction->SetBranchAddress("elecIsoWeight",&elecIsoWeight);

  LostLeptonPrediction->SetBranchAddress("isoTrackSysUp", &isoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("isoTrackSysDown", &isoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackSysUp", &muIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackSysDown", &muIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  LostLeptonPrediction->SetBranchAddress("MTWSysUp", &MTWSysUp);
  LostLeptonPrediction->SetBranchAddress("MTWSysDown", &MTWSysDown);
  LostLeptonPrediction->SetBranchAddress("puritySysUp", &puritySysUp);
  LostLeptonPrediction->SetBranchAddress("puritySysDown", &puritySysDown);
  LostLeptonPrediction->SetBranchAddress("singleLepPuritySysUp", &singleLepPuritySysUp);
  LostLeptonPrediction->SetBranchAddress("singleLepPuritySysDown", &singleLepPuritySysDown);
  LostLeptonPrediction->SetBranchAddress("diLepFoundSysUp", &diLepFoundSysUp);
  LostLeptonPrediction->SetBranchAddress("diLepFoundSysDown", &diLepFoundSysDown);
  LostLeptonPrediction->SetBranchAddress("muIsoSysUp", &muIsoSysUp);
  LostLeptonPrediction->SetBranchAddress("muIsoSysDown", &muIsoSysDown);
  LostLeptonPrediction->SetBranchAddress("muRecoSysUp", &muRecoSysUp);
  LostLeptonPrediction->SetBranchAddress("muRecoSysDown", &muRecoSysDown);
  LostLeptonPrediction->SetBranchAddress("muAccSysUp", &muAccSysUp);
  LostLeptonPrediction->SetBranchAddress("muAccSysDown", &muAccSysDown);
  LostLeptonPrediction->SetBranchAddress("muAccQsquareSysUp", &muAccQsquareSysUp);
  LostLeptonPrediction->SetBranchAddress("muAccQsquareSysDown", &muAccQsquareSysDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoSysUp", &elecIsoSysUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoSysDown", &elecIsoSysDown);
  LostLeptonPrediction->SetBranchAddress("elecRecoSysUp", &elecRecoSysUp);
  LostLeptonPrediction->SetBranchAddress("elecRecoSysDown", &elecRecoSysDown);
  LostLeptonPrediction->SetBranchAddress("elecAccSysUp", &elecAccSysUp);
  LostLeptonPrediction->SetBranchAddress("elecAccSysDown", &elecAccSysDown);
  LostLeptonPrediction->SetBranchAddress("elecAccQsquareSysUp", &elecAccQsquareSysUp);
  LostLeptonPrediction->SetBranchAddress("elecAccQsquareSysDown", &elecAccQsquareSysDown);

  LostLeptonPrediction->SetBranchAddress("isoTrackStatUp", &isoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("isoTrackStatDown", &isoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackStatUp", &muIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("muIsoTrackStatDown", &muIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  LostLeptonPrediction->SetBranchAddress("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  LostLeptonPrediction->SetBranchAddress("MTWStatUp", &MTWStatUp);
  LostLeptonPrediction->SetBranchAddress("MTWStatDown", &MTWStatDown);
  LostLeptonPrediction->SetBranchAddress("purityStatUp", &purityStatUp);
  LostLeptonPrediction->SetBranchAddress("purityStatDown", &purityStatDown);
  LostLeptonPrediction->SetBranchAddress("singleLepPurityStatUp", &singleLepPurityStatUp);
  LostLeptonPrediction->SetBranchAddress("singleLepPurityStatDown", &singleLepPurityStatDown);
  LostLeptonPrediction->SetBranchAddress("diLepFoundStatUp", &diLepFoundStatUp);
  LostLeptonPrediction->SetBranchAddress("diLepFoundStatDown", &diLepFoundStatDown);
  LostLeptonPrediction->SetBranchAddress("muIsoStatUp", &muIsoStatUp);
  LostLeptonPrediction->SetBranchAddress("muIsoStatDown", &muIsoStatDown);
  LostLeptonPrediction->SetBranchAddress("muRecoStatUp", &muRecoStatUp);
  LostLeptonPrediction->SetBranchAddress("muRecoStatDown", &muRecoStatDown);
  LostLeptonPrediction->SetBranchAddress("muAccStatUp", &muAccStatUp);
  LostLeptonPrediction->SetBranchAddress("muAccStatDown", &muAccStatDown);
  LostLeptonPrediction->SetBranchAddress("elecIsoStatUp", &elecIsoStatUp);
  LostLeptonPrediction->SetBranchAddress("elecIsoStatDown", &elecIsoStatDown);
  LostLeptonPrediction->SetBranchAddress("elecRecoStatUp", &elecRecoStatUp);
  LostLeptonPrediction->SetBranchAddress("elecRecoStatDown", &elecRecoStatDown);
  LostLeptonPrediction->SetBranchAddress("elecAccStatUp", &elecAccStatUp);
  LostLeptonPrediction->SetBranchAddress("elecAccStatDown", &elecAccStatDown);


  std::cout<<"Loop on Prediction (MC)"<<std::endl;
  
  nentries = LostLeptonPrediction->GetEntries();
  nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
    }
    else SearchBin = Bin;

    if(doExtrapolation || SearchBin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    totalPred_LL_MC_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);
    totalPredIsoTrackSysUp_LL_MC_->Fill(SearchBin, isoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_MC_->Fill(SearchBin, isoTrackSysDown*scaleFactorWeight/2);
    totalPredMuIsoTrackSysUp_LL_MC_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredMuIsoTrackSysDown_LL_MC_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredElecIsoTrackSysUp_LL_MC_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredElecIsoTrackSysDown_LL_MC_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredPionIsoTrackSysUp_LL_MC_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredPionIsoTrackSysDown_LL_MC_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);
    totalPredMTWSysUp_LL_MC_->Fill(SearchBin, MTWSysUp*scaleFactorWeight/2);
    totalPredMTWSysDown_LL_MC_->Fill(SearchBin, MTWSysDown*scaleFactorWeight/2);
    totalPredPuritySysUp_LL_MC_->Fill(SearchBin, puritySysUp*scaleFactorWeight/2);
    totalPredPuritySysDown_LL_MC_->Fill(SearchBin, puritySysDown*scaleFactorWeight/2);
    totalPredSingleLepPuritySysUp_LL_MC_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeight/2);
    totalPredSingleLepPuritySysDown_LL_MC_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeight/2);
    totalPredDiLepFoundSysUp_LL_MC_->Fill(SearchBin, diLepFoundSysUp*scaleFactorWeight/2);
    totalPredDiLepFoundSysDown_LL_MC_->Fill(SearchBin, diLepFoundSysDown*scaleFactorWeight/2);
    totalPredMuIsoSysUp_LL_MC_->Fill(SearchBin, muIsoSysUp*scaleFactorWeight/2);
    totalPredMuIsoSysDown_LL_MC_->Fill(SearchBin, muIsoSysDown*scaleFactorWeight/2);
    totalPredMuRecoSysUp_LL_MC_->Fill(SearchBin, muRecoSysUp*scaleFactorWeight/2);
    totalPredMuRecoSysDown_LL_MC_->Fill(SearchBin, muRecoSysDown*scaleFactorWeight/2);
    totalPredMuAccSysUp_LL_MC_->Fill(SearchBin, muAccSysUp*scaleFactorWeight/2);
    totalPredMuAccSysDown_LL_MC_->Fill(SearchBin, muAccSysDown*scaleFactorWeight/2);
    totalPredMuAccQsquareSysUp_LL_MC_->Fill(SearchBin, muAccQsquareSysUp*scaleFactorWeight/2);
    totalPredMuAccQsquareSysDown_LL_MC_->Fill(SearchBin, muAccQsquareSysDown*scaleFactorWeight/2);
    totalPredElecIsoSysUp_LL_MC_->Fill(SearchBin, elecIsoSysUp*scaleFactorWeight/2);
    totalPredElecIsoSysDown_LL_MC_->Fill(SearchBin, elecIsoSysDown*scaleFactorWeight/2);
    totalPredElecRecoSysUp_LL_MC_->Fill(SearchBin, elecRecoSysUp*scaleFactorWeight/2);
    totalPredElecRecoSysDown_LL_MC_->Fill(SearchBin, elecRecoSysDown*scaleFactorWeight/2);
    totalPredElecAccSysUp_LL_MC_->Fill(SearchBin, elecAccSysUp*scaleFactorWeight/2);
    totalPredElecAccSysDown_LL_MC_->Fill(SearchBin, elecAccSysDown*scaleFactorWeight/2);
    totalPredElecAccQsquareSysUp_LL_MC_->Fill(SearchBin, elecAccQsquareSysUp*scaleFactorWeight/2);
    totalPredElecAccQsquareSysDown_LL_MC_->Fill(SearchBin, elecAccQsquareSysDown*scaleFactorWeight/2);

    totalPredIsoTrackStatUp_LL_MC_->Fill(SearchBin, isoTrackStatUp*scaleFactorWeight/2);
    totalPredIsoTrackStatDown_LL_MC_->Fill(SearchBin, isoTrackStatDown*scaleFactorWeight/2);
    totalPredMuIsoTrackStatUp_LL_MC_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2);
    totalPredMuIsoTrackStatDown_LL_MC_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2);
    totalPredElecIsoTrackStatUp_LL_MC_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2);
    totalPredElecIsoTrackStatDown_LL_MC_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2);
    totalPredPionIsoTrackStatUp_LL_MC_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2);
    totalPredPionIsoTrackStatDown_LL_MC_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2);
    totalPredMTWStatUp_LL_MC_->Fill(SearchBin, MTWStatUp*scaleFactorWeight/2);
    totalPredMTWStatDown_LL_MC_->Fill(SearchBin, MTWStatDown*scaleFactorWeight/2);
    totalPredPurityStatUp_LL_MC_->Fill(SearchBin, purityStatUp*scaleFactorWeight/2);
    totalPredPurityStatDown_LL_MC_->Fill(SearchBin, purityStatDown*scaleFactorWeight/2);
    totalPredSingleLepPurityStatUp_LL_MC_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeight/2);
    totalPredSingleLepPurityStatDown_LL_MC_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeight/2);
    totalPredDiLepFoundStatUp_LL_MC_->Fill(SearchBin, diLepFoundStatUp*scaleFactorWeight/2);
    totalPredDiLepFoundStatDown_LL_MC_->Fill(SearchBin, diLepFoundStatDown*scaleFactorWeight/2);
    totalPredMuIsoStatUp_LL_MC_->Fill(SearchBin, muIsoStatUp*scaleFactorWeight/2);
    totalPredMuIsoStatDown_LL_MC_->Fill(SearchBin, muIsoStatDown*scaleFactorWeight/2);
    totalPredMuRecoStatUp_LL_MC_->Fill(SearchBin, muRecoStatUp*scaleFactorWeight/2);
    totalPredMuRecoStatDown_LL_MC_->Fill(SearchBin, muRecoStatDown*scaleFactorWeight/2);
    totalPredMuAccStatUp_LL_MC_->Fill(SearchBin, muAccStatUp*scaleFactorWeight/2);
    totalPredMuAccStatDown_LL_MC_->Fill(SearchBin, muAccStatDown*scaleFactorWeight/2);
    totalPredElecIsoStatUp_LL_MC_->Fill(SearchBin, elecIsoStatUp*scaleFactorWeight/2);
    totalPredElecIsoStatDown_LL_MC_->Fill(SearchBin, elecIsoStatDown*scaleFactorWeight/2);
    totalPredElecRecoStatUp_LL_MC_->Fill(SearchBin, elecRecoStatUp*scaleFactorWeight/2);
    totalPredElecRecoStatDown_LL_MC_->Fill(SearchBin, elecRecoStatDown*scaleFactorWeight/2);
    totalPredElecAccStatUp_LL_MC_->Fill(SearchBin, elecAccStatUp*scaleFactorWeight/2);
    totalPredElecAccStatDown_LL_MC_->Fill(SearchBin, elecAccStatDown*scaleFactorWeight/2);

    totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

    totalPropSysUp_LL_MC_->Fill(SearchBin, totalPropSysUp*scaleFactorWeight/2);
    totalPropSysDown_LL_MC_->Fill(SearchBin, totalPropSysDown*scaleFactorWeight/2);

    totalCS_LL_MC_->Fill(SearchBin, scaledWeight);
    nEvtsCS_LL_MC_->Fill(SearchBin);

    avgWeight_LL_MC_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);
    
    hAvgWeightAllBins->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    if(BTags==0) hAvgWeightHTMHT0b->Fill(getHTMHTBox(HT, MHT), abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    else hAvgWeightHTMHTwb->Fill(getHTMHTBox(HT, MHT), abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    hAvgWeightNJetBins->Fill(NJets, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));
    hAvgWeightNbBins->Fill(BTags, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2));

  }

  std::cout<<"Finished"<<std::endl;

  //Prediction Data Tree
  gROOT->Reset();
  TFile *fPre = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Prediction_Data);
  if (!fPre) {
    fPre = new TFile(InputPath_Prediction_Data);
  }
  TTree* LostLeptonPredictionData = (TTree*) fPre->Get("LostLeptonPrediction");

  LostLeptonPredictionData->SetBranchStatus("*",0);
  LostLeptonPredictionData->SetBranchStatus("HT",1);
  LostLeptonPredictionData->SetBranchStatus("MHT",1);
  LostLeptonPredictionData->SetBranchStatus("NJets",1);
  LostLeptonPredictionData->SetBranchStatus("BTags",1);
  LostLeptonPredictionData->SetBranchStatus("Weight",1);
  LostLeptonPredictionData->SetBranchStatus("Bin",1);
  LostLeptonPredictionData->SetBranchStatus("BinQCD",1);
  LostLeptonPredictionData->SetBranchStatus("MTW",1);
  LostLeptonPredictionData->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPredictionData->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  LostLeptonPredictionData->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  LostLeptonPredictionData->SetBranchStatus("muIsoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("muAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecAccWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoWeight",1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoWeight",1);

  LostLeptonPredictionData->SetBranchStatus("isoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("isoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("puritySysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("puritySysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPuritySysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPuritySysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccQsquareSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccQsquareSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccSysDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccQsquareSysUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccQsquareSysDown", 1);

  LostLeptonPredictionData->SetBranchStatus("isoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("isoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("pionIsoTrackStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("MTWStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("purityStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("purityStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPurityStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("singleLepPurityStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("diLepFoundStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muIsoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muRecoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("muAccStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecIsoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecRecoStatDown", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccStatUp", 1);
  LostLeptonPredictionData->SetBranchStatus("elecAccStatDown", 1);

  LostLeptonPredictionData->SetBranchAddress("HT",&HT);
  LostLeptonPredictionData->SetBranchAddress("MHT",&MHT);
  LostLeptonPredictionData->SetBranchAddress("NJets",&NJets);
  LostLeptonPredictionData->SetBranchAddress("BTags",&BTags);
  LostLeptonPredictionData->SetBranchAddress("Weight",&Weight);
  LostLeptonPredictionData->SetBranchAddress("Bin",&Bin);
  LostLeptonPredictionData->SetBranchAddress("BinQCD",&BinQCD);
	
  LostLeptonPredictionData->SetBranchAddress("MTW",&MTW);
  LostLeptonPredictionData->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  LostLeptonPredictionData->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  LostLeptonPredictionData->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
	
  LostLeptonPredictionData->SetBranchAddress("muIsoWeight",&muIsoWeight);
  LostLeptonPredictionData->SetBranchAddress("muRecoWeight",&muRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("muAccWeight",&muAccWeight);
	
  LostLeptonPredictionData->SetBranchAddress("elecAccWeight",&elecAccWeight);
  LostLeptonPredictionData->SetBranchAddress("elecRecoWeight",&elecRecoWeight);
  LostLeptonPredictionData->SetBranchAddress("elecIsoWeight",&elecIsoWeight);

  LostLeptonPredictionData->SetBranchAddress("isoTrackSysUp", &isoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("isoTrackSysDown", &isoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackSysUp", &muIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackSysDown", &muIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  LostLeptonPredictionData->SetBranchAddress("MTWSysUp", &MTWSysUp);
  LostLeptonPredictionData->SetBranchAddress("MTWSysDown", &MTWSysDown);
  LostLeptonPredictionData->SetBranchAddress("puritySysUp", &puritySysUp);
  LostLeptonPredictionData->SetBranchAddress("puritySysDown", &puritySysDown);
  LostLeptonPredictionData->SetBranchAddress("singleLepPuritySysUp", &singleLepPuritySysUp);
  LostLeptonPredictionData->SetBranchAddress("singleLepPuritySysDown", &singleLepPuritySysDown);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundSysUp", &diLepFoundSysUp);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundSysDown", &diLepFoundSysDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoSysUp", &muIsoSysUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoSysDown", &muIsoSysDown);
  LostLeptonPredictionData->SetBranchAddress("muRecoSysUp", &muRecoSysUp);
  LostLeptonPredictionData->SetBranchAddress("muRecoSysDown", &muRecoSysDown);
  LostLeptonPredictionData->SetBranchAddress("muAccSysUp", &muAccSysUp);
  LostLeptonPredictionData->SetBranchAddress("muAccSysDown", &muAccSysDown);
  LostLeptonPredictionData->SetBranchAddress("muAccQsquareSysUp", &muAccQsquareSysUp);
  LostLeptonPredictionData->SetBranchAddress("muAccQsquareSysDown", &muAccQsquareSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoSysUp", &elecIsoSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoSysDown", &elecIsoSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecRecoSysUp", &elecRecoSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecRecoSysDown", &elecRecoSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccSysUp", &elecAccSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccSysDown", &elecAccSysDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccQsquareSysUp", &elecAccQsquareSysUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccQsquareSysDown", &elecAccQsquareSysDown);

  LostLeptonPredictionData->SetBranchAddress("isoTrackStatUp", &isoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("isoTrackStatDown", &isoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackStatUp", &muIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoTrackStatDown", &muIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  LostLeptonPredictionData->SetBranchAddress("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  LostLeptonPredictionData->SetBranchAddress("MTWStatUp", &MTWStatUp);
  LostLeptonPredictionData->SetBranchAddress("MTWStatDown", &MTWStatDown);
  LostLeptonPredictionData->SetBranchAddress("purityStatUp", &purityStatUp);
  LostLeptonPredictionData->SetBranchAddress("purityStatDown", &purityStatDown);
  LostLeptonPredictionData->SetBranchAddress("singleLepPurityStatUp", &singleLepPurityStatUp);
  LostLeptonPredictionData->SetBranchAddress("singleLepPurityStatDown", &singleLepPurityStatDown);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundStatUp", &diLepFoundStatUp);
  LostLeptonPredictionData->SetBranchAddress("diLepFoundStatDown", &diLepFoundStatDown);
  LostLeptonPredictionData->SetBranchAddress("muIsoStatUp", &muIsoStatUp);
  LostLeptonPredictionData->SetBranchAddress("muIsoStatDown", &muIsoStatDown);
  LostLeptonPredictionData->SetBranchAddress("muRecoStatUp", &muRecoStatUp);
  LostLeptonPredictionData->SetBranchAddress("muRecoStatDown", &muRecoStatDown);
  LostLeptonPredictionData->SetBranchAddress("muAccStatUp", &muAccStatUp);
  LostLeptonPredictionData->SetBranchAddress("muAccStatDown", &muAccStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecIsoStatUp", &elecIsoStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecIsoStatDown", &elecIsoStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecRecoStatUp", &elecRecoStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecRecoStatDown", &elecRecoStatDown);
  LostLeptonPredictionData->SetBranchAddress("elecAccStatUp", &elecAccStatUp);
  LostLeptonPredictionData->SetBranchAddress("elecAccStatDown", &elecAccStatDown);


  std::cout<<"Loop on Prediction (Data)"<<std::endl;
	
  nentries = LostLeptonPredictionData->GetEntries();
  nbytes = 0;
  double scaleMC = 1.0;
  if(!useMCForDataTree && InputPath_Prediction_Data != InputPath_Prediction) scaleFactorWeight = 1.0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPredictionData->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
      if(mergeQCDbins) SearchBin = getMergedBinQCD(BinQCD, NJets);
    }
    else SearchBin = Bin;
    
    if(doExtrapolation || SearchBin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    if(!useMCForDataTree && InputPath_Prediction_Data != InputPath_Prediction) scaleMC = Weight;

    totalPred_LL_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackSysUp_LL_->Fill(SearchBin, isoTrackSysUp*scaleFactorWeight/2);
    totalPredIsoTrackSysDown_LL_->Fill(SearchBin, isoTrackSysDown*scaleFactorWeight/2);
    totalPredMuIsoTrackSysUp_LL_->Fill(SearchBin, muIsoTrackSysUp*scaleFactorWeight/2);
    totalPredMuIsoTrackSysDown_LL_->Fill(SearchBin, muIsoTrackSysDown*scaleFactorWeight/2);
    totalPredElecIsoTrackSysUp_LL_->Fill(SearchBin, elecIsoTrackSysUp*scaleFactorWeight/2);
    totalPredElecIsoTrackSysDown_LL_->Fill(SearchBin, elecIsoTrackSysDown*scaleFactorWeight/2);
    totalPredPionIsoTrackSysUp_LL_->Fill(SearchBin, pionIsoTrackSysUp*scaleFactorWeight/2);
    totalPredPionIsoTrackSysDown_LL_->Fill(SearchBin, pionIsoTrackSysDown*scaleFactorWeight/2);
    totalPredMTWSysUp_LL_->Fill(SearchBin, MTWSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMTWSysDown_LL_->Fill(SearchBin, MTWSysDown*scaleFactorWeight/2/scaleMC);
    totalPredPuritySysUp_LL_->Fill(SearchBin, puritySysUp*scaleFactorWeight/2/scaleMC);
    totalPredPuritySysDown_LL_->Fill(SearchBin, puritySysDown*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPuritySysUp_LL_->Fill(SearchBin, singleLepPuritySysUp*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPuritySysDown_LL_->Fill(SearchBin, singleLepPuritySysDown*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundSysUp_LL_->Fill(SearchBin, diLepFoundSysUp*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundSysDown_LL_->Fill(SearchBin, diLepFoundSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoSysUp_LL_->Fill(SearchBin, muIsoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoSysDown_LL_->Fill(SearchBin, muIsoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoSysUp_LL_->Fill(SearchBin, muRecoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoSysDown_LL_->Fill(SearchBin, muRecoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccSysUp_LL_->Fill(SearchBin, muAccSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccSysDown_LL_->Fill(SearchBin, muAccSysDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccQsquareSysUp_LL_->Fill(SearchBin, muAccQsquareSysUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccQsquareSysDown_LL_->Fill(SearchBin, muAccQsquareSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoSysUp_LL_->Fill(SearchBin, elecIsoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoSysDown_LL_->Fill(SearchBin, elecIsoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoSysUp_LL_->Fill(SearchBin, elecRecoSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoSysDown_LL_->Fill(SearchBin, elecRecoSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccSysUp_LL_->Fill(SearchBin, elecAccSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccSysDown_LL_->Fill(SearchBin, elecAccSysDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccQsquareSysUp_LL_->Fill(SearchBin, elecAccQsquareSysUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccQsquareSysDown_LL_->Fill(SearchBin, elecAccQsquareSysDown*scaleFactorWeight/2/scaleMC);

    totalPredIsoTrackStatUp_LL_->Fill(SearchBin, isoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredIsoTrackStatDown_LL_->Fill(SearchBin, isoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoTrackStatUp_LL_->Fill(SearchBin, muIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoTrackStatDown_LL_->Fill(SearchBin, muIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoTrackStatUp_LL_->Fill(SearchBin, elecIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoTrackStatDown_LL_->Fill(SearchBin, elecIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredPionIsoTrackStatUp_LL_->Fill(SearchBin, pionIsoTrackStatUp*scaleFactorWeight/2/scaleMC);
    totalPredPionIsoTrackStatDown_LL_->Fill(SearchBin, pionIsoTrackStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMTWStatUp_LL_->Fill(SearchBin, MTWStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMTWStatDown_LL_->Fill(SearchBin, MTWStatDown*scaleFactorWeight/2/scaleMC);
    totalPredPurityStatUp_LL_->Fill(SearchBin, purityStatUp*scaleFactorWeight/2/scaleMC);
    totalPredPurityStatDown_LL_->Fill(SearchBin, purityStatDown*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPurityStatUp_LL_->Fill(SearchBin, singleLepPurityStatUp*scaleFactorWeight/2/scaleMC);
    totalPredSingleLepPurityStatDown_LL_->Fill(SearchBin, singleLepPurityStatDown*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundStatUp_LL_->Fill(SearchBin, diLepFoundStatUp*scaleFactorWeight/2/scaleMC);
    totalPredDiLepFoundStatDown_LL_->Fill(SearchBin, diLepFoundStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoStatUp_LL_->Fill(SearchBin, muIsoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuIsoStatDown_LL_->Fill(SearchBin, muIsoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoStatUp_LL_->Fill(SearchBin, muRecoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuRecoStatDown_LL_->Fill(SearchBin, muRecoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredMuAccStatUp_LL_->Fill(SearchBin, muAccStatUp*scaleFactorWeight/2/scaleMC);
    totalPredMuAccStatDown_LL_->Fill(SearchBin, muAccStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoStatUp_LL_->Fill(SearchBin, elecIsoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecIsoStatDown_LL_->Fill(SearchBin, elecIsoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoStatUp_LL_->Fill(SearchBin, elecRecoStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecRecoStatDown_LL_->Fill(SearchBin, elecRecoStatDown*scaleFactorWeight/2/scaleMC);
    totalPredElecAccStatUp_LL_->Fill(SearchBin, elecAccStatUp*scaleFactorWeight/2/scaleMC);
    totalPredElecAccStatDown_LL_->Fill(SearchBin, elecAccStatDown*scaleFactorWeight/2/scaleMC);

    totalPropSysUp = sqrt(isoTrackSysUp*isoTrackSysUp+MTWSysUp*MTWSysUp+puritySysUp*puritySysUp+singleLepPuritySysUp*singleLepPuritySysUp+diLepFoundSysUp*diLepFoundSysUp+muIsoSysUp*muIsoSysUp+muRecoSysUp*muRecoSysUp+muAccSysUp*muAccSysUp+muAccQsquareSysUp*muAccQsquareSysUp+elecIsoSysUp*elecIsoSysUp+elecRecoSysUp*elecRecoSysUp+elecAccSysUp*elecAccSysUp+elecAccQsquareSysUp*elecAccQsquareSysUp+isoTrackStatUp*isoTrackStatUp+MTWStatUp*MTWStatUp+purityStatUp*purityStatUp+singleLepPurityStatUp*singleLepPurityStatUp+diLepFoundStatUp*diLepFoundStatUp+muIsoStatUp*muIsoStatUp+muRecoStatUp*muRecoStatUp+muAccStatUp*muAccStatUp+elecIsoStatUp*elecIsoStatUp+elecRecoStatUp*elecRecoStatUp+elecAccStatUp*elecAccStatUp);
    totalPropSysDown = -sqrt(isoTrackSysDown*isoTrackSysDown+MTWSysDown*MTWSysDown+puritySysDown*puritySysDown+singleLepPuritySysDown*singleLepPuritySysDown+diLepFoundSysDown*diLepFoundSysDown+muIsoSysDown*muIsoSysDown+muRecoSysDown*muRecoSysDown+muAccSysDown*muAccSysDown+muAccQsquareSysDown*muAccQsquareSysDown+elecIsoSysDown*elecIsoSysDown+elecRecoSysDown*elecRecoSysDown+elecAccSysDown*elecAccSysDown+elecAccQsquareSysDown*elecAccQsquareSysDown+isoTrackStatDown*isoTrackStatDown+MTWStatDown*MTWStatDown+purityStatDown*purityStatDown+singleLepPurityStatDown*singleLepPurityStatDown+diLepFoundStatDown*diLepFoundStatDown+muIsoStatDown*muIsoStatDown+muRecoStatDown*muRecoStatDown+muAccStatDown*muAccStatDown+elecIsoStatDown*elecIsoStatDown+elecRecoStatDown*elecRecoStatDown+elecAccStatDown*elecAccStatDown);

    totalPropSysUp_LL_->Fill(SearchBin, totalPropSysUp*scaleFactorWeight/2/scaleMC);
    totalPropSysDown_LL_->Fill(SearchBin, totalPropSysDown*scaleFactorWeight/2/scaleMC);

    totalCS_LL_->Fill(SearchBin, scaledWeight/scaleMC);
    nEvtsCS_LL_->Fill(SearchBin);

    avgWeight_LL_->Fill(SearchBin, abs(totalWeightDiLepIsoTrackReducedCombined/Weight/2), Weight);


    hPredAllBins->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    if(BTags==0) hPredHTMHT0b->Fill(getHTMHTBox(HT, MHT), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    else hPredHTMHTwb->Fill(getHTMHTBox(HT, MHT), totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    hPredNJetBins->Fill(NJets, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
    hPredNbBins->Fill(BTags, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);


    if(selectedIDIsoMuonsNum==1 && selectedIDIsoElectronsNum==0){
    	ControlSampleMu_->Fill(SearchBin, scaledWeight/scaleMC);
    			
    	totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
    	totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
    	totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionMu_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
    	totalPreMu+=totalWeightDiLep*scaleFactorWeight/scaleMC;
    	totalPreMuError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
    	// isotrackveto applied
    	totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC/scaleMC;
    	totalPredictionMuIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC);
    	totalPreIsoTrackMu+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC;
    	totalPreIsoTrackMuError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC/scaleMC;

    	// separted closure
    	totalPredictionMuCSMuAcc_->Fill(SearchBin, muAccWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSMuReco_->Fill(SearchBin, muRecoWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSMuIso_->Fill(SearchBin, muIsoWeight*scaleFactorWeight/scaleMC);
    	totalPreMuAcc+=muAccWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuReco+=muRecoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuIso+=muIsoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuMuAcc+=muAccWeight*scaleFactorWeight/scaleMC;
    	totalPreMuMuReco+=muRecoWeight*scaleFactorWeight/scaleMC;
    	totalPreMuMuIso+=muIsoWeight*scaleFactorWeight/scaleMC;
    			
    	totalPredictionMuCSElecAcc_->Fill(SearchBin, elecAccWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSElecReco_->Fill(SearchBin, elecRecoWeight*scaleFactorWeight/scaleMC);
    	totalPredictionMuCSElecIso_->Fill(SearchBin, elecIsoWeight*scaleFactorWeight/scaleMC);
    	totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2/scaleMC;
    	totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2/scaleMC;
    	totalPreMuElecAcc+=elecAccWeight*scaleFactorWeight/scaleMC;
    	totalPreMuElecReco+=elecRecoWeight*scaleFactorWeight/scaleMC;
    	totalPreMuElecIso+=elecIsoWeight*scaleFactorWeight/scaleMC;
    }
    if(selectedIDIsoMuonsNum==0 && selectedIDIsoElectronsNum==1)
    {
    	ControlSampleElec_->Fill(SearchBin, scaledWeight/scaleMC);
          
      totalPrediction_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/2/scaleMC);
      totalPre+=totalWeightDiLep*scaleFactorWeight/2/scaleMC;
      totalPreError+= totalWeightDiLep*scaleFactorWeight/2*totalWeightDiLep*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElec_->Fill(SearchBin, totalWeightDiLep*scaleFactorWeight/scaleMC);
      totalPreElec+=totalWeightDiLep*scaleFactorWeight/scaleMC;
      totalPreElecError+= totalWeightDiLep*scaleFactorWeight*totalWeightDiLep*scaleFactorWeight/scaleMC/scaleMC;
      // isotrackveto applied
      totalPredictionIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC);
      totalPreIsoTrack+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC;
      totalPreIsoTrackError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2/scaleMC/scaleMC;
      totalPredictionElecIsoTrackReduction_->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC);
      totalPreIsoTrackElec+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC;
      totalPreIsoTrackElecError+=totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight*totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/scaleMC/scaleMC;

      // separted closure
      totalPredictionElecCSElecAcc_->Fill(SearchBin, elecAccWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSElecReco_->Fill(SearchBin, elecRecoWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSElecIso_->Fill(SearchBin, elecIsoWeight*scaleFactorWeight/scaleMC);
      totalPreElecAcc+=elecAccWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecReco+=elecRecoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecIso+=elecIsoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecElecAcc+=elecAccWeight*scaleFactorWeight/scaleMC;
      totalPreElecElecReco+=elecRecoWeight*scaleFactorWeight/scaleMC;
      totalPreElecElecIso+=elecIsoWeight*scaleFactorWeight/scaleMC;
          
      totalPredictionElecCSMuAcc_->Fill(SearchBin, muAccWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSMuReco_->Fill(SearchBin, muRecoWeight*scaleFactorWeight/scaleMC);
      totalPredictionElecCSMuIso_->Fill(SearchBin, muIsoWeight*scaleFactorWeight/scaleMC);
      totalPreMuAcc+=muAccWeight*scaleFactorWeight/2/scaleMC;
      totalPreMuReco+=muRecoWeight*scaleFactorWeight/2/scaleMC;
      totalPreMuIso+=muIsoWeight*scaleFactorWeight/2/scaleMC;
      totalPreElecMuAcc+=muAccWeight*scaleFactorWeight/scaleMC;
      totalPreElecMuReco+=muRecoWeight*scaleFactorWeight/scaleMC;
      totalPreElecMuIso+=muIsoWeight*scaleFactorWeight/scaleMC;
      }
  }

  std::cout<<"Finished"<<std::endl;

	
  TH1D* FullClosure = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosure->Divide(totalPredictionIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosure->SetName("LostLeptonClosure");
  FullClosure->SetTitle("Closure of lost-lepton method");
	
  TH1D* FullClosureMu = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureMu->Divide(totalPredictionMuIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureMu->SetName("LostLeptonClosureMuCS");
  FullClosureMu->SetTitle("Closure of lost-lepton method #mu control-sample");
	
  TH1D* FullClosureElec = (TH1D*) totalExpectationIsoTrackReduction_->Clone();
  FullClosureElec->Divide(totalPredictionElecIsoTrackReduction_,totalExpectationIsoTrackReduction_,1,1,"");
  FullClosureElec->SetName("LostLeptonClosureElecCS");
  FullClosureElec->SetTitle("Closure of lost-lepton method elec control-sample");

  TH1D* ClosureWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureWoIsoTrack->Divide(totalPrediction_,totalExpectation_,1,1,"");
  ClosureWoIsoTrack->SetName("ClosureWoIsoTrack");
  ClosureWoIsoTrack->SetTitle("Closure of lost-lepton method (wo IsotrackVeto)");
  
  TH1D* ClosureMuWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureMuWoIsoTrack->Divide(totalPredictionMu_,totalExpectation_,1,1,"");
  ClosureMuWoIsoTrack->SetName("ClosureMuWoIsoTrack");
  ClosureMuWoIsoTrack->SetTitle("Closure of lost-lepton method #mu control-sample (wo IsotrackVeto)");
  
  TH1D* ClosureElecWoIsoTrack = (TH1D*) totalExpectation_->Clone();
  ClosureElecWoIsoTrack->Divide(totalPredictionElec_,totalExpectation_,1,1,"");
  ClosureElecWoIsoTrack->SetName("ClosureElecWoIsoTrack");
  ClosureElecWoIsoTrack->SetTitle("Closure of lost-lepton method elec control-sample (wo IsotrackVeto)");


  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";
  std::cout<<"\n Muon and Electron CS:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrack<<" +- "<<sqrt(totalPreIsoTrackError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPre<<" +- "<<sqrt(totalPreError)<<std::endl;
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreElecIso<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

  std::cout<<"\n Muon CS only:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrackMu<<" +- "<<sqrt(totalPreIsoTrackMuError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPreMu<<" +- "<<sqrt(totalPreMuError)<<std::endl;	
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreMuMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreMuMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreMuMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreMuElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreMuElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreMuElecIso<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

  std::cout<<"\n Elec CS only:"<<std::endl;
  std::cout<<"TotalExpectationIsoTrack: "<<totalExpIsoTrack<<" +- " << sqrt(totalExpIsoTrackError)<<"\n TotalPredictionIsoTrack: "<<totalPreIsoTrackElec<<" +- "<<sqrt(totalPreIsoTrackElecError)<<std::endl;
  std::cout<<"TotalExpectation: "<<totalExp<<" +- " << sqrt(totalExpError)<<"\n TotalPrediction: "<<totalPreElec<<" +- "<<sqrt(totalPreElecError)<<std::endl;	
  std::cout<<"MuAccExp: "<<totalExpMuAcc<<"\n MuAccPre: "<<totalPreElecMuAcc<<std::endl;
  std::cout<<"MuRecoExp: "<<totalExpMuReco<<"\n MuRecoPre: "<<totalPreElecMuReco<<std::endl;
  std::cout<<"MuIsoExp: "<<totalExpMuIso<<"\n MuIsoPre: "<<totalPreElecMuIso<<std::endl;
  std::cout<<"ElecAccExp: "<<totalExpElecAcc<<"\n ElecAccPre: "<<totalPreElecElecAcc<<std::endl;
  std::cout<<"ElecRecoExp: "<<totalExpElecReco<<"\n ElecRecoPre: "<<totalPreElecElecReco<<std::endl;
  std::cout<<"ElecIsoExp: "<<totalExpElecIso<<"\n ElecIsoPre: "<<totalPreElecElecIso<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------\n";

	
  outPutFile->cd();
  FullClosure->Write();
  FullClosureMu->Write();
  FullClosureElec->Write();
  ClosureWoIsoTrack->Write();
  ClosureMuWoIsoTrack->Write();
  ClosureElecWoIsoTrack->Write();
  outPutFile->mkdir("Closures");
  TDirectory *dClosures = (TDirectory*)outPutFile->Get("Closures");

  SaveClosure(totalPredictionMuCSMuAcc_, totalExpectationMuAcc_, dClosures);
  SaveClosure(totalPredictionMuCSMuReco_, totalExpectationMuReco_, dClosures);
  SaveClosure(totalPredictionMuCSMuIso_, totalExpectationMuIso_, dClosures);
	
  SaveClosure(totalPredictionMuCSElecAcc_, totalExpectationElecAcc_, dClosures);
  SaveClosure(totalPredictionMuCSElecReco_, totalExpectationElecReco_, dClosures);
  SaveClosure(totalPredictionMuCSElecIso_, totalExpectationElecIso_, dClosures);
	
  SaveClosure(totalPredictionElecCSMuAcc_, totalExpectationMuAcc_, dClosures);
  SaveClosure(totalPredictionElecCSMuReco_, totalExpectationMuReco_, dClosures);
  SaveClosure(totalPredictionElecCSMuIso_, totalExpectationMuIso_, dClosures);
	
  SaveClosure(totalPredictionElecCSElecAcc_, totalExpectationElecAcc_, dClosures);
  SaveClosure(totalPredictionElecCSElecReco_, totalExpectationElecReco_, dClosures);
  SaveClosure(totalPredictionElecCSElecIso_, totalExpectationElecIso_, dClosures);
	
  SaveClosure(totalPredictionIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
  SaveClosure(totalPredictionMuIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
  SaveClosure(totalPredictionElecIsoTrackReduction_, totalExpectationIsoTrackReduction_, dClosures);
	
  outPutFile->mkdir("Expectation");
  TDirectory *dExpectation = (TDirectory*)outPutFile->Get("Expectation");
  dExpectation->cd();
  totalExpectation_->Write();
  outPutFile->mkdir("Prediction");
  TDirectory *dPrediction = (TDirectory*)outPutFile->Get("Prediction");
  dPrediction->cd();
  totalPrediction_->Write();
  totalPredictionMu_->Write();
  totalPredictionElec_->Write();
	
  outPutFile->mkdir("ControlSample");
  TDirectory *dControlSample = (TDirectory*)outPutFile->Get("ControlSample");
  SaveClosure(ControlSampleElec_, ControlSampleMu_, dControlSample);
  dControlSample->cd();
  ControlSampleMu_->Write();
  ControlSampleElec_->Write();



  TFile *LLoutPutFile = new TFile(OutputPath_Prediction,"RECREATE");

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Closure");
  TDirectory *dClosure = (TDirectory*)LLoutPutFile->Get("Closure");
  dClosure->cd();

  TH1D *ClosureTest = (TH1D*) totalExp_LL_->Clone("ClosureTest");
  ClosureTest->Divide(totalPred_LL_MC_);
  ClosureTest->SetTitle("Expectation / Prediction");
  SetBinLabel(ClosureTest);
  ClosureTest->Write();
/*
  TH1D *ClosureTest_HT = (TH1D*) totalExp_LL_->Clone("ClosureTest_HT");
  ClosureTest_HT->SetTitle("Expectation / Prediction (HT bins)");

  int nBin = 1;
  for(int i =1; i<=6; i++){
    for(int j =0; j<=11; j++){
      ClosureTest_HT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i));
      ClosureTest_HT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i));
      ClosureTest_HT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i));
      nBin++;
    }
  }
  ClosureTest_HT->Write();

  TH1D *ClosureTest_MHT = (TH1D*) totalExp_LL_->Clone("ClosureTest_MHT");
  ClosureTest_MHT->SetTitle("Expectation / Prediction (MHT bins)");

  nBin = 1;
  for(int i =1; i<=3; i++){
    for(int j =0; j<=11; j++){
      if(i==1){
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i));
        nBin++;
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i+1));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i+1));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i+1));
        nBin++;
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i+2));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i+2));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i+2));
        nBin++;
      }if(i==2){
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i+2));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i+2));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i+2));
        nBin++;
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i+3));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i+3));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i+3));
        nBin++;
      }if(i==3){
        ClosureTest_MHT->SetBinContent(nBin, ClosureTest->GetBinContent(j*6+i+3));
        ClosureTest_MHT->SetBinError(nBin, ClosureTest->GetBinError(j*6+i+3));
        ClosureTest_MHT->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(j*6+i+3));
        nBin++;
      }      
    }
  }
  ClosureTest_MHT->Write();

  nBin = 1;
  Double_t nCSmax = 10000000000.;
  TH1D *ClosureTest_CS = (TH1D*) totalExp_LL_->Clone("ClosureTest_CS");
  ClosureTest_CS->SetTitle("Expectation / Prediction (CS stats)");
  while(nBin <= 72){
    Double_t nCS = 0.;
    int iMax = 0;
    for(int i = 1; i <= 72; i++){
      if(totalCS_LL_MC_->GetBinContent(i)<nCSmax){
        if(nCS < totalCS_LL_MC_->GetBinContent(i)){
          nCS = totalCS_LL_MC_->GetBinContent(i);
          iMax = i;
        }
      }
    }
    nCSmax = nCS;
    ClosureTest_CS->SetBinContent(nBin, ClosureTest->GetBinContent(iMax));
    ClosureTest_CS->SetBinError(nBin, ClosureTest->GetBinError(iMax));
    ClosureTest_CS->GetXaxis()->SetBinLabel(nBin, ClosureTest->GetXaxis()->GetBinLabel(iMax));
    nBin++;
  }
  ClosureTest_CS->Write();
*/
  TH1D *nonClosureSysUp = (TH1D*) ClosureTest->Clone("nonClosureSysUp");
  nonClosureSysUp->Reset();
  nonClosureSysUp->SetTitle("nonClosureSysUp");
  TH1D *nonClosureSysDown = (TH1D*) ClosureTest->Clone("nonClosureSysDown");
  nonClosureSysDown->Reset();
  nonClosureSysDown->SetTitle("nonClosureSysUp");

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Expectation");
  TDirectory *dExp = (TDirectory*)LLoutPutFile->Get("Expectation");
  dExp->cd();

  SetBinLabel(totalExp_LL_);
  totalExp_LL_->Write();
  SetBinLabel(nEvtsExp_LL_);
  nEvtsExp_LL_->Write();

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_data");
  TDirectory *dPreData = (TDirectory*)LLoutPutFile->Get("Prediction_data");
  dPreData->cd();

  SetBinLabel(totalPred_LL_);
  totalPred_LL_->Write();
  
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

  for(int i = 0; i<=ClosureTest->GetNbinsX()+1; ++i){
      totalPredNonClosureUp_LL_->SetBinContent(i, 1.+min(1., max(abs(ClosureTest->GetBinContent(i)-1.), ClosureTest->GetBinError(i))));
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

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_MC");
  TDirectory *dPreMC = (TDirectory*)LLoutPutFile->Get("Prediction_MC");
  dPreMC->cd();

  SetBinLabel(totalPred_LL_MC_);
  totalPred_LL_MC_->Write();
  
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
  avgWeight_LL_MC_->Write();

  if(doMergedHistograms){
    LLoutPutFile->cd();
    LLoutPutFile->mkdir("Readiness");
    TDirectory *dReadiness = (TDirectory*)LLoutPutFile->Get("Readiness");
    dReadiness->cd();

    hPredAllBins->Write();
    hAvgWeightAllBins->Write();
    hPredHTMHT0b->Write();
    hPredHTMHTwb->Write();    
    hAvgWeightHTMHT0b->Write();
    hAvgWeightHTMHTwb->Write();
    hPredNJetBins->Write();
    hAvgWeightNJetBins->Write();
    hPredNbBins->Write();
    hAvgWeightNbBins->Write();

    LLoutPutFile->cd();
    LLoutPutFile->mkdir("Readiness_additional");
    TDirectory *Readiness_additional = (TDirectory*)LLoutPutFile->Get("Readiness_additional");
    Readiness_additional->cd();

    hExpAllBins->Write();
    hExpHTMHT0b->Write();
    hExpHTMHTwb->Write();
    hExpNJetBins->Write();
    hExpNbBins->Write();

    TH1D *hDataMCAllBins = (TH1D*) hPredAllBins->Clone("hDataMCAllBins");
    hDataMCAllBins->Divide(hExpAllBins);
    hDataMCAllBins->SetTitle("Prediction / Expectation");
    hDataMCAllBins->Write();

    TH1D *hDataMCHTMHT0b = (TH1D*) hPredHTMHT0b->Clone("hDataMCHTMHT0b");
    hDataMCHTMHT0b->Divide(hExpHTMHT0b);
    hDataMCHTMHT0b->SetTitle("Prediction / Expectation");
    hDataMCHTMHT0b->Write();

    TH1D *hDataMCHTMHTwb = (TH1D*) hPredHTMHTwb->Clone("hDataMCHTMHTwb");
    hDataMCHTMHTwb->Divide(hExpHTMHTwb);
    hDataMCHTMHTwb->SetTitle("Prediction / Expectation");
    hDataMCHTMHTwb->Write();

    TH1D *hDataMCNJetBins = (TH1D*) hPredNJetBins->Clone("hDataMCNJetBins");
    hDataMCNJetBins->Divide(hExpNJetBins);
    hDataMCNJetBins->SetTitle("Prediction / Expectation");
    hDataMCNJetBins->Write();

    TH1D *hDataMCNbBins = (TH1D*) hPredNbBins->Clone("hDataMCNbBins");
    hDataMCNbBins->Divide(hExpNbBins);
    hDataMCNbBins->SetTitle("Prediction / Expectation");
    hDataMCNbBins->Write();  
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Prediction_Data_MC");
  TDirectory *dDataMC = (TDirectory*)LLoutPutFile->Get("Prediction_Data_MC");
  dDataMC->cd();

  TH1D *Prediction_Data_MC = (TH1D*) totalPred_LL_->Clone("Prediction_Data_MC");
  Prediction_Data_MC->Divide(totalPred_LL_MC_);
  Prediction_Data_MC->SetTitle("Prediction Data / Prediction MC");
  SetBinLabel(Prediction_Data_MC);
  Prediction_Data_MC->Write();


  LLoutPutFile->cd();
  LLoutPutFile->mkdir("AdditionalContent");
  TDirectory *dAdd = (TDirectory*)LLoutPutFile->Get("AdditionalContent");
  dAdd->cd();

  SaveFraction(totalPropSysUp_LL_MC_, totalPred_LL_MC_, dAdd);
  SaveFraction(totalPropSysDown_LL_MC_, totalPred_LL_MC_, dAdd);
  SaveFraction(totalPropSysUp_LL_, totalPred_LL_, dAdd);
  SaveFraction(totalPropSysDown_LL_, totalPred_LL_, dAdd);

  LLoutPutFile->Close();

	

  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);

  double LLexpErr = 0;
  double LLexp = totalExp_LL_->IntegralAndError(1, 72, LLexpErr);
  double LLpreErr = 0;
  double LLpre = totalPred_LL_->IntegralAndError(1, 72, LLpreErr);

  //printf("Total: & & & & & & & $%3.3f\\pm$%3.3f & $%3.3f\\pm$%3.3f \\\\\n", LLexp, LLexpErr, LLpre, LLpreErr);

  //if(!useMCForDataTree && InputPath_Prediction_Data == InputPath_Prediction) std::cout<<"ATTENTION: Full MC statistics used to do prediction! Only approx. stat. unc. (~sqrt(n)) shown on prediction!"<<std::endl;

  if(InputPath_Prediction_Data != InputPath_Prediction) printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & CS\\_data & avg. weight (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (data) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");
  else printf("Bin & NJets & BTags & HT & MHT & CS\\_MC (nEntries) & avg. weight (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Prediction (MC) [$\\pm$ stat. $\\pm$ statEff. $\\pm$ sysEff. $\\pm$ nonClos.] & Expectation \\\\\n");

  for(int i = 1; i<totalPred_LL_->GetNbinsX()+1; ++i){

    //SearchBin (Number, NJets, BTags, HT, MHT)
    printf("%1.0i & ", i);

    if(SearchBins_->GetSearchBin(i-1)->NJetsmin_<SearchBins_->GetSearchBin(i-1)->NJetsmax_ && SearchBins_->GetSearchBin(i-1)->NJetsmin_>=0){
      printf("%d-", SearchBins_->GetSearchBin(i-1)->NJetsmin_);
      if(SearchBins_->GetSearchBin(i-1)->NJetsmax_<9999) printf("%d & ", SearchBins_->GetSearchBin(i-1)->NJetsmax_);
      else printf("Inf & ");
    }else{
      printf("%d & ", SearchBins_->GetSearchBin(i-1)->NJetsmax_);
    }

    if(SearchBins_->GetSearchBin(i-1)->BTagsmin_<SearchBins_->GetSearchBin(i-1)->BTagsmax_ && SearchBins_->GetSearchBin(i-1)->BTagsmin_>=0){
      printf("%d-",SearchBins_->GetSearchBin(i-1)->BTagsmin_);
      if(SearchBins_->GetSearchBin(i-1)->BTagsmax_<9999) printf("%d & ",SearchBins_->GetSearchBin(i-1)->BTagsmax_);
      else printf("Inf & ");
    }else{
      printf("%d & ", SearchBins_->GetSearchBin(i-1)->BTagsmax_);
    }

    printf("%3.0f-",SearchBins_->GetSearchBin(i-1)->HTmin_);
    if(SearchBins_->GetSearchBin(i-1)->HTmax_<9999) printf("%3.0f & ",SearchBins_->GetSearchBin(i-1)->HTmax_);
    else printf("Inf & ");

    printf("%3.0f-",SearchBins_->GetSearchBin(i-1)->MHTmin_);
    if(SearchBins_->GetSearchBin(i-1)->MHTmax_<9999) printf("%3.0f & ",SearchBins_->GetSearchBin(i-1)->MHTmax_);
    else printf("Inf & ");

    // CS events (MC)
    printf("%3.3f & ", totalCS_LL_MC_->GetBinContent(i));
    //printf("%3.3f (%1.0f) & ", totalCS_LL_MC_->GetBinContent(i), nEvtsCS_LL_MC_->GetBinContent(i));
 
    // Average weight per Bin (MC)
    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", avgWeight_LL_MC_->GetBinContent(i), avgWeight_LL_MC_->GetBinError(i), (totalPropSysUp_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPropSysDown_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPredNonClosureUp_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i), (totalPredNonClosureDown_LL_MC_->GetBinContent(i)-1)*avgWeight_LL_MC_->GetBinContent(i));
    
    // CS events (data)
    if(InputPath_Prediction_Data != InputPath_Prediction) printf("%1.0f & ", totalCS_LL_->GetBinContent(i));

    // Average weight per Bin (data)
    //if(InputPath_Prediction_Data != InputPath_Prediction) printf("$%3.3f\\pm%3.3f^{+%3.3f}_{-%3.3f}{}^{+%3.3f}_{-%3.3f}{}^{+%3.3f}_{-%3.3f}$ & ", avgWeight_LL_->GetBinContent(i), avgWeight_LL_->GetBinError(i), avgWeightStatUp_LL_->GetBinContent(i), avgWeightStatDown_LL_->GetBinContent(i), avgWeightSysUp_LL_->GetBinContent(i), avgWeightSysDown_LL_->GetBinContent(i), avgWeightNonClosureUp_LL_->GetBinContent(i), avgWeightNonClosureDown_LL_->GetBinContent(i));

    // Prediction
    // Correct estimate of stat. uncertainty on prediction only possible if data is used or limited MC statistics (e.g. number of events corresponding to 3fb-1)
    // For approximation of stat. uncertainty on prediction using full MC statistics use:
    //if(!useMCForDataTree && InputPath_Prediction_Data == InputPath_Prediction && approxStatUncertainty) if(totalCS_LL_->GetBinContent(i)>0.00001) totalPred_LL_->SetBinError(i, sqrt(totalPred_LL_->GetBinContent(i)*totalPred_LL_->GetBinContent(i)/totalCS_LL_->GetBinContent(i)));

    printf("$%3.3f\\pm%3.3f^{+%3.3f}_{%3.3f}{}^{+%3.3f}_{%3.3f}$ & ", totalPred_LL_->GetBinContent(i), totalPred_LL_->GetBinError(i), (totalPropSysUp_LL_MC_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPropSysDown_LL_MC_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPredNonClosureUp_LL_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i), (totalPredNonClosureDown_LL_->GetBinContent(i)-1)*totalPred_LL_->GetBinContent(i));

    // Expectation
    printf("$%3.3f\\pm%3.3f$ \\\\\n", totalExp_LL_->GetBinContent(i), totalExp_LL_->GetBinError(i));

  }
}
