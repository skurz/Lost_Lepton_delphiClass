# RA2b Lost Lepton Background Prediction

- Optimized for CMSSW_7_6_0 or later
## How to set up the project
1. Check out code:

  ```
  git clone https://github.com/skurz/Lost_Lepton_delphiClass.git
  ```

## Run Package 

- If set up properly (check source files in 'ttbar/Make...C', 'wpj/Make...C', 'singlet/Make...C', '/rare/Make...C'), the bash script 'runAll.sh' can be used to run steps 1)-3) or 'runPrediction.sh' for steps 2)+3)

- Step-by-step walkthrough (details on how to recalculate the systematics and other adjustments like the definitions of SearchBins, see step 3):

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

3. Check path to Skims in ExpecMaker.h and Prediction.h (The Skims are necessary since the weights for b-tag reweighting are included.)
    ```
    const string path_toSkims("/nfs/dust/cms/user/kurzsimo/LostLepton/skims_v12/SLe/tree_");
    ```

4. Check source files (Trees/Skims) in

    ```
    MakeExpectation_separate.C  // has to be run on full Trees
    MakePrediction_separate.C   // can also be run on Skims
    ```

    If you want to run the prediction on the full nTuples (slower!), please set the following variable in Prediction.h

    ```
    const bool runOnNtuples = true;
    ```

5. Run code:
  
    ```
    root -l MakeExpectation_separate.C+                 // Do the expectation (MC truth)
    hadd Expectation.root Expectation_separate/*.root
    root -l MakeEff.C+                                  // Generate the efficiency histograms
    root -l MakePrediction_separate.C+                  // Do the prediction based on the MC events
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
    root -l MakePrediction_Data.C+  // Do the prediction based on Data
    ```
  
### 3) Produce final output 'LLPrediction.root' for e.g. integration, closure test etc. (after completing step 1&2):

1. Check PlotMaker.C if

    ```
    const bool doQCDbinning = false;                // Present output in QCD binning (depending on what you want)
    const bool doBtagProbabilities = true;          // Weight MC events with bTag probabilities
    const Double_t scaleFactorWeight = 35862.351;   // Scale all MC weights by this factor
    const bool doCombinedUnc = true;                // Add some of the uncertainties in quadrature
    ```

    If you want to change the correlation of the uncertainties , have a look at void SaveFraction(..) in PlotMaker.h
  
3. Run code:
  
    ```
    root -l PlotMaker.C+
    ```

### 4) Produce closure plot or data/MC comparison for paper ('LLPrediction.root' has to exist):

1. Check 'Plot_searchBin_full_extended2016.C' if:
   
    ```
    void Plot_searchBin_full_extended2016(string option="", int pull=0){...  // use option="QCD" to show in QCD binning -> needs LLPrediction.root in QCD binning!    
    bool doDataVsMC = false;                                    // true if you want to show data/MC instead
    ```

    Some additional changes might be necessary if the SearchBins were changed (separation lines in plot etc)
  
2. Run code:
  
    ```
    root -l Plot_searchBin_full_extended2016.C
    ```

3. For 1D closure plots run (use script runClosurePlots.sh to produce all plots):
  
    ```
    root -l Plot_closure.C
    ```

    The settings can be changed by passing a string

    ```
    Plot_closure(string cutname="baseline", string histname="MHT",string option="ExpVsPre",bool zoom=true, bool debug=false)
    ```


## Do signal contamination studies ('Efficiencies.root' has to exist). 

