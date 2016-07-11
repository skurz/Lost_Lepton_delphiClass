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
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <vector>
#include "LLTools.h"
#include "THEff.h"
#include "TROOT.h"

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder);
void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir);
void SetBinLabel(TH1D* hist);
void addUncertainties(TH1D* total, std::vector<TH1D*> uncertainties, bool upperUnc);
void setBranchesExpectation(TTree *tree);
void setBranchesPrediction(TTree *tree, bool isData=false);


// Tree types
UShort_t         Bin;
UShort_t         BinQCD;
UShort_t         SearchBin=0;
Double_t         Weight;
Double_t         scaledWeight=0;
Double_t         HT;
Double_t         MHT;
Double_t         MHTPhi;
Int_t            NJets;
Int_t            BTags;

std::vector<UShort_t> Bin_bTags(4, 0.);
std::vector<double> *bTagProb=0;

UShort_t        Expectation;
UShort_t        ExpectationDiLep;
UShort_t        ExpectationReductionIsoTrack;

Float_t         MTW;
UShort_t        selectedIDIsoMuonsNum;
UShort_t        selectedIDIsoElectronsNum;

std::vector<TLorentzVector>* selectedIDIsoMuons=0;
std::vector<TLorentzVector>* selectedIDIsoElectrons=0;
std::vector<Float_t>* selectedIDIsoMuonsPTW=0;
std::vector<Float_t>* selectedIDIsoElectronsPTW=0;
std::vector<TLorentzVector> *GenMus=0;
std::vector<TLorentzVector> *GenEls=0;

Float_t         totalWeightDiLep;
Float_t         totalWeightDiLepIsoTrackReduced;
Float_t         totalWeightDiLepIsoTrackReducedCombined;
Float_t         totalWeight_BTags0;
Float_t         totalWeight_BTags1Inf;
Float_t         totalWeight_BTags0_noIsoTrack;
Float_t         totalWeight_BTags1Inf_noIsoTrack;

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

// Histograms
TH1D* totalExp_LL_ = 0;
TH1D* totalExp_woIsoTrack_LL_ = 0;
TH1D* nEvtsExp_LL_ = 0;

TH1D* totalPred_LL_ = 0;
TH1D* totalCS_LL_ = 0;
TH1D* nEvtsCS_LL_ = 0;
TProfile* avgWeight_LL_ = 0;

TH1D* totalPred_LL_MC_ = 0;
TH1D* totalPred_woIsoTrack_LL_MC_ = 0;
TH1D* totalCS_LL_MC_ = 0;
TH1D* nEvtsCS_LL_MC_ = 0;
TProfile* avgWeight_LL_MC_ = 0;

TH1D* totalPredIsoTrackSysUp_LL_ = 0;
TH1D* totalPredIsoTrackSysDown_LL_ = 0;
TH1D* totalPredMuIsoTrackSysUp_LL_ = 0;
TH1D* totalPredMuIsoTrackSysDown_LL_ = 0;
TH1D* totalPredElecIsoTrackSysUp_LL_ = 0;
TH1D* totalPredElecIsoTrackSysDown_LL_ = 0;
TH1D* totalPredPionIsoTrackSysUp_LL_ = 0;
TH1D* totalPredPionIsoTrackSysDown_LL_ = 0;
TH1D* totalPredMTWSysUp_LL_ = 0;
TH1D* totalPredMTWSysDown_LL_ = 0;
TH1D* totalPredPuritySysUp_LL_ = 0;
TH1D* totalPredPuritySysDown_LL_ = 0;
TH1D* totalPredSingleLepPuritySysUp_LL_ = 0;
TH1D* totalPredSingleLepPuritySysDown_LL_ = 0;
TH1D* totalPredDiLepFoundSysUp_LL_ = 0;
TH1D* totalPredDiLepFoundSysDown_LL_ = 0;
TH1D* totalPredMuIsoSysUp_LL_ = 0;
TH1D* totalPredMuIsoSysDown_LL_ = 0;
TH1D* totalPredMuRecoSysUp_LL_ = 0;
TH1D* totalPredMuRecoSysDown_LL_ = 0;
TH1D* totalPredMuAccSysUp_LL_ = 0;
TH1D* totalPredMuAccSysDown_LL_ = 0;
TH1D* totalPredMuAccQsquareSysUp_LL_ = 0;
TH1D* totalPredMuAccQsquareSysDown_LL_ = 0;
TH1D* totalPredElecIsoSysUp_LL_ = 0;
TH1D* totalPredElecIsoSysDown_LL_ = 0;
TH1D* totalPredElecRecoSysUp_LL_ = 0;
TH1D* totalPredElecRecoSysDown_LL_ = 0;
TH1D* totalPredElecAccSysUp_LL_ = 0;
TH1D* totalPredElecAccSysDown_LL_ = 0;
TH1D* totalPredElecAccQsquareSysUp_LL_ = 0;
TH1D* totalPredElecAccQsquareSysDown_LL_ = 0;
TH1D* totalPredNonClosureUp_LL_ = 0;
TH1D* totalPredNonClosureDown_LL_ = 0;

