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


void SignalContamination()
{

  // General Settings
  TString InputPath_Prediction("Prediction_Scan_T1bbbb_SLm.root");
  TString OutputPath_Prediction("LLContamination_T1bbbb.root");


  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 1; //1280 //150

  // Present output in QCD binning
  bool doQCDbinning = false;


  // Begin of Code
  int nSearchBinsTotal = 72;
  if(doQCDbinning){
    nSearchBinsTotal = 220;
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
  Double_t         SusyLSPMass;
  Double_t         SusyMotherMass;
  
  Float_t         MTW;
  UShort_t        selectedIDIsoMuonsNum;
  UShort_t        selectedIDIsoElectronsNum;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReduced;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;



  std::vector<TH1D*> histVec;  
  std::vector<double> mothMass;  
  std::vector<double> lspMass;  

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
  LostLeptonPrediction->SetBranchStatus("SusyLSPMass", 1);
  LostLeptonPrediction->SetBranchStatus("SusyMotherMass", 1);
  
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
  
  LostLeptonPrediction->SetBranchAddress("SusyLSPMass",&SusyLSPMass);
  LostLeptonPrediction->SetBranchAddress("SusyMotherMass",&SusyMotherMass);


  std::cout<<"Loop on Prediction (MC)"<<std::endl;
  
  Long64_t nentries = LostLeptonPrediction->GetEntries();
  Long64_t nbytes = 0;
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += LostLeptonPrediction->GetEntry(i);

    if(doQCDbinning){
      SearchBin = BinQCD;
    }
    else SearchBin = Bin;

    if(SearchBin > 900) continue;
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    scaledWeight = Weight * scaleFactorWeight;

    int found = -1;
    for(unsigned int i = 0; i < histVec.size(); i++){
      if(abs(SusyLSPMass-lspMass.at(i)) < 0.1 && abs(SusyMotherMass-mothMass.at(i)) < 0.1){
        found = i;
      }
    }


    if(found < 0){
      char buffer [50];
      sprintf(buffer, "mGluino_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
      histVec.push_back(new TH1D(buffer, buffer, nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5));
      found = histVec.size()-1;
      histVec.at(found)->Sumw2();
      lspMass.push_back(SusyLSPMass);
      mothMass.push_back(SusyMotherMass);
    }

    histVec.at(found)->Fill(SearchBin, totalWeightDiLepIsoTrackReducedCombined*scaleFactorWeight/2);    
  }

  std::cout<<"Finished"<<std::endl;

  TFile *LLoutPutFile = new TFile(OutputPath_Prediction,"RECREATE");
  LLoutPutFile->cd();
  LLoutPutFile->mkdir("SignalContamination");
  TDirectory *dPreMC = (TDirectory*)LLoutPutFile->Get("SignalContamination");
  dPreMC->cd();

  for(unsigned int i = 0; i < histVec.size(); i++){
    SetBinLabel(histVec.at(i));
    histVec.at(i)->Write();
  }

  std::cout<<"Saved Output to "<<OutputPath_Prediction<<std::endl;
}