1. Check Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1  // -1 for prediction in low delta Phi region
    ```
    
2. Check Prediction.h if
    
    ```
    const bool runOnData = false;
    const bool runOnStandardModelMC = false;
    const bool runOnSignalMC = true;
    ```
    The correct production for the Signal should be picked automatically based on the filename of the skims (T1, T2, T5). 
    
3. Check source files (Trees/Skims) in

    ```
    MakePrediction_Scan.C  // has to be run on either full Trees or Skims, however Skims preferred (runtime)
    ```
    
4. Produce trees (use scripts runSignalContamination.sh and runSignalContamination_mixed.sh to run all of them):
  
    ```
    root -l MakePrediction_Scan.C+
    hadd MakePrediction_Scan_T1tttt.root Prediction_Scan/Prediction_Scan_T1tttt*.root // e.g. for T1tttt
    ```

5. Check settings for output in 'SignalContamination.C':

    ```
    bool doQCDbinning = false; // true for output in QCD binning
  
    TString InputPath_Prediction("Prediction_Scan_T1tttt.root");
    TString OutputPath_Prediction("LLContamination_T1tttt.root");
    ```

6. Produce output for integration:

    ```
    root -l SignalContamination.C+
    ```


## Modifications: SearchBins, recalculation of uncertainties etc

1. LLTools.h

  - Trigger Efficiencies for SM and Signal. Not applied right now, also has to be enabled in Prediction.h/Expectation.h
  
    ```
    static double GetTriggerEffWeight(Double_t MHT){...}
    static double GetSignalTriggerEffWeight(Double_t MHT) {...}
    ```

2. SearchBins.h

  - The definition of the SearchBins

3. Prediction.h: Uncertainties

  - Lepton SFs: Adjust the path if new SFs are available
  
    ```
    // Elec ID/Iso
    const TString path_elecID("SFs/scaleFactors_electrons.root");
    const TString hist_elecID("GsfElectronToVeto");
    const TString path_elecIso("SFs/scaleFactors_electrons.root");
    const TString hist_elecIso("MVAVLooseElectronToMini");

    // Muon ID/Iso
    const TString path_muID("SFs/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root");
    const TString hist_muID("pt_abseta_PLOT_pair_probeMultiplicity_bin0");
    const TString path_muIso("SFs/TnP_MuonID_NUM_MiniIsoTight_DENOM_MediumID_VAR_map_pt_eta.root");
    const TString hist_muIso("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_Medium2016_pass");

    // Muon tracking inefficiency
    const TString path_muonTrk("SFs/general_tracks_and_early_general_tracks_corr_ratio.root");
    const TString hist_muonTrkHighPt("mutrksfptg10");
    const TString hist_muonTrkLowPt("mutrksfptl10");

    // Electron tracking inefficiency
    const TString path_elecTrk("SFs/egammaEffi.txt_SF2D.root");
    const TString hist_elecTrk("EGamma_SF2D");
    ```

    In case Tracking SFs are no longer needed, change bool in Prediction.h
  
    ```
    const bool doTrackingCorrection = true;
    ```

   - Lepton SF Uncertainties: Somethimes an additional systematic has to be added on top of what is stored in the histogram. This has to be set directly in Prediction.C when calling the function

    ```
    GetSFUnc(TH2 *hist, Double_t xVal, Double_t yVal, double addSys = 0.)
    ```

  - PileUp Corrections (currently only used for signal scan):
   
    ```
    const TString path_puHist("PU/PileupHistograms_0721_63mb_pm5.root");
    ```
    
  - bTag corrections / bTag reweighting:
  
    ```
    const string path_bTagCalib("btag/CSVv2_Moriond17_B_H_mod.csv");
    const string path_bTagCalibFastSim("btag/fastsim_csvv2_ttbar_26_1_2017.csv");
    ```
  
  - ISR corrections (currently only used for signal scan):
   
    ```
    const TString path_ISRcorr("isr_corrections/ISRWeights.root");
    ```

  - Other uncertaintes that are calculated within our group
   
    ```
    const TString path_AccPDF_up("AcceptanceUncertainty/PDFuncertainty_up.root");       // PDF variation (see below how to do recalculate the histograms)
    const TString path_AccPDF_down("AcceptanceUncertainty/PDFuncertainty_down.root");
    const TString path_AccQ2_up("AcceptanceUncertainty/Q2uncertainty_up.root");         // Renormalization / Factorization scale (see below how to do recalculate the histograms)
    const TString path_AccQ2_down("AcceptanceUncertainty/Q2uncertainty_down.root");
    const TString path_MTWunc("MTWUncertainty/MTWuncertainty.root");                    // MTW cut efficiency (see below how to do recalculate the histograms)
    const TString path_isoTrackunc("IsoTrackUncertainty/NJets_uncertainty.root");       // Iso track veto efficiency (usually provided by Jack, TAP)
    ```
    
4. Derivation of the uncertainties on the acceptance and MTW cut efficiency (Expectation.root needed, see step 1)

    - MTW cut efficiency: Run VaryMet.C

    - Acceptance efficiency: Run VaryPDFs.C, and VaryQ2.C TWICE and adjust the following lines (asymmetric uncertainty)

    ```
    TString outName("AcceptanceUncertainty/PDFuncertainty_up.root");
    bool lower = false;
    ```