TH1D* totalPredIsoTrackStatUp_LL_ = 0;
TH1D* totalPredIsoTrackStatDown_LL_ = 0;
TH1D* totalPredMuIsoTrackStatUp_LL_ = 0;
TH1D* totalPredMuIsoTrackStatDown_LL_ = 0;
TH1D* totalPredElecIsoTrackStatUp_LL_ = 0;
TH1D* totalPredElecIsoTrackStatDown_LL_ = 0;
TH1D* totalPredPionIsoTrackStatUp_LL_ = 0;
TH1D* totalPredPionIsoTrackStatDown_LL_ = 0;
TH1D* totalPredMTWStatUp_LL_ = 0;
TH1D* totalPredMTWStatDown_LL_ = 0;
TH1D* totalPredPurityStatUp_LL_ = 0;
TH1D* totalPredPurityStatDown_LL_ = 0;
TH1D* totalPredSingleLepPurityStatUp_LL_ = 0;
TH1D* totalPredSingleLepPurityStatDown_LL_ = 0;
TH1D* totalPredDiLepFoundStatUp_LL_ = 0;
TH1D* totalPredDiLepFoundStatDown_LL_ = 0;
TH1D* totalPredMuIsoStatUp_LL_ = 0;
TH1D* totalPredMuIsoStatDown_LL_ = 0;
TH1D* totalPredMuRecoStatUp_LL_ = 0;
TH1D* totalPredMuRecoStatDown_LL_ = 0;
TH1D* totalPredMuAccStatUp_LL_ = 0;
TH1D* totalPredMuAccStatDown_LL_ = 0;
TH1D* totalPredElecIsoStatUp_LL_ = 0;
TH1D* totalPredElecIsoStatDown_LL_ = 0;
TH1D* totalPredElecRecoStatUp_LL_ = 0;
TH1D* totalPredElecRecoStatDown_LL_ = 0;
TH1D* totalPredElecAccStatUp_LL_ = 0;
TH1D* totalPredElecAccStatDown_LL_ = 0;

TH1D* totalPropSysUp_LL_ = 0;
TH1D* totalPropSysDown_LL_ = 0;

