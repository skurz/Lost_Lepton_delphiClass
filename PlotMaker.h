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
void SaveFraction(TH1D* Num, TH1D* Denom, TDirectory* dir, TString name = "", TString correlation = "");
void SetBinLabel(TH1D* hist, TString name = "");
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
UShort_t        MuonsNum;
UShort_t        ElectronsNum;

std::vector<TLorentzVector>* Muons=0;
std::vector<TLorentzVector>* Electrons=0;
std::vector<Float_t>* MuonsPTW=0;
std::vector<Float_t>* ElectronsPTW=0;
std::vector<TLorentzVector> *GenMuons=0;
std::vector<TLorentzVector> *GenElectrons=0;

Float_t         totalWeightDiLep;
Float_t         totalWeightDiLepIsoTrackReduced;
Float_t         totalWeightDiLepIsoTrackReducedCombined;
std::vector<Float_t>*         totalWeight_BTags=0;
std::vector<Float_t>*         totalWeight_BTags_noIsoTrack=0;

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

// Add some of the uncertainties in quadrature (easier for integration)
TH1D* totalPredDiLepContributionStatUp_LL_ = 0;
TH1D* totalPredDiLepContributionStatDown_LL_ = 0;
TH1D* totalPredDiLepContributionSysUp_LL_ = 0;
TH1D* totalPredDiLepContributionSysDown_LL_ = 0;
TH1D* totalPredLepRecoIsoStatUp_LL_ = 0;
TH1D* totalPredLepRecoIsoStatDown_LL_ = 0;
TH1D* totalPredLepAccStatUp_LL_ = 0;
TH1D* totalPredLepAccStatDown_LL_ = 0;
TH1D* totalPredLepAccSysUp_LL_ = 0;
TH1D* totalPredLepAccSysDown_LL_ = 0;
TH1D* totalPredLepAccQsquareSysUp_LL_ = 0;
TH1D* totalPredLepAccQsquareSysDown_LL_ = 0;

TH1D* totalPredDiLepContributionStatUp_LL_MC_ = 0;
TH1D* totalPredDiLepContributionStatDown_LL_MC_ = 0;
TH1D* totalPredDiLepContributionSysUp_LL_MC_ = 0;
TH1D* totalPredDiLepContributionSysDown_LL_MC_ = 0;
TH1D* totalPredLepRecoIsoStatUp_LL_MC_ = 0;
TH1D* totalPredLepRecoIsoStatDown_LL_MC_ = 0;
TH1D* totalPredLepAccStatUp_LL_MC_ = 0;
TH1D* totalPredLepAccStatDown_LL_MC_ = 0;
TH1D* totalPredLepAccSysUp_LL_MC_ = 0;
TH1D* totalPredLepAccSysDown_LL_MC_ = 0;
TH1D* totalPredLepAccQsquareSysUp_LL_MC_ = 0;
TH1D* totalPredLepAccQsquareSysDown_LL_MC_ = 0;

SearchBins* SearchBins_ = 0;

