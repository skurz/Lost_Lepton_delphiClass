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
#include "TSystem.h"


//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


void MakeGenRatio(string InputPath_Expectation="Expectation.root")
{
  // Weight MC events with bTag probabilities
  bool doBtagProbabilities = true;

  // Present output in QCD binning
  bool doQCDbinning = true;

  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 35862;  //in units of [pb]


  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);


  TH1::SetDefaultSumw2();
  unsigned nSB = SearchBins_->GetNbins();

  TH1D* h_genMus = new TH1D("genMus", "genMus", nSB, 0.5, nSB+0.5);
  TH1D* h_genEls = new TH1D("genEls", "genEls", nSB, 0.5, nSB+0.5);
  TH1D* h_genMuElRatio = new TH1D("genMuElRatio", "genMuElRatio", nSB, 0.5, nSB+0.5);

  UShort_t         SearchBin=0;

  //Declaration of leaves types for both trees (Expectation/Prediction)
  UShort_t         Bin;
  UShort_t         BinQCD;
  Double_t         Weight;
  Double_t         scaledWeight;
  Double_t         HT;
  Double_t         MHT;
  Double_t         MHTPhi;
  Int_t            NJets;
  Int_t            BTags;

  std::vector<UShort_t> Bin_bTags(4, 0.);
  std::vector<double> *bTagProb=0;
  
  UShort_t        Expectation;
  Int_t           isoTracksNum;
  UShort_t        ExpectationDiLep;
  UShort_t        ExpectationReductionIsoTrack;

  Float_t         MTW;
  UShort_t        MuonsNum;
  UShort_t        ElectronsNum;

  std::vector<TLorentzVector>* Muons=0;
  std::vector<TLorentzVector>* Electrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<TLorentzVector> *GenElectrons=0;
  

  gROOT->Reset();
  TFile *fExp = (TFile*)gROOT->GetListOfFiles()->FindObject(InputPath_Expectation.c_str());
  if (!fExp) {
    fExp = new TFile(InputPath_Expectation.c_str());
  }
  
  TTree* LostLeptonExpectation = (TTree*) fExp->Get("LostLeptonExpectation");

  
  // Set branch addresses.
  LostLeptonExpectation->SetBranchStatus("*",0);
  LostLeptonExpectation->SetBranchStatus("HT",1);
  LostLeptonExpectation->SetBranchAddress("HT",&HT);
  LostLeptonExpectation->SetBranchStatus("MHT",1);
  LostLeptonExpectation->SetBranchAddress("MHT",&MHT);
  LostLeptonExpectation->SetBranchStatus("NJets",1);
  LostLeptonExpectation->SetBranchAddress("NJets",&NJets);
  LostLeptonExpectation->SetBranchStatus("BTags",1);
  LostLeptonExpectation->SetBranchAddress("BTags",&BTags);
  LostLeptonExpectation->SetBranchStatus("Weight",1);
  LostLeptonExpectation->SetBranchAddress("Weight",&Weight);
  LostLeptonExpectation->SetBranchStatus("Bin",1);
  LostLeptonExpectation->SetBranchAddress("Bin",&Bin);
  LostLeptonExpectation->SetBranchStatus("BinQCD",1);
  LostLeptonExpectation->SetBranchAddress("BinQCD",&BinQCD);
  LostLeptonExpectation->SetBranchStatus("GenMuons",1);
  LostLeptonExpectation->SetBranchAddress("GenMuons",&GenMuons);
  LostLeptonExpectation->SetBranchStatus("GenElectrons",1);
  LostLeptonExpectation->SetBranchAddress("GenElectrons",&GenElectrons);
  LostLeptonExpectation->SetBranchStatus("MTW",1);
  LostLeptonExpectation->SetBranchAddress("MTW",&MTW);
  LostLeptonExpectation->SetBranchStatus("Expectation",1);
  LostLeptonExpectation->SetBranchAddress("Expectation",&Expectation);
  LostLeptonExpectation->SetBranchStatus("ExpectationReductionIsoTrack",1);
  LostLeptonExpectation->SetBranchAddress("ExpectationReductionIsoTrack",&ExpectationReductionIsoTrack);
  LostLeptonExpectation->SetBranchStatus("isoTracksNum",1);
  LostLeptonExpectation->SetBranchAddress("isoTracksNum",&isoTracksNum);
  LostLeptonExpectation->SetBranchStatus("ExpectationDiLep",1);
  LostLeptonExpectation->SetBranchAddress("ExpectationDiLep",&ExpectationDiLep);
  LostLeptonExpectation->SetBranchStatus("bTagProb",1);
  LostLeptonExpectation->SetBranchAddress("bTagProb",&bTagProb);


  std::cout<<"Loop on Expectation"<<std::endl;
  Long64_t nentries = LostLeptonExpectation->GetEntries();  

  Long64_t nbytes = 0;
  for (Long64_t j=0; j<nentries;j++) {
    nbytes += LostLeptonExpectation->GetEntry(j);

    if(doQCDbinning){
      SearchBin = BinQCD;
    }
    else SearchBin = Bin;

    // total expectation
    if(SearchBin > 900) continue;

    for(int i = 0; i < 4; i++){
      if(doBtagProbabilities){
        Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
      }else{
        Bin_bTags.at(i)=SearchBin;
      }
    }

    // Fill events 4 times if using bTag probabilities
    int nLoops = 4;
    if(!doBtagProbabilities){
      nLoops = 1;
    }else if(NJets < 3){
      nLoops = 3;
    }

    for(int i = 0; i < nLoops; i++){
      if(doBtagProbabilities){
        scaledWeight = Weight * scaleFactorWeight * bTagProb->at(i);
        BTags = i;
      }else{
        scaledWeight = Weight * scaleFactorWeight;
      }

      if(GenMuons->size()==1 && GenElectrons->size()==0){
        h_genMus->Fill(Bin_bTags.at(i), scaledWeight);
      }else if(GenMuons->size()==0 && GenElectrons->size()==1){
        h_genEls->Fill(Bin_bTags.at(i), scaledWeight);
      }

    }
  }

  fExp->Close();
  std::cout<<"Finished"<<std::endl;

  //closure test
  TFile *outPutFile = new TFile("genRatio.root","RECREATE"); 
  outPutFile->cd();

  h_genEls->Write();
  h_genMus->Write();
  h_genMuElRatio->Divide(h_genMus, h_genEls,1,1,"B");
  h_genMuElRatio->Write();

}