TH1D* totalPredIsoTrackSysUp_LL_MC_ = 0;
TH1D* totalPredIsoTrackSysDown_LL_MC_ = 0;
TH1D* totalPredMuIsoTrackSysUp_LL_MC_ = 0;
TH1D* totalPredMuIsoTrackSysDown_LL_MC_ = 0;
TH1D* totalPredElecIsoTrackSysUp_LL_MC_ = 0;
TH1D* totalPredElecIsoTrackSysDown_LL_MC_ = 0;
TH1D* totalPredPionIsoTrackSysUp_LL_MC_ = 0;
TH1D* totalPredPionIsoTrackSysDown_LL_MC_ = 0;
TH1D* totalPredMTWSysUp_LL_MC_ = 0;
TH1D* totalPredMTWSysDown_LL_MC_ = 0;
TH1D* totalPredPuritySysUp_LL_MC_ = 0;
TH1D* totalPredPuritySysDown_LL_MC_ = 0;
TH1D* totalPredSingleLepPuritySysUp_LL_MC_ = 0;
TH1D* totalPredSingleLepPuritySysDown_LL_MC_ = 0;
TH1D* totalPredDiLepFoundSysUp_LL_MC_ = 0;
TH1D* totalPredDiLepFoundSysDown_LL_MC_ = 0;
TH1D* totalPredMuIsoSysUp_LL_MC_ = 0;
TH1D* totalPredMuIsoSysDown_LL_MC_ = 0;
TH1D* totalPredMuRecoSysUp_LL_MC_ = 0;
TH1D* totalPredMuRecoSysDown_LL_MC_ = 0;
TH1D* totalPredMuAccSysUp_LL_MC_ = 0;
TH1D* totalPredMuAccSysDown_LL_MC_ = 0;
TH1D* totalPredMuAccQsquareSysUp_LL_MC_ = 0;
TH1D* totalPredMuAccQsquareSysDown_LL_MC_ = 0;
TH1D* totalPredElecIsoSysUp_LL_MC_ = 0;
TH1D* totalPredElecIsoSysDown_LL_MC_ = 0;
TH1D* totalPredElecRecoSysUp_LL_MC_ = 0;
TH1D* totalPredElecRecoSysDown_LL_MC_ = 0;
TH1D* totalPredElecAccSysUp_LL_MC_ = 0;
TH1D* totalPredElecAccSysDown_LL_MC_ = 0;
TH1D* totalPredElecAccQsquareSysUp_LL_MC_ = 0;
TH1D* totalPredElecAccQsquareSysDown_LL_MC_ = 0;
TH1D* totalPredNonClosureUp_LL_MC_ = 0;
TH1D* totalPredNonClosureDown_LL_MC_ = 0;

TH1D* totalPredIsoTrackStatUp_LL_MC_ = 0;
TH1D* totalPredIsoTrackStatDown_LL_MC_ = 0;
TH1D* totalPredMuIsoTrackStatUp_LL_MC_ = 0;
TH1D* totalPredMuIsoTrackStatDown_LL_MC_ = 0;
TH1D* totalPredElecIsoTrackStatUp_LL_MC_ = 0;
TH1D* totalPredElecIsoTrackStatDown_LL_MC_ = 0;
TH1D* totalPredPionIsoTrackStatUp_LL_MC_ = 0;
TH1D* totalPredPionIsoTrackStatDown_LL_MC_ = 0;
TH1D* totalPredMTWStatUp_LL_MC_ = 0;
TH1D* totalPredMTWStatDown_LL_MC_ = 0;
TH1D* totalPredPurityStatUp_LL_MC_ = 0;
TH1D* totalPredPurityStatDown_LL_MC_ = 0;
TH1D* totalPredSingleLepPurityStatUp_LL_MC_ = 0;
TH1D* totalPredSingleLepPurityStatDown_LL_MC_ = 0;
TH1D* totalPredDiLepFoundStatUp_LL_MC_ = 0;
TH1D* totalPredDiLepFoundStatDown_LL_MC_ = 0;
TH1D* totalPredMuIsoStatUp_LL_MC_ = 0;
TH1D* totalPredMuIsoStatDown_LL_MC_ = 0;
TH1D* totalPredMuRecoStatUp_LL_MC_ = 0;
TH1D* totalPredMuRecoStatDown_LL_MC_ = 0;
TH1D* totalPredMuAccStatUp_LL_MC_ = 0;
TH1D* totalPredMuAccStatDown_LL_MC_ = 0;
TH1D* totalPredElecIsoStatUp_LL_MC_ = 0;
TH1D* totalPredElecIsoStatDown_LL_MC_ = 0;
TH1D* totalPredElecRecoStatUp_LL_MC_ = 0;
TH1D* totalPredElecRecoStatDown_LL_MC_ = 0;
TH1D* totalPredElecAccStatUp_LL_MC_ = 0;
TH1D* totalPredElecAccStatDown_LL_MC_ = 0;

