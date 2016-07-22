#!/bin/bash
# My first script

echo "->Merging files"
hadd -f Prediction_ttbar.root Prediction_separate/Prediction_{0..6}.root&
hadd -f Prediction_wjets.root Prediction_separate/Prediction_{7..13}.root&
hadd -f Prediction_singlet.root Prediction_separate/Prediction_{14..18}.root&
hadd -f Prediction_rare.root Prediction_separate/Prediction_{19..32}.root&
wait
echo "->Done"
