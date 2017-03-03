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
#include <algorithm>

void SetBinLabel(TH1D* hist, SearchBins* SB, TString name = "");

void SignalContamination(std::string input = "Prediction_Scan_T2tt.root", std::string output = "LLContamination_T2tt.root")
{

  // General Settings
  TString InputPath_Prediction(input);
  TString OutputPath_Prediction(output);


  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 1; // in units of [pb] //<-check------------------------

  // Present output in QCD binning
  bool doQCDbinning = false;  //<-check------------------------;

  bool doSignalContaminationStudy = false;

  // Begin of Code
  SearchBins *SearchBins_ = new SearchBins(doQCDbinning);

  const int nSearchBinsTotal = SearchBins_->GetNbins();

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
  UShort_t        MuonsNum;
  UShort_t        ElectronsNum;

  std::vector<Float_t>*         totalWeight_BTags=0;
  std::vector<Float_t>*         totalWeight_BTags_noIsoTrack=0;

  std::vector<UShort_t> Bin_bTags(4, 0.);
  std::vector<double> *bTagProb=0;

  std::vector<TH1D*> histVec;
  std::vector<TH1D*> histVec_eCS;
  std::vector<TH1D*> histVec_muCS;
  std::vector<TH1D*> histVec_avgWeight;
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
  LostLeptonPrediction->SetBranchStatus("MuonsNum",1);
  LostLeptonPrediction->SetBranchStatus("ElectronsNum",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags",1);
  LostLeptonPrediction->SetBranchStatus("totalWeight_BTags_noIsoTrack",1);
  LostLeptonPrediction->SetBranchStatus("SusyLSPMass", 1);
  LostLeptonPrediction->SetBranchStatus("SusyMotherMass", 1);
  LostLeptonPrediction->SetBranchStatus("bTagProb", 1);

  
  LostLeptonPrediction->SetBranchAddress("HT",&HT);
  LostLeptonPrediction->SetBranchAddress("MHT",&MHT);
  LostLeptonPrediction->SetBranchAddress("NJets",&NJets);
  LostLeptonPrediction->SetBranchAddress("BTags",&BTags);
  LostLeptonPrediction->SetBranchAddress("Weight",&Weight);
  LostLeptonPrediction->SetBranchAddress("Bin",&Bin);
  LostLeptonPrediction->SetBranchAddress("BinQCD",&BinQCD);
  
  LostLeptonPrediction->SetBranchAddress("MTW",&MTW);
  LostLeptonPrediction->SetBranchAddress("MuonsNum",&MuonsNum);
  LostLeptonPrediction->SetBranchAddress("ElectronsNum",&ElectronsNum);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags",&totalWeight_BTags);
  LostLeptonPrediction->SetBranchAddress("totalWeight_BTags_noIsoTrack",&totalWeight_BTags_noIsoTrack);

  LostLeptonPrediction->SetBranchAddress("SusyLSPMass",&SusyLSPMass);
  LostLeptonPrediction->SetBranchAddress("SusyMotherMass",&SusyMotherMass);

  LostLeptonPrediction->SetBranchAddress("bTagProb",&bTagProb);


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
    if(MTW>100) continue;
    if(MuonsNum+ElectronsNum!=1) continue;

    int nLoops = (NJets < 3 ? 3 : 4);

    for(int i = 0; i < nLoops; i++){
      Bin_bTags.at(i)=SearchBins_->GetBinNumber(HT,MHT,NJets,i);
    }

    scaledWeight = Weight * scaleFactorWeight;

    int found = -1;
    for(unsigned int i = 0; i < histVec.size(); i++){
      if(abs(SusyLSPMass-lspMass.at(i)) < 0.1 && abs(SusyMotherMass-mothMass.at(i)) < 0.1){
        found = i;
      }
    }


    if(found < 0){
      TString currentTree = TString(LostLeptonPrediction->GetCurrentFile()->GetName());
      char buffer [50];
      char buffer_mu [50];
      char buffer_e [50];
      char buffer_avgWeight [50];

      if((std::string(currentTree.Data()).find(std::string("T1"))) != std::string::npos || (std::string(currentTree.Data()).find(std::string("T5"))) != std::string::npos){
        sprintf(buffer, "mGluino_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_mu, "muCS_mGluino_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_e, "elecCS_mGluino_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_avgWeight, "avgWeight_mGluino_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
      }else if((std::string(currentTree.Data()).find(std::string("T2"))) != std::string::npos){
        sprintf(buffer, "mStop_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_mu, "muCS_mStop_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_e, "elecCS_mStop_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
        sprintf(buffer_avgWeight, "avgWeight_mStop_%.0f_mLSP_%.0f", SusyMotherMass, SusyLSPMass);
      }else{
        std::cout<<"No valid sample found (T1/T2/T5)!"<<std::endl;
        return;
      }

      histVec.push_back(new TH1D(buffer, buffer, nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5));
      histVec_muCS.push_back(new TH1D(buffer_mu, buffer_mu, nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5));
      histVec_eCS.push_back(new TH1D(buffer_e, buffer_e, nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5));
      histVec_avgWeight.push_back(new TH1D(buffer_avgWeight, buffer_avgWeight, nSearchBinsTotal, 0.5, nSearchBinsTotal+0.5));

      found = histVec.size()-1;
      histVec.at(found)->Sumw2();
      lspMass.push_back(SusyLSPMass);
      mothMass.push_back(SusyMotherMass);
    }

    //fill event 4 times weighting with the btag probability
    for(int i = 0; i < nLoops; i++){
      if(MuonsNum > 0) histVec_muCS.at(found)->Fill(Bin_bTags.at(i), scaledWeight*bTagProb->at(i));
      if(ElectronsNum > 0) histVec_eCS.at(found)->Fill(Bin_bTags.at(i), scaledWeight*bTagProb->at(i));
      histVec_avgWeight.at(found)->Fill(Bin_bTags.at(i), scaledWeight*bTagProb->at(i));
      
      histVec.at(found)->Fill(Bin_bTags.at(i), totalWeight_BTags->at(i)*scaleFactorWeight/2*bTagProb->at(i));
    }
  }

  std::cout<<"Finished"<<std::endl;

  TFile *LLoutPutFile = new TFile(OutputPath_Prediction,"RECREATE");
  LLoutPutFile->cd();
  LLoutPutFile->mkdir("SignalContamination");
  TDirectory *dPreMC = (TDirectory*)LLoutPutFile->Get("SignalContamination");
  dPreMC->cd();

  for(unsigned int i = 0; i < histVec.size(); i++){
    SetBinLabel(histVec.at(i), SearchBins_);
    histVec.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Electron_CS");
  TDirectory *dElecMC = (TDirectory*)LLoutPutFile->Get("Electron_CS");
  dElecMC->cd();

  for(unsigned int i = 0; i < histVec_eCS.size(); i++){
    SetBinLabel(histVec_eCS.at(i), SearchBins_);
    histVec_eCS.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Muon_CS");
  TDirectory *dMuMC = (TDirectory*)LLoutPutFile->Get("Muon_CS");
  dMuMC->cd();

  for(unsigned int i = 0; i < histVec_muCS.size(); i++){
    SetBinLabel(histVec_muCS.at(i), SearchBins_);
    histVec_muCS.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("AvgWeight");
  TDirectory *dAvgWeight = (TDirectory*)LLoutPutFile->Get("AvgWeight");
  dAvgWeight->cd();

  for(unsigned int i = 0; i < histVec_muCS.size(); i++){
    SetBinLabel(histVec_avgWeight.at(i), SearchBins_);
    histVec_avgWeight.at(i)->Divide(histVec.at(i), histVec_avgWeight.at(i));
    histVec_avgWeight.at(i)->Write();
  }
/*
  for(unsigned int i_hist = 0; i_hist < histVec_muCS.size(); i_hist++){
	std::cout<<"mMother"<<mothMass.at(i_hist)<<"_mLSP"<<lspMass.at(i_hist)<<": "<<histVec_muCS.at(i_hist)->Integral()<<std::endl;
  }
*/
  std::cout<<"Saved Output to "<<OutputPath_Prediction<<std::endl;

  if(doSignalContaminationStudy){
    std::cout<<"Signal Contamination Study: "<<OutputPath_Prediction<<std::endl;

    TFile *predFile = TFile::Open("LLPrediction.root", "READ");
    TH1F* h_pred = (TH1F*) predFile->Get("Prediction_MC/totalPred_LL_MC")->Clone();

    std::cout.setf(ios::fixed, ios::floatfield);
    std::cout.precision(4);

    for(unsigned int i_hist = 0; i_hist < histVec.size(); i_hist++){
    	// T1tttt
      if((abs(1-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
        || (abs(400-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
        || (abs(600-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
        || (abs(800-lspMass.at(i_hist)) < 0.1 && abs(1200-mothMass.at(i_hist)) < 0.1)
        || (abs(800-lspMass.at(i_hist)) < 0.1 && abs(1400-mothMass.at(i_hist)) < 0.1)){

      // T5qqqqVV
  //    if((abs(1-lspMass.at(i_hist)) < 0.1 && abs(1700-mothMass.at(i_hist)) < 0.1)
  //      || (abs(600-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
  //      || (abs(800-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
  //      || (abs(800-lspMass.at(i_hist)) < 0.1 && abs(1000-mothMass.at(i_hist)) < 0.1)){

      // T2tt
  //    if((abs(1-lspMass.at(i_hist)) < 0.1 && abs(800-mothMass.at(i_hist)) < 0.1)
  //      || (abs(300-lspMass.at(i_hist)) < 0.1 && abs(800-mothMass.at(i_hist)) < 0.1)
  //      || (abs(300-lspMass.at(i_hist)) < 0.1 && abs(600-mothMass.at(i_hist)) < 0.1)
  //      || (abs(300-lspMass.at(i_hist)) < 0.1 && abs(400-mothMass.at(i_hist)) < 0.1)
  //      || (abs(250-lspMass.at(i_hist)) < 0.1 && abs(450-mothMass.at(i_hist)) < 0.1)
  //      || (abs(200-lspMass.at(i_hist)) < 0.1 && abs(300-mothMass.at(i_hist)) < 0.1)
  //      || (abs(50-lspMass.at(i_hist)) < 0.1 && abs(700-mothMass.at(i_hist)) < 0.1)
  //      || (abs(1-lspMass.at(i_hist)) < 0.1 && abs(175-mothMass.at(i_hist)) < 0.1)){

        std::cout << histVec.at(i_hist)->GetName() << ": " << std::endl;
        double max = 0., maxBg = 0., maxSig =0.;
        double bgSum = 0., sigSum =0.;
        int max_bin = 0;
        std::vector<double> relVals;

        for(int i_bin = 1; i_bin <= h_pred->GetNbinsX(); i_bin++){
          //std::cout << "     Bin " << i_bin << "(" << histVec.at(i_hist)->GetXaxis()->GetBinLabel(i_bin) << "): Increase: " << histVec.at(i_hist)->GetBinContent(i_bin) / (h_pred->GetBinContent(i_bin)+histVec.at(i_hist)->GetBinContent(i_bin)) << " (tt+W+t: " << h_pred->GetBinContent(i_bin) << "evts; Signal: "<< histVec.at(i_hist)->GetBinContent(i_bin) << "evts)" << std::endl;

          if(i_bin == 124 || i_bin == 134 || i_bin == 144 || i_bin == 154){
            relVals.push_back(0.);
            continue;
          }

          if(h_pred->GetBinContent(i_bin) < 0.00001){
            std::cout<<"No events in prediction: bin "<<i_bin<<std::endl;
            relVals.push_back(0.);
            continue;
          }

          bgSum += h_pred->GetBinContent(i_bin);
          sigSum += histVec.at(i_hist)->GetBinContent(i_bin);

          relVals.push_back(histVec.at(i_hist)->GetBinContent(i_bin)/(h_pred->GetBinContent(i_bin)+histVec.at(i_hist)->GetBinContent(i_bin)));

          double signalCont = histVec.at(i_hist)->GetBinContent(i_bin) / (h_pred->GetBinContent(i_bin)+histVec.at(i_hist)->GetBinContent(i_bin));
          if(max < signalCont){
            maxBg = h_pred->GetBinContent(i_bin);
            maxSig = histVec.at(i_hist)->GetBinContent(i_bin);
            max = signalCont;
            max_bin = i_bin;
          }
        }

        auto biggest = std::max_element(std::begin(relVals), std::end(relVals));
        double bgHighSum = 0., sigHighSum =0.;
        for(int i = 0; i<5; i++){
          //std::cout << *biggest << "; bg: " << h_pred->GetBinContent(std::distance(std::begin(relVals), biggest)+1) << "; sig: " << histVec.at(i_hist)->GetBinContent(std::distance(std::begin(relVals), biggest)+1) << std::endl;
          bgHighSum += h_pred->GetBinContent(std::distance(std::begin(relVals), biggest)+1);
          sigHighSum += histVec.at(i_hist)->GetBinContent(std::distance(std::begin(relVals), biggest)+1);
          *biggest = 0.;
          biggest = std::max_element(std::begin(relVals), std::end(relVals));
        }
        
        std::cout << "Avg. Signal Contamination baseline sig/(sig+bg): " << sigSum << "/(" << sigSum << "+" << bgSum << ")="<< sigSum/(bgSum+sigSum) << std::endl;
        std::cout << "Avg. Signal Contamination from 5 highest bins sig/(sig+bg): " << sigHighSum << "/(" << sigHighSum << "+" << bgHighSum << ")="<< sigHighSum/(sigHighSum+bgHighSum) << "\n" << std::endl;
        //std::cout << "Maximal increase from Signal Contamination in bin " << max_bin << "(" << histVec.at(i_hist)->GetXaxis()->GetBinLabel(max_bin) << "): " << max << std::endl;
      }
    }
  }
  // end of signal contamination study

}

void SetBinLabel(TH1D* hist, SearchBins* SB, TString name){
  for(int bi = 1; bi < hist->GetNbinsX()+1; bi++){
    if(name == "") hist->GetXaxis()->SetBinLabel(bi, SB->GetSearchBin(bi)->getString());
    else hist->GetXaxis()->SetBinLabel(bi, name + TString("_") + SB->GetSearchBin(bi)->getString());
  }

  hist -> GetXaxis() -> LabelsOption("v");
}