void SetBinLabel(TH1D* hist, TString name){
  for(int bi = 1; bi < hist->GetNbinsX()+1; bi++){
    if(name == "") hist->GetXaxis()->SetBinLabel(bi, SearchBins_->GetSearchBin(bi)->getString());
    else hist->GetXaxis()->SetBinLabel(bi, name + TString("_") + SearchBins_->GetSearchBin(bi)->getString());
  }

  hist -> GetXaxis() -> LabelsOption("v");
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

void SaveFraction(TH1D* Num, TH1D* Denom, TDirectory* dir, TString name, TString correlation){
  for(int i = 1; i<Denom->GetNbinsX()+1; ++i){
  	if(std::string(Num->GetName()).find(std::string("Up")) != std::string::npos && Num->GetBinContent(i)/Denom->GetBinContent(i)<0) std::cout << Num->GetName() << "/" << Denom->GetName() << ": " << (Num->GetBinContent(i)/Denom->GetBinContent(i)) << std::endl;
    if(std::string(Num->GetName()).find(std::string("Down")) != std::string::npos && Num->GetBinContent(i)/Denom->GetBinContent(i)>0) std::cout << Num->GetName() << "/" << Denom->GetName() << ": " << (Num->GetBinContent(i)/Denom->GetBinContent(i)) << std::endl;
    
    if(Denom->GetBinContent(i)!=0) Num->SetBinContent(i, 1.+Num->GetBinContent(i)/Denom->GetBinContent(i));
    else Num->SetBinContent(i, 1);

    Num->SetBinError(i, 0);
  } 

  if(correlation == "")  SetBinLabel(Num, name);
  else{
    // Efficiency parametrized in NJets only (1D) or NJets and HT (HT bin overlap so treat them correlated in any case)
    if(correlation == TString("NJets")){
      for(int bi = 1; bi<Num->GetNbinsX()+1; ++bi){
        std::vector<int> idx = SearchBins_->GetSearchBin(bi)->getIdx();
        Num->GetXaxis()->SetBinLabel(bi, name + TString::Format("_NJets%d", idx.at(0)));
      }
    // Efficiency parametrized in NJets and MHT
    }else if(correlation == TString("NJetsMHT") || correlation == TString("MHTNJets")){
      for(int bi = 1; bi<Num->GetNbinsX()+1; ++bi){
        std::vector<int> idx = SearchBins_->GetSearchBin(bi)->getIdx();
        Num->GetXaxis()->SetBinLabel(bi, name + TString::Format("_NJets%d_MHT%d", idx.at(0), idx.at(2)));
      }
    // All bins correlated (not parametrized as a function of search bins)
    }else if(correlation == TString("ptAct") || correlation == TString("ActPt")){
      for(int bi = 1; bi<Num->GetNbinsX()+1; ++bi){
        Num->GetXaxis()->SetBinLabel(bi, name);
      }
    // Used for e.g. the isolated Tracks Veto. Please note that some bins are combined!!!
    }else if(correlation == TString("NJetsHTMHTCombined") || correlation == TString("HTMHTNJetsCombined")){
      for(int bi = 1; bi<Num->GetNbinsX()+1; ++bi){
        std::vector<int> idx = SearchBins_->GetSearchBin(bi)->getIdx();
        // combine NJets=2,3-4 and NJets=7-8.9+
        int nj = idx.at(0);
        switch(nj){
          // NJets = 2, 3-4
          case 0:
          case 1:
            nj = 0;
            break;
          // NJets = 5-6
          case 2:
            nj = 1;
            break;
          // NJets = 7-8, 9+
          default:
            nj=2;
            break;
        }
        Num->GetXaxis()->SetBinLabel(bi, name + TString::Format("_NJets%d_MHT%d_HT%d", nj, idx.at(2), idx.at(3)));
      }
      //  Used for e.g. the lepton acceptance. Please note that some bins are combined!!!
    }else if(correlation == TString("NJetsBTagsHTMHTCombined") || correlation == TString("HTMHTNJetsBTagsCombined")){
      for(int bi = 1; bi<Num->GetNbinsX()+1; ++bi){
        std::vector<int> idx = SearchBins_->GetSearchBin(bi)->getIdx();
        // combine all BTags for NJets=2; BTags=1,2+ for NJets=7-8 and all BTags for NJets=9+
        // BTags 2,3+ are always combined
        int nb = idx.at(1);
        switch(idx.at(0)){
          // NJets = 2
          case 0:
            nb = 0;
            break;
          // NJets = 3-4, 5-6
          case 1:
          case 2:
            if(nb == 3) nb = 2;
            break;
          // NJets = 7-8
          case 3:
            if(nb >= 2) nb = 1;
            break;
          // NJets = 9+
          default:
            nb = 0;
            break;
        }
        Num->GetXaxis()->SetBinLabel(bi, name + TString::Format("_NJets%d_BTags%d_MHT%d_HT%d", idx.at(0), nb, idx.at(2), idx.at(3)));
      }
    }else{
      std::cout<<"No valid correlation model for "<<Num->GetName()<<std::endl;
    }
  }

  dir->cd();
  Num->Write();
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
  //tree->SetBranchStatus("GenMuons",1);
  //tree->SetBranchAddress("GenMuons",&GenMuons);
  //tree->SetBranchStatus("GenElectrons",1);
  //tree->SetBranchAddress("GenElectrons",&GenElectrons);

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
  tree->SetBranchStatus("MuonsNum",1);
  tree->SetBranchAddress("MuonsNum",&MuonsNum);
  tree->SetBranchStatus("Muons",1);
  tree->SetBranchAddress("Muons",&Muons);
  tree->SetBranchStatus("ElectronsNum",1);
  tree->SetBranchAddress("ElectronsNum",&ElectronsNum);
  tree->SetBranchStatus("Electrons",1);
  tree->SetBranchAddress("Electrons",&Electrons);
  tree->SetBranchStatus("MuonsPTW",1);
  tree->SetBranchAddress("MuonsPTW",&MuonsPTW);
  tree->SetBranchStatus("ElectronsPTW",1);
  tree->SetBranchAddress("ElectronsPTW",&ElectronsPTW);

  tree->SetBranchStatus("totalWeightDiLep",1);
  tree->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  tree->SetBranchStatus("totalWeightDiLepIsoTrackReduced",1);
  tree->SetBranchAddress("totalWeightDiLepIsoTrackReduced",&totalWeightDiLepIsoTrackReduced);
  tree->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
  tree->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);

  if(!isData){
    tree->SetBranchStatus("bTagProb",1);
    tree->SetBranchAddress("bTagProb",&bTagProb);

    tree->SetBranchStatus("totalWeight_BTags",1);
    tree->SetBranchAddress("totalWeight_BTags",&totalWeight_BTags);
    tree->SetBranchStatus("totalWeight_BTags_noIsoTrack",1);
    tree->SetBranchAddress("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack);
  }else{
    bTagProb = 0;
    totalWeight_BTags = 0;
    totalWeight_BTags_noIsoTrack = 0;
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