TH1D* totalPropSysUp_LL_MC_ = 0;
TH1D* totalPropSysDown_LL_MC_ = 0;



void SetBinLabel(TH1D* hist){
  if(hist->GetNbinsX()==190){
    // only BTags=0,1,2 for NJets=2
    for(int nbi = 0; nbi<4; ++nbi){
      for(int hti = 0; hti<10; ++hti){
        int mhti =0;
        if(hti >=0 && hti <=2) mhti = 0;
        else if(hti >=3 && hti <=5) mhti = 1;
        else if(hti >=6 && hti <=7) mhti = 2;
        else mhti = 3;
        char binlabel[100];
        int bi = nbi * 10 + hti + 1;
        //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", 0, nbi, mhti, hti, bi);
        sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", 0, nbi, mhti, hti);
        hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
      }
    }

    for(int nji = 1; nji<5; ++nji){
      for(int nbi = 0; nbi<4; ++nbi){
        for(int hti = 0; hti<10; ++hti){
          int mhti =0;
          if(hti >=0 && hti <=2) mhti = 0;
          else if(hti >=3 && hti <=5) mhti = 1;
          else if(hti >=6 && hti <=7) mhti = 2;
          else mhti = 3;
          char binlabel[100];
          int bi = 30 + (nji-1) * 40 + nbi * 10 + hti + 1;
          //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
          sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
          hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
        }
      }
    }
  }

  if(hist->GetNbinsX()==160)
  for(int nji = 0; nji<4; ++nji){
    for(int nbi = 0; nbi<4; ++nbi){
      for(int hti = 0; hti<10; ++hti){
        int mhti =0;
        if(hti >=0 && hti <=2) mhti = 0;
        else if(hti >=3 && hti <=5) mhti = 1;
        else if(hti >=6 && hti <=7) mhti = 2;
        else mhti = 3;
        char binlabel[100];
        int bi = (nji) * 40 + nbi * 10 + hti + 1;
        //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
        sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti);
        hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
      }
    }
  }

  if(hist->GetNbinsX()==208)
  for(int nji = 0; nji<4; ++nji){
    for(int nbi = 0; nbi<4; ++nbi){
      for(int hti = 0; hti<13; ++hti){
        int mhti =0;
        if(hti >=0 && hti <=2) mhti = -1;
        else if(hti >=3 && hti <=5) mhti = 0;
        else if(hti >=6 && hti <=8) mhti = 1;
        else if(hti >=9 && hti <=10) mhti = 2;
        else mhti = 3;
        char binlabel[100];
        int bi = (nji) * 52 + nbi * 13 + hti + 1;
        //sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d  %3d", nji, nbi, mhti, hti, bi);
        if(mhti < 0)  sprintf(binlabel, "NJets%d-BTags%d-MHTC-HT%d", nji, nbi, hti);
        else sprintf(binlabel, "NJets%d-BTags%d-MHT%d-HT%d", nji, nbi, mhti, hti-3);
        hist -> GetXaxis() -> SetBinLabel(bi, binlabel);
      }
    }
  }
  
  if(hist->GetNbinsX()==190 || hist->GetNbinsX()==160 || hist->GetNbinsX()==208) hist -> GetXaxis() -> LabelsOption("v");
}

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder) // prediction durch expectation
{
  TH1D* Closure = (TH1D*) prediction->Clone();
  Closure->Divide(prediction,expectation,1,1,"B");
  TString title = prediction->GetTitle();
  title +="_closure";
  //  title = "#mu & e Control-Sample Ratio in Search Bins; Search bins; #mu / e CS";
  Closure->SetTitle(title);
  title = prediction->GetName();
  title+="_closure";
  Closure->SetName(title);
  Folder->cd();
  Closure->Write();
}

