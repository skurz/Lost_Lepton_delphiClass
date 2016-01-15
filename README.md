# RA2b Lost Lepton Background Prediction

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
  
3. Run on Standard Model MC:

  - Check ExpecMaker.h and Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1 // -1 for prediction in low delta Phi region
    ```

  - Check Prediction.h if
    
    ```
    const bool runOnData = false;
    const bool runOnStandardModelMC = true;
    const bool runOnSignalMC = false; 
    ```
  
  - Run code
  
    ```
    root -l MakeExpectation_separate.C+  // has to be run on full Trees
    hadd Expectation.root Expectation_separate/*.root
    root -l MakeEff.C+
    root -l MakePrediction_separate.C+  // can also be run on Skims
    hadd Prediction.root Prediction_separate/*.root
    ```
    
4. Run on Data (after completing step 3):
   
  - Check Prediction.h if
  
    ```
    const int useDeltaPhiCut = 1  // -1 for prediction in low delta Phi region
    ```
    
  - Check Prediction.h if
    
    ```
    const bool runOnData = true;
    const bool runOnStandardModelMC = false;
    const bool runOnSignalMC = false; 
    ```
  
  - Run code
  
    ```
    root -l MakePrediction_Data.C+  // can also be run on Skims
    ```
  
5. Produce 'LLPrediction.root' for e.g. integration, closure test etc. (after completing step 3&4):

  - Check ResultsPlot.C if
  
    ```
    bool doQCDbinning = false; // true for output in QCD binning
    Double_t scaleFactorWeight = 2262; // scale MC to this data luminosity
    ```
    
  - If no data available, use MC tree for data tree:
  
    ```
    TString InputPath_Prediction("Prediction.root");
    TString InputPath_Prediction_Data("Prediction.root"); // instead of Prediction_data.root
    ```
  
  - Run Code
  
    ```
    ResultsPlot.C+
    ```
