//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 24 04:56:27 2016 by ROOT version 6.02/05
// from TTree PreSelection/PreSelection
// found on file: /eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV6/Spring15v2.TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_3_RA2AnalysisTree.root
//////////////////////////////////////////////////////////

#ifndef topPt_h
#define topPt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TProofOutputFile.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TLorentzVector.h"

class topPt : public TSelector {
public :
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // output tree
   TTree *tOut = 0;

   TProofOutputFile* ProofFile = 0;
   TFile *outPutFile = 0;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           BTags;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi4;
   vector<TLorentzVector> *Electrons = 0;
   vector<TLorentzVector> *GenEls = 0;
   vector<TLorentzVector> *GenMus = 0;
   vector<TLorentzVector> *GenParticles = 0;
//   vector<int>     *GenParticles_ParentId = 0;
//   vector<int>     *GenParticles_ParentIdx = 0;
   vector<int>     *GenParticles_PdgId = 0;
//   vector<int>     *GenParticles_Status = 0;
   Double_t        HT;
   Double_t        madHT;
   Double_t        MHT;
   vector<TLorentzVector> *Muons = 0;
   Int_t           NJets;
   Double_t        Weight;

  Double_t       topPtSF;
  std::vector<double> top_Pt;



   // List of branches
   TBranch        *b_BTags;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_Electrons;   //!
   TBranch        *b_GenEls;   //!
   TBranch        *b_GenMus;   //!
   TBranch        *b_GenParticles;   //!
//   TBranch        *b_GenParticles_ParentId;   //!
//   TBranch        *b_GenParticles_ParentIdx;   //!
   TBranch        *b_GenParticles_PdgId;   //!
//   TBranch        *b_GenParticles_Status;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_madHT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_Muons;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_Weight;   //!


   topPt(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~topPt() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(topPt,0);
};

#endif

#ifdef topPt_cxx
void topPt::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchStatus("*", 0);

   fChain->SetBranchStatus("BTags", 1);
   fChain->SetBranchStatus("DeltaPhi1", 1);
   fChain->SetBranchStatus("DeltaPhi2", 1);
   fChain->SetBranchStatus("DeltaPhi3", 1);
   fChain->SetBranchStatus("DeltaPhi4", 1);
   fChain->SetBranchStatus("Electrons", 1);
   fChain->SetBranchStatus("GenEls", 1);
   fChain->SetBranchStatus("GenMus", 1);
   fChain->SetBranchStatus("GenParticles", 1);
//   fChain->SetBranchStatus("GenParticles_ParentId", 1);
//   fChain->SetBranchStatus("GenParticles_ParentIdx", 1);
   fChain->SetBranchStatus("GenParticles_PdgId", 1);
//   fChain->SetBranchStatus("GenParticles_Status", 1);
   fChain->SetBranchStatus("HT", 1);
   fChain->SetBranchStatus("madHT", 1);
   fChain->SetBranchStatus("MHT", 1);
   fChain->SetBranchStatus("Muons", 1);
   fChain->SetBranchStatus("NJets", 1);
   fChain->SetBranchStatus("Weight", 1);

   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
   fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
   fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
//   fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
//   fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
   fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
//   fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
}

Bool_t topPt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef topPt_cxx
