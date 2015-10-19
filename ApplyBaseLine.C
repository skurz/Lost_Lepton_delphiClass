#include <TChain.h>
#include <TFile.h>
#include <iostream>




void ApplyBaseLine(){

  const int nChains = 14;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }

  TString fileNames[nChains] = {"TTJets_SingleLeptFromT", "TTJets_SingleLeptFromTbar", "TTJets_DiLept", "TTJets_HT-600to800", "TTJets_HT-800to1200", "TTJets_HT-1200to2500", "TTJets_HT-2500toInf", "WJetsToLNu_HT-200To400", "WJetsToLNu_HT-400To600", "WJetsToLNu_HT-600To800", "WJetsToLNu_HT-800To1200", "WJetsToLNu_HT-1200To2500", "WJetsToLNu_HT-2500ToInf", "ST_all"};

  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/inclusive/*TTJets_SingleLeptFromT_*.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/inclusive/*TTJets_SingleLeptFromTbar_*.root");

  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/inclusive/*TTJets_DiLept*.root");

  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*TTJets_HT-600to800*.root");
  Effchain[4]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*TTJets_HT-800to1200*.root");
  Effchain[5]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*TTJets_HT-1200to2500*.root");
  Effchain[6]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*TTJets_HT-2500toInf*.root");

  Effchain[7]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-200To400*.root");
  Effchain[8]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-400To600*.root"); 
  Effchain[9]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-600To800*.root");
  Effchain[10]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-800To1200*.root"); 
  Effchain[11]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-1200To2500*.root"); 
  Effchain[12]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/HTbinned/*WJetsToLNu_HT-2500ToInf*.root"); 

  Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/*.root");
  //Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/ST_t-channel_antitop_4f_leptonDecays/*.root");
  //Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/ST_t-channel_top_4f_leptonDecays/*.root");
  //Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/ST_tW_antitop_5f_inclusiveDecays/*.root");
  //Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/ST_tW_top_5f_inclusiveDecays/*.root"); 
  //Effchain[13]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/jack_TAP_oct16/singleT/ST_s-channel_4f_leptonDecays/*.root");

  for(Int_t iChain=0; iChain<nChains; iChain++){
    std::cout<<"Begin Chain "<<iChain<<" ("<<fileNames[iChain]<<")"<<std::endl;

    Long64_t nentries = Effchain[iChain]->GetEntries();
    Double_t HT;
    Double_t MHT;
    Int_t    NJets;
    Double_t        DeltaPhi1;
    Double_t        DeltaPhi2;
    Double_t        DeltaPhi3;
    Double_t        DeltaPhi4;

    Effchain[iChain]->SetBranchAddress("HT",&HT);
    Effchain[iChain]->SetBranchAddress("MHT",&MHT);
    Effchain[iChain]->SetBranchAddress("NJets",&NJets);
    Effchain[iChain]->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
    Effchain[iChain]->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
    Effchain[iChain]->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
    Effchain[iChain]->SetBranchAddress("DeltaPhi4", &DeltaPhi4);

    /*
    std::string infname=Effchain[iChain]->GetFile()->GetName();
    std::string baseName(infname);
    size_t pos=baseName.rfind("/");
    if(pos!=std::string::npos){
      if(pos!=baseName.size()-1){
        baseName.erase(0,pos+1);
      }
    }
    */


    TFile *newfile = new TFile(TString("/nfs/dust/cms/user/kurzsimo/LostLepton/TAP_baseline/") + fileNames[iChain] + TString(".root"),"recreate");
    TTree *newtree = Effchain[iChain]->CloneTree(0);


    for (Long64_t i=0;i<nentries; i++) {
      Effchain[iChain]->GetEntry(i);
      if(HT < 500) continue;
      if(MHT < 200) continue;
      if(NJets < 4) continue;
      if(DeltaPhi1 < 0.5 || DeltaPhi2 < 0.5 || DeltaPhi3 < 0.3 || DeltaPhi4 < 0.3) continue;
      newtree->Fill();
    }

    newtree->Print();
    newtree->AutoSave();
    delete newtree;
    delete newfile;
  }
}
