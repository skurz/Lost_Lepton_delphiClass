#define topPt_cxx

#include "topPt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TSystem.h>
#include <iostream>

void topPt::Begin(TTree * /*tree*/)
{

   TString option = GetOption();

}

void topPt::SlaveBegin(TTree * /*tree*/)
{
   
   gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

   TString option = GetOption();

   ProofFile = new TProofOutputFile(option, TProofOutputFile::kMerge);
   ProofFile->SetOutputFileName(option);

   outPutFile = ProofFile->OpenFile("RECREATE");


   tOut = new TTree("PreSelection","a simple Tree with simple variables");

   tOut->AutoSave();

   tOut->Branch("BTags", &BTags);
   tOut->Branch("DeltaPhi1", &DeltaPhi1);
   tOut->Branch("DeltaPhi2", &DeltaPhi2);
   tOut->Branch("DeltaPhi3", &DeltaPhi3);
   tOut->Branch("DeltaPhi4", &DeltaPhi4);
   tOut->Branch("Electrons", &Electrons);
   tOut->Branch("GenEls", &GenEls);
   tOut->Branch("GenMus", &GenMus);
   tOut->Branch("GenParticles", &GenParticles);
//   tOut->Branch("GenParticles_ParentId", &GenParticles_ParentId);
//   tOut->Branch("GenParticles_ParentIdx", &GenParticles_ParentIdx);
   tOut->Branch("GenParticles_PdgId", &GenParticles_PdgId);
//   tOut->Branch("GenParticles_Status", &GenParticles_Status);
   tOut->Branch("HT", &HT);
   tOut->Branch("madHT", &madHT);
   tOut->Branch("MHT", &MHT);
   tOut->Branch("Muons", &Muons);
   tOut->Branch("NJets", &NJets);
   tOut->Branch("Weight", &Weight);

   tOut->Branch("topPtSF", &topPtSF);
   tOut->Branch("top_Pt", &top_Pt);
}

Bool_t topPt::Process(Long64_t entry)
{
   fChain->GetTree()->GetEntry(entry);

   //if(HT < 250)  return kTRUE;
   //if(MHT < 200)  return kTRUE;
   //if(NJets < 2)  return kTRUE;
   // if(DeltaPhi1 < 0.5 || DeltaPhi2 < 0.5 || DeltaPhi3 < 0.3 || DeltaPhi4 < 0.3)  return kTRUE;

   //if(madHT > 600) return kTRUE;

  top_Pt.clear();

   if(GenParticles->size() != GenParticles_PdgId->size()){
      std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
      }else{
         for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
           if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
             top_Pt.push_back(GenParticles->at(iGen).Pt());
           }
         }
      
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#Example
      if(top_Pt.size() == 2){
         // dilept
         if(GenEls->size() + GenMus->size() == 2){
         topPtSF = std::sqrt(std::exp(0.148-0.00129*(top_Pt.at(0) < 400. ? top_Pt.at(0) : 400.))*std::exp(0.148-0.00129*(top_Pt.at(1) < 400. ? top_Pt.at(1) : 400.)));
         // singlelept
         }else if(GenEls->size() + GenMus->size() == 1){
            topPtSF = std::sqrt(std::exp(0.159-0.00141*(top_Pt.at(0) < 400. ? top_Pt.at(0) : 400.))*std::exp(0.159-0.00141*(top_Pt.at(1) < 400. ? top_Pt.at(1) : 400.)));
         //had
         }else{
            // Usually non-promt (in hadTau evts): use average SF
            topPtSF = std::sqrt(std::exp(0.156-0.00137*(top_Pt.at(0) < 400. ? top_Pt.at(0) : 400.))*std::exp(0.156-0.00137*(top_Pt.at(1) < 400. ? top_Pt.at(1) : 400.)));
            //std::cout << "Cannot do top-pT reweighting! No leptonic top found."<< std::endl; 
         }
      }else{
         topPtSF = -1;
         std::cout << "Cannot do top-pT reweighting! More/Less than 2 tops found."<< std::endl;
         return kTRUE;
      }
   } 


   tOut->Fill();
   return kTRUE;
}

void topPt::SlaveTerminate()
{
   outPutFile->cd();
   tOut->Write();
   ProofFile->Print();
   fOutput->Add(ProofFile);
   tOut->SetDirectory(0);
   outPutFile->Close();
}

void topPt::Terminate()
{
   



}