void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir){
  for(int i = 1; i<Bottom->GetNbinsX()+1; ++i){
    if(Bottom->GetBinContent(i)!=0) Top->SetBinContent(i, 1.+std::abs(Top->GetBinContent(i)/Bottom->GetBinContent(i)));
    else Top->SetBinContent(i, -999);
    //else Top->SetBinContent(i, 0);
    Top->SetBinError(i, 0);
  } 

  SetBinLabel(Top);

  dir->cd();
  Top->Write();
}

void addUncertainties(TH1D* total, std::vector<TH1D*> uncertainties, bool upperUnc){
  for(int i = 0; i <= total->GetNbinsX(); i++){
    Double_t sumSq = 0.;

    for (std::vector<TH1D*>::iterator it = uncertainties.begin() ; it != uncertainties.end(); ++it){
      sumSq += (*it)->GetBinContent(i) * (*it)->GetBinContent(i);
    }

    if(upperUnc) total->SetBinContent(i, std::sqrt(sumSq));
    else total->SetBinContent(i, -std::sqrt(sumSq));
  }
}

void setBranchesExpectation(TTree* tree){
  tree->SetBranchStatus("*",0);

  tree->SetBranchStatus("HT",1);
  tree->SetBranchAddress("HT",&HT);
  tree->SetBranchStatus("MHT",1);
  tree->SetBranchAddress("MHT",&MHT);
  tree->SetBranchStatus("MHTPhi",1);
  tree->SetBranchAddress("MHTPhi",&MHTPhi);
  tree->SetBranchStatus("NJets",1);
  tree->SetBranchAddress("NJets",&NJets);
  tree->SetBranchStatus("BTags",1);
  tree->SetBranchAddress("BTags",&BTags);
  tree->SetBranchStatus("Weight",1);
  tree->SetBranchAddress("Weight",&Weight);
  tree->SetBranchStatus("Bin",1);
  tree->SetBranchAddress("Bin",&Bin);
  tree->SetBranchStatus("BinQCD",1);
  tree->SetBranchAddress("BinQCD",&BinQCD);
  tree->SetBranchStatus("GenMus",1);
  tree->SetBranchAddress("GenMus",&GenMus);
  tree->SetBranchStatus("GenEls",1);
  tree->SetBranchAddress("GenEls",&GenEls);

  tree->SetBranchStatus("Expectation",1);
  tree->SetBranchAddress("Expectation",&Expectation);
  tree->SetBranchStatus("ExpectationReductionIsoTrack",1);
  tree->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  tree->SetBranchStatus("ExpectationDiLep",1);
  tree->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);

  tree->SetBranchStatus("bTagProb",1);
  tree->SetBranchAddress("bTagProb",&bTagProb);
}

