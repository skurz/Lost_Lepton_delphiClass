# RA2b Lost Lepton Background Prediction

- Optimized for CMSSW_7_4_6_patch6 (should work on every version though)

## How to set up the project
1. Check out code:

  ```
  git clone https://github.com/skurz/Lost_Lepton_delphiClass.git
  ```
2. Extract eventFilter/csc2015.txt (>100MB):

  ```
  cd eventFilter
  tar -zxvf csc2015.tar.gz
  ```


## Run Package 

- If set up properly, the bash script runAll.sh can be used to run steps 1)-3) or runPrediction.sh for steps 2)+3)

### 1) Run on Standard Model MC:

1. Check ExpecMaker.h and Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1 // -1 for prediction in low delta Phi region
    ```

2. Check Prediction.h if
    
    ```
    const bool runOnData = false;
    const bool runOnStandardModelMC = true;
    const bool runOnSignalMC = false; 
    ```
    
3. Check source files (Trees/Skims) in

    ```
    MakeExpectation_separate.C  // has to be run on full Trees
    MakePrediction_separate.C  // can also be run on Skims
    ```

4. Run code:
  
    ```
    root -l MakeExpectation_separate.C+
    hadd Expectation.root Expectation_separate/*.root
    root -l MakeEff.C+
    root -l MakePrediction_separate.C+
    hadd Prediction.root Prediction_separate/*.root
    ```
    
### 2) Run on Data (after completing step 1):
   
1. Check Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1  // -1 for prediction in low delta Phi region
    ```
    
2. Check Prediction.h if
    
    ```
    const bool runOnData = true;
    const bool runOnStandardModelMC = false;
    const bool runOnSignalMC = false; 
    ```
    
3. Check source files (Trees/Skims) in

    ```
    MakePrediction_Data.C  // can be run on either full Trees or Skims

    ```
    
4. Run code:
  
    ```
    root -l MakePrediction_Data.C+
    ```
  
### 3) Produce final output 'LLPrediction.root' for e.g. integration, closure test etc. (after completing step 1&2):

1. Check ResultsPlot.C if
  
    ```
    bool doQCDbinning = false; // true for output in QCD binning
    Double_t scaleFactorWeight = 2262; // scale MC to this data luminosity
    ```
    
2. If no data available, use MC tree for data tree:
  
    ```
    TString InputPath_Prediction("Prediction.root");
    TString InputPath_Prediction_Data("Prediction.root"); // instead of Prediction_data.root
    ```
  
3. Run code:
  
    ```
    root -l ResultsPlot.C+
    ```

### 4) Produce closure plot or data/MC comparison for paper ('LLPrediction.root' has to exist):

1. Check 'Plot_searchBin_full.C' if:
   
    ```
    void Plot_searchBin_full(string option="", int pull=0){... // use option="QCD" to show in QCD binning -> needs LLPrediction.root in QCD binning!
    
    bool doDataVsMC = false; // true if you want to show data/MC instead
    ```
  
2. Run code:
  
    ```
    root -l Plot_searchBin_full.C
    ```


## Do signal contamination studies ('Efficiencies.root' has to exist)

1. Check Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1  // -1 for prediction in low delta Phi region
    ```
    
2. Check Prediction.h if
    
    ```
    const bool runOnData = false;
    const bool runOnStandardModelMC = false;
    const bool runOnSignalMC = true;

    const string path_xsec("xsec/dict_xsec.txt"); // using correct production xsec! gluino: dict_xsec.txt; stop: dict_xsec_T2.txt
    ```
    
3. Check source files (Trees/Skims) in

    ```
    MakePrediction_Scan.C  // has to be run on either full Trees or Skims, however Skims preferred (runtime)
    ```
    
4. Produce trees:
  
    ```
    root -l MakePrediction_Scan.C+
    hadd MakePrediction_Scan_T1tttt.root Prediction_Scan/Prediction_Scan_T1tttt*.root // e.g. for T1tttt
    ```

5. Check settings for output in 'SignalContamination.C':

    ```
    Double_t scaleFactorWeight = 2262; // scale MC to this luminosity

    bool doQCDbinning = false; // true for output in QCD binning
  
    TString InputPath_Prediction("Prediction_Scan_T1tttt.root");
    TString OutputPath_Prediction("LLContamination_T1tttt.root");

    string motherName("Gluino"); // name of SUSY mother particle: T1/T5 "Gluino"; T2 "Stop" (capitalized!)
    ```

6. Produce output for integration:

    ```
    root -l SignalContamination.C+
    ```


## Changes that might be necessary for next iteration

1. LLTools.h

  - Trigger Efficiencies for SM and Signal. Hardcoded in the following methods:
  
    ```
    static double GetTriggerEffWeight(Double_t MHT){...}
    static double GetSignalTriggerEffWeight(Double_t MHT) {...}
    ```

2. Prediction.h
 
  - CSCTightHaloFilter from list (only used for data):
   
    ```
    const string path_evtListFilter("eventFilter/csc2015.txt");
    ```

  - Lepton SFs:
  
    ```
    const TString path_elecID("SFs/kinematicBinSFele.root");
    const TString hist_elecID("CutBasedVeto");
    const TString path_elecIso("SFs/kinematicBinSFele.root");
    const TString hist_elecIso("MiniIso0p1_vs_RelActivity");
    
    const TString path_muID("SFs/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root");
    const TString hist_muID("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    const TString path_muIso("SFs/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
    // IMPORTANT!!!
    // muIso: still binned in pt/eta since this was recommended! Has to be changed for Moriond (also in Prediction.C when getting the uncertainties)!
    const TString hist_muIso("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");
    ```

  - PileUp Corrections (only used for signal scan):
   
    ```
    const TString path_puHist("PU/PileupHistograms_1117.root");
    ```
    
  - bTag corrections (only used for signal scan):
  
    ```
    const string path_bTagCalib("btag/CSVv2_mod.csv");
    const string path_bTagCalibFastSim("btag/CSV_13TEV_Combined_20_11_2015.csv");
    ```
  
  - ISR corrections (not recommended right now - maybe used for signal scan in future):
   
    ```
    const TString path_ISRcorr("isr_corrections/ISRWeights.root");
    // has to be uncommented in Prediction::Init(Tree*)
    //if(runOnSignalMC) doISRcorr = true;
    ```
    
  
