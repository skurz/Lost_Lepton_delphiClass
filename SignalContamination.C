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

void SaveClosure(TH1D* prediction, TH1D* expectation, TDirectory* Folder);
UShort_t getMergedBinQCD(UShort_t BinQCD, Int_t NJets);
UShort_t getHTMHTBox(Double_t HT, Double_t MHT);
void SetBinLabel(TH1D* hist);
void SaveFraction(TH1D* Top, TH1D* Bottom, TDirectory* dir);

void SignalContamination()
{

  // General Settings
  TString InputPath_Prediction("Prediction_Scan_T2tt.root");
  TString OutputPath_Prediction("LLContamination_T2tt.root");


  // Scale all MC weights by this factor
  Double_t scaleFactorWeight = 7632; // in units of [pb] //<-check------------------------

  // Present output in QCD binning
  bool doQCDbinning = false;  //<-check------------------------;

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
  UShort_t        selectedIDIsoMuonsNum;
  UShort_t        selectedIDIsoElectronsNum;
  
  Float_t         totalWeightDiLep;
  Float_t         totalWeightDiLepIsoTrackReducedCombined;

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
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoMuonsNum",1);
  LostLeptonPrediction->SetBranchStatus("selectedIDIsoElectronsNum",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLep",1);
  LostLeptonPrediction->SetBranchStatus("totalWeightDiLepIsoTrackReducedCombined",1);
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
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum);
  LostLeptonPrediction->SetBranchAddress("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLep",&totalWeightDiLep);
  LostLeptonPrediction->SetBranchAddress("totalWeightDiLepIsoTrackReducedCombined",&totalWeightDiLepIsoTrackReducedCombined);
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
    if(MTW>100)continue;
    if(selectedIDIsoMuonsNum+selectedIDIsoElectronsNum!=1)continue;

    for(int i = 0; i < 4; i++){
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
    for(int i = 0; i < 4; i++){
      if(selectedIDIsoMuonsNum > 0) histVec_muCS.at(found)->Fill(Bin_bTags.at(i), scaledWeight*bTagProb->at(i));
      if(selectedIDIsoElectronsNum > 0) histVec_eCS.at(found)->Fill(Bin_bTags.at(i), scaledWeight*bTagProb->at(i));
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
    SetBinLabel(histVec.at(i));
    histVec.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Electron_CS");
  TDirectory *dElecMC = (TDirectory*)LLoutPutFile->Get("Electron_CS");
  dElecMC->cd();

  for(unsigned int i = 0; i < histVec_eCS.size(); i++){
    SetBinLabel(histVec_eCS.at(i));
    histVec_eCS.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("Muon_CS");
  TDirectory *dMuMC = (TDirectory*)LLoutPutFile->Get("Muon_CS");
  dMuMC->cd();

  for(unsigned int i = 0; i < histVec_muCS.size(); i++){
    SetBinLabel(histVec_muCS.at(i));
    histVec_muCS.at(i)->Write();
  }

  LLoutPutFile->cd();
  LLoutPutFile->mkdir("AvgWeight");
  TDirectory *dAvgWeight = (TDirectory*)LLoutPutFile->Get("AvgWeight");
  dAvgWeight->cd();

  for(unsigned int i = 0; i < histVec_muCS.size(); i++){
    SetBinLabel(histVec_avgWeight.at(i));
    histVec_avgWeight.at(i)->Divide(histVec.at(i), histVec_avgWeight.at(i));
    histVec_avgWeight.at(i)->Write();
  }
/*
  for(unsigned int i_hist = 0; i_hist < histVec_muCS.size(); i_hist++){
	std::cout<<"mMother"<<mothMass.at(i_hist)<<"_mLSP"<<lspMass.at(i_hist)<<": "<<histVec_muCS.at(i_hist)->Integral()<<std::endl;
  }
*/
  std::cout<<"Saved Output to "<<OutputPath_Prediction<<std::endl;

  std::cout<<"Signal Contamination Study: "<<OutputPath_Prediction<<std::endl;
/*
  TFile *predFile = TFile::Open("LLPrediction_Feb01.root", "READ");
  TH1F* h_pred = (TH1F*) predFile->Get("Prediction_MC/totalPred_LL_MC")->Clone();

  std::cout.setf(ios::fixed, ios::floatfield);
  std::cout.precision(4);

  for(unsigned int i_hist = 0; i_hist < histVec.size(); i_hist++){
//    if((abs(0-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
//      || (abs(300-lspMass.at(i_hist)) < 0.1 && abs(1600-mothMass.at(i_hist)) < 0.1)
//      || (abs(600-lspMass.at(i_hist)) < 0.1 && abs(1500-mothMass.at(i_hist)) < 0.1)
//      || (abs(750-lspMass.at(i_hist)) < 0.1 && abs(1000-mothMass.at(i_hist)) < 0.1)){
//
    if((abs(0-lspMass.at(i_hist)) < 0.1 && abs(1500-mothMass.at(i_hist)) < 0.1)
      || (abs(300-lspMass.at(i_hist)) < 0.1 && abs(1500-mothMass.at(i_hist)) < 0.1)
      || (abs(600-lspMass.at(i_hist)) < 0.1 && abs(1400-mothMass.at(i_hist)) < 0.1)
      || (abs(800-lspMass.at(i_hist)) < 0.1 && abs(1000-mothMass.at(i_hist)) < 0.1)){

      std::cout << histVec.at(i_hist)->GetName() << ": " << std::endl;
      double max = 0., maxBg = 0., maxSig =0.;
      double bgSum = 0., sigSum =0.;
      int max_bin = 0;
      std::vector<double> relVals;

      for(int i_bin = 1; i_bin <= h_pred->GetNbinsX(); i_bin++){
        //std::cout << "     Bin " << i_bin << "(" << histVec.at(i_hist)->GetXaxis()->GetBinLabel(i_bin) << "): Increase: " << histVec.at(i_hist)->GetBinContent(i_bin) / (h_pred->GetBinContent(i_bin)+histVec.at(i_hist)->GetBinContent(i_bin)) << " (tt+W+t: " << h_pred->GetBinContent(i_bin) << "evts; Signal: "<< histVec.at(i_hist)->GetBinContent(i_bin) << "evts)" << std::endl;

        bgSum += h_pred->GetBinContent(i_bin);
        sigSum += histVec.at(i_hist)->GetBinContent(i_bin);

        relVals.push_back(histVec.at(i_hist)->GetBinContent(i_bin)/(h_pred->GetBinContent(i_bin)+histVec.at(i_hist)->GetBinContent(i_bin)));

        if(h_pred->GetBinContent(i_bin) < 0.00001){
          std::cout<<"No events in prediction: bin "<<i_bin<<std::endl;
          continue;
        }

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
        //std::cout << *biggest << std::endl;
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
*/}


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