void setBranchesPrediction(TTree *tree, bool isData){
  tree->SetBranchStatus("*",0);

  tree->SetBranchStatus("HT",1);
  tree->SetBranchAddress("HT",&HT);
  tree->SetBranchStatus("MHT",1);
  tree->SetBranchAddress("MHT",&MHT);
  tree->SetBranchStatus("NJets",1);
  tree->SetBranchAddress("NJets",&NJets);
  tree->SetBranchStatus("BTags",1);
  tree->SetBranchAddress("BTags",&BTags);
  tree->SetBranchStatus("Bin",1);
  tree->SetBranchAddress("Bin",&Bin);
  tree->SetBranchStatus("BinQCD",1);
  tree->SetBranchAddress("BinQCD",&BinQCD);
  tree->SetBranchStatus("Weight",1);
  tree->SetBranchAddress("Weight",&Weight);
  tree->SetBranchStatus("MTW",1);
  tree->SetBranchAddress("MTW",&MTW);
  tree->SetBranchStatus("selectedIDIsoMuonsNum",1);
  tree->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  tree->SetBranchStatus("selectedIDIsoMuons",1);
  tree->SetBranchAddress("selectedIDIsoMuons",&selectedIDIsoMuons);
  tree->SetBranchStatus("selectedIDIsoElectronsNum",1);
  tree->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  tree->SetBranchStatus("selectedIDIsoElectrons",1);
  tree->SetBranchAddress("selectedIDIsoElectrons",&selectedIDIsoElectrons);
  tree->SetBranchStatus("selectedIDIsoMuonsPTW",1);
  tree->SetBranchAddress("selectedIDIsoMuonsPTW",&selectedIDIsoMuonsPTW);
  tree->SetBranchStatus("selectedIDIsoElectronsPTW",1);
  tree->SetBranchAddress("selectedIDIsoElectronsPTW",&selectedIDIsoElectronsPTW);

  tree->SetBranchStatus("totalWeightDiLep",1);
  tree->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  tree->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  tree->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  tree->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  tree->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);

  if(!isData){
    tree->SetBranchStatus("bTagProb",1);
    tree->SetBranchAddress("bTagProb",&bTagProb);

    tree->SetBranchStatus("totalWeight_BTags0",1);
    tree->SetBranchAddress("totalWeight_BTags0",&totalWeight_BTags0);
    tree->SetBranchStatus("totalWeight_BTags1Inf",1);
    tree->SetBranchAddress("totalWeight_BTags1Inf",&totalWeight_BTags1Inf);
    tree->SetBranchStatus("totalWeight_BTags0_noIsoTrack",1);
    tree->SetBranchAddress("totalWeight_BTags0_noIsoTrack",&totalWeight_BTags0_noIsoTrack);
    tree->SetBranchStatus("totalWeight_BTags1Inf_noIsoTrack",1);
    tree->SetBranchAddress("totalWeight_BTags1Inf_noIsoTrack",&totalWeight_BTags1Inf_noIsoTrack); 
  }else{
    bTagProb = 0;
    totalWeight_BTags0 = 0;
    totalWeight_BTags1Inf = 0;
    totalWeight_BTags0_noIsoTrack = 0;
    totalWeight_BTags1Inf_noIsoTrack = 0;
  }  

  tree->SetBranchStatus("isoTrackSysUp", 1);
  tree->SetBranchStatus("isoTrackSysDown", 1);
  tree->SetBranchStatus("muIsoTrackSysUp", 1);
  tree->SetBranchStatus("muIsoTrackSysDown", 1);
  tree->SetBranchStatus("elecIsoTrackSysUp", 1);
  tree->SetBranchStatus("elecIsoTrackSysDown", 1);
  tree->SetBranchStatus("pionIsoTrackSysUp", 1);
  tree->SetBranchStatus("pionIsoTrackSysDown", 1);
  tree->SetBranchStatus("MTWSysUp", 1);
  tree->SetBranchStatus("MTWSysDown", 1);
  tree->SetBranchStatus("puritySysUp", 1);
  tree->SetBranchStatus("puritySysDown", 1);
  tree->SetBranchStatus("singleLepPuritySysUp", 1);
  tree->SetBranchStatus("singleLepPuritySysDown", 1);
  tree->SetBranchStatus("diLepFoundSysUp", 1);
  tree->SetBranchStatus("diLepFoundSysDown", 1);
  tree->SetBranchStatus("muIsoSysUp", 1);
  tree->SetBranchStatus("muIsoSysDown", 1);
  tree->SetBranchStatus("muRecoSysUp", 1);
  tree->SetBranchStatus("muRecoSysDown", 1);
  tree->SetBranchStatus("muAccSysUp", 1);
  tree->SetBranchStatus("muAccSysDown", 1);
  tree->SetBranchStatus("muAccQsquareSysUp", 1);
  tree->SetBranchStatus("muAccQsquareSysDown", 1);
  tree->SetBranchStatus("elecIsoSysUp", 1);
  tree->SetBranchStatus("elecIsoSysDown", 1);
  tree->SetBranchStatus("elecRecoSysUp", 1);
  tree->SetBranchStatus("elecRecoSysDown", 1);
  tree->SetBranchStatus("elecAccSysUp", 1);
  tree->SetBranchStatus("elecAccSysDown", 1);
  tree->SetBranchStatus("elecAccQsquareSysUp", 1);
  tree->SetBranchStatus("elecAccQsquareSysDown", 1);

  tree->SetBranchStatus("isoTrackStatUp", 1);
  tree->SetBranchStatus("isoTrackStatDown", 1);
  tree->SetBranchStatus("muIsoTrackStatUp", 1);
  tree->SetBranchStatus("muIsoTrackStatDown", 1);
  tree->SetBranchStatus("elecIsoTrackStatUp", 1);
  tree->SetBranchStatus("elecIsoTrackStatDown", 1);
  tree->SetBranchStatus("pionIsoTrackStatUp", 1);
  tree->SetBranchStatus("pionIsoTrackStatDown", 1);
  tree->SetBranchStatus("MTWStatUp", 1);
  tree->SetBranchStatus("MTWStatDown", 1);
  tree->SetBranchStatus("purityStatUp", 1);
  tree->SetBranchStatus("purityStatDown", 1);
  tree->SetBranchStatus("singleLepPurityStatUp", 1);
  tree->SetBranchStatus("singleLepPurityStatDown", 1);
  tree->SetBranchStatus("diLepFoundStatUp", 1);
  tree->SetBranchStatus("diLepFoundStatDown", 1);
  tree->SetBranchStatus("muIsoStatUp", 1);
  tree->SetBranchStatus("muIsoStatDown", 1);
  tree->SetBranchStatus("muRecoStatUp", 1);
  tree->SetBranchStatus("muRecoStatDown", 1);
  tree->SetBranchStatus("muAccStatUp", 1);
  tree->SetBranchStatus("muAccStatDown", 1);
  tree->SetBranchStatus("elecIsoStatUp", 1);
  tree->SetBranchStatus("elecIsoStatDown", 1);
  tree->SetBranchStatus("elecRecoStatUp", 1);
  tree->SetBranchStatus("elecRecoStatDown", 1);
  tree->SetBranchStatus("elecAccStatUp", 1);
  tree->SetBranchStatus("elecAccStatDown", 1);

  tree->SetBranchAddress("isoTrackSysUp", &isoTrackSysUp);
  tree->SetBranchAddress("isoTrackSysDown", &isoTrackSysDown);
  tree->SetBranchAddress("muIsoTrackSysUp", &muIsoTrackSysUp);
  tree->SetBranchAddress("muIsoTrackSysDown", &muIsoTrackSysDown);
  tree->SetBranchAddress("elecIsoTrackSysUp", &elecIsoTrackSysUp);
  tree->SetBranchAddress("elecIsoTrackSysDown", &elecIsoTrackSysDown);
  tree->SetBranchAddress("pionIsoTrackSysUp", &pionIsoTrackSysUp);
  tree->SetBranchAddress("pionIsoTrackSysDown", &pionIsoTrackSysDown);
  tree->SetBranchAddress("MTWSysUp", &MTWSysUp);
  tree->SetBranchAddress("MTWSysDown", &MTWSysDown);
  tree->SetBranchAddress("puritySysUp", &puritySysUp);
  tree->SetBranchAddress("puritySysDown", &puritySysDown);
  tree->SetBranchAddress("singleLepPuritySysUp", &singleLepPuritySysUp);
  tree->SetBranchAddress("singleLepPuritySysDown", &singleLepPuritySysDown);
  tree->SetBranchAddress("diLepFoundSysUp", &diLepFoundSysUp);
  tree->SetBranchAddress("diLepFoundSysDown", &diLepFoundSysDown);
  tree->SetBranchAddress("muIsoSysUp", &muIsoSysUp);
  tree->SetBranchAddress("muIsoSysDown", &muIsoSysDown);
  tree->SetBranchAddress("muRecoSysUp", &muRecoSysUp);
  tree->SetBranchAddress("muRecoSysDown", &muRecoSysDown);
  tree->SetBranchAddress("muAccSysUp", &muAccSysUp);
  tree->SetBranchAddress("muAccSysDown", &muAccSysDown);
  tree->SetBranchAddress("muAccQsquareSysUp", &muAccQsquareSysUp);
  tree->SetBranchAddress("muAccQsquareSysDown", &muAccQsquareSysDown);
  tree->SetBranchAddress("elecIsoSysUp", &elecIsoSysUp);
  tree->SetBranchAddress("elecIsoSysDown", &elecIsoSysDown);
  tree->SetBranchAddress("elecRecoSysUp", &elecRecoSysUp);
  tree->SetBranchAddress("elecRecoSysDown", &elecRecoSysDown);
  tree->SetBranchAddress("elecAccSysUp", &elecAccSysUp);
  tree->SetBranchAddress("elecAccSysDown", &elecAccSysDown);
  tree->SetBranchAddress("elecAccQsquareSysUp", &elecAccQsquareSysUp);
  tree->SetBranchAddress("elecAccQsquareSysDown", &elecAccQsquareSysDown);

  tree->SetBranchAddress("isoTrackStatUp", &isoTrackStatUp);
  tree->SetBranchAddress("isoTrackStatDown", &isoTrackStatDown);
  tree->SetBranchAddress("muIsoTrackStatUp", &muIsoTrackStatUp);
  tree->SetBranchAddress("muIsoTrackStatDown", &muIsoTrackStatDown);
  tree->SetBranchAddress("elecIsoTrackStatUp", &elecIsoTrackStatUp);
  tree->SetBranchAddress("elecIsoTrackStatDown", &elecIsoTrackStatDown);
  tree->SetBranchAddress("pionIsoTrackStatUp", &pionIsoTrackStatUp);
  tree->SetBranchAddress("pionIsoTrackStatDown", &pionIsoTrackStatDown);
  tree->SetBranchAddress("MTWStatUp", &MTWStatUp);
  tree->SetBranchAddress("MTWStatDown", &MTWStatDown);
  tree->SetBranchAddress("purityStatUp", &purityStatUp);
  tree->SetBranchAddress("purityStatDown", &purityStatDown);
  tree->SetBranchAddress("singleLepPurityStatUp", &singleLepPurityStatUp);
  tree->SetBranchAddress("singleLepPurityStatDown", &singleLepPurityStatDown);
  tree->SetBranchAddress("diLepFoundStatUp", &diLepFoundStatUp);
  tree->SetBranchAddress("diLepFoundStatDown", &diLepFoundStatDown);
  tree->SetBranchAddress("muIsoStatUp", &muIsoStatUp);
  tree->SetBranchAddress("muIsoStatDown", &muIsoStatDown);
  tree->SetBranchAddress("muRecoStatUp", &muRecoStatUp);
  tree->SetBranchAddress("muRecoStatDown", &muRecoStatDown);
  tree->SetBranchAddress("muAccStatUp", &muAccStatUp);
  tree->SetBranchAddress("muAccStatDown", &muAccStatDown);
  tree->SetBranchAddress("elecIsoStatUp", &elecIsoStatUp);
  tree->SetBranchAddress("elecIsoStatDown", &elecIsoStatDown);
  tree->SetBranchAddress("elecRecoStatUp", &elecRecoStatUp);
  tree->SetBranchAddress("elecRecoStatDown", &elecRecoStatDown);
  tree->SetBranchAddress("elecAccStatUp", &elecAccStatUp);
  tree->SetBranchAddress("elecAccStatDown", &elecAccStatDown